function(target_activate_cxx_compiler_warnings target)
    target_compile_options(${target} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>)
    target_compile_options(${target} PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -pedantic>)
endfunction()
