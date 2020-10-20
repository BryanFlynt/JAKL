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

		jakl::ID id = 3;
		jakl::Device b(id);
		REQUIRE( b.is_host() == false );
		REQUIRE( b.is_gpu()  == true  );
		REQUIRE( b.id()      == id    );
	}

}






