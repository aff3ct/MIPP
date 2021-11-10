#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_EMULATED_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_EMULATED_H_

// ---------------------------------------------------------------------- fmadd

#define MIPP_MACRO_ARITHMETIC_EMULATED_FMADD(INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_fmadd_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd3) \
  { \
    return mipp_##INSTR_NAME_LO##_add_##TYPE##N_BITS(rvd3, mipp_##INSTR_NAME_LO##_mul_##TYPE##N_BITS(rvd1, rvd2)); \
  }

// --------------------------------------------------------------------- fnmadd

#define MIPP_MACRO_ARITHMETIC_EMULATED_FNMADD(INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_fnmadd_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd3) \
  { \
    return mipp_##INSTR_NAME_LO##_sub_##TYPE##N_BITS(rvd3, mipp_##INSTR_NAME_LO##_mul_##TYPE##N_BITS(rvd1, rvd2)); \
  }

// ---------------------------------------------------------------------- fmsub

#define MIPP_MACRO_ARITHMETIC_EMULATED_FMSUB(INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_fmsub_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd3) \
  { \
    return mipp_##INSTR_NAME_LO##_sub_##TYPE##N_BITS(mipp_##INSTR_NAME_LO##_mul_##TYPE##N_BITS(rvd1, rvd2), rvd3); \
  }

// --------------------------------------------------------------------- fnmsub

#define MIPP_MACRO_ARITHMETIC_EMULATED_FNMSUB(INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_fnmsub_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd2, rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd3) \
  { \
    return mipp_##INSTR_NAME_LO##_sub_##TYPE##N_BITS(mipp_##INSTR_NAME_LO##_sub_##TYPE##N_BITS(mipp_##INSTR_NAME_LO##_set0_##TYPE##N_BITS(), mipp_##INSTR_NAME_LO##_mul_##TYPE##N_BITS(rvd1, rvd2)), rvd3); \
  }

// ----------------------------------------------------------------------- notb

#define MIPP_MACRO_LOGICAL_EMULATED_NOTB(INSTR_NAME_LO, N_BITS, TYPE, UNUSED_INTEL_TYPE, UNUSED_INTEL_LDST_TYPE, UNUSED_CAST_TYPE) \
  rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t mipp_##INSTR_NAME_LO##_notb_##TYPE##N_BITS(rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd1) \
  { \
    rvd_##INSTR_NAME_LO##_##TYPE##N_BITS_HACK##_t rvd_tmp = mipp_##INSTR_NAME_LO##_set1_int##N_BITS((FULL_TYPE_HACK##_t)-1); \
    rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t rvd_ones; \
    rvd_ones.m = (rvd_##INSTR_NAME_LO##_##TYPE##N_BITS##_t)rvd_tmp.m; \
    return mipp_##INSTR_NAME_LO##_andnb_##TYPE##N_BITS(rvd1, rvd_ones); \
  }

#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_EMULATED_H_ */