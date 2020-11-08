/*
 * system.cpp
 *
 *  Created on: Mar 18, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"


#include <cstdint>
#include <iostream>

// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL System", "[default]") {

	SECTION("num_device"){
		REQUIRE( jakl::system::num_device() >= 0 );
	}

//	SECTION("host_device"){
//		REQUIRE( jakl::system::host_device() < 0 );
//	}
//
//	SECTION("default_device"){
//		auto def_device = jakl::system::default_device();
//		auto hst_device = jakl::system::host_device();
//		REQUIRE( hst_device <= def_device );
//	}
//
//	SECTION("allocate_free"){
//		const std::size_t bytes = 80000;
//		auto device = jakl::system::default_device();
//
//		void* ptr = nullptr;
//		REQUIRE( ptr == nullptr );
//
//		ptr = jakl::system::allocate_memory(bytes,device);
//		REQUIRE( ptr != nullptr );
//
//		jakl::system::free_memory(ptr,device);
//	}

}




