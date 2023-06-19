#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_

#include "mipp_v2.h"

#include <immintrin.h>

// ---------------------------------------------------------------- definitions

#define MIPP_MACRO_FLOAT64(MACRO, ...) MACRO(__VA_ARGS__ , 64 , float , pd    , pd    , float64_t)
#define MIPP_MACRO_FLOAT32(MACRO, ...) MACRO(__VA_ARGS__ , 32 , float , ps    , ps    , float32_t)
#define MIPP_MACRO_INT64(MACRO, ...)   MACRO(__VA_ARGS__ , 64 , int   , epi64 , si512 , int64_t)
#define MIPP_MACRO_INT32(MACRO, ...)   MACRO(__VA_ARGS__ , 32 , int   , epi32 , si512 , int32_t)
#define MIPP_MACRO_INT16(MACRO, ...)   MACRO(__VA_ARGS__ , 16 , int   , epi16 , si512 , int16_t)
#define MIPP_MACRO_INT8(MACRO, ...)    MACRO(__VA_ARGS__ , 8  , int   , epi8  , si512 , int8_t)
#define MIPP_MACRO_UINT64(MACRO, ...)  MACRO(__VA_ARGS__ , 64 , uint  , epu64 , si512 , uint64_t)
#define MIPP_MACRO_UINT32(MACRO, ...)  MACRO(__VA_ARGS__ , 32 , uint  , epu32 , si512 , uint32_t)
#define MIPP_MACRO_UINT16(MACRO, ...)  MACRO(__VA_ARGS__ , 16 , uint  , epu16 , si512 , uint16_t)
#define MIPP_MACRO_UINT8(MACRO, ...)   MACRO(__VA_ARGS__ , 8  , uint  , epu8  , si512 , uint8_t)

#define MIPP_AVX512_RVD_SIZE_BIT 512
#define MIPP_AVX512_RVD_SIZE_BYTE 64

#define MIPP_AVX512_N_FLOAT64 8
#define MIPP_AVX512_N_FLOAT32 16
#define MIPP_AVX512_N_INT64 8
#define MIPP_AVX512_N_INT32 16
#define MIPP_AVX512_N_INT16 32
#define MIPP_AVX512_N_INT8 64
#define MIPP_AVX512_N_UINT64 8
#define MIPP_AVX512_N_UINT32 16
#define MIPP_AVX512_N_UINT16 32
#define MIPP_AVX512_N_UINT8 64

// ----------------------------- declaration of the data vector registers (rvd)

typedef struct { __m512d m; } rvd_avx512_float64_t;
typedef struct { __m512 m;  } rvd_avx512_float32_t;
typedef struct { __m512i m; } rvd_avx512_int64_t;
typedef struct { __m512i m; } rvd_avx512_int32_t;
typedef struct { __m512i m; } rvd_avx512_int16_t;
typedef struct { __m512i m; } rvd_avx512_int8_t;
typedef struct { __m512i m; } rvd_avx512_uint64_t;
typedef struct { __m512i m; } rvd_avx512_uint32_t;
typedef struct { __m512i m; } rvd_avx512_uint16_t;
typedef struct { __m512i m; } rvd_avx512_uint8_t;

// ----------------------------- declaration of the mask vector registers (rvm)

typedef struct { __mmask8 m;  } rvm_avx512_float64_t;
typedef struct { __mmask16 m; } rvm_avx512_float32_t;
typedef struct { __mmask8 m;  } rvm_avx512_int64_t;
typedef struct { __mmask16 m; } rvm_avx512_int32_t;
typedef struct { __mmask32 m; } rvm_avx512_int16_t;
typedef struct { __mmask64 m; } rvm_avx512_int8_t;
typedef struct { __mmask8 m;  } rvm_avx512_uint64_t;
typedef struct { __mmask16 m; } rvm_avx512_uint32_t;
typedef struct { __mmask32 m; } rvm_avx512_uint16_t;
typedef struct { __mmask64 m; } rvm_avx512_uint8_t;

#ifdef MIPP_ALIGNED_LOADS
#define MIPP_AVX512_INTR_NAME_LOAD load
#define MIPP_AVX512_INTR_NAME_STORE store
#else
#define MIPP_AVX512_INTR_NAME_LOAD loadu
#define MIPP_AVX512_INTR_NAME_STORE storeu
#endif

// --------------------------------------------------------- generic load macro

#define MIPP_MACRO_LOAD_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t *mem_addr) { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_LDST_TYPE((CAST_TYPE*) mem_addr); \
    return rvd; \
  }

// ---------------------------------------------------------------------- loadu

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_AVX512, loadu, loadu)

// ----------------------------------------------------------------------- load

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_LOAD_AVX512, load, MIPP_AVX512_INTR_NAME_LOAD)

// -------------------------------------------------------- generic store macro

#define MIPP_MACRO_STORE_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, CAST_TYPE) \
  void mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t *mem_addr, rvd_avx512_##TYPE##N_BITS##_t rvd) { \
    _mm512_##INTR_NAME##_##INTEL_LDST_TYPE((CAST_TYPE*) mem_addr, rvd.m); \
  }

// --------------------------------------------------------------------- storeu

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_AVX512, storeu, storeu)

// ---------------------------------------------------------------------- store

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_STORE_AVX512, store, MIPP_AVX512_INTR_NAME_STORE)


// ----------------------------------------------------------------------- set1

#define MIPP_MACRO_SET1_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t val) { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_TYPE(val); \
    return rvd; \
  }

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_SET1_AVX512, set1, set1)
MIPP_MACRO_SET1_AVX512(set1, set1, 64, int, epi64x, osef, osef)
MIPP_MACRO_INT32(MIPP_MACRO_SET1_AVX512, set1, set1)
MIPP_MACRO_INT16(MIPP_MACRO_SET1_AVX512, set1, set1)
MIPP_MACRO_INT8(MIPP_MACRO_SET1_AVX512, set1, set1)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_UINT, MIPP_MACRO_UNIMPLEMENTED_SET1, set1, avx)

// ----------------------------------------------------------------------- set0

#define MIPP_MACRO_SET0_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS() { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_LDST_TYPE(); \
    return rvd; \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_SET0_AVX512, set0, setzero)

// -------------------------------------------- generic arithmetic 1 args macro

#define MIPP_MACRO_ARITHMETIC_1ARG_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(rvd_avx512_##TYPE##N_BITS##_t rvd1) \
  { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_TYPE(rvd1.m); \
    return rvd; \
  }

// ----------------------------------------------------------------------- sqrt

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_1ARG_AVX512, sqrt, sqrt)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_1ARG, sqrt, avx)

// ---------------------------------------------------------------------- rsqrt

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_FLOAT64, MIPP_MACRO_UNIMPLEMENTED_1ARG, rsqrt, avx)
MIPP_MACRO_FLOAT32(MIPP_MACRO_ARITHMETIC_1ARG_AVX512, rsqrt, rsqrt)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_1ARG, rsqrt, avx)

// -------------------------------------------- generic arithmetic 2 args macro

#define MIPP_MACRO_ARITHMETIC_2ARGS_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(rvd_avx512_##TYPE##N_BITS##_t rvd1, rvd_avx512_##TYPE##N_BITS##_t rvd2) \
  { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_TYPE(rvd1.m, rvd2.m); \
    return rvd; \
  }

// ------------------------------------------------------------------------ add

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, add)
#ifdef __AVX2__
MIPP_MACRO_INT64(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, add)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, add)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, adds)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, adds)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT32, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, adds)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, add, adds)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, add, avx)
#endif

// ------------------------------------------------------------------------ sub

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, sub)
#ifdef __AVX2__
MIPP_MACRO_INT64(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, sub)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, sub)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, subs)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, subs)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT32, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, subs)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, sub, subs)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, sub, avx)
#endif

// ------------------------------------------------------------------------ mul

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, mul, mul)
#ifdef __AVX2__
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, mul, avx)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, mul, mullo)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, mul, mullo)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT8, MIPP_MACRO_UNIMPLEMENTED_2ARGS, mul, avx)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, mul, avx)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, mul, avx)
#endif

