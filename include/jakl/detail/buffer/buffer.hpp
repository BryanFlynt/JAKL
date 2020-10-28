/*
 * buffer.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
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

public:
	buffer()                               = delete;
	buffer(const buffer& other)            = default;
	buffer(buffer&& other)                 = default;
	~buffer();
	buffer& operator=(const buffer& other) = default;
	buffer& operator=(buffer&& other)      = default;

	buffer(pointer host_ptr, const range_type& range);

	template<access::mode Mode>
	pointer get_access(Context const& context);

	template<access::mode Mode>
	pointer get_access(const Handler& handle);

	/** Flush data back to host pointer
	 *
	 * Copies data back to host_ptr but does not
	 * reset the buffers record of who wrote last
	 */
	void flush() const;

	/** Update buffer with new data from the host pointer
	 *
	 * Update the internal copy of the host data from the
	 * originally provided host location.  This will reset
	 * the record of last written data to the host copy.
	 * i.e. You will lose the record of the last written data.
	 */
	void update();

	/** Return number of elements within the buffer
	 */
	size_type size() const;

	/** Return number of bytes within the buffer array
	 */
	size_type bytes() const;

	/** Get Range associated with buffer
	 */
	const range_type& range() const;


private:
	range_type                 range_;
	Context                    source_context_;
	pointer                    source_ptr_;

	std::map<Context,pointer>  context_data_ptrs_;
	Context                    context_of_last_write_;
};

} // namespace detail
} // namespace jakl



namespace jakl {
namespace detail {

template<typename T, std::size_t N>
buffer<T,N>::buffer(pointer host_ptr, const range_type& range)
: source_ptr_(host_ptr),
  range_(range) {

	// Assumes Default Host Context
	source_context_ = Context(system::host_device());
	context_of_last_write_ = source_context_;

	// Allocate buffer memory on host
	auto dev_ptr = system::allocate_memory(source_context_, bytes());
	context_data_ptrs_[context_of_last_write_] = reinterpret_cast<pointer>(dev_ptr);

	// Copy host data into buffer memory on host
	this->update();
}


template<typename T, std::size_t N>
buffer<T,N>::~buffer() {

	// Copy last written data back to host data
	this->flush();

	// DeAllocate all device pointer memory
	for(auto& [context, ptr] : context_data_ptrs_) {
		system::free_memory(context, ptr, bytes());
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
			auto ptr = system::allocate_memory(context, bytes());
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
					context_data_ptrs_[context],                // Destination pointer
					context_data_ptrs_[context_of_last_write_], // Source pointer
					this->bytes(),                              // Size in Bytes
					context,                                    // Destination Context
					context_of_last_write_                      // Source Context
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
void
buffer<T,N>::flush() const {
	system::copy_memory(
			source_ptr_,                                // Destination pointer
			context_data_ptrs_[context_of_last_write_], // Source pointer
			this->bytes(),                              // Size in Bytes
			source_context_,                            // Destination Context
			context_of_last_write_                      // Source Context
			);

}

template<typename T, std::size_t N>
void
buffer<T,N>::update() {
	system::copy_memory(
			context_data_ptrs_[source_context_], // Destination pointer
			source_ptr_,                         // Source pointer
			this->bytes(),                       // Size in Bytes
			source_context_,                     // Destination Context
			source_context_                      // Source Context
			);
	context_of_last_write_ = source_context_;
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
