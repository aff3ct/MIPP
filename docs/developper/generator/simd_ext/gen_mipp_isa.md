# ISA Architecture Metadata (`<isa>_isa.json`)

Each target architecture supported by MIPP is configured via a `<isa>_isa.json` descriptor in `generator/simd_ext/<isa>/`.

---

## 1. Schema Overview

```json
{
    "name": "avx",
    "prefix": "_mm256",
    "size": 256,
    "sub_isa": "sse",
    "define": "defined(__AVX__)",
    "header_template": [
        "#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_",
        "#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_",
        "#include <immintrin.h>",
        "#include <mipp/internal/simd_ext/sse/c/common.h>"
    ],
    "datatypes": {
        "float32": {
            "data_ext": "ps",
            "data_ext_logi": "ps",
            "data_ext_msk": "ps",
            "reg": "__m256",
            "msk": "__m256",
            "to_ptr": "float32_t"
        }
    },
    "sw_lmul": [1, 2, 4, 8, -2],
    "hw_lmul": [],
    "mipp_definitions": [
        "#define MIPP_64BIT",
        "#ifdef __AVX2__",
        "\t#define MIPP_AVX2",
        "\t#define MIPP_INSTR_VERSION 2",
        "\t#define MIPP_BW",
        "#else",
        "\t#define MIPP_INSTR_VERSION 1",
        "#endif"
    ]
}
```

---

## 2. Core Fields

- `name`: Target ISA identifier (e.g. `sse`, `avx`, `rvv`). The generator defines `MIPP_<NAME>` when the ISA is selected.
- `prefix`: Intrinsic function prefix used in template string expansions (e.g. `_mm256`).
- `size`: Base register width in bits (e.g. 128, 256, 512). Scalable ISAs (SVE) list the supported widths.
- `sub_isa`: Parent ISA (e.g. `avx` for `avx512`, `sse` for `avx`). It sets the detection precedence (a derived ISA is tested before its parent) and is automatically included by `--simd-ext`. It does **not** make the parent's implementations available implicitly.
- `define`: Compiler preprocessor expression detecting hardware support (e.g. `defined(__AVX__)`).
- `header_template`: C include directives and guard macros emitted at the top of the generated ISA header.
- `datatypes`: Mapping of each data type to:
    - `reg`: Vector register type (e.g. `__m256`, `float32x4_t`, `vfloat32m1_t`).
    - `msk`: Mask register type (e.g. `__m256`, `uint32x4_t`, `vbool32_t`).
    - `data_ext`: Intrinsic naming suffix.
    - `to_ptr`: Pointer cast type.
- `sw_lmul`: LMUL factors emulated in software by aggregating several base registers (e.g. `[1, 2, 4, 8]`).
- `hw_lmul`: LMUL factors supported natively by the hardware (register groups on RVV: `[1, 2, 4, 8, -2]`; `[1]` on SVE).
- `-2` in `sw_lmul` or `hw_lmul` enables half-vectors (`d2`, exposed to users through `MIPP_LDIV_2`).
- `sw_ldiv_type`: `"sub_isa"` builds the software half-vectors on the registers of `sub_isa` (AVX `d2` uses SSE registers). Requires `sub_isa`; only `-2` is supported.
- `mipp_definitions`: MIPP feature flag macros emitted for user applications (e.g. `MIPP_AVX2`, `MIPP_BW`, `MIPP_64BIT`).

Other optional fields (`hw_mask`, `hw_mask_is_bitfield`, `layout`, ...) are described by `generator/helpers_headers/schemas/isa_schema.json`.