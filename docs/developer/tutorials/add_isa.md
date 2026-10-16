# Add an ISA

This tutorial creates a new target, `myisa`, a fictional 128-bit instruction set. No Python file is edited: the generators discover the ISAs from the directories of `generator/simd_ext/`. All paths are relative to `generator/`.

| Step | File (in `simd_ext/myisa/`) | Required |
| :--- | :--- | :---: |
| [1. Create the directory](#step-1-create-the-directory) | | Yes |
| [2. Describe the ISA](#step-2-describe-the-isa) | `myisa_isa.json` | Yes |
| [3. Generate](#step-3-generate) | none | Yes |
| [4. Implement the functions](#step-4-implement-the-functions) | `myisa_native_*.json`, `myisa_emu_*.json` | Yes / No |
| [5. Describe the ISA for the API Explorer](#step-5-describe-the-isa-for-the-api-explorer) | `myisa_explorer.json` | No |
| [6. Test and add to the CI](#step-6-test-and-add-to-the-ci) | `.gitlab-ci.yml`, `.github/workflows/ci.yml` | Yes |

---

## Step 1: Create the Directory

Create `simd_ext/myisa/`. The directory name is the ISA name. It holds:

| File | Required | Content |
| :--- | :---: | :--- |
| `myisa_isa.json` | Yes | ISA descriptor: registers, compiler condition, LMUL support ([step 2](#step-2-describe-the-isa)). |
| `myisa_native_templates.json` | Yes | <span class="mipp-isa-badge lvl-0">L0</span> templates (may be `{}` at first). |
| `myisa_native_implems.json` | Yes | <span class="mipp-isa-badge lvl-0">L0</span> entries (may be `{}` at first). |
| `myisa_emu_templates.json`, `myisa_emu_implems.json` | No | <span class="mipp-isa-badge lvl-1">L1</span> templates and entries. |
| `myisa_explorer.json` | No | Metadata for the API Explorer ([step 5](#step-5-describe-the-isa-for-the-api-explorer)). |

Without one of the three mandatory files, the generator stops with `FileNotFoundError: Missing mandatory configuration files`.

The fastest start is to copy the directory of the closest ISA, rename the files and change the `name`, `define` and `info_names` fields of the descriptor. A copy of `sse/` renamed this way generates a working `myisa` target, identical to SSE.

---

## Step 2: Describe the ISA

`myisa_isa.json`:

```json
{
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
    "define": "defined(__MY_ISA__)",
    "header_template": [
        "#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_MYISA_H_",
        "#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_MYISA_H_",
        "#include <my_isa_intrinsics.h>"
    ],
    "hw_lmul": [],
    "info_names": [
        { "if": "defined(__MY_ISA_V2__)", "name": "My ISA v2" },
        { "name": "My ISA" }
    ],
    "mipp_definitions": [
        "#define MIPP_64BIT"
    ],
    "name": "myisa",
    "prefix": "_mm_myisa",
    "size": 128,
    "sw_lmul": [1, 2, 4, 8]
}
```

| Field | Use |
| :--- | :--- |
| `name` | ISA name, equal to the directory name. |
| `define` | Compiler condition that selects the ISA, written in `include/mipp/internal/interfaces/c/common.h`. |
| `datatypes` | One entry per datatype the ISA supports natively: register type `reg`, mask type `msk`, intrinsic suffixes `data_ext*`, pointer type `to_ptr`. The other datatypes are still generated, at <span class="mipp-isa-badge lvl-2">L2</span> or <span class="mipp-isa-badge lvl-3">L3</span>. The templates read these fields as `isa_dt_par.*`. |
| `prefix` | Intrinsic prefix, read by the templates as `isa.prefix`. |
| `size` | Register width in bits. |
| `sw_lmul`, `hw_lmul` | LMUL values emulated in software (several registers) or supported by the hardware. `-2` enables half-vectors (`d2`). |
| `header_template` | First lines of the generated ISA header: include guard and intrinsics header. |
| `mipp_definitions` | Macros defined for the users when the ISA is selected (`MIPP_64BIT`, `MIPP_BW`, ...). |
| `info_names` | Optional. Name printed by `mipp_info()`: the first entry whose `if` condition holds; the entry without `if` is the default and must be last. Without this field, the upper-case `name` is printed. |
| `sub_isa` | Optional. Parent ISA: the derived ISA is tested before its parent, and `--simd-ext` pulls in the parent. With `"sw_ldiv_type": "sub_isa"`, the half-vectors use the parent's registers (AVX `d2` uses SSE registers). With `"sw_ldiv_type": "mask"` and `-2` in `sw_lmul`, no parent is needed: the half-vectors reuse the LMUL = 1 register and ignore the upper lanes (optional per-ISA optimizations in `<isa>_ldiv_mask.json`). |

The other fields (hardware masks, scalable layouts, ...) are described in [ISA Descriptor](../reference/registries/isa.md). The descriptor is validated against `helpers_headers/schemas/isa_schema.json`; the cross-field rules (existing `sub_isa`, `-2` and `sw_ldiv_type`, default `info_names` entry) stop the generator on the first violation.

---

## Step 3: Generate

```bash
./gen_mipp_headers.py --simd-ext myisa
```

`--simd-ext` restricts the generation to the listed ISAs, plus their `sub_isa` chain and the scalar target. The generator derives from the new directory:

- the `myisa` layer and the `--layers myisa` value;
- the detection block in `common.h`:
  ```c
  #elif defined(__MY_ISA__)
  #define MIPP_MYISA
  ```
  followed by the `mipp_definitions`;
- the `ISA::MYISA` value of the C++ `mipp::ISA` enum, and `DEFAULT_ISA == ISA::MYISA` when the ISA is selected;
- the `mipp_info()` report (`My ISA`).

The `mipp::ISA` enum lists every directory of `simd_ext/`, whatever the `--simd-ext` value.

With empty implementation files, every function already exists on `myisa` and the generated headers compile: about three quarters of the functions are at <span class="mipp-isa-badge lvl-3">L3</span>, the others at <span class="mipp-isa-badge lvl-2">L2</span>. The summary table printed at the end shows the distribution of the levels for the new ISA.

---

## Step 4: Implement the Functions

Add the <span class="mipp-isa-badge lvl-0">L0</span> entries, then the <span class="mipp-isa-badge lvl-1">L1</span> ones where needed, as described in [Add an Implementation](add_implementation.md). Start with the functions the generic templates call most: loads and stores, `set1`, `set0`, arithmetic, comparisons, `select`, bitwise operations, `max` and `min`. Each one turns many <span class="mipp-isa-badge lvl-3">L3</span> functions into <span class="mipp-isa-badge lvl-2">L2</span> at once.

Watch the audits at each generation: they report entries placed at the wrong level, dead entries and overlapping conditions ([Audits & Validation](../reference/audits.md)).

---

## Step 5: Describe the ISA for the API Explorer

`myisa_explorer.json` is read by `gen_mipp_api_data.py` and validated against `helpers_headers/schemas/explorer_isa_schema.json`. It gives the API Explorer the display name and description of the ISA, its Compiler Explorer settings and the extensions the user can toggle. Example from `sse/sse_explorer.json`:

```json
{
    "$schema": "../../helpers_headers/schemas/explorer_isa_schema.json",
    "name": "sse",
    "display_name": "SSE",
    "description": "Streaming SIMD Extensions (x86 / x86-64 128-bit vector extensions)",
    "order": 10,
    "headers": ["<immintrin.h>"],
    "compiler": { "id": "g142", "arch": "x86", "label": "x86-64 GCC", "base_flags": "-O3" },
    "features": {
        "mode": "hierarchy",
        "default": "SSE4.2",
        "items": [
            { "id": "SSE2", "label": "SSE2", "define": "__SSE2__", "flag": "-msse2", "default": true, "locked": false, "description": "Streaming SIMD Extensions 2" }
        ]
    }
}
```

`compiler.id` is a Compiler Explorer compiler identifier; `features` lists the extensions the user can toggle, with their macro and compiler flag. All the fields are described in [Explorer Metadata](../reference/registries/explorer_isa.md).

---

## Step 6: Test and Add to the CI

Generate the tests, then build and run them with the compiler flags of the new target (see [Setup](../setup.md#4-build-and-run-the-unit-tests) and, without the hardware, [Testing Other Targets](../setup.md#5-testing-other-targets)).

Then add the target to the CI:

- `.gitlab-ci.yml`:
    - add `myisa` to the `--simd-ext` list of the `generation-headers` job;
    - add an architecture name (e.g. `myisa-v1`) to the `ARCH` list of `.matrix-linux-common`, and a rule in `.build-common` that maps it to the compiler flags (`SIMD_EXT: "-mmyisa"`);
    - the build jobs run in the image `registry.gitlab.com/aff3ct/aff3ct/mipp_linux:<compiler>_<arch>` on a runner tagged with the architecture name: both must exist;
- `.github/workflows/ci.yml`: add `myisa` to the `--simd-ext` list of the generation step, so that the released headers include the new target.

The existing targets and their flags are listed in [CI Targets and Flags](../setup.md#51-ci-targets-and-flags); the jobs are described in [Continuous Integration](../process/ci.md).
