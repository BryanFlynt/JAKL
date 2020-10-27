/*
 * queue.hpp
 *
 *  Created on: Apr 1, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_HPP_

#include "jakl/core/device.hpp"
#include "jakl/core/event.hpp"
#include "jakl/core/handler.hpp"


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

	queue(const queue& other)            = default;
	queue(queue&& other)                 = default;
	queue& operator=(const queue& other) = default;
	queue& operator=(queue&& other)      = default;
	~queue()                             = default;

	/** Create Queue using default Device
	 */
	queue() : execution_device_(Device()){
	}

	/** Create Queue using provided Device
	 */
	queue(const Device& dev) : execution_device_(dev) {
	}

	/** Submit task to be run
	 *
	 * The TaskPred can either move or copy the Handler into it.
	 * It CANNOT use a reference to a Handler since anything
	 * created here will be destroyed possibly before the
	 * task executes.
	 */
	template<typename TaskPred>
	Event submit(TaskPred&& func) {
		running_kernels_.emplace_back(std::async(std::launch::async, std::forward<TaskPred>(func), Handler(shared_from_this()) ));
		return running_kernels_.back();
	}

	/** Return the device the queue runs on
	 */
	const Device& get_device() const {
		return execution_device_;
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
	Device           execution_device_;
	std::list<Event> running_kernels_;
};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_QUEUE_HPP_ */
