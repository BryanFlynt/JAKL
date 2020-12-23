/**
 * \file       access.hpp
 * \author     Bryan Flynt
 * \date       Dec 22, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_ACCESS_HPP_
#define INCLUDE_JAKL_ACCESS_HPP_


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


#endif /* INCLUDE_JAKL_ACCESS_HPP_ */
