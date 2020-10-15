/*
 * macros.hpp
 *
 *  Created on: Mar 23, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_CONFIG_MACROS_HPP_
#define INCLUDE_JAKL_CONFIG_MACROS_HPP_


#define JAKL_COMPUTE_FUNCTION(return_type, func_name, arg_list, code)   \
	_Pragma("omp declare target")                                       \
	auto func_name = [=] arg_list -> return_type code;                  \
	_Pragma("omp end declare target")


#define JAKL_BEGIN_DEVICE_CODE _Pragma("omp declare target")
#define JAKL_END_DEVICE_CODE _Pragma("omp end declare target")

#endif /* INCLUDE_JAKL_CONFIG_MACROS_HPP_ */
