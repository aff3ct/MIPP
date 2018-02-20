# MyIntrinsics++ (MIPP)

![](mipp.jpg)

## Purpose

MIPP is a portable and Open-source wrapper (MIT license) for vector intrinsic functions (SIMD) written in C++11. It works for SSE, AVX, AVX-512 and ARM NEON (32-bit and 64-bit) instructions.
MIPP wrapper supports simple/double precision floating-point numbers and also signed integer arithmetic (64-bit, 32-bit, 16-bit and 8-bit).

With the MIPP wrapper you do not need to write a specific intrinsic code anymore. Just use provided functions and the wrapper will automatically generates the right intrisic calls for your specific architecture.

## Short documentation

### Supported compilers

At this time, MIPP has been tested on the following compilers:

  - Intel: `icpc` >= `16`,
  - GNU: `g++` >= `4.8`,
  - Clang: `clang++` >= `3.6`,
  - Microsoft: `msvc` >= `14` (the performances are reduced compared to the other compilers, the compiler is not able to fully inline all the MIPP methods).

### Install and configure your code

You don't have to install MIPP because it is a simple C++ header file.
Just include the header into your source files when the wrapper is needed.

```cpp
#include "mipp.h"
```

mipp.h use a C++ `namespace`: `mipp`, if you do not want to prefix all the MIPP calls by `mipp::` you can do that:

```cpp
#include "mipp.h"
using namespace mipp;
```

Before trying to compile, think to tell the compiler what kind of vector instructions you want to use.
For instance, if you are using GNU compiler (`g++`) you simply have to add the `-march=native` option for SSE and AVX CPUs compatible.
For ARM CPUs with NEON instructions you have to add the `-mfpu=neon` option (since most of current NEON instructions are not IEEE-754 compatible).
MIPP also use some nice features provided by the C++11 and so we have to add the `-std=c++11` flag to compile the code. Your are now ready to run your code with the mipp.h wrapper.

### Sequential mode

By default, MIPP try to recognize the instruction set from the preprocessor definitions.
If MIPP can't match the instruction set (for instance when MIPP does not support the targeted instruction set), MIPP fall back on standard sequential instructions.
In this mode, the vectorization is not guarantee anymore but the compiler can still perform auto-vectorization.

It is possible to force MIPP to use the sequential mode with the following compiler definition: `-DMIPP_NO_INTRINSICS`.
Sometime it can be useful for debugging or to bench a code.

If you want to check the MIPP mode configuration, you can print the following global variable: `mipp::InstructionFullType` (`std::string`).

### Vector register declaration

Just use the `mipp::Reg<T>` type.

```cpp
mipp:Reg<T> r1, r2, r3; // we have declared 3 vector registers
```

But we do not know the number of elements per registers here. This number of elements can be obtained by calling the `mipp::N<T>()` function (`T` is a template parameter, it can be `double`, `float`, `int64_t`, `int32_t`, `int16_t` or `int8_t` type).

```cpp
for(int i = 0; i < n; i += mipp::N<float>()) {
	// ...
}
```

The register size directly depends on the precision of the data we are working on.

### Register load and store instructions

Loading memory from a vector into a register:

```cpp
int n = mipp::N<float>() * 10;
std::vector<float> myVector(n);
int i = 0;
mipp::Reg<float> r1 = &myVector[i*mipp::N<float>()];
```

Store can be done with the `store(...)` method:

```cpp
int n = mipp::N<float>() * 10;
std::vector<float> myVector(n);
int i = 0;
mipp::Reg<float> r1 = &myVector[i*mipp::N<float>()];

// do something with r1

r1.store(&myVector[(i+1)*mipp::N<float>()]);
```

By default the loads and stores work on **unaligned memory**.
It is possible to control this behavior with the `-DMIPP_ALIGNED_LOADS` definition: when specified, the loads and stores work on **aligned memory** by default.
In the **aligned memory** mode, it is still possible to perform unaligned memory operations with the `mipp::loadu` and `mipp::storeu` functions.
However, it is not possible to perform aligned loads and stores in the **unaligned memory** mode.


