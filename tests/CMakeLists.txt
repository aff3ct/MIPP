cmake_minimum_required(VERSION 3.5)

project(MIPP_tests CXX)

set (CMAKE_MACOSX_RPATH 1)

# Enable C++20 (for std::bit_cast)
set (CMAKE_CXX_STANDARD 20)

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

file (GLOB_RECURSE MIPP_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_executable(tests_exe ${MIPP_SRCS_TEST})
set_target_properties(tests_exe PROPERTIES OUTPUT_NAME run-tests POSITION_INDEPENDENT_CODE ON) # set -fpie

 # include MIPP headers
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# link with Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(tests_exe PRIVATE Catch2::Catch2)

enable_testing()
add_test(NAME mipp::test COMMAND tests_exe)
