/*
 * host_device.hpp
 *
 *  Created on: Oct 18, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_HOST_DEVICE_HPP_
#define INCLUDE_JAKL_DETAIL_HOST_DEVICE_HPP_

#include "jakl/config.hpp"
#include "jakl/id.hpp"
#include "jakl/detail/device/device.hpp"
#include "jakl/detail/tools/singleton.hpp"


namespace jakl {
namespace detail {


class host_device :
		public device,
		public detail::singleton<host_device> {

public:
	host_device()                                    = default;
	host_device(host_device const& other)            = default;
	host_device(host_device&& other)                 = default;
	host_device& operator=(host_device const& other) = default;
	host_device& operator=(host_device&& other)      = default;
	virtual ~host_device(){}

	/// Return true if "Host" device
	bool is_host() const noexcept {
		return true;
	}

	// Return true if "CPU" device
	bool is_cpu() const noexcept {
		return false;
	}

	/// Return true if "GPU" device
	bool is_gpu() const noexcept {
		return false;
	}

	ID const& id() const noexcept {
		JAKL_ASSERT(false);
	}

};



} /* namespace detail */
} /* namespace jakl */




#endif /* INCLUDE_JAKL_DETAIL_HOST_DEVICE_HPP_ */