To allocate aligned data you can use the MIPP aligned memory allocator wrapped into the `mipp::vector` class.
`mipp::vector` is fully retro-compatible with the standard `std::vector` class and it can be use everywhere you can use `std::vector`.

```cpp
mipp::vector<float> myVector(n);
```

### Register initialization

You can initialize a vector register from a scalar value:

```cpp
mipp::Reg<float> r1; // r1 = | unknown | unknown | unknown | unknown |
r1 = 1.0;            // r1 = |    +1.0 |    +1.0 |    +1.0 |    +1.0 |
```

Or from an initializer list (`std::initializer_list`):

```cpp
mipp::Reg<float> r1;       // r1 = | unknown | unknown | unknown | unknown |
r1 = {1.0, 2.0, 3.0, 4.0}; // r1 = |    +1.0 |    +2.0 |    +3.0 |    +4.0 |
```

### Computational instructions

**Add** two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 1.0;     // r1 = | +1.0 | +1.0 | +1.0 | +1.0 |
r2 = 2.0;     // r2 = | +2.0 | +2.0 | +2.0 | +2.0 |

r3 = r1 + r2; // r3 = | +3.0 | +3.0 | +3.0 | +3.0 |
```

**Subtract** two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 1.0;     // r1 = | +1.0 | +1.0 | +1.0 | +1.0 |
r2 = 2.0;     // r2 = | +2.0 | +2.0 | +2.0 | +2.0 |

r3 = r1 - r2; // r3 = | -1.0 | -1.0 | -1.0 | -1.0 |
```

**Multiply** two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 1.0;     // r1 = | +1.0 | +1.0 | +1.0 | +1.0 |
r2 = 2.0;     // r2 = | +2.0 | +2.0 | +2.0 | +2.0 |

r3 = r1 * r2; // r3 = | +2.0 | +2.0 | +2.0 | +2.0 |
```

**Divide** two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 1.0;     // r1 = | +1.0 | +1.0 | +1.0 | +1.0 |
r2 = 2.0;     // r2 = | +2.0 | +2.0 | +2.0 | +2.0 |

r3 = r1 / r2; // r3 = | +0.5 | +0.5 | +0.5 | +0.5 |
```

**Fused multiply and add** of three vector registers:

```cpp
mipp::Reg<float> r1, r2, r3, r4;

r1 = 2.0;                     // r1 = | +2.0 | +2.0 | +2.0 | +2.0 |
r2 = 3.0;                     // r2 = | +3.0 | +3.0 | +3.0 | +3.0 |
r2 = 1.0;                     // r3 = | +1.0 | +1.0 | +1.0 | +1.0 |

// r4 = (r1 * r2) + r3
r4 = mipp::fmadd(r1, r2, r3); // r4 = | +7.0 | +7.0 | +7.0 | +7.0 |
```

**Fused negative multiply and add** of three vector registers:

```cpp
mipp::Reg<float> r1, r2, r3, r4;

r1 = 2.0;                      // r1 = | +2.0 | +2.0 | +2.0 | +2.0 |
r2 = 3.0;                      // r2 = | +3.0 | +3.0 | +3.0 | +3.0 |
r2 = 1.0;                      // r3 = | +1.0 | +1.0 | +1.0 | +1.0 |

// r4 = -((r1 * r2) + r3)
r4 = mipp::fnmadd(r1, r2, r3); // r4 = | -7.0 | -7.0 | -7.0 | -7.0 |
```

**Square root** of a vector register:

```cpp
mipp::Reg<float> r1, r2;

r1 = 9.0;             // r1 = | +9.0 | +9.0 | +9.0 | +9.0 |

r2 = mipp::sqrt(r1);  // r2 = | +3.0 | +3.0 | +3.0 | +3.0 |
```

**Reciprocal square root** of a vector register (be careful: this intrinsic exists only for simple precision floating-point numbers):

