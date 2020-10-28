/*
 * system.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_SYSTEM_HPP_
#define INCLUDE_JAKL_SYSTEM_HPP_


#include "jakl/device.hpp"
#include "jakl/id.hpp"



#include <cstddef>

namespace jakl {
namespace system {


// ===================================================
//             Device Query Routines
// ===================================================


/** Return Number of Devices on System
 */
inline
std::size_t num_device() {

//
// OpenMP Off-Loading
//
#if defined(JAKL_USE_OPENMP_DEVICE)
	return openmp::num_device();
	//return omp_get_num_devices();

//
// CUDA Off-Loading
//
#elif defined(JAKL_USE_CUDA_DEVICE)
	return cuda::num_device();

	//int count = 0;
	//auto error_code = cudaGetDeviceCount(&count);
	//if(error_code != cudaSuccess){
	//	JAKL_ACCESS(false);
	//}
	//return count;

//
// HIP Off-Loading
//
#elif defined(JAKL_USE_HIP_DEVICE)
	return hip::num_device();
	//return 0;

//
// No Device Off-Loading
//
#else
	return 0;

#endif

}

// ===================================================
//             Device Factory Routines
// ===================================================

/** Return Host Device
 */
inline
Device host_device() {
	return detail::host_device::instance();
}

/** Return CPU Device
 */
inline
Device cpu_device(ID const& id = 0) {
	return std::make_shared<detail::cpu_device>(id);
}

/** Return GPU Device
 */
inline
Device gpu_device(ID const& id = 0) {
	return std::make_shared<detail::gpu_device>(id);
}

/** Return Default Device
 */
inline
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
		mem = gpu::allocate_memory(bytes);
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
		gpu::free_memory(ptr_to_memory,bytes);
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

	const auto& dst_device = dst_context.get_device();
	const auto& src_device = src_context.get_device();

	if( dst_device.is_gpu() || src_device.is_gpu() ) {
		gpu::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
	}
	else if( dst_device.is_cpu() || src_device.is_cpu() ) {
		cpu::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
	}
	else if( dst_device.is_host() and src_device.is_host() ) {
		host::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
	}
	else {
		JAKL_ASSERT(false);
	}
}



} // namespace system
} // namespace jakl



#endif /* INCLUDE_JAKL_SYSTEM_HPP_ */
