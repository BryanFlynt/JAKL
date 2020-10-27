/*
 * host.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */


#include "jakl/config/assert.hpp"

#include <new>      // new
#include <cstring>  // memcpy

namespace jakl {
namespace system {


struct host {

	static void* allocate_memory(const std::size_t bytes, const std::size_t alignment = 64){
		void* ptr = ::operator new(bytes, std::align_val_t(alignment));
		JAKL_ASSERT(ptr);
		return ptr;
	}

	static void free_memory(void* ptr, const std::size_t alignment = 64){
		::operator delete(ptr, std::align_val_t(alignment));
	}

	static void copy_memory(void* dst_ptr, const void* src_ptr, std::size_t bytes) {
		JAKL_ASSERT(dst_ptr);
		JAKL_ASSERT(src_ptr);
		const std::size_t zero_offset = 0;
		std::memcpy(dst_ptr, src_ptr, bytes);
	}

};  // struct host

} // namespace system
} // namespace jakl




