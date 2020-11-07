/*
 * openmp.hpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_


#include "jakl/context.hpp"


#include <cstddef>  // std::size_t


namespace jakl {
namespace system {
namespace gpu {
namespace openmp {



/** Return Number of Devices on System
 */
std::size_t num_device();

/** Allocate Memory
 */
void* allocate_memory(Context const& context, const std::size_t bytes);

void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes);

void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context);

} /* namespace openmp */
} /* namespace gpu */
} /* namespace system */
} /* namespace jakl */



#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_OPENMP_HPP_ */
