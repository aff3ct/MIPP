# Documentation Generator (`gen_mipp_docs.py`)

`generator/gen_mipp_docs.py` generates the **Function Support** (`docs/funcs_support/`) and **Hardware Support** (`docs/isas_support/`) sections of the documentation, as well as the data file of the **API Explorer**.

Instead of maintaining documentation tables by hand, they are synthesized directly from:

- `generator/helpers_headers/registry_interfaces.json` (signatures and supported datatypes)
- `generator/helpers_headers/registry_categories.json` (functional groupings)
- `generator/helpers_headers/funcs_docs.json` (descriptions and formulas)
- `generator/simd_ext/<isa>/<isa>_native_implems.json` and `<isa>_emu_implems.json` (hardware support)
- `generator/helpers_headers/generic_emu_implems*.json` (Level 2 coverage)
- `generator/helpers_tests/tests_specs.json` and `generator/simd_ext/<isa>/<isa>_explorer.json` (API Explorer only)

## Running the Documentation Generator

From `generator/`, with the virtual environment activated (see `generator/README.md`):

```bash
./gen_mipp_docs.py
```

The script has no command-line options. It updates:

- `docs/funcs_support/`: one page per function, with C and C++ prototype tabs, parameter tables and support matrices.
- `docs/isas_support/`: one page per ISA, with the instruction mappings and the implementation level per datatype.
- `docs/assets/data/mipp_api_index.json`: the API Explorer index, produced by `gen_mipp_api_data.py` (called by `gen_mipp_docs.py`). It resolves the effective implementation level of every function with the same candidate resolver as the header generator.

The site itself is then built with MkDocs from the repository root:

```bash
pip install -r docs/requirements.txt
mkdocs build --strict
```