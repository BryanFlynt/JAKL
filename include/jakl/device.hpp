/*
 * device.hpp
 *
 *  Created on: Oct 14, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_DEVICE_HPP_
#define INCLUDE_JAKL_CORE_DEVICE_HPP_

#include "jakl/config.hpp"
#include "jakl/id.hpp"

#include "jakl/detail/device/device.hpp"
#include "jakl/detail/device/cpu_device.hpp"
#include "jakl/detail/device/gpu_device.hpp"
#include "jakl/detail/device/host_device.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"

#include <cassert>

namespace jakl {


class Device : public detail::shared_ptr_impl<Device, detail::device> {

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
	Device(ID const& id) : base_type(new detail::gpu_device(id))  {
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------

	bool operator<(Device const& other) const noexcept {
		if( this->is_host() ^ other.is_host() ){
			return this->is_host();
		}
		return (this->is_host()) ? false: (this->id() < other.id());
	}


	bool operator==(Device const& other) const noexcept {
		if( this->is_host() ^ other.is_host() ){
			return false;
		}
		return (this->is_host()) ? true: (this->id() == other.id());
	}


	//-------------------------------------------------------------------------
	// Access
	//-------------------------------------------------------------------------

	/** Returns true if Device is Host
	 */
	bool is_host() const noexcept {
		return impl_ptr->is_host();
	}

	/** Returns true if Device is CPU
	 */
	bool is_cpu() const noexcept {
		return impl_ptr->is_cpu();
	}

	/** Returns true if Device is GPU
	 */
	bool is_gpu() const noexcept {
		return impl_ptr->is_gpu();
	}

	/** Get ID of Device
	 */
	ID const& id() const noexcept {
		JAKL_ASSERT(not is_host());
		return impl_ptr->id();
	}

	//-------------------------------------------------------------------------
	// [Private]
	//-------------------------------------------------------------------------
private:
	// Provide shortcut for base type name
	// base_type = std::shared_ptr<detail::device>
	using base_type = typename Device::shared_ptr_impl;

	// Make the implementation directly accessible in this class
	using base_type::impl_ptr;

	// Allow base to access for comparison operators
	friend base_type;

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------
	//
	// Everything in base since we are using PIMPL design pattern
};


} // namespace jakl



#endif /* INCLUDE_JAKL_CORE_DEVICE_HPP_ */
