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

# GCC 15 + SVE: miscompilation of the 'immediates' test (wrong results of 'slidedown_b128' on LMUL = 2 types, in C++20
# at -O2/-O3), worked around by disabling the scalar replacement of aggregates for this file only (disabling it for
# all the tests makes the static binary too big for the AArch64 branches); GCC 16 is not affected (but it ICEs on other
# SVE tests)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 15
   AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("#ifndef __ARM_FEATURE_SVE\n#error\n#endif\nint main() { return 0; }" MIPP_TESTS_SVE)
    if(MIPP_TESTS_SVE)
        set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/src/manual/immediates.cpp" PROPERTIES
            COMPILE_OPTIONS "-fno-tree-sra" SKIP_PRECOMPILE_HEADERS ON)
    endif()
endif()

enable_testing()
add_test(NAME mipp::test COMMAND tests_exe)
