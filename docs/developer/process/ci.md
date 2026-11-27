# Continuous Integration

MIPP has two pipelines. The **GitLab CI** (`.gitlab-ci.yml`, on the development repository) is the verification pipeline: it builds and runs the tests on every target. **GitHub Actions** (`.github/workflows/ci.yml`, on the public repository) only generates, and publishes the documentation and the release archives on version tags.

To reproduce a job on your machine (compiler flags, Docker images, emulation), see [Testing Other Targets](../setup.md#5-testing-other-targets).

---

## 1. GitLab CI

Every push runs the whole pipeline.

| Stage | Job | What it does |
| :--- | :--- | :--- |
| `generation` | `generation-headers` | `./gen_mipp_headers.py --simd-ext sse avx avx512 rvv neon scalar sve --granularity fine` (the granularity comes from the `MIPP_GRANULARITY` variable). |
| | `generation-tests` | `./gen_mipp_tests.py obj --lmul 0 8 --ldiv 2 --mask-kind unmasked mask maskz masks`: the C++ Object tests, for the base registers, LMUL 8 and the half-vectors. |
| | `generation-docs` | `./gen_mipp_headers.py --granularity fine`, then `./gen_mipp_docs.py` (the headers are read by the Algorithm modal of the API Explorer). |
| `analysis` | `analysis-cppcheck` | `ci/analysis-cppcheck.sh` on the generated headers. |
| `build` | `build-test-examples` | Compiles the programs of `examples/` with `-Werror`, for each target of the matrix. In fine granularity, also checks that `mipp_fine_grained.cpp` includes atomic headers only. Then compiles the code examples of the documentation (`scripts/check_doc_snippets.sh --build-only`, see [Code Examples of the User Guide](../setup.md#61-code-examples-of-the-user-guide)). |
| | `build-test-unit` | Configures and builds the unit tests (`tests/`) for each target of the matrix, with `-Wall -Wno-unused-function -Werror -funroll-loops -finline-functions` and the flags of the target, linked with `-static -static-libgcc -static-libstdc++`. |
| `test` | `test-unit` | Runs `run-tests` on each target. |
| | `test-examples` | Runs the examples and the code examples of the documentation (`--run-only`) on each target. |
| `deploy` | `deploy-docs-html` | `mkdocs build` (without `--strict`); the site is kept as an artifact. |

**Matrix.** The `build` and `test` jobs run for two compilers (`gcc-14`, `clang-20`) and the 16 targets of [§1.1](#11-targets-and-flags). Each job runs in the image `registry.gitlab.com/aff3ct/aff3ct/mipp_linux:<compiler>_<target>`, on a runner tagged with the target name. The ARMv7 targets (`armv7-neon`, `armv7-neon-fma`) have flags in `.build-common` but are not in the matrix.

### 1.1. Targets and Flags

The matrix is the `ARCH` list of `.matrix-linux-common`; the flags of each target are set in `.build-common` (`SIMD_EXT`) and passed in `CMAKE_CXX_FLAGS` and to the examples:

| Target | Flags |
| :--- | :--- |
| `sse2`, `sse3`, `ssse3`, `sse4.1`, `sse4.2` | `-msse2`, `-msse3`, `-mssse3`, `-msse4.1`, `-msse4.2` |
| `avx`, `avx2`, `avx2-fma` | `-mavx`, `-mavx2`, `-mavx2 -mfma` |
| `avx512f`, `avx512bw`, `avx512dq` | `-mavx512f`, then `-mavx512bw`, then `-mavx512dq`, cumulatively |
| `armv8-neon` | `-march=armv8.1-a+simd` |
| `armv9-sve`, `armv9-sve2` | `-march=armv9-a+sve -msve-vector-bits=128`, `-march=armv9-a+sve2 -msve-vector-bits=128` |
| `riscv64-rvv1.0` | `-march=rv64gv1_zve32f_zvl256b -mrvv-vector-bits=zvl` |
| `x86-scalar` | `-DMIPP_SCALAR -DMIPP_SCALAR_SIZE=1024` |

**RVV.** The C examples (and the C code examples of the documentation) are skipped on `riscv64-rvv1.0`, and the unit tests are built without unity build and precompiled headers (`-DCMAKE_UNITY_BUILD=OFF -DMIPP_PRECOMPILED_HEADERS=OFF`).

**SVE.** On `armv9-sve` and `armv9-sve2`, the unit tests are also built without unity build and precompiled headers. GCC 14 stops with an internal compiler error on the SVE code, so the `gcc-14` jobs of these two targets install GCC 15 from the Ubuntu toolchain PPA and build with it (the job names keep `gcc-14`; the Docker image is unchanged). The C++ programs of `examples/` are then linked with `-static-libstdc++ -static-libgcc`, because they run in another job, with the older `libstdc++` of the image. The code examples of the documentation are linked dynamically (`check_doc_snippets.sh` takes no linker flags).

---

## 2. GitHub Actions

The workflow runs on pushes and pull requests to `develop`, on `v*` tags, and manually.

| Job | When | What it does |
| :--- | :--- | :--- |
| `generation` | always | Same generation as GitLab: headers (`--simd-ext sse avx avx512 rvv neon scalar sve --granularity fine`), C++ Object tests and documentation pages, with Python 3.14. The outputs are uploaded as artifacts (`mipp-headers`, `mipp-tests`, `mipp-docs`), kept 7 days. |
| `deploy-docs` | `v*` tags | Downloads `mipp-docs`, runs `mkdocs build --clean --strict` and deploys the site to GitHub Pages. |
| `release` | `v*` tags | Downloads `mipp-headers`, packs `include/` into `mipp-<tag>-headers.zip` and `.tar.gz`, and creates the GitHub release ([Release](release.md)). |

GitHub Actions does not compile anything: a change is only built and tested by the GitLab CI.

---

## 3. Differences Between the Pipelines

| | GitLab CI | GitHub Actions |
| :--- | :--- | :--- |
| Static analysis | cppcheck | none |
| Builds and tests | 2 compilers × 16 targets | none |
| Site build | `mkdocs build` | `mkdocs build --strict`, tags only |
| Publication | none | GitHub Pages and release, tags only |

Since the GitHub site build is strict and only runs on tags, a broken link is first detected at release time. Run `mkdocs build --strict` locally before tagging ([Release](release.md)).

---

## 4. Changing the CI

- **New ISA**: add it to the `--simd-ext` lists and to the matrix, as described in [Add an ISA](../tutorials/add_isa.md#step-6-test-and-add-to-the-ci).
- **New generated documentation page**: add its path to the docs artifact of both files ([Docs & API Explorer](../internals/docs_and_explorer.md#7-adding-a-generated-part)).
- **Generator options**: the generation commands are duplicated in the two files; keep them in sync.

The audits only print warnings and never fail a job; the validation checks stop the generation job ([Audits & Validation](../reference/audits.md)).
