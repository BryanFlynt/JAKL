/*
 * singleton.hpp
 *
 *  Created on: Oct 18, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SINGLETON_HPP_
#define INCLUDE_JAKL_DETAIL_SINGLETON_HPP_


#include <memory>  // std::shared_ptr


namespace jakl {
namespace detail {

/// Smart Pointer Singleton
/**
 * Provides the framework for the "Singleton" design pattern
 * but uses a smart pointer instead of a raw pointer. The static
 * construction is guaranteed to be thread safe by C++11 standard.
 */
template<typename T>
struct singleton {

	/** Return the pointer to the single instance of the host
	 *
	 * Returns a std::shared_ptr to the single host instance. By using
	 * a static construction the C++11 standard guarantees thread safety.
	 * The std::shared_ptr must not delete the instance since it was
	 * constructed in the static area so a no-operation deleter was
	 * passed as a lambda function.
	 */
	static std::shared_ptr<T> instance() {
		static T single_instance_;
		static std::shared_ptr<T> single_ptr_{&single_instance_, [](T*){}};
		return single_ptr_;
	}

};


} /* namespace detail */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_SINGLETON_HPP_ */