```cpp
mipp::Reg<float> r1, r2;

r1 = 9.0;             // r1 = | +9.0 | +9.0 | +9.0 | +9.0 |

r2 = mipp::rsqrt(r1); // r2 = | +0.3 | +0.3 | +0.3 | +0.3 |
```

### Comparisons

Find the **minimum** between two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 2.0;               // r1 = | +2.0 | +2.0 | +2.0 | +2.0 |
r2 = 3.0;               // r2 = | +3.0 | +3.0 | +3.0 | +3.0 |

r3 = mipp::min(r1, r2); // r3 = | +2.0 | +2.0 | +2.0 | +2.0 |
```

Find the **maximum** between two vector registers:

```cpp
mipp::Reg<float> r1, r2, r3;

r1 = 2.0;               // r1 = | +2.0 | +2.0 | +2.0 | +2.0 |
r2 = 3.0;               // r2 = | +3.0 | +3.0 | +3.0 | +3.0 |

r3 = mipp::max(r1, r2); // r3 = | +3.0 | +3.0 | +3.0 | +3.0 |
```

### Permutations

The `lrot(...)` method allows you to perform a **left rotation** (a cyclic permutation) of the elements inside the register:

```cpp
mipp::Reg<float> r1, r2;
r1 = {3.0, 2.0, 1.0, 0.0} // r1 = | +3.0 | +2.0 | +1.0 | +0.0 |

r2 = mipp::lrot(r1);       // r2 = | +0.0 | +3.0 | +2.0 | +1.0 |
r1 = mipp::lrot(r2);       // r1 = | +1.0 | +0.0 | +3.0 | +2.0 |
r2 = mipp::lrot(r1);       // r2 = | +2.0 | +1.0 | +0.0 | +3.0 |
r1 = mipp::lrot(r2);       // r1 = | +3.0 | +2.0 | +1.0 | +0.0 |
```

Of course there are many more available instructions in the MIPP wrapper and you can find these instructions at the end of this page.

## Code examples

### Addition of two vectors

```cpp
#include <cstdlib> // rand()
#include "mipp.h"

