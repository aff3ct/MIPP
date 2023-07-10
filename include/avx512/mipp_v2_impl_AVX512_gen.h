#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX512_H_
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
typedef struct { __m512d r; } rvd_avx512_float64_t;
typedef struct { __m512 r; } rvd_avx512_float32_t;
typedef struct { __m512i r; } rvd_avx512_int64_t;
typedef struct { __m512i r; } rvd_avx512_int32_t;
typedef struct { __m512i r; } rvd_avx512_int16_t;
typedef struct { __m512i r; } rvd_avx512_int8_t;
typedef struct { __m512i r; } rvd_avx512_uint64_t;
typedef struct { __m512i r; } rvd_avx512_uint32_t;
typedef struct { __m512i r; } rvd_avx512_uint16_t;
typedef struct { __m512i r; } rvd_avx512_uint8_t;
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
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_float64_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_float32_float64(const rvd_avx512_float32_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castps_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_int64_float64(const rvd_avx512_int64_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_int32_float64(const rvd_avx512_int32_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_int16_float64(const rvd_avx512_int16_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_int8_float64(const rvd_avx512_int8_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_uint64_float64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_uint32_float64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_uint16_float64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float64_t mipp_avx512_cast_uint8_float64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_float64_float32(const rvd_avx512_float64_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castpd_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_float32_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_int64_float32(const rvd_avx512_int64_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_int32_float32(const rvd_avx512_int32_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_int16_float32(const rvd_avx512_int16_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_int8_float32(const rvd_avx512_int8_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_uint64_float32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_uint32_float32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_uint16_float32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_float32_t mipp_avx512_cast_uint8_float32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_float64_int64(const rvd_avx512_float64_t r0) {
	rvd_avx512_int64_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_float32_int64(const rvd_avx512_float32_t r0) {
	rvd_avx512_int64_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_int64_int64(const rvd_avx512_int64_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_int32_int64(const rvd_avx512_int32_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_int16_int64(const rvd_avx512_int16_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_int8_int64(const rvd_avx512_int8_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_uint64_int64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_uint32_int64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_uint16_int64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int64_t mipp_avx512_cast_uint8_int64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_float64_int32(const rvd_avx512_float64_t r0) {
	rvd_avx512_int32_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_float32_int32(const rvd_avx512_float32_t r0) {
	rvd_avx512_int32_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_int64_int32(const rvd_avx512_int64_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_int32_int32(const rvd_avx512_int32_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_int16_int32(const rvd_avx512_int16_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_int8_int32(const rvd_avx512_int8_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_uint64_int32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_uint32_int32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_uint16_int32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int32_t mipp_avx512_cast_uint8_int32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_float64_int16(const rvd_avx512_float64_t r0) {
	rvd_avx512_int16_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_float32_int16(const rvd_avx512_float32_t r0) {
	rvd_avx512_int16_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_int64_int16(const rvd_avx512_int64_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_int32_int16(const rvd_avx512_int32_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_int16_int16(const rvd_avx512_int16_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_int8_int16(const rvd_avx512_int8_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_uint64_int16(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_uint32_int16(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_uint16_int16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int16_t mipp_avx512_cast_uint8_int16(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_float64_int8(const rvd_avx512_float64_t r0) {
	rvd_avx512_int8_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_float32_int8(const rvd_avx512_float32_t r0) {
	rvd_avx512_int8_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_int64_int8(const rvd_avx512_int64_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_int32_int8(const rvd_avx512_int32_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_int16_int8(const rvd_avx512_int16_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_int8_int8(const rvd_avx512_int8_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_uint64_int8(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_uint32_int8(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_uint16_int8(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_int8_t mipp_avx512_cast_uint8_int8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_float64_uint64(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint64_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_float32_uint64(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint64_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_int64_uint64(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_int32_uint64(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_int16_uint64(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_int8_uint64(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_uint64_uint64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_uint32_uint64(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_uint16_uint64(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint64_t mipp_avx512_cast_uint8_uint64(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint64_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_float64_uint32(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint32_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_float32_uint32(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint32_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_int64_uint32(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_int32_uint32(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_int16_uint32(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_int8_uint32(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_uint64_uint32(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_uint32_uint32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_uint16_uint32(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint32_t mipp_avx512_cast_uint8_uint32(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint32_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_float64_uint16(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint16_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_float32_uint16(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint16_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_int64_uint16(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_int32_uint16(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_int16_uint16(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_int8_uint16(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_uint64_uint16(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_uint32_uint16(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_uint16_uint16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint16_t mipp_avx512_cast_uint8_uint16(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint16_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_float64_uint8(const rvd_avx512_float64_t r0) {
	rvd_avx512_uint8_t res;
	res.r= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_float32_uint8(const rvd_avx512_float32_t r0) {
	rvd_avx512_uint8_t res;
	res.r= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_int64_uint8(const rvd_avx512_int64_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_int32_uint8(const rvd_avx512_int32_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_int16_uint8(const rvd_avx512_int16_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_int8_uint8(const rvd_avx512_int8_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_uint64_uint8(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_uint32_uint8(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_uint16_uint8(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
rvd_avx512_uint8_t mipp_avx512_cast_uint8_uint8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint8_t res;
	res.r= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_float64_float64(const rvm_avx512_float64_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_float32_float64(const rvm_avx512_float32_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_int64_float64(const rvm_avx512_int64_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_int32_float64(const rvm_avx512_int32_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_int16_float64(const rvm_avx512_int16_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_int8_float64(const rvm_avx512_int8_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_uint64_float64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_uint32_float64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_uint16_float64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float64_t mipp_avx512_cast_k_uint8_float64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_float64_float32(const rvm_avx512_float64_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_float32_float32(const rvm_avx512_float32_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_int64_float32(const rvm_avx512_int64_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_int32_float32(const rvm_avx512_int32_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_int16_float32(const rvm_avx512_int16_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_int8_float32(const rvm_avx512_int8_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_uint64_float32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_uint32_float32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_uint16_float32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_float32_t mipp_avx512_cast_k_uint8_float32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_float64_int64(const rvm_avx512_float64_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_float32_int64(const rvm_avx512_float32_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_int64_int64(const rvm_avx512_int64_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_int32_int64(const rvm_avx512_int32_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_int16_int64(const rvm_avx512_int16_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_int8_int64(const rvm_avx512_int8_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_uint64_int64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_uint32_int64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_uint16_int64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int64_t mipp_avx512_cast_k_uint8_int64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_float64_int32(const rvm_avx512_float64_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_float32_int32(const rvm_avx512_float32_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_int64_int32(const rvm_avx512_int64_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_int32_int32(const rvm_avx512_int32_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_int16_int32(const rvm_avx512_int16_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_int8_int32(const rvm_avx512_int8_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_uint64_int32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_uint32_int32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_uint16_int32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int32_t mipp_avx512_cast_k_uint8_int32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_float64_int16(const rvm_avx512_float64_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_float32_int16(const rvm_avx512_float32_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_int64_int16(const rvm_avx512_int64_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_int32_int16(const rvm_avx512_int32_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_int16_int16(const rvm_avx512_int16_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_int8_int16(const rvm_avx512_int8_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_uint64_int16(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_uint32_int16(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_uint16_int16(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int16_t mipp_avx512_cast_k_uint8_int16(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_float64_int8(const rvm_avx512_float64_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_float32_int8(const rvm_avx512_float32_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_int64_int8(const rvm_avx512_int64_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_int32_int8(const rvm_avx512_int32_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_int16_int8(const rvm_avx512_int16_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_int8_int8(const rvm_avx512_int8_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_uint64_int8(const rvm_avx512_uint64_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_uint32_int8(const rvm_avx512_uint32_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_uint16_int8(const rvm_avx512_uint16_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_int8_t mipp_avx512_cast_k_uint8_int8(const rvm_avx512_uint8_t m0) {
	rvm_avx512_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_float64_uint64(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_float32_uint64(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_int64_uint64(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_int32_uint64(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_int16_uint64(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_int8_uint64(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_uint64_uint64(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_uint32_uint64(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_uint16_uint64(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint64_t mipp_avx512_cast_k_uint8_uint64(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_float64_uint32(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_float32_uint32(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_int64_uint32(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_int32_uint32(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_int16_uint32(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_int8_uint32(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_uint64_uint32(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_uint32_uint32(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_uint16_uint32(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint32_t mipp_avx512_cast_k_uint8_uint32(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_float64_uint16(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_float32_uint16(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_int64_uint16(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_int32_uint16(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_int16_uint16(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_int8_uint16(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_uint64_uint16(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_uint32_uint16(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_uint16_uint16(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint16_t mipp_avx512_cast_k_uint8_uint16(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_float64_uint8(const rvm_avx512_float64_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_float32_uint8(const rvm_avx512_float32_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_int64_uint8(const rvm_avx512_int64_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_int32_uint8(const rvm_avx512_int32_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_int16_uint8(const rvm_avx512_int16_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_int8_uint8(const rvm_avx512_int8_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_uint64_uint8(const rvm_avx512_uint64_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_uint32_uint8(const rvm_avx512_uint32_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_uint16_uint8(const rvm_avx512_uint16_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
rvm_avx512_uint8_t mipp_avx512_cast_k_uint8_uint8(const rvm_avx512_uint8_t m0) {
	rvm_avx512_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_float64_t mipp_avx512_toreg_float64(const rvm_avx512_float64_t m0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_castsi512_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_float32_t mipp_avx512_toreg_float32(const rvm_avx512_float32_t m0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_castsi512_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_int64_t mipp_avx512_toreg_int64(const rvm_avx512_int64_t m0) {
	rvd_avx512_int64_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_int32_t mipp_avx512_toreg_int32(const rvm_avx512_int32_t m0) {
	rvd_avx512_int32_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_int16_t mipp_avx512_toreg_int16(const rvm_avx512_int16_t m0) {
	rvd_avx512_int16_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_int8_t mipp_avx512_toreg_int8(const rvm_avx512_int8_t m0) {
	rvd_avx512_int8_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_uint64_t mipp_avx512_toreg_uint64(const rvm_avx512_uint64_t m0) {
	rvd_avx512_uint64_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_uint32_t mipp_avx512_toreg_uint32(const rvm_avx512_uint32_t m0) {
	rvd_avx512_uint32_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_uint16_t mipp_avx512_toreg_uint16(const rvm_avx512_uint16_t m0) {
	rvd_avx512_uint16_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
rvd_avx512_uint8_t mipp_avx512_toreg_uint8(const rvm_avx512_uint8_t m0) {
	rvd_avx512_uint8_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_float64_t mipp_avx512_tomsk_float64(const rvd_avx512_float64_t r0) {
	rvm_avx512_float64_t res;
	res.m= _mm512_castpd_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_float32_t mipp_avx512_tomsk_float32(const rvd_avx512_float32_t r0) {
	rvm_avx512_float32_t res;
	res.m= _mm512_castps_si512(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_int64_t mipp_avx512_tomsk_int64(const rvd_avx512_int64_t r0) {
	rvm_avx512_int64_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_int32_t mipp_avx512_tomsk_int32(const rvd_avx512_int32_t r0) {
	rvm_avx512_int32_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_int16_t mipp_avx512_tomsk_int16(const rvd_avx512_int16_t r0) {
	rvm_avx512_int16_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_int8_t mipp_avx512_tomsk_int8(const rvd_avx512_int8_t r0) {
	rvm_avx512_int8_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_uint64_t mipp_avx512_tomsk_uint64(const rvd_avx512_uint64_t r0) {
	rvm_avx512_uint64_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_uint32_t mipp_avx512_tomsk_uint32(const rvd_avx512_uint32_t r0) {
	rvm_avx512_uint32_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_uint16_t mipp_avx512_tomsk_uint16(const rvd_avx512_uint16_t r0) {
	rvm_avx512_uint16_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
rvm_avx512_uint8_t mipp_avx512_tomsk_uint8(const rvd_avx512_uint8_t r0) {
	rvm_avx512_uint8_t res;
	res.m= r0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float64_t mipp_avx512_load_float64(const float64_t* p0) {
_mm512_load_pd((float64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float32_t mipp_avx512_load_float32(const float32_t* p0) {
_mm512_load_ps((float32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int64_t mipp_avx512_load_int64(const int64_t* p0) {
_mm512_load_si512((int64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int32_t mipp_avx512_load_int32(const int32_t* p0) {
_mm512_load_si512((int32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int16_t mipp_avx512_load_int16(const int16_t* p0) {
_mm512_load_si512((int16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int8_t mipp_avx512_load_int8(const int8_t* p0) {
_mm512_load_si512((int8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint64_t mipp_avx512_load_uint64(const uint64_t* p0) {
_mm512_load_si512((uint64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint32_t mipp_avx512_load_uint32(const uint32_t* p0) {
_mm512_load_si512((uint32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint16_t mipp_avx512_load_uint16(const uint16_t* p0) {
_mm512_load_si512((uint16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint8_t mipp_avx512_load_uint8(const uint8_t* p0) {
_mm512_load_si512((uint8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float64_t mipp_avx512_load_float64(const float64_t* p0) {
_mm512_loadu_pd((float64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_float32_t mipp_avx512_load_float32(const float32_t* p0) {
_mm512_loadu_ps((float32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int64_t mipp_avx512_load_int64(const int64_t* p0) {
_mm512_loadu_si512((int64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int32_t mipp_avx512_load_int32(const int32_t* p0) {
_mm512_loadu_si512((int32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int16_t mipp_avx512_load_int16(const int16_t* p0) {
_mm512_loadu_si512((int16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_int8_t mipp_avx512_load_int8(const int8_t* p0) {
_mm512_loadu_si512((int8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint64_t mipp_avx512_load_uint64(const uint64_t* p0) {
_mm512_loadu_si512((uint64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint32_t mipp_avx512_load_uint32(const uint32_t* p0) {
_mm512_loadu_si512((uint32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint16_t mipp_avx512_load_uint16(const uint16_t* p0) {
_mm512_loadu_si512((uint16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
rvd_avx512_uint8_t mipp_avx512_load_uint8(const uint8_t* p0) {
_mm512_loadu_si512((uint8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_float64_t mipp_avx512_loadu_float64(const float64_t* p0) {
_mm512_loadu_pd((float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_float32_t mipp_avx512_loadu_float32(const float32_t* p0) {
_mm512_loadu_ps((float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_int64_t mipp_avx512_loadu_int64(const int64_t* p0) {
_mm512_loadu_si512((int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_int32_t mipp_avx512_loadu_int32(const int32_t* p0) {
_mm512_loadu_si512((int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_int16_t mipp_avx512_loadu_int16(const int16_t* p0) {
_mm512_loadu_si512((int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_int8_t mipp_avx512_loadu_int8(const int8_t* p0) {
_mm512_loadu_si512((int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_uint64_t mipp_avx512_loadu_uint64(const uint64_t* p0) {
_mm512_loadu_si512((uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_uint32_t mipp_avx512_loadu_uint32(const uint32_t* p0) {
_mm512_loadu_si512((uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_uint16_t mipp_avx512_loadu_uint16(const uint16_t* p0) {
_mm512_loadu_si512((uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
rvd_avx512_uint8_t mipp_avx512_loadu_uint8(const uint8_t* p0) {
_mm512_loadu_si512((uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_store_pd((float64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_store_ps((float32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_store_si512((int64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_store_si512((int32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_store_si512((int16_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_store_si512((int8_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_store_si512((uint64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_store_si512((uint32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_store_si512((uint16_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_store_si512((uint8_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_storeu_pd((float64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_storeu_ps((float32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_storeu_si512((int64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_storeu_si512((int32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_storeu_si512((int16_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_storeu_si512((int8_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_storeu_si512((uint64_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_storeu_si512((uint32_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_storeu_si512((uint16_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
void mipp_avx512_store_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_storeu_si512((uint8_t*) p0, r0.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	_mm512_storeu_pd((float64_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	_mm512_storeu_ps((float32_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	_mm512_storeu_si512((int64_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	_mm512_storeu_si512((int32_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	_mm512_storeu_si512((int16_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	_mm512_storeu_si512((int8_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	_mm512_storeu_si512((uint64_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	_mm512_storeu_si512((uint32_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	_mm512_storeu_si512((uint16_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
void mipp_avx512_storeu_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	_mm512_storeu_si512((uint8_t*) p0, r0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
float64_t mipp_avx512_getfirst_float64(const rvd_avx512_float64_t r0) {
 return _mm512_cvtsd_f64(mipp_avx512_cast_float64_int64(r0).m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
float32_t mipp_avx512_getfirst_float32(const rvd_avx512_float32_t r0) {
 return _mm512_cvtss_f32(mipp_avx512_cast_float32_int32(r0).m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_float64_t mipp_avx512_set1_float64(const float64_t v0) {
_mm512_set1_pd(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_float32_t mipp_avx512_set1_float32(const float32_t v0) {
_mm512_set1_ps(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_int64_t mipp_avx512_set1_int64(const int64_t v0) {
_mm512_set1_epi64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_int32_t mipp_avx512_set1_int32(const int32_t v0) {
_mm512_set1_epi32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_int16_t mipp_avx512_set1_int16(const int16_t v0) {
_mm512_set1_epi16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_int8_t mipp_avx512_set1_int8(const int8_t v0) {
_mm512_set1_epi8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_uint64_t mipp_avx512_set1_uint64(const uint64_t v0) {
_mm512_set1_epu64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_uint32_t mipp_avx512_set1_uint32(const uint32_t v0) {
_mm512_set1_epu32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_uint16_t mipp_avx512_set1_uint16(const uint16_t v0) {
_mm512_set1_epu16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
rvd_avx512_uint8_t mipp_avx512_set1_uint8(const uint8_t v0) {
_mm512_set1_epu8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_float64_t mipp_avx512_set0_float64() {
_mm512_setzero_pd();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_float32_t mipp_avx512_set0_float32() {
_mm512_setzero_ps();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_int64_t mipp_avx512_set0_int64() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_int32_t mipp_avx512_set0_int32() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_int16_t mipp_avx512_set0_int16() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_int8_t mipp_avx512_set0_int8() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_uint64_t mipp_avx512_set0_uint64() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_uint32_t mipp_avx512_set0_uint32() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_uint16_t mipp_avx512_set0_uint16() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
rvd_avx512_uint8_t mipp_avx512_set0_uint8() {
_mm512_setzero_si512();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sqrt
rvd_avx512_float64_t mipp_avx512_sqrt_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t res;
	res.r= _mm512_sqrt_pd(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sqrt
rvd_avx512_float32_t mipp_avx512_sqrt_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_sqrt_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- rsqrt
rvd_avx512_float32_t mipp_avx512_rsqrt_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t res;
	res.r= _mm512_rsqrt_ps(r0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
rvd_avx512_float64_t mipp_avx512_add_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_add_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
rvd_avx512_float32_t mipp_avx512_add_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_add_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
rvd_avx512_int32_t mipp_avx512_add_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_add_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
rvd_avx512_int64_t mipp_avx512_add_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_add_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_add_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_adds_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_add_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_adds_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__AVX512BW__)
rvd_avx512_uint16_t mipp_avx512_add_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.r= 	rvd_avx512_uint16_t res;
	res.r= _mm512_adds_epu16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__AVX512BW__)
rvd_avx512_uint8_t mipp_avx512_add_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.r= 	rvd_avx512_uint8_t res;
	res.r= _mm512_adds_epu8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
rvd_avx512_float64_t mipp_avx512_sub_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_sub_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
rvd_avx512_float32_t mipp_avx512_sub_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_sub_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
rvd_avx512_int64_t mipp_avx512_sub_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_sub_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
rvd_avx512_int32_t mipp_avx512_sub_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_sub_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_sub_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_subs_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_sub_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_subs_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
rvd_avx512_float64_t mipp_avx512_mul_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_mul_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
rvd_avx512_float32_t mipp_avx512_mul_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_mul_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
rvd_avx512_int32_t mipp_avx512_mul_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_mullo_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_mul_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_mullo_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
#if defined(__AVX512BW__)
rvd_avx512_float64_t mipp_avx512_div_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_div_pd(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
#if defined(__AVX512BW__)
rvd_avx512_float32_t mipp_avx512_div_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_div_ps(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
rvd_avx512_float64_t mipp_avx512_min_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_min_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
rvd_avx512_float32_t mipp_avx512_min_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_min_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
rvd_avx512_int64_t mipp_avx512_min_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_min_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
rvd_avx512_int32_t mipp_avx512_min_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_min_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_min_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_min_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_min_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_min_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
// ---------------------------------------------------------------------------------------------------------------------------------------------- min
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
rvd_avx512_float64_t mipp_avx512_max_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_max_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
rvd_avx512_float32_t mipp_avx512_max_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_max_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
rvd_avx512_int64_t mipp_avx512_max_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_max_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
rvd_avx512_int32_t mipp_avx512_max_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_max_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_max_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_max_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_max_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_max_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
// ---------------------------------------------------------------------------------------------------------------------------------------------- max
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
rvd_avx512_float64_t mipp_avx512_fmadd_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1, const rvd_avx512_float64_t r2) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_fmadd_pd(r0.m, r1.m, r2.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
rvd_avx512_float32_t mipp_avx512_fmadd_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1, const rvd_avx512_float32_t r2) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_fmadd_ps(r0.m, r1.m, r2.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_int32_t mipp_avx512_fmadd_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1, const rvd_avx512_int32_t r2) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_fmadd_epi32(r0.m, r1.m, r2.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmsub
rvd_avx512_float64_t mipp_avx512_fmsub_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1, const rvd_avx512_float64_t r2) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_fmsub_pd(r0.m, r1.m, r2.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmsub
rvd_avx512_float32_t mipp_avx512_fmsub_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1, const rvd_avx512_float32_t r2) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_fmsub_ps(r0.m, r1.m, r2.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_float64_t mipp_avx512_andb_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_and_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_float32_t mipp_avx512_andb_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_and_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_int64_t mipp_avx512_andb_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_int32_t mipp_avx512_andb_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_int16_t mipp_avx512_andb_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_int8_t mipp_avx512_andb_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_uint64_t mipp_avx512_andb_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	rvd_avx512_uint64_t res;
	res.r= 	rvd_avx512_uint64_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_uint32_t mipp_avx512_andb_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	rvd_avx512_uint32_t res;
	res.r= 	rvd_avx512_uint32_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_uint16_t mipp_avx512_andb_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.r= 	rvd_avx512_uint16_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
rvd_avx512_uint8_t mipp_avx512_andb_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.r= 	rvd_avx512_uint8_t res;
	res.r= _mm512_and_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
rvm_avx512_int8_t mipp_avx512_andb_k_int8(const rvm_avx512_int8_t m0, const rvm_avx512_int8_t m1) {
_mm512_kand(m0.m, m1.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
rvm_avx512_int16_t mipp_avx512_andb_k_int16(const rvm_avx512_int16_t m0, const rvm_avx512_int16_t m1) {
_mm512_kand(m0.m, m1.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_float64_t mipp_avx512_andnb_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_andnot_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_float32_t mipp_avx512_andnb_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_andnot_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_int64_t mipp_avx512_andnb_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_int32_t mipp_avx512_andnb_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_int16_t mipp_avx512_andnb_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_int8_t mipp_avx512_andnb_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_uint64_t mipp_avx512_andnb_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	rvd_avx512_uint64_t res;
	res.r= 	rvd_avx512_uint64_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_uint32_t mipp_avx512_andnb_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	rvd_avx512_uint32_t res;
	res.r= 	rvd_avx512_uint32_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_uint16_t mipp_avx512_andnb_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.r= 	rvd_avx512_uint16_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
rvd_avx512_uint8_t mipp_avx512_andnb_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.r= 	rvd_avx512_uint8_t res;
	res.r= _mm512_andnot_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
rvm_avx512_int8_t mipp_avx512_andnb_k_int8(const rvm_avx512_int8_t m0, const rvm_avx512_int8_t m1) {
_mm512_kand(m0.m, m1.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
rvm_avx512_int16_t mipp_avx512_andnb_k_int16(const rvm_avx512_int16_t m0, const rvm_avx512_int16_t m1) {
_mm512_kand(m0.m, m1.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_float64_t mipp_avx512_xorb_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_xor_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_float32_t mipp_avx512_xorb_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_xor_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_int64_t mipp_avx512_xorb_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_int32_t mipp_avx512_xorb_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_int16_t mipp_avx512_xorb_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_int8_t mipp_avx512_xorb_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_uint64_t mipp_avx512_xorb_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	rvd_avx512_uint64_t res;
	res.r= 	rvd_avx512_uint64_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_uint32_t mipp_avx512_xorb_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	rvd_avx512_uint32_t res;
	res.r= 	rvd_avx512_uint32_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_uint16_t mipp_avx512_xorb_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.r= 	rvd_avx512_uint16_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
rvd_avx512_uint8_t mipp_avx512_xorb_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.r= 	rvd_avx512_uint8_t res;
	res.r= _mm512_xor_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_float64_t mipp_avx512_orb_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_or_pd(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_float32_t mipp_avx512_orb_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_or_ps(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_int64_t mipp_avx512_orb_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_int32_t mipp_avx512_orb_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_int16_t mipp_avx512_orb_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_int8_t mipp_avx512_orb_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_uint64_t mipp_avx512_orb_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	rvd_avx512_uint64_t res;
	res.r= 	rvd_avx512_uint64_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_uint32_t mipp_avx512_orb_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	rvd_avx512_uint32_t res;
	res.r= 	rvd_avx512_uint32_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_uint16_t mipp_avx512_orb_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_uint16_t res;
	res.r= 	rvd_avx512_uint16_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
rvd_avx512_uint8_t mipp_avx512_orb_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_uint8_t res;
	res.r= 	rvd_avx512_uint8_t res;
	res.r= _mm512_or_si512(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
rvm_avx512_int32_t mipp_avx512_cmpeq_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmpeq_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
rvm_avx512_int64_t mipp_avx512_cmpeq_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmpeq_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmpeq_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmpeq_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmpeq_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmpeq_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
rvm_avx512_float64_t mipp_avx512_cmpeq_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_EQ_OQ);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
rvm_avx512_float32_t mipp_avx512_cmpeq_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_EQ_OQ);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
rvm_avx512_float64_t mipp_avx512_cmpneq_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_NEQ_OQ);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
rvm_avx512_float32_t mipp_avx512_cmpneq_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_NEQ_OQ);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
rvm_avx512_int32_t mipp_avx512_cmpneq_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmpneq_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
rvm_avx512_int64_t mipp_avx512_cmpneq_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmpneq_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmpneq_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmpneq_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmpneq_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmpneq_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
rvm_avx512_float64_t mipp_avx512_cmplt_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_LT_OS);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
rvm_avx512_float32_t mipp_avx512_cmplt_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_LT_OS);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
rvm_avx512_int32_t mipp_avx512_cmplt_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmplt_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
rvm_avx512_int64_t mipp_avx512_cmplt_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmplt_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmplt_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmplt_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmplt_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmplt_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
rvm_avx512_float64_t mipp_avx512_cmple_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_LE_OS);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
rvm_avx512_float32_t mipp_avx512_cmple_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_LE_OS);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
rvm_avx512_int32_t mipp_avx512_cmple_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmple_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
rvm_avx512_int64_t mipp_avx512_cmple_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmple_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmple_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmple_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmple_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmple_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
rvm_avx512_int32_t mipp_avx512_cmpge_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmpge_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
rvm_avx512_int64_t mipp_avx512_cmpge_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmpge_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmpge_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmpge_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmpge_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmpge_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
rvm_avx512_float64_t mipp_avx512_cmpge_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_GE_OS);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
rvm_avx512_float32_t mipp_avx512_cmpge_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_GE_OS);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
rvm_avx512_float64_t mipp_avx512_cmpgt_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
 rvd_avx512_float64_t tmp;
    tmp.m = _mm512_cmp_pd_mask(r0.m, r1.m, _CMP_GT_OS);
    return mipp_avx512_tomsk_float64(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
rvm_avx512_float32_t mipp_avx512_cmpgt_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
 rvd_avx512_float32_t tmp;
    tmp.m = _mm512_cmp_ps_mask(r0.m, r1.m, _CMP_GT_OS);
    return mipp_avx512_tomsk_float32(tmp);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
rvm_avx512_int32_t mipp_avx512_cmpgt_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvm_avx512_int32_t res;
	res.m= 	rvm_avx512_int32_t res;
	res.m= _mm512_cmpgt_epi32(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
rvm_avx512_int64_t mipp_avx512_cmpgt_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvm_avx512_int64_t res;
	res.m= 	rvm_avx512_int64_t res;
	res.m= _mm512_cmpgt_epi64(r0.m, r1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__AVX512BW__)
rvm_avx512_int16_t mipp_avx512_cmpgt_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvm_avx512_int16_t res;
	res.m= 	rvm_avx512_int16_t res;
	res.m= _mm512_cmpgt_epi16(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__AVX512BW__)
rvm_avx512_int8_t mipp_avx512_cmpgt_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvm_avx512_int8_t res;
	res.m= 	rvm_avx512_int8_t res;
	res.m= _mm512_cmpgt_epi8(r0.m, r1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- round
#if defined(__MIC__) || defined(__KNCNI__)
float64_t mipp_avx512_round_float64(const rvd_avx512_float64_t r0) {
 return _mm512_round_pd(r0.m, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC, _MM_EXPADJ_NONE);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- round
#if defined(__MIC__) || defined(__KNCNI__)
float32_t mipp_avx512_round_float32(const rvd_avx512_float32_t r0) {
 return _mm512_round_ps(r0.m, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC, _MM_EXPADJ_NONE);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- round
float64_t mipp_avx512_round_float64(const rvd_avx512_float64_t r0) {
 return _mm512_roundscale_pd(r0.m, 0, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- round
float32_t mipp_avx512_round_float32(const rvd_avx512_float32_t r0) {
 return _mm512_roundscale_ps(r0.m, 0, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_blend_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1, const rvm_avx512_float64_t m0) {
	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= 	rvd_avx512_float64_t res;
	res.r= _mm512_mask_blend_pd(r0.m, r1.m, mipp_avx512_toreg_float64(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_blend_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1, const rvm_avx512_float32_t m0) {
	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= 	rvd_avx512_float32_t res;
	res.r= _mm512_mask_blend_ps(r0.m, r1.m, mipp_avx512_toreg_float32(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
rvd_avx512_int64_t mipp_avx512_blend_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1, const rvm_avx512_int64_t m0) {
	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= 	rvd_avx512_int64_t res;
	res.r= _mm512_mask_blend_epi64(r0.m, r1.m, mipp_avx512_toreg_int64(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_blend_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1, const rvm_avx512_int32_t m0) {
	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= 	rvd_avx512_int32_t res;
	res.r= _mm512_mask_blend_epi32(r0.m, r1.m, mipp_avx512_toreg_int32(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_blend_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1, const rvm_avx512_int8_t m0) {
	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= 	rvd_avx512_int8_t res;
	res.r= _mm512_mask_blend_epi8(r0.m, r1.m, mipp_avx512_toreg_int8(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_blend_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1, const rvm_avx512_int16_t m0) {
	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= 	rvd_avx512_int16_t res;
	res.r= _mm512_mask_blend_epi16(r0.m, r1.m, mipp_avx512_toreg_int16(m0).m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
rvd_avx512_float64_t mipp_avx512_hadd_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_add_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_add_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_add_pd(rs2.m, rs3.m);
    return rs3;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
rvd_avx512_int64_t mipp_avx512_hadd_int64(const rvd_avx512_int64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_int64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_int64_float32(r0.m)));
    rvd_avx512_int64_t rs1 = mipp_avx512_cast_float32_int64(rsf);
    rs1.m = _mm512_add_epi64(r0.m, rs1.m);
    rsf = mipp_avx512_cast_int64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_int64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_int64_float32(r0.m)));
    rvd_avx512_int64_t rs2 = mipp_avx512_cast_float32_int64(rsf);
    rs2.m = _mm512_add_epi64(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int64_t rs3 = mipp_avx512_cast_float32_int64(rsf);
    rs3.m = _mm512_add_epi64(rs2.m, rs3.m);
    return rs3;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
rvd_avx512_float32_t mipp_avx512_hadd_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_add_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_add_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_add_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_add_ps(rs3.m, rs4.m);
    return rs4;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
rvd_avx512_int32_t mipp_avx512_hadd_int32(const rvd_avx512_int32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs1 = mipp_avx512_cast_float32_int32(rsf);
    rs1.m = _mm512_add_epi32(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs2 = mipp_avx512_cast_float32_int32(rsf);
    rs2.m = _mm512_add_epi32(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs3 = mipp_avx512_cast_float32_int32(rsf);
    rs3.m = _mm512_add_epi32(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs4 = mipp_avx512_cast_float32_int32(rsf);
    rs4.m = _mm512_add_epi32(rs3.m, rs4.m);
    return rs4;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_hadd_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_adds_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_adds_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_adds_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_adds_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_adds_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_hadd_int8(const rvd_avx512_int8_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs1 = mipp_avx512_cast_float32_int8(rsf);
    rs1.m = _mm512_adds_epi8(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int8_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs2 = mipp_avx512_cast_float32_int8(rsf);
    rs2.m = _mm512_adds_epi8(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int8_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int8_t rs3 = mipp_avx512_cast_float32_int8(rsf);
    rs3.m = _mm512_adds_epi8(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int8_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    rvd_avx512_int8_t rs4 = mipp_avx512_cast_float32_int8(rsf);
    rs4.m = _mm512_adds_epi8(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int8_float32(rs4);
    __m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                      45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                      29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                      13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int8_t rs5 = mipp_avx512_cast_int8_int8(rsi);
    rs5.m = _mm512_adds_epi8(rs4.m, rs5.m);
    __m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
                                      46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
                                      30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
                                      14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_8));
    rvd_avx512_int8_t rs6 = mipp_avx512_cast_int8_int8(rsi);
    rs6.m = _mm512_adds_epi8(rs5.m, rs6.m);
    return rs6;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmul
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_hmul_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_mul_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_mul_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_mul_pd(rs2.m, rs3.m);
    return rs3;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmul
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_hmul_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_mul_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_mul_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_mul_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_mul_ps(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmul
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_hmul_int32(const rvd_avx512_int32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs1 = mipp_avx512_cast_float32_int32(rsf);
    rs1.m = _mm512_mul_epi32(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs2 = mipp_avx512_cast_float32_int32(rsf);
    rs2.m = _mm512_mul_epi32(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs3 = mipp_avx512_cast_float32_int32(rsf);
    rs3.m = _mm512_mul_epi32(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs4 = mipp_avx512_cast_float32_int32(rsf);
    rs4.m = _mm512_mul_epi32(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmul
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_hmul_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_mullo_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_mullo_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_mullo_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_mullo_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_mullo_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_hmin_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_min_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_min_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_min_pd(rs2.m, rs3.m);
    return rs3;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_hmin_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_min_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_min_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_min_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_min_ps(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float64_t mipp_avx512_hmin_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_gmin_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_gmin_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_gmin_pd(rs2.m, rs3.m);
    return rs3;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float32_t mipp_avx512_hmin_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_gmin_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_gmin_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_gmin_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_gmin_ps(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_hmin_int32(const rvd_avx512_int32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs1 = mipp_avx512_cast_float32_int32(rsf);
    rs1.m = _mm512_min_epi32(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs2 = mipp_avx512_cast_float32_int32(rsf);
    rs2.m = _mm512_min_epi32(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs3 = mipp_avx512_cast_float32_int32(rsf);
    rs3.m = _mm512_min_epi32(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs4 = mipp_avx512_cast_float32_int32(rsf);
    rs4.m = _mm512_min_epi32(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_hmin_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_min_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_min_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_min_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_min_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_min_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_hmin_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_min_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_min_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_min_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_min_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_min_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmin
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_hmin_int8(const rvd_avx512_int8_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs1 = mipp_avx512_cast_float32_int8(rsf);
    rs1.m = _mm512_min_epi8(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int8_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs2 = mipp_avx512_cast_float32_int8(rsf);
    rs2.m = _mm512_min_epi8(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int8_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int8_t rs3 = mipp_avx512_cast_float32_int8(rsf);
    rs3.m = _mm512_min_epi8(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int8_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    rvd_avx512_int8_t rs4 = mipp_avx512_cast_float32_int8(rsf);
    rs4.m = _mm512_min_epi8(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int8_float32(rs4);
    __m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                      45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                      29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                      13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int8_t rs5 = mipp_avx512_cast_int8_int8(rsi);
    rs5.m = _mm512_min_epi8(rs4.m, rs5.m);
    __m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
                                      46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
                                      30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
                                      14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_8));
    rvd_avx512_int8_t rs6 = mipp_avx512_cast_int8_int8(rsi);
    rs6.m = _mm512_min_epi8(rs5.m, rs6.m);
    return rs6;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512F__)
rvd_avx512_float64_t mipp_avx512_hmax_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_max_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_max_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_max_pd(rs2.m, rs3.m);
    return rs3;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512F__)
rvd_avx512_float32_t mipp_avx512_hmax_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_max_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_max_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_max_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_max_ps(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float64_t mipp_avx512_hmax_float64(const rvd_avx512_float64_t r0) {
 rvd_avx512_float32_t rsf; 
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs1 = mipp_avx512_cast_float32_float64(rsf);
    rs1.m = _mm512_gmax_pd(r0.m, rs1.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(mipp_avx512_cast_float64_float32(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), mipp_avx512_cast_float64_float32(r0.m)));
    rvd_avx512_float64_t rs2 = mipp_avx512_cast_float32_float64(rsf);
    rs2.m = _mm512_gmax_pd(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float64_float32(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float64_t rs3 = mipp_avx512_cast_float32_float64(rsf);
    rs3.m = _mm512_gmax_pd(rs2.m, rs3.m);
    return rs3;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__MIC__) || defined(__KNCNI__)
rvd_avx512_float32_t mipp_avx512_hmax_float32(const rvd_avx512_float32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs1 = mipp_avx512_cast_float32_float32(rsf);
    rs1.m = _mm512_gmax_ps(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_float32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_float32_float32(r0.m));
    rvd_avx512_float32_t rs2 = mipp_avx512_cast_float32_float32(rsf);
    rs2.m = _mm512_gmax_ps(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_float32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs3 = mipp_avx512_cast_float32_float32(rsf);
    rs3.m = _mm512_gmax_ps(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_float32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_float32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_float32_t rs4 = mipp_avx512_cast_float32_float32(rsf);
    rs4.m = _mm512_gmax_ps(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512F__)
rvd_avx512_int32_t mipp_avx512_hmax_int32(const rvd_avx512_int32_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs1 = mipp_avx512_cast_float32_int32(rsf);
    rs1.m = _mm512_max_epi32(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int32_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int32_float32(r0.m));
    rvd_avx512_int32_t rs2 = mipp_avx512_cast_float32_int32(rsf);
    rs2.m = _mm512_max_epi32(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int32_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs3 = mipp_avx512_cast_float32_int32(rsf);
    rs3.m = _mm512_max_epi32(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int32_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int32_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))); 
    rvd_avx512_int32_t rs4 = mipp_avx512_cast_float32_int32(rsf);
    rs4.m = _mm512_max_epi32(rs3.m, rs4.m);
    return rs4;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512F__)
rvd_avx512_int16_t mipp_avx512_hmax_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_max_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_max_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_max_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_max_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_max_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512BW__)
rvd_avx512_int16_t mipp_avx512_hmax_int16(const rvd_avx512_int16_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs1 = mipp_avx512_cast_float32_int16(rsf);
    rs1.m = _mm512_max_epi16(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int16_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int16_float32(r0.m));
    rvd_avx512_int16_t rs2 = mipp_avx512_cast_float32_int16(rsf);
    rs2.m = _mm512_max_epi16(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int16_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rs3.m = _mm512_max_epi16(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int16_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int16_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int16_t rs4 = mipp_avx512_cast_float32_int16(rsf);
    rs4.m = _mm512_max_epi16(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int16_float32(rs4);
    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                       45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                       29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                       13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int16_t rs5 = mipp_avx512_cast_int8_int16(rsi);
    rs5.m = _mm512_max_epi16(rs4.m, rs5.m);
    return rs5;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- hmax
#if defined(__AVX512BW__)
rvd_avx512_int8_t mipp_avx512_hmax_int8(const rvd_avx512_int8_t r0) {
 rvd_avx512_float32_t rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs1 = mipp_avx512_cast_float32_int8(rsf);
    rs1.m = _mm512_max_epi8(r0.m, rs1.m);   
    rsf = mipp_avx512_cast_int8_float32(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),mipp_avx512_cast_int8_float32(r0.m));
    rvd_avx512_int8_t rs2 = mipp_avx512_cast_float32_int8(rsf);
    rs2.m = _mm512_max_epi8(rs1.m, rs2.m);
    rsf = mipp_avx512_cast_int8_float32(rs2);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    rvd_avx512_int8_t rs3 = mipp_avx512_cast_float32_int8(rsf);
    rs3.m = _mm512_max_epi8(rs2.m, rs3.m);
    rsf = mipp_avx512_cast_int8_float32(rs3);
    rsf.m = _mm512_shuffle_epi32(mipp_avx512_cast_int8_float32(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    rvd_avx512_int8_t rs4 = mipp_avx512_cast_float32_int8(rsf);
    rs4.m = _mm512_max_epi8(rs3.m, rs4.m);
    rsf = mipp_avx512_cast_int8_float32(rs4);
    __m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                      45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                      29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                      13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
    rsi.m = _mm512_shuffle_epi8(rsi.m, mask_16);
    rvd_avx512_int8_t rs5 = mipp_avx512_cast_int8_int8(rsi);
    rs5.m = _mm512_max_epi8(rs4.m, rs5.m);
    __m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
                                      46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
                                      30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
                                      14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_8));
    rvd_avx512_int8_t rs6 = mipp_avx512_cast_int8_int8(rsi);
    rs6.m = _mm512_max_epi8(rs5.m, rs6.m);
    return rs6;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
#if defined(__AVX512F__)
rvm_avx512_float64_t mipp_avx512_set_float64() {
	mipp_avx512_cast_k_float64_float64(_mm512_set_pd(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]));
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
#if defined(__AVX512F__)
rvm_avx512_float32_t mipp_avx512_set_float32() {
	_mm512_set_ps(vals[15], vals[14], vals[13], vals[12],vals[11], vals[10], vals[ 9], vals[ 8],
	                     vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
#if defined(__AVX512F__)
rvm_avx512_int32_t mipp_avx512_set_int32() {
 rcast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi32(vals[15], vals[14], vals[13], vals[12], vals[11], vals[10], vals[ 9], vals[ 8],                                            					
																	 vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0])));
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
#if defined(__AVX512F__)
rvm_avx512_int64_t mipp_avx512_set_int64() {
	mipp_avx512_cast_k_float64_int64(_mm512_set_epi64((vals[15], vals[14], vals[13], vals[12],
	                     					  	  vals[11], vals[10], vals[ 9], vals[ 8],
	                     					  	  vals[ 7], vals[ 6], vals[ 5], vals[ 4],
	                     					 	  vals[ 3], vals[ 2], vals[ 1], vals[ 0])));
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
#if defined(__AVX512BW__) && (( ( ( defined(__AVX512F__) ) ) ))
rvd_avx512_int32_t mipp_avx512_set_k_int32(const int32_t v0) {
	int32_t t[MIPP_AVX512_N_INT32] = {vals[ 0] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[ 1] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[ 2] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[ 3] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[ 4] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[ 5] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[ 6] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[ 7] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[ 8] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[ 9] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[10] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[11] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[12] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[13] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[14] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[15] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[16] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[17] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[18] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[19] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[20] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[21] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[22] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[23] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[24] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[25] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[26] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[27] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[28] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[29] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0,
		                  vals[30] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0, vals[31] ? (mipp_avx512_cast_int32_int32)0xFFFF : (mipp_avx512_cast_int32_int32)0};
    rvd_avx512_int32_t r0_32 = mipp_avx512_set_int32((mipp_avx512_cast_int32_int32)*t);
    rvd_avx512_int32_t r1_32 = mipp_avx512_set1_int32(0xFFFF);
	rvd_avx512_int32_t msk   = mipp_avx512_cmpneq_int32(r0_32, r1_32);
    rvm_avx512_int32_t res   = mipp_avx512_tomsk_int32(msk);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
#if defined(__AVX512BW__) && (( ( ( defined(__AVX512F__) ) ) ))
rvd_avx512_int64_t mipp_avx512_set_k_int64(const int64_t v0) {
 int64_t t[MIPP_AVX512_N_INT64] = { vals[ 0] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 1] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 2] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 3] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[ 4] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 5] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 6] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 7] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[ 8] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[ 9] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[10] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[11] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[12] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[13] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[14] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[15] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[16] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[17] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[18] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[19] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[20] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[21] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[22] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[23] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[24] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[25] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[26] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[27] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[28] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[29] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[30] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[31] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[32] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[33] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[34] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[35] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[36] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[37] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[38] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[39] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[40] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[41] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[42] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[43] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0,
                            vals[44] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[45] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[46] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0, vals[47] ? (mipp_avx512_cast_int64_int64)0xFF : (mipp_avx512_cast_int64_int64)0};
    rvd_avx512_int64_t r0_32 = mipp_avx512_set_int64((mipp_avx512_cast_int64_int64)*t);
    rvd_avx512_int64_t r1_32 = mipp_avx512_set1_int64(0xFF);
	rvd_avx512_int64_t msk   = mipp_avx512_cmpneq_int64(r0_32, r1_32);
    rvm_avx512_int64_t res   = mipp_avx512_tomsk_int64(msk);
	return res; 
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
#if ( ( ( defined(__AVX512BW__) ) ) )
rvm_avx512_int8_t mipp_avx512_set1_k_int8() {
 rvd_avx512_int8_t r0_32 = mipp_avx512_set1_int8(r0 ? (mipp_avx512_cast_int8_int8)0xFFFFFFFFFFFFFFFF : 0);
    rvd_avx512_int8_t r1_32 = mipp_avx512_set1_int8( (mipp_avx512_cast_int8_int8)0xFFFFFFFFFFFFFFFF    );
	rvd_avx512_int8_t msk   = mipp_avx512_cmpneq_int8(r0_32, r1_32)
    rvm_avx512_int8_t res   = mipp_avx512_tomsk_int8(msk);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
#if ( ( ( defined(__AVX512BW__) ) ) )
rvm_avx512_int16_t mipp_avx512_set1_k_int16() {
 rvd_avx512_int16_t r0_32 = mipp_avx512_set1_int16(r0 ? 0xFFFFFFFF : 0);
    rvd_avx512_int16_t r1_32 = mipp_avx512_set1_int16(  0xFFFFFFFF    );
	rvd_avx512_int16_t msk   = mipp_avx512_cmpneq_int16(r0_32, r1_32);
    rvm_avx512_int16_t res   = mipp_avx512_tomsk_int16(msk);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
rvm_avx512_int32_t mipp_avx512_set1_k_int32() {
 rvd_avx512_int32_t r0_32 = mipp_avx512_set1_int32(r0 ? 0xFFFF : 0);
    rvd_avx512_int32_t r1_32 = mipp_avx512_set1_int32( 0xFFFF    );
	rvd_avx512_int32_t msk   = mipp_avx512_cmpneq_int32(r0_32, r1_32);
    rvm_avx512_int32_t res   = mipp_avx512_tomsk_int32(msk);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
rvm_avx512_int64_t mipp_avx512_set1_k_int64() {
 rvd_avx512_int64_t r0_32 = mipp_avx512_set1_int64(r0 ? 0xFF : 0);
    rvd_avx512_int64_t r1_32 = mipp_avx512_set1_int64( 0xFF    );
	rvd_avx512_int64_t msk   = mipp_avx512_cmpneq_int64(r0_32, r1_32);
    rvm_avx512_int64_t res   = mipp_avx512_tomsk_int64(msk);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_mk
#if defined(__MIC__) || (__KNCNI__)
rvm_avx512_float64_t mipp_avx512_set0_mk_float64() {
 return mipp_avx512_set1_float64_float64(0.0); 
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_mk
#if defined(__MIC__) || (__KNCNI__)
rvm_avx512_float32_t mipp_avx512_set0_mk_float32() {
 return mipp_avx512_set1_float32_float32(0.f); 
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_mk
#if defined(__MIC__) || (__KNCNI__)
rvm_avx512_int32_t mipp_avx512_set0_mk_int32() {
 return mipp_avx512_set1_int32_int32(0); 
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_int64_t mipp_avx512_set0_k_int64() {
 rvm_avx512_int64_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_int32_t mipp_avx512_set0_k_int32() {
 rvm_avx512_int32_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_int16_t mipp_avx512_set0_k_int16() {
 rvm_avx512_int16_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_int8_t mipp_avx512_set0_k_int8() {
 rvm_avx512_int8_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_uint64_t mipp_avx512_set0_k_uint64() {
 rvm_avx512_int64_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_uint32_t mipp_avx512_set0_k_uint32() {
 rvm_avx512_int32_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_uint16_t mipp_avx512_set0_k_uint16() {
 rvm_avx512_int16_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
rvm_avx512_uint8_t mipp_avx512_set0_k_uint8() {
 rvm_avx512_int8_t m  = 0;
	return _mm512_kxor(m, m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__AVX512BW__)
rvm_avx512_float64_t mipp_avx512_andb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
 return (m0.m & m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__AVX512BW__)
rvm_avx512_float32_t mipp_avx512_andb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
 return (m0.m & m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__AVX512BW__)
rvm_avx512_float64_t mipp_avx512_andnb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
 return ((~m0.m) & m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__AVX512BW__)
rvm_avx512_float32_t mipp_avx512_andnb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
 return ((~m0.m) & m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__AVX512BW__)
rvm_avx512_float64_t mipp_avx512_xorb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
 return (m0.m ^ m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__AVX512BW__)
rvm_avx512_float32_t mipp_avx512_xorb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
 return (m0.m ^ m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__AVX512BW__)
rvm_avx512_float64_t mipp_avx512_orb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
 return (m0.m | m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__AVX512BW__)
rvm_avx512_float32_t mipp_avx512_orb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
 return (m0.m | m1.m);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_float64_t mipp_avx512_msb_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t rm = mipp_avx512_cast_int64_float64(mipp_avx512_set1_int64(0x8000000000000000));
	return mipp_avx512_andb_float64(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_int64_t mipp_avx512_msb_int64(const rvd_avx512_int64_t r0) {
	rvd_avx512_int64_t rm = mipp_avx512_cast_int64_int64(mipp_avx512_set1_int64(0x8000000000000000));
	return mipp_avx512_andb_int64(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_uint64_t mipp_avx512_msb_uint64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_uint64_t rm = mipp_avx512_cast_int64_uint64(mipp_avx512_set1_int64(0x8000000000000000));
	return mipp_avx512_andb_uint64(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_float32_t mipp_avx512_msb_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t rm = mipp_avx512_cast_int32_float32(mipp_avx512_set1_int32(0x80000000));
	return mipp_avx512_andb_float32(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_int32_t mipp_avx512_msb_int32(const rvd_avx512_int32_t r0) {
	rvd_avx512_int32_t rm = mipp_avx512_cast_int32_int32(mipp_avx512_set1_int32(0x80000000));
	return mipp_avx512_andb_int32(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_uint32_t mipp_avx512_msb_uint32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_uint32_t rm = mipp_avx512_cast_int32_uint32(mipp_avx512_set1_int32(0x80000000));
	return mipp_avx512_andb_uint32(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_int16_t mipp_avx512_msb_int16(const rvd_avx512_int16_t r0) {
	rvd_avx512_int16_t rm = mipp_avx512_cast_int16_int16(mipp_avx512_set1_int16(0x8000));
	return mipp_avx512_andb_int16(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_uint16_t mipp_avx512_msb_uint16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_uint16_t rm = mipp_avx512_cast_int16_uint16(mipp_avx512_set1_int16(0x8000));
	return mipp_avx512_andb_uint16(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_int8_t mipp_avx512_msb_int8(const rvd_avx512_int8_t r0) {
	rvd_avx512_int8_t rm = mipp_avx512_cast_int8_int8(mipp_avx512_set1_int8(0x80));
	return mipp_avx512_andb_int8(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- msb
rvd_avx512_uint8_t mipp_avx512_msb_uint8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_uint8_t rm = mipp_avx512_cast_int8_uint8(mipp_avx512_set1_int8(0x80));
	return mipp_avx512_andb_uint8(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_float64_t mipp_avx512_notb_float64(const rvd_avx512_float64_t r0) {
	rvd_avx512_float64_t rm = mipp_avx512_cast_int64_float64(mipp_avx512_set1_int64(0xFFFFFFFFFFFFFFFF));
	return mipp_avx512_andnb_float64(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_int64_t mipp_avx512_notb_int64(const rvd_avx512_int64_t r0) {
	rvd_avx512_int64_t rm = mipp_avx512_cast_int64_int64(mipp_avx512_set1_int64(0xFFFFFFFFFFFFFFFF));
	return mipp_avx512_andnb_int64(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_float32_t mipp_avx512_notb_float32(const rvd_avx512_float32_t r0) {
	rvd_avx512_float32_t rm = mipp_avx512_cast_int32_float32(mipp_avx512_set1_int32(0xFFFFFFFF));
	return mipp_avx512_andnb_float32(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_int32_t mipp_avx512_notb_int32(const rvd_avx512_int32_t r0) {
	rvd_avx512_int32_t rm = mipp_avx512_cast_int32_int32(mipp_avx512_set1_int32(0xFFFFFFFF));
	return mipp_avx512_andnb_int32(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_int16_t mipp_avx512_notb_int16(const rvd_avx512_int16_t r0) {
	rvd_avx512_int16_t rm = mipp_avx512_cast_int16_int16(mipp_avx512_set1_int16(0xFFFF));
	return mipp_avx512_andnb_int16(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb
rvd_avx512_int8_t mipp_avx512_notb_int8(const rvd_avx512_int8_t r0) {
	rvd_avx512_int8_t rm = mipp_avx512_cast_int8_int8(mipp_avx512_set1_int8(0xFF));
	return mipp_avx512_andnb_int8(r0, rm);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_float64_t mipp_avx512_notb_k_float64(const rvm_avx512_float64_t m0) {
	return ~(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_int64_t mipp_avx512_notb_k_int64(const rvm_avx512_int64_t m0) {
	return ~(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_float32_t mipp_avx512_notb_k_float32(const rvm_avx512_float32_t m0) {
	return ~(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_int32_t mipp_avx512_notb_k_int32(const rvm_avx512_int32_t m0) {
	return ~(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_int16_t mipp_avx512_notb_k_int16(const rvm_avx512_int16_t m0) {
	return _mm512_knot(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
rvm_avx512_int8_t mipp_avx512_notb_k_int8(const rvm_avx512_int8_t m0) {
	return _mm512_knot(m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_int32(const rvd_avx512_int32_t r0) {
	rvd_avx512_int32_t r32 = mipp_avx512_set0_int32();
	rvm_avx512_int32_t msk = mipp_avx512_cmpneq_int32(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int16());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_uint32(const rvd_avx512_uint32_t r0) {
	rvd_avx512_int32_t r32 = mipp_avx512_set0_int32();
	rvm_avx512_int32_t msk = mipp_avx512_cmpneq_int32(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int16());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_int64(const rvd_avx512_int64_t r0) {
	rvd_avx512_int64_t r32 = mipp_avx512_set0_int64();
	rvm_avx512_int64_t msk = mipp_avx512_cmpneq_int64(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int8());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_uint64(const rvd_avx512_uint64_t r0) {
	rvd_avx512_int64_t r32 = mipp_avx512_set0_int64();
	rvm_avx512_int64_t msk = mipp_avx512_cmpneq_int64(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int8());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_int16(const rvd_avx512_int16_t r0) {
	rvd_avx512_int16_t r32 = mipp_avx512_set0_int16();
	rvm_avx512_int16_t msk = mipp_avx512_cmpneq_int16(r0, r32);				
	return mipp_avx512_cast_uint64_int16(msk == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_uint16(const rvd_avx512_uint16_t r0) {
	rvd_avx512_int16_t r32 = mipp_avx512_set0_int16();
	rvm_avx512_int16_t msk = mipp_avx512_cmpneq_int16(r0, r32);				
	return mipp_avx512_cast_uint64_uint16(msk == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_int8(const rvd_avx512_int8_t r0) {
	rvd_avx512_int8_t r32 = mipp_avx512_set0_int8();
	rvm_avx512_int8_t msk = mipp_avx512_cmpneq_int8(r0, r32)	;				
	return mipp_avx512_cast_uint64_int8(msk == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_uint8(const rvd_avx512_uint8_t r0) {
	rvd_avx512_int8_t r32 = mipp_avx512_set0_int8();
	rvm_avx512_int8_t msk = mipp_avx512_cmpneq_int8(r0, r32)	;				
	return mipp_avx512_cast_uint64_uint8(msk == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_2_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	rvd_avx512_int32_t r0_32 = mipp_avx512_andb_int32(r0, r1);
	rvd_avx512_int32_t r1_32 = mipp_avx512_set0_int32();
	rvm_avx512_int32_t msk   = mipp_avx512_cmpneq_int32(r0_32, r1_32);
	return _mm512_kortestz(m32, mipp_avx512_set0_int16());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_2_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	rvd_avx512_int32_t r0_32 = mipp_avx512_andb_int32(r0, r1);
	rvd_avx512_int32_t r1_32 = mipp_avx512_set0_int32();
	rvm_avx512_int32_t msk   = mipp_avx512_cmpneq_int32(r0_32, r1_32);
	return _mm512_kortestz(m32, mipp_avx512_set0_int16());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_2_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	rvd_avx512_int64_t r32 = mipp_avx512_set0_int64();
	rvm_avx512_int64_t msk = mipp_avx512_cmpneq_int64(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int8());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
int32_t mipp_avx512_testz_2_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	rvd_avx512_int64_t r32 = mipp_avx512_set0_int64();
	rvm_avx512_int64_t msk = mipp_avx512_cmpneq_int64(r0, r32);		
	return _mm512_kortestz(msk,mipp_avx512_set0_int8());
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_2_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	rvd_avx512_int16_t r0_32 = mipp_avx512_andb_int16(r0, r1);
	rvd_avx512_int16_t r1_32 = mipp_avx512_set0_int16();
	rvm_avx512_int16_t msk   = mipp_avx512_cmpneq_int16(r0_32, r1_32);
	return mipp_avx512_cast_uint16_int16(m32 == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_2_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	rvd_avx512_int8_t r0_32 = mipp_avx512_andb_int8(r0, r1);
	rvd_avx512_int8_t r1_32 = mipp_avx512_set0_int8();
	rvm_avx512_int8_t msk   = mipp_avx512_cmpneq_int8(r0_32, r1_32);
	return mipp_avx512_cast_uint8_int8(m32 == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_2_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	rvd_avx512_int16_t r0_32 = mipp_avx512_andb_int16(r0, r1);
	rvd_avx512_int16_t r1_32 = mipp_avx512_set0_int16();
	rvm_avx512_int16_t msk   = mipp_avx512_cmpneq_int16(r0_32, r1_32);
	return mipp_avx512_cast_uint16_uint16(m32 == 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz_2
#if defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) ))
int32_t mipp_avx512_testz_2_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	rvd_avx512_int8_t r0_32 = mipp_avx512_andb_int8(r0, r1);
	rvd_avx512_int8_t r1_32 = mipp_avx512_set0_int8();
	rvm_avx512_int8_t msk   = mipp_avx512_cmpneq_int8(r0_32, r1_32);
	return mipp_avx512_cast_uint8_uint8(m32 == 0);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_float64_t mipp_avx512_load_float64(const float64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_float32_t mipp_avx512_load_float32(const float32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_int64_t mipp_avx512_load_int64(const int64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_int32_t mipp_avx512_load_int32(const int32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_int16_t mipp_avx512_load_int16(const int16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_int8_t mipp_avx512_load_int8(const int8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_int8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_uint64_t mipp_avx512_load_uint64(const uint64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_uint64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_uint32_t mipp_avx512_load_uint32(const uint32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_uint32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_uint16_t mipp_avx512_load_uint16(const uint16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_uint16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
rvd_avx512_uint8_t mipp_avx512_load_uint8(const uint8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_load_uint8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_float64(float64_t* p0, const rvd_avx512_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_float32(float32_t* p0, const rvd_avx512_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_int64(int64_t* p0, const rvd_avx512_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_int32(int32_t* p0, const rvd_avx512_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_int16(int16_t* p0, const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_int8(int8_t* p0, const rvd_avx512_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_int8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_uint64(uint64_t* p0, const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_uint64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_uint32(uint32_t* p0, const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_uint32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_uint16(uint16_t* p0, const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_uint16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
void mipp_avx512_store_uint8(uint8_t* p0, const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_store_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvm_avx512_float64_t mipp_avx512_set_float64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvm_avx512_float32_t mipp_avx512_set_float32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_float32");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvm_avx512_int64_t mipp_avx512_set_int64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvm_avx512_int32_t mipp_avx512_set_int32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_int32");
	exit(-1);
}
#endif
rvm_avx512_int16_t mipp_avx512_set_int16() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_int16");
	exit(-1);
}
rvm_avx512_int8_t mipp_avx512_set_int8() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_int8");
	exit(-1);
}
rvm_avx512_uint64_t mipp_avx512_set_uint64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_set_uint32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_set_uint16() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_set_uint8() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) && (( ( ( defined(__AVX512F__) ) ) )) && (( ( ( defined(__AVX512F__) ) ) )) )
rvd_avx512_int64_t mipp_avx512_set_k_int64(const int64_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_k_int64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) && (( ( ( defined(__AVX512F__) ) ) )) && (( ( ( defined(__AVX512F__) ) ) )) )
rvd_avx512_int32_t mipp_avx512_set_k_int32(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_k_int32");
	exit(-1);
}
#endif
rvd_avx512_int16_t mipp_avx512_set_k_int16(const int16_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_k_int16");
	exit(-1);
}
rvd_avx512_int8_t mipp_avx512_set_k_int8(const int8_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set_k_int8");
	exit(-1);
}
rvm_avx512_float64_t mipp_avx512_set1_k_float64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_float64");
	exit(-1);
}
rvm_avx512_float32_t mipp_avx512_set1_k_float32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_float32");
	exit(-1);
}
#if !( ( ( ( defined(__AVX512BW__) ) ) ) && (( ( ( defined(__AVX512BW__) ) ) )) )
rvm_avx512_int16_t mipp_avx512_set1_k_int16() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_int16");
	exit(-1);
}
#endif
#if !( ( ( ( defined(__AVX512BW__) ) ) ) && (( ( ( defined(__AVX512BW__) ) ) )) )
rvm_avx512_int8_t mipp_avx512_set1_k_int8() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_set1_k_uint64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_set1_k_uint32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_set1_k_uint16() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_set1_k_uint8() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set1_k_uint8");
	exit(-1);
}
rvm_avx512_float64_t mipp_avx512_set0_k_float64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set0_k_float64");
	exit(-1);
}
rvm_avx512_float32_t mipp_avx512_set0_k_float32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set0_k_float32");
	exit(-1);
}
#if !( defined(__MIC__) || (__KNCNI__) )
rvm_avx512_float64_t mipp_avx512_set0_mk_float64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set0_mk_float64");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || (__KNCNI__) )
rvm_avx512_float32_t mipp_avx512_set0_mk_float32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set0_mk_float32");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || (__KNCNI__) )
rvm_avx512_int32_t mipp_avx512_set0_mk_int32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_set0_mk_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_add_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_add_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_int8");
	exit(-1);
}
#endif
rvd_avx512_uint64_t mipp_avx512_add_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_add_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_uint32");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvd_avx512_uint16_t mipp_avx512_add_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_uint16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_uint8_t mipp_avx512_add_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_add_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_sub_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_sub_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_sub_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_sub_int8");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_mul_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_mul_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_float64_t mipp_avx512_div_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_div_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_float32_t mipp_avx512_div_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_div_float32");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_min_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_min_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_min_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_min_int8");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_max_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_max_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_max_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_max_int8");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) )
rvd_avx512_int32_t mipp_avx512_fmadd_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1, const rvd_avx512_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_fmadd_int32");
	exit(-1);
}
#endif
rvd_avx512_int32_t mipp_avx512_fmsub_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1, const rvd_avx512_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_fmsub_int32");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_float64_t mipp_avx512_andb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_andb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float32_t mipp_avx512_andb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_andb_k_float32");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float64_t mipp_avx512_andnb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_andnb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float32_t mipp_avx512_andnb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_andnb_k_float32");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float64_t mipp_avx512_orb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float32_t mipp_avx512_orb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_float32");
	exit(-1);
}
#endif
rvm_avx512_int64_t mipp_avx512_orb_k_int64(const rvm_avx512_int64_t m0, const rvm_avx512_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_int64");
	exit(-1);
}
rvm_avx512_int32_t mipp_avx512_orb_k_int32(const rvm_avx512_int32_t m0, const rvm_avx512_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_int32");
	exit(-1);
}
rvm_avx512_int16_t mipp_avx512_orb_k_int16(const rvm_avx512_int16_t m0, const rvm_avx512_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_int16");
	exit(-1);
}
rvm_avx512_int8_t mipp_avx512_orb_k_int8(const rvm_avx512_int8_t m0, const rvm_avx512_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_int8");
	exit(-1);
}
rvm_avx512_uint64_t mipp_avx512_orb_k_uint64(const rvm_avx512_uint64_t m0, const rvm_avx512_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_orb_k_uint32(const rvm_avx512_uint32_t m0, const rvm_avx512_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_orb_k_uint16(const rvm_avx512_uint16_t m0, const rvm_avx512_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_orb_k_uint8(const rvm_avx512_uint8_t m0, const rvm_avx512_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_orb_k_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_float64_t mipp_avx512_xorb_k_float64(const rvm_avx512_float64_t m0, const rvm_avx512_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_float32_t mipp_avx512_xorb_k_float32(const rvm_avx512_float32_t m0, const rvm_avx512_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_float32");
	exit(-1);
}
#endif
rvm_avx512_int64_t mipp_avx512_xorb_k_int64(const rvm_avx512_int64_t m0, const rvm_avx512_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_int64");
	exit(-1);
}
rvm_avx512_int32_t mipp_avx512_xorb_k_int32(const rvm_avx512_int32_t m0, const rvm_avx512_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_int32");
	exit(-1);
}
rvm_avx512_int16_t mipp_avx512_xorb_k_int16(const rvm_avx512_int16_t m0, const rvm_avx512_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_int16");
	exit(-1);
}
rvm_avx512_int8_t mipp_avx512_xorb_k_int8(const rvm_avx512_int8_t m0, const rvm_avx512_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_int8");
	exit(-1);
}
rvm_avx512_uint64_t mipp_avx512_xorb_k_uint64(const rvm_avx512_uint64_t m0, const rvm_avx512_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_xorb_k_uint32(const rvm_avx512_uint32_t m0, const rvm_avx512_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_xorb_k_uint16(const rvm_avx512_uint16_t m0, const rvm_avx512_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_xorb_k_uint8(const rvm_avx512_uint8_t m0, const rvm_avx512_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_xorb_k_uint8");
	exit(-1);
}
rvd_avx512_uint64_t mipp_avx512_notb_uint64(const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_notb_uint32(const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_uint32");
	exit(-1);
}
rvd_avx512_uint16_t mipp_avx512_notb_uint16(const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_uint16");
	exit(-1);
}
rvd_avx512_uint8_t mipp_avx512_notb_uint8(const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_uint8");
	exit(-1);
}
rvm_avx512_uint64_t mipp_avx512_notb_k_uint64(const rvm_avx512_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_k_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_notb_k_uint32(const rvm_avx512_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_k_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_notb_k_uint16(const rvm_avx512_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_k_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_notb_k_uint8(const rvm_avx512_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_notb_k_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmpeq_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmpeq_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmpeq_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmpeq_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmpeq_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmpeq_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpeq_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmpneq_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmpneq_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmpneq_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmpneq_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmpneq_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmpneq_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpneq_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmplt_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmplt_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmplt_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmplt_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmplt_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmplt_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmplt_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmple_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmple_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmple_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmple_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmple_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmple_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmple_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmpge_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmpge_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmpge_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmpge_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmpge_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmpge_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpge_uint8");
	exit(-1);
}
#if !( defined(__AVX512BW__) )
rvm_avx512_int16_t mipp_avx512_cmpgt_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvm_avx512_int8_t mipp_avx512_cmpgt_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_int8");
	exit(-1);
}
#endif
rvm_avx512_uint64_t mipp_avx512_cmpgt_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_uint64");
	exit(-1);
}
rvm_avx512_uint32_t mipp_avx512_cmpgt_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_uint32");
	exit(-1);
}
rvm_avx512_uint16_t mipp_avx512_cmpgt_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_uint16");
	exit(-1);
}
rvm_avx512_uint8_t mipp_avx512_cmpgt_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_cmpgt_uint8");
	exit(-1);
}
#if !( defined(__MIC__) || defined(__KNCNI__) )
float64_t mipp_avx512_round_float64(const rvd_avx512_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_round_float64");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) )
float32_t mipp_avx512_round_float32(const rvd_avx512_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_round_float32");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__) )
rvd_avx512_float64_t mipp_avx512_blend_float64(const rvd_avx512_float64_t r0, const rvd_avx512_float64_t r1, const rvm_avx512_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_float64");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__) )
rvd_avx512_float32_t mipp_avx512_blend_float32(const rvd_avx512_float32_t r0, const rvd_avx512_float32_t r1, const rvm_avx512_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_float32");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__) )
rvd_avx512_int64_t mipp_avx512_blend_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1, const rvm_avx512_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_int64");
	exit(-1);
}
#endif
#if !( defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__) )
rvd_avx512_int32_t mipp_avx512_blend_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1, const rvm_avx512_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_blend_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1, const rvm_avx512_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_blend_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1, const rvm_avx512_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_int8");
	exit(-1);
}
#endif
rvd_avx512_uint64_t mipp_avx512_blend_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1, const rvm_avx512_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_blend_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1, const rvm_avx512_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_uint32");
	exit(-1);
}
rvd_avx512_uint16_t mipp_avx512_blend_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1, const rvm_avx512_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_uint16");
	exit(-1);
}
rvd_avx512_uint8_t mipp_avx512_blend_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1, const rvm_avx512_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_blend_uint8");
	exit(-1);
}
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_int64(const rvd_avx512_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_int64");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_int32(const rvd_avx512_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_int32");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_int16(const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_int16");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_int8(const rvd_avx512_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_int8");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_uint64(const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_uint64");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_uint32(const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_uint32");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_uint16(const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_uint16");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_uint8(const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_uint8");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_2_int64(const rvd_avx512_int64_t r0, const rvd_avx512_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_int64");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_2_int32(const rvd_avx512_int32_t r0, const rvd_avx512_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_int32");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_2_int16(const rvd_avx512_int16_t r0, const rvd_avx512_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_int16");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_2_int8(const rvd_avx512_int8_t r0, const rvd_avx512_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_int8");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_2_uint64(const rvd_avx512_uint64_t r0, const rvd_avx512_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_uint64");
	exit(-1);
}
#endif
#if !( defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__) )
int32_t mipp_avx512_testz_2_uint32(const rvd_avx512_uint32_t r0, const rvd_avx512_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_uint32");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_2_uint16(const rvd_avx512_uint16_t r0, const rvd_avx512_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_uint16");
	exit(-1);
}
#endif
#if !( defined (__AVX512BW__) && (( ( ( defined(__AVX512BW__) ) ) )) && (( ( ( defined(__AVX512BW__) ) ) )) )
int32_t mipp_avx512_testz_2_uint8(const rvd_avx512_uint8_t r0, const rvd_avx512_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_testz_2_uint8");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_hadd_int16(const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_hadd_int8(const rvd_avx512_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_int8");
	exit(-1);
}
#endif
rvd_avx512_uint64_t mipp_avx512_hadd_uint64(const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_hadd_uint32(const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_uint32");
	exit(-1);
}
rvd_avx512_uint16_t mipp_avx512_hadd_uint16(const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_uint16");
	exit(-1);
}
rvd_avx512_uint8_t mipp_avx512_hadd_uint8(const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hadd_uint8");
	exit(-1);
}
#if !( defined(__AVX512F__) )
rvd_avx512_float64_t mipp_avx512_hmul_float64(const rvd_avx512_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmul_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvd_avx512_float32_t mipp_avx512_hmul_float32(const rvd_avx512_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmul_float32");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvd_avx512_int32_t mipp_avx512_hmul_int32(const rvd_avx512_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmul_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) )
rvd_avx512_int16_t mipp_avx512_hmul_int16(const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmul_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) ) && !( defined(__MIC__) || defined(__KNCNI__) )
rvd_avx512_float64_t mipp_avx512_hmin_float64(const rvd_avx512_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) ) && !( defined(__MIC__) || defined(__KNCNI__) )
rvd_avx512_float32_t mipp_avx512_hmin_float32(const rvd_avx512_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_float32");
	exit(-1);
}
#endif
rvd_avx512_int64_t mipp_avx512_hmin_int64(const rvd_avx512_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_int64");
	exit(-1);
}
#if !( defined(__AVX512F__) )
rvd_avx512_int32_t mipp_avx512_hmin_int32(const rvd_avx512_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) ) && !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_hmin_int16(const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_hmin_int8(const rvd_avx512_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_int8");
	exit(-1);
}
#endif
rvd_avx512_uint64_t mipp_avx512_hmin_uint64(const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_hmin_uint32(const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_uint32");
	exit(-1);
}
rvd_avx512_uint16_t mipp_avx512_hmin_uint16(const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_uint16");
	exit(-1);
}
rvd_avx512_uint8_t mipp_avx512_hmin_uint8(const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmin_uint8");
	exit(-1);
}
#if !( defined(__AVX512F__) ) && !( defined(__MIC__) || defined(__KNCNI__) )
rvd_avx512_float64_t mipp_avx512_hmax_float64(const rvd_avx512_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_float64");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) ) && !( defined(__MIC__) || defined(__KNCNI__) )
rvd_avx512_float32_t mipp_avx512_hmax_float32(const rvd_avx512_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_float32");
	exit(-1);
}
#endif
rvd_avx512_int64_t mipp_avx512_hmax_int64(const rvd_avx512_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_int64");
	exit(-1);
}
#if !( defined(__AVX512F__) )
rvd_avx512_int32_t mipp_avx512_hmax_int32(const rvd_avx512_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_int32");
	exit(-1);
}
#endif
#if !( defined(__AVX512F__) ) && !( defined(__AVX512BW__) )
rvd_avx512_int16_t mipp_avx512_hmax_int16(const rvd_avx512_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_int16");
	exit(-1);
}
#endif
#if !( defined(__AVX512BW__) )
rvd_avx512_int8_t mipp_avx512_hmax_int8(const rvd_avx512_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_int8");
	exit(-1);
}
#endif
rvd_avx512_uint64_t mipp_avx512_hmax_uint64(const rvd_avx512_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_uint64");
	exit(-1);
}
rvd_avx512_uint32_t mipp_avx512_hmax_uint32(const rvd_avx512_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_uint32");
	exit(-1);
}
rvd_avx512_uint16_t mipp_avx512_hmax_uint16(const rvd_avx512_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_uint16");
	exit(-1);
}
rvd_avx512_uint8_t mipp_avx512_hmax_uint8(const rvd_avx512_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_avx512_hmax_uint8");
	exit(-1);
}
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_ */
