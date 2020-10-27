/*
 * range.cpp
 *
 *  Created on: Mar 18, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Range", "[default]") {
	using namespace jakl;

	SECTION("Range<1>") {

		const std::size_t N = 10;
		Range<1> range(N);

		REQUIRE( range.size() == N );
		REQUIRE( range[0]     == N );
	}

	SECTION("Range<2>") {

		const std::size_t N = 10;
		const std::size_t M = 20;
		Range<2> range(N,M);

		REQUIRE( range.size() == N*M );
		REQUIRE( range[0]     == N );
		REQUIRE( range[1]     == M );
	}

	SECTION("Range<3>") {

		const std::size_t N = 10;
		const std::size_t M = 20;
		const std::size_t O = 30;
		Range<3> range(N,M,O);

		REQUIRE( range.size() == N*M*O );
		REQUIRE( range[0]     == N );
		REQUIRE( range[1]     == M );
		REQUIRE( range[2]     == O );
	}
}


