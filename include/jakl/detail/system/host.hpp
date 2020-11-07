/*
 * host.hpp
 *
 *  Created on: Nov 6, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_SYSTEM_HOST_HPP_
#define INCLUDE_JAKL_DETAIL_SYSTEM_HOST_HPP_



#include <cstddef>  // std::size_t

namespace jakl {
namespace system {
namespace host {


/** Allocate Memory
 */
void* allocate_memory(const std::size_t bytes);

void free_memory(void* ptr_to_memory, const std::size_t bytes);

void copy_memory(void* dst_ptr,	const void* src_ptr, const std::size_t bytes);


} /* namespace host */
} /* namespace system */
} /* namespace jakl */



#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_HOST_HPP_ */
