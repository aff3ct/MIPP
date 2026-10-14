# Static Audits & Database Verification

MIPPv2 validates its declarative JSON database before emitting any code. Two kinds of checks coexist:

- **Validation checks** are always active. They stop the generator with an error (exit code 1).
- **Audits** are selected with `--audit`. They report warnings and never stop generation.

The header-generator checks live in `generator/helpers_headers/input_validation.py`; the test-generator checks live in `generator/helpers_tests/tests_builder.py`.

---

## 1. Validation Checks (Always Active, Blocking)

| File | Checks |
| :--- | :--- |
| All inputs | Valid against its JSON Schema (`generator/helpers_headers/schemas/`, `generator/helpers_tests/schemas/`, documented in [Registries](registries/index.md)): registries, ISA descriptors, templates and implementation files, `tests_specs.json`, `tests_templates.json`. |
| `registry_interfaces.json` | Every `proto_ref` exists in `registry_protos.json`. |
| `registry_categories.json` | A function belongs to at most one category.<br>Every categorized function is declared. |
| `registry_scalar_implems.json` | Every declared function has a scalar implementation, for exactly its declared datatypes. |
| `<isa>_native_implems.json`<br>`<isa>_emu_implems.json` | Every implemented function and emulation dependency is declared.<br>The implemented datatypes are supported by the interface and by the ISA descriptor. |
| `*_implems.json` | Every `template` / `template_ref` resolves to an existing template. |
| `<isa>_emu_implems.json` | No dependency cycle between emulated functions. |
| `<isa>_isa.json` | `sub_isa` exists.<br>`-2` in `sw_lmul` requires `sw_ldiv_type: sub_isa`.<br>`sw_ldiv_type: sub_isa` requires `sub_isa` and a `size` twice the size of `sub_isa`.<br>At most one default `info_names` entry, in last position. |
| `simd_ext/<isa>/` | Contains `<isa>_isa.json`, `<isa>_native_implems.json` and `<isa>_native_templates.json`. |

---

## 2. Header Generator Audits (`gen_mipp_headers.py --audit`)

```bash
./gen_mipp_headers.py --audit all          # default
./gen_mipp_headers.py --audit levels dead-code
./gen_mipp_headers.py --audit none
```

### 2.1. `levels`: Implementation Level Placement

For each ISA, the code of every template is inspected heuristically to infer its level:

- a single intrinsic call and no call to other MIPP functions: <span class="mipp-isa-badge lvl-0">L0</span>;
- intrinsics combined with other intrinsics or MIPP functions: <span class="mipp-isa-badge lvl-1">L1</span>;
- MIPP functions only: <span class="mipp-isa-badge lvl-2">L2</span>.

A warning is emitted when the inferred level does not match the file the entry lives in (`<isa>_native_implems.json` is expected to be <span class="mipp-isa-badge lvl-0">L0</span>, `<isa>_emu_implems.json` <span class="mipp-isa-badge lvl-1">L1</span>). Intentional exceptions can be marked on the entry with `"skip_audit_level": true` and a `"skip_audit_level_reason"`.

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

Both CI pipelines run the generators with their default audits ([Continuous Integration](../process/ci.md)). Since audits only emit warnings, they do not fail a pipeline. Validation checks ([§1](#1-validation-checks-always-active-blocking)) do.
