/*
 * buffer_base.hpp
 *
 *  Created on: Mar 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_BUFFER_BASE_HPP_
#define INCLUDE_JAKL_DETAIL_BUFFER_BASE_HPP_


#include "jakl/detail/task.hpp"
#include "jakl/core/device.hpp"
#include "jakl/core/system.hpp"

#include <atomic>
#include <cstddef>
#include <memory>
#include <optional>

namespace jakl {
namespace detail {

/** Memory BufferBase
 *
 */
class BufferBase : public std::enable_shared_from_this<BufferBase> {

public:

	BufferBase()                                   = default;
	BufferBase(const BufferBase& other)            = default;
	BufferBase(BufferBase&& other)                 = default;
	~BufferBase()                                  = default;
	BufferBase& operator=(const BufferBase& other) = default;
	BufferBase& operator=(BufferBase&& other)      = default;

	BufferBase() :
		number_of_users(0),
		fresh_device(system::host_device()) {
	}

	~BufferBase() {
		wait();
		if( notify_buffer_destructor ){
			notify_buffer_destructor->set_value();
		}
	}

	/** Wait for this Buffer to be ready
	 */
	void wait() {
		std::unique_lock<std::mutex> ul(ready_mutex);
	    ready.wait(ul, [&](){
	        return number_of_users == 0;
	      });
	  }

	/** Mark this Buffer as in use by a task
	 */
	void use() {
		++number_of_users;
	}

	/** A task has released the buffer
	 */
	  void release() {
	    std::unique_lock<std::mutex> lock(ready_mutex);
	    --number_of_users;
	    if(number_of_users == 0) {
	      // Micro-optimization: unlock before the notification
	      // https://en.cppreference.com/w/cpp/thread/condition_variable/notify_all
	      lock.unlock();
	      // Notify the host consumers or the buffer destructor that it is ready
	      ready.notify_all();
	    }
	  }

	  /** Return the latest producer for the buffer
	   */
	  std::shared_ptr<detail::Task> get_latest_producer() {
	    std::lock_guard<std::mutex> lg(latest_producer_mutex);
	    return latest_producer.lock();
	  }

	  /** Get latest producer
	   *
	   * Return the latest producer for the buffer and set another
	   * future producer
	   */
	  std::shared_ptr<detail::Task>
	  set_latest_producer(std::weak_ptr<detail::Task> newer_latest_producer) {
	    std::lock_guard<std::mutex> lg(latest_producer_mutex);
	    using std::swap;
	    swap(newer_latest_producer, latest_producer);
	    return newer_latest_producer.lock();
	  }

	  /** Add a buffer to the task running the command group
	   */
	  std::shared_ptr<detail::Task>
	  add_to_task(Handler *command_group_handler, bool is_write_mode) {
	    return add_buffer_to_task(command_group_handler,
	                              shared_from_this(),
	                              is_write_mode);
	  }

	  /** Check if data is up to date
	   */
	  bool is_data_up_to_date(const Device& device) {
	    return fresh_device.count(device);
	  }

	  bool is_cached(const Device& device) {
	    return buffer_cache.count(device);
	  }

	  /** Synchronize with host
	   *
	   * Transfer the most up-to-date version of the data to the host
	   *  if the host version is not already up-to-date
	   */
	  void sync_with_host(std::size_t size, void* data) {
	    Device host_device;

	    // Check if host is up to date
	    // Check if fresh_device is empty
	    if (!is_data_up_to_date(host_device) && !fresh_device.empty() ) {
	      auto fresh_context = *(fresh_device.begin());
	      auto fresh_q = fresh_context.get_boost_queue();
	      fresh_q.enqueue_read_buffer(buffer_cache[fresh_context], 0, size, data);
	      fresh_device.insert(host_context);
	    }
	  }

