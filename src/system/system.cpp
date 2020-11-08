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
#include "jakl/detail/system/openmp.hpp"


#include <memory> // std::make_shared

namespace jakl {
namespace system {


// ===================================================
//             Device Query Routines
// ===================================================


/** Return Number of Devices on System
 */
std::size_t num_device() {
#if defined(JAKL_USE_OPENMP_DEVICE)
	return gpu::openmp::num_device();
#elif defined(JAKL_USE_CUDA_DEVICE)
	return gpu::cuda::num_device();
#elif defined(JAKL_USE_HIP_DEVICE)
	return gpu::hip::num_device();
#else
	return 0;
#endif
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
Device cpu_device(ID const& id) {
	return Device(std::make_shared<detail::cpu_device>(id));
}

/** Return GPU Device
 */
Device gpu_device(ID const& id) {
	return Device(std::make_shared<detail::gpu_device>(id));
}

/** Return Default Device
 */
Device default_device() {
	if( num_device() == 0 ){
		return cpu_device();
	}
	return gpu_device();
}


// ===================================================
//                 Memory Routines
// ===================================================

/** Allocate Memory
 */
void* allocate_memory(Context const& context, const std::size_t bytes) {
	void* mem = nullptr;
	if( context.get_device().is_host() ){
		mem = host::allocate_memory(bytes);
	}
	else if( context.get_device().is_cpu() ){
		mem = cpu::allocate_memory(bytes);
	}
	else if( context.get_device().is_gpu() ){
		mem = gpu::allocate_memory(context,bytes);
	}
	else {
		JAKL_ASSERT(false);
	}
	JAKL_ASSERT(mem);
	return mem;
}

/** Free Memory
 */
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	if( context.get_device().is_host() ){
		host::free_memory(ptr_to_memory,bytes);
	}
	else if( context.get_device().is_cpu() ){
		cpu::free_memory(ptr_to_memory,bytes);
	}
	else if( context.get_device().is_gpu() ){
		gpu::free_memory(context,ptr_to_memory,bytes);
	}
	else {
		JAKL_ASSERT(false);
	}
	ptr_to_memory = nullptr;
}


/** Copy Memory
 */
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context
		) {
	JAKL_ASSERT(dst_ptr);
	JAKL_ASSERT(src_ptr);

	const auto& dst_device = dst_context.get_device();
	const auto& src_device = src_context.get_device();

	if( dst_device.is_gpu() || src_device.is_gpu() ) {
		gpu::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
	}
	else if( dst_device.is_cpu() || src_device.is_cpu() ) {
		cpu::copy_memory(dst_ptr,src_ptr,bytes);
	}
	else if( dst_device.is_host() and src_device.is_host() ) {
		host::copy_memory(dst_ptr,src_ptr,bytes);
	}
	else {
		JAKL_ASSERT(false);
	}
}



} // namespace system
} // namespace jakl

