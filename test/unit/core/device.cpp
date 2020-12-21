/*
 * device.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: bflynt
 */


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/unit/catch.hpp"

#include "jakl/device.hpp"


TEST_CASE("JAKL Device", "[default]") {

	SECTION("Constructors") {

		jakl::Device a;
		REQUIRE( a.is_host() == true );
		REQUIRE( a.is_cpu()  == false );
		REQUIRE( a.is_gpu()  == false );
		REQUIRE( a.is_accelerator() == false );

		jakl::Device c(jakl::cpu_selector_v);
		REQUIRE( c.is_host() == false );
		REQUIRE( c.is_cpu()  == true );
		REQUIRE( c.is_gpu()  == false );
		REQUIRE( c.is_accelerator() == false );

		jakl::ID id = 3;
		jakl::Device g(id);
		REQUIRE( g.is_host() == false );
		REQUIRE( g.is_cpu()  == false );
		REQUIRE( g.is_gpu()  == true );
		REQUIRE( g.is_accelerator() == false );
		REQUIRE( g.id()      == id    );
	}

}






