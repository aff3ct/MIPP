#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#include <immintrin.h>
#define MIPP_SSE_RVD_SIZE_BIT 128
#define MIPP_SSE_RVD_SIZE_BYTE 16
#define MIPP_N_FLOAT64 2
#define MIPP_N_FLOAT32 4
#define MIPP_N_INT64 2
#define MIPP_N_INT32 4
#define MIPP_N_INT16 8
#define MIPP_N_INT8 16
#define MIPP_N_UINT64 2
#define MIPP_N_UINT32 4
#define MIPP_N_UINT16 8
#define MIPP_N_UINT8 16
typedef struct { __m128d r; } rvd_sse_float64_t;
typedef struct {  __m128 r; } rvd_sse_float32_t;
typedef struct { __m128i r; } rvd_sse_int64_t;
typedef struct { __m128i r; } rvd_sse_int32_t;
typedef struct { __m128i r; } rvd_sse_int16_t;
typedef struct { __m128i r; } rvd_sse_int8_t;
typedef struct { __m128i r; } rvd_sse_uint64_t;
typedef struct { __m128i r; } rvd_sse_uint32_t;
typedef struct { __m128i r; } rvd_sse_uint16_t;
typedef struct { __m128i r; } rvd_sse_uint8_t;
typedef struct { __m128d m; } rvm_sse_float64_t;
typedef struct { __m128 m; } rvm_sse_float32_t;
typedef struct { __m128i m; } rvm_sse_int64_t;
typedef struct { __m128i m; } rvm_sse_int32_t;
typedef struct { __m128i m; } rvm_sse_int16_t;
typedef struct { __m128i m; } rvm_sse_int8_t;
typedef struct { __m128i m; } rvm_sse_uint64_t;
typedef struct { __m128i m; } rvm_sse_uint32_t;
typedef struct { __m128i m; } rvm_sse_uint16_t;
typedef struct { __m128i m; } rvm_sse_uint8_t;
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_float64_float64(const rvd_sse_float64_t r0) {
	rvd_sse_float64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_float32_float64(const rvd_sse_float32_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castps_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_int64_float64(const rvd_sse_int64_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_int32_float64(const rvd_sse_int32_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_int16_float64(const rvd_sse_int16_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_int8_float64(const rvd_sse_int8_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_uint64_float64(const rvd_sse_uint64_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_uint32_float64(const rvd_sse_uint32_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_uint16_float64(const rvd_sse_uint16_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float64_t mipp_sse_cast_uint8_float64(const rvd_sse_uint8_t r0) {
	rvd_sse_float64_t res;
	res.r= _mm_castsi128_pd(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_float64_float32(const rvd_sse_float64_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castpd_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_float32_float32(const rvd_sse_float32_t r0) {
	rvd_sse_float32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_int64_float32(const rvd_sse_int64_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_int32_float32(const rvd_sse_int32_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_int16_float32(const rvd_sse_int16_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_int8_float32(const rvd_sse_int8_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_uint64_float32(const rvd_sse_uint64_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_uint32_float32(const rvd_sse_uint32_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_uint16_float32(const rvd_sse_uint16_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_float32_t mipp_sse_cast_uint8_float32(const rvd_sse_uint8_t r0) {
	rvd_sse_float32_t res;
	res.r= _mm_castsi128_ps(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_float64_int64(const rvd_sse_float64_t r0) {
	rvd_sse_int64_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_float32_int64(const rvd_sse_float32_t r0) {
	rvd_sse_int64_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_int64_int64(const rvd_sse_int64_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_int32_int64(const rvd_sse_int32_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_int16_int64(const rvd_sse_int16_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_int8_int64(const rvd_sse_int8_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_uint64_int64(const rvd_sse_uint64_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_uint32_int64(const rvd_sse_uint32_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_uint16_int64(const rvd_sse_uint16_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int64_t mipp_sse_cast_uint8_int64(const rvd_sse_uint8_t r0) {
	rvd_sse_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_float64_int32(const rvd_sse_float64_t r0) {
	rvd_sse_int32_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_float32_int32(const rvd_sse_float32_t r0) {
	rvd_sse_int32_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_int64_int32(const rvd_sse_int64_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_int32_int32(const rvd_sse_int32_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_int16_int32(const rvd_sse_int16_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_int8_int32(const rvd_sse_int8_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_uint64_int32(const rvd_sse_uint64_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_uint32_int32(const rvd_sse_uint32_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_uint16_int32(const rvd_sse_uint16_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int32_t mipp_sse_cast_uint8_int32(const rvd_sse_uint8_t r0) {
	rvd_sse_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_float64_int16(const rvd_sse_float64_t r0) {
	rvd_sse_int16_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_float32_int16(const rvd_sse_float32_t r0) {
	rvd_sse_int16_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_int64_int16(const rvd_sse_int64_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_int32_int16(const rvd_sse_int32_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_int16_int16(const rvd_sse_int16_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_int8_int16(const rvd_sse_int8_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_uint64_int16(const rvd_sse_uint64_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_uint32_int16(const rvd_sse_uint32_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_uint16_int16(const rvd_sse_uint16_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int16_t mipp_sse_cast_uint8_int16(const rvd_sse_uint8_t r0) {
	rvd_sse_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_float64_int8(const rvd_sse_float64_t r0) {
	rvd_sse_int8_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_float32_int8(const rvd_sse_float32_t r0) {
	rvd_sse_int8_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_int64_int8(const rvd_sse_int64_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_int32_int8(const rvd_sse_int32_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_int16_int8(const rvd_sse_int16_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_int8_int8(const rvd_sse_int8_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_uint64_int8(const rvd_sse_uint64_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_uint32_int8(const rvd_sse_uint32_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_uint16_int8(const rvd_sse_uint16_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_int8_t mipp_sse_cast_uint8_int8(const rvd_sse_uint8_t r0) {
	rvd_sse_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_float64_uint64(const rvd_sse_float64_t r0) {
	rvd_sse_uint64_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_float32_uint64(const rvd_sse_float32_t r0) {
	rvd_sse_uint64_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_int64_uint64(const rvd_sse_int64_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_int32_uint64(const rvd_sse_int32_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_int16_uint64(const rvd_sse_int16_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_int8_uint64(const rvd_sse_int8_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_uint64_uint64(const rvd_sse_uint64_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_uint32_uint64(const rvd_sse_uint32_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_uint16_uint64(const rvd_sse_uint16_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint64_t mipp_sse_cast_uint8_uint64(const rvd_sse_uint8_t r0) {
	rvd_sse_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_float64_uint32(const rvd_sse_float64_t r0) {
	rvd_sse_uint32_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_float32_uint32(const rvd_sse_float32_t r0) {
	rvd_sse_uint32_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_int64_uint32(const rvd_sse_int64_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_int32_uint32(const rvd_sse_int32_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_int16_uint32(const rvd_sse_int16_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_int8_uint32(const rvd_sse_int8_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_uint64_uint32(const rvd_sse_uint64_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_uint32_uint32(const rvd_sse_uint32_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_uint16_uint32(const rvd_sse_uint16_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint32_t mipp_sse_cast_uint8_uint32(const rvd_sse_uint8_t r0) {
	rvd_sse_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_float64_uint16(const rvd_sse_float64_t r0) {
	rvd_sse_uint16_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_float32_uint16(const rvd_sse_float32_t r0) {
	rvd_sse_uint16_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_int64_uint16(const rvd_sse_int64_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_int32_uint16(const rvd_sse_int32_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_int16_uint16(const rvd_sse_int16_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_int8_uint16(const rvd_sse_int8_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_uint64_uint16(const rvd_sse_uint64_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_uint32_uint16(const rvd_sse_uint32_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_uint16_uint16(const rvd_sse_uint16_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint16_t mipp_sse_cast_uint8_uint16(const rvd_sse_uint8_t r0) {
	rvd_sse_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_float64_uint8(const rvd_sse_float64_t r0) {
	rvd_sse_uint8_t res;
	res.r= _mm_castpd_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_float32_uint8(const rvd_sse_float32_t r0) {
	rvd_sse_uint8_t res;
	res.r= _mm_castps_si128(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_int64_uint8(const rvd_sse_int64_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_int32_uint8(const rvd_sse_int32_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_int16_uint8(const rvd_sse_int16_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_int8_uint8(const rvd_sse_int8_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_uint64_uint8(const rvd_sse_uint64_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_uint32_uint8(const rvd_sse_uint32_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_uint16_uint8(const rvd_sse_uint16_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sse_uint8_t mipp_sse_cast_uint8_uint8(const rvd_sse_uint8_t r0) {
	rvd_sse_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_float64_float64(const rvm_sse_float64_t m0) {
	rvm_sse_float64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_float32_float64(const rvm_sse_float32_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castps_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_int64_float64(const rvm_sse_int64_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_int32_float64(const rvm_sse_int32_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_int16_float64(const rvm_sse_int16_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_int8_float64(const rvm_sse_int8_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_uint64_float64(const rvm_sse_uint64_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_uint32_float64(const rvm_sse_uint32_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_uint16_float64(const rvm_sse_uint16_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float64_t mipp_sse_cast_k_uint8_float64(const rvm_sse_uint8_t m0) {
	rvm_sse_float64_t res;
	res.m= _mm_castsi128_pd(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_float64_float32(const rvm_sse_float64_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castpd_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_float32_float32(const rvm_sse_float32_t m0) {
	rvm_sse_float32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_int64_float32(const rvm_sse_int64_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_int32_float32(const rvm_sse_int32_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_int16_float32(const rvm_sse_int16_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_int8_float32(const rvm_sse_int8_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_uint64_float32(const rvm_sse_uint64_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_uint32_float32(const rvm_sse_uint32_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_uint16_float32(const rvm_sse_uint16_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_float32_t mipp_sse_cast_k_uint8_float32(const rvm_sse_uint8_t m0) {
	rvm_sse_float32_t res;
	res.m= _mm_castsi128_ps(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_float64_int64(const rvm_sse_float64_t m0) {
	rvm_sse_int64_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_float32_int64(const rvm_sse_float32_t m0) {
	rvm_sse_int64_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_int64_int64(const rvm_sse_int64_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_int32_int64(const rvm_sse_int32_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_int16_int64(const rvm_sse_int16_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_int8_int64(const rvm_sse_int8_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_uint64_int64(const rvm_sse_uint64_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_uint32_int64(const rvm_sse_uint32_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_uint16_int64(const rvm_sse_uint16_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int64_t mipp_sse_cast_k_uint8_int64(const rvm_sse_uint8_t m0) {
	rvm_sse_int64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_float64_int32(const rvm_sse_float64_t m0) {
	rvm_sse_int32_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_float32_int32(const rvm_sse_float32_t m0) {
	rvm_sse_int32_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_int64_int32(const rvm_sse_int64_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_int32_int32(const rvm_sse_int32_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_int16_int32(const rvm_sse_int16_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_int8_int32(const rvm_sse_int8_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_uint64_int32(const rvm_sse_uint64_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_uint32_int32(const rvm_sse_uint32_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_uint16_int32(const rvm_sse_uint16_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int32_t mipp_sse_cast_k_uint8_int32(const rvm_sse_uint8_t m0) {
	rvm_sse_int32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_float64_int16(const rvm_sse_float64_t m0) {
	rvm_sse_int16_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_float32_int16(const rvm_sse_float32_t m0) {
	rvm_sse_int16_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_int64_int16(const rvm_sse_int64_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_int32_int16(const rvm_sse_int32_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_int16_int16(const rvm_sse_int16_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_int8_int16(const rvm_sse_int8_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_uint64_int16(const rvm_sse_uint64_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_uint32_int16(const rvm_sse_uint32_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_uint16_int16(const rvm_sse_uint16_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int16_t mipp_sse_cast_k_uint8_int16(const rvm_sse_uint8_t m0) {
	rvm_sse_int16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_float64_int8(const rvm_sse_float64_t m0) {
	rvm_sse_int8_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_float32_int8(const rvm_sse_float32_t m0) {
	rvm_sse_int8_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_int64_int8(const rvm_sse_int64_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_int32_int8(const rvm_sse_int32_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_int16_int8(const rvm_sse_int16_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_int8_int8(const rvm_sse_int8_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_uint64_int8(const rvm_sse_uint64_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_uint32_int8(const rvm_sse_uint32_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_uint16_int8(const rvm_sse_uint16_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_int8_t mipp_sse_cast_k_uint8_int8(const rvm_sse_uint8_t m0) {
	rvm_sse_int8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_float64_uint64(const rvm_sse_float64_t m0) {
	rvm_sse_uint64_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_float32_uint64(const rvm_sse_float32_t m0) {
	rvm_sse_uint64_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_int64_uint64(const rvm_sse_int64_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_int32_uint64(const rvm_sse_int32_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_int16_uint64(const rvm_sse_int16_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_int8_uint64(const rvm_sse_int8_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_uint64_uint64(const rvm_sse_uint64_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_uint32_uint64(const rvm_sse_uint32_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_uint16_uint64(const rvm_sse_uint16_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint64_t mipp_sse_cast_k_uint8_uint64(const rvm_sse_uint8_t m0) {
	rvm_sse_uint64_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_float64_uint32(const rvm_sse_float64_t m0) {
	rvm_sse_uint32_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_float32_uint32(const rvm_sse_float32_t m0) {
	rvm_sse_uint32_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_int64_uint32(const rvm_sse_int64_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_int32_uint32(const rvm_sse_int32_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_int16_uint32(const rvm_sse_int16_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_int8_uint32(const rvm_sse_int8_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_uint64_uint32(const rvm_sse_uint64_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_uint32_uint32(const rvm_sse_uint32_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_uint16_uint32(const rvm_sse_uint16_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint32_t mipp_sse_cast_k_uint8_uint32(const rvm_sse_uint8_t m0) {
	rvm_sse_uint32_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_float64_uint16(const rvm_sse_float64_t m0) {
	rvm_sse_uint16_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_float32_uint16(const rvm_sse_float32_t m0) {
	rvm_sse_uint16_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_int64_uint16(const rvm_sse_int64_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_int32_uint16(const rvm_sse_int32_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_int16_uint16(const rvm_sse_int16_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_int8_uint16(const rvm_sse_int8_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_uint64_uint16(const rvm_sse_uint64_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_uint32_uint16(const rvm_sse_uint32_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_uint16_uint16(const rvm_sse_uint16_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint16_t mipp_sse_cast_k_uint8_uint16(const rvm_sse_uint8_t m0) {
	rvm_sse_uint16_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_float64_uint8(const rvm_sse_float64_t m0) {
	rvm_sse_uint8_t res;
	res.m= _mm_castpd_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_float32_uint8(const rvm_sse_float32_t m0) {
	rvm_sse_uint8_t res;
	res.m= _mm_castps_si128(m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_int64_uint8(const rvm_sse_int64_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_int32_uint8(const rvm_sse_int32_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_int16_uint8(const rvm_sse_int16_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_int8_uint8(const rvm_sse_int8_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_uint64_uint8(const rvm_sse_uint64_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_uint32_uint8(const rvm_sse_uint32_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_uint16_uint8(const rvm_sse_uint16_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sse_uint8_t mipp_sse_cast_k_uint8_uint8(const rvm_sse_uint8_t m0) {
	rvm_sse_uint8_t res;
	res.m= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_float64_t mipp_sse_toreg_float64(const rvm_sse_float64_t m0) {
	rvd_sse_float64_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_float32_t mipp_sse_toreg_float32(const rvm_sse_float32_t m0) {
	rvd_sse_float32_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_int64_t mipp_sse_toreg_int64(const rvm_sse_int64_t m0) {
	rvd_sse_int64_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_int32_t mipp_sse_toreg_int32(const rvm_sse_int32_t m0) {
	rvd_sse_int32_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_int16_t mipp_sse_toreg_int16(const rvm_sse_int16_t m0) {
	rvd_sse_int16_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_int8_t mipp_sse_toreg_int8(const rvm_sse_int8_t m0) {
	rvd_sse_int8_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_uint64_t mipp_sse_toreg_uint64(const rvm_sse_uint64_t m0) {
	rvd_sse_uint64_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_uint32_t mipp_sse_toreg_uint32(const rvm_sse_uint32_t m0) {
	rvd_sse_uint32_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_uint16_t mipp_sse_toreg_uint16(const rvm_sse_uint16_t m0) {
	rvd_sse_uint16_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sse_uint8_t mipp_sse_toreg_uint8(const rvm_sse_uint8_t m0) {
	rvd_sse_uint8_t res;
	res.r= m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_float64_t mipp_sse_tomsk_float64(const rvd_sse_float64_t r0) {
	rvm_sse_float64_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_float32_t mipp_sse_tomsk_float32(const rvd_sse_float32_t r0) {
	rvm_sse_float32_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_int64_t mipp_sse_tomsk_int64(const rvd_sse_int64_t r0) {
	rvm_sse_int64_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_int32_t mipp_sse_tomsk_int32(const rvd_sse_int32_t r0) {
	rvm_sse_int32_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_int16_t mipp_sse_tomsk_int16(const rvd_sse_int16_t r0) {
	rvm_sse_int16_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_int8_t mipp_sse_tomsk_int8(const rvd_sse_int8_t r0) {
	rvm_sse_int8_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_uint64_t mipp_sse_tomsk_uint64(const rvd_sse_uint64_t r0) {
	rvm_sse_uint64_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_uint32_t mipp_sse_tomsk_uint32(const rvd_sse_uint32_t r0) {
	rvm_sse_uint32_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_uint16_t mipp_sse_tomsk_uint16(const rvd_sse_uint16_t r0) {
	rvm_sse_uint16_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- tomsk
static inline rvm_sse_uint8_t mipp_sse_tomsk_uint8(const rvd_sse_uint8_t r0) {
	rvm_sse_uint8_t res;
	res.m= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int64_t mipp_sse_load_int64(const int64_t* p0) {
	rvd_sse_int64_t res;
	res.r= _mm_load_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int32_t mipp_sse_load_int32(const int32_t* p0) {
	rvd_sse_int32_t res;
	res.r= _mm_load_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int16_t mipp_sse_load_int16(const int16_t* p0) {
	rvd_sse_int16_t res;
	res.r= _mm_load_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int8_t mipp_sse_load_int8(const int8_t* p0) {
	rvd_sse_int8_t res;
	res.r= _mm_load_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_float32_t mipp_sse_load_float32(const float32_t* p0) {
	rvd_sse_float32_t res;
	res.r= _mm_load_ps((float32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if defined(MIPP_ALIGNED_LOADS) && defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_load_float64(const float64_t* p0) {
	rvd_sse_float64_t res;
	res.r= _mm_load_pd((float64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_float64_t mipp_sse_load_float64(const float64_t* p0) {
	rvd_sse_float64_t res;
	res.r= _mm_loadu_pd((float64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_float32_t mipp_sse_load_float32(const float32_t* p0) {
	rvd_sse_float32_t res;
	res.r= _mm_loadu_ps((float32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int64_t mipp_sse_load_int64(const int64_t* p0) {
	rvd_sse_int64_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int32_t mipp_sse_load_int32(const int32_t* p0) {
	rvd_sse_int32_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int16_t mipp_sse_load_int16(const int16_t* p0) {
	rvd_sse_int16_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_int8_t mipp_sse_load_int8(const int8_t* p0) {
	rvd_sse_int8_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_uint64_t mipp_sse_load_uint64(const uint64_t* p0) {
	rvd_sse_uint64_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_uint32_t mipp_sse_load_uint32(const uint32_t* p0) {
	rvd_sse_uint32_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_uint16_t mipp_sse_load_uint16(const uint16_t* p0) {
	rvd_sse_uint16_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
#if !defined(MIPP_ALIGNED_LOADS)
static inline rvd_sse_uint8_t mipp_sse_load_uint8(const uint8_t* p0) {
	rvd_sse_uint8_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_float64_t mipp_sse_loadu_float64(const float64_t* p0) {
	rvd_sse_float64_t res;
	res.r= _mm_loadu_pd((float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_float32_t mipp_sse_loadu_float32(const float32_t* p0) {
	rvd_sse_float32_t res;
	res.r= _mm_loadu_ps((float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_int64_t mipp_sse_loadu_int64(const int64_t* p0) {
	rvd_sse_int64_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_int32_t mipp_sse_loadu_int32(const int32_t* p0) {
	rvd_sse_int32_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_int16_t mipp_sse_loadu_int16(const int16_t* p0) {
	rvd_sse_int16_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_int8_t mipp_sse_loadu_int8(const int8_t* p0) {
	rvd_sse_int8_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_uint64_t mipp_sse_loadu_uint64(const uint64_t* p0) {
	rvd_sse_uint64_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_uint32_t mipp_sse_loadu_uint32(const uint32_t* p0) {
	rvd_sse_uint32_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_uint16_t mipp_sse_loadu_uint16(const uint16_t* p0) {
	rvd_sse_uint16_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sse_uint8_t mipp_sse_loadu_uint8(const uint8_t* p0) {
	rvd_sse_uint8_t res;
	res.r= _mm_loadu_si128((__m128i*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_float64(float64_t* p0, const rvd_sse_float64_t r0) {
_mm_store_pd((float64_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_float32(float32_t* p0, const rvd_sse_float32_t r0) {
_mm_store_ps((float32_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int64(int64_t* p0, const rvd_sse_int64_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int32(int32_t* p0, const rvd_sse_int32_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int16(int16_t* p0, const rvd_sse_int16_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int8(int8_t* p0, const rvd_sse_int8_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint64(uint64_t* p0, const rvd_sse_uint64_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint32(uint32_t* p0, const rvd_sse_uint32_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint16(uint16_t* p0, const rvd_sse_uint16_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint8(uint8_t* p0, const rvd_sse_uint8_t r0) {
_mm_store_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_float64(float64_t* p0, const rvd_sse_float64_t r0) {
_mm_storeu_pd((float64_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_float32(float32_t* p0, const rvd_sse_float32_t r0) {
_mm_storeu_ps((float32_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int64(int64_t* p0, const rvd_sse_int64_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int32(int32_t* p0, const rvd_sse_int32_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int16(int16_t* p0, const rvd_sse_int16_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_int8(int8_t* p0, const rvd_sse_int8_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint64(uint64_t* p0, const rvd_sse_uint64_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint32(uint32_t* p0, const rvd_sse_uint32_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint16(uint16_t* p0, const rvd_sse_uint16_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
#if !defined(MIPP_ALIGNED_LOADS)
static inline void mipp_sse_store_uint8(uint8_t* p0, const rvd_sse_uint8_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_float64(float64_t* p0, const rvd_sse_float64_t r0) {
_mm_storeu_pd((float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_float32(float32_t* p0, const rvd_sse_float32_t r0) {
_mm_storeu_ps((float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_int64(int64_t* p0, const rvd_sse_int64_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_int32(int32_t* p0, const rvd_sse_int32_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_int16(int16_t* p0, const rvd_sse_int16_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_int8(int8_t* p0, const rvd_sse_int8_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_uint64(uint64_t* p0, const rvd_sse_uint64_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_uint32(uint32_t* p0, const rvd_sse_uint32_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_uint16(uint16_t* p0, const rvd_sse_uint16_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sse_storeu_uint8(uint8_t* p0, const rvd_sse_uint8_t r0) {
_mm_storeu_si128((__m128i*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sse_float32_t mipp_sse_set1_float32(const float32_t v0) {
	rvd_sse_float32_t res;
	res.r= _mm_set1_ps(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_set1_int16(const int16_t v0) {
	rvd_sse_int16_t res;
	res.r= _mm_set1_epi16(v0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_set1_int32(const int32_t v0) {
	rvd_sse_int32_t res;
	res.r= _mm_set1_epi32(v0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_set1_float64(const float64_t v0) {
	rvd_sse_float64_t res;
	res.r= _mm_set1_pd(v0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_set1_int64(const int64_t v0) {
	rvd_sse_int64_t res;
	res.r= _mm_set1_epi64x(v0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
#if defined(__SSE2__)
static inline rvd_sse_float32_t mipp_sse_set0_float32() {
	rvd_sse_float32_t res;
	res.r= _mm_setzero_ps();
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sse_int64_t mipp_sse_set0_int64() {
	rvd_sse_int64_t res;
	res.r= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sse_int32_t mipp_sse_set0_int32() {
	rvd_sse_int32_t res;
	res.r= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sse_int16_t mipp_sse_set0_int16() {
	rvd_sse_int16_t res;
	res.r= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sse_int8_t mipp_sse_set0_int8() {
	rvd_sse_int8_t res;
	res.r= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_float64_t mipp_sse_set0_k_float64() {
	rvm_sse_float64_t res;
	res.m= _mm_setzero_pd();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_float32_t mipp_sse_set0_k_float32() {
	rvm_sse_float32_t res;
	res.m= _mm_setzero_ps();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_int64_t mipp_sse_set0_k_int64() {
	rvm_sse_int64_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_int32_t mipp_sse_set0_k_int32() {
	rvm_sse_int32_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_int16_t mipp_sse_set0_k_int16() {
	rvm_sse_int16_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_int8_t mipp_sse_set0_k_int8() {
	rvm_sse_int8_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_uint64_t mipp_sse_set0_k_uint64() {
	rvm_sse_uint64_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_uint32_t mipp_sse_set0_k_uint32() {
	rvm_sse_uint32_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_uint16_t mipp_sse_set0_k_uint16() {
	rvm_sse_uint16_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sse_uint8_t mipp_sse_set0_k_uint8() {
	rvm_sse_uint8_t res;
	res.m= _mm_setzero_si128();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sse_float32_t mipp_sse_add_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_add_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_add_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_add_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_add_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_add_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_add_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_add_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__SSE2__)
static inline rvd_sse_int8_t mipp_sse_add_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	rvd_sse_int8_t res;
	res.r= _mm_add_epi8(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_add_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_add_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sse_float32_t mipp_sse_sub_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_sub_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_sub_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_sub_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_sub_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_sub_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_sub_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_sub_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__SSE2__)
static inline rvd_sse_int8_t mipp_sse_sub_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	rvd_sse_int8_t res;
	res.r= _mm_sub_epi8(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_sub_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_sub_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sse_float32_t mipp_sse_mul_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_mul_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_mul_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_mul_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_mul_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_mullo_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
#if defined(__SSE4_1__)
static inline rvd_sse_int32_t mipp_sse_mul_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_mullo_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
static inline rvd_sse_float32_t mipp_sse_div_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_sub_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_div_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_sub_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sse_float32_t mipp_sse_andb_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_and_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_andb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_and_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_andb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_andb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_andb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sse_float32_t mipp_sse_andb_k_float32(const rvm_sse_float32_t m0, const rvm_sse_float32_t m1) {
	rvm_sse_float32_t res;
	res.m= _mm_and_ps(m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_andb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	rvm_sse_float64_t res;
	res.m= _mm_and_pd(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_andb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	rvm_sse_int16_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_andb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	rvm_sse_int32_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_andb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	rvm_sse_int64_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
static inline rvd_sse_float32_t mipp_sse_andnb_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_and_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_andnb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_and_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_andnb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_andnb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_andnb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_and_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
static inline rvm_sse_float32_t mipp_sse_andnb_k_float32(const rvm_sse_float32_t m0, const rvm_sse_float32_t m1) {
	rvm_sse_float32_t res;
	res.m= _mm_and_ps(m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_andnb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	rvm_sse_float64_t res;
	res.m= _mm_and_pd(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_andnb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	rvm_sse_int16_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_andnb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	rvm_sse_int32_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- andnb_k
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_andnb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	rvm_sse_int64_t res;
	res.m= _mm_and_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
static inline rvd_sse_float32_t mipp_sse_orb_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_or_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_orb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_or_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_orb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_or_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_orb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_or_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_orb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_or_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
static inline rvm_sse_float32_t mipp_sse_orb_k_float32(const rvm_sse_float32_t m0, const rvm_sse_float32_t m1) {
	rvm_sse_float32_t res;
	res.m= _mm_or_ps(m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_orb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	rvm_sse_float64_t res;
	res.m= _mm_or_pd(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_orb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	rvm_sse_int16_t res;
	res.m= _mm_or_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_orb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	rvm_sse_int32_t res;
	res.m= _mm_or_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- orb_k
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_orb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	rvm_sse_int64_t res;
	res.m= _mm_or_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
static inline rvd_sse_float32_t mipp_sse_xorb_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvd_sse_float32_t res;
	res.r= _mm_xor_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
#if defined(__SSE2__)
static inline rvd_sse_float64_t mipp_sse_xorb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvd_sse_float64_t res;
	res.r= _mm_xor_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
#if defined(__SSE2__)
static inline rvd_sse_int16_t mipp_sse_xorb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvd_sse_int16_t res;
	res.r= _mm_xor_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
#if defined(__SSE2__)
static inline rvd_sse_int32_t mipp_sse_xorb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvd_sse_int32_t res;
	res.r= _mm_xor_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb
#if defined(__SSE2__)
static inline rvd_sse_int64_t mipp_sse_xorb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvd_sse_int64_t res;
	res.r= _mm_xor_si128(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
static inline rvm_sse_float32_t mipp_sse_xorb_k_float32(const rvm_sse_float32_t m0, const rvm_sse_float32_t m1) {
	rvm_sse_float32_t res;
	res.m= _mm_xor_ps(m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_xorb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	rvm_sse_float64_t res;
	res.m= _mm_xor_pd(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_xorb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	rvm_sse_int16_t res;
	res.m= _mm_xor_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_xorb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	rvm_sse_int32_t res;
	res.m= _mm_xor_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- xorb_k
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_xorb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	rvm_sse_int64_t res;
	res.m= _mm_xor_si128(m0.m, m1.m);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sse_float32_t mipp_sse_cmpeq_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmpeq_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmpeq_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmpeq_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_cmpeq_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvm_sse_int16_t res;
	res.m= _mm_cmpeq_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_cmpeq_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvm_sse_int32_t res;
	res.m= _mm_cmpeq_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_cmpeq_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvm_sse_int64_t res;
	res.m= _mm_cmpeq_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
#if defined(__SSE4_1__)
static inline rvm_sse_int64_t mipp_sse_cmpeq_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvm_sse_int64_t res;
	res.m= _mm_cmpeq_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sse_float32_t mipp_sse_cmpneq_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmpneq_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmpneq_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmpneq_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
#if defined(__SSE4_1__)
static inline rvm_sse_int64_t mipp_sse_cmpneq_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvm_sse_int64_t res;
	res.m= _mm_cmpneq_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
static inline rvm_sse_float32_t mipp_sse_cmplt_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmplt_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_cmplt_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvm_sse_int16_t res;
	res.m= _mm_cmplt_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_cmplt_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvm_sse_int32_t res;
	res.m= _mm_cmplt_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmplt
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmplt_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmplt_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
static inline rvm_sse_float32_t mipp_sse_cmpgt_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmpgt_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__SSE2__)
static inline rvm_sse_int64_t mipp_sse_cmpgt_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	rvm_sse_int64_t res;
	res.m= _mm_cmpgt_epi64(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__SSE2__)
static inline rvm_sse_int32_t mipp_sse_cmpgt_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	rvm_sse_int32_t res;
	res.m= _mm_cmpgt_epi32(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__SSE2__)
static inline rvm_sse_int16_t mipp_sse_cmpgt_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	rvm_sse_int16_t res;
	res.m= _mm_cmpgt_epi16(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__SSE2__)
static inline rvm_sse_int8_t mipp_sse_cmpgt_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	rvm_sse_int8_t res;
	res.m= _mm_cmpgt_epi8(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpgt
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmpgt_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmpgt_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
static inline rvm_sse_float32_t mipp_sse_cmple_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmple_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmple
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmple_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmple_pd(r0.r, r1.r);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
static inline rvm_sse_float32_t mipp_sse_cmpge_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	rvm_sse_float32_t res;
	res.m= _mm_cmpge_ps(r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpge
#if defined(__SSE2__)
static inline rvm_sse_float64_t mipp_sse_cmpge_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	rvm_sse_float64_t res;
	res.m= _mm_cmpge_pd(r0.r, r1.r);
	return res;
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) && defined(__SSE2__) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_float64_t mipp_sse_load_float64(const float64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_float32_t mipp_sse_load_float32(const float32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_int64_t mipp_sse_load_int64(const int64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_int32_t mipp_sse_load_int32(const int32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_int16_t mipp_sse_load_int16(const int16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_int8_t mipp_sse_load_int8(const int8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_int8");
	exit(-1);
}
#endif
#if !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_uint64_t mipp_sse_load_uint64(const uint64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_uint64");
	exit(-1);
}
#endif
#if !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_uint32_t mipp_sse_load_uint32(const uint32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_uint32");
	exit(-1);
}
#endif
#if !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_uint16_t mipp_sse_load_uint16(const uint16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_uint16");
	exit(-1);
}
#endif
#if !( !defined(MIPP_ALIGNED_LOADS) )
static inline rvd_sse_uint8_t mipp_sse_load_uint8(const uint8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_load_uint8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_float64(float64_t* p0, const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_float64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_float32(float32_t* p0, const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_float32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_int64(int64_t* p0, const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_int64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_int32(int32_t* p0, const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_int32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_int16(int16_t* p0, const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_int16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_int8(int8_t* p0, const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_int8");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_uint64(uint64_t* p0, const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_uint64");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_uint32(uint32_t* p0, const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_uint32");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_uint16(uint16_t* p0, const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_uint16");
	exit(-1);
}
#endif
#if !( defined(MIPP_ALIGNED_LOADS) ) && !( !defined(MIPP_ALIGNED_LOADS) )
static inline void mipp_sse_store_uint8(uint8_t* p0, const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_store_uint8");
	exit(-1);
}
#endif
static inline rvd_sse_float64_t mipp_sse_set_float64(const float64_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_set_float32(const float32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_set_int64(const int64_t vals[MIPP_N_INT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_set_int32(const int32_t vals[MIPP_N_INT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_set_int16(const int16_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_set_int8(const int8_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_set_uint64(const uint64_t vals[MIPP_N_UINT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_set_uint32(const uint32_t vals[MIPP_N_UINT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_set_uint16(const uint16_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_set_uint8(const uint8_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_uint8");
	exit(-1);
}
static inline rvm_sse_float64_t mipp_sse_set_k_float64(const int32_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_float64");
	exit(-1);
}
static inline rvm_sse_float32_t mipp_sse_set_k_float32(const int32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_float32");
	exit(-1);
}
static inline rvm_sse_int64_t mipp_sse_set_k_int64(const int32_t vals[MIPP_N_INT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_int64");
	exit(-1);
}
static inline rvm_sse_int32_t mipp_sse_set_k_int32(const int32_t vals[MIPP_N_INT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_set_k_int16(const int32_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_set_k_int8(const int32_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_set_k_uint64(const int32_t vals[MIPP_N_UINT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_set_k_uint32(const int32_t vals[MIPP_N_UINT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_set_k_uint16(const int32_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_set_k_uint8(const int32_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set_k_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_set1_float64(const float64_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_set1_int64(const int64_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_set1_int32(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_set1_int16(const int16_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_set1_int8(const int8_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_set1_uint64(const uint64_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_set1_uint32(const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_set1_uint16(const uint16_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_set1_uint8(const uint8_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_uint8");
	exit(-1);
}
static inline rvm_sse_int64_t mipp_sse_set1_k_int64(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_int64");
	exit(-1);
}
static inline rvm_sse_int32_t mipp_sse_set1_k_int32(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_set1_k_int16(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_set1_k_int8(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_set1_k_uint64(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_set1_k_uint32(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_set1_k_uint16(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_set1_k_uint8(const int32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set1_k_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_maskzld_float64(const rvm_sse_int32_t m0, const float64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_maskzld_float32(const rvm_sse_int32_t m0, const float32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_maskzld_int64(const rvm_sse_int32_t m0, const int64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_maskzld_int32(const rvm_sse_int32_t m0, const int32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_maskzld_int16(const rvm_sse_int32_t m0, const int16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_maskzld_int8(const rvm_sse_int32_t m0, const int8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_maskzld_uint64(const rvm_sse_int32_t m0, const uint64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_maskzld_uint32(const rvm_sse_int32_t m0, const uint32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_maskzld_uint16(const rvm_sse_int32_t m0, const uint16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_maskzld_uint8(const rvm_sse_int32_t m0, const uint8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskzld_uint8");
	exit(-1);
}
static inline void mipp_sse_maskst_float64(float64_t* p0, const rvm_sse_int32_t m0, const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_float64");
	exit(-1);
}
static inline void mipp_sse_maskst_float32(float32_t* p0, const rvm_sse_int32_t m0, const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_float32");
	exit(-1);
}
static inline void mipp_sse_maskst_int64(int64_t* p0, const rvm_sse_int32_t m0, const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_int64");
	exit(-1);
}
static inline void mipp_sse_maskst_int32(int32_t* p0, const rvm_sse_int32_t m0, const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_int32");
	exit(-1);
}
static inline void mipp_sse_maskst_int16(int16_t* p0, const rvm_sse_int32_t m0, const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_int16");
	exit(-1);
}
static inline void mipp_sse_maskst_int8(int8_t* p0, const rvm_sse_int32_t m0, const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_int8");
	exit(-1);
}
static inline void mipp_sse_maskst_uint64(uint64_t* p0, const rvm_sse_int32_t m0, const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_uint64");
	exit(-1);
}
static inline void mipp_sse_maskst_uint32(uint32_t* p0, const rvm_sse_int32_t m0, const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_uint32");
	exit(-1);
}
static inline void mipp_sse_maskst_uint16(uint16_t* p0, const rvm_sse_int32_t m0, const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_uint16");
	exit(-1);
}
static inline void mipp_sse_maskst_uint8(uint8_t* p0, const rvm_sse_int32_t m0, const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskst_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_set0_float64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_float64");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float32_t mipp_sse_set0_float32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_float32");
	exit(-1);
}
#endif
static inline rvd_sse_uint64_t mipp_sse_set0_uint64() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_set0_uint32() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_set0_uint16() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_set0_uint8() {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_set0_uint8");
	exit(-1);
}
static inline float64_t mipp_sse_get_float64(const rvd_sse_float64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_float64");
	exit(-1);
}
static inline float32_t mipp_sse_get_float32(const rvd_sse_float32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_float32");
	exit(-1);
}
static inline int64_t mipp_sse_get_int64(const rvd_sse_int64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_int64");
	exit(-1);
}
static inline int32_t mipp_sse_get_int32(const rvd_sse_int32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_int32");
	exit(-1);
}
static inline int16_t mipp_sse_get_int16(const rvd_sse_int16_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_int16");
	exit(-1);
}
static inline int8_t mipp_sse_get_int8(const rvd_sse_int8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_int8");
	exit(-1);
}
static inline uint64_t mipp_sse_get_uint64(const rvd_sse_uint64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_uint64");
	exit(-1);
}
static inline uint32_t mipp_sse_get_uint32(const rvd_sse_uint32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_uint32");
	exit(-1);
}
static inline uint16_t mipp_sse_get_uint16(const rvd_sse_uint16_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_uint16");
	exit(-1);
}
static inline uint8_t mipp_sse_get_uint8(const rvd_sse_uint8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_uint8");
	exit(-1);
}
static inline float64_t mipp_sse_get_k_float64(const rvm_sse_float64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_float64");
	exit(-1);
}
static inline float32_t mipp_sse_get_k_float32(const rvm_sse_float32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_float32");
	exit(-1);
}
static inline int64_t mipp_sse_get_k_int64(const rvm_sse_int64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_int64");
	exit(-1);
}
static inline int32_t mipp_sse_get_k_int32(const rvm_sse_int32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_int32");
	exit(-1);
}
static inline int16_t mipp_sse_get_k_int16(const rvm_sse_int16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_int16");
	exit(-1);
}
static inline int8_t mipp_sse_get_k_int8(const rvm_sse_int8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_int8");
	exit(-1);
}
static inline uint64_t mipp_sse_get_k_uint64(const rvm_sse_uint64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_uint64");
	exit(-1);
}
static inline uint32_t mipp_sse_get_k_uint32(const rvm_sse_uint32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_uint32");
	exit(-1);
}
static inline uint16_t mipp_sse_get_k_uint16(const rvm_sse_uint16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_uint16");
	exit(-1);
}
static inline uint8_t mipp_sse_get_k_uint8(const rvm_sse_uint8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_get_k_uint8");
	exit(-1);
}
static inline float64_t mipp_sse_getfirst_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_float64");
	exit(-1);
}
static inline float32_t mipp_sse_getfirst_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_float32");
	exit(-1);
}
static inline int64_t mipp_sse_getfirst_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_int64");
	exit(-1);
}
static inline int32_t mipp_sse_getfirst_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_int32");
	exit(-1);
}
static inline int16_t mipp_sse_getfirst_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_int16");
	exit(-1);
}
static inline int8_t mipp_sse_getfirst_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_int8");
	exit(-1);
}
static inline uint64_t mipp_sse_getfirst_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_uint64");
	exit(-1);
}
static inline uint32_t mipp_sse_getfirst_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_uint32");
	exit(-1);
}
static inline uint16_t mipp_sse_getfirst_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_uint16");
	exit(-1);
}
static inline uint8_t mipp_sse_getfirst_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_getfirst_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_sqrt_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sqrt_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_sqrt_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sqrt_float32");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_rsqrt_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_rsqrt_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_rsqrt_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_rsqrt_float32");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_add_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_add_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_add_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_add_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_int16");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int8_t mipp_sse_add_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_int8");
	exit(-1);
}
#endif
static inline rvd_sse_uint64_t mipp_sse_add_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_add_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_add_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_add_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_add_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_sub_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_sub_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_sub_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_sub_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_int16");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int8_t mipp_sse_sub_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_int8");
	exit(-1);
}
#endif
static inline rvd_sse_uint64_t mipp_sse_sub_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_sub_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_sub_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_sub_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_sub_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_mul_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_float64");
	exit(-1);
}
#endif
static inline rvd_sse_int64_t mipp_sse_mul_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_int64");
	exit(-1);
}
#if !( defined(__SSE4_1__) )
static inline rvd_sse_int32_t mipp_sse_mul_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_mul_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_mul_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_mul_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_mul_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_mul_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_mul_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_mul_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_div_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_div_float64");
	exit(-1);
}
#endif
static inline rvd_sse_float64_t mipp_sse_min_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_min_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_min_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_min_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_min_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_min_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_min_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_min_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_min_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_min_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_min_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_max_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_max_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_max_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_max_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_max_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_max_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_max_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_max_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_max_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_max_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_max_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_fmadd_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1, const rvd_sse_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmadd_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_fmadd_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1, const rvd_sse_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmadd_float32");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_fmadd_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1, const rvd_sse_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmadd_int32");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_fmsub_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1, const rvd_sse_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmsub_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_fmsub_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1, const rvd_sse_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmsub_float32");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_fmsub_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1, const rvd_sse_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_fmsub_int32");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_andb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_andb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_andb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_andb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_andb_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_andb_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_andb_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_andb_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_andb_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_andb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int64_t mipp_sse_andb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_andb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_andb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_andb_k_int8(const rvm_sse_int8_t m0, const rvm_sse_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_andb_k_uint64(const rvm_sse_uint64_t m0, const rvm_sse_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_andb_k_uint32(const rvm_sse_uint32_t m0, const rvm_sse_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_andb_k_uint16(const rvm_sse_uint16_t m0, const rvm_sse_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_andb_k_uint8(const rvm_sse_uint8_t m0, const rvm_sse_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andb_k_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_andnb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_andnb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_andnb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_andnb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_andnb_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_andnb_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_andnb_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_andnb_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_andnb_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_andnb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int64_t mipp_sse_andnb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_andnb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_andnb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_andnb_k_int8(const rvm_sse_int8_t m0, const rvm_sse_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_andnb_k_uint64(const rvm_sse_uint64_t m0, const rvm_sse_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_andnb_k_uint32(const rvm_sse_uint32_t m0, const rvm_sse_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_andnb_k_uint16(const rvm_sse_uint16_t m0, const rvm_sse_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_andnb_k_uint8(const rvm_sse_uint8_t m0, const rvm_sse_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_andnb_k_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_orb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_orb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_orb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_orb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_orb_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_orb_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_orb_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_orb_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_orb_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_orb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int64_t mipp_sse_orb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_orb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_orb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_orb_k_int8(const rvm_sse_int8_t m0, const rvm_sse_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_orb_k_uint64(const rvm_sse_uint64_t m0, const rvm_sse_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_orb_k_uint32(const rvm_sse_uint32_t m0, const rvm_sse_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_orb_k_uint16(const rvm_sse_uint16_t m0, const rvm_sse_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_orb_k_uint8(const rvm_sse_uint8_t m0, const rvm_sse_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_orb_k_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvd_sse_float64_t mipp_sse_xorb_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int64_t mipp_sse_xorb_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int32_t mipp_sse_xorb_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvd_sse_int16_t mipp_sse_xorb_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_int16");
	exit(-1);
}
#endif
static inline rvd_sse_int8_t mipp_sse_xorb_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_xorb_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_xorb_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_xorb_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_xorb_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_xorb_k_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int64_t mipp_sse_xorb_k_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_xorb_k_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_xorb_k_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_xorb_k_int8(const rvm_sse_int8_t m0, const rvm_sse_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_xorb_k_uint64(const rvm_sse_uint64_t m0, const rvm_sse_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_xorb_k_uint32(const rvm_sse_uint32_t m0, const rvm_sse_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_xorb_k_uint16(const rvm_sse_uint16_t m0, const rvm_sse_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_xorb_k_uint8(const rvm_sse_uint8_t m0, const rvm_sse_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_xorb_k_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_msb_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_msb_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_msb_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_msb_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_msb_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_msb_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_msb_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_msb_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_msb_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_msb_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_msb_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_notb_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_notb_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_notb_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_notb_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_notb_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_notb_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_notb_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_notb_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_notb_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_notb_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_uint8");
	exit(-1);
}
static inline rvm_sse_float64_t mipp_sse_notb_k_float64(const rvm_sse_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_float64");
	exit(-1);
}
static inline rvm_sse_float32_t mipp_sse_notb_k_float32(const rvm_sse_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_float32");
	exit(-1);
}
static inline rvm_sse_int64_t mipp_sse_notb_k_int64(const rvm_sse_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_int64");
	exit(-1);
}
static inline rvm_sse_int32_t mipp_sse_notb_k_int32(const rvm_sse_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_notb_k_int16(const rvm_sse_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_notb_k_int8(const rvm_sse_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_notb_k_uint64(const rvm_sse_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_notb_k_uint32(const rvm_sse_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_notb_k_uint16(const rvm_sse_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_notb_k_uint8(const rvm_sse_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_notb_k_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmpeq_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) ) && !( defined(__SSE4_1__) )
static inline rvm_sse_int64_t mipp_sse_cmpeq_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_cmpeq_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_cmpeq_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_cmpeq_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_cmpeq_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmpeq_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmpeq_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmpeq_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpeq_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmpneq_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE4_1__) )
static inline rvm_sse_int64_t mipp_sse_cmpneq_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_int64");
	exit(-1);
}
#endif
static inline rvm_sse_int32_t mipp_sse_cmpneq_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_cmpneq_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_cmpneq_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_cmpneq_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmpneq_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmpneq_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmpneq_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpneq_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmplt_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_float64");
	exit(-1);
}
#endif
static inline rvm_sse_int64_t mipp_sse_cmplt_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_int64");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_cmplt_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_cmplt_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_int16");
	exit(-1);
}
#endif
static inline rvm_sse_int8_t mipp_sse_cmplt_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_cmplt_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmplt_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmplt_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmplt_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmplt_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmple_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_float64");
	exit(-1);
}
#endif
static inline rvm_sse_int64_t mipp_sse_cmple_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_int64");
	exit(-1);
}
static inline rvm_sse_int32_t mipp_sse_cmple_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_cmple_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_cmple_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_cmple_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmple_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmple_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmple_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmple_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmpge_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_float64");
	exit(-1);
}
#endif
static inline rvm_sse_int64_t mipp_sse_cmpge_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_int64");
	exit(-1);
}
static inline rvm_sse_int32_t mipp_sse_cmpge_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_int32");
	exit(-1);
}
static inline rvm_sse_int16_t mipp_sse_cmpge_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_int16");
	exit(-1);
}
static inline rvm_sse_int8_t mipp_sse_cmpge_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_int8");
	exit(-1);
}
static inline rvm_sse_uint64_t mipp_sse_cmpge_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmpge_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmpge_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmpge_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpge_uint8");
	exit(-1);
}
#if !( defined(__SSE2__) )
static inline rvm_sse_float64_t mipp_sse_cmpgt_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_float64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int64_t mipp_sse_cmpgt_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_int64");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int32_t mipp_sse_cmpgt_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_int32");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int16_t mipp_sse_cmpgt_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_int16");
	exit(-1);
}
#endif
#if !( defined(__SSE2__) )
static inline rvm_sse_int8_t mipp_sse_cmpgt_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_int8");
	exit(-1);
}
#endif
static inline rvm_sse_uint64_t mipp_sse_cmpgt_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_uint64");
	exit(-1);
}
static inline rvm_sse_uint32_t mipp_sse_cmpgt_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_uint32");
	exit(-1);
}
static inline rvm_sse_uint16_t mipp_sse_cmpgt_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_uint16");
	exit(-1);
}
static inline rvm_sse_uint8_t mipp_sse_cmpgt_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_cmpgt_uint8");
	exit(-1);
}
static inline float64_t mipp_sse_round_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_float64");
	exit(-1);
}
static inline float32_t mipp_sse_round_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_float32");
	exit(-1);
}
static inline int64_t mipp_sse_round_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_int64");
	exit(-1);
}
static inline int32_t mipp_sse_round_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_int32");
	exit(-1);
}
static inline int16_t mipp_sse_round_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_int16");
	exit(-1);
}
static inline int8_t mipp_sse_round_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_int8");
	exit(-1);
}
static inline uint64_t mipp_sse_round_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_uint64");
	exit(-1);
}
static inline uint32_t mipp_sse_round_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_uint32");
	exit(-1);
}
static inline uint16_t mipp_sse_round_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_uint16");
	exit(-1);
}
static inline uint8_t mipp_sse_round_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_round_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_blend_float64(const rvd_sse_float64_t r0, const rvd_sse_float64_t r1, const rvm_sse_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_blend_float32(const rvd_sse_float32_t r0, const rvd_sse_float32_t r1, const rvm_sse_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_blend_int64(const rvd_sse_int64_t r0, const rvd_sse_int64_t r1, const rvm_sse_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_blend_int32(const rvd_sse_int32_t r0, const rvd_sse_int32_t r1, const rvm_sse_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_blend_int16(const rvd_sse_int16_t r0, const rvd_sse_int16_t r1, const rvm_sse_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_blend_int8(const rvd_sse_int8_t r0, const rvd_sse_int8_t r1, const rvm_sse_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_blend_uint64(const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1, const rvm_sse_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_blend_uint32(const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1, const rvm_sse_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_blend_uint16(const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1, const rvm_sse_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_blend_uint8(const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1, const rvm_sse_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_blend_uint8");
	exit(-1);
}
static inline int32_t mipp_sse_testz_float64(const rvm_sse_float64_t m0, const rvm_sse_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_float64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_float32(const rvm_sse_float32_t m0, const rvm_sse_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_float32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_int64(const rvm_sse_int64_t m0, const rvm_sse_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_int64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_int32(const rvm_sse_int32_t m0, const rvm_sse_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_int32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_int16(const rvm_sse_int16_t m0, const rvm_sse_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_int16");
	exit(-1);
}
static inline int32_t mipp_sse_testz_int8(const rvm_sse_int8_t m0, const rvm_sse_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_int8");
	exit(-1);
}
static inline int32_t mipp_sse_testz_uint64(const rvm_sse_uint64_t m0, const rvm_sse_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_uint64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_uint32(const rvm_sse_uint32_t m0, const rvm_sse_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_uint32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_uint16(const rvm_sse_uint16_t m0, const rvm_sse_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_uint16");
	exit(-1);
}
static inline int32_t mipp_sse_testz_uint8(const rvm_sse_uint8_t m0, const rvm_sse_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_uint8");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_float64(const rvm_sse_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_float64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_float32(const rvm_sse_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_float32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_int64(const rvm_sse_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_int64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_int32(const rvm_sse_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_int32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_int16(const rvm_sse_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_int16");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_int8(const rvm_sse_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_int8");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_uint64(const rvm_sse_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_uint64");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_uint32(const rvm_sse_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_uint32");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_uint16(const rvm_sse_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_uint16");
	exit(-1);
}
static inline int32_t mipp_sse_testz_2_uint8(const rvm_sse_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_testz_2_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_hadd_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_hadd_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_hadd_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_hadd_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_hadd_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_hadd_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_hadd_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_hadd_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_hadd_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_hadd_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_hmul_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_hmul_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_hmul_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_hmul_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_hmul_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_hmul_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_hmul_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_hmul_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_hmul_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_hmul_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmul_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_hmin_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_hmin_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_hmin_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_hmin_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_hmin_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_hmin_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_hmin_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_hmin_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_hmin_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_hmin_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmin_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_hmax_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_hmax_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_hmax_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_hmax_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_hmax_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_hmax_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_hmax_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_hmax_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_hmax_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_hmax_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hmax_uint8");
	exit(-1);
}
static inline float64_t mipp_sse_hadd_to_scal_float64(const rvd_sse_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_float64");
	exit(-1);
}
static inline float32_t mipp_sse_hadd_to_scal_float32(const rvd_sse_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_float32");
	exit(-1);
}
static inline int64_t mipp_sse_hadd_to_scal_int64(const rvd_sse_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_int64");
	exit(-1);
}
static inline int32_t mipp_sse_hadd_to_scal_int32(const rvd_sse_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_int32");
	exit(-1);
}
static inline int16_t mipp_sse_hadd_to_scal_int16(const rvd_sse_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_int16");
	exit(-1);
}
static inline int8_t mipp_sse_hadd_to_scal_int8(const rvd_sse_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_int8");
	exit(-1);
}
static inline uint64_t mipp_sse_hadd_to_scal_uint64(const rvd_sse_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_uint64");
	exit(-1);
}
static inline uint32_t mipp_sse_hadd_to_scal_uint32(const rvd_sse_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_uint32");
	exit(-1);
}
static inline uint16_t mipp_sse_hadd_to_scal_uint16(const rvd_sse_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_uint16");
	exit(-1);
}
static inline uint8_t mipp_sse_hadd_to_scal_uint8(const rvd_sse_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_hadd_to_scal_uint8");
	exit(-1);
}
static inline rvd_sse_float64_t mipp_sse_maskz_add_float64(const rvm_sse_float64_t m0, const rvd_sse_float64_t r0, const rvd_sse_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_float64");
	exit(-1);
}
static inline rvd_sse_float32_t mipp_sse_maskz_add_float32(const rvm_sse_float32_t m0, const rvd_sse_float32_t r0, const rvd_sse_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_float32");
	exit(-1);
}
static inline rvd_sse_int64_t mipp_sse_maskz_add_int64(const rvm_sse_int64_t m0, const rvd_sse_int64_t r0, const rvd_sse_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_int64");
	exit(-1);
}
static inline rvd_sse_int32_t mipp_sse_maskz_add_int32(const rvm_sse_int32_t m0, const rvd_sse_int32_t r0, const rvd_sse_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_int32");
	exit(-1);
}
static inline rvd_sse_int16_t mipp_sse_maskz_add_int16(const rvm_sse_int16_t m0, const rvd_sse_int16_t r0, const rvd_sse_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_int16");
	exit(-1);
}
static inline rvd_sse_int8_t mipp_sse_maskz_add_int8(const rvm_sse_int8_t m0, const rvd_sse_int8_t r0, const rvd_sse_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_int8");
	exit(-1);
}
static inline rvd_sse_uint64_t mipp_sse_maskz_add_uint64(const rvm_sse_uint64_t m0, const rvd_sse_uint64_t r0, const rvd_sse_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_uint64");
	exit(-1);
}
static inline rvd_sse_uint32_t mipp_sse_maskz_add_uint32(const rvm_sse_uint32_t m0, const rvd_sse_uint32_t r0, const rvd_sse_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_uint32");
	exit(-1);
}
static inline rvd_sse_uint16_t mipp_sse_maskz_add_uint16(const rvm_sse_uint16_t m0, const rvd_sse_uint16_t r0, const rvd_sse_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_uint16");
	exit(-1);
}
static inline rvd_sse_uint8_t mipp_sse_maskz_add_uint8(const rvm_sse_uint8_t m0, const rvd_sse_uint8_t r0, const rvd_sse_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sse_maskz_add_uint8");
	exit(-1);
}
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_ */
