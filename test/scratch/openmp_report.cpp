/*
 * openmp_report.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: bflynt
 */


#include <cstdint>
#include <iostream>


#include "omp.h"



int main() {

	const std::size_t N = 1000;
	const std::size_t M = 1000;

	std::cout << "--- Host Values: " << std::endl;
	std::cout << "omp_get_num_procs()      = " << omp_get_num_procs()   << std::endl;
	std::cout << "omp_get_num_teams()      = " << omp_get_num_teams()   << std::endl;
	std::cout << "omp_get_max_threads()    = " << omp_get_max_threads() << std::endl;
	std::cout << std::endl;
	std::cout << "--- Device Values: " << std::endl;
	std::cout << "omp_is_initial_device()  = " << omp_is_initial_device()  << std::endl;
	std::cout << "omp_get_initial_device() = " << omp_get_initial_device() << std::endl;
	std::cout << "omp_get_default_device() = " << omp_get_default_device() << std::endl;
	std::cout << "omp_get_num_devices()    = " << omp_get_num_devices()    << std::endl;

	int T[5] = {-1};
#pragma omp target
	{
		T[0] = omp_is_initial_device();
		T[1] = omp_get_num_procs();
		//T[2] = omp_get_num_teams();
		//T[3] = omp_get_max_threads();

#pragma omp teams num_teams(65000)
		{
			if (omp_get_team_num() == 0){
				T[2] = omp_get_num_teams();
				T[3] = omp_get_max_threads();
			}
		}
	}

	std::cout << std::endl;
	std::cout << "--- Target Region: " << std::endl;
	std::cout << "omp_is_initial_device() = " << T[0] << std::endl;
	std::cout << "omp_get_num_procs()     = " << T[1] << std::endl;
	std::cout << "omp_get_num_teams()     = " << T[2] << std::endl;
	std::cout << "omp_get_max_threads()   = " << T[3] << std::endl;
	std::cout << std::endl;
	std::cout << "--- DONE" << std::endl;

	return 0;
}



