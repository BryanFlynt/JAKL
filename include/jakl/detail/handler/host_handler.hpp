/**
 * \file       host_handler.hpp
 * \author     Bryan Flynt
 * \date       Dec 21, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_HANDLER_HOST_HANDLER_HPP_
#define INCLUDE_JAKL_DETAIL_HANDLER_HOST_HANDLER_HPP_

#include "jakl/context.hpp"
#include "jakl/event.hpp"
#include "jakl/detail/handler/handler.hpp"

namespace jakl {
namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class host_handler : public handler {

public:
	host_handler()                                     = delete;
	host_handler(const host_handler& other)            = default;
	host_handler(host_handler&& other)                 = default;
	host_handler& operator=(const host_handler& other) = default;
	host_handler& operator=(host_handler&& other)      = default;
	~host_handler()                                    = default;

	/** Create Host Handler using provided Context
	 */
	host_handler(const Context& c) : handler(c){
		JAKL_ASSERT(c.device().is_host());
	}


private:

};

} // namespace detail
} // namespace jakl

#endif /* INCLUDE_JAKL_DETAIL_HANDLER_HOST_HANDLER_HPP_ */
