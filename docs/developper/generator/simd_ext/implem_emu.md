# Specific Emulation Registries (`<isa>_emu_*.json`)

When an ISA lacks a direct hardware instruction for a given datatype but possesses an architecture-specific sequence that is faster than a portable generic emulation (Level 2), it can define **Level 1 specific emulations**.

These files live in `generator/simd_ext/<isa>/`:

- `<isa>_emu_templates.json`: Code templates for ISA-specific emulations.
- `<isa>_emu_implems.json`: Mappings associating MIPP functions to these templates for specific datatypes.

---

## Example: AVX Emulations (`avx_emu_templates.json`)

On AVX (which natively supports 256-bit floating-point operations but lacks 256-bit integer operations until AVX2), 256-bit integer operations are emulated using two 128-bit SSE instructions:

```json
{
    "arith_2args_2x128": {
        "format": "long",
        "code": [
            "__m128i r0_lo = _mm256_extractf128_si256(r0.r, 0);",
            "__m128i r0_hi = _mm256_extractf128_si256(r0.r, 1);",
            "__m128i r1_lo = _mm256_extractf128_si256(r1.r, 0);",
            "__m128i r1_hi = _mm256_extractf128_si256(r1.r, 1);",
            "__m128i res_lo = {{ sub_isa.prefix }}{{ instr_name }}_{{ sub_isa_dt.data_ext }}(r0_lo, r1_lo);",
            "__m128i res_hi = {{ sub_isa.prefix }}{{ instr_name }}_{{ sub_isa_dt.data_ext }}(r0_hi, r1_hi);",
            "rvd_avx_{{ dt }}_t res;",
            "res.r = _mm256_insertf128_si256(_mm256_castsi128_si256(res_lo), res_hi, 1);",
            "return res;"
        ]
    }
}
```

In `avx_emu_implems.json`:

```json
{
    "add": [
        {
            "instr_name": "add",
            "datatypes": "all_int_uint",
            "template": "arith_2args_2x128",
            "if": "!defined(__AVX2__)"
        }
    ]
}
```

When compiled on an AVX-only CPU (`!defined(__AVX2__)`), the generator emits this fast 2x128-bit split rather than falling back to scalar code.