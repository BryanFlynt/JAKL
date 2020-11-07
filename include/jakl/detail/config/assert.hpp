/*
 * Filename:	assert.hpp
 * Author:      bflynt
 * Created:		Jun 11, 2016
 * Copyright:   2016, Bryan Flynt, All rights reserved.
 */
#ifndef DEBUG_ASSERT_H_
#define DEBUG_ASSERT_H_


/**
 * Request traceback when assert is triggered
 */
#define JAKL_REQUEST_TRACEBACK

/**
 * Request static assertions
 */
#define JAKL_REQUEST_STATIC_ASSERTIONS

/**
 * Request runtime assertions
 */
#define JAKL_REQUEST_RUNTIME_ASSERTIONS

// ==============================================================================
//     Macros
// ==============================================================================

//
// Manual Traceback
//
#ifdef JAKL_REQUEST_TRACEBACK
	#include <iostream>   // std::err
	#include <execinfo.h> // backtrace
    #define JAKL_MANUAL_TRACEBACK										\
		do {															\
			void* callstack[128];                             			\
			int frames = backtrace(callstack, 128);           			\
			char** strs = backtrace_symbols(callstack,frames); 			\
			std::cerr << "********* TraceBack ********" << std::endl;  	\
			for (int i=0; i<frames; ++i) {                  			\
				std::cerr << strs[i] << std::endl;            			\
			}                                                			\
			free(strs);                                      			\
		} while (0)
#else
	#define JAKL_MANUAL_TRACEBACK
#endif

//
// Static Asserts
//
#ifdef JAKL_REQUEST_STATIC_ASSERTIONS
	#define JAKL_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#else
	#define JAKL_STATIC_ASSERT(...)
#endif

//
// RunTime Asserts
//
#ifdef JAKL_REQUEST_RUNTIME_ASSERTIONS
	#include <iostream>  // std::err
	#include <cstdlib>   // exit()
	#define JAKL_ASSERT(EXP)                                                 \
		do {                                                                 \
			if (!(EXP)) {                                                    \
				std::cerr << std::endl;                                      \
				std::cerr << "***** Failed assertion *****" << std::endl;    \
				std::cerr << "Failed expression: " << # EXP << std::endl;    \
				std::cerr << "File: " << __FILE__ << std::endl;              \
				std::cerr << "Line: " << __LINE__ << std::endl;              \
				std::cerr << std::endl;                                      \
				JAKL_MANUAL_TRACEBACK;										 \
				exit(EXIT_FAILURE);                                          \
			}                                                                \
		} while (0)
#else
	#define JAKL_ASSERT(EXP)
#endif





#endif /* DEBUG_ASSERT_H_ */
