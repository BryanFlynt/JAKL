/*
 * device.hpp
 *
 *  Created on: Oct 14, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_DEVICE_HPP_
#define INCLUDE_JAKL_CORE_DEVICE_HPP_

#include "jakl/id.hpp"

#include "jakl/detail/device/device.hpp"
#include "jakl/detail/device/cpu_device.hpp"
#include "jakl/detail/device/gpu_device.hpp"
#include "jakl/detail/device/host_device.hpp"
#include "jakl/detail/tools/shared_ptr_impl.hpp"


namespace jakl {


struct default_selector {};
struct host_selector {};
struct cpu_selector {};
struct gpu_selector {};
struct accelerator_selector {};


default_selector     default_selector_v;
host_selector        host_selector_v;
cpu_selector         cpu_selector_v;
gpu_selector         gpu_selector_v;
accelerator_selector accelerator_selector_v;



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
	 * TODO: Should get host_device from a Factory class
	 */
	Device() : base_type{ detail::host_device::instance() } {
	}

	/** Device with ID uses GPU device
	 * TODO: Should get gpu_device from a Factory class
	 */
	Device(ID const& id) : base_type{ std::make_shared<detail::gpu_device>(id) }  {
	}


	Device(host_selector const& /* selector */) : base_type{ detail::host_device::instance() } {
	}

	Device(cpu_selector const& /* selector */) : base_type{ detail::cpu_device::instance() } {
	}

	Device(gpu_selector const& /* selector */) : base_type{ std::make_shared<detail::gpu_device>(0) } {
	}

	Device(accelerator_selector const& /* selector */) {
		JAKL_ASSERT("Not Implemented");
	}

	//-------------------------------------------------------------------------
	// Operators
	//-------------------------------------------------------------------------


	//-------------------------------------------------------------------------
	// Access
	//-------------------------------------------------------------------------

	/** Returns true if Device is Host
	 */
	bool is_host() const noexcept {
		return impl->is_host();
	}

	/** Returns true if Device is CPU
	 */
	bool is_cpu() const noexcept {
		return impl->is_cpu();
	}

	/** Returns true if Device is GPU
	 */
	bool is_gpu() const noexcept {
		return impl->is_gpu();
	}

	/** Returns true if Device is Accelerator
	 */
	bool is_accelerator() const noexcept {
		return impl->is_accelerator();
	}

	/** Get ID of Device
	 */
	ID const& id() const noexcept {
		return impl->id();
	}

	//-------------------------------------------------------------------------
	// [Private]
	//-------------------------------------------------------------------------
private:
	// Provide shortcut for base type name
	using base_type = typename Device::shared_ptr_impl;

	// Make the implementation directly accessible in this class
	using base_type::impl;

	// Allow base to access for comparison operators
	friend base_type;

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------

};


} // namespace jakl



#endif /* INCLUDE_JAKL_CORE_DEVICE_HPP_ */
