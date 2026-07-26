cmake_minimum_required(VERSION 3.5)

project(MIPP_tests CXX)

set (CMAKE_MACOSX_RPATH 1)

# Enable C++20 (for std::bit_cast)
set (CMAKE_CXX_STANDARD 20)

# CMake options for tests build configuration
option(MIPP_PRECOMPILED_HEADERS "Enable Precompiled Headers (PCH) for tests" ON)

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

file (GLOB_RECURSE MIPP_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_executable(tests_exe ${MIPP_SRCS_TEST})
set_target_properties(tests_exe PROPERTIES OUTPUT_NAME run-tests POSITION_INDEPENDENT_CODE ON) # set -fpie

 # include MIPP headers and test helpers
target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/" "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# link with Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(tests_exe PRIVATE Catch2::Catch2)

# Precompiled Headers (PCH) to accelerate compilation
if(MIPP_PRECOMPILED_HEADERS AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.16)
    target_precompile_headers(tests_exe PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/mipp.h"
    )
endif()

enable_testing()
add_test(NAME mipp::test COMMAND tests_exe)
