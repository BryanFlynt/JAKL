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

	SECTION("Operators") {

		jakl::Device a;
		jakl::Device b;
		REQUIRE( a == b );

		jakl::ID id = 3;
		jakl::Device c(id);
		jakl::Device d(id);
		REQUIRE( c == d );

		jakl::Device e(id+1);
		REQUIRE(not (c == e) );
		REQUIRE(not (d == e) );
	}

}






