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
%r<tp>% res = %add<tp>%(r0, r1);
```

When evaluated for `float32` on AVX, this becomes:

```c
rvd_avx_float32_t res = mipp_avx_add_float32(r0, r1);
```

---

## 2. Token Types

The prefix before the opening angle bracket `<` indicates what entity is being generated:

| Token Prefix | Entity Generated | Example Expression | Generated C Code (AVX, `float32`) |
| :--- | :--- | :--- | :--- |
| **`r`** | Vector Data Register (`rvd`) | `%r<tp>%` | `rvd_avx_float32_t` |
| **`m`** | Vector Mask Register (`rvm`) | `%m<tp>%` | `rvm_avx_float32_t` |
| **`v`** | Scalar Value Type | `%v<tp>%` | `float32_t` |
| **`N`** | Number of Elements Constant | `%N<tp>%` | `MIPP_AVX_N_FLOAT32` |
| **`<function>`** | Call to another MIPP function | `%select<tp>%(...)` | `mipp_avx_select_float32(...)` |

---

## 3. Type Expressions (`<...>`)

The content inside `<...>` describes the target data type to resolve.

### 3.1. Base Type References

- **`tp`**: Parameter datatype of the enclosing function (e.g. `float32`, `int16`).
- **`tr`**: Return datatype of the enclosing function.

```mipp-dsl
%r<tp>%   // A vector register matching the parameter type
%v<tr>%   // A scalar matching the return type
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
%r<c:int|b:32>%        // 32-bit signed integer register (rvd_avx_int32_t)
%r<c:uint|b:tp>%       // Unsigned integer with the same bitwidth as tp (rvd_avx_uint32_t if tp is float32)
%r<c:float|b:64>%      // 64-bit floating-point register (rvd_avx_float64_t)
%m<c:uint|b:tp>%       // Mask register matching tp's bitwidth
```

### 3.3. Two Datatypes

Functions with a datatype pair (conversions, `cast`) take two type expressions separated by a comma, source first:

```mipp-dsl
%cast<tp, c:int|b:tp>%(r0)   // mipp_avx_cast_uint32_int32(r0) if tp is uint32
```

---

## 4. Modifiers: LMUL and Masking

### 4.1. LMUL Modifiers (`m:`)

You can adjust the register multiplier of a type or of a function call:

- Fixed LMUL: `m:1`, `m:2`, `m:4`, `m:8`.
- Relative to the current LMUL: `m:tp*2`, `m:tp/2`.

```mipp-dsl
%r<tp|m:tp/2>%             // Register with half the current LMUL
%hmax<tp|m:tp/2>%(r_lo)    // Call the version of hmax at half the current LMUL
```

!!! warning "Only in templates rendered for an LMUL"
    `m:` has an effect only when the template is rendered for a specific LMUL, as the horizontal templates of `generic_emu_templates_lmulh.json` are (`version: horiz_lmul`). The other templates are rendered once, for the base register: there, `m:` is silently ignored and `%add<tp|m:2>%` produces `mipp_avx_add_float32`.

### 4.2. Variant Modifiers (`v:`)

When calling another MIPP function, `v:` selects its masking variant, with the letters of the C++ `mipp::VARIANT` enum. The arguments then follow the C signature of that variant: the mask first, then the source register for `S`, then the operands.

| Modifier | Variant called | Inactive lanes |
| :--- | :--- | :--- |
| `v:M` | Merge-Masked (`_mask`) | first operand |
| `v:Z` | Zero-Masked (`_maskz`) | zero |
| `v:S` | Source-Masked (`_masks`) | source register `rsrc` |
| `v:U` | unmasked (same as no `v:`) | |

Only these four letters are accepted; any other value stops the generation with a "Panic" message.

```mipp-dsl
%r<tp>% a = %sub<tp|v:Z>%(m0, r0, r1);        // mipp_avx_sub_float32_maskz(m0, r0, r1)
%r<tp>% b = %sub<tp|v:S>%(m0, rsrc, r0, r1);  // mipp_avx_sub_float32_masks(m0, rsrc, r0, r1)
```

`v:` combines with the other modifiers. The horizontal LMUL templates reduce the two halves of a register group with the Zero-Masked variant at half the LMUL:

```mipp-dsl
%hmax<c:tp|b:tp|m:tp/2|v:Z>%(m0_lo, r0_lo)
```

---

## 5. Interaction with Jinja2 Templating

In many template files (like `generic_emu_templates_mask.json`), MIPP combines the **DSL placeholders (`%...%`)** with **Jinja2 placeholders (`{{ ... }}`)**:

1. **Jinja2 passes first**: Substitutes template variables such as `{{ func_name }}`, `{{ instr_name }}`, or conditional blocks `{% if ... %}` (see [Add an Implementation](../tutorials/add_implementation.md#templates) for the list of variables).
2. **DSL parser passes second**: `parse_placeholders` resolves all `%r<...>%` and `%function<...>%` tokens into C types and function names.

### Real-World Example: Masked Operation Emulation

Extracted from `generator/helpers_headers/generic_emu_templates_mask.json`:

```mipp-json
"binary_mask_all_datatypes": {
    "format": "long",
    "code": [
        "%r<tp>% op = %{{func_name}}<tp>%(r0, r1);",
        "%r<tp>% res = %select<tp>%(m0, op, r0);",
        "return res;"
    ]
}
```

When specializing this template for `func_name = "add"` on AVX with `tp = float32`:

1. Jinja2 renders:

    ```mipp-dsl
    %r<tp>% op = %add<tp>%(r0, r1);
    %r<tp>% res = %select<tp>%(m0, op, r0);
    return res;
    ```

2. The DSL parser produces the body of `mipp_avx_add_float32_mask`:

    ```c
    static inline rvd_avx_float32_t mipp_avx_add_float32_mask(const rvm_avx_float32_t m0, const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
    	// Level 2 (Generic Emulation)
    	rvd_avx_float32_t op = mipp_avx_add_float32(r0, r1);
    	rvd_avx_float32_t res = mipp_avx_select_float32(m0, op, r0);
    	return res;
    }
    ```

### Real-World Example: Unsigned Arithmetic via Reinterpretation

When an ISA natively supports signed integer arithmetic but lacks unsigned variants, the operation can be written once:

```mipp-dsl
// Emulate unsigned addition via bitcast to signed integer
%r<c:int|b:tp>% r0_s = %cast<tp, c:int|b:tp>%(r0);
%r<c:int|b:tp>% r1_s = %cast<tp, c:int|b:tp>%(r1);
%r<c:int|b:tp>% res_s = %add<c:int|b:tp>%(r0_s, r1_s);
return %cast<c:int|b:tp, tp>%(res_s);
```

For `uint32`, this generates:

```c
rvd_avx_int32_t r0_s = mipp_avx_cast_uint32_int32(r0);
rvd_avx_int32_t r1_s = mipp_avx_cast_uint32_int32(r1);
rvd_avx_int32_t res_s = mipp_avx_add_int32(r0_s, r1_s);
return mipp_avx_cast_int32_uint32(res_s);
```
