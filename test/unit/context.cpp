/*
 * context.cpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Context", "[default]") {

	SECTION("Constructors") {

		// Constructor using host device
		jakl::Device  host_dev = jakl::system::host_device();
		jakl::Context context_on_host(host_dev);
		REQUIRE( context_on_host.get_device().is_host() == true );
		REQUIRE( context_on_host.get_device().is_cpu()  == false );

		// Taking a Device
		jakl::Device  cpu_dev = jakl::system::cpu_device();
		jakl::Context context_on_cpu(cpu_dev);
		REQUIRE( context_on_cpu.get_device().is_host() == false );
		REQUIRE( context_on_cpu.get_device().is_cpu()  == true );

		// Since only one host device exists they should be equal
		jakl::Device  host_dev2 = jakl::system::host_device();
		jakl::Context context_on_host2(host_dev2);
		REQUIRE(context_on_host2.get_device() == context_on_host.get_device());
	}

}




