/*
 * handler.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_HANDLER_HPP_
#define INCLUDE_JAKL_HANDLER_HPP_

#include <memory>

#include "jakl/detail/handler/handler.hpp"


namespace jakl {


class Handler : public detail::shared_ptr_impl<Handler,detail::handler> {

public:
	Handler()                                = delete;
	Handler(const Handler& other)            = default;
	Handler(Handler&& other)                 = default;
	Handler& operator=(const Handler& other) = default;
	Handler& operator=(Handler&& other)      = default;
	~Handler()                               = default;

	Handler(const std::shared_ptr<detail::handler>& handle) : base_type{handle} {
	}

//	void depends_on(const Event& event) const {
//		event.wait();
//	}

private:
	// Provide shortcut for base type name
	using base_type = typename Handler::shared_ptr_impl;

	// Make the base_ptr directly accessible in this class
	using base_type::impl;

	// Allow base to access for comparison operators
	friend base_type;
};


//template<typename Name, std::size_t N, typename Functor>
//void
//Handler::parallel_for(Range<N> r, Functor f) {
//
//	// Get pointer to range data
//	// - We can't pass a Range<N> into Index<N> on device
//	const auto range_ptr = r.data();
//
//	// HOST execution model
//	if( queue_->get_device().is_host() ){
//		//std::cout << "Running on HOST" << std::endl;
//
//		#pragma omp parallel for
//		for(std::size_t i = 0; i < r.size(); ++i){
//			f( Index<N>(i, range_ptr) );
//		}
//	}
//
//	// DEVICE execution model
//	else {
//		//std::cout << "Running on DEVICE" << std::endl;
//
//		const std::size_t S = r.size();
//		const auto dev_id = queue_->get_device().id();
//
//		#pragma omp target data map(to: range_ptr[:N], f) device(dev_id)
//		{
//			#pragma omp target teams num_teams((S-1)/128+1) thread_limit(128)
//			#pragma omp distribute parallel for
//			for(std::size_t i = 0; i < S; ++i){
//				f( kernel::make_index<N>(i, range_ptr) );
//			}
//		}
//	}
//}

} // namespace jakl



#endif /* INCLUDE_JAKL_HANDLER_HPP_ */
