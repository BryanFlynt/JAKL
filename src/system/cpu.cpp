/*
 * cpu.cpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */


#include "jakl/system/cpu.hpp"


#include <cstring>
#include <new>


namespace jakl {
namespace system {
namespace cpu {


/** Allocate Memory
 */
void* allocate_memory(const std::size_t bytes){
	return ::operator new(bytes, std::align_val_t(64));
}

void free_memory(void* ptr_to_memory, const std::size_t bytes){
	return ::operator delete(ptr_to_memory, bytes, std::align_val_t(64));
}

void copy_memory(void* dst_ptr,	const void* src_ptr, const std::size_t bytes){
	std::memcpy(dst_ptr,src_ptr,bytes); // TODO: OpenMP parallel copy?
}


} /* namespace cpu */
} /* namespace system */
} /* namespace jakl */


