/*
 * event.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_EVENT_HPP_
#define INCLUDE_JAKL_EVENT_HPP_

#include <future>

#include "jakl/config.hpp"


namespace jakl {


class Event {

public:

	Event()                              = delete;
	Event(const Event& other)            = default;
	Event(Event&& other)                 = default;
	Event& operator=(const Event& other) = default;
	Event& operator=(Event&& other)      = default;
	~Event()                             = default;

	Event(const std::shared_future<void>& f) : future_(f) {
	}

	/** Wait till task is complete
	 */
	void wait() const {
		future_.wait();
	}

private:
	std::shared_future<void> future_;
};

} // namespace jakl


#endif /* INCLUDE_JAKL_EVENT_HPP_ */
