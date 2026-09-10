# Static Audits & Database Verification

To ensure that the declarative JSON database remains clean, deterministic, and free of bugs as contributors add new functions and architectures, MIPPv2 incorporates a comprehensive **static audit engine** (`generator/helpers_headers/input_validation.py`).

---

## 1. The Need for Static Audits

In large-scale SIMD wrapper libraries:

- **Dead Code**: An emulation template might be defined for a datatype that is already natively supported by hardware.
- **Level Collisions / Duplicates**: A function might accidentally have conflicting definitions across multiple tiers for the same `(ISA, Datatype, MaskVariant)` tuple.
- **Divergence**: A function might be defined in `registry_interfaces.json` but lack a scalar reference baseline in `registry_scalar_implems.json`, breaking the test engine.

MIPPv2 runs static verification passes **before code generation begins**, catching errors at generator runtime rather than producing broken headers.

---

## 2. Active Audit Passes

You can control which audits are executed via the `--audit` argument:

```bash
cd generator
.venv/bin/python gen_mipp_headers.py --audit all
```

Options: `levels`, `dead-code`, `duplicates`, `json-structure`, `all`, `none`.

### 2.1. Dead-Code Audit (`dead-code`)

Scans all generic and specific emulation templates:

- Compares each template's targeted datatypes against the native implementation registry.
- If all targeted datatypes are already implemented natively (Level 0), the generator raises a warning identifying the unneeded template as dead code.

### 2.2. Duplicate & Collision Audit (`duplicates`)

Verifies that no two templates compete ambiguously for the same function and datatype within the same implementation tier.

### 2.3. Level Discrepancy Audit (`levels`)

Checks that functions assigned to Level 1 (specific emulation) or Level 2 (generic emulation) do not conflict with Level 0 hardware intrinsics.

### 2.4. JSON Schema & Formatting Integrity (`json-structure`)

Enforces consistent repository hygiene:

- Checks that JSON dictionary keys are consistently sorted.
- Detects stray empty lists or null placeholders that could lead to subtle parsing discrepancies.

---

## 3. Continuous Integration Verification

In the CI pipeline (`.github/workflows/ci.yml`), static audits run automatically during the `generation` stage. If any critical integrity check fails, the job fails immediately, preventing invalid code from being released.
