/*
 * device.hpp
 *
 *  Created on: Oct 18, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_DEVICE_HPP_
#define INCLUDE_JAKL_DETAIL_DEVICE_HPP_


#include "jakl/id.hpp"


namespace jakl {
namespace detail {

class device {
public:
	device()                               = default;
	device(device const& other)            = default;
	device(device&& other)                 = default;
	device& operator=(device const& other) = default;
	device& operator=(device&& other)      = default;
	virtual ~device()                      = default;

	/// Return true if "Host" device
	virtual bool is_host() const noexcept = 0;

	// Return true if "CPU" device
	virtual bool is_cpu() const noexcept = 0;

	/// Return true if "GPU" device
	virtual bool is_gpu() const noexcept = 0;

	/// Return true if "Accelerator" device
	virtual bool is_accelerator() const noexcept = 0;

	/// Return Device ID if exists
	virtual ID const& id() const noexcept = 0;
};


} /* namespace detail */
} /* namespace jakl */


#endif /* INCLUDE_JAKL_DETAIL_DEVICE_HPP_ */
