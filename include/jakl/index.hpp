/*
 * index.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_INDEX_HPP_
#define INCLUDE_JAKL_INDEX_HPP_


#include "jakl/config.hpp"

#include <cstddef>

namespace jakl {

template<std::size_t N>
class Index final {
	JAKL_STATIC_ASSERT(N > 0, "Cannot have 0 Dimensional Index");

public:
	using size_type  = std::size_t;
	using index_type = std::ptrdiff_t;

public:

	Index()                              = delete;
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


namespace jakl {


template<std::size_t N>
Index<N>::Index(const size_type i, size_type const* range_data_ptr)
: i_(i), range_(range_data_ptr) {
	this->calc_index_();
}

template<std::size_t N>
typename Index<N>::size_type
Index<N>::operator[](const size_type n) const {
	return index_[n];
}

template<std::size_t N>
template<typename... Args>
typename Index<N>::size_type
Index<N>::operator()(const Args... args) const {
	//JAKL_STATIC_ASSERT(std::conjunction_v<std::is_integral<Args>...>, "Must be integers");
	JAKL_STATIC_ASSERT(sizeof...(args) == N);
	size_type dims[] = {static_cast<size_type>(args)...};
	size_type offset = 0;
	size_type stride = 1;
	for(size_type j = N; j--> 0;) {
		offset += dims[j] * stride;
		stride *= range_[j];
	}
	return offset;
}

template<std::size_t N>
void
Index<N>::set_on_device_(const size_type i, size_type const* range_data_ptr){
	i_ = i;
	range_ = range_data_ptr;
	this->calc_index_();
}

template<std::size_t N>
void
Index<N>::calc_index_(){
	size_type fac(1);
	for(size_type j = N; j--> 1;) {
		index_[j] = (i_ / fac) % range_[j];
		fac *= range_[j];
	}
	index_[0] = i_ / fac;
}

} // namespace jakl

#endif /* INCLUDE_JAKL_INDEX_HPP_ */
