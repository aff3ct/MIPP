# Core Registries (`registry_*.json`)

The declarative database in `generator/helpers_headers/` defines canonical function prototypes, signatures, categories, and reference implementations across several JSON files:

- `registry_protos.json`: Generic function prototype templates.
- `registry_categories.json`: Functional groupings (arithmetic, logic, comparison, etc.).
- `registry_interfaces.json`: Canonical function definitions and signatures.
- `registry_scalar_implems.json`: Scalar reference fallback implementations (Level 3).

---

## 1. `registry_protos.json`

Defines abstract function prototypes used across all MIPP generators.

Example:

```json
"ret_reg_2args_reg": {
    "ret": {
        "type": "reg",
        "fixeddatatype": false,
        "charac": "WO"
    },
    "args": [
        {
            "type": "reg",
            "fixeddatatype": false,
            "charac": "RO"
        },
        {
            "type": "reg",
            "fixeddatatype": false,
            "charac": "RO"
        }
    ]
}
```

Field values:

- `type`:
    - `reg`: Vector value register (`rvd`)
    - `msk`: Vector mask register (`rvm`)
    - `val`: Scalar value
    - `ptr`: Memory pointer
    - `Nele`: Array of scalar values
- `charac`: `RO` (Read-Only) or `WO` (Write-Only).
- `fixeddatatype`: `false` if polymorphic across vector types, or an explicit type name (e.g. `"int32"`).

---

## 2. `registry_interfaces.json`

The central contract of all MIPP functions. Each entry specifies:

```json
"add": {
    "proto_ref": "ret_reg_2args_reg",
    "datatypes": "all_datatypes",
    "horizontal": false,
    "mask_support": "all_mask"
}
```

- `proto_ref`: References a prototype template from `registry_protos.json`.
- `datatypes`: Supported datatypes (`"all_datatypes"`, `"all_float"`, `"all_int"`, `"all_int_uint"`, etc.).
- `horizontal`: `false` for element-wise SIMD operations, `true` for horizontal reductions.
- `mask_support`: `"all_mask"`, `"no_mask"`, `"only_mask"`, `"only_maskz"`, `"only_masks"`, `"mask_and_maskz"`, `"mask_and_masks"`, `"maskz_and_masks"`.

---

## 3. `registry_categories.json`

Maps categories to function names:

```json
{
    "arithmetic": ["add", "adds", "sub", "subs", "mul", "div"],
    "comparison": ["cmpeq", "cmpneq", "cmple", "cmplt", "cmpge", "cmpgt"]
}
```
