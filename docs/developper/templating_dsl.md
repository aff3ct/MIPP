# Mini-Templating DSL Reference

To avoid manually duplicating thousands of lines of identical C intrinsic boilerplate across 10 data types, 6 hardware architectures, and multiple masking modes, MIPPv2 uses a dedicated **Domain-Specific Language (DSL)** embedded directly inside JSON string templates.

This DSL is parsed and specialized by the generator (`generator/helpers_headers/tools.py`) during header emission.

---

## 1. Syntax Overview

All DSL expressions are enclosed within percent symbols:
```text
%type_specifier<expression>%
```

For example:
```text
%r<tp>% res = %add<tp>%(r0, r1);
```

When evaluated for `float32` on AVX, this compiles directly to:
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
| **`v`** | Scalar Value Type | `%v<tp>%` | `float` |
| **`N`** | Number of Elements Constant | `%N<tp>%` | `MIPP_AVX_N_FLOAT32` |
| **`<function>`** | Call to another MIPP function | `%blend<tp>%(...)` | `mipp_avx_blend_float32(...)` |

---

## 3. Type Expressions (`<...>`)

The content inside `<...>` describes the target data type to resolve.

### 3.1. Base Type References
- **`tp`**: Parameter datatype of the enclosing function (e.g. `float32`, `int16`).
- **`tr`**: Return datatype of the enclosing function.

```text
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

#### Examples:
```text
%r<c:int|b:32>%        // Force a 32-bit signed integer register (rvd_int32_t)
%r<c:uint|b:tp>%       // Unsigned integer with the SAME bitwidth as tp (e.g. uint32 if tp is float32)
%r<c:float|b:64>%      // 64-bit floating point register (rvd_float64_t)
%m<c:uint|b:tp>%       // Mask register matching tp's bitwidth
```

---

## 4. Modifiers: LMUL and Masking

### 4.1. LMUL Modifiers (`m:`)
You can adjust the register multiplier for wide register grouping or widening/narrowing operations:

- Fixed LMUL: `m:1`, `m:2`, `m:4`, `m:8`, `m:-2` (where `-2` denotes `1/2`).
- Arithmetic scaling: `m:tp*2`, `m:tp/2`.

```text
%r<tp|m:2>%            // Vector register with 2x LMUL grouping
%r<tp|m:tp*2>%         // Double the LMUL of the current parameter
%add<tp|m:2>%(r0, r1)  // Call the LMUL=2 version of add
```

### 4.2. Mask Modifiers (`mk:`)
When calling another MIPP function, you can explicitly request a specific masking variant:

- `mk:M` or `mk:mask`: Masked variant ($\text{res} = m \ ? \ f(a, b) : a$)
- `mk:Z` or `mk:maskz`: Zero-masked variant ($\text{res} = m \ ? \ f(a, b) : 0$)
- `mk:S` or `mk:masks`: Source-masked variant ($\text{res} = m \ ? \ f(a, b) : \text{src}$)
- `mk:U`: Unmasked variant

```text
// Call the masked variant of blend using m0
%blend<tp|mk:mask>%(op, r0, m0);
```

---

## 5. Interaction with Jinja2 Templating

In many template files (like `generic_emu_templates_mask.json`), MIPP combines the **DSL placeholders (`%...%`)** with **Jinja2 placeholders (`{{ ... }}`)**:

1. **Jinja2 passes first**: Substitutes template variables such as `{{ func_name }}`, `{{ instr_name }}`, or conditional blocks `{% if ... %}`.
2. **DSL parser passes second**: `parse_placeholders` resolves all `%r<...>%` and `%call<...>%` tokens into concrete C99 signatures.

### Real-World Example: Masked Operation Emulation

Extracted from `generator/helpers_headers/generic_emu_templates_mask.json`:

```json
{
    "mask": {
        "code": [
            "%r<tp>% op = %{{func_name}}<tp>%(r0, r1);",
            "%r<tp>% res = %blend<tp>%(op, r0, m0);",
            "return res;"
        ]
    }
}
```

When specializing this template for `func_name = "add"` on `AVX` with `tp = float32`:
1. Jinja2 renders: `%r<tp>% op = %add<tp>%(r0, r1); ...`
2. The DSL parser produces:
```c
static inline rvd_avx_float32_t mipp_avx_add_float32_mask(rvm_avx_float32_t m0, const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
    // Level 2 (Generic Emulated)
    rvd_avx_float32_t op = mipp_avx_add_float32(r0, r1);
    rvd_avx_float32_t res = mipp_avx_blend_float32(op, r0, m0);
    return res;
}
```

### Real-World Example: Unsigned Arithmetic via Reinterpretation

When an ISA natively supports signed integer arithmetic but lacks unsigned variants, the operation can be written once:

```c
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
