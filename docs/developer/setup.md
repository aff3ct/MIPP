# Setup

This page sets up a development environment: generate the headers, build and run the unit tests, build this documentation, and test other targets than your machine.

---

## 1. Prerequisites

| Tool | Version | Used for |
| :--- | :--- | :--- |
| Python | 3 (the CI uses 3.12 on GitLab and 3.14 on GitHub) | the generators |
| Jinja2, jsonschema, colorama | see `generator/requirements.txt` | the generators |
| A C++20 compiler | GCC 14 and Clang 20 in the CI | the unit tests (the headers themselves only need C99 or C++11) |
| CMake | 3.5 or later (3.16 or later for precompiled headers) | the unit tests |
| Catch2 | v3 | the unit tests |

On Ubuntu 24.04:

```bash
sudo apt install python3 python3-venv python3-pip cmake g++ catch2
```

On macOS with Homebrew:

```bash
brew install python cmake catch2
```

---

## 2. Python Environment

The generators are run **from the `generator/` directory**: they read and write paths relative to it (`../include/`, `../tests/src/`, `../docs/`). Create the virtual environment there once:

```bash
cd generator
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

All the commands of this guide assume that you are in `generator/` with this environment activated, and call the scripts directly (`./gen_mipp_headers.py`).

---

## 3. Generate

### 3.1. Headers

```bash
./gen_mipp_headers.py                        # all ISAs, coarse headers
./gen_mipp_headers.py --granularity fine     # also the fine-grained headers (as in the CI)
./gen_mipp_headers.py --simd-ext neon        # only NEON (plus the scalar fallback)
```

The script deletes and rewrites `../include/`. It prints the validation results, the audit warnings, then a summary table with the number of functions per implementation level and per ISA. Restricting the ISAs with `--simd-ext` makes the generation faster during development. The options are described in the [Command-Line Reference](reference/cli.md#gen_mipp_headers).

### 3.2. Unit Tests

```bash
./gen_mipp_tests.py                          # C, C++ Functional and C++ Object tests
./gen_mipp_tests.py obj                      # C++ Object tests only (as in the CI)
```

The sources are written to `../tests/src/{c,cpp,obj}/`, one file per function (and per LMUL and mask variant for the C API). The options are described in the [Command-Line Reference](reference/cli.md#gen_mipp_tests).

!!! warning "Generating one API leaves the others in place"
    `./gen_mipp_tests.py obj` only cleans and rewrites `tests/src/obj/`. The `c/` and `cpp/` directories of a previous run stay, and CMake compiles every file under `tests/src/`. Delete them if you only want the Object tests: `rm -rf ../tests/src/c ../tests/src/cpp`.

### 3.3. Documentation Pages

```bash
./gen_mipp_docs.py                                    # every generated page
./gen_mipp_docs.py --only dev_reference includes      # only what the hand-written pages need (fast)
```

This writes the Function Support pages (`docs/funcs_support/`), the Hardware Support pages (`docs/isas_support/`), the API Explorer data (`docs/assets/data/`), the [Command-Line](reference/cli.md) and [Registries](reference/registries/index.md) reference of this guide, and the tables included in the hand-written pages (`docs/includes/generated/`). These files are ignored by Git. See [Build the Documentation](#6-build-the-documentation) and [Docs & API Explorer](internals/docs_and_explorer.md).

---

## 4. Build and Run the Unit Tests

The headers and the test sources must be generated first. From the repository root:

```bash
cd tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_UNITY_BUILD=ON \
      -DCMAKE_CXX_FLAGS="-march=native"
