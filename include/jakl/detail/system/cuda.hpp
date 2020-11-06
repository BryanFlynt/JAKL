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
namespace gpu {
namespace cuda {
#if defined(JAKL_USE_CUDA_DEVICE)

/** Allocate Memory
 */
inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	int error_code(cudaSuccess);
	void* dev_ptr;

	error_code = cudaSetDevice(dev.id());
	if( error_code != cudaSuccess ) {
		JAKL_ERROR("cudaSetDevice Failed");
	}

	error_code = cudaMalloc(&dev_ptr, bytes);
	if(error_code != cudaSuccess){
		JAKL_ERROR("cudaMalloc Failed");
	}
	return dev_ptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	int error_code(cudaSuccess);

	error_code = cudaSetDevice(dev.id());
	if( error_code != cudaSuccess ) {
		JAKL_ERROR("cudaSetDevice Failed");
	}

	error_code = cudaFree(device_ptr);
	if(error_code != cudaSuccess){
		JAKL_ERROR("cudaFree Failed");
	}
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){

	int error_code(cudaSuccess);
	int direction(cudaMemcpyDefault);

	// Select Copy Direction
	if( src.is_host() ){
		if( dst.is_host() ){
			direction = cudaMemcpyHostToHost;
		}
		else {
			direction = cudaMemcpyHostToDevice;
		}
	}
	else {
		if( dst.is_host() ){
			direction = cudaMemcpyDeviceToHost;
		}
		else {
			direction = cudaMemcpyDeviceToDevice;
		}
	}

	// Perform Copy
	error_code = cudaMemcpy(dst_ptr,src_ptr,bytes,direction);
	if(error_code != cudaSuccess){
		JAKL_ASSERT(false);
	}
}
#else // defined(JAKL_USE_CUDA_DEVICE)


inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	JAKL_ERROR("cuda::allocate_memory called but not compiled");
	return nullptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	JAKL_ERROR("cuda::free_memory called but not compiled");
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	JAKL_ERROR("cuda::copy_memory called but not compiled");
}
#endif // defined(JAKL_USE_CUDA_DEVICE)

} /* namespace cuda */
} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */




#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_CUDA_HPP_ */
