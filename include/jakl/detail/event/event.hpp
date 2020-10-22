/*
 * event.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_EVENT_EVENT_HPP_
#define INCLUDE_JAKL_DETAIL_EVENT_EVENT_HPP_


namespace jakl {
namespace detail {

class event {

public:
	event()                              = default;
	event(const event& other)            = default;
	event(event&& other)                 = default;
	event& operator=(const event& other) = default;
	event& operator=(event&& other)      = default;
	virtual ~event(){}

	/** Wait till task is complete
	 */
	virtual void wait() const = 0;

private:

};

} /* namespace detail */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_EVENT_EVENT_HPP_ */
