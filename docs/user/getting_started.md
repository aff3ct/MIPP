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
./gen_mipp_headers.py                        # Default (coarse) headers, emitted into ../include/
# or: ./gen_mipp_headers.py --granularity fine   # Same, plus fine-grained 2D headers (see below)
```

The generated `include/` directory at the root of the repository is then ready to use.

### Header Selection & Inclusion Strategies

MIPP offers two inclusion paradigms: **Monolithic Inclusion** and **Granular Inclusion**.

#### Option 1: Monolithic Inclusion (Rapid Prototyping)

Monolithic headers bring the complete set of all MIPP SIMD functions into scope in a single `#include`. This is the simplest way to get started with MIPP and is ideal for prototyping, exploratory code, and small applications:

| Header File | API Tier | Description |
| :--- | :--- | :--- |
| `<mipp.h>` | **C Low-Level API** | Pure C99 function prototypes with explicit type suffixes (e.g., `mipp_add_float32(r0, r1)`). |
| `<mipp.hpp>` | **C++ Functional API** | Overloaded functions under namespace `mipp::` (e.g., `mipp::add(r0, r1)`). |
| `<mipp_obj.hpp>` | **C++ Object API** | Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` classes with operator overloading (`+`, `-`, `*`, `==`) and free functions. |

#### Option 2: Granular Inclusion (Production & Fast Compilation)

For large-scale projects, production pipelines, or builds with hundreds of translation units, including every SIMD function can increase compiler memory usage and compilation times. Granular headers allow you to include **only the exact operations** your code uses:

```cpp
// Option 2: Granular inclusion (C++ Object API example)
#include <mipp/obj/fun/load.hpp>
#include <mipp/obj/fun/add.hpp>
#include <mipp/obj/fun/mul.hpp>
#include <mipp/obj/fun/store.hpp>
```

Corresponding granular paths exist across all three API tiers:

- **C Low-Level API**: `<mipp/c/fun/<func>.h>` (or category headers `<mipp/c/cat/<category>.h>`)
- **C++ Functional API**: `<mipp/cpp/fun/<func>.hpp>` (or category headers `<mipp/cpp/cat/<category>.hpp>`)
- **C++ Object API**: `<mipp/obj/fun/<func>.hpp>` (or category headers `<mipp/obj/cat/<category>.hpp>`)

!!! tip "Fine-Grained 2D Inclusions for Ultra-Fast Compilation"
    For production pipelines and large codebases seeking minimum compilation times, MIPP also supports 2D atomic headers (e.g. `<mipp/obj/fun/m/m2/add.hpp>`). They are only present when the headers are generated with `--granularity fine` (see [Option B](#option-b-generate-the-headers-from-source)). See [Programming Model: Fine-Grained Headers](programming_model.md#fine-grained-headers) for full details.

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
| **ARM SVE** *(WIP)* | `-march=armv8-a+sve -msve-vector-bits=256` | `MIPP_SVE` | Fixed at compile time |
| **RISC-V Vector 1.0** | `-march=rv64gcv_zvl256b -mrvv-vector-bits=zvl` | `MIPP_RVV` | Fixed at compile time ($\ge 128\text{ bits}$) |
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
2. **Tail Loop (Reliquat)**: Handle remaining $S \pmod N$ elements.

### Complete Working Example (SAXPY with Tail Loop)

=== "C99 Low-Level API (`<mipp.h>`)"

    ```c
    #include <stdio.h>
    #include <stdlib.h>

    #include <mipp.h>

    // Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
    void saxpy_mipp(float a, const float* x, float* y, size_t size)
    {
        const size_t N = MIPP_N_FLOAT32; // Elements per SIMD register (e.g. 8 on AVX2)
        const size_t vec_limit = (size / N) * N;
        rvd_float32_m1_t va = mipp_set1_float32_m1(a);

        // 1. Vector main loop
        for (size_t i = 0; i < vec_limit; i += N)
        {
            rvd_float32_m1_t vx = mipp_loadu_float32_m1(&x[i]);
            rvd_float32_m1_t vy = mipp_loadu_float32_m1(&y[i]);

            rvd_float32_m1_t vres = mipp_fmadd_float32_m1(va, vx, vy);

            mipp_storeu_float32_m1(&y[i], vres);
        }

        // 2. Scalar tail loop for remaining elements
        for (size_t i = vec_limit; i < size; ++i)
        {
            y[i] += a * x[i];
        }
    }

    int main(void)
    {
        const size_t size = 1007;
        float *x = (float*)malloc(size * sizeof(float));
        float *y = (float*)malloc(size * sizeof(float));

        for (size_t i = 0; i < size; i++) { x[i] = 2.0f; y[i] = 1.0f; }

        saxpy_mipp(3.0f, x, y, size);

        printf("y[0] = %f (expected: 7.0)\n", y[0]);
        printf("y[1006] = %f (expected: 7.0)\n", y[1006]);

        free(x);
        free(y);
        return 0;
    }

    // Compile and run:
    // gcc -std=c99 -O3 -mavx2 -mfma -I/path/to/mipp/include saxpy_c.c -o saxpy_c
    // ./saxpy_c
    ```

=== "C++ Functional API (`<mipp.hpp>`)"

    ```cpp
    #include <iostream>
    #include <vector>

    #include <mipp.hpp>

    // Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
    void saxpy_mipp(float a, const float* x, float* y, size_t size)
    {
        constexpr size_t N = mipp::N<float>(); // Elements per SIMD register (e.g. 8 on AVX2)
        const size_t vec_limit = (size / N) * N;
        mipp::rvd<float> va = mipp::set1<float>(a);

        // 1. Vector main loop
        for (size_t i = 0; i < vec_limit; i += N)
        {
            mipp::rvd<float> vx = mipp::loadu<float>(&x[i]);
            mipp::rvd<float> vy = mipp::loadu<float>(&y[i]);

            mipp::rvd<float> vres = mipp::fmadd(va, vx, vy); // T deduced from operands

            mipp::storeu(&y[i], vres);
        }

        // 2. Scalar tail loop for remaining elements
        for (size_t i = vec_limit; i < size; ++i)
        {
            y[i] += a * x[i];
        }
    }

    int main()
    {
        const size_t size = 1007;
        std::vector<float> x(size, 2.0f);
        std::vector<float> y(size, 1.0f);

        saxpy_mipp(3.0f, x.data(), y.data(), size);

        std::cout << "y[0] = " << y[0] << " (expected: 7.0)" << std::endl;
        std::cout << "y[1006] = " << y[1006] << " (expected: 7.0)" << std::endl;
        return 0;
    }

    // Compile and run:
    // g++ -std=c++11 -O3 -mavx2 -mfma -I/path/to/mipp/include saxpy.cpp -o saxpy
    // ./saxpy
    ```



=== "C++ Object API (`<mipp_obj.hpp>`)"

    ```cpp
    #include <iostream>
    #include <vector>

    #include <mipp_obj.hpp>

    // Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
    void saxpy_mipp(float a, const float* x, float* y, size_t size)
    {
        constexpr size_t N = mipp::Rvd<float>::N(); // Elements per SIMD register (e.g. 8 on AVX2)
        const size_t vec_limit = (size / N) * N;
        mipp::Rvd<float> va = a;

        // 1. Vector main loop
        for (size_t i = 0; i < vec_limit; i += N)
        {
            mipp::Rvd<float> vx(&x[i]);
            mipp::Rvd<float> vy(&y[i]);

            vy += va * vx; // Natural operators 

            mipp::storeu(&y[i], vy);
        }

        // 2. Scalar tail loop for remaining elements
        for (size_t i = vec_limit; i < size; ++i)
        {
            y[i] += a * x[i];
        }
    }

    int main()
    {
        const size_t size = 1007;
        std::vector<float> x(size, 2.0f);
        std::vector<float> y(size, 1.0f);

        saxpy_mipp(3.0f, x.data(), y.data(), size);

        std::cout << "y[0] = " << y[0] << " (expected: 7.0)" << std::endl;
        std::cout << "y[1006] = " << y[1006] << " (expected: 7.0)" << std::endl;
        return 0;
    }

    // Compile and run:
    // g++ -std=c++11 -O3 -mavx2 -mfma -I/path/to/mipp/include saxpy.cpp -o saxpy
    // ./saxpy
    ```

---

## 4. Architecture Introspection (`mipp_info`)

You can call `mipp_info()` at runtime to print the detected OS, compiler, active SIMD extension, and vector register bitwidth to `stdout`:

```cpp
#include <mipp.h>

int main()
{
    mipp_info();
    return 0;
}
```
