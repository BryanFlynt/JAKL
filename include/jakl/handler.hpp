/*
 * handler.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_HANDLER_HPP_
#define INCLUDE_JAKL_HANDLER_HPP_


#include "jakl/context.hpp"
#include "jakl/event.hpp"
#include "jakl/index.hpp"
#include "jakl/queue.hpp"
#include "jakl/range.hpp"


namespace jakl {


class Handler final {

public:
	Handler()                                = delete;
	Handler(const Handler& other)            = default;
	Handler(Handler&& other)                 = default;
	Handler& operator=(const Handler& other) = default;
	Handler& operator=(Handler&& other)      = default;
	~Handler()                               = default;

	/** Construct from shared_ptr to Implementation
	 */
	Handler(std::shared_ptr<detail::queue> const& qptr) : queue_ptr_(qptr){
	}

	template<typename Name = std::nullptr_t, std::size_t N, typename Functor>
	void parallel_for(Range<N> r, Functor f) {

/**
		// Get pointer to range data
		// - We can't pass a Range<N> into Index<N> on device
		const auto range_ptr = r.data();

		if( get_context().get_device().is_host() ){
#pragma omp parallel for
			for(std::size_t i = 0; i < r.size(); ++i){
				f( Index<N>(i, range_ptr) );
			}
		}
		else {
			JAKL_ASSERT(false);
		}
**/
	}

	void depends_on(const Event& event) const {
		event.wait();
	}

	const Context& get_context() const {
		return queue_ptr_->get_context();
	}


	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------

	std::shared_ptr<detail::queue> queue_ptr_;
};

} /* namespace jakl */


#endif /* INCLUDE_JAKL_HANDLER_HPP_ */
