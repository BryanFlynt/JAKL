/*
 * Device.hpp
 *
 *  Created on: Mar 16, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DEVICE_HPP_
#define INCLUDE_JAKL_DEVICE_HPP_

#include "jakl/core/id.hpp"
#include "jakl/core/system.hpp"
#include "jakl/detail/device.hpp"
#include "jakl/detail/host_device.hpp"
#include "jakl/detail/gpu_device.hpp"

#include <cstddef>

#include <iostream>

namespace jakl {

class Device : public detail::shared_ptr_base<Event,detail::device>  {


	//-------------------------------------------------------------------------
	// Types & Constants
	//-------------------------------------------------------------------------


	//-------------------------------------------------------------------------
	// Construction & Destruction
	//-------------------------------------------------------------------------
public:
	Device(Device const& other)            = default;
	Device(Device&& other)                 = default;
	~Device()                              = default;
	Device& operator=(Device const& other) = default;
	Device& operator=(Device&& other)      = default;

	/** Default constructed Device uses the host
	 *
	 * Assigns our shared_ptr (impl_ptr) to be the
	 * single instance of the shared_ptr to host_device
	 *
	 * TODO: Should get host_device from a Factory class ?
	 */
	Device() : base_type(detail::host_device::instance()) {
	}

	/** Device with ID uses GPU device
	 *
	 * Assigns our shared_ptr (impl_ptr) to be a new
	 * shared_ptr tracking the GPU with device ID
	 *
	 * TODO: Should get gpu_device from a Factory class ?
	 */
	Device(ID const& id) : base_type( std::make_shared<detail::gpu_device>(id) )  {
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------

	/** Less than Operator
	 *
	 * A Host is less than a device and devices are compared by their ID
	 */
	bool operator<(Device const& other) const {
		if( is_host() ^ other.is_host() ){
			return is_host();
		}
		return is_host() ? false: (id() < other.id());
	}

	bool operator==(Device const& other) const {
		if( is_host() ^ other.is_host() ){
			return false;
		}
		return is_host() ? true: (id() == other.id());
	}

	//-------------------------------------------------------------------------
	// Access
	//-------------------------------------------------------------------------

	/** Returns true if Device is Host
	 */
	bool is_host() const noexcept {
		return base_ptr_->is_host();
	}

	/** Returns true if Device is CPU
	 */
	bool is_cpu() const noexcept {
		return base_ptr_->is_cpu();
	}

	/** Returns true if Device is GPU
	 */
	bool is_gpu() const noexcept {
		return base_ptr_->is_gpu();
	}

	/** Get ID of Device
	 */
	ID id() const noexcept {
		JAKL_ASSERT(not is_host());
		return base_ptr_->id();
	}

	//-------------------------------------------------------------------------
	// [Private]
	//-------------------------------------------------------------------------
private:
	// Provide shortcut for base type name
	// base_type = std::shared_ptr<detail::device>
	using base_type = typename Device::shared_ptr_base;

	// Make the implementation directly accessible in this class
	using base_type::base_ptr_;

	// Allow base to access for comparison operators
	friend base_type;

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------
	//
	// Everything in base since we are using PIMPL design pattern

};


} // namespace jakl


#endif /* INCLUDE_JAKL_DEVICE_HPP_ */
