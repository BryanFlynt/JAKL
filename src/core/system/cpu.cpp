/*
 * cpu.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */


#include "jakl/config/assert.hpp"
#include "jakl/core/system.hpp"

#include "omp.h"

#include <cstdlib>

namespace jakl {
namespace system {


struct cpu {

	static void* allocate_memory(const std::size_t bytes, Device const& dev){
		JAKL_ASSERT( dev.is_host() );
		void* ptr = omp_target_alloc(bytes, dev.id());
		if( not ptr ){
			JAKL_ASSERT(false); // Some type of bad alloc
		}
		return ptr;
	}

	static void free_memory(void* device_ptr, Device const& dev){
		JAKL_ASSERT( dev.is_host() );
		omp_target_free(device_ptr, dev.id());
	}

	static void copy_memory(void* dst_ptr, const void* src_ptr, std::size_t bytes, Device const& dst, Device const& src) {
		const std::size_t zero_offset = 0;
		omp_target_memcpy(dst_ptr, src_ptr, bytes, zero_offset, zero_offset, dst.id(), src.id());
	}


};  // struct cpu

} // namespace system
} // namespace jakl


