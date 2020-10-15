# JAKL - Just Another Kernel Launcher
Just Another Kernel Launcher (JAKL) is a C++ library which implements an asynchronous kernel launcher with elements drawn from [DPC++](https://software.intel.com/en-us/oneapi/dpc-compiler), [SYCL](https://www.khronos.org/sycl/) and [Boost.Compute](https://www.boost.org/doc/libs/1_74_0/libs/compute/doc/html/index.html).  JAKL requires a C++17 standards compliant compiler and OpenMP 4.5 support for multi-core CPU or off-loading to a GPU device.  

## Requirments
JAKL is a stand alone library requiring only a C++ compiler supporting the C++17 standard.  To exploit shared memory parallel processing on the CPU the compiler additionaly needs to support OpenMP 4.5 directives.  If the user wishes to off-load computations to a device (GPU, etc.) then the compiler needs to support OpenMP 4.5 target based directives for that device. 

## Simple Example 
### Matrix Multiplication
```c++

#include "jakl.hpp"
#include <vector>

int main() {

	using size_type  = std::size_t;
	using value_type = double;

	// Matrix size (N x N) 
	const size_type N = 1000;

	// Define range of square (N x N) matrix
	jakl::Range<2> range(N,N);

	// Get host memory of size required by range
	std::vector<value_type> a(range.size(), 1);
	std::vector<value_type> b(range.size(), 2);
	std::vector<value_type> c(range.size(), 0);

	// Wrap memory with mapping between devices
	jakl::Buffer<double, 2> a_buf(a.data(), range);
	jakl::Buffer<double, 2> b_buf(b.data(), range);
	jakl::Buffer<double, 2> c_buf(c.data(), range);

	// Create queue on the host which executes on default device
	jakl::Device dev;   // Get devault device
	jakl::Queue q(dev); // Asynchronous gueue

	// Submit matrix multiplication (A * B = C) to the queue to be performed
	auto task = q.submit([&](jakl::Handler&& h) {

		// Get data on device we are running on
		auto a_access = a_buf.get_access<jakl::access::mode::read>(h);
		auto b_access = b_buf.get_access<jakl::access::mode::read>(h);
		auto c_access = c_buf.get_access<jakl::access::mode::write>(h);

		// Kernel to be run in parallel on device
		h.parallel_for(range, [=](jakl::Index<2> indx) {
			auto j = indx[0];
			auto i = indx[1];
			c_access[indx] = 0;
			for(size_type k = 0; k < N; ++k) {
				c_access[indx] += a_access[indx(j,k)] * b_access[indx(k,i)];
			}
		});
	});
	task.wait() // Wait for execution to complete before access data 
	
	// Flush the data from the device back to host vector<> c
	c_buf.flush();

	return 0;
}
```

