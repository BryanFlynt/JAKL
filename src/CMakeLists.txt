######################################################
#   Build tbox Library
######################################################
#
# Name of library to build
#
add_library(jakl STATIC "")

#
# Source files to compile into library
#
target_sources(jakl
	PRIVATE
		core/system.cpp
)

#
# Compiler standard required
# Turn off standard extensions
# List required features
#
option(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET jakl PROPERTY CXX_EXTENSIONS OFF)
target_compile_features(jakl
	PUBLIC
                cxx_std_17
		cxx_constexpr
		cxx_static_assert
)

#
# Compile line options
# 
target_compile_options(jakl 
	PRIVATE
		"$<$<CXX_COMPILER_ID:AppleClang>:-Wno-comment>"
)

#
# Include directories for building library
# Note: 
# - The configure.hpp file is within ${MY_INSTALL_SRCDIR}
#   until it gets installed to ${MY_INSTALL_INCDIR} at the end.
#
target_include_directories(jakl
	PUBLIC  
		"$<INSTALL_INTERFACE:${MY_INSTALL_INCDIR}>"
		"$<BUILD_INTERFACE:${MY_PROJECT_INCDIR}>"
		"$<BUILD_INTERFACE:${MY_INSTALL_SRCDIR}>"
)


#
# Links required by library
# 
target_link_libraries(jakl 
	PUBLIC
		"$<$<BOOL:${OpenMP_FOUND}>:OpenMP::OpenMP_CXX>"
)

#
# Install public headers
#
#install(
#	DIRECTORY "${MY_PROJECT_INCDIR}/jakl"
#	DESTINATION "${MY_INSTALL_INCDIR}"  
#	FILES_MATCHING
#		PATTERN "*.hpp"
#)

#
# Install Library
#
install(TARGETS jakl
		LIBRARY DESTINATION "${MY_INSTALL_LIBDIR}"
		ARCHIVE DESTINATION "${MY_INSTALL_LIBDIR}")
		
		
		
		
		
