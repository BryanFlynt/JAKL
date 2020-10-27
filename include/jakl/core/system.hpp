/*
 * system.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_SYSTEM_HPP_
#define INCLUDE_JAKL_CORE_SYSTEM_HPP_


#include "jakl/core/id.hpp"

#include <cstddef>

namespace jakl {
namespace system {

/** Return Number of Devices on System
 */
std::size_t num_device();

/** Return ID of Host Device
 */
ID host_device();

/** Return ID of Default Device
 *
 * OpenMP always returns default_device of 0
 * even when there are not devices.
 */
ID default_device();

/** Allocate Device Memory
 */
void* allocate_memory(const std::size_t bytes, const ID device);

/** Free Device Memory
 */
void free_memory(void* device_ptr, const ID device);


/** Copy memory between device pointer
 */
void memcpy(void* dst_ptr, const void* src_ptr, std::size_t bytes, ID dst_id, ID src_id);

/** Allocate Memory on the Host
 */
void* malloc_host(const std::size_t bytes);

/** Allocate Memory on the Device
 */
void* malloc_device(const std::size_t bytes, const ID device);

/** Allocate Memory on the Shared Device
 */
void* malloc_shared(const std::size_t bytes, const ID device);



} // namespace system
} // namespace jakl


#endif /* INCLUDE_JAKL_CORE_SYSTEM_HPP_ */
