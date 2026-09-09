# Getting Started with MIPP

## 1. Header-Only Integration

MIPP is a **header-only** library. It requires no separate compilation or pre-built shared/static libraries. To integrate MIPP into your project, simply add the `include/` directory to your compiler's include search paths.

### Header Selection

Depending on your target programming language and preferred level of abstraction, include the appropriate header:

| Header File | API Tier | Description |
| :--- | :--- | :--- |
| `<mipp.h>` | **C Low-Level API** | Pure C99 function prototypes with explicit type suffixes (e.g., `mipp_add_float32_m1(r0, r1)`). |
| `<mipp.hpp>` | **C++ Functional API** | Parameterized functions under namespace `mipp::` (e.g., `mipp::add<float>(r0, r1)`). |
| `<mipp_obj.hpp>` | **C++ Object API** | Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` classes with operator overloading (`+`, `-`, `*`, `==`). |

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
| **ARM SVE** | `-march=armv8-a+sve -msve-vector-bits=256` | `MIPP_SVE` | Fixed at compile time |
| **RISC-V Vector 1.0** | `-march=rv64gcv_zvl256b -mrvv-vector-bits=zvl` | `MIPP_RVV` | Fixed at compile time ($\ge 128\text{ bits}$) |
| **Scalar Target** | `-DMIPP_SCALAR [-DMIPP_SCALAR_SIZE=bits]` | `MIPP_SCALAR` | Configurable (defaults to detected host ISA width, or user-defined bitwidth) |

!!! warning "Compile-Time Fixed Vector Length (No VLA)"
    MIPP operates on **compile-time fixed-length vector registers** (where `mipp::N<T>()` is evaluated as a `constexpr` integer). MIPP does not support Vector Length Agnostic (VLA) dynamic runtime sizing.
    
    When targeting scalable architectures such as **RISC-V Vector (RVV 1.0)** or **ARM SVE**, it is strongly recommended to specify the target hardware vector length (`VLEN`) using compiler flags:
    
    - **RISC-V Vector (e.g. SpacemiT X100, $\text{VLEN}=256\text{ bits}$)**:
      ```bash
      -march=rv64gcv_zvl256b -mrvv-vector-bits=zvl
      ```
    - **ARM SVE (e.g. fixed 256-bit or 512-bit vector length)**:
      ```bash
      -march=armv8-a+sve -msve-vector-bits=256
      ```

!!! tip "Recommended Optimization Flags for MIPP"
    To ensure proper inlining, vector code generation, and software LMUL unrolling, use the following recommended compiler flags:
    
    ```bash
    g++ -O3 -march=native -funroll-loops -finline-functions -I/path/to/mipp/include main.cpp -o app
    ```
    
    - **`-O3`**: Activates high-level optimization passes.
    - **`-march=native`** (or target ISA flags such as `-mavx2` / `-march=armv8-a+simd`): Enables target SIMD hardware instructions.
    - **`-finline-functions`**: Ensures all MIPP `static inline` wrappers are inlined with zero function-call overhead.
    - **`-funroll-loops`**: Maximizes throughput by unrolling loops aggressively.
    
    Additional flags may be enabled depending on application-specific requirements:
    
    - **`-flto`**: Link-time optimization for whole-program inlining across separate translation units.
    - **`-ffast-math`**: Relaxes strict IEEE-754 precision constraints (enables reciprocal approximations and algebraic reassociation).

---

## 3. CMake Integration

In your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MippDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Declare application target
add_executable(my_application main.cpp)

# Add MIPP include directory
target_include_directories(my_application PRIVATE /path/to/mipp/include)

# Enable target architecture vector extensions & inlining
target_compile_options(my_application PRIVATE -march=native -funroll-loops -finline-functions)
```

---

## 4. Minimal Working Examples

Full standalone source files for each API dialect are provided in the [`examples/`](https://github.com/aff3ct/MIPP/tree/develop/examples) directory of the repository (`examples/mipp.cpp`, `examples/mipp_object.cpp`, `examples/mipp.c`, `examples/vecadd.c`).

### 4.1. C Low-Level API (`<mipp.h>`)

```c
#include <stdio.h>
#include <mipp.h>

int main(void)
{
    const int N = MIPP_N_FLOAT32;
    float a[N];
    float b[N];
    float c[N];

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

```cpp
#include <iostream>
#include <vector>
#include <mipp.hpp>

int main()
{
    // Query compile-time element capacity and required byte alignment
    constexpr int N = mipp::N<float>();
    constexpr int ALIGN = mipp::req_alignment();
    std::cout << "Vector capacity (float32): " << N << " elements (" << ALIGN << "-byte alignment)" << std::endl;

    // Allocate aligned data
    alignas(ALIGN) float a[N];
    alignas(ALIGN) float b[N];
    alignas(ALIGN) float c[N];

    for (int i = 0; i < N; ++i) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(i * 2);
    }

    // Load, compute, and store
    mipp::rvd<float> va = mipp::load<float>(a);
    mipp::rvd<float> vb = mipp::load<float>(b);
    mipp::rvd<float> vc = mipp::add(va, vb);

    mipp::store(c, vc);

    std::cout << "Result: c[0]=" << c[0] << ", c[" << N - 1 << "]=" << c[N - 1] << std::endl;
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

```cpp
#include <iostream>
#include <numeric>
#include <mipp_obj.hpp>

int main()
{
    using RegF = mipp::Rvd<float>;
    constexpr int N = RegF::size();
    constexpr int ALIGN = mipp::req_alignment();

    alignas(ALIGN) float a[N];
    alignas(ALIGN) float b[N];
    alignas(ALIGN) float c[N];

    std::iota(a, a + N, 10.0f);
    std::iota(b, b + N, 20.0f);

    // Construct vector objects directly from pointers
    RegF va = mipp::load<float>(a);
    RegF vb = mipp::load<float>(b);

    // Overloaded operators
    RegF vc = (va + vb) * 2.0f;

    // Store back
    mipp::store(c, vc.r);

    std::cout << "Object API Result: c[0]=" << c[0] << " (element 0: " << vc[0] << ")" << std::endl;
    return 0;
}
```

Compile with:
```bash
g++ -O3 -mavx2 -I/path/to/mipp/include example_obj.cpp -o example_obj
./example_obj
```

---

## 5. Architecture Introspection

You can call `mipp_info()` to output the detected OS, compiler, active SIMD extension, and vector register bitwidth to standard output:

```cpp
#include <mipp.hpp>

int main()
{
    mipp_info();
    return 0;
}
```
