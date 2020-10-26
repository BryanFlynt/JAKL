/*
 * host_event.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_EVENT_HOST_EVENT_HPP_
#define INCLUDE_JAKL_DETAIL_EVENT_HOST_EVENT_HPP_


#include "jakl/detail/event/event.hpp"

#include <future>

namespace jakl {
namespace detail {

class host_event : public event  {

public:
	host_event()                                   = delete;
	host_event(const host_event& other)            = default;
	host_event(host_event&& other)                 = default;
	host_event& operator=(const host_event& other) = default;
	host_event& operator=(host_event&& other)      = default;
	~host_event()                                  = default;

	/** Forward future into class
	 */
	host_event(std::shared_future<void> const& f) : future_result_(f) {
	}

	/** Wait till task is complete
	 */
	void wait() const {
		future_result_.wait();
	}

private:
	std::shared_future<void> future_result_;
};


} /* namespace detail */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_EVENT_HOST_EVENT_HPP_ */
