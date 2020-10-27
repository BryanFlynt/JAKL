/*
 * index.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Index", "[default]") {
	using namespace jakl;

	SECTION("Index<1>") {

		Range<1> dims(10);

		Index<1> a(0, dims.data());
		REQUIRE( a    == 0 );
		REQUIRE( a[0] == 0 );
		REQUIRE( a(0) == 0 );

		Index<1> b(5, dims.data());
		REQUIRE( b    == 5 );
		REQUIRE( b[0] == 5 );
		REQUIRE( b(5) == 5 );

		Index<1> c(9, dims.data());
		REQUIRE( c    == 9 );
		REQUIRE( c[0] == 9 );
		REQUIRE( c(9) == 9 );
	}

	SECTION("Index<2>") {

		Range<2> dims(10, 2);

		Index<2> a(0, dims.data());
		REQUIRE( a    == 0 );
		REQUIRE( a[0] == 0 );
		REQUIRE( a[1] == 0 );
		REQUIRE( a(0,0) == 0 );

		Index<2> b(5, dims.data());
		REQUIRE( b    == 5 );
		REQUIRE( b[0] == 2 );
		REQUIRE( b[1] == 1 );
		REQUIRE( b(2,1) == 5 );

		Index<2> c(19, dims.data());
		REQUIRE( c    == 19 );
		REQUIRE( c[0] ==  9 );
		REQUIRE( c[1] ==  1 );
		REQUIRE( c(9,1) == 19 );
	}

	SECTION("Index<3>") {

		Range<3> dims(10, 2, 2);

		Index<3> a(0, dims.data());
		REQUIRE( a    == 0 );
		REQUIRE( a[0] == 0 );
		REQUIRE( a[1] == 0 );
		REQUIRE( a[2] == 0 );
		REQUIRE( a(0,0,0) == 0 );

		Index<3> b(15, dims.data());
		REQUIRE( b    == 15 );
		REQUIRE( b[0] ==  3 );
		REQUIRE( b[1] ==  1 );
		REQUIRE( b[2] ==  1 );
		REQUIRE( b(3,1,1) == 15 );

		Index<3> c(39, dims.data());
		REQUIRE( c    == 39 );
		REQUIRE( c[0] ==  9 );
		REQUIRE( c[1] ==  1 );
		REQUIRE( c[2] ==  1 );
		REQUIRE( c(9,1,1) == 39 );
	}

}



