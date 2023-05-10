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
typedef struct { __m256 m; } rvd_avx_float32_t;
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
#if defined(__FMA__)
rvd_avx_float64_t mipp_avx_fmsub_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res;
	res.m = _mm256_fmsub_pd(r0.m, r1.m, r2.m);
	return res;
}
#endif
#if defined(__FMA__)
rvd_avx_float32_t mipp_avx_fmsub_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res;
	res.m = _mm256_fmsub_ps(r0.m, r1.m, r2.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_andb_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_and_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_andb_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_and_ps(r0.m, r1.m);
	return res;
}
#if !defined(__AVX2__)
rvd_avx_int64_t mipp_avx_andb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int32_t mipp_avx_andb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int16_t mipp_avx_andb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int8_t mipp_avx_andb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int8(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_andb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_andb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_andb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_andb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint8(resf);
}
#endif
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_andb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_int64_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_andb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_andb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_andb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_andb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_uint64_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_andb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_uint32_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_andb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_andb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_and_si256(r0.m, r1.m);
	return res;
}
#endif
#if !defined(__AVX2__)
rvm_avx_int64_t mipp_avx_andb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_int64(mipp_avx_cast_float32_int64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int32_t mipp_avx_andb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_int32(mipp_avx_cast_float32_int32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int16_t mipp_avx_andb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_int16(mipp_avx_cast_float32_int16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int8_t mipp_avx_andb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_int8(mipp_avx_cast_float32_int8(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_andb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint64(mipp_avx_cast_float32_uint64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_andb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint32(mipp_avx_cast_float32_uint32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_andb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint16(mipp_avx_cast_float32_uint16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_andb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint8(mipp_avx_cast_float32_uint8(resf));
}
#endif
#if defined(__AVX2__)
rvm_avx_float64_t mipp_avx_andb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	rvm_avx_float64_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_float32_t mipp_avx_andb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	rvm_avx_float32_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int64_t mipp_avx_andb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvm_avx_int64_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int32_t mipp_avx_andb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvm_avx_int32_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int16_t mipp_avx_andb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvm_avx_int16_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int8_t mipp_avx_andb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvm_avx_int8_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_andb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvm_avx_uint64_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_andb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvm_avx_uint32_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_andb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvm_avx_uint16_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_andb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvm_avx_uint8_t res;
	res.m = _mm256_and_si256(m0.m, m1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_andnb_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_andnot_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_andnb_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_andnot_ps(r0.m, r1.m);
	return res;
}
#if !defined(__AVX2__)
rvd_avx_int64_t mipp_avx_andnb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int32_t mipp_avx_andnb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int16_t mipp_avx_andnb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int8_t mipp_avx_andnb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int8(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_andnb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_andnb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_andnb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_andnb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint8(resf);
}
#endif
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_andnb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_int64_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_andnb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_andnb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_andnb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_andnb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_uint64_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_andnb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_uint32_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_andnb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_andnb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_andnot_si256(r0.m, r1.m);
	return res;
}
#endif
#if !defined(__AVX2__)
rvm_avx_int64_t mipp_avx_andnb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_int64(mipp_avx_cast_float32_int64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int32_t mipp_avx_andnb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_int32(mipp_avx_cast_float32_int32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int16_t mipp_avx_andnb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_int16(mipp_avx_cast_float32_int16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int8_t mipp_avx_andnb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_int8(mipp_avx_cast_float32_int8(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_andnb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint64(mipp_avx_cast_float32_uint64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_andnb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint32(mipp_avx_cast_float32_uint32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_andnb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint16(mipp_avx_cast_float32_uint16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_andnb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_andnb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint8(mipp_avx_cast_float32_uint8(resf));
}
#endif
#if defined(__AVX2__)
rvm_avx_float64_t mipp_avx_andnb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	rvm_avx_float64_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_float32_t mipp_avx_andnb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	rvm_avx_float32_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int64_t mipp_avx_andnb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvm_avx_int64_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int32_t mipp_avx_andnb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvm_avx_int32_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int16_t mipp_avx_andnb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvm_avx_int16_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int8_t mipp_avx_andnb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvm_avx_int8_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_andnb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvm_avx_uint64_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_andnb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvm_avx_uint32_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_andnb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvm_avx_uint16_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_andnb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvm_avx_uint8_t res;
	res.m = _mm256_andnot_si256(m0.m, m1.m);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_xorb_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t res;
	res.m = _mm256_xor_pd(r0.m, r1.m);
	return res;
}
rvd_avx_float32_t mipp_avx_xorb_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t res;
	res.m = _mm256_xor_ps(r0.m, r1.m);
	return res;
}
#if !defined(__AVX2__)
rvd_avx_int64_t mipp_avx_xorb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int32_t mipp_avx_xorb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int16_t mipp_avx_xorb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_int8_t mipp_avx_xorb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_int8(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_xorb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint64_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint64_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint64(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_xorb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint32_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint32(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_xorb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint16_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint16_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint16(resf);
}
#endif
#if !defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_xorb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint8_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint8_float32(r1);
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_cast_float32_uint8(resf);
}
#endif
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_xorb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvd_avx_int64_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_xorb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvd_avx_int32_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_xorb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvd_avx_int16_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_xorb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvd_avx_int8_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_xorb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	rvd_avx_uint64_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_xorb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	rvd_avx_uint32_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_xorb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	rvd_avx_uint16_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_xorb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	rvd_avx_uint8_t res;
	res.m = _mm256_xor_si256(r0.m, r1.m);
	return res;
}
#endif
#if !defined(__AVX2__)
rvm_avx_int64_t mipp_avx_xorb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_int64(mipp_avx_cast_float32_int64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int32_t mipp_avx_xorb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_int32(mipp_avx_cast_float32_int32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int16_t mipp_avx_xorb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_int16(mipp_avx_cast_float32_int16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_int8_t mipp_avx_xorb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_int8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_int8(mipp_avx_cast_float32_int8(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_xorb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint64_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint64(mipp_avx_cast_float32_uint64(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_xorb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint32_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint32(mipp_avx_cast_float32_uint32(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_xorb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint16_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint16(mipp_avx_cast_float32_uint16(resf));
}
#endif
#if !defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_xorb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvd_avx_float32_t r0f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m0));
	rvd_avx_float32_t r1f = mipp_avx_toreg_float32(mipp_avx_cast_k_uint8_float32(m1));
	rvd_avx_float32_t resf = mipp_avx_xorb_float32(r0f, r1f);
	return mipp_avx_tomsk_uint8(mipp_avx_cast_float32_uint8(resf));
}
#endif
#if defined(__AVX2__)
rvm_avx_float64_t mipp_avx_xorb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	rvm_avx_float64_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_float32_t mipp_avx_xorb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	rvm_avx_float32_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int64_t mipp_avx_xorb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	rvm_avx_int64_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int32_t mipp_avx_xorb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	rvm_avx_int32_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int16_t mipp_avx_xorb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	rvm_avx_int16_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int8_t mipp_avx_xorb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	rvm_avx_int8_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint64_t mipp_avx_xorb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	rvm_avx_uint64_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint32_t mipp_avx_xorb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	rvm_avx_uint32_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint16_t mipp_avx_xorb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	rvm_avx_uint16_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_uint8_t mipp_avx_xorb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	rvm_avx_uint8_t res;
	res.m = _mm256_xor_si256(m0.m, m1.m);
	return res;
}
#endif
rvm_avx_float64_t mipp_avx_cmpeq_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t tmp;
	tmp.m = _mm256_cmp_pd(r0.m, r1.m, _CMP_EQ_OQ);
	return mipp_avx_tomsk_float64(tmp);
}
rvm_avx_float32_t mipp_avx_cmpeq_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t tmp;
	tmp.m = _mm256_cmp_ps(r0.m, r1.m, _CMP_EQ_OQ);
	return mipp_avx_tomsk_float32(tmp);
}
#if defined(__AVX2__)
rvm_avx_int64_t mipp_avx_cmpeq_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	rvm_avx_int64_t res;
	res.m = _mm256_cmpeq_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int32_t mipp_avx_cmpeq_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	rvm_avx_int32_t res;
	res.m = _mm256_cmpeq_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int16_t mipp_avx_cmpeq_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	rvm_avx_int16_t res;
	res.m = _mm256_cmpeq_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvm_avx_int8_t mipp_avx_cmpeq_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	rvm_avx_int8_t res;
	res.m = _mm256_cmpeq_epi8(r0.m, r1.m);
	return res;
}
#endif
rvm_avx_float64_t mipp_avx_cmpneq_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
	rvd_avx_float64_t tmp;
	tmp.m = _mm256_cmp_pd(r0.m, r1.m, _CMP_NEQ_OQ);
	return mipp_avx_tomsk_float64(tmp);
}
rvm_avx_float32_t mipp_avx_cmpneq_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	rvd_avx_float32_t tmp;
	tmp.m = _mm256_cmp_ps(r0.m, r1.m, _CMP_NEQ_OQ);
	return mipp_avx_tomsk_float32(tmp);
}
rvd_avx_float64_t mipp_avx_blend_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t res;
	res.m = _mm256_blendv_pd(r0.m, r1.m, mipp_avx_toreg_float64(m0).m);
	return res;
}
rvd_avx_float32_t mipp_avx_blend_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t res;
	res.m = _mm256_blendv_ps(r0.m, r1.m, mipp_avx_toreg_float32(m0).m);
	return res;
}
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_blend_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	rvd_avx_int64_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_blend_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_blend_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_blend_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint64_t mipp_avx_blend_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	rvd_avx_uint64_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_blend_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	rvd_avx_uint32_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_blend_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_blend_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t res;
	res.m = _mm256_blendv_epi8(r0.m, r1.m, m0.m);
	return res;
}
#endif
int32_t mipp_avx_testz_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
int32_t mipp_avx_testz_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	return _mm256_testz_si256(m0.m, m1.m);
}
rvd_avx_float64_t mipp_avx_hadd_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float64_float32(r0).m, mipp_avx_cast_float64_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float64_t rs1 = mipp_avx_cast_float32_float64(rsf);
	rs1.m = _mm256_add_pd(r0.m, rs1.m);
	rsf = mipp_avx_cast_float64_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float64_t rs2 = mipp_avx_cast_float32_float64(rsf);
	rs2.m = _mm256_add_pd(rs1.m, rs2.m);
	return rs2;
}
#if defined(__AVX2__)
rvd_avx_int64_t mipp_avx_hadd_int64(const rvd_avx_int64_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int64_float32(r0).m, mipp_avx_cast_int64_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int64_t rs1 = mipp_avx_cast_float32_int64(rsf);
	rs1.m = _mm256_add_epi64(r0.m, rs1.m);
	rsf = mipp_avx_cast_int64_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int64_t rs2 = mipp_avx_cast_float32_int64(rsf);
	rs2.m = _mm256_add_epi64(rs1.m, rs2.m);
	return rs2;
}
#endif
rvd_avx_float32_t mipp_avx_hadd_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float32_float32(r0).m, mipp_avx_cast_float32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float32_t rs1 = mipp_avx_cast_float32_float32(rsf);
	rs1.m = _mm256_add_ps(r0.m, rs1.m);
	rsf = mipp_avx_cast_float32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float32_t rs2 = mipp_avx_cast_float32_float32(rsf);
	rs2.m = _mm256_add_ps(rs1.m, rs2.m);
	rsf = mipp_avx_cast_float32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_float32_t rs3 = mipp_avx_cast_float32_float32(rsf);
	rs3.m = _mm256_add_ps(rs2.m, rs3.m);
	return rs3;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_hadd_int32(const rvd_avx_int32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int32_float32(r0).m, mipp_avx_cast_int32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int32_t rs1 = mipp_avx_cast_float32_int32(rsf);
	rs1.m = _mm256_add_epi32(r0.m, rs1.m);
	rsf = mipp_avx_cast_int32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int32_t rs2 = mipp_avx_cast_float32_int32(rsf);
	rs2.m = _mm256_add_epi32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int32_t rs3 = mipp_avx_cast_float32_int32(rsf);
	rs3.m = _mm256_add_epi32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_hadd_int16(const rvd_avx_int16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int16_float32(r0).m, mipp_avx_cast_int16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int16_t rs1 = mipp_avx_cast_float32_int16(rsf);
	rs1.m = _mm256_adds_epi16(r0.m, rs1.m);
	rsf = mipp_avx_cast_int16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int16_t rs2 = mipp_avx_cast_float32_int16(rsf);
	rs2.m = _mm256_adds_epi16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int16_t rs3 = mipp_avx_cast_float32_int16(rsf);
	rs3.m = _mm256_adds_epi16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int16_t rs4 = mipp_avx_cast_int8_int16(rsi);
	rs4.m = _mm256_adds_epi16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_hadd_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint16_float32(r0).m, mipp_avx_cast_uint16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint16_t rs1 = mipp_avx_cast_float32_uint16(rsf);
	rs1.m = _mm256_adds_epu16(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint16_t rs2 = mipp_avx_cast_float32_uint16(rsf);
	rs2.m = _mm256_adds_epu16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint16_t rs3 = mipp_avx_cast_float32_uint16(rsf);
	rs3.m = _mm256_adds_epu16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint16_t rs4 = mipp_avx_cast_int8_uint16(rsi);
	rs4.m = _mm256_adds_epu16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_hadd_int8(const rvd_avx_int8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int8_float32(r0).m, mipp_avx_cast_int8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int8_t rs1 = mipp_avx_cast_float32_int8(rsf);
	rs1.m = _mm256_adds_epi8(r0.m, rs1.m);
	rsf = mipp_avx_cast_int8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int8_t rs2 = mipp_avx_cast_float32_int8(rsf);
	rs2.m = _mm256_adds_epi8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int8_t rs3 = mipp_avx_cast_float32_int8(rsf);
	rs3.m = _mm256_adds_epi8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int8_t rs4 = mipp_avx_cast_int8_int8(rsi);
	rs4.m = _mm256_adds_epi8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_int8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_int8_t rs5 = mipp_avx_cast_int8_int8(rsi);
	rs5.m = _mm256_adds_epi8(rs4.m, rs5.m);
	return rs5;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_hadd_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint8_float32(r0).m, mipp_avx_cast_uint8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint8_t rs1 = mipp_avx_cast_float32_uint8(rsf);
	rs1.m = _mm256_adds_epu8(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint8_t rs2 = mipp_avx_cast_float32_uint8(rsf);
	rs2.m = _mm256_adds_epu8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint8_t rs3 = mipp_avx_cast_float32_uint8(rsf);
	rs3.m = _mm256_adds_epu8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint8_t rs4 = mipp_avx_cast_int8_uint8(rsi);
	rs4.m = _mm256_adds_epu8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_uint8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_uint8_t rs5 = mipp_avx_cast_int8_uint8(rsi);
	rs5.m = _mm256_adds_epu8(rs4.m, rs5.m);
	return rs5;
}
#endif
rvd_avx_float64_t mipp_avx_hmul_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float64_float32(r0).m, mipp_avx_cast_float64_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float64_t rs1 = mipp_avx_cast_float32_float64(rsf);
	rs1.m = _mm256_mul_pd(r0.m, rs1.m);
	rsf = mipp_avx_cast_float64_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float64_t rs2 = mipp_avx_cast_float32_float64(rsf);
	rs2.m = _mm256_mul_pd(rs1.m, rs2.m);
	return rs2;
}
rvd_avx_float32_t mipp_avx_hmul_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float32_float32(r0).m, mipp_avx_cast_float32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float32_t rs1 = mipp_avx_cast_float32_float32(rsf);
	rs1.m = _mm256_mul_ps(r0.m, rs1.m);
	rsf = mipp_avx_cast_float32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float32_t rs2 = mipp_avx_cast_float32_float32(rsf);
	rs2.m = _mm256_mul_ps(rs1.m, rs2.m);
	rsf = mipp_avx_cast_float32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_float32_t rs3 = mipp_avx_cast_float32_float32(rsf);
	rs3.m = _mm256_mul_ps(rs2.m, rs3.m);
	return rs3;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_hmul_int32(const rvd_avx_int32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int32_float32(r0).m, mipp_avx_cast_int32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int32_t rs1 = mipp_avx_cast_float32_int32(rsf);
	rs1.m = _mm256_mullo_epi32(r0.m, rs1.m);
	rsf = mipp_avx_cast_int32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int32_t rs2 = mipp_avx_cast_float32_int32(rsf);
	rs2.m = _mm256_mullo_epi32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int32_t rs3 = mipp_avx_cast_float32_int32(rsf);
	rs3.m = _mm256_mullo_epi32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_hmul_int16(const rvd_avx_int16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int16_float32(r0).m, mipp_avx_cast_int16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int16_t rs1 = mipp_avx_cast_float32_int16(rsf);
	rs1.m = _mm256_mullo_epi16(r0.m, rs1.m);
	rsf = mipp_avx_cast_int16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int16_t rs2 = mipp_avx_cast_float32_int16(rsf);
	rs2.m = _mm256_mullo_epi16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int16_t rs3 = mipp_avx_cast_float32_int16(rsf);
	rs3.m = _mm256_mullo_epi16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int16_t rs4 = mipp_avx_cast_int8_int16(rsi);
	rs4.m = _mm256_mullo_epi16(rs3.m, rs4.m);
	return rs4;
}
#endif
rvd_avx_float64_t mipp_avx_hmin_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float64_float32(r0).m, mipp_avx_cast_float64_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float64_t rs1 = mipp_avx_cast_float32_float64(rsf);
	rs1.m = _mm256_min_pd(r0.m, rs1.m);
	rsf = mipp_avx_cast_float64_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float64_t rs2 = mipp_avx_cast_float32_float64(rsf);
	rs2.m = _mm256_min_pd(rs1.m, rs2.m);
	return rs2;
}
rvd_avx_float32_t mipp_avx_hmin_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float32_float32(r0).m, mipp_avx_cast_float32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float32_t rs1 = mipp_avx_cast_float32_float32(rsf);
	rs1.m = _mm256_min_ps(r0.m, rs1.m);
	rsf = mipp_avx_cast_float32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float32_t rs2 = mipp_avx_cast_float32_float32(rsf);
	rs2.m = _mm256_min_ps(rs1.m, rs2.m);
	rsf = mipp_avx_cast_float32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_float32_t rs3 = mipp_avx_cast_float32_float32(rsf);
	rs3.m = _mm256_min_ps(rs2.m, rs3.m);
	return rs3;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_hmin_int32(const rvd_avx_int32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int32_float32(r0).m, mipp_avx_cast_int32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int32_t rs1 = mipp_avx_cast_float32_int32(rsf);
	rs1.m = _mm256_min_epi32(r0.m, rs1.m);
	rsf = mipp_avx_cast_int32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int32_t rs2 = mipp_avx_cast_float32_int32(rsf);
	rs2.m = _mm256_min_epi32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int32_t rs3 = mipp_avx_cast_float32_int32(rsf);
	rs3.m = _mm256_min_epi32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_hmin_uint32(const rvd_avx_uint32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint32_float32(r0).m, mipp_avx_cast_uint32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint32_t rs1 = mipp_avx_cast_float32_uint32(rsf);
	rs1.m = _mm256_min_epu32(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint32_t rs2 = mipp_avx_cast_float32_uint32(rsf);
	rs2.m = _mm256_min_epu32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint32_t rs3 = mipp_avx_cast_float32_uint32(rsf);
	rs3.m = _mm256_min_epu32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_hmin_int16(const rvd_avx_int16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int16_float32(r0).m, mipp_avx_cast_int16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int16_t rs1 = mipp_avx_cast_float32_int16(rsf);
	rs1.m = _mm256_min_epi16(r0.m, rs1.m);
	rsf = mipp_avx_cast_int16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int16_t rs2 = mipp_avx_cast_float32_int16(rsf);
	rs2.m = _mm256_min_epi16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int16_t rs3 = mipp_avx_cast_float32_int16(rsf);
	rs3.m = _mm256_min_epi16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int16_t rs4 = mipp_avx_cast_int8_int16(rsi);
	rs4.m = _mm256_min_epi16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_hmin_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint16_float32(r0).m, mipp_avx_cast_uint16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint16_t rs1 = mipp_avx_cast_float32_uint16(rsf);
	rs1.m = _mm256_min_epu16(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint16_t rs2 = mipp_avx_cast_float32_uint16(rsf);
	rs2.m = _mm256_min_epu16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint16_t rs3 = mipp_avx_cast_float32_uint16(rsf);
	rs3.m = _mm256_min_epu16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint16_t rs4 = mipp_avx_cast_int8_uint16(rsi);
	rs4.m = _mm256_min_epu16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_hmin_int8(const rvd_avx_int8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int8_float32(r0).m, mipp_avx_cast_int8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int8_t rs1 = mipp_avx_cast_float32_int8(rsf);
	rs1.m = _mm256_min_epi8(r0.m, rs1.m);
	rsf = mipp_avx_cast_int8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int8_t rs2 = mipp_avx_cast_float32_int8(rsf);
	rs2.m = _mm256_min_epi8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int8_t rs3 = mipp_avx_cast_float32_int8(rsf);
	rs3.m = _mm256_min_epi8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int8_t rs4 = mipp_avx_cast_int8_int8(rsi);
	rs4.m = _mm256_min_epi8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_int8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_int8_t rs5 = mipp_avx_cast_int8_int8(rsi);
	rs5.m = _mm256_min_epi8(rs4.m, rs5.m);
	return rs5;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_hmin_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint8_float32(r0).m, mipp_avx_cast_uint8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint8_t rs1 = mipp_avx_cast_float32_uint8(rsf);
	rs1.m = _mm256_min_epu8(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint8_t rs2 = mipp_avx_cast_float32_uint8(rsf);
	rs2.m = _mm256_min_epu8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint8_t rs3 = mipp_avx_cast_float32_uint8(rsf);
	rs3.m = _mm256_min_epu8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint8_t rs4 = mipp_avx_cast_int8_uint8(rsi);
	rs4.m = _mm256_min_epu8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_uint8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_uint8_t rs5 = mipp_avx_cast_int8_uint8(rsi);
	rs5.m = _mm256_min_epu8(rs4.m, rs5.m);
	return rs5;
}
#endif
rvd_avx_float64_t mipp_avx_hmax_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float64_float32(r0).m, mipp_avx_cast_float64_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float64_t rs1 = mipp_avx_cast_float32_float64(rsf);
	rs1.m = _mm256_max_pd(r0.m, rs1.m);
	rsf = mipp_avx_cast_float64_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float64_t rs2 = mipp_avx_cast_float32_float64(rsf);
	rs2.m = _mm256_max_pd(rs1.m, rs2.m);
	return rs2;
}
rvd_avx_float32_t mipp_avx_hmax_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_float32_float32(r0).m, mipp_avx_cast_float32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_float32_t rs1 = mipp_avx_cast_float32_float32(rsf);
	rs1.m = _mm256_max_ps(r0.m, rs1.m);
	rsf = mipp_avx_cast_float32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_float32_t rs2 = mipp_avx_cast_float32_float32(rsf);
	rs2.m = _mm256_max_ps(rs1.m, rs2.m);
	rsf = mipp_avx_cast_float32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_float32_t rs3 = mipp_avx_cast_float32_float32(rsf);
	rs3.m = _mm256_max_ps(rs2.m, rs3.m);
	return rs3;
}
#if defined(__AVX2__)
rvd_avx_int32_t mipp_avx_hmax_int32(const rvd_avx_int32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int32_float32(r0).m, mipp_avx_cast_int32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int32_t rs1 = mipp_avx_cast_float32_int32(rsf);
	rs1.m = _mm256_max_epi32(r0.m, rs1.m);
	rsf = mipp_avx_cast_int32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int32_t rs2 = mipp_avx_cast_float32_int32(rsf);
	rs2.m = _mm256_max_epi32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int32_t rs3 = mipp_avx_cast_float32_int32(rsf);
	rs3.m = _mm256_max_epi32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint32_t mipp_avx_hmax_uint32(const rvd_avx_uint32_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint32_float32(r0).m, mipp_avx_cast_uint32_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint32_t rs1 = mipp_avx_cast_float32_uint32(rsf);
	rs1.m = _mm256_max_epu32(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint32_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint32_t rs2 = mipp_avx_cast_float32_uint32(rsf);
	rs2.m = _mm256_max_epu32(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint32_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint32_t rs3 = mipp_avx_cast_float32_uint32(rsf);
	rs3.m = _mm256_max_epu32(rs2.m, rs3.m);
	return rs3;
}
#endif
#if defined(__AVX2__)
rvd_avx_int16_t mipp_avx_hmax_int16(const rvd_avx_int16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int16_float32(r0).m, mipp_avx_cast_int16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int16_t rs1 = mipp_avx_cast_float32_int16(rsf);
	rs1.m = _mm256_max_epi16(r0.m, rs1.m);
	rsf = mipp_avx_cast_int16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int16_t rs2 = mipp_avx_cast_float32_int16(rsf);
	rs2.m = _mm256_max_epi16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int16_t rs3 = mipp_avx_cast_float32_int16(rsf);
	rs3.m = _mm256_max_epi16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int16_t rs4 = mipp_avx_cast_int8_int16(rsi);
	rs4.m = _mm256_max_epi16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint16_t mipp_avx_hmax_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint16_float32(r0).m, mipp_avx_cast_uint16_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint16_t rs1 = mipp_avx_cast_float32_uint16(rsf);
	rs1.m = _mm256_max_epu16(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint16_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint16_t rs2 = mipp_avx_cast_float32_uint16(rsf);
	rs2.m = _mm256_max_epu16(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint16_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint16_t rs3 = mipp_avx_cast_float32_uint16(rsf);
	rs3.m = _mm256_max_epu16(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint16_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint16_t rs4 = mipp_avx_cast_int8_uint16(rsi);
	rs4.m = _mm256_max_epu16(rs3.m, rs4.m);
	return rs4;
}
#endif
#if defined(__AVX2__)
rvd_avx_int8_t mipp_avx_hmax_int8(const rvd_avx_int8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_int8_float32(r0).m, mipp_avx_cast_int8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_int8_t rs1 = mipp_avx_cast_float32_int8(rsf);
	rs1.m = _mm256_max_epi8(r0.m, rs1.m);
	rsf = mipp_avx_cast_int8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_int8_t rs2 = mipp_avx_cast_float32_int8(rsf);
	rs2.m = _mm256_max_epi8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_int8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_int8_t rs3 = mipp_avx_cast_float32_int8(rsf);
	rs3.m = _mm256_max_epi8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_int8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_int8_t rs4 = mipp_avx_cast_int8_int8(rsi);
	rs4.m = _mm256_max_epi8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_int8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_int8_t rs5 = mipp_avx_cast_int8_int8(rsi);
	rs5.m = _mm256_max_epi8(rs4.m, rs5.m);
	return rs5;
}
#endif
#if defined(__AVX2__)
rvd_avx_uint8_t mipp_avx_hmax_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_float32_t rsf;
	rsf.m = _mm256_permute2f128_ps(mipp_avx_cast_uint8_float32(r0).m, mipp_avx_cast_uint8_float32(r0).m, _MM_SHUFFLE(0,0,0,1));
	rvd_avx_uint8_t rs1 = mipp_avx_cast_float32_uint8(rsf);
	rs1.m = _mm256_max_epu8(r0.m, rs1.m);
	rsf = mipp_avx_cast_uint8_float32(rs1);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(1,0,3,2));
	rvd_avx_uint8_t rs2 = mipp_avx_cast_float32_uint8(rsf);
	rs2.m = _mm256_max_epu8(rs1.m, rs2.m);
	rsf = mipp_avx_cast_uint8_float32(rs2);
	rsf.m = _mm256_shuffle_ps(rsf.m, rsf.m, _MM_SHUFFLE(2,3,0,1));
	rvd_avx_uint8_t rs3 = mipp_avx_cast_float32_uint8(rsf);
	rs3.m = _mm256_max_epu8(rs2.m, rs3.m);
	rvd_avx_int8_t rsi = mipp_avx_cast_uint8_int8(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_16);
	rvd_avx_uint8_t rs4 = mipp_avx_cast_int8_uint8(rsi);
	rs4.m = _mm256_max_epu8(rs3.m, rs4.m);
	rsi = mipp_avx_cast_uint8_int8(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.m = _mm256_shuffle_epi8(rsi.m, mask_8);
	rvd_avx_uint8_t rs5 = mipp_avx_cast_int8_uint8(rsi);
	rs5.m = _mm256_max_epu8(rs4.m, rs5.m);
	return rs5;
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_blend_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	rvd_avx_float64_t r0f = mipp_avx_cast_int64_float64(r0);
	rvd_avx_float64_t r1f = mipp_avx_cast_int64_float64(r1);
	rvm_avx_float64_t m0f = mipp_avx_cast_k_int64_float64(m0);
	rvd_avx_float64_t resf = mipp_avx_blend_float64(r0f, r1f, m0f);
	return mipp_avx_cast_float64_int64(resf); 
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_blend_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_float32_t r0f = mipp_avx_cast_int32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_int32_float32(r1);
	rvm_avx_float32_t m0f = mipp_avx_cast_k_int32_float32(m0);
	rvd_avx_float32_t resf = mipp_avx_blend_float32(r0f, r1f, m0f);
	return mipp_avx_cast_float32_int32(resf); 
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint64_t mipp_avx_blend_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	rvd_avx_float64_t r0f = mipp_avx_cast_uint64_float64(r0);
	rvd_avx_float64_t r1f = mipp_avx_cast_uint64_float64(r1);
	rvm_avx_float64_t m0f = mipp_avx_cast_k_uint64_float64(m0);
	rvd_avx_float64_t resf = mipp_avx_blend_float64(r0f, r1f, m0f);
	return mipp_avx_cast_float64_uint64(resf); 
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_blend_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	rvd_avx_float32_t r0f = mipp_avx_cast_uint32_float32(r0);
	rvd_avx_float32_t r1f = mipp_avx_cast_uint32_float32(r1);
	rvm_avx_float32_t m0f = mipp_avx_cast_k_uint32_float32(m0);
	rvd_avx_float32_t resf = mipp_avx_blend_float32(r0f, r1f, m0f);
	return mipp_avx_cast_float32_uint32(resf); 
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_int64_t mipp_avx_blend_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	rvd_avx_int64_t rmi = mipp_avx_cast_int64_int64(mipp_avx_toreg_int64(m0));
	rvd_avx_int64_t r0i = mipp_avx_cast_int64_int64(r0);
	rvd_avx_int64_t r1i = mipp_avx_cast_int64_int64(r1);
	rvd_avx_int64_t r_0i = mipp_avx_andb_int64(rmi, r0i);
	rvd_avx_int64_t r_1i = mipp_avx_andnb_int64(rmi, r1i);
	rvd_avx_int64_t resi = mipp_avx_xorb_int64(r_0i, r_1i);
	rvd_avx_int64_t res = mipp_avx_cast_int64_int64(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_int32_t mipp_avx_blend_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rmi = mipp_avx_cast_int32_int32(mipp_avx_toreg_int32(m0));
	rvd_avx_int32_t r0i = mipp_avx_cast_int32_int32(r0);
	rvd_avx_int32_t r1i = mipp_avx_cast_int32_int32(r1);
	rvd_avx_int32_t r_0i = mipp_avx_andb_int32(rmi, r0i);
	rvd_avx_int32_t r_1i = mipp_avx_andnb_int32(rmi, r1i);
	rvd_avx_int32_t resi = mipp_avx_xorb_int32(r_0i, r_1i);
	rvd_avx_int32_t res = mipp_avx_cast_int32_int32(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_int16_t mipp_avx_blend_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rmi = mipp_avx_cast_int16_int16(mipp_avx_toreg_int16(m0));
	rvd_avx_int16_t r0i = mipp_avx_cast_int16_int16(r0);
	rvd_avx_int16_t r1i = mipp_avx_cast_int16_int16(r1);
	rvd_avx_int16_t r_0i = mipp_avx_andb_int16(rmi, r0i);
	rvd_avx_int16_t r_1i = mipp_avx_andnb_int16(rmi, r1i);
	rvd_avx_int16_t resi = mipp_avx_xorb_int16(r_0i, r_1i);
	rvd_avx_int16_t res = mipp_avx_cast_int16_int16(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_int8_t mipp_avx_blend_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t rmi = mipp_avx_cast_int8_int8(mipp_avx_toreg_int8(m0));
	rvd_avx_int8_t r0i = mipp_avx_cast_int8_int8(r0);
	rvd_avx_int8_t r1i = mipp_avx_cast_int8_int8(r1);
	rvd_avx_int8_t r_0i = mipp_avx_andb_int8(rmi, r0i);
	rvd_avx_int8_t r_1i = mipp_avx_andnb_int8(rmi, r1i);
	rvd_avx_int8_t resi = mipp_avx_xorb_int8(r_0i, r_1i);
	rvd_avx_int8_t res = mipp_avx_cast_int8_int8(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_uint64_t mipp_avx_blend_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	rvd_avx_int64_t rmi = mipp_avx_cast_uint64_int64(mipp_avx_toreg_uint64(m0));
	rvd_avx_int64_t r0i = mipp_avx_cast_uint64_int64(r0);
	rvd_avx_int64_t r1i = mipp_avx_cast_uint64_int64(r1);
	rvd_avx_int64_t r_0i = mipp_avx_andb_int64(rmi, r0i);
	rvd_avx_int64_t r_1i = mipp_avx_andnb_int64(rmi, r1i);
	rvd_avx_int64_t resi = mipp_avx_xorb_int64(r_0i, r_1i);
	rvd_avx_uint64_t res = mipp_avx_cast_int64_uint64(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_uint32_t mipp_avx_blend_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	rvd_avx_int32_t rmi = mipp_avx_cast_uint32_int32(mipp_avx_toreg_uint32(m0));
	rvd_avx_int32_t r0i = mipp_avx_cast_uint32_int32(r0);
	rvd_avx_int32_t r1i = mipp_avx_cast_uint32_int32(r1);
	rvd_avx_int32_t r_0i = mipp_avx_andb_int32(rmi, r0i);
	rvd_avx_int32_t r_1i = mipp_avx_andnb_int32(rmi, r1i);
	rvd_avx_int32_t resi = mipp_avx_xorb_int32(r_0i, r_1i);
	rvd_avx_uint32_t res = mipp_avx_cast_int32_uint32(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_uint16_t mipp_avx_blend_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_int16_t rmi = mipp_avx_cast_uint16_int16(mipp_avx_toreg_uint16(m0));
	rvd_avx_int16_t r0i = mipp_avx_cast_uint16_int16(r0);
	rvd_avx_int16_t r1i = mipp_avx_cast_uint16_int16(r1);
	rvd_avx_int16_t r_0i = mipp_avx_andb_int16(rmi, r0i);
	rvd_avx_int16_t r_1i = mipp_avx_andnb_int16(rmi, r1i);
	rvd_avx_int16_t resi = mipp_avx_xorb_int16(r_0i, r_1i);
	rvd_avx_uint16_t res = mipp_avx_cast_int16_uint16(resi);
	return res;
}
#endif
#if !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) )
rvd_avx_uint8_t mipp_avx_blend_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_int8_t rmi = mipp_avx_cast_uint8_int8(mipp_avx_toreg_uint8(m0));
	rvd_avx_int8_t r0i = mipp_avx_cast_uint8_int8(r0);
	rvd_avx_int8_t r1i = mipp_avx_cast_uint8_int8(r1);
	rvd_avx_int8_t r_0i = mipp_avx_andb_int8(rmi, r0i);
	rvd_avx_int8_t r_1i = mipp_avx_andnb_int8(rmi, r1i);
	rvd_avx_int8_t resi = mipp_avx_xorb_int8(r_0i, r_1i);
	rvd_avx_uint8_t res = mipp_avx_cast_int8_uint8(resi);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_sat_float64(const rvd_avx_float64_t r0, const float64_t v0, const float64_t v1) {
	rvd_avx_float64_t rmin = mipp_avx_set1_float64(v0);
	rvd_avx_float64_t rmax = mipp_avx_set1_float64(v1);
	rvd_avx_float64_t res = mipp_avx_max_float64(mipp_avx_min_float64(r0, rmax), rmin);
	return res;
}
rvd_avx_float32_t mipp_avx_sat_float32(const rvd_avx_float32_t r0, const float32_t v0, const float32_t v1) {
	rvd_avx_float32_t rmin = mipp_avx_set1_float32(v0);
	rvd_avx_float32_t rmax = mipp_avx_set1_float32(v1);
	rvd_avx_float32_t res = mipp_avx_max_float32(mipp_avx_min_float32(r0, rmax), rmin);
	return res;
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
rvd_avx_int32_t mipp_avx_sat_int32(const rvd_avx_int32_t r0, const int32_t v0, const int32_t v1) {
	rvd_avx_int32_t rmin = mipp_avx_set1_int32(v0);
	rvd_avx_int32_t rmax = mipp_avx_set1_int32(v1);
	rvd_avx_int32_t res = mipp_avx_max_int32(mipp_avx_min_int32(r0, rmax), rmin);
	return res;
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
rvd_avx_int16_t mipp_avx_sat_int16(const rvd_avx_int16_t r0, const int16_t v0, const int16_t v1) {
	rvd_avx_int16_t rmin = mipp_avx_set1_int16(v0);
	rvd_avx_int16_t rmax = mipp_avx_set1_int16(v1);
	rvd_avx_int16_t res = mipp_avx_max_int16(mipp_avx_min_int16(r0, rmax), rmin);
	return res;
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
rvd_avx_int8_t mipp_avx_sat_int8(const rvd_avx_int8_t r0, const int8_t v0, const int8_t v1) {
	rvd_avx_int8_t rmin = mipp_avx_set1_int8(v0);
	rvd_avx_int8_t rmax = mipp_avx_set1_int8(v1);
	rvd_avx_int8_t res = mipp_avx_max_int8(mipp_avx_min_int8(r0, rmax), rmin);
	return res;
}
#endif
#if !( defined(__FMA__) )
rvd_avx_float64_t mipp_avx_fmadd_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t rmul = mipp_avx_mul_float64(r0, r1);
	rvd_avx_float64_t res = mipp_avx_add_float64(rmul, r2);
	return res;
}
#endif
#if !( defined(__FMA__) )
rvd_avx_float32_t mipp_avx_fmadd_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t rmul = mipp_avx_mul_float32(r0, r1);
	rvd_avx_float32_t res = mipp_avx_add_float32(rmul, r2);
	return res;
}
#endif
#if !( defined(__FMA__) )
rvd_avx_float64_t mipp_avx_fmsub_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t rmul = mipp_avx_mul_float64(r0, r1);
	rvd_avx_float64_t res = mipp_avx_sub_float64(rmul, r2);
	return res;
}
#endif
#if !( defined(__FMA__) )
rvd_avx_float32_t mipp_avx_fmsub_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t rmul = mipp_avx_mul_float32(r0, r1);
	rvd_avx_float32_t res = mipp_avx_sub_float32(rmul, r2);
	return res;
}
#endif
rvd_avx_float64_t mipp_avx_add_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_add_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_add_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_add_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int64_t mipp_avx_add_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	rvd_avx_int64_t res = mipp_avx_add_int64(r0, r1);
	return mipp_avx_blend_int64(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_add_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	rvd_avx_int32_t res = mipp_avx_add_int32(r0, r1);
	return mipp_avx_blend_int32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_add_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	rvd_avx_int16_t res = mipp_avx_add_int16(r0, r1);
	return mipp_avx_blend_int16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_add_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	rvd_avx_int8_t res = mipp_avx_add_int8(r0, r1);
	return mipp_avx_blend_int8(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_add_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	rvd_avx_uint16_t res = mipp_avx_add_uint16(r0, r1);
	return mipp_avx_blend_uint16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_add_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	rvd_avx_uint8_t res = mipp_avx_add_uint8(r0, r1);
	return mipp_avx_blend_uint8(res, r2, m0);
}
#endif
rvd_avx_float64_t mipp_avx_add_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_add_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_add_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_add_m_float32(r0, r1, m0, rz);
}
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int64_t mipp_avx_add_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	rvd_avx_int64_t rz = mipp_avx_set0_int64();
	return mipp_avx_add_m_int64(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_add_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rz = mipp_avx_set0_int32();
	return mipp_avx_add_m_int32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_add_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rz = mipp_avx_set0_int16();
	return mipp_avx_add_m_int16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_add_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t rz = mipp_avx_set0_int8();
	return mipp_avx_add_m_int8(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_add_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t rz = mipp_avx_set0_uint16();
	return mipp_avx_add_m_uint16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_add_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t rz = mipp_avx_set0_uint8();
	return mipp_avx_add_m_uint8(r0, r1, m0, rz);
}
#endif
rvd_avx_float64_t mipp_avx_sub_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_sub_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_sub_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_sub_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int64_t mipp_avx_sub_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	rvd_avx_int64_t res = mipp_avx_sub_int64(r0, r1);
	return mipp_avx_blend_int64(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_sub_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	rvd_avx_int32_t res = mipp_avx_sub_int32(r0, r1);
	return mipp_avx_blend_int32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_sub_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	rvd_avx_int16_t res = mipp_avx_sub_int16(r0, r1);
	return mipp_avx_blend_int16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_sub_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	rvd_avx_int8_t res = mipp_avx_sub_int8(r0, r1);
	return mipp_avx_blend_int8(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_sub_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	rvd_avx_uint16_t res = mipp_avx_sub_uint16(r0, r1);
	return mipp_avx_blend_uint16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_sub_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	rvd_avx_uint8_t res = mipp_avx_sub_uint8(r0, r1);
	return mipp_avx_blend_uint8(res, r2, m0);
}
#endif
rvd_avx_float64_t mipp_avx_sub_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_sub_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_sub_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_sub_m_float32(r0, r1, m0, rz);
}
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int64_t mipp_avx_sub_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	rvd_avx_int64_t rz = mipp_avx_set0_int64();
	return mipp_avx_sub_m_int64(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_sub_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rz = mipp_avx_set0_int32();
	return mipp_avx_sub_m_int32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_sub_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rz = mipp_avx_set0_int16();
	return mipp_avx_sub_m_int16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_sub_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t rz = mipp_avx_set0_int8();
	return mipp_avx_sub_m_int8(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_sub_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t rz = mipp_avx_set0_uint16();
	return mipp_avx_sub_m_uint16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_sub_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t rz = mipp_avx_set0_uint8();
	return mipp_avx_sub_m_uint8(r0, r1, m0, rz);
}
#endif
rvd_avx_float64_t mipp_avx_mul_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_mul_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_mul_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_mul_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_mul_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	rvd_avx_int32_t res = mipp_avx_mul_int32(r0, r1);
	return mipp_avx_blend_int32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_mul_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	rvd_avx_int16_t res = mipp_avx_mul_int16(r0, r1);
	return mipp_avx_blend_int16(res, r2, m0);
}
#endif
rvd_avx_float64_t mipp_avx_mul_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_mul_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_mul_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_mul_m_float32(r0, r1, m0, rz);
}
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_mul_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rz = mipp_avx_set0_int32();
	return mipp_avx_mul_m_int32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_mul_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rz = mipp_avx_set0_int16();
	return mipp_avx_mul_m_int16(r0, r1, m0, rz);
}
#endif
rvd_avx_float64_t mipp_avx_div_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_div_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_div_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_div_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
rvd_avx_float64_t mipp_avx_div_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_div_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_div_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_div_m_float32(r0, r1, m0, rz);
}
rvd_avx_float64_t mipp_avx_min_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_min_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_min_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_min_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_min_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	rvd_avx_int32_t res = mipp_avx_min_int32(r0, r1);
	return mipp_avx_blend_int32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_min_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	rvd_avx_int16_t res = mipp_avx_min_int16(r0, r1);
	return mipp_avx_blend_int16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_min_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	rvd_avx_int8_t res = mipp_avx_min_int8(r0, r1);
	return mipp_avx_blend_int8(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint32_t mipp_avx_min_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	rvd_avx_uint32_t res = mipp_avx_min_uint32(r0, r1);
	return mipp_avx_blend_uint32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_min_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	rvd_avx_uint16_t res = mipp_avx_min_uint16(r0, r1);
	return mipp_avx_blend_uint16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_min_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	rvd_avx_uint8_t res = mipp_avx_min_uint8(r0, r1);
	return mipp_avx_blend_uint8(res, r2, m0);
}
#endif
rvd_avx_float64_t mipp_avx_min_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_min_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_min_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_min_m_float32(r0, r1, m0, rz);
}
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_min_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rz = mipp_avx_set0_int32();
	return mipp_avx_min_m_int32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_min_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rz = mipp_avx_set0_int16();
	return mipp_avx_min_m_int16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_min_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t rz = mipp_avx_set0_int8();
	return mipp_avx_min_m_int8(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint32_t mipp_avx_min_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	rvd_avx_uint32_t rz = mipp_avx_set0_uint32();
	return mipp_avx_min_m_uint32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_min_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t rz = mipp_avx_set0_uint16();
	return mipp_avx_min_m_uint16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_min_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t rz = mipp_avx_set0_uint8();
	return mipp_avx_min_m_uint8(r0, r1, m0, rz);
}
#endif
rvd_avx_float64_t mipp_avx_max_m_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0, const rvd_avx_float64_t r2) {
	rvd_avx_float64_t res = mipp_avx_max_float64(r0, r1);
	return mipp_avx_blend_float64(res, r2, m0);
}
rvd_avx_float32_t mipp_avx_max_m_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0, const rvd_avx_float32_t r2) {
	rvd_avx_float32_t res = mipp_avx_max_float32(r0, r1);
	return mipp_avx_blend_float32(res, r2, m0);
}
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_max_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	rvd_avx_int32_t res = mipp_avx_max_int32(r0, r1);
	return mipp_avx_blend_int32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_max_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	rvd_avx_int16_t res = mipp_avx_max_int16(r0, r1);
	return mipp_avx_blend_int16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_max_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	rvd_avx_int8_t res = mipp_avx_max_int8(r0, r1);
	return mipp_avx_blend_int8(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint32_t mipp_avx_max_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	rvd_avx_uint32_t res = mipp_avx_max_uint32(r0, r1);
	return mipp_avx_blend_uint32(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_max_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	rvd_avx_uint16_t res = mipp_avx_max_uint16(r0, r1);
	return mipp_avx_blend_uint16(res, r2, m0);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_max_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	rvd_avx_uint8_t res = mipp_avx_max_uint8(r0, r1);
	return mipp_avx_blend_uint8(res, r2, m0);
}
#endif
rvd_avx_float64_t mipp_avx_max_mz_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvm_avx_float64_t m0) {
	rvd_avx_float64_t rz = mipp_avx_set0_float64();
	return mipp_avx_max_m_float64(r0, r1, m0, rz);
}
rvd_avx_float32_t mipp_avx_max_mz_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvm_avx_float32_t m0) {
	rvd_avx_float32_t rz = mipp_avx_set0_float32();
	return mipp_avx_max_m_float32(r0, r1, m0, rz);
}
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int32_t mipp_avx_max_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	rvd_avx_int32_t rz = mipp_avx_set0_int32();
	return mipp_avx_max_m_int32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int16_t mipp_avx_max_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	rvd_avx_int16_t rz = mipp_avx_set0_int16();
	return mipp_avx_max_m_int16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_int8_t mipp_avx_max_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	rvd_avx_int8_t rz = mipp_avx_set0_int8();
	return mipp_avx_max_m_int8(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint32_t mipp_avx_max_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	rvd_avx_uint32_t rz = mipp_avx_set0_uint32();
	return mipp_avx_max_m_uint32(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint16_t mipp_avx_max_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	rvd_avx_uint16_t rz = mipp_avx_set0_uint16();
	return mipp_avx_max_m_uint16(r0, r1, m0, rz);
}
#endif
#if ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )
rvd_avx_uint8_t mipp_avx_max_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	rvd_avx_uint8_t rz = mipp_avx_set0_uint8();
	return mipp_avx_max_m_uint8(r0, r1, m0, rz);
}
#endif
rvd_avx_float64_t mipp_avx_msb_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float64_t rm = mipp_avx_cast_int64_float64(mipp_avx_set1_int64(0x8000000000000000));
	return mipp_avx_andb_float64(r0, rm);
}
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int64_t mipp_avx_msb_int64(const rvd_avx_int64_t r0) {
	rvd_avx_int64_t rm = mipp_avx_cast_int64_int64(mipp_avx_set1_int64(0x8000000000000000));
	return mipp_avx_andb_int64(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint64_t mipp_avx_msb_uint64(const rvd_avx_uint64_t r0) {
	rvd_avx_uint64_t rm = mipp_avx_cast_int64_uint64(mipp_avx_set1_int64(0x8000000000000000));
	return mipp_avx_andb_uint64(r0, rm);
}
#endif
rvd_avx_float32_t mipp_avx_msb_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rm = mipp_avx_cast_int32_float32(mipp_avx_set1_int32(0x80000000));
	return mipp_avx_andb_float32(r0, rm);
}
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int32_t mipp_avx_msb_int32(const rvd_avx_int32_t r0) {
	rvd_avx_int32_t rm = mipp_avx_cast_int32_int32(mipp_avx_set1_int32(0x80000000));
	return mipp_avx_andb_int32(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint32_t mipp_avx_msb_uint32(const rvd_avx_uint32_t r0) {
	rvd_avx_uint32_t rm = mipp_avx_cast_int32_uint32(mipp_avx_set1_int32(0x80000000));
	return mipp_avx_andb_uint32(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int16_t mipp_avx_msb_int16(const rvd_avx_int16_t r0) {
	rvd_avx_int16_t rm = mipp_avx_cast_int16_int16(mipp_avx_set1_int16(0x8000));
	return mipp_avx_andb_int16(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint16_t mipp_avx_msb_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_uint16_t rm = mipp_avx_cast_int16_uint16(mipp_avx_set1_int16(0x8000));
	return mipp_avx_andb_uint16(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int8_t mipp_avx_msb_int8(const rvd_avx_int8_t r0) {
	rvd_avx_int8_t rm = mipp_avx_cast_int8_int8(mipp_avx_set1_int8(0x80));
	return mipp_avx_andb_int8(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint8_t mipp_avx_msb_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_uint8_t rm = mipp_avx_cast_int8_uint8(mipp_avx_set1_int8(0x80));
	return mipp_avx_andb_uint8(r0, rm);
}
#endif
rvd_avx_float64_t mipp_avx_notb_float64(const rvd_avx_float64_t r0) {
	rvd_avx_float64_t rm = mipp_avx_cast_int64_float64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF));
	return mipp_avx_andnb_float64(r0, rm);
}
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int64_t mipp_avx_notb_int64(const rvd_avx_int64_t r0) {
	rvd_avx_int64_t rm = mipp_avx_cast_int64_int64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF));
	return mipp_avx_andnb_int64(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint64_t mipp_avx_notb_uint64(const rvd_avx_uint64_t r0) {
	rvd_avx_uint64_t rm = mipp_avx_cast_int64_uint64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF));
	return mipp_avx_andnb_uint64(r0, rm);
}
#endif
rvd_avx_float32_t mipp_avx_notb_float32(const rvd_avx_float32_t r0) {
	rvd_avx_float32_t rm = mipp_avx_cast_int32_float32(mipp_avx_set1_int32(0xFFFFFFFF));
	return mipp_avx_andnb_float32(r0, rm);
}
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int32_t mipp_avx_notb_int32(const rvd_avx_int32_t r0) {
	rvd_avx_int32_t rm = mipp_avx_cast_int32_int32(mipp_avx_set1_int32(0xFFFFFFFF));
	return mipp_avx_andnb_int32(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint32_t mipp_avx_notb_uint32(const rvd_avx_uint32_t r0) {
	rvd_avx_uint32_t rm = mipp_avx_cast_int32_uint32(mipp_avx_set1_int32(0xFFFFFFFF));
	return mipp_avx_andnb_uint32(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int16_t mipp_avx_notb_int16(const rvd_avx_int16_t r0) {
	rvd_avx_int16_t rm = mipp_avx_cast_int16_int16(mipp_avx_set1_int16(0xFFFF));
	return mipp_avx_andnb_int16(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint16_t mipp_avx_notb_uint16(const rvd_avx_uint16_t r0) {
	rvd_avx_uint16_t rm = mipp_avx_cast_int16_uint16(mipp_avx_set1_int16(0xFFFF));
	return mipp_avx_andnb_uint16(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_int8_t mipp_avx_notb_int8(const rvd_avx_int8_t r0) {
	rvd_avx_int8_t rm = mipp_avx_cast_int8_int8(mipp_avx_set1_int8(0xFF));
	return mipp_avx_andnb_int8(r0, rm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvd_avx_uint8_t mipp_avx_notb_uint8(const rvd_avx_uint8_t r0) {
	rvd_avx_uint8_t rm = mipp_avx_cast_int8_uint8(mipp_avx_set1_int8(0xFF));
	return mipp_avx_andnb_uint8(r0, rm);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
rvm_avx_float64_t mipp_avx_notb_k_float64(const rvm_avx_float64_t m0) {
	rvm_avx_float64_t mm = mipp_avx_cast_k_int64_float64(mipp_avx_tomsk_int64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF)));
	return mipp_avx_andnb_k_float64(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_int64_t mipp_avx_notb_k_int64(const rvm_avx_int64_t m0) {
	rvm_avx_int64_t mm = mipp_avx_cast_k_int64_int64(mipp_avx_tomsk_int64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF)));
	return mipp_avx_andnb_k_int64(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_uint64_t mipp_avx_notb_k_uint64(const rvm_avx_uint64_t m0) {
	rvm_avx_uint64_t mm = mipp_avx_cast_k_int64_uint64(mipp_avx_tomsk_int64(mipp_avx_set1_int64(0xFFFFFFFFFFFFFFFF)));
	return mipp_avx_andnb_k_uint64(m0, mm);
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
rvm_avx_float32_t mipp_avx_notb_k_float32(const rvm_avx_float32_t m0) {
	rvm_avx_float32_t mm = mipp_avx_cast_k_int32_float32(mipp_avx_tomsk_int32(mipp_avx_set1_int32(0xFFFFFFFF)));
	return mipp_avx_andnb_k_float32(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_int32_t mipp_avx_notb_k_int32(const rvm_avx_int32_t m0) {
	rvm_avx_int32_t mm = mipp_avx_cast_k_int32_int32(mipp_avx_tomsk_int32(mipp_avx_set1_int32(0xFFFFFFFF)));
	return mipp_avx_andnb_k_int32(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_uint32_t mipp_avx_notb_k_uint32(const rvm_avx_uint32_t m0) {
	rvm_avx_uint32_t mm = mipp_avx_cast_k_int32_uint32(mipp_avx_tomsk_int32(mipp_avx_set1_int32(0xFFFFFFFF)));
	return mipp_avx_andnb_k_uint32(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_int16_t mipp_avx_notb_k_int16(const rvm_avx_int16_t m0) {
	rvm_avx_int16_t mm = mipp_avx_cast_k_int16_int16(mipp_avx_tomsk_int16(mipp_avx_set1_int16(0xFFFF)));
	return mipp_avx_andnb_k_int16(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_uint16_t mipp_avx_notb_k_uint16(const rvm_avx_uint16_t m0) {
	rvm_avx_uint16_t mm = mipp_avx_cast_k_int16_uint16(mipp_avx_tomsk_int16(mipp_avx_set1_int16(0xFFFF)));
	return mipp_avx_andnb_k_uint16(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_int8_t mipp_avx_notb_k_int8(const rvm_avx_int8_t m0) {
	rvm_avx_int8_t mm = mipp_avx_cast_k_int8_int8(mipp_avx_tomsk_int8(mipp_avx_set1_int8(0xFF)));
	return mipp_avx_andnb_k_int8(m0, mm);
}
#endif
#if ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )
rvm_avx_uint8_t mipp_avx_notb_k_uint8(const rvm_avx_uint8_t m0) {
	rvm_avx_uint8_t mm = mipp_avx_cast_k_int8_uint8(mipp_avx_tomsk_int8(mipp_avx_set1_int8(0xFF)));
	return mipp_avx_andnb_k_uint8(m0, mm);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_int64_t mipp_avx_cmpeq_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	return mipp_avx_cast_k_float64_int64(mipp_avx_cmpeq_float64(mipp_avx_cast_int64_float64(r0), mipp_avx_cast_int64_float64(r1)));
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_int32_t mipp_avx_cmpeq_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	return mipp_avx_cast_k_float32_int32(mipp_avx_cmpeq_float32(mipp_avx_cast_int32_float32(r0), mipp_avx_cast_int32_float32(r1)));
}
#endif
rvm_avx_uint64_t mipp_avx_cmpeq_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	return mipp_avx_cast_k_float64_uint64(mipp_avx_cmpeq_float64(mipp_avx_cast_uint64_float64(r0), mipp_avx_cast_uint64_float64(r1)));
}
rvm_avx_uint32_t mipp_avx_cmpeq_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	return mipp_avx_cast_k_float32_uint32(mipp_avx_cmpeq_float32(mipp_avx_cast_uint32_float32(r0), mipp_avx_cast_uint32_float32(r1)));
}
#if ( ( ( defined(__AVX2__) ) ) )
rvm_avx_uint16_t mipp_avx_cmpeq_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	return mipp_avx_cast_k_int16_uint16(mipp_avx_cmpeq_int16(mipp_avx_cast_uint16_int16(r0), mipp_avx_cast_uint16_int16(r1)));
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
rvm_avx_uint8_t mipp_avx_cmpeq_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	return mipp_avx_cast_k_int8_uint8(mipp_avx_cmpeq_int8(mipp_avx_cast_uint8_int8(r0), mipp_avx_cast_uint8_int8(r1)));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) )
rvm_avx_int64_t mipp_avx_cmpneq_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	return mipp_avx_notb_k_int64(mipp_avx_cmpeq_int64(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) )
rvm_avx_int32_t mipp_avx_cmpneq_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	return mipp_avx_notb_k_int32(mipp_avx_cmpeq_int32(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
rvm_avx_int16_t mipp_avx_cmpneq_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	return mipp_avx_notb_k_int16(mipp_avx_cmpeq_int16(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
rvm_avx_int8_t mipp_avx_cmpneq_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	return mipp_avx_notb_k_int8(mipp_avx_cmpeq_int8(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvm_avx_uint64_t mipp_avx_cmpneq_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	return mipp_avx_notb_k_uint64(mipp_avx_cmpeq_uint64(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )
rvm_avx_uint32_t mipp_avx_cmpneq_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	return mipp_avx_notb_k_uint32(mipp_avx_cmpeq_uint32(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) )
rvm_avx_uint16_t mipp_avx_cmpneq_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	return mipp_avx_notb_k_uint16(mipp_avx_cmpeq_uint16(r0, r1));
}
#endif
#if ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) )
rvm_avx_uint8_t mipp_avx_cmpneq_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	return mipp_avx_notb_k_uint8(mipp_avx_cmpeq_uint8(r0, r1));
}
#endif
int32_t mipp_avx_testz_2_float64(const rvm_avx_float64_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_float64(m0, mipp_avx_cast_k_int32_float64(m32));
}
int32_t mipp_avx_testz_2_float32(const rvm_avx_float32_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_float32(m0, mipp_avx_cast_k_int32_float32(m32));
}
int32_t mipp_avx_testz_2_int64(const rvm_avx_int64_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_int64(m0, mipp_avx_cast_k_int32_int64(m32));
}
int32_t mipp_avx_testz_2_int32(const rvm_avx_int32_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_int32(m0, mipp_avx_cast_k_int32_int32(m32));
}
int32_t mipp_avx_testz_2_int16(const rvm_avx_int16_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_int16(m0, mipp_avx_cast_k_int32_int16(m32));
}
int32_t mipp_avx_testz_2_int8(const rvm_avx_int8_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_int8(m0, mipp_avx_cast_k_int32_int8(m32));
}
int32_t mipp_avx_testz_2_uint64(const rvm_avx_uint64_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_uint64(m0, mipp_avx_cast_k_int32_uint64(m32));
}
int32_t mipp_avx_testz_2_uint32(const rvm_avx_uint32_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_uint32(m0, mipp_avx_cast_k_int32_uint32(m32));
}
int32_t mipp_avx_testz_2_uint16(const rvm_avx_uint16_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_uint16(m0, mipp_avx_cast_k_int32_uint16(m32));
}
int32_t mipp_avx_testz_2_uint8(const rvm_avx_uint8_t m0) {
	rvd_avx_int32_t r32 = mipp_avx_set1_int32(-1);
	rvm_avx_int32_t m32 = mipp_avx_tomsk_int32(r32);
	return mipp_avx_testz_uint8(m0, mipp_avx_cast_k_int32_uint8(m32));
}
float64_t mipp_avx_get_float64(const rvd_avx_float64_t r0, const uint32_t v0) {
	float64_t t[MIPP_AVX_N_FLOAT64];
	mipp_avx_storeu_float64(t, r0);
	return t[v0];
}
float32_t mipp_avx_get_float32(const rvd_avx_float32_t r0, const uint32_t v0) {
	float32_t t[MIPP_AVX_N_FLOAT32];
	mipp_avx_storeu_float32(t, r0);
	return t[v0];
}
int64_t mipp_avx_get_int64(const rvd_avx_int64_t r0, const uint32_t v0) {
	int64_t t[MIPP_AVX_N_INT64];
	mipp_avx_storeu_int64(t, r0);
	return t[v0];
}
int32_t mipp_avx_get_int32(const rvd_avx_int32_t r0, const uint32_t v0) {
	int32_t t[MIPP_AVX_N_INT32];
	mipp_avx_storeu_int32(t, r0);
	return t[v0];
}
int16_t mipp_avx_get_int16(const rvd_avx_int16_t r0, const uint32_t v0) {
	int16_t t[MIPP_AVX_N_INT16];
	mipp_avx_storeu_int16(t, r0);
	return t[v0];
}
int8_t mipp_avx_get_int8(const rvd_avx_int8_t r0, const uint32_t v0) {
	int8_t t[MIPP_AVX_N_INT8];
	mipp_avx_storeu_int8(t, r0);
	return t[v0];
}
uint64_t mipp_avx_get_uint64(const rvd_avx_uint64_t r0, const uint32_t v0) {
	uint64_t t[MIPP_AVX_N_UINT64];
	mipp_avx_storeu_uint64(t, r0);
	return t[v0];
}
uint32_t mipp_avx_get_uint32(const rvd_avx_uint32_t r0, const uint32_t v0) {
	uint32_t t[MIPP_AVX_N_UINT32];
	mipp_avx_storeu_uint32(t, r0);
	return t[v0];
}
uint16_t mipp_avx_get_uint16(const rvd_avx_uint16_t r0, const uint32_t v0) {
	uint16_t t[MIPP_AVX_N_UINT16];
	mipp_avx_storeu_uint16(t, r0);
	return t[v0];
}
uint8_t mipp_avx_get_uint8(const rvd_avx_uint8_t r0, const uint32_t v0) {
	uint8_t t[MIPP_AVX_N_UINT8];
	mipp_avx_storeu_uint8(t, r0);
	return t[v0];
}
#if !( defined(__AVX2__) )
int16_t mipp_avx_getfirst_int16(const rvd_avx_int16_t r0) {
	return mipp_avx_get_int16(r0, 0);
}
#endif
#if !( defined(__AVX2__) )
int8_t mipp_avx_getfirst_int8(const rvd_avx_int8_t r0) {
	return mipp_avx_get_int8(r0, 0);
}
#endif
#if !( defined(__AVX2__) )
uint16_t mipp_avx_getfirst_uint16(const rvd_avx_uint16_t r0) {
	return mipp_avx_get_uint16(r0, 0);
}
#endif
#if !( defined(__AVX2__) )
uint8_t mipp_avx_getfirst_uint8(const rvd_avx_uint8_t r0) {
	return mipp_avx_get_uint8(r0, 0);
}
#endif
float64_t mipp_avx_hadd_2_float64(const rvd_avx_float64_t r0) {
	return mipp_avx_getfirst_float64(mipp_avx_hadd_float64(r0));
}
float32_t mipp_avx_hadd_2_float32(const rvd_avx_float32_t r0) {
	return mipp_avx_getfirst_float32(mipp_avx_hadd_float32(r0));
}
#if ( ( ( defined(__AVX2__) ) ) )
int64_t mipp_avx_hadd_2_int64(const rvd_avx_int64_t r0) {
	return mipp_avx_getfirst_int64(mipp_avx_hadd_int64(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
int32_t mipp_avx_hadd_2_int32(const rvd_avx_int32_t r0) {
	return mipp_avx_getfirst_int32(mipp_avx_hadd_int32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int16_t mipp_avx_hadd_2_int16(const rvd_avx_int16_t r0) {
	return mipp_avx_getfirst_int16(mipp_avx_hadd_int16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int8_t mipp_avx_hadd_2_int8(const rvd_avx_int8_t r0) {
	return mipp_avx_getfirst_int8(mipp_avx_hadd_int8(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint16_t mipp_avx_hadd_2_uint16(const rvd_avx_uint16_t r0) {
	return mipp_avx_getfirst_uint16(mipp_avx_hadd_uint16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint8_t mipp_avx_hadd_2_uint8(const rvd_avx_uint8_t r0) {
	return mipp_avx_getfirst_uint8(mipp_avx_hadd_uint8(r0));
}
#endif
float64_t mipp_avx_hmul_2_float64(const rvd_avx_float64_t r0) {
	return mipp_avx_getfirst_float64(mipp_avx_hmul_float64(r0));
}
float32_t mipp_avx_hmul_2_float32(const rvd_avx_float32_t r0) {
	return mipp_avx_getfirst_float32(mipp_avx_hmul_float32(r0));
}
#if ( ( ( defined(__AVX2__) ) ) )
int32_t mipp_avx_hmul_2_int32(const rvd_avx_int32_t r0) {
	return mipp_avx_getfirst_int32(mipp_avx_hmul_int32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int16_t mipp_avx_hmul_2_int16(const rvd_avx_int16_t r0) {
	return mipp_avx_getfirst_int16(mipp_avx_hmul_int16(r0));
}
#endif
float64_t mipp_avx_hmin_2_float64(const rvd_avx_float64_t r0) {
	return mipp_avx_getfirst_float64(mipp_avx_hmin_float64(r0));
}
float32_t mipp_avx_hmin_2_float32(const rvd_avx_float32_t r0) {
	return mipp_avx_getfirst_float32(mipp_avx_hmin_float32(r0));
}
#if ( ( ( defined(__AVX2__) ) ) )
int32_t mipp_avx_hmin_2_int32(const rvd_avx_int32_t r0) {
	return mipp_avx_getfirst_int32(mipp_avx_hmin_int32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int16_t mipp_avx_hmin_2_int16(const rvd_avx_int16_t r0) {
	return mipp_avx_getfirst_int16(mipp_avx_hmin_int16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int8_t mipp_avx_hmin_2_int8(const rvd_avx_int8_t r0) {
	return mipp_avx_getfirst_int8(mipp_avx_hmin_int8(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
uint32_t mipp_avx_hmin_2_uint32(const rvd_avx_uint32_t r0) {
	return mipp_avx_getfirst_uint32(mipp_avx_hmin_uint32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint16_t mipp_avx_hmin_2_uint16(const rvd_avx_uint16_t r0) {
	return mipp_avx_getfirst_uint16(mipp_avx_hmin_uint16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint8_t mipp_avx_hmin_2_uint8(const rvd_avx_uint8_t r0) {
	return mipp_avx_getfirst_uint8(mipp_avx_hmin_uint8(r0));
}
#endif
float64_t mipp_avx_hmax_2_float64(const rvd_avx_float64_t r0) {
	return mipp_avx_getfirst_float64(mipp_avx_hmax_float64(r0));
}
float32_t mipp_avx_hmax_2_float32(const rvd_avx_float32_t r0) {
	return mipp_avx_getfirst_float32(mipp_avx_hmax_float32(r0));
}
#if ( ( ( defined(__AVX2__) ) ) )
int32_t mipp_avx_hmax_2_int32(const rvd_avx_int32_t r0) {
	return mipp_avx_getfirst_int32(mipp_avx_hmax_int32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int16_t mipp_avx_hmax_2_int16(const rvd_avx_int16_t r0) {
	return mipp_avx_getfirst_int16(mipp_avx_hmax_int16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
int8_t mipp_avx_hmax_2_int8(const rvd_avx_int8_t r0) {
	return mipp_avx_getfirst_int8(mipp_avx_hmax_int8(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) ) )
uint32_t mipp_avx_hmax_2_uint32(const rvd_avx_uint32_t r0) {
	return mipp_avx_getfirst_uint32(mipp_avx_hmax_uint32(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint16_t mipp_avx_hmax_2_uint16(const rvd_avx_uint16_t r0) {
	return mipp_avx_getfirst_uint16(mipp_avx_hmax_uint16(r0));
}
#endif
#if ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )
uint8_t mipp_avx_hmax_2_uint8(const rvd_avx_uint8_t r0) {
	return mipp_avx_getfirst_uint8(mipp_avx_hmax_uint8(r0));
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_float64_t mipp_avx_load_float64(const float64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_float32_t mipp_avx_load_float32(const float32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_int64_t mipp_avx_load_int64(const int64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_int32_t mipp_avx_load_int32(const int32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_int16_t mipp_avx_load_int16(const int16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_int8_t mipp_avx_load_int8(const int8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_int8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_uint64_t mipp_avx_load_uint64(const uint64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_uint64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_uint32_t mipp_avx_load_uint32(const uint32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_uint32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_uint16_t mipp_avx_load_uint16(const uint16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_uint16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx_uint8_t mipp_avx_load_uint8(const uint8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_load_uint8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_float64(float64_t* p0, const rvd_avx_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_float32(float32_t* p0, const rvd_avx_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_int64(int64_t* p0, const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_int32(int32_t* p0, const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_int16(int16_t* p0, const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_int8(int8_t* p0, const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_int8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_uint64(uint64_t* p0, const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_uint64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_uint32(uint32_t* p0, const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_uint32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_uint16(uint16_t* p0, const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_uint16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx_store_uint8(uint8_t* p0, const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_store_uint8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_set1_uint64(const uint64_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_set1_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_set1_uint32(const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_set1_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_set1_uint16(const uint16_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_set1_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_set1_uint8(const uint8_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_set1_uint8");
	exit(-1);
}
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
int16_t mipp_avx_getfirst_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_getfirst_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
int8_t mipp_avx_getfirst_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_getfirst_int8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
uint16_t mipp_avx_getfirst_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_getfirst_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
uint8_t mipp_avx_getfirst_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_getfirst_uint8");
	exit(-1);
}
#endif
rvd_avx_float64_t mipp_avx_rsqrt_float64(const rvd_avx_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_rsqrt_float64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_add_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_add_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_add_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_add_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_add_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_add_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_uint32");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_add_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_add_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int64_t mipp_avx_add_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_int64");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_add_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_add_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_add_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_add_m_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0, const rvd_avx_uint64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_add_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_uint32");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_add_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_add_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_m_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int64_t mipp_avx_add_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_int64");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_add_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_add_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_int16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_add_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_add_mz_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_add_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_uint32");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_add_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_add_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_add_mz_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_sub_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_sub_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_sub_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_sub_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_sub_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_sub_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_uint32");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_sub_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_sub_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int64_t mipp_avx_sub_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_int64");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_sub_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_sub_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_sub_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_sub_m_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0, const rvd_avx_uint64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_sub_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_uint32");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_sub_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_sub_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_m_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int64_t mipp_avx_sub_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_int64");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_sub_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_sub_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_int16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_sub_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_sub_mz_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_sub_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_uint32");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_sub_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_sub_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sub_mz_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_mul_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_mul_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_mul_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_int16");
	exit(-1);
}
#endif
rvd_avx_int8_t mipp_avx_mul_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_int8");
	exit(-1);
}
rvd_avx_uint64_t mipp_avx_mul_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_mul_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_mul_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_mul_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_uint8");
	exit(-1);
}
rvd_avx_int64_t mipp_avx_mul_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_mul_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_mul_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_int16");
	exit(-1);
}
#endif
rvd_avx_int8_t mipp_avx_mul_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_int8");
	exit(-1);
}
rvd_avx_uint64_t mipp_avx_mul_m_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0, const rvd_avx_uint64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_mul_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_mul_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_mul_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_m_uint8");
	exit(-1);
}
rvd_avx_int64_t mipp_avx_mul_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_int64");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_mul_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_mul_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_int16");
	exit(-1);
}
#endif
rvd_avx_int8_t mipp_avx_mul_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_int8");
	exit(-1);
}
rvd_avx_uint64_t mipp_avx_mul_mz_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_mul_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_mul_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_mul_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_mul_mz_uint8");
	exit(-1);
}
rvd_avx_int64_t mipp_avx_min_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_min_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_min_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_min_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_min_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_uint64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_min_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_uint32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_min_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_min_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_min_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_min_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_min_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_min_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_min_m_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0, const rvd_avx_uint64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_uint64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint32_t mipp_avx_min_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_min_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_min_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_m_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_min_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_int64");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_min_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_min_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_int16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_min_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_min_mz_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_uint64");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint32_t mipp_avx_min_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_min_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_min_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_min_mz_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_max_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_max_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_max_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_max_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_max_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_uint64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_max_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_uint32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_max_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_max_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_max_m_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0, const rvd_avx_int64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_max_m_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0, const rvd_avx_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_max_m_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0, const rvd_avx_int16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_max_m_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0, const rvd_avx_int8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_max_m_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0, const rvd_avx_uint64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_uint64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint32_t mipp_avx_max_m_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0, const rvd_avx_uint32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_max_m_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0, const rvd_avx_uint16_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_max_m_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0, const rvd_avx_uint8_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_m_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_max_mz_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_int64");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int32_t mipp_avx_max_mz_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int16_t mipp_avx_max_mz_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_int16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_int8_t mipp_avx_max_mz_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_max_mz_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_uint64");
	exit(-1);
}
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) || ( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint32_t mipp_avx_max_mz_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint16_t mipp_avx_max_mz_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) ) && (( ( ( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) ) ) )) )
rvd_avx_uint8_t mipp_avx_max_mz_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_max_mz_uint8");
	exit(-1);
}
#endif
#if !( defined(__FMA__) ) && !( !( defined(__FMA__) ) )
rvd_avx_float64_t mipp_avx_fmadd_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_fmadd_float64");
	exit(-1);
}
#endif
#if !( defined(__FMA__) ) && !( !( defined(__FMA__) ) )
rvd_avx_float32_t mipp_avx_fmadd_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_fmadd_float32");
	exit(-1);
}
#endif
#if !( defined(__FMA__) ) && !( !( defined(__FMA__) ) )
rvd_avx_float64_t mipp_avx_fmsub_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1, const rvd_avx_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_fmsub_float64");
	exit(-1);
}
#endif
#if !( defined(__FMA__) ) && !( !( defined(__FMA__) ) )
rvd_avx_float32_t mipp_avx_fmsub_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1, const rvd_avx_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_fmsub_float32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_andb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_andb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_andb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_andb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint64_t mipp_avx_andb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_andb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_andb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_andb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float64_t mipp_avx_andb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float32_t mipp_avx_andb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_float32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int64_t mipp_avx_andb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int32_t mipp_avx_andb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int16_t mipp_avx_andb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int8_t mipp_avx_andb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint64_t mipp_avx_andb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint32_t mipp_avx_andb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint16_t mipp_avx_andb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint8_t mipp_avx_andb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andb_k_uint8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_andnb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_andnb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_andnb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_andnb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint64_t mipp_avx_andnb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_andnb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_andnb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_andnb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float64_t mipp_avx_andnb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float32_t mipp_avx_andnb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_float32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int64_t mipp_avx_andnb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int32_t mipp_avx_andnb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int16_t mipp_avx_andnb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int8_t mipp_avx_andnb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint64_t mipp_avx_andnb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint32_t mipp_avx_andnb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint16_t mipp_avx_andnb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint8_t mipp_avx_andnb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_andnb_k_uint8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_xorb_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_xorb_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_xorb_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_xorb_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint64_t mipp_avx_xorb_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_xorb_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_xorb_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_xorb_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float64_t mipp_avx_xorb_k_float64(const rvm_avx_float64_t m0, const rvm_avx_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_float32_t mipp_avx_xorb_k_float32(const rvm_avx_float32_t m0, const rvm_avx_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_float32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int64_t mipp_avx_xorb_k_int64(const rvm_avx_int64_t m0, const rvm_avx_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_int64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int32_t mipp_avx_xorb_k_int32(const rvm_avx_int32_t m0, const rvm_avx_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_int32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int16_t mipp_avx_xorb_k_int16(const rvm_avx_int16_t m0, const rvm_avx_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_int16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_int8_t mipp_avx_xorb_k_int8(const rvm_avx_int8_t m0, const rvm_avx_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_int8");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint64_t mipp_avx_xorb_k_uint64(const rvm_avx_uint64_t m0, const rvm_avx_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_uint64");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint32_t mipp_avx_xorb_k_uint32(const rvm_avx_uint32_t m0, const rvm_avx_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_uint32");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint16_t mipp_avx_xorb_k_uint16(const rvm_avx_uint16_t m0, const rvm_avx_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_uint16");
	exit(-1);
}
#endif
#if !( !defined(__AVX2__) ) && !( defined(__AVX2__) )
rvm_avx_uint8_t mipp_avx_xorb_k_uint8(const rvm_avx_uint8_t m0, const rvm_avx_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_xorb_k_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int64_t mipp_avx_msb_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_int64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int32_t mipp_avx_msb_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_int32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int16_t mipp_avx_msb_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_int16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int8_t mipp_avx_msb_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_int8");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint64_t mipp_avx_msb_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_uint64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint32_t mipp_avx_msb_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint16_t mipp_avx_msb_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint8_t mipp_avx_msb_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_msb_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int64_t mipp_avx_notb_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_int64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int32_t mipp_avx_notb_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_int32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int16_t mipp_avx_notb_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_int16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int8_t mipp_avx_notb_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_int8");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint64_t mipp_avx_notb_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_uint64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint32_t mipp_avx_notb_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint16_t mipp_avx_notb_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint8_t mipp_avx_notb_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_float64_t mipp_avx_notb_k_float64(const rvm_avx_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_float64");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_float32_t mipp_avx_notb_k_float32(const rvm_avx_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_float32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_int64_t mipp_avx_notb_k_int64(const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_int64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_int32_t mipp_avx_notb_k_int32(const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_int32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_int16_t mipp_avx_notb_k_int16(const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_int16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_int8_t mipp_avx_notb_k_int8(const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_int8");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_uint64_t mipp_avx_notb_k_uint64(const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_uint64");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_uint32_t mipp_avx_notb_k_uint32(const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_uint16_t mipp_avx_notb_k_uint16(const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvm_avx_uint8_t mipp_avx_notb_k_uint8(const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_notb_k_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
rvm_avx_int64_t mipp_avx_cmpeq_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) )
rvm_avx_int32_t mipp_avx_cmpeq_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_int16_t mipp_avx_cmpeq_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvm_avx_int8_t mipp_avx_cmpeq_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_int8");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_uint16_t mipp_avx_cmpeq_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_uint8_t mipp_avx_cmpeq_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpeq_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) )) )
rvm_avx_int64_t mipp_avx_cmpneq_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_int64");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) )) )
rvm_avx_int32_t mipp_avx_cmpneq_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_int32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_int16_t mipp_avx_cmpneq_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_int16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
rvm_avx_int8_t mipp_avx_cmpneq_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_int8");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvm_avx_uint64_t mipp_avx_cmpneq_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_uint64");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) )) )
rvm_avx_uint32_t mipp_avx_cmpneq_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) )) )
rvm_avx_uint16_t mipp_avx_cmpneq_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) ) && (( ( ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) ) ) ) && ( ( ( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) ) ) )) )
rvm_avx_uint8_t mipp_avx_cmpneq_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_cmpneq_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && !( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int64_t mipp_avx_blend_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1, const rvm_avx_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && !( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int32_t mipp_avx_blend_int32(const rvd_avx_int32_t r0, const rvd_avx_int32_t r1, const rvm_avx_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int16_t mipp_avx_blend_int16(const rvd_avx_int16_t r0, const rvd_avx_int16_t r1, const rvm_avx_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_int8_t mipp_avx_blend_int8(const rvd_avx_int8_t r0, const rvd_avx_int8_t r1, const rvm_avx_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_int8");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && !( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint64_t mipp_avx_blend_uint64(const rvd_avx_uint64_t r0, const rvd_avx_uint64_t r1, const rvm_avx_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_uint64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && !( !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint32_t mipp_avx_blend_uint32(const rvd_avx_uint32_t r0, const rvd_avx_uint32_t r1, const rvm_avx_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_uint32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint16_t mipp_avx_blend_uint16(const rvd_avx_uint16_t r0, const rvd_avx_uint16_t r1, const rvm_avx_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) ) && !( !( defined(__AVX2__) ) && ( ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) ) && (( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) ) && ( ( ( !defined(__AVX2__) ) || ( defined(__AVX2__) ) ) )) )
rvd_avx_uint8_t mipp_avx_blend_uint8(const rvd_avx_uint8_t r0, const rvd_avx_uint8_t r1, const rvm_avx_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_blend_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_sat_int64(const rvd_avx_int64_t r0, const int64_t v0, const int64_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
rvd_avx_int32_t mipp_avx_sat_int32(const rvd_avx_int32_t r0, const int32_t v0, const int32_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
rvd_avx_int16_t mipp_avx_sat_int16(const rvd_avx_int16_t r0, const int16_t v0, const int16_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
rvd_avx_int8_t mipp_avx_sat_int8(const rvd_avx_int8_t r0, const int8_t v0, const int8_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_sat_uint64(const rvd_avx_uint64_t r0, const uint64_t v0, const uint64_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_sat_uint32(const rvd_avx_uint32_t r0, const uint32_t v0, const uint32_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_sat_uint16(const rvd_avx_uint16_t r0, const uint16_t v0, const uint16_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_sat_uint8(const rvd_avx_uint8_t r0, const uint8_t v0, const uint8_t v1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_sat_uint8");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int64_t mipp_avx_hadd_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_hadd_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_hadd_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_hadd_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_hadd_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_hadd_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_uint32");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_hadd_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_hadd_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_uint8");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
int64_t mipp_avx_hadd_2_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_int64");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
int32_t mipp_avx_hadd_2_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int16_t mipp_avx_hadd_2_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int8_t mipp_avx_hadd_2_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_int8");
	exit(-1);
}
#endif
uint64_t mipp_avx_hadd_2_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_uint64");
	exit(-1);
}
uint32_t mipp_avx_hadd_2_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_uint32");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint16_t mipp_avx_hadd_2_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint8_t mipp_avx_hadd_2_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hadd_2_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_hmul_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_hmul_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_hmul_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_int16");
	exit(-1);
}
#endif
rvd_avx_int8_t mipp_avx_hmul_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_int8");
	exit(-1);
}
rvd_avx_uint64_t mipp_avx_hmul_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_uint64");
	exit(-1);
}
rvd_avx_uint32_t mipp_avx_hmul_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_uint32");
	exit(-1);
}
rvd_avx_uint16_t mipp_avx_hmul_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_uint16");
	exit(-1);
}
rvd_avx_uint8_t mipp_avx_hmul_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_uint8");
	exit(-1);
}
int64_t mipp_avx_hmul_2_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
int32_t mipp_avx_hmul_2_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int16_t mipp_avx_hmul_2_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_int16");
	exit(-1);
}
#endif
int8_t mipp_avx_hmul_2_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_int8");
	exit(-1);
}
uint64_t mipp_avx_hmul_2_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_uint64");
	exit(-1);
}
uint32_t mipp_avx_hmul_2_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_uint32");
	exit(-1);
}
uint16_t mipp_avx_hmul_2_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_uint16");
	exit(-1);
}
uint8_t mipp_avx_hmul_2_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmul_2_uint8");
	exit(-1);
}
rvd_avx_int64_t mipp_avx_hmin_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_hmin_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_hmin_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_hmin_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_hmin_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_uint64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_hmin_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_uint32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_hmin_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_hmin_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_uint8");
	exit(-1);
}
#endif
int64_t mipp_avx_hmin_2_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
int32_t mipp_avx_hmin_2_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int16_t mipp_avx_hmin_2_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int8_t mipp_avx_hmin_2_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_int8");
	exit(-1);
}
#endif
uint64_t mipp_avx_hmin_2_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_uint64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
uint32_t mipp_avx_hmin_2_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint16_t mipp_avx_hmin_2_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint8_t mipp_avx_hmin_2_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmin_2_uint8");
	exit(-1);
}
#endif
rvd_avx_int64_t mipp_avx_hmax_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_int64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_int32_t mipp_avx_hmax_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int16_t mipp_avx_hmax_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_int8_t mipp_avx_hmax_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_int8");
	exit(-1);
}
#endif
rvd_avx_uint64_t mipp_avx_hmax_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_uint64");
	exit(-1);
}
#if !( defined(__AVX2__) )
rvd_avx_uint32_t mipp_avx_hmax_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_uint32");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint16_t mipp_avx_hmax_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX2__) )
rvd_avx_uint8_t mipp_avx_hmax_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_uint8");
	exit(-1);
}
#endif
int64_t mipp_avx_hmax_2_int64(const rvd_avx_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_int64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
int32_t mipp_avx_hmax_2_int32(const rvd_avx_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_int32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int16_t mipp_avx_hmax_2_int16(const rvd_avx_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
int8_t mipp_avx_hmax_2_int8(const rvd_avx_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_int8");
	exit(-1);
}
#endif
uint64_t mipp_avx_hmax_2_uint64(const rvd_avx_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_uint64");
	exit(-1);
}
#if !( ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) ) )) )
uint32_t mipp_avx_hmax_2_uint32(const rvd_avx_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_uint32");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint16_t mipp_avx_hmax_2_uint16(const rvd_avx_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_uint16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) ) && (( ( ( defined(__AVX2__) ) || ( !( defined(__AVX2__) ) ) ) ) && ( ( ( defined(__AVX2__) ) ) )) )
uint8_t mipp_avx_hmax_2_uint8(const rvd_avx_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx_hmax_2_uint8");
	exit(-1);
}
#endif
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */
