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

# include Catch2 header
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/include/")

# Generate the source files list
file (GLOB_RECURSE source_files src/*)
add_executable(run_tests ${source_files})

set_target_properties(run_tests PROPERTIES POSITION_INDEPENDENT_CODE ON) # set -fpie
