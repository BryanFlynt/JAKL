/*
 * id.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_ID_HPP_
#define INCLUDE_JAKL_ID_HPP_

#include <cstdint>

namespace jakl {

/// ID Class
/**
 * Simple ID to identify the Device ID.  This could be a simple Integer but
 * each device library requires a different integer representation so
 * it was decided to place into a class for now.
 */
class ID final {

	//-------------------------------------------------------------------------
	// Types & Constants
	//-------------------------------------------------------------------------
public:
	using value_type = std::int32_t;

	//-------------------------------------------------------------------------
	// Construction & Destruction
	//-------------------------------------------------------------------------

	ID(ID const& other)            = default;
	ID(ID&& other)                 = default;
	~ID()                          = default;
	ID& operator=(ID const& other) = default;
	ID& operator=(ID&& other)      = default;

	/// Construct with default bogus value
	ID(value_type const& value = -9999) : id_(value) {
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------

	/// Assign from a value_type
	ID& operator=(value_type const& value) noexcept {
		id_ = value;
		return *this;
	}

	//-------------------------------------------------------------------------
	// Access
	//-------------------------------------------------------------------------

	/// Implicit conversion to value_type
	operator value_type const&() const noexcept {
		return id_;
	}

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------
private:
	value_type id_;
};


} // namespace jakl


#endif /* INCLUDE_JAKL_ID_HPP_ */
