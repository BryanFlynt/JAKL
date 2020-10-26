/*
 * handler.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_HANDLER_HPP_
#define INCLUDE_JAKL_HANDLER_HPP_



#include "jakl/event.hpp"
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
	Handler(std::shared_ptr<Queue> const& qptr) : queue_ptr_(qptr){
	}

	template<typename Name = std::nullptr_t, std::size_t N, typename Functor>
	void parallel_for(Range<N> r, Functor f) {

	}

	void depends_on(const Event& event) const {
		event.wait();
	}

//	const Device& get_device() const {
//		return queue_ptr_->get_device();
//	}


	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------

	std::shared_ptr<Queue> queue_ptr_;
};

} /* namespace jakl */


#endif /* INCLUDE_JAKL_HANDLER_HPP_ */
