#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#include "mipp_v2.h"
#include <immintrin.h>
#define MIPP_MACRO_FLOAT64(MACRO, ...) MACRO(__VA_ARGS__, 64, float, pd, pd, float64_t)
#define MIPP_MACRO_FLOAT32(MACRO, ...) MACRO(__VA_ARGS__, 32, float, ps, ps, float32_t)
#define MIPP_MACRO_INT64(MACRO, ...) MACRO(__VA_ARGS__, 64, int, epi64, si256, __m256i)
#define MIPP_MACRO_INT32(MACRO, ...) MACRO(__VA_ARGS__, 32, int, epi32, si256, __m256i)
#define MIPP_MACRO_INT16(MACRO, ...) MACRO(__VA_ARGS__, 16, int, epi16, si256, __m256i)
#define MIPP_MACRO_INT8(MACRO, ...) MACRO(__VA_ARGS__, 8, int, epi8, si256, __m256i)
#define MIPP_MACRO_UINT64(MACRO, ...) MACRO(__VA_ARGS__, 64, uint, epu64, si256, __m256i)
#define MIPP_MACRO_UINT32(MACRO, ...) MACRO(__VA_ARGS__, 32, uint, epu32, si256, __m256i)
#define MIPP_MACRO_UINT16(MACRO, ...) MACRO(__VA_ARGS__, 16, uint, epu16, si256, __m256i)
#define MIPP_MACRO_UINT8(MACRO, ...) MACRO(__VA_ARGS__, 8, uint, epu8, si256, __m256i)
#define MIPP_AVX_RVD_SIZE_BIT 256
#define MIPP_AVX_RVD_SIZE_BYTE 32
#define MIPP_AVX_N_FLOAT64 4
#define MIPP_AVX_N_FLOAT32 8
#define MIPP_AVX_N_INT64 4
#define MIPP_AVX_N_INT32 8
#define MIPP_AVX_N_INT16 16
#define MIPP_AVX_N_INT8 32
#define MIPP_AVX_N_UINT64 4
#define MIPP_AVX_N_UINT32 8
#define MIPP_AVX_N_UINT16 16
#define MIPP_AVX_N_UINT8 32
typedef struct { __m256d m; } rvd_avx_float64_t;
typedef struct {  __m256 m; } rvd_avx_float32_t;
typedef struct { __m256i m; } rvd_avx_int64_t;
typedef struct { __m256i m; } rvd_avx_int32_t;
typedef struct { __m256i m; } rvd_avx_int16_t;
typedef struct { __m256i m; } rvd_avx_int8_t;
typedef struct { __m256i m; } rvd_avx_uint64_t;
typedef struct { __m256i m; } rvd_avx_uint32_t;
typedef struct { __m256i m; } rvd_avx_uint16_t;
typedef struct { __m256i m; } rvd_avx_uint8_t;
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
rvd_avx_float64_t mipp_avx_cast_float64_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_float64_t mipp_avx_cast_float32_float64(const rvd_avx_float32_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castps_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_int64_float64(const rvd_avx_int64_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_int32_float64(const rvd_avx_int32_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_int16_float64(const rvd_avx_int16_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_int8_float64(const rvd_avx_int8_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_uint64_float64(const rvd_avx_uint64_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_uint32_float64(const rvd_avx_uint32_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_uint16_float64(const rvd_avx_uint16_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_cast_uint8_float64(const rvd_avx_uint8_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_float64_float32(const rvd_avx_float64_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castpd_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_float32_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_float32_t mipp_avx_cast_int64_float32(const rvd_avx_int64_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_int32_float32(const rvd_avx_int32_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_int16_float32(const rvd_avx_int16_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_int8_float32(const rvd_avx_int8_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_uint64_float32(const rvd_avx_uint64_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_uint32_float32(const rvd_avx_uint32_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_uint16_float32(const rvd_avx_uint16_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_cast_uint8_float32(const rvd_avx_uint8_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(r0.m);
	return res;
}
rvd_avx_int64_t mipp_avx_cast_float64_int64(const rvd_avx_float64_t r0) {
	rvd_avx_int64_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_int64_t mipp_avx_cast_float32_int64(const rvd_avx_float32_t r0) {
	rvd_avx_int64_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_int64_t mipp_avx_cast_int64_int64(const rvd_avx_int64_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_int32_int64(const rvd_avx_int32_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_int16_int64(const rvd_avx_int16_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_int8_int64(const rvd_avx_int8_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_uint64_int64(const rvd_avx_uint64_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_uint32_int64(const rvd_avx_uint32_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_uint16_int64(const rvd_avx_uint16_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int64_t mipp_avx_cast_uint8_int64(const rvd_avx_uint8_t r0) {
	rvd_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_float64_int32(const rvd_avx_float64_t r0) {
	rvd_avx_int32_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_int32_t mipp_avx_cast_float32_int32(const rvd_avx_float32_t r0) {
	rvd_avx_int32_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_int32_t mipp_avx_cast_int64_int32(const rvd_avx_int64_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_int32_int32(const rvd_avx_int32_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_int16_int32(const rvd_avx_int16_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_int8_int32(const rvd_avx_int8_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_uint64_int32(const rvd_avx_uint64_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_uint32_int32(const rvd_avx_uint32_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_uint16_int32(const rvd_avx_uint16_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_cast_uint8_int32(const rvd_avx_uint8_t r0) {
	rvd_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_float64_int16(const rvd_avx_float64_t r0) {
	rvd_avx_int16_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_int16_t mipp_avx_cast_float32_int16(const rvd_avx_float32_t r0) {
	rvd_avx_int16_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_int16_t mipp_avx_cast_int64_int16(const rvd_avx_int64_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_int32_int16(const rvd_avx_int32_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_int16_int16(const rvd_avx_int16_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_int8_int16(const rvd_avx_int8_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_uint64_int16(const rvd_avx_uint64_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_uint32_int16(const rvd_avx_uint32_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_uint16_int16(const rvd_avx_uint16_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_cast_uint8_int16(const rvd_avx_uint8_t r0) {
	rvd_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_float64_int8(const rvd_avx_float64_t r0) {
	rvd_avx_int8_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_int8_t mipp_avx_cast_float32_int8(const rvd_avx_float32_t r0) {
	rvd_avx_int8_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_int8_t mipp_avx_cast_int64_int8(const rvd_avx_int64_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_int32_int8(const rvd_avx_int32_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_int16_int8(const rvd_avx_int16_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_int8_int8(const rvd_avx_int8_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_uint64_int8(const rvd_avx_uint64_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_uint32_int8(const rvd_avx_uint32_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_uint16_int8(const rvd_avx_uint16_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_cast_uint8_int8(const rvd_avx_uint8_t r0) {
	rvd_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_float64_uint64(const rvd_avx_float64_t r0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_float32_uint64(const rvd_avx_float32_t r0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_int64_uint64(const rvd_avx_int64_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_int32_uint64(const rvd_avx_int32_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_int16_uint64(const rvd_avx_int16_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_int8_uint64(const rvd_avx_int8_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_uint64_uint64(const rvd_avx_uint64_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_uint32_uint64(const rvd_avx_uint32_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_uint16_uint64(const rvd_avx_uint16_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_cast_uint8_uint64(const rvd_avx_uint8_t r0) {
	rvd_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_float64_uint32(const rvd_avx_float64_t r0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_float32_uint32(const rvd_avx_float32_t r0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_int64_uint32(const rvd_avx_int64_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_int32_uint32(const rvd_avx_int32_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_int16_uint32(const rvd_avx_int16_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_int8_uint32(const rvd_avx_int8_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_uint64_uint32(const rvd_avx_uint64_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_uint32_uint32(const rvd_avx_uint32_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_uint16_uint32(const rvd_avx_uint16_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_cast_uint8_uint32(const rvd_avx_uint8_t r0) {
	rvd_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_float64_uint16(const rvd_avx_float64_t r0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_float32_uint16(const rvd_avx_float32_t r0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_int64_uint16(const rvd_avx_int64_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_int32_uint16(const rvd_avx_int32_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_int16_uint16(const rvd_avx_int16_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_int8_uint16(const rvd_avx_int8_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_uint64_uint16(const rvd_avx_uint64_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_uint32_uint16(const rvd_avx_uint32_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_uint16_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_cast_uint8_uint16(const rvd_avx_uint8_t r0) {
	rvd_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_float64_uint8(const rvd_avx_float64_t r0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_float32_uint8(const rvd_avx_float32_t r0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_int64_uint8(const rvd_avx_int64_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_int32_uint8(const rvd_avx_int32_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_int16_uint8(const rvd_avx_int16_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_int8_uint8(const rvd_avx_int8_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_uint64_uint8(const rvd_avx_uint64_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_uint32_uint8(const rvd_avx_uint32_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_uint16_uint8(const rvd_avx_uint16_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_cast_uint8_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_float64_float64(const rvm_avx_float64_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_float32_float64(const rvm_avx_float32_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_int64_float64(const rvm_avx_int64_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_int32_float64(const rvm_avx_int32_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_int16_float64(const rvm_avx_int16_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_int8_float64(const rvm_avx_int8_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_uint64_float64(const rvm_avx_uint64_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_uint32_float64(const rvm_avx_uint32_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_uint16_float64(const rvm_avx_uint16_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_cast_k_uint8_float64(const rvm_avx_uint8_t m0) {
	rvm_avx_float64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_float64_float32(const rvm_avx_float64_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_float32_float32(const rvm_avx_float32_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_int64_float32(const rvm_avx_int64_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_int32_float32(const rvm_avx_int32_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_int16_float32(const rvm_avx_int16_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_int8_float32(const rvm_avx_int8_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_uint64_float32(const rvm_avx_uint64_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_uint32_float32(const rvm_avx_uint32_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_uint16_float32(const rvm_avx_uint16_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float32_t mipp_avx_cast_k_uint8_float32(const rvm_avx_uint8_t m0) {
	rvm_avx_float32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_float64_int64(const rvm_avx_float64_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_float32_int64(const rvm_avx_float32_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_int64_int64(const rvm_avx_int64_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_int32_int64(const rvm_avx_int32_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_int16_int64(const rvm_avx_int16_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_int8_int64(const rvm_avx_int8_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_uint64_int64(const rvm_avx_uint64_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_uint32_int64(const rvm_avx_uint32_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_uint16_int64(const rvm_avx_uint16_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int64_t mipp_avx_cast_k_uint8_int64(const rvm_avx_uint8_t m0) {
	rvm_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_float64_int32(const rvm_avx_float64_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_float32_int32(const rvm_avx_float32_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_int64_int32(const rvm_avx_int64_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_int32_int32(const rvm_avx_int32_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_int16_int32(const rvm_avx_int16_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_int8_int32(const rvm_avx_int8_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_uint64_int32(const rvm_avx_uint64_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_uint32_int32(const rvm_avx_uint32_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_uint16_int32(const rvm_avx_uint16_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_cast_k_uint8_int32(const rvm_avx_uint8_t m0) {
	rvm_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_float64_int16(const rvm_avx_float64_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_float32_int16(const rvm_avx_float32_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_int64_int16(const rvm_avx_int64_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_int32_int16(const rvm_avx_int32_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_int16_int16(const rvm_avx_int16_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_int8_int16(const rvm_avx_int8_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_uint64_int16(const rvm_avx_uint64_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_uint32_int16(const rvm_avx_uint32_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_uint16_int16(const rvm_avx_uint16_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_cast_k_uint8_int16(const rvm_avx_uint8_t m0) {
	rvm_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_float64_int8(const rvm_avx_float64_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_float32_int8(const rvm_avx_float32_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_int64_int8(const rvm_avx_int64_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_int32_int8(const rvm_avx_int32_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_int16_int8(const rvm_avx_int16_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_int8_int8(const rvm_avx_int8_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_uint64_int8(const rvm_avx_uint64_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_uint32_int8(const rvm_avx_uint32_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_uint16_int8(const rvm_avx_uint16_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_cast_k_uint8_int8(const rvm_avx_uint8_t m0) {
	rvm_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_float64_uint64(const rvm_avx_float64_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_float32_uint64(const rvm_avx_float32_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_int64_uint64(const rvm_avx_int64_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_int32_uint64(const rvm_avx_int32_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_int16_uint64(const rvm_avx_int16_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_int8_uint64(const rvm_avx_int8_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_uint64_uint64(const rvm_avx_uint64_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_uint32_uint64(const rvm_avx_uint32_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_uint16_uint64(const rvm_avx_uint16_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_cast_k_uint8_uint64(const rvm_avx_uint8_t m0) {
	rvm_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_float64_uint32(const rvm_avx_float64_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_float32_uint32(const rvm_avx_float32_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_int64_uint32(const rvm_avx_int64_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_int32_uint32(const rvm_avx_int32_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_int16_uint32(const rvm_avx_int16_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_int8_uint32(const rvm_avx_int8_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_uint64_uint32(const rvm_avx_uint64_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_uint32_uint32(const rvm_avx_uint32_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_uint16_uint32(const rvm_avx_uint16_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_cast_k_uint8_uint32(const rvm_avx_uint8_t m0) {
	rvm_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_float64_uint16(const rvm_avx_float64_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_float32_uint16(const rvm_avx_float32_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_int64_uint16(const rvm_avx_int64_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_int32_uint16(const rvm_avx_int32_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_int16_uint16(const rvm_avx_int16_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_int8_uint16(const rvm_avx_int8_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_uint64_uint16(const rvm_avx_uint64_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_uint32_uint16(const rvm_avx_uint32_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_uint16_uint16(const rvm_avx_uint16_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_cast_k_uint8_uint16(const rvm_avx_uint8_t m0) {
	rvm_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_float64_uint8(const rvm_avx_float64_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_float32_uint8(const rvm_avx_float32_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_int64_uint8(const rvm_avx_int64_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_int32_uint8(const rvm_avx_int32_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_int16_uint8(const rvm_avx_int16_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_int8_uint8(const rvm_avx_int8_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_uint64_uint8(const rvm_avx_uint64_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_uint32_uint8(const rvm_avx_uint32_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_uint16_uint8(const rvm_avx_uint16_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_cast_k_uint8_uint8(const rvm_avx_uint8_t m0) {
	rvm_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_float64_t mipp_avx_toreg_float64(const rvm_avx_float64_t m0) {
	rvd_avx_float64_t res;
	res.m = _mm256_castsi256_pd(m0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_toreg_float32(const rvm_avx_float32_t m0) {
	rvd_avx_float32_t res;
	res.m = _mm256_castsi256_ps(m0.m);
	return res;
}
rvd_avx_int64_t mipp_avx_toreg_int64(const rvm_avx_int64_t m0) {
	rvd_avx_int64_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_int32_t mipp_avx_toreg_int32(const rvm_avx_int32_t m0) {
	rvd_avx_int32_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_int16_t mipp_avx_toreg_int16(const rvm_avx_int16_t m0) {
	rvd_avx_int16_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_int8_t mipp_avx_toreg_int8(const rvm_avx_int8_t m0) {
	rvd_avx_int8_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_uint64_t mipp_avx_toreg_uint64(const rvm_avx_uint64_t m0) {
	rvd_avx_uint64_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_uint32_t mipp_avx_toreg_uint32(const rvm_avx_uint32_t m0) {
	rvd_avx_uint32_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_uint16_t mipp_avx_toreg_uint16(const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t res;
	res.m = m0.m;
	return res;
}
rvd_avx_uint8_t mipp_avx_toreg_uint8(const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t res;
	res.m = m0.m;
	return res;
}
rvm_avx_float64_t mipp_avx_tomsk_float64(const rvd_avx_float64_t r0) {
	rvm_avx_float64_t res;
	res.m = _mm256_castpd_si256(r0.m);
	return res;
}
rvm_avx_float32_t mipp_avx_tomsk_float32(const rvd_avx_float32_t r0) {
	rvm_avx_float32_t res;
	res.m = _mm256_castps_si256(r0.m);
	return res;
}
rvm_avx_int64_t mipp_avx_tomsk_int64(const rvd_avx_int64_t r0) {
	rvm_avx_int64_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_int32_t mipp_avx_tomsk_int32(const rvd_avx_int32_t r0) {
	rvm_avx_int32_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_int16_t mipp_avx_tomsk_int16(const rvd_avx_int16_t r0) {
	rvm_avx_int16_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_int8_t mipp_avx_tomsk_int8(const rvd_avx_int8_t r0) {
	rvm_avx_int8_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_uint64_t mipp_avx_tomsk_uint64(const rvd_avx_uint64_t r0) {
	rvm_avx_uint64_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_uint32_t mipp_avx_tomsk_uint32(const rvd_avx_uint32_t r0) {
	rvm_avx_uint32_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_uint16_t mipp_avx_tomsk_uint16(const rvd_avx_uint16_t r0) {
	rvm_avx_uint16_t res;
	res.m = r0.m;
	return res;
}
rvm_avx_uint8_t mipp_avx_tomsk_uint8(const rvd_avx_uint8_t r0) {
	rvm_avx_uint8_t res;
	res.m = r0.m;
	return res;
}
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_float64_t mipp_avx_load_float64(const float64_t* p0) {
	rvd_avx_float64_t res;
	res.m = _mm256_load_pd((float64_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_float32_t mipp_avx_load_float32(const float32_t* p0) {
	rvd_avx_float32_t res;
	res.m = _mm256_load_ps((float32_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_int64_t mipp_avx_load_int64(const int64_t* p0) {
	rvd_avx_int64_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_int32_t mipp_avx_load_int32(const int32_t* p0) {
	rvd_avx_int32_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_int16_t mipp_avx_load_int16(const int16_t* p0) {
	rvd_avx_int16_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_int8_t mipp_avx_load_int8(const int8_t* p0) {
	rvd_avx_int8_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint64_t mipp_avx_load_uint64(const uint64_t* p0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint32_t mipp_avx_load_uint32(const uint32_t* p0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint16_t mipp_avx_load_uint16(const uint16_t* p0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint8_t mipp_avx_load_uint8(const uint8_t* p0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_load_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_float64_t mipp_avx_load_float64(const float64_t* p0) {
	rvd_avx_float64_t res;
	res.m = _mm256_loadu_pd((float64_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_float32_t mipp_avx_load_float32(const float32_t* p0) {
	rvd_avx_float32_t res;
	res.m = _mm256_loadu_ps((float32_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_int64_t mipp_avx_load_int64(const int64_t* p0) {
	rvd_avx_int64_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_int32_t mipp_avx_load_int32(const int32_t* p0) {
	rvd_avx_int32_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_int16_t mipp_avx_load_int16(const int16_t* p0) {
	rvd_avx_int16_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_int8_t mipp_avx_load_int8(const int8_t* p0) {
	rvd_avx_int8_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint64_t mipp_avx_load_uint64(const uint64_t* p0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint32_t mipp_avx_load_uint32(const uint32_t* p0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint16_t mipp_avx_load_uint16(const uint16_t* p0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx_uint8_t mipp_avx_load_uint8(const uint8_t* p0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_loadu_float64(const float64_t* p0) {
	rvd_avx_float64_t res;
	res.m = _mm256_loadu_pd((float64_t*) p0);
	return res;
}
rvd_avx_float32_t mipp_avx_loadu_float32(const float32_t* p0) {
	rvd_avx_float32_t res;
	res.m = _mm256_loadu_ps((float32_t*) p0);
	return res;
}
rvd_avx_int64_t mipp_avx_loadu_int64(const int64_t* p0) {
	rvd_avx_int64_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_int32_t mipp_avx_loadu_int32(const int32_t* p0) {
	rvd_avx_int32_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_int16_t mipp_avx_loadu_int16(const int16_t* p0) {
	rvd_avx_int16_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_int8_t mipp_avx_loadu_int8(const int8_t* p0) {
	rvd_avx_int8_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_uint64_t mipp_avx_loadu_uint64(const uint64_t* p0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_uint32_t mipp_avx_loadu_uint32(const uint32_t* p0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_uint16_t mipp_avx_loadu_uint16(const uint16_t* p0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
rvd_avx_uint8_t mipp_avx_loadu_uint8(const uint8_t* p0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_loadu_si256((__m256i*) p0);
	return res;
}
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_float64(float64_t* p0, const rvd_avx_float64_t r0) {
	_mm256_store_pd((float64_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_float32(float32_t* p0, const rvd_avx_float32_t r0) {
	_mm256_store_ps((float32_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int64(int64_t* p0, const rvd_avx_int64_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int32(int32_t* p0, const rvd_avx_int32_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int16(int16_t* p0, const rvd_avx_int16_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int8(int8_t* p0, const rvd_avx_int8_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint64(uint64_t* p0, const rvd_avx_uint64_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint32(uint32_t* p0, const rvd_avx_uint32_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint16(uint16_t* p0, const rvd_avx_uint16_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint8(uint8_t* p0, const rvd_avx_uint8_t r0) {
	_mm256_store_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_float64(float64_t* p0, const rvd_avx_float64_t r0) {
	_mm256_storeu_pd((float64_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_float32(float32_t* p0, const rvd_avx_float32_t r0) {
	_mm256_storeu_ps((float32_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int64(int64_t* p0, const rvd_avx_int64_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int32(int32_t* p0, const rvd_avx_int32_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int16(int16_t* p0, const rvd_avx_int16_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_int8(int8_t* p0, const rvd_avx_int8_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint64(uint64_t* p0, const rvd_avx_uint64_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint32(uint32_t* p0, const rvd_avx_uint32_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint16(uint16_t* p0, const rvd_avx_uint16_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx_store_uint8(uint8_t* p0, const rvd_avx_uint8_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
#endif
void mipp_avx_storeu_float64(float64_t* p0, const rvd_avx_float64_t r0) {
	_mm256_storeu_pd((float64_t*) p0, r0.m);
}
void mipp_avx_storeu_float32(float32_t* p0, const rvd_avx_float32_t r0) {
	_mm256_storeu_ps((float32_t*) p0, r0.m);
}
void mipp_avx_storeu_int64(int64_t* p0, const rvd_avx_int64_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_int32(int32_t* p0, const rvd_avx_int32_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_int16(int16_t* p0, const rvd_avx_int16_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_int8(int8_t* p0, const rvd_avx_int8_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_uint64(uint64_t* p0, const rvd_avx_uint64_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_uint32(uint32_t* p0, const rvd_avx_uint32_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_uint16(uint16_t* p0, const rvd_avx_uint16_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
void mipp_avx_storeu_uint8(uint8_t* p0, const rvd_avx_uint8_t r0) {
	_mm256_storeu_si256((__m256i*) p0, r0.m);
}
rvd_avx_float64_t mipp_avx_set1_float64(const float64_t v0) {
	rvd_avx_float64_t res;
	res.m = _mm256_set1_pd(v0);
	return res;
}
rvd_avx_float32_t mipp_avx_set1_float32(const float32_t v0) {
	rvd_avx_float32_t res;
	res.m = _mm256_set1_ps(v0);
	return res;
}
rvd_avx_int64_t mipp_avx_set1_int64(const int64_t v0) {
	rvd_avx_int64_t res;
	res.m = _mm256_set1_epi64x(v0);
	return res;
}
rvd_avx_int32_t mipp_avx_set1_int32(const int32_t v0) {
	rvd_avx_int32_t res;
	res.m = _mm256_set1_epi32(v0);
	return res;
}
rvd_avx_int16_t mipp_avx_set1_int16(const int16_t v0) {
	rvd_avx_int16_t res;
	res.m = _mm256_set1_epi16(v0);
	return res;
}
rvd_avx_int8_t mipp_avx_set1_int8(const int8_t v0) {
	rvd_avx_int8_t res;
	res.m = _mm256_set1_epi8(v0);
	return res;
}
rvd_avx_float64_t mipp_avx_set0_float64() {
	rvd_avx_float64_t res;
	res.m = _mm256_setzero_pd();
	return res;
}
rvd_avx_float32_t mipp_avx_set0_float32() {
	rvd_avx_float32_t res;
	res.m = _mm256_setzero_ps();
	return res;
}
rvd_avx_int64_t mipp_avx_set0_int64() {
	rvd_avx_int64_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_int32_t mipp_avx_set0_int32() {
	rvd_avx_int32_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_int16_t mipp_avx_set0_int16() {
	rvd_avx_int16_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_int8_t mipp_avx_set0_int8() {
	rvd_avx_int8_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_uint64_t mipp_avx_set0_uint64() {
	rvd_avx_uint64_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_uint32_t mipp_avx_set0_uint32() {
	rvd_avx_uint32_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_uint16_t mipp_avx_set0_uint16() {
	rvd_avx_uint16_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvd_avx_uint8_t mipp_avx_set0_uint8() {
	rvd_avx_uint8_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_float64_t mipp_avx_set0_k_float64() {
	rvm_avx_float64_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_float32_t mipp_avx_set0_k_float32() {
	rvm_avx_float32_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_int64_t mipp_avx_set0_k_int64() {
	rvm_avx_int64_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_int32_t mipp_avx_set0_k_int32() {
	rvm_avx_int32_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_int16_t mipp_avx_set0_k_int16() {
	rvm_avx_int16_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_int8_t mipp_avx_set0_k_int8() {
	rvm_avx_int8_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_uint64_t mipp_avx_set0_k_uint64() {
	rvm_avx_uint64_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_uint32_t mipp_avx_set0_k_uint32() {
	rvm_avx_uint32_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_uint16_t mipp_avx_set0_k_uint16() {
	rvm_avx_uint16_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
rvm_avx_uint8_t mipp_avx_set0_k_uint8() {
	rvm_avx_uint8_t res;
	res.m = _mm256_setzero_si256();
	return res;
}
float64_t mipp_avx_getfirst_float64(const rvd_avx_float64_t r0) {
	return (float64_t)_mm256_extract_epi64(mipp_avx_cast_float64_int64(r0).m, 0);
}
float32_t mipp_avx_getfirst_float32(const rvd_avx_float32_t r0) {
	return (float32_t)_mm256_extract_epi32(mipp_avx_cast_float32_int32(r0).m, 0);
}
int64_t mipp_avx_getfirst_int64(const rvd_avx_int64_t r0) {
	return (int64_t)_mm256_extract_epi64(mipp_avx_cast_int64_int64(r0).m, 0);
}
int32_t mipp_avx_getfirst_int32(const rvd_avx_int32_t r0) {
	return (int32_t)_mm256_extract_epi32(mipp_avx_cast_int32_int32(r0).m, 0);
}
uint64_t mipp_avx_getfirst_uint64(const rvd_avx_uint64_t r0) {
	return (uint64_t)_mm256_extract_epi64(mipp_avx_cast_uint64_int64(r0).m, 0);
}
uint32_t mipp_avx_getfirst_uint32(const rvd_avx_uint32_t r0) {
	return (uint32_t)_mm256_extract_epi32(mipp_avx_cast_uint32_int32(r0).m, 0);
}
#if defined(__AVX2__)
int16_t mipp_avx_getfirst_int16(const rvd_avx_int16_t r0) {
	return (int16_t)_mm256_extract_epi16(mipp_avx_cast_int16_int16(r0).m, 0);
}
#endif
#if defined(__AVX2__)
int8_t mipp_avx_getfirst_int8(const rvd_avx_int8_t r0) {
	return (int8_t)_mm256_extract_epi8(mipp_avx_cast_int8_int8(r0).m, 0);
}
#endif
#if defined(__AVX2__)
uint16_t mipp_avx_getfirst_uint16(const rvd_avx_uint16_t r0) {
	return (uint16_t)_mm256_extract_epi16(mipp_avx_cast_uint16_int16(r0).m, 0);
}
#endif
#if defined(__AVX2__)
uint8_t mipp_avx_getfirst_uint8(const rvd_avx_uint8_t r0) {
	return (uint8_t)_mm256_extract_epi8(mipp_avx_cast_uint8_int8(r0).m, 0);
}
#endif
rvd_avx_float64_t mipp_avx_sqrt_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float64_t res;
	res.m = _mm256_sqrt_pd(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_sqrt_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_sqrt_ps(r0.m);
	return res;
}
rvd_avx_float32_t mipp_avx_rsqrt_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t res;
	res.m = _mm256_rsqrt_ps(r0.m);
	return res;
}
rvd_avx_float64_t mipp_avx_add_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_add_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_add_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_add_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_add_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_int64_t res;
	res.m = _mm256_add_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_add_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_add_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_add_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_adds_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_add_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_adds_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_add_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_adds_epu16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_add_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_adds_epu8(r0.m, r1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_sub_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_sub_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_sub_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_sub_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_sub_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_int64_t res;
	res.m = _mm256_sub_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_sub_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_sub_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_sub_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_subs_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_sub_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_subs_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_sub_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_subs_epu16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_sub_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_subs_epu8(r0.m, r1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_mul_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_mul_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_mul_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_mul_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_mul_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_mullo_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_mul_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_mullo_epi16(r0.m, r1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_div_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_div_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_div_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_div_ps(r0.m, r1.m);
	return res;
}
rvd_avx_float64_t mipp_avx_min_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_min_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_min_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_min_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_min_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_min_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_min_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_min_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_min_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_min_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_min_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_uint32_t res;
	res.m = _mm256_min_epu32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_min_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_min_epu16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_min_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_min_epu8(r0.m, r1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_max_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_max_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_max_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_max_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_max_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_max_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_max_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_max_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_max_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_max_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_max_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_uint32_t res;
	res.m = _mm256_max_epu32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_max_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_max_epu16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_max_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_max_epu8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__FMA__)
rvd_avx_float64_t mipp_avx_fmadd_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res;
	res.m = _mm256_fmadd_pd(r0.m, r1.m, r2.m);
	return res;
}
#endif
#if defined(__FMA__)
rvd_avx_float32_t mipp_avx_fmadd_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res;
	res.m = _mm256_fmadd_ps(r0.m, r1.m, r2.m);
	return res;
}
#endif
