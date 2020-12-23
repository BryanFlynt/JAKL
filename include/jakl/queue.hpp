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
#include "jakl/detail/queue/queue.hpp"
#include "jakl/detail/queue/cpu_queue.hpp"
#include "jakl/detail/queue/host_queue.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"

#include <functional>
#include <memory>
#include <utility>

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
			impl = std::make_shared<detail::host_queue>(context);
		}
		else if( context.device().is_cpu() ) {
			impl = std::make_shared<detail::cpu_queue>(context);
		}
//		else if( context.device().is_gpu() ) {
//			impl.reset(std::make_shared<detail::gpu_queue>(context));
//		}
		else {
			JAKL_ASSERT("Not Implemented");
		}
	}

	/** Submit function to be run
	 */
	Event submit(std::function<void(Handler&&)>&& func) {
		return impl->submit(std::move(func));
	}

	/** Get Context of Queue
	 */
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
