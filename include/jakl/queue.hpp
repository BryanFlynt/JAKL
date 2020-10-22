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
#include "jakl/detail/queue/queue.hpp"
#include "jakl/detail/queue/gpu_queue.hpp"
#include "jakl/detail/queue/host_queue.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"


#include <memory>


namespace jakl {


class Queue : public detail::shared_ptr_impl<Queue,detail::queue> {

public:
	Queue()                              = delete;
	Queue(const Queue& other)            = default;
	Queue(Queue&& other)                 = default;
	Queue& operator=(const Queue& other) = default;
	Queue& operator=(Queue&& other)      = default;
	~Queue()                             = default;

	/** Create Queue using provided Context
	 */
	Queue(const Context& context) {
		if( context.device().is_host() ) {
			impl.reset(new detail::host_queue(context));
		}
		else if( context.device().is_gpu() ) {
			impl.reset(new detail::gpu_queue(context));
		}
	}

	/** Submit function to be run
	 */
//	template<typename TaskPred>
//	Event submit(TaskPred&& func) {
//		return impl->submit(func);
//	}

	const Context& get_context() const noexcept {
		return impl->get_context();
	}

	/** Wait for Queue to complete all tasks
	 */
	void wait() {
		impl->wait();
	}

private:
	// Provide shortcut for base type name
	using base_type = typename Queue::shared_ptr_impl;

	// Make the base_ptr directly accessible in this class
	using base_type::impl;

	// Allow base to access for comparison operators
	friend base_type;
};

} // namespace jakl


#endif /* INCLUDE_JAKL_QUEUE_HPP_ */
