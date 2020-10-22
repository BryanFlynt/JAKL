/*
 * range.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_RANGE_HPP_
#define INCLUDE_JAKL_RANGE_HPP_


#include "jakl/config.hpp"

#include <cstddef>

namespace jakl {

template<std::size_t N>
class Range final {
	JAKL_STATIC_ASSERT(N > 0, "Cannot have 0 Dimensional Range");

public:
  using size_type  = std::size_t;
  using index_type = std::ptrdiff_t;

public:

  Range()                              = delete;
  Range(const Range& other)            = default;
  Range(Range&& other)                 = default;
  ~Range()                             = default;
  Range& operator=(const Range& other) = default;
  Range& operator=(Range&& other)      = default;

  template<typename... Args>
  Range(const Args... args);

  size_type operator[](const size_type n) const;

  size_type size() const;

  const size_type* data() const;

private:
  const size_type dims_[N];
};

} // namespace jakl


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



#endif /* INCLUDE_JAKL_RANGE_HPP_ */
