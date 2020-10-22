#
# Tests Directories
#

#
# Function to add a test scratch files
#
function(add_scratch_test test_name)
	set(test_target test_${test_name})  # Target becomes test_xxxx
	set(test_source ${test_name}.cpp)   # Source becomes xxxx.cpp
	add_executable(${test_target} ${test_source})
	target_include_directories(${test_target} 
		PRIVATE 
			${CATCH_INCLUDE_DIR}
			$<BUILD_INTERFACE:${MY_PROJECT_INCDIR}> # Pick up uninstalled library
    		$<BUILD_INTERFACE:${MY_INSTALL_INCDIR}> # Pick up processed configure.hpp
    )
   	target_link_libraries(${test_target}
		PRIVATE
	)
	set_target_properties(${test_target}
		PROPERTIES
    		CXX_STANDARD 17
    		CXX_STANDARD_REQUIRED YES
    		CXX_EXTENSIONS NO
	)
	target_compile_options(${test_target}
		PRIVATE
	)
	add_test(${test_name} ${test_target})
endfunction()


add_scratch_test(simple)

