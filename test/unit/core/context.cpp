/*
 * context.cpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/unit/catch.hpp"

#include "jakl/context.hpp"


TEST_CASE("JAKL Context", "[default]") {

	SECTION("Constructors") {

		// Default constructor is on host device
		jakl::Context context_on_host;
		REQUIRE( context_on_host.device().is_host() == true );

		// Taking a Device
		jakl::Device a;
		jakl::Context c(a);
		REQUIRE( context_on_host.device().is_host() == true );

		// Since only one host device exists they should be equal
		REQUIRE(context_on_host.device() == context_on_host.device());
	}

}




