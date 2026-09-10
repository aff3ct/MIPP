# SIMD Extensions

`generator/simd_ext/` is the directory where target-specific SIMD backends are defined. The following ISA subdirectories are supported:

- `scalar`: Portable scalar baseline fallback (used for Level 3 fallback and testing)
- `sse`: SSE, SSE2, SSE3, SSSE3, SSE4.1, and SSE4.2
- `avx`: AVX, AVX2, and AVX2+FMA
- `avx512`: AVX-512F, AVX-512BW, and AVX-512DQ
- `neon`: ARM NEON (32-bit and 64-bit / ARMv7 and ARMv8-A)
- `rvv`: RISC-V Vector 1.0 (RVV 1.0)
- `sve`: ARM Scalable Vector Extension (SVE)

Each ISA directory is purely declarative and contains JSON registries:

- `<isa>_isa.json`: Architecture metadata, vector registers (`reg`), mask types (`msk`), header includes, and compiler guard defines (`define`).
- `<isa>_native_templates.json`: Intrinsics code templates with Jinja2 placeholders (`{{ isa.prefix }}`, `{{ instr_name }}`, `{{ isa_dt_par.data_ext }}`).
- `<isa>_native_implems.json`: Maps MIPP functions and supported data types to native templates (Level 0).
- `<isa>_emu_templates.json` (optional): ISA-specific emulation templates (Level 1).
- `<isa>_emu_implems.json` (optional): Maps MIPP functions to ISA-specific emulations (Level 1).

!!! info
    Adding a new directory inside `generator/simd_ext/` is automatically discovered by `gen_mipp_headers.py`, `gen_mipp_tests.py`, and `gen_mipp_docs.py` without modifying any generator Python scripts.
