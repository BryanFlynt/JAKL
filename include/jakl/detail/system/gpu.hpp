/*
 * gpu.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_


#include <cstddef> // std::size_t

namespace jakl {
namespace system {
namespace gpu {

/// Return number of CPU Devices on System
/*
 */
std::size_t num_device();

} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_ */
