/*
 * queue.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_


#include "jakl/context.hpp"
#include "jakl/device.hpp"
#include "jakl/event.hpp"
#include "jakl/handler.hpp"

#include <list>
#include <memory>

namespace jakl {

// Declare Handler as class
// - circular dependency is keeping it out
class Handler;

namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class queue : public std::enable_shared_from_this<queue>{

public:
	queue()                              = delete;
	queue(const queue& other)            = default;
	queue(queue&& other)                 = default;
	queue& operator=(const queue& other) = default;
	queue& operator=(queue&& other)      = default;
	~queue()                             = default;

	/** Create Queue using provided Context
	 */
	queue(const Context& context) : execution_context_(context){
	}

	/** Submit function to be run
	 */
	template<typename TaskPred>
	Event submit(TaskPred&& func) {
		Handler kernel_handler(shared_from_this());
		auto kernel_future = std::async(std::launch::async, std::forward<TaskPred>(func), kernel_handler);
		auto shared_future = kernel_future.share();   // Get copyable future
		running_kernels_.emplace_back(shared_future); // Construct Event in running_kernels_
		return running_kernels_.back();               // Return the newly created Event
	}

	/** Return the device the queue runs on
	 */
	const Context& get_context() const noexcept {
		return execution_context_;
	}

	/** Wait for Queue to complete all tasks
	 */
	void wait() {
		for(auto kernel : running_kernels_){
			kernel.wait();
		}
		running_kernels_.clear();
	}

private:
	Context          execution_context_;
	std::list<Event> running_kernels_;
};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_ */
