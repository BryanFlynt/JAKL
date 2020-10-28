/*
 * omp_checkout.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: bflynt
 */

#include <iostream>

#include "omp.h"

int main() {

	std::cout << "omp_get_num_devices()     = " << omp_get_num_devices()     << std::endl;
	std::cout << "omp_get_initial_device()  = " << omp_get_initial_device()  << std::endl;
	std::cout << "omp_get_default_device()  = " << omp_get_default_device()  << std::endl;

	std::cout << "omp_get_thread_limit()    = " << omp_get_thread_limit()     << std::endl;
	std::cout << "omp_get_team_size()       = " << omp_get_team_size(0)       << std::endl;
	std::cout << "omp_get_num_places()      = " << omp_get_num_places()       << std::endl;
	std::cout << "omp_get_place_num_procs() = " << omp_get_place_num_procs(0) << std::endl;
	std::cout << "omp_get_num_procs()       = " << omp_get_num_procs()        << std::endl;
	std::cout << "omp_get_max_threads()     = " << omp_get_max_threads()      << std::endl;

	return 0;
}


