/*
 * access.hpp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_ACCESS_HPP_
#define INCLUDE_JAKL_CORE_ACCESS_HPP_

namespace jakl {
namespace access {

/** Memory Buffer Access Modes
 */
enum class mode {
	read,               // Read-only access on device
	write,              // Write-only access on device
	read_write,         // Read and Write access on device
	discard_write,      // Empty space to write access on device
	discard_read_write  // Empty space to read and write access on device
}; // enum class mode

} // namespace access
} // namespace jakl

#endif /* INCLUDE_JAKL_CORE_ACCESS_HPP_ */