/*
 * simple.cpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */




#include "jakl.hpp"


#include <vector>

int main() {

	using size_type  = std::size_t;
	using value_type = double;

	// Matrix size (N x N)
	const size_type N = 1000;
	const value_type xval = 1;
	const value_type yval = 2;

	// Define range of square matrix
	jakl::Range<2> range(N,N);

	// Get host memory of size required by range
	std::vector<value_type> x(range.size(), xval);
	std::vector<value_type> y(range.size(), yval);
	std::vector<value_type> a(range.size(), 9999);

//	// Wrap memory with mapping between devices
//	jakl::Buffer<double, 2> x_buf(x.data(), range); // holds pointer to the host memory
//	jakl::Buffer<double, 2> y_buf(y.data(), range); // will update y.data() when destroyed
//	jakl::Buffer<double, 2> a_buf(a.data(), range);

	// Get queue on the host which executes on offload device
	jakl::Device dev(jakl::cpu_selector_v);
	jakl::Context cont(dev);
	jakl::Queue q(cont);

	auto event = q.submit([&](jakl::Handler&& h) {

		// Get data on device we are running on
//		auto x_access = x_buf.get_access<jakl::access::mode::read>(h);
//		auto y_access = y_buf.get_access<jakl::access::mode::read>(h);
//		auto a_access = a_buf.get_access<jakl::access::mode::write>(h);
//
//		JAKL_COMPUTE_FUNCTION(void, f, (jakl::Index<2> indx), {
//				a_access[indx] = x_access[indx] * y_access[indx];
//		});
//
//		h.parallel_for(range, f);

	});

	// Get data back on host vector<> a
//	a_buf.flush();

	// Compare to solution
//	for(std::size_t i = 0; i < a.size(); ++i) {
//		if( a[i] != (xval*yval) ) {
//			std::cout << "ERROR" << std::endl;
//		}
//	}

	return 0;
}


