
# have MIPP intrinsics activated, which depends on on target architecture
option(USE_MIPP_INTRINSICS  "Use MIPP intrinsics?" ON)


# TARGET_C_ARCH / TARGET_CPP_ARCH:
# see https://en.wikichip.org/wiki/x86/extensions
# and https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html
#   for gcc specific architecture options
# and https://docs.microsoft.com/en-us/cpp/build/reference/arch-x64
# or  https://docs.microsoft.com/en-us/cpp/build/reference/arch-x86
#   for msvc specific architecture options

set(GCC_MARCH_DESC "native/SSE2:pentium4/SSE3:core2/SSE4:nehalem/AVX:sandybridge/AVX2:haswell/ARM-NEON:armv7-a")

set(GCC_MARCH_VALUES "native;pentium4;core2;nehalem;sandybridge;haswell;armv7-a" CACHE INTERNAL
  "List of possible SIMD architectures")

# cmake options - depending on C/C++ compiler
# how are chances, that C and C++ compilers are from different vendors?
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(TARGET_C_ARCH "native" CACHE STRING "gcc target C architecture (-march): ${GCC_MARCH_DESC}")
    set_property(CACHE TARGET_C_ARCH PROPERTY STRINGS ${GCC_MARCH_VALUES})
elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(TARGET_C_ARCH "native" CACHE STRING "clang target C architecture (-march): ${GCC_MARCH_DESC}")
    set_property(CACHE TARGET_C_ARCH PROPERTY STRINGS ${GCC_MARCH_VALUES})
elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(TARGET_C_ARCH "AVX" CACHE STRING "msvc target C architecture (/arch): SSE2/AVX/AVX2/AVX512")
else()
    message(WARNING "unsupported C compiler '${CMAKE_C_COMPILER_ID}', see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(TARGET_CXX_ARCH "native" CACHE STRING "gcc target C++ architecture (-march): ${GCC_MARCH_DESC}")
    set_property(CACHE TARGET_CXX_ARCH PROPERTY STRINGS ${GCC_MARCH_VALUES})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(TARGET_CXX_ARCH "native" CACHE STRING "clang target C++ architecture (-march): ${GCC_MARCH_DESC}")
    set_property(CACHE TARGET_CXX_ARCH PROPERTY STRINGS ${GCC_MARCH_VALUES})
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(TARGET_CXX_ARCH "AVX" CACHE STRING "msvc target C++ architecture (/arch): SSE2/AVX/AVX2/AVX512")
else()
    message(WARNING "unsupported C++ compiler '${CMAKE_CXX_COMPILER_ID}', see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
endif()

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

function(target_set_c_arch_flags target)
    if (TARGET_C_ARCH STREQUAL "")
        message(WARNING "C ARCH for target ${target} is not set!")
    else()
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE "-march=${TARGET_C_ARCH}")
            message(STATUS "C ARCH for target ${target} set: ${TARGET_C_ARCH}")
        elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${target} PRIVATE "-march=${TARGET_C_ARCH}")
            message(STATUS "C ARCH for target ${target} set: ${TARGET_C_ARCH}")
        elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
            target_compile_options(${target} PRIVATE "/arch:${TARGET_C_ARCH}")
            message(STATUS "C ARCH for target ${target} set: ${TARGET_C_ARCH}")
        else()
          message(WARNING "unsupported C compiler '${CMAKE_C_COMPILER_ID}' for target_set_c_arch_flags(), see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
        endif()
    endif()
endfunction()

function(target_set_cxx_arch_flags target)
    if (TARGET_CXX_ARCH STREQUAL "")
        message(WARNING "C++ ARCH for target ${target} is not set!")
    else()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE "-march=${TARGET_CXX_ARCH}")
            message(STATUS "C++ ARCH for target ${target} set: ${TARGET_CXX_ARCH}")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${target} PRIVATE "-march=${TARGET_CXX_ARCH}")
            message(STATUS "C++ ARCH for target ${target} set: ${TARGET_CXX_ARCH}")
        elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
            target_compile_options(${target} PRIVATE "/arch:${TARGET_CXX_ARCH}")
            message(STATUS "C++ ARCH for target ${target} set: ${TARGET_CXX_ARCH}")
        else()
            message(WARNING "unsupported C++ compiler '${CMAKE_CXX_COMPILER_ID}' for target_set_cxx_arch_flags(), see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
        endif()
    endif()
endfunction()

