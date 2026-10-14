# Add a Function

This tutorial adds a new function, `absdiff`, which computes the absolute difference $|a_i - b_i|$ of two registers, for all datatypes and all mask variants. At the end, `absdiff` exists in the three APIs on every ISA, is tested and is documented. It runs at <span class="mipp-isa-badge lvl-3">L3</span> (scalar fallback) everywhere: [Add an Implementation](add_implementation.md) then makes it fast.

| Step | File (in `generator/`) | Required |
| :--- | :--- | :---: |
| [1. Declare the interface](#step-1-declare-the-interface) | `helpers_headers/registry_interfaces.json` | Yes |
| [2. Assign a category](#step-2-assign-a-category) | `helpers_headers/registry_categories.json` | Yes |
| [3. Write the scalar reference](#step-3-write-the-scalar-reference) | `helpers_headers/registry_scalar_implems.json` | Yes |
| [4. Document the function](#step-4-document-the-function) | `helpers_headers/funcs_docs.json` | Recommended |
| [5. Generate and test](#step-5-generate-and-test) | none | Yes |
| [6. Set the test properties](#step-6-set-the-test-properties) | `helpers_tests/tests_specs.json` | If the default inputs do not suit the function |

The top-level keys of every JSON file are sorted alphabetically: insert the new entries at their place (the `json-structure` audit warns otherwise).

---

## Step 1: Declare the Interface

In `helpers_headers/registry_interfaces.json`:

```json
"absdiff": {
    "proto_ref": "ret_reg_2args_reg",
    "datatypes": "all_datatypes",
    "horizontal": false,
    "mask_support": "all_mask"
}
```

| Field | Values |
| :--- | :--- |
| `proto_ref` | A prototype of `registry_protos.json`. `ret_reg_2args_reg` takes two registers and returns one. See [Choosing a Prototype](#choosing-a-prototype). |
| `datatypes` | An alias of `DATATYPES_MAP` (`generator/helpers_headers/tools.py`): `all_datatypes`, `all_float`, `all_int` (signed), `all_uint`, `all_int_uint`, `all_64bit`, `all_32bit`, `all_16bit`, `all_8bit`, or pair aliases for conversions (`all_datatypes_cart_prod`, `all_datatypes_same_size`, `all_datatypes_widenning`, ...). An explicit list such as `["float32", "float64"]` is also accepted. |
| `horizontal` | `true` for reductions across the lanes of a register (`hadd`, `hmax`), `false` otherwise. |
| `mask_support` | `no_mask`, `only_mask`, `only_maskz`, `only_masks`, `mask_and_maskz`, `mask_and_masks`, `maskz_and_masks` or `all_mask`. `mask` is Merge-Masked, `maskz` Zero-Masked, `masks` Source-Masked ([Masking Semantics](../../user/masking_semantics.md)). |
| `cpp_name` | Optional. Name of the C++ function when it differs from the C name: `get_k` is exposed as `mipp::get`. |

The names of the generated functions are derived from this entry: `mipp_absdiff_float32`, `mipp_absdiff_float32_maskz`, `mipp_absdiff_float32_m2` in C, `mipp::absdiff` in C++.

### Choosing a Prototype

`registry_protos.json` holds 30 prototypes. Each one describes the return value and the arguments:

```json
"ret_reg_2args_reg": {
    "ret": { "type": "reg", "fixeddatatype": false, "charac": "WO" },
    "args": [
        { "type": "reg", "fixeddatatype": false, "charac": "RO" },
        { "type": "reg", "fixeddatatype": false, "charac": "RO" }
    ]
}
```

| Field | Values |
| :--- | :--- |
| `type` | `reg` (data register), `msk` (mask register), `val` (scalar), `ptr` (pointer), `Nele` (array of one scalar per lane), or `false` for a `void` return. |
| `fixeddatatype` | `false` when the parameter follows the datatype of the function, or a fixed type: `int32` (a shift count), `uint` (the unsigned type of the same width, used for gather and scatter indices). |
| `charac` | `RO` (read) or `WO` (written). |

Add a prototype only if none fits. The names follow the pattern `ret_<return>_<n>args_<arguments>`.

!!! note "Object API"
    The C and C++ Functional APIs are generated for any prototype. The C++ Object API (`generator/helpers_headers/obj_generator.py`) handles automatically the functions that take registers and `int32_t` values and return a register, like `absdiff`: it generates `mipp::absdiff(Rvd, Rvd)` and the masked overloads. Functions with other prototypes (loads, stores, reductions, comparisons, conversions) have a dedicated branch in `obj_generator.py`; a new function of that kind needs one too.

---

## Step 2: Assign a Category

In `helpers_headers/registry_categories.json`, add the function to exactly one of the 10 categories: `arithmetic`, `comparison`, `converts`, `load`, `logic`, `math`, `reduction`, `reinterpret`, `selection`, `store`.

```json
"arithmetic": [
    "add",
    "adds",
    "absdiff"
]
```

The category sets the location of the generated headers (`mipp/internal/.../functions/arithmetic/absdiff.h`), the test files (`tests/src/obj/arithmetic/absdiff.cpp`) and the grouping in the Function Support pages. A function in two categories stops the generator; a function in none gets a `dead-code` warning.

---

## Step 3: Write the Scalar Reference

In `helpers_headers/registry_scalar_implems.json`:

```mipp-json
"absdiff": [
    {
        "type": "element-wide",
        "datatypes": "all_defs",
        "mask_variants": [],
        "implem": [
            "res.r[i] = %!pred_cond!% (r0.r[i] > r1.r[i] ? r0.r[i] - r1.r[i] : r1.r[i] - r0.r[i]) %!pred_alt!%;"
        ]
    }
]
```

This implementation defines what the function computes. It is the <span class="mipp-isa-badge lvl-3">L3</span> fallback of every ISA, and the generated tests compare every API against it. The generator stops if a declared function has no scalar implementation, or if the implementation does not cover exactly the declared datatypes.

| Field | Values |
| :--- | :--- |
| `type` | `element-wide`: `implem` is the body of a loop over the lanes, generated by MIPP (`i` is the lane index, `r0.r[i]` the lane of the first argument, `res.r[i]` the lane of the result). `vector-wide`: `implem` is the whole function body, for reductions and permutations (see `hadd` in the same file). |
| `datatypes` | `all_defs` (the datatypes of the interface), an alias, or a list. Several entries can split the datatypes, for instance one body for `all_int` and one for `all_float`. |
| `mask_variants` | `[]` generates every variant allowed by `mask_support`. A list such as `["no_mask", "maskz"]` restricts the entry to these variants, so that another entry can give a different body for the others (as `store` does). |
| `implem` | The code, as a list of lines. It may use the [templating DSL](../reference/templating_dsl.md) (`%v<tr>%`, `%N<tp>%`, ...). |

`%!pred_cond!%` and `%!pred_alt!%` implement the mask variants: they expand to nothing in the unmasked version, and to the test of the mask lane and the value of an inactive lane (first operand, zero or source register) in the masked versions. Put them around the whole expression, as above.

!!! warning "The reference follows C rules"
    The scalar reference is compiled as C or C++: the overflow of a signed integer is undefined behavior there, while SIMD instructions wrap around. Results then differ on overflow. [Step 6](#step-6-set-the-test-properties) shows how to keep such inputs out of the tests.

---

## Step 4: Document the Function

In `helpers_headers/funcs_docs.json`, a short description and an optional LaTeX formula, used by the Function Support pages and the API Explorer:

```json
"absdiff": {
    "description": "Computes the absolute difference of two vector registers element-wise.",
    "latex": "\\text{res}_i = |r0_i - r1_i|"
}
```

---

## Step 5: Generate and Test

From `generator/` (see [Setup](../setup.md)):

```bash
./gen_mipp_headers.py --simd-ext neon avx    # or without --simd-ext for all ISAs
./gen_mipp_tests.py
```

The generator writes, among others:

- the public headers `<mipp/c/fun/absdiff.h>`, `<mipp/cpp/fun/absdiff.hpp>` and `<mipp/obj/fun/absdiff.hpp>`;
- one implementation header per ISA, for instance `mipp/internal/simd_ext/neon/c/functions/arithmetic/absdiff.h`, where every function carries a comment with its level:

```c
static inline rvd_neon_float32_t mipp_neon_absdiff_float32(const rvd_neon_float32_t r0, const rvd_neon_float32_t r1) {
	// Level 3 (Scalar Fallback)
	...
```

Then build the tests and run those of `absdiff` (see [Build and Run the Unit Tests](../setup.md#4-build-and-run-the-unit-tests), and [Faster Iterations](../setup.md#41-faster-iterations) to build fewer tests):

```bash
cd ../tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_UNITY_BUILD=ON -DCMAKE_CXX_FLAGS="-march=native"
cmake --build build -j4
./build/bin/run-tests "[absdiff]"
```

At this stage the tests pass on every target, but they prove little: at <span class="mipp-isa-badge lvl-3">L3</span>, the function under test calls the scalar reference itself. They check that the function is declared, dispatched and callable in the three APIs, for every datatype, LMUL and mask variant.

Finally, regenerate the documentation pages with `./gen_mipp_docs.py`: `absdiff` gets its Function Support page and appears in the API Explorer.

---

## Step 6: Set the Test Properties

Without an entry in `helpers_tests/tests_specs.json`, the `default` properties apply: uniform random inputs over the whole range of each datatype, and an exact comparison with the scalar reference. For `absdiff`, this default is wrong for the signed integers, and the tests show it as soon as a SIMD implementation exists. With the NEON implementation of the [next tutorial](add_implementation.md):

```text
REQUIRE( mipp_get_int32_m1(rres, i) == mipp_scalar_get_int32_m1(sres, i) )
with expansion:
  -2069792195 == 2069792195 (0x7b5e85c3)
```

The two inputs were so far apart that $a - b$ does not fit in an `int32_t`: the SIMD code wrapped around, the scalar reference did something else. This is not a bug of the function but of the test inputs. Restrict the input domain of the signed types so that the difference always fits:

```json
"absdiff": {
    "domain": {
        "by_datatype": {
            "int8":  { "min": -60, "max": 60 },
            "int16": { "min": -16000, "max": 16000 },
            "int32": { "min": -1000000000, "max": 1000000000 },
            "int64": { "min": -1000000000000, "max": 1000000000000 }
        }
    }
}
```

Add this entry under the `functions` key of `tests_specs.json` and regenerate the tests: with the native implementation, all the `absdiff` tests pass again.

Other common properties:

| Property | Use |
| :--- | :--- |
| `tolerance` and `"comparison": "tolerance"` | Floating-point results that may differ in the last bits (math functions). |
| `overflow_check` | Skip the comparison of the lanes where `add`, `sub` or `mul` overflows, instead of restricting the domain. Currently applied in the C tests only. |
| `nan_inf_skip` | With a tolerance, skip the lanes where the difference with the reference is NaN or infinite. |
| `disabled` and `disabled_reason` | Comment out the generated test (the reason is printed in the file). |
| `support_obj` | `false` if the function has no C++ Object API overload. |

The domain can also depend on the ISA (`by_define`, e.g. `MIPP_AVX2`) and on the mask variant (`unmasked`, `mask`, `maskz`, `masks` keys). All the properties are described in [Test Specifications](../reference/registries/tests_specs.md), and `tests_specs.json` contains an example of each of them.

---

## Next Step

`absdiff` now works everywhere, but at <span class="mipp-isa-badge lvl-3">L3</span>: the registers are copied to arrays and processed lane by lane. [Add an Implementation](add_implementation.md) gives it a native NEON implementation and a generic implementation for the other ISAs.