// ------------------------------------------------------------------------ div

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, div, div)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, div, avx)

// ------------------------------------------------------------------------ min

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
#ifdef __AVX2__
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, min, avx)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, min, avx)
MIPP_MACRO_UINT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, min, min)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, min, avx)
#endif

// ------------------------------------------------------------------------ max

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
#ifdef __AVX2__
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, max, avx)
MIPP_MACRO_INT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
MIPP_MACRO_INT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
MIPP_MACRO_INT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_UNIMPLEMENTED_2ARGS, max, avx)
MIPP_MACRO_UINT32(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
MIPP_MACRO_UINT16(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
MIPP_MACRO_UINT8(MIPP_MACRO_ARITHMETIC_2ARGS_AVX512, max, max)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, max, avx)
#endif

// -------------------------------------------- generic arithmetic 3 args macro

#define MIPP_MACRO_ARITHMETIC_3ARGS_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(rvd_avx512_##TYPE##N_BITS##_t rvd1, rvd_avx512_##TYPE##N_BITS##_t rvd2, rvd_avx512_##TYPE##N_BITS##_t rvd3) \
  { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_TYPE(rvd1.m, rvd2.m, rvd3.m); \
    return rvd; \
  }

// ---------------------------------------------------------------------- fmadd

#ifdef __FMA__
MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_3ARGS_AVX512, fmadd, fmadd)
#else
MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_EMULATED_FMADD, avx)
#endif
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_3ARGS, fmadd, avx)


// ---------------------------------------------------------------------- fmsub

#ifdef __FMA__
MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_3ARGS_AVX512, fmsub, fmsub)
#else
MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_ARITHMETIC_EMULATED_FMSUB, avx)
#endif
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_3ARGS, fmsub, avx)

// ----------------------------------------------- generic logical 2 args macro

#define MIPP_MACRO_LOGICAL_2ARGS_AVX512(MIPP_NAME, INTR_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_avx512_##TYPE##N_BITS##_t mipp_avx512_##MIPP_NAME##_##TYPE##N_BITS(rvd_avx512_##TYPE##N_BITS##_t rvd1, rvd_avx512_##TYPE##N_BITS##_t rvd2) \
  { \
    rvd_avx512_##TYPE##N_BITS##_t rvd; \
    rvd.m = _mm512_##INTR_NAME##_##INTEL_LDST_TYPE(rvd1.m, rvd2.m); \
    return rvd; \
  }

// ----------------------------------------------------------------------- andb

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, andb, and)
#ifdef __AVX2__
MIPP_MACRO_ALL_INT_AND_UINT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, andb, and)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, andb, avx)
#endif

// ---------------------------------------------------------------------- andnb

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, andnb, andnot)
#ifdef __AVX2__
MIPP_MACRO_ALL_INT_AND_UINT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, andnb, andnot)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, andnb, avx)
#endif

// ------------------------------------------------------------------------ orb

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, orb, or)
#ifdef __AVX2__
MIPP_MACRO_ALL_INT_AND_UINT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, orb, or)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, orb, avx)
#endif

// ----------------------------------------------------------------------- xorb

MIPP_MACRO_ALL_FLOAT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, xorb, xor)
#ifdef __AVX2__
MIPP_MACRO_ALL_INT_AND_UINT(MIPP_MACRO_LOGICAL_2ARGS_AVX512, xorb, xor)
#else
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_INT_AND_UINT, MIPP_MACRO_UNIMPLEMENTED_2ARGS, xorb, avx)
#endif

// ----------------------------------------------------------------------- notb

// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_FLOAT64, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int64)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_FLOAT32, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int32)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT64, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int64)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT32, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int32)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT16, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int16)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_INT8, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int8)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT64, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int64)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT32, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int32)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT16, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int16)
// MIPP_MACRO_LATE_EVAL(MIPP_MACRO_UINT8, MIPP_MACRO_LOGICAL_EMULATED_NOTB, avx, int8)

#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_AVX512_H_ */