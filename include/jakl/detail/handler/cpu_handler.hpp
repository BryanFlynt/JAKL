/**
 * \file       cpu_handler.hpp
 * \author     Bryan Flynt
 * \date       Dec 21, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_HANDLER_CPU_HANDLER_HPP_
#define INCLUDE_JAKL_DETAIL_HANDLER_CPU_HANDLER_HPP_

#include "jakl/context.hpp"
#include "jakl/event.hpp"
#include "jakl/detail/handler/handler.hpp"

namespace jakl {
namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class cpu_handler : public handler {

public:
	cpu_handler()                                    = delete;
	cpu_handler(const cpu_handler& other)            = default;
	cpu_handler(cpu_handler&& other)                 = default;
	cpu_handler& operator=(const cpu_handler& other) = default;
	cpu_handler& operator=(cpu_handler&& other)      = default;
	~cpu_handler()                                   = default;

	/** Create CPU Handler using provided Context
	 */
	cpu_handler(const Context& c) : handler(c){
		JAKL_ASSERT(c.device().is_cpu());
	}


private:

};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_HANDLER_CPU_HANDLER_HPP_ */
