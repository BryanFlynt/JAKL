/*
 * gpu_event.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_EVENT_GPU_EVENT_HPP_
#define INCLUDE_JAKL_DETAIL_EVENT_GPU_EVENT_HPP_

#include "jakl/config.hpp"
#include "jakl/detail/event/event.hpp"

namespace jakl {
namespace detail {

class gpu_event : public event {

public:
	gpu_event()                                  = default;
	gpu_event(const gpu_event& other)            = default;
	gpu_event(gpu_event&& other)                 = default;
	gpu_event& operator=(const gpu_event& other) = default;
	gpu_event& operator=(gpu_event&& other)      = default;
	~gpu_event()                                 = default;

	/** Wait till task is complete
	 */
	void wait() const {
		JAKL_ASSERT(false);
	}


};

} /* namespace detail */
} /* namespace jakl */



#endif /* INCLUDE_JAKL_DETAIL_EVENT_GPU_EVENT_HPP_ */
