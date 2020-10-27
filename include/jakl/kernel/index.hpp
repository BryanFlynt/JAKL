/*
 * index.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_INDEX_HPP_
#define INCLUDE_JAKL_CORE_INDEX_HPP_

#include "jakl/config/config.hpp"

JAKL_BEGIN_DEVICE_CODE
#include <cstddef>

namespace jakl {

template<std::size_t N>
class Index final {
	static_assert(N > 0, "Cannot have 0 Dimensional Index");

public:
	using size_type  = std::size_t;
	using index_type = std::ptrdiff_t;

public:

	Index()                              = default;
	Index(const Index& other)            = default;
	Index(Index&& other)                 = default;
	~Index()                             = default;
	Index& operator=(const Index& other) = default;
	Index& operator=(Index&& other)      = default;

	/** Create from Range
	 *
	 * Will run on host but not on Device
	 */
	Index(const size_type i, size_type const* range_data_ptr);

	/** Implicit conversion to single index
	 */
	operator size_type() const {
		return i_;
	}

	/** Get index by dimension
	 */
	size_type operator[](const size_type n) const;

	/** Get index of arbitrary combination
	 */
	template<typename... Args>
	size_type operator()(const Args... args) const;

protected:

	void set_on_device_(const size_type i, size_type const* range_data_ptr);

	void calc_index_();

private:
	size_type const* range_;
	size_type index_[N];
	size_type i_;

	// Class used to construct Index on a device
	// Required because constructors do not work on
	// all devices.  AArrgghh!!!
	friend class kernel;
};

} // namespace jakl
JAKL_END_DEVICE_CODE

#include "index.ipp"

#endif /* INCLUDE_JAKL_CORE_INDEX_HPP_ */
