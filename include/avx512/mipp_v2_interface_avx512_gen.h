#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#include "mipp_v2.h" 
#if defined(__AVX__)
#define MIPP_RVD_SIZE_BIT MIPP_AVX_RVD_SIZE_BIT
#define MIPP_RVD_SIZE_BYTE MIPP_AVX_RVD_SIZE_BYTE
#define MIPP_N_FLOAT64 MIPP_AVX_N_FLOAT64
#define MIPP_N_FLOAT32 MIPP_AVX_N_FLOAT32
#define MIPP_N_INT64 MIPP_AVX_N_INT64
#define MIPP_N_INT32 MIPP_AVX_N_INT32
#define MIPP_N_INT16 MIPP_AVX_N_INT16
#define MIPP_N_INT8 MIPP_AVX_N_INT8
#define MIPP_N_UINT64 MIPP_AVX_N_UINT64
#define MIPP_N_UINT32 MIPP_AVX_N_UINT32
#define MIPP_N_UINT16 MIPP_AVX_N_UINT16
#define MIPP_N_UINT8 MIPP_AVX_N_UINT8
#endif
#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))
#define MIPP_N_FLOAT64_M1 (MIPP_N_FLOAT64 * 1)
#define MIPP_N_FLOAT32_M1 (MIPP_N_FLOAT32 * 1)
#define MIPP_N_INT64_M1 (MIPP_N_INT64 * 1)
#define MIPP_N_INT32_M1 (MIPP_N_INT32 * 1)
#define MIPP_N_INT16_M1 (MIPP_N_INT16 * 1)
#define MIPP_N_INT8_M1 (MIPP_N_INT8 * 1)
#define MIPP_N_UINT64_M1 (MIPP_N_UINT64 * 1)
#define MIPP_N_UINT32_M1 (MIPP_N_UINT32 * 1)
#define MIPP_N_UINT16_M1 (MIPP_N_UINT16 * 1)
#define MIPP_N_UINT8_M1 (MIPP_N_UINT8 * 1)
#define MIPP_N_FLOAT64_M2 (MIPP_N_FLOAT64 * 2)
#define MIPP_N_FLOAT32_M2 (MIPP_N_FLOAT32 * 2)
#define MIPP_N_INT64_M2 (MIPP_N_INT64 * 2)
#define MIPP_N_INT32_M2 (MIPP_N_INT32 * 2)
#define MIPP_N_INT16_M2 (MIPP_N_INT16 * 2)
#define MIPP_N_INT8_M2 (MIPP_N_INT8 * 2)
#define MIPP_N_UINT64_M2 (MIPP_N_UINT64 * 2)
#define MIPP_N_UINT32_M2 (MIPP_N_UINT32 * 2)
#define MIPP_N_UINT16_M2 (MIPP_N_UINT16 * 2)
#define MIPP_N_UINT8_M2 (MIPP_N_UINT8 * 2)
#define MIPP_N_FLOAT64_M4 (MIPP_N_FLOAT64 * 4)
#define MIPP_N_FLOAT32_M4 (MIPP_N_FLOAT32 * 4)
#define MIPP_N_INT64_M4 (MIPP_N_INT64 * 4)
#define MIPP_N_INT32_M4 (MIPP_N_INT32 * 4)
#define MIPP_N_INT16_M4 (MIPP_N_INT16 * 4)
#define MIPP_N_INT8_M4 (MIPP_N_INT8 * 4)
#define MIPP_N_UINT64_M4 (MIPP_N_UINT64 * 4)
#define MIPP_N_UINT32_M4 (MIPP_N_UINT32 * 4)
#define MIPP_N_UINT16_M4 (MIPP_N_UINT16 * 4)
#define MIPP_N_UINT8_M4 (MIPP_N_UINT8 * 4)
#define MIPP_N_FLOAT64_M8 (MIPP_N_FLOAT64 * 8)
#define MIPP_N_FLOAT32_M8 (MIPP_N_FLOAT32 * 8)
#define MIPP_N_INT64_M8 (MIPP_N_INT64 * 8)
#define MIPP_N_INT32_M8 (MIPP_N_INT32 * 8)
#define MIPP_N_INT16_M8 (MIPP_N_INT16 * 8)
#define MIPP_N_INT8_M8 (MIPP_N_INT8 * 8)
#define MIPP_N_UINT64_M8 (MIPP_N_UINT64 * 8)
#define MIPP_N_UINT32_M8 (MIPP_N_UINT32 * 8)
#define MIPP_N_UINT16_M8 (MIPP_N_UINT16 * 8)
#define MIPP_N_UINT8_M8 (MIPP_N_UINT8 * 8)
#if defined(__AVX__)
typedef rvd_avx_float64_t rvd_float64_t;
typedef rvd_avx_float32_t rvd_float32_t;
typedef rvd_avx_int64_t rvd_int64_t;
typedef rvd_avx_int32_t rvd_int32_t;
typedef rvd_avx_int16_t rvd_int16_t;
typedef rvd_avx_int8_t rvd_int8_t;
typedef rvd_avx_uint64_t rvd_uint64_t;
typedef rvd_avx_uint32_t rvd_uint32_t;
typedef rvd_avx_uint16_t rvd_uint16_t;
typedef rvd_avx_uint8_t rvd_uint8_t;
typedef rvm_avx_float64_t rvm_float64_t;
typedef rvm_avx_float32_t rvm_float32_t;
typedef rvm_avx_int64_t rvm_int64_t;
typedef rvm_avx_int32_t rvm_int32_t;
typedef rvm_avx_int16_t rvm_int16_t;
typedef rvm_avx_int8_t rvm_int8_t;
typedef rvm_avx_uint64_t rvm_uint64_t;
typedef rvm_avx_uint32_t rvm_uint32_t;
typedef rvm_avx_uint16_t rvm_uint16_t;
typedef rvm_avx_uint8_t rvm_uint8_t;
#endif
typedef rvd_float64_t rvd_float64_m1_t;
typedef rvd_float32_t rvd_float32_m1_t;
typedef rvd_int64_t rvd_int64_m1_t;
typedef rvd_int32_t rvd_int32_m1_t;
typedef rvd_int16_t rvd_int16_m1_t;
typedef rvd_int8_t rvd_int8_m1_t;
typedef rvd_uint64_t rvd_uint64_m1_t;
typedef rvd_uint32_t rvd_uint32_m1_t;
typedef rvd_uint16_t rvd_uint16_m1_t;
typedef rvd_uint8_t rvd_uint8_m1_t;
typedef rvm_float64_t rvm_float64_m1_t;
typedef rvm_float32_t rvm_float32_m1_t;
typedef rvm_int64_t rvm_int64_m1_t;
typedef rvm_int32_t rvm_int32_m1_t;
typedef rvm_int16_t rvm_int16_m1_t;
typedef rvm_int8_t rvm_int8_m1_t;
typedef rvm_uint64_t rvm_uint64_m1_t;
typedef rvm_uint32_t rvm_uint32_m1_t;
typedef rvm_uint16_t rvm_uint16_m1_t;
typedef rvm_uint8_t rvm_uint8_m1_t;
typedef struct { rvd_float64_m1_t m1, m2; } rvd_float64_m2_t;
typedef struct { rvd_float32_m1_t m1, m2; } rvd_float32_m2_t;
typedef struct { rvd_int64_m1_t m1, m2; } rvd_int64_m2_t;
typedef struct { rvd_int32_m1_t m1, m2; } rvd_int32_m2_t;
typedef struct { rvd_int16_m1_t m1, m2; } rvd_int16_m2_t;
typedef struct { rvd_int8_m1_t m1, m2; } rvd_int8_m2_t;
typedef struct { rvd_uint64_m1_t m1, m2; } rvd_uint64_m2_t;
typedef struct { rvd_uint32_m1_t m1, m2; } rvd_uint32_m2_t;
typedef struct { rvd_uint16_m1_t m1, m2; } rvd_uint16_m2_t;
typedef struct { rvd_uint8_m1_t m1, m2; } rvd_uint8_m2_t;
typedef struct { rvd_float64_m2_t m1, m2; } rvd_float64_m4_t;
typedef struct { rvd_float32_m2_t m1, m2; } rvd_float32_m4_t;
typedef struct { rvd_int64_m2_t m1, m2; } rvd_int64_m4_t;
typedef struct { rvd_int32_m2_t m1, m2; } rvd_int32_m4_t;
typedef struct { rvd_int16_m2_t m1, m2; } rvd_int16_m4_t;
typedef struct { rvd_int8_m2_t m1, m2; } rvd_int8_m4_t;
typedef struct { rvd_uint64_m2_t m1, m2; } rvd_uint64_m4_t;
typedef struct { rvd_uint32_m2_t m1, m2; } rvd_uint32_m4_t;
typedef struct { rvd_uint16_m2_t m1, m2; } rvd_uint16_m4_t;
typedef struct { rvd_uint8_m2_t m1, m2; } rvd_uint8_m4_t;
typedef struct { rvd_float64_m4_t m1, m2; } rvd_float64_m8_t;
typedef struct { rvd_float32_m4_t m1, m2; } rvd_float32_m8_t;
typedef struct { rvd_int64_m4_t m1, m2; } rvd_int64_m8_t;
typedef struct { rvd_int32_m4_t m1, m2; } rvd_int32_m8_t;
typedef struct { rvd_int16_m4_t m1, m2; } rvd_int16_m8_t;
typedef struct { rvd_int8_m4_t m1, m2; } rvd_int8_m8_t;
typedef struct { rvd_uint64_m4_t m1, m2; } rvd_uint64_m8_t;
typedef struct { rvd_uint32_m4_t m1, m2; } rvd_uint32_m8_t;
typedef struct { rvd_uint16_m4_t m1, m2; } rvd_uint16_m8_t;
typedef struct { rvd_uint8_m4_t m1, m2; } rvd_uint8_m8_t;
typedef struct { rvm_float64_m1_t m1, m2; } rvm_float64_m2_t;
typedef struct { rvm_float32_m1_t m1, m2; } rvm_float32_m2_t;
typedef struct { rvm_int64_m1_t m1, m2; } rvm_int64_m2_t;
typedef struct { rvm_int32_m1_t m1, m2; } rvm_int32_m2_t;
typedef struct { rvm_int16_m1_t m1, m2; } rvm_int16_m2_t;
typedef struct { rvm_int8_m1_t m1, m2; } rvm_int8_m2_t;
typedef struct { rvm_uint64_m1_t m1, m2; } rvm_uint64_m2_t;
typedef struct { rvm_uint32_m1_t m1, m2; } rvm_uint32_m2_t;
typedef struct { rvm_uint16_m1_t m1, m2; } rvm_uint16_m2_t;
typedef struct { rvm_uint8_m1_t m1, m2; } rvm_uint8_m2_t;
typedef struct { rvm_float64_m2_t m1, m2; } rvm_float64_m4_t;
typedef struct { rvm_float32_m2_t m1, m2; } rvm_float32_m4_t;
typedef struct { rvm_int64_m2_t m1, m2; } rvm_int64_m4_t;
typedef struct { rvm_int32_m2_t m1, m2; } rvm_int32_m4_t;
typedef struct { rvm_int16_m2_t m1, m2; } rvm_int16_m4_t;
typedef struct { rvm_int8_m2_t m1, m2; } rvm_int8_m4_t;
typedef struct { rvm_uint64_m2_t m1, m2; } rvm_uint64_m4_t;
typedef struct { rvm_uint32_m2_t m1, m2; } rvm_uint32_m4_t;
typedef struct { rvm_uint16_m2_t m1, m2; } rvm_uint16_m4_t;
typedef struct { rvm_uint8_m2_t m1, m2; } rvm_uint8_m4_t;
typedef struct { rvm_float64_m4_t m1, m2; } rvm_float64_m8_t;
typedef struct { rvm_float32_m4_t m1, m2; } rvm_float32_m8_t;
typedef struct { rvm_int64_m4_t m1, m2; } rvm_int64_m8_t;
typedef struct { rvm_int32_m4_t m1, m2; } rvm_int32_m8_t;
typedef struct { rvm_int16_m4_t m1, m2; } rvm_int16_m8_t;
typedef struct { rvm_int8_m4_t m1, m2; } rvm_int8_m8_t;
typedef struct { rvm_uint64_m4_t m1, m2; } rvm_uint64_m8_t;
typedef struct { rvm_uint32_m4_t m1, m2; } rvm_uint32_m8_t;
typedef struct { rvm_uint16_m4_t m1, m2; } rvm_uint16_m8_t;
typedef struct { rvm_uint8_m4_t m1, m2; } rvm_uint8_m8_t;
rvd_float64_t mipp_cast_float64_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_float64_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_float64(r0);
}
rvd_float64_m2_t mipp_cast_float64_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_float64_float64_m1(r0.m1);
	res.m2 = mipp_cast_float64_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_float64_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_float64_float64_m2(r0.m1);
	res.m2 = mipp_cast_float64_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_float64_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_float64_float64_m4(r0.m1);
	res.m2 = mipp_cast_float64_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_float32_float64(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_float32_float64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_float64(r0);
}
rvd_float64_m2_t mipp_cast_float32_float64_m2(const rvd_float32_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_float32_float64_m1(r0.m1);
	res.m2 = mipp_cast_float32_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_float32_float64_m4(const rvd_float32_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_float32_float64_m2(r0.m1);
	res.m2 = mipp_cast_float32_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_float32_float64_m8(const rvd_float32_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_float32_float64_m4(r0.m1);
	res.m2 = mipp_cast_float32_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_int64_float64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_int64_float64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_float64(r0);
}
rvd_float64_m2_t mipp_cast_int64_float64_m2(const rvd_int64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_int64_float64_m1(r0.m1);
	res.m2 = mipp_cast_int64_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_int64_float64_m4(const rvd_int64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_int64_float64_m2(r0.m1);
	res.m2 = mipp_cast_int64_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_int64_float64_m8(const rvd_int64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_int64_float64_m4(r0.m1);
	res.m2 = mipp_cast_int64_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_int32_float64(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_int32_float64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_float64(r0);
}
rvd_float64_m2_t mipp_cast_int32_float64_m2(const rvd_int32_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_int32_float64_m1(r0.m1);
	res.m2 = mipp_cast_int32_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_int32_float64_m4(const rvd_int32_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_int32_float64_m2(r0.m1);
	res.m2 = mipp_cast_int32_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_int32_float64_m8(const rvd_int32_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_int32_float64_m4(r0.m1);
	res.m2 = mipp_cast_int32_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_int16_float64(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_int16_float64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_float64(r0);
}
rvd_float64_m2_t mipp_cast_int16_float64_m2(const rvd_int16_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_int16_float64_m1(r0.m1);
	res.m2 = mipp_cast_int16_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_int16_float64_m4(const rvd_int16_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_int16_float64_m2(r0.m1);
	res.m2 = mipp_cast_int16_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_int16_float64_m8(const rvd_int16_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_int16_float64_m4(r0.m1);
	res.m2 = mipp_cast_int16_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_int8_float64(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_int8_float64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_float64(r0);
}
rvd_float64_m2_t mipp_cast_int8_float64_m2(const rvd_int8_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_int8_float64_m1(r0.m1);
	res.m2 = mipp_cast_int8_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_int8_float64_m4(const rvd_int8_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_int8_float64_m2(r0.m1);
	res.m2 = mipp_cast_int8_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_int8_float64_m8(const rvd_int8_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_int8_float64_m4(r0.m1);
	res.m2 = mipp_cast_int8_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_uint64_float64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_uint64_float64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_float64(r0);
}
rvd_float64_m2_t mipp_cast_uint64_float64_m2(const rvd_uint64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_uint64_float64_m1(r0.m1);
	res.m2 = mipp_cast_uint64_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_uint64_float64_m4(const rvd_uint64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_uint64_float64_m2(r0.m1);
	res.m2 = mipp_cast_uint64_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_uint64_float64_m8(const rvd_uint64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_uint64_float64_m4(r0.m1);
	res.m2 = mipp_cast_uint64_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_uint32_float64(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_uint32_float64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_float64(r0);
}
rvd_float64_m2_t mipp_cast_uint32_float64_m2(const rvd_uint32_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_uint32_float64_m1(r0.m1);
	res.m2 = mipp_cast_uint32_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_uint32_float64_m4(const rvd_uint32_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_uint32_float64_m2(r0.m1);
	res.m2 = mipp_cast_uint32_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_uint32_float64_m8(const rvd_uint32_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_uint32_float64_m4(r0.m1);
	res.m2 = mipp_cast_uint32_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_uint16_float64(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_uint16_float64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_float64(r0);
}
rvd_float64_m2_t mipp_cast_uint16_float64_m2(const rvd_uint16_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_uint16_float64_m1(r0.m1);
	res.m2 = mipp_cast_uint16_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_uint16_float64_m4(const rvd_uint16_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_uint16_float64_m2(r0.m1);
	res.m2 = mipp_cast_uint16_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_uint16_float64_m8(const rvd_uint16_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_uint16_float64_m4(r0.m1);
	res.m2 = mipp_cast_uint16_float64_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_cast_uint8_float64(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_float64(r0);
#endif
}
rvd_float64_m1_t mipp_cast_uint8_float64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_float64(r0);
}
rvd_float64_m2_t mipp_cast_uint8_float64_m2(const rvd_uint8_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_cast_uint8_float64_m1(r0.m1);
	res.m2 = mipp_cast_uint8_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_cast_uint8_float64_m4(const rvd_uint8_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_cast_uint8_float64_m2(r0.m1);
	res.m2 = mipp_cast_uint8_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_cast_uint8_float64_m8(const rvd_uint8_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_cast_uint8_float64_m4(r0.m1);
	res.m2 = mipp_cast_uint8_float64_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_float64_float32(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_float64_float32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_float32(r0);
}
rvd_float32_m2_t mipp_cast_float64_float32_m2(const rvd_float64_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_float64_float32_m1(r0.m1);
	res.m2 = mipp_cast_float64_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_float64_float32_m4(const rvd_float64_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_float64_float32_m2(r0.m1);
	res.m2 = mipp_cast_float64_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_float64_float32_m8(const rvd_float64_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_float64_float32_m4(r0.m1);
	res.m2 = mipp_cast_float64_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_float32_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_float32_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_float32(r0);
}
rvd_float32_m2_t mipp_cast_float32_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_float32_float32_m1(r0.m1);
	res.m2 = mipp_cast_float32_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_float32_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_float32_float32_m2(r0.m1);
	res.m2 = mipp_cast_float32_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_float32_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_float32_float32_m4(r0.m1);
	res.m2 = mipp_cast_float32_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_int64_float32(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_int64_float32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_float32(r0);
}
rvd_float32_m2_t mipp_cast_int64_float32_m2(const rvd_int64_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_int64_float32_m1(r0.m1);
	res.m2 = mipp_cast_int64_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_int64_float32_m4(const rvd_int64_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_int64_float32_m2(r0.m1);
	res.m2 = mipp_cast_int64_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_int64_float32_m8(const rvd_int64_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_int64_float32_m4(r0.m1);
	res.m2 = mipp_cast_int64_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_int32_float32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_int32_float32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_float32(r0);
}
rvd_float32_m2_t mipp_cast_int32_float32_m2(const rvd_int32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_int32_float32_m1(r0.m1);
	res.m2 = mipp_cast_int32_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_int32_float32_m4(const rvd_int32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_int32_float32_m2(r0.m1);
	res.m2 = mipp_cast_int32_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_int32_float32_m8(const rvd_int32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_int32_float32_m4(r0.m1);
	res.m2 = mipp_cast_int32_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_int16_float32(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_int16_float32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_float32(r0);
}
rvd_float32_m2_t mipp_cast_int16_float32_m2(const rvd_int16_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_int16_float32_m1(r0.m1);
	res.m2 = mipp_cast_int16_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_int16_float32_m4(const rvd_int16_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_int16_float32_m2(r0.m1);
	res.m2 = mipp_cast_int16_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_int16_float32_m8(const rvd_int16_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_int16_float32_m4(r0.m1);
	res.m2 = mipp_cast_int16_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_int8_float32(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_int8_float32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_float32(r0);
}
rvd_float32_m2_t mipp_cast_int8_float32_m2(const rvd_int8_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_int8_float32_m1(r0.m1);
	res.m2 = mipp_cast_int8_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_int8_float32_m4(const rvd_int8_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_int8_float32_m2(r0.m1);
	res.m2 = mipp_cast_int8_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_int8_float32_m8(const rvd_int8_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_int8_float32_m4(r0.m1);
	res.m2 = mipp_cast_int8_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_uint64_float32(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_uint64_float32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_float32(r0);
}
rvd_float32_m2_t mipp_cast_uint64_float32_m2(const rvd_uint64_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_uint64_float32_m1(r0.m1);
	res.m2 = mipp_cast_uint64_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_uint64_float32_m4(const rvd_uint64_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_uint64_float32_m2(r0.m1);
	res.m2 = mipp_cast_uint64_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_uint64_float32_m8(const rvd_uint64_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_uint64_float32_m4(r0.m1);
	res.m2 = mipp_cast_uint64_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_uint32_float32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_uint32_float32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_float32(r0);
}
rvd_float32_m2_t mipp_cast_uint32_float32_m2(const rvd_uint32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_uint32_float32_m1(r0.m1);
	res.m2 = mipp_cast_uint32_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_uint32_float32_m4(const rvd_uint32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_uint32_float32_m2(r0.m1);
	res.m2 = mipp_cast_uint32_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_uint32_float32_m8(const rvd_uint32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_uint32_float32_m4(r0.m1);
	res.m2 = mipp_cast_uint32_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_uint16_float32(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_uint16_float32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_float32(r0);
}
rvd_float32_m2_t mipp_cast_uint16_float32_m2(const rvd_uint16_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_uint16_float32_m1(r0.m1);
	res.m2 = mipp_cast_uint16_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_uint16_float32_m4(const rvd_uint16_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_uint16_float32_m2(r0.m1);
	res.m2 = mipp_cast_uint16_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_uint16_float32_m8(const rvd_uint16_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_uint16_float32_m4(r0.m1);
	res.m2 = mipp_cast_uint16_float32_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_cast_uint8_float32(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_float32(r0);
#endif
}
rvd_float32_m1_t mipp_cast_uint8_float32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_float32(r0);
}
rvd_float32_m2_t mipp_cast_uint8_float32_m2(const rvd_uint8_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_cast_uint8_float32_m1(r0.m1);
	res.m2 = mipp_cast_uint8_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_cast_uint8_float32_m4(const rvd_uint8_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_cast_uint8_float32_m2(r0.m1);
	res.m2 = mipp_cast_uint8_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_cast_uint8_float32_m8(const rvd_uint8_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_cast_uint8_float32_m4(r0.m1);
	res.m2 = mipp_cast_uint8_float32_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_float64_int64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_float64_int64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int64(r0);
}
rvd_int64_m2_t mipp_cast_float64_int64_m2(const rvd_float64_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_float64_int64_m1(r0.m1);
	res.m2 = mipp_cast_float64_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_float64_int64_m4(const rvd_float64_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_float64_int64_m2(r0.m1);
	res.m2 = mipp_cast_float64_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_float64_int64_m8(const rvd_float64_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_float64_int64_m4(r0.m1);
	res.m2 = mipp_cast_float64_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_float32_int64(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_float32_int64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int64(r0);
}
rvd_int64_m2_t mipp_cast_float32_int64_m2(const rvd_float32_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_float32_int64_m1(r0.m1);
	res.m2 = mipp_cast_float32_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_float32_int64_m4(const rvd_float32_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_float32_int64_m2(r0.m1);
	res.m2 = mipp_cast_float32_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_float32_int64_m8(const rvd_float32_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_float32_int64_m4(r0.m1);
	res.m2 = mipp_cast_float32_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_int64_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_int64_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int64(r0);
}
rvd_int64_m2_t mipp_cast_int64_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_int64_int64_m1(r0.m1);
	res.m2 = mipp_cast_int64_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_int64_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_int64_int64_m2(r0.m1);
	res.m2 = mipp_cast_int64_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_int64_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_int64_int64_m4(r0.m1);
	res.m2 = mipp_cast_int64_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_int32_int64(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_int32_int64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int64(r0);
}
rvd_int64_m2_t mipp_cast_int32_int64_m2(const rvd_int32_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_int32_int64_m1(r0.m1);
	res.m2 = mipp_cast_int32_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_int32_int64_m4(const rvd_int32_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_int32_int64_m2(r0.m1);
	res.m2 = mipp_cast_int32_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_int32_int64_m8(const rvd_int32_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_int32_int64_m4(r0.m1);
	res.m2 = mipp_cast_int32_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_int16_int64(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_int16_int64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int64(r0);
}
rvd_int64_m2_t mipp_cast_int16_int64_m2(const rvd_int16_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_int16_int64_m1(r0.m1);
	res.m2 = mipp_cast_int16_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_int16_int64_m4(const rvd_int16_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_int16_int64_m2(r0.m1);
	res.m2 = mipp_cast_int16_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_int16_int64_m8(const rvd_int16_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_int16_int64_m4(r0.m1);
	res.m2 = mipp_cast_int16_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_int8_int64(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_int8_int64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int64(r0);
}
rvd_int64_m2_t mipp_cast_int8_int64_m2(const rvd_int8_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_int8_int64_m1(r0.m1);
	res.m2 = mipp_cast_int8_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_int8_int64_m4(const rvd_int8_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_int8_int64_m2(r0.m1);
	res.m2 = mipp_cast_int8_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_int8_int64_m8(const rvd_int8_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_int8_int64_m4(r0.m1);
	res.m2 = mipp_cast_int8_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_uint64_int64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_uint64_int64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int64(r0);
}
rvd_int64_m2_t mipp_cast_uint64_int64_m2(const rvd_uint64_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_uint64_int64_m1(r0.m1);
	res.m2 = mipp_cast_uint64_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_uint64_int64_m4(const rvd_uint64_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_uint64_int64_m2(r0.m1);
	res.m2 = mipp_cast_uint64_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_uint64_int64_m8(const rvd_uint64_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_uint64_int64_m4(r0.m1);
	res.m2 = mipp_cast_uint64_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_uint32_int64(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_uint32_int64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int64(r0);
}
rvd_int64_m2_t mipp_cast_uint32_int64_m2(const rvd_uint32_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_uint32_int64_m1(r0.m1);
	res.m2 = mipp_cast_uint32_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_uint32_int64_m4(const rvd_uint32_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_uint32_int64_m2(r0.m1);
	res.m2 = mipp_cast_uint32_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_uint32_int64_m8(const rvd_uint32_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_uint32_int64_m4(r0.m1);
	res.m2 = mipp_cast_uint32_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_uint16_int64(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_uint16_int64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int64(r0);
}
rvd_int64_m2_t mipp_cast_uint16_int64_m2(const rvd_uint16_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_uint16_int64_m1(r0.m1);
	res.m2 = mipp_cast_uint16_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_uint16_int64_m4(const rvd_uint16_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_uint16_int64_m2(r0.m1);
	res.m2 = mipp_cast_uint16_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_uint16_int64_m8(const rvd_uint16_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_uint16_int64_m4(r0.m1);
	res.m2 = mipp_cast_uint16_int64_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_cast_uint8_int64(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_int64(r0);
#endif
}
rvd_int64_m1_t mipp_cast_uint8_int64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int64(r0);
}
rvd_int64_m2_t mipp_cast_uint8_int64_m2(const rvd_uint8_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_cast_uint8_int64_m1(r0.m1);
	res.m2 = mipp_cast_uint8_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_cast_uint8_int64_m4(const rvd_uint8_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_cast_uint8_int64_m2(r0.m1);
	res.m2 = mipp_cast_uint8_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_cast_uint8_int64_m8(const rvd_uint8_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_cast_uint8_int64_m4(r0.m1);
	res.m2 = mipp_cast_uint8_int64_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_float64_int32(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_float64_int32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int32(r0);
}
rvd_int32_m2_t mipp_cast_float64_int32_m2(const rvd_float64_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_float64_int32_m1(r0.m1);
	res.m2 = mipp_cast_float64_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_float64_int32_m4(const rvd_float64_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_float64_int32_m2(r0.m1);
	res.m2 = mipp_cast_float64_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_float64_int32_m8(const rvd_float64_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_float64_int32_m4(r0.m1);
	res.m2 = mipp_cast_float64_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_float32_int32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_float32_int32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int32(r0);
}
rvd_int32_m2_t mipp_cast_float32_int32_m2(const rvd_float32_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_float32_int32_m1(r0.m1);
	res.m2 = mipp_cast_float32_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_float32_int32_m4(const rvd_float32_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_float32_int32_m2(r0.m1);
	res.m2 = mipp_cast_float32_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_float32_int32_m8(const rvd_float32_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_float32_int32_m4(r0.m1);
	res.m2 = mipp_cast_float32_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_int64_int32(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_int64_int32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int32(r0);
}
rvd_int32_m2_t mipp_cast_int64_int32_m2(const rvd_int64_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_int64_int32_m1(r0.m1);
	res.m2 = mipp_cast_int64_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_int64_int32_m4(const rvd_int64_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_int64_int32_m2(r0.m1);
	res.m2 = mipp_cast_int64_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_int64_int32_m8(const rvd_int64_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_int64_int32_m4(r0.m1);
	res.m2 = mipp_cast_int64_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_int32_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_int32_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int32(r0);
}
rvd_int32_m2_t mipp_cast_int32_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_int32_int32_m1(r0.m1);
	res.m2 = mipp_cast_int32_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_int32_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_int32_int32_m2(r0.m1);
	res.m2 = mipp_cast_int32_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_int32_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_int32_int32_m4(r0.m1);
	res.m2 = mipp_cast_int32_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_int16_int32(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_int16_int32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int32(r0);
}
rvd_int32_m2_t mipp_cast_int16_int32_m2(const rvd_int16_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_int16_int32_m1(r0.m1);
	res.m2 = mipp_cast_int16_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_int16_int32_m4(const rvd_int16_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_int16_int32_m2(r0.m1);
	res.m2 = mipp_cast_int16_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_int16_int32_m8(const rvd_int16_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_int16_int32_m4(r0.m1);
	res.m2 = mipp_cast_int16_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_int8_int32(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_int8_int32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int32(r0);
}
rvd_int32_m2_t mipp_cast_int8_int32_m2(const rvd_int8_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_int8_int32_m1(r0.m1);
	res.m2 = mipp_cast_int8_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_int8_int32_m4(const rvd_int8_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_int8_int32_m2(r0.m1);
	res.m2 = mipp_cast_int8_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_int8_int32_m8(const rvd_int8_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_int8_int32_m4(r0.m1);
	res.m2 = mipp_cast_int8_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_uint64_int32(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_uint64_int32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int32(r0);
}
rvd_int32_m2_t mipp_cast_uint64_int32_m2(const rvd_uint64_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_uint64_int32_m1(r0.m1);
	res.m2 = mipp_cast_uint64_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_uint64_int32_m4(const rvd_uint64_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_uint64_int32_m2(r0.m1);
	res.m2 = mipp_cast_uint64_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_uint64_int32_m8(const rvd_uint64_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_uint64_int32_m4(r0.m1);
	res.m2 = mipp_cast_uint64_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_uint32_int32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_uint32_int32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int32(r0);
}
rvd_int32_m2_t mipp_cast_uint32_int32_m2(const rvd_uint32_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_uint32_int32_m1(r0.m1);
	res.m2 = mipp_cast_uint32_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_uint32_int32_m4(const rvd_uint32_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_uint32_int32_m2(r0.m1);
	res.m2 = mipp_cast_uint32_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_uint32_int32_m8(const rvd_uint32_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_uint32_int32_m4(r0.m1);
	res.m2 = mipp_cast_uint32_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_uint16_int32(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_uint16_int32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int32(r0);
}
rvd_int32_m2_t mipp_cast_uint16_int32_m2(const rvd_uint16_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_uint16_int32_m1(r0.m1);
	res.m2 = mipp_cast_uint16_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_uint16_int32_m4(const rvd_uint16_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_uint16_int32_m2(r0.m1);
	res.m2 = mipp_cast_uint16_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_uint16_int32_m8(const rvd_uint16_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_uint16_int32_m4(r0.m1);
	res.m2 = mipp_cast_uint16_int32_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_cast_uint8_int32(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_int32(r0);
#endif
}
rvd_int32_m1_t mipp_cast_uint8_int32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int32(r0);
}
rvd_int32_m2_t mipp_cast_uint8_int32_m2(const rvd_uint8_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_cast_uint8_int32_m1(r0.m1);
	res.m2 = mipp_cast_uint8_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_cast_uint8_int32_m4(const rvd_uint8_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_cast_uint8_int32_m2(r0.m1);
	res.m2 = mipp_cast_uint8_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_cast_uint8_int32_m8(const rvd_uint8_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_cast_uint8_int32_m4(r0.m1);
	res.m2 = mipp_cast_uint8_int32_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_float64_int16(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_float64_int16_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int16(r0);
}
rvd_int16_m2_t mipp_cast_float64_int16_m2(const rvd_float64_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_float64_int16_m1(r0.m1);
	res.m2 = mipp_cast_float64_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_float64_int16_m4(const rvd_float64_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_float64_int16_m2(r0.m1);
	res.m2 = mipp_cast_float64_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_float64_int16_m8(const rvd_float64_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_float64_int16_m4(r0.m1);
	res.m2 = mipp_cast_float64_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_float32_int16(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_float32_int16_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int16(r0);
}
rvd_int16_m2_t mipp_cast_float32_int16_m2(const rvd_float32_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_float32_int16_m1(r0.m1);
	res.m2 = mipp_cast_float32_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_float32_int16_m4(const rvd_float32_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_float32_int16_m2(r0.m1);
	res.m2 = mipp_cast_float32_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_float32_int16_m8(const rvd_float32_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_float32_int16_m4(r0.m1);
	res.m2 = mipp_cast_float32_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_int64_int16(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_int64_int16_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int16(r0);
}
rvd_int16_m2_t mipp_cast_int64_int16_m2(const rvd_int64_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_int64_int16_m1(r0.m1);
	res.m2 = mipp_cast_int64_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_int64_int16_m4(const rvd_int64_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_int64_int16_m2(r0.m1);
	res.m2 = mipp_cast_int64_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_int64_int16_m8(const rvd_int64_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_int64_int16_m4(r0.m1);
	res.m2 = mipp_cast_int64_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_int32_int16(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_int32_int16_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int16(r0);
}
rvd_int16_m2_t mipp_cast_int32_int16_m2(const rvd_int32_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_int32_int16_m1(r0.m1);
	res.m2 = mipp_cast_int32_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_int32_int16_m4(const rvd_int32_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_int32_int16_m2(r0.m1);
	res.m2 = mipp_cast_int32_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_int32_int16_m8(const rvd_int32_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_int32_int16_m4(r0.m1);
	res.m2 = mipp_cast_int32_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_int16_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_int16_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int16(r0);
}
rvd_int16_m2_t mipp_cast_int16_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_int16_int16_m1(r0.m1);
	res.m2 = mipp_cast_int16_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_int16_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_int16_int16_m2(r0.m1);
	res.m2 = mipp_cast_int16_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_int16_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_int16_int16_m4(r0.m1);
	res.m2 = mipp_cast_int16_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_int8_int16(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_int8_int16_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int16(r0);
}
rvd_int16_m2_t mipp_cast_int8_int16_m2(const rvd_int8_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_int8_int16_m1(r0.m1);
	res.m2 = mipp_cast_int8_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_int8_int16_m4(const rvd_int8_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_int8_int16_m2(r0.m1);
	res.m2 = mipp_cast_int8_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_int8_int16_m8(const rvd_int8_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_int8_int16_m4(r0.m1);
	res.m2 = mipp_cast_int8_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_uint64_int16(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_uint64_int16_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int16(r0);
}
rvd_int16_m2_t mipp_cast_uint64_int16_m2(const rvd_uint64_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_uint64_int16_m1(r0.m1);
	res.m2 = mipp_cast_uint64_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_uint64_int16_m4(const rvd_uint64_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_uint64_int16_m2(r0.m1);
	res.m2 = mipp_cast_uint64_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_uint64_int16_m8(const rvd_uint64_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_uint64_int16_m4(r0.m1);
	res.m2 = mipp_cast_uint64_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_uint32_int16(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_uint32_int16_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int16(r0);
}
rvd_int16_m2_t mipp_cast_uint32_int16_m2(const rvd_uint32_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_uint32_int16_m1(r0.m1);
	res.m2 = mipp_cast_uint32_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_uint32_int16_m4(const rvd_uint32_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_uint32_int16_m2(r0.m1);
	res.m2 = mipp_cast_uint32_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_uint32_int16_m8(const rvd_uint32_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_uint32_int16_m4(r0.m1);
	res.m2 = mipp_cast_uint32_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_uint16_int16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_uint16_int16_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int16(r0);
}
rvd_int16_m2_t mipp_cast_uint16_int16_m2(const rvd_uint16_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_uint16_int16_m1(r0.m1);
	res.m2 = mipp_cast_uint16_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_uint16_int16_m4(const rvd_uint16_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_uint16_int16_m2(r0.m1);
	res.m2 = mipp_cast_uint16_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_uint16_int16_m8(const rvd_uint16_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_uint16_int16_m4(r0.m1);
	res.m2 = mipp_cast_uint16_int16_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_cast_uint8_int16(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_int16(r0);
#endif
}
rvd_int16_m1_t mipp_cast_uint8_int16_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int16(r0);
}
rvd_int16_m2_t mipp_cast_uint8_int16_m2(const rvd_uint8_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_cast_uint8_int16_m1(r0.m1);
	res.m2 = mipp_cast_uint8_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_cast_uint8_int16_m4(const rvd_uint8_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_cast_uint8_int16_m2(r0.m1);
	res.m2 = mipp_cast_uint8_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_cast_uint8_int16_m8(const rvd_uint8_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_cast_uint8_int16_m4(r0.m1);
	res.m2 = mipp_cast_uint8_int16_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_float64_int8(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_float64_int8_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int8(r0);
}
rvd_int8_m2_t mipp_cast_float64_int8_m2(const rvd_float64_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_float64_int8_m1(r0.m1);
	res.m2 = mipp_cast_float64_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_float64_int8_m4(const rvd_float64_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_float64_int8_m2(r0.m1);
	res.m2 = mipp_cast_float64_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_float64_int8_m8(const rvd_float64_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_float64_int8_m4(r0.m1);
	res.m2 = mipp_cast_float64_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_float32_int8(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_float32_int8_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int8(r0);
}
rvd_int8_m2_t mipp_cast_float32_int8_m2(const rvd_float32_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_float32_int8_m1(r0.m1);
	res.m2 = mipp_cast_float32_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_float32_int8_m4(const rvd_float32_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_float32_int8_m2(r0.m1);
	res.m2 = mipp_cast_float32_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_float32_int8_m8(const rvd_float32_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_float32_int8_m4(r0.m1);
	res.m2 = mipp_cast_float32_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_int64_int8(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_int64_int8_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int8(r0);
}
rvd_int8_m2_t mipp_cast_int64_int8_m2(const rvd_int64_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_int64_int8_m1(r0.m1);
	res.m2 = mipp_cast_int64_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_int64_int8_m4(const rvd_int64_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_int64_int8_m2(r0.m1);
	res.m2 = mipp_cast_int64_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_int64_int8_m8(const rvd_int64_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_int64_int8_m4(r0.m1);
	res.m2 = mipp_cast_int64_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_int32_int8(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_int32_int8_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int8(r0);
}
rvd_int8_m2_t mipp_cast_int32_int8_m2(const rvd_int32_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_int32_int8_m1(r0.m1);
	res.m2 = mipp_cast_int32_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_int32_int8_m4(const rvd_int32_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_int32_int8_m2(r0.m1);
	res.m2 = mipp_cast_int32_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_int32_int8_m8(const rvd_int32_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_int32_int8_m4(r0.m1);
	res.m2 = mipp_cast_int32_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_int16_int8(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_int16_int8_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int8(r0);
}
rvd_int8_m2_t mipp_cast_int16_int8_m2(const rvd_int16_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_int16_int8_m1(r0.m1);
	res.m2 = mipp_cast_int16_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_int16_int8_m4(const rvd_int16_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_int16_int8_m2(r0.m1);
	res.m2 = mipp_cast_int16_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_int16_int8_m8(const rvd_int16_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_int16_int8_m4(r0.m1);
	res.m2 = mipp_cast_int16_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_int8_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_int8_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int8(r0);
}
rvd_int8_m2_t mipp_cast_int8_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_int8_int8_m1(r0.m1);
	res.m2 = mipp_cast_int8_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_int8_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_int8_int8_m2(r0.m1);
	res.m2 = mipp_cast_int8_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_int8_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_int8_int8_m4(r0.m1);
	res.m2 = mipp_cast_int8_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_uint64_int8(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_uint64_int8_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int8(r0);
}
rvd_int8_m2_t mipp_cast_uint64_int8_m2(const rvd_uint64_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_uint64_int8_m1(r0.m1);
	res.m2 = mipp_cast_uint64_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_uint64_int8_m4(const rvd_uint64_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_uint64_int8_m2(r0.m1);
	res.m2 = mipp_cast_uint64_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_uint64_int8_m8(const rvd_uint64_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_uint64_int8_m4(r0.m1);
	res.m2 = mipp_cast_uint64_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_uint32_int8(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_uint32_int8_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int8(r0);
}
rvd_int8_m2_t mipp_cast_uint32_int8_m2(const rvd_uint32_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_uint32_int8_m1(r0.m1);
	res.m2 = mipp_cast_uint32_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_uint32_int8_m4(const rvd_uint32_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_uint32_int8_m2(r0.m1);
	res.m2 = mipp_cast_uint32_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_uint32_int8_m8(const rvd_uint32_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_uint32_int8_m4(r0.m1);
	res.m2 = mipp_cast_uint32_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_uint16_int8(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_uint16_int8_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int8(r0);
}
rvd_int8_m2_t mipp_cast_uint16_int8_m2(const rvd_uint16_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_uint16_int8_m1(r0.m1);
	res.m2 = mipp_cast_uint16_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_uint16_int8_m4(const rvd_uint16_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_uint16_int8_m2(r0.m1);
	res.m2 = mipp_cast_uint16_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_uint16_int8_m8(const rvd_uint16_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_uint16_int8_m4(r0.m1);
	res.m2 = mipp_cast_uint16_int8_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_cast_uint8_int8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_int8(r0);
#endif
}
rvd_int8_m1_t mipp_cast_uint8_int8_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int8(r0);
}
rvd_int8_m2_t mipp_cast_uint8_int8_m2(const rvd_uint8_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_cast_uint8_int8_m1(r0.m1);
	res.m2 = mipp_cast_uint8_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_cast_uint8_int8_m4(const rvd_uint8_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_cast_uint8_int8_m2(r0.m1);
	res.m2 = mipp_cast_uint8_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_cast_uint8_int8_m8(const rvd_uint8_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_cast_uint8_int8_m4(r0.m1);
	res.m2 = mipp_cast_uint8_int8_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_float64_uint64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_float64_uint64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_float64_uint64_m2(const rvd_float64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_float64_uint64_m1(r0.m1);
	res.m2 = mipp_cast_float64_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_float64_uint64_m4(const rvd_float64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_float64_uint64_m2(r0.m1);
	res.m2 = mipp_cast_float64_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_float64_uint64_m8(const rvd_float64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_float64_uint64_m4(r0.m1);
	res.m2 = mipp_cast_float64_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_float32_uint64(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_float32_uint64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_float32_uint64_m2(const rvd_float32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_float32_uint64_m1(r0.m1);
	res.m2 = mipp_cast_float32_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_float32_uint64_m4(const rvd_float32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_float32_uint64_m2(r0.m1);
	res.m2 = mipp_cast_float32_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_float32_uint64_m8(const rvd_float32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_float32_uint64_m4(r0.m1);
	res.m2 = mipp_cast_float32_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_int64_uint64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_int64_uint64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_int64_uint64_m2(const rvd_int64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_int64_uint64_m1(r0.m1);
	res.m2 = mipp_cast_int64_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_int64_uint64_m4(const rvd_int64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_int64_uint64_m2(r0.m1);
	res.m2 = mipp_cast_int64_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_int64_uint64_m8(const rvd_int64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_int64_uint64_m4(r0.m1);
	res.m2 = mipp_cast_int64_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_int32_uint64(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_int32_uint64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_int32_uint64_m2(const rvd_int32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_int32_uint64_m1(r0.m1);
	res.m2 = mipp_cast_int32_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_int32_uint64_m4(const rvd_int32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_int32_uint64_m2(r0.m1);
	res.m2 = mipp_cast_int32_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_int32_uint64_m8(const rvd_int32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_int32_uint64_m4(r0.m1);
	res.m2 = mipp_cast_int32_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_int16_uint64(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_int16_uint64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_int16_uint64_m2(const rvd_int16_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_int16_uint64_m1(r0.m1);
	res.m2 = mipp_cast_int16_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_int16_uint64_m4(const rvd_int16_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_int16_uint64_m2(r0.m1);
	res.m2 = mipp_cast_int16_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_int16_uint64_m8(const rvd_int16_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_int16_uint64_m4(r0.m1);
	res.m2 = mipp_cast_int16_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_int8_uint64(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_int8_uint64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_int8_uint64_m2(const rvd_int8_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_int8_uint64_m1(r0.m1);
	res.m2 = mipp_cast_int8_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_int8_uint64_m4(const rvd_int8_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_int8_uint64_m2(r0.m1);
	res.m2 = mipp_cast_int8_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_int8_uint64_m8(const rvd_int8_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_int8_uint64_m4(r0.m1);
	res.m2 = mipp_cast_int8_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_uint64_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_uint64_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_uint64_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_uint64_uint64_m1(r0.m1);
	res.m2 = mipp_cast_uint64_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_uint64_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_uint64_uint64_m2(r0.m1);
	res.m2 = mipp_cast_uint64_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_uint64_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_uint64_uint64_m4(r0.m1);
	res.m2 = mipp_cast_uint64_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_uint32_uint64(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_uint32_uint64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_uint32_uint64_m2(const rvd_uint32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_uint32_uint64_m1(r0.m1);
	res.m2 = mipp_cast_uint32_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_uint32_uint64_m4(const rvd_uint32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_uint32_uint64_m2(r0.m1);
	res.m2 = mipp_cast_uint32_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_uint32_uint64_m8(const rvd_uint32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_uint32_uint64_m4(r0.m1);
	res.m2 = mipp_cast_uint32_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_uint16_uint64(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_uint16_uint64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_uint16_uint64_m2(const rvd_uint16_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_uint16_uint64_m1(r0.m1);
	res.m2 = mipp_cast_uint16_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_uint16_uint64_m4(const rvd_uint16_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_uint16_uint64_m2(r0.m1);
	res.m2 = mipp_cast_uint16_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_uint16_uint64_m8(const rvd_uint16_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_uint16_uint64_m4(r0.m1);
	res.m2 = mipp_cast_uint16_uint64_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_cast_uint8_uint64(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_cast_uint8_uint64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint64(r0);
}
rvd_uint64_m2_t mipp_cast_uint8_uint64_m2(const rvd_uint8_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_cast_uint8_uint64_m1(r0.m1);
	res.m2 = mipp_cast_uint8_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_cast_uint8_uint64_m4(const rvd_uint8_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_cast_uint8_uint64_m2(r0.m1);
	res.m2 = mipp_cast_uint8_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_cast_uint8_uint64_m8(const rvd_uint8_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_cast_uint8_uint64_m4(r0.m1);
	res.m2 = mipp_cast_uint8_uint64_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_float64_uint32(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_float64_uint32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_float64_uint32_m2(const rvd_float64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_float64_uint32_m1(r0.m1);
	res.m2 = mipp_cast_float64_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_float64_uint32_m4(const rvd_float64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_float64_uint32_m2(r0.m1);
	res.m2 = mipp_cast_float64_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_float64_uint32_m8(const rvd_float64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_float64_uint32_m4(r0.m1);
	res.m2 = mipp_cast_float64_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_float32_uint32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_float32_uint32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_float32_uint32_m2(const rvd_float32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_float32_uint32_m1(r0.m1);
	res.m2 = mipp_cast_float32_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_float32_uint32_m4(const rvd_float32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_float32_uint32_m2(r0.m1);
	res.m2 = mipp_cast_float32_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_float32_uint32_m8(const rvd_float32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_float32_uint32_m4(r0.m1);
	res.m2 = mipp_cast_float32_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_int64_uint32(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_int64_uint32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_int64_uint32_m2(const rvd_int64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_int64_uint32_m1(r0.m1);
	res.m2 = mipp_cast_int64_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_int64_uint32_m4(const rvd_int64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_int64_uint32_m2(r0.m1);
	res.m2 = mipp_cast_int64_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_int64_uint32_m8(const rvd_int64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_int64_uint32_m4(r0.m1);
	res.m2 = mipp_cast_int64_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_int32_uint32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_int32_uint32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_int32_uint32_m2(const rvd_int32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_int32_uint32_m1(r0.m1);
	res.m2 = mipp_cast_int32_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_int32_uint32_m4(const rvd_int32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_int32_uint32_m2(r0.m1);
	res.m2 = mipp_cast_int32_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_int32_uint32_m8(const rvd_int32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_int32_uint32_m4(r0.m1);
	res.m2 = mipp_cast_int32_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_int16_uint32(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_int16_uint32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_int16_uint32_m2(const rvd_int16_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_int16_uint32_m1(r0.m1);
	res.m2 = mipp_cast_int16_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_int16_uint32_m4(const rvd_int16_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_int16_uint32_m2(r0.m1);
	res.m2 = mipp_cast_int16_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_int16_uint32_m8(const rvd_int16_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_int16_uint32_m4(r0.m1);
	res.m2 = mipp_cast_int16_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_int8_uint32(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_int8_uint32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_int8_uint32_m2(const rvd_int8_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_int8_uint32_m1(r0.m1);
	res.m2 = mipp_cast_int8_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_int8_uint32_m4(const rvd_int8_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_int8_uint32_m2(r0.m1);
	res.m2 = mipp_cast_int8_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_int8_uint32_m8(const rvd_int8_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_int8_uint32_m4(r0.m1);
	res.m2 = mipp_cast_int8_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_uint64_uint32(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_uint64_uint32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_uint64_uint32_m2(const rvd_uint64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_uint64_uint32_m1(r0.m1);
	res.m2 = mipp_cast_uint64_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_uint64_uint32_m4(const rvd_uint64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_uint64_uint32_m2(r0.m1);
	res.m2 = mipp_cast_uint64_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_uint64_uint32_m8(const rvd_uint64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_uint64_uint32_m4(r0.m1);
	res.m2 = mipp_cast_uint64_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_uint32_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_uint32_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_uint32_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_uint32_uint32_m1(r0.m1);
	res.m2 = mipp_cast_uint32_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_uint32_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_uint32_uint32_m2(r0.m1);
	res.m2 = mipp_cast_uint32_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_uint32_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_uint32_uint32_m4(r0.m1);
	res.m2 = mipp_cast_uint32_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_uint16_uint32(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_uint16_uint32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_uint16_uint32_m2(const rvd_uint16_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_uint16_uint32_m1(r0.m1);
	res.m2 = mipp_cast_uint16_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_uint16_uint32_m4(const rvd_uint16_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_uint16_uint32_m2(r0.m1);
	res.m2 = mipp_cast_uint16_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_uint16_uint32_m8(const rvd_uint16_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_uint16_uint32_m4(r0.m1);
	res.m2 = mipp_cast_uint16_uint32_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_cast_uint8_uint32(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_cast_uint8_uint32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint32(r0);
}
rvd_uint32_m2_t mipp_cast_uint8_uint32_m2(const rvd_uint8_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_cast_uint8_uint32_m1(r0.m1);
	res.m2 = mipp_cast_uint8_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_cast_uint8_uint32_m4(const rvd_uint8_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_cast_uint8_uint32_m2(r0.m1);
	res.m2 = mipp_cast_uint8_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_cast_uint8_uint32_m8(const rvd_uint8_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_cast_uint8_uint32_m4(r0.m1);
	res.m2 = mipp_cast_uint8_uint32_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_float64_uint16(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_float64_uint16_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_float64_uint16_m2(const rvd_float64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_float64_uint16_m1(r0.m1);
	res.m2 = mipp_cast_float64_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_float64_uint16_m4(const rvd_float64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_float64_uint16_m2(r0.m1);
	res.m2 = mipp_cast_float64_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_float64_uint16_m8(const rvd_float64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_float64_uint16_m4(r0.m1);
	res.m2 = mipp_cast_float64_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_float32_uint16(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_float32_uint16_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_float32_uint16_m2(const rvd_float32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_float32_uint16_m1(r0.m1);
	res.m2 = mipp_cast_float32_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_float32_uint16_m4(const rvd_float32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_float32_uint16_m2(r0.m1);
	res.m2 = mipp_cast_float32_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_float32_uint16_m8(const rvd_float32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_float32_uint16_m4(r0.m1);
	res.m2 = mipp_cast_float32_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_int64_uint16(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_int64_uint16_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_int64_uint16_m2(const rvd_int64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_int64_uint16_m1(r0.m1);
	res.m2 = mipp_cast_int64_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_int64_uint16_m4(const rvd_int64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_int64_uint16_m2(r0.m1);
	res.m2 = mipp_cast_int64_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_int64_uint16_m8(const rvd_int64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_int64_uint16_m4(r0.m1);
	res.m2 = mipp_cast_int64_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_int32_uint16(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_int32_uint16_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_int32_uint16_m2(const rvd_int32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_int32_uint16_m1(r0.m1);
	res.m2 = mipp_cast_int32_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_int32_uint16_m4(const rvd_int32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_int32_uint16_m2(r0.m1);
	res.m2 = mipp_cast_int32_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_int32_uint16_m8(const rvd_int32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_int32_uint16_m4(r0.m1);
	res.m2 = mipp_cast_int32_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_int16_uint16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_int16_uint16_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_int16_uint16_m2(const rvd_int16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_int16_uint16_m1(r0.m1);
	res.m2 = mipp_cast_int16_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_int16_uint16_m4(const rvd_int16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_int16_uint16_m2(r0.m1);
	res.m2 = mipp_cast_int16_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_int16_uint16_m8(const rvd_int16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_int16_uint16_m4(r0.m1);
	res.m2 = mipp_cast_int16_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_int8_uint16(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_int8_uint16_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_int8_uint16_m2(const rvd_int8_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_int8_uint16_m1(r0.m1);
	res.m2 = mipp_cast_int8_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_int8_uint16_m4(const rvd_int8_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_int8_uint16_m2(r0.m1);
	res.m2 = mipp_cast_int8_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_int8_uint16_m8(const rvd_int8_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_int8_uint16_m4(r0.m1);
	res.m2 = mipp_cast_int8_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_uint64_uint16(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_uint64_uint16_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_uint64_uint16_m2(const rvd_uint64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_uint64_uint16_m1(r0.m1);
	res.m2 = mipp_cast_uint64_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_uint64_uint16_m4(const rvd_uint64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_uint64_uint16_m2(r0.m1);
	res.m2 = mipp_cast_uint64_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_uint64_uint16_m8(const rvd_uint64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_uint64_uint16_m4(r0.m1);
	res.m2 = mipp_cast_uint64_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_uint32_uint16(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_uint32_uint16_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_uint32_uint16_m2(const rvd_uint32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_uint32_uint16_m1(r0.m1);
	res.m2 = mipp_cast_uint32_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_uint32_uint16_m4(const rvd_uint32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_uint32_uint16_m2(r0.m1);
	res.m2 = mipp_cast_uint32_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_uint32_uint16_m8(const rvd_uint32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_uint32_uint16_m4(r0.m1);
	res.m2 = mipp_cast_uint32_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_uint16_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_uint16_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_uint16_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_uint16_uint16_m1(r0.m1);
	res.m2 = mipp_cast_uint16_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_uint16_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_uint16_uint16_m2(r0.m1);
	res.m2 = mipp_cast_uint16_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_uint16_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_uint16_uint16_m4(r0.m1);
	res.m2 = mipp_cast_uint16_uint16_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_cast_uint8_uint16(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_cast_uint8_uint16_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint16(r0);
}
rvd_uint16_m2_t mipp_cast_uint8_uint16_m2(const rvd_uint8_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_cast_uint8_uint16_m1(r0.m1);
	res.m2 = mipp_cast_uint8_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_cast_uint8_uint16_m4(const rvd_uint8_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_cast_uint8_uint16_m2(r0.m1);
	res.m2 = mipp_cast_uint8_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_cast_uint8_uint16_m8(const rvd_uint8_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_cast_uint8_uint16_m4(r0.m1);
	res.m2 = mipp_cast_uint8_uint16_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_float64_uint8(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float64_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_float64_uint8_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_float64_uint8_m2(const rvd_float64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_float64_uint8_m1(r0.m1);
	res.m2 = mipp_cast_float64_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_float64_uint8_m4(const rvd_float64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_float64_uint8_m2(r0.m1);
	res.m2 = mipp_cast_float64_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_float64_uint8_m8(const rvd_float64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_float64_uint8_m4(r0.m1);
	res.m2 = mipp_cast_float64_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_float32_uint8(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_float32_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_float32_uint8_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_float32_uint8_m2(const rvd_float32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_float32_uint8_m1(r0.m1);
	res.m2 = mipp_cast_float32_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_float32_uint8_m4(const rvd_float32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_float32_uint8_m2(r0.m1);
	res.m2 = mipp_cast_float32_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_float32_uint8_m8(const rvd_float32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_float32_uint8_m4(r0.m1);
	res.m2 = mipp_cast_float32_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_int64_uint8(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int64_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_int64_uint8_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_int64_uint8_m2(const rvd_int64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_int64_uint8_m1(r0.m1);
	res.m2 = mipp_cast_int64_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_int64_uint8_m4(const rvd_int64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_int64_uint8_m2(r0.m1);
	res.m2 = mipp_cast_int64_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_int64_uint8_m8(const rvd_int64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_int64_uint8_m4(r0.m1);
	res.m2 = mipp_cast_int64_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_int32_uint8(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int32_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_int32_uint8_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_int32_uint8_m2(const rvd_int32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_int32_uint8_m1(r0.m1);
	res.m2 = mipp_cast_int32_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_int32_uint8_m4(const rvd_int32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_int32_uint8_m2(r0.m1);
	res.m2 = mipp_cast_int32_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_int32_uint8_m8(const rvd_int32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_int32_uint8_m4(r0.m1);
	res.m2 = mipp_cast_int32_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_int16_uint8(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int16_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_int16_uint8_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_int16_uint8_m2(const rvd_int16_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_int16_uint8_m1(r0.m1);
	res.m2 = mipp_cast_int16_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_int16_uint8_m4(const rvd_int16_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_int16_uint8_m2(r0.m1);
	res.m2 = mipp_cast_int16_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_int16_uint8_m8(const rvd_int16_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_int16_uint8_m4(r0.m1);
	res.m2 = mipp_cast_int16_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_int8_uint8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_int8_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_int8_uint8_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_int8_uint8_m2(const rvd_int8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_int8_uint8_m1(r0.m1);
	res.m2 = mipp_cast_int8_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_int8_uint8_m4(const rvd_int8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_int8_uint8_m2(r0.m1);
	res.m2 = mipp_cast_int8_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_int8_uint8_m8(const rvd_int8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_int8_uint8_m4(r0.m1);
	res.m2 = mipp_cast_int8_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_uint64_uint8(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint64_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_uint64_uint8_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_uint64_uint8_m2(const rvd_uint64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_uint64_uint8_m1(r0.m1);
	res.m2 = mipp_cast_uint64_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_uint64_uint8_m4(const rvd_uint64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_uint64_uint8_m2(r0.m1);
	res.m2 = mipp_cast_uint64_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_uint64_uint8_m8(const rvd_uint64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_uint64_uint8_m4(r0.m1);
	res.m2 = mipp_cast_uint64_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_uint32_uint8(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint32_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_uint32_uint8_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_uint32_uint8_m2(const rvd_uint32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_uint32_uint8_m1(r0.m1);
	res.m2 = mipp_cast_uint32_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_uint32_uint8_m4(const rvd_uint32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_uint32_uint8_m2(r0.m1);
	res.m2 = mipp_cast_uint32_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_uint32_uint8_m8(const rvd_uint32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_uint32_uint8_m4(r0.m1);
	res.m2 = mipp_cast_uint32_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_uint16_uint8(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint16_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_uint16_uint8_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_uint16_uint8_m2(const rvd_uint16_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_uint16_uint8_m1(r0.m1);
	res.m2 = mipp_cast_uint16_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_uint16_uint8_m4(const rvd_uint16_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_uint16_uint8_m2(r0.m1);
	res.m2 = mipp_cast_uint16_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_uint16_uint8_m8(const rvd_uint16_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_uint16_uint8_m4(r0.m1);
	res.m2 = mipp_cast_uint16_uint8_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_cast_uint8_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_cast_uint8_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_cast_uint8_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint8(r0);
}
rvd_uint8_m2_t mipp_cast_uint8_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_cast_uint8_uint8_m1(r0.m1);
	res.m2 = mipp_cast_uint8_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_cast_uint8_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_cast_uint8_uint8_m2(r0.m1);
	res.m2 = mipp_cast_uint8_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_cast_uint8_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_cast_uint8_uint8_m4(r0.m1);
	res.m2 = mipp_cast_uint8_uint8_m4(r0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_float64_float64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_float64_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_float64_float64_m2(const rvm_float64_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_float64_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_float64_float64_m4(const rvm_float64_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_float64_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_float64_float64_m8(const rvm_float64_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_float64_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_float32_float64(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_float32_float64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_float32_float64_m2(const rvm_float32_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_float32_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_float32_float64_m4(const rvm_float32_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_float32_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_float32_float64_m8(const rvm_float32_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_float32_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_int64_float64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_int64_float64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_int64_float64_m2(const rvm_int64_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_int64_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_int64_float64_m4(const rvm_int64_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_int64_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_int64_float64_m8(const rvm_int64_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_int64_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_int32_float64(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_int32_float64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_int32_float64_m2(const rvm_int32_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_int32_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_int32_float64_m4(const rvm_int32_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_int32_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_int32_float64_m8(const rvm_int32_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_int32_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_int16_float64(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_int16_float64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_int16_float64_m2(const rvm_int16_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_int16_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_int16_float64_m4(const rvm_int16_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_int16_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_int16_float64_m8(const rvm_int16_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_int16_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_int8_float64(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_int8_float64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_int8_float64_m2(const rvm_int8_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_int8_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_int8_float64_m4(const rvm_int8_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_int8_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_int8_float64_m8(const rvm_int8_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_int8_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_uint64_float64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_uint64_float64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_uint64_float64_m2(const rvm_uint64_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_uint64_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_uint64_float64_m4(const rvm_uint64_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_uint64_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_uint64_float64_m8(const rvm_uint64_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_uint64_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_uint32_float64(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_uint32_float64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_uint32_float64_m2(const rvm_uint32_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_uint32_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_uint32_float64_m4(const rvm_uint32_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_uint32_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_uint32_float64_m8(const rvm_uint32_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_uint32_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_uint16_float64(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_uint16_float64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_uint16_float64_m2(const rvm_uint16_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_uint16_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_uint16_float64_m4(const rvm_uint16_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_uint16_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_uint16_float64_m8(const rvm_uint16_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_uint16_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_float64_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cast_k_uint8_float64(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_float64(m0);
#endif
}
rvm_float64_m1_t mipp_cast_k_uint8_float64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_float64(m0);
}
rvm_float64_m2_t mipp_cast_k_uint8_float64_m2(const rvm_uint8_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cast_k_uint8_float64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_cast_k_uint8_float64_m4(const rvm_uint8_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cast_k_uint8_float64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_cast_k_uint8_float64_m8(const rvm_uint8_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cast_k_uint8_float64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_float64_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_float64_float32(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_float64_float32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_float64_float32_m2(const rvm_float64_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_float64_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_float64_float32_m4(const rvm_float64_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_float64_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_float64_float32_m8(const rvm_float64_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_float64_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_float32_float32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_float32_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_float32_float32_m2(const rvm_float32_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_float32_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_float32_float32_m4(const rvm_float32_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_float32_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_float32_float32_m8(const rvm_float32_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_float32_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_int64_float32(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_int64_float32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_int64_float32_m2(const rvm_int64_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_int64_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_int64_float32_m4(const rvm_int64_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_int64_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_int64_float32_m8(const rvm_int64_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_int64_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_int32_float32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_int32_float32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_int32_float32_m2(const rvm_int32_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_int32_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_int32_float32_m4(const rvm_int32_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_int32_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_int32_float32_m8(const rvm_int32_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_int32_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_int16_float32(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_int16_float32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_int16_float32_m2(const rvm_int16_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_int16_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_int16_float32_m4(const rvm_int16_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_int16_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_int16_float32_m8(const rvm_int16_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_int16_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_int8_float32(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_int8_float32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_int8_float32_m2(const rvm_int8_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_int8_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_int8_float32_m4(const rvm_int8_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_int8_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_int8_float32_m8(const rvm_int8_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_int8_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_uint64_float32(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_uint64_float32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_uint64_float32_m2(const rvm_uint64_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_uint64_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_uint64_float32_m4(const rvm_uint64_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_uint64_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_uint64_float32_m8(const rvm_uint64_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_uint64_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_uint32_float32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_uint32_float32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_uint32_float32_m2(const rvm_uint32_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_uint32_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_uint32_float32_m4(const rvm_uint32_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_uint32_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_uint32_float32_m8(const rvm_uint32_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_uint32_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_uint16_float32(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_uint16_float32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_uint16_float32_m2(const rvm_uint16_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_uint16_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_uint16_float32_m4(const rvm_uint16_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_uint16_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_uint16_float32_m8(const rvm_uint16_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_uint16_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_float32_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_cast_k_uint8_float32(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_float32(m0);
#endif
}
rvm_float32_m1_t mipp_cast_k_uint8_float32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_float32(m0);
}
rvm_float32_m2_t mipp_cast_k_uint8_float32_m2(const rvm_uint8_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cast_k_uint8_float32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_cast_k_uint8_float32_m4(const rvm_uint8_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cast_k_uint8_float32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_cast_k_uint8_float32_m8(const rvm_uint8_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cast_k_uint8_float32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_float32_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_float64_int64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_float64_int64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_float64_int64_m2(const rvm_float64_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_float64_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_float64_int64_m4(const rvm_float64_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_float64_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_float64_int64_m8(const rvm_float64_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_float64_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_float32_int64(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_float32_int64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_float32_int64_m2(const rvm_float32_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_float32_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_float32_int64_m4(const rvm_float32_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_float32_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_float32_int64_m8(const rvm_float32_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_float32_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_int64_int64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_int64_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_int64_int64_m2(const rvm_int64_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_int64_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_int64_int64_m4(const rvm_int64_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_int64_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_int64_int64_m8(const rvm_int64_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_int64_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_int32_int64(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_int32_int64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_int32_int64_m2(const rvm_int32_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_int32_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_int32_int64_m4(const rvm_int32_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_int32_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_int32_int64_m8(const rvm_int32_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_int32_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_int16_int64(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_int16_int64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_int16_int64_m2(const rvm_int16_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_int16_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_int16_int64_m4(const rvm_int16_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_int16_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_int16_int64_m8(const rvm_int16_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_int16_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_int8_int64(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_int8_int64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_int8_int64_m2(const rvm_int8_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_int8_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_int8_int64_m4(const rvm_int8_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_int8_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_int8_int64_m8(const rvm_int8_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_int8_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_uint64_int64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_uint64_int64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_uint64_int64_m2(const rvm_uint64_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_uint64_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_uint64_int64_m4(const rvm_uint64_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_uint64_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_uint64_int64_m8(const rvm_uint64_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_uint64_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_uint32_int64(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_uint32_int64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_uint32_int64_m2(const rvm_uint32_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_uint32_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_uint32_int64_m4(const rvm_uint32_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_uint32_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_uint32_int64_m8(const rvm_uint32_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_uint32_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_uint16_int64(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_uint16_int64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_uint16_int64_m2(const rvm_uint16_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_uint16_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_uint16_int64_m4(const rvm_uint16_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_uint16_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_uint16_int64_m8(const rvm_uint16_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_uint16_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_int64_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_cast_k_uint8_int64(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_int64(m0);
#endif
}
rvm_int64_m1_t mipp_cast_k_uint8_int64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int64(m0);
}
rvm_int64_m2_t mipp_cast_k_uint8_int64_m2(const rvm_uint8_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cast_k_uint8_int64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_cast_k_uint8_int64_m4(const rvm_uint8_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cast_k_uint8_int64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_cast_k_uint8_int64_m8(const rvm_uint8_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cast_k_uint8_int64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_int64_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_float64_int32(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_float64_int32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_float64_int32_m2(const rvm_float64_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_float64_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_float64_int32_m4(const rvm_float64_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_float64_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_float64_int32_m8(const rvm_float64_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_float64_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_float32_int32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_float32_int32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_float32_int32_m2(const rvm_float32_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_float32_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_float32_int32_m4(const rvm_float32_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_float32_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_float32_int32_m8(const rvm_float32_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_float32_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_int64_int32(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_int64_int32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_int64_int32_m2(const rvm_int64_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_int64_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_int64_int32_m4(const rvm_int64_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_int64_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_int64_int32_m8(const rvm_int64_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_int64_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_int32_int32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_int32_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_int32_int32_m2(const rvm_int32_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_int32_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_int32_int32_m4(const rvm_int32_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_int32_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_int32_int32_m8(const rvm_int32_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_int32_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_int16_int32(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_int16_int32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_int16_int32_m2(const rvm_int16_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_int16_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_int16_int32_m4(const rvm_int16_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_int16_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_int16_int32_m8(const rvm_int16_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_int16_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_int8_int32(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_int8_int32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_int8_int32_m2(const rvm_int8_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_int8_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_int8_int32_m4(const rvm_int8_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_int8_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_int8_int32_m8(const rvm_int8_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_int8_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_uint64_int32(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_uint64_int32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_uint64_int32_m2(const rvm_uint64_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_uint64_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_uint64_int32_m4(const rvm_uint64_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_uint64_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_uint64_int32_m8(const rvm_uint64_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_uint64_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_uint32_int32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_uint32_int32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_uint32_int32_m2(const rvm_uint32_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_uint32_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_uint32_int32_m4(const rvm_uint32_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_uint32_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_uint32_int32_m8(const rvm_uint32_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_uint32_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_uint16_int32(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_uint16_int32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_uint16_int32_m2(const rvm_uint16_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_uint16_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_uint16_int32_m4(const rvm_uint16_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_uint16_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_uint16_int32_m8(const rvm_uint16_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_uint16_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_int32_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_cast_k_uint8_int32(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_int32(m0);
#endif
}
rvm_int32_m1_t mipp_cast_k_uint8_int32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int32(m0);
}
rvm_int32_m2_t mipp_cast_k_uint8_int32_m2(const rvm_uint8_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cast_k_uint8_int32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_cast_k_uint8_int32_m4(const rvm_uint8_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cast_k_uint8_int32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_cast_k_uint8_int32_m8(const rvm_uint8_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cast_k_uint8_int32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_int32_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_float64_int16(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_float64_int16_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_float64_int16_m2(const rvm_float64_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_float64_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_float64_int16_m4(const rvm_float64_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_float64_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_float64_int16_m8(const rvm_float64_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_float64_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_float32_int16(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_float32_int16_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_float32_int16_m2(const rvm_float32_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_float32_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_float32_int16_m4(const rvm_float32_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_float32_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_float32_int16_m8(const rvm_float32_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_float32_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_int64_int16(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_int64_int16_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_int64_int16_m2(const rvm_int64_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_int64_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_int64_int16_m4(const rvm_int64_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_int64_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_int64_int16_m8(const rvm_int64_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_int64_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_int32_int16(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_int32_int16_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_int32_int16_m2(const rvm_int32_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_int32_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_int32_int16_m4(const rvm_int32_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_int32_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_int32_int16_m8(const rvm_int32_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_int32_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_int16_int16(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_int16_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_int16_int16_m2(const rvm_int16_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_int16_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_int16_int16_m4(const rvm_int16_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_int16_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_int16_int16_m8(const rvm_int16_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_int16_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_int8_int16(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_int8_int16_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_int8_int16_m2(const rvm_int8_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_int8_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_int8_int16_m4(const rvm_int8_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_int8_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_int8_int16_m8(const rvm_int8_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_int8_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_uint64_int16(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_uint64_int16_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_uint64_int16_m2(const rvm_uint64_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_uint64_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_uint64_int16_m4(const rvm_uint64_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_uint64_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_uint64_int16_m8(const rvm_uint64_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_uint64_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_uint32_int16(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_uint32_int16_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_uint32_int16_m2(const rvm_uint32_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_uint32_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_uint32_int16_m4(const rvm_uint32_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_uint32_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_uint32_int16_m8(const rvm_uint32_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_uint32_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_uint16_int16(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_uint16_int16_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_uint16_int16_m2(const rvm_uint16_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_uint16_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_uint16_int16_m4(const rvm_uint16_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_uint16_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_uint16_int16_m8(const rvm_uint16_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_uint16_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_int16_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_cast_k_uint8_int16(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_int16(m0);
#endif
}
rvm_int16_m1_t mipp_cast_k_uint8_int16_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int16(m0);
}
rvm_int16_m2_t mipp_cast_k_uint8_int16_m2(const rvm_uint8_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cast_k_uint8_int16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_cast_k_uint8_int16_m4(const rvm_uint8_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cast_k_uint8_int16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_cast_k_uint8_int16_m8(const rvm_uint8_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cast_k_uint8_int16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_int16_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_float64_int8(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_float64_int8_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_float64_int8_m2(const rvm_float64_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_float64_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_float64_int8_m4(const rvm_float64_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_float64_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_float64_int8_m8(const rvm_float64_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_float64_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_float32_int8(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_float32_int8_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_float32_int8_m2(const rvm_float32_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_float32_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_float32_int8_m4(const rvm_float32_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_float32_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_float32_int8_m8(const rvm_float32_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_float32_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_int64_int8(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_int64_int8_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_int64_int8_m2(const rvm_int64_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_int64_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_int64_int8_m4(const rvm_int64_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_int64_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_int64_int8_m8(const rvm_int64_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_int64_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_int32_int8(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_int32_int8_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_int32_int8_m2(const rvm_int32_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_int32_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_int32_int8_m4(const rvm_int32_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_int32_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_int32_int8_m8(const rvm_int32_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_int32_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_int16_int8(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_int16_int8_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_int16_int8_m2(const rvm_int16_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_int16_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_int16_int8_m4(const rvm_int16_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_int16_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_int16_int8_m8(const rvm_int16_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_int16_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_int8_int8(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_int8_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_int8_int8_m2(const rvm_int8_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_int8_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_int8_int8_m4(const rvm_int8_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_int8_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_int8_int8_m8(const rvm_int8_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_int8_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_uint64_int8(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_uint64_int8_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_uint64_int8_m2(const rvm_uint64_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_uint64_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_uint64_int8_m4(const rvm_uint64_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_uint64_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_uint64_int8_m8(const rvm_uint64_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_uint64_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_uint32_int8(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_uint32_int8_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_uint32_int8_m2(const rvm_uint32_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_uint32_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_uint32_int8_m4(const rvm_uint32_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_uint32_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_uint32_int8_m8(const rvm_uint32_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_uint32_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_uint16_int8(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_uint16_int8_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_uint16_int8_m2(const rvm_uint16_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_uint16_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_uint16_int8_m4(const rvm_uint16_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_uint16_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_uint16_int8_m8(const rvm_uint16_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_uint16_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_int8_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_cast_k_uint8_int8(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_int8(m0);
#endif
}
rvm_int8_m1_t mipp_cast_k_uint8_int8_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int8(m0);
}
rvm_int8_m2_t mipp_cast_k_uint8_int8_m2(const rvm_uint8_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cast_k_uint8_int8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_cast_k_uint8_int8_m4(const rvm_uint8_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cast_k_uint8_int8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_cast_k_uint8_int8_m8(const rvm_uint8_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cast_k_uint8_int8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_int8_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_float64_uint64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_float64_uint64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_float64_uint64_m2(const rvm_float64_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_float64_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_float64_uint64_m4(const rvm_float64_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_float64_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_float64_uint64_m8(const rvm_float64_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_float64_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_float32_uint64(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_float32_uint64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_float32_uint64_m2(const rvm_float32_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_float32_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_float32_uint64_m4(const rvm_float32_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_float32_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_float32_uint64_m8(const rvm_float32_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_float32_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_int64_uint64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_int64_uint64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_int64_uint64_m2(const rvm_int64_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_int64_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_int64_uint64_m4(const rvm_int64_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_int64_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_int64_uint64_m8(const rvm_int64_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_int64_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_int32_uint64(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_int32_uint64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_int32_uint64_m2(const rvm_int32_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_int32_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_int32_uint64_m4(const rvm_int32_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_int32_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_int32_uint64_m8(const rvm_int32_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_int32_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_int16_uint64(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_int16_uint64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_int16_uint64_m2(const rvm_int16_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_int16_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_int16_uint64_m4(const rvm_int16_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_int16_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_int16_uint64_m8(const rvm_int16_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_int16_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_int8_uint64(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_int8_uint64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_int8_uint64_m2(const rvm_int8_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_int8_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_int8_uint64_m4(const rvm_int8_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_int8_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_int8_uint64_m8(const rvm_int8_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_int8_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_uint64_uint64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_uint64_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_uint64_uint64_m2(const rvm_uint64_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_uint64_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_uint64_uint64_m4(const rvm_uint64_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_uint64_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_uint64_uint64_m8(const rvm_uint64_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_uint64_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_uint32_uint64(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_uint32_uint64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_uint32_uint64_m2(const rvm_uint32_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_uint32_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_uint32_uint64_m4(const rvm_uint32_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_uint32_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_uint32_uint64_m8(const rvm_uint32_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_uint32_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_uint16_uint64(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_uint16_uint64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_uint16_uint64_m2(const rvm_uint16_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_uint16_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_uint16_uint64_m4(const rvm_uint16_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_uint16_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_uint16_uint64_m8(const rvm_uint16_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_uint16_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint64_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_cast_k_uint8_uint64(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_cast_k_uint8_uint64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint64(m0);
}
rvm_uint64_m2_t mipp_cast_k_uint8_uint64_m2(const rvm_uint8_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cast_k_uint8_uint64_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_cast_k_uint8_uint64_m4(const rvm_uint8_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cast_k_uint8_uint64_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_cast_k_uint8_uint64_m8(const rvm_uint8_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cast_k_uint8_uint64_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint64_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_float64_uint32(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_float64_uint32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_float64_uint32_m2(const rvm_float64_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_float64_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_float64_uint32_m4(const rvm_float64_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_float64_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_float64_uint32_m8(const rvm_float64_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_float64_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_float32_uint32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_float32_uint32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_float32_uint32_m2(const rvm_float32_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_float32_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_float32_uint32_m4(const rvm_float32_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_float32_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_float32_uint32_m8(const rvm_float32_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_float32_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_int64_uint32(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_int64_uint32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_int64_uint32_m2(const rvm_int64_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_int64_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_int64_uint32_m4(const rvm_int64_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_int64_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_int64_uint32_m8(const rvm_int64_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_int64_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_int32_uint32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_int32_uint32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_int32_uint32_m2(const rvm_int32_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_int32_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_int32_uint32_m4(const rvm_int32_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_int32_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_int32_uint32_m8(const rvm_int32_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_int32_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_int16_uint32(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_int16_uint32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_int16_uint32_m2(const rvm_int16_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_int16_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_int16_uint32_m4(const rvm_int16_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_int16_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_int16_uint32_m8(const rvm_int16_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_int16_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_int8_uint32(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_int8_uint32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_int8_uint32_m2(const rvm_int8_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_int8_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_int8_uint32_m4(const rvm_int8_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_int8_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_int8_uint32_m8(const rvm_int8_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_int8_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_uint64_uint32(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_uint64_uint32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_uint64_uint32_m2(const rvm_uint64_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_uint64_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_uint64_uint32_m4(const rvm_uint64_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_uint64_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_uint64_uint32_m8(const rvm_uint64_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_uint64_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_uint32_uint32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_uint32_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_uint32_uint32_m2(const rvm_uint32_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_uint32_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_uint32_uint32_m4(const rvm_uint32_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_uint32_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_uint32_uint32_m8(const rvm_uint32_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_uint32_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_uint16_uint32(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_uint16_uint32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_uint16_uint32_m2(const rvm_uint16_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_uint16_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_uint16_uint32_m4(const rvm_uint16_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_uint16_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_uint16_uint32_m8(const rvm_uint16_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_uint16_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint32_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_cast_k_uint8_uint32(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_cast_k_uint8_uint32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint32(m0);
}
rvm_uint32_m2_t mipp_cast_k_uint8_uint32_m2(const rvm_uint8_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cast_k_uint8_uint32_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_cast_k_uint8_uint32_m4(const rvm_uint8_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cast_k_uint8_uint32_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_cast_k_uint8_uint32_m8(const rvm_uint8_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cast_k_uint8_uint32_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint32_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_float64_uint16(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_float64_uint16_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_float64_uint16_m2(const rvm_float64_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_float64_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_float64_uint16_m4(const rvm_float64_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_float64_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_float64_uint16_m8(const rvm_float64_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_float64_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_float32_uint16(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_float32_uint16_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_float32_uint16_m2(const rvm_float32_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_float32_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_float32_uint16_m4(const rvm_float32_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_float32_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_float32_uint16_m8(const rvm_float32_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_float32_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_int64_uint16(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_int64_uint16_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_int64_uint16_m2(const rvm_int64_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_int64_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_int64_uint16_m4(const rvm_int64_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_int64_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_int64_uint16_m8(const rvm_int64_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_int64_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_int32_uint16(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_int32_uint16_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_int32_uint16_m2(const rvm_int32_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_int32_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_int32_uint16_m4(const rvm_int32_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_int32_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_int32_uint16_m8(const rvm_int32_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_int32_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_int16_uint16(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_int16_uint16_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_int16_uint16_m2(const rvm_int16_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_int16_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_int16_uint16_m4(const rvm_int16_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_int16_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_int16_uint16_m8(const rvm_int16_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_int16_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_int8_uint16(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_int8_uint16_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_int8_uint16_m2(const rvm_int8_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_int8_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_int8_uint16_m4(const rvm_int8_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_int8_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_int8_uint16_m8(const rvm_int8_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_int8_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_uint64_uint16(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_uint64_uint16_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_uint64_uint16_m2(const rvm_uint64_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_uint64_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_uint64_uint16_m4(const rvm_uint64_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_uint64_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_uint64_uint16_m8(const rvm_uint64_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_uint64_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_uint32_uint16(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_uint32_uint16_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_uint32_uint16_m2(const rvm_uint32_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_uint32_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_uint32_uint16_m4(const rvm_uint32_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_uint32_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_uint32_uint16_m8(const rvm_uint32_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_uint32_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_uint16_uint16(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_uint16_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_uint16_uint16_m2(const rvm_uint16_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_uint16_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_uint16_uint16_m4(const rvm_uint16_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_uint16_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_uint16_uint16_m8(const rvm_uint16_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_uint16_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint16_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_cast_k_uint8_uint16(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_cast_k_uint8_uint16_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint16(m0);
}
rvm_uint16_m2_t mipp_cast_k_uint8_uint16_m2(const rvm_uint8_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cast_k_uint8_uint16_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_cast_k_uint8_uint16_m4(const rvm_uint8_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cast_k_uint8_uint16_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_cast_k_uint8_uint16_m8(const rvm_uint8_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cast_k_uint8_uint16_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint16_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_float64_uint8(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float64_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_float64_uint8_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_float64_uint8_m2(const rvm_float64_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_float64_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_float64_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_float64_uint8_m4(const rvm_float64_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_float64_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_float64_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_float64_uint8_m8(const rvm_float64_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_float64_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_float64_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_float32_uint8(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_float32_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_float32_uint8_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_float32_uint8_m2(const rvm_float32_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_float32_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_float32_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_float32_uint8_m4(const rvm_float32_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_float32_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_float32_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_float32_uint8_m8(const rvm_float32_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_float32_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_float32_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_int64_uint8(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int64_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_int64_uint8_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_int64_uint8_m2(const rvm_int64_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_int64_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_int64_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_int64_uint8_m4(const rvm_int64_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_int64_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_int64_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_int64_uint8_m8(const rvm_int64_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_int64_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_int64_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_int32_uint8(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int32_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_int32_uint8_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_int32_uint8_m2(const rvm_int32_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_int32_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_int32_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_int32_uint8_m4(const rvm_int32_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_int32_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_int32_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_int32_uint8_m8(const rvm_int32_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_int32_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_int32_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_int16_uint8(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int16_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_int16_uint8_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_int16_uint8_m2(const rvm_int16_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_int16_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_int16_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_int16_uint8_m4(const rvm_int16_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_int16_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_int16_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_int16_uint8_m8(const rvm_int16_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_int16_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_int16_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_int8_uint8(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_int8_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_int8_uint8_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_int8_uint8_m2(const rvm_int8_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_int8_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_int8_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_int8_uint8_m4(const rvm_int8_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_int8_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_int8_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_int8_uint8_m8(const rvm_int8_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_int8_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_int8_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_uint64_uint8(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_uint64_uint8_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_uint64_uint8_m2(const rvm_uint64_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_uint64_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_uint64_uint8_m4(const rvm_uint64_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_uint64_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_uint64_uint8_m8(const rvm_uint64_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_uint64_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint64_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_uint32_uint8(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_uint32_uint8_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_uint32_uint8_m2(const rvm_uint32_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_uint32_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_uint32_uint8_m4(const rvm_uint32_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_uint32_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_uint32_uint8_m8(const rvm_uint32_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_uint32_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint32_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_uint16_uint8(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_uint16_uint8_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_uint16_uint8_m2(const rvm_uint16_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_uint16_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_uint16_uint8_m4(const rvm_uint16_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_uint16_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_uint16_uint8_m8(const rvm_uint16_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_uint16_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint16_uint8_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_cast_k_uint8_uint8(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_cast_k_uint8_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint8(m0);
}
rvm_uint8_m2_t mipp_cast_k_uint8_uint8_m2(const rvm_uint8_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cast_k_uint8_uint8_m1(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_cast_k_uint8_uint8_m4(const rvm_uint8_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cast_k_uint8_uint8_m2(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_cast_k_uint8_uint8_m8(const rvm_uint8_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cast_k_uint8_uint8_m4(m0.m1);
	res.m2 = mipp_cast_k_uint8_uint8_m4(m0.m2);
	return res;
}
rvd_float64_t mipp_toreg_float64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_float64(m0);
#endif
}
rvd_float64_m1_t mipp_toreg_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_toreg_float64(m0);
}
rvd_float64_m2_t mipp_toreg_float64_m2(const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_toreg_float64_m1(m0.m1);
	res.m2 = mipp_toreg_float64_m1(m0.m2);
	return res;
}
rvd_float64_m4_t mipp_toreg_float64_m4(const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_toreg_float64_m2(m0.m1);
	res.m2 = mipp_toreg_float64_m2(m0.m2);
	return res;
}
rvd_float64_m8_t mipp_toreg_float64_m8(const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_toreg_float64_m4(m0.m1);
	res.m2 = mipp_toreg_float64_m4(m0.m2);
	return res;
}
rvd_float32_t mipp_toreg_float32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_float32(m0);
#endif
}
rvd_float32_m1_t mipp_toreg_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_toreg_float32(m0);
}
rvd_float32_m2_t mipp_toreg_float32_m2(const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_toreg_float32_m1(m0.m1);
	res.m2 = mipp_toreg_float32_m1(m0.m2);
	return res;
}
rvd_float32_m4_t mipp_toreg_float32_m4(const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_toreg_float32_m2(m0.m1);
	res.m2 = mipp_toreg_float32_m2(m0.m2);
	return res;
}
rvd_float32_m8_t mipp_toreg_float32_m8(const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_toreg_float32_m4(m0.m1);
	res.m2 = mipp_toreg_float32_m4(m0.m2);
	return res;
}
rvd_int64_t mipp_toreg_int64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_int64(m0);
#endif
}
rvd_int64_m1_t mipp_toreg_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_toreg_int64(m0);
}
rvd_int64_m2_t mipp_toreg_int64_m2(const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_toreg_int64_m1(m0.m1);
	res.m2 = mipp_toreg_int64_m1(m0.m2);
	return res;
}
rvd_int64_m4_t mipp_toreg_int64_m4(const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_toreg_int64_m2(m0.m1);
	res.m2 = mipp_toreg_int64_m2(m0.m2);
	return res;
}
rvd_int64_m8_t mipp_toreg_int64_m8(const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_toreg_int64_m4(m0.m1);
	res.m2 = mipp_toreg_int64_m4(m0.m2);
	return res;
}
rvd_int32_t mipp_toreg_int32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_int32(m0);
#endif
}
rvd_int32_m1_t mipp_toreg_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_toreg_int32(m0);
}
rvd_int32_m2_t mipp_toreg_int32_m2(const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_toreg_int32_m1(m0.m1);
	res.m2 = mipp_toreg_int32_m1(m0.m2);
	return res;
}
rvd_int32_m4_t mipp_toreg_int32_m4(const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_toreg_int32_m2(m0.m1);
	res.m2 = mipp_toreg_int32_m2(m0.m2);
	return res;
}
rvd_int32_m8_t mipp_toreg_int32_m8(const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_toreg_int32_m4(m0.m1);
	res.m2 = mipp_toreg_int32_m4(m0.m2);
	return res;
}
rvd_int16_t mipp_toreg_int16(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_int16(m0);
#endif
}
rvd_int16_m1_t mipp_toreg_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_toreg_int16(m0);
}
rvd_int16_m2_t mipp_toreg_int16_m2(const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_toreg_int16_m1(m0.m1);
	res.m2 = mipp_toreg_int16_m1(m0.m2);
	return res;
}
rvd_int16_m4_t mipp_toreg_int16_m4(const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_toreg_int16_m2(m0.m1);
	res.m2 = mipp_toreg_int16_m2(m0.m2);
	return res;
}
rvd_int16_m8_t mipp_toreg_int16_m8(const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_toreg_int16_m4(m0.m1);
	res.m2 = mipp_toreg_int16_m4(m0.m2);
	return res;
}
rvd_int8_t mipp_toreg_int8(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_int8(m0);
#endif
}
rvd_int8_m1_t mipp_toreg_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_toreg_int8(m0);
}
rvd_int8_m2_t mipp_toreg_int8_m2(const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_toreg_int8_m1(m0.m1);
	res.m2 = mipp_toreg_int8_m1(m0.m2);
	return res;
}
rvd_int8_m4_t mipp_toreg_int8_m4(const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_toreg_int8_m2(m0.m1);
	res.m2 = mipp_toreg_int8_m2(m0.m2);
	return res;
}
rvd_int8_m8_t mipp_toreg_int8_m8(const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_toreg_int8_m4(m0.m1);
	res.m2 = mipp_toreg_int8_m4(m0.m2);
	return res;
}
rvd_uint64_t mipp_toreg_uint64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_uint64(m0);
#endif
}
rvd_uint64_m1_t mipp_toreg_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_toreg_uint64(m0);
}
rvd_uint64_m2_t mipp_toreg_uint64_m2(const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_toreg_uint64_m1(m0.m1);
	res.m2 = mipp_toreg_uint64_m1(m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_toreg_uint64_m4(const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_toreg_uint64_m2(m0.m1);
	res.m2 = mipp_toreg_uint64_m2(m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_toreg_uint64_m8(const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_toreg_uint64_m4(m0.m1);
	res.m2 = mipp_toreg_uint64_m4(m0.m2);
	return res;
}
rvd_uint32_t mipp_toreg_uint32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_uint32(m0);
#endif
}
rvd_uint32_m1_t mipp_toreg_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_toreg_uint32(m0);
}
rvd_uint32_m2_t mipp_toreg_uint32_m2(const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_toreg_uint32_m1(m0.m1);
	res.m2 = mipp_toreg_uint32_m1(m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_toreg_uint32_m4(const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_toreg_uint32_m2(m0.m1);
	res.m2 = mipp_toreg_uint32_m2(m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_toreg_uint32_m8(const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_toreg_uint32_m4(m0.m1);
	res.m2 = mipp_toreg_uint32_m4(m0.m2);
	return res;
}
rvd_uint16_t mipp_toreg_uint16(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_uint16(m0);
#endif
}
rvd_uint16_m1_t mipp_toreg_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_toreg_uint16(m0);
}
rvd_uint16_m2_t mipp_toreg_uint16_m2(const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_toreg_uint16_m1(m0.m1);
	res.m2 = mipp_toreg_uint16_m1(m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_toreg_uint16_m4(const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_toreg_uint16_m2(m0.m1);
	res.m2 = mipp_toreg_uint16_m2(m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_toreg_uint16_m8(const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_toreg_uint16_m4(m0.m1);
	res.m2 = mipp_toreg_uint16_m4(m0.m2);
	return res;
}
rvd_uint8_t mipp_toreg_uint8(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_toreg_uint8(m0);
#endif
}
rvd_uint8_m1_t mipp_toreg_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_toreg_uint8(m0);
}
rvd_uint8_m2_t mipp_toreg_uint8_m2(const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_toreg_uint8_m1(m0.m1);
	res.m2 = mipp_toreg_uint8_m1(m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_toreg_uint8_m4(const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_toreg_uint8_m2(m0.m1);
	res.m2 = mipp_toreg_uint8_m2(m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_toreg_uint8_m8(const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_toreg_uint8_m4(m0.m1);
	res.m2 = mipp_toreg_uint8_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_tomsk_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_float64(r0);
#endif
}
rvm_float64_m1_t mipp_tomsk_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_tomsk_float64(r0);
}
rvm_float64_m2_t mipp_tomsk_float64_m2(const rvd_float64_m2_t r0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_tomsk_float64_m1(r0.m1);
	res.m2 = mipp_tomsk_float64_m1(r0.m2);
	return res;
}
rvm_float64_m4_t mipp_tomsk_float64_m4(const rvd_float64_m4_t r0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_tomsk_float64_m2(r0.m1);
	res.m2 = mipp_tomsk_float64_m2(r0.m2);
	return res;
}
rvm_float64_m8_t mipp_tomsk_float64_m8(const rvd_float64_m8_t r0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_tomsk_float64_m4(r0.m1);
	res.m2 = mipp_tomsk_float64_m4(r0.m2);
	return res;
}
rvm_float32_t mipp_tomsk_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_float32(r0);
#endif
}
rvm_float32_m1_t mipp_tomsk_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_tomsk_float32(r0);
}
rvm_float32_m2_t mipp_tomsk_float32_m2(const rvd_float32_m2_t r0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_tomsk_float32_m1(r0.m1);
	res.m2 = mipp_tomsk_float32_m1(r0.m2);
	return res;
}
rvm_float32_m4_t mipp_tomsk_float32_m4(const rvd_float32_m4_t r0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_tomsk_float32_m2(r0.m1);
	res.m2 = mipp_tomsk_float32_m2(r0.m2);
	return res;
}
rvm_float32_m8_t mipp_tomsk_float32_m8(const rvd_float32_m8_t r0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_tomsk_float32_m4(r0.m1);
	res.m2 = mipp_tomsk_float32_m4(r0.m2);
	return res;
}
rvm_int64_t mipp_tomsk_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_int64(r0);
#endif
}
rvm_int64_m1_t mipp_tomsk_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_tomsk_int64(r0);
}
rvm_int64_m2_t mipp_tomsk_int64_m2(const rvd_int64_m2_t r0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_tomsk_int64_m1(r0.m1);
	res.m2 = mipp_tomsk_int64_m1(r0.m2);
	return res;
}
rvm_int64_m4_t mipp_tomsk_int64_m4(const rvd_int64_m4_t r0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_tomsk_int64_m2(r0.m1);
	res.m2 = mipp_tomsk_int64_m2(r0.m2);
	return res;
}
rvm_int64_m8_t mipp_tomsk_int64_m8(const rvd_int64_m8_t r0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_tomsk_int64_m4(r0.m1);
	res.m2 = mipp_tomsk_int64_m4(r0.m2);
	return res;
}
rvm_int32_t mipp_tomsk_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_int32(r0);
#endif
}
rvm_int32_m1_t mipp_tomsk_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_tomsk_int32(r0);
}
rvm_int32_m2_t mipp_tomsk_int32_m2(const rvd_int32_m2_t r0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_tomsk_int32_m1(r0.m1);
	res.m2 = mipp_tomsk_int32_m1(r0.m2);
	return res;
}
rvm_int32_m4_t mipp_tomsk_int32_m4(const rvd_int32_m4_t r0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_tomsk_int32_m2(r0.m1);
	res.m2 = mipp_tomsk_int32_m2(r0.m2);
	return res;
}
rvm_int32_m8_t mipp_tomsk_int32_m8(const rvd_int32_m8_t r0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_tomsk_int32_m4(r0.m1);
	res.m2 = mipp_tomsk_int32_m4(r0.m2);
	return res;
}
rvm_int16_t mipp_tomsk_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_int16(r0);
#endif
}
rvm_int16_m1_t mipp_tomsk_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_tomsk_int16(r0);
}
rvm_int16_m2_t mipp_tomsk_int16_m2(const rvd_int16_m2_t r0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_tomsk_int16_m1(r0.m1);
	res.m2 = mipp_tomsk_int16_m1(r0.m2);
	return res;
}
rvm_int16_m4_t mipp_tomsk_int16_m4(const rvd_int16_m4_t r0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_tomsk_int16_m2(r0.m1);
	res.m2 = mipp_tomsk_int16_m2(r0.m2);
	return res;
}
rvm_int16_m8_t mipp_tomsk_int16_m8(const rvd_int16_m8_t r0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_tomsk_int16_m4(r0.m1);
	res.m2 = mipp_tomsk_int16_m4(r0.m2);
	return res;
}
rvm_int8_t mipp_tomsk_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_int8(r0);
#endif
}
rvm_int8_m1_t mipp_tomsk_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_tomsk_int8(r0);
}
rvm_int8_m2_t mipp_tomsk_int8_m2(const rvd_int8_m2_t r0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_tomsk_int8_m1(r0.m1);
	res.m2 = mipp_tomsk_int8_m1(r0.m2);
	return res;
}
rvm_int8_m4_t mipp_tomsk_int8_m4(const rvd_int8_m4_t r0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_tomsk_int8_m2(r0.m1);
	res.m2 = mipp_tomsk_int8_m2(r0.m2);
	return res;
}
rvm_int8_m8_t mipp_tomsk_int8_m8(const rvd_int8_m8_t r0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_tomsk_int8_m4(r0.m1);
	res.m2 = mipp_tomsk_int8_m4(r0.m2);
	return res;
}
rvm_uint64_t mipp_tomsk_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_uint64(r0);
#endif
}
rvm_uint64_m1_t mipp_tomsk_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_tomsk_uint64(r0);
}
rvm_uint64_m2_t mipp_tomsk_uint64_m2(const rvd_uint64_m2_t r0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_tomsk_uint64_m1(r0.m1);
	res.m2 = mipp_tomsk_uint64_m1(r0.m2);
	return res;
}
rvm_uint64_m4_t mipp_tomsk_uint64_m4(const rvd_uint64_m4_t r0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_tomsk_uint64_m2(r0.m1);
	res.m2 = mipp_tomsk_uint64_m2(r0.m2);
	return res;
}
rvm_uint64_m8_t mipp_tomsk_uint64_m8(const rvd_uint64_m8_t r0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_tomsk_uint64_m4(r0.m1);
	res.m2 = mipp_tomsk_uint64_m4(r0.m2);
	return res;
}
rvm_uint32_t mipp_tomsk_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_uint32(r0);
#endif
}
rvm_uint32_m1_t mipp_tomsk_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_tomsk_uint32(r0);
}
rvm_uint32_m2_t mipp_tomsk_uint32_m2(const rvd_uint32_m2_t r0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_tomsk_uint32_m1(r0.m1);
	res.m2 = mipp_tomsk_uint32_m1(r0.m2);
	return res;
}
rvm_uint32_m4_t mipp_tomsk_uint32_m4(const rvd_uint32_m4_t r0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_tomsk_uint32_m2(r0.m1);
	res.m2 = mipp_tomsk_uint32_m2(r0.m2);
	return res;
}
rvm_uint32_m8_t mipp_tomsk_uint32_m8(const rvd_uint32_m8_t r0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_tomsk_uint32_m4(r0.m1);
	res.m2 = mipp_tomsk_uint32_m4(r0.m2);
	return res;
}
rvm_uint16_t mipp_tomsk_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_uint16(r0);
#endif
}
rvm_uint16_m1_t mipp_tomsk_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_tomsk_uint16(r0);
}
rvm_uint16_m2_t mipp_tomsk_uint16_m2(const rvd_uint16_m2_t r0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_tomsk_uint16_m1(r0.m1);
	res.m2 = mipp_tomsk_uint16_m1(r0.m2);
	return res;
}
rvm_uint16_m4_t mipp_tomsk_uint16_m4(const rvd_uint16_m4_t r0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_tomsk_uint16_m2(r0.m1);
	res.m2 = mipp_tomsk_uint16_m2(r0.m2);
	return res;
}
rvm_uint16_m8_t mipp_tomsk_uint16_m8(const rvd_uint16_m8_t r0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_tomsk_uint16_m4(r0.m1);
	res.m2 = mipp_tomsk_uint16_m4(r0.m2);
	return res;
}
rvm_uint8_t mipp_tomsk_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_tomsk_uint8(r0);
#endif
}
rvm_uint8_m1_t mipp_tomsk_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_tomsk_uint8(r0);
}
rvm_uint8_m2_t mipp_tomsk_uint8_m2(const rvd_uint8_m2_t r0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_tomsk_uint8_m1(r0.m1);
	res.m2 = mipp_tomsk_uint8_m1(r0.m2);
	return res;
}
rvm_uint8_m4_t mipp_tomsk_uint8_m4(const rvd_uint8_m4_t r0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_tomsk_uint8_m2(r0.m1);
	res.m2 = mipp_tomsk_uint8_m2(r0.m2);
	return res;
}
rvm_uint8_m8_t mipp_tomsk_uint8_m8(const rvd_uint8_m8_t r0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_tomsk_uint8_m4(r0.m1);
	res.m2 = mipp_tomsk_uint8_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_load_float64(const float64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_float64(p0);
#endif
}
rvd_float64_m1_t mipp_load_float64_m1(const float64_t* p0) {
	return mipp_load_float64(p0);
}
rvd_float64_m2_t mipp_load_float64_m2(const float64_t* p0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_load_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_float64_m4_t mipp_load_float64_m4(const float64_t* p0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_load_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_float64_m8_t mipp_load_float64_m8(const float64_t* p0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_load_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_float32_t mipp_load_float32(const float32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_float32(p0);
#endif
}
rvd_float32_m1_t mipp_load_float32_m1(const float32_t* p0) {
	return mipp_load_float32(p0);
}
rvd_float32_m2_t mipp_load_float32_m2(const float32_t* p0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_load_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_float32_m4_t mipp_load_float32_m4(const float32_t* p0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_load_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_float32_m8_t mipp_load_float32_m8(const float32_t* p0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_load_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int64_t mipp_load_int64(const int64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_int64(p0);
#endif
}
rvd_int64_m1_t mipp_load_int64_m1(const int64_t* p0) {
	return mipp_load_int64(p0);
}
rvd_int64_m2_t mipp_load_int64_m2(const int64_t* p0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_load_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int64_m4_t mipp_load_int64_m4(const int64_t* p0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_load_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int64_m8_t mipp_load_int64_m8(const int64_t* p0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_load_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int32_t mipp_load_int32(const int32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_int32(p0);
#endif
}
rvd_int32_m1_t mipp_load_int32_m1(const int32_t* p0) {
	return mipp_load_int32(p0);
}
rvd_int32_m2_t mipp_load_int32_m2(const int32_t* p0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_load_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int32_m4_t mipp_load_int32_m4(const int32_t* p0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_load_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int32_m8_t mipp_load_int32_m8(const int32_t* p0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_load_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int16_t mipp_load_int16(const int16_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_int16(p0);
#endif
}
rvd_int16_m1_t mipp_load_int16_m1(const int16_t* p0) {
	return mipp_load_int16(p0);
}
rvd_int16_m2_t mipp_load_int16_m2(const int16_t* p0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_load_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int16_m4_t mipp_load_int16_m4(const int16_t* p0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_load_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int16_m8_t mipp_load_int16_m8(const int16_t* p0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_load_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int8_t mipp_load_int8(const int8_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_int8(p0);
#endif
}
rvd_int8_m1_t mipp_load_int8_m1(const int8_t* p0) {
	return mipp_load_int8(p0);
}
rvd_int8_m2_t mipp_load_int8_m2(const int8_t* p0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_load_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int8_m4_t mipp_load_int8_m4(const int8_t* p0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_load_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int8_m8_t mipp_load_int8_m8(const int8_t* p0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_load_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint64_t mipp_load_uint64(const uint64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_uint64(p0);
#endif
}
rvd_uint64_m1_t mipp_load_uint64_m1(const uint64_t* p0) {
	return mipp_load_uint64(p0);
}
rvd_uint64_m2_t mipp_load_uint64_m2(const uint64_t* p0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_load_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint64_m4_t mipp_load_uint64_m4(const uint64_t* p0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_load_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint64_m8_t mipp_load_uint64_m8(const uint64_t* p0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_load_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint32_t mipp_load_uint32(const uint32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_uint32(p0);
#endif
}
rvd_uint32_m1_t mipp_load_uint32_m1(const uint32_t* p0) {
	return mipp_load_uint32(p0);
}
rvd_uint32_m2_t mipp_load_uint32_m2(const uint32_t* p0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_load_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint32_m4_t mipp_load_uint32_m4(const uint32_t* p0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_load_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint32_m8_t mipp_load_uint32_m8(const uint32_t* p0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_load_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint16_t mipp_load_uint16(const uint16_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_uint16(p0);
#endif
}
rvd_uint16_m1_t mipp_load_uint16_m1(const uint16_t* p0) {
	return mipp_load_uint16(p0);
}
rvd_uint16_m2_t mipp_load_uint16_m2(const uint16_t* p0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_load_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint16_m4_t mipp_load_uint16_m4(const uint16_t* p0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_load_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint16_m8_t mipp_load_uint16_m8(const uint16_t* p0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_load_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint8_t mipp_load_uint8(const uint8_t* p0) {
#if defined(__AVX__)
	return mipp_avx_load_uint8(p0);
#endif
}
rvd_uint8_m1_t mipp_load_uint8_m1(const uint8_t* p0) {
	return mipp_load_uint8(p0);
}
rvd_uint8_m2_t mipp_load_uint8_m2(const uint8_t* p0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_load_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_load_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint8_m4_t mipp_load_uint8_m4(const uint8_t* p0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_load_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_load_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint8_m8_t mipp_load_uint8_m8(const uint8_t* p0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_load_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_load_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_float64_t mipp_loadu_float64(const float64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_float64(p0);
#endif
}
rvd_float64_m1_t mipp_loadu_float64_m1(const float64_t* p0) {
	return mipp_loadu_float64(p0);
}
rvd_float64_m2_t mipp_loadu_float64_m2(const float64_t* p0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_loadu_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_float64_m4_t mipp_loadu_float64_m4(const float64_t* p0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_loadu_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_float64_m8_t mipp_loadu_float64_m8(const float64_t* p0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_loadu_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_float32_t mipp_loadu_float32(const float32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_float32(p0);
#endif
}
rvd_float32_m1_t mipp_loadu_float32_m1(const float32_t* p0) {
	return mipp_loadu_float32(p0);
}
rvd_float32_m2_t mipp_loadu_float32_m2(const float32_t* p0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_loadu_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_float32_m4_t mipp_loadu_float32_m4(const float32_t* p0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_loadu_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_float32_m8_t mipp_loadu_float32_m8(const float32_t* p0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_loadu_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int64_t mipp_loadu_int64(const int64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_int64(p0);
#endif
}
rvd_int64_m1_t mipp_loadu_int64_m1(const int64_t* p0) {
	return mipp_loadu_int64(p0);
}
rvd_int64_m2_t mipp_loadu_int64_m2(const int64_t* p0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_loadu_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int64_m4_t mipp_loadu_int64_m4(const int64_t* p0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_loadu_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int64_m8_t mipp_loadu_int64_m8(const int64_t* p0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_loadu_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int32_t mipp_loadu_int32(const int32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_int32(p0);
#endif
}
rvd_int32_m1_t mipp_loadu_int32_m1(const int32_t* p0) {
	return mipp_loadu_int32(p0);
}
rvd_int32_m2_t mipp_loadu_int32_m2(const int32_t* p0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_loadu_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int32_m4_t mipp_loadu_int32_m4(const int32_t* p0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_loadu_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int32_m8_t mipp_loadu_int32_m8(const int32_t* p0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_loadu_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int16_t mipp_loadu_int16(const int16_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_int16(p0);
#endif
}
rvd_int16_m1_t mipp_loadu_int16_m1(const int16_t* p0) {
	return mipp_loadu_int16(p0);
}
rvd_int16_m2_t mipp_loadu_int16_m2(const int16_t* p0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_loadu_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int16_m4_t mipp_loadu_int16_m4(const int16_t* p0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_loadu_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int16_m8_t mipp_loadu_int16_m8(const int16_t* p0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_loadu_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_int8_t mipp_loadu_int8(const int8_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_int8(p0);
#endif
}
rvd_int8_m1_t mipp_loadu_int8_m1(const int8_t* p0) {
	return mipp_loadu_int8(p0);
}
rvd_int8_m2_t mipp_loadu_int8_m2(const int8_t* p0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_loadu_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_int8_m4_t mipp_loadu_int8_m4(const int8_t* p0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_loadu_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_int8_m8_t mipp_loadu_int8_m8(const int8_t* p0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_loadu_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint64_t mipp_loadu_uint64(const uint64_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_uint64(p0);
#endif
}
rvd_uint64_m1_t mipp_loadu_uint64_m1(const uint64_t* p0) {
	return mipp_loadu_uint64(p0);
}
rvd_uint64_m2_t mipp_loadu_uint64_m2(const uint64_t* p0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_loadu_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint64_m4_t mipp_loadu_uint64_m4(const uint64_t* p0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_loadu_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint64_m8_t mipp_loadu_uint64_m8(const uint64_t* p0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_loadu_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint32_t mipp_loadu_uint32(const uint32_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_uint32(p0);
#endif
}
rvd_uint32_m1_t mipp_loadu_uint32_m1(const uint32_t* p0) {
	return mipp_loadu_uint32(p0);
}
rvd_uint32_m2_t mipp_loadu_uint32_m2(const uint32_t* p0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_loadu_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint32_m4_t mipp_loadu_uint32_m4(const uint32_t* p0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_loadu_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint32_m8_t mipp_loadu_uint32_m8(const uint32_t* p0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_loadu_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint16_t mipp_loadu_uint16(const uint16_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_uint16(p0);
#endif
}
rvd_uint16_m1_t mipp_loadu_uint16_m1(const uint16_t* p0) {
	return mipp_loadu_uint16(p0);
}
rvd_uint16_m2_t mipp_loadu_uint16_m2(const uint16_t* p0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_loadu_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint16_m4_t mipp_loadu_uint16_m4(const uint16_t* p0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_loadu_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint16_m8_t mipp_loadu_uint16_m8(const uint16_t* p0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_loadu_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
rvd_uint8_t mipp_loadu_uint8(const uint8_t* p0) {
#if defined(__AVX__)
	return mipp_avx_loadu_uint8(p0);
#endif
}
rvd_uint8_m1_t mipp_loadu_uint8_m1(const uint8_t* p0) {
	return mipp_loadu_uint8(p0);
}
rvd_uint8_m2_t mipp_loadu_uint8_m2(const uint8_t* p0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_loadu_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.m2 = mipp_loadu_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
rvd_uint8_m4_t mipp_loadu_uint8_m4(const uint8_t* p0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_loadu_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.m2 = mipp_loadu_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
rvd_uint8_m8_t mipp_loadu_uint8_m8(const uint8_t* p0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_loadu_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.m2 = mipp_loadu_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
void mipp_store_float64(float64_t* p0, const rvd_float64_t r0) {
#if defined(__AVX__)
	mipp_avx_store_float64(p0, r0);
#endif
}
void mipp_store_float64_m1(float64_t* p0, const rvd_float64_m1_t r0) {
	mipp_store_float64(p0, r0);
}
void mipp_store_float64_m2(float64_t* p0, const rvd_float64_m2_t r0) {
	mipp_store_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_float64_m4(float64_t* p0, const rvd_float64_m4_t r0) {
	mipp_store_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_float64_m8(float64_t* p0, const rvd_float64_m8_t r0) {
	mipp_store_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_float32(float32_t* p0, const rvd_float32_t r0) {
#if defined(__AVX__)
	mipp_avx_store_float32(p0, r0);
#endif
}
void mipp_store_float32_m1(float32_t* p0, const rvd_float32_m1_t r0) {
	mipp_store_float32(p0, r0);
}
void mipp_store_float32_m2(float32_t* p0, const rvd_float32_m2_t r0) {
	mipp_store_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_float32_m4(float32_t* p0, const rvd_float32_m4_t r0) {
	mipp_store_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_float32_m8(float32_t* p0, const rvd_float32_m8_t r0) {
	mipp_store_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_int64(int64_t* p0, const rvd_int64_t r0) {
#if defined(__AVX__)
	mipp_avx_store_int64(p0, r0);
#endif
}
void mipp_store_int64_m1(int64_t* p0, const rvd_int64_m1_t r0) {
	mipp_store_int64(p0, r0);
}
void mipp_store_int64_m2(int64_t* p0, const rvd_int64_m2_t r0) {
	mipp_store_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_int64_m4(int64_t* p0, const rvd_int64_m4_t r0) {
	mipp_store_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_int64_m8(int64_t* p0, const rvd_int64_m8_t r0) {
	mipp_store_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_int32(int32_t* p0, const rvd_int32_t r0) {
#if defined(__AVX__)
	mipp_avx_store_int32(p0, r0);
#endif
}
void mipp_store_int32_m1(int32_t* p0, const rvd_int32_m1_t r0) {
	mipp_store_int32(p0, r0);
}
void mipp_store_int32_m2(int32_t* p0, const rvd_int32_m2_t r0) {
	mipp_store_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_int32_m4(int32_t* p0, const rvd_int32_m4_t r0) {
	mipp_store_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_int32_m8(int32_t* p0, const rvd_int32_m8_t r0) {
	mipp_store_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_int16(int16_t* p0, const rvd_int16_t r0) {
#if defined(__AVX__)
	mipp_avx_store_int16(p0, r0);
#endif
}
void mipp_store_int16_m1(int16_t* p0, const rvd_int16_m1_t r0) {
	mipp_store_int16(p0, r0);
}
void mipp_store_int16_m2(int16_t* p0, const rvd_int16_m2_t r0) {
	mipp_store_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_int16_m4(int16_t* p0, const rvd_int16_m4_t r0) {
	mipp_store_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_int16_m8(int16_t* p0, const rvd_int16_m8_t r0) {
	mipp_store_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_int8(int8_t* p0, const rvd_int8_t r0) {
#if defined(__AVX__)
	mipp_avx_store_int8(p0, r0);
#endif
}
void mipp_store_int8_m1(int8_t* p0, const rvd_int8_m1_t r0) {
	mipp_store_int8(p0, r0);
}
void mipp_store_int8_m2(int8_t* p0, const rvd_int8_m2_t r0) {
	mipp_store_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_int8_m4(int8_t* p0, const rvd_int8_m4_t r0) {
	mipp_store_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_int8_m8(int8_t* p0, const rvd_int8_m8_t r0) {
	mipp_store_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_uint64(uint64_t* p0, const rvd_uint64_t r0) {
#if defined(__AVX__)
	mipp_avx_store_uint64(p0, r0);
#endif
}
void mipp_store_uint64_m1(uint64_t* p0, const rvd_uint64_m1_t r0) {
	mipp_store_uint64(p0, r0);
}
void mipp_store_uint64_m2(uint64_t* p0, const rvd_uint64_m2_t r0) {
	mipp_store_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_uint64_m4(uint64_t* p0, const rvd_uint64_m4_t r0) {
	mipp_store_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_uint64_m8(uint64_t* p0, const rvd_uint64_m8_t r0) {
	mipp_store_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_uint32(uint32_t* p0, const rvd_uint32_t r0) {
#if defined(__AVX__)
	mipp_avx_store_uint32(p0, r0);
#endif
}
void mipp_store_uint32_m1(uint32_t* p0, const rvd_uint32_m1_t r0) {
	mipp_store_uint32(p0, r0);
}
void mipp_store_uint32_m2(uint32_t* p0, const rvd_uint32_m2_t r0) {
	mipp_store_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_uint32_m4(uint32_t* p0, const rvd_uint32_m4_t r0) {
	mipp_store_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_uint32_m8(uint32_t* p0, const rvd_uint32_m8_t r0) {
	mipp_store_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_uint16(uint16_t* p0, const rvd_uint16_t r0) {
#if defined(__AVX__)
	mipp_avx_store_uint16(p0, r0);
#endif
}
void mipp_store_uint16_m1(uint16_t* p0, const rvd_uint16_m1_t r0) {
	mipp_store_uint16(p0, r0);
}
void mipp_store_uint16_m2(uint16_t* p0, const rvd_uint16_m2_t r0) {
	mipp_store_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_uint16_m4(uint16_t* p0, const rvd_uint16_m4_t r0) {
	mipp_store_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_uint16_m8(uint16_t* p0, const rvd_uint16_m8_t r0) {
	mipp_store_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_store_uint8(uint8_t* p0, const rvd_uint8_t r0) {
#if defined(__AVX__)
	mipp_avx_store_uint8(p0, r0);
#endif
}
void mipp_store_uint8_m1(uint8_t* p0, const rvd_uint8_m1_t r0) {
	mipp_store_uint8(p0, r0);
}
void mipp_store_uint8_m2(uint8_t* p0, const rvd_uint8_m2_t r0) {
	mipp_store_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_store_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_store_uint8_m4(uint8_t* p0, const rvd_uint8_m4_t r0) {
	mipp_store_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_store_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_store_uint8_m8(uint8_t* p0, const rvd_uint8_m8_t r0) {
	mipp_store_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_store_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_float64(float64_t* p0, const rvd_float64_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_float64(p0, r0);
#endif
}
void mipp_storeu_float64_m1(float64_t* p0, const rvd_float64_m1_t r0) {
	mipp_storeu_float64(p0, r0);
}
void mipp_storeu_float64_m2(float64_t* p0, const rvd_float64_m2_t r0) {
	mipp_storeu_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_float64_m4(float64_t* p0, const rvd_float64_m4_t r0) {
	mipp_storeu_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_float64_m8(float64_t* p0, const rvd_float64_m8_t r0) {
	mipp_storeu_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_float32(float32_t* p0, const rvd_float32_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_float32(p0, r0);
#endif
}
void mipp_storeu_float32_m1(float32_t* p0, const rvd_float32_m1_t r0) {
	mipp_storeu_float32(p0, r0);
}
void mipp_storeu_float32_m2(float32_t* p0, const rvd_float32_m2_t r0) {
	mipp_storeu_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_float32_m4(float32_t* p0, const rvd_float32_m4_t r0) {
	mipp_storeu_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_float32_m8(float32_t* p0, const rvd_float32_m8_t r0) {
	mipp_storeu_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_int64(int64_t* p0, const rvd_int64_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_int64(p0, r0);
#endif
}
void mipp_storeu_int64_m1(int64_t* p0, const rvd_int64_m1_t r0) {
	mipp_storeu_int64(p0, r0);
}
void mipp_storeu_int64_m2(int64_t* p0, const rvd_int64_m2_t r0) {
	mipp_storeu_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_int64_m4(int64_t* p0, const rvd_int64_m4_t r0) {
	mipp_storeu_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_int64_m8(int64_t* p0, const rvd_int64_m8_t r0) {
	mipp_storeu_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_int32(int32_t* p0, const rvd_int32_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_int32(p0, r0);
#endif
}
void mipp_storeu_int32_m1(int32_t* p0, const rvd_int32_m1_t r0) {
	mipp_storeu_int32(p0, r0);
}
void mipp_storeu_int32_m2(int32_t* p0, const rvd_int32_m2_t r0) {
	mipp_storeu_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_int32_m4(int32_t* p0, const rvd_int32_m4_t r0) {
	mipp_storeu_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_int32_m8(int32_t* p0, const rvd_int32_m8_t r0) {
	mipp_storeu_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_int16(int16_t* p0, const rvd_int16_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_int16(p0, r0);
#endif
}
void mipp_storeu_int16_m1(int16_t* p0, const rvd_int16_m1_t r0) {
	mipp_storeu_int16(p0, r0);
}
void mipp_storeu_int16_m2(int16_t* p0, const rvd_int16_m2_t r0) {
	mipp_storeu_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_int16_m4(int16_t* p0, const rvd_int16_m4_t r0) {
	mipp_storeu_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_int16_m8(int16_t* p0, const rvd_int16_m8_t r0) {
	mipp_storeu_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_int8(int8_t* p0, const rvd_int8_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_int8(p0, r0);
#endif
}
void mipp_storeu_int8_m1(int8_t* p0, const rvd_int8_m1_t r0) {
	mipp_storeu_int8(p0, r0);
}
void mipp_storeu_int8_m2(int8_t* p0, const rvd_int8_m2_t r0) {
	mipp_storeu_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_int8_m4(int8_t* p0, const rvd_int8_m4_t r0) {
	mipp_storeu_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_int8_m8(int8_t* p0, const rvd_int8_m8_t r0) {
	mipp_storeu_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_uint64(uint64_t* p0, const rvd_uint64_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_uint64(p0, r0);
#endif
}
void mipp_storeu_uint64_m1(uint64_t* p0, const rvd_uint64_m1_t r0) {
	mipp_storeu_uint64(p0, r0);
}
void mipp_storeu_uint64_m2(uint64_t* p0, const rvd_uint64_m2_t r0) {
	mipp_storeu_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_uint64_m4(uint64_t* p0, const rvd_uint64_m4_t r0) {
	mipp_storeu_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_uint64_m8(uint64_t* p0, const rvd_uint64_m8_t r0) {
	mipp_storeu_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_uint32(uint32_t* p0, const rvd_uint32_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_uint32(p0, r0);
#endif
}
void mipp_storeu_uint32_m1(uint32_t* p0, const rvd_uint32_m1_t r0) {
	mipp_storeu_uint32(p0, r0);
}
void mipp_storeu_uint32_m2(uint32_t* p0, const rvd_uint32_m2_t r0) {
	mipp_storeu_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_uint32_m4(uint32_t* p0, const rvd_uint32_m4_t r0) {
	mipp_storeu_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_uint32_m8(uint32_t* p0, const rvd_uint32_m8_t r0) {
	mipp_storeu_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_uint16(uint16_t* p0, const rvd_uint16_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_uint16(p0, r0);
#endif
}
void mipp_storeu_uint16_m1(uint16_t* p0, const rvd_uint16_m1_t r0) {
	mipp_storeu_uint16(p0, r0);
}
void mipp_storeu_uint16_m2(uint16_t* p0, const rvd_uint16_m2_t r0) {
	mipp_storeu_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_uint16_m4(uint16_t* p0, const rvd_uint16_m4_t r0) {
	mipp_storeu_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_uint16_m8(uint16_t* p0, const rvd_uint16_m8_t r0) {
	mipp_storeu_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
void mipp_storeu_uint8(uint8_t* p0, const rvd_uint8_t r0) {
#if defined(__AVX__)
	mipp_avx_storeu_uint8(p0, r0);
#endif
}
void mipp_storeu_uint8_m1(uint8_t* p0, const rvd_uint8_m1_t r0) {
	mipp_storeu_uint8(p0, r0);
}
void mipp_storeu_uint8_m2(uint8_t* p0, const rvd_uint8_m2_t r0) {
	mipp_storeu_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m1);
	mipp_storeu_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.m2);
}
void mipp_storeu_uint8_m4(uint8_t* p0, const rvd_uint8_m4_t r0) {
	mipp_storeu_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m1);
	mipp_storeu_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.m2);
}
void mipp_storeu_uint8_m8(uint8_t* p0, const rvd_uint8_m8_t r0) {
	mipp_storeu_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m1);
	mipp_storeu_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.m2);
}
rvd_float64_t mipp_set1_float64(const float64_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_float64(v0);
#endif
}
rvd_float64_m1_t mipp_set1_float64_m1(const float64_t v0) {
	return mipp_set1_float64(v0);
}
rvd_float64_m2_t mipp_set1_float64_m2(const float64_t v0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_set1_float64_m1(v0);
	res.m2 = mipp_set1_float64_m1(v0);
	return res;
}
rvd_float64_m4_t mipp_set1_float64_m4(const float64_t v0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_set1_float64_m2(v0);
	res.m2 = mipp_set1_float64_m2(v0);
	return res;
}
rvd_float64_m8_t mipp_set1_float64_m8(const float64_t v0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_set1_float64_m4(v0);
	res.m2 = mipp_set1_float64_m4(v0);
	return res;
}
rvd_float32_t mipp_set1_float32(const float32_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_float32(v0);
#endif
}
rvd_float32_m1_t mipp_set1_float32_m1(const float32_t v0) {
	return mipp_set1_float32(v0);
}
rvd_float32_m2_t mipp_set1_float32_m2(const float32_t v0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_set1_float32_m1(v0);
	res.m2 = mipp_set1_float32_m1(v0);
	return res;
}
rvd_float32_m4_t mipp_set1_float32_m4(const float32_t v0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_set1_float32_m2(v0);
	res.m2 = mipp_set1_float32_m2(v0);
	return res;
}
rvd_float32_m8_t mipp_set1_float32_m8(const float32_t v0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_set1_float32_m4(v0);
	res.m2 = mipp_set1_float32_m4(v0);
	return res;
}
rvd_int64_t mipp_set1_int64(const int64_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_int64(v0);
#endif
}
rvd_int64_m1_t mipp_set1_int64_m1(const int64_t v0) {
	return mipp_set1_int64(v0);
}
rvd_int64_m2_t mipp_set1_int64_m2(const int64_t v0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_set1_int64_m1(v0);
	res.m2 = mipp_set1_int64_m1(v0);
	return res;
}
rvd_int64_m4_t mipp_set1_int64_m4(const int64_t v0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_set1_int64_m2(v0);
	res.m2 = mipp_set1_int64_m2(v0);
	return res;
}
rvd_int64_m8_t mipp_set1_int64_m8(const int64_t v0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_set1_int64_m4(v0);
	res.m2 = mipp_set1_int64_m4(v0);
	return res;
}
rvd_int32_t mipp_set1_int32(const int32_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_int32(v0);
#endif
}
rvd_int32_m1_t mipp_set1_int32_m1(const int32_t v0) {
	return mipp_set1_int32(v0);
}
rvd_int32_m2_t mipp_set1_int32_m2(const int32_t v0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_set1_int32_m1(v0);
	res.m2 = mipp_set1_int32_m1(v0);
	return res;
}
rvd_int32_m4_t mipp_set1_int32_m4(const int32_t v0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_set1_int32_m2(v0);
	res.m2 = mipp_set1_int32_m2(v0);
	return res;
}
rvd_int32_m8_t mipp_set1_int32_m8(const int32_t v0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_set1_int32_m4(v0);
	res.m2 = mipp_set1_int32_m4(v0);
	return res;
}
rvd_int16_t mipp_set1_int16(const int16_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_int16(v0);
#endif
}
rvd_int16_m1_t mipp_set1_int16_m1(const int16_t v0) {
	return mipp_set1_int16(v0);
}
rvd_int16_m2_t mipp_set1_int16_m2(const int16_t v0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_set1_int16_m1(v0);
	res.m2 = mipp_set1_int16_m1(v0);
	return res;
}
rvd_int16_m4_t mipp_set1_int16_m4(const int16_t v0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_set1_int16_m2(v0);
	res.m2 = mipp_set1_int16_m2(v0);
	return res;
}
rvd_int16_m8_t mipp_set1_int16_m8(const int16_t v0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_set1_int16_m4(v0);
	res.m2 = mipp_set1_int16_m4(v0);
	return res;
}
rvd_int8_t mipp_set1_int8(const int8_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_int8(v0);
#endif
}
rvd_int8_m1_t mipp_set1_int8_m1(const int8_t v0) {
	return mipp_set1_int8(v0);
}
rvd_int8_m2_t mipp_set1_int8_m2(const int8_t v0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_set1_int8_m1(v0);
	res.m2 = mipp_set1_int8_m1(v0);
	return res;
}
rvd_int8_m4_t mipp_set1_int8_m4(const int8_t v0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_set1_int8_m2(v0);
	res.m2 = mipp_set1_int8_m2(v0);
	return res;
}
rvd_int8_m8_t mipp_set1_int8_m8(const int8_t v0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_set1_int8_m4(v0);
	res.m2 = mipp_set1_int8_m4(v0);
	return res;
}
rvd_uint64_t mipp_set1_uint64(const uint64_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_uint64(v0);
#endif
}
rvd_uint64_m1_t mipp_set1_uint64_m1(const uint64_t v0) {
	return mipp_set1_uint64(v0);
}
rvd_uint64_m2_t mipp_set1_uint64_m2(const uint64_t v0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_set1_uint64_m1(v0);
	res.m2 = mipp_set1_uint64_m1(v0);
	return res;
}
rvd_uint64_m4_t mipp_set1_uint64_m4(const uint64_t v0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_set1_uint64_m2(v0);
	res.m2 = mipp_set1_uint64_m2(v0);
	return res;
}
rvd_uint64_m8_t mipp_set1_uint64_m8(const uint64_t v0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_set1_uint64_m4(v0);
	res.m2 = mipp_set1_uint64_m4(v0);
	return res;
}
rvd_uint32_t mipp_set1_uint32(const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_uint32(v0);
#endif
}
rvd_uint32_m1_t mipp_set1_uint32_m1(const uint32_t v0) {
	return mipp_set1_uint32(v0);
}
rvd_uint32_m2_t mipp_set1_uint32_m2(const uint32_t v0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_set1_uint32_m1(v0);
	res.m2 = mipp_set1_uint32_m1(v0);
	return res;
}
rvd_uint32_m4_t mipp_set1_uint32_m4(const uint32_t v0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_set1_uint32_m2(v0);
	res.m2 = mipp_set1_uint32_m2(v0);
	return res;
}
rvd_uint32_m8_t mipp_set1_uint32_m8(const uint32_t v0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_set1_uint32_m4(v0);
	res.m2 = mipp_set1_uint32_m4(v0);
	return res;
}
rvd_uint16_t mipp_set1_uint16(const uint16_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_uint16(v0);
#endif
}
rvd_uint16_m1_t mipp_set1_uint16_m1(const uint16_t v0) {
	return mipp_set1_uint16(v0);
}
rvd_uint16_m2_t mipp_set1_uint16_m2(const uint16_t v0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_set1_uint16_m1(v0);
	res.m2 = mipp_set1_uint16_m1(v0);
	return res;
}
rvd_uint16_m4_t mipp_set1_uint16_m4(const uint16_t v0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_set1_uint16_m2(v0);
	res.m2 = mipp_set1_uint16_m2(v0);
	return res;
}
rvd_uint16_m8_t mipp_set1_uint16_m8(const uint16_t v0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_set1_uint16_m4(v0);
	res.m2 = mipp_set1_uint16_m4(v0);
	return res;
}
rvd_uint8_t mipp_set1_uint8(const uint8_t v0) {
#if defined(__AVX__)
	return mipp_avx_set1_uint8(v0);
#endif
}
rvd_uint8_m1_t mipp_set1_uint8_m1(const uint8_t v0) {
	return mipp_set1_uint8(v0);
}
rvd_uint8_m2_t mipp_set1_uint8_m2(const uint8_t v0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_set1_uint8_m1(v0);
	res.m2 = mipp_set1_uint8_m1(v0);
	return res;
}
rvd_uint8_m4_t mipp_set1_uint8_m4(const uint8_t v0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_set1_uint8_m2(v0);
	res.m2 = mipp_set1_uint8_m2(v0);
	return res;
}
rvd_uint8_m8_t mipp_set1_uint8_m8(const uint8_t v0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_set1_uint8_m4(v0);
	res.m2 = mipp_set1_uint8_m4(v0);
	return res;
}
rvd_float64_t mipp_set0_float64() {
#if defined(__AVX__)
	return mipp_avx_set0_float64();
#endif
}
rvd_float64_m1_t mipp_set0_float64_m1() {
	return mipp_set0_float64();
}
rvd_float64_m2_t mipp_set0_float64_m2() {
	rvd_float64_m2_t res;
	res.m1 = mipp_set0_float64_m1();
	res.m2 = mipp_set0_float64_m1();
	return res;
}
rvd_float64_m4_t mipp_set0_float64_m4() {
	rvd_float64_m4_t res;
	res.m1 = mipp_set0_float64_m2();
	res.m2 = mipp_set0_float64_m2();
	return res;
}
rvd_float64_m8_t mipp_set0_float64_m8() {
	rvd_float64_m8_t res;
	res.m1 = mipp_set0_float64_m4();
	res.m2 = mipp_set0_float64_m4();
	return res;
}
rvd_float32_t mipp_set0_float32() {
#if defined(__AVX__)
	return mipp_avx_set0_float32();
#endif
}
rvd_float32_m1_t mipp_set0_float32_m1() {
	return mipp_set0_float32();
}
rvd_float32_m2_t mipp_set0_float32_m2() {
	rvd_float32_m2_t res;
	res.m1 = mipp_set0_float32_m1();
	res.m2 = mipp_set0_float32_m1();
	return res;
}
rvd_float32_m4_t mipp_set0_float32_m4() {
	rvd_float32_m4_t res;
	res.m1 = mipp_set0_float32_m2();
	res.m2 = mipp_set0_float32_m2();
	return res;
}
rvd_float32_m8_t mipp_set0_float32_m8() {
	rvd_float32_m8_t res;
	res.m1 = mipp_set0_float32_m4();
	res.m2 = mipp_set0_float32_m4();
	return res;
}
rvd_int64_t mipp_set0_int64() {
#if defined(__AVX__)
	return mipp_avx_set0_int64();
#endif
}
rvd_int64_m1_t mipp_set0_int64_m1() {
	return mipp_set0_int64();
}
rvd_int64_m2_t mipp_set0_int64_m2() {
	rvd_int64_m2_t res;
	res.m1 = mipp_set0_int64_m1();
	res.m2 = mipp_set0_int64_m1();
	return res;
}
rvd_int64_m4_t mipp_set0_int64_m4() {
	rvd_int64_m4_t res;
	res.m1 = mipp_set0_int64_m2();
	res.m2 = mipp_set0_int64_m2();
	return res;
}
rvd_int64_m8_t mipp_set0_int64_m8() {
	rvd_int64_m8_t res;
	res.m1 = mipp_set0_int64_m4();
	res.m2 = mipp_set0_int64_m4();
	return res;
}
rvd_int32_t mipp_set0_int32() {
#if defined(__AVX__)
	return mipp_avx_set0_int32();
#endif
}
rvd_int32_m1_t mipp_set0_int32_m1() {
	return mipp_set0_int32();
}
rvd_int32_m2_t mipp_set0_int32_m2() {
	rvd_int32_m2_t res;
	res.m1 = mipp_set0_int32_m1();
	res.m2 = mipp_set0_int32_m1();
	return res;
}
rvd_int32_m4_t mipp_set0_int32_m4() {
	rvd_int32_m4_t res;
	res.m1 = mipp_set0_int32_m2();
	res.m2 = mipp_set0_int32_m2();
	return res;
}
rvd_int32_m8_t mipp_set0_int32_m8() {
	rvd_int32_m8_t res;
	res.m1 = mipp_set0_int32_m4();
	res.m2 = mipp_set0_int32_m4();
	return res;
}
rvd_int16_t mipp_set0_int16() {
#if defined(__AVX__)
	return mipp_avx_set0_int16();
#endif
}
rvd_int16_m1_t mipp_set0_int16_m1() {
	return mipp_set0_int16();
}
rvd_int16_m2_t mipp_set0_int16_m2() {
	rvd_int16_m2_t res;
	res.m1 = mipp_set0_int16_m1();
	res.m2 = mipp_set0_int16_m1();
	return res;
}
rvd_int16_m4_t mipp_set0_int16_m4() {
	rvd_int16_m4_t res;
	res.m1 = mipp_set0_int16_m2();
	res.m2 = mipp_set0_int16_m2();
	return res;
}
rvd_int16_m8_t mipp_set0_int16_m8() {
	rvd_int16_m8_t res;
	res.m1 = mipp_set0_int16_m4();
	res.m2 = mipp_set0_int16_m4();
	return res;
}
rvd_int8_t mipp_set0_int8() {
#if defined(__AVX__)
	return mipp_avx_set0_int8();
#endif
}
rvd_int8_m1_t mipp_set0_int8_m1() {
	return mipp_set0_int8();
}
rvd_int8_m2_t mipp_set0_int8_m2() {
	rvd_int8_m2_t res;
	res.m1 = mipp_set0_int8_m1();
	res.m2 = mipp_set0_int8_m1();
	return res;
}
rvd_int8_m4_t mipp_set0_int8_m4() {
	rvd_int8_m4_t res;
	res.m1 = mipp_set0_int8_m2();
	res.m2 = mipp_set0_int8_m2();
	return res;
}
rvd_int8_m8_t mipp_set0_int8_m8() {
	rvd_int8_m8_t res;
	res.m1 = mipp_set0_int8_m4();
	res.m2 = mipp_set0_int8_m4();
	return res;
}
rvd_uint64_t mipp_set0_uint64() {
#if defined(__AVX__)
	return mipp_avx_set0_uint64();
#endif
}
rvd_uint64_m1_t mipp_set0_uint64_m1() {
	return mipp_set0_uint64();
}
rvd_uint64_m2_t mipp_set0_uint64_m2() {
	rvd_uint64_m2_t res;
	res.m1 = mipp_set0_uint64_m1();
	res.m2 = mipp_set0_uint64_m1();
	return res;
}
rvd_uint64_m4_t mipp_set0_uint64_m4() {
	rvd_uint64_m4_t res;
	res.m1 = mipp_set0_uint64_m2();
	res.m2 = mipp_set0_uint64_m2();
	return res;
}
rvd_uint64_m8_t mipp_set0_uint64_m8() {
	rvd_uint64_m8_t res;
	res.m1 = mipp_set0_uint64_m4();
	res.m2 = mipp_set0_uint64_m4();
	return res;
}
rvd_uint32_t mipp_set0_uint32() {
#if defined(__AVX__)
	return mipp_avx_set0_uint32();
#endif
}
rvd_uint32_m1_t mipp_set0_uint32_m1() {
	return mipp_set0_uint32();
}
rvd_uint32_m2_t mipp_set0_uint32_m2() {
	rvd_uint32_m2_t res;
	res.m1 = mipp_set0_uint32_m1();
	res.m2 = mipp_set0_uint32_m1();
	return res;
}
rvd_uint32_m4_t mipp_set0_uint32_m4() {
	rvd_uint32_m4_t res;
	res.m1 = mipp_set0_uint32_m2();
	res.m2 = mipp_set0_uint32_m2();
	return res;
}
rvd_uint32_m8_t mipp_set0_uint32_m8() {
	rvd_uint32_m8_t res;
	res.m1 = mipp_set0_uint32_m4();
	res.m2 = mipp_set0_uint32_m4();
	return res;
}
rvd_uint16_t mipp_set0_uint16() {
#if defined(__AVX__)
	return mipp_avx_set0_uint16();
#endif
}
rvd_uint16_m1_t mipp_set0_uint16_m1() {
	return mipp_set0_uint16();
}
rvd_uint16_m2_t mipp_set0_uint16_m2() {
	rvd_uint16_m2_t res;
	res.m1 = mipp_set0_uint16_m1();
	res.m2 = mipp_set0_uint16_m1();
	return res;
}
rvd_uint16_m4_t mipp_set0_uint16_m4() {
	rvd_uint16_m4_t res;
	res.m1 = mipp_set0_uint16_m2();
	res.m2 = mipp_set0_uint16_m2();
	return res;
}
rvd_uint16_m8_t mipp_set0_uint16_m8() {
	rvd_uint16_m8_t res;
	res.m1 = mipp_set0_uint16_m4();
	res.m2 = mipp_set0_uint16_m4();
	return res;
}
rvd_uint8_t mipp_set0_uint8() {
#if defined(__AVX__)
	return mipp_avx_set0_uint8();
#endif
}
rvd_uint8_m1_t mipp_set0_uint8_m1() {
	return mipp_set0_uint8();
}
rvd_uint8_m2_t mipp_set0_uint8_m2() {
	rvd_uint8_m2_t res;
	res.m1 = mipp_set0_uint8_m1();
	res.m2 = mipp_set0_uint8_m1();
	return res;
}
rvd_uint8_m4_t mipp_set0_uint8_m4() {
	rvd_uint8_m4_t res;
	res.m1 = mipp_set0_uint8_m2();
	res.m2 = mipp_set0_uint8_m2();
	return res;
}
rvd_uint8_m8_t mipp_set0_uint8_m8() {
	rvd_uint8_m8_t res;
	res.m1 = mipp_set0_uint8_m4();
	res.m2 = mipp_set0_uint8_m4();
	return res;
}
rvm_float64_t mipp_set0_k_float64() {
#if defined(__AVX__)
	return mipp_avx_set0_k_float64();
#endif
}
rvm_float64_m1_t mipp_set0_k_float64_m1() {
	return mipp_set0_k_float64();
}
rvm_float64_m2_t mipp_set0_k_float64_m2() {
	rvm_float64_m2_t res;
	res.m1 = mipp_set0_k_float64_m1();
	res.m2 = mipp_set0_k_float64_m1();
	return res;
}
rvm_float64_m4_t mipp_set0_k_float64_m4() {
	rvm_float64_m4_t res;
	res.m1 = mipp_set0_k_float64_m2();
	res.m2 = mipp_set0_k_float64_m2();
	return res;
}
rvm_float64_m8_t mipp_set0_k_float64_m8() {
	rvm_float64_m8_t res;
	res.m1 = mipp_set0_k_float64_m4();
	res.m2 = mipp_set0_k_float64_m4();
	return res;
}
rvm_float32_t mipp_set0_k_float32() {
#if defined(__AVX__)
	return mipp_avx_set0_k_float32();
#endif
}
rvm_float32_m1_t mipp_set0_k_float32_m1() {
	return mipp_set0_k_float32();
}
rvm_float32_m2_t mipp_set0_k_float32_m2() {
	rvm_float32_m2_t res;
	res.m1 = mipp_set0_k_float32_m1();
	res.m2 = mipp_set0_k_float32_m1();
	return res;
}
rvm_float32_m4_t mipp_set0_k_float32_m4() {
	rvm_float32_m4_t res;
	res.m1 = mipp_set0_k_float32_m2();
	res.m2 = mipp_set0_k_float32_m2();
	return res;
}
rvm_float32_m8_t mipp_set0_k_float32_m8() {
	rvm_float32_m8_t res;
	res.m1 = mipp_set0_k_float32_m4();
	res.m2 = mipp_set0_k_float32_m4();
	return res;
}
rvm_int64_t mipp_set0_k_int64() {
#if defined(__AVX__)
	return mipp_avx_set0_k_int64();
#endif
}
rvm_int64_m1_t mipp_set0_k_int64_m1() {
	return mipp_set0_k_int64();
}
rvm_int64_m2_t mipp_set0_k_int64_m2() {
	rvm_int64_m2_t res;
	res.m1 = mipp_set0_k_int64_m1();
	res.m2 = mipp_set0_k_int64_m1();
	return res;
}
rvm_int64_m4_t mipp_set0_k_int64_m4() {
	rvm_int64_m4_t res;
	res.m1 = mipp_set0_k_int64_m2();
	res.m2 = mipp_set0_k_int64_m2();
	return res;
}
rvm_int64_m8_t mipp_set0_k_int64_m8() {
	rvm_int64_m8_t res;
	res.m1 = mipp_set0_k_int64_m4();
	res.m2 = mipp_set0_k_int64_m4();
	return res;
}
rvm_int32_t mipp_set0_k_int32() {
#if defined(__AVX__)
	return mipp_avx_set0_k_int32();
#endif
}
rvm_int32_m1_t mipp_set0_k_int32_m1() {
	return mipp_set0_k_int32();
}
rvm_int32_m2_t mipp_set0_k_int32_m2() {
	rvm_int32_m2_t res;
	res.m1 = mipp_set0_k_int32_m1();
	res.m2 = mipp_set0_k_int32_m1();
	return res;
}
rvm_int32_m4_t mipp_set0_k_int32_m4() {
	rvm_int32_m4_t res;
	res.m1 = mipp_set0_k_int32_m2();
	res.m2 = mipp_set0_k_int32_m2();
	return res;
}
rvm_int32_m8_t mipp_set0_k_int32_m8() {
	rvm_int32_m8_t res;
	res.m1 = mipp_set0_k_int32_m4();
	res.m2 = mipp_set0_k_int32_m4();
	return res;
}
rvm_int16_t mipp_set0_k_int16() {
#if defined(__AVX__)
	return mipp_avx_set0_k_int16();
#endif
}
rvm_int16_m1_t mipp_set0_k_int16_m1() {
	return mipp_set0_k_int16();
}
rvm_int16_m2_t mipp_set0_k_int16_m2() {
	rvm_int16_m2_t res;
	res.m1 = mipp_set0_k_int16_m1();
	res.m2 = mipp_set0_k_int16_m1();
	return res;
}
rvm_int16_m4_t mipp_set0_k_int16_m4() {
	rvm_int16_m4_t res;
	res.m1 = mipp_set0_k_int16_m2();
	res.m2 = mipp_set0_k_int16_m2();
	return res;
}
rvm_int16_m8_t mipp_set0_k_int16_m8() {
	rvm_int16_m8_t res;
	res.m1 = mipp_set0_k_int16_m4();
	res.m2 = mipp_set0_k_int16_m4();
	return res;
}
rvm_int8_t mipp_set0_k_int8() {
#if defined(__AVX__)
	return mipp_avx_set0_k_int8();
#endif
}
rvm_int8_m1_t mipp_set0_k_int8_m1() {
	return mipp_set0_k_int8();
}
rvm_int8_m2_t mipp_set0_k_int8_m2() {
	rvm_int8_m2_t res;
	res.m1 = mipp_set0_k_int8_m1();
	res.m2 = mipp_set0_k_int8_m1();
	return res;
}
rvm_int8_m4_t mipp_set0_k_int8_m4() {
	rvm_int8_m4_t res;
	res.m1 = mipp_set0_k_int8_m2();
	res.m2 = mipp_set0_k_int8_m2();
	return res;
}
rvm_int8_m8_t mipp_set0_k_int8_m8() {
	rvm_int8_m8_t res;
	res.m1 = mipp_set0_k_int8_m4();
	res.m2 = mipp_set0_k_int8_m4();
	return res;
}
rvm_uint64_t mipp_set0_k_uint64() {
#if defined(__AVX__)
	return mipp_avx_set0_k_uint64();
#endif
}
rvm_uint64_m1_t mipp_set0_k_uint64_m1() {
	return mipp_set0_k_uint64();
}
rvm_uint64_m2_t mipp_set0_k_uint64_m2() {
	rvm_uint64_m2_t res;
	res.m1 = mipp_set0_k_uint64_m1();
	res.m2 = mipp_set0_k_uint64_m1();
	return res;
}
rvm_uint64_m4_t mipp_set0_k_uint64_m4() {
	rvm_uint64_m4_t res;
	res.m1 = mipp_set0_k_uint64_m2();
	res.m2 = mipp_set0_k_uint64_m2();
	return res;
}
rvm_uint64_m8_t mipp_set0_k_uint64_m8() {
	rvm_uint64_m8_t res;
	res.m1 = mipp_set0_k_uint64_m4();
	res.m2 = mipp_set0_k_uint64_m4();
	return res;
}
rvm_uint32_t mipp_set0_k_uint32() {
#if defined(__AVX__)
	return mipp_avx_set0_k_uint32();
#endif
}
rvm_uint32_m1_t mipp_set0_k_uint32_m1() {
	return mipp_set0_k_uint32();
}
rvm_uint32_m2_t mipp_set0_k_uint32_m2() {
	rvm_uint32_m2_t res;
	res.m1 = mipp_set0_k_uint32_m1();
	res.m2 = mipp_set0_k_uint32_m1();
	return res;
}
rvm_uint32_m4_t mipp_set0_k_uint32_m4() {
	rvm_uint32_m4_t res;
	res.m1 = mipp_set0_k_uint32_m2();
	res.m2 = mipp_set0_k_uint32_m2();
	return res;
}
rvm_uint32_m8_t mipp_set0_k_uint32_m8() {
	rvm_uint32_m8_t res;
	res.m1 = mipp_set0_k_uint32_m4();
	res.m2 = mipp_set0_k_uint32_m4();
	return res;
}
rvm_uint16_t mipp_set0_k_uint16() {
#if defined(__AVX__)
	return mipp_avx_set0_k_uint16();
#endif
}
rvm_uint16_m1_t mipp_set0_k_uint16_m1() {
	return mipp_set0_k_uint16();
}
rvm_uint16_m2_t mipp_set0_k_uint16_m2() {
	rvm_uint16_m2_t res;
	res.m1 = mipp_set0_k_uint16_m1();
	res.m2 = mipp_set0_k_uint16_m1();
	return res;
}
rvm_uint16_m4_t mipp_set0_k_uint16_m4() {
	rvm_uint16_m4_t res;
	res.m1 = mipp_set0_k_uint16_m2();
	res.m2 = mipp_set0_k_uint16_m2();
	return res;
}
rvm_uint16_m8_t mipp_set0_k_uint16_m8() {
	rvm_uint16_m8_t res;
	res.m1 = mipp_set0_k_uint16_m4();
	res.m2 = mipp_set0_k_uint16_m4();
	return res;
}
rvm_uint8_t mipp_set0_k_uint8() {
#if defined(__AVX__)
	return mipp_avx_set0_k_uint8();
#endif
}
rvm_uint8_m1_t mipp_set0_k_uint8_m1() {
	return mipp_set0_k_uint8();
}
rvm_uint8_m2_t mipp_set0_k_uint8_m2() {
	rvm_uint8_m2_t res;
	res.m1 = mipp_set0_k_uint8_m1();
	res.m2 = mipp_set0_k_uint8_m1();
	return res;
}
rvm_uint8_m4_t mipp_set0_k_uint8_m4() {
	rvm_uint8_m4_t res;
	res.m1 = mipp_set0_k_uint8_m2();
	res.m2 = mipp_set0_k_uint8_m2();
	return res;
}
rvm_uint8_m8_t mipp_set0_k_uint8_m8() {
	rvm_uint8_m8_t res;
	res.m1 = mipp_set0_k_uint8_m4();
	res.m2 = mipp_set0_k_uint8_m4();
	return res;
}
float64_t mipp_get_float64(const rvd_float64_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_float64(r0, v0);
#endif
}
float64_t mipp_get_float64_m1(const rvd_float64_m1_t r0, const uint32_t v0) {
	return mipp_get_float64(r0, v0);
}
float64_t mipp_get_float64_m2(const rvd_float64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m2");
	exit(-1);
}
float64_t mipp_get_float64_m4(const rvd_float64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m4");
	exit(-1);
}
float64_t mipp_get_float64_m8(const rvd_float64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m8");
	exit(-1);
}
float32_t mipp_get_float32(const rvd_float32_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_float32(r0, v0);
#endif
}
float32_t mipp_get_float32_m1(const rvd_float32_m1_t r0, const uint32_t v0) {
	return mipp_get_float32(r0, v0);
}
float32_t mipp_get_float32_m2(const rvd_float32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m2");
	exit(-1);
}
float32_t mipp_get_float32_m4(const rvd_float32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m4");
	exit(-1);
}
float32_t mipp_get_float32_m8(const rvd_float32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m8");
	exit(-1);
}
int64_t mipp_get_int64(const rvd_int64_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_int64(r0, v0);
#endif
}
int64_t mipp_get_int64_m1(const rvd_int64_m1_t r0, const uint32_t v0) {
	return mipp_get_int64(r0, v0);
}
int64_t mipp_get_int64_m2(const rvd_int64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m2");
	exit(-1);
}
int64_t mipp_get_int64_m4(const rvd_int64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m4");
	exit(-1);
}
int64_t mipp_get_int64_m8(const rvd_int64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m8");
	exit(-1);
}
int32_t mipp_get_int32(const rvd_int32_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_int32(r0, v0);
#endif
}
int32_t mipp_get_int32_m1(const rvd_int32_m1_t r0, const uint32_t v0) {
	return mipp_get_int32(r0, v0);
}
int32_t mipp_get_int32_m2(const rvd_int32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m2");
	exit(-1);
}
int32_t mipp_get_int32_m4(const rvd_int32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m4");
	exit(-1);
}
int32_t mipp_get_int32_m8(const rvd_int32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m8");
	exit(-1);
}
int16_t mipp_get_int16(const rvd_int16_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_int16(r0, v0);
#endif
}
int16_t mipp_get_int16_m1(const rvd_int16_m1_t r0, const uint32_t v0) {
	return mipp_get_int16(r0, v0);
}
int16_t mipp_get_int16_m2(const rvd_int16_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m2");
	exit(-1);
}
int16_t mipp_get_int16_m4(const rvd_int16_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m4");
	exit(-1);
}
int16_t mipp_get_int16_m8(const rvd_int16_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m8");
	exit(-1);
}
int8_t mipp_get_int8(const rvd_int8_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_int8(r0, v0);
#endif
}
int8_t mipp_get_int8_m1(const rvd_int8_m1_t r0, const uint32_t v0) {
	return mipp_get_int8(r0, v0);
}
int8_t mipp_get_int8_m2(const rvd_int8_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m2");
	exit(-1);
}
int8_t mipp_get_int8_m4(const rvd_int8_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m4");
	exit(-1);
}
int8_t mipp_get_int8_m8(const rvd_int8_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m8");
	exit(-1);
}
uint64_t mipp_get_uint64(const rvd_uint64_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_uint64(r0, v0);
#endif
}
uint64_t mipp_get_uint64_m1(const rvd_uint64_m1_t r0, const uint32_t v0) {
	return mipp_get_uint64(r0, v0);
}
uint64_t mipp_get_uint64_m2(const rvd_uint64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m2");
	exit(-1);
}
uint64_t mipp_get_uint64_m4(const rvd_uint64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m4");
	exit(-1);
}
uint64_t mipp_get_uint64_m8(const rvd_uint64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m8");
	exit(-1);
}
uint32_t mipp_get_uint32(const rvd_uint32_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_uint32(r0, v0);
#endif
}
uint32_t mipp_get_uint32_m1(const rvd_uint32_m1_t r0, const uint32_t v0) {
	return mipp_get_uint32(r0, v0);
}
uint32_t mipp_get_uint32_m2(const rvd_uint32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m2");
	exit(-1);
}
uint32_t mipp_get_uint32_m4(const rvd_uint32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m4");
	exit(-1);
}
uint32_t mipp_get_uint32_m8(const rvd_uint32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m8");
	exit(-1);
}
uint16_t mipp_get_uint16(const rvd_uint16_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_uint16(r0, v0);
#endif
}
uint16_t mipp_get_uint16_m1(const rvd_uint16_m1_t r0, const uint32_t v0) {
	return mipp_get_uint16(r0, v0);
}
uint16_t mipp_get_uint16_m2(const rvd_uint16_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m2");
	exit(-1);
}
uint16_t mipp_get_uint16_m4(const rvd_uint16_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m4");
	exit(-1);
}
uint16_t mipp_get_uint16_m8(const rvd_uint16_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m8");
	exit(-1);
}
uint8_t mipp_get_uint8(const rvd_uint8_t r0, const uint32_t v0) {
#if defined(__AVX__)
	return mipp_avx_get_uint8(r0, v0);
#endif
}
uint8_t mipp_get_uint8_m1(const rvd_uint8_m1_t r0, const uint32_t v0) {
	return mipp_get_uint8(r0, v0);
}
uint8_t mipp_get_uint8_m2(const rvd_uint8_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m2");
	exit(-1);
}
uint8_t mipp_get_uint8_m4(const rvd_uint8_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m4");
	exit(-1);
}
uint8_t mipp_get_uint8_m8(const rvd_uint8_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m8");
	exit(-1);
}
float64_t mipp_getfirst_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_float64(r0);
#endif
}
float64_t mipp_getfirst_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_getfirst_float64(r0);
}
float64_t mipp_getfirst_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m2");
	exit(-1);
}
float64_t mipp_getfirst_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m4");
	exit(-1);
}
float64_t mipp_getfirst_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m8");
	exit(-1);
}
float32_t mipp_getfirst_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_float32(r0);
#endif
}
float32_t mipp_getfirst_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_getfirst_float32(r0);
}
float32_t mipp_getfirst_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m2");
	exit(-1);
}
float32_t mipp_getfirst_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m4");
	exit(-1);
}
float32_t mipp_getfirst_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m8");
	exit(-1);
}
int64_t mipp_getfirst_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_int64(r0);
#endif
}
int64_t mipp_getfirst_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_getfirst_int64(r0);
}
int64_t mipp_getfirst_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m2");
	exit(-1);
}
int64_t mipp_getfirst_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m4");
	exit(-1);
}
int64_t mipp_getfirst_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m8");
	exit(-1);
}
int32_t mipp_getfirst_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_int32(r0);
#endif
}
int32_t mipp_getfirst_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_getfirst_int32(r0);
}
int32_t mipp_getfirst_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m2");
	exit(-1);
}
int32_t mipp_getfirst_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m4");
	exit(-1);
}
int32_t mipp_getfirst_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m8");
	exit(-1);
}
int16_t mipp_getfirst_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_int16(r0);
#endif
}
int16_t mipp_getfirst_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_getfirst_int16(r0);
}
int16_t mipp_getfirst_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m2");
	exit(-1);
}
int16_t mipp_getfirst_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m4");
	exit(-1);
}
int16_t mipp_getfirst_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m8");
	exit(-1);
}
int8_t mipp_getfirst_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_int8(r0);
#endif
}
int8_t mipp_getfirst_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_getfirst_int8(r0);
}
int8_t mipp_getfirst_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m2");
	exit(-1);
}
int8_t mipp_getfirst_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m4");
	exit(-1);
}
int8_t mipp_getfirst_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m8");
	exit(-1);
}
uint64_t mipp_getfirst_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_uint64(r0);
#endif
}
uint64_t mipp_getfirst_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_getfirst_uint64(r0);
}
uint64_t mipp_getfirst_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m2");
	exit(-1);
}
uint64_t mipp_getfirst_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m4");
	exit(-1);
}
uint64_t mipp_getfirst_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m8");
	exit(-1);
}
uint32_t mipp_getfirst_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_uint32(r0);
#endif
}
uint32_t mipp_getfirst_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_getfirst_uint32(r0);
}
uint32_t mipp_getfirst_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m2");
	exit(-1);
}
uint32_t mipp_getfirst_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m4");
	exit(-1);
}
uint32_t mipp_getfirst_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m8");
	exit(-1);
}
uint16_t mipp_getfirst_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_uint16(r0);
#endif
}
uint16_t mipp_getfirst_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_getfirst_uint16(r0);
}
uint16_t mipp_getfirst_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m2");
	exit(-1);
}
uint16_t mipp_getfirst_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m4");
	exit(-1);
}
uint16_t mipp_getfirst_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m8");
	exit(-1);
}
uint8_t mipp_getfirst_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_getfirst_uint8(r0);
#endif
}
uint8_t mipp_getfirst_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_getfirst_uint8(r0);
}
uint8_t mipp_getfirst_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m2");
	exit(-1);
}
uint8_t mipp_getfirst_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m4");
	exit(-1);
}
uint8_t mipp_getfirst_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m8");
	exit(-1);
}
rvd_float64_t mipp_sqrt_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_sqrt_float64(r0);
#endif
}
rvd_float64_m1_t mipp_sqrt_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_sqrt_float64(r0);
}
rvd_float64_m2_t mipp_sqrt_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_sqrt_float64_m1(r0.m1);
	res.m2 = mipp_sqrt_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_sqrt_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_sqrt_float64_m2(r0.m1);
	res.m2 = mipp_sqrt_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_sqrt_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_sqrt_float64_m4(r0.m1);
	res.m2 = mipp_sqrt_float64_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_sqrt_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_sqrt_float32(r0);
#endif
}
rvd_float32_m1_t mipp_sqrt_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_sqrt_float32(r0);
}
rvd_float32_m2_t mipp_sqrt_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_sqrt_float32_m1(r0.m1);
	res.m2 = mipp_sqrt_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_sqrt_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_sqrt_float32_m2(r0.m1);
	res.m2 = mipp_sqrt_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_sqrt_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_sqrt_float32_m4(r0.m1);
	res.m2 = mipp_sqrt_float32_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_rsqrt_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_rsqrt_float64(r0);
#endif
}
rvd_float64_m1_t mipp_rsqrt_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_rsqrt_float64(r0);
}
rvd_float64_m2_t mipp_rsqrt_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_rsqrt_float64_m1(r0.m1);
	res.m2 = mipp_rsqrt_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_rsqrt_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_rsqrt_float64_m2(r0.m1);
	res.m2 = mipp_rsqrt_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_rsqrt_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_rsqrt_float64_m4(r0.m1);
	res.m2 = mipp_rsqrt_float64_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_rsqrt_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_rsqrt_float32(r0);
#endif
}
rvd_float32_m1_t mipp_rsqrt_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_rsqrt_float32(r0);
}
rvd_float32_m2_t mipp_rsqrt_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_rsqrt_float32_m1(r0.m1);
	res.m2 = mipp_rsqrt_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_rsqrt_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_rsqrt_float32_m2(r0.m1);
	res.m2 = mipp_rsqrt_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_rsqrt_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_rsqrt_float32_m4(r0.m1);
	res.m2 = mipp_rsqrt_float32_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_add_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_add_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_add_float64(r0, r1);
}
rvd_float64_m2_t mipp_add_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_add_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_add_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_add_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_add_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_add_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_add_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_add_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_add_float32(r0, r1);
}
rvd_float32_m2_t mipp_add_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_add_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_add_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_add_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_add_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_add_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_add_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_add_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_add_int64(r0, r1);
}
rvd_int64_m2_t mipp_add_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_add_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_add_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_add_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_add_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_add_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_add_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_add_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_add_int32(r0, r1);
}
rvd_int32_m2_t mipp_add_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_add_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_add_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_add_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_add_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_add_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_add_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_add_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_add_int16(r0, r1);
}
rvd_int16_m2_t mipp_add_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_add_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_add_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_add_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_add_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_add_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_add_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_add_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_add_int8(r0, r1);
}
rvd_int8_m2_t mipp_add_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_add_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_add_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_add_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_add_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_add_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_add_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_add_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_add_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_add_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_add_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_add_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_add_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_add_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_add_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_add_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_add_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_add_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_add_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_add_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_add_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_add_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_add_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_add_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_add_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_add_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_add_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_add_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_add_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_add_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_add_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_add_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_add_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_add_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_add_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_add_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_add_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_add_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_add_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_add_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_add_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_add_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_add_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_add_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_add_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_add_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_add_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_add_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_add_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_add_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_add_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_add_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_add_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_add_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_add_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_add_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_add_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_add_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_add_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_add_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_add_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_add_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_add_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_add_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_t mipp_add_m_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0, const rvd_int64_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_int64(r0, r1, m0, r2);
#endif
}
rvd_int64_m1_t mipp_add_m_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0, const rvd_int64_m1_t r2) {
	return mipp_add_m_int64(r0, r1, m0, r2);
}
rvd_int64_m2_t mipp_add_m_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0, const rvd_int64_m2_t r2) {
	rvd_int64_m2_t res;
	res.m1 = mipp_add_m_int64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m4_t mipp_add_m_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0, const rvd_int64_m4_t r2) {
	rvd_int64_m4_t res;
	res.m1 = mipp_add_m_int64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m8_t mipp_add_m_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0, const rvd_int64_m8_t r2) {
	rvd_int64_m8_t res;
	res.m1 = mipp_add_m_int64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_t mipp_add_m_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0, const rvd_int32_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_int32(r0, r1, m0, r2);
#endif
}
rvd_int32_m1_t mipp_add_m_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0, const rvd_int32_m1_t r2) {
	return mipp_add_m_int32(r0, r1, m0, r2);
}
rvd_int32_m2_t mipp_add_m_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.m1 = mipp_add_m_int32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m4_t mipp_add_m_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.m1 = mipp_add_m_int32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m8_t mipp_add_m_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.m1 = mipp_add_m_int32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_t mipp_add_m_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0, const rvd_int16_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_int16(r0, r1, m0, r2);
#endif
}
rvd_int16_m1_t mipp_add_m_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0, const rvd_int16_m1_t r2) {
	return mipp_add_m_int16(r0, r1, m0, r2);
}
rvd_int16_m2_t mipp_add_m_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0, const rvd_int16_m2_t r2) {
	rvd_int16_m2_t res;
	res.m1 = mipp_add_m_int16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m4_t mipp_add_m_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0, const rvd_int16_m4_t r2) {
	rvd_int16_m4_t res;
	res.m1 = mipp_add_m_int16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m8_t mipp_add_m_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0, const rvd_int16_m8_t r2) {
	rvd_int16_m8_t res;
	res.m1 = mipp_add_m_int16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_t mipp_add_m_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0, const rvd_int8_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_int8(r0, r1, m0, r2);
#endif
}
rvd_int8_m1_t mipp_add_m_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0, const rvd_int8_m1_t r2) {
	return mipp_add_m_int8(r0, r1, m0, r2);
}
rvd_int8_m2_t mipp_add_m_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0, const rvd_int8_m2_t r2) {
	rvd_int8_m2_t res;
	res.m1 = mipp_add_m_int8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m4_t mipp_add_m_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0, const rvd_int8_m4_t r2) {
	rvd_int8_m4_t res;
	res.m1 = mipp_add_m_int8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m8_t mipp_add_m_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0, const rvd_int8_m8_t r2) {
	rvd_int8_m8_t res;
	res.m1 = mipp_add_m_int8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_int8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_t mipp_add_m_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0, const rvd_uint64_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_uint64(r0, r1, m0, r2);
#endif
}
rvd_uint64_m1_t mipp_add_m_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r2) {
	return mipp_add_m_uint64(r0, r1, m0, r2);
}
rvd_uint64_m2_t mipp_add_m_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r2) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_add_m_uint64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m4_t mipp_add_m_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r2) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_add_m_uint64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m8_t mipp_add_m_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r2) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_add_m_uint64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_t mipp_add_m_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0, const rvd_uint32_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_uint32(r0, r1, m0, r2);
#endif
}
rvd_uint32_m1_t mipp_add_m_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r2) {
	return mipp_add_m_uint32(r0, r1, m0, r2);
}
rvd_uint32_m2_t mipp_add_m_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r2) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_add_m_uint32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m4_t mipp_add_m_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r2) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_add_m_uint32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m8_t mipp_add_m_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r2) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_add_m_uint32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_t mipp_add_m_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0, const rvd_uint16_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_uint16(r0, r1, m0, r2);
#endif
}
rvd_uint16_m1_t mipp_add_m_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r2) {
	return mipp_add_m_uint16(r0, r1, m0, r2);
}
rvd_uint16_m2_t mipp_add_m_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r2) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_add_m_uint16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m4_t mipp_add_m_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r2) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_add_m_uint16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m8_t mipp_add_m_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r2) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_add_m_uint16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_t mipp_add_m_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0, const rvd_uint8_t r2) {
#if defined(__AVX__)
	return mipp_avx_add_m_uint8(r0, r1, m0, r2);
#endif
}
rvd_uint8_m1_t mipp_add_m_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r2) {
	return mipp_add_m_uint8(r0, r1, m0, r2);
}
rvd_uint8_m2_t mipp_add_m_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r2) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_add_m_uint8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m4_t mipp_add_m_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r2) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_add_m_uint8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m8_t mipp_add_m_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r2) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_add_m_uint8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_add_m_uint8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_add_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_add_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_add_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_add_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_add_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_add_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_add_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_add_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_add_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_add_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_add_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_add_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_add_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_add_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_add_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_add_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_add_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_add_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_add_mz_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_add_mz_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_add_mz_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_add_mz_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_add_mz_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_add_mz_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_add_mz_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_add_mz_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_add_mz_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_add_mz_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_add_mz_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_add_mz_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_add_mz_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_add_mz_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_add_mz_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_add_mz_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_add_mz_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_add_mz_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_add_mz_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_add_mz_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_add_mz_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_add_mz_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_add_mz_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_add_mz_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_add_mz_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_add_mz_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_add_mz_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_add_mz_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_add_mz_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_add_mz_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_add_mz_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_add_mz_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_add_mz_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_add_mz_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_add_mz_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_add_mz_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_add_mz_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_add_mz_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_add_mz_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_add_mz_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_add_mz_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_add_mz_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_add_mz_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_add_mz_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_add_mz_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_add_mz_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_add_mz_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_add_mz_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_add_mz_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_add_mz_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_add_mz_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_add_mz_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_add_mz_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_add_mz_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_add_mz_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_add_mz_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_add_mz_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_add_mz_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_add_mz_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_add_mz_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_add_mz_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_add_mz_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_add_mz_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_add_mz_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_add_mz_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_add_mz_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_add_mz_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_add_mz_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_add_mz_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_add_mz_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_add_mz_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_add_mz_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_add_mz_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_add_mz_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_sub_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_sub_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_sub_float64(r0, r1);
}
rvd_float64_m2_t mipp_sub_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_sub_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_sub_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_sub_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_sub_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_sub_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_sub_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_sub_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_sub_float32(r0, r1);
}
rvd_float32_m2_t mipp_sub_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_sub_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_sub_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_sub_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_sub_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_sub_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_sub_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_sub_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_sub_int64(r0, r1);
}
rvd_int64_m2_t mipp_sub_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_sub_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_sub_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_sub_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_sub_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_sub_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_sub_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_sub_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_sub_int32(r0, r1);
}
rvd_int32_m2_t mipp_sub_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_sub_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_sub_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_sub_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_sub_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_sub_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_sub_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_sub_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_sub_int16(r0, r1);
}
rvd_int16_m2_t mipp_sub_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_sub_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_sub_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_sub_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_sub_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_sub_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_sub_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_sub_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_sub_int8(r0, r1);
}
rvd_int8_m2_t mipp_sub_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_sub_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_sub_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_sub_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_sub_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_sub_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_sub_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_sub_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_sub_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_sub_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_sub_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_sub_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_sub_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_sub_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_sub_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_sub_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_sub_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_sub_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_sub_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_sub_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_sub_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_sub_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_sub_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_sub_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_sub_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_sub_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_sub_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_sub_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_sub_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_sub_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_sub_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_sub_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_sub_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_sub_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_sub_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_sub_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_sub_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_sub_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_sub_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_sub_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_sub_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_sub_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_sub_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_sub_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_sub_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_sub_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_sub_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_sub_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_sub_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_sub_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_sub_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_sub_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_sub_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_sub_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_sub_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_sub_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_sub_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_sub_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_sub_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_sub_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_sub_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_sub_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_t mipp_sub_m_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0, const rvd_int64_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_int64(r0, r1, m0, r2);
#endif
}
rvd_int64_m1_t mipp_sub_m_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0, const rvd_int64_m1_t r2) {
	return mipp_sub_m_int64(r0, r1, m0, r2);
}
rvd_int64_m2_t mipp_sub_m_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0, const rvd_int64_m2_t r2) {
	rvd_int64_m2_t res;
	res.m1 = mipp_sub_m_int64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m4_t mipp_sub_m_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0, const rvd_int64_m4_t r2) {
	rvd_int64_m4_t res;
	res.m1 = mipp_sub_m_int64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m8_t mipp_sub_m_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0, const rvd_int64_m8_t r2) {
	rvd_int64_m8_t res;
	res.m1 = mipp_sub_m_int64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_t mipp_sub_m_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0, const rvd_int32_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_int32(r0, r1, m0, r2);
#endif
}
rvd_int32_m1_t mipp_sub_m_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0, const rvd_int32_m1_t r2) {
	return mipp_sub_m_int32(r0, r1, m0, r2);
}
rvd_int32_m2_t mipp_sub_m_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.m1 = mipp_sub_m_int32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m4_t mipp_sub_m_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.m1 = mipp_sub_m_int32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m8_t mipp_sub_m_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.m1 = mipp_sub_m_int32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_t mipp_sub_m_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0, const rvd_int16_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_int16(r0, r1, m0, r2);
#endif
}
rvd_int16_m1_t mipp_sub_m_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0, const rvd_int16_m1_t r2) {
	return mipp_sub_m_int16(r0, r1, m0, r2);
}
rvd_int16_m2_t mipp_sub_m_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0, const rvd_int16_m2_t r2) {
	rvd_int16_m2_t res;
	res.m1 = mipp_sub_m_int16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m4_t mipp_sub_m_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0, const rvd_int16_m4_t r2) {
	rvd_int16_m4_t res;
	res.m1 = mipp_sub_m_int16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m8_t mipp_sub_m_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0, const rvd_int16_m8_t r2) {
	rvd_int16_m8_t res;
	res.m1 = mipp_sub_m_int16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_t mipp_sub_m_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0, const rvd_int8_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_int8(r0, r1, m0, r2);
#endif
}
rvd_int8_m1_t mipp_sub_m_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0, const rvd_int8_m1_t r2) {
	return mipp_sub_m_int8(r0, r1, m0, r2);
}
rvd_int8_m2_t mipp_sub_m_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0, const rvd_int8_m2_t r2) {
	rvd_int8_m2_t res;
	res.m1 = mipp_sub_m_int8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m4_t mipp_sub_m_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0, const rvd_int8_m4_t r2) {
	rvd_int8_m4_t res;
	res.m1 = mipp_sub_m_int8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m8_t mipp_sub_m_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0, const rvd_int8_m8_t r2) {
	rvd_int8_m8_t res;
	res.m1 = mipp_sub_m_int8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_int8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_t mipp_sub_m_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0, const rvd_uint64_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_uint64(r0, r1, m0, r2);
#endif
}
rvd_uint64_m1_t mipp_sub_m_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r2) {
	return mipp_sub_m_uint64(r0, r1, m0, r2);
}
rvd_uint64_m2_t mipp_sub_m_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r2) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_sub_m_uint64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m4_t mipp_sub_m_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r2) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_sub_m_uint64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m8_t mipp_sub_m_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r2) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_sub_m_uint64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_t mipp_sub_m_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0, const rvd_uint32_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_uint32(r0, r1, m0, r2);
#endif
}
rvd_uint32_m1_t mipp_sub_m_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r2) {
	return mipp_sub_m_uint32(r0, r1, m0, r2);
}
rvd_uint32_m2_t mipp_sub_m_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r2) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_sub_m_uint32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m4_t mipp_sub_m_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r2) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_sub_m_uint32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m8_t mipp_sub_m_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r2) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_sub_m_uint32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_t mipp_sub_m_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0, const rvd_uint16_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_uint16(r0, r1, m0, r2);
#endif
}
rvd_uint16_m1_t mipp_sub_m_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r2) {
	return mipp_sub_m_uint16(r0, r1, m0, r2);
}
rvd_uint16_m2_t mipp_sub_m_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r2) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_sub_m_uint16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m4_t mipp_sub_m_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r2) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_sub_m_uint16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m8_t mipp_sub_m_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r2) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_sub_m_uint16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_t mipp_sub_m_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0, const rvd_uint8_t r2) {
#if defined(__AVX__)
	return mipp_avx_sub_m_uint8(r0, r1, m0, r2);
#endif
}
rvd_uint8_m1_t mipp_sub_m_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r2) {
	return mipp_sub_m_uint8(r0, r1, m0, r2);
}
rvd_uint8_m2_t mipp_sub_m_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r2) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_sub_m_uint8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m4_t mipp_sub_m_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r2) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_sub_m_uint8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m8_t mipp_sub_m_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r2) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_sub_m_uint8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_sub_m_uint8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_sub_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_sub_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_sub_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_sub_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_sub_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_sub_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_sub_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_sub_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_sub_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_sub_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_sub_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_sub_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_sub_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_sub_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_sub_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_sub_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_sub_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_sub_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_sub_mz_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_sub_mz_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_sub_mz_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_sub_mz_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_sub_mz_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_sub_mz_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_sub_mz_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_sub_mz_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_sub_mz_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_sub_mz_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_sub_mz_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_sub_mz_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_sub_mz_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_sub_mz_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_sub_mz_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_sub_mz_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_sub_mz_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_sub_mz_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_sub_mz_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_sub_mz_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_sub_mz_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_sub_mz_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_sub_mz_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_sub_mz_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_sub_mz_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_sub_mz_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_sub_mz_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_sub_mz_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_sub_mz_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_sub_mz_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_sub_mz_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_sub_mz_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_sub_mz_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_sub_mz_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_sub_mz_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_sub_mz_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_sub_mz_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_sub_mz_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_sub_mz_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_sub_mz_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_sub_mz_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_sub_mz_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_sub_mz_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_sub_mz_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_sub_mz_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_sub_mz_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_sub_mz_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_sub_mz_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_sub_mz_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_sub_mz_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_sub_mz_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_sub_mz_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_sub_mz_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_sub_mz_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_sub_mz_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_sub_mz_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_sub_mz_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_sub_mz_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_sub_mz_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_sub_mz_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_sub_mz_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_sub_mz_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_sub_mz_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_sub_mz_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_sub_mz_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_sub_mz_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_sub_mz_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_sub_mz_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_sub_mz_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_sub_mz_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_sub_mz_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_sub_mz_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_sub_mz_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_sub_mz_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_mul_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_mul_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_mul_float64(r0, r1);
}
rvd_float64_m2_t mipp_mul_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_mul_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_mul_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_mul_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_mul_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_mul_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_mul_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_mul_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_mul_float32(r0, r1);
}
rvd_float32_m2_t mipp_mul_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_mul_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_mul_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_mul_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_mul_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_mul_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_mul_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_mul_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_mul_int64(r0, r1);
}
rvd_int64_m2_t mipp_mul_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_mul_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_mul_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_mul_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_mul_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_mul_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_mul_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_mul_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_mul_int32(r0, r1);
}
rvd_int32_m2_t mipp_mul_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_mul_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_mul_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_mul_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_mul_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_mul_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_mul_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_mul_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_mul_int16(r0, r1);
}
rvd_int16_m2_t mipp_mul_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_mul_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_mul_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_mul_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_mul_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_mul_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_mul_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_mul_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_mul_int8(r0, r1);
}
rvd_int8_m2_t mipp_mul_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_mul_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_mul_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_mul_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_mul_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_mul_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_mul_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_mul_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_mul_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_mul_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_mul_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_mul_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_mul_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_mul_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_mul_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_mul_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_mul_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_mul_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_mul_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_mul_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_mul_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_mul_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_mul_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_mul_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_mul_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_mul_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_mul_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_mul_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_mul_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_mul_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_mul_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_mul_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_mul_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_mul_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_mul_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_mul_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_mul_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_mul_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_mul_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_mul_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_mul_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_mul_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_mul_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_mul_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_mul_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_mul_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_mul_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_mul_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_mul_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_mul_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_mul_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_mul_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_mul_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_mul_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_mul_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_mul_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_mul_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_mul_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_mul_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_mul_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_mul_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_mul_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_t mipp_mul_m_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0, const rvd_int64_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_int64(r0, r1, m0, r2);
#endif
}
rvd_int64_m1_t mipp_mul_m_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0, const rvd_int64_m1_t r2) {
	return mipp_mul_m_int64(r0, r1, m0, r2);
}
rvd_int64_m2_t mipp_mul_m_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0, const rvd_int64_m2_t r2) {
	rvd_int64_m2_t res;
	res.m1 = mipp_mul_m_int64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m4_t mipp_mul_m_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0, const rvd_int64_m4_t r2) {
	rvd_int64_m4_t res;
	res.m1 = mipp_mul_m_int64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m8_t mipp_mul_m_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0, const rvd_int64_m8_t r2) {
	rvd_int64_m8_t res;
	res.m1 = mipp_mul_m_int64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_t mipp_mul_m_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0, const rvd_int32_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_int32(r0, r1, m0, r2);
#endif
}
rvd_int32_m1_t mipp_mul_m_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0, const rvd_int32_m1_t r2) {
	return mipp_mul_m_int32(r0, r1, m0, r2);
}
rvd_int32_m2_t mipp_mul_m_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.m1 = mipp_mul_m_int32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m4_t mipp_mul_m_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.m1 = mipp_mul_m_int32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m8_t mipp_mul_m_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.m1 = mipp_mul_m_int32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_t mipp_mul_m_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0, const rvd_int16_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_int16(r0, r1, m0, r2);
#endif
}
rvd_int16_m1_t mipp_mul_m_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0, const rvd_int16_m1_t r2) {
	return mipp_mul_m_int16(r0, r1, m0, r2);
}
rvd_int16_m2_t mipp_mul_m_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0, const rvd_int16_m2_t r2) {
	rvd_int16_m2_t res;
	res.m1 = mipp_mul_m_int16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m4_t mipp_mul_m_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0, const rvd_int16_m4_t r2) {
	rvd_int16_m4_t res;
	res.m1 = mipp_mul_m_int16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m8_t mipp_mul_m_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0, const rvd_int16_m8_t r2) {
	rvd_int16_m8_t res;
	res.m1 = mipp_mul_m_int16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_t mipp_mul_m_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0, const rvd_int8_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_int8(r0, r1, m0, r2);
#endif
}
rvd_int8_m1_t mipp_mul_m_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0, const rvd_int8_m1_t r2) {
	return mipp_mul_m_int8(r0, r1, m0, r2);
}
rvd_int8_m2_t mipp_mul_m_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0, const rvd_int8_m2_t r2) {
	rvd_int8_m2_t res;
	res.m1 = mipp_mul_m_int8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m4_t mipp_mul_m_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0, const rvd_int8_m4_t r2) {
	rvd_int8_m4_t res;
	res.m1 = mipp_mul_m_int8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m8_t mipp_mul_m_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0, const rvd_int8_m8_t r2) {
	rvd_int8_m8_t res;
	res.m1 = mipp_mul_m_int8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_int8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_t mipp_mul_m_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0, const rvd_uint64_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_uint64(r0, r1, m0, r2);
#endif
}
rvd_uint64_m1_t mipp_mul_m_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r2) {
	return mipp_mul_m_uint64(r0, r1, m0, r2);
}
rvd_uint64_m2_t mipp_mul_m_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r2) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_mul_m_uint64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m4_t mipp_mul_m_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r2) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_mul_m_uint64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m8_t mipp_mul_m_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r2) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_mul_m_uint64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_t mipp_mul_m_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0, const rvd_uint32_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_uint32(r0, r1, m0, r2);
#endif
}
rvd_uint32_m1_t mipp_mul_m_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r2) {
	return mipp_mul_m_uint32(r0, r1, m0, r2);
}
rvd_uint32_m2_t mipp_mul_m_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r2) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_mul_m_uint32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m4_t mipp_mul_m_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r2) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_mul_m_uint32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m8_t mipp_mul_m_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r2) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_mul_m_uint32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_t mipp_mul_m_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0, const rvd_uint16_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_uint16(r0, r1, m0, r2);
#endif
}
rvd_uint16_m1_t mipp_mul_m_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r2) {
	return mipp_mul_m_uint16(r0, r1, m0, r2);
}
rvd_uint16_m2_t mipp_mul_m_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r2) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_mul_m_uint16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m4_t mipp_mul_m_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r2) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_mul_m_uint16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m8_t mipp_mul_m_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r2) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_mul_m_uint16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_t mipp_mul_m_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0, const rvd_uint8_t r2) {
#if defined(__AVX__)
	return mipp_avx_mul_m_uint8(r0, r1, m0, r2);
#endif
}
rvd_uint8_m1_t mipp_mul_m_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r2) {
	return mipp_mul_m_uint8(r0, r1, m0, r2);
}
rvd_uint8_m2_t mipp_mul_m_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r2) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_mul_m_uint8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m4_t mipp_mul_m_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r2) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_mul_m_uint8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m8_t mipp_mul_m_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r2) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_mul_m_uint8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_mul_m_uint8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_mul_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_mul_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_mul_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_mul_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_mul_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_mul_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_mul_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_mul_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_mul_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_mul_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_mul_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_mul_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_mul_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_mul_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_mul_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_mul_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_mul_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_mul_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_mul_mz_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_mul_mz_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_mul_mz_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_mul_mz_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_mul_mz_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_mul_mz_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_mul_mz_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_mul_mz_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_mul_mz_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_mul_mz_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_mul_mz_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_mul_mz_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_mul_mz_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_mul_mz_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_mul_mz_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_mul_mz_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_mul_mz_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_mul_mz_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_mul_mz_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_mul_mz_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_mul_mz_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_mul_mz_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_mul_mz_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_mul_mz_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_mul_mz_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_mul_mz_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_mul_mz_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_mul_mz_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_mul_mz_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_mul_mz_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_mul_mz_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_mul_mz_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_mul_mz_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_mul_mz_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_mul_mz_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_mul_mz_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_mul_mz_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_mul_mz_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_mul_mz_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_mul_mz_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_mul_mz_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_mul_mz_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_mul_mz_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_mul_mz_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_mul_mz_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_mul_mz_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_mul_mz_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_mul_mz_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_mul_mz_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_mul_mz_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_mul_mz_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_mul_mz_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_mul_mz_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_mul_mz_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_mul_mz_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_mul_mz_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_mul_mz_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_mul_mz_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_mul_mz_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_mul_mz_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_mul_mz_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_mul_mz_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_mul_mz_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_mul_mz_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_mul_mz_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_mul_mz_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_mul_mz_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_mul_mz_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_mul_mz_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_mul_mz_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_mul_mz_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_mul_mz_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_mul_mz_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_mul_mz_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_div_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_div_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_div_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_div_float64(r0, r1);
}
rvd_float64_m2_t mipp_div_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_div_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_div_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_div_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_div_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_div_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_div_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_div_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_div_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_div_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_div_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_div_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_div_float32(r0, r1);
}
rvd_float32_m2_t mipp_div_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_div_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_div_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_div_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_div_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_div_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_div_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_div_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_div_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_div_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_div_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_div_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_div_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_div_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_div_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_div_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_div_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_div_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_div_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_div_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_div_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_div_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_div_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_div_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_div_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_div_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_div_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_div_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_div_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_div_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_div_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_div_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_div_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_div_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_div_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_div_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_div_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_div_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_div_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_div_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_div_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_div_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_div_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_div_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_div_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_div_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_div_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_div_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_div_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_div_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_div_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_min_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_min_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_min_float64(r0, r1);
}
rvd_float64_m2_t mipp_min_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_min_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_min_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_min_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_min_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_min_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_min_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_min_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_min_float32(r0, r1);
}
rvd_float32_m2_t mipp_min_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_min_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_min_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_min_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_min_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_min_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_min_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_min_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_min_int64(r0, r1);
}
rvd_int64_m2_t mipp_min_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_min_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_min_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_min_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_min_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_min_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_min_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_min_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_min_int32(r0, r1);
}
rvd_int32_m2_t mipp_min_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_min_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_min_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_min_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_min_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_min_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_min_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_min_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_min_int16(r0, r1);
}
rvd_int16_m2_t mipp_min_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_min_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_min_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_min_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_min_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_min_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_min_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_min_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_min_int8(r0, r1);
}
rvd_int8_m2_t mipp_min_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_min_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_min_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_min_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_min_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_min_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_min_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_min_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_min_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_min_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_min_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_min_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_min_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_min_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_min_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_min_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_min_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_min_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_min_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_min_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_min_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_min_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_min_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_min_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_min_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_min_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_min_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_min_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_min_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_min_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_min_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_min_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_min_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_min_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_min_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_min_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_min_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_min_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_min_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_min_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_min_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_min_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_min_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_min_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_min_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_min_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_min_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_min_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_min_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_min_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_min_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_min_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_min_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_min_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_min_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_min_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_min_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_min_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_min_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_min_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_min_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_min_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_min_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_min_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_t mipp_min_m_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0, const rvd_int64_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_int64(r0, r1, m0, r2);
#endif
}
rvd_int64_m1_t mipp_min_m_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0, const rvd_int64_m1_t r2) {
	return mipp_min_m_int64(r0, r1, m0, r2);
}
rvd_int64_m2_t mipp_min_m_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0, const rvd_int64_m2_t r2) {
	rvd_int64_m2_t res;
	res.m1 = mipp_min_m_int64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m4_t mipp_min_m_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0, const rvd_int64_m4_t r2) {
	rvd_int64_m4_t res;
	res.m1 = mipp_min_m_int64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m8_t mipp_min_m_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0, const rvd_int64_m8_t r2) {
	rvd_int64_m8_t res;
	res.m1 = mipp_min_m_int64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_t mipp_min_m_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0, const rvd_int32_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_int32(r0, r1, m0, r2);
#endif
}
rvd_int32_m1_t mipp_min_m_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0, const rvd_int32_m1_t r2) {
	return mipp_min_m_int32(r0, r1, m0, r2);
}
rvd_int32_m2_t mipp_min_m_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.m1 = mipp_min_m_int32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m4_t mipp_min_m_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.m1 = mipp_min_m_int32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m8_t mipp_min_m_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.m1 = mipp_min_m_int32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_t mipp_min_m_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0, const rvd_int16_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_int16(r0, r1, m0, r2);
#endif
}
rvd_int16_m1_t mipp_min_m_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0, const rvd_int16_m1_t r2) {
	return mipp_min_m_int16(r0, r1, m0, r2);
}
rvd_int16_m2_t mipp_min_m_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0, const rvd_int16_m2_t r2) {
	rvd_int16_m2_t res;
	res.m1 = mipp_min_m_int16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m4_t mipp_min_m_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0, const rvd_int16_m4_t r2) {
	rvd_int16_m4_t res;
	res.m1 = mipp_min_m_int16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m8_t mipp_min_m_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0, const rvd_int16_m8_t r2) {
	rvd_int16_m8_t res;
	res.m1 = mipp_min_m_int16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_t mipp_min_m_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0, const rvd_int8_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_int8(r0, r1, m0, r2);
#endif
}
rvd_int8_m1_t mipp_min_m_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0, const rvd_int8_m1_t r2) {
	return mipp_min_m_int8(r0, r1, m0, r2);
}
rvd_int8_m2_t mipp_min_m_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0, const rvd_int8_m2_t r2) {
	rvd_int8_m2_t res;
	res.m1 = mipp_min_m_int8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m4_t mipp_min_m_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0, const rvd_int8_m4_t r2) {
	rvd_int8_m4_t res;
	res.m1 = mipp_min_m_int8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m8_t mipp_min_m_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0, const rvd_int8_m8_t r2) {
	rvd_int8_m8_t res;
	res.m1 = mipp_min_m_int8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_int8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_t mipp_min_m_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0, const rvd_uint64_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_uint64(r0, r1, m0, r2);
#endif
}
rvd_uint64_m1_t mipp_min_m_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r2) {
	return mipp_min_m_uint64(r0, r1, m0, r2);
}
rvd_uint64_m2_t mipp_min_m_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r2) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_min_m_uint64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m4_t mipp_min_m_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r2) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_min_m_uint64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m8_t mipp_min_m_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r2) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_min_m_uint64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_t mipp_min_m_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0, const rvd_uint32_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_uint32(r0, r1, m0, r2);
#endif
}
rvd_uint32_m1_t mipp_min_m_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r2) {
	return mipp_min_m_uint32(r0, r1, m0, r2);
}
rvd_uint32_m2_t mipp_min_m_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r2) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_min_m_uint32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m4_t mipp_min_m_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r2) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_min_m_uint32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m8_t mipp_min_m_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r2) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_min_m_uint32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_t mipp_min_m_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0, const rvd_uint16_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_uint16(r0, r1, m0, r2);
#endif
}
rvd_uint16_m1_t mipp_min_m_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r2) {
	return mipp_min_m_uint16(r0, r1, m0, r2);
}
rvd_uint16_m2_t mipp_min_m_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r2) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_min_m_uint16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m4_t mipp_min_m_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r2) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_min_m_uint16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m8_t mipp_min_m_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r2) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_min_m_uint16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_t mipp_min_m_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0, const rvd_uint8_t r2) {
#if defined(__AVX__)
	return mipp_avx_min_m_uint8(r0, r1, m0, r2);
#endif
}
rvd_uint8_m1_t mipp_min_m_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r2) {
	return mipp_min_m_uint8(r0, r1, m0, r2);
}
rvd_uint8_m2_t mipp_min_m_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r2) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_min_m_uint8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m4_t mipp_min_m_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r2) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_min_m_uint8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m8_t mipp_min_m_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r2) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_min_m_uint8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_min_m_uint8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_min_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_min_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_min_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_min_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_min_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_min_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_min_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_min_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_min_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_min_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_min_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_min_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_min_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_min_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_min_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_min_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_min_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_min_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_min_mz_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_min_mz_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_min_mz_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_min_mz_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_min_mz_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_min_mz_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_min_mz_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_min_mz_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_min_mz_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_min_mz_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_min_mz_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_min_mz_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_min_mz_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_min_mz_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_min_mz_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_min_mz_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_min_mz_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_min_mz_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_min_mz_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_min_mz_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_min_mz_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_min_mz_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_min_mz_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_min_mz_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_min_mz_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_min_mz_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_min_mz_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_min_mz_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_min_mz_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_min_mz_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_min_mz_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_min_mz_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_min_mz_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_min_mz_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_min_mz_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_min_mz_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_min_mz_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_min_mz_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_min_mz_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_min_mz_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_min_mz_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_min_mz_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_min_mz_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_min_mz_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_min_mz_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_min_mz_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_min_mz_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_min_mz_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_min_mz_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_min_mz_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_min_mz_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_min_mz_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_min_mz_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_min_mz_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_min_mz_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_min_mz_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_min_mz_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_min_mz_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_min_mz_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_min_mz_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_min_mz_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_min_mz_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_min_mz_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_min_mz_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_min_mz_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_min_mz_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_min_mz_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_min_mz_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_min_mz_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_min_mz_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_min_mz_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_min_mz_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_min_mz_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_min_mz_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_max_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_max_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_max_float64(r0, r1);
}
rvd_float64_m2_t mipp_max_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_max_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_max_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_max_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_max_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_max_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_max_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_max_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_max_float32(r0, r1);
}
rvd_float32_m2_t mipp_max_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_max_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_max_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_max_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_max_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_max_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_max_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_max_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_max_int64(r0, r1);
}
rvd_int64_m2_t mipp_max_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_max_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_max_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_max_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_max_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_max_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_max_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_max_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_max_int32(r0, r1);
}
rvd_int32_m2_t mipp_max_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_max_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_max_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_max_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_max_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_max_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_max_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_max_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_max_int16(r0, r1);
}
rvd_int16_m2_t mipp_max_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_max_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_max_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_max_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_max_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_max_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_max_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_max_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_max_int8(r0, r1);
}
rvd_int8_m2_t mipp_max_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_max_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_max_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_max_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_max_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_max_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_max_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_max_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_max_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_max_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_max_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_max_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_max_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_max_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_max_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_max_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_max_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_max_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_max_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_max_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_max_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_max_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_max_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_max_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_max_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_max_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_max_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_max_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_max_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_max_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_max_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_max_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_max_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_max_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_max_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_max_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_max_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_max_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_max_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_max_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_max_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_max_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_max_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_max_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_max_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_max_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_max_m_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_float64(r0, r1, m0, r2);
#endif
}
rvd_float64_m1_t mipp_max_m_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0, const rvd_float64_m1_t r2) {
	return mipp_max_m_float64(r0, r1, m0, r2);
}
rvd_float64_m2_t mipp_max_m_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_max_m_float64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_max_m_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_max_m_float64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_max_m_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_max_m_float64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_max_m_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_float32(r0, r1, m0, r2);
#endif
}
rvd_float32_m1_t mipp_max_m_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0, const rvd_float32_m1_t r2) {
	return mipp_max_m_float32(r0, r1, m0, r2);
}
rvd_float32_m2_t mipp_max_m_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_max_m_float32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_max_m_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_max_m_float32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_max_m_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_max_m_float32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_float32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_t mipp_max_m_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0, const rvd_int64_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_int64(r0, r1, m0, r2);
#endif
}
rvd_int64_m1_t mipp_max_m_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0, const rvd_int64_m1_t r2) {
	return mipp_max_m_int64(r0, r1, m0, r2);
}
rvd_int64_m2_t mipp_max_m_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0, const rvd_int64_m2_t r2) {
	rvd_int64_m2_t res;
	res.m1 = mipp_max_m_int64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m4_t mipp_max_m_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0, const rvd_int64_m4_t r2) {
	rvd_int64_m4_t res;
	res.m1 = mipp_max_m_int64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int64_m8_t mipp_max_m_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0, const rvd_int64_m8_t r2) {
	rvd_int64_m8_t res;
	res.m1 = mipp_max_m_int64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_t mipp_max_m_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0, const rvd_int32_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_int32(r0, r1, m0, r2);
#endif
}
rvd_int32_m1_t mipp_max_m_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0, const rvd_int32_m1_t r2) {
	return mipp_max_m_int32(r0, r1, m0, r2);
}
rvd_int32_m2_t mipp_max_m_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.m1 = mipp_max_m_int32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m4_t mipp_max_m_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.m1 = mipp_max_m_int32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int32_m8_t mipp_max_m_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.m1 = mipp_max_m_int32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_t mipp_max_m_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0, const rvd_int16_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_int16(r0, r1, m0, r2);
#endif
}
rvd_int16_m1_t mipp_max_m_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0, const rvd_int16_m1_t r2) {
	return mipp_max_m_int16(r0, r1, m0, r2);
}
rvd_int16_m2_t mipp_max_m_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0, const rvd_int16_m2_t r2) {
	rvd_int16_m2_t res;
	res.m1 = mipp_max_m_int16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m4_t mipp_max_m_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0, const rvd_int16_m4_t r2) {
	rvd_int16_m4_t res;
	res.m1 = mipp_max_m_int16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int16_m8_t mipp_max_m_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0, const rvd_int16_m8_t r2) {
	rvd_int16_m8_t res;
	res.m1 = mipp_max_m_int16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_t mipp_max_m_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0, const rvd_int8_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_int8(r0, r1, m0, r2);
#endif
}
rvd_int8_m1_t mipp_max_m_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0, const rvd_int8_m1_t r2) {
	return mipp_max_m_int8(r0, r1, m0, r2);
}
rvd_int8_m2_t mipp_max_m_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0, const rvd_int8_m2_t r2) {
	rvd_int8_m2_t res;
	res.m1 = mipp_max_m_int8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m4_t mipp_max_m_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0, const rvd_int8_m4_t r2) {
	rvd_int8_m4_t res;
	res.m1 = mipp_max_m_int8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_int8_m8_t mipp_max_m_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0, const rvd_int8_m8_t r2) {
	rvd_int8_m8_t res;
	res.m1 = mipp_max_m_int8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_int8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_t mipp_max_m_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0, const rvd_uint64_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_uint64(r0, r1, m0, r2);
#endif
}
rvd_uint64_m1_t mipp_max_m_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r2) {
	return mipp_max_m_uint64(r0, r1, m0, r2);
}
rvd_uint64_m2_t mipp_max_m_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r2) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_max_m_uint64_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint64_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m4_t mipp_max_m_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r2) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_max_m_uint64_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint64_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint64_m8_t mipp_max_m_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r2) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_max_m_uint64_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint64_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_t mipp_max_m_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0, const rvd_uint32_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_uint32(r0, r1, m0, r2);
#endif
}
rvd_uint32_m1_t mipp_max_m_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r2) {
	return mipp_max_m_uint32(r0, r1, m0, r2);
}
rvd_uint32_m2_t mipp_max_m_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r2) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_max_m_uint32_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint32_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m4_t mipp_max_m_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r2) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_max_m_uint32_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint32_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint32_m8_t mipp_max_m_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r2) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_max_m_uint32_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint32_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_t mipp_max_m_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0, const rvd_uint16_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_uint16(r0, r1, m0, r2);
#endif
}
rvd_uint16_m1_t mipp_max_m_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r2) {
	return mipp_max_m_uint16(r0, r1, m0, r2);
}
rvd_uint16_m2_t mipp_max_m_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r2) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_max_m_uint16_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint16_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m4_t mipp_max_m_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r2) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_max_m_uint16_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint16_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint16_m8_t mipp_max_m_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r2) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_max_m_uint16_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint16_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_t mipp_max_m_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0, const rvd_uint8_t r2) {
#if defined(__AVX__)
	return mipp_avx_max_m_uint8(r0, r1, m0, r2);
#endif
}
rvd_uint8_m1_t mipp_max_m_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r2) {
	return mipp_max_m_uint8(r0, r1, m0, r2);
}
rvd_uint8_m2_t mipp_max_m_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r2) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_max_m_uint8_m1(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint8_m1(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m4_t mipp_max_m_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r2) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_max_m_uint8_m2(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint8_m2(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_uint8_m8_t mipp_max_m_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r2) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_max_m_uint8_m4(r0.m1, r1.m1, m0.m1, r2.m1);
	res.m2 = mipp_max_m_uint8_m4(r0.m2, r1.m2, m0.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_max_mz_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_max_mz_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_max_mz_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_max_mz_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_max_mz_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_max_mz_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_max_mz_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_max_mz_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_max_mz_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_max_mz_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_max_mz_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_max_mz_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_max_mz_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_max_mz_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_max_mz_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_max_mz_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_max_mz_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_max_mz_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_max_mz_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_max_mz_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_max_mz_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_max_mz_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_max_mz_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_max_mz_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_max_mz_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_max_mz_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_max_mz_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_max_mz_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_max_mz_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_max_mz_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_max_mz_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_max_mz_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_max_mz_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_max_mz_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_max_mz_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_max_mz_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_max_mz_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_max_mz_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_max_mz_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_max_mz_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_max_mz_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_max_mz_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_max_mz_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_max_mz_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_max_mz_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_max_mz_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_max_mz_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_max_mz_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_max_mz_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_max_mz_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_max_mz_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_max_mz_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_max_mz_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_max_mz_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_max_mz_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_max_mz_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_max_mz_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_max_mz_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_max_mz_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_max_mz_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_max_mz_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_max_mz_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_max_mz_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_max_mz_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_max_mz_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_max_mz_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_max_mz_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_max_mz_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_max_mz_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_max_mz_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_max_mz_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_max_mz_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_max_mz_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_max_mz_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_max_mz_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_max_mz_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_max_mz_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_max_mz_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_max_mz_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_max_mz_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_max_mz_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_max_mz_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_max_mz_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_max_mz_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_max_mz_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_max_mz_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_max_mz_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_max_mz_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_max_mz_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_max_mz_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_max_mz_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_max_mz_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_fmadd_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_fmadd_float64(r0, r1, r2);
#endif
}
rvd_float64_m1_t mipp_fmadd_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvd_float64_m1_t r2) {
	return mipp_fmadd_float64(r0, r1, r2);
}
rvd_float64_m2_t mipp_fmadd_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_fmadd_float64_m1(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float64_m1(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_fmadd_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_fmadd_float64_m2(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float64_m2(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_fmadd_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_fmadd_float64_m4(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float64_m4(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_fmadd_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_fmadd_float32(r0, r1, r2);
#endif
}
rvd_float32_m1_t mipp_fmadd_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvd_float32_m1_t r2) {
	return mipp_fmadd_float32(r0, r1, r2);
}
rvd_float32_m2_t mipp_fmadd_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_fmadd_float32_m1(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float32_m1(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_fmadd_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_fmadd_float32_m2(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float32_m2(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_fmadd_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_fmadd_float32_m4(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmadd_float32_m4(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_fmsub_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvd_float64_t r2) {
#if defined(__AVX__)
	return mipp_avx_fmsub_float64(r0, r1, r2);
#endif
}
rvd_float64_m1_t mipp_fmsub_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvd_float64_m1_t r2) {
	return mipp_fmsub_float64(r0, r1, r2);
}
rvd_float64_m2_t mipp_fmsub_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.m1 = mipp_fmsub_float64_m1(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float64_m1(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_m4_t mipp_fmsub_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.m1 = mipp_fmsub_float64_m2(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float64_m2(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_m8_t mipp_fmsub_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.m1 = mipp_fmsub_float64_m4(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float64_m4(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_t mipp_fmsub_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvd_float32_t r2) {
#if defined(__AVX__)
	return mipp_avx_fmsub_float32(r0, r1, r2);
#endif
}
rvd_float32_m1_t mipp_fmsub_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvd_float32_m1_t r2) {
	return mipp_fmsub_float32(r0, r1, r2);
}
rvd_float32_m2_t mipp_fmsub_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.m1 = mipp_fmsub_float32_m1(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float32_m1(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_m4_t mipp_fmsub_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.m1 = mipp_fmsub_float32_m2(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float32_m2(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float32_m8_t mipp_fmsub_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.m1 = mipp_fmsub_float32_m4(r0.m1, r1.m1, r2.m1);
	res.m2 = mipp_fmsub_float32_m4(r0.m2, r1.m2, r2.m2);
	return res;
}
rvd_float64_t mipp_andb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_andb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_andb_float64(r0, r1);
}
rvd_float64_m2_t mipp_andb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_andb_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_andb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_andb_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_andb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_andb_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_andb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_andb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_andb_float32(r0, r1);
}
rvd_float32_m2_t mipp_andb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_andb_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_andb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_andb_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_andb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_andb_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_andb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_andb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_andb_int64(r0, r1);
}
rvd_int64_m2_t mipp_andb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_andb_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_andb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_andb_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_andb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_andb_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_andb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_andb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_andb_int32(r0, r1);
}
rvd_int32_m2_t mipp_andb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_andb_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_andb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_andb_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_andb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_andb_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_andb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_andb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_andb_int16(r0, r1);
}
rvd_int16_m2_t mipp_andb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_andb_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_andb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_andb_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_andb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_andb_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_andb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_andb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_andb_int8(r0, r1);
}
rvd_int8_m2_t mipp_andb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_andb_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_andb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_andb_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_andb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_andb_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_andb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_andb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_andb_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_andb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_andb_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_andb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_andb_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_andb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_andb_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_andb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_andb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_andb_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_andb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_andb_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_andb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_andb_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_andb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_andb_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_andb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_andb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_andb_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_andb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_andb_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_andb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_andb_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_andb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_andb_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_andb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_andb_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_andb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_andb_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_andb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_andb_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_andb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_andb_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_andb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_andb_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_andb_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvm_float64_t mipp_andb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_float64(m0, m1);
#endif
}
rvm_float64_m1_t mipp_andb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_andb_k_float64(m0, m1);
}
rvm_float64_m2_t mipp_andb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t res;
	res.m1 = mipp_andb_k_float64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float64_m1(m0.m2, m1.m2);
	return res;
}
rvm_float64_m4_t mipp_andb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t res;
	res.m1 = mipp_andb_k_float64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float64_m2(m0.m2, m1.m2);
	return res;
}
rvm_float64_m8_t mipp_andb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t res;
	res.m1 = mipp_andb_k_float64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float64_m4(m0.m2, m1.m2);
	return res;
}
rvm_float32_t mipp_andb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_float32(m0, m1);
#endif
}
rvm_float32_m1_t mipp_andb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_andb_k_float32(m0, m1);
}
rvm_float32_m2_t mipp_andb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t res;
	res.m1 = mipp_andb_k_float32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float32_m1(m0.m2, m1.m2);
	return res;
}
rvm_float32_m4_t mipp_andb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t res;
	res.m1 = mipp_andb_k_float32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float32_m2(m0.m2, m1.m2);
	return res;
}
rvm_float32_m8_t mipp_andb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t res;
	res.m1 = mipp_andb_k_float32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_float32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int64_t mipp_andb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_int64(m0, m1);
#endif
}
rvm_int64_m1_t mipp_andb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_andb_k_int64(m0, m1);
}
rvm_int64_m2_t mipp_andb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t res;
	res.m1 = mipp_andb_k_int64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int64_m1(m0.m2, m1.m2);
	return res;
}
rvm_int64_m4_t mipp_andb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t res;
	res.m1 = mipp_andb_k_int64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int64_m2(m0.m2, m1.m2);
	return res;
}
rvm_int64_m8_t mipp_andb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t res;
	res.m1 = mipp_andb_k_int64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int64_m4(m0.m2, m1.m2);
	return res;
}
rvm_int32_t mipp_andb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_int32(m0, m1);
#endif
}
rvm_int32_m1_t mipp_andb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_andb_k_int32(m0, m1);
}
rvm_int32_m2_t mipp_andb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t res;
	res.m1 = mipp_andb_k_int32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int32_m1(m0.m2, m1.m2);
	return res;
}
rvm_int32_m4_t mipp_andb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t res;
	res.m1 = mipp_andb_k_int32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int32_m2(m0.m2, m1.m2);
	return res;
}
rvm_int32_m8_t mipp_andb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t res;
	res.m1 = mipp_andb_k_int32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int16_t mipp_andb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_int16(m0, m1);
#endif
}
rvm_int16_m1_t mipp_andb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_andb_k_int16(m0, m1);
}
rvm_int16_m2_t mipp_andb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t res;
	res.m1 = mipp_andb_k_int16_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int16_m1(m0.m2, m1.m2);
	return res;
}
rvm_int16_m4_t mipp_andb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t res;
	res.m1 = mipp_andb_k_int16_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int16_m2(m0.m2, m1.m2);
	return res;
}
rvm_int16_m8_t mipp_andb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t res;
	res.m1 = mipp_andb_k_int16_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int16_m4(m0.m2, m1.m2);
	return res;
}
rvm_int8_t mipp_andb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_int8(m0, m1);
#endif
}
rvm_int8_m1_t mipp_andb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_andb_k_int8(m0, m1);
}
rvm_int8_m2_t mipp_andb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t res;
	res.m1 = mipp_andb_k_int8_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int8_m1(m0.m2, m1.m2);
	return res;
}
rvm_int8_m4_t mipp_andb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t res;
	res.m1 = mipp_andb_k_int8_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int8_m2(m0.m2, m1.m2);
	return res;
}
rvm_int8_m8_t mipp_andb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t res;
	res.m1 = mipp_andb_k_int8_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_int8_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint64_t mipp_andb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_uint64(m0, m1);
#endif
}
rvm_uint64_m1_t mipp_andb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_andb_k_uint64(m0, m1);
}
rvm_uint64_m2_t mipp_andb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_andb_k_uint64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint64_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m4_t mipp_andb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_andb_k_uint64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint64_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m8_t mipp_andb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_andb_k_uint64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint64_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint32_t mipp_andb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_uint32(m0, m1);
#endif
}
rvm_uint32_m1_t mipp_andb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_andb_k_uint32(m0, m1);
}
rvm_uint32_m2_t mipp_andb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_andb_k_uint32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint32_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m4_t mipp_andb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_andb_k_uint32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint32_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m8_t mipp_andb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_andb_k_uint32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint32_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint16_t mipp_andb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_uint16(m0, m1);
#endif
}
rvm_uint16_m1_t mipp_andb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_andb_k_uint16(m0, m1);
}
rvm_uint16_m2_t mipp_andb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_andb_k_uint16_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint16_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m4_t mipp_andb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_andb_k_uint16_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint16_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m8_t mipp_andb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_andb_k_uint16_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint16_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint8_t mipp_andb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX__)
	return mipp_avx_andb_k_uint8(m0, m1);
#endif
}
rvm_uint8_m1_t mipp_andb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_andb_k_uint8(m0, m1);
}
rvm_uint8_m2_t mipp_andb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_andb_k_uint8_m1(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint8_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m4_t mipp_andb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_andb_k_uint8_m2(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint8_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m8_t mipp_andb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_andb_k_uint8_m4(m0.m1, m1.m1);
	res.m2 = mipp_andb_k_uint8_m4(m0.m2, m1.m2);
	return res;
}
rvd_float64_t mipp_andnb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_andnb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_andnb_float64(r0, r1);
}
rvd_float64_m2_t mipp_andnb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_andnb_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_andnb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_andnb_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_andnb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_andnb_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_andnb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_andnb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_andnb_float32(r0, r1);
}
rvd_float32_m2_t mipp_andnb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_andnb_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_andnb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_andnb_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_andnb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_andnb_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_andnb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_andnb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_andnb_int64(r0, r1);
}
rvd_int64_m2_t mipp_andnb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_andnb_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_andnb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_andnb_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_andnb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_andnb_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_andnb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_andnb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_andnb_int32(r0, r1);
}
rvd_int32_m2_t mipp_andnb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_andnb_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_andnb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_andnb_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_andnb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_andnb_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_andnb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_andnb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_andnb_int16(r0, r1);
}
rvd_int16_m2_t mipp_andnb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_andnb_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_andnb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_andnb_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_andnb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_andnb_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_andnb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_andnb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_andnb_int8(r0, r1);
}
rvd_int8_m2_t mipp_andnb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_andnb_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_andnb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_andnb_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_andnb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_andnb_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_andnb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_andnb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_andnb_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_andnb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_andnb_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_andnb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_andnb_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_andnb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_andnb_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_andnb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_andnb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_andnb_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_andnb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_andnb_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_andnb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_andnb_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_andnb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_andnb_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_andnb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_andnb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_andnb_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_andnb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_andnb_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_andnb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_andnb_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_andnb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_andnb_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_andnb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_andnb_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_andnb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_andnb_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_andnb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_andnb_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_andnb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_andnb_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_andnb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_andnb_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_andnb_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvm_float64_t mipp_andnb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_float64(m0, m1);
#endif
}
rvm_float64_m1_t mipp_andnb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_andnb_k_float64(m0, m1);
}
rvm_float64_m2_t mipp_andnb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t res;
	res.m1 = mipp_andnb_k_float64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float64_m1(m0.m2, m1.m2);
	return res;
}
rvm_float64_m4_t mipp_andnb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t res;
	res.m1 = mipp_andnb_k_float64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float64_m2(m0.m2, m1.m2);
	return res;
}
rvm_float64_m8_t mipp_andnb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t res;
	res.m1 = mipp_andnb_k_float64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float64_m4(m0.m2, m1.m2);
	return res;
}
rvm_float32_t mipp_andnb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_float32(m0, m1);
#endif
}
rvm_float32_m1_t mipp_andnb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_andnb_k_float32(m0, m1);
}
rvm_float32_m2_t mipp_andnb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t res;
	res.m1 = mipp_andnb_k_float32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float32_m1(m0.m2, m1.m2);
	return res;
}
rvm_float32_m4_t mipp_andnb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t res;
	res.m1 = mipp_andnb_k_float32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float32_m2(m0.m2, m1.m2);
	return res;
}
rvm_float32_m8_t mipp_andnb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t res;
	res.m1 = mipp_andnb_k_float32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_float32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int64_t mipp_andnb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_int64(m0, m1);
#endif
}
rvm_int64_m1_t mipp_andnb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_andnb_k_int64(m0, m1);
}
rvm_int64_m2_t mipp_andnb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t res;
	res.m1 = mipp_andnb_k_int64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int64_m1(m0.m2, m1.m2);
	return res;
}
rvm_int64_m4_t mipp_andnb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t res;
	res.m1 = mipp_andnb_k_int64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int64_m2(m0.m2, m1.m2);
	return res;
}
rvm_int64_m8_t mipp_andnb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t res;
	res.m1 = mipp_andnb_k_int64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int64_m4(m0.m2, m1.m2);
	return res;
}
rvm_int32_t mipp_andnb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_int32(m0, m1);
#endif
}
rvm_int32_m1_t mipp_andnb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_andnb_k_int32(m0, m1);
}
rvm_int32_m2_t mipp_andnb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t res;
	res.m1 = mipp_andnb_k_int32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int32_m1(m0.m2, m1.m2);
	return res;
}
rvm_int32_m4_t mipp_andnb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t res;
	res.m1 = mipp_andnb_k_int32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int32_m2(m0.m2, m1.m2);
	return res;
}
rvm_int32_m8_t mipp_andnb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t res;
	res.m1 = mipp_andnb_k_int32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int16_t mipp_andnb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_int16(m0, m1);
#endif
}
rvm_int16_m1_t mipp_andnb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_andnb_k_int16(m0, m1);
}
rvm_int16_m2_t mipp_andnb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t res;
	res.m1 = mipp_andnb_k_int16_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int16_m1(m0.m2, m1.m2);
	return res;
}
rvm_int16_m4_t mipp_andnb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t res;
	res.m1 = mipp_andnb_k_int16_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int16_m2(m0.m2, m1.m2);
	return res;
}
rvm_int16_m8_t mipp_andnb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t res;
	res.m1 = mipp_andnb_k_int16_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int16_m4(m0.m2, m1.m2);
	return res;
}
rvm_int8_t mipp_andnb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_int8(m0, m1);
#endif
}
rvm_int8_m1_t mipp_andnb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_andnb_k_int8(m0, m1);
}
rvm_int8_m2_t mipp_andnb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t res;
	res.m1 = mipp_andnb_k_int8_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int8_m1(m0.m2, m1.m2);
	return res;
}
rvm_int8_m4_t mipp_andnb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t res;
	res.m1 = mipp_andnb_k_int8_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int8_m2(m0.m2, m1.m2);
	return res;
}
rvm_int8_m8_t mipp_andnb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t res;
	res.m1 = mipp_andnb_k_int8_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_int8_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint64_t mipp_andnb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_uint64(m0, m1);
#endif
}
rvm_uint64_m1_t mipp_andnb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_andnb_k_uint64(m0, m1);
}
rvm_uint64_m2_t mipp_andnb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_andnb_k_uint64_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint64_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m4_t mipp_andnb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_andnb_k_uint64_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint64_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m8_t mipp_andnb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_andnb_k_uint64_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint64_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint32_t mipp_andnb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_uint32(m0, m1);
#endif
}
rvm_uint32_m1_t mipp_andnb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_andnb_k_uint32(m0, m1);
}
rvm_uint32_m2_t mipp_andnb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_andnb_k_uint32_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint32_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m4_t mipp_andnb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_andnb_k_uint32_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint32_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m8_t mipp_andnb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_andnb_k_uint32_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint32_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint16_t mipp_andnb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_uint16(m0, m1);
#endif
}
rvm_uint16_m1_t mipp_andnb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_andnb_k_uint16(m0, m1);
}
rvm_uint16_m2_t mipp_andnb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_andnb_k_uint16_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint16_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m4_t mipp_andnb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_andnb_k_uint16_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint16_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m8_t mipp_andnb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_andnb_k_uint16_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint16_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint8_t mipp_andnb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX__)
	return mipp_avx_andnb_k_uint8(m0, m1);
#endif
}
rvm_uint8_m1_t mipp_andnb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_andnb_k_uint8(m0, m1);
}
rvm_uint8_m2_t mipp_andnb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_andnb_k_uint8_m1(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint8_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m4_t mipp_andnb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_andnb_k_uint8_m2(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint8_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m8_t mipp_andnb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_andnb_k_uint8_m4(m0.m1, m1.m1);
	res.m2 = mipp_andnb_k_uint8_m4(m0.m2, m1.m2);
	return res;
}
rvd_float64_t mipp_xorb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_float64(r0, r1);
#endif
}
rvd_float64_m1_t mipp_xorb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_xorb_float64(r0, r1);
}
rvd_float64_m2_t mipp_xorb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_xorb_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float64_m1(r0.m2, r1.m2);
	return res;
}
rvd_float64_m4_t mipp_xorb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_xorb_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float64_m2(r0.m2, r1.m2);
	return res;
}
rvd_float64_m8_t mipp_xorb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_xorb_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float64_m4(r0.m2, r1.m2);
	return res;
}
rvd_float32_t mipp_xorb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_float32(r0, r1);
#endif
}
rvd_float32_m1_t mipp_xorb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_xorb_float32(r0, r1);
}
rvd_float32_m2_t mipp_xorb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_xorb_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float32_m1(r0.m2, r1.m2);
	return res;
}
rvd_float32_m4_t mipp_xorb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_xorb_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float32_m2(r0.m2, r1.m2);
	return res;
}
rvd_float32_m8_t mipp_xorb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_xorb_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_float32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int64_t mipp_xorb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_int64(r0, r1);
#endif
}
rvd_int64_m1_t mipp_xorb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_xorb_int64(r0, r1);
}
rvd_int64_m2_t mipp_xorb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_xorb_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int64_m1(r0.m2, r1.m2);
	return res;
}
rvd_int64_m4_t mipp_xorb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_xorb_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int64_m2(r0.m2, r1.m2);
	return res;
}
rvd_int64_m8_t mipp_xorb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_xorb_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int64_m4(r0.m2, r1.m2);
	return res;
}
rvd_int32_t mipp_xorb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_int32(r0, r1);
#endif
}
rvd_int32_m1_t mipp_xorb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_xorb_int32(r0, r1);
}
rvd_int32_m2_t mipp_xorb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_xorb_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int32_m1(r0.m2, r1.m2);
	return res;
}
rvd_int32_m4_t mipp_xorb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_xorb_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int32_m2(r0.m2, r1.m2);
	return res;
}
rvd_int32_m8_t mipp_xorb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_xorb_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int32_m4(r0.m2, r1.m2);
	return res;
}
rvd_int16_t mipp_xorb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_int16(r0, r1);
#endif
}
rvd_int16_m1_t mipp_xorb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_xorb_int16(r0, r1);
}
rvd_int16_m2_t mipp_xorb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_xorb_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int16_m1(r0.m2, r1.m2);
	return res;
}
rvd_int16_m4_t mipp_xorb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_xorb_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int16_m2(r0.m2, r1.m2);
	return res;
}
rvd_int16_m8_t mipp_xorb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_xorb_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int16_m4(r0.m2, r1.m2);
	return res;
}
rvd_int8_t mipp_xorb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_int8(r0, r1);
#endif
}
rvd_int8_m1_t mipp_xorb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_xorb_int8(r0, r1);
}
rvd_int8_m2_t mipp_xorb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_xorb_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int8_m1(r0.m2, r1.m2);
	return res;
}
rvd_int8_m4_t mipp_xorb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_xorb_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int8_m2(r0.m2, r1.m2);
	return res;
}
rvd_int8_m8_t mipp_xorb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_xorb_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_int8_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint64_t mipp_xorb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_uint64(r0, r1);
#endif
}
rvd_uint64_m1_t mipp_xorb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_xorb_uint64(r0, r1);
}
rvd_uint64_m2_t mipp_xorb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_xorb_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m4_t mipp_xorb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_xorb_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint64_m8_t mipp_xorb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_xorb_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint32_t mipp_xorb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_uint32(r0, r1);
#endif
}
rvd_uint32_m1_t mipp_xorb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_xorb_uint32(r0, r1);
}
rvd_uint32_m2_t mipp_xorb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_xorb_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m4_t mipp_xorb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_xorb_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint32_m8_t mipp_xorb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_xorb_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint16_t mipp_xorb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_uint16(r0, r1);
#endif
}
rvd_uint16_m1_t mipp_xorb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_xorb_uint16(r0, r1);
}
rvd_uint16_m2_t mipp_xorb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_xorb_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m4_t mipp_xorb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_xorb_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint16_m8_t mipp_xorb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_xorb_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvd_uint8_t mipp_xorb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_xorb_uint8(r0, r1);
#endif
}
rvd_uint8_m1_t mipp_xorb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_xorb_uint8(r0, r1);
}
rvd_uint8_m2_t mipp_xorb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_xorb_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m4_t mipp_xorb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_xorb_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvd_uint8_m8_t mipp_xorb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_xorb_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_xorb_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvm_float64_t mipp_xorb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_float64(m0, m1);
#endif
}
rvm_float64_m1_t mipp_xorb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_xorb_k_float64(m0, m1);
}
rvm_float64_m2_t mipp_xorb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t res;
	res.m1 = mipp_xorb_k_float64_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float64_m1(m0.m2, m1.m2);
	return res;
}
rvm_float64_m4_t mipp_xorb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t res;
	res.m1 = mipp_xorb_k_float64_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float64_m2(m0.m2, m1.m2);
	return res;
}
rvm_float64_m8_t mipp_xorb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t res;
	res.m1 = mipp_xorb_k_float64_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float64_m4(m0.m2, m1.m2);
	return res;
}
rvm_float32_t mipp_xorb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_float32(m0, m1);
#endif
}
rvm_float32_m1_t mipp_xorb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_xorb_k_float32(m0, m1);
}
rvm_float32_m2_t mipp_xorb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t res;
	res.m1 = mipp_xorb_k_float32_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float32_m1(m0.m2, m1.m2);
	return res;
}
rvm_float32_m4_t mipp_xorb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t res;
	res.m1 = mipp_xorb_k_float32_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float32_m2(m0.m2, m1.m2);
	return res;
}
rvm_float32_m8_t mipp_xorb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t res;
	res.m1 = mipp_xorb_k_float32_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_float32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int64_t mipp_xorb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_int64(m0, m1);
#endif
}
rvm_int64_m1_t mipp_xorb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_xorb_k_int64(m0, m1);
}
rvm_int64_m2_t mipp_xorb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t res;
	res.m1 = mipp_xorb_k_int64_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int64_m1(m0.m2, m1.m2);
	return res;
}
rvm_int64_m4_t mipp_xorb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t res;
	res.m1 = mipp_xorb_k_int64_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int64_m2(m0.m2, m1.m2);
	return res;
}
rvm_int64_m8_t mipp_xorb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t res;
	res.m1 = mipp_xorb_k_int64_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int64_m4(m0.m2, m1.m2);
	return res;
}
rvm_int32_t mipp_xorb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_int32(m0, m1);
#endif
}
rvm_int32_m1_t mipp_xorb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_xorb_k_int32(m0, m1);
}
rvm_int32_m2_t mipp_xorb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t res;
	res.m1 = mipp_xorb_k_int32_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int32_m1(m0.m2, m1.m2);
	return res;
}
rvm_int32_m4_t mipp_xorb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t res;
	res.m1 = mipp_xorb_k_int32_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int32_m2(m0.m2, m1.m2);
	return res;
}
rvm_int32_m8_t mipp_xorb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t res;
	res.m1 = mipp_xorb_k_int32_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int32_m4(m0.m2, m1.m2);
	return res;
}
rvm_int16_t mipp_xorb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_int16(m0, m1);
#endif
}
rvm_int16_m1_t mipp_xorb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_xorb_k_int16(m0, m1);
}
rvm_int16_m2_t mipp_xorb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t res;
	res.m1 = mipp_xorb_k_int16_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int16_m1(m0.m2, m1.m2);
	return res;
}
rvm_int16_m4_t mipp_xorb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t res;
	res.m1 = mipp_xorb_k_int16_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int16_m2(m0.m2, m1.m2);
	return res;
}
rvm_int16_m8_t mipp_xorb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t res;
	res.m1 = mipp_xorb_k_int16_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int16_m4(m0.m2, m1.m2);
	return res;
}
rvm_int8_t mipp_xorb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_int8(m0, m1);
#endif
}
rvm_int8_m1_t mipp_xorb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_xorb_k_int8(m0, m1);
}
rvm_int8_m2_t mipp_xorb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t res;
	res.m1 = mipp_xorb_k_int8_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int8_m1(m0.m2, m1.m2);
	return res;
}
rvm_int8_m4_t mipp_xorb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t res;
	res.m1 = mipp_xorb_k_int8_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int8_m2(m0.m2, m1.m2);
	return res;
}
rvm_int8_m8_t mipp_xorb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t res;
	res.m1 = mipp_xorb_k_int8_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_int8_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint64_t mipp_xorb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_uint64(m0, m1);
#endif
}
rvm_uint64_m1_t mipp_xorb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_xorb_k_uint64(m0, m1);
}
rvm_uint64_m2_t mipp_xorb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_xorb_k_uint64_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint64_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m4_t mipp_xorb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_xorb_k_uint64_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint64_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint64_m8_t mipp_xorb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_xorb_k_uint64_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint64_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint32_t mipp_xorb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_uint32(m0, m1);
#endif
}
rvm_uint32_m1_t mipp_xorb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_xorb_k_uint32(m0, m1);
}
rvm_uint32_m2_t mipp_xorb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_xorb_k_uint32_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint32_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m4_t mipp_xorb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_xorb_k_uint32_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint32_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint32_m8_t mipp_xorb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_xorb_k_uint32_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint32_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint16_t mipp_xorb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_uint16(m0, m1);
#endif
}
rvm_uint16_m1_t mipp_xorb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_xorb_k_uint16(m0, m1);
}
rvm_uint16_m2_t mipp_xorb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_xorb_k_uint16_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint16_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m4_t mipp_xorb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_xorb_k_uint16_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint16_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint16_m8_t mipp_xorb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_xorb_k_uint16_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint16_m4(m0.m2, m1.m2);
	return res;
}
rvm_uint8_t mipp_xorb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX__)
	return mipp_avx_xorb_k_uint8(m0, m1);
#endif
}
rvm_uint8_m1_t mipp_xorb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_xorb_k_uint8(m0, m1);
}
rvm_uint8_m2_t mipp_xorb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_xorb_k_uint8_m1(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint8_m1(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m4_t mipp_xorb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_xorb_k_uint8_m2(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint8_m2(m0.m2, m1.m2);
	return res;
}
rvm_uint8_m8_t mipp_xorb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_xorb_k_uint8_m4(m0.m1, m1.m1);
	res.m2 = mipp_xorb_k_uint8_m4(m0.m2, m1.m2);
	return res;
}
rvd_float64_t mipp_msb_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_float64(r0);
#endif
}
rvd_float64_m1_t mipp_msb_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_msb_float64(r0);
}
rvd_float64_m2_t mipp_msb_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_msb_float64_m1(r0.m1);
	res.m2 = mipp_msb_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_msb_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_msb_float64_m2(r0.m1);
	res.m2 = mipp_msb_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_msb_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_msb_float64_m4(r0.m1);
	res.m2 = mipp_msb_float64_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_msb_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_float32(r0);
#endif
}
rvd_float32_m1_t mipp_msb_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_msb_float32(r0);
}
rvd_float32_m2_t mipp_msb_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_msb_float32_m1(r0.m1);
	res.m2 = mipp_msb_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_msb_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_msb_float32_m2(r0.m1);
	res.m2 = mipp_msb_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_msb_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_msb_float32_m4(r0.m1);
	res.m2 = mipp_msb_float32_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_msb_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_int64(r0);
#endif
}
rvd_int64_m1_t mipp_msb_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_msb_int64(r0);
}
rvd_int64_m2_t mipp_msb_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_msb_int64_m1(r0.m1);
	res.m2 = mipp_msb_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_msb_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_msb_int64_m2(r0.m1);
	res.m2 = mipp_msb_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_msb_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_msb_int64_m4(r0.m1);
	res.m2 = mipp_msb_int64_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_msb_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_int32(r0);
#endif
}
rvd_int32_m1_t mipp_msb_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_msb_int32(r0);
}
rvd_int32_m2_t mipp_msb_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_msb_int32_m1(r0.m1);
	res.m2 = mipp_msb_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_msb_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_msb_int32_m2(r0.m1);
	res.m2 = mipp_msb_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_msb_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_msb_int32_m4(r0.m1);
	res.m2 = mipp_msb_int32_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_msb_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_int16(r0);
#endif
}
rvd_int16_m1_t mipp_msb_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_msb_int16(r0);
}
rvd_int16_m2_t mipp_msb_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_msb_int16_m1(r0.m1);
	res.m2 = mipp_msb_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_msb_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_msb_int16_m2(r0.m1);
	res.m2 = mipp_msb_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_msb_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_msb_int16_m4(r0.m1);
	res.m2 = mipp_msb_int16_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_msb_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_int8(r0);
#endif
}
rvd_int8_m1_t mipp_msb_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_msb_int8(r0);
}
rvd_int8_m2_t mipp_msb_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_msb_int8_m1(r0.m1);
	res.m2 = mipp_msb_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_msb_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_msb_int8_m2(r0.m1);
	res.m2 = mipp_msb_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_msb_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_msb_int8_m4(r0.m1);
	res.m2 = mipp_msb_int8_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_msb_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_msb_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_msb_uint64(r0);
}
rvd_uint64_m2_t mipp_msb_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_msb_uint64_m1(r0.m1);
	res.m2 = mipp_msb_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_msb_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_msb_uint64_m2(r0.m1);
	res.m2 = mipp_msb_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_msb_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_msb_uint64_m4(r0.m1);
	res.m2 = mipp_msb_uint64_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_msb_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_msb_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_msb_uint32(r0);
}
rvd_uint32_m2_t mipp_msb_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_msb_uint32_m1(r0.m1);
	res.m2 = mipp_msb_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_msb_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_msb_uint32_m2(r0.m1);
	res.m2 = mipp_msb_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_msb_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_msb_uint32_m4(r0.m1);
	res.m2 = mipp_msb_uint32_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_msb_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_msb_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_msb_uint16(r0);
}
rvd_uint16_m2_t mipp_msb_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_msb_uint16_m1(r0.m1);
	res.m2 = mipp_msb_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_msb_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_msb_uint16_m2(r0.m1);
	res.m2 = mipp_msb_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_msb_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_msb_uint16_m4(r0.m1);
	res.m2 = mipp_msb_uint16_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_msb_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_msb_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_msb_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_msb_uint8(r0);
}
rvd_uint8_m2_t mipp_msb_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_msb_uint8_m1(r0.m1);
	res.m2 = mipp_msb_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_msb_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_msb_uint8_m2(r0.m1);
	res.m2 = mipp_msb_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_msb_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_msb_uint8_m4(r0.m1);
	res.m2 = mipp_msb_uint8_m4(r0.m2);
	return res;
}
rvd_float64_t mipp_notb_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_float64(r0);
#endif
}
rvd_float64_m1_t mipp_notb_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_notb_float64(r0);
}
rvd_float64_m2_t mipp_notb_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_notb_float64_m1(r0.m1);
	res.m2 = mipp_notb_float64_m1(r0.m2);
	return res;
}
rvd_float64_m4_t mipp_notb_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_notb_float64_m2(r0.m1);
	res.m2 = mipp_notb_float64_m2(r0.m2);
	return res;
}
rvd_float64_m8_t mipp_notb_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_notb_float64_m4(r0.m1);
	res.m2 = mipp_notb_float64_m4(r0.m2);
	return res;
}
rvd_float32_t mipp_notb_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_float32(r0);
#endif
}
rvd_float32_m1_t mipp_notb_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_notb_float32(r0);
}
rvd_float32_m2_t mipp_notb_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_notb_float32_m1(r0.m1);
	res.m2 = mipp_notb_float32_m1(r0.m2);
	return res;
}
rvd_float32_m4_t mipp_notb_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_notb_float32_m2(r0.m1);
	res.m2 = mipp_notb_float32_m2(r0.m2);
	return res;
}
rvd_float32_m8_t mipp_notb_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_notb_float32_m4(r0.m1);
	res.m2 = mipp_notb_float32_m4(r0.m2);
	return res;
}
rvd_int64_t mipp_notb_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_int64(r0);
#endif
}
rvd_int64_m1_t mipp_notb_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_notb_int64(r0);
}
rvd_int64_m2_t mipp_notb_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_notb_int64_m1(r0.m1);
	res.m2 = mipp_notb_int64_m1(r0.m2);
	return res;
}
rvd_int64_m4_t mipp_notb_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_notb_int64_m2(r0.m1);
	res.m2 = mipp_notb_int64_m2(r0.m2);
	return res;
}
rvd_int64_m8_t mipp_notb_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_notb_int64_m4(r0.m1);
	res.m2 = mipp_notb_int64_m4(r0.m2);
	return res;
}
rvd_int32_t mipp_notb_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_int32(r0);
#endif
}
rvd_int32_m1_t mipp_notb_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_notb_int32(r0);
}
rvd_int32_m2_t mipp_notb_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_notb_int32_m1(r0.m1);
	res.m2 = mipp_notb_int32_m1(r0.m2);
	return res;
}
rvd_int32_m4_t mipp_notb_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_notb_int32_m2(r0.m1);
	res.m2 = mipp_notb_int32_m2(r0.m2);
	return res;
}
rvd_int32_m8_t mipp_notb_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_notb_int32_m4(r0.m1);
	res.m2 = mipp_notb_int32_m4(r0.m2);
	return res;
}
rvd_int16_t mipp_notb_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_int16(r0);
#endif
}
rvd_int16_m1_t mipp_notb_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_notb_int16(r0);
}
rvd_int16_m2_t mipp_notb_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_notb_int16_m1(r0.m1);
	res.m2 = mipp_notb_int16_m1(r0.m2);
	return res;
}
rvd_int16_m4_t mipp_notb_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_notb_int16_m2(r0.m1);
	res.m2 = mipp_notb_int16_m2(r0.m2);
	return res;
}
rvd_int16_m8_t mipp_notb_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_notb_int16_m4(r0.m1);
	res.m2 = mipp_notb_int16_m4(r0.m2);
	return res;
}
rvd_int8_t mipp_notb_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_int8(r0);
#endif
}
rvd_int8_m1_t mipp_notb_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_notb_int8(r0);
}
rvd_int8_m2_t mipp_notb_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_notb_int8_m1(r0.m1);
	res.m2 = mipp_notb_int8_m1(r0.m2);
	return res;
}
rvd_int8_m4_t mipp_notb_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_notb_int8_m2(r0.m1);
	res.m2 = mipp_notb_int8_m2(r0.m2);
	return res;
}
rvd_int8_m8_t mipp_notb_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_notb_int8_m4(r0.m1);
	res.m2 = mipp_notb_int8_m4(r0.m2);
	return res;
}
rvd_uint64_t mipp_notb_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_notb_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_notb_uint64(r0);
}
rvd_uint64_m2_t mipp_notb_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_notb_uint64_m1(r0.m1);
	res.m2 = mipp_notb_uint64_m1(r0.m2);
	return res;
}
rvd_uint64_m4_t mipp_notb_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_notb_uint64_m2(r0.m1);
	res.m2 = mipp_notb_uint64_m2(r0.m2);
	return res;
}
rvd_uint64_m8_t mipp_notb_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_notb_uint64_m4(r0.m1);
	res.m2 = mipp_notb_uint64_m4(r0.m2);
	return res;
}
rvd_uint32_t mipp_notb_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_notb_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_notb_uint32(r0);
}
rvd_uint32_m2_t mipp_notb_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_notb_uint32_m1(r0.m1);
	res.m2 = mipp_notb_uint32_m1(r0.m2);
	return res;
}
rvd_uint32_m4_t mipp_notb_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_notb_uint32_m2(r0.m1);
	res.m2 = mipp_notb_uint32_m2(r0.m2);
	return res;
}
rvd_uint32_m8_t mipp_notb_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_notb_uint32_m4(r0.m1);
	res.m2 = mipp_notb_uint32_m4(r0.m2);
	return res;
}
rvd_uint16_t mipp_notb_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_notb_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_notb_uint16(r0);
}
rvd_uint16_m2_t mipp_notb_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_notb_uint16_m1(r0.m1);
	res.m2 = mipp_notb_uint16_m1(r0.m2);
	return res;
}
rvd_uint16_m4_t mipp_notb_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_notb_uint16_m2(r0.m1);
	res.m2 = mipp_notb_uint16_m2(r0.m2);
	return res;
}
rvd_uint16_m8_t mipp_notb_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_notb_uint16_m4(r0.m1);
	res.m2 = mipp_notb_uint16_m4(r0.m2);
	return res;
}
rvd_uint8_t mipp_notb_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_notb_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_notb_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_notb_uint8(r0);
}
rvd_uint8_m2_t mipp_notb_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_notb_uint8_m1(r0.m1);
	res.m2 = mipp_notb_uint8_m1(r0.m2);
	return res;
}
rvd_uint8_m4_t mipp_notb_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_notb_uint8_m2(r0.m1);
	res.m2 = mipp_notb_uint8_m2(r0.m2);
	return res;
}
rvd_uint8_m8_t mipp_notb_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_notb_uint8_m4(r0.m1);
	res.m2 = mipp_notb_uint8_m4(r0.m2);
	return res;
}
rvm_float64_t mipp_notb_k_float64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_float64(m0);
#endif
}
rvm_float64_m1_t mipp_notb_k_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_notb_k_float64(m0);
}
rvm_float64_m2_t mipp_notb_k_float64_m2(const rvm_float64_m2_t m0) {
	rvm_float64_m2_t res;
	res.m1 = mipp_notb_k_float64_m1(m0.m1);
	res.m2 = mipp_notb_k_float64_m1(m0.m2);
	return res;
}
rvm_float64_m4_t mipp_notb_k_float64_m4(const rvm_float64_m4_t m0) {
	rvm_float64_m4_t res;
	res.m1 = mipp_notb_k_float64_m2(m0.m1);
	res.m2 = mipp_notb_k_float64_m2(m0.m2);
	return res;
}
rvm_float64_m8_t mipp_notb_k_float64_m8(const rvm_float64_m8_t m0) {
	rvm_float64_m8_t res;
	res.m1 = mipp_notb_k_float64_m4(m0.m1);
	res.m2 = mipp_notb_k_float64_m4(m0.m2);
	return res;
}
rvm_float32_t mipp_notb_k_float32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_float32(m0);
#endif
}
rvm_float32_m1_t mipp_notb_k_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_notb_k_float32(m0);
}
rvm_float32_m2_t mipp_notb_k_float32_m2(const rvm_float32_m2_t m0) {
	rvm_float32_m2_t res;
	res.m1 = mipp_notb_k_float32_m1(m0.m1);
	res.m2 = mipp_notb_k_float32_m1(m0.m2);
	return res;
}
rvm_float32_m4_t mipp_notb_k_float32_m4(const rvm_float32_m4_t m0) {
	rvm_float32_m4_t res;
	res.m1 = mipp_notb_k_float32_m2(m0.m1);
	res.m2 = mipp_notb_k_float32_m2(m0.m2);
	return res;
}
rvm_float32_m8_t mipp_notb_k_float32_m8(const rvm_float32_m8_t m0) {
	rvm_float32_m8_t res;
	res.m1 = mipp_notb_k_float32_m4(m0.m1);
	res.m2 = mipp_notb_k_float32_m4(m0.m2);
	return res;
}
rvm_int64_t mipp_notb_k_int64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_int64(m0);
#endif
}
rvm_int64_m1_t mipp_notb_k_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_notb_k_int64(m0);
}
rvm_int64_m2_t mipp_notb_k_int64_m2(const rvm_int64_m2_t m0) {
	rvm_int64_m2_t res;
	res.m1 = mipp_notb_k_int64_m1(m0.m1);
	res.m2 = mipp_notb_k_int64_m1(m0.m2);
	return res;
}
rvm_int64_m4_t mipp_notb_k_int64_m4(const rvm_int64_m4_t m0) {
	rvm_int64_m4_t res;
	res.m1 = mipp_notb_k_int64_m2(m0.m1);
	res.m2 = mipp_notb_k_int64_m2(m0.m2);
	return res;
}
rvm_int64_m8_t mipp_notb_k_int64_m8(const rvm_int64_m8_t m0) {
	rvm_int64_m8_t res;
	res.m1 = mipp_notb_k_int64_m4(m0.m1);
	res.m2 = mipp_notb_k_int64_m4(m0.m2);
	return res;
}
rvm_int32_t mipp_notb_k_int32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_int32(m0);
#endif
}
rvm_int32_m1_t mipp_notb_k_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_notb_k_int32(m0);
}
rvm_int32_m2_t mipp_notb_k_int32_m2(const rvm_int32_m2_t m0) {
	rvm_int32_m2_t res;
	res.m1 = mipp_notb_k_int32_m1(m0.m1);
	res.m2 = mipp_notb_k_int32_m1(m0.m2);
	return res;
}
rvm_int32_m4_t mipp_notb_k_int32_m4(const rvm_int32_m4_t m0) {
	rvm_int32_m4_t res;
	res.m1 = mipp_notb_k_int32_m2(m0.m1);
	res.m2 = mipp_notb_k_int32_m2(m0.m2);
	return res;
}
rvm_int32_m8_t mipp_notb_k_int32_m8(const rvm_int32_m8_t m0) {
	rvm_int32_m8_t res;
	res.m1 = mipp_notb_k_int32_m4(m0.m1);
	res.m2 = mipp_notb_k_int32_m4(m0.m2);
	return res;
}
rvm_int16_t mipp_notb_k_int16(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_int16(m0);
#endif
}
rvm_int16_m1_t mipp_notb_k_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_notb_k_int16(m0);
}
rvm_int16_m2_t mipp_notb_k_int16_m2(const rvm_int16_m2_t m0) {
	rvm_int16_m2_t res;
	res.m1 = mipp_notb_k_int16_m1(m0.m1);
	res.m2 = mipp_notb_k_int16_m1(m0.m2);
	return res;
}
rvm_int16_m4_t mipp_notb_k_int16_m4(const rvm_int16_m4_t m0) {
	rvm_int16_m4_t res;
	res.m1 = mipp_notb_k_int16_m2(m0.m1);
	res.m2 = mipp_notb_k_int16_m2(m0.m2);
	return res;
}
rvm_int16_m8_t mipp_notb_k_int16_m8(const rvm_int16_m8_t m0) {
	rvm_int16_m8_t res;
	res.m1 = mipp_notb_k_int16_m4(m0.m1);
	res.m2 = mipp_notb_k_int16_m4(m0.m2);
	return res;
}
rvm_int8_t mipp_notb_k_int8(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_int8(m0);
#endif
}
rvm_int8_m1_t mipp_notb_k_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_notb_k_int8(m0);
}
rvm_int8_m2_t mipp_notb_k_int8_m2(const rvm_int8_m2_t m0) {
	rvm_int8_m2_t res;
	res.m1 = mipp_notb_k_int8_m1(m0.m1);
	res.m2 = mipp_notb_k_int8_m1(m0.m2);
	return res;
}
rvm_int8_m4_t mipp_notb_k_int8_m4(const rvm_int8_m4_t m0) {
	rvm_int8_m4_t res;
	res.m1 = mipp_notb_k_int8_m2(m0.m1);
	res.m2 = mipp_notb_k_int8_m2(m0.m2);
	return res;
}
rvm_int8_m8_t mipp_notb_k_int8_m8(const rvm_int8_m8_t m0) {
	rvm_int8_m8_t res;
	res.m1 = mipp_notb_k_int8_m4(m0.m1);
	res.m2 = mipp_notb_k_int8_m4(m0.m2);
	return res;
}
rvm_uint64_t mipp_notb_k_uint64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_uint64(m0);
#endif
}
rvm_uint64_m1_t mipp_notb_k_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_notb_k_uint64(m0);
}
rvm_uint64_m2_t mipp_notb_k_uint64_m2(const rvm_uint64_m2_t m0) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_notb_k_uint64_m1(m0.m1);
	res.m2 = mipp_notb_k_uint64_m1(m0.m2);
	return res;
}
rvm_uint64_m4_t mipp_notb_k_uint64_m4(const rvm_uint64_m4_t m0) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_notb_k_uint64_m2(m0.m1);
	res.m2 = mipp_notb_k_uint64_m2(m0.m2);
	return res;
}
rvm_uint64_m8_t mipp_notb_k_uint64_m8(const rvm_uint64_m8_t m0) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_notb_k_uint64_m4(m0.m1);
	res.m2 = mipp_notb_k_uint64_m4(m0.m2);
	return res;
}
rvm_uint32_t mipp_notb_k_uint32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_uint32(m0);
#endif
}
rvm_uint32_m1_t mipp_notb_k_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_notb_k_uint32(m0);
}
rvm_uint32_m2_t mipp_notb_k_uint32_m2(const rvm_uint32_m2_t m0) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_notb_k_uint32_m1(m0.m1);
	res.m2 = mipp_notb_k_uint32_m1(m0.m2);
	return res;
}
rvm_uint32_m4_t mipp_notb_k_uint32_m4(const rvm_uint32_m4_t m0) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_notb_k_uint32_m2(m0.m1);
	res.m2 = mipp_notb_k_uint32_m2(m0.m2);
	return res;
}
rvm_uint32_m8_t mipp_notb_k_uint32_m8(const rvm_uint32_m8_t m0) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_notb_k_uint32_m4(m0.m1);
	res.m2 = mipp_notb_k_uint32_m4(m0.m2);
	return res;
}
rvm_uint16_t mipp_notb_k_uint16(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_uint16(m0);
#endif
}
rvm_uint16_m1_t mipp_notb_k_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_notb_k_uint16(m0);
}
rvm_uint16_m2_t mipp_notb_k_uint16_m2(const rvm_uint16_m2_t m0) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_notb_k_uint16_m1(m0.m1);
	res.m2 = mipp_notb_k_uint16_m1(m0.m2);
	return res;
}
rvm_uint16_m4_t mipp_notb_k_uint16_m4(const rvm_uint16_m4_t m0) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_notb_k_uint16_m2(m0.m1);
	res.m2 = mipp_notb_k_uint16_m2(m0.m2);
	return res;
}
rvm_uint16_m8_t mipp_notb_k_uint16_m8(const rvm_uint16_m8_t m0) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_notb_k_uint16_m4(m0.m1);
	res.m2 = mipp_notb_k_uint16_m4(m0.m2);
	return res;
}
rvm_uint8_t mipp_notb_k_uint8(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_notb_k_uint8(m0);
#endif
}
rvm_uint8_m1_t mipp_notb_k_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_notb_k_uint8(m0);
}
rvm_uint8_m2_t mipp_notb_k_uint8_m2(const rvm_uint8_m2_t m0) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_notb_k_uint8_m1(m0.m1);
	res.m2 = mipp_notb_k_uint8_m1(m0.m2);
	return res;
}
rvm_uint8_m4_t mipp_notb_k_uint8_m4(const rvm_uint8_m4_t m0) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_notb_k_uint8_m2(m0.m1);
	res.m2 = mipp_notb_k_uint8_m2(m0.m2);
	return res;
}
rvm_uint8_m8_t mipp_notb_k_uint8_m8(const rvm_uint8_m8_t m0) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_notb_k_uint8_m4(m0.m1);
	res.m2 = mipp_notb_k_uint8_m4(m0.m2);
	return res;
}
rvm_float64_t mipp_cmpeq_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_float64(r0, r1);
#endif
}
rvm_float64_m1_t mipp_cmpeq_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpeq_float64(r0, r1);
}
rvm_float64_m2_t mipp_cmpeq_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cmpeq_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float64_m1(r0.m2, r1.m2);
	return res;
}
rvm_float64_m4_t mipp_cmpeq_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cmpeq_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float64_m2(r0.m2, r1.m2);
	return res;
}
rvm_float64_m8_t mipp_cmpeq_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cmpeq_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float64_m4(r0.m2, r1.m2);
	return res;
}
rvm_float32_t mipp_cmpeq_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_float32(r0, r1);
#endif
}
rvm_float32_m1_t mipp_cmpeq_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpeq_float32(r0, r1);
}
rvm_float32_m2_t mipp_cmpeq_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cmpeq_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float32_m1(r0.m2, r1.m2);
	return res;
}
rvm_float32_m4_t mipp_cmpeq_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cmpeq_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float32_m2(r0.m2, r1.m2);
	return res;
}
rvm_float32_m8_t mipp_cmpeq_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cmpeq_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_float32_m4(r0.m2, r1.m2);
	return res;
}
rvm_int64_t mipp_cmpeq_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_int64(r0, r1);
#endif
}
rvm_int64_m1_t mipp_cmpeq_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpeq_int64(r0, r1);
}
rvm_int64_m2_t mipp_cmpeq_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cmpeq_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int64_m1(r0.m2, r1.m2);
	return res;
}
rvm_int64_m4_t mipp_cmpeq_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cmpeq_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int64_m2(r0.m2, r1.m2);
	return res;
}
rvm_int64_m8_t mipp_cmpeq_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cmpeq_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int64_m4(r0.m2, r1.m2);
	return res;
}
rvm_int32_t mipp_cmpeq_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_int32(r0, r1);
#endif
}
rvm_int32_m1_t mipp_cmpeq_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpeq_int32(r0, r1);
}
rvm_int32_m2_t mipp_cmpeq_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cmpeq_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int32_m1(r0.m2, r1.m2);
	return res;
}
rvm_int32_m4_t mipp_cmpeq_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cmpeq_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int32_m2(r0.m2, r1.m2);
	return res;
}
rvm_int32_m8_t mipp_cmpeq_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cmpeq_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int32_m4(r0.m2, r1.m2);
	return res;
}
rvm_int16_t mipp_cmpeq_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_int16(r0, r1);
#endif
}
rvm_int16_m1_t mipp_cmpeq_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpeq_int16(r0, r1);
}
rvm_int16_m2_t mipp_cmpeq_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cmpeq_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int16_m1(r0.m2, r1.m2);
	return res;
}
rvm_int16_m4_t mipp_cmpeq_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cmpeq_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int16_m2(r0.m2, r1.m2);
	return res;
}
rvm_int16_m8_t mipp_cmpeq_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cmpeq_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int16_m4(r0.m2, r1.m2);
	return res;
}
rvm_int8_t mipp_cmpeq_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_int8(r0, r1);
#endif
}
rvm_int8_m1_t mipp_cmpeq_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpeq_int8(r0, r1);
}
rvm_int8_m2_t mipp_cmpeq_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cmpeq_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int8_m1(r0.m2, r1.m2);
	return res;
}
rvm_int8_m4_t mipp_cmpeq_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cmpeq_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int8_m2(r0.m2, r1.m2);
	return res;
}
rvm_int8_m8_t mipp_cmpeq_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cmpeq_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_int8_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint64_t mipp_cmpeq_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_uint64(r0, r1);
#endif
}
rvm_uint64_m1_t mipp_cmpeq_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpeq_uint64(r0, r1);
}
rvm_uint64_m2_t mipp_cmpeq_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cmpeq_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint64_m4_t mipp_cmpeq_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cmpeq_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint64_m8_t mipp_cmpeq_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cmpeq_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint32_t mipp_cmpeq_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_uint32(r0, r1);
#endif
}
rvm_uint32_m1_t mipp_cmpeq_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpeq_uint32(r0, r1);
}
rvm_uint32_m2_t mipp_cmpeq_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cmpeq_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint32_m4_t mipp_cmpeq_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cmpeq_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint32_m8_t mipp_cmpeq_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cmpeq_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint16_t mipp_cmpeq_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_uint16(r0, r1);
#endif
}
rvm_uint16_m1_t mipp_cmpeq_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpeq_uint16(r0, r1);
}
rvm_uint16_m2_t mipp_cmpeq_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cmpeq_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint16_m4_t mipp_cmpeq_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cmpeq_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint16_m8_t mipp_cmpeq_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cmpeq_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint8_t mipp_cmpeq_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpeq_uint8(r0, r1);
#endif
}
rvm_uint8_m1_t mipp_cmpeq_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpeq_uint8(r0, r1);
}
rvm_uint8_m2_t mipp_cmpeq_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cmpeq_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint8_m4_t mipp_cmpeq_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cmpeq_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint8_m8_t mipp_cmpeq_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cmpeq_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpeq_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvm_float64_t mipp_cmpneq_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_float64(r0, r1);
#endif
}
rvm_float64_m1_t mipp_cmpneq_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpneq_float64(r0, r1);
}
rvm_float64_m2_t mipp_cmpneq_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t res;
	res.m1 = mipp_cmpneq_float64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float64_m1(r0.m2, r1.m2);
	return res;
}
rvm_float64_m4_t mipp_cmpneq_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t res;
	res.m1 = mipp_cmpneq_float64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float64_m2(r0.m2, r1.m2);
	return res;
}
rvm_float64_m8_t mipp_cmpneq_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t res;
	res.m1 = mipp_cmpneq_float64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float64_m4(r0.m2, r1.m2);
	return res;
}
rvm_float32_t mipp_cmpneq_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_float32(r0, r1);
#endif
}
rvm_float32_m1_t mipp_cmpneq_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpneq_float32(r0, r1);
}
rvm_float32_m2_t mipp_cmpneq_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t res;
	res.m1 = mipp_cmpneq_float32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float32_m1(r0.m2, r1.m2);
	return res;
}
rvm_float32_m4_t mipp_cmpneq_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t res;
	res.m1 = mipp_cmpneq_float32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float32_m2(r0.m2, r1.m2);
	return res;
}
rvm_float32_m8_t mipp_cmpneq_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t res;
	res.m1 = mipp_cmpneq_float32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_float32_m4(r0.m2, r1.m2);
	return res;
}
rvm_int64_t mipp_cmpneq_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_int64(r0, r1);
#endif
}
rvm_int64_m1_t mipp_cmpneq_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpneq_int64(r0, r1);
}
rvm_int64_m2_t mipp_cmpneq_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t res;
	res.m1 = mipp_cmpneq_int64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int64_m1(r0.m2, r1.m2);
	return res;
}
rvm_int64_m4_t mipp_cmpneq_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t res;
	res.m1 = mipp_cmpneq_int64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int64_m2(r0.m2, r1.m2);
	return res;
}
rvm_int64_m8_t mipp_cmpneq_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t res;
	res.m1 = mipp_cmpneq_int64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int64_m4(r0.m2, r1.m2);
	return res;
}
rvm_int32_t mipp_cmpneq_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_int32(r0, r1);
#endif
}
rvm_int32_m1_t mipp_cmpneq_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpneq_int32(r0, r1);
}
rvm_int32_m2_t mipp_cmpneq_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t res;
	res.m1 = mipp_cmpneq_int32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int32_m1(r0.m2, r1.m2);
	return res;
}
rvm_int32_m4_t mipp_cmpneq_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t res;
	res.m1 = mipp_cmpneq_int32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int32_m2(r0.m2, r1.m2);
	return res;
}
rvm_int32_m8_t mipp_cmpneq_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t res;
	res.m1 = mipp_cmpneq_int32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int32_m4(r0.m2, r1.m2);
	return res;
}
rvm_int16_t mipp_cmpneq_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_int16(r0, r1);
#endif
}
rvm_int16_m1_t mipp_cmpneq_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpneq_int16(r0, r1);
}
rvm_int16_m2_t mipp_cmpneq_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t res;
	res.m1 = mipp_cmpneq_int16_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int16_m1(r0.m2, r1.m2);
	return res;
}
rvm_int16_m4_t mipp_cmpneq_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t res;
	res.m1 = mipp_cmpneq_int16_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int16_m2(r0.m2, r1.m2);
	return res;
}
rvm_int16_m8_t mipp_cmpneq_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t res;
	res.m1 = mipp_cmpneq_int16_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int16_m4(r0.m2, r1.m2);
	return res;
}
rvm_int8_t mipp_cmpneq_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_int8(r0, r1);
#endif
}
rvm_int8_m1_t mipp_cmpneq_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpneq_int8(r0, r1);
}
rvm_int8_m2_t mipp_cmpneq_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t res;
	res.m1 = mipp_cmpneq_int8_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int8_m1(r0.m2, r1.m2);
	return res;
}
rvm_int8_m4_t mipp_cmpneq_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t res;
	res.m1 = mipp_cmpneq_int8_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int8_m2(r0.m2, r1.m2);
	return res;
}
rvm_int8_m8_t mipp_cmpneq_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t res;
	res.m1 = mipp_cmpneq_int8_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_int8_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint64_t mipp_cmpneq_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_uint64(r0, r1);
#endif
}
rvm_uint64_m1_t mipp_cmpneq_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpneq_uint64(r0, r1);
}
rvm_uint64_m2_t mipp_cmpneq_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t res;
	res.m1 = mipp_cmpneq_uint64_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint64_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint64_m4_t mipp_cmpneq_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t res;
	res.m1 = mipp_cmpneq_uint64_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint64_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint64_m8_t mipp_cmpneq_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t res;
	res.m1 = mipp_cmpneq_uint64_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint64_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint32_t mipp_cmpneq_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_uint32(r0, r1);
#endif
}
rvm_uint32_m1_t mipp_cmpneq_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpneq_uint32(r0, r1);
}
rvm_uint32_m2_t mipp_cmpneq_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t res;
	res.m1 = mipp_cmpneq_uint32_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint32_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint32_m4_t mipp_cmpneq_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t res;
	res.m1 = mipp_cmpneq_uint32_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint32_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint32_m8_t mipp_cmpneq_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t res;
	res.m1 = mipp_cmpneq_uint32_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint32_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint16_t mipp_cmpneq_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_uint16(r0, r1);
#endif
}
rvm_uint16_m1_t mipp_cmpneq_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpneq_uint16(r0, r1);
}
rvm_uint16_m2_t mipp_cmpneq_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t res;
	res.m1 = mipp_cmpneq_uint16_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint16_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint16_m4_t mipp_cmpneq_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t res;
	res.m1 = mipp_cmpneq_uint16_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint16_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint16_m8_t mipp_cmpneq_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t res;
	res.m1 = mipp_cmpneq_uint16_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint16_m4(r0.m2, r1.m2);
	return res;
}
rvm_uint8_t mipp_cmpneq_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX__)
	return mipp_avx_cmpneq_uint8(r0, r1);
#endif
}
rvm_uint8_m1_t mipp_cmpneq_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpneq_uint8(r0, r1);
}
rvm_uint8_m2_t mipp_cmpneq_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t res;
	res.m1 = mipp_cmpneq_uint8_m1(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint8_m1(r0.m2, r1.m2);
	return res;
}
rvm_uint8_m4_t mipp_cmpneq_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t res;
	res.m1 = mipp_cmpneq_uint8_m2(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint8_m2(r0.m2, r1.m2);
	return res;
}
rvm_uint8_m8_t mipp_cmpneq_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t res;
	res.m1 = mipp_cmpneq_uint8_m4(r0.m1, r1.m1);
	res.m2 = mipp_cmpneq_uint8_m4(r0.m2, r1.m2);
	return res;
}
rvd_float64_t mipp_blend_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_float64(r0, r1, m0);
#endif
}
rvd_float64_m1_t mipp_blend_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_blend_float64(r0, r1, m0);
}
rvd_float64_m2_t mipp_blend_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.m1 = mipp_blend_float64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m4_t mipp_blend_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.m1 = mipp_blend_float64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_m8_t mipp_blend_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.m1 = mipp_blend_float64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_t mipp_blend_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_float32(r0, r1, m0);
#endif
}
rvd_float32_m1_t mipp_blend_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_blend_float32(r0, r1, m0);
}
rvd_float32_m2_t mipp_blend_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.m1 = mipp_blend_float32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m4_t mipp_blend_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.m1 = mipp_blend_float32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float32_m8_t mipp_blend_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.m1 = mipp_blend_float32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_float32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_t mipp_blend_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_int64(r0, r1, m0);
#endif
}
rvd_int64_m1_t mipp_blend_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_blend_int64(r0, r1, m0);
}
rvd_int64_m2_t mipp_blend_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.m1 = mipp_blend_int64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m4_t mipp_blend_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.m1 = mipp_blend_int64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int64_m8_t mipp_blend_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.m1 = mipp_blend_int64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_t mipp_blend_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_int32(r0, r1, m0);
#endif
}
rvd_int32_m1_t mipp_blend_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_blend_int32(r0, r1, m0);
}
rvd_int32_m2_t mipp_blend_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.m1 = mipp_blend_int32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m4_t mipp_blend_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.m1 = mipp_blend_int32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int32_m8_t mipp_blend_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.m1 = mipp_blend_int32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_t mipp_blend_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_int16(r0, r1, m0);
#endif
}
rvd_int16_m1_t mipp_blend_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_blend_int16(r0, r1, m0);
}
rvd_int16_m2_t mipp_blend_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.m1 = mipp_blend_int16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m4_t mipp_blend_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.m1 = mipp_blend_int16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int16_m8_t mipp_blend_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.m1 = mipp_blend_int16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_t mipp_blend_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_int8(r0, r1, m0);
#endif
}
rvd_int8_m1_t mipp_blend_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_blend_int8(r0, r1, m0);
}
rvd_int8_m2_t mipp_blend_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.m1 = mipp_blend_int8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m4_t mipp_blend_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.m1 = mipp_blend_int8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_int8_m8_t mipp_blend_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.m1 = mipp_blend_int8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_int8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_t mipp_blend_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_uint64(r0, r1, m0);
#endif
}
rvd_uint64_m1_t mipp_blend_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_blend_uint64(r0, r1, m0);
}
rvd_uint64_m2_t mipp_blend_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_blend_uint64_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint64_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m4_t mipp_blend_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_blend_uint64_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint64_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint64_m8_t mipp_blend_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_blend_uint64_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint64_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_t mipp_blend_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_uint32(r0, r1, m0);
#endif
}
rvd_uint32_m1_t mipp_blend_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_blend_uint32(r0, r1, m0);
}
rvd_uint32_m2_t mipp_blend_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_blend_uint32_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint32_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m4_t mipp_blend_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_blend_uint32_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint32_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint32_m8_t mipp_blend_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_blend_uint32_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint32_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_t mipp_blend_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_uint16(r0, r1, m0);
#endif
}
rvd_uint16_m1_t mipp_blend_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_blend_uint16(r0, r1, m0);
}
rvd_uint16_m2_t mipp_blend_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_blend_uint16_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint16_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m4_t mipp_blend_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_blend_uint16_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint16_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint16_m8_t mipp_blend_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_blend_uint16_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint16_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_t mipp_blend_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_blend_uint8(r0, r1, m0);
#endif
}
rvd_uint8_m1_t mipp_blend_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_blend_uint8(r0, r1, m0);
}
rvd_uint8_m2_t mipp_blend_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_blend_uint8_m1(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint8_m1(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m4_t mipp_blend_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_blend_uint8_m2(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint8_m2(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_uint8_m8_t mipp_blend_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_blend_uint8_m4(r0.m1, r1.m1, m0.m1);
	res.m2 = mipp_blend_uint8_m4(r0.m2, r1.m2, m0.m2);
	return res;
}
rvd_float64_t mipp_sat_float64(const rvd_float64_t r0, const float64_t v0, const float64_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_float64(r0, v0, v1);
#endif
}
rvd_float64_m1_t mipp_sat_float64_m1(const rvd_float64_m1_t r0, const float64_t v0, const float64_t v1) {
	return mipp_sat_float64(r0, v0, v1);
}
rvd_float64_m2_t mipp_sat_float64_m2(const rvd_float64_m2_t r0, const float64_t v0, const float64_t v1) {
	rvd_float64_m2_t res;
	res.m1 = mipp_sat_float64_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_float64_m1(r0.m2, v0, v1);
	return res;
}
rvd_float64_m4_t mipp_sat_float64_m4(const rvd_float64_m4_t r0, const float64_t v0, const float64_t v1) {
	rvd_float64_m4_t res;
	res.m1 = mipp_sat_float64_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_float64_m2(r0.m2, v0, v1);
	return res;
}
rvd_float64_m8_t mipp_sat_float64_m8(const rvd_float64_m8_t r0, const float64_t v0, const float64_t v1) {
	rvd_float64_m8_t res;
	res.m1 = mipp_sat_float64_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_float64_m4(r0.m2, v0, v1);
	return res;
}
rvd_float32_t mipp_sat_float32(const rvd_float32_t r0, const float32_t v0, const float32_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_float32(r0, v0, v1);
#endif
}
rvd_float32_m1_t mipp_sat_float32_m1(const rvd_float32_m1_t r0, const float32_t v0, const float32_t v1) {
	return mipp_sat_float32(r0, v0, v1);
}
rvd_float32_m2_t mipp_sat_float32_m2(const rvd_float32_m2_t r0, const float32_t v0, const float32_t v1) {
	rvd_float32_m2_t res;
	res.m1 = mipp_sat_float32_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_float32_m1(r0.m2, v0, v1);
	return res;
}
rvd_float32_m4_t mipp_sat_float32_m4(const rvd_float32_m4_t r0, const float32_t v0, const float32_t v1) {
	rvd_float32_m4_t res;
	res.m1 = mipp_sat_float32_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_float32_m2(r0.m2, v0, v1);
	return res;
}
rvd_float32_m8_t mipp_sat_float32_m8(const rvd_float32_m8_t r0, const float32_t v0, const float32_t v1) {
	rvd_float32_m8_t res;
	res.m1 = mipp_sat_float32_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_float32_m4(r0.m2, v0, v1);
	return res;
}
rvd_int64_t mipp_sat_int64(const rvd_int64_t r0, const int64_t v0, const int64_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_int64(r0, v0, v1);
#endif
}
rvd_int64_m1_t mipp_sat_int64_m1(const rvd_int64_m1_t r0, const int64_t v0, const int64_t v1) {
	return mipp_sat_int64(r0, v0, v1);
}
rvd_int64_m2_t mipp_sat_int64_m2(const rvd_int64_m2_t r0, const int64_t v0, const int64_t v1) {
	rvd_int64_m2_t res;
	res.m1 = mipp_sat_int64_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_int64_m1(r0.m2, v0, v1);
	return res;
}
rvd_int64_m4_t mipp_sat_int64_m4(const rvd_int64_m4_t r0, const int64_t v0, const int64_t v1) {
	rvd_int64_m4_t res;
	res.m1 = mipp_sat_int64_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_int64_m2(r0.m2, v0, v1);
	return res;
}
rvd_int64_m8_t mipp_sat_int64_m8(const rvd_int64_m8_t r0, const int64_t v0, const int64_t v1) {
	rvd_int64_m8_t res;
	res.m1 = mipp_sat_int64_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_int64_m4(r0.m2, v0, v1);
	return res;
}
rvd_int32_t mipp_sat_int32(const rvd_int32_t r0, const int32_t v0, const int32_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_int32(r0, v0, v1);
#endif
}
rvd_int32_m1_t mipp_sat_int32_m1(const rvd_int32_m1_t r0, const int32_t v0, const int32_t v1) {
	return mipp_sat_int32(r0, v0, v1);
}
rvd_int32_m2_t mipp_sat_int32_m2(const rvd_int32_m2_t r0, const int32_t v0, const int32_t v1) {
	rvd_int32_m2_t res;
	res.m1 = mipp_sat_int32_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_int32_m1(r0.m2, v0, v1);
	return res;
}
rvd_int32_m4_t mipp_sat_int32_m4(const rvd_int32_m4_t r0, const int32_t v0, const int32_t v1) {
	rvd_int32_m4_t res;
	res.m1 = mipp_sat_int32_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_int32_m2(r0.m2, v0, v1);
	return res;
}
rvd_int32_m8_t mipp_sat_int32_m8(const rvd_int32_m8_t r0, const int32_t v0, const int32_t v1) {
	rvd_int32_m8_t res;
	res.m1 = mipp_sat_int32_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_int32_m4(r0.m2, v0, v1);
	return res;
}
rvd_int16_t mipp_sat_int16(const rvd_int16_t r0, const int16_t v0, const int16_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_int16(r0, v0, v1);
#endif
}
rvd_int16_m1_t mipp_sat_int16_m1(const rvd_int16_m1_t r0, const int16_t v0, const int16_t v1) {
	return mipp_sat_int16(r0, v0, v1);
}
rvd_int16_m2_t mipp_sat_int16_m2(const rvd_int16_m2_t r0, const int16_t v0, const int16_t v1) {
	rvd_int16_m2_t res;
	res.m1 = mipp_sat_int16_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_int16_m1(r0.m2, v0, v1);
	return res;
}
rvd_int16_m4_t mipp_sat_int16_m4(const rvd_int16_m4_t r0, const int16_t v0, const int16_t v1) {
	rvd_int16_m4_t res;
	res.m1 = mipp_sat_int16_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_int16_m2(r0.m2, v0, v1);
	return res;
}
rvd_int16_m8_t mipp_sat_int16_m8(const rvd_int16_m8_t r0, const int16_t v0, const int16_t v1) {
	rvd_int16_m8_t res;
	res.m1 = mipp_sat_int16_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_int16_m4(r0.m2, v0, v1);
	return res;
}
rvd_int8_t mipp_sat_int8(const rvd_int8_t r0, const int8_t v0, const int8_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_int8(r0, v0, v1);
#endif
}
rvd_int8_m1_t mipp_sat_int8_m1(const rvd_int8_m1_t r0, const int8_t v0, const int8_t v1) {
	return mipp_sat_int8(r0, v0, v1);
}
rvd_int8_m2_t mipp_sat_int8_m2(const rvd_int8_m2_t r0, const int8_t v0, const int8_t v1) {
	rvd_int8_m2_t res;
	res.m1 = mipp_sat_int8_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_int8_m1(r0.m2, v0, v1);
	return res;
}
rvd_int8_m4_t mipp_sat_int8_m4(const rvd_int8_m4_t r0, const int8_t v0, const int8_t v1) {
	rvd_int8_m4_t res;
	res.m1 = mipp_sat_int8_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_int8_m2(r0.m2, v0, v1);
	return res;
}
rvd_int8_m8_t mipp_sat_int8_m8(const rvd_int8_m8_t r0, const int8_t v0, const int8_t v1) {
	rvd_int8_m8_t res;
	res.m1 = mipp_sat_int8_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_int8_m4(r0.m2, v0, v1);
	return res;
}
rvd_uint64_t mipp_sat_uint64(const rvd_uint64_t r0, const uint64_t v0, const uint64_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_uint64(r0, v0, v1);
#endif
}
rvd_uint64_m1_t mipp_sat_uint64_m1(const rvd_uint64_m1_t r0, const uint64_t v0, const uint64_t v1) {
	return mipp_sat_uint64(r0, v0, v1);
}
rvd_uint64_m2_t mipp_sat_uint64_m2(const rvd_uint64_m2_t r0, const uint64_t v0, const uint64_t v1) {
	rvd_uint64_m2_t res;
	res.m1 = mipp_sat_uint64_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint64_m1(r0.m2, v0, v1);
	return res;
}
rvd_uint64_m4_t mipp_sat_uint64_m4(const rvd_uint64_m4_t r0, const uint64_t v0, const uint64_t v1) {
	rvd_uint64_m4_t res;
	res.m1 = mipp_sat_uint64_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint64_m2(r0.m2, v0, v1);
	return res;
}
rvd_uint64_m8_t mipp_sat_uint64_m8(const rvd_uint64_m8_t r0, const uint64_t v0, const uint64_t v1) {
	rvd_uint64_m8_t res;
	res.m1 = mipp_sat_uint64_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint64_m4(r0.m2, v0, v1);
	return res;
}
rvd_uint32_t mipp_sat_uint32(const rvd_uint32_t r0, const uint32_t v0, const uint32_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_uint32(r0, v0, v1);
#endif
}
rvd_uint32_m1_t mipp_sat_uint32_m1(const rvd_uint32_m1_t r0, const uint32_t v0, const uint32_t v1) {
	return mipp_sat_uint32(r0, v0, v1);
}
rvd_uint32_m2_t mipp_sat_uint32_m2(const rvd_uint32_m2_t r0, const uint32_t v0, const uint32_t v1) {
	rvd_uint32_m2_t res;
	res.m1 = mipp_sat_uint32_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint32_m1(r0.m2, v0, v1);
	return res;
}
rvd_uint32_m4_t mipp_sat_uint32_m4(const rvd_uint32_m4_t r0, const uint32_t v0, const uint32_t v1) {
	rvd_uint32_m4_t res;
	res.m1 = mipp_sat_uint32_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint32_m2(r0.m2, v0, v1);
	return res;
}
rvd_uint32_m8_t mipp_sat_uint32_m8(const rvd_uint32_m8_t r0, const uint32_t v0, const uint32_t v1) {
	rvd_uint32_m8_t res;
	res.m1 = mipp_sat_uint32_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint32_m4(r0.m2, v0, v1);
	return res;
}
rvd_uint16_t mipp_sat_uint16(const rvd_uint16_t r0, const uint16_t v0, const uint16_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_uint16(r0, v0, v1);
#endif
}
rvd_uint16_m1_t mipp_sat_uint16_m1(const rvd_uint16_m1_t r0, const uint16_t v0, const uint16_t v1) {
	return mipp_sat_uint16(r0, v0, v1);
}
rvd_uint16_m2_t mipp_sat_uint16_m2(const rvd_uint16_m2_t r0, const uint16_t v0, const uint16_t v1) {
	rvd_uint16_m2_t res;
	res.m1 = mipp_sat_uint16_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint16_m1(r0.m2, v0, v1);
	return res;
}
rvd_uint16_m4_t mipp_sat_uint16_m4(const rvd_uint16_m4_t r0, const uint16_t v0, const uint16_t v1) {
	rvd_uint16_m4_t res;
	res.m1 = mipp_sat_uint16_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint16_m2(r0.m2, v0, v1);
	return res;
}
rvd_uint16_m8_t mipp_sat_uint16_m8(const rvd_uint16_m8_t r0, const uint16_t v0, const uint16_t v1) {
	rvd_uint16_m8_t res;
	res.m1 = mipp_sat_uint16_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint16_m4(r0.m2, v0, v1);
	return res;
}
rvd_uint8_t mipp_sat_uint8(const rvd_uint8_t r0, const uint8_t v0, const uint8_t v1) {
#if defined(__AVX__)
	return mipp_avx_sat_uint8(r0, v0, v1);
#endif
}
rvd_uint8_m1_t mipp_sat_uint8_m1(const rvd_uint8_m1_t r0, const uint8_t v0, const uint8_t v1) {
	return mipp_sat_uint8(r0, v0, v1);
}
rvd_uint8_m2_t mipp_sat_uint8_m2(const rvd_uint8_m2_t r0, const uint8_t v0, const uint8_t v1) {
	rvd_uint8_m2_t res;
	res.m1 = mipp_sat_uint8_m1(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint8_m1(r0.m2, v0, v1);
	return res;
}
rvd_uint8_m4_t mipp_sat_uint8_m4(const rvd_uint8_m4_t r0, const uint8_t v0, const uint8_t v1) {
	rvd_uint8_m4_t res;
	res.m1 = mipp_sat_uint8_m2(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint8_m2(r0.m2, v0, v1);
	return res;
}
rvd_uint8_m8_t mipp_sat_uint8_m8(const rvd_uint8_m8_t r0, const uint8_t v0, const uint8_t v1) {
	rvd_uint8_m8_t res;
	res.m1 = mipp_sat_uint8_m4(r0.m1, v0, v1);
	res.m2 = mipp_sat_uint8_m4(r0.m2, v0, v1);
	return res;
}
int32_t mipp_testz_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_float64(m0, m1);
#endif
}
int32_t mipp_testz_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_testz_float64(m0, m1);
}
int32_t mipp_testz_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m2");
	exit(-1);
}
int32_t mipp_testz_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m4");
	exit(-1);
}
int32_t mipp_testz_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m8");
	exit(-1);
}
int32_t mipp_testz_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_float32(m0, m1);
#endif
}
int32_t mipp_testz_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_testz_float32(m0, m1);
}
int32_t mipp_testz_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m2");
	exit(-1);
}
int32_t mipp_testz_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m4");
	exit(-1);
}
int32_t mipp_testz_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m8");
	exit(-1);
}
int32_t mipp_testz_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_int64(m0, m1);
#endif
}
int32_t mipp_testz_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_testz_int64(m0, m1);
}
int32_t mipp_testz_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m2");
	exit(-1);
}
int32_t mipp_testz_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m4");
	exit(-1);
}
int32_t mipp_testz_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m8");
	exit(-1);
}
int32_t mipp_testz_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_int32(m0, m1);
#endif
}
int32_t mipp_testz_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_testz_int32(m0, m1);
}
int32_t mipp_testz_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m2");
	exit(-1);
}
int32_t mipp_testz_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m4");
	exit(-1);
}
int32_t mipp_testz_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m8");
	exit(-1);
}
int32_t mipp_testz_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_int16(m0, m1);
#endif
}
int32_t mipp_testz_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_testz_int16(m0, m1);
}
int32_t mipp_testz_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m2");
	exit(-1);
}
int32_t mipp_testz_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m4");
	exit(-1);
}
int32_t mipp_testz_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m8");
	exit(-1);
}
int32_t mipp_testz_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_int8(m0, m1);
#endif
}
int32_t mipp_testz_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_testz_int8(m0, m1);
}
int32_t mipp_testz_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m2");
	exit(-1);
}
int32_t mipp_testz_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m4");
	exit(-1);
}
int32_t mipp_testz_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m8");
	exit(-1);
}
int32_t mipp_testz_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_uint64(m0, m1);
#endif
}
int32_t mipp_testz_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_testz_uint64(m0, m1);
}
int32_t mipp_testz_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m2");
	exit(-1);
}
int32_t mipp_testz_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m4");
	exit(-1);
}
int32_t mipp_testz_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m8");
	exit(-1);
}
int32_t mipp_testz_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_uint32(m0, m1);
#endif
}
int32_t mipp_testz_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_testz_uint32(m0, m1);
}
int32_t mipp_testz_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m2");
	exit(-1);
}
int32_t mipp_testz_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m4");
	exit(-1);
}
int32_t mipp_testz_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m8");
	exit(-1);
}
int32_t mipp_testz_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_uint16(m0, m1);
#endif
}
int32_t mipp_testz_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_testz_uint16(m0, m1);
}
int32_t mipp_testz_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m2");
	exit(-1);
}
int32_t mipp_testz_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m4");
	exit(-1);
}
int32_t mipp_testz_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m8");
	exit(-1);
}
int32_t mipp_testz_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX__)
	return mipp_avx_testz_uint8(m0, m1);
#endif
}
int32_t mipp_testz_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_testz_uint8(m0, m1);
}
int32_t mipp_testz_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m2");
	exit(-1);
}
int32_t mipp_testz_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m4");
	exit(-1);
}
int32_t mipp_testz_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m8");
	exit(-1);
}
int32_t mipp_testz_2_float64(const rvm_float64_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_float64(m0);
#endif
}
int32_t mipp_testz_2_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_testz_2_float64(m0);
}
int32_t mipp_testz_2_float64_m2(const rvm_float64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m2");
	exit(-1);
}
int32_t mipp_testz_2_float64_m4(const rvm_float64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m4");
	exit(-1);
}
int32_t mipp_testz_2_float64_m8(const rvm_float64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m8");
	exit(-1);
}
int32_t mipp_testz_2_float32(const rvm_float32_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_float32(m0);
#endif
}
int32_t mipp_testz_2_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_testz_2_float32(m0);
}
int32_t mipp_testz_2_float32_m2(const rvm_float32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m2");
	exit(-1);
}
int32_t mipp_testz_2_float32_m4(const rvm_float32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m4");
	exit(-1);
}
int32_t mipp_testz_2_float32_m8(const rvm_float32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m8");
	exit(-1);
}
int32_t mipp_testz_2_int64(const rvm_int64_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_int64(m0);
#endif
}
int32_t mipp_testz_2_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_testz_2_int64(m0);
}
int32_t mipp_testz_2_int64_m2(const rvm_int64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m2");
	exit(-1);
}
int32_t mipp_testz_2_int64_m4(const rvm_int64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m4");
	exit(-1);
}
int32_t mipp_testz_2_int64_m8(const rvm_int64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m8");
	exit(-1);
}
int32_t mipp_testz_2_int32(const rvm_int32_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_int32(m0);
#endif
}
int32_t mipp_testz_2_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_testz_2_int32(m0);
}
int32_t mipp_testz_2_int32_m2(const rvm_int32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m2");
	exit(-1);
}
int32_t mipp_testz_2_int32_m4(const rvm_int32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m4");
	exit(-1);
}
int32_t mipp_testz_2_int32_m8(const rvm_int32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m8");
	exit(-1);
}
int32_t mipp_testz_2_int16(const rvm_int16_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_int16(m0);
#endif
}
int32_t mipp_testz_2_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_testz_2_int16(m0);
}
int32_t mipp_testz_2_int16_m2(const rvm_int16_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m2");
	exit(-1);
}
int32_t mipp_testz_2_int16_m4(const rvm_int16_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m4");
	exit(-1);
}
int32_t mipp_testz_2_int16_m8(const rvm_int16_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m8");
	exit(-1);
}
int32_t mipp_testz_2_int8(const rvm_int8_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_int8(m0);
#endif
}
int32_t mipp_testz_2_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_testz_2_int8(m0);
}
int32_t mipp_testz_2_int8_m2(const rvm_int8_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m2");
	exit(-1);
}
int32_t mipp_testz_2_int8_m4(const rvm_int8_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m4");
	exit(-1);
}
int32_t mipp_testz_2_int8_m8(const rvm_int8_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m8");
	exit(-1);
}
int32_t mipp_testz_2_uint64(const rvm_uint64_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_uint64(m0);
#endif
}
int32_t mipp_testz_2_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_testz_2_uint64(m0);
}
int32_t mipp_testz_2_uint64_m2(const rvm_uint64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m2");
	exit(-1);
}
int32_t mipp_testz_2_uint64_m4(const rvm_uint64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m4");
	exit(-1);
}
int32_t mipp_testz_2_uint64_m8(const rvm_uint64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m8");
	exit(-1);
}
int32_t mipp_testz_2_uint32(const rvm_uint32_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_uint32(m0);
#endif
}
int32_t mipp_testz_2_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_testz_2_uint32(m0);
}
int32_t mipp_testz_2_uint32_m2(const rvm_uint32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m2");
	exit(-1);
}
int32_t mipp_testz_2_uint32_m4(const rvm_uint32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m4");
	exit(-1);
}
int32_t mipp_testz_2_uint32_m8(const rvm_uint32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m8");
	exit(-1);
}
int32_t mipp_testz_2_uint16(const rvm_uint16_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_uint16(m0);
#endif
}
int32_t mipp_testz_2_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_testz_2_uint16(m0);
}
int32_t mipp_testz_2_uint16_m2(const rvm_uint16_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m2");
	exit(-1);
}
int32_t mipp_testz_2_uint16_m4(const rvm_uint16_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m4");
	exit(-1);
}
int32_t mipp_testz_2_uint16_m8(const rvm_uint16_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m8");
	exit(-1);
}
int32_t mipp_testz_2_uint8(const rvm_uint8_t m0) {
#if defined(__AVX__)
	return mipp_avx_testz_2_uint8(m0);
#endif
}
int32_t mipp_testz_2_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_testz_2_uint8(m0);
}
int32_t mipp_testz_2_uint8_m2(const rvm_uint8_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m2");
	exit(-1);
}
int32_t mipp_testz_2_uint8_m4(const rvm_uint8_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m4");
	exit(-1);
}
int32_t mipp_testz_2_uint8_m8(const rvm_uint8_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m8");
	exit(-1);
}
rvd_float64_t mipp_hadd_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_float64(r0);
#endif
}
rvd_float64_m1_t mipp_hadd_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hadd_float64(r0);
}
rvd_float64_m2_t mipp_hadd_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m2");
	exit(-1);
}
rvd_float64_m4_t mipp_hadd_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m4");
	exit(-1);
}
rvd_float64_m8_t mipp_hadd_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m8");
	exit(-1);
}
rvd_float32_t mipp_hadd_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_float32(r0);
#endif
}
rvd_float32_m1_t mipp_hadd_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hadd_float32(r0);
}
rvd_float32_m2_t mipp_hadd_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m2");
	exit(-1);
}
rvd_float32_m4_t mipp_hadd_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m4");
	exit(-1);
}
rvd_float32_m8_t mipp_hadd_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m8");
	exit(-1);
}
rvd_int64_t mipp_hadd_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_int64(r0);
#endif
}
rvd_int64_m1_t mipp_hadd_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hadd_int64(r0);
}
rvd_int64_m2_t mipp_hadd_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m2");
	exit(-1);
}
rvd_int64_m4_t mipp_hadd_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m4");
	exit(-1);
}
rvd_int64_m8_t mipp_hadd_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m8");
	exit(-1);
}
rvd_int32_t mipp_hadd_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_int32(r0);
#endif
}
rvd_int32_m1_t mipp_hadd_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hadd_int32(r0);
}
rvd_int32_m2_t mipp_hadd_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m2");
	exit(-1);
}
rvd_int32_m4_t mipp_hadd_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m4");
	exit(-1);
}
rvd_int32_m8_t mipp_hadd_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m8");
	exit(-1);
}
rvd_int16_t mipp_hadd_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_int16(r0);
#endif
}
rvd_int16_m1_t mipp_hadd_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hadd_int16(r0);
}
rvd_int16_m2_t mipp_hadd_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m2");
	exit(-1);
}
rvd_int16_m4_t mipp_hadd_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m4");
	exit(-1);
}
rvd_int16_m8_t mipp_hadd_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m8");
	exit(-1);
}
rvd_int8_t mipp_hadd_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_int8(r0);
#endif
}
rvd_int8_m1_t mipp_hadd_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hadd_int8(r0);
}
rvd_int8_m2_t mipp_hadd_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m2");
	exit(-1);
}
rvd_int8_m4_t mipp_hadd_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m4");
	exit(-1);
}
rvd_int8_m8_t mipp_hadd_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m8");
	exit(-1);
}
rvd_uint64_t mipp_hadd_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_hadd_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hadd_uint64(r0);
}
rvd_uint64_m2_t mipp_hadd_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m2");
	exit(-1);
}
rvd_uint64_m4_t mipp_hadd_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m4");
	exit(-1);
}
rvd_uint64_m8_t mipp_hadd_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m8");
	exit(-1);
}
rvd_uint32_t mipp_hadd_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_hadd_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hadd_uint32(r0);
}
rvd_uint32_m2_t mipp_hadd_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m2");
	exit(-1);
}
rvd_uint32_m4_t mipp_hadd_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m4");
	exit(-1);
}
rvd_uint32_m8_t mipp_hadd_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m8");
	exit(-1);
}
rvd_uint16_t mipp_hadd_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_hadd_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hadd_uint16(r0);
}
rvd_uint16_m2_t mipp_hadd_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m2");
	exit(-1);
}
rvd_uint16_m4_t mipp_hadd_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m4");
	exit(-1);
}
rvd_uint16_m8_t mipp_hadd_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m8");
	exit(-1);
}
rvd_uint8_t mipp_hadd_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_hadd_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hadd_uint8(r0);
}
rvd_uint8_m2_t mipp_hadd_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m2");
	exit(-1);
}
rvd_uint8_m4_t mipp_hadd_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m4");
	exit(-1);
}
rvd_uint8_m8_t mipp_hadd_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m8");
	exit(-1);
}
float64_t mipp_hadd_2_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_float64(r0);
#endif
}
float64_t mipp_hadd_2_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hadd_2_float64(r0);
}
float64_t mipp_hadd_2_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float64_m2");
	exit(-1);
}
float64_t mipp_hadd_2_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float64_m4");
	exit(-1);
}
float64_t mipp_hadd_2_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float64_m8");
	exit(-1);
}
float32_t mipp_hadd_2_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_float32(r0);
#endif
}
float32_t mipp_hadd_2_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hadd_2_float32(r0);
}
float32_t mipp_hadd_2_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float32_m2");
	exit(-1);
}
float32_t mipp_hadd_2_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float32_m4");
	exit(-1);
}
float32_t mipp_hadd_2_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_float32_m8");
	exit(-1);
}
int64_t mipp_hadd_2_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_int64(r0);
#endif
}
int64_t mipp_hadd_2_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hadd_2_int64(r0);
}
int64_t mipp_hadd_2_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int64_m2");
	exit(-1);
}
int64_t mipp_hadd_2_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int64_m4");
	exit(-1);
}
int64_t mipp_hadd_2_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int64_m8");
	exit(-1);
}
int32_t mipp_hadd_2_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_int32(r0);
#endif
}
int32_t mipp_hadd_2_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hadd_2_int32(r0);
}
int32_t mipp_hadd_2_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int32_m2");
	exit(-1);
}
int32_t mipp_hadd_2_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int32_m4");
	exit(-1);
}
int32_t mipp_hadd_2_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int32_m8");
	exit(-1);
}
int16_t mipp_hadd_2_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_int16(r0);
#endif
}
int16_t mipp_hadd_2_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hadd_2_int16(r0);
}
int16_t mipp_hadd_2_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int16_m2");
	exit(-1);
}
int16_t mipp_hadd_2_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int16_m4");
	exit(-1);
}
int16_t mipp_hadd_2_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int16_m8");
	exit(-1);
}
int8_t mipp_hadd_2_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_int8(r0);
#endif
}
int8_t mipp_hadd_2_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hadd_2_int8(r0);
}
int8_t mipp_hadd_2_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int8_m2");
	exit(-1);
}
int8_t mipp_hadd_2_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int8_m4");
	exit(-1);
}
int8_t mipp_hadd_2_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_int8_m8");
	exit(-1);
}
uint64_t mipp_hadd_2_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_uint64(r0);
#endif
}
uint64_t mipp_hadd_2_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hadd_2_uint64(r0);
}
uint64_t mipp_hadd_2_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint64_m2");
	exit(-1);
}
uint64_t mipp_hadd_2_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint64_m4");
	exit(-1);
}
uint64_t mipp_hadd_2_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint64_m8");
	exit(-1);
}
uint32_t mipp_hadd_2_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_uint32(r0);
#endif
}
uint32_t mipp_hadd_2_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hadd_2_uint32(r0);
}
uint32_t mipp_hadd_2_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint32_m2");
	exit(-1);
}
uint32_t mipp_hadd_2_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint32_m4");
	exit(-1);
}
uint32_t mipp_hadd_2_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint32_m8");
	exit(-1);
}
uint16_t mipp_hadd_2_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_uint16(r0);
#endif
}
uint16_t mipp_hadd_2_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hadd_2_uint16(r0);
}
uint16_t mipp_hadd_2_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint16_m2");
	exit(-1);
}
uint16_t mipp_hadd_2_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint16_m4");
	exit(-1);
}
uint16_t mipp_hadd_2_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint16_m8");
	exit(-1);
}
uint8_t mipp_hadd_2_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hadd_2_uint8(r0);
#endif
}
uint8_t mipp_hadd_2_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hadd_2_uint8(r0);
}
uint8_t mipp_hadd_2_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint8_m2");
	exit(-1);
}
uint8_t mipp_hadd_2_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint8_m4");
	exit(-1);
}
uint8_t mipp_hadd_2_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_2_uint8_m8");
	exit(-1);
}
rvd_float64_t mipp_hmul_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_float64(r0);
#endif
}
rvd_float64_m1_t mipp_hmul_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmul_float64(r0);
}
rvd_float64_m2_t mipp_hmul_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m2");
	exit(-1);
}
rvd_float64_m4_t mipp_hmul_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m4");
	exit(-1);
}
rvd_float64_m8_t mipp_hmul_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m8");
	exit(-1);
}
rvd_float32_t mipp_hmul_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_float32(r0);
#endif
}
rvd_float32_m1_t mipp_hmul_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmul_float32(r0);
}
rvd_float32_m2_t mipp_hmul_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m2");
	exit(-1);
}
rvd_float32_m4_t mipp_hmul_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m4");
	exit(-1);
}
rvd_float32_m8_t mipp_hmul_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m8");
	exit(-1);
}
rvd_int64_t mipp_hmul_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_int64(r0);
#endif
}
rvd_int64_m1_t mipp_hmul_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmul_int64(r0);
}
rvd_int64_m2_t mipp_hmul_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m2");
	exit(-1);
}
rvd_int64_m4_t mipp_hmul_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m4");
	exit(-1);
}
rvd_int64_m8_t mipp_hmul_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m8");
	exit(-1);
}
rvd_int32_t mipp_hmul_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_int32(r0);
#endif
}
rvd_int32_m1_t mipp_hmul_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmul_int32(r0);
}
rvd_int32_m2_t mipp_hmul_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m2");
	exit(-1);
}
rvd_int32_m4_t mipp_hmul_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m4");
	exit(-1);
}
rvd_int32_m8_t mipp_hmul_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m8");
	exit(-1);
}
rvd_int16_t mipp_hmul_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_int16(r0);
#endif
}
rvd_int16_m1_t mipp_hmul_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmul_int16(r0);
}
rvd_int16_m2_t mipp_hmul_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m2");
	exit(-1);
}
rvd_int16_m4_t mipp_hmul_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m4");
	exit(-1);
}
rvd_int16_m8_t mipp_hmul_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m8");
	exit(-1);
}
rvd_int8_t mipp_hmul_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_int8(r0);
#endif
}
rvd_int8_m1_t mipp_hmul_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmul_int8(r0);
}
rvd_int8_m2_t mipp_hmul_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m2");
	exit(-1);
}
rvd_int8_m4_t mipp_hmul_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m4");
	exit(-1);
}
rvd_int8_m8_t mipp_hmul_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m8");
	exit(-1);
}
rvd_uint64_t mipp_hmul_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_hmul_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmul_uint64(r0);
}
rvd_uint64_m2_t mipp_hmul_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m2");
	exit(-1);
}
rvd_uint64_m4_t mipp_hmul_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m4");
	exit(-1);
}
rvd_uint64_m8_t mipp_hmul_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m8");
	exit(-1);
}
rvd_uint32_t mipp_hmul_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_hmul_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmul_uint32(r0);
}
rvd_uint32_m2_t mipp_hmul_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m2");
	exit(-1);
}
rvd_uint32_m4_t mipp_hmul_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m4");
	exit(-1);
}
rvd_uint32_m8_t mipp_hmul_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m8");
	exit(-1);
}
rvd_uint16_t mipp_hmul_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_hmul_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmul_uint16(r0);
}
rvd_uint16_m2_t mipp_hmul_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m2");
	exit(-1);
}
rvd_uint16_m4_t mipp_hmul_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m4");
	exit(-1);
}
rvd_uint16_m8_t mipp_hmul_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m8");
	exit(-1);
}
rvd_uint8_t mipp_hmul_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_hmul_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmul_uint8(r0);
}
rvd_uint8_m2_t mipp_hmul_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m2");
	exit(-1);
}
rvd_uint8_m4_t mipp_hmul_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m4");
	exit(-1);
}
rvd_uint8_m8_t mipp_hmul_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m8");
	exit(-1);
}
float64_t mipp_hmul_2_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_float64(r0);
#endif
}
float64_t mipp_hmul_2_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmul_2_float64(r0);
}
float64_t mipp_hmul_2_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float64_m2");
	exit(-1);
}
float64_t mipp_hmul_2_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float64_m4");
	exit(-1);
}
float64_t mipp_hmul_2_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float64_m8");
	exit(-1);
}
float32_t mipp_hmul_2_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_float32(r0);
#endif
}
float32_t mipp_hmul_2_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmul_2_float32(r0);
}
float32_t mipp_hmul_2_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float32_m2");
	exit(-1);
}
float32_t mipp_hmul_2_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float32_m4");
	exit(-1);
}
float32_t mipp_hmul_2_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_float32_m8");
	exit(-1);
}
int64_t mipp_hmul_2_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_int64(r0);
#endif
}
int64_t mipp_hmul_2_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmul_2_int64(r0);
}
int64_t mipp_hmul_2_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int64_m2");
	exit(-1);
}
int64_t mipp_hmul_2_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int64_m4");
	exit(-1);
}
int64_t mipp_hmul_2_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int64_m8");
	exit(-1);
}
int32_t mipp_hmul_2_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_int32(r0);
#endif
}
int32_t mipp_hmul_2_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmul_2_int32(r0);
}
int32_t mipp_hmul_2_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int32_m2");
	exit(-1);
}
int32_t mipp_hmul_2_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int32_m4");
	exit(-1);
}
int32_t mipp_hmul_2_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int32_m8");
	exit(-1);
}
int16_t mipp_hmul_2_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_int16(r0);
#endif
}
int16_t mipp_hmul_2_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmul_2_int16(r0);
}
int16_t mipp_hmul_2_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int16_m2");
	exit(-1);
}
int16_t mipp_hmul_2_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int16_m4");
	exit(-1);
}
int16_t mipp_hmul_2_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int16_m8");
	exit(-1);
}
int8_t mipp_hmul_2_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_int8(r0);
#endif
}
int8_t mipp_hmul_2_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmul_2_int8(r0);
}
int8_t mipp_hmul_2_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int8_m2");
	exit(-1);
}
int8_t mipp_hmul_2_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int8_m4");
	exit(-1);
}
int8_t mipp_hmul_2_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_int8_m8");
	exit(-1);
}
uint64_t mipp_hmul_2_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_uint64(r0);
#endif
}
uint64_t mipp_hmul_2_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmul_2_uint64(r0);
}
uint64_t mipp_hmul_2_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint64_m2");
	exit(-1);
}
uint64_t mipp_hmul_2_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint64_m4");
	exit(-1);
}
uint64_t mipp_hmul_2_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint64_m8");
	exit(-1);
}
uint32_t mipp_hmul_2_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_uint32(r0);
#endif
}
uint32_t mipp_hmul_2_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmul_2_uint32(r0);
}
uint32_t mipp_hmul_2_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint32_m2");
	exit(-1);
}
uint32_t mipp_hmul_2_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint32_m4");
	exit(-1);
}
uint32_t mipp_hmul_2_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint32_m8");
	exit(-1);
}
uint16_t mipp_hmul_2_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_uint16(r0);
#endif
}
uint16_t mipp_hmul_2_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmul_2_uint16(r0);
}
uint16_t mipp_hmul_2_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint16_m2");
	exit(-1);
}
uint16_t mipp_hmul_2_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint16_m4");
	exit(-1);
}
uint16_t mipp_hmul_2_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint16_m8");
	exit(-1);
}
uint8_t mipp_hmul_2_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmul_2_uint8(r0);
#endif
}
uint8_t mipp_hmul_2_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmul_2_uint8(r0);
}
uint8_t mipp_hmul_2_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint8_m2");
	exit(-1);
}
uint8_t mipp_hmul_2_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint8_m4");
	exit(-1);
}
uint8_t mipp_hmul_2_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_2_uint8_m8");
	exit(-1);
}
rvd_float64_t mipp_hmin_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_float64(r0);
#endif
}
rvd_float64_m1_t mipp_hmin_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmin_float64(r0);
}
rvd_float64_m2_t mipp_hmin_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m2");
	exit(-1);
}
rvd_float64_m4_t mipp_hmin_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m4");
	exit(-1);
}
rvd_float64_m8_t mipp_hmin_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m8");
	exit(-1);
}
rvd_float32_t mipp_hmin_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_float32(r0);
#endif
}
rvd_float32_m1_t mipp_hmin_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmin_float32(r0);
}
rvd_float32_m2_t mipp_hmin_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m2");
	exit(-1);
}
rvd_float32_m4_t mipp_hmin_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m4");
	exit(-1);
}
rvd_float32_m8_t mipp_hmin_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m8");
	exit(-1);
}
rvd_int64_t mipp_hmin_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_int64(r0);
#endif
}
rvd_int64_m1_t mipp_hmin_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmin_int64(r0);
}
rvd_int64_m2_t mipp_hmin_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m2");
	exit(-1);
}
rvd_int64_m4_t mipp_hmin_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m4");
	exit(-1);
}
rvd_int64_m8_t mipp_hmin_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m8");
	exit(-1);
}
rvd_int32_t mipp_hmin_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_int32(r0);
#endif
}
rvd_int32_m1_t mipp_hmin_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmin_int32(r0);
}
rvd_int32_m2_t mipp_hmin_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m2");
	exit(-1);
}
rvd_int32_m4_t mipp_hmin_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m4");
	exit(-1);
}
rvd_int32_m8_t mipp_hmin_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m8");
	exit(-1);
}
rvd_int16_t mipp_hmin_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_int16(r0);
#endif
}
rvd_int16_m1_t mipp_hmin_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmin_int16(r0);
}
rvd_int16_m2_t mipp_hmin_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m2");
	exit(-1);
}
rvd_int16_m4_t mipp_hmin_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m4");
	exit(-1);
}
rvd_int16_m8_t mipp_hmin_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m8");
	exit(-1);
}
rvd_int8_t mipp_hmin_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_int8(r0);
#endif
}
rvd_int8_m1_t mipp_hmin_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmin_int8(r0);
}
rvd_int8_m2_t mipp_hmin_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m2");
	exit(-1);
}
rvd_int8_m4_t mipp_hmin_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m4");
	exit(-1);
}
rvd_int8_m8_t mipp_hmin_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m8");
	exit(-1);
}
rvd_uint64_t mipp_hmin_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_hmin_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmin_uint64(r0);
}
rvd_uint64_m2_t mipp_hmin_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m2");
	exit(-1);
}
rvd_uint64_m4_t mipp_hmin_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m4");
	exit(-1);
}
rvd_uint64_m8_t mipp_hmin_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m8");
	exit(-1);
}
rvd_uint32_t mipp_hmin_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_hmin_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmin_uint32(r0);
}
rvd_uint32_m2_t mipp_hmin_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m2");
	exit(-1);
}
rvd_uint32_m4_t mipp_hmin_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m4");
	exit(-1);
}
rvd_uint32_m8_t mipp_hmin_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m8");
	exit(-1);
}
rvd_uint16_t mipp_hmin_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_hmin_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmin_uint16(r0);
}
rvd_uint16_m2_t mipp_hmin_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m2");
	exit(-1);
}
rvd_uint16_m4_t mipp_hmin_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m4");
	exit(-1);
}
rvd_uint16_m8_t mipp_hmin_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m8");
	exit(-1);
}
rvd_uint8_t mipp_hmin_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_hmin_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmin_uint8(r0);
}
rvd_uint8_m2_t mipp_hmin_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m2");
	exit(-1);
}
rvd_uint8_m4_t mipp_hmin_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m4");
	exit(-1);
}
rvd_uint8_m8_t mipp_hmin_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m8");
	exit(-1);
}
float64_t mipp_hmin_2_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_float64(r0);
#endif
}
float64_t mipp_hmin_2_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmin_2_float64(r0);
}
float64_t mipp_hmin_2_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float64_m2");
	exit(-1);
}
float64_t mipp_hmin_2_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float64_m4");
	exit(-1);
}
float64_t mipp_hmin_2_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float64_m8");
	exit(-1);
}
float32_t mipp_hmin_2_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_float32(r0);
#endif
}
float32_t mipp_hmin_2_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmin_2_float32(r0);
}
float32_t mipp_hmin_2_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float32_m2");
	exit(-1);
}
float32_t mipp_hmin_2_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float32_m4");
	exit(-1);
}
float32_t mipp_hmin_2_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_float32_m8");
	exit(-1);
}
int64_t mipp_hmin_2_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_int64(r0);
#endif
}
int64_t mipp_hmin_2_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmin_2_int64(r0);
}
int64_t mipp_hmin_2_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int64_m2");
	exit(-1);
}
int64_t mipp_hmin_2_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int64_m4");
	exit(-1);
}
int64_t mipp_hmin_2_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int64_m8");
	exit(-1);
}
int32_t mipp_hmin_2_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_int32(r0);
#endif
}
int32_t mipp_hmin_2_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmin_2_int32(r0);
}
int32_t mipp_hmin_2_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int32_m2");
	exit(-1);
}
int32_t mipp_hmin_2_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int32_m4");
	exit(-1);
}
int32_t mipp_hmin_2_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int32_m8");
	exit(-1);
}
int16_t mipp_hmin_2_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_int16(r0);
#endif
}
int16_t mipp_hmin_2_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmin_2_int16(r0);
}
int16_t mipp_hmin_2_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int16_m2");
	exit(-1);
}
int16_t mipp_hmin_2_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int16_m4");
	exit(-1);
}
int16_t mipp_hmin_2_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int16_m8");
	exit(-1);
}
int8_t mipp_hmin_2_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_int8(r0);
#endif
}
int8_t mipp_hmin_2_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmin_2_int8(r0);
}
int8_t mipp_hmin_2_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int8_m2");
	exit(-1);
}
int8_t mipp_hmin_2_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int8_m4");
	exit(-1);
}
int8_t mipp_hmin_2_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_int8_m8");
	exit(-1);
}
uint64_t mipp_hmin_2_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_uint64(r0);
#endif
}
uint64_t mipp_hmin_2_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmin_2_uint64(r0);
}
uint64_t mipp_hmin_2_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint64_m2");
	exit(-1);
}
uint64_t mipp_hmin_2_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint64_m4");
	exit(-1);
}
uint64_t mipp_hmin_2_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint64_m8");
	exit(-1);
}
uint32_t mipp_hmin_2_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_uint32(r0);
#endif
}
uint32_t mipp_hmin_2_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmin_2_uint32(r0);
}
uint32_t mipp_hmin_2_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint32_m2");
	exit(-1);
}
uint32_t mipp_hmin_2_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint32_m4");
	exit(-1);
}
uint32_t mipp_hmin_2_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint32_m8");
	exit(-1);
}
uint16_t mipp_hmin_2_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_uint16(r0);
#endif
}
uint16_t mipp_hmin_2_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmin_2_uint16(r0);
}
uint16_t mipp_hmin_2_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint16_m2");
	exit(-1);
}
uint16_t mipp_hmin_2_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint16_m4");
	exit(-1);
}
uint16_t mipp_hmin_2_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint16_m8");
	exit(-1);
}
uint8_t mipp_hmin_2_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmin_2_uint8(r0);
#endif
}
uint8_t mipp_hmin_2_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmin_2_uint8(r0);
}
uint8_t mipp_hmin_2_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint8_m2");
	exit(-1);
}
uint8_t mipp_hmin_2_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint8_m4");
	exit(-1);
}
uint8_t mipp_hmin_2_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_2_uint8_m8");
	exit(-1);
}
rvd_float64_t mipp_hmax_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_float64(r0);
#endif
}
rvd_float64_m1_t mipp_hmax_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmax_float64(r0);
}
rvd_float64_m2_t mipp_hmax_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m2");
	exit(-1);
}
rvd_float64_m4_t mipp_hmax_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m4");
	exit(-1);
}
rvd_float64_m8_t mipp_hmax_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m8");
	exit(-1);
}
rvd_float32_t mipp_hmax_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_float32(r0);
#endif
}
rvd_float32_m1_t mipp_hmax_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmax_float32(r0);
}
rvd_float32_m2_t mipp_hmax_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m2");
	exit(-1);
}
rvd_float32_m4_t mipp_hmax_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m4");
	exit(-1);
}
rvd_float32_m8_t mipp_hmax_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m8");
	exit(-1);
}
rvd_int64_t mipp_hmax_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_int64(r0);
#endif
}
rvd_int64_m1_t mipp_hmax_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmax_int64(r0);
}
rvd_int64_m2_t mipp_hmax_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m2");
	exit(-1);
}
rvd_int64_m4_t mipp_hmax_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m4");
	exit(-1);
}
rvd_int64_m8_t mipp_hmax_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m8");
	exit(-1);
}
rvd_int32_t mipp_hmax_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_int32(r0);
#endif
}
rvd_int32_m1_t mipp_hmax_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmax_int32(r0);
}
rvd_int32_m2_t mipp_hmax_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m2");
	exit(-1);
}
rvd_int32_m4_t mipp_hmax_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m4");
	exit(-1);
}
rvd_int32_m8_t mipp_hmax_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m8");
	exit(-1);
}
rvd_int16_t mipp_hmax_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_int16(r0);
#endif
}
rvd_int16_m1_t mipp_hmax_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmax_int16(r0);
}
rvd_int16_m2_t mipp_hmax_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m2");
	exit(-1);
}
rvd_int16_m4_t mipp_hmax_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m4");
	exit(-1);
}
rvd_int16_m8_t mipp_hmax_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m8");
	exit(-1);
}
rvd_int8_t mipp_hmax_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_int8(r0);
#endif
}
rvd_int8_m1_t mipp_hmax_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmax_int8(r0);
}
rvd_int8_m2_t mipp_hmax_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m2");
	exit(-1);
}
rvd_int8_m4_t mipp_hmax_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m4");
	exit(-1);
}
rvd_int8_m8_t mipp_hmax_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m8");
	exit(-1);
}
rvd_uint64_t mipp_hmax_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_uint64(r0);
#endif
}
rvd_uint64_m1_t mipp_hmax_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmax_uint64(r0);
}
rvd_uint64_m2_t mipp_hmax_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m2");
	exit(-1);
}
rvd_uint64_m4_t mipp_hmax_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m4");
	exit(-1);
}
rvd_uint64_m8_t mipp_hmax_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m8");
	exit(-1);
}
rvd_uint32_t mipp_hmax_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_uint32(r0);
#endif
}
rvd_uint32_m1_t mipp_hmax_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmax_uint32(r0);
}
rvd_uint32_m2_t mipp_hmax_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m2");
	exit(-1);
}
rvd_uint32_m4_t mipp_hmax_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m4");
	exit(-1);
}
rvd_uint32_m8_t mipp_hmax_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m8");
	exit(-1);
}
rvd_uint16_t mipp_hmax_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_uint16(r0);
#endif
}
rvd_uint16_m1_t mipp_hmax_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmax_uint16(r0);
}
rvd_uint16_m2_t mipp_hmax_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m2");
	exit(-1);
}
rvd_uint16_m4_t mipp_hmax_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m4");
	exit(-1);
}
rvd_uint16_m8_t mipp_hmax_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m8");
	exit(-1);
}
rvd_uint8_t mipp_hmax_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_uint8(r0);
#endif
}
rvd_uint8_m1_t mipp_hmax_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmax_uint8(r0);
}
rvd_uint8_m2_t mipp_hmax_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m2");
	exit(-1);
}
rvd_uint8_m4_t mipp_hmax_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m4");
	exit(-1);
}
rvd_uint8_m8_t mipp_hmax_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m8");
	exit(-1);
}
float64_t mipp_hmax_2_float64(const rvd_float64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_float64(r0);
#endif
}
float64_t mipp_hmax_2_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmax_2_float64(r0);
}
float64_t mipp_hmax_2_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float64_m2");
	exit(-1);
}
float64_t mipp_hmax_2_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float64_m4");
	exit(-1);
}
float64_t mipp_hmax_2_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float64_m8");
	exit(-1);
}
float32_t mipp_hmax_2_float32(const rvd_float32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_float32(r0);
#endif
}
float32_t mipp_hmax_2_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmax_2_float32(r0);
}
float32_t mipp_hmax_2_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float32_m2");
	exit(-1);
}
float32_t mipp_hmax_2_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float32_m4");
	exit(-1);
}
float32_t mipp_hmax_2_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_float32_m8");
	exit(-1);
}
int64_t mipp_hmax_2_int64(const rvd_int64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_int64(r0);
#endif
}
int64_t mipp_hmax_2_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmax_2_int64(r0);
}
int64_t mipp_hmax_2_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int64_m2");
	exit(-1);
}
int64_t mipp_hmax_2_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int64_m4");
	exit(-1);
}
int64_t mipp_hmax_2_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int64_m8");
	exit(-1);
}
int32_t mipp_hmax_2_int32(const rvd_int32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_int32(r0);
#endif
}
int32_t mipp_hmax_2_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmax_2_int32(r0);
}
int32_t mipp_hmax_2_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int32_m2");
	exit(-1);
}
int32_t mipp_hmax_2_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int32_m4");
	exit(-1);
}
int32_t mipp_hmax_2_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int32_m8");
	exit(-1);
}
int16_t mipp_hmax_2_int16(const rvd_int16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_int16(r0);
#endif
}
int16_t mipp_hmax_2_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmax_2_int16(r0);
}
int16_t mipp_hmax_2_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int16_m2");
	exit(-1);
}
int16_t mipp_hmax_2_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int16_m4");
	exit(-1);
}
int16_t mipp_hmax_2_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int16_m8");
	exit(-1);
}
int8_t mipp_hmax_2_int8(const rvd_int8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_int8(r0);
#endif
}
int8_t mipp_hmax_2_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmax_2_int8(r0);
}
int8_t mipp_hmax_2_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int8_m2");
	exit(-1);
}
int8_t mipp_hmax_2_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int8_m4");
	exit(-1);
}
int8_t mipp_hmax_2_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_int8_m8");
	exit(-1);
}
uint64_t mipp_hmax_2_uint64(const rvd_uint64_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_uint64(r0);
#endif
}
uint64_t mipp_hmax_2_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmax_2_uint64(r0);
}
uint64_t mipp_hmax_2_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint64_m2");
	exit(-1);
}
uint64_t mipp_hmax_2_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint64_m4");
	exit(-1);
}
uint64_t mipp_hmax_2_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint64_m8");
	exit(-1);
}
uint32_t mipp_hmax_2_uint32(const rvd_uint32_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_uint32(r0);
#endif
}
uint32_t mipp_hmax_2_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmax_2_uint32(r0);
}
uint32_t mipp_hmax_2_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint32_m2");
	exit(-1);
}
uint32_t mipp_hmax_2_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint32_m4");
	exit(-1);
}
uint32_t mipp_hmax_2_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint32_m8");
	exit(-1);
}
uint16_t mipp_hmax_2_uint16(const rvd_uint16_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_uint16(r0);
#endif
}
uint16_t mipp_hmax_2_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmax_2_uint16(r0);
}
uint16_t mipp_hmax_2_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint16_m2");
	exit(-1);
}
uint16_t mipp_hmax_2_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint16_m4");
	exit(-1);
}
uint16_t mipp_hmax_2_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint16_m8");
	exit(-1);
}
uint8_t mipp_hmax_2_uint8(const rvd_uint8_t r0) {
#if defined(__AVX__)
	return mipp_avx_hmax_2_uint8(r0);
#endif
}
uint8_t mipp_hmax_2_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmax_2_uint8(r0);
}
uint8_t mipp_hmax_2_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint8_m2");
	exit(-1);
}
uint8_t mipp_hmax_2_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint8_m4");
	exit(-1);
}
uint8_t mipp_hmax_2_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_2_uint8_m8");
	exit(-1);
}
#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */
