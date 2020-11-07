/*
 * shared_ptr_impl.hpp
 *
 *  Created on: Oct 18, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SHARED_PTR_IMPL_HPP_
#define INCLUDE_JAKL_DETAIL_SHARED_PTR_IMPL_HPP_


#include <memory>  // std::shared_ptr


namespace jakl {
namespace detail {

/// Pointer to Implementation
/**
 * Provides the framework for the "Pointer to Implementation"
 * design pattern where the derived type (Interface) holds a
 * pointer to the base class (Implementation).
 *
 * Advantages:
 *   - Provides a compilation fire wall by breaking the dependency
 *     between the implementation and the users of the interface.
 *   - Hides pointer polymorphism behind the implementation, making
 *     it look like a non-pointer type.
 *
 * Disadvantages:
 *   - Access overhead is increased as each call to the derived type
 *     requires at least one pointer dereference and possibly a virtual
 *     function call.
 *   - Adds one pointer to the public component and possibly another if
 *     a private member needs access to a public member.
 *
 * Example:
 * \code{.cpp}
 * class Device
 *   : public detail::shared_ptr_impl<Device,detail::device> {
 * public:
 *
 *   // Function to do something
 *   void doit() {
 *   	this->impl->doit();
 *   }
 *
 * private:
 *   // Provide shortcut for base type name
 *	 using base_type = typename Device::shared_ptr_impl;
 *
 *   // Make the base_ptr directly accessible in this class
 *	 using base_type::impl_ptr;
 *
 *	 // Allow base to access for comparison operators
 *	 friend base_type;
 * }
 * \endcode
 *
 * \tparam Interface Derived interface who holds the pointer to base
 * \tparam Implementation Implementation of class
 */
template<typename Interface, typename Implementation>
struct shared_ptr_impl {

	//-------------------------------------------------------------------------
	// Types & Constants
	//-------------------------------------------------------------------------
	using raw_ptr_to_impl    = Implementation*;
	using shared_ptr_to_impl = std::shared_ptr<Implementation>;

	//-------------------------------------------------------------------------
	// Construction & Destruction
	//-------------------------------------------------------------------------

	shared_ptr_impl()                                        = default;
	shared_ptr_impl(shared_ptr_impl const& other)            = default;
	shared_ptr_impl(shared_ptr_impl&& other)                 = default;
	~shared_ptr_impl()                                       = default;
	shared_ptr_impl& operator=(shared_ptr_impl const& other) = default;
	shared_ptr_impl& operator=(shared_ptr_impl&& other)      = default;

	/** Construct from shared_ptr to the Implementation
	 */
	shared_ptr_impl(shared_ptr_to_impl const& other_ptr) : impl_ptr(other_ptr) {
	}

	/** Take ownership from a raw pointer to the Implementation
	 */
	shared_ptr_impl(raw_ptr_to_impl const& ptr) : impl_ptr(ptr) {
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------

	/** Less Than Operator
	 *
	 * Uses the std::shared_ptr less than operator
	 * which only compares the pointer address not the value
	 * contained within it.
	 */
	bool operator<(Interface const& other) const {
		return (this->impl_ptr < other.impl_ptr);
	}

	/** Equal To Operator
	 *
	 * Uses the std::shared_ptr equal to operator
	 * which only compares the pointer address not the value
	 * contained within it.
	 */
	bool operator ==(Interface const& other) const {
		return (this->impl_ptr == other.impl_ptr);
	}

	/// The Interface forwards all calls to this base shared_ptr
	shared_ptr_to_impl impl_ptr;
};


} /* namespace detail */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_SHARED_PTR_IMPL_HPP_ */
