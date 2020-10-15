/*
 * device.hpp
 *
 *  Created on: Oct 14, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CORE_DEVICE_HPP_
#define INCLUDE_JAKL_CORE_DEVICE_HPP_

#include "jakl/core/id.hpp"


namespace jakl {


class Device final {

public:
	Device(Device const& other)            = default;
	Device(Device&& other)                 = default;
	~Device()                              = default;
	Device& operator=(Device const& other) = default;
	Device& operator=(Device&& other)      = default;

	/** Default construct Device or Provide ID
	 */
	Device(ID const& id = system::default_device()) : id_(id) {
	}

	/** Returns true if Device is host_Device
	 */
	bool is_host() const {
		return (id() == system::host_device());
	}

	/** Check if Device are the same
	 */
	bool operator==(Device const& other) const {
		return id_ == other.id_;
	}

	/** Get ID of Device
	 */
	ID const& id() const {
		return id_;
	}


private:
	ID id_;
};


} // namespace jakl



#endif /* INCLUDE_JAKL_CORE_DEVICE_HPP_ */
