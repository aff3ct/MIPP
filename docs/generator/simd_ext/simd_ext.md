`simd_ext/` is the directory where the implementation of MIPP for specific ISAs live. 
These are the current subdirectories of `simd_ext/` :

- avx : avx, avx2 and avx2fma implementations of MIPP
- avx512 : avx512f, avx512 bw bq, avx512 kcni, implementations of MIPP
- neon : neon 32 bit and 64 bits implementations of MIPP
- rvv : RVV1.0 implementation of MIPP
- sse : sse, sse2, sse3, ssse3, sse4.1, sse4.2 implementations of MIPP
- sve : sve implementation of MIPP

In each of these subdirectories, we find three files. 
n.b : "isa" should be replaced by the extension name, like implem_avx.py for avx, implem_rvv.py for RVV and so on.

- implem_isa.py : defines MIPP functions where an intrinsic equivalent exists in the ISA.
- implem_emu_isa.py : defines MIPP functions that need to be emulated in the ISA.
- gen_mipp_isa.py : "glue" function that uses `c_generator.gen_c_functions` (or a function similar to it) and `generic_emu.gen_c_generic_functions` to generate the `include/isa/mipp_impl_isa_gen.h` header.
