#include <iostream>
#include <mipp.h>
#include <catch2/catch_session.hpp>

#if defined(__riscv_vector)
__attribute__((constructor))
static void force_enable_rvv() {
  // Touch vector state early. This should not depend on any memory.
  asm volatile ("vsetvli zero, zero, e8, m1, ta, ma" ::: "memory");
}
#endif

int main(int argc, char* argv[])
{
    mipp_info();
    std::cout << std::endl << "Run MIPP tests..." << std::endl;
    int result = Catch::Session().run(argc, argv);
    return result;
}
