/*
 * cuda_checkout.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */


#include <iostream>



int main() {

	// CUDA Always returns >0 for Device Count
	// It will emulate on the CPU the device if no device exists
	int count = -999;
	cudaGetDeviceCount(&count);
	std::cout << "cudaGetDeviceCount = " << count << std::endl;
	
	// CUDA Always returns a 0 for initial device
	// even when no device exists since it will emulate on the CPU the device
	int initial = 0;
	std::cout << " = " << initial << std::endl;
	
	int device = -999;
	cudaGetDevice(&device);
	std::cout << "cudaGetDevice = " << device << std::endl;
	
	

	return 0;
}





