/*
 * gpu.hpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */


#include "jakl/config/assert.hpp"
#include "jakl/core/system.hpp"


#include <cstdlib>

namespace jakl {
namespace system {

struct gpu {

	static void* allocate_memory(const std::size_t bytes, Device const& dev){
		int error_code(cudaSuccess);
		void* dev_ptr;

		error_code = cudaSetDevice(dev.id());
		if( error_code != cudaSuccess ) {
			JAKL_ASSERT(false);
		}

		error_code = cudaMalloc(&dev_ptr, bytes);
		if(error_code != cudaSuccess){
			JAKL_ASSERT(false);
		}
		return dev_ptr;
	}

	static void free_memory(void* device_ptr, Device const& dev){
		int error_code(cudaSuccess);

		error_code = cudaSetDevice(dev.id());
		if( error_code != cudaSuccess ) {
			JAKL_ASSERT(false);
		}

		error_code = cudaFree(device_ptr);
		if(error_code != cudaSuccess){
			JAKL_ASSERT(false);
		}
	}

	static void copy_memory(void* dst_ptr, const void* src_ptr, std::size_t bytes, Device const& dst, Device const& src) {
		int error_code(cudaSuccess);
		int direction(cudaMemcpyDefault);

		// Select Copy Direction
		if( src.is_host() ){
			if( dst.is_host() ){
				direction = cudaMemcpyHostToHost;
			}
			else {
				direction = cudaMemcpyHostToDevice;
			}
		}
		else {
			if( dst.is_host() ){
				direction = cudaMemcpyDeviceToHost;
			}
			else {
				direction = cudaMemcpyDeviceToDevice;
			}
		}

		// Perform Copy
		error_code = cudaMemcpy(dst_ptr,src_ptr,bytes,direction);
		if(error_code != cudaSuccess){
			JAKL_ASSERT(false);
		}
	}

};  // struct gpu


} // namespace system
} // namespace jakl


