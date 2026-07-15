# Code Generation Sub-Modules (`codegen`)

This directory contains the core implementation of the MIPP C++ code generator, structured into distinct modules to separate concerns and improve maintainability.

---

## File Overview

### 1. [`__init__.py`](file:///Users/adrien/workspace/mipp_dev/mipp/generator/helpers_headers/codegen/__init__.py)
- **Role**: Package initializer.
- **Details**: Defines the `codegen` directory as a Python package.

### 2. [`implem_tracker.py`](file:///Users/adrien/workspace/mipp_dev/mipp/generator/helpers_headers/codegen/implem_tracker.py)
- **Role**: Implementation status and preprocessor guard tracking.
- **Details**:
  - Manages the `implem_status` database, which tracks what combinations of functions, datatypes, and masks have been generated.
  - Avoids duplicate declarations or definition collisions.
  - Builds, combines, and simplifies `#if`/`#endif` preprocessor conditions (e.g. `_build_prev_exclusion_ifdef`, `_combine_current_ifdefs`).

### 3. [`emit_helpers.py`](file:///Users/adrien/workspace/mipp_dev/mipp/generator/helpers_headers/codegen/emit_helpers.py)
- **Role**: Code formatting and text writing.
- **Details**:
  - Handles writing of function signatures (prototypes) and formatting function bodies.
  - Wraps generated functions in the appropriate `#ifdef` wrappers.
  - Generates specialized AVX `ldiv` (division by 2) structures and preprocessor macros (`_gen_ldiv_structs_avx`, `_gen_ldiv_defines_avx`).

### 4. [`candidate_resolver.py`](file:///Users/adrien/workspace/mipp_dev/mipp/generator/helpers_headers/codegen/candidate_resolver.py)
- **Role**: Dependency solving and fallback resolution.
- **Details**:
  - Core solver (`_resolve_and_emit_missing_functions`) that iterates through all missing functions and resolves their dependencies.
  - Renders instruction Jinja2 templates.
  - Generates **Level 3** scalar fallbacks (`_gen_c_auto_scalar_fallback_one`) that redirect vector calls to scalar implementations via memory copying (`memcpy`).
  - Generates **Level 4** panic stubs (`_missing_emit_stub`) for unimplemented datatypes.

### 5. [`lmul_orchestrator.py`](file:///Users/adrien/workspace/mipp_dev/mipp/generator/helpers_headers/codegen/lmul_orchestrator.py)
- **Role**: SIMD Register grouping and division orchestration (LMUL/LDIV).
- **Details**:
  - Orchestrates loop generation for architectures with hardware-configurable register widths (primarily RISC-V Vector LMUL `m1`, `m2`, `m4`, `m8` and fractional `mf2`, `mf4`, `mf8`).
  - Handles writing of horizontal/reduction wrappers (`gen_c_horiz_lmul`).
  - Generates `ldiv` structures for splitting vectors into smaller widths.
  - Generates the standard C interface function definitions for RVV (`gen_c_functions_rvv`).
