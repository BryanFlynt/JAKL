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

	SECTION("Default Device") {

		Device dev;

		REQUIRE( dev.id() == system::default_device() );
	}

	SECTION("Host Device") {

		Device dev(system::host_device());

		REQUIRE( dev.id() == system::host_device() );
	}

	SECTION("Random Device") {

		Device a(321);
		Device b(321);

		REQUIRE( a == b );
	}

}

