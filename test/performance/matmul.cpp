/*
 * stencil.cpp
 *
 *  Created on: Mar 10, 2020
 *      Author: bflynt
 */

#include "jakl.hpp"

#include "stop_watch.hpp"

#include <vector>

int main() {

	using size_type  = std::size_t;
	using value_type = double;
	xstd::StopWatch task_watch;
	xstd::StopWatch kernel_watch;

	// Matrix size (N x N)
	const size_type N = 500;
	const value_type aval = 1;
	const value_type bval = 2;

	// Define range of square matrix
	jakl::Range<2> range(N,N);

	// Get host memory of size required by range
	std::vector<value_type> a(range.size(), aval);
	std::vector<value_type> b(range.size(), bval);
	std::vector<value_type> c(range.size(), 9999);

	// Wrap memory with mapping between devices
	jakl::Buffer<double, 2> a_buf(a.data(), range); // holds pointer to the host memory
	jakl::Buffer<double, 2> b_buf(b.data(), range); // will update y.data() when destroyed
	jakl::Buffer<double, 2> c_buf(c.data(), range);

	// Get queue on the host which executes on offload device
	jakl::Device dev;
	jakl::Queue q(dev);

	auto task = q.submit([&](jakl::Handler&& h) {
		task_watch.start();

		// Get data on device we are running on
		auto a_access = a_buf.get_access<jakl::access::mode::read>(h);
		auto b_access = b_buf.get_access<jakl::access::mode::read>(h);
		auto c_access = c_buf.get_access<jakl::access::mode::write>(h);

		JAKL_COMPUTE_FUNCTION(void, func, (jakl::Index<2> indx), {
			auto j = indx[0];
			auto i = indx[1];
			c_access[indx] = 0;
			for(std::size_t k = 0; k < N; ++k) {
				c_access[indx] += a_access[indx(j,k)] * b_access[indx(k,i)];
			}
		});

		kernel_watch.start();
		h.parallel_for(range, func);
		kernel_watch.stop();
		task_watch.stop();
	});
	task.wait(); // wait for compute to finish

	// Get data back on host vector<> a
	c_buf.flush();

	// Compare to solution
	for(std::size_t i = 0; i < c.size(); ++i) {
		if( c[i] != (aval*bval*N) ) {
			std::cout << "ERROR" << std::endl;
		}
	}

	std::cout << "Timing (sec):" << std::endl;
	std::cout << "Kernel = " << kernel_watch.elapsed_seconds() << std::endl;
	std::cout << "Task   = " << task_watch.elapsed_seconds()   << std::endl;

	return 0;
}









