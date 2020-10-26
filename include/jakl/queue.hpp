/*
 * queue.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_QUEUE_HPP_
#define INCLUDE_JAKL_QUEUE_HPP_

#include "jakl/config.hpp"
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


/**
 *
 */
class Queue final : public std::enable_shared_from_this<Queue> {

public:
	Queue()                              = default;
	Queue(const Queue& other)            = default;
	Queue(Queue&& other)                 = default;
	Queue& operator=(const Queue& other) = default;
	Queue& operator=(Queue&& other)      = default;
	~Queue()                             = default;

	/** Create Queue using provided Context
	 */
	Queue(const Context& context) : execution_context_(context){
	}

	/** Submit function to be run
	 */
	template<typename TaskPred>
	Event submit(TaskPred&& func) {
		Handler kernel_handler(shared_from_this());
		auto kernel_future = std::async(std::launch::async, std::forward<TaskPred>(func), kernel_handler);
		auto shared_future = kernel_future.share();         // Get copyable future
		this->running_kernels_.emplace_back(shared_future); // Calls Event Constructor
		return this->running_kernels_.back();               // Return Event with copyable future
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

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------

	Context          execution_context_;
	std::list<Event> running_kernels_;
};

} // namespace jakl


#endif /* INCLUDE_JAKL_QUEUE_HPP_ */
