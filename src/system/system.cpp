/*
 * system.cpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */



#include "jakl/system.hpp"

#include "jakl/config.hpp"
#include "jakl/device.hpp"
#include "jakl/id.hpp"

#include "jakl/detail/device/device.hpp"
#include "jakl/detail/device/cpu_device.hpp"
#include "jakl/detail/device/gpu_device.hpp"
#include "jakl/detail/device/host_device.hpp"

#include "jakl/detail/system/cpu.hpp"
#include "jakl/detail/system/gpu.hpp"
#include "jakl/detail/system/host.hpp"

#include <memory> // std::make_shared

namespace jakl {
namespace system {


// ===================================================
//             Device Query Routines
// ===================================================


/** Return Number of Devices on System
 */
std::size_t num_device() {
	std::size_t total = 0;
	total += host::num_device();
	total += cpu::num_device();
	total += gpu::num_device();
	return total;
}

// ===================================================
//             Device Factory Routines
// ===================================================

/** Return Host Device
 */
Device host_device() {
	return Device(detail::host_device::instance());
}

/** Return CPU Device
 */
Device cpu_device() {
	return Device(detail::cpu_device::instance());
}

/** Return GPU Device
 */
Device gpu_device(ID const& id) {
	JAKL_ASSERT(gpu::num_device() > 0);
	return Device(std::make_shared<detail::gpu_device>(id));
}

/** Return Default Device
 */
Device default_device() {
	if( gpu::num_device() == 0 ){
		return cpu_device();
	}
	return gpu_device();
}

} // namespace system
} // namespace jakl

