/*
 * event.hpp
 *
 *  Created on: Apr 1, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_EVENT_HPP_
#define INCLUDE_JAKL_DETAIL_EVENT_HPP_


#include <future>


namespace jakl {
namespace detail {

class event {

public:
	event()                              = delete;
	event(const event& other)            = default;
	event(event&& other)                 = default;
	event& operator=(const event& other) = default;
	event& operator=(event&& other)      = default;
	~event()                             = default;

	/** Create event taking an std::future
	 */
	event(std::future<void>&& f) : future_result_(std::forward<std::future<void>>(f)) {
	}

	/** Wait till task is complete
	 */
	void wait() const {
		future_result_.wait();
	}

private:
	std::future<void> future_result_;
};

} // namespace detail
} // namespace jakl




#endif /* INCLUDE_JAKL_DETAIL_EVENT_HPP_ */
