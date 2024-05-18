cmake_minimum_required(VERSION 3.5)
project(MIPP CXX)

option(MIPP_TESTS_EXE "Compile MIPP test suite" ON)
option(MIPP_EXAMPLES_EXE "Compile MIPP examples" ON)
option(MIPP_STATIC_LIB "Compile MIPP as static library (e.g. to include LUT)" OFF)
option(MIPP_NO_INTRINSICS "Disable SIMD instrinsic functions and use regular code instead" OFF)
option(MIPP_ENABLE_BACKTRACE "Print the backtrace when throwing an error" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify bin and lib paths
set(EXECUTABLE_OUTPUT_PATH bin/)
set(LIBRARY_OUTPUT_PATH lib/)

# Print CMake options values --------------------------------------------------
# -----------------------------------------------------------------------------
message(STATUS "MIPP options: ")
message(STATUS "  * MIPP_TESTS_EXE: '${MIPP_TESTS_EXE}'")
message(STATUS "  * MIPP_EXAMPLES_EXE: '${MIPP_EXAMPLES_EXE}'")
message(STATUS "  * MIPP_STATIC_LIB: '${MIPP_STATIC_LIB}'")
message(STATUS "  * MIPP_NO_INTRINSICS: '${MIPP_NO_INTRINSICS}'")
message(STATUS "  * MIPP_ENABLE_BACKTRACE: '${MIPP_ENABLE_BACKTRACE}'")

set(MIPP_HEADERS
  include/mipp.h
  include/mipp_impl_AVX512.hxx
  include/mipp_impl_AVX.hxx
  include/mipp_impl_NEON.hxx
  include/mipp_impl_SSE.hxx
  include/mipp_object.hxx
  include/mipp_scalar_op.h
  include/mipp_scalar_op.hxx
)

set(MIPP_MATH_HEADERS
  include/math/avx512_mathfun.h
  include/math/avx512_mathfun.hxx
  include/math/avx_mathfun.h
  include/math/avx_mathfun.hxx
  include/math/neon_mathfun.h
  include/math/neon_mathfun.hxx
  include/math/sse_mathfun.h
  include/math/sse_mathfun.hxx
)

if (MIPP_STATIC_LIB)
  set(MIPP_SRCS
      src/gen/compress_LUT_AVX.cpp
      src/gen/compress_LUT_SSE.cpp
      src/gen/compress_LUT_NEON.cpp
  )
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

# Install headers files
install(FILES ${MIPP_HEADERS}      DESTINATION include/mipp)
install(FILES ${MIPP_MATH_HEADERS} DESTINATION include/mipp/math)

# Create the library
if (MIPP_STATIC_LIB)
  add_library(mipp STATIC ${MIPP_SRCS}) # Compiled version
else()
  add_library(mipp INTERFACE) # Header-ony version
endif()
add_library(MIPP::mipp ALIAS mipp)

target_compile_definitions(mipp INTERFACE HAVE_MIPP=1)
target_compile_features(mipp INTERFACE cxx_std_11)
target_include_directories(mipp INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/mipp>)

if (MIPP_STATIC_LIB)
  target_compile_definitions(mipp INTERFACE MIPP_STATIC_LIB)
endif()
if (MIPP_NO_INTRINSICS)
  target_compile_definitions(mipp INTERFACE MIPP_NO_INTRINSICS)
endif()
if (MIPP_ENABLE_BACKTRACE)
  target_compile_definitions(mipp INTERFACE MIPP_ENABLE_BACKTRACE)
endif()

# Target export
install(EXPORT mippTargets
        NAMESPACE MIPP::
        DESTINATION lib/cmake/mipp)

# Install targets file
install(TARGETS mipp EXPORT mippTargets)

# Prepare the MIPPConfig.cmake file to be installed for users
include(CMakePackageConfigHelpers)
set(INC_INSTALL_DIR "include/mipp" CACHE STRING "where to install headers relative to prefix" )
configure_package_config_file(cmake/MIPPConfig.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/MIPPConfig.cmake
                              INSTALL_DESTINATION lib/cmake/mipp
                              PATH_VARS INC_INSTALL_DIR)

# Install MIPPConfig.cmake
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MIPPConfig.cmake
        DESTINATION lib/cmake/mipp)

# Create uninstall target
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    @ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

if (MIPP_TESTS_EXE)
    # Generate the source files list
    file (GLOB_RECURSE MIPP_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/*)
    add_executable(tests_exe ${MIPP_SRCS_TEST})
    set_target_properties(tests_exe PROPERTIES OUTPUT_NAME run-tests POSITION_INDEPENDENT_CODE ON) # set -fpie

    # include MIPP headers
    target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

    # include Catch2 header
    target_include_directories(tests_exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests/lib/Catch2/include/")

    # If MIPP was compiled as static library then link argainst it
    if (MIPP_STATIC_LIB)
        target_link_libraries(tests_exe PUBLIC mipp)
    endif()

    enable_testing()
    add_test(NAME mipp::test COMMAND tests_exe)
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

if (MIPP_EXAMPLES_EXE)
    add_executable(ex_conversion ${CMAKE_CURRENT_SOURCE_DIR}/examples/conversion.cpp)
    set_target_properties(ex_conversion PROPERTIES OUTPUT_NAME example-conversion POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_conversion PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_conversion PUBLIC mipp)
    endif()

    add_executable(ex_gemm ${CMAKE_CURRENT_SOURCE_DIR}/examples/gemm.cpp)
    set_target_properties(ex_gemm PROPERTIES OUTPUT_NAME example-gemm POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_gemm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_gemm PUBLIC mipp)
    endif()

    add_executable(ex_initreg ${CMAKE_CURRENT_SOURCE_DIR}/examples/initreg.cpp)
    set_target_properties(ex_initreg PROPERTIES OUTPUT_NAME example-initreg POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_initreg PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_initreg PUBLIC mipp)
    endif()

    add_executable(ex_mask ${CMAKE_CURRENT_SOURCE_DIR}/examples/mask.cpp)
    set_target_properties(ex_mask PROPERTIES OUTPUT_NAME example-mask POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_mask PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_mask PUBLIC mipp)
    endif()

    add_executable(ex_mathfun ${CMAKE_CURRENT_SOURCE_DIR}/examples/mathfun.cpp)
    set_target_properties(ex_mathfun PROPERTIES OUTPUT_NAME example-mathfun POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_mathfun PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_mathfun PUBLIC mipp)
    endif()

    add_executable(ex_operator ${CMAKE_CURRENT_SOURCE_DIR}/examples/operator.cpp)
    set_target_properties(ex_operator PROPERTIES OUTPUT_NAME example-operator POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_operator PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_operator PUBLIC mipp)
    endif()

    add_executable(ex_reduction ${CMAKE_CURRENT_SOURCE_DIR}/examples/reduction.cpp)
    set_target_properties(ex_reduction PROPERTIES OUTPUT_NAME example-reduction POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_reduction PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_reduction PUBLIC mipp)
    endif()

    add_executable(ex_sorting ${CMAKE_CURRENT_SOURCE_DIR}/examples/sorting.cpp)
    set_target_properties(ex_sorting PROPERTIES OUTPUT_NAME example-sorting POSITION_INDEPENDENT_CODE ON) # set -fpie
    target_include_directories(ex_sorting PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if (MIPP_STATIC_LIB)
        target_link_libraries(ex_sorting PUBLIC mipp)
    endif()
endif()
