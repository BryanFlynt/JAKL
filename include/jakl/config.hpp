/*
 * config.hpp
 *
 *  Created on: Oct 21, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CONFIG_HPP_
#define INCLUDE_JAKL_CONFIG_HPP_


// ========================================================
//                   CPU Execution Model
// ========================================================
//
// Use PTHREAD on CPU
//
#undef JAKL_USE_PTHREAD_CPU

//
// Use OpenMP on CPU
//
#define JAKL_USE_OPENMP_CPU


// ========================================================
//                      Device Model
// ========================================================

//
// Use OpenMP Off-Loading
//
#define JAKL_USE_OPENMP_DEVICE
//#undef JAKL_USE_OPENMP_DEVICE

//
// Use CUDA Off-Loading
//
#undef JAKL_USE_CUDA_DEVICE

//
// Use HIP Off-Loading
//
#undef JAKL_USE_HIP_DEVICE


// ========================================================
//            Include other Configuration Files
// ========================================================

#include "jakl/detail/config/assert.hpp"
#include "jakl/detail/config/error.hpp"



#endif /* INCLUDE_JAKL_CONFIG_HPP_ */
