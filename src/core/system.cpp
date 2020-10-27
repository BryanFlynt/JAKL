/*
 * system.cpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#include "jakl/config/assert.hpp"
#include "jakl/core/system.hpp"
#include "jakl/core/device.hpp"

#include "omp.h"

#include <cstdlib>

namespace jakl {
namespace system {


std::size_t
num_device() {
	return omp_get_num_devices();
}

Device
host_device() {
	return detail::host_device::instance();
}

// OpenMP always returns default_device of 0
// even when there are no devices ???
Device
default_device() {
	if( num_device() == 0 ){
		return host_device();
	}
	return detail::gpu_device(0);
}






void*
allocate_memory(const std::size_t bytes, const Device& dev){
	void* ptr = omp_target_alloc(bytes, dev.id());
	if( not ptr ){
		// Some type of bad alloc
	}
	return ptr;
}

void
free_memory(void* device_ptr, const Device& dev){
	omp_target_free(device_ptr, dev.id());
}

void
memcpy(void* dst_ptr, const void* src_ptr, std::size_t bytes, const Device& dst_dev, const Device&  src_dev){
	const std::size_t zero_offset = 0;
	omp_target_memcpy(dst_ptr, src_ptr, bytes, zero_offset, zero_offset, dst_dev.id(), src_dev.id());
}

void*
malloc_host(const std::size_t bytes) {
	void* ptr = malloc(bytes);
	if( not ptr ){
		// Some type of bad alloc
	}
	return ptr;
}

void*
malloc_device(const std::size_t bytes, const Device& dev) {
	void* ptr = omp_target_alloc(bytes, dev.id());
	if( not ptr ){
		// Some type of bad alloc
	}
	return ptr;
}

void*
malloc_shared(const std::size_t bytes, const Device& dev) {
	void* ptr = omp_target_alloc(bytes, dev.id());
	omp_target_associate_ptr(ptr,ptr,bytes,0,0);
	if( not ptr ){
		// Some type of bad alloc
	}
	return ptr;
}


} // namespace system
} // namespace jakl
