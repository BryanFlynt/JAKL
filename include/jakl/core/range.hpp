/*
 * range.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_RANGE_HPP_
#define INCLUDE_JAKL_CORE_RANGE_HPP_

#include "jakl/config/assert.hpp"


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

#include "range.ipp"

#endif /* INCLUDE_JAKL_CORE_RANGE_HPP_ */
