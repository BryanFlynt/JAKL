/*
 * config.hpp
 *
 *  Created on: Mar 3, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CONFIG_CONFIG_HPP_
#define INCLUDE_JAKL_CONFIG_CONFIG_HPP_

// ========================================================
//                   CPU Execution Model
// ========================================================
//
// Use PTHREAD on CPU
//
#undef JAKL_USE_PTHREAD_HOST

//
// Use OpenMP on CPU
//
#define JAKL_USE_OPENMP_HOST


// ========================================================
//                  Device Offload Model
// ========================================================

//
// Use OpenMP Off-Loading
//
#define JAKL_USE_OPENMP_DEVICE

//
// Use CUDA Off-Loading
//
#undef JAKL_USE_CUDA_DEVICE

//
// Use HIP Off-Loading
//
#undef JAKL_USE_HIP_DEVICE



#endif /* INCLUDE_JAKL_CONFIG_CONFIG_HPP_ */
