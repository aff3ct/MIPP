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
file (GLOB_RECURSE MIPP_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_executable(tests_exe ${MIPP_SRCS_TEST})
set_target_properties(tests_exe PROPERTIES OUTPUT_NAME run-tests POSITION_INDEPENDENT_CODE ON) # set -fpie

 # include MIPP headers
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# include Catch2 header
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/include/")

enable_testing()
add_test(NAME mipp::test COMMAND tests_exe)
