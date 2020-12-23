/**
 * \file       handler.hpp
 * \author     Bryan Flynt
 * \date       Dec 21, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_HANDLER_HANDLER_HPP_
#define INCLUDE_JAKL_DETAIL_HANDLER_HANDLER_HPP_

#include "jakl/context.hpp"
#include "jakl/event.hpp"

namespace jakl {
namespace detail {

/** Queue Implementation
 *
 * The actual implementation of the Queue class.
 */
class handler {

public:
	handler()                                = delete;
	handler(const handler& other)            = default;
	handler(handler&& other)                 = default;
	handler& operator=(const handler& other) = default;
	handler& operator=(handler&& other)      = default;
	virtual ~handler()                       = default;

	/** Create Queue using provided Context
	 */
	handler(const Context& context) : context_(context){
	}



private:
	Context context_;
};

} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_HANDLER_HANDLER_HPP_ */
