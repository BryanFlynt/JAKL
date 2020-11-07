/*
 * queue.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Device", "[default]") {
	using namespace jakl;

	SECTION("Host Device") {
		Device dev = system::host_device();
		REQUIRE( dev == system::host_device() );
	}

	SECTION("CPU Device") {
		Device dev = system::cpu_device();
		REQUIRE( dev == system::cpu_device() );
	}

	SECTION("GPU Device") {
		Device dev = system::gpu_device();
		REQUIRE( dev == system::gpu_device() );
	}

	SECTION("Default Device") {
		Device dev = system::default_device();
		REQUIRE( dev == system::default_device() );
	}

}

