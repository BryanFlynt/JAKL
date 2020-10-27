/*
 * task.hpp
 *
 *  Created on: Mar 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_TASK_HPP_
#define INCLUDE_JAKL_DETAIL_TASK_HPP_


#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "jakl/detail/buffer_base.hpp"


namespace jakl {
namespace detail {

/** Internal JAKL task to manage dependencies within a Buffer
 */
class Task : public std::enable_shared_from_this<Task> {

public:

	Task()                             = default;
	Task(const Task& other)            = default;
	Task(Task&& other)                 = default;
	~Task()                            = default;
	Task& operator=(const Task& other) = default;
	Task& operator=(Task&& other)      = default;


	Task(const std::shared_ptr<detail::queue> &q_ptr) : owner_queue_(q_ptr){
	}

	/** Add a new task
	 *
	 * Add a new task to the task graph and schedule for execution
	 */
	void schedule(std::function<void(void)> f) {

		// To keep a copy capture it by copy in the following lambda
		auto execution = [f = std::move(f), task = shared_from_this()] {

			// Wait for tasks to be ready
			task->wait_for_producers();
			task->run_pre_tasks();

			// Execute kernel
			f();

			task->run_post_tasks();

			// Release the buffers written by this task
			task->release_buffers();

			// Notify waiting tasks
			task->notify_consumers();

			// Notify queue
			task->owner_queue->kernel_end();
		};

		// Notify the queue that there is a kernel submitted
		// DO NOT do this from within the execution lambda
		// because the Queue could finish before the thread
		// is scheduled
		owner_queue->kernel_start();

		// Launch in new thread
		std::thread thread(execution);
		thread.detach();
	}


	/** Wait for tasks to be ready
	 */
	void wait_for_producers() {
		for (auto &t : producer_tasks){
			t->wait();
		}
		producer_tasks.clear();
	}

	/** Release the Buffers that were used
	 */
	void release_buffers() {
		for (auto b: buffers_in_use) {
			b->release();
		}
		buffers_in_use.clear();
	}

	/** Notify waiting tasks we are done
	 */
	void notify_consumers() {
		{  // Ensure the lock goes out of scope before notification
			std::unique_lock<std::mutex> ul(task_is_ready_mutex);
			execution_ended = true;
		}
		task_is_ready.notify_all();
	}

	/** Wait for task to be ready
	 *
	 * Wait from another thread for this task to be complete
	 */
	void wait() {
		std::unique_lock<std::mutex> ul(task_is_ready_mutex);
		task_is_ready.wait(ul, [&] { return execution_ended; });
	}

	/** Register a Buffer to this task
	 *
	 * This is how the dependency graph is incrementally built
	 */
	void add_buffer(std::shared_ptr<detail::BufferBase> &buf, bool is_write_mode) {

		// Keep track of the use of the buffer
		buffers_in_use.push_back(buf);

		// Make sure the buffer does not disappear before the kernel can run
		buf->use();

		std::shared_ptr<detail::task> latest_producer;
		if( is_write_mode ) {
			// Set this task as the latest producer
			latest_producer = buf->set_latest_producer(shared_from_this());
		}
		else
			latest_producer = buf->get_latest_producer();

		// If the buffer is to be produced by a task, add the task in the
		// producer list to wait on it before running this task
		//
		// If a buffer is accessed first in write mode and then in read mode,
		// the task will add itself as a producer and will wait for itself
		// when calling \c wait_for_producers, we avoid this by checking that
		// \c latest_producer is not \c this
		//
		if( latest_producer && (latest_producer != shared_from_this()) ){
			producer_tasks.push_back(latest_producer);
		}
	}

	/** Execute the pre-kernel tasks
	 */
	void run_pre_tasks() {
		for (const auto &p : prologues_) {
			p();
		}
		prologues_.clear();
	}

	/** Execute the epilogues tasks
	 */
	void run_post_tasks() {
		for (const auto &p : epilogues_) {
			p();
		}
		epilogues_.clear();
	}

	/** Add a function to run before kernel
	 */
	void add_pre_task(const std::function<void(void)> &f) {
		prologues_.push_back(f);
	}

	/** Add a function to run after kernel
	 */

	void add_post_task(const std::function<void(void)> &f) {
		epilogues_.push_back(f);
	}

	/** Get queue
	 */
	auto get_queue() {
		return owner_queue;
	}

	/** Set the kernel running this task
	 */
	void set_kernel(const std::shared_ptr<detail::kernel> &k) {
		kernel = k;
	}

	/** Get the running kernel if it exists
	 */
	detail::kernel& get_kernel() {
		if( !kernel ) {
			assert(false); // Throw an error
		}
		return *kernel;
	}

	/** Register an Accessor
	 *
	 * Register and Accessor and return the registration order
	 */
	std::size_t register_accessor(std::weak_ptr<detail::accessor_base> a) {
		accessors.push_back(a);
		return accessors.size() - 1;
	}



protected:

	// Buffers used by this task
	std::vector<std::shared_ptr<detail::BufferBase>> buffers_in_use_;

	// Tasks producing the Buffers used by this task
	std::vector<std::shared_ptr<detail::Task>> producer_tasks_;

	// Keep track of any functions to be executed before the kernel
	std::vector<std::function<void(void)>> prologues_;

	// Keep track of any functions to be executed after the kernel
	std::vector<std::function<void(void)>> epilogues_;

	// Flag if execution ended
	bool execution_ended_ = false;

	// To signal when this task is ready
	std::condition_variable task_is_ready_;

	// Mutex to protect the condition variable
	std::mutex task_is_ready_mutex_;

	// Queue used for submission
	std::shared_ptr<detail::queue> owner_queue_;

	// The kernel run by this task, if any
	std::shared_ptr<detail::kernel> kernel_;

	// Accessors indexed by their creation order
	std::vector<std::weak_ptr<detail::accessor_base>> accessors_;

};


}  // namespace detail
}  // namespace jakl




#endif /* INCLUDE_JAKL_DETAIL_TASK_HPP_ */
