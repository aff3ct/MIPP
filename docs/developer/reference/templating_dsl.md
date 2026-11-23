# Mini-Templating DSL Reference

To avoid manually duplicating thousands of lines of identical C intrinsic boilerplate across 10 data types, 6 hardware architectures, and multiple masking modes, MIPPv2 uses a dedicated **Domain-Specific Language (DSL)** embedded directly inside JSON string templates.

This DSL is parsed and specialized by the generator (`generator/helpers_headers/tools.py`) during header emission. In this documentation, code blocks use the `mipp-dsl` (C with DSL) and `mipp-json` (JSON templates) highlighting, provided by the lexers of `scripts/pygments_mipp/`.

---

## 1. Syntax Overview

All DSL expressions are enclosed within percent symbols:

```text
%<prefix><<type expression>>%
```

For example:

```mipp-dsl
%vd<tp>% res = %add<tp>%(vd0, vd1);
```

When evaluated for `float32` on AVX, for the base registers, this becomes:

```c
vd_avx_float32_m1_t res = mipp_avx_add_float32_m1(vd0, vd1);
```

Inside an ISA, the base registers and the functions on them are named with the `_m1` suffix ([Code Generation](../internals/code_generation.md#2-one-isa-layer)); the examples of this page use these names.

---

## 2. Token Types

The prefix before the opening angle bracket `<` indicates what entity is being generated:

| Token Prefix | Entity Generated | Example Expression | Generated C Code (AVX, `float32`) |
| :--- | :--- | :--- | :--- |
| **`vd`** | Vector Data Register (`vd`) | `%vd<tp>%` | `vd_avx_float32_m1_t` |
| **`vm`** | Vector Mask Register (`vm`) | `%vm<tp>%` | `vm_avx_float32_m1_t` |
| **`s`** | Scalar Value Type | `%s<tp>%` | `float32_t` |
| **`N`** | Number of Elements Constant | `%N<tp>%` | `MIPP_AVX_N_FLOAT32` |
| **`<function>`** | Call to another MIPP function | `%select<tp>%(...)` | `mipp_avx_select_float32_m1(...)` |

### 2.1. Naming Convention of Function Arguments

Inside a template body, the parameters of the function being generated are not named freely: their name is derived from their kind and from their position **among the arguments of the same kind** (counting from 0). The letters are the same as the token prefixes above.

| Name | Kind of argument | Example |
| :--- | :--- | :--- |
| **`vd0`, `vd1`, `vd2`, ...** | Vector data registers (`vd`) | `add(vd0, vd1)` |
| **`vm0`, `vm1`, `vm2`, ...** | Vector mask registers (`vm`) | `select(vm0, vd0, vd1)` |
| **`s0`, `s1`, `s2`, ...** | Scalar values | `set1(s0)`, `rshift_vs(vd0, s0)` |
| **`p0`, `p1`, `p2`, ...** | Pointers (memory addresses) | `loadu(p0)` |

For example, in `%vd<tp>% res = %add<tp>%(vd0, vd1);`, `vd0` and `vd1` are the first and second register arguments. A function taking a mask, a register and a scalar (e.g. a masked shift) names them `vm0`, `vd0` and `s0`.

A few arguments have a fixed, special name instead: `vdsrc` (the source register of the Source-Masked `masks` variants, e.g. `%sub<tp|v:S>%(vm0, vdsrc, vd0, vd1)`), `vals` (the values of `set`) and `vi` (the index vector of `gather`/`scatter`).

---

## 3. Type Expressions (`<...>`)

The content inside `<...>` describes the target data type to resolve.

### 3.1. Base Type References

- **`tp`**: Parameter datatype of the enclosing function (e.g. `float32`, `int16`).
- **`tr`**: Return datatype of the enclosing function.

```mipp-dsl
%vd<tp>% // A vector register matching the parameter type
%s<tr>% // A scalar matching the return type
```

### 3.2. Structured Type Attributes (`c:` and `b:`)

You can construct new datatypes by altering the **category** (`c:`) or the **bitwidth** (`b:`), separated by a pipe `|`:

* **Categories (`c:`)**:

    - `c:int` : Signed integer
    - `c:uint` : Unsigned integer
    - `c:float` : Floating-point
    - `c:tp` or `c:tr` : Copy category from parameter / return type

* **Bitwidths (`b:`)**:

    - `b:64`, `b:32`, `b:16`, `b:8` : Fixed bitwidth
    - `b:tp` or `b:tr` : Copy bitwidth from parameter / return type

A missing attribute is taken from `tp`. The accepted parts are `tp`, `tr`, `c:`, `b:`, and the modifiers `m:` and `v:` of §4; any other part stops the generation with a "Panic" message.

#### Examples

```mipp-dsl
%vd<c:int|b:32>%  // 32-bit signed integer register (vd_avx_int32_m1_t)
%vd<c:uint|b:tp>% // Unsigned integer with the same bitwidth as tp (vd_avx_uint32_m1_t if tp is float32)
%vd<c:float|b:64>% // 64-bit floating-point register (vd_avx_float64_m1_t)
%vm<c:uint|b:tp>% // Mask register matching tp's bitwidth
```

!!! note "`tr` and the LMUL of the result"
    For the functions that change the LMUL (`lo`, `hi`, `combine`), a plain `%vd<tr>%` / `%vm<tr>%` is the register of the **result**, with its own LMUL (for example `d2` for `lo` applied to an `m1`), whereas `tp` and the `m:` expressions start from the LMUL of the arguments.

### 3.3. Two Datatypes

Functions with a datatype pair (conversions, `cast`) take two type expressions separated by a comma, source first:

```mipp-dsl
%cast<tp, c:int|b:tp>%(vd0) // mipp_avx_cast_uint32_int32_m1(vd0) if tp is uint32
```

---

## 4. Modifiers: LMUL and Masking

### 4.1. LMUL Modifiers (`m:`)

You can adjust the register multiplier of a type or of a function call:

- Fixed LMUL: `m:1`, `m:2`, `m:4`, `m:8`, and `m:-2` for the half-vectors (`d2`).
- Relative to the current LMUL: `m:tp*2`, `m:tp/2` (and `tr` instead of `tp`). From a half-vector, `m:tp*2` is the full register (`d2` to `m1`).

```mipp-dsl
%vd<tp|m:tp/2>%         // Register with half the current LMUL
%hmax<tp|m:tp/2>%(r_lo) // Call the version of hmax at half the current LMUL
```

!!! warning "Only in templates rendered for an LMUL"
    `m:` has an effect only when the template is rendered for a specific LMUL: the horizontal templates of `generic_emu_templates_lmulh.json` (`mode: horiz_lmul`), and the half-vector templates of `generic_ldiv_mask.json` and `<isa>_ldiv_mask.json`, rendered for `d2` (or `m1` for `lo` and `hi`), where `%N<tp|m:tp*2>%` is the number of elements of the full register. The other templates are rendered once, for the base register: there, `m:` is silently ignored and `%add<tp|m:2>%` produces `mipp_avx_add_float32_m1`.

### 4.2. Variant Modifiers (`v:`)

When calling another MIPP function, `v:` selects its masking variant, with the letters of the C++ `mipp::VARIANT` enum. The arguments then follow the C signature of that variant: the mask first, then the source register for `S`, then the operands.

| Modifier | Variant called | Inactive lanes |
| :--- | :--- | :--- |
| `v:M` | Merge-Masked (`_mask`) | first operand |
| `v:Z` | Zero-Masked (`_maskz`) | zero |
| `v:S` | Source-Masked (`_masks`) | source register `vdsrc` |
| `v:U` | unmasked (same as no `v:`) | |

Only these four letters are accepted; any other value stops the generation with a "Panic" message.

```mipp-dsl
%vd<tp>% a = %sub<tp|v:Z>%(vm0, vd0, vd1);   // mipp_avx_sub_float32_maskz_m1(vm0, vd0, vd1)
%vd<tp>% b = %sub<tp|v:S>%(vm0, vdsrc, vd0, vd1); // mipp_avx_sub_float32_masks_m1(vm0, vdsrc, vd0, vd1)
```

`v:` combines with the other modifiers. The horizontal LMUL templates reduce the two halves of a register group with the Zero-Masked variant at half the LMUL:

```mipp-dsl
%hmax<c:tp|b:tp|m:tp/2|v:Z>%(m0_lo, r0_lo)
```

---

## 5. Interaction with Jinja2 Templating

In many template files (like `generic_emu_templates_mask.json`), MIPP combines the **DSL placeholders (`%...%`)** with **Jinja2 placeholders (`{{ ... }}`)**:

1. **Jinja2 passes first**: Substitutes template variables such as `{{ func_name }}`, `{{ instr_name }}`, or conditional blocks `{% if ... %}` (see [Add an Implementation](../tutorials/add_implementation.md#templates) for the list of variables).
2. **DSL parser passes second**: `parse_placeholders` resolves all `%vd<...>%` and `%function<...>%` tokens into C types and function names.

### Real-World Example: Masked Operation Emulation

Extracted from `generator/helpers_headers/generic_emu_templates_mask.json`:

```mipp-json
"binary_mask_all_datatypes": {
    "format": "long",
    "code": [
        "%vd<tp>% op = %{{func_name}}<tp>%(vd0, vd1);",
        "%vd<tp>% res = %select<tp>%(vm0, op, vd0);",
        "return res;"
    ]
}
```

When specializing this template for `func_name = "add"` on AVX with `tp = float32`:

1. Jinja2 renders:

    ```mipp-dsl
    %vd<tp>% op = %add<tp>%(vd0, vd1);
    %vd<tp>% res = %select<tp>%(vm0, op, vd0);
    return res;
    ```

2. The DSL parser produces the body of `mipp_avx_add_float32_mask_m1`:

    ```c
    static inline vd_avx_float32_m1_t mipp_avx_add_float32_mask_m1(const vm_avx_float32_m1_t vm0, const vd_avx_float32_m1_t vd0, const vd_avx_float32_m1_t vd1) {
    	// Level 2 (Generic Emulation)
    	vd_avx_float32_m1_t op = mipp_avx_add_float32_m1(vd0, vd1);
    	vd_avx_float32_m1_t res = mipp_avx_select_float32_m1(vm0, op, vd0);
    	return res;
    }
    ```

### Real-World Example: Unsigned Arithmetic via Reinterpretation

When an ISA natively supports signed integer arithmetic but lacks unsigned variants, the operation can be written once:

```mipp-dsl
// Emulate unsigned addition via bitcast to signed integer
%vd<c:int|b:tp>% r0_s = %cast<tp, c:int|b:tp>%(vd0);
%vd<c:int|b:tp>% r1_s = %cast<tp, c:int|b:tp>%(vd1);
%vd<c:int|b:tp>% res_s = %add<c:int|b:tp>%(r0_s, r1_s);
return %cast<c:int|b:tp, tp>%(res_s);
```

For `uint32`, this generates:

```c
vd_avx_int32_m1_t r0_s = mipp_avx_cast_uint32_int32_m1(vd0);
vd_avx_int32_m1_t r1_s = mipp_avx_cast_uint32_int32_m1(vd1);
vd_avx_int32_m1_t res_s = mipp_avx_add_int32_m1(r0_s, r1_s);
return mipp_avx_cast_int32_uint32_m1(res_s);
```
