# Docs & API Explorer

Part of this site is generated from the same JSON files as the headers. This page describes how `gen_mipp_docs.py` produces these pages and the data of the API Explorer, and how to extend them. The options of the script are in the [Command-Line Reference](../reference/cli.md#gen_mipp_docs); building the site is described in [Setup](../setup.md#6-build-the-documentation).

---

## 1. Generated Parts

| Part (`--only`) | Output (in `docs/`) | Code |
| :--- | :--- | :--- |
| `isas_support` | `isas_support/`: Hardware Support pages | `MippInfo`, `write_mipp_infos*()` in `gen_mipp_docs.py` |
| `funcs_support` | `funcs_support/`: Function Support pages | `SpecFuncInfos` in `gen_mipp_docs.py` |
| `explorer` | `assets/data/mipp_api_index.json` and `assets/data/mipp_api_details.json`: data of the API Explorer; `assets/data/algo/`: symbol tables of the generated headers, for the Algorithm modal ([§3.2](#32-algorithm-modal)) | `gen_mipp_api_data.py`, `helpers_docs/algo_sources.py` |
| `dev_reference` | `developer/reference/cli.md` and `developer/reference/registries/` | `helpers_docs/` |
| `includes` | `includes/generated/`: tables included in hand-written pages | `helpers_docs/includes.py` |

All these outputs are ignored by Git and rewritten at each run. The CI generates them, passes them to the site build as an artifact, then runs `mkdocs build` ([Continuous Integration](../process/ci.md)). A local `mkdocs build --strict` fails on the missing pages and fragments if `gen_mipp_docs.py` has not been run.

---

## 2. Support Pages

**Hardware Support.** For each ISA, `MippInfo.gen_mipp_infos()` registers and resolves the candidates exactly as the header generator does ([Code Generation](code_generation.md#4-resolution)), for the base registers only (LMUL 1). The level shown for a function, a datatype and a mask variant is the best effective level among the branches of the resolution: a function that is <span class="mipp-isa-badge lvl-0">L0</span> under `#if defined(__aarch64__)` and <span class="mipp-isa-badge lvl-3">L3</span> elsewhere is shown <span class="mipp-isa-badge lvl-0">L0</span>. The section also gets a page for the masked variants and an intersection page (the functions available at the same level on every ISA).

**Function Support.** One page per function and per category, built from `registry_interfaces.json` (datatypes, mask variants), `registry_protos.json` (prototypes in the three APIs), `registry_categories.json`, `funcs_docs.json` (description and formula), the support matrix computed above and the test properties of `tests_specs.json`.

**Test properties.** The "Test & Verification Specifications" section of these pages and the Verification Specs tab of the Explorer come from `helpers_docs/test_specs.py`, which does not read `tests_specs.json` on its own: it resolves, for each function, mask variant, datatype and input, the values drawn and the comparison with the scalar reference through the test generator (`TestsBuilderEngine`, `DomainResolver`), as in the generated C API tests. It rebuilds the C lines of each input and each tolerance from what it resolved and compares them with the ones the test generator writes: a difference prints a `[test_specs] warning` and means that `test_specs.py` must follow a change of the test generator.

---

## 3. API Explorer

The [API Explorer](../../explorer/index.md) is a client-side application: `docs/explorer/index.md` only holds an empty container, and the ES modules of `docs/assets/explorer/` (`main.js`, `data.js`, `filters.js`, `codegen.js`, `components/`, ...) build the interface from `assets/data/mipp_api_index.json` at load time, then load `assets/data/mipp_api_details.json` in the background.

### 3.1. Data Files

`gen_mipp_api_data.py` writes these files. For each ISA, it resolves the candidates for every hardware LMUL, then merges for each function the prototypes and code samples of the three APIs, the implementation level and intrinsics per ISA, datatype, mask variant and LMUL, the scalar reference, the test properties and the description. The top-level keys of the index are:

| Key | Content |
| :--- | :--- |
| `isas` | Display metadata of each ISA, from `<isa>_explorer.json` ([Explorer Metadata](../reference/registries/explorer_isa.md)): name, description, Compiler Explorer settings, extensions. |
| `datatypes`, `datatype_groups`, `mask_modes`, `levels`, `categories` | Values of the filters. |
| `primitives` | One entry per function. |

The main fields of a `primitives` entry:

| Field | Content |
| :--- | :--- |
| `name`, `category`, `description`, `latex`, `datatypes`, `variants` | From the registries and `funcs_docs.json`. |
| `traits` | Properties derived from the prototype and the interface, never from the category name: `memory` (an argument is a pointer), `returns_mask`, `reduction` (`horizontal`), `changes_datatype` (a datatype pair with two different types, outside memory accesses) and `needs_math` (the scalar reference calls `<math.h>`). The Explorer uses them to build the code samples and the Compiler Explorer programs, so that a new function or category needs no change in the JavaScript. |
| `isa_support` | Level and intrinsics per ISA, datatype, mask variant and LMUL. |
| `prototypes` | The C, C++ Functional and C++ Object prototypes, per LMUL and mask variant (`c99_samples`, `cpp_samples`, `obj_samples`). `defined_lmuls` lists the LMULs where the function exists: the functions that change the LMUL are not generated for every LMUL (no `lo` from `d2`, no `combine` or `wcvt` from `m8`), and for the other LMULs the Explorer shows a notice instead of the prototype. |
| `snippets`, `doc_url` | Code samples and link to the Function Support page. |
| `reference_algo`, `reference_algos`, `scalar_macros`, `test_specs` | Scalar reference and test properties. Not in the index: in `mipp_api_details.json`, keyed by function name (see below). |

The levels of the functions that change the LMUL between `m1` and `d2` (`lo`, `hi`, `combine`, `wcvt`, `ncvt`) do not come from the candidate resolution: they are given by the half-vector templates. For the ISAs with half-vectors by mask, the script gets them from `compute_changing_levels()` (`codegen/ldiv_mask.py`), which runs the half-vector generation without writing anything.

The fields only read once a card tab or the Algorithm modal is opened (`API_DETAIL_FIELDS` in `gen_mipp_api_data.py`: scalar reference, scalar macros, test properties) are written to `mipp_api_details.json` instead of the index, about half of the data. The cards, the filters and the search only need the index, so the first display waits for half the data; `data.js` (`loadApiDetails()`) loads the details once the cards are shown and merges them into the entries, and the Scalar C Reference and Verification Specs tabs show a loading note until then.

The files are written without indentation, since only the Explorer reads them. `data.js` resolves their URL from the module itself (`../data/mipp_api_index.json` relative to `assets/explorer/data.js`), so the Explorer works whatever the base path of the site (`/MIPP/` on GitHub Pages). They are fetched with `cache: "no-cache"`: the browser revalidates its copy with the server (`ETag` / `Last-Modified`) and downloads a file again only when it changed.

To make `mkdocs serve` pick up new data files without a restart, the script also copies them to `site/` and to the temporary directories of a running `mkdocs serve`. `mkdocs serve` sends no cache validators, so locally the files are downloaded at each visit.

### 3.2. Algorithm Modal

The Algorithm modal (button of the Hardware Matrix tab) shows the code of one function for one ISA, datatype, mask variant, LMUL and set of compiler flags. This code is not rebuilt from the templates: it is the code of the generated headers, so it cannot drift from what the CI compiles.

The Hardware Matrix says which features of the ISA a level needs (`(req. AVX-512VL + AVX-512BW)`), and its button opens the modal with these features enabled. They are the features of `simd_ext/<isa>/<isa>_explorer.json` whose macro the condition of the implementation tests (`extract_required_features()` in `gen_mipp_api_data.py`, key `required_features` of the data: a list per datatype). An extension that an implementation tests has to be declared there, otherwise the matrix announces a level that the modal cannot reach.

#### Data

`helpers_docs/algo_sources.py` (called by `gen_mipp_docs.py --only explorer`, after `gen_mipp_headers.py`) splits the C headers of each ISA (`include/mipp/internal/simd_ext/<isa>/c/`) into top-level symbols (macros, types, functions) and writes `assets/data/algo/<isa>.json`:

| Key | Content |
| :--- | :--- |
| `symbols` | For each name, its definitions: `kind`, exact `code` (with its `// Level N` comment), `cond` (the `#if` conditions under which it is defined) and `deps` (the other symbols it uses). |
| `imports` | The tables it uses: `scalar` (fallbacks), the parent ISA (`sse` for the AVX half-vectors), `interface` (the shared macros of `interfaces/c/common.h`, such as `MIPP_LMUL_STRIDE`). |
| `includes` | The system headers of the ISA (`<immintrin.h>`, ...). |
| `cpp` | For each C function, the call of the C++ Functional API that wraps it (`mipp_avx_add_float32_mask_m1` -> `add<M, float32_t, 1>`), read from the generated C++ wrappers. |

`index.json` also holds the ISA selection logic of `interfaces/c/common.h` (`MIPP_AVX`, `MIPP_BW`, ...). A table weighs 5 to 8 MB (0.2 to 0.4 MB compressed); the modal loads the tables of an ISA when it shows this ISA.

#### Assembly

In `docs/assets/explorer/algo_source.js`, `targetMacros()` gives the macros the compiler defines for the flags of the Godbolt link (`-mavx2` defines `__AVX2__`, `__AVX__`, the SSE macros, ...) and evaluates the selection logic. `closure()` resolves the root function, `mipp_<isa>_<func>_<dt>[_<variant>]_<lmul>`, then its dependencies, keeping the definition whose conditions hold (a small preprocessor evaluates the `#if` expressions and the nested conditions of the bodies).

- **Flat C Code** (`buildFlatCode()`): the macros, types and functions of the closure, then a `test` function that calls the function in a loop over `n` registers. In the assembly of `test` (Compiler Explorer, "Open in Godbolt"), the MIPP calls are gone and the loop only contains the instructions of the operation; the header of the code says when a scalar fallback (Level 3) may stay a function call. The "Run in Godbolt" button opens the same code with `buildFlatCode(..., { verify: true })`: a `main` runs `test` once on values of the test domain of the function (`test_specs`) and compares the result with the scalar reference of MIPP.
- **Abstract C++ Implementation** (`buildAbstractCode()`): the body of the function with the types `vd<T, LMUL>` / `vm<T, LMUL>` and the calls of the C++ Functional API (`mipp::select(mipp::cmplt(vd0, vd1), vd0, vd1)`). The functions and types of another ISA (scalar fallback, SSE half-vectors of AVX) keep their C names. The code compiles with `#include <mipp.hpp>`. Below the code:
    - **How it is built** (`callTree()`): the MIPP functions called, recursively, each with what its body is (native, dedicated emulation, composition, scalar fallback, LMUL wrapper; `sourceOf()` reads it from the code) and its level, the highest level of everything it uses. This is where the level propagation shows: `min<int64>` on AVX is a composition of `select` (L0) and `cmplt` (L3, scalar fallback), so it is L3. Each function opens in the modal (with a back button).
- **Compare ISAs**: the abstract view of the same function on several ISAs, side by side. The boxes can be moved and resized (`components/box_layout.js`): the header of a box is dragged to move it, and the gutters right of and below a box change its width and its height (double-click for the automatic size). On the grip of a header, the arrow keys move the box and `Shift` with the arrow keys resizes it. The order of the boxes is in the URL (`algo_cmp`); their sizes last for the visit.

#### Vendor Intrinsics

In the three views (`components/intrinsic_tooltip.js`), `highlightCpp(code, macros, { isa })` gives a tooltip to the intrinsics of the ISA (`_mm*`, NEON `v...q_...`, `sv...`, `__riscv_...`). The tooltip shows:

- the extension the intrinsic needs: the feature macros that every definition using it tests (`defined(__AVX2__)`, `defined(__AVX512BW__)`, ...), only the highest one on the SSE hierarchy;
- the MIPP functions of the ISA that use it, found in the tables already loaded; each one opens in the modal;
- a link to the official documentation: the Intel Intrinsics Guide, the Arm intrinsics page (SVE names in the ACLE form, `svadd[_f32]_z`, computed by `sveDocName()`), or the page of the family in the RVV intrinsics documentation (no page per intrinsic).

No external data is embedded.

Above the code, a line explains the LMUL (software registers, halves `lo` and `hi`, or RVV register groups, the half-vector of each target) and the mask variant (native predication or `select` after the operation, from the call tree), with links to the user guide. The level shown in the modal is the effective level computed from the real code (`effectiveLevel()`): the `// Level N` comment of the headers already gives this effective level, not the kind of the body.

The elements of the code that have a tooltip behave the same way (`tooltipWanted()`, `openTooltip()` and `toggleTooltip()` in `syntax.js`): the tooltip shows while the pointer is on the element (help cursor), and a click keeps it open until a click elsewhere, `Escape` or its close button. One colour per kind, on the element and on the edge of its tooltip: black for a macro, blue for a vendor intrinsic, violet for a parameter that can be an immediate. An open tooltip stays under its element when something scrolls (`followTooltipAnchors()`). The buttons of the hardware features have a tooltip too, on hover only since a click switches the feature (`components/feature_tooltip.js`, neutral grey): the description of the feature, the macro the implementations test and the compiler flag that defines it.

#### Checking

Both views can be generated for every combination outside the browser, by running the modules with a JavaScript engine (`setAlgoLoader()` replaces `fetch`), then compiled with the flags of their Godbolt link: the abstract code against `<mipp.hpp>`, the Flat C Code with its verification `main`. The Flat C Code must compile, the loop of `test` must contain no call up to Level 2, and the program must print `OK` where it can run.

---

## 4. Developer Guide Reference

The [Command-Line](../reference/cli.md) and [Registries](../reference/registries/index.md) pages are generated so that they cannot drift from the code.

### 4.1. Command Line

In `helpers_docs/cli.py`, each generator builds its parser in a `build_arg_parser()` function, with the `MippHelpFormatter` formatter and `set_examples()`. `render_cli_page()` renders these parsers into `cli.md`; `--help` prints the same text. The help strings follow a few conventions, because they are shown both in a terminal and in Markdown:

- literal values, paths and file names are written between single quotes (`'all'`, `'../include/'`) and become code spans; option names (`--no-clean`) become code spans too;
- defaults are not written in the help strings: the formatter appends them in the terminal, and the page has a *Default* column;
- the paragraphs of a description are separated by a blank line; a paragraph whose lines all start with `- ` is a bullet list.

To document a new script, give it a `build_arg_parser()` function and add it to the `entries` of `write_dev_reference()` in `gen_mipp_docs.py`.

### 4.2. Registries

`helpers_docs/schemas.py` writes one page per JSON Schema, listed in `PAGES` (page name, schema, validated files, code fence language). The pages use standard annotations, ignored by the validation:

| Annotation | Use |
| :--- | :--- |
| `title` | Title of the page (root only). |
| `description` | Markdown: introduction of the page (root), text of the field (fields). Relative links are relative to the generated page. |
| `examples` | The first example of the root is shown as a JSON block. |
| `propertyNames.title` | Name of the keys of a map, shown in the field paths (`<function>.proto_ref`). |

Fields are listed with their path, type, `required` flag, `enum` values and `default`; the `definitions` get their own section, and `$ref` types link to it. To document a new JSON file, add its schema to `PAGES`, or to `UNVALIDATED` if it has none.

---

## 5. Tables Included in Hand-Written Pages

Some tables of the hand-written pages restate the registries or the ISA descriptors. They are generated as Markdown fragments in `docs/includes/generated/` by `helpers_docs/includes.py`, and included where they are needed with `pymdownx.snippets`:

```markdown
;--8<-- "docs/includes/generated/lmul_availability.md"
```

| Fragment | Source | Included in |
| :--- | :--- | :--- |
| `lmul_availability.md` | `sw_lmul`, `hw_lmul`, `sw_ldiv_type` of the ISA descriptors; the `MIPP_LDIV_2` column uses the same condition as `ci_generator.py` | [Vector Types & LMUL](../../user/vector_types_and_lmul.md#34-representation-per-target) |
| `datatypes.md` | `all_datatypes` (`datatypes.py`), `registry_scalar_isa.json` | [Vector Types & LMUL](../../user/vector_types_and_lmul.md#1-supported-datatypes-matrix) |
| `categories.md` | `registry_categories.json` | [Add a Function](../tutorials/add_function.md#step-2-assign-a-category) |
| `variants.md` | `registry_interfaces.json` | [Add a Function](../tutorials/add_function.md#step-1-declare-the-interface) |

`docs/includes/` is excluded from the site (`exclude_docs` in `mkdocs.yml`): its files are fragments, not pages. A fragment is included in pages at different depths, so it contains no relative link. To add one, write a `render_*()` function and add its output to `write_includes()`.

---

## 6. Syntax Highlighting

The code blocks of the Developer Guide use two Pygments lexers defined in `scripts/pygments_mipp/`, installed by `docs/requirements.txt`:

- `mipp-dsl`: a template in the [templating DSL](../reference/templating_dsl.md) (`%...%` markers on top of C and Jinja2);
- `mipp-json`: an implementation or template file, where the `code` strings are highlighted with `mipp-dsl`.

---

## 7. Adding a Generated Part

1. Write the generator, and call it from `main()` in `gen_mipp_docs.py` under a new name of `DOC_PARTS`.
2. Write its output under `docs/`, and add the path to `.gitignore`.
3. Add the path to the docs artifact of both CI files (`generation` job in `.github/workflows/ci.yml`, `generation-docs` job in `.gitlab-ci.yml`), otherwise the deployed site misses it.
4. Link the new pages from the hand-written ones (or include the fragments, [§5](#5-tables-included-in-hand-written-pages)), and run `mkdocs build --strict`.
