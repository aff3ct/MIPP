#ifndef MY_INTRINSICS_PLUS_PLUS_TOOLS_H_
#define MY_INTRINSICS_PLUS_PLUS_TOOLS_H_

#include <stdlib.h> // exit
#include <stdio.h> // printf

// -------------------------------------------------------------- generic macro
#define MIPP_LMUL1 1

#define MIPP_MACRO_LATE_EVAL(MACRO, ...) \
  MACRO(__VA_ARGS__)

#define MIPP_MACRO_ALL_FLOAT(MACRO, ...) \
  MIPP_MACRO_FLOAT64(MACRO, __VA_ARGS__) \
  MIPP_MACRO_FLOAT32(MACRO, __VA_ARGS__)

#define MIPP_MACRO_ALL_INT(MACRO, ...) \
  MIPP_MACRO_INT64(MACRO, __VA_ARGS__) \
  MIPP_MACRO_INT32(MACRO, __VA_ARGS__) \
  MIPP_MACRO_INT16(MACRO, __VA_ARGS__) \
  MIPP_MACRO_INT8(MACRO, __VA_ARGS__)

#define MIPP_MACRO_ALL_UINT(MACRO, ...) \
  MIPP_MACRO_UINT64(MACRO, __VA_ARGS__) \
  MIPP_MACRO_UINT32(MACRO, __VA_ARGS__) \
  MIPP_MACRO_UINT16(MACRO, __VA_ARGS__) \
  MIPP_MACRO_UINT8(MACRO, __VA_ARGS__)

#define MIPP_MACRO_ALL_INT_AND_UINT(MACRO, ...) \
  MIPP_MACRO_ALL_INT(MACRO, __VA_ARGS__) \
  MIPP_MACRO_ALL_UINT(MACRO, __VA_ARGS__)

#define MIPP_MACRO_ALL_TYPES(MACRO, ...) \
  MIPP_MACRO_ALL_FLOAT(MACRO, __VA_ARGS__) \
  MIPP_MACRO_ALL_INT_AND_UINT(MACRO, __VA_ARGS__)

#define MIPP_MACRO_LMUL2(MACRO, ...) \
  MIPP_MACRO_ALL_TYPES(MACRO, __VA_ARGS__, 2, 1)

#define MIPP_MACRO_LMUL4(MACRO, ...) \
  MIPP_MACRO_ALL_TYPES(MACRO, __VA_ARGS__, 4, 2)

#define MIPP_MACRO_LMUL8(MACRO, ...) \
  MIPP_MACRO_ALL_TYPES(MACRO, __VA_ARGS__, 8, 4)

#define MIPP_MACRO_ALL_LMUL(MACRO, ...) \
  MIPP_MACRO_LMUL2(MACRO, __VA_ARGS__) \
  MIPP_MACRO_LMUL4(MACRO, __VA_ARGS__) \
  MIPP_MACRO_LMUL8(MACRO, __VA_ARGS__)

// ----------------------------------------------------------- error management

#define MIPP_MACRO_UNIMPLEMENTED_SET1(MIPP_NAME, INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_##MIPP_NAME##_##TYPE##N_BITS(TYPE##N_BITS##_t val) \
  { \
    printf("ERROR: 'mipp_%s_%s_%s%s' is not supported!\n", #INSTR_NAME_LO, #MIPP_NAME, #TYPE, #N_BITS); \
    exit(-1); \
  }

#define MIPP_MACRO_UNIMPLEMENTED_1ARG(MIPP_NAME, INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_##MIPP_NAME##_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd) \
  { \
    printf("ERROR: 'mipp_%s_%s_%s%s' is not supported!\n", #INSTR_NAME_LO, #MIPP_NAME, #TYPE, #N_BITS); \
    exit(-1); \
  }

#define MIPP_MACRO_UNIMPLEMENTED_2ARGS(MIPP_NAME, INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_##MIPP_NAME##_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2) \
  { \
    printf("ERROR: 'mipp_%s_%s_%s%s' is not supported!\n", #INSTR_NAME_LO, #MIPP_NAME, #TYPE, #N_BITS); \
    exit(-1); \
  }

#define MIPP_MACRO_UNIMPLEMENTED_3ARGS(MIPP_NAME, INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_##MIPP_NAME##_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd3) \
  { \
    printf("ERROR: 'mipp_%s_%s_%s%s' is not supported!\n", #INSTR_NAME_LO, #MIPP_NAME, #TYPE, #N_BITS); \
    exit(-1); \
  }

#define MIPP_MACRO_UNIMPLEMENTED_XSHIFTR(MIPP_NAME, INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_##MIPP_NAME##_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_int##N_BITS##_t rvd2) \
  { \
    printf("ERROR: 'mipp_%s_%s_%s%s' is not supported!\n", #INSTR_NAME_LO, #MIPP_NAME, #TYPE, #N_BITS); \
    exit(-1); \
  }

#endif /* MY_INTRINSICS_PLUS_PLUS_TOOLS_H_ */