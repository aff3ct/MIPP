cmake_minimum_required(VERSION 3.5)
project(MY_INTRINSICS_PLUS_PLUS CXX)

option(MIPP_TESTS_EXE "Compile MIPP test suite" ON)
option(MIPP_STATIC_LIB "Compile MIPP as static library (e.g. to include LUT)" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Print CMake options values --------------------------------------------------
# -----------------------------------------------------------------------------
message(STATUS "MIPP options: ")
message(STATUS "  * MIPP_TESTS_EXE: '${MIPP_TESTS_EXE}'")
message(STATUS "  * MIPP_STATIC_LIB: '${MIPP_STATIC_LIB}'")

set(MIPP_HEADERS
  src/mipp.h
  src/mipp_impl_AVX512.hxx
  src/mipp_impl_AVX.hxx
  src/mipp_impl_NEON.hxx
  src/mipp_impl_SSE.hxx
  src/mipp_object.hxx
  src/mipp_scalar_op.h
  src/mipp_scalar_op.hxx
)

set(MIPP_MATH_HEADERS
  src/math/avx512_mathfun.h
  src/math/avx512_mathfun.hxx
  src/math/avx_mathfun.h
  src/math/avx_mathfun.hxx
  src/math/neon_mathfun.h
  src/math/neon_mathfun.hxx
  src/math/sse_mathfun.h
  src/math/sse_mathfun.hxx
)

if (MIPP_STATIC_LIB)
  set(MIPP_SRCS
      src/mipp_SSE_LUT.cpp
      src/mipp_AVX_LUT.cpp
      src/mipp_NEON_LUT.cpp
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

target_compile_definitions(mipp INTERFACE HAVE_MIPP=1)
target_compile_features(mipp INTERFACE cxx_std_11)
target_include_directories(mipp INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:include/mipp>)

if (MIPP_STATIC_LIB)
  target_compile_definitions(mipp PUBLIC MIPP_STATIC_LIB)
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
    add_subdirectory(tests)
endif()