int main()
{
	// data allocation
	const int n = 32000; // size of the vectors vA, vB, vC
	mipp::vector<float> vA(n); // in
	mipp::vector<float> vB(n); // in
	mipp::vector<float> vC(n); // out

	// data initialization
	for (int i = 0; i < n; i++) vA[i] = rand() % 10;
	for (int i = 0; i < n; i++) vB[i] = rand() % 10;

	// declare 3 vector registers
	mipp::Reg<float> rA, rB, rC;

	// compute rC with the MIPP vectorized functions
	for (int i = 0; i < n; i += mipp::N<float>()) {
		rA = &vA[i];
		rB = &vB[i];
		rC = rA + rB;
		rC.store(&vC[i]);
	}

	return 0;
}
```

## List of MIPP functions

### Memory operations

| **Short name**  | **Prototype**                                                       | **Supported types**                                          |
| :---            | :---                                                                | :---                                                         |
| `load`          | `Reg  <T> load          (const T*)`                                 | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `loadu`         | `Reg  <T> loadu         (const T*)`                                 | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `store`         | `void     store         (T*, const Reg<T>)`                         | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `storeu`        | `void     storeu        (T*, const Reg<T>)`                         | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `set`           | `Reg  <T> set           (const T[N])`                               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `set`           | `Msk  <N> set           (const bool[N])`                            |                                                              |
| `set1`          | `Reg  <T> set1          (const T)`                                  | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `set1`          | `Msk  <N> set1          (const bool)`                               |                                                              |
| `set0`          | `Reg  <T> set0          ()`                                         | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `set0`          | `Msk  <N> set0          ()`                                         |                                                              |
| `low`           | `Reg_2<T> low           ()`                                         | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `high`          | `Reg_2<T> high          ()`                                         | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmask`         | `Reg  <T> cmask         (const uint32_t[N  ])`                      | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmask2`        | `Reg  <T> cmask2        (const uint32_t[N/2])`                      | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmask4`        | `Reg  <T> cmask4        (const uint32_t[N/4])`                      | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `shuff`         | `Reg  <T> shuff         (const Reg<T>, const Reg<T> cm)`            | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `shuff2`        | `Reg  <T> shuff2        (const Reg<T>, const Reg<T> cm2)`           | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `shuff4`        | `Reg  <T> shuff4        (const Reg<T>, const Reg<T> cm4)`           | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleave`    | `Regx2<T> interleave    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleave2`   | `Regx2<T> interleave2   (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleave4`   | `Regx2<T> interleave4   (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavelo`  | `Reg  <T> interleavelo  (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavelo2` | `Reg  <T> interleavelo2 (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavelo4` | `Reg  <T> interleavelo4 (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavehi`  | `Reg  <T> interleavehi  (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavehi2` | `Reg  <T> interleavehi2 (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `interleavehi4` | `Reg  <T> interleavehi4 (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `lrot`          | `Reg  <T> lrot          (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `rrot`          | `Reg  <T> rrot          (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `blend`         | `Reg  <T> blend         (const Reg<T>, const Reg<T>, const Msk<N>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |

### Bitwise operations

| **Short name** | **Operator**   | **Prototype**                                  | **Supported types**                                          |
| :---           | :---           | :---                                           | :---                                                         |
| `andb`         | `&` and `&=`   | `Reg<T> andb   (const Reg<T>, const Reg<T>)`   | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `andb`         | `&` and `&=`   | `Msk<N> andb   (const Msk<N>, const Msk<N>)`   |                                                              |
| `andnb`        |                | `Reg<T> andnb  (const Reg<T>, const Reg<T>)`   | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `andnb`        |                | `Msk<N> andnb  (const Msk<N>, const Msk<N>)`   |                                                              |
| `orb`          | `\|` and `\|=` | `Reg<T> orb    (const Reg<T>, const Reg<T>)`   | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `orb`          | `\|` and `\|=` | `Msk<N> orb    (const Msk<N>, const Msk<N>)`   |                                                              |
| `xorb`         | `^` and `^=`   | `Reg<T> xorb   (const Reg<T>, const Reg<T>)`   | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `xorb`         | `^` and `^=`   | `Msk<N> xorb   (const Msk<N>, const Msk<N>)`   |                                                              |
| `lshift`       | `<<` and `<<=` | `Reg<T> lshift (const Reg<T>, const uint32_t)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `lshift`       | `<<` and `<<=` | `Msk<N> lshift (const Msk<N>, const uint32_t)` |                                                              |
| `rshift`       | `>>` and `>>=` | `Reg<T> rshift (const Reg<T>, const uint32_t)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `rshift`       | `>>` and `>>=` | `Msk<N> rshift (const Msk<N>, const uint32_t)` |                                                              |
| `notb`         | `~`            | `Reg<T> not    (const Reg<T>)`                 | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `notb`         | `~`            | `Msk<N> not    (const Msk<N>)`                 |                                                              |

### Comparisons

| **Short name** | **Operator** | **Prototype**                                | **Supported types**                                          |
| :---           | :---         | :---                                         | :---                                                         |
| `cmpeq`        | `==`         | `Msk<N> cmpeq  (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmpneq`       | `!=`         | `Msk<N> cmpneq (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmpge`        | `>=`         | `Msk<N> cmpge  (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmpgt`        | `>`          | `Msk<N> cmpgt  (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmple`        | `<=`         | `Msk<N> cmple  (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `cmplt`        | `<`          | `Msk<N> cmplt  (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |

### Conversions and packing

| **Short name** | **Prototype**                                  | **Supported types**                                             |
| :---           | :---                                           | :---                                                            |
| `toReg`        | `Reg<T>  toReg (const Msk<N>)`                 | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t`    |
| `cvt`          | `Reg<T2> cvt   (const Reg<T1>)`                | `float -> int32_t`,                                             |
| `cvt`          | `Reg<T2> cvt   (const Reg_2<T1>)`              | `int8_t -> int16_t`, `int16_t -> int32_t`, `int32_t -> int64_t` |
| `pack`         | `Reg<T2> pack  (const Reg<T1>, const Reg<T1>)` | `int32_t -> int16_t`, `int16_t -> int8_t`                       |

### Arithmetic operations

| **Short name** | **Operator** | **Prototype**                                              | **Supported types**                                          |
| :---           | :---         | :---                                                       | :---                                                         |
| `add`          | `+` and `+=` | `Reg<T> add    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `sub`          | `-` and `-=` | `Reg<T> sub    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `mul`          | `*` and `*=` | `Reg<T> mul    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int32_t`, `int16_t`, `int8_t`            |
| `div`          | `/` and `/=` | `Reg<T> mul    (const Reg<T>, const Reg<T>)`               | `double`, `float`                                            |
| `fmadd`        |              | `Reg<T> fmadd  (const Reg<T>, const Reg<T>, const Reg<T>)` | `double`, `float`                                            |
| `fnmadd`       |              | `Reg<T> fnmadd (const Reg<T>, const Reg<T>, const Reg<T>)` | `double`, `float`                                            |
| `fmsub`        |              | `Reg<T> fmsub  (const Reg<T>, const Reg<T>, const Reg<T>)` | `double`, `float`                                            |
| `fnmsub`       |              | `Reg<T> fnmsub (const Reg<T>, const Reg<T>, const Reg<T>)` | `double`, `float`                                            |
| `min`          |              | `Reg<T> min    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `max`          |              | `Reg<T> max    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `div2`         |              | `Reg<T> div2   (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `div4`         |              | `Reg<T> div4   (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `abs`          |              | `Reg<T> abs    (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `sqrt`         |              | `Reg<T> sqrt   (const Reg<T>)`                             | `double`, `float`                                            |
| `rsqrt`        |              | `Reg<T> rsqrt  (const Reg<T>)`                             | `double`, `float`                                            |
| `sat`          |              | `Reg<T> sat    (const Reg<T>, const T, const T)`           | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `neg`          |              | `Reg<T> neg    (const Reg<T>, const Msk<N>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `neg`          |              | `Reg<T> neg    (const Reg<T>, const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `sign`         |              | `Msk<N> sign   (const Reg<T>)`                             | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `round`        |              | `Reg<T> round  (const Reg<T>)`                             | `double`, `float`                                            |

### Reductions (horizontal functions)

| **Short name**    | **Prototype**                                              | **Supported types**                                          |
| :---              | :---                                                       | :---                                                         |
| `hadd` or `sum`   | `T   hadd                    (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `hmul`            | `T   hmul                    (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `hmin`            | `T   hmin                    (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `hmax`            | `T   hmax                    (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `testz`           | `int testz                   (const Reg<T>, const Reg<T>)` | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `testz`           | `int testz                   (const Msk<N>, const Msk<N>)` |                                                              |
| `testz`           | `int testz                   (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |
| `testz`           | `int testz                   (const Msk<N>)`               |                                                              |
| `Reduction<T,OP>` | `T   Reduction<T,OP>::sapply (const Reg<T>)`               | `double`, `float`, `int64_t`, `int32_t`, `int16_t`, `int8_t` |

### Math functions

| **Short name** | **Prototype**                                    | **Supported types**                |
| :---           | :---                                             | :---                               |
| `exp`          | `Reg<T> exp    (const Reg<T>)`                   | `double` (only on `icpc`), `float` |
| `log`          | `Reg<T> log    (const Reg<T>)`                   | `double` (only on `icpc`), `float` |
| `sin`          | `Reg<T> sin    (const Reg<T>)`                   | `double` (only on `icpc`), `float` |
| `cos`          | `Reg<T> cos    (const Reg<T>)`                   | `double` (only on `icpc`), `float` |
| `sincos`       | `void   sincos (const Reg<T>, Reg<T>&, Reg<T>&)` | `double` (only on `icpc`), `float` |