/*
 * buffer.cpp
 *
 *  Created on: Mar 18, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"

#include <vector>


// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "../../test/catch.hpp"


TEST_CASE("JAKL Buffer Host", "[host_device]") {

	using namespace jakl;

	const std::size_t M = 10;
	std::vector<double> a(M, 1);
	std::vector<double> b(M, 2);
	std::vector<double> c(M, 0);

	SECTION("num_device") {

	{ // Scope Brackets
		Buffer<double, 1> a_buffer(a.data(), Range<1>(a.size()));
	    Buffer<double, 1> b_buffer(b.data(), Range<1>(b.size()));
	    Buffer<double, 1> c_buffer(c.data(), Range<1>(c.size()));

	    ID dev = system::host_device();
	    double* a_data = a_buffer.get_access<access::mode::read>(dev);
	    double* b_data = b_buffer.get_access<access::mode::read>(dev);
	    double* c_data = c_buffer.get_access<access::mode::write>(dev);

	    for(std::size_t i = 0; i < M; ++i){
	    	c_data[i] = a_data[i] + b_data[i];
	    }

	    auto c_host = c_buffer.get_access<access::mode::read>();
	    for(std::size_t i = 0; i < M; ++i){
	    	REQUIRE( a_data[i] == 1 );
	    	REQUIRE( b_data[i] == 2 );
	    	REQUIRE( c_host[i] == (a_data[i] + b_data[i]) );
	    	REQUIRE( c[i]      == 0 );
	    }

	} // END Scope Brackets

	// After Buffer destructor we should have data back
    for(std::size_t i = 0; i < M; ++i){
    	REQUIRE( c[i] == 3 );
    }

	} // end SECTION("num_device")
}

TEST_CASE("JAKL Buffer Device", "[default_device]") {

	using namespace jakl;

	const std::size_t M = 10;
	std::vector<double> a(M, 1);
	std::vector<double> b(M, 2);
	std::vector<double> c(M, 0);

	SECTION("num_device") {

	{ // Scope Brackets
		Buffer<double, 1> a_buffer(a.data(), Range<1>(a.size()));
	    Buffer<double, 1> b_buffer(b.data(), Range<1>(b.size()));
	    Buffer<double, 1> c_buffer(c.data(), Range<1>(c.size()));

	    ID dev = system::default_device();
	    double* a_data = a_buffer.get_access<access::mode::read>(dev);
	    double* b_data = b_buffer.get_access<access::mode::read>(dev);
	    double* c_data = c_buffer.get_access<access::mode::write>(dev);

		#pragma omp target map(a_data,b_data,c_data)
		#pragma teams parallel for device(dev)
	    for(std::size_t i = 0; i < M; ++i){
	    	c_data[i] = a_data[i] + b_data[i];
	    }

	    auto c_host = c_buffer.get_access<access::mode::read>();
	    for(std::size_t i = 0; i < M; ++i){
	    	REQUIRE( c_host[i] == (a[i] + b[i]) );
	    	REQUIRE( c[i]      == 0 );
	    }

	} // END Scope Brackets

	// After Buffer destructor we should have data back
    for(std::size_t i = 0; i < M; ++i){
    	REQUIRE( c[i] == 3 );
    }

	} // end SECTION("num_device")
}

