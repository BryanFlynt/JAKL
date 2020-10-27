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

#include <cstddef>


namespace jakl {

class Device final {

public:
	Device(const Device& other)            = default;
	Device(Device&& other)                 = default;
	~Device()                              = default;
	Device& operator=(const Device& other) = default;
	Device& operator=(Device&& other)      = default;

	Device() : id_(system::default_device()){
	}

	/** Create Device with ID
	 */
	Device(const ID& id) : id_(id) {
	}

	/** Get ID of Device
	 */
	const ID& id() const {
		return id_;
	}

	/** Returns true if Device is host_Device
	 */
	bool is_host() const {
		return (id() == system::host_device());
	}

	/** Check if Device are the same
	 */
	bool operator==(const Device &other) const {
		return id_ == other.id_;
	}


private:
	ID id_;
};


} // namespace jakl


#endif /* INCLUDE_JAKL_DEVICE_HPP_ */
