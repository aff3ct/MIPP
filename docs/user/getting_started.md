# Getting Started with MIPP

## 1. Header-Only Integration

MIPP is a **header-only** library. It requires no separate compilation or pre-built shared/static libraries. To integrate MIPP into your project, simply add the `include/` directory to your compiler's include search paths.

### Header Selection & Inclusion Strategies

MIPP offers two inclusion paradigms: **Monolithic Inclusion** and **Granular Inclusion**.

#### Option 1: Monolithic Inclusion (Rapid Prototyping)

Monolithic headers bring the complete set of all MIPP SIMD functions into scope in a single `#include`. This is the simplest way to get started with MIPP and is ideal for prototyping, exploratory code, and small applications:

| Header File | API Tier | Description |
| :--- | :--- | :--- |
| `<mipp.h>` | **C Low-Level API** | Pure C99 function prototypes with explicit type suffixes (e.g., `mipp_add_float32(r0, r1)`). |
| `<mipp.hpp>` | **C++ Functional API** | Parameterized functions under namespace `mipp::` (e.g., `mipp::add<float>(r0, r1)`). |
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

##### Fine-Grained & Atomic 2D Headers (`--granularity fine`)

When MIPP headers are generated with `--granularity fine`, you can target even more specific subsets to achieve the fastest possible compilation times:

- **1D Variant Umbrella**: `<mipp/cpp/fun/<variant>/<func>.hpp>` or `<mipp/cpp/cat/<variant>/<category>.hpp>` (e.g. `m/add.hpp`)
- **1D LMUL Umbrella**: `<mipp/cpp/fun/<lmul>/<func>.hpp>` or `<mipp/cpp/cat/<lmul>/<category>.hpp>` (e.g. `m2/add.hpp`)
- **2D Atomic Fine**: `<mipp/cpp/fun/<variant>/<lmul>/<func>.hpp>` or `<mipp/cpp/cat/<variant>/<lmul>/<category>.hpp>` (e.g. `m/m2/add.hpp`)

Benchmarking shows that granular inclusion drastically reduces preprocessor expansion, slashes compiler parsing time by up to 5x-10x, and substantially reduces peak compiler memory consumption (RSS).

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

### Complete Working Example (C++ Object API)

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <mipp_obj.hpp>

// Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
void saxpy_mipp(float a, const float* x, float* y, size_t size)
{
    constexpr size_t N = mipp::Rvd<float>::N(); // Elements per SIMD register (e.g. 8 on AVX2)

    // 1. Compute the limit for full vector chunks
    const size_t vec_limit = (size / N) * N;

    // Load the scalar multiplier into a vector register (broadcast)
    mipp::Rvd<float> va = a;

    // 2. Vector main loop
    for (size_t i = 0; i < vec_limit; i += N)
    {
        mipp::Rvd<float> vx = mipp::loadu<float>(&x[i]);
        mipp::Rvd<float> vy = mipp::loadu<float>(&y[i]);

        vy += va * vx; // Operator overloading compiles to native FMA / mul+add

        mipp::storeu<float>(&y[i], vy);
    }

    // 3. Scalar tail loop for remaining elements
    for (size_t i = vec_limit; i < size; ++i)
    {
        y[i] += a * x[i];
    }
}

int main()
{
    const size_t size = 1007; // Not a multiple of vector width
    std::vector<float> x(size, 2.0f);
    std::vector<float> y(size, 1.0f);

    saxpy_mipp(3.0f, x.data(), y.data(), size);

    std::cout << "y[0] = " << y[0] << " (expected: 7.0)" << std::endl;
    std::cout << "y[1006] = " << y[1006] << " (expected: 7.0)" << std::endl;
    return 0;
}
```

Compile and run:
```bash
g++ -O3 -mavx2 -mfma -I/path/to/mipp/include saxpy.cpp -o saxpy
./saxpy
```

---

## 4. Minimal Working Examples by API Dialect

MIPP gives you three different ways to write vector code, depending on your constraints:

### 4.1. C Low-Level API (`<mipp.h>`)

For pure C99 projects, drivers, or FFIs:

```c
#include <stdio.h>
#include <mipp.h>

int main(void)
{
    const int N = MIPP_N_FLOAT32;
    float a[N], b[N], c[N];

    for (int i = 0; i < N; ++i) {
        a[i] = (float)i;
        b[i] = (float)(i * 10);
    }

    // Unaligned load, SIMD addition, and unaligned store
    rvd_float32_m1_t va = mipp_loadu_float32_m1(a);
    rvd_float32_m1_t vb = mipp_loadu_float32_m1(b);
    rvd_float32_m1_t vc = mipp_add_float32_m1(va, vb);

    mipp_storeu_float32_m1(c, vc);

    printf("C API Result: c[0]=%f, c[%d]=%f\n", c[0], N - 1, c[N - 1]);
    return 0;
}
```

Compile with:
```bash
gcc -O3 -mavx2 -I/path/to/mipp/include example_c.c -o example_c
./example_c
```

---

### 4.2. C++ Functional Template API (`<mipp.hpp>`)

For generic C++ template programming:

```cpp
#include <iostream>
#include <mipp.hpp>

int main()
{
    constexpr int N = mipp::N<float>();
    alignas(mipp::req_alignment()) float a[N], b[N], c[N];

    for (int i = 0; i < N; ++i) {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

    mipp::rvd<float> va = mipp::load<float>(a);
    mipp::rvd<float> vb = mipp::load<float>(b);
    mipp::rvd<float> vc = mipp::add(va, vb);

    mipp::store(c, vc);

    std::cout << "C++ Functional API Result: c[0]=" << c[0] << ", c[" << N - 1 << "]=" << c[N - 1] << std::endl;
    return 0;
}
```

Compile with:
```bash
g++ -O3 -mavx2 -I/path/to/mipp/include example_cpp.cpp -o example_cpp
./example_cpp
```

---

### 4.3. C++ Object API (`<mipp_obj.hpp>`)

For clean, readable, high-level code with overloaded operators:

```cpp
#include <iostream>
#include <mipp_obj.hpp>

int main()
{
    using RegF = mipp::Rvd<float>;
    constexpr int N = RegF::size();

    float a[N], b[N], c[N];
    for (int i = 0; i < N; ++i) {
        a[i] = (float)i;
        b[i] = 100.0f;
    }

    RegF va = mipp::loadu<float>(a);
    RegF vb = mipp::loadu<float>(b);

    // Natural arithmetic expressions
    RegF vc = (va + vb) * 2.0f;

    mipp::storeu<float>(c, vc);

    std::cout << "C++ Object API Result: c[0]=" << c[0] << " (expected: 200.0)" << std::endl;
    return 0;
}
```

Compile with:
```bash
g++ -O3 -mavx2 -I/path/to/mipp/include example_obj.cpp -o example_obj
./example_obj
```

---

## 5. Architecture Introspection (`mipp_info`)

You can call `mipp_info()` at runtime to print the detected OS, compiler, active SIMD extension, and vector register bitwidth to `stdout`:

```cpp
#include <mipp.hpp>

int main()
{
    mipp_info();
    return 0;
}
```
