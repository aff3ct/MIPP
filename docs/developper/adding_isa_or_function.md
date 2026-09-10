# Guide: Adding a Function or Target ISA

This guide provides a step-by-step workflow for contributors wishing to add a new vector operation or support a new hardware vector instruction set.

---

## 1. Adding a New MIPP Function

Adding a function involves registering its canonical signature, categorizing it, providing a scalar reference baseline, and adding native hardware mappings.

### Step 1: Declare the Function Interface (`generator/helpers_headers/registry_interfaces.json`)

Every MIPP function must be defined in `registry_interfaces.json`. This file acts as the single source of truth for function signatures, data types, and masking modes:

```json
"my_op": {
    "proto_ref": "ret_reg_2args_reg",
    "datatypes": "all_datatypes",
    "horizontal": false,
    "mask_support": "all_mask"
}
```

Key fields:

- `proto_ref`: References an abstract prototype declared in `generator/helpers_headers/registry_protos.json` (for example `ret_reg_2args_reg` for two register inputs and one register output, `ret_reg_1arg_reg`, `ret_msk_2args_msk`, `ret_i32_1arg_msk`, etc.). If your function introduces an unprecedented signature pattern, declare the new prototype in `registry_protos.json` first.
- `datatypes`: Target datatype alias (`"all_datatypes"`, `"all_float"`, `"all_int"`, `"all_int_uint"`, `"all_64bit"`, `"all_32bit"`, etc.) or an explicit list of types (`["float32", "float64"]`).
- `horizontal`: Boolean flag (`false` for element-wise SIMD operations, `true` for horizontal reductions across lanes).
- `mask_support`: Masking variant support level (`"all_mask"`, `"no_mask"`, `"only_mask"`, `"only_maskz"`, `"only_masks"`, `"mask_and_maskz"`, `"mask_and_masks"`, `"maskz_and_masks"`).
- `cpp_name` (optional): Overrides the C++ wrapper function name if it differs from the C99 function identifier (for example, `andb_k` specifies `"cpp_name": "andb"`).

### Step 2: Categorize the Function (`generator/helpers_headers/registry_categories.json`)

Assign your function to an appropriate functional category (e.g. `arithmetic`, `comparison`, `converts`, `load`, `logic`, `masks`, `pack`, `reduction`, `rounding`, `store`, `trigo`):

```json
"arithmetic": [
    "add",
    "adds",
    "my_op"
]
```

This classification is used by:

- `gen_mipp_docs.py` to organize API reference pages.
- `gen_mipp_tests.py` to structure test suites.
- `cpp_object_generator.py` to organize method categories in the `rvd` and `rvm` object interfaces.

### Step 3: Provide the Scalar Baseline (`generator/helpers_headers/registry_scalar_implems.json`)

MIPP strictly enforces that **all declared functions must provide a scalar reference baseline**. This powers the Level 3 automatic fallback and the test verification engine:

```json
"my_op": [
    {
        "type": "element-wide",
        "datatypes": "all_datatypes",
        "mask_variants": [],
        "implem": [
            "res.r[i] = %!pred_cond!% r0.r[i] + r1.r[i] %!pred_alt!%;"
        ]
    }
]
```

Key fields:

- `type`: `"element-wide"` instructs the generator to automatically synthesize the element-wise iteration loop (`for (size_t i = 0; i < N; i++)`). For non-element-wise operations (such as reductions or custom permutations), specify `"type": "custom"` and provide the full loop body.
- `datatypes`: Supported datatype alias or explicit list.
- `mask_variants`: List of custom handled mask variants, or `[]` for automatic handling.
- `implem`: Array of C code lines for the loop body. The placeholders `%!pred_cond!%` and `%!pred_alt!%` are automatically expanded by the generator to handle masked operations (`_mask`, `_maskz`, `_masks`).
- The generator automatically emits the C99 scalar fallback headers in `include/simd_ext/scalar/c/functions/`.

### Step 4: Add Native Hardware Acceleration (`generator/simd_ext/<isa>/`)

To accelerate your function on a target ISA:

1. **Define the intrinsic template in `generator/simd_ext/<isa>/<isa>_native_templates.json`**:
    ```json
    "arith_2args": {
        "format": "short",
        "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);"
    }
    ```
    Here, Jinja2 placeholders like `{{ isa.prefix }}`, `{{ instr_name }}`, and `{{ isa_dt_par.data_ext }}` are dynamically resolved per architecture and datatype.

