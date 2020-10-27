/*
 * queue.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Queue", "[default]") {
	using namespace jakl;

	SECTION("Queue") {

		int a = +5;
		int b =  0;
		int c = -5;

		Queue q;
		auto a_to_b = q.submit([&](Handler&& handle){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			b = a;
		});

		// If depends_on() doesn't wait then b will not be set
		auto b_to_c = q.submit([&](Handler&& handle){
			handle.depends_on(a_to_b);
			c = b;
		});

		// If wait() doesn't wait then c will not be set
		b_to_c.wait();

		REQUIRE( c == a );
		REQUIRE( b == a );
		REQUIRE( a == a );
	}

}



