/*
 * gpu.cpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */



#include "jakl/context.hpp"

#include "jakl/detail/system/host.hpp"
#include "jakl/detail/system/cpu.hpp"
#include "jakl/detail/system/gpu.hpp"
#include "jakl/detail/system/cuda.hpp"
#include "jakl/detail/system/hip.hpp"
#include "jakl/detail/system/openmp.hpp"

namespace jakl {
namespace system {
namespace gpu {


/** Allocate Memory
 */
void* allocate_memory(Context const& context, const std::size_t bytes){

#if defined(JAKL_USE_OPENMP_DEVICE)
	return openmp::allocate_memory(context,bytes);
#elif defined(JAKL_USE_CUDA_DEVICE)
	return cuda::allocate_memory(context,bytes);
#elif defined(JAKL_USE_HIP_DEVICE)
	return hip::allocate_memory(context,bytes);
#else
	JAKL_ERROR("Unrecognized gpu::allocate_memory called");
#endif
}


void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){

#if defined(JAKL_USE_OPENMP_DEVICE)
	openmp::free_memory(context,ptr_to_memory,bytes);
#elif defined(JAKL_USE_CUDA_DEVICE)
	cuda::free_memory(context,ptr_to_memory,bytes);
#elif defined(JAKL_USE_HIP_DEVICE)
	hip::free_memory(context,ptr_to_memory,bytes);
#else
	JAKL_ERROR("Unrecognized gpu::free_memory called");
#endif
}


void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){

#if defined(JAKL_USE_OPENMP_DEVICE)
	openmp::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
#elif defined(JAKL_USE_CUDA_DEVICE)
	cuda::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
#elif defined(JAKL_USE_HIP_DEVICE)
	hip::copy_memory(dst_ptr,src_ptr,bytes,dst_context,src_context);
#else
	JAKL_ERROR("Unrecognized gpu::copy_memory called");
#endif
}


} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */


