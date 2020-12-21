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

/// Return number of Host Devices on System
/*
 */
constexpr
std::size_t num_device() noexcept {
	return 1;
}

} /* namespace host */
} /* namespace system */
} /* namespace jakl */

#endif /* INCLUDE_JAKL_DETAIL_SYSTEM_HOST_HPP_ */
