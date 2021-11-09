#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_

#include "mipp_v2.h"

#include <immintrin.h>

// ---------------------------------------------------------------- definitions

#define MIPP_MACRO_FLOAT64(MACRO, ...) \
  MACRO(__VA_ARGS__, float64, pd, pd, float64_t)
#define MIPP_MACRO_FLOAT32(MACRO, ...) \
  MACRO(__VA_ARGS__, float32, ps, ps, float32_t)
#define MIPP_MACRO_INT64(MACRO, ...) \
  MACRO(__VA_ARGS__, int64, epi64, si256, __m256i)
#define MIPP_MACRO_INT32(MACRO, ...) \
  MACRO(__VA_ARGS__, int32, epi32, si256, __m256i)
#define MIPP_MACRO_INT16(MACRO, ...) \
  MACRO(__VA_ARGS__, int16, epi16, si256, __m256i)
#define MIPP_MACRO_INT8(MACRO, ...) \
  MACRO(__VA_ARGS__, int8,  epi8, si256, __m256i)
#define MIPP_MACRO_UINT64(MACRO, ...) \
  MACRO(__VA_ARGS__, uint64, epu64, si256, __m256i)
#define MIPP_MACRO_UINT32(MACRO, ...) \
  MACRO(__VA_ARGS__, uint32, epu32, si256, __m256i)
#define MIPP_MACRO_UINT16(MACRO, ...) \
  MACRO(__VA_ARGS__, uint16, epu16, si256, __m256i)
#define MIPP_MACRO_UINT8(MACRO, ...) \
  MACRO(__VA_ARGS__, uint8,  epu8, si256, __m256i)

#define MIPP_AVX_RVD_SIZE_BIT 256
#define MIPP_AVX_RVD_SIZE_BYTE (MIPP_AVX_RVD_SIZE_BIT/8)

#define MIPP_AVX_N_FLOAT64  4
#define MIPP_AVX_N_FLOAT32  8
#define   MIPP_AVX_N_INT64  4
#define   MIPP_AVX_N_INT32  8
#define   MIPP_AVX_N_INT16 16
#define    MIPP_AVX_N_INT8 32
#define  MIPP_AVX_N_UINT64  4
#define  MIPP_AVX_N_UINT32  8
#define  MIPP_AVX_N_UINT16 16
#define   MIPP_AVX_N_UINT8 32

// ----------------------------- declaration of the data vector registers (rvd)

typedef struct { __m256d m; } rvd_avx_float64_t;
typedef struct { __m256  m; } rvd_avx_float32_t;
typedef struct { __m256i m; } rvd_avx_int64_t;
typedef struct { __m256i m; } rvd_avx_int32_t;
typedef struct { __m256i m; } rvd_avx_int16_t;
typedef struct { __m256i m; } rvd_avx_int8_t;
typedef struct { __m256i m; } rvd_avx_uint64_t;
typedef struct { __m256i m; } rvd_avx_uint32_t;
typedef struct { __m256i m; } rvd_avx_uint16_t;
typedef struct { __m256i m; } rvd_avx_uint8_t;

// ----------------------------- declaration of the mask vector registers (rvm)

typedef struct { __m256i m; } rvm_avx_float64_t;
typedef struct { __m256i m; } rvm_avx_float32_t;
typedef struct { __m256i m; } rvm_avx_int64_t;
typedef struct { __m256i m; } rvm_avx_int32_t;
typedef struct { __m256i m; } rvm_avx_int16_t;
typedef struct { __m256i m; } rvm_avx_int8_t;
typedef struct { __m256i m; } rvm_avx_uint64_t;
typedef struct { __m256i m; } rvm_avx_uint32_t;
typedef struct { __m256i m; } rvm_avx_uint16_t;
typedef struct { __m256i m; } rvm_avx_uint8_t;

#ifdef MIPP_ALIGNED_LOADS
#define MIPP_AVX_INTR_NAME_LOAD load
#define MIPP_AVX_INTR_NAME_STORE store
#else
#define MIPP_AVX_INTR_NAME_LOAD loadu
#define MIPP_AVX_INTR_NAME_STORE storeu
#endif

// --------------------------------------------------------- generic load macro

#define MIPP_MACRO_LOAD_AVX(MIPP_NAME, INTR_NAME, FULL_TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, CAST_TYPE) \
  rvd_avx_##FULL_TYPE##_t mipp_avx_##MIPP_NAME##_##FULL_TYPE(FULL_TYPE##_t *mem_addr) { \
    rvd_avx_##FULL_TYPE##_t rvd; \
    rvd.m = _mm256_##INTR_NAME##_##INTEL_LDST_TYPE((CAST_TYPE*) mem_addr); \
    return rvd; \
  }

// ---------------------------------------------------------------------- loadu

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_AVX, loadu, loadu)

// ----------------------------------------------------------------------- load

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_LOAD_AVX, load, MIPP_AVX_INTR_NAME_LOAD)

// -------------------------------------------------------- generic store macro

#define MIPP_MACRO_STORE_AVX(MIPP_NAME, INTR_NAME, FULL_TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, CAST_TYPE) \
  void mipp_avx_##MIPP_NAME##_##FULL_TYPE(FULL_TYPE##_t *mem_addr, rvd_avx_##FULL_TYPE##_t rvd) { \
    _mm256_##INTR_NAME##_##INTEL_LDST_TYPE((CAST_TYPE*) mem_addr, rvd.m); \
  }

// --------------------------------------------------------------------- storeu

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_AVX, storeu, storeu)

// ---------------------------------------------------------------------- store

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_STORE_AVX, store, MIPP_AVX_INTR_NAME_STORE)

// -------------------------------------------- generic arithmetic 2 args macro

#define MIPP_MACRO_ARITHMETIC_2ARGS_AVX(MIPP_NAME, INTR_NAME, FULL_TYPE, INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx_##FULL_TYPE##_t mipp_avx_##MIPP_NAME##_##FULL_TYPE(rvd_avx_##FULL_TYPE##_t rvd1, rvd_avx_##FULL_TYPE##_t rvd2) \
  { \
    rvd_avx_##FULL_TYPE##_t rvd; \
    rvd.m = _mm256_##INTR_NAME##_##INTEL_TYPE(rvd1.m, rvd2.m); \
    return rvd; \
  }

// ------------------------------------------------------------------------ add

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, add)
#ifdef __AVX2__
MIPP_MACRO_INT64(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, add)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, add)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, adds)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, adds)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx, MIPP_LMUL1)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT32, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx, MIPP_LMUL1)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, adds)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, add, adds)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx, MIPP_LMUL1)
#endif

// ------------------------------------------------------------------------ sub

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, sub)
#ifdef __AVX2__
MIPP_MACRO_INT64(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, sub)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, sub)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, subs)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, subs)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx, MIPP_LMUL1)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT32, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx, MIPP_LMUL1)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, subs)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX, sub, subs)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx, MIPP_LMUL1)
#endif

#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_ */