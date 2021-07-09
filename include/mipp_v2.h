#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#include <stdint.h>

typedef double float64_t;
typedef float float32_t;

#if defined(__AVX__)
#include "mipp_v2_impl_AVX.h"
#endif

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */