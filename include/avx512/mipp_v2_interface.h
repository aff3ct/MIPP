#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_

#include "mipp_v2.h"

// ----------------------------------------------------------------------------
// -------------------------------------------------- MIPP C portable interface
// ----------------------------------------------------------------------------

// ---------------------------------------------------------------- definitions

#if defined(__AVX__)
#define MIPP_INSTR_NAME_UP AVX
#define MIPP_INSTR_NAME_LO avx

#define MIPP_RVD_SIZE_BIT  MIPP_AVX_RVD_SIZE_BIT
#define MIPP_RVD_SIZE_BYTE MIPP_AVX_RVD_SIZE_BYTE

#define MIPP_N_FLOAT64 MIPP_AVX_N_FLOAT64
#define MIPP_N_FLOAT32 MIPP_AVX_N_FLOAT32
#define MIPP_N_INT64   MIPP_AVX_N_INT64
#define MIPP_N_INT32   MIPP_AVX_N_INT32
#define MIPP_N_INT16   MIPP_AVX_N_INT16
#define MIPP_N_INT8    MIPP_AVX_N_INT8
#define MIPP_N_UINT64  MIPP_AVX_N_UINT64
#define MIPP_N_UINT32  MIPP_AVX_N_UINT32
#define MIPP_N_UINT16  MIPP_AVX_N_UINT16
#define MIPP_N_UINT8   MIPP_AVX_N_UINT8
#endif

// ---------------- declaration of the data/mask vector registers (rvd and rvm)

#define MIPP_MACRO_GEN_RV(INSTR_NAME_SMALL, DATA_OR_MASK, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  typedef rv##DATA_OR_MASK##_##INSTR_NAME_SMALL##_##TYPE##N_BITS##_t rv##DATA_OR_MASK##_##TYPE##N_BITS##_t;

MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_GEN_RV, MIPP_INSTR_NAME_LO, d)
MIPP_MACRO_LATE_EVAL(MIPP_MACRO_ALL_TYPES, MIPP_MACRO_GEN_RV, MIPP_INSTR_NAME_LO, m)

// --------------------------------------------------------------- load / store

#define MIPP_MACRO_LOAD_GENERIC(INSTR_NAME_SMALL, MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_t mipp_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t *mem_addr) { \
    return (rvd_##TYPE##N_BITS##_t) mipp_##INSTR_NAME_SMALL##_##MIPP_NAME##_##TYPE##N_BITS(mem_addr); \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_GENERIC, MIPP_INSTR_NAME_LO, loadu)
MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_GENERIC, MIPP_INSTR_NAME_LO, load )

#define MIPP_MACRO_STORE_GENERIC(INSTR_NAME_SMALL, MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  void mipp_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t *mem_addr, rvd_##TYPE##N_BITS##_t rvd) { \
    mipp_##INSTR_NAME_SMALL##_##MIPP_NAME##_##TYPE##N_BITS(mem_addr, (rvd_##INSTR_NAME_SMALL##_##TYPE##N_BITS##_t) rvd); \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_GENERIC, MIPP_INSTR_NAME_LO, storeu)
MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_GENERIC, MIPP_INSTR_NAME_LO, store )

// ------------------------------------------------------------------------ add

#define MIPP_MACRO_ARITHMETIC_2ARGS_GENERIC(INSTR_NAME_SMALL, MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_t mipp_##MIPP_NAME##_##TYPE##N_BITS(rvd_##TYPE##N_BITS##_t rvd1, rvd_##TYPE##N_BITS##_t rvd2) { \
    return (rvd_##TYPE##N_BITS##_t) mipp_##INSTR_NAME_SMALL##_##MIPP_NAME##_##TYPE##N_BITS((rvd_##INSTR_NAME_SMALL##_##TYPE##N_BITS##_t) rvd1, (rvd_##INSTR_NAME_SMALL##_##TYPE##N_BITS##_t) rvd2); \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_ARITHMETIC_2ARGS_GENERIC, MIPP_INSTR_NAME_LO, add)

// ------------------------------------------------------------------------ sub

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_ARITHMETIC_2ARGS_GENERIC, MIPP_INSTR_NAME_LO, sub)

// ----------------------------------------------------------------------------
// ------------------------------------------------------------- LMUL emulation
// ----------------------------------------------------------------------------
#if !defined(__riscv_vector)

#define MIPP_N_FLOAT64_M1 MIPP_N_FLOAT64
#define MIPP_N_FLOAT32_M1 MIPP_N_FLOAT32
#define MIPP_N_INT64_M1   MIPP_N_INT64
#define MIPP_N_INT32_M1   MIPP_N_INT32
#define MIPP_N_INT16_M1   MIPP_N_INT16
#define MIPP_N_INT8_M1    MIPP_N_INT8
#define MIPP_N_UINT64_M1  MIPP_N_UINT64
#define MIPP_N_UINT32_M1  MIPP_N_UINT32
#define MIPP_N_UINT16_M1  MIPP_N_UINT16
#define MIPP_N_UINT8_M1   MIPP_N_UINT8

#define MIPP_N_FLOAT64_M2 (MIPP_N_FLOAT64_M1 * 2)
#define MIPP_N_FLOAT32_M2 (MIPP_N_FLOAT32_M1 * 2)
#define   MIPP_N_INT64_M2 (  MIPP_N_INT64_M1 * 2)
#define   MIPP_N_INT32_M2 (  MIPP_N_INT32_M1 * 2)
#define   MIPP_N_INT16_M2 (  MIPP_N_INT16_M1 * 2)
#define    MIPP_N_INT8_M2 (   MIPP_N_INT8_M1 * 2)
#define  MIPP_N_UINT64_M2 ( MIPP_N_UINT64_M1 * 2)
#define  MIPP_N_UINT32_M2 ( MIPP_N_UINT32_M1 * 2)
#define  MIPP_N_UINT16_M2 ( MIPP_N_UINT16_M1 * 2)
#define   MIPP_N_UINT8_M2 (  MIPP_N_UINT8_M1 * 2)

#define MIPP_N_FLOAT64_M4 (MIPP_N_FLOAT64_M1 * 4)
#define MIPP_N_FLOAT32_M4 (MIPP_N_FLOAT32_M1 * 4)
#define   MIPP_N_INT64_M4 (  MIPP_N_INT64_M1 * 4)
#define   MIPP_N_INT32_M4 (  MIPP_N_INT32_M1 * 4)
#define   MIPP_N_INT16_M4 (  MIPP_N_INT16_M1 * 4)
#define    MIPP_N_INT8_M4 (   MIPP_N_INT8_M1 * 4)
#define  MIPP_N_UINT64_M4 ( MIPP_N_UINT64_M1 * 4)
#define  MIPP_N_UINT32_M4 ( MIPP_N_UINT32_M1 * 4)
#define  MIPP_N_UINT16_M4 ( MIPP_N_UINT16_M1 * 4)
#define   MIPP_N_UINT8_M4 (  MIPP_N_UINT8_M1 * 4)

#define MIPP_N_FLOAT64_M8 (MIPP_N_FLOAT64_M1 * 8)
#define MIPP_N_FLOAT32_M8 (MIPP_N_FLOAT32_M1 * 8)
#define   MIPP_N_INT64_M8 (  MIPP_N_INT64_M1 * 8)
#define   MIPP_N_INT32_M8 (  MIPP_N_INT32_M1 * 8)
#define   MIPP_N_INT16_M8 (  MIPP_N_INT16_M1 * 8)
#define    MIPP_N_INT8_M8 (   MIPP_N_INT8_M1 * 8)
#define  MIPP_N_UINT64_M8 ( MIPP_N_UINT64_M1 * 8)
#define  MIPP_N_UINT32_M8 ( MIPP_N_UINT32_M1 * 8)
#define  MIPP_N_UINT16_M8 ( MIPP_N_UINT16_M1 * 8)
#define   MIPP_N_UINT8_M8 (  MIPP_N_UINT8_M1 * 8)

typedef rvd_float64_t rvd_float64_m1_t;
typedef rvd_float32_t rvd_float32_m1_t;
typedef rvd_int64_t   rvd_int64_m1_t;
typedef rvd_int32_t   rvd_int32_m1_t;
typedef rvd_int16_t   rvd_int16_m1_t;
typedef rvd_int8_t    rvd_int8_m1_t;
typedef rvd_uint64_t  rvd_uint64_m1_t;
typedef rvd_uint32_t  rvd_uint32_m1_t;
typedef rvd_uint16_t  rvd_uint16_m1_t;
typedef rvd_uint8_t   rvd_uint8_m1_t;

typedef struct { rvd_float64_m1_t m1, m2; } rvd_float64_m2_t;
typedef struct { rvd_float32_m1_t m1, m2; } rvd_float32_m2_t;
typedef struct { rvd_int64_m1_t   m1, m2; } rvd_int64_m2_t;
typedef struct { rvd_int32_m1_t   m1, m2; } rvd_int32_m2_t;
typedef struct { rvd_int16_m1_t   m1, m2; } rvd_int16_m2_t;
typedef struct { rvd_int8_m1_t    m1, m2; } rvd_int8_m2_t;
typedef struct { rvd_uint64_m1_t  m1, m2; } rvd_uint64_m2_t;
typedef struct { rvd_uint32_m1_t  m1, m2; } rvd_uint32_m2_t;
typedef struct { rvd_uint16_m1_t  m1, m2; } rvd_uint16_m2_t;
typedef struct { rvd_uint8_m1_t   m1, m2; } rvd_uint8_m2_t;

