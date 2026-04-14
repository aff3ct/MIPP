# TITLE?

`simd_ext/` is the directory where the implementation of MIPP for specific ISAs 
live. These are the current subdirectories of `simd_ext/`:

- `avx`: AVX, AVX2 and AVX2+FMA implementations of MIPP
- `avx512`: AVX-512F, AVX-512BW, AVX-512DQ, AVX-512DQ KNCI, implementations of 
  MIPP
- `neon`: NEON 32 bit and 64 bits implementations of MIPP
- `rvv`: RVV1.0 implementation of MIPP
- `sse`: SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2 implementations of MIPP
- `sve`: SVE implementation of MIPP

In each of these subdirectories, we find three files:

- implem_`[isa]`.py : defines MIPP functions where an intrinsic equivalent 
  exists in the ISA.
- implem_emu_`[isa]`.py : defines MIPP functions that need to be emulated in the 
  ISA.
- gen_mipp_`[isa]`.py : "glue" function that uses `c_generator.gen_c_functions` 
  (or a function similar to it) and `generic_emu.gen_c_generic_functions` to 
  generate the `include/isa/mipp_impl_isa_gen.h` header.

!!! info
    `[isa]` should be replaced by the extension name, like implem_avx.py for 
    avx, implem_rvv.py for RVV and so on.
