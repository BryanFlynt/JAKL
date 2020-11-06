/*
 * openmp.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_

#include "jakl/context.hpp"

//
// ============================================================
//             OpenMP Device Off-Load Functions
// ============================================================
//
#if defined(JAKL_USE_OPENMP_DEVICE)

#include "omp.h"


namespace jakl {
namespace system {
namespace gpu {
namespace openmp {



/** Allocate Memory
 */
inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	const int omp_id = context.get_device().id();
	void* ptr = omp_target_alloc(bytes, omp_id);
	if( not ptr ){
		JAKL_ERROR("omp_target_alloc Failed");
	}
	return ptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	const int omp_id = context.get_device().id();
	omp_target_free(ptr_to_memory, omp_id);
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	const std::size_t zero_offset = 0;
	const int dst_id = dst_context.get_device().id();
	const int src_id = src_context.get_device().id();
	omp_target_memcpy(dst_ptr, src_ptr, bytes, zero_offset, zero_offset, dst_id, src_id);
}


} /* namespace openmp */
} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */


//
// ============================================================
//              Empty (Error) Functions To Compile
// ============================================================
//
#else // defined(JAKL_USE_OPENMP_DEVICE)

namespace jakl {
namespace system {
namespace gpu {
namespace openmp {

inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	JAKL_ERROR("openmp::allocate_memory called but not compiled");
	return nullptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	JAKL_ERROR("openmp::free_memory called but not compiled");
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	JAKL_ERROR("openmp::copy_memory called but not compiled");
}

} /* namespace openmp */
} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */

#endif // defined(JAKL_USE_OPENMP_DEVICE)


#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_ */
