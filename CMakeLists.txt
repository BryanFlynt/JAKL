# Check CMake Version 
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)

#
#---------------------------------------------------------------------
# Project Setup
#---------------------------------------------------------------------
#
project("JAKL" VERSION 0.0.0.1 LANGUAGES CXX)
#set(PROJECT_VERSION_MAJOR 0)
#set(PROJECT_VERSION_MINOR 0)
#set(PROJECT_VERSION_PATCH 0)
#set(PROJECT_VERSION_TWEAK 1)

#---------------------------------------------------------------------
# User Configure Build Process
#---------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_COLOR_MAKEFILE TRUE)
set(DEFAULT_BUILD_TYPE "Debug")

# Control message level of CMake
# Should be set on command line as follow by user
# --log-level=<ERROR|WARNING|NOTICE|STATUS|VERBOSE|DEBUG|TRACE>
# --loglevel=  Older versions of CMake
set(CMAKE_MESSAGE_LOG_LEVEL VERBOSE)

#---------------------------------------------------------------------
# Set location of *.cmake modules
#---------------------------------------------------------------------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#
#---------------------------------------------------------------------
# Force build in seperate directory
#---------------------------------------------------------------------
#
include(InSourceBuild)

#
#---------------------------------------------------------------------
# Directory Report
#---------------------------------------------------------------------
#
message(VERBOSE "")
message(VERBOSE "")
message(VERBOSE "--------------------- Directory Report -----------------------")
message(VERBOSE "") # CMAKE directories are from top level CMakeLists.txt
message(VERBOSE "Top Level Directories:")
message(VERBOSE "CMAKE_SOURCE_DIR  = ${CMAKE_SOURCE_DIR}")
message(VERBOSE "CMAKE_BINARY_DIR  = ${CMAKE_BINARY_DIR}")
message(VERBOSE "") # PROJECT directories are for recent project call
message(VERBOSE "Project Level Directories:")
message(VERBOSE "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(VERBOSE "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")


#---------------------------------------------------------------------
# Locations of Installation & Report
#---------------------------------------------------------------------

# Source locations in source tree
set(MY_PROJECT_PREFIX ${PROJECT_SOURCE_DIR})
set(MY_PROJECT_INCDIR ${MY_PROJECT_PREFIX}/include)
set(MY_PROJECT_SRCDIR ${MY_PROJECT_PREFIX}/src)
set(MY_PROJECT_TSTDIR ${MY_PROJECT_PREFIX}/test)

# Where to place all libraries
set(MY_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(MY_INSTALL_INCDIR ${MY_INSTALL_PREFIX}/include)
set(MY_INSTALL_SRCDIR ${MY_INSTALL_PREFIX}/src)
set(MY_INSTALL_LIBDIR ${MY_INSTALL_PREFIX}/lib)
set(MY_INSTALL_TSTDIR ${MY_INSTALL_PREFIX}/test)

message(VERBOSE " ")
message(VERBOSE "Using Directories:")
message(VERBOSE "--- Original Locations ---")
message(VERBOSE "MY_PROJECT_PREFIX = ${MY_PROJECT_PREFIX}")
message(VERBOSE "MY_PROJECT_INCDIR = ${MY_PROJECT_INCDIR}")
message(VERBOSE "MY_PROJECT_SRCDIR = ${MY_PROJECT_SRCDIR}")
message(VERBOSE "MY_PROJECT_TSTDIR = ${MY_PROJECT_TSTDIR}")
message(VERBOSE " ")
message(VERBOSE "--- Installation Locations ---")
message(VERBOSE "MY_INSTALL_PREFIX = ${MY_INSTALL_PREFIX}")
message(VERBOSE "MY_INSTALL_INCDIR = ${MY_INSTALL_INCDIR}")
message(VERBOSE "MY_INSTALL_SRCDIR = ${MY_INSTALL_SRCDIR}")
message(VERBOSE "MY_INSTALL_LIBDIR = ${MY_INSTALL_LIBDIR}")
message(VERBOSE "MY_INSTALL_TSTDIR = ${MY_INSTALL_TSTDIR}")

#---------------------------------------------------------------------
# Detect Configuration for Record
#---------------------------------------------------------------------
include(RecordVars)

#---------------------------------------------------------------------
# Detect Library includes, flags, etc.
#---------------------------------------------------------------------
message(VERBOSE "")
message(VERBOSE "================================================================")
message(VERBOSE "                    Searching for Libraries                     ")
message(VERBOSE "================================================================")
if(${CMAKE_VERSION} VERSION_GREATER "3.11.999") 
	cmake_policy(SET CMP0074 NEW) # find_package search <name>_ROOT
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(USE_OPENMP TRUE)
if(USE_OPENMP) 
	find_package(_OpenMP) 
endif()

#
#---------------------------------------------------------------------
# Compiler Feature Detection
#---------------------------------------------------------------------
# Hasn't proven to be very usefull. I find testing for the exact 
# feature of interest in the following section much better.
# Partialy because each compiler names features differently or 
# some not at all.
#
message(VERBOSE "")
message(VERBOSE "------------------ Compiler Feature Detection ---------------------")
message(VERBOSE "")
message(VERBOSE "CMAKE_CXX_COMPILER         = ${CMAKE_CXX_COMPILER}")
message(VERBOSE "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}")
message(VERBOSE "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

message(VERBOSE "")
message(VERBOSE "CMake Version Test can for the following C++ features:")
get_property(known_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
foreach(i ${known_features})
	message(VERBOSE "${i}")
endforeach()
	
message(VERBOSE "")
message(VERBOSE "C++ Compiler Supported Features:")
foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
	message(VERBOSE "${i}")
endforeach()

#---------------------------------------------------------------------
# Set Project Level Compiler Options
#---------------------------------------------------------------------
# ONLY those options which impact level of compiler errors
add_compile_options("-Werror")


#---------------------------------------------------------------------
# 
#---------------------------------------------------------------------

# Build Libraries & Applications
add_subdirectory(include)
#add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test/unit)
  add_subdirectory(test/scratch)
endif()



