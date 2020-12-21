/**
 * \file       cpu_device.hpp
 * \author     Bryan Flynt
 * \date       Dec 21, 2020
 * \copyright  Copyright (C) 2020 Bryan Flynt - All Rights Reserved
 */

#ifndef INCLUDE_JAKL_DETAIL_DEVICE_CPU_DEVICE_HPP_
#define INCLUDE_JAKL_DETAIL_DEVICE_CPU_DEVICE_HPP_


#include "jakl/config.hpp"
#include "jakl/id.hpp"
#include "jakl/detail/device/device.hpp"
#include "jakl/detail/tools/singleton.hpp"


namespace jakl {
namespace detail {


class cpu_device :
		public device,
		public detail::singleton<cpu_device> {

public:
	cpu_device()                                   = default;
	cpu_device(cpu_device const& other)            = default;
	cpu_device(cpu_device&& other)                 = default;
	cpu_device& operator=(cpu_device const& other) = default;
	cpu_device& operator=(cpu_device&& other)      = default;
	virtual ~cpu_device(){}

	/// Return false
	bool is_host() const noexcept {
		return false;
	}

	/// Return true since "CPU" device
	bool is_cpu() const noexcept {
		return true;
	}

	/// Return false
	bool is_gpu() const noexcept {
		return false;
	}

	/// Return false
	bool is_accelerator() const noexcept {
		return false;
	}

	ID const& id() const noexcept {
		JAKL_ASSERT(false); // CPU has no ID
	}

};

} /* namespace detail */
} /* namespace jakl */

#endif /* INCLUDE_JAKL_DETAIL_DEVICE_CPU_DEVICE_HPP_ */
