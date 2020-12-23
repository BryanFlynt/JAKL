/**
 * \file       cpu_queue.hpp
 * \author     Bryan Flynt
 * \date       Dec 21, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_CPU_QUEUE_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_CPU_QUEUE_HPP_

#include "jakl/context.hpp"
#include "jakl/device.hpp"
#include "jakl/event.hpp"
#include "jakl/detail/handler/cpu_handler.hpp"
#include "jakl/detail/queue/queue.hpp"


namespace jakl {
namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class cpu_queue : public queue {

public:
	cpu_queue()                                  = delete;
	cpu_queue(const cpu_queue& other)            = default;
	cpu_queue(cpu_queue&& other)                 = default;
	cpu_queue& operator=(const cpu_queue& other) = default;
	cpu_queue& operator=(cpu_queue&& other)      = default;
	virtual ~cpu_queue()                         = default;

	/** Create Queue using provided Context
	 */
	cpu_queue(const Context& context) : queue(context){
	}

	/** Launch Task to run on GPU
	 */
	Event submit(std::function<void(Handler&&)>&& func) {
		auto kernel_handler_ptr = std::make_shared<cpu_handler>(get_context());
		auto kernel_handler     = Handler(kernel_handler_ptr);
		auto kernel_future = std::async(std::launch::async, std::move(func), kernel_handler);
		auto shared_future = kernel_future.share();         // Get copy-able future
		this->running_kernels_.emplace_back(shared_future); // Calls Event Constructor
		return this->running_kernels_.back();
	}

private:

};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_QUEUE_CPU_QUEUE_HPP_ */
