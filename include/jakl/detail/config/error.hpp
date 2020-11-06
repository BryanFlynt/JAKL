/*
 * Filename:	error.hpp
 * Author:      bflynt
 * Created:		Jun 11, 2016
 * Copyright:   2016, Bryan Flynt, All rights reserved.
 */
#ifndef DEBUG_ERROR_H_
#define DEBUG_ERROR_H_


#include <iostream>  // std::err
#include <cstdlib>   // exit()

// ==============================================================================
//     Macros
// ==============================================================================

#define JAKL_ERROR(EXP)                                              \
	do {                                                             \
		std::cerr << std::endl;                                      \
		std::cerr << "********** ERROR ***********" << std::endl;    \
		std::cerr << "Mssg: " << EXP      << std::endl;              \
		std::cerr << "File: " << __FILE__ << std::endl;              \
		std::cerr << "Line: " << __LINE__ << std::endl;              \
		std::cerr << std::endl;                                      \
		exit(EXIT_FAILURE);                                          \
	} while (0)

#endif // DEBUG_ERROR_H_