cmake --build build -j4
./build/bin/run-tests
```

- **Target ISA.** As for any MIPP program, the ISA is selected by the compiler flags in `CMAKE_CXX_FLAGS` (`-march=native` tests the ISA of your machine). The CI flags of each target are listed in [Testing Other Targets](#5-testing-other-targets).
- **Build time.** `-DCMAKE_UNITY_BUILD=ON` groups the translation units, which makes the build up to 7× faster (55 s instead of 401 s in one measurement). Precompiled headers are enabled by default (`-DMIPP_PRECOMPILED_HEADERS=OFF` disables them).
- **Selecting tests.** Each test case is tagged with its function name. `./build/bin/run-tests "[add]"` runs the tests of `add` in all APIs, and `./build/bin/run-tests --list-tests` lists them.
- **Iterations.** Each test runs 10 random iterations by default. The `N_ITER` environment variable changes it at run time (`N_ITER=100 ./build/bin/run-tests`), and `./gen_mipp_tests.py -N <n>` changes the default.

### 4.1. Faster Iterations

The complete test suite takes several minutes to build. While working on one function, generate fewer tests:

```bash
./gen_mipp_tests.py obj --lmul 1 --no-ldiv --mask-kind unmasked mask
```

This generates the C++ Object tests for LMUL 1 only, without half-vectors, and for the unmasked and Merge-Masked variants only.

!!! warning "C tests and half-vectors"
    The C API does not expose the masked half-vector functions (`mipp_add_float32_mask_d2`), but the test generator writes tests for them. The C tests therefore do not compile on the targets with half-vectors (AVX, AVX-512, RVV). Generate the C tests with `--no-ldiv` on these targets. The CI only builds the C++ Object tests.

### 4.2. Examples

The `examples/` directory contains small programs for each API, built and run by the CI on every target:

```bash
cd examples
g++ -std=c++11 -O3 -march=native -DMIPP_PRINT_INFO -I../include -o mipp_cpp mipp.cpp && ./mipp_cpp
gcc -std=c11   -O3 -march=native -DMIPP_PRINT_INFO -I../include -o mipp_c   mipp.c   && ./mipp_c
```

`mipp_fine_grained.cpp` requires headers generated with `--granularity fine`.

---

## 5. Testing Other Targets

### 5.1. CI Targets and Flags

The GitLab CI builds and runs the tests with GCC 14 and Clang 20 on 14 targets. The flags it passes in `CMAKE_CXX_FLAGS` are:

| Target | Flags |
| :--- | :--- |
| `sse2`, `sse3`, `ssse3`, `sse4.1`, `sse4.2` | `-msse2`, `-msse3`, `-mssse3`, `-msse4.1`, `-msse4.2` |
| `avx`, `avx2`, `avx2-fma` | `-mavx`, `-mavx2`, `-mavx2 -mfma` |
| `avx512f`, `avx512bw`, `avx512dq` | `-mavx512f`, then `-mavx512bw`, then `-mavx512dq`, cumulatively |
| `armv8-neon` | `-march=armv8.1-a+simd` |
| `riscv64-rvv1.0` | `-march=rv64gv1_zve32f_zvl256b -mrvv-vector-bits=zvl` |
| `x86-scalar` | `-DMIPP_SCALAR -DMIPP_SCALAR_SIZE=1024` |

On RVV, the CI also disables the unity build and the precompiled headers (`-DCMAKE_UNITY_BUILD=OFF -DMIPP_PRECOMPILED_HEADERS=OFF`), and skips the C examples.

### 5.2. CI Docker Images

The CI images are public. They contain GCC 14, Clang 20, CMake, Python and Catch2, and are named `registry.gitlab.com/aff3ct/aff3ct/mipp_linux:<compiler>_<target>`, for instance `gcc-14_avx2` or `clang-20_riscv64-rvv1.0`. Their Dockerfiles are in `ci/docker/`. To run the tests of a foreign architecture on your machine, Docker needs to emulate it (QEMU user-mode emulation, included in Docker Desktop):

```bash
docker run --rm --platform linux/riscv64 -v "$PWD":/mipp -w /mipp/tests \
  registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_riscv64-rvv1.0 \
  bash -c 'cmake -S . -B build_rvv -DCMAKE_CXX_COMPILER=g++-14 -DCMAKE_BUILD_TYPE=Release \
             -DCMAKE_CXX_FLAGS="-march=rv64gv1_zve32f_zvl256b -mrvv-vector-bits=zvl" \
             -DCMAKE_UNITY_BUILD=OFF -DMIPP_PRECOMPILED_HEADERS=OFF \
           && cmake --build build_rvv -j8 && ./build_rvv/bin/run-tests'
