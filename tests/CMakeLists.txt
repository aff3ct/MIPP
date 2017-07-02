cmake_minimum_required(VERSION 2.6)

project(MIPP_tests)

set (CMAKE_MACOSX_RPATH 1)

# Enable C++11
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set (CMAKE_CXX_STANDARD 14)
else ()
    set (CMAKE_CXX_STANDARD 11)
endif()

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

#if(COMMAND cmake_policy)
#    cmake_policy(SET CMP0003 NEW)
#endif(COMMAND cmake_policy)

# include MIPP headers
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../src/")

# Generate the source files list
file (GLOB_RECURSE source_files src/*)
add_executable(run_tests ${source_files})
#add_test(tests run_tests)

# Link with CPP Unit
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(CPPUNIT REQUIRED)

if (CPPUNIT_FOUND)
    include_directories (${CPPUNIT_INCLUDE_DIR})
    target_link_libraries (run_tests "${CPPUNIT_LIBRARIES}")
endif (CPPUNIT_FOUND)