/*
 * omp_checkout.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#include <iostream>

#include "omp.h"

int main() {

	std::cout << "omp_get_num_devices()    = " << omp_get_num_devices()    << std::endl;
	std::cout << "omp_get_initial_device() = " << omp_get_initial_device() << std::endl;
	std::cout << "omp_get_default_device() = " << omp_get_default_device() << std::endl;

	return 0;
}


