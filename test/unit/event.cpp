/*
 * queue.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"

#include <future>
#include <thread>


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Event", "[default]") {
	using namespace jakl;

	SECTION("Event from Promise") {

		// SetUp Event and wait for execution
		std::promise<void> prom;
		Event ev( prom.get_future() );
		std::thread( [&prom]{ prom.set_value_at_thread_exit(); }).detach();
		ev.wait();

		REQUIRE( true );
	}

	SECTION("Event from Async") {

		auto func = [](){
			int a(5);
			int b(4);
			int c(0);
			c = a + b;
		};

		// SetUp Event and wait for execution
		Event ev( std::async(std::launch::async, func) );
		ev.wait();

		REQUIRE( true );
	}

}



