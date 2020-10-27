/*
 * buffer.hpp
 *
 *  Created on: Apr 1, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_BUFFER_HPP_
#define INCLUDE_JAKL_DETAIL_BUFFER_HPP_


#include "jakl/core/access.hpp"
#include "jakl/core/handler.hpp"
#include "jakl/core/id.hpp"
#include "jakl/core/range.hpp"
#include "jakl/core/system.hpp"

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
	pointer get_access(const ID id);

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
	pointer               host_ptr_;
	std::map<ID,pointer>  data_ptrs_;
	range_type            range_;
	ID                    id_of_last_write_;

};

} // namespace detail
} // namespace jakl


#include "buffer.ipp"


#endif /* INCLUDE_JAKL_DETAIL_BUFFER_HPP_ */
