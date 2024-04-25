cmake_minimum_required(VERSION 3.5)

project(MIPP_tests CXX)

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

include(cmake/target_optimizations.cmake)
include(cmake/target_fast_math.cmake)
include(cmake/compiler_warnings.cmake)

# have MIPP intrinsics activated, which depends on on target architecture
option(USE_MIPP_INTRINSICS  "Use MIPP intrinsics?" ON)

######################################################

function(target_set_mipp_intrinsics target)
    if (USE_MIPP_INTRINSICS)
        message(STATUS "MIPP intrinsics for target ${target} are enabled")
    else()
        message(STATUS "MIPP intrinsics for target ${target} are disabled with definition MIPP_NO_INTRINSICS")
        target_compile_definitions(${target} PRIVATE MIPP_NO_INTRINSICS)
    endif()
endfunction()

######################################################

# include MIPP headers
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../src/")

# include Catch2 header
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/include/")

# Generate the source files list
file (GLOB_RECURSE source_files src/*)
add_executable(run_tests ${source_files})
target_set_cxx_arch_flags(run_tests)
target_set_mipp_intrinsics(run_tests)  # allow deactivation of mipp
# target_set_cxx_fast_math(run_tests)  # produces errors in tests
# target_activate_cxx_compiler_warnings(run_tests)  # too many warning

set_target_properties(run_tests PROPERTIES POSITION_INDEPENDENT_CODE ON) # set -fpie

# If MIPP was compiled as static library then link argainst it
if (MIPP_STATIC_LIB)
    target_link_libraries(run_tests PUBLIC mipp)
endif()

# no need to compile test program for install
# set_target_properties(run_tests PROPERTIES EXCLUDE_FROM_ALL TRUE)

######################################################

add_custom_target(test
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/bin/run_tests"
  DEPENDS run_tests
)

