/*
 * gpu.cpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */


#include "jakl/detail/system/gpu.hpp"

#include "jakl/config.hpp"

namespace jakl {
namespace system {
namespace gpu {

// Return number of CPU Devices on System
std::size_t num_device() {
#if defined(JAKL_USE_OPENMP_DEVICE)
	return omp_get_num_devices();
#elif defined(JAKL_USE_CUDA_DEVICE)
	int count = 0;
	cudaGetDeviceCount(&count);
	return count;
#elif defined(JAKL_USE_HIP_DEVICE)
	return 0;
#else
	return 0;
#endif
}

} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */


