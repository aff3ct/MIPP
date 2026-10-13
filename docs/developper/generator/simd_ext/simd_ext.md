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
- `<isa>_explorer.json` (optional): API Explorer metadata (display name, Compiler Explorer settings, feature flags).

!!! info
    ISA directories are discovered automatically by the generators: adding a directory is enough to get the ISA layer, its `--layers` value, its entry in the C++ `mipp::ISA` enum and its `mipp_info()` report. See [Adding a New SIMD Extension](../../adding_isa_or_function.md#2-adding-a-new-simd-extension-isa).

The `scalar` directory is special: instead of `scalar_isa.json` and implementation files, it contains `scalar_gen.py`, which emits the Level 3 implementations from `helpers_headers/registry_scalar_implems.json` and `registry_scalar_isa.json`.
