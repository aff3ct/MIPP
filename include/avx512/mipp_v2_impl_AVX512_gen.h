#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX512_H_
#include "mipp_v2_avx512.h"
#include <immintrin.h>
#define MIPP_MACRO_FLOAT64(MACRO, ...) MACRO(__VA_ARGS__, 64, float, pd, pd, float64_t)
#define MIPP_MACRO_FLOAT32(MACRO, ...) MACRO(__VA_ARGS__, 32, float, ps, ps, float32_t)
#define MIPP_MACRO_INT64(MACRO, ...) MACRO(__VA_ARGS__, 64, int, epi64, si512, int64_t)
#define MIPP_MACRO_INT32(MACRO, ...) MACRO(__VA_ARGS__, 32, int, epi32, si512, int32_t)
#define MIPP_MACRO_INT16(MACRO, ...) MACRO(__VA_ARGS__, 16, int, epi16, si512, int16_t)
#define MIPP_MACRO_INT8(MACRO, ...) MACRO(__VA_ARGS__, 8, int, epi8, si512, int8_t)
#define MIPP_MACRO_UINT64(MACRO, ...) MACRO(__VA_ARGS__, 64, uint, epu64, si512, uint64_t)
#define MIPP_MACRO_UINT32(MACRO, ...) MACRO(__VA_ARGS__, 32, uint, epu32, si512, uint32_t)
#define MIPP_MACRO_UINT16(MACRO, ...) MACRO(__VA_ARGS__, 16, uint, epu16, si512, uint16_t)
#define MIPP_MACRO_UINT8(MACRO, ...) MACRO(__VA_ARGS__, 8, uint, epu8, si512, uint8_t)
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
typedef struct { __m512d m; } rvd_avx512_float64_t;
typedef struct { __m512 m; } rvd_avx512_float32_t;
typedef struct { __m512i m; } rvd_avx512_int64_t;
typedef struct { __m512i m; } rvd_avx512_int32_t;
typedef struct { __m512i m; } rvd_avx512_int16_t;
typedef struct { __m512i m; } rvd_avx512_int8_t;
typedef struct { __m512i m; } rvd_avx512_uint64_t;
typedef struct { __m512i m; } rvd_avx512_uint32_t;
typedef struct { __m512i m; } rvd_avx512_uint16_t;
typedef struct { __m512i m; } rvd_avx512_uint8_t;
typedef struct { __mmask8 m; } rvm_avx512_float64_t;
typedef struct { __mmask16 m; } rvm_avx512_float32_t;
typedef struct { __mmask8 m; } rvm_avx512_int64_t;
typedef struct { __mmask16 m; } rvm_avx512_int32_t;
typedef struct { __mmask32 m; } rvm_avx512_int16_t;
typedef struct { __mmask64 m; } rvm_avx512_int8_t;
typedef struct { __mmask8 m; } rvm_avx512_uint64_t;
typedef struct { __mmask16 m; } rvm_avx512_uint32_t;
typedef struct { __mmask32 m; } rvm_avx512_uint16_t;
typedef struct { __mmask64 m; } rvm_avx512_uint8_t;
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_float64_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_float32_float64(const rvd_avx512_float32_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castps_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_int64_float64(const rvd_avx512_int64_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_int32_float64(const rvd_avx512_int32_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_int16_float64(const rvd_avx512_int16_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_int8_float64(const rvd_avx512_int8_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_uint64_float64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_uint32_float64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_uint16_float64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_cast_uint8_float64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_float64_float32(const rvd_avx512_float64_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castpd_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_float32_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_int64_float32(const rvd_avx512_int64_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_int32_float32(const rvd_avx512_int32_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_int16_float32(const rvd_avx512_int16_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_int8_float32(const rvd_avx512_int8_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_uint64_float32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_uint32_float32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_uint16_float32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_cast_uint8_float32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_float64_int64(const rvd_avx512_float64_t r0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_float32_int64(const rvd_avx512_float32_t r0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_int64_int64(const rvd_avx512_int64_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_int32_int64(const rvd_avx512_int32_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_int16_int64(const rvd_avx512_int16_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_int8_int64(const rvd_avx512_int8_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_uint64_int64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_uint32_int64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_uint16_int64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_cast_uint8_int64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_float64_int32(const rvd_avx512_float64_t r0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_float32_int32(const rvd_avx512_float32_t r0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_int64_int32(const rvd_avx512_int64_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_int32_int32(const rvd_avx512_int32_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_int16_int32(const rvd_avx512_int16_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_int8_int32(const rvd_avx512_int8_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_uint64_int32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_uint32_int32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_uint16_int32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_cast_uint8_int32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_float64_int16(const rvd_avx512_float64_t r0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_float32_int16(const rvd_avx512_float32_t r0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_int64_int16(const rvd_avx512_int64_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_int32_int16(const rvd_avx512_int32_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_int16_int16(const rvd_avx512_int16_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_int8_int16(const rvd_avx512_int8_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_uint64_int16(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_uint32_int16(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_uint16_int16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_cast_uint8_int16(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_float64_int8(const rvd_avx512_float64_t r0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_float32_int8(const rvd_avx512_float32_t r0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_int64_int8(const rvd_avx512_int64_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_int32_int8(const rvd_avx512_int32_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_int16_int8(const rvd_avx512_int16_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_int8_int8(const rvd_avx512_int8_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_uint64_int8(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_uint32_int8(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_uint16_int8(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_cast_uint8_int8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_float64_uint64(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_float32_uint64(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_int64_uint64(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_int32_uint64(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_int16_uint64(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_int8_uint64(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_uint64_uint64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_uint32_uint64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_uint16_uint64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_cast_uint8_uint64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_float64_uint32(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_float32_uint32(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_int64_uint32(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_int32_uint32(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_int16_uint32(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_int8_uint32(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_uint64_uint32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_uint32_uint32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_uint16_uint32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_cast_uint8_uint32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_float64_uint16(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_float32_uint16(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_int64_uint16(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_int32_uint16(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_int16_uint16(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_int8_uint16(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_uint64_uint16(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_uint32_uint16(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_uint16_uint16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_cast_uint8_uint16(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_float64_uint8(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_float32_uint8(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_int64_uint8(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_int32_uint8(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_int16_uint8(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_int8_uint8(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_uint64_uint8(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_uint32_uint8(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_uint16_uint8(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_cast_uint8_uint8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_float64_float64(const rvm_avx512_float64_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_float32_float64(const rvm_avx512_float32_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_int64_float64(const rvm_avx512_int64_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_int32_float64(const rvm_avx512_int32_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_int16_float64(const rvm_avx512_int16_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_int8_float64(const rvm_avx512_int8_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_uint64_float64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_uint32_float64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_uint16_float64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_cast_k_uint8_float64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_float64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_float64_float32(const rvm_avx512_float64_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_float32_float32(const rvm_avx512_float32_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_int64_float32(const rvm_avx512_int64_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_int32_float32(const rvm_avx512_int32_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_int16_float32(const rvm_avx512_int16_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_int8_float32(const rvm_avx512_int8_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_uint64_float32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_uint32_float32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_uint16_float32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_cast_k_uint8_float32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_float32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_float64_int64(const rvm_avx512_float64_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_float32_int64(const rvm_avx512_float32_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_int64_int64(const rvm_avx512_int64_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_int32_int64(const rvm_avx512_int32_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_int16_int64(const rvm_avx512_int16_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_int8_int64(const rvm_avx512_int8_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_uint64_int64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_uint32_int64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_uint16_int64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_cast_k_uint8_int64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_float64_int32(const rvm_avx512_float64_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_float32_int32(const rvm_avx512_float32_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_int64_int32(const rvm_avx512_int64_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_int32_int32(const rvm_avx512_int32_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_int16_int32(const rvm_avx512_int16_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_int8_int32(const rvm_avx512_int8_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_uint64_int32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_uint32_int32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_uint16_int32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_cast_k_uint8_int32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_float64_int16(const rvm_avx512_float64_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_float32_int16(const rvm_avx512_float32_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_int64_int16(const rvm_avx512_int64_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_int32_int16(const rvm_avx512_int32_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_int16_int16(const rvm_avx512_int16_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_int8_int16(const rvm_avx512_int8_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_uint64_int16(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_uint32_int16(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_uint16_int16(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int16_t mipp_avx512_cast_k_uint8_int16(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_float64_int8(const rvm_avx512_float64_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_float32_int8(const rvm_avx512_float32_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_int64_int8(const rvm_avx512_int64_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_int32_int8(const rvm_avx512_int32_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_int16_int8(const rvm_avx512_int16_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_int8_int8(const rvm_avx512_int8_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_uint64_int8(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_uint32_int8(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_uint16_int8(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_int8_t mipp_avx512_cast_k_uint8_int8(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_float64_uint64(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_float32_uint64(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_int64_uint64(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_int32_uint64(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_int16_uint64(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_int8_uint64(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_uint64_uint64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_uint32_uint64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_uint16_uint64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint64_t mipp_avx512_cast_k_uint8_uint64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_float64_uint32(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_float32_uint32(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_int64_uint32(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_int32_uint32(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_int16_uint32(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_int8_uint32(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_uint64_uint32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_uint32_uint32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_uint16_uint32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint32_t mipp_avx512_cast_k_uint8_uint32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_float64_uint16(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_float32_uint16(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_int64_uint16(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_int32_uint16(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_int16_uint16(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_int8_uint16(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_uint64_uint16(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_uint32_uint16(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_uint16_uint16(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint16_t mipp_avx512_cast_k_uint8_uint16(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_float64_uint8(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_float32_uint8(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_int64_uint8(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_int32_uint8(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_int16_uint8(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_int8_uint8(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_uint64_uint8(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_uint32_uint8(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_uint16_uint8(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvm_avx512_uint8_t mipp_avx512_cast_k_uint8_uint8(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_toreg_float64(const rvm_avx512_float64_t m0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_castsi512_pd(m0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_toreg_float32(const rvm_avx512_float32_t m0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_castsi512_ps(m0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_toreg_int64(const rvm_avx512_int64_t m0) {
	rvd_avx512_int64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_toreg_int32(const rvm_avx512_int32_t m0) {
	rvd_avx512_int32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_toreg_int16(const rvm_avx512_int16_t m0) {
	rvd_avx512_int16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_toreg_int8(const rvm_avx512_int8_t m0) {
	rvd_avx512_int8_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_toreg_uint64(const rvm_avx512_uint64_t m0) {
	rvd_avx512_uint64_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_toreg_uint32(const rvm_avx512_uint32_t m0) {
	rvd_avx512_uint32_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_toreg_uint16(const rvm_avx512_uint16_t m0) {
	rvd_avx512_uint16_t res;
	res.m = m0.m;
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_toreg_uint8(const rvm_avx512_uint8_t m0) {
	rvd_avx512_uint8_t res;
	res.m = m0.m;
	return res;
}
#endif
rvm_avx512_float64_t mipp_avx512_tomsk_float64(const rvd_avx512_float64_t r0) {
	rvm_avx512_float64_t res;
	res.m = _mm512_castpd_si512(r0.m);
	return res;
}
rvm_avx512_float32_t mipp_avx512_tomsk_float32(const rvd_avx512_float32_t r0) {
	rvm_avx512_float32_t res;
	res.m = _mm512_castps_si512(r0.m);
	return res;
}
rvm_avx512_int64_t mipp_avx512_tomsk_int64(const rvd_avx512_int64_t r0) {
	rvm_avx512_int64_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_int32_t mipp_avx512_tomsk_int32(const rvd_avx512_int32_t r0) {
	rvm_avx512_int32_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_int16_t mipp_avx512_tomsk_int16(const rvd_avx512_int16_t r0) {
	rvm_avx512_int16_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_int8_t mipp_avx512_tomsk_int8(const rvd_avx512_int8_t r0) {
	rvm_avx512_int8_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_uint64_t mipp_avx512_tomsk_uint64(const rvd_avx512_uint64_t r0) {
	rvm_avx512_uint64_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_uint32_t mipp_avx512_tomsk_uint32(const rvd_avx512_uint32_t r0) {
	rvm_avx512_uint32_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_uint16_t mipp_avx512_tomsk_uint16(const rvd_avx512_uint16_t r0) {
	rvm_avx512_uint16_t res;
	res.m = r0.m;
	return res;
}
rvm_avx512_uint8_t mipp_avx512_tomsk_uint8(const rvd_avx512_uint8_t r0) {
	rvm_avx512_uint8_t res;
	res.m = r0.m;
	return res;
}
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float64_t mipp_avx512_load_float64(const float64_t* p0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_load_pd((float64_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float32_t mipp_avx512_load_float32(const float32_t* p0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_load_ps((float32_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int64_t mipp_avx512_load_int64(const int64_t* p0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_load_si512((int64_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int32_t mipp_avx512_load_int32(const int32_t* p0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_load_si512((int32_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int16_t mipp_avx512_load_int16(const int16_t* p0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_load_si512((int16_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int8_t mipp_avx512_load_int8(const int8_t* p0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_load_si512((int8_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint64_t mipp_avx512_load_uint64(const uint64_t* p0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_load_si512((uint64_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint32_t mipp_avx512_load_uint32(const uint32_t* p0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_load_si512((uint32_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint16_t mipp_avx512_load_uint16(const uint16_t* p0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_load_si512((uint16_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint8_t mipp_avx512_load_uint8(const uint8_t* p0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_load_si512((uint8_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float64_t mipp_avx512_load_float64(const float64_t* p0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_loadu_pd((float64_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float32_t mipp_avx512_load_float32(const float32_t* p0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_loadu_ps((float32_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int64_t mipp_avx512_load_int64(const int64_t* p0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_loadu_si512((int64_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int32_t mipp_avx512_load_int32(const int32_t* p0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_loadu_si512((int32_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int16_t mipp_avx512_load_int16(const int16_t* p0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_loadu_si512((int16_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int8_t mipp_avx512_load_int8(const int8_t* p0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_loadu_si512((int8_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint64_t mipp_avx512_load_uint64(const uint64_t* p0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_loadu_si512((uint64_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint32_t mipp_avx512_load_uint32(const uint32_t* p0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_loadu_si512((uint32_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint16_t mipp_avx512_load_uint16(const uint16_t* p0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_loadu_si512((uint16_t*) p0);
	return res;
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint8_t mipp_avx512_load_uint8(const uint8_t* p0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_loadu_si512((uint8_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_loadu_float64(const float64_t* p0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_loadu_pd((float64_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_loadu_float32(const float32_t* p0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_loadu_ps((float32_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_loadu_int64(const int64_t* p0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_loadu_si512((int64_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_loadu_int32(const int32_t* p0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_loadu_si512((int32_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_loadu_int16(const int16_t* p0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_loadu_si512((int16_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_loadu_int8(const int8_t* p0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_loadu_si512((int8_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_loadu_uint64(const uint64_t* p0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_loadu_si512((uint64_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_loadu_uint32(const uint32_t* p0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_loadu_si512((uint32_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_loadu_uint16(const uint16_t* p0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_loadu_si512((uint16_t*) p0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_loadu_uint8(const uint8_t* p0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_loadu_si512((uint8_t*) p0);
	return res;
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_store_pd((float64_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_store_ps((float32_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_store_si512((int64_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_store_si512((int32_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_store_si512((int16_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_store_si512((int8_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_store_si512((uint64_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_store_si512((uint32_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_store_si512((uint16_t*) p0, r0.m);
}
#endif
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_store_si512((uint8_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_storeu_pd((float64_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_storeu_ps((float32_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_storeu_si512((int64_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_storeu_si512((int32_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_storeu_si512((int16_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_storeu_si512((int8_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_storeu_si512((uint64_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_storeu_si512((uint32_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_storeu_si512((uint16_t*) p0, r0.m);
}
#endif
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_storeu_si512((uint8_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_storeu_pd((float64_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_storeu_ps((float32_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_storeu_si512((int64_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_storeu_si512((int32_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_storeu_si512((int16_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_storeu_si512((int8_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_storeu_si512((uint64_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_storeu_si512((uint32_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_storeu_si512((uint16_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
void mipp_avx512_storeu_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_storeu_si512((uint8_t*) p0, r0.m);
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_set1_float64(const float64_t v0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_set1_pd(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_set1_float32(const float32_t v0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_set1_ps(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_set1_int64(const int64_t v0) {
	rvd_avx512_int64_t res;
	res.m = _mm512_set1_epi64(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_set1_int32(const int32_t v0) {
	rvd_avx512_int32_t res;
	res.m = _mm512_set1_epi32(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_set1_int16(const int16_t v0) {
	rvd_avx512_int16_t res;
	res.m = _mm512_set1_epi16(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_set1_int8(const int8_t v0) {
	rvd_avx512_int8_t res;
	res.m = _mm512_set1_epi8(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_set1_uint64(const uint64_t v0) {
	rvd_avx512_uint64_t res;
	res.m = _mm512_set1_epu64(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_set1_uint32(const uint32_t v0) {
	rvd_avx512_uint32_t res;
	res.m = _mm512_set1_epu32(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_set1_uint16(const uint16_t v0) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_set1_epu16(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_set1_uint8(const uint8_t v0) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_set1_epu8(v0);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_set0_float64() {
	rvd_avx512_float64_t res;
	res.m = _mm512_setzero_pd();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_set0_float32() {
	rvd_avx512_float32_t res;
	res.m = _mm512_setzero_ps();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_set0_int64() {
	rvd_avx512_int64_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_set0_int32() {
	rvd_avx512_int32_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_set0_int16() {
	rvd_avx512_int16_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int8_t mipp_avx512_set0_int8() {
	rvd_avx512_int8_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint64_t mipp_avx512_set0_uint64() {
	rvd_avx512_uint64_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint32_t mipp_avx512_set0_uint32() {
	rvd_avx512_uint32_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint16_t mipp_avx512_set0_uint16() {
	rvd_avx512_uint16_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_uint8_t mipp_avx512_set0_uint8() {
	rvd_avx512_uint8_t res;
	res.m = _mm512_setzero_si512();
	return res;
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
float64_t mipp_avx512_low_float64(const rvd_avx512_float64_t r0) {
 return mipp_avx512_cast_float64_float32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_float64(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ))
float32_t mipp_avx512_low_float32(const rvd_avx512_float32_t r0) {
 return mipp_avx512_cast_float32_float32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_float32(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int64_t mipp_avx512_low_int64(const rvd_avx512_int64_t r0) {
 return mipp_avx512_cast_int64_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int64(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int32_t mipp_avx512_low_int32(const rvd_avx512_int32_t r0) {
 return mipp_avx512_cast_int32_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int32(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int16_t mipp_avx512_low_int16(const rvd_avx512_int16_t r0) {
 return mipp_avx512_cast_int16_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int16(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int8_t mipp_avx512_low_int8(const rvd_avx512_int8_t r0) {
 return mipp_avx512_cast_int8_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int8(r0).m, 0));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
float64_t mipp_avx512_high_float64(const rvd_avx512_float64_t r0) {
 return mipp_avx512_cast_float64_float32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_float64(r0).m, 1));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ))
float32_t mipp_avx512_high_float32(const rvd_avx512_float32_t r0) {
 return mipp_avx512_cast_float32_float32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_float32(r0).m, 1));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int64_t mipp_avx512_high_int64(const rvd_avx512_int64_t r0) {
 return mipp_avx512_cast_int64_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int64(r0).m, 1));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int32_t mipp_avx512_high_int32(const rvd_avx512_int32_t r0) {
 return mipp_avx512_cast_int32_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int32(r0).m, 1));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int16_t mipp_avx512_high_int16(const rvd_avx512_int16_t r0) {
 return mipp_avx512_cast_int16_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int16(r0).m, 1));
}
#endif
#if defined(__AVX512F__) && (( ( ( defined(__AVX512F__) ) ) ) && ( ( ( defined(__AVX512F__) ) ) ))
int8_t mipp_avx512_high_int8(const rvd_avx512_int8_t r0) {
 return mipp_avx512_cast_int8_int32(_mm512_extractf64x4_pd(mipp_avx512_cast_float32_int8(r0).m, 1));
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_sqrt_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t res;
	res.m = _mm512_sqrt_pd(r0.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_sqrt_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_sqrt_ps(r0.m);
	return res;
}
#endif
rvd_avx512_float32_t mipp_avx512_rsqrt_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.m = _mm512_rsqrt_ps(r0.m);
	return res;
}
rvd_avx512_float64_t mipp_avx512_add_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_add_pd(r0.m, r1.m);
	return res;
}
rvd_avx512_float32_t mipp_avx512_add_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_add_ps(r0.m, r1.m);
	return res;
}
rvd_avx512_int32_t mipp_avx512_add_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.m = _mm512_add_epi32(r0.m, r1.m);
	return res;
}
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_add_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.m = _mm512_add_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_add_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.m = _mm512_adds_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_add_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.m = _mm512_adds_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_uint16_t mipp_avx512_add_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.m = _mm512_adds_epu16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_uint8_t mipp_avx512_add_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.m = _mm512_adds_epu8(r0.m, r1.m);
	return res;
}
#endif
rvd_avx512_float64_t mipp_avx512_sub_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_sub_pd(r0.m, r1.m);
	return res;
}
rvd_avx512_float32_t mipp_avx512_sub_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_sub_ps(r0.m, r1.m);
	return res;
}
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_sub_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.m = _mm512_sub_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_sub_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.m = _mm512_sub_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_sub_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.m = _mm512_subs_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_sub_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.m = _mm512_subs_epi8(r0.m, r1.m);
	return res;
}
#endif
rvd_avx512_float64_t mipp_avx512_mul_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_mul_pd(r0.m, r1.m);
	return res;
}
rvd_avx512_float32_t mipp_avx512_mul_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_mul_ps(r0.m, r1.m);
	return res;
}
rvd_avx512_int32_t mipp_avx512_mul_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.m = _mm512_mullo_epi32(r0.m, r1.m);
	return res;
}
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_mul_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.m = _mm512_mullo_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_float64_t mipp_avx512_div_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_div_pd(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_float32_t mipp_avx512_div_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_div_ps(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_min_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_min_pd(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_min_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_min_ps(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_min_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.m = _mm512_min_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_min_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.m = _mm512_min_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_min_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.m = _mm512_min_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_min_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.m = _mm512_min_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float64_t mipp_avx512_min_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_gmin_pd(r0.m, r1.m);
	return res;
}
#endif
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float32_t mipp_avx512_min_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_gmin_ps(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_max_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_max_pd(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_max_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_max_ps(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_max_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.m = _mm512_max_epi64(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_max_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.m = _mm512_max_epi32(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_max_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.m = _mm512_max_epi16(r0.m, r1.m);
	return res;
}
#endif
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_max_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.m = _mm512_max_epi8(r0.m, r1.m);
	return res;
}
#endif
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float64_t mipp_avx512_max_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.m = _mm512_gmax_pd(r0.m, r1.m);
	return res;
}
#endif
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float32_t mipp_avx512_max_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.m = _mm512_gmax_ps(r0.m, r1.m);
	return res;
}
#endif
rvd_avx512_float64_t mipp_avx512_fmadd_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1, const rvd_avx512_float64_t r2) {
	rvd_avx512_float64_t res;
	res.m = _mm512_fmadd_pd(r0.m, r1.m, r2.m);
	return res;
}
rvd_avx512_float32_t mipp_avx512_fmadd_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1, const rvd_avx512_float32_t r2) {
	rvd_avx512_float32_t res;
	res.m = _mm512_fmadd_ps(r0.m, r1.m, r2.m);
	return res;
}
