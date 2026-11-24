<p align="center">
  <img src="docs/assets/images/mipp.jpg" alt="MIPP" width="480"/>
</p>

# MyIntrinsics++ (MIPP)

[![CI](https://github.com/aff3ct/MIPP/actions/workflows/ci.yml/badge.svg)](https://github.com/aff3ct/MIPP/actions/workflows/ci.yml)
[![Release](https://img.shields.io/github/v/release/aff3ct/MIPP?sort=semver&display_name=tag&color=blue)](https://github.com/aff3ct/MIPP/releases)
[![Documentation](https://img.shields.io/badge/docs-online-blue)](https://aff3ct.github.io/MIPP/)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

MIPP is a header-only SIMD library for C11 and C++11. The same code compiles
for SSE, AVX, AVX-512, NEON, SVE and RVV, and falls back to emulation or scalar
code where an instruction is missing. The headers are generated from a
declarative registry of functions and implementations.

> [!NOTE]
> MIPPv2 is under active development on the `develop` branch: its API may still
> change between v2.x tags. MIPPv1 remains available on the `master` branch.

## Features

- **Three APIs, one implementation**: C (`<mipp.h>`), C++ Functional
  (`<mipp.hpp>`) and C++ Object with overloaded operators (`<mipp_obj.hpp>`).
- **Fallback guarantee**: every function compiles on every target for the
  10 datatypes, through native instructions, a dedicated emulation, a generic
  emulation built on other MIPP functions, or a scalar loop
  ([known limitations](https://aff3ct.github.io/MIPP/user/implementation_levels/#known-limitations)).
- **Register grouping and masking**: LMUL 2, 4, 8 and half-vectors, and four
  masking variants (unmasked, merge, zero, source) on all targets.
- **Header-only**: no library to build. Fine-grained headers (one function,
  variant and LMUL) make compilation 2× to 4× faster than the umbrella header.

## Supported targets

| Architecture | Instruction sets                                       |
| :----------- | :----------------------------------------------------- |
| x86          | SSE, AVX, AVX-512                                      |
| ARM          | NEON, SVE (vector length fixed at compile time)        |
| RISC-V       | RVV 1.0 (vector length fixed at compile time)          |
| Any          | Scalar fallback                                        |

## Example

Leaky ReLU (`y = x > 0 ? x : alpha * x`) with the C++ Object API:

```cpp
#include <cstdlib>
#include <iostream>
#include <vector>
#include <mipp_obj.hpp>

void leaky_relu(float alpha, const float* x, float* y, size_t size)
{
    constexpr size_t N = mipp::Vd<float>::N(); // elements per register (e.g. 8 with AVX2)
    const size_t vec_end = (size / N) * N;

    // 1. Vector main loop
    for (size_t i = 0; i < vec_end; i += N) {
        mipp::Vd<float> vx(&x[i]);                                // load
        mipp::Vm<float> pos = vx > 0.f;                           // comparison -> mask
        mipp::Vd<float> vy  = mipp::select(pos, vx, vx * alpha); // branch-free
        mipp::storeu(&y[i], vy);
    }
    // 2. Scalar tail loop for the remaining elements
    for (size_t i = vec_end; i < size; i++)
        y[i] = x[i] > 0.f ? x[i] : alpha * x[i];
}

int main()
{
    std::vector<float> x(1007), y(1007);
    for (size_t i = 0; i < x.size(); i++)
        x[i] = (i % 2) ? 2.0f : -2.0f;
    leaky_relu(0.1f, x.data(), y.data(), x.size());
    std::cout << "y[0] = " << y[0] << ", y[1] = " << y[1] << " (expected -0.2, 2)" << std::endl;
    return (y[1006] == -0.2f && y[1005] == 2.0f) ? EXIT_SUCCESS : EXIT_FAILURE;
}
```

The same loop body with the C API and the C++ Functional API (`vzero` and
`valpha` hold the broadcast constants):

```c
vd_float32_m1_t vx  = mipp_loadu_float32_m1(&x[i]);
vm_float32_m1_t pos = mipp_cmpgt_float32_m1(vx, vzero);
vd_float32_m1_t vy  = mipp_select_float32_m1(pos, vx, mipp_mul_float32_m1(vx, valpha));
mipp_storeu_float32_m1(&y[i], vy);
```

```cpp
mipp::vd<float> vx  = mipp::loadu<float>(&x[i]);
mipp::vm<float> pos = mipp::cmpgt(vx, vzero);
mipp::vd<float> vy  = mipp::select(pos, vx, mipp::mul(vx, valpha));
mipp::storeu(&y[i], vy);
```

## Installation

The headers are generated and not stored in the repository. Either download
`mipp-<version>-headers.tar.gz` (or `.zip`) from the
[releases](https://github.com/aff3ct/MIPP/releases), or generate them:

```bash
cd generator
python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
./gen_mipp_headers.py   # writes ../include/
```

Then add the `include/` directory to the include path and select the target
with the usual compiler flags:

```bash
g++ -std=c++11 -O3 -march=native -I/path/to/mipp/include leaky_relu.cpp -o leaky_relu
```

See [Getting Started](https://aff3ct.github.io/MIPP/user/getting_started/) for
the flags of each instruction set and
[Headers & Compile Time](https://aff3ct.github.io/MIPP/user/headers_and_compile_time/)
for the fine-grained headers.

## Documentation

The documentation is online at [aff3ct.github.io/MIPP](https://aff3ct.github.io/MIPP/):

- [Getting Started](https://aff3ct.github.io/MIPP/user/getting_started/): installation, compiler flags, a first vectorized loop
- [API Explorer](https://aff3ct.github.io/MIPP/explorer/): search the 92 functions, including by vendor intrinsic
- [Programming Model](https://aff3ct.github.io/MIPP/user/programming_model/): the C, C++ Functional and C++ Object APIs
- [Why MIPPv2](https://aff3ct.github.io/MIPP/why_mippv2/): design and comparison with Highway, xsimd, Eve and others
- [Migrating from MIPPv1](https://aff3ct.github.io/MIPP/user/migrating_from_mippv1/): what changes, the functions whose result changes, the correspondence tables
- [Specifications](https://aff3ct.github.io/MIPP/funcs_support/): semantics and implementation matrix of each function
- [Developer Guide](https://aff3ct.github.io/MIPP/developer/): generation pipeline, adding a function, an implementation or an ISA

## Acknowledgements

MIPP is supported by:

<p>
  <a href="https://www.sorbonne-universite.fr/"><img src="docs/assets/images/logos/sorbonne_universite.svg" alt="Sorbonne Université" height="40"/></a>
  &nbsp;&nbsp;&nbsp;
  <a href="https://www.ifpenergiesnouvelles.fr/"><img src="docs/assets/images/logos/ifpen.jpg" alt="IFP Energies nouvelles" height="40"/></a>
  &nbsp;&nbsp;&nbsp;
  <a href="https://www.inria.fr/"><img src="docs/assets/images/logos/inria.svg" alt="Inria" height="34"/></a>
</p>

## License

MIPP is released under the [MIT License](LICENSE).
