cmake_minimum_required(VERSION 2.8.9)
project(Interval Algebra)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Show verbose command while compiling
#set(CMAKE_VERBOSE_MAKEFILE ON)

# The project version number.
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

find_package(Boost COMPONENTS regex system filesystem program_options unit_test_framework graph REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# TEST
enable_testing()

function(add_boost_test SOURCE_FILE_NAME DEPENDENCY_LIB)
	get_filename_component(FILENAME ${SOURCE_FILE_NAME} NAME_WE)
	string(REGEX REPLACE "${CMAKE_SOURCE_DIR}/unit_test/" "" TEST_EXECUTABLE_NAME ${SOURCE_FILE_NAME})
	string(REGEX REPLACE ".cpp" "" TEST_EXECUTABLE_NAME ${TEST_EXECUTABLE_NAME})
	string(REGEX REPLACE "/+" "_" TEST_EXECUTABLE_NAME ${TEST_EXECUTABLE_NAME})
	
	add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILE_NAME})
	target_link_libraries(${TEST_EXECUTABLE_NAME} ${DEPENDENCY_LIB} ${Boost_LIBRARIES} )
	set_target_properties(${TEST_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit_test")
	
	
	file(READ "${SOURCE_FILE_NAME}" SOURCE_FILE_CONTENTS)
	string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)" FOUND_TESTS ${SOURCE_FILE_CONTENTS})
	foreach(HIT ${FOUND_TESTS})
		string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+) *\\).*" "\\1" TEST_NAME ${HIT})
		add_test(NAME ${TEST_EXECUTABLE_NAME}.${TEST_NAME} 
							COMMAND "${CMAKE_BINARY_DIR}/unit_test/${TEST_EXECUTABLE_NAME}"
							--run_test=${TEST_NAME} --catch_system_error=yes)
	endforeach()
endfunction()

file(GLOB SOURCES_UNIT_TEST "unit_test/*.cpp" "unit_test/*/*.cpp")
foreach(F ${SOURCES_UNIT_TEST})
	add_boost_test(${F} "")
endforeach()

# DOCs
# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()
	
	set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
	
	configure_file(${doxyfile_in} ${doxyfile} @ONLY)
	
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM)
	
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()
