#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#include <stdint.h>

typedef double float64_t;
typedef float float32_t;

#include "mipp_v2_tools.h"
#include "mipp_v2_impl_emulated.h"

#if defined(__AVX__)
#include "mipp_v2_impl_AVX.h"
#endif

#include "mipp_v2_interface.h"

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */