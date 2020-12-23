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

		// Taking a Device
		jakl::Device a(jakl::host_selector_v);
		jakl::Context context(a);
		REQUIRE( context.device().is_host() == true );

	}

}




