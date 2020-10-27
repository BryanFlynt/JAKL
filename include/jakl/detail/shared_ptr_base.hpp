/*
 * shared_ptr_base.hpp
 *
 *  Created on: Apr 1, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SHARED_PTR_BASE_HPP_
#define INCLUDE_JAKL_DETAIL_SHARED_PTR_BASE_HPP_


#include <memory>


namespace jakl {
namespace detail {

/** Provide the Base as a std::shared_ptr<Base> within the Parent
 *
 */
template<typename Parent, typename Base>
struct shared_ptr_base {


	using base_ptr_type = std::shared_ptr<Base>;


	shared_ptr_base()                                        = default;
	shared_ptr_base(const shared_ptr_base& other)            = default;
	shared_ptr_base(shared_ptr_base&& other)                 = default;
	~shared_ptr_base()                                       = default;
	shared_ptr_base& operator=(const shared_ptr_base& other) = default;
	shared_ptr_base& operator=(shared_ptr_base&& other)      = default;

	/** Construct from shared_ptr to base
	 */
	shared_ptr_base(std::shared_ptr<Base> base_ptr) : base_ptr_(base_ptr){
	}

	/** Less Than Operator
	 *
	 * Uses the std::shared_ptr less than operator
	 * which only compares the pointer address not the value
	 * contained within it.
	 */
	bool operator<(const Parent &other) const {
		return (base_ptr_ < other.base_ptr_);
	}

	/** Equal To Operator
	 *
	 * Uses the std::shared_ptr equal to operator
	 * which only compares the pointer address not the value
	 * contained within it.
	 */
	bool operator==(const Parent &other) const {
		return (base_ptr_ == other.base_ptr_);
	}


	/// The Parent forwards all calls to this base shared_ptr
	base_ptr_type base_ptr_;
};


} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_SHARED_PTR_BASE_HPP_ */
