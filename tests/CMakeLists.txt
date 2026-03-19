cmake_minimum_required(VERSION 3.5)

project(MIPP_tests)

set (CMAKE_MACOSX_RPATH 1)

# Enable C++14
set (CMAKE_CXX_STANDARD 14)

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

file (GLOB_RECURSE MIPP_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_executable(tests_exe ${MIPP_SRCS_TEST} lib/Catch2/src/catch_amalgamated.cpp)
set_target_properties(tests_exe PROPERTIES OUTPUT_NAME run-tests POSITION_INDEPENDENT_CODE ON) # set -fpie

 # include MIPP headers
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# include Catch2 header
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/include/")

enable_testing()
add_test(NAME mipp::test COMMAND tests_exe)
