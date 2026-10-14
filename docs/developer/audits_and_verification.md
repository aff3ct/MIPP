# Static Audits & Database Verification

MIPPv2 validates its declarative JSON database before emitting any code. Two kinds of checks coexist:

- **Validation checks** are always active. They stop the generator with an error (exit code 1).
- **Audits** are selected with `--audit`. They report warnings and never stop generation.

The header-generator checks live in `generator/helpers_headers/input_validation.py`; the test-generator checks live in `generator/helpers_tests/tests_builder.py`.

---

## 1. Validation Checks (Always Active, Blocking)

| Check | Files |
| :--- | :--- |
| JSON Schema validation (`generator/helpers_headers/schemas/`, `generator/helpers_tests/schemas/`) | Every registry, ISA descriptor, template and implementation file, `tests_specs.json`, `tests_templates.json` |
| Every `proto_ref` exists in `registry_protos.json` | `registry_interfaces.json` |
| A function belongs to at most one category, and every categorized function is declared | `registry_categories.json` |
| Every declared function has a scalar implementation, for exactly the declared datatypes | `registry_scalar_implems.json` |
| Every implemented function and emulation dependency is declared; implemented datatypes are supported by both the interface and the ISA descriptor | `<isa>_native_implems.json`, `<isa>_emu_implems.json` |
| Every `template` / `template_ref` resolves to an existing template | `*_implems.json` |
| No dependency cycle between emulated functions | `<isa>_emu_implems.json` |
| ISA descriptor consistency: `sub_isa` exists; `-2` in `sw_lmul` requires `sw_ldiv_type: sub_isa`, which requires `sub_isa` and a `size` twice the size of `sub_isa`; at most one default `info_names` entry, in last position | `<isa>_isa.json` |
| A mandatory file is missing for an ISA (`<isa>_isa.json`, `<isa>_native_implems.json`, `<isa>_native_templates.json`) | `simd_ext/<isa>/` |

---

## 2. Header Generator Audits (`gen_mipp_headers.py --audit`)

```bash
./gen_mipp_headers.py --audit all          # default
./gen_mipp_headers.py --audit levels dead-code
./gen_mipp_headers.py --audit none
```

### 2.1. `levels`: Implementation Level Placement

For each ISA, the code of every template is inspected heuristically to infer its level:

- a single intrinsic call and no call to other MIPP functions: **Level 0**;
- intrinsics combined with other intrinsics or MIPP functions: **Level 1**;
- MIPP functions only: **Level 2**.

A warning is emitted when the inferred level does not match the file the entry lives in (`<isa>_native_implems.json` is expected to be Level 0, `<isa>_emu_implems.json` Level 1). Intentional exceptions can be marked on the entry with `"skip_audit_level": true` and a `"skip_audit_level_reason"`.

### 2.2. `dead-code`: Unreferenced or Unreachable Entries

- Native and ISA-specific emulation templates that no implementation entry references.
- Generic templates (`tpl_generic_emu`, `tpl_mask_generic_emu`, `tpl_horiz_lmul_generic_emu`) that no generic implementation entry references.
- Generic emulation entries that can never be selected because every targeted datatype is already implemented natively on every candidate ISA.
- Scalar implementations of functions that are not declared in `registry_interfaces.json`.
- Functions declared in `registry_interfaces.json` but not assigned to any category.

### 2.3. `duplicates`: Overlapping Implementations

Reports, for a given `(function, datatype, mask variant)`, two entries at the same level whose preprocessor conditions (`if`) are not mutually exclusive, or overlapping entries across levels.

### 2.4. `json-structure`: Repository Hygiene

- Top-level keys of every JSON file must be sorted lexicographically.
- Implementation files must not contain empty lists.

---

## 3. Test Generator Audits (`gen_mipp_tests.py --audit`)

```bash
./gen_mipp_tests.py --audit all            # default
```

The options are `coverage`, `redundancy`, `consistency`, `all` and `none`. In the current implementation, only `consistency` performs a check: it warns when `tests_specs.json` describes a function that is not declared in `registry_interfaces.json`. `coverage` and `redundancy` are accepted but not implemented yet.

---

## 4. Continuous Integration

- **GitLab CI** (`.gitlab-ci.yml`) is the main verification pipeline: it generates the headers (fine granularity, all ISAs including SVE) and the tests, then builds and runs the unit tests and the examples on a matrix of target architectures and compilers.
- **GitHub Actions** (`.github/workflows/ci.yml`) generates headers, tests and documentation pages, deploys the documentation to GitHub Pages (`mkdocs build --strict`), and, on `v*` tags, attaches the header archives to the GitHub release.

Since audits only emit warnings, they do not fail a pipeline. Validation checks ([§1](#1-validation-checks-always-active-blocking)) do.
