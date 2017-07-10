# MyIntrinsics++ (MIPP)

![](mipp.jpg)

## Purpose

MIPP is a portable and Open-source wrapper (MIT license) for vector intrinsic functions (SIMD) written in C++11. It works for SSE, AVX, AVX512 and ARM NEON instructions. 
MIPP wrapper supports simple/double precision floating-point numbers and also signed integer arithmetic (32-bit, 16-bit and 8-bit). 

With the MIPP wrapper you do not need to write a specific intrinsic code anymore. Just use provided functions and the wrapper will automatically generates the right intrisic calls for your specific architecture.

## Short documentation

### Install and configure your code for MIPP

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

Before trying to compile, think to tell the compiler what kind of vector instructions you want to use. Remember, MIPP currently supports SSE, AVX and NEON instructions. 
For example, if you are using GNU compiler (g++) you simply have to add the `-march=native` option for SSE and AVX CPUs compatible. 
For ARM CPUs with NEON instructions you have to add the `-mfpu=neon` option (since most of current NEON instructions are not IEEE-754 compatible). 
MIPP also use some nice features provided by the C++11 and so we have to add the `-std=c++11` flag to compile the code. Your are now ready to run your code with the mipp.h wrapper.

### Vector register declaration

Just use the `mipp::Reg<T>` type.

```cpp
mipp:Reg<T> r1, r2, r3; // we have declared 3 vector registers
```

But we do not know the number of elements per registers here. This number of elements can be obtained by calling the `mipp::nElReg<T>()` function (`T` is a template parameter, it can be `double`, `float`, `int`, `short` or `signed char` type).

```cpp
for(int i = 0; i < n; i += mipp::nElReg<float>()) {
	// ...
}
```

The register size directly depends on the precision of the data we are working on.

### Register load and store instructions

Firstly, register loads or stores need to be aligned on the register size.
To allocate aligned data you can use the mipp predifined vector class: `mipp::vector`. This class is fully retro-compatible with the standard `std::vector` class and it can be use everywhere you can use `std::vector`.

```cpp
mipp::vector<float> myVector(n);
```

Now, if the data are correctly allocated we can perform a register loading from the vector:

```cpp
int n = mipp::nElReg<float>() * 10;
mipp::vector<float> myVector(n);
int i = 0;
mipp::Reg<float> r1 = &myVector[i*mipp::nElReg<float>()];
```

Store can be done with the `store(...)` method:

```cpp
int n = mipp::nElReg<float>() * 10;
mipp::vector<float> myVector(n);
int i = 0;
mipp::Reg<float> r1 = &myVector[i*mipp::nElReg<float>()];

// do something with r1

r1.store(&myVector[(i+1)*mipp::nElReg<float>()]);
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

**Reciprocal square root** of a vector register (be careful: this instrinsic exists only for simple precision floating-point numbers):

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

The `rot(...)` method allows you to perform a **rotation** (a cyclic permutation) of the elements inside the register:

```cpp
mipp::Reg<float> r1, r2;
r1 = {3.0, 2.0, 1.0, 0.0} // r1 = | +3.0 | +2.0 | +1.0 | +0.0 |

r2 = mipp::rot(r1);       // r2 = | +0.0 | +3.0 | +2.0 | +1.0 |
r1 = mipp::rot(r2);       // r1 = | +1.0 | +0.0 | +3.0 | +2.0 |
r2 = mipp::rot(r1);       // r2 = | +2.0 | +1.0 | +0.0 | +3.0 |
r1 = mipp::rot(r2);       // r1 = | +3.0 | +2.0 | +1.0 | +0.0 |
```

Of course there are many more available instructions in the MIPP wrapper and you can find these instructions in the MIPP files.

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
	for (int i = 0; i < n; i += mipp::nElReg<float>()) {
		rA = &vA[i];
		rB = &vB[i];
		rC = rA + rB;
		rC.store(&vC[i]);
	}

	return 0;
}
```