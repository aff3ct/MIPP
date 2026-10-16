# Docs & API Explorer

Part of this site is generated from the same JSON files as the headers. This page describes how `gen_mipp_docs.py` produces these pages and the data of the API Explorer, and how to extend them. The options of the script are in the [Command-Line Reference](../reference/cli.md#gen_mipp_docs); building the site is described in [Setup](../setup.md#6-build-the-documentation).

---

## 1. Generated Parts

| Part (`--only`) | Output (in `docs/`) | Code |
| :--- | :--- | :--- |
| `isas_support` | `isas_support/`: Hardware Support pages | `MippInfo`, `write_mipp_infos*()` in `gen_mipp_docs.py` |
| `funcs_support` | `funcs_support/`: Function Support pages | `SpecFuncInfos` in `gen_mipp_docs.py` |
| `explorer` | `assets/data/mipp_api_index.json`: data of the API Explorer | `gen_mipp_api_data.py` |
| `dev_reference` | `developer/reference/cli.md` and `developer/reference/registries/` | `helpers_docs/` |
| `includes` | `includes/generated/`: tables included in hand-written pages | `helpers_docs/includes.py` |

All these outputs are ignored by Git and rewritten at each run. The CI generates them, passes them to the site build as an artifact, then runs `mkdocs build` ([Continuous Integration](../process/ci.md)). A local `mkdocs build --strict` fails on the missing pages and fragments if `gen_mipp_docs.py` has not been run.

---

## 2. Support Pages

**Hardware Support.** For each ISA, `MippInfo.gen_mipp_infos()` registers and resolves the candidates exactly as the header generator does ([Code Generation](code_generation.md#4-resolution)), for the base registers only (LMUL 1). The level shown for a function, a datatype and a mask variant is the best effective level among the branches of the resolution: a function that is <span class="mipp-isa-badge lvl-0">L0</span> under `#if defined(__aarch64__)` and <span class="mipp-isa-badge lvl-3">L3</span> elsewhere is shown <span class="mipp-isa-badge lvl-0">L0</span>. The section also gets a page for the masked variants and an intersection page (the functions available at the same level on every ISA).

**Function Support.** One page per function and per category, built from `registry_interfaces.json` (datatypes, mask variants), `registry_protos.json` (prototypes in the three APIs), `registry_categories.json`, `funcs_docs.json` (description and formula), the support matrix computed above and the test properties of `tests_specs.json`.

---

## 3. API Explorer

The [API Explorer](../../explorer/index.md) is a client-side application: `docs/explorer/index.md` only holds an empty container, and the ES modules of `docs/assets/explorer/` (`main.js`, `data.js`, `filters.js`, `codegen.js`, `components/`, ...) build the interface from `assets/data/mipp_api_index.json` at load time.

`gen_mipp_api_data.py` writes this file. For each ISA, it resolves the candidates for every hardware LMUL, then merges for each function the prototypes and code samples of the three APIs, the implementation level and intrinsics per ISA, datatype, mask variant and LMUL, the scalar reference, the test properties and the description. The top-level keys are:

| Key | Content |
| :--- | :--- |
| `isas` | Display metadata of each ISA, from `<isa>_explorer.json` ([Explorer Metadata](../reference/registries/explorer_isa.md)): name, description, Compiler Explorer settings, extensions. |
| `datatypes`, `datatype_groups`, `mask_modes`, `levels`, `categories` | Values of the filters. |
| `primitives` | One entry per function. |

To make `mkdocs serve` pick up a new data file without a restart, the script also copies it to `site/` and to the temporary directories of a running `mkdocs serve`.

---

## 4. Developer Guide Reference

The [Command-Line](../reference/cli.md) and [Registries](../reference/registries/index.md) pages are generated so that they cannot drift from the code.

**Command line** (`helpers_docs/cli.py`). Each generator builds its parser in a `build_arg_parser()` function, with the `MippHelpFormatter` formatter and `set_examples()`. `render_cli_page()` renders these parsers into `cli.md`; `--help` prints the same text. The help strings follow a few conventions, because they are shown both in a terminal and in Markdown:

- literal values, paths and file names are written between single quotes (`'all'`, `'../include/'`) and become code spans; option names (`--no-clean`) become code spans too;
- defaults are not written in the help strings: the formatter appends them in the terminal, and the page has a *Default* column;
- the paragraphs of a description are separated by a blank line; a paragraph whose lines all start with `- ` is a bullet list.

To document a new script, give it a `build_arg_parser()` function and add it to the `entries` of `write_dev_reference()` in `gen_mipp_docs.py`.

**Registries** (`helpers_docs/schemas.py`). One page per JSON Schema, listed in `PAGES` (page name, schema, validated files, code fence language). The pages use standard annotations, ignored by the validation:

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
