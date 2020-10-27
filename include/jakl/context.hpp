/*
 * context.hpp
 *
 *  Created on: Oct 14, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_CONTEXT_HPP_
#define INCLUDE_JAKL_CORE_CONTEXT_HPP_


#include "jakl/device.hpp"


namespace jakl {


class Context final {

	//-------------------------------------------------------------------------
	// Types & Constants
	//-------------------------------------------------------------------------
public:

	//-------------------------------------------------------------------------
	// Construction & Destruction
	//-------------------------------------------------------------------------
public:
	Context()                                = default;
	Context(Context const& other)            = default;
	Context(Context&& other)                 = default;
	~Context()                               = default;
	Context& operator=(Context const& other) = default;
	Context& operator=(Context&& other)      = default;

	/** Create Context with Device
	 */
	Context(Device const& device) : device_(device){
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------

	/** Check if Context are the same
	 */
	bool operator==(Context const& other) const noexcept {
		return device_ == other.device_;
	}

	//-------------------------------------------------------------------------
	// Access
	//-------------------------------------------------------------------------

	/** Get Contexts device
	 */
	Device const& device() const noexcept {
		return device_;
	}

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------
private:
	Device device_;
};


} // namespace jakl




#endif /* INCLUDE_JAKL_CORE_CONTEXT_HPP_ */
