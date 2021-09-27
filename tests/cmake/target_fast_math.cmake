
# activation of TARGET_USE_FAST_MATH does break tests of MIPP!
option(TARGET_USE_FAST_MATH  "Build with fast math - non IEEE compliant - breaks MIPP tests!" OFF)

function(target_set_c_fast_math target)
    if (TARGET_USE_FAST_MATH)
        if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
          target_compile_options(${target} PRIVATE "/fp:fast")
        elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
          target_compile_options(${target} PRIVATE "-ffast-math")
        elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
          target_compile_options(${target} PRIVATE "-ffast-math")
        else()
          message(WARNING "unsupported C compiler '${CMAKE_C_COMPILER_ID}' for target_set_c_fast_math, see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
        endif()
    endif()
endfunction()


function(target_set_cxx_fast_math target)
    if (TARGET_USE_FAST_MATH)
        if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
          target_compile_options(${target} PRIVATE "/fp:fast")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
          target_compile_options(${target} PRIVATE "-ffast-math")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
          target_compile_options(${target} PRIVATE "-ffast-math")
        else()
          message(WARNING "unsupported C++ compiler '${CMAKE_CXX_COMPILER_ID}' for target_set_c_fast_math, see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html")
        endif()
    endif()
endfunction()

