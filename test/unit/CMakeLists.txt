#
# === Unit Tests
#
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test)

# 
# Build list of all tests to create
#
set(jakl_unit_files  
		context.cpp
 		device.cpp
		id.cpp
		system.cpp
)

#
# Build list of compiler options for tests
#
set(compiler_options 
		"$<$<CXX_COMPILER_ID:AppleClang>:-Wno-comment>"
	)
		       
# Set include headers unique to testing
set(include_headers "")

# Set libraries the test need
# - Gets library include paths from here
set(linked_libraries 
		jakl
		"$<$<BOOL:${OpenMP_FOUND}>:OpenMP::OpenMP_CXX>"
	)
	
#
# With NVPTX offloading it appears the linker must have 
# the OpenMP compiler flag passed if any of the header or
# inline files have OpenMP code within them.  This is not 
# required for CPU only OpenMP code.  Perhaps a bug within 
# the GCC compiler ??? 
#
set(linked_options
		"$<$<BOOL:${OpenMP_FOUND}>:${OpenMP_CXX_FLAGS}>"
	)
	
# 
# MPI launch commands
# CTest does not like them to be all within one command
# 
if(${USE_MPI})
	set(LAUNCH_COMMAND "mpirun")  
	set(LAUNCH_ARGS    "-np")
	set(LAUNCH_PROCS   "4")
else()
	set(LAUNCH_COMMAND "")  
	set(LAUNCH_ARGS    "")
	set(LAUNCH_PROCS   "")
endif()


#
# Loop over each test building and adding to ctest
# - Build test name
#	             
FOREACH(test_src ${jakl_unit_files})
	string(REPLACE ".cpp" "" test_name ${test_src})
	add_executable(${test_name} ${test_src})
        set_property(TARGET ${test_name} PROPERTY CXX_EXTENSIONS OFF)
        set_property(TARGET ${test_name} PROPERTY CXX_STANDARD 17)
	target_compile_options(${test_name} 
		PRIVATE 
			${compiler_options})
	target_include_directories(${test_name} 
		PRIVATE
			${CATCH_INCLUDE_DIR}
			${include_headers})
			
	target_link_options(${test_name} PRIVATE ${linked_options})
			
	target_link_libraries(${test_name} ${linked_libraries})
	
	add_test(NAME ${test_name} 
		     COMMAND ${LAUNCH_COMMAND} ${LAUNCH_ARGS} ${LAUNCH_PROCS} $<TARGET_FILE:${test_name}>)
ENDFOREACH(test_src)

