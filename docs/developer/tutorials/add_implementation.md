# Add an Implementation

At the end of [Add a Function](add_function.md), `absdiff` works on every ISA but at <span class="mipp-isa-badge lvl-3">L3</span>: the registers are copied to arrays and processed lane by lane. This tutorial makes it fast:

1. a **native** implementation on NEON, which has a dedicated instruction (`vabdq`): <span class="mipp-isa-badge lvl-0">L0</span>;
2. a **generic** implementation for the other ISAs, written once with other MIPP functions: <span class="mipp-isa-badge lvl-2">L2</span>;
3. a generic implementation of the **masked** variants: <span class="mipp-isa-badge lvl-2">L2</span>.

An ISA that has no single instruction but can build the operation from a few of its own intrinsics gets a **dedicated emulation** (<span class="mipp-isa-badge lvl-1">L1</span>), shown at the [end of this page](#level-1-dedicated-emulation).

| Level | Code made of | Templates | Entries |
| :--- | :--- | :--- | :--- |
| <span class="mipp-isa-badge lvl-0">L0</span> Native | one intrinsic | `simd_ext/<isa>/<isa>_native_templates.json` | `simd_ext/<isa>/<isa>_native_implems.json` |
| <span class="mipp-isa-badge lvl-1">L1</span> Dedicated emulation | several intrinsics of the ISA, possibly MIPP calls | `simd_ext/<isa>/<isa>_emu_templates.json` | `simd_ext/<isa>/<isa>_emu_implems.json` |
| <span class="mipp-isa-badge lvl-2">L2</span> Generic emulation | MIPP calls only, for all ISAs | `helpers_headers/generic_emu_templates*.json` | `helpers_headers/generic_emu_implems*.json` |

The file sets the level: the same template placed in another file gets another level. All paths are relative to `generator/`.

---

## Step 1: Native Implementation on NEON <span class="mipp-isa-badge lvl-0">L0</span> { #step-1-native-implementation-on-neon-l0 }

An implementation is made of a **template**, the code, and an **entry**, which applies the template to a function and a set of datatypes.

NEON already has a template for the instructions that take two registers and return one, in `simd_ext/neon/neon_native_templates.json`:

```mipp-json
"arith_2args": {
    "format": "short",
    "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);"
}
```

`add`, `sub`, `max` and `min` use it. Add the `absdiff` entry to `simd_ext/neon/neon_native_implems.json`:

```json
"absdiff": [
    {
        "instr_name": "abdq",
        "datatypes": ["float64"],
        "template": "arith_2args",
        "if": "defined(__aarch64__)"
    },
    {
        "instr_name": "abdq",
        "datatypes": ["float32", "int32", "int16", "int8", "uint32", "uint16", "uint8"],
        "template": "arith_2args"
    }
]
```

- `vabdq_f64` exists on AArch64 only, hence the `if` condition. On ARMv7, the resolver looks for another candidate for `float64`.
- NEON has no `vabdq` for 64-bit integers: `int64` and `uint64` are left out, the generic implementation of [step 2](#step-2-generic-implementation-l2) covers them.

After `./gen_mipp_headers.py`, the NEON header contains:

```c
#if defined(__aarch64__)
static inline rvd_neon_float64_t mipp_neon_absdiff_float64(const rvd_neon_float64_t r0, const rvd_neon_float64_t r1) {
	// Level 0 (Native Hardware)
	rvd_neon_float64_t res;
	res.r = vabdq_f64(r0.r, r1.r);
	return res;
}
#endif
```

### Templates

A template has a `format` and a `code`:

- `short`: `code` is one expression. The generator declares `res`, assigns the expression to `res.r` and returns `res`, as above.
- `long`: `code` is the whole function body, as a list of lines.

The code is rendered by Jinja2 with these variables:

| Variable | Content |
| :--- | :--- |
| `isa` | The ISA descriptor (`<isa>_isa.json`): `isa.prefix` (`v` on NEON, `_mm` on SSE, `_mm256` on AVX), `isa.name`, `isa.size`, ... |
| `instr_name` | The `instr_name` of the entry. |
| `isa_dt_par`, `isa_dt_ret` | The datatype entry of the ISA descriptor, for the parameter and the return types: `data_ext` (`f32`, `s32`, `ps`, `epi32`, ...), `reg`, `msk`, ... |
| `dt_par`, `dt_ret` | The generic description of the datatypes (`name`, `n_bits`, `category`, ...). |
| `cstdint_ret` | The C type of the return datatype (`int32_t`, `float`, ...). |
| `func_name` | The MIPP function name (`absdiff`), useful in templates shared by several functions. |
| `lmul`, `mask_kind` | The LMUL and the mask variant being generated. |

The separator between prefix and name belongs to the template: SSE templates write `{{ isa.prefix }}_{{ instr_name }}`, NEON ones `{{ isa.prefix }}{{ instr_name }}`. Inside the parameters, `r0.r` is the native register wrapped by the MIPP type `rvd_neon_float32_t`. The code may also call MIPP functions through the [templating DSL](../reference/templating_dsl.md) (`%max<tp>%(r0, r1)`), as the <span class="mipp-isa-badge lvl-1">L1</span> and <span class="mipp-isa-badge lvl-2">L2</span> templates do.

An entry can also hold its template inline (`"template": { "format": ..., "code": ... }`) instead of a name.

---

## Step 2: Generic Implementation <span class="mipp-isa-badge lvl-2">L2</span> { #step-2-generic-implementation-l2 }

$|a - b| = \max(a, b) - \min(a, b)$ holds for every datatype, including unsigned ones, and uses three MIPP functions. Write it once in `helpers_headers/generic_emu_templates.json`:

```mipp-json
"absdiff": {
    "format": "long",
    "code": [
        "%r<tp>% hi = %max<tp>%(r0, r1);",
        "%r<tp>% lo = %min<tp>%(r0, r1);",
        "return %sub<tp>%(hi, lo);"
    ]
}
```

and the entry in `helpers_headers/generic_emu_implems.json`:

```json
"absdiff": [
    {
        "datatypes": "all_datatypes",
        "template_ref": "tpl_generic_emu.absdiff"
    }
]
```

`%r<tp>%` is the register type and `%max<tp>%` the `max` function of the ISA being generated, for the current datatype and LMUL. On AVX the template becomes:

```c
static inline rvd_avx_float32_t mipp_avx_absdiff_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	// Level 2 (Generic Emulation)
	rvd_avx_float32_t hi = mipp_avx_max_float32(r0, r1);
	rvd_avx_float32_t lo = mipp_avx_min_float32(r0, r1);
	return mipp_avx_sub_float32(hi, lo);
}
```

The <span class="mipp-isa-badge lvl-0">L0</span> entries of step 1 have priority on NEON: the generic template only fills the gaps (`int64` and `uint64`).

`template_ref` names a template of another file, with a prefix:

| Prefix | Templates | Entries |
| :--- | :--- | :--- |
| `tpl_generic_emu.` | `generic_emu_templates.json` | `generic_emu_implems.json` |
| `tpl_mask_generic_emu.` | `generic_emu_templates_mask.json` | `generic_emu_implems_mask.json` |
| `tpl_horiz_lmul_generic_emu.` | `generic_emu_templates_lmulh.json` | `generic_emu_implems_lmulh.json` |

The `lmulh` files combine the registers of an LMUL > 1 group for horizontal functions (reductions).

!!! note "A generic template is only as fast as its dependencies"
    The resolver uses an <span class="mipp-isa-badge lvl-2">L2</span> template only where the functions it calls exist. When one of them is itself an <span class="mipp-isa-badge lvl-3">L3</span> fallback, the scalar fallback of `absdiff` is used instead, or the generic code is reported as <span class="mipp-isa-badge lvl-3">L3</span> (see [Invariants](../index.md#2-invariants)). Check the result with the methods of [step 4](#step-4-check-the-levels).

---

## Step 3: Masked Variants <span class="mipp-isa-badge lvl-2">L2</span> { #step-3-masked-variants-l2 }

At this point `mipp_neon_absdiff_float32_maskz` is still <span class="mipp-isa-badge lvl-3">L3</span>. The masked variants have their own candidates, selected with the `version` field. `generic_emu_templates_mask.json` provides templates for any function with two register arguments, which compute the unmasked function then apply the mask:

```mipp-json
"binary_maskz_all_datatypes": {
    "format": "long",
    "code": [
        "%r<tp>% op = %{{func_name}}<tp>%(r0, r1);",
        "%r<tp>% tmp = %toreg<tp>%(m0);",
        "%r<tp>% res = %andb<tp>%(op, tmp);",
        "return res;"
    ]
}
```

Reuse them in `helpers_headers/generic_emu_implems_mask.json`, as `add`, `max` or `min` do:

```json
"absdiff": [
    {
        "instr_name": "absdiff",
        "datatypes": "all_datatypes",
        "version": "mask",
        "template_ref": "tpl_mask_generic_emu.binary_mask_all_datatypes"
    },
    {
        "instr_name": "absdiff",
        "datatypes": "all_datatypes",
        "version": "maskz",
        "template_ref": "tpl_mask_generic_emu.binary_maskz_all_datatypes"
    },
    {
        "instr_name": "absdiff",
        "datatypes": "all_datatypes",
        "version": "masks",
        "template_ref": "tpl_mask_generic_emu.binary_masks_all_datatypes"
    }
]
```

The masked variants then follow the level of the unmasked one. An ISA with native masked instructions (AVX-512, SVE, RVV) adds entries with a `version` field in its own `*_native_implems.json` instead.

---

## Step 4: Check the Levels

After `./gen_mipp_headers.py`:

- every generated function starts with a `// Level N` comment, in `include/mipp/internal/simd_ext/<isa>/c/functions/<category>/`;
- the summary table printed at the end of `gen_mipp_headers.py` gives the distribution of the levels per ISA;
- after `./gen_mipp_docs.py`, the Function Support page of `absdiff` and the [API Explorer](../../explorer/index.md) show the level of each datatype, variant and ISA.

The `absdiff` of this tutorial (LMUL 1, unmasked) gives:

| ISA | <span class="mipp-isa-badge lvl-0">L0</span> | <span class="mipp-isa-badge lvl-2">L2</span> | <span class="mipp-isa-badge lvl-3">L3</span> |
| :--- | :--- | :--- | :--- |
| NEON | `float32`, 8/16/32-bit integers; `float64` on AArch64 | `int64`, `uint64` on AArch64 | `float64`, `int64`, `uint64` on ARMv7 |
| AVX | | `float32`, `float64`; the integers except `int64` with AVX2 | `int64`; the integers without AVX2 |
| SSE | | | all: SSE has no `max` and `min` implementation |

The masked variants are <span class="mipp-isa-badge lvl-2">L2</span> wherever the unmasked function is <span class="mipp-isa-badge lvl-0">L0</span> or <span class="mipp-isa-badge lvl-2">L2</span>, and <span class="mipp-isa-badge lvl-3">L3</span> elsewhere. To improve SSE, give `max` and `min` SSE implementations (SSE4.1 has `_mm_max_epi32`, ...): `absdiff` will follow without any change.

Then run the tests on each target you changed (see [Setup](../setup.md#4-build-and-run-the-unit-tests)). On NEON the first run fails for `int32` and `int64`: the [test properties](add_function.md#step-6-set-the-test-properties) of `absdiff` must keep the signed differences in range.

---

## Dedicated Emulation <span class="mipp-isa-badge lvl-1">L1</span> { #level-1-dedicated-emulation }

When an ISA has no instruction for an operation but can build it from a few of its own intrinsics, faster than the generic code, the implementation goes to `simd_ext/<isa>/<isa>_emu_templates.json` and `<isa>_emu_implems.json`. The format is the same as for <span class="mipp-isa-badge lvl-0">L0</span>.

ARMv7 NEON has no floating-point division. `neon_emu_templates.json` computes a reciprocal estimate, refines it with two Newton-Raphson steps, then multiplies with the MIPP `mul`:

```mipp-json
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
```

The entry in `neon_emu_implems.json` is restricted to 32-bit Arm, since AArch64 has a native `vdivq_f32`:

```json
"div": [
    {
        "instr_name": "recpeq",
        "datatypes": ["float32"],
        "template": "arith_2args_recp",
        "if": "!defined(__aarch64__)"
    }
]
```

The `levels` audit checks that each entry is in the right file: a native entry must contain exactly one intrinsic and no MIPP call, a dedicated emulation several intrinsics or intrinsics and MIPP calls. Code without any intrinsic belongs to the generic files. When an exception is justified, set `"skip_audit_level": true` and explain it in `skip_audit_level_reason`.

---

## Fields of an Entry

The fields are the same in all the `*_implems.json` files. The complete reference is [Implementations](../reference/registries/implems.md).

| Field | Use |
| :--- | :--- |
| `datatypes` | Required. Alias or list of datatypes (datatype pairs for conversions). |
| `template` / `template_ref` | Required, one of them. Template name of the ISA's templates file, inline template, or reference to a generic template with its prefix. |
| `instr_name` | String passed to the template as `instr_name`. |
| `if` | Preprocessor condition. The entry is emitted under `#if <condition>`; the rest of the condition space goes to the next candidate. |
| `version` | `mask`, `maskz` or `masks`: the entry implements this mask variant. `horiz_lmul`: the entry implements an LMUL > 1 horizontal function. |
| `preferred_simd_ext` | ISA or list of ISAs. Among the candidates of the same level, the entry is tried first on these ISAs and last on the others. Used to choose between several generic entries. |
| `simd_size` | Register size or list of sizes (in bits, after LMUL) for which the entry applies, e.g. `128`. |
| `skip_audit_level`, `skip_audit_level_reason` | Disable the `levels` audit for this entry, with a reason. |

---

## Next Step

[Add an ISA](add_isa.md) creates a new target from scratch. To understand how the resolver handles conditions and dependencies, see [Code Generation](../internals/code_generation.md).
