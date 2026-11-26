# Add an ISA

This tutorial creates a new target, `myisa`, a fictional 128-bit instruction set. No Python file is edited: the generators discover the ISAs from the directories of `generator/simd_ext/`. All paths are relative to `generator/`.

| Step | File (in `simd_ext/myisa/`) | Required |
| :--- | :--- | :---: |
| [1. Create the directory](#step-1-create-the-directory) | | Yes |
| [2. Describe the ISA](#step-2-describe-the-isa) | `myisa_isa.json` | Yes |
| [3. Generate](#step-3-generate) | none | Yes |
| [4. Implement the functions](#step-4-implement-the-functions) | `myisa_native_*.json`, `myisa_emu_*.json`, `myisa_ldiv_mask.json`, `myisa_sw_lmul.json` | Yes / No |
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
| `myisa_ldiv_mask.json` | No | Half-vector (`d2`) specializations and the functions that change the LMUL ([step 4](#half-vectors-and-functions-that-change-the-lmul)). |
| `myisa_sw_lmul.json` | No | `wcvt` (`m1` → `m2`) and `ncvt` (`m2` → `m1`) written by the ISA for its software LMUL registers ([step 4](#half-vectors-and-functions-that-change-the-lmul)). |
| `myisa_explorer.json` | No | Metadata for the API Explorer ([step 5](#step-5-describe-the-isa-for-the-api-explorer)). |

Without one of the three mandatory files, the generator stops with `FileNotFoundError: Missing mandatory configuration files`.

The fastest start is to copy the directory of the closest ISA, rename the files and change the `name`, `define`, `info_names` and `header_template` (include guard) fields of the descriptor, and the `name` of `myisa_explorer.json`. A copy of `sse/` renamed this way generates a working `myisa` target, identical to SSE.

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
        },
        ...
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
    "sw_ldiv_type": "mask",
    "sw_lmul": [1, 2, 4, 8, -2]
}
```

The `...` stands for the nine other datatypes: the descriptor must have an entry for each of the 10 datatypes (`float64`, `float32`, `int64`, `int32`, `int16`, `int8`, `uint64`, `uint32`, `uint16`, `uint8`), otherwise the generator stops with a `KeyError` when it renders the templates. See `sse/sse_isa.json` for a complete descriptor.

| Field | Use |
| :--- | :--- |
| `name` | ISA name, equal to the directory name. |
| `define` | Compiler condition that selects the ISA, written in `include/mipp/internal/interfaces/c/common.h`. |
| `datatypes` | One entry per datatype, for all 10 datatypes: register type `reg`, mask type `msk`, intrinsic suffixes `data_ext*`, pointer type `to_ptr`. A datatype without native instructions still needs an entry (its register type); its functions are then generated at <span class="mipp-isa-badge lvl-2">L2</span> or <span class="mipp-isa-badge lvl-3">L3</span>. The templates read these fields as `isa_dt_par.*`. |
| `prefix` | Intrinsic prefix, read by the templates as `isa.prefix`. |
| `size` | Register width in bits. |
| `sw_lmul`, `hw_lmul` | LMUL values emulated in software (several registers) or supported by the hardware. `-2` enables half-vectors (`d2`); all the current targets have them. |
| `header_template` | First lines of the generated ISA header: include guard and intrinsics header. |
| `mipp_definitions` | Macros defined for the users when the ISA is selected (`MIPP_64BIT`, `MIPP_BW`, ...). |
| `info_names` | Optional. Name printed by `mipp_info()`: the first entry whose `if` condition holds; the entry without `if` is the default and must be last. Without this field, the upper-case `name` is printed. |
| `sw_ldiv_type` | How the half-vectors of `sw_lmul` are built: `"mask"` (the LMUL = 1 register, upper lanes ignored: SSE, NEON, SVE) or `"sub_isa"` (a register of the parent ISA: AVX, AVX-512). |
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

With empty implementation files, every function already exists on `myisa` and the generated headers compile. The summary table printed at the end shows the distribution of the levels for the new ISA: more than half of the functions are at <span class="mipp-isa-badge lvl-3">L3</span>, and most of the others at <span class="mipp-isa-badge lvl-2">L2</span> (mostly the versions of the other LMULs, built on the LMUL 1 ones). At LMUL 1 and without mask, almost every function is at <span class="mipp-isa-badge lvl-3">L3</span> ([Step 4](#which-functions-first)).

---

## Step 4: Implement the Functions

Add the <span class="mipp-isa-badge lvl-0">L0</span> entries, then the <span class="mipp-isa-badge lvl-1">L1</span> ones where needed, as described in [Add an Implementation](add_implementation.md).

### Which functions first

A generic emulation (<span class="mipp-isa-badge lvl-2">L2</span>) is written with other MIPP functions, and it is at <span class="mipp-isa-badge lvl-3">L3</span> as long as one of them is ([Effective Level](../internals/code_generation.md#44-effective-level)). With empty files, the emulations have nothing to stand on: almost every function is at <span class="mipp-isa-badge lvl-3">L3</span>. A core of functions is the base of all the others: once it is written, every other function is at <span class="mipp-isa-badge lvl-2">L2</span> or better, and can then be improved one by one.

The table below is computed by the generator. It simulates an ISA whose implementation files are empty with the candidate resolver, gives each function of the core a native implementation for all its datatypes, then counts, for each function of the core, what goes back to <span class="mipp-isa-badge lvl-3">L3</span> when it alone is missing:

- **Functions**: the functions at <span class="mipp-isa-badge lvl-3">L3</span> without it (unmasked);
- **Scalar forms**: the same for the [scalar forms](../../user/scalar_forms.md) (`add_vs`, ...);
- **Masked variants**: the other functions whose masked variants go back to <span class="mipp-isa-badge lvl-3">L3</span>. This column depends on the masks of the ISA: the table uses the full-vector masks of NEON, and with the masks of AVX-512 and RVV, `cast` and `andb` hold back far fewer masked variants.

--8<-- "docs/includes/generated/isa_bootstrap.md"

In practice:

- Write the first rows first: `set1`, `cast` (a reinterpretation, usually without instruction), `select`, the arithmetic, the bitwise operations, the comparisons, `loadu` and `storeu`. They bring most of the library to <span class="mipp-isa-badge lvl-2">L2</span>.
- `mul` and `div` have no generic emulation, and many emulations call them (math and complex functions): until they are written, these functions stay at <span class="mipp-isa-badge lvl-3">L3</span>, whatever else is written.
- The functions that no other function needs (the reductions, the aligned `load` and `store`, `scatter`, several rearrangements) can wait: each one only improves itself.

The counts assume an implementation for every datatype. A function written for some datatypes only (no 64-bit multiplication, for instance) holds back its dependents for the other datatypes.

### Audits

Watch the audits at each generation: they report entries placed at the wrong level, dead entries and overlapping conditions ([Audits & Validation](../reference/audits.md)).

### Half-vectors and functions that change the LMUL

`lo`, `hi`, `combine`, `wcvt` and `ncvt` return a register of another LMUL than their arguments (`ret.lmul` in `registry_protos.json`). Their templates, and the half-vector specializations, go to `<isa>_ldiv_mask.json` ([Half-Vector Templates](../reference/registries/ldiv_mask.md)). What an ISA must provide depends on its descriptor:

- **LMUL ≥ 2** (`sw_lmul` without a hardware group): nothing to write. `lo` and `hi` return one half of the register group, `combine` joins two registers, and `wcvt` / `ncvt` apply the conversion to each half. When the ISA converts a whole register into two (or two into one) better than through `lo` / `hi` and `combine`, write `wcvt` (`m1` → `m2`, the result has the registers `res.lo` and `res.hi`) and `ncvt` (`m2` → `m1`, the argument has `vd0.lo` and `vd0.hi`) in `<isa>_sw_lmul.json` ([Software LMUL Templates](../reference/registries/sw_lmul.md)); see `simd_ext/sve/sve_sw_lmul.json`.
- **Between `m1` and `d2`** with `"sw_ldiv_type": "mask"`: add `lo` and `hi` (`m1` to `d2`) and `combine` (`d2` to `m1`) to `<isa>_ldiv_mask.json`, with the intrinsics of the ISA and, if needed, an `if` condition (`defined(__SSE4_1__)`). Without an entry, or when the condition does not hold, the generic version of `generic_ldiv_mask.json` is used (level L3, through a buffer). `wcvt` (`d2` to `m1`) and `ncvt` (`m1` to `d2`) are templates of the generic file that an ISA can override the same way.
- **Between `m1` and `d2`** with `"sw_ldiv_type": "sub_isa"` (the `d2` is a register of the parent ISA, e.g. an SSE register for AVX): the generic file does not apply, since the two registers have different types. Write all of `lo`, `hi`, `combine`, `lo_k`, `hi_k`, `combine_k`, `wcvt` and `ncvt` in `<isa>_ldiv_mask.json` (see `simd_ext/avx/avx_ldiv_mask.json`); the generator reports an error if a template is missing. The fallbacks of `wcvt` / `ncvt` go through a buffer (level L3). Without a `<isa>_ldiv_mask.json`, nothing is provided between `m1` and `d2`.
- **Hardware groups** (RVV: `-2` and several LMULs in `hw_lmul`): one template per function in `<isa>_ldiv_mask.json` (see `simd_ext/rvv/rvv_ldiv_mask.json`) is rendered for every pair of consecutive hardware LMULs (`d2` to `m1`, `m1` to `m2`, ...). The template reads `ctx.lmul_in`, `ctx.lmul_out` and `ctx.ext(dt, lmul)` (the `data_ext` of the datatype at that LMUL, such as `i32mf2`) and branches on them. The masks (`lo_k`, `hi_k`, `combine_k`) go through a vector: the mask is turned into a vector of `-1` / `0` (`vmerge`), the data operation is applied, and the result is turned back into a mask (`vmsne`); the 64-bit `d2` masks, which are C arrays, are filled or read with `vse64` / `vle64`. The tests are not generated for the functions that are not provided (see [Test Generator](../internals/test_generator.md)).

The generated test of each function is protected by `#if defined(MIPP_<ISA>)` for the ISAs that provide it, so that adding an entry to `<isa>_ldiv_mask.json` is enough to have it tested.

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
    "compiler": { "id": "cg142", "arch": "x86", "label": "x86-64 GCC", "base_flags": "-O3" },
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

The existing targets and their flags are listed in [Targets and Flags](../process/ci.md#11-targets-and-flags); the jobs are described in [Continuous Integration](../process/ci.md).
