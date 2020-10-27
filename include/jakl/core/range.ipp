/*
 * range.ipp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */


#include "jakl/config/assert.hpp"


namespace jakl {

template<std::size_t N>
template<typename... Args>
Range<N>::Range(const Args... args) : dims_{static_cast<size_type>(args)...}{
	JAKL_STATIC_ASSERT(sizeof...(args) == N, "Must have N Dimensions");
}

template<std::size_t N>
typename Range<N>::size_type
Range<N>::operator[](const size_type n) const {
	JAKL_ASSERT(n < N);
    return dims_[n];
  }

template<std::size_t N>
typename Range<N>::size_type
Range<N>::size() const {
	size_type sz = 1;
	for(std::size_t i = 0; i < N; ++i){
		sz *= dims_[i];
	}
	return sz;
}

template<std::size_t N>
const typename Range<N>::size_type*
Range<N>::data() const{
	return dims_;
}

} // namespace jakl
