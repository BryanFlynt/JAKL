/*
 * system.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_SYSTEM_HPP_
#define INCLUDE_JAKL_SYSTEM_HPP_

#include "jakl/context.hpp"
#include "jakl/device.hpp"
#include "jakl/id.hpp"

#include <cstddef> // std::size_t

namespace jakl {
namespace system {


// ===================================================
//             Device Query Routines
// ===================================================

/** Return Number of Devices on System
 */
std::size_t num_device();


// ===================================================
//             Device Factory Routines
// ===================================================

/** Return Host Device
 */
Device host_device();

/** Return CPU Device
 */
Device cpu_device(ID const& id = 0);

/** Return GPU Device
 */
Device gpu_device(ID const& id = 0);

/** Return Default Device
 */
Device default_device();



// ===================================================
//                 Memory Routines
// ===================================================

/** Allocate Memory
 */
void* allocate_memory(Context const& context, const std::size_t bytes);

/** Free Memory
 */
void free_memory(Context const& context, void* ptr_to_memory, const std::size_t bytes);


/** Copy Memory
 */
void copy_memory(
		void* dst_ptr,
		const void* src_ptr,
		const std::size_t bytes,
		Context const& dst_context,
		Context const& src_context
		);


} // namespace system
} // namespace jakl



#endif /* INCLUDE_JAKL_SYSTEM_HPP_ */