	  /**
	   *
	   * When a transfer is requested this function is called, it will
	   * update the state of the buffer according to the context in which
	   * the accessor is created and the access mode
	   */
	    void update_buffer_state(const trisycl::context& target_ctx,
	                             access::mode mode, std::size_t size, void* data) {
	      /* The \c cl_buffer we put in the cache might get accessed again in the
	         future, this means that we have to always to create it in read/write
	         mode to be able to write to it if it is accessed through a
	         write accessor in the future
	       */
	      auto constexpr flag = CL_MEM_READ_WRITE;

	      /* The buffer is accessed in read mode, we want to transfer the data only if
	         necessary. We start a transfer if the data on the target context is not
	         up to date and then update the fresh context set.
	       */
	      if (mode == access::mode::read) {

	        if (is_data_up_to_date(target_ctx))
	          // If read mode and the data is up-to-date there is nothing to do
	          return;

	        // The data is not up-to-date, we need a transfer
	        // We also want to be sure that the host holds the most recent data
	        sync_with_host(size, data);

	        if (!target_ctx.is_host()) {
	          // If the target context is a device context
	          if (!is_cached(target_ctx)) {
	            /* If not cached, we create the buffer and copy the data
	               at the same time
	            */
	            create_in_cache(target_ctx, size,
	                            (flag | CL_MEM_COPY_HOST_PTR), data);
	            fresh_ctx.insert(target_ctx);
	            return;
	          }

	          /* Else we transfer the data to the existing buffer associated
	             with the target context buffer
	          */
	          auto q = target_ctx.get_boost_queue();
	          q.enqueue_write_buffer(buffer_cache[target_ctx], 0, size, data);
	          fresh_ctx.insert(target_ctx);
	        }
	        return;
	      }


	      /* The buffer might be written to, this means that we have to consider
	         every version of the data obsolete except in the target context

	         We go through the same process as in read mode but in addition
	         we empty the fresh context set and just add the target context

	         If the data is up to date on the target we just have to update
	         the context set and nothing else
	      */
	      if (!is_data_up_to_date(target_ctx)) {

	        if (   mode == access::mode::read_write
	            || mode == access::mode::write
	            || mode == access::mode::atomic) {
	          // If the data is not up-to-date in the target context
	          // We want to host to be up-to-date
	          sync_with_host(size, data);

	          if (!target_ctx.is_host()) {
	            // If the target context is a device context
	            if (!is_cached(target_ctx)) {
	              create_in_cache(target_ctx, size,
	                              (flag | CL_MEM_COPY_HOST_PTR), data);
	            }
	            else {
	              // We update the buffer associated with the target context
	              auto q = target_ctx.get_boost_queue();
	              q.enqueue_write_buffer(buffer_cache[target_ctx], 0, size, data);
	            }
	          }
	        }

	        /* When in discard mode we don't need to transfer any data, we just create
	           the \c cl_buffer if it doesn't exist in the cache
	        */
	        if (   mode == access::mode::discard_write
	            || mode == access::mode::discard_read_write) {
	          /* We only need to create the buffer if it doesn't exist
	             but without copying any data because of the discard mode
	          */
	          if (!target_ctx.is_host() && !is_cached(target_ctx)) {
	            // If the context doesn't exist we create it.
	            /* We don't want to transfer any data so we don't
	               add \c CL_MEM_COPY_HOST_PTR
	            */
	            create_in_cache(target_ctx, size, flag, 0);
	          }
	        }
	      }
	      /* Here we are sure that we are in some kind of write mode,
	         we indicate that all contexts except the target context
	         are not up-to-date anymore
	      */
	      fresh_ctx.clear();
	      fresh_ctx.insert(target_ctx);
	    }


	    /** Returns the cl_buffer for a given context.
	     */
	    boost::compute::buffer get_cl_buffer(const trisycl::context& context) {
	      return buffer_cache[context];
	    }







protected:

	// Count of kernels using this Buffer
	std::atomic<std::size_t> number_of_users;

	// Latest task to produce this buffer
	std::weak_ptr<detail::Task> latest_producer;

	// Mutex to protect access to latest producer
	std::mutex latest_producer_mutex;

	// Buffer ready flag
	std::condition_variable ready;

	// To protect the access to the condition variable
	std::mutex ready_mutex;

	// Use to block until this Buffer is destroyed
	std::optional<std::promise<void>> notify_buffer_destructor;

	// Track Devices in which the data is up to date
	 std::unordered_set<Device> fresh_device;

	 // Buffer-side cache that keeps the
	 std::unordered_map<Device, Buffer> buffer_cache;


};


}  // namespace detail
}  // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_BUFFER_BASE_HPP_ */
