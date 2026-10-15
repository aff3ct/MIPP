# Getting Started with MIPP

## 1. Installation

MIPP is a **header-only** library: no separate compilation, no pre-built shared/static library, and no runtime dependency. The headers are **generated** from a declarative database by a Python tool and are **not versioned** in the Git repository (cloning the repository alone does not provide an `include/` directory).

There are two ways to obtain them.

### Option A: Download a Release Archive (Recommended)

Each tagged release on [GitHub Releases](https://github.com/aff3ct/MIPP/releases) ships pre-generated headers as `mipp-<version>-headers.zip` and `mipp-<version>-headers.tar.gz`. Extract the archive and add the resulting `include/` directory to your compiler's include search path:

```bash
tar -xzf mipp-<version>-headers.tar.gz
g++ -std=c++11 -O3 -mavx2 -mfma -I/path/to/include main.cpp -o app
```

### Option B: Generate the Headers from Source

Generating the headers requires Python 3 and the packages listed in `generator/requirements.txt`:

```bash
git clone https://github.com/aff3ct/MIPP.git
cd MIPP/generator
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
./gen_mipp_headers.py                            # Default (coarse) headers, emitted into ../include/
# or: ./gen_mipp_headers.py --granularity fine   # Same, plus fine-grained headers (as in the release archives)
```

The generated `include/` directory at the root of the repository is then ready to use.

### Which Header to Include

Each API has a single umbrella header that brings every MIPP function into scope:

| Header File | API | Description |
| :--- | :--- | :--- |
| `<mipp.h>` | **C API** | C99 function prototypes with explicit type suffixes (e.g., `mipp_add_float32(r0, r1)`). |
| `<mipp.hpp>` | **C++ Functional API** | Overloaded functions under namespace `mipp::` (e.g., `mipp::add(r0, r1)`). |
| `<mipp_obj.hpp>` | **C++ Object API** | Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` classes with operator overloading (`+`, `-`, `*`, `==`) and free functions. |

This is the simplest way to start. For larger projects, you can include only the functions you use (`<mipp/obj/fun/add.hpp>`), or even a single masking variant and LMUL (`<mipp/obj/fun/m/m2/add.hpp>`), which makes compilation 2× to 4× faster: see [Headers & Compile Time](headers_and_compile_time.md).

---

## 2. Compiler Flags & Target Architecture Selection

MIPP automatically detects the target instruction set architecture (ISA) at compile time based on standard compiler architecture flags.

### 2.1. Compilation Flags Matrix

| Target Architecture | Compiler Flags (GCC / Clang / ICX) | Detected MIPP Macro | Vector Bitwidth |
| :--- | :--- | :--- | :--- |
| **x86 SSE4.2** | `-msse4.2` | `MIPP_SSE` | 128 bits |
| **x86 AVX** | `-mavx` | `MIPP_AVX` | 256 bits |
| **x86 AVX2 + FMA** | `-mavx2 -mfma` | `MIPP_AVX` (with `MIPP_BW`, `MIPP_FMA`) | 256 bits |
| **x86 AVX-512** | `-mavx512f -mavx512bw -mavx512dq` | `MIPP_AVX512` | 512 bits |
| **ARM NEON (v8-A)** | `-march=armv8-a+simd` | `MIPP_NEON` | 128 bits |
| **ARM SVE** *(WIP)* | `-march=armv8-a+sve -msve-vector-bits=256` | `MIPP_SVE` | Fixed at compile time (256-bit in the example) |
| **RISC-V Vector 1.0** | `-march=rv64gcv_zvl256b -mrvv-vector-bits=zvl` | `MIPP_RVV` | Fixed at compile time ($\ge 128\text{ bits}$, 256-bit in the example) |
| **Scalar Target** | `-DMIPP_SCALAR [-DMIPP_SCALAR_SIZE=bits]` | `MIPP_SCALAR` | Configurable width |

!!! tip "Recommended Optimization Flags for MIPP"
    To ensure proper inlining and vector code generation, compile with:
    
    ```bash
    g++ -O3 -march=native -funroll-loops -finline-functions -I/path/to/mipp/include main.cpp -o app
    ```

---

## 3. Real-World Tutorial: Vectorizing a Loop & Handling Tail Loops

In real applications, data arrays rarely have a size that is an exact multiple of the hardware vector register length ($N = \text{mipp::N<T>()}$). 

Here is the standard, battle-tested pattern to vectorize any loop over an arbitrary array size $S$ with MIPP:

1. **Vector Main Loop**: Process contiguous chunks of $N$ elements with SIMD.
2. **Tail Loop (Remainder)**: Handle remaining $S \pmod N$ elements.

### Complete Working Example (SAXPY with Tail Loop)

=== "C API"

    ```c
    --8<-- "examples/doc/getting_started/c.c"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/getting_started/fun.cpp"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/getting_started/obj.cpp"
    ```

---

## 4. Architecture Introspection (`mipp_info`)

You can call `mipp_info()` at runtime to print the detected OS, compiler, active SIMD extension, and vector register bitwidth to `stdout`:

```c
--8<-- "examples/doc/getting_started/c_info.c"
```
