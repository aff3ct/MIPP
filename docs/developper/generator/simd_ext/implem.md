# Native ISA Implementation Registries

Each ISA directory in `generator/simd_ext/<isa>/` defines its native Level 0 implementations using two complementary JSON registries.

---

## 1. `<isa>_native_templates.json`

This file contains hardware intrinsic code templates parameterized with Jinja2 placeholders.

Example from `generator/simd_ext/neon/neon_native_templates.json`:

```json
{
    "arith_2args": {
        "format": "short",
        "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);"
    }
}
```

Key placeholders:

- `{{ isa.prefix }}`: The intrinsic prefix defined in `<isa>_isa.json` (e.g. `_mm_` for SSE, `_mm256_` for AVX, `v` for NEON).
- `{{ instr_name }}`: The specific operation suffix passed from `<isa>_native_implems.json`.
- `{{ isa_dt_par.data_ext }}`: Target datatype suffix (e.g. `f32`, `s32`, `ps`, `epi32`).

---

## 2. `<isa>_native_implems.json`

This file maps canonical MIPP function names to specific native templates.

Example from `generator/simd_ext/neon/neon_native_implems.json`:

```json
{
    "add": [
        {
            "instr_name": "addq",
            "datatypes": [
                "float64"
            ],
            "template": "arith_2args",
            "if": "defined(__aarch64__)"
        },
        {
            "instr_name": "addq",
            "datatypes": [
                "int32",
                "uint32",
                "float32"
            ],
            "template": "arith_2args"
        }
    ]
}
```

Key fields:

- `instr_name`: Architecture-specific intrinsic name.
- `datatypes`: Datatype alias (e.g. `"all_datatypes"`, `"all_float"`) or explicit array of datatypes.
- `template`: Name of the template key declared in `<isa>_native_templates.json`.
- `if` (optional): Preprocessor `#if` guard for architecture feature extensions (e.g. `defined(__aarch64__)` or `defined(__AVX2__)`).