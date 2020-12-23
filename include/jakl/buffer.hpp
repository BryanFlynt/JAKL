/**
 * \file       buffer.hpp
 * \author     Bryan Flynt
 * \date       Dec 22, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_BUFFER_HPP_
#define INCLUDE_JAKL_BUFFER_HPP_

#include <cstddef>  // std::size_t

#include "jakl/config.hpp"
#include "jakl/access.hpp"
#include "jakl/context.hpp"
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
	using size_type       = std::size_t;
	using value_type      = T;
	using range_type      = Range<N>;
	using pointer         = value_type*;
	using const_pointer   = value_type const*;
	using reference       = value_type&;
	using const_reference = value_type const&;

public:
	Buffer()                               = delete;
	Buffer(const Buffer& other)            = default;
	Buffer(Buffer&& other)                 = default;
	Buffer& operator=(const Buffer& other) = default;
	Buffer& operator=(Buffer&& other)      = default;
	~Buffer()                              = default;

	Buffer(const range_type& range) :
		base_type(std::make_shared<detail::buffer<T,N>>(range)) {
	}

	Buffer(pointer host_ptr, const range_type& range) :
		base_type(std::make_shared<detail::buffer<T,N>>(host_ptr,range)) {
	}

	template<access::mode Mode>
	pointer get_access(Context const& context){
		return impl->template get_access<Mode>(context);
	}

	template<access::mode Mode>
	pointer get_access(const Handler& handle){
		return impl->template get_access<Mode>(handle);
	}

	/** Return number of elements within the Buffer
	 */
	size_type size() const {
		return impl->size();
	}

	/** Return number of bytes within the Buffer array
	 */
	size_type bytes() const {
		return impl->bytes();
	}

	/** Get Range associated with Buffer
	 */
	const range_type& range() const {
		return impl->range();
	}

	/** Set pointer where final data will be written on destruction
	 */
	template<typename Destination = std::nullptr_t>
	void set_final_data(Destination final_data = nullptr) {
		impl->set_final_data(final_data);
	}

	/** Force or cancel writing back data on destruction
	 */
	void set_write_back(const bool flag = true) {
		impl->set_write_back(flag);
	}

private:
	// Provide shortcut for base type name
	using base_type = typename Buffer::shared_ptr_impl;

	// Make the base_ptr directly accessible in this class
	using base_type::impl;

	// Allow base to access for comparison operators
	friend base_type;
};

} // namespace jakl



#endif /* INCLUDE_JAKL_BUFFER_HPP_ */
