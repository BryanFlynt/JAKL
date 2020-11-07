/*
 * gpu_device.hpp
 *
 *  Created on: Oct 18, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_DEVICE_GPU_DEVICE_HPP_
#define INCLUDE_JAKL_DETAIL_DEVICE_GPU_DEVICE_HPP_


#include "jakl/id.hpp"
#include "jakl/detail/device/device.hpp"
#include "jakl/detail/tools/singleton.hpp"


namespace jakl {
namespace detail {

class gpu_device :
		public device {

public:
	gpu_device(gpu_device const& other)            = default;
	gpu_device(gpu_device&& other)                 = default;
	gpu_device& operator=(gpu_device const& other) = default;
	gpu_device& operator=(gpu_device&& other)      = default;
	virtual ~gpu_device(){}

	gpu_device() : id_(0) {
	}

	gpu_device(ID const& id) : id_(id) {
	}

	/// Return true if "Host" device
	bool is_host() const noexcept {
		return false;
	}

	/// Return true if "CPU" device
	bool is_cpu() const noexcept {
		return false;
	}

	/// Return true if "GPU" device
	bool is_gpu() const noexcept {
		return true;
	}

	ID const& id() const noexcept {
		return id_;
	}

protected:
	ID id_;

};



} /* namespace detail */
} /* namespace jakl */




#endif /* INCLUDE_JAKL_DETAIL_DEVICE_GPU_DEVICE_HPP_ */
