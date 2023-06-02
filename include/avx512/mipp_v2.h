#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#include <stdint.h>

typedef double float64_t;
typedef float float32_t;

#include "mipp_v2_tools.h"
#include "mipp_v2_impl_emulated.h"

#if defined((__AVX512F__) || defined(__AVX512BW__)|| defined(__MIC__) || defined(__KNCNI__))
#include "mipp_v2_impl_AVX512.h"
#endif

#include "mipp_v2_interface.h"

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */