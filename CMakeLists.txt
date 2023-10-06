cmake_minimum_required(VERSION 3.0)
project(MY_INTRINSICS_PLUS_PLUS CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( MIPP_HEADERS
  src/mipp.h
  src/mipp_impl_AVX512.hxx
  src/mipp_impl_AVX.hxx
  src/mipp_impl_NEON.hxx
  src/mipp_impl_SSE.hxx
  src/mipp_object.hxx
  src/mipp_scalar_op.h
  src/mipp_scalar_op.hxx
)

set( MIPP_MATH_HEADERS
  src/math/avx512_mathfun.h
  src/math/avx512_mathfun.hxx
  src/math/avx_mathfun.h
  src/math/avx_mathfun.hxx
  src/math/neon_mathfun.h
  src/math/neon_mathfun.hxx
  src/math/sse_mathfun.h
  src/math/sse_mathfun.hxx
)

######################################################

install( FILES ${MIPP_HEADERS}       DESTINATION include/mipp)
install( FILES ${MIPP_MATH_HEADERS}  DESTINATION include/mipp/math)


# Create uninstall target
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

######################################################

add_subdirectory(tests)
