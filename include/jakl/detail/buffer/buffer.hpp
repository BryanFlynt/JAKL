/**
 * \file       buffer.hpp
 * \author     Bryan Flynt
 * \date       Dec 22, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_BUFFER_BUFFER_HPP_
#define INCLUDE_JAKL_DETAIL_BUFFER_BUFFER_HPP_


#include "jakl/access.hpp"
#include "jakl/config.hpp"
#include "jakl/context.hpp"
#include "jakl/handler.hpp"
#include "jakl/id.hpp"
#include "jakl/range.hpp"
#include "jakl/system.hpp"

#include <cstddef>
#include <map>


namespace jakl {
namespace detail {

/** Memory buffer
 *
 */
template<typename T, std::size_t N>
class buffer {

public:
	using size_type     = std::size_t;
	using value_type    = T;
	using range_type    = Range<N>;
	using pointer       = value_type*;
	using const_pointer = value_type const*;
	using reference       = value_type&;
	using const_reference = value_type const&;

public:
	buffer()                               = delete;
	buffer(const buffer& other)            = default;
	buffer(buffer&& other)                 = default;
	~buffer();
	buffer& operator=(const buffer& other) = default;
	buffer& operator=(buffer&& other)      = default;

	buffer(const range_type& range);

	buffer(pointer host_ptr, const range_type& range);

	template<access::mode Mode>
	pointer get_access(Context const& context);

	template<access::mode Mode>
	pointer get_access(const Handler& handle);

	/** Return number of elements within the buffer
	 */
	size_type size() const;

	/** Return number of bytes within the buffer array
	 */
	size_type bytes() const;

	/** Get Range associated with buffer
	 */
	const range_type& range() const;

	/** Set pointer where final data will be written on destruction
	 */
	template<typename Destination>
	void set_final_data(Destination final_data) {
		final_data_ = final_data;
		write_back_ = true;
	}

	/** Force or cancel writing back data on destruction
	 */
	void set_write_back(const bool flag) {
		write_back_ = flag;
	}

private:
	range_type                 range_;
	pointer                    final_data_;
	bool                       write_back_;

	std::map<Context,pointer>  context_data_ptrs_;
	Context                    context_of_last_write_;
};

} // namespace detail
} // namespace jakl



namespace jakl {
namespace detail {


template<typename T, std::size_t N>
buffer<T,N>::buffer(const range_type& range) : range_(range),
                                               final_data_(nullptr),
											   write_back_(false) {
}

template<typename T, std::size_t N>
buffer<T,N>::buffer(pointer host_ptr, const range_type& range) : range_(range),
                                                                 final_data_(host_ptr),
                                                                 write_back_(true) {
	context_data_ptrs_[Context()] = host_ptr;
}

template<typename T, std::size_t N>
buffer<T,N>::~buffer() {
	if( write_back_ && final_data_ ) {
		Context host_context;
		system::copy_memory(
			this->bytes(),                              // Size in Bytes
			context_of_last_write_,                     // Source Context
			context_data_ptrs_[context_of_last_write_], // Source pointer
			host_context,                               // Destination Context
			final_data_                                 // Destination pointer
		);
	}
}

template<typename T, std::size_t N>
template<access::mode Mode>
typename buffer<T,N>::pointer
buffer<T,N>::get_access(Context const& context){

	// If we need space then allocate it
	if constexpr(
			(Mode == access::mode::read)  or
			(Mode == access::mode::write) or
			(Mode == access::mode::read_write) ) {

		if( context_data_ptrs_.count(context) == 0 ){
			auto ptr = system::allocate_memory(context,bytes());
			context_data_ptrs_[context] = reinterpret_cast<pointer>(ptr);
		}
	}
	JAKL_ASSERT(context_data_ptrs_.count(context) == 0);
	JAKL_ASSERT(context_data_ptrs_[context]);

	// If we need to copy data then do it
	if constexpr(
			(Mode == access::mode::read)  or
			(Mode == access::mode::read_write) ) {

		if( context != context_of_last_write_ ){
			system::copy_memory(
				this->bytes(),                              // Size in Bytes
				context_of_last_write_                      // Source Context
				context_data_ptrs_[context_of_last_write_], // Source pointer
				context,                                    // Destination Context
				context_data_ptrs_[context]                 // Destination pointer
			);
		}
	}

	// If we write data then flag as most recent
	if constexpr(
			(Mode == access::mode::write)  or
			(Mode == access::mode::read_write) ) {
		context_of_last_write_ = context;
	}

	return context_data_ptrs_[context];
}


template<typename T, std::size_t N>
template<access::mode Mode>
typename buffer<T,N>::pointer
buffer<T,N>::get_access(const Handler& handle){
	return this->get_access<Mode>(handle.get_context());
}

template<typename T, std::size_t N>
typename buffer<T,N>::size_type
buffer<T,N>::size() const {
	return this->range_.size();
}

template<typename T, std::size_t N>
typename buffer<T,N>::size_type
buffer<T,N>::bytes() const {
	return (this->size() * sizeof(value_type));
}

template<typename T, std::size_t N>
const typename buffer<T,N>::range_type&
buffer<T,N>::range() const{
	return range_;
}


} // namespace detail
} // namespace jakl


#endif /* INCLUDE_JAKL_DETAIL_BUFFER_BUFFER_HPP_ */
