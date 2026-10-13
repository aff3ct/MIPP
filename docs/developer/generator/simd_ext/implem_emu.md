# Specific Emulation Registries (`<isa>_emu_*.json`)

When an ISA lacks a direct hardware instruction for a given datatype but possesses an architecture-specific sequence that is faster than a portable generic emulation (Level 2), it can define **Level 1 specific emulations**.

These files live in `generator/simd_ext/<isa>/`:

- `<isa>_emu_templates.json`: Code templates for ISA-specific emulations.
- `<isa>_emu_implems.json`: Mappings associating MIPP functions to these templates for specific datatypes.

The format is the same as for the native registries ([Native ISA Implementation Registries](implem.md)). Templates can mix Jinja2 placeholders, raw intrinsics and calls to other MIPP functions through the [Mini-Templating DSL](../../templating_dsl.md).

---

## Example: `float32` Division on ARMv7 NEON

ARMv7 NEON has no floating-point division instruction. `neon_emu_templates.json` defines a reciprocal estimate refined by two Newton-Raphson steps, followed by a MIPP multiplication:

```json
{
    "arith_2args_recp": {
        "format": "long",
        "code": [
            "%r<tp>% recp;",
            "recp.r = {{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r1.r);",
            "recp.r = vmulq_{{ isa_dt_par.data_ext }}(recp.r, vrecpsq_{{ isa_dt_par.data_ext }}(r1.r, recp.r));",
            "recp.r = vmulq_{{ isa_dt_par.data_ext }}(recp.r, vrecpsq_{{ isa_dt_par.data_ext }}(r1.r, recp.r));",
            "%r<tp>% res = %mul<tp>%(r0, recp);",
            "return res;"
        ]
    }
}
```

In `neon_emu_implems.json`, the entry is restricted to 32-bit ARM, since AArch64 provides a native `vdivq_f32`:

```json
{
    "div": [
        {
            "instr_name": "recpeq",
            "datatypes": ["float32"],
            "template": "arith_2args_recp",
            "if": "!defined(__aarch64__)"
        }
    ]
}
```

On ARMv7 the generator emits this sequence (Level 1); on AArch64 the native entry (Level 0) is selected instead.