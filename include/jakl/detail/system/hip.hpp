/*
 * hip.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_HIP_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_HIP_HPP_


#include "jakl/context.hpp"


namespace jakl {
namespace system {
namespace gpu {
namespace hip {
#if defined(JAKL_USE_HIP_DEVICE)

/** Allocate Memory
 */
inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	JAKL_ERROR("hip::allocate_memory called but not implemented");
	return nullptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	JAKL_ERROR("hip::free_memory called but not implemented");
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	JAKL_ERROR("hip::copy_memory called but not implemented");
}
#else // defined(JAKL_USE_HIP_DEVICE)


inline
void* allocate_memory(Context const& context, const std::size_t bytes){
	JAKL_ERROR("hip::allocate_memory called but not compiled");
	return nullptr;
}

inline
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes){
	JAKL_ERROR("hip::free_memory called but not compiled");
}

inline
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context){
	JAKL_ERROR("hip::copy_memory called but not compiled");
}
#endif // defined(JAKL_USE_HIP_DEVICE)


} /* namespace hip */
} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */





#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_HIP_HPP_ */
