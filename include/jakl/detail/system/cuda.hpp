/*
 * cuda.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_CUDA_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_CUDA_HPP_


#include "jakl/context.hpp"

namespace jakl {
namespace system {
namespace cuda {


/** Allocate Memory
 */
inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	const int cuda_id = context.get_device().id();
	auto dev_result = cudaSetDevice(cuda_id);
	if( dev_result != cudaSuccess ){

	}

	void* mem;
	auto result = cudaMalloc(&mem,bytes);
	if( result != cudaSuccess ){

	}
	return mem;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	const int cuda_id = context.get_device().id();
	auto dev_result = cudaSetDevice(cuda_id);
	if( dev_result != cudaSuccess ){

	}

	auto result = cudaFree(ptr_to_memory);
	if( result != cudaSuccess ){

	}
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){

	cudaError_t result = cudaSuccess;
	if( dst_context.get_device().is_host() ) {

	}

	cudaMemcpy(dst_ptr,src_ptr,bytes, );

}


} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */




#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_CUDA_HPP_ */
