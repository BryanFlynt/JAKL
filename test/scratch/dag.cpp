/*
 * dag.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: bflynt
 */


#include "jakl.hpp"

#include <vector>

int main() {

	using size_type  = std::size_t;
	using value_type = double;

	// Matrix size (N x N)
	const size_type N = 10;
	const value_type xval = 1;
	const value_type yval = 2;

	// Define range of square matrix
	jakl::Range<2> range(N,N);

	// Get host memory of size required by range
	std::vector<value_type> x(range.size(), xval);
	std::vector<value_type> y(range.size(), yval);
	std::vector<value_type> a(range.size(), 9999);

	// Wrap memory with mapping between devices
	jakl::Buffer<double, 2> x_buf(x.data(), range); // holds pointer to the host memory
	jakl::Buffer<double, 2> y_buf(y.data(), range); // will update y.data() when destroyed
	jakl::Buffer<double, 2> a_buf(a.data(), range);

	// Get queue on the host which executes on offload device
	jakl::Device dev;
	jakl::Queue q(dev);

	// Perform  element wise (X + Y  = A)
	auto e1 = q.submit([&](jakl::Handler&& h) {

		// Get data on device we are running on
		auto x_access = x_buf.get_access<jakl::access::mode::read>(h);
		auto y_access = y_buf.get_access<jakl::access::mode::read>(h);
		auto a_access = a_buf.get_access<jakl::access::mode::write>(h);

		JAKL_COMPUTE_FUNCTION(void, f, (jakl::Index<2> indx), {
				a_access[indx] = x_access[indx] + y_access[indx];
		});

		h.parallel_for(range, f);
	});
	//e1.wait(); // Removing the waits causes a data race

	// Perform element wise (A *= 2)
	auto e2 = q.submit([&](jakl::Handler&& h) {

		// Get data on device we are running on
		auto a_access = a_buf.get_access<jakl::access::mode::read_write>(h);

		JAKL_COMPUTE_FUNCTION(void, f, (jakl::Index<2> indx), {
				a_access[indx] *= 2;
		});

		h.parallel_for(range, f);
	});
	//e2.wait(); // Removing the waits causes a data race

	// Get data back on host vector<> without flush & Compare to solution
	auto a_on_host = a_buf.get_access<jakl::access::mode::read>();
	for(std::size_t i = 0; i < a.size(); ++i) {
		if( a_on_host[i] != 2*(xval+yval) ) {
			std::cout << "ERROR" << std::endl;
		}
	}

	// Flush data back on host vector<> & Compare to solution
	a_buf.flush();
	for(std::size_t i = 0; i < a.size(); ++i) {
		if( a[i] != 2*(xval+yval) ) {
			std::cout << "ERROR" << std::endl;
		}
	}

	return 0;
}