```

Emulated builds are slow: restrict the generated tests first ([Faster Iterations](#41-faster-iterations)).

### 5.3. x86 on Apple Silicon

On a Mac with Apple Silicon, Rosetta runs x86-64 binaries with SSE, AVX and AVX2 (not AVX-512). Compile with `-target x86_64-apple-macos` and the x86 flags:

```bash
clang++ -std=c++11 -O2 -target x86_64-apple-macos -mavx2 -mfma -I../include my_test.cpp -o my_test && ./my_test
```

Libraries such as Catch2 must then be available for x86-64 too: a Homebrew installation in `/opt/homebrew` only provides arm64 libraries, so this approach suits standalone programs better than the unit tests.

---

## 6. Build the Documentation

The site uses MkDocs with the Material theme. From the repository root, in a virtual environment:

```bash
pip install -r docs/requirements.txt
(cd generator && ./gen_mipp_docs.py)      # generated pages, needed by the site
mkdocs serve                              # live preview on http://127.0.0.1:8000
mkdocs build --strict                     # what the CI runs: warnings are errors
```

`--strict` turns broken links and missing pages into errors. Run it before submitting a change to the documentation.

### 6.1. Code Examples of the User Guide

The C and C++ code blocks of the User Guide are not written in the pages: they are sections of complete programs in `examples/doc/<page>/`, one file per API (`c.c`, `fun.cpp`, `obj.cpp`), included by `pymdownx.snippets`. A section is delimited by two comments in the program:

```cpp
mipp::rvd<float> a = mipp::load<float>(A);              // setup, not shown
// --8<-- [start:masked]
mipp::rvd<float> c = mipp::add<mipp::M, float>(m, a, b);
// --8<-- [end:masked]
DOC_CHECK(...);                                         // check, not shown
```

and the page includes it inside a code block, with the path from the repository root:

```text
    ```cpp
    ;--8<-- "examples/doc/programming_model/fun.cpp:masked"
    ```
```

The section is dedented, and takes the indentation of the `--8<--` line (code blocks in admonitions, tabs and lists). Without `:section`, the whole file is included. Several `--8<--` lines in the same code block are concatenated. A missing file or section fails `mkdocs build`.

When an example exists in several APIs, each version goes in a content tab, with the labels `C API`, `C++ Functional API` and `C++ Object API`. These are the labels of the Function Support pages: with `content.tabs.link`, choosing an API in one tab set selects it everywhere on the site. A notion specific to one API (deduction in the Functional API, operators of the Object API) gets a single tab with the label of its API.

The tabs of a set do exactly the same thing: same variables, same order, same comments, same number of lines. Each API uses its own syntax (operators in the Object API: `a + b`, `a < b`, `v[i]`), but the Object API loads with `load_obj` / `loadu_obj` rather than with the constructor, which does not show the alignment. A remark specific to one API (what is deduced, what must be given) goes in the text, not in a comment of one tab. Types are written: no `auto`, except in the examples that present it (programming_model §3.5).

```text
=== "C API"

    ```c
    ;--8<-- "examples/doc/masking_semantics/c.c:blend"
    ```

=== "C++ Functional API"
    ...
```

Each program prepares its inputs outside the sections, and checks the results announced by the snippet with `DOC_CHECK` (`examples/doc/doc_check.h`): a failed check makes the program return a non-zero exit code. `scripts/check_doc_snippets.sh` compiles every program with `-Werror` (C99 and C++11, or the standard given by a `// doc-std: c++17` line), runs it, compiles and runs the C++ example of `README.md`, and fails if a C or C++ block of `docs/user/` is written inline, if a tab label is not one of the three above, if a tab includes the file of another API, if the tabs of a set include sections of different lengths (non-blank lines of the named sections at the top level of each tab; complete programs are not compared), or if the included code uses `auto` (exceptions in `AUTO_ALLOWED`):

```bash
scripts/check_doc_snippets.sh                                    # native target
SIMD_EXT="-DMIPP_SCALAR -DMIPP_SCALAR_SIZE=1024" scripts/check_doc_snippets.sh
CC="clang -arch x86_64" CXX="clang++ -arch x86_64" SIMD_EXT="-mavx2 -mfma" \
  scripts/check_doc_snippets.sh --out /tmp/doc_avx2              # x86 on Apple Silicon
```

A block that cannot be compiled (a class synopsis, an excerpt of generated code) stays inline, preceded by `<!-- not-compiled: reason -->`. The GitLab CI runs the script on every target of the matrix ([CI](process/ci.md)).
