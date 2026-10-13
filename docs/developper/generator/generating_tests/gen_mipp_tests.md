# Test Generator (`gen_mipp_tests.py`)

`generator/gen_mipp_tests.py` emits the Catch2 v3 unit-test sources in `tests/src/`. One test file is generated per function and per API, organized by category: `tests/src/<api>/<category>/<function>.{c,cpp}` with `<api>` in `c`, `cpp`, `obj`.

Each test fills input buffers with random values, calls the function under test for the target ISA, and compares every lane against the **scalar reference implementation** (Level 3, generated from `registry_scalar_implems.json`). The same test is instantiated for every supported datatype, LMUL and mask variant.

---

## 1. Source Files

| File | Role |
| :--- | :--- |
| `gen_mipp_tests.py` | Command-line entry point. |
| `helpers_tests/tests_builder.py` | Test engine: loads and validates the JSON inputs, builds one file per function, API and category. |
| `helpers_tests/dialect_adapters.py` | Syntax adapters for the C, C++ functional and C++ object APIs (pure expression formatting). |
| `helpers_tests/domain_resolver.py` | Resolves input domains and mask patterns per datatype, LMUL, mask variant and ISA define. |
| `helpers_tests/tests_specs.json` | Per-function test properties (input domain, tolerance, comparison mode, ...). |
| `helpers_tests/tests_templates.json` | Code templates for headers, test bodies and assertions. |
| `helpers_tests/schemas/` | JSON Schemas for `tests_specs.json` and `tests_templates.json`. |

Both JSON files are validated against their schema at startup; a validation error stops the generator.

---

## 2. Test Specifications (`tests_specs.json`)

The file has two top-level keys:

- `default`: properties applied to every function.
- `functions`: per-function overrides. A function that is not listed is tested with the `default` properties.

Current defaults:

```json
"default": {
    "distribution": "uniform",
    "domain": {},
    "tolerance": { "type": "exact" },
    "comparison": "exact",
    "overflow_check": null,
    "disabled": false,
    "disabled_reason": null,
    "extra_includes": [],
    "nan_inf_skip": false,
    "skip_condition": null,
    "support_obj": true,
    "mask_pattern": "uniform_bool"
}
```

Typical override for a math function with a restricted domain and a tolerance:

```json
"acos": {
    "domain": { "min": -1.0, "max": 1.0 },
    "tolerance": {
        "by_datatype": {
            "float32": { "type": "max_abs_diff", "value": 1e-06 },
            "float64": { "type": "max_abs_diff", "value": 1e-12 }
        }
    },
    "comparison": "tolerance"
}
```

Domains can be refined per datatype (`by_datatype`), per ISA define (`by_define`, e.g. `MIPP_AVX2`) and per mask kind (`unmasked`, ...). The authoritative list of keys is `generator/helpers_tests/schemas/specs_schema.json`.

---

## 3. Usage

From `generator/`, with the virtual environment activated (see `generator/README.md`):

```bash
./gen_mipp_tests.py [{c,cpp,obj}] [OPTIONS]
```

| Option | Default | Description |
| :--- | :--- | :--- |
| `{c,cpp,obj}` | all three | API for which tests are generated. |
| `-N`, `--num-iterations` | `10` | Number of random iterations per test. |
| `--lmul` | `0 1 2 4 8` | LMUL values to generate. |
| `--ldiv` / `--no-ldiv` | `2` | Half-vector (`d2`) tests, or none. |
| `--mask-kind` | `unmasked mask maskz masks` | Mask variants to generate. |
| `--header-type {function,full}` | `function` | Include one header per function, or the global header. |
| `--no-clean` | off | Keep previously generated files. |
| `--audit` | `all` | Audits on `tests_specs.json` (see [Static Audits](../../audits_and_verification.md)). |

`--skip-lmul-cpp` and `--skip-mask-cpp` are deprecated and have no effect.

---

## 4. Building and Running the Tests

Headers and test sources must be generated first. The tests require Catch2 v3:

```bash
cd tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_UNITY_BUILD=ON \
      -DCMAKE_CXX_FLAGS="-march=native"
cmake --build build -j4
./build/bin/run-tests
```

- `-DCMAKE_UNITY_BUILD=ON` groups translation units and reduces build time substantially; precompiled headers are enabled by `tests/CMakeLists.txt`.
- The `N_ITER` environment variable overrides the number of random iterations at run time (`N_ITER=100 ./build/bin/run-tests`).

See `tests/README.md` for the complete set of build options.