2. **Map the function in `generator/simd_ext/<isa>/<isa>_native_implems.json`**:
    ```json
    "my_op": [
        {
            "instr_name": "addq",
            "datatypes": [
                "float32",
                "float64"
            ],
            "template": "arith_2args",
            "if": "defined(__ARM_FEATURE_...)"
        }
    ]
    ```
    - `instr_name`: Architecture-specific intrinsic suffix passed to the template.
    - `datatypes`: Datatype alias or list of datatypes supported natively by this instruction.
    - `template`: Name of the template defined in `<isa>_native_templates.json`.
    - `if` (optional): Preprocessor guard condition for compiler feature checks.

### Step 5: (Optional) Add a Generic Level 2 Emulation (`generator/helpers_headers/generic_emu_*`)

If an ISA lacks a native instruction for a datatype (e.g. 64-bit integer division or unsigned addition), define a portable generic emulation using other MIPP functions via the [Mini-Templating DSL](templating_dsl.md):

1. **Add the algorithmic template in `generator/helpers_headers/generic_emu_templates.json`**:
    ```json
    "my_op": {
        "format": "long",
        "code": [
            "%r<tp>% diff = %sub<tp>%(r0, r1);",
            "return %abs<tp>%(diff);"
        ]
    }
    ```

2. **Register the emulation in `generator/helpers_headers/generic_emu_implems.json`**:
    ```json
    "my_op": [
        {
            "datatypes": "all_uint",
            "template_ref": "tpl_generic_emu.my_op"
        }
    ]
    ```
    The `template_ref` uses namespacing:

    - `tpl_generic_emu.<name>` for standard operations in `generic_emu_templates.json`.
    - `tpl_mask_generic_emu.<name>` for mask operations in `generic_emu_templates_mask.json`.
    - `tpl_horiz_lmul_generic_emu.<name>` for horizontal reductions in `generic_emu_templates_lmulh.json`.

### Step 6: Verify and Regenerate

Run the generator with full static audits enabled:

```bash
cd generator
.venv/bin/python gen_mipp_headers.py --audit all
```

Next, update tests and documentation:

```bash
.venv/bin/python gen_mipp_tests.py
.venv/bin/python gen_mipp_docs.py
```

---

## 2. Adding a New SIMD Extension (ISA)

MIPPv2 features automatic discovery for SIMD extensions: adding a folder to `generator/simd_ext/` automatically registers the new ISA across all generators.

### Step 1: Create the Directory

Create `generator/simd_ext/<new_isa>/`.

### Step 2: Create `<new_isa>_isa.json`

Define the architecture metadata, compiler detection guards, register types, and dependencies:

```json
{
    "name": "myisa",
    "prefix": "_mm_myisa",
    "size": 128,
    "sub_isa": "sse",
    "define": "defined(__MY_ISA__)",
    "header_template": [
        "#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_MYISA_H_",
        "#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_MYISA_H_",
        "#include <my_isa_intrinsics.h>"
    ],
    "datatypes": {
        "float32": {
            "data_ext": "ps",
            "data_ext_logi": "ps",
            "data_ext_msk": "ps",
            "reg": "__m128",
            "msk": "__m128",
            "to_ptr": "float32_t"
        }
    },
    "sw_lmul": [1, 2, 4, 8],
    "hw_lmul": [],
    "mipp_definitions": [
        "#define MIPP_MY_ISA"
    ]
}
```

Key fields:

- `sub_isa`: Declares fallback inheritance. If `myisa` is missing an instruction, it will inherit implementations from its `sub_isa` (e.g. `avx` inherits from `sse`, `avx512` from `avx`).
- `size`: Base hardware vector size in bits (128, 256, 512, etc.).
- `datatypes`: Architecture-specific vector register types (`reg`), mask types (`msk`), and type suffixes (`data_ext`).
- `sw_lmul`: Software vector length multiplier factors supported (`[1, 2, 4, 8]`).

### Step 3: Create Template and Implementation Registries

In your new ISA directory, create:

- `generator/simd_ext/<new_isa>/<new_isa>_native_templates.json`
- `generator/simd_ext/<new_isa>/<new_isa>_native_implems.json`
- (Optional) `<new_isa>_emu_templates.json` and `<new_isa>_emu_implems.json` for ISA-specific Level 1 emulations.

### Step 4: Automatic Discovery & Validation

The generator automatically discovers your new directory:

```bash
cd generator
.venv/bin/python gen_mipp_headers.py --layers myisa
```

The summary table at the end of the generator run will immediately report the Level 0, 1, 2, and 3 distribution for your new ISA.