typedef struct { rvd_float64_m2_t m1, m2; } rvd_float64_m4_t;
typedef struct { rvd_float32_m2_t m1, m2; } rvd_float32_m4_t;
typedef struct { rvd_int64_m2_t   m1, m2; } rvd_int64_m4_t;
typedef struct { rvd_int32_m2_t   m1, m2; } rvd_int32_m4_t;
typedef struct { rvd_int16_m2_t   m1, m2; } rvd_int16_m4_t;
typedef struct { rvd_int8_m2_t    m1, m2; } rvd_int8_m4_t;
typedef struct { rvd_uint64_m2_t  m1, m2; } rvd_uint64_m4_t;
typedef struct { rvd_uint32_m2_t  m1, m2; } rvd_uint32_m4_t;
typedef struct { rvd_uint16_m2_t  m1, m2; } rvd_uint16_m4_t;
typedef struct { rvd_uint8_m2_t   m1, m2; } rvd_uint8_m4_t;

typedef struct { rvd_float64_m4_t m1, m2; } rvd_float64_m8_t;
typedef struct { rvd_float32_m4_t m1, m2; } rvd_float32_m8_t;
typedef struct { rvd_int64_m4_t   m1, m2; } rvd_int64_m8_t;
typedef struct { rvd_int32_m4_t   m1, m2; } rvd_int32_m8_t;
typedef struct { rvd_int16_m4_t   m1, m2; } rvd_int16_m8_t;
typedef struct { rvd_int8_m4_t    m1, m2; } rvd_int8_m8_t;
typedef struct { rvd_uint64_m4_t  m1, m2; } rvd_uint64_m8_t;
typedef struct { rvd_uint32_m4_t  m1, m2; } rvd_uint32_m8_t;
typedef struct { rvd_uint16_m4_t  m1, m2; } rvd_uint16_m8_t;
typedef struct { rvd_uint8_m4_t   m1, m2; } rvd_uint8_m8_t;

#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))

// --------------------------------------------------------------- load / loadu

#define MIPP_MACRO_LOAD_LMUL1(MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_m1_t mipp_##MIPP_NAME##_##TYPE##N_BITS##_m1(TYPE##N_BITS##_t *mem_addr) { \
    return mipp_##MIPP_NAME##_##TYPE##N_BITS(mem_addr); \
  }

#define MIPP_MACRO_LOAD_LMULX(MIPP_NAME, LMUL, LMUL_PREV, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_m##LMUL##_t mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL(TYPE##N_BITS##_t *mem_addr) { \
    rvd_##TYPE##N_BITS##_m##LMUL##_t rvd; \
    rvd.m1 = mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(mem_addr); \
    rvd.m2 = mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), LMUL_PREV)); \
    return rvd; \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_LMUL1, load)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_LOAD_LMULX, load)

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_LOAD_LMUL1, loadu)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_LOAD_LMULX, loadu)

// ------------------------------------------------------------- store / storeu

#define MIPP_MACRO_STORE_LMUL1(MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  void mipp_##MIPP_NAME##_##TYPE##N_BITS##_m1(TYPE##N_BITS##_t *mem_addr, rvd_##TYPE##N_BITS##_m1_t rvd) { \
    mipp_##MIPP_NAME##_##TYPE##N_BITS(mem_addr, rvd); \
  }

#define MIPP_MACRO_STORE_LMULX(MIPP_NAME, LMUL, LMUL_PREV, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  void mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL(TYPE##N_BITS##_t *mem_addr, rvd_##TYPE##N_BITS##_m##LMUL##_t rvd) { \
    mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(mem_addr, rvd.m1); \
    mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), LMUL_PREV), rvd.m2); \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_LMUL1, store)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_STORE_LMULX, store)

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_STORE_LMUL1, storeu)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_STORE_LMULX, storeu)

// ------------------------------------------------------------------------ add

#define MIPP_MACRO_ARITHMETIC_2ARGS_LMUL1(MIPP_NAME, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_m1_t mipp_##MIPP_NAME##_##TYPE##N_BITS##_m1(rvd_##TYPE##N_BITS##_m1_t rvd1, rvd_##TYPE##N_BITS##_m1_t rvd2) { \
    return mipp_##MIPP_NAME##_##TYPE##N_BITS(rvd1, rvd2); \
  }

#define MIPP_MACRO_ARITHMETIC_2ARGS_LMULX(MIPP_NAME, LMUL, LMUL_PREV, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##TYPE##N_BITS##_m##LMUL##_t mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL(rvd_##TYPE##N_BITS##_m##LMUL##_t rvd1, rvd_##TYPE##N_BITS##_m##LMUL##_t rvd2) { \
    rvd_##TYPE##N_BITS##_m##LMUL##_t rvd; \
    rvd.m1 = mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(rvd1.m1, rvd2.m1); \
    rvd.m2 = mipp_##MIPP_NAME##_##TYPE##N_BITS##_m##LMUL_PREV(rvd1.m2, rvd2.m2); \
    return rvd; \
  }

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_ARITHMETIC_2ARGS_LMUL1, add)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_ARITHMETIC_2ARGS_LMULX, add)

// ------------------------------------------------------------------------ sub

MIPP_MACRO_ALL_TYPES(MIPP_MACRO_ARITHMETIC_2ARGS_LMUL1, sub)
MIPP_MACRO_ALL_LMUL(MIPP_MACRO_ARITHMETIC_2ARGS_LMULX, sub)

#endif

#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */