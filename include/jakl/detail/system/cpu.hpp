/*
 * cpu.hpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_CPU_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_CPU_HPP_


#include <cstddef>  // std::size_t

namespace jakl {
namespace system {
namespace cpu {

/// Return number of CPU Devices on System
/*
 */
constexpr
std::size_t num_device() noexcept {
	return 1;
}

} /* namespace cpu */
} /* namespace system */
} /* namespace jakl */

#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_CPU_HPP_ */
