/*
 * event.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_EVENT_HPP_
#define INCLUDE_JAKL_EVENT_HPP_



#include "jakl/detail/event/event.hpp"
#include "jakl/detail/event/gpu_event.hpp"
#include "jakl/detail/event/host_event.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"


#include <future>

namespace jakl {


class Event : public detail::shared_ptr_impl<Event,detail::event> {

public:

	Event()                              = default;
	Event(const Event& other)            = default;
	Event(Event&& other)                 = default;
	Event& operator=(const Event& other) = default;
	Event& operator=(Event&& other)      = default;
	~Event()                             = default;

	Event(std::shared_future<void> const& f) : base_type( std::make_shared<detail::host_event>(f) ){
	}

	/** Wait till task is complete
	 */
	void wait() const {
		impl_ptr->wait();
	}


private:
	// Provide shortcut for base type name
	using base_type = typename Event::shared_ptr_impl;

	// Allow base to access for comparison operators
	friend base_type;

	// Make the base_ptr directly accessible in this class
	using base_type::impl_ptr;

};

} // namespace jakl


#endif /* INCLUDE_JAKL_EVENT_HPP_ */
