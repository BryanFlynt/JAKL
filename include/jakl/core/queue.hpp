/*
 * queue.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_QUEUE_HPP_
#define INCLUDE_JAKL_CORE_QUEUE_HPP_

#include "jakl/core/device.hpp"
#include "jakl/core/event.hpp"

#include "jakl/detail/queue.hpp"
#include "jakl/detail/shared_ptr_base.hpp"

#include <memory>


namespace jakl {


class Queue : public detail::shared_ptr_base<Queue,detail::queue> {

public:

	Queue(const Queue& other)            = default;
	Queue(Queue&& other)                 = default;
	Queue& operator=(const Queue& other) = default;
	Queue& operator=(Queue&& other)      = default;
	~Queue()                             = default;

	/** Create Queue using default Device
	 */
	Queue() : base_type(std::make_shared<detail::queue>()) {
	}

	/** Create Queue using provided Device
	 */
	Queue(const Device& device) : base_type(std::make_shared<detail::queue>(device)) {
	}

	/** Submit function to be run
	 */
	template<typename TaskPred>
	Event submit(TaskPred&& func) {
		return base_ptr_->submit(func);
	}

	/** Return the device the Queue runs on
	 */
	const Device& get_device() const {
		return base_ptr_->get_device();
	}

	/** Wait for Queue to complete all tasks
	 */
	void wait() {
		base_ptr_->wait();
	}

private:
	// Provide shortcut for base type name
	using base_type = typename Queue::shared_ptr_base;

	// Make the base_ptr directly accessible in this class
	using base_type::base_ptr_;

	// Allow base to access for comparison operators
	friend base_type;
};

} // namespace jakl


#endif /* INCLUDE_JAKL_CORE_QUEUE_HPP_ */
