/*
 * gpu.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_


#include "jakl/context.hpp"

namespace jakl {
namespace system {
namespace gpu {


/** Allocate Memory
 */
inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	void* mem;
	auto result = cudaMalloc(&mem,bytes);
	if( result != cudaSuccess ){

	}
	return mem;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	return ::operator delete(ptr_to_memory, bytes, std::align_val_t(64));
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	std::memcpy(dst_ptr,src_ptr,bytes); // TODO: OpenMP parallel copy?
}


} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */



#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_GPU_HPP_ */
