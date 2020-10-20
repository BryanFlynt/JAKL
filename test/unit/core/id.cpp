/*
 * id.cpp
 *
 *  Created on: Oct 14, 2020
 *      Author: bflynt
 */

// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/unit/catch.hpp"

#include "jakl/id.hpp"


TEST_CASE("JAKL ID", "[default]") {

	SECTION("Basic Pps") {

		jakl::ID a;
		a = 3;
		REQUIRE( a == 3 );

		jakl::ID b(a);
		REQUIRE( b == 3 );
	}

}



