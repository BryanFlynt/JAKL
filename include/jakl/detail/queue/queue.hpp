/*
 * queue.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_


#include "jakl/context.hpp"
#include "jakl/event.hpp"
#include "jakl/handler.hpp"

#include <functional>
#include <list>

namespace jakl {
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
	virtual ~queue()                     = default;

	/** Create Queue using provided Context
	 */
	queue(const Context& context) : execution_context_(context){
	}


	virtual Event submit(std::function<void(Handler&&)>&& func) = 0;

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

protected:
	Context          execution_context_;
	std::list<Event> running_kernels_;
};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_QUEUE_QUEUE_HPP_ */
