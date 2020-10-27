/*
 * event.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_EVENT_HPP_
#define INCLUDE_JAKL_CORE_EVENT_HPP_


#include "jakl/detail/event.hpp"
#include "jakl/detail/shared_ptr_base.hpp"


#include <future>

namespace jakl {

class Event : public detail::shared_ptr_base<Event,detail::event> {

public:

	Event()                              = delete;
	Event(const Event& other)            = default;
	Event(Event&& other)                 = default;
	Event& operator=(const Event& other) = default;
	Event& operator=(Event&& other)      = default;
	~Event()                             = default;

	/** Create Event taking a std::future
	 */
	Event(std::future<void>&& f) : base_type(std::make_shared<detail::event>(std::forward<std::future<void>>(f))){
	}

	/** Wait till task is complete
	 */
	void wait() const {
		base_ptr_->wait();
	}


private:
	// Provide shortcut for base type name
	using base_type = typename Event::shared_ptr_base;

	// Allow base to access for comparison operators
	friend base_type;

	// Make the base_ptr directly accessible in this class
	using base_type::base_ptr_;

};

} // namespace jakl




#endif /* INCLUDE_JAKL_CORE_EVENT_HPP_ */
