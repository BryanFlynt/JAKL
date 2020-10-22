/*
 * host_queue.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_HOST_QUEUE_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_HOST_QUEUE_HPP_


#include "jakl/context.hpp"
#include "jakl/device.hpp"
#include "jakl/event.hpp"
#include "jakl/detail/queue/queue.hpp"
//#include "jakl/handler.hpp"

#include <list>


namespace jakl {
namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class host_queue : public queue {

public:
	host_queue()                                   = delete;
	host_queue(const host_queue& other)            = default;
	host_queue(host_queue&& other)                 = default;
	host_queue& operator=(const host_queue& other) = default;
	host_queue& operator=(host_queue&& other)      = default;
	~host_queue()                                  = default;

	/** Create Queue using provided Context
	 */
	host_queue(const Context& context) : queue(context){
	}


private:

};

} // namespace detail
} // namespace jakl




#endif /* INCLUDE_JAKL_DETAIL_QUEUE_HOST_QUEUE_HPP_ */
