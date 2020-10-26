/*
 * buffer.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_BUFFER_HPP_
#define INCLUDE_JAKL_BUFFER_HPP_


#include "jakl/access.hpp"
#include "jakl/handler.hpp"
#include "jakl/id.hpp"
#include "jakl/range.hpp"

#include "jakl/detail/buffer/buffer.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"


namespace jakl {

/** Memory Buffer
 *
 */
template<typename T, std::size_t N>
class Buffer : public detail::shared_ptr_impl<Buffer<T,N>,detail::buffer<T,N>> {

public:
	using size_type     = std::size_t;
	using value_type    = T;
	using range_type    = Range<N>;
	using pointer       = value_type*;
	using const_pointer = value_type const*;

public:
	Buffer()                               = delete;
	Buffer(const Buffer& other)            = default;
	Buffer(Buffer&& other)                 = default;
	Buffer& operator=(const Buffer& other) = default;
	Buffer& operator=(Buffer&& other)      = default;
	~Buffer()                              = default;

	Buffer(pointer host_ptr, const range_type& range) : base_type(std::make_shared<detail::buffer<T,N>>(host_ptr,range)) {
	}

	template<access::mode Mode>
	pointer get_access(const ID id = system::host_device()){
		return impl_ptr_->template get_access<Mode>(id);
	}

	template<access::mode Mode>
	pointer get_access(const Handler& handle){
		return impl_ptr_->template get_access<Mode>(handle);
	}

	/** Flush data back to host pointer
	 *
	 * Copies data back to host_ptr but does not
	 * reset the buffers record of who wrote last
	 */
	void flush() const {
		impl_ptr_->flush();
	}

	/** Update buffer with new data from the host pointer
	 *
	 * Update the internal copy of the host data from the
	 * originally provided host location.  This will reset
	 * the record of last written data to the host copy.
	 * i.e. You will lose the record of the last written data.
	 */
	void update() {
		impl_ptr_->update();
	}

	/** Return number of elements within the Buffer
	 */
	size_type size() const {
		return impl_ptr_->size();
	}

	/** Return number of bytes within the Buffer array
	 */
	size_type bytes() const {
		return impl_ptr_->bytes();
	}

	/** Get Range associated with Buffer
	 */
	const range_type& range() const {
		return impl_ptr_->range();
	}

private:
	// Provide shortcut for base type name
	using base_type = typename Buffer::shared_ptr_impl;

	// Make the base_ptr directly accessible in this class
	using base_type::impl_ptr_;

	// Allow base to access for comparison operators
	friend base_type;
};

} // namespace jakl



#endif /* INCLUDE_JAKL_BUFFER_HPP_ */
