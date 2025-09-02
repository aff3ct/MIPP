#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ 
#if defined(__AVX512__)
#define MIPP_RVD_SIZE_BYTE MIPP_AVX512_RVD_SIZE_BYTE
#elif defined(__AVX__)
#define MIPP_RVD_SIZE_BYTE MIPP_AVX_RVD_SIZE_BYTE
#elif defined(__SSE__)
#define MIPP_RVD_SIZE_BYTE MIPP_SSE_RVD_SIZE_BYTE
#endif
#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))
#if defined(__AVX512__)
typedef rvd_avx512_float64_t rvd_float64_t;
typedef rvd_avx512_float32_t rvd_float32_t;
typedef rvd_avx512_int64_t rvd_int64_t;
typedef rvd_avx512_int32_t rvd_int32_t;
typedef rvd_avx512_int16_t rvd_int16_t;
typedef rvd_avx512_int8_t rvd_int8_t;
typedef rvd_avx512_uint64_t rvd_uint64_t;
typedef rvd_avx512_uint32_t rvd_uint32_t;
typedef rvd_avx512_uint16_t rvd_uint16_t;
typedef rvd_avx512_uint8_t rvd_uint8_t;
typedef rvm_avx512_float64_t rvm_float64_t;
typedef rvm_avx512_float32_t rvm_float32_t;
typedef rvm_avx512_int64_t rvm_int64_t;
typedef rvm_avx512_int32_t rvm_int32_t;
typedef rvm_avx512_int16_t rvm_int16_t;
typedef rvm_avx512_int8_t rvm_int8_t;
typedef rvm_avx512_uint64_t rvm_uint64_t;
typedef rvm_avx512_uint32_t rvm_uint32_t;
typedef rvm_avx512_uint16_t rvm_uint16_t;
typedef rvm_avx512_uint8_t rvm_uint8_t;
#elif defined(__AVX__)
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
#elif defined(__SSE__)
typedef rvd_sse_float64_t rvd_float64_t;
typedef rvd_sse_float32_t rvd_float32_t;
typedef rvd_sse_int64_t rvd_int64_t;
typedef rvd_sse_int32_t rvd_int32_t;
typedef rvd_sse_int16_t rvd_int16_t;
typedef rvd_sse_int8_t rvd_int8_t;
typedef rvd_sse_uint64_t rvd_uint64_t;
typedef rvd_sse_uint32_t rvd_uint32_t;
typedef rvd_sse_uint16_t rvd_uint16_t;
typedef rvd_sse_uint8_t rvd_uint8_t;
typedef rvm_sse_float64_t rvm_float64_t;
typedef rvm_sse_float32_t rvm_float32_t;
typedef rvm_sse_int64_t rvm_int64_t;
typedef rvm_sse_int32_t rvm_int32_t;
typedef rvm_sse_int16_t rvm_int16_t;
typedef rvm_sse_int8_t rvm_int8_t;
typedef rvm_sse_uint64_t rvm_uint64_t;
typedef rvm_sse_uint32_t rvm_uint32_t;
typedef rvm_sse_uint16_t rvm_uint16_t;
typedef rvm_sse_uint8_t rvm_uint8_t;
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
typedef struct { rvd_float64_m1_t r1, r2; } rvd_float64_m2_t;
typedef struct { rvd_float32_m1_t r1, r2; } rvd_float32_m2_t;
typedef struct { rvd_int64_m1_t r1, r2; } rvd_int64_m2_t;
typedef struct { rvd_int32_m1_t r1, r2; } rvd_int32_m2_t;
typedef struct { rvd_int16_m1_t r1, r2; } rvd_int16_m2_t;
typedef struct { rvd_int8_m1_t r1, r2; } rvd_int8_m2_t;
typedef struct { rvd_uint64_m1_t r1, r2; } rvd_uint64_m2_t;
typedef struct { rvd_uint32_m1_t r1, r2; } rvd_uint32_m2_t;
typedef struct { rvd_uint16_m1_t r1, r2; } rvd_uint16_m2_t;
typedef struct { rvd_uint8_m1_t r1, r2; } rvd_uint8_m2_t;
typedef struct { rvd_float64_m2_t r1, r2; } rvd_float64_m4_t;
typedef struct { rvd_float32_m2_t r1, r2; } rvd_float32_m4_t;
typedef struct { rvd_int64_m2_t r1, r2; } rvd_int64_m4_t;
typedef struct { rvd_int32_m2_t r1, r2; } rvd_int32_m4_t;
typedef struct { rvd_int16_m2_t r1, r2; } rvd_int16_m4_t;
typedef struct { rvd_int8_m2_t r1, r2; } rvd_int8_m4_t;
typedef struct { rvd_uint64_m2_t r1, r2; } rvd_uint64_m4_t;
typedef struct { rvd_uint32_m2_t r1, r2; } rvd_uint32_m4_t;
typedef struct { rvd_uint16_m2_t r1, r2; } rvd_uint16_m4_t;
typedef struct { rvd_uint8_m2_t r1, r2; } rvd_uint8_m4_t;
typedef struct { rvd_float64_m4_t r1, r2; } rvd_float64_m8_t;
typedef struct { rvd_float32_m4_t r1, r2; } rvd_float32_m8_t;
typedef struct { rvd_int64_m4_t r1, r2; } rvd_int64_m8_t;
typedef struct { rvd_int32_m4_t r1, r2; } rvd_int32_m8_t;
typedef struct { rvd_int16_m4_t r1, r2; } rvd_int16_m8_t;
typedef struct { rvd_int8_m4_t r1, r2; } rvd_int8_m8_t;
typedef struct { rvd_uint64_m4_t r1, r2; } rvd_uint64_m8_t;
typedef struct { rvd_uint32_m4_t r1, r2; } rvd_uint32_m8_t;
typedef struct { rvd_uint16_m4_t r1, r2; } rvd_uint16_m8_t;
typedef struct { rvd_uint8_m4_t r1, r2; } rvd_uint8_m8_t;
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
inline rvd_float64_t mipp_cast_float64_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_float64_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_float64_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_float64_float64_m1(r0.r1);
	res.r2 = mipp_cast_float64_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_float64_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_float64_float64_m2(r0.r1);
	res.r2 = mipp_cast_float64_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_float64_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_float64_float64_m4(r0.r1);
	res.r2 = mipp_cast_float64_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_float32_float64(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_float32_float64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_float32_float64_m2(const rvd_float32_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_float32_float64_m1(r0.r1);
	res.r2 = mipp_cast_float32_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_float32_float64_m4(const rvd_float32_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_float32_float64_m2(r0.r1);
	res.r2 = mipp_cast_float32_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_float32_float64_m8(const rvd_float32_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_float32_float64_m4(r0.r1);
	res.r2 = mipp_cast_float32_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_int64_float64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_int64_float64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_int64_float64_m2(const rvd_int64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_int64_float64_m1(r0.r1);
	res.r2 = mipp_cast_int64_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_int64_float64_m4(const rvd_int64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_int64_float64_m2(r0.r1);
	res.r2 = mipp_cast_int64_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_int64_float64_m8(const rvd_int64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_int64_float64_m4(r0.r1);
	res.r2 = mipp_cast_int64_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_int32_float64(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_int32_float64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_int32_float64_m2(const rvd_int32_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_int32_float64_m1(r0.r1);
	res.r2 = mipp_cast_int32_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_int32_float64_m4(const rvd_int32_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_int32_float64_m2(r0.r1);
	res.r2 = mipp_cast_int32_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_int32_float64_m8(const rvd_int32_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_int32_float64_m4(r0.r1);
	res.r2 = mipp_cast_int32_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_int16_float64(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_int16_float64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_int16_float64_m2(const rvd_int16_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_int16_float64_m1(r0.r1);
	res.r2 = mipp_cast_int16_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_int16_float64_m4(const rvd_int16_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_int16_float64_m2(r0.r1);
	res.r2 = mipp_cast_int16_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_int16_float64_m8(const rvd_int16_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_int16_float64_m4(r0.r1);
	res.r2 = mipp_cast_int16_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_int8_float64(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_int8_float64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_int8_float64_m2(const rvd_int8_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_int8_float64_m1(r0.r1);
	res.r2 = mipp_cast_int8_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_int8_float64_m4(const rvd_int8_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_int8_float64_m2(r0.r1);
	res.r2 = mipp_cast_int8_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_int8_float64_m8(const rvd_int8_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_int8_float64_m4(r0.r1);
	res.r2 = mipp_cast_int8_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_uint64_float64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_uint64_float64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_uint64_float64_m2(const rvd_uint64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_uint64_float64_m1(r0.r1);
	res.r2 = mipp_cast_uint64_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_uint64_float64_m4(const rvd_uint64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_uint64_float64_m2(r0.r1);
	res.r2 = mipp_cast_uint64_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_uint64_float64_m8(const rvd_uint64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_uint64_float64_m4(r0.r1);
	res.r2 = mipp_cast_uint64_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_uint32_float64(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_uint32_float64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_uint32_float64_m2(const rvd_uint32_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_uint32_float64_m1(r0.r1);
	res.r2 = mipp_cast_uint32_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_uint32_float64_m4(const rvd_uint32_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_uint32_float64_m2(r0.r1);
	res.r2 = mipp_cast_uint32_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_uint32_float64_m8(const rvd_uint32_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_uint32_float64_m4(r0.r1);
	res.r2 = mipp_cast_uint32_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_uint16_float64(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_uint16_float64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_uint16_float64_m2(const rvd_uint16_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_uint16_float64_m1(r0.r1);
	res.r2 = mipp_cast_uint16_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_uint16_float64_m4(const rvd_uint16_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_uint16_float64_m2(r0.r1);
	res.r2 = mipp_cast_uint16_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_uint16_float64_m8(const rvd_uint16_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_uint16_float64_m4(r0.r1);
	res.r2 = mipp_cast_uint16_float64_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_cast_uint8_float64(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_cast_uint8_float64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_float64(r0);
}
inline rvd_float64_m2_t mipp_cast_uint8_float64_m2(const rvd_uint8_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_cast_uint8_float64_m1(r0.r1);
	res.r2 = mipp_cast_uint8_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_cast_uint8_float64_m4(const rvd_uint8_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_cast_uint8_float64_m2(r0.r1);
	res.r2 = mipp_cast_uint8_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_cast_uint8_float64_m8(const rvd_uint8_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_cast_uint8_float64_m4(r0.r1);
	res.r2 = mipp_cast_uint8_float64_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_float64_float32(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_float64_float32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_float64_float32_m2(const rvd_float64_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_float64_float32_m1(r0.r1);
	res.r2 = mipp_cast_float64_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_float64_float32_m4(const rvd_float64_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_float64_float32_m2(r0.r1);
	res.r2 = mipp_cast_float64_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_float64_float32_m8(const rvd_float64_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_float64_float32_m4(r0.r1);
	res.r2 = mipp_cast_float64_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_float32_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_float32_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_float32_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_float32_float32_m1(r0.r1);
	res.r2 = mipp_cast_float32_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_float32_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_float32_float32_m2(r0.r1);
	res.r2 = mipp_cast_float32_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_float32_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_float32_float32_m4(r0.r1);
	res.r2 = mipp_cast_float32_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_int64_float32(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_int64_float32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_int64_float32_m2(const rvd_int64_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_int64_float32_m1(r0.r1);
	res.r2 = mipp_cast_int64_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_int64_float32_m4(const rvd_int64_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_int64_float32_m2(r0.r1);
	res.r2 = mipp_cast_int64_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_int64_float32_m8(const rvd_int64_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_int64_float32_m4(r0.r1);
	res.r2 = mipp_cast_int64_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_int32_float32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_int32_float32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_int32_float32_m2(const rvd_int32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_int32_float32_m1(r0.r1);
	res.r2 = mipp_cast_int32_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_int32_float32_m4(const rvd_int32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_int32_float32_m2(r0.r1);
	res.r2 = mipp_cast_int32_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_int32_float32_m8(const rvd_int32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_int32_float32_m4(r0.r1);
	res.r2 = mipp_cast_int32_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_int16_float32(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_int16_float32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_int16_float32_m2(const rvd_int16_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_int16_float32_m1(r0.r1);
	res.r2 = mipp_cast_int16_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_int16_float32_m4(const rvd_int16_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_int16_float32_m2(r0.r1);
	res.r2 = mipp_cast_int16_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_int16_float32_m8(const rvd_int16_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_int16_float32_m4(r0.r1);
	res.r2 = mipp_cast_int16_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_int8_float32(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_int8_float32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_int8_float32_m2(const rvd_int8_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_int8_float32_m1(r0.r1);
	res.r2 = mipp_cast_int8_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_int8_float32_m4(const rvd_int8_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_int8_float32_m2(r0.r1);
	res.r2 = mipp_cast_int8_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_int8_float32_m8(const rvd_int8_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_int8_float32_m4(r0.r1);
	res.r2 = mipp_cast_int8_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_uint64_float32(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_uint64_float32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_uint64_float32_m2(const rvd_uint64_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_uint64_float32_m1(r0.r1);
	res.r2 = mipp_cast_uint64_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_uint64_float32_m4(const rvd_uint64_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_uint64_float32_m2(r0.r1);
	res.r2 = mipp_cast_uint64_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_uint64_float32_m8(const rvd_uint64_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_uint64_float32_m4(r0.r1);
	res.r2 = mipp_cast_uint64_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_uint32_float32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_uint32_float32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_uint32_float32_m2(const rvd_uint32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_uint32_float32_m1(r0.r1);
	res.r2 = mipp_cast_uint32_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_uint32_float32_m4(const rvd_uint32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_uint32_float32_m2(r0.r1);
	res.r2 = mipp_cast_uint32_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_uint32_float32_m8(const rvd_uint32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_uint32_float32_m4(r0.r1);
	res.r2 = mipp_cast_uint32_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_uint16_float32(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_uint16_float32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_uint16_float32_m2(const rvd_uint16_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_uint16_float32_m1(r0.r1);
	res.r2 = mipp_cast_uint16_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_uint16_float32_m4(const rvd_uint16_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_uint16_float32_m2(r0.r1);
	res.r2 = mipp_cast_uint16_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_uint16_float32_m8(const rvd_uint16_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_uint16_float32_m4(r0.r1);
	res.r2 = mipp_cast_uint16_float32_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_cast_uint8_float32(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_cast_uint8_float32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_float32(r0);
}
inline rvd_float32_m2_t mipp_cast_uint8_float32_m2(const rvd_uint8_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_cast_uint8_float32_m1(r0.r1);
	res.r2 = mipp_cast_uint8_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_cast_uint8_float32_m4(const rvd_uint8_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_cast_uint8_float32_m2(r0.r1);
	res.r2 = mipp_cast_uint8_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_cast_uint8_float32_m8(const rvd_uint8_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_cast_uint8_float32_m4(r0.r1);
	res.r2 = mipp_cast_uint8_float32_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_float64_int64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_float64_int64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_float64_int64_m2(const rvd_float64_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_float64_int64_m1(r0.r1);
	res.r2 = mipp_cast_float64_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_float64_int64_m4(const rvd_float64_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_float64_int64_m2(r0.r1);
	res.r2 = mipp_cast_float64_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_float64_int64_m8(const rvd_float64_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_float64_int64_m4(r0.r1);
	res.r2 = mipp_cast_float64_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_float32_int64(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_float32_int64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_float32_int64_m2(const rvd_float32_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_float32_int64_m1(r0.r1);
	res.r2 = mipp_cast_float32_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_float32_int64_m4(const rvd_float32_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_float32_int64_m2(r0.r1);
	res.r2 = mipp_cast_float32_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_float32_int64_m8(const rvd_float32_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_float32_int64_m4(r0.r1);
	res.r2 = mipp_cast_float32_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_int64_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_int64_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_int64_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_int64_int64_m1(r0.r1);
	res.r2 = mipp_cast_int64_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_int64_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_int64_int64_m2(r0.r1);
	res.r2 = mipp_cast_int64_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_int64_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_int64_int64_m4(r0.r1);
	res.r2 = mipp_cast_int64_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_int32_int64(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_int32_int64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_int32_int64_m2(const rvd_int32_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_int32_int64_m1(r0.r1);
	res.r2 = mipp_cast_int32_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_int32_int64_m4(const rvd_int32_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_int32_int64_m2(r0.r1);
	res.r2 = mipp_cast_int32_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_int32_int64_m8(const rvd_int32_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_int32_int64_m4(r0.r1);
	res.r2 = mipp_cast_int32_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_int16_int64(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_int16_int64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_int16_int64_m2(const rvd_int16_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_int16_int64_m1(r0.r1);
	res.r2 = mipp_cast_int16_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_int16_int64_m4(const rvd_int16_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_int16_int64_m2(r0.r1);
	res.r2 = mipp_cast_int16_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_int16_int64_m8(const rvd_int16_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_int16_int64_m4(r0.r1);
	res.r2 = mipp_cast_int16_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_int8_int64(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_int8_int64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_int8_int64_m2(const rvd_int8_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_int8_int64_m1(r0.r1);
	res.r2 = mipp_cast_int8_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_int8_int64_m4(const rvd_int8_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_int8_int64_m2(r0.r1);
	res.r2 = mipp_cast_int8_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_int8_int64_m8(const rvd_int8_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_int8_int64_m4(r0.r1);
	res.r2 = mipp_cast_int8_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_uint64_int64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_uint64_int64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_uint64_int64_m2(const rvd_uint64_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_uint64_int64_m1(r0.r1);
	res.r2 = mipp_cast_uint64_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_uint64_int64_m4(const rvd_uint64_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_uint64_int64_m2(r0.r1);
	res.r2 = mipp_cast_uint64_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_uint64_int64_m8(const rvd_uint64_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_uint64_int64_m4(r0.r1);
	res.r2 = mipp_cast_uint64_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_uint32_int64(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_uint32_int64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_uint32_int64_m2(const rvd_uint32_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_uint32_int64_m1(r0.r1);
	res.r2 = mipp_cast_uint32_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_uint32_int64_m4(const rvd_uint32_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_uint32_int64_m2(r0.r1);
	res.r2 = mipp_cast_uint32_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_uint32_int64_m8(const rvd_uint32_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_uint32_int64_m4(r0.r1);
	res.r2 = mipp_cast_uint32_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_uint16_int64(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_uint16_int64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_uint16_int64_m2(const rvd_uint16_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_uint16_int64_m1(r0.r1);
	res.r2 = mipp_cast_uint16_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_uint16_int64_m4(const rvd_uint16_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_uint16_int64_m2(r0.r1);
	res.r2 = mipp_cast_uint16_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_uint16_int64_m8(const rvd_uint16_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_uint16_int64_m4(r0.r1);
	res.r2 = mipp_cast_uint16_int64_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_cast_uint8_int64(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_cast_uint8_int64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int64(r0);
}
inline rvd_int64_m2_t mipp_cast_uint8_int64_m2(const rvd_uint8_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_cast_uint8_int64_m1(r0.r1);
	res.r2 = mipp_cast_uint8_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_cast_uint8_int64_m4(const rvd_uint8_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_cast_uint8_int64_m2(r0.r1);
	res.r2 = mipp_cast_uint8_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_cast_uint8_int64_m8(const rvd_uint8_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_cast_uint8_int64_m4(r0.r1);
	res.r2 = mipp_cast_uint8_int64_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_float64_int32(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_float64_int32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_float64_int32_m2(const rvd_float64_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_float64_int32_m1(r0.r1);
	res.r2 = mipp_cast_float64_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_float64_int32_m4(const rvd_float64_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_float64_int32_m2(r0.r1);
	res.r2 = mipp_cast_float64_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_float64_int32_m8(const rvd_float64_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_float64_int32_m4(r0.r1);
	res.r2 = mipp_cast_float64_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_float32_int32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_float32_int32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_float32_int32_m2(const rvd_float32_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_float32_int32_m1(r0.r1);
	res.r2 = mipp_cast_float32_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_float32_int32_m4(const rvd_float32_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_float32_int32_m2(r0.r1);
	res.r2 = mipp_cast_float32_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_float32_int32_m8(const rvd_float32_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_float32_int32_m4(r0.r1);
	res.r2 = mipp_cast_float32_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_int64_int32(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_int64_int32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_int64_int32_m2(const rvd_int64_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_int64_int32_m1(r0.r1);
	res.r2 = mipp_cast_int64_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_int64_int32_m4(const rvd_int64_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_int64_int32_m2(r0.r1);
	res.r2 = mipp_cast_int64_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_int64_int32_m8(const rvd_int64_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_int64_int32_m4(r0.r1);
	res.r2 = mipp_cast_int64_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_int32_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_int32_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_int32_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_int32_int32_m1(r0.r1);
	res.r2 = mipp_cast_int32_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_int32_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_int32_int32_m2(r0.r1);
	res.r2 = mipp_cast_int32_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_int32_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_int32_int32_m4(r0.r1);
	res.r2 = mipp_cast_int32_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_int16_int32(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_int16_int32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_int16_int32_m2(const rvd_int16_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_int16_int32_m1(r0.r1);
	res.r2 = mipp_cast_int16_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_int16_int32_m4(const rvd_int16_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_int16_int32_m2(r0.r1);
	res.r2 = mipp_cast_int16_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_int16_int32_m8(const rvd_int16_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_int16_int32_m4(r0.r1);
	res.r2 = mipp_cast_int16_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_int8_int32(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_int8_int32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_int8_int32_m2(const rvd_int8_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_int8_int32_m1(r0.r1);
	res.r2 = mipp_cast_int8_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_int8_int32_m4(const rvd_int8_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_int8_int32_m2(r0.r1);
	res.r2 = mipp_cast_int8_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_int8_int32_m8(const rvd_int8_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_int8_int32_m4(r0.r1);
	res.r2 = mipp_cast_int8_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_uint64_int32(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_uint64_int32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_uint64_int32_m2(const rvd_uint64_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_uint64_int32_m1(r0.r1);
	res.r2 = mipp_cast_uint64_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_uint64_int32_m4(const rvd_uint64_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_uint64_int32_m2(r0.r1);
	res.r2 = mipp_cast_uint64_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_uint64_int32_m8(const rvd_uint64_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_uint64_int32_m4(r0.r1);
	res.r2 = mipp_cast_uint64_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_uint32_int32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_uint32_int32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_uint32_int32_m2(const rvd_uint32_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_uint32_int32_m1(r0.r1);
	res.r2 = mipp_cast_uint32_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_uint32_int32_m4(const rvd_uint32_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_uint32_int32_m2(r0.r1);
	res.r2 = mipp_cast_uint32_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_uint32_int32_m8(const rvd_uint32_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_uint32_int32_m4(r0.r1);
	res.r2 = mipp_cast_uint32_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_uint16_int32(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_uint16_int32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_uint16_int32_m2(const rvd_uint16_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_uint16_int32_m1(r0.r1);
	res.r2 = mipp_cast_uint16_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_uint16_int32_m4(const rvd_uint16_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_uint16_int32_m2(r0.r1);
	res.r2 = mipp_cast_uint16_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_uint16_int32_m8(const rvd_uint16_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_uint16_int32_m4(r0.r1);
	res.r2 = mipp_cast_uint16_int32_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_cast_uint8_int32(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_cast_uint8_int32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int32(r0);
}
inline rvd_int32_m2_t mipp_cast_uint8_int32_m2(const rvd_uint8_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_cast_uint8_int32_m1(r0.r1);
	res.r2 = mipp_cast_uint8_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_cast_uint8_int32_m4(const rvd_uint8_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_cast_uint8_int32_m2(r0.r1);
	res.r2 = mipp_cast_uint8_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_cast_uint8_int32_m8(const rvd_uint8_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_cast_uint8_int32_m4(r0.r1);
	res.r2 = mipp_cast_uint8_int32_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_float64_int16(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_float64_int16_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_float64_int16_m2(const rvd_float64_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_float64_int16_m1(r0.r1);
	res.r2 = mipp_cast_float64_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_float64_int16_m4(const rvd_float64_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_float64_int16_m2(r0.r1);
	res.r2 = mipp_cast_float64_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_float64_int16_m8(const rvd_float64_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_float64_int16_m4(r0.r1);
	res.r2 = mipp_cast_float64_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_float32_int16(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_float32_int16_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_float32_int16_m2(const rvd_float32_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_float32_int16_m1(r0.r1);
	res.r2 = mipp_cast_float32_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_float32_int16_m4(const rvd_float32_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_float32_int16_m2(r0.r1);
	res.r2 = mipp_cast_float32_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_float32_int16_m8(const rvd_float32_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_float32_int16_m4(r0.r1);
	res.r2 = mipp_cast_float32_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_int64_int16(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_int64_int16_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_int64_int16_m2(const rvd_int64_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_int64_int16_m1(r0.r1);
	res.r2 = mipp_cast_int64_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_int64_int16_m4(const rvd_int64_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_int64_int16_m2(r0.r1);
	res.r2 = mipp_cast_int64_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_int64_int16_m8(const rvd_int64_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_int64_int16_m4(r0.r1);
	res.r2 = mipp_cast_int64_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_int32_int16(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_int32_int16_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_int32_int16_m2(const rvd_int32_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_int32_int16_m1(r0.r1);
	res.r2 = mipp_cast_int32_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_int32_int16_m4(const rvd_int32_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_int32_int16_m2(r0.r1);
	res.r2 = mipp_cast_int32_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_int32_int16_m8(const rvd_int32_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_int32_int16_m4(r0.r1);
	res.r2 = mipp_cast_int32_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_int16_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_int16_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_int16_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_int16_int16_m1(r0.r1);
	res.r2 = mipp_cast_int16_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_int16_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_int16_int16_m2(r0.r1);
	res.r2 = mipp_cast_int16_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_int16_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_int16_int16_m4(r0.r1);
	res.r2 = mipp_cast_int16_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_int8_int16(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_int8_int16_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_int8_int16_m2(const rvd_int8_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_int8_int16_m1(r0.r1);
	res.r2 = mipp_cast_int8_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_int8_int16_m4(const rvd_int8_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_int8_int16_m2(r0.r1);
	res.r2 = mipp_cast_int8_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_int8_int16_m8(const rvd_int8_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_int8_int16_m4(r0.r1);
	res.r2 = mipp_cast_int8_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_uint64_int16(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_uint64_int16_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_uint64_int16_m2(const rvd_uint64_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_uint64_int16_m1(r0.r1);
	res.r2 = mipp_cast_uint64_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_uint64_int16_m4(const rvd_uint64_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_uint64_int16_m2(r0.r1);
	res.r2 = mipp_cast_uint64_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_uint64_int16_m8(const rvd_uint64_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_uint64_int16_m4(r0.r1);
	res.r2 = mipp_cast_uint64_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_uint32_int16(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_uint32_int16_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_uint32_int16_m2(const rvd_uint32_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_uint32_int16_m1(r0.r1);
	res.r2 = mipp_cast_uint32_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_uint32_int16_m4(const rvd_uint32_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_uint32_int16_m2(r0.r1);
	res.r2 = mipp_cast_uint32_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_uint32_int16_m8(const rvd_uint32_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_uint32_int16_m4(r0.r1);
	res.r2 = mipp_cast_uint32_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_uint16_int16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_uint16_int16_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_uint16_int16_m2(const rvd_uint16_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_uint16_int16_m1(r0.r1);
	res.r2 = mipp_cast_uint16_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_uint16_int16_m4(const rvd_uint16_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_uint16_int16_m2(r0.r1);
	res.r2 = mipp_cast_uint16_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_uint16_int16_m8(const rvd_uint16_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_uint16_int16_m4(r0.r1);
	res.r2 = mipp_cast_uint16_int16_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_cast_uint8_int16(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_cast_uint8_int16_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int16(r0);
}
inline rvd_int16_m2_t mipp_cast_uint8_int16_m2(const rvd_uint8_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_cast_uint8_int16_m1(r0.r1);
	res.r2 = mipp_cast_uint8_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_cast_uint8_int16_m4(const rvd_uint8_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_cast_uint8_int16_m2(r0.r1);
	res.r2 = mipp_cast_uint8_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_cast_uint8_int16_m8(const rvd_uint8_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_cast_uint8_int16_m4(r0.r1);
	res.r2 = mipp_cast_uint8_int16_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_float64_int8(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_float64_int8_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_float64_int8_m2(const rvd_float64_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_float64_int8_m1(r0.r1);
	res.r2 = mipp_cast_float64_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_float64_int8_m4(const rvd_float64_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_float64_int8_m2(r0.r1);
	res.r2 = mipp_cast_float64_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_float64_int8_m8(const rvd_float64_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_float64_int8_m4(r0.r1);
	res.r2 = mipp_cast_float64_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_float32_int8(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_float32_int8_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_float32_int8_m2(const rvd_float32_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_float32_int8_m1(r0.r1);
	res.r2 = mipp_cast_float32_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_float32_int8_m4(const rvd_float32_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_float32_int8_m2(r0.r1);
	res.r2 = mipp_cast_float32_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_float32_int8_m8(const rvd_float32_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_float32_int8_m4(r0.r1);
	res.r2 = mipp_cast_float32_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_int64_int8(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_int64_int8_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_int64_int8_m2(const rvd_int64_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_int64_int8_m1(r0.r1);
	res.r2 = mipp_cast_int64_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_int64_int8_m4(const rvd_int64_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_int64_int8_m2(r0.r1);
	res.r2 = mipp_cast_int64_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_int64_int8_m8(const rvd_int64_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_int64_int8_m4(r0.r1);
	res.r2 = mipp_cast_int64_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_int32_int8(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_int32_int8_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_int32_int8_m2(const rvd_int32_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_int32_int8_m1(r0.r1);
	res.r2 = mipp_cast_int32_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_int32_int8_m4(const rvd_int32_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_int32_int8_m2(r0.r1);
	res.r2 = mipp_cast_int32_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_int32_int8_m8(const rvd_int32_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_int32_int8_m4(r0.r1);
	res.r2 = mipp_cast_int32_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_int16_int8(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_int16_int8_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_int16_int8_m2(const rvd_int16_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_int16_int8_m1(r0.r1);
	res.r2 = mipp_cast_int16_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_int16_int8_m4(const rvd_int16_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_int16_int8_m2(r0.r1);
	res.r2 = mipp_cast_int16_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_int16_int8_m8(const rvd_int16_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_int16_int8_m4(r0.r1);
	res.r2 = mipp_cast_int16_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_int8_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_int8_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_int8_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_int8_int8_m1(r0.r1);
	res.r2 = mipp_cast_int8_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_int8_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_int8_int8_m2(r0.r1);
	res.r2 = mipp_cast_int8_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_int8_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_int8_int8_m4(r0.r1);
	res.r2 = mipp_cast_int8_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_uint64_int8(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_uint64_int8_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_uint64_int8_m2(const rvd_uint64_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_uint64_int8_m1(r0.r1);
	res.r2 = mipp_cast_uint64_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_uint64_int8_m4(const rvd_uint64_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_uint64_int8_m2(r0.r1);
	res.r2 = mipp_cast_uint64_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_uint64_int8_m8(const rvd_uint64_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_uint64_int8_m4(r0.r1);
	res.r2 = mipp_cast_uint64_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_uint32_int8(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_uint32_int8_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_uint32_int8_m2(const rvd_uint32_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_uint32_int8_m1(r0.r1);
	res.r2 = mipp_cast_uint32_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_uint32_int8_m4(const rvd_uint32_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_uint32_int8_m2(r0.r1);
	res.r2 = mipp_cast_uint32_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_uint32_int8_m8(const rvd_uint32_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_uint32_int8_m4(r0.r1);
	res.r2 = mipp_cast_uint32_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_uint16_int8(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_uint16_int8_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_uint16_int8_m2(const rvd_uint16_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_uint16_int8_m1(r0.r1);
	res.r2 = mipp_cast_uint16_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_uint16_int8_m4(const rvd_uint16_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_uint16_int8_m2(r0.r1);
	res.r2 = mipp_cast_uint16_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_uint16_int8_m8(const rvd_uint16_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_uint16_int8_m4(r0.r1);
	res.r2 = mipp_cast_uint16_int8_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_cast_uint8_int8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_cast_uint8_int8_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_int8(r0);
}
inline rvd_int8_m2_t mipp_cast_uint8_int8_m2(const rvd_uint8_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_cast_uint8_int8_m1(r0.r1);
	res.r2 = mipp_cast_uint8_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_cast_uint8_int8_m4(const rvd_uint8_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_cast_uint8_int8_m2(r0.r1);
	res.r2 = mipp_cast_uint8_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_cast_uint8_int8_m8(const rvd_uint8_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_cast_uint8_int8_m4(r0.r1);
	res.r2 = mipp_cast_uint8_int8_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_float64_uint64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_float64_uint64_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_float64_uint64_m2(const rvd_float64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_float64_uint64_m1(r0.r1);
	res.r2 = mipp_cast_float64_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_float64_uint64_m4(const rvd_float64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_float64_uint64_m2(r0.r1);
	res.r2 = mipp_cast_float64_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_float64_uint64_m8(const rvd_float64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_float64_uint64_m4(r0.r1);
	res.r2 = mipp_cast_float64_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_float32_uint64(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_float32_uint64_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_float32_uint64_m2(const rvd_float32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_float32_uint64_m1(r0.r1);
	res.r2 = mipp_cast_float32_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_float32_uint64_m4(const rvd_float32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_float32_uint64_m2(r0.r1);
	res.r2 = mipp_cast_float32_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_float32_uint64_m8(const rvd_float32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_float32_uint64_m4(r0.r1);
	res.r2 = mipp_cast_float32_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_int64_uint64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_int64_uint64_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_int64_uint64_m2(const rvd_int64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_int64_uint64_m1(r0.r1);
	res.r2 = mipp_cast_int64_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_int64_uint64_m4(const rvd_int64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_int64_uint64_m2(r0.r1);
	res.r2 = mipp_cast_int64_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_int64_uint64_m8(const rvd_int64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_int64_uint64_m4(r0.r1);
	res.r2 = mipp_cast_int64_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_int32_uint64(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_int32_uint64_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_int32_uint64_m2(const rvd_int32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_int32_uint64_m1(r0.r1);
	res.r2 = mipp_cast_int32_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_int32_uint64_m4(const rvd_int32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_int32_uint64_m2(r0.r1);
	res.r2 = mipp_cast_int32_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_int32_uint64_m8(const rvd_int32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_int32_uint64_m4(r0.r1);
	res.r2 = mipp_cast_int32_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_int16_uint64(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_int16_uint64_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_int16_uint64_m2(const rvd_int16_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_int16_uint64_m1(r0.r1);
	res.r2 = mipp_cast_int16_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_int16_uint64_m4(const rvd_int16_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_int16_uint64_m2(r0.r1);
	res.r2 = mipp_cast_int16_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_int16_uint64_m8(const rvd_int16_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_int16_uint64_m4(r0.r1);
	res.r2 = mipp_cast_int16_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_int8_uint64(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_int8_uint64_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_int8_uint64_m2(const rvd_int8_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_int8_uint64_m1(r0.r1);
	res.r2 = mipp_cast_int8_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_int8_uint64_m4(const rvd_int8_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_int8_uint64_m2(r0.r1);
	res.r2 = mipp_cast_int8_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_int8_uint64_m8(const rvd_int8_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_int8_uint64_m4(r0.r1);
	res.r2 = mipp_cast_int8_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_uint64_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_uint64_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_uint64_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_uint64_uint64_m1(r0.r1);
	res.r2 = mipp_cast_uint64_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_uint64_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_uint64_uint64_m2(r0.r1);
	res.r2 = mipp_cast_uint64_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_uint64_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_uint64_uint64_m4(r0.r1);
	res.r2 = mipp_cast_uint64_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_uint32_uint64(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_uint32_uint64_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_uint32_uint64_m2(const rvd_uint32_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_uint32_uint64_m1(r0.r1);
	res.r2 = mipp_cast_uint32_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_uint32_uint64_m4(const rvd_uint32_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_uint32_uint64_m2(r0.r1);
	res.r2 = mipp_cast_uint32_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_uint32_uint64_m8(const rvd_uint32_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_uint32_uint64_m4(r0.r1);
	res.r2 = mipp_cast_uint32_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_uint16_uint64(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_uint16_uint64_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_uint16_uint64_m2(const rvd_uint16_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_uint16_uint64_m1(r0.r1);
	res.r2 = mipp_cast_uint16_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_uint16_uint64_m4(const rvd_uint16_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_uint16_uint64_m2(r0.r1);
	res.r2 = mipp_cast_uint16_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_uint16_uint64_m8(const rvd_uint16_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_uint16_uint64_m4(r0.r1);
	res.r2 = mipp_cast_uint16_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_cast_uint8_uint64(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_cast_uint8_uint64_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint64(r0);
}
inline rvd_uint64_m2_t mipp_cast_uint8_uint64_m2(const rvd_uint8_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_cast_uint8_uint64_m1(r0.r1);
	res.r2 = mipp_cast_uint8_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_cast_uint8_uint64_m4(const rvd_uint8_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_cast_uint8_uint64_m2(r0.r1);
	res.r2 = mipp_cast_uint8_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_cast_uint8_uint64_m8(const rvd_uint8_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_cast_uint8_uint64_m4(r0.r1);
	res.r2 = mipp_cast_uint8_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_float64_uint32(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_float64_uint32_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_float64_uint32_m2(const rvd_float64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_float64_uint32_m1(r0.r1);
	res.r2 = mipp_cast_float64_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_float64_uint32_m4(const rvd_float64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_float64_uint32_m2(r0.r1);
	res.r2 = mipp_cast_float64_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_float64_uint32_m8(const rvd_float64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_float64_uint32_m4(r0.r1);
	res.r2 = mipp_cast_float64_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_float32_uint32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_float32_uint32_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_float32_uint32_m2(const rvd_float32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_float32_uint32_m1(r0.r1);
	res.r2 = mipp_cast_float32_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_float32_uint32_m4(const rvd_float32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_float32_uint32_m2(r0.r1);
	res.r2 = mipp_cast_float32_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_float32_uint32_m8(const rvd_float32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_float32_uint32_m4(r0.r1);
	res.r2 = mipp_cast_float32_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_int64_uint32(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_int64_uint32_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_int64_uint32_m2(const rvd_int64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_int64_uint32_m1(r0.r1);
	res.r2 = mipp_cast_int64_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_int64_uint32_m4(const rvd_int64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_int64_uint32_m2(r0.r1);
	res.r2 = mipp_cast_int64_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_int64_uint32_m8(const rvd_int64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_int64_uint32_m4(r0.r1);
	res.r2 = mipp_cast_int64_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_int32_uint32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_int32_uint32_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_int32_uint32_m2(const rvd_int32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_int32_uint32_m1(r0.r1);
	res.r2 = mipp_cast_int32_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_int32_uint32_m4(const rvd_int32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_int32_uint32_m2(r0.r1);
	res.r2 = mipp_cast_int32_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_int32_uint32_m8(const rvd_int32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_int32_uint32_m4(r0.r1);
	res.r2 = mipp_cast_int32_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_int16_uint32(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_int16_uint32_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_int16_uint32_m2(const rvd_int16_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_int16_uint32_m1(r0.r1);
	res.r2 = mipp_cast_int16_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_int16_uint32_m4(const rvd_int16_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_int16_uint32_m2(r0.r1);
	res.r2 = mipp_cast_int16_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_int16_uint32_m8(const rvd_int16_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_int16_uint32_m4(r0.r1);
	res.r2 = mipp_cast_int16_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_int8_uint32(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_int8_uint32_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_int8_uint32_m2(const rvd_int8_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_int8_uint32_m1(r0.r1);
	res.r2 = mipp_cast_int8_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_int8_uint32_m4(const rvd_int8_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_int8_uint32_m2(r0.r1);
	res.r2 = mipp_cast_int8_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_int8_uint32_m8(const rvd_int8_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_int8_uint32_m4(r0.r1);
	res.r2 = mipp_cast_int8_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_uint64_uint32(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_uint64_uint32_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_uint64_uint32_m2(const rvd_uint64_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_uint64_uint32_m1(r0.r1);
	res.r2 = mipp_cast_uint64_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_uint64_uint32_m4(const rvd_uint64_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_uint64_uint32_m2(r0.r1);
	res.r2 = mipp_cast_uint64_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_uint64_uint32_m8(const rvd_uint64_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_uint64_uint32_m4(r0.r1);
	res.r2 = mipp_cast_uint64_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_uint32_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_uint32_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_uint32_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_uint32_uint32_m1(r0.r1);
	res.r2 = mipp_cast_uint32_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_uint32_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_uint32_uint32_m2(r0.r1);
	res.r2 = mipp_cast_uint32_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_uint32_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_uint32_uint32_m4(r0.r1);
	res.r2 = mipp_cast_uint32_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_uint16_uint32(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_uint16_uint32_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_uint16_uint32_m2(const rvd_uint16_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_uint16_uint32_m1(r0.r1);
	res.r2 = mipp_cast_uint16_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_uint16_uint32_m4(const rvd_uint16_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_uint16_uint32_m2(r0.r1);
	res.r2 = mipp_cast_uint16_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_uint16_uint32_m8(const rvd_uint16_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_uint16_uint32_m4(r0.r1);
	res.r2 = mipp_cast_uint16_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_cast_uint8_uint32(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_cast_uint8_uint32_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint32(r0);
}
inline rvd_uint32_m2_t mipp_cast_uint8_uint32_m2(const rvd_uint8_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_cast_uint8_uint32_m1(r0.r1);
	res.r2 = mipp_cast_uint8_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_cast_uint8_uint32_m4(const rvd_uint8_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_cast_uint8_uint32_m2(r0.r1);
	res.r2 = mipp_cast_uint8_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_cast_uint8_uint32_m8(const rvd_uint8_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_cast_uint8_uint32_m4(r0.r1);
	res.r2 = mipp_cast_uint8_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_float64_uint16(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_float64_uint16_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_float64_uint16_m2(const rvd_float64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_float64_uint16_m1(r0.r1);
	res.r2 = mipp_cast_float64_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_float64_uint16_m4(const rvd_float64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_float64_uint16_m2(r0.r1);
	res.r2 = mipp_cast_float64_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_float64_uint16_m8(const rvd_float64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_float64_uint16_m4(r0.r1);
	res.r2 = mipp_cast_float64_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_float32_uint16(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_float32_uint16_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_float32_uint16_m2(const rvd_float32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_float32_uint16_m1(r0.r1);
	res.r2 = mipp_cast_float32_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_float32_uint16_m4(const rvd_float32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_float32_uint16_m2(r0.r1);
	res.r2 = mipp_cast_float32_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_float32_uint16_m8(const rvd_float32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_float32_uint16_m4(r0.r1);
	res.r2 = mipp_cast_float32_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_int64_uint16(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_int64_uint16_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_int64_uint16_m2(const rvd_int64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_int64_uint16_m1(r0.r1);
	res.r2 = mipp_cast_int64_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_int64_uint16_m4(const rvd_int64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_int64_uint16_m2(r0.r1);
	res.r2 = mipp_cast_int64_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_int64_uint16_m8(const rvd_int64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_int64_uint16_m4(r0.r1);
	res.r2 = mipp_cast_int64_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_int32_uint16(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_int32_uint16_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_int32_uint16_m2(const rvd_int32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_int32_uint16_m1(r0.r1);
	res.r2 = mipp_cast_int32_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_int32_uint16_m4(const rvd_int32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_int32_uint16_m2(r0.r1);
	res.r2 = mipp_cast_int32_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_int32_uint16_m8(const rvd_int32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_int32_uint16_m4(r0.r1);
	res.r2 = mipp_cast_int32_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_int16_uint16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_int16_uint16_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_int16_uint16_m2(const rvd_int16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_int16_uint16_m1(r0.r1);
	res.r2 = mipp_cast_int16_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_int16_uint16_m4(const rvd_int16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_int16_uint16_m2(r0.r1);
	res.r2 = mipp_cast_int16_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_int16_uint16_m8(const rvd_int16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_int16_uint16_m4(r0.r1);
	res.r2 = mipp_cast_int16_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_int8_uint16(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_int8_uint16_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_int8_uint16_m2(const rvd_int8_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_int8_uint16_m1(r0.r1);
	res.r2 = mipp_cast_int8_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_int8_uint16_m4(const rvd_int8_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_int8_uint16_m2(r0.r1);
	res.r2 = mipp_cast_int8_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_int8_uint16_m8(const rvd_int8_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_int8_uint16_m4(r0.r1);
	res.r2 = mipp_cast_int8_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_uint64_uint16(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_uint64_uint16_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_uint64_uint16_m2(const rvd_uint64_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_uint64_uint16_m1(r0.r1);
	res.r2 = mipp_cast_uint64_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_uint64_uint16_m4(const rvd_uint64_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_uint64_uint16_m2(r0.r1);
	res.r2 = mipp_cast_uint64_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_uint64_uint16_m8(const rvd_uint64_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_uint64_uint16_m4(r0.r1);
	res.r2 = mipp_cast_uint64_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_uint32_uint16(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_uint32_uint16_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_uint32_uint16_m2(const rvd_uint32_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_uint32_uint16_m1(r0.r1);
	res.r2 = mipp_cast_uint32_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_uint32_uint16_m4(const rvd_uint32_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_uint32_uint16_m2(r0.r1);
	res.r2 = mipp_cast_uint32_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_uint32_uint16_m8(const rvd_uint32_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_uint32_uint16_m4(r0.r1);
	res.r2 = mipp_cast_uint32_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_uint16_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_uint16_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_uint16_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_uint16_uint16_m1(r0.r1);
	res.r2 = mipp_cast_uint16_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_uint16_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_uint16_uint16_m2(r0.r1);
	res.r2 = mipp_cast_uint16_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_uint16_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_uint16_uint16_m4(r0.r1);
	res.r2 = mipp_cast_uint16_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_cast_uint8_uint16(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_cast_uint8_uint16_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint16(r0);
}
inline rvd_uint16_m2_t mipp_cast_uint8_uint16_m2(const rvd_uint8_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_cast_uint8_uint16_m1(r0.r1);
	res.r2 = mipp_cast_uint8_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_cast_uint8_uint16_m4(const rvd_uint8_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_cast_uint8_uint16_m2(r0.r1);
	res.r2 = mipp_cast_uint8_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_cast_uint8_uint16_m8(const rvd_uint8_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_cast_uint8_uint16_m4(r0.r1);
	res.r2 = mipp_cast_uint8_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_float64_uint8(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float64_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float64_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float64_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_float64_uint8_m1(const rvd_float64_m1_t r0) {
	return mipp_cast_float64_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_float64_uint8_m2(const rvd_float64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_float64_uint8_m1(r0.r1);
	res.r2 = mipp_cast_float64_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_float64_uint8_m4(const rvd_float64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_float64_uint8_m2(r0.r1);
	res.r2 = mipp_cast_float64_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_float64_uint8_m8(const rvd_float64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_float64_uint8_m4(r0.r1);
	res.r2 = mipp_cast_float64_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_float32_uint8(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_float32_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_float32_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_float32_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_float32_uint8_m1(const rvd_float32_m1_t r0) {
	return mipp_cast_float32_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_float32_uint8_m2(const rvd_float32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_float32_uint8_m1(r0.r1);
	res.r2 = mipp_cast_float32_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_float32_uint8_m4(const rvd_float32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_float32_uint8_m2(r0.r1);
	res.r2 = mipp_cast_float32_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_float32_uint8_m8(const rvd_float32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_float32_uint8_m4(r0.r1);
	res.r2 = mipp_cast_float32_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_int64_uint8(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int64_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int64_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int64_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_int64_uint8_m1(const rvd_int64_m1_t r0) {
	return mipp_cast_int64_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_int64_uint8_m2(const rvd_int64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_int64_uint8_m1(r0.r1);
	res.r2 = mipp_cast_int64_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_int64_uint8_m4(const rvd_int64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_int64_uint8_m2(r0.r1);
	res.r2 = mipp_cast_int64_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_int64_uint8_m8(const rvd_int64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_int64_uint8_m4(r0.r1);
	res.r2 = mipp_cast_int64_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_int32_uint8(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int32_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int32_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int32_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_int32_uint8_m1(const rvd_int32_m1_t r0) {
	return mipp_cast_int32_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_int32_uint8_m2(const rvd_int32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_int32_uint8_m1(r0.r1);
	res.r2 = mipp_cast_int32_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_int32_uint8_m4(const rvd_int32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_int32_uint8_m2(r0.r1);
	res.r2 = mipp_cast_int32_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_int32_uint8_m8(const rvd_int32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_int32_uint8_m4(r0.r1);
	res.r2 = mipp_cast_int32_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_int16_uint8(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int16_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int16_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int16_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_int16_uint8_m1(const rvd_int16_m1_t r0) {
	return mipp_cast_int16_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_int16_uint8_m2(const rvd_int16_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_int16_uint8_m1(r0.r1);
	res.r2 = mipp_cast_int16_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_int16_uint8_m4(const rvd_int16_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_int16_uint8_m2(r0.r1);
	res.r2 = mipp_cast_int16_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_int16_uint8_m8(const rvd_int16_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_int16_uint8_m4(r0.r1);
	res.r2 = mipp_cast_int16_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_int8_uint8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_int8_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_int8_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_int8_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_int8_uint8_m1(const rvd_int8_m1_t r0) {
	return mipp_cast_int8_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_int8_uint8_m2(const rvd_int8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_int8_uint8_m1(r0.r1);
	res.r2 = mipp_cast_int8_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_int8_uint8_m4(const rvd_int8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_int8_uint8_m2(r0.r1);
	res.r2 = mipp_cast_int8_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_int8_uint8_m8(const rvd_int8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_int8_uint8_m4(r0.r1);
	res.r2 = mipp_cast_int8_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_uint64_uint8(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint64_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint64_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint64_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_uint64_uint8_m1(const rvd_uint64_m1_t r0) {
	return mipp_cast_uint64_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_uint64_uint8_m2(const rvd_uint64_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_uint64_uint8_m1(r0.r1);
	res.r2 = mipp_cast_uint64_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_uint64_uint8_m4(const rvd_uint64_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_uint64_uint8_m2(r0.r1);
	res.r2 = mipp_cast_uint64_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_uint64_uint8_m8(const rvd_uint64_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_uint64_uint8_m4(r0.r1);
	res.r2 = mipp_cast_uint64_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_uint32_uint8(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint32_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint32_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint32_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_uint32_uint8_m1(const rvd_uint32_m1_t r0) {
	return mipp_cast_uint32_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_uint32_uint8_m2(const rvd_uint32_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_uint32_uint8_m1(r0.r1);
	res.r2 = mipp_cast_uint32_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_uint32_uint8_m4(const rvd_uint32_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_uint32_uint8_m2(r0.r1);
	res.r2 = mipp_cast_uint32_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_uint32_uint8_m8(const rvd_uint32_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_uint32_uint8_m4(r0.r1);
	res.r2 = mipp_cast_uint32_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_uint16_uint8(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint16_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint16_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint16_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_uint16_uint8_m1(const rvd_uint16_m1_t r0) {
	return mipp_cast_uint16_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_uint16_uint8_m2(const rvd_uint16_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_uint16_uint8_m1(r0.r1);
	res.r2 = mipp_cast_uint16_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_uint16_uint8_m4(const rvd_uint16_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_uint16_uint8_m2(r0.r1);
	res.r2 = mipp_cast_uint16_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_uint16_uint8_m8(const rvd_uint16_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_uint16_uint8_m4(r0.r1);
	res.r2 = mipp_cast_uint16_uint8_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_cast_uint8_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_uint8_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_cast_uint8_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_cast_uint8_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_cast_uint8_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_cast_uint8_uint8(r0);
}
inline rvd_uint8_m2_t mipp_cast_uint8_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_cast_uint8_uint8_m1(r0.r1);
	res.r2 = mipp_cast_uint8_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_cast_uint8_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_cast_uint8_uint8_m2(r0.r1);
	res.r2 = mipp_cast_uint8_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_cast_uint8_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_cast_uint8_uint8_m4(r0.r1);
	res.r2 = mipp_cast_uint8_uint8_m4(r0.r2);
	return res;
}
inline rvm_float64_t mipp_cast_k_float64_float64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_float64_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_float64_float64_m2(const rvm_float64_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_float64_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_float64_float64_m4(const rvm_float64_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_float64_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_float64_float64_m8(const rvm_float64_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_float64_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_float32_float64(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_float32_float64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_float32_float64_m2(const rvm_float32_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_float32_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_float32_float64_m4(const rvm_float32_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_float32_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_float32_float64_m8(const rvm_float32_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_float32_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_int64_float64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_int64_float64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_int64_float64_m2(const rvm_int64_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_int64_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_int64_float64_m4(const rvm_int64_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_int64_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_int64_float64_m8(const rvm_int64_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_int64_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_int32_float64(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_int32_float64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_int32_float64_m2(const rvm_int32_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_int32_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_int32_float64_m4(const rvm_int32_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_int32_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_int32_float64_m8(const rvm_int32_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_int32_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_int16_float64(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_int16_float64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_int16_float64_m2(const rvm_int16_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_int16_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_int16_float64_m4(const rvm_int16_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_int16_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_int16_float64_m8(const rvm_int16_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_int16_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_int8_float64(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_int8_float64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_int8_float64_m2(const rvm_int8_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_int8_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_int8_float64_m4(const rvm_int8_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_int8_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_int8_float64_m8(const rvm_int8_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_int8_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_uint64_float64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_uint64_float64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_uint64_float64_m2(const rvm_uint64_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_uint64_float64_m4(const rvm_uint64_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_uint64_float64_m8(const rvm_uint64_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_uint32_float64(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_uint32_float64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_uint32_float64_m2(const rvm_uint32_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_uint32_float64_m4(const rvm_uint32_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_uint32_float64_m8(const rvm_uint32_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_uint16_float64(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_uint16_float64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_uint16_float64_m2(const rvm_uint16_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_uint16_float64_m4(const rvm_uint16_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_uint16_float64_m8(const rvm_uint16_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float64_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cast_k_uint8_float64(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_cast_k_uint8_float64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_float64(m0);
}
inline rvm_float64_m2_t mipp_cast_k_uint8_float64_m2(const rvm_uint8_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_float64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_cast_k_uint8_float64_m4(const rvm_uint8_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_float64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_cast_k_uint8_float64_m8(const rvm_uint8_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_float64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float64_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_float64_float32(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_float64_float32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_float64_float32_m2(const rvm_float64_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_float64_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_float64_float32_m4(const rvm_float64_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_float64_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_float64_float32_m8(const rvm_float64_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_float64_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_float32_float32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_float32_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_float32_float32_m2(const rvm_float32_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_float32_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_float32_float32_m4(const rvm_float32_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_float32_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_float32_float32_m8(const rvm_float32_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_float32_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_int64_float32(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_int64_float32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_int64_float32_m2(const rvm_int64_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_int64_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_int64_float32_m4(const rvm_int64_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_int64_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_int64_float32_m8(const rvm_int64_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_int64_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_int32_float32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_int32_float32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_int32_float32_m2(const rvm_int32_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_int32_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_int32_float32_m4(const rvm_int32_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_int32_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_int32_float32_m8(const rvm_int32_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_int32_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_int16_float32(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_int16_float32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_int16_float32_m2(const rvm_int16_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_int16_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_int16_float32_m4(const rvm_int16_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_int16_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_int16_float32_m8(const rvm_int16_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_int16_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_int8_float32(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_int8_float32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_int8_float32_m2(const rvm_int8_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_int8_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_int8_float32_m4(const rvm_int8_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_int8_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_int8_float32_m8(const rvm_int8_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_int8_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_uint64_float32(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_uint64_float32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_uint64_float32_m2(const rvm_uint64_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_uint64_float32_m4(const rvm_uint64_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_uint64_float32_m8(const rvm_uint64_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_uint32_float32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_uint32_float32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_uint32_float32_m2(const rvm_uint32_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_uint32_float32_m4(const rvm_uint32_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_uint32_float32_m8(const rvm_uint32_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_uint16_float32(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_uint16_float32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_uint16_float32_m2(const rvm_uint16_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_uint16_float32_m4(const rvm_uint16_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_uint16_float32_m8(const rvm_uint16_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_float32_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_cast_k_uint8_float32(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_cast_k_uint8_float32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_float32(m0);
}
inline rvm_float32_m2_t mipp_cast_k_uint8_float32_m2(const rvm_uint8_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_float32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_cast_k_uint8_float32_m4(const rvm_uint8_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_float32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_cast_k_uint8_float32_m8(const rvm_uint8_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_float32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_float32_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_float64_int64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_float64_int64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_float64_int64_m2(const rvm_float64_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_float64_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_float64_int64_m4(const rvm_float64_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_float64_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_float64_int64_m8(const rvm_float64_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_float64_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_float32_int64(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_float32_int64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_float32_int64_m2(const rvm_float32_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_float32_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_float32_int64_m4(const rvm_float32_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_float32_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_float32_int64_m8(const rvm_float32_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_float32_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_int64_int64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_int64_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_int64_int64_m2(const rvm_int64_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_int64_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_int64_int64_m4(const rvm_int64_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_int64_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_int64_int64_m8(const rvm_int64_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_int64_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_int32_int64(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_int32_int64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_int32_int64_m2(const rvm_int32_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_int32_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_int32_int64_m4(const rvm_int32_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_int32_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_int32_int64_m8(const rvm_int32_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_int32_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_int16_int64(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_int16_int64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_int16_int64_m2(const rvm_int16_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_int16_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_int16_int64_m4(const rvm_int16_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_int16_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_int16_int64_m8(const rvm_int16_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_int16_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_int8_int64(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_int8_int64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_int8_int64_m2(const rvm_int8_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_int8_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_int8_int64_m4(const rvm_int8_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_int8_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_int8_int64_m8(const rvm_int8_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_int8_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_uint64_int64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_uint64_int64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_uint64_int64_m2(const rvm_uint64_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_uint64_int64_m4(const rvm_uint64_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_uint64_int64_m8(const rvm_uint64_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_uint32_int64(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_uint32_int64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_uint32_int64_m2(const rvm_uint32_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_uint32_int64_m4(const rvm_uint32_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_uint32_int64_m8(const rvm_uint32_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_uint16_int64(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_uint16_int64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_uint16_int64_m2(const rvm_uint16_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_uint16_int64_m4(const rvm_uint16_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_uint16_int64_m8(const rvm_uint16_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int64_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_cast_k_uint8_int64(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_cast_k_uint8_int64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int64(m0);
}
inline rvm_int64_m2_t mipp_cast_k_uint8_int64_m2(const rvm_uint8_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_int64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_cast_k_uint8_int64_m4(const rvm_uint8_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_int64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_cast_k_uint8_int64_m8(const rvm_uint8_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_int64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int64_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_float64_int32(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_float64_int32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_float64_int32_m2(const rvm_float64_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_float64_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_float64_int32_m4(const rvm_float64_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_float64_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_float64_int32_m8(const rvm_float64_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_float64_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_float32_int32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_float32_int32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_float32_int32_m2(const rvm_float32_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_float32_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_float32_int32_m4(const rvm_float32_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_float32_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_float32_int32_m8(const rvm_float32_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_float32_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_int64_int32(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_int64_int32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_int64_int32_m2(const rvm_int64_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_int64_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_int64_int32_m4(const rvm_int64_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_int64_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_int64_int32_m8(const rvm_int64_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_int64_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_int32_int32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_int32_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_int32_int32_m2(const rvm_int32_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_int32_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_int32_int32_m4(const rvm_int32_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_int32_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_int32_int32_m8(const rvm_int32_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_int32_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_int16_int32(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_int16_int32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_int16_int32_m2(const rvm_int16_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_int16_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_int16_int32_m4(const rvm_int16_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_int16_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_int16_int32_m8(const rvm_int16_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_int16_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_int8_int32(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_int8_int32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_int8_int32_m2(const rvm_int8_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_int8_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_int8_int32_m4(const rvm_int8_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_int8_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_int8_int32_m8(const rvm_int8_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_int8_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_uint64_int32(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_uint64_int32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_uint64_int32_m2(const rvm_uint64_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_uint64_int32_m4(const rvm_uint64_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_uint64_int32_m8(const rvm_uint64_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_uint32_int32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_uint32_int32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_uint32_int32_m2(const rvm_uint32_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_uint32_int32_m4(const rvm_uint32_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_uint32_int32_m8(const rvm_uint32_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_uint16_int32(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_uint16_int32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_uint16_int32_m2(const rvm_uint16_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_uint16_int32_m4(const rvm_uint16_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_uint16_int32_m8(const rvm_uint16_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int32_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_cast_k_uint8_int32(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_cast_k_uint8_int32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int32(m0);
}
inline rvm_int32_m2_t mipp_cast_k_uint8_int32_m2(const rvm_uint8_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_int32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_cast_k_uint8_int32_m4(const rvm_uint8_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_int32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_cast_k_uint8_int32_m8(const rvm_uint8_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_int32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int32_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_float64_int16(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_float64_int16_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_float64_int16_m2(const rvm_float64_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_float64_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_float64_int16_m4(const rvm_float64_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_float64_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_float64_int16_m8(const rvm_float64_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_float64_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_float32_int16(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_float32_int16_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_float32_int16_m2(const rvm_float32_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_float32_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_float32_int16_m4(const rvm_float32_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_float32_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_float32_int16_m8(const rvm_float32_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_float32_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_int64_int16(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_int64_int16_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_int64_int16_m2(const rvm_int64_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_int64_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_int64_int16_m4(const rvm_int64_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_int64_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_int64_int16_m8(const rvm_int64_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_int64_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_int32_int16(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_int32_int16_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_int32_int16_m2(const rvm_int32_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_int32_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_int32_int16_m4(const rvm_int32_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_int32_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_int32_int16_m8(const rvm_int32_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_int32_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_int16_int16(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_int16_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_int16_int16_m2(const rvm_int16_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_int16_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_int16_int16_m4(const rvm_int16_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_int16_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_int16_int16_m8(const rvm_int16_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_int16_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_int8_int16(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_int8_int16_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_int8_int16_m2(const rvm_int8_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_int8_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_int8_int16_m4(const rvm_int8_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_int8_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_int8_int16_m8(const rvm_int8_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_int8_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_uint64_int16(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_uint64_int16_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_uint64_int16_m2(const rvm_uint64_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_uint64_int16_m4(const rvm_uint64_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_uint64_int16_m8(const rvm_uint64_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_uint32_int16(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_uint32_int16_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_uint32_int16_m2(const rvm_uint32_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_uint32_int16_m4(const rvm_uint32_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_uint32_int16_m8(const rvm_uint32_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_uint16_int16(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_uint16_int16_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_uint16_int16_m2(const rvm_uint16_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_uint16_int16_m4(const rvm_uint16_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_uint16_int16_m8(const rvm_uint16_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int16_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_cast_k_uint8_int16(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_cast_k_uint8_int16_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int16(m0);
}
inline rvm_int16_m2_t mipp_cast_k_uint8_int16_m2(const rvm_uint8_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_int16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_cast_k_uint8_int16_m4(const rvm_uint8_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_int16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_cast_k_uint8_int16_m8(const rvm_uint8_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_int16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int16_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_float64_int8(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_float64_int8_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_float64_int8_m2(const rvm_float64_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_float64_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_float64_int8_m4(const rvm_float64_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_float64_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_float64_int8_m8(const rvm_float64_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_float64_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_float32_int8(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_float32_int8_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_float32_int8_m2(const rvm_float32_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_float32_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_float32_int8_m4(const rvm_float32_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_float32_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_float32_int8_m8(const rvm_float32_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_float32_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_int64_int8(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_int64_int8_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_int64_int8_m2(const rvm_int64_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_int64_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_int64_int8_m4(const rvm_int64_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_int64_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_int64_int8_m8(const rvm_int64_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_int64_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_int32_int8(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_int32_int8_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_int32_int8_m2(const rvm_int32_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_int32_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_int32_int8_m4(const rvm_int32_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_int32_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_int32_int8_m8(const rvm_int32_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_int32_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_int16_int8(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_int16_int8_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_int16_int8_m2(const rvm_int16_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_int16_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_int16_int8_m4(const rvm_int16_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_int16_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_int16_int8_m8(const rvm_int16_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_int16_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_int8_int8(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_int8_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_int8_int8_m2(const rvm_int8_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_int8_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_int8_int8_m4(const rvm_int8_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_int8_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_int8_int8_m8(const rvm_int8_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_int8_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_uint64_int8(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_uint64_int8_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_uint64_int8_m2(const rvm_uint64_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_uint64_int8_m4(const rvm_uint64_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_uint64_int8_m8(const rvm_uint64_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_uint32_int8(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_uint32_int8_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_uint32_int8_m2(const rvm_uint32_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_uint32_int8_m4(const rvm_uint32_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_uint32_int8_m8(const rvm_uint32_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_uint16_int8(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_uint16_int8_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_uint16_int8_m2(const rvm_uint16_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_uint16_int8_m4(const rvm_uint16_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_uint16_int8_m8(const rvm_uint16_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_int8_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_cast_k_uint8_int8(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_cast_k_uint8_int8_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_int8(m0);
}
inline rvm_int8_m2_t mipp_cast_k_uint8_int8_m2(const rvm_uint8_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_int8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_cast_k_uint8_int8_m4(const rvm_uint8_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_int8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_cast_k_uint8_int8_m8(const rvm_uint8_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_int8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_int8_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_float64_uint64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_float64_uint64_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_float64_uint64_m2(const rvm_float64_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_float64_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_float64_uint64_m4(const rvm_float64_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_float64_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_float64_uint64_m8(const rvm_float64_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_float64_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_float32_uint64(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_float32_uint64_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_float32_uint64_m2(const rvm_float32_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_float32_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_float32_uint64_m4(const rvm_float32_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_float32_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_float32_uint64_m8(const rvm_float32_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_float32_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_int64_uint64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_int64_uint64_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_int64_uint64_m2(const rvm_int64_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_int64_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_int64_uint64_m4(const rvm_int64_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_int64_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_int64_uint64_m8(const rvm_int64_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_int64_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_int32_uint64(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_int32_uint64_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_int32_uint64_m2(const rvm_int32_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_int32_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_int32_uint64_m4(const rvm_int32_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_int32_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_int32_uint64_m8(const rvm_int32_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_int32_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_int16_uint64(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_int16_uint64_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_int16_uint64_m2(const rvm_int16_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_int16_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_int16_uint64_m4(const rvm_int16_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_int16_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_int16_uint64_m8(const rvm_int16_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_int16_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_int8_uint64(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_int8_uint64_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_int8_uint64_m2(const rvm_int8_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_int8_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_int8_uint64_m4(const rvm_int8_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_int8_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_int8_uint64_m8(const rvm_int8_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_int8_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_uint64_uint64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_uint64_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_uint64_uint64_m2(const rvm_uint64_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_uint64_uint64_m4(const rvm_uint64_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_uint64_uint64_m8(const rvm_uint64_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_uint32_uint64(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_uint32_uint64_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_uint32_uint64_m2(const rvm_uint32_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_uint32_uint64_m4(const rvm_uint32_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_uint32_uint64_m8(const rvm_uint32_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_uint16_uint64(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_uint16_uint64_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_uint16_uint64_m2(const rvm_uint16_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_uint16_uint64_m4(const rvm_uint16_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_uint16_uint64_m8(const rvm_uint16_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_cast_k_uint8_uint64(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_cast_k_uint8_uint64_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint64(m0);
}
inline rvm_uint64_m2_t mipp_cast_k_uint8_uint64_m2(const rvm_uint8_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_uint64_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cast_k_uint8_uint64_m4(const rvm_uint8_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_uint64_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cast_k_uint8_uint64_m8(const rvm_uint8_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_uint64_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_float64_uint32(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_float64_uint32_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_float64_uint32_m2(const rvm_float64_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_float64_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_float64_uint32_m4(const rvm_float64_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_float64_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_float64_uint32_m8(const rvm_float64_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_float64_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_float32_uint32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_float32_uint32_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_float32_uint32_m2(const rvm_float32_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_float32_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_float32_uint32_m4(const rvm_float32_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_float32_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_float32_uint32_m8(const rvm_float32_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_float32_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_int64_uint32(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_int64_uint32_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_int64_uint32_m2(const rvm_int64_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_int64_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_int64_uint32_m4(const rvm_int64_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_int64_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_int64_uint32_m8(const rvm_int64_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_int64_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_int32_uint32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_int32_uint32_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_int32_uint32_m2(const rvm_int32_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_int32_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_int32_uint32_m4(const rvm_int32_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_int32_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_int32_uint32_m8(const rvm_int32_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_int32_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_int16_uint32(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_int16_uint32_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_int16_uint32_m2(const rvm_int16_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_int16_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_int16_uint32_m4(const rvm_int16_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_int16_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_int16_uint32_m8(const rvm_int16_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_int16_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_int8_uint32(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_int8_uint32_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_int8_uint32_m2(const rvm_int8_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_int8_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_int8_uint32_m4(const rvm_int8_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_int8_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_int8_uint32_m8(const rvm_int8_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_int8_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_uint64_uint32(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_uint64_uint32_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_uint64_uint32_m2(const rvm_uint64_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_uint64_uint32_m4(const rvm_uint64_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_uint64_uint32_m8(const rvm_uint64_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_uint32_uint32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_uint32_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_uint32_uint32_m2(const rvm_uint32_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_uint32_uint32_m4(const rvm_uint32_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_uint32_uint32_m8(const rvm_uint32_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_uint16_uint32(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_uint16_uint32_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_uint16_uint32_m2(const rvm_uint16_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_uint16_uint32_m4(const rvm_uint16_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_uint16_uint32_m8(const rvm_uint16_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_cast_k_uint8_uint32(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_cast_k_uint8_uint32_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint32(m0);
}
inline rvm_uint32_m2_t mipp_cast_k_uint8_uint32_m2(const rvm_uint8_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_uint32_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cast_k_uint8_uint32_m4(const rvm_uint8_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_uint32_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cast_k_uint8_uint32_m8(const rvm_uint8_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_uint32_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_float64_uint16(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_float64_uint16_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_float64_uint16_m2(const rvm_float64_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_float64_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_float64_uint16_m4(const rvm_float64_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_float64_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_float64_uint16_m8(const rvm_float64_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_float64_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_float32_uint16(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_float32_uint16_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_float32_uint16_m2(const rvm_float32_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_float32_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_float32_uint16_m4(const rvm_float32_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_float32_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_float32_uint16_m8(const rvm_float32_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_float32_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_int64_uint16(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_int64_uint16_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_int64_uint16_m2(const rvm_int64_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_int64_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_int64_uint16_m4(const rvm_int64_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_int64_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_int64_uint16_m8(const rvm_int64_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_int64_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_int32_uint16(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_int32_uint16_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_int32_uint16_m2(const rvm_int32_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_int32_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_int32_uint16_m4(const rvm_int32_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_int32_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_int32_uint16_m8(const rvm_int32_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_int32_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_int16_uint16(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_int16_uint16_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_int16_uint16_m2(const rvm_int16_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_int16_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_int16_uint16_m4(const rvm_int16_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_int16_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_int16_uint16_m8(const rvm_int16_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_int16_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_int8_uint16(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_int8_uint16_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_int8_uint16_m2(const rvm_int8_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_int8_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_int8_uint16_m4(const rvm_int8_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_int8_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_int8_uint16_m8(const rvm_int8_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_int8_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_uint64_uint16(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_uint64_uint16_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_uint64_uint16_m2(const rvm_uint64_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_uint64_uint16_m4(const rvm_uint64_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_uint64_uint16_m8(const rvm_uint64_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_uint32_uint16(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_uint32_uint16_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_uint32_uint16_m2(const rvm_uint32_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_uint32_uint16_m4(const rvm_uint32_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_uint32_uint16_m8(const rvm_uint32_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_uint16_uint16(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_uint16_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_uint16_uint16_m2(const rvm_uint16_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_uint16_uint16_m4(const rvm_uint16_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_uint16_uint16_m8(const rvm_uint16_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_cast_k_uint8_uint16(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_cast_k_uint8_uint16_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint16(m0);
}
inline rvm_uint16_m2_t mipp_cast_k_uint8_uint16_m2(const rvm_uint8_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_uint16_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cast_k_uint8_uint16_m4(const rvm_uint8_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_uint16_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cast_k_uint8_uint16_m8(const rvm_uint8_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_uint16_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_float64_uint8(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float64_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float64_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float64_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_float64_uint8_m1(const rvm_float64_m1_t m0) {
	return mipp_cast_k_float64_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_float64_uint8_m2(const rvm_float64_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_float64_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_float64_uint8_m4(const rvm_float64_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_float64_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_float64_uint8_m8(const rvm_float64_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_float64_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_float64_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_float32_uint8(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_float32_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_float32_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_float32_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_float32_uint8_m1(const rvm_float32_m1_t m0) {
	return mipp_cast_k_float32_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_float32_uint8_m2(const rvm_float32_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_float32_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_float32_uint8_m4(const rvm_float32_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_float32_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_float32_uint8_m8(const rvm_float32_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_float32_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_float32_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_int64_uint8(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int64_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int64_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int64_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_int64_uint8_m1(const rvm_int64_m1_t m0) {
	return mipp_cast_k_int64_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_int64_uint8_m2(const rvm_int64_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_int64_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_int64_uint8_m4(const rvm_int64_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_int64_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_int64_uint8_m8(const rvm_int64_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_int64_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int64_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_int32_uint8(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int32_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int32_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int32_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_int32_uint8_m1(const rvm_int32_m1_t m0) {
	return mipp_cast_k_int32_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_int32_uint8_m2(const rvm_int32_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_int32_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_int32_uint8_m4(const rvm_int32_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_int32_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_int32_uint8_m8(const rvm_int32_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_int32_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int32_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_int16_uint8(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int16_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int16_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int16_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_int16_uint8_m1(const rvm_int16_m1_t m0) {
	return mipp_cast_k_int16_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_int16_uint8_m2(const rvm_int16_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_int16_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_int16_uint8_m4(const rvm_int16_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_int16_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_int16_uint8_m8(const rvm_int16_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_int16_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int16_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_int8_uint8(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_int8_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_int8_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_int8_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_int8_uint8_m1(const rvm_int8_m1_t m0) {
	return mipp_cast_k_int8_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_int8_uint8_m2(const rvm_int8_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_int8_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_int8_uint8_m4(const rvm_int8_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_int8_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_int8_uint8_m8(const rvm_int8_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_int8_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_int8_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_uint64_uint8(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint64_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint64_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint64_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_uint64_uint8_m1(const rvm_uint64_m1_t m0) {
	return mipp_cast_k_uint64_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_uint64_uint8_m2(const rvm_uint64_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_uint64_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_uint64_uint8_m4(const rvm_uint64_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_uint64_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_uint64_uint8_m8(const rvm_uint64_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_uint64_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint64_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_uint32_uint8(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint32_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint32_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint32_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_uint32_uint8_m1(const rvm_uint32_m1_t m0) {
	return mipp_cast_k_uint32_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_uint32_uint8_m2(const rvm_uint32_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_uint32_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_uint32_uint8_m4(const rvm_uint32_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_uint32_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_uint32_uint8_m8(const rvm_uint32_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_uint32_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint32_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_uint16_uint8(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint16_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint16_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint16_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_uint16_uint8_m1(const rvm_uint16_m1_t m0) {
	return mipp_cast_k_uint16_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_uint16_uint8_m2(const rvm_uint16_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_uint16_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_uint16_uint8_m4(const rvm_uint16_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_uint16_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_uint16_uint8_m8(const rvm_uint16_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_uint16_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint16_uint8_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_cast_k_uint8_uint8(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_cast_k_uint8_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_cast_k_uint8_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_cast_k_uint8_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_cast_k_uint8_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_cast_k_uint8_uint8(m0);
}
inline rvm_uint8_m2_t mipp_cast_k_uint8_uint8_m2(const rvm_uint8_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cast_k_uint8_uint8_m1(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cast_k_uint8_uint8_m4(const rvm_uint8_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cast_k_uint8_uint8_m2(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cast_k_uint8_uint8_m8(const rvm_uint8_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cast_k_uint8_uint8_m4(m0.m1);
	msk.m2 = mipp_cast_k_uint8_uint8_m4(m0.m2);
	return msk;
}
inline rvd_float64_t mipp_toreg_float64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_float64(m0);
#endif
}
inline rvd_float64_m1_t mipp_toreg_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_toreg_float64(m0);
}
inline rvd_float64_m2_t mipp_toreg_float64_m2(const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_toreg_float64_m1(m0.m1);
	res.r2 = mipp_toreg_float64_m1(m0.m2);
	return res;
}
inline rvd_float64_m4_t mipp_toreg_float64_m4(const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_toreg_float64_m2(m0.m1);
	res.r2 = mipp_toreg_float64_m2(m0.m2);
	return res;
}
inline rvd_float64_m8_t mipp_toreg_float64_m8(const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_toreg_float64_m4(m0.m1);
	res.r2 = mipp_toreg_float64_m4(m0.m2);
	return res;
}
inline rvd_float32_t mipp_toreg_float32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_float32(m0);
#endif
}
inline rvd_float32_m1_t mipp_toreg_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_toreg_float32(m0);
}
inline rvd_float32_m2_t mipp_toreg_float32_m2(const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_toreg_float32_m1(m0.m1);
	res.r2 = mipp_toreg_float32_m1(m0.m2);
	return res;
}
inline rvd_float32_m4_t mipp_toreg_float32_m4(const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_toreg_float32_m2(m0.m1);
	res.r2 = mipp_toreg_float32_m2(m0.m2);
	return res;
}
inline rvd_float32_m8_t mipp_toreg_float32_m8(const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_toreg_float32_m4(m0.m1);
	res.r2 = mipp_toreg_float32_m4(m0.m2);
	return res;
}
inline rvd_int64_t mipp_toreg_int64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_int64(m0);
#endif
}
inline rvd_int64_m1_t mipp_toreg_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_toreg_int64(m0);
}
inline rvd_int64_m2_t mipp_toreg_int64_m2(const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_toreg_int64_m1(m0.m1);
	res.r2 = mipp_toreg_int64_m1(m0.m2);
	return res;
}
inline rvd_int64_m4_t mipp_toreg_int64_m4(const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_toreg_int64_m2(m0.m1);
	res.r2 = mipp_toreg_int64_m2(m0.m2);
	return res;
}
inline rvd_int64_m8_t mipp_toreg_int64_m8(const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_toreg_int64_m4(m0.m1);
	res.r2 = mipp_toreg_int64_m4(m0.m2);
	return res;
}
inline rvd_int32_t mipp_toreg_int32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_int32(m0);
#endif
}
inline rvd_int32_m1_t mipp_toreg_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_toreg_int32(m0);
}
inline rvd_int32_m2_t mipp_toreg_int32_m2(const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_toreg_int32_m1(m0.m1);
	res.r2 = mipp_toreg_int32_m1(m0.m2);
	return res;
}
inline rvd_int32_m4_t mipp_toreg_int32_m4(const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_toreg_int32_m2(m0.m1);
	res.r2 = mipp_toreg_int32_m2(m0.m2);
	return res;
}
inline rvd_int32_m8_t mipp_toreg_int32_m8(const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_toreg_int32_m4(m0.m1);
	res.r2 = mipp_toreg_int32_m4(m0.m2);
	return res;
}
inline rvd_int16_t mipp_toreg_int16(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_int16(m0);
#endif
}
inline rvd_int16_m1_t mipp_toreg_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_toreg_int16(m0);
}
inline rvd_int16_m2_t mipp_toreg_int16_m2(const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_toreg_int16_m1(m0.m1);
	res.r2 = mipp_toreg_int16_m1(m0.m2);
	return res;
}
inline rvd_int16_m4_t mipp_toreg_int16_m4(const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_toreg_int16_m2(m0.m1);
	res.r2 = mipp_toreg_int16_m2(m0.m2);
	return res;
}
inline rvd_int16_m8_t mipp_toreg_int16_m8(const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_toreg_int16_m4(m0.m1);
	res.r2 = mipp_toreg_int16_m4(m0.m2);
	return res;
}
inline rvd_int8_t mipp_toreg_int8(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_int8(m0);
#endif
}
inline rvd_int8_m1_t mipp_toreg_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_toreg_int8(m0);
}
inline rvd_int8_m2_t mipp_toreg_int8_m2(const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_toreg_int8_m1(m0.m1);
	res.r2 = mipp_toreg_int8_m1(m0.m2);
	return res;
}
inline rvd_int8_m4_t mipp_toreg_int8_m4(const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_toreg_int8_m2(m0.m1);
	res.r2 = mipp_toreg_int8_m2(m0.m2);
	return res;
}
inline rvd_int8_m8_t mipp_toreg_int8_m8(const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_toreg_int8_m4(m0.m1);
	res.r2 = mipp_toreg_int8_m4(m0.m2);
	return res;
}
inline rvd_uint64_t mipp_toreg_uint64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_uint64(m0);
#endif
}
inline rvd_uint64_m1_t mipp_toreg_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_toreg_uint64(m0);
}
inline rvd_uint64_m2_t mipp_toreg_uint64_m2(const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_toreg_uint64_m1(m0.m1);
	res.r2 = mipp_toreg_uint64_m1(m0.m2);
	return res;
}
inline rvd_uint64_m4_t mipp_toreg_uint64_m4(const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_toreg_uint64_m2(m0.m1);
	res.r2 = mipp_toreg_uint64_m2(m0.m2);
	return res;
}
inline rvd_uint64_m8_t mipp_toreg_uint64_m8(const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_toreg_uint64_m4(m0.m1);
	res.r2 = mipp_toreg_uint64_m4(m0.m2);
	return res;
}
inline rvd_uint32_t mipp_toreg_uint32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_uint32(m0);
#endif
}
inline rvd_uint32_m1_t mipp_toreg_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_toreg_uint32(m0);
}
inline rvd_uint32_m2_t mipp_toreg_uint32_m2(const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_toreg_uint32_m1(m0.m1);
	res.r2 = mipp_toreg_uint32_m1(m0.m2);
	return res;
}
inline rvd_uint32_m4_t mipp_toreg_uint32_m4(const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_toreg_uint32_m2(m0.m1);
	res.r2 = mipp_toreg_uint32_m2(m0.m2);
	return res;
}
inline rvd_uint32_m8_t mipp_toreg_uint32_m8(const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_toreg_uint32_m4(m0.m1);
	res.r2 = mipp_toreg_uint32_m4(m0.m2);
	return res;
}
inline rvd_uint16_t mipp_toreg_uint16(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_uint16(m0);
#endif
}
inline rvd_uint16_m1_t mipp_toreg_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_toreg_uint16(m0);
}
inline rvd_uint16_m2_t mipp_toreg_uint16_m2(const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_toreg_uint16_m1(m0.m1);
	res.r2 = mipp_toreg_uint16_m1(m0.m2);
	return res;
}
inline rvd_uint16_m4_t mipp_toreg_uint16_m4(const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_toreg_uint16_m2(m0.m1);
	res.r2 = mipp_toreg_uint16_m2(m0.m2);
	return res;
}
inline rvd_uint16_m8_t mipp_toreg_uint16_m8(const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_toreg_uint16_m4(m0.m1);
	res.r2 = mipp_toreg_uint16_m4(m0.m2);
	return res;
}
inline rvd_uint8_t mipp_toreg_uint8(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_toreg_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_toreg_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_toreg_uint8(m0);
#endif
}
inline rvd_uint8_m1_t mipp_toreg_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_toreg_uint8(m0);
}
inline rvd_uint8_m2_t mipp_toreg_uint8_m2(const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_toreg_uint8_m1(m0.m1);
	res.r2 = mipp_toreg_uint8_m1(m0.m2);
	return res;
}
inline rvd_uint8_m4_t mipp_toreg_uint8_m4(const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_toreg_uint8_m2(m0.m1);
	res.r2 = mipp_toreg_uint8_m2(m0.m2);
	return res;
}
inline rvd_uint8_m8_t mipp_toreg_uint8_m8(const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_toreg_uint8_m4(m0.m1);
	res.r2 = mipp_toreg_uint8_m4(m0.m2);
	return res;
}
inline rvm_float64_t mipp_tomsk_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_float64(r0);
#endif
}
inline rvm_float64_m1_t mipp_tomsk_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_tomsk_float64(r0);
}
inline rvm_float64_m2_t mipp_tomsk_float64_m2(const rvd_float64_m2_t r0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_tomsk_float64_m1(r0.r1);
	msk.m2 = mipp_tomsk_float64_m1(r0.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_tomsk_float64_m4(const rvd_float64_m4_t r0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_tomsk_float64_m2(r0.r1);
	msk.m2 = mipp_tomsk_float64_m2(r0.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_tomsk_float64_m8(const rvd_float64_m8_t r0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_tomsk_float64_m4(r0.r1);
	msk.m2 = mipp_tomsk_float64_m4(r0.r2);
	return msk;
}
inline rvm_float32_t mipp_tomsk_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_float32(r0);
#endif
}
inline rvm_float32_m1_t mipp_tomsk_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_tomsk_float32(r0);
}
inline rvm_float32_m2_t mipp_tomsk_float32_m2(const rvd_float32_m2_t r0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_tomsk_float32_m1(r0.r1);
	msk.m2 = mipp_tomsk_float32_m1(r0.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_tomsk_float32_m4(const rvd_float32_m4_t r0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_tomsk_float32_m2(r0.r1);
	msk.m2 = mipp_tomsk_float32_m2(r0.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_tomsk_float32_m8(const rvd_float32_m8_t r0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_tomsk_float32_m4(r0.r1);
	msk.m2 = mipp_tomsk_float32_m4(r0.r2);
	return msk;
}
inline rvm_int64_t mipp_tomsk_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_int64(r0);
#endif
}
inline rvm_int64_m1_t mipp_tomsk_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_tomsk_int64(r0);
}
inline rvm_int64_m2_t mipp_tomsk_int64_m2(const rvd_int64_m2_t r0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_tomsk_int64_m1(r0.r1);
	msk.m2 = mipp_tomsk_int64_m1(r0.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_tomsk_int64_m4(const rvd_int64_m4_t r0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_tomsk_int64_m2(r0.r1);
	msk.m2 = mipp_tomsk_int64_m2(r0.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_tomsk_int64_m8(const rvd_int64_m8_t r0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_tomsk_int64_m4(r0.r1);
	msk.m2 = mipp_tomsk_int64_m4(r0.r2);
	return msk;
}
inline rvm_int32_t mipp_tomsk_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_int32(r0);
#endif
}
inline rvm_int32_m1_t mipp_tomsk_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_tomsk_int32(r0);
}
inline rvm_int32_m2_t mipp_tomsk_int32_m2(const rvd_int32_m2_t r0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_tomsk_int32_m1(r0.r1);
	msk.m2 = mipp_tomsk_int32_m1(r0.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_tomsk_int32_m4(const rvd_int32_m4_t r0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_tomsk_int32_m2(r0.r1);
	msk.m2 = mipp_tomsk_int32_m2(r0.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_tomsk_int32_m8(const rvd_int32_m8_t r0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_tomsk_int32_m4(r0.r1);
	msk.m2 = mipp_tomsk_int32_m4(r0.r2);
	return msk;
}
inline rvm_int16_t mipp_tomsk_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_int16(r0);
#endif
}
inline rvm_int16_m1_t mipp_tomsk_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_tomsk_int16(r0);
}
inline rvm_int16_m2_t mipp_tomsk_int16_m2(const rvd_int16_m2_t r0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_tomsk_int16_m1(r0.r1);
	msk.m2 = mipp_tomsk_int16_m1(r0.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_tomsk_int16_m4(const rvd_int16_m4_t r0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_tomsk_int16_m2(r0.r1);
	msk.m2 = mipp_tomsk_int16_m2(r0.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_tomsk_int16_m8(const rvd_int16_m8_t r0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_tomsk_int16_m4(r0.r1);
	msk.m2 = mipp_tomsk_int16_m4(r0.r2);
	return msk;
}
inline rvm_int8_t mipp_tomsk_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_int8(r0);
#endif
}
inline rvm_int8_m1_t mipp_tomsk_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_tomsk_int8(r0);
}
inline rvm_int8_m2_t mipp_tomsk_int8_m2(const rvd_int8_m2_t r0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_tomsk_int8_m1(r0.r1);
	msk.m2 = mipp_tomsk_int8_m1(r0.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_tomsk_int8_m4(const rvd_int8_m4_t r0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_tomsk_int8_m2(r0.r1);
	msk.m2 = mipp_tomsk_int8_m2(r0.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_tomsk_int8_m8(const rvd_int8_m8_t r0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_tomsk_int8_m4(r0.r1);
	msk.m2 = mipp_tomsk_int8_m4(r0.r2);
	return msk;
}
inline rvm_uint64_t mipp_tomsk_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_uint64(r0);
#endif
}
inline rvm_uint64_m1_t mipp_tomsk_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_tomsk_uint64(r0);
}
inline rvm_uint64_m2_t mipp_tomsk_uint64_m2(const rvd_uint64_m2_t r0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_tomsk_uint64_m1(r0.r1);
	msk.m2 = mipp_tomsk_uint64_m1(r0.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_tomsk_uint64_m4(const rvd_uint64_m4_t r0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_tomsk_uint64_m2(r0.r1);
	msk.m2 = mipp_tomsk_uint64_m2(r0.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_tomsk_uint64_m8(const rvd_uint64_m8_t r0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_tomsk_uint64_m4(r0.r1);
	msk.m2 = mipp_tomsk_uint64_m4(r0.r2);
	return msk;
}
inline rvm_uint32_t mipp_tomsk_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_uint32(r0);
#endif
}
inline rvm_uint32_m1_t mipp_tomsk_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_tomsk_uint32(r0);
}
inline rvm_uint32_m2_t mipp_tomsk_uint32_m2(const rvd_uint32_m2_t r0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_tomsk_uint32_m1(r0.r1);
	msk.m2 = mipp_tomsk_uint32_m1(r0.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_tomsk_uint32_m4(const rvd_uint32_m4_t r0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_tomsk_uint32_m2(r0.r1);
	msk.m2 = mipp_tomsk_uint32_m2(r0.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_tomsk_uint32_m8(const rvd_uint32_m8_t r0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_tomsk_uint32_m4(r0.r1);
	msk.m2 = mipp_tomsk_uint32_m4(r0.r2);
	return msk;
}
inline rvm_uint16_t mipp_tomsk_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_uint16(r0);
#endif
}
inline rvm_uint16_m1_t mipp_tomsk_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_tomsk_uint16(r0);
}
inline rvm_uint16_m2_t mipp_tomsk_uint16_m2(const rvd_uint16_m2_t r0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_tomsk_uint16_m1(r0.r1);
	msk.m2 = mipp_tomsk_uint16_m1(r0.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_tomsk_uint16_m4(const rvd_uint16_m4_t r0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_tomsk_uint16_m2(r0.r1);
	msk.m2 = mipp_tomsk_uint16_m2(r0.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_tomsk_uint16_m8(const rvd_uint16_m8_t r0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_tomsk_uint16_m4(r0.r1);
	msk.m2 = mipp_tomsk_uint16_m4(r0.r2);
	return msk;
}
inline rvm_uint8_t mipp_tomsk_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_tomsk_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_tomsk_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_tomsk_uint8(r0);
#endif
}
inline rvm_uint8_m1_t mipp_tomsk_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_tomsk_uint8(r0);
}
inline rvm_uint8_m2_t mipp_tomsk_uint8_m2(const rvd_uint8_m2_t r0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_tomsk_uint8_m1(r0.r1);
	msk.m2 = mipp_tomsk_uint8_m1(r0.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_tomsk_uint8_m4(const rvd_uint8_m4_t r0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_tomsk_uint8_m2(r0.r1);
	msk.m2 = mipp_tomsk_uint8_m2(r0.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_tomsk_uint8_m8(const rvd_uint8_m8_t r0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_tomsk_uint8_m4(r0.r1);
	msk.m2 = mipp_tomsk_uint8_m4(r0.r2);
	return msk;
}
inline rvd_float64_t mipp_load_float64(const float64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_float64(p0);
#elif defined(__AVX__)
	return mipp_avx_load_float64(p0);
#elif defined(__SSE__)
	return mipp_sse_load_float64(p0);
#endif
}
inline rvd_float64_m1_t mipp_load_float64_m1(const float64_t* p0) {
	return mipp_load_float64(p0);
}
inline rvd_float64_m2_t mipp_load_float64_m2(const float64_t* p0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_load_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float64_m4_t mipp_load_float64_m4(const float64_t* p0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_load_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float64_m8_t mipp_load_float64_m8(const float64_t* p0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_load_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_float32_t mipp_load_float32(const float32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_float32(p0);
#elif defined(__AVX__)
	return mipp_avx_load_float32(p0);
#elif defined(__SSE__)
	return mipp_sse_load_float32(p0);
#endif
}
inline rvd_float32_m1_t mipp_load_float32_m1(const float32_t* p0) {
	return mipp_load_float32(p0);
}
inline rvd_float32_m2_t mipp_load_float32_m2(const float32_t* p0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_load_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float32_m4_t mipp_load_float32_m4(const float32_t* p0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_load_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float32_m8_t mipp_load_float32_m8(const float32_t* p0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_load_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int64_t mipp_load_int64(const int64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_int64(p0);
#elif defined(__AVX__)
	return mipp_avx_load_int64(p0);
#elif defined(__SSE__)
	return mipp_sse_load_int64(p0);
#endif
}
inline rvd_int64_m1_t mipp_load_int64_m1(const int64_t* p0) {
	return mipp_load_int64(p0);
}
inline rvd_int64_m2_t mipp_load_int64_m2(const int64_t* p0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_load_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int64_m4_t mipp_load_int64_m4(const int64_t* p0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_load_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int64_m8_t mipp_load_int64_m8(const int64_t* p0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_load_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int32_t mipp_load_int32(const int32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_int32(p0);
#elif defined(__AVX__)
	return mipp_avx_load_int32(p0);
#elif defined(__SSE__)
	return mipp_sse_load_int32(p0);
#endif
}
inline rvd_int32_m1_t mipp_load_int32_m1(const int32_t* p0) {
	return mipp_load_int32(p0);
}
inline rvd_int32_m2_t mipp_load_int32_m2(const int32_t* p0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_load_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int32_m4_t mipp_load_int32_m4(const int32_t* p0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_load_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int32_m8_t mipp_load_int32_m8(const int32_t* p0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_load_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int16_t mipp_load_int16(const int16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_int16(p0);
#elif defined(__AVX__)
	return mipp_avx_load_int16(p0);
#elif defined(__SSE__)
	return mipp_sse_load_int16(p0);
#endif
}
inline rvd_int16_m1_t mipp_load_int16_m1(const int16_t* p0) {
	return mipp_load_int16(p0);
}
inline rvd_int16_m2_t mipp_load_int16_m2(const int16_t* p0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_load_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int16_m4_t mipp_load_int16_m4(const int16_t* p0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_load_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int16_m8_t mipp_load_int16_m8(const int16_t* p0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_load_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int8_t mipp_load_int8(const int8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_int8(p0);
#elif defined(__AVX__)
	return mipp_avx_load_int8(p0);
#elif defined(__SSE__)
	return mipp_sse_load_int8(p0);
#endif
}
inline rvd_int8_m1_t mipp_load_int8_m1(const int8_t* p0) {
	return mipp_load_int8(p0);
}
inline rvd_int8_m2_t mipp_load_int8_m2(const int8_t* p0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_load_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int8_m4_t mipp_load_int8_m4(const int8_t* p0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_load_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int8_m8_t mipp_load_int8_m8(const int8_t* p0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_load_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint64_t mipp_load_uint64(const uint64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_uint64(p0);
#elif defined(__AVX__)
	return mipp_avx_load_uint64(p0);
#elif defined(__SSE__)
	return mipp_sse_load_uint64(p0);
#endif
}
inline rvd_uint64_m1_t mipp_load_uint64_m1(const uint64_t* p0) {
	return mipp_load_uint64(p0);
}
inline rvd_uint64_m2_t mipp_load_uint64_m2(const uint64_t* p0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_load_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint64_m4_t mipp_load_uint64_m4(const uint64_t* p0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_load_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint64_m8_t mipp_load_uint64_m8(const uint64_t* p0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_load_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint32_t mipp_load_uint32(const uint32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_uint32(p0);
#elif defined(__AVX__)
	return mipp_avx_load_uint32(p0);
#elif defined(__SSE__)
	return mipp_sse_load_uint32(p0);
#endif
}
inline rvd_uint32_m1_t mipp_load_uint32_m1(const uint32_t* p0) {
	return mipp_load_uint32(p0);
}
inline rvd_uint32_m2_t mipp_load_uint32_m2(const uint32_t* p0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_load_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint32_m4_t mipp_load_uint32_m4(const uint32_t* p0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_load_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint32_m8_t mipp_load_uint32_m8(const uint32_t* p0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_load_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint16_t mipp_load_uint16(const uint16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_uint16(p0);
#elif defined(__AVX__)
	return mipp_avx_load_uint16(p0);
#elif defined(__SSE__)
	return mipp_sse_load_uint16(p0);
#endif
}
inline rvd_uint16_m1_t mipp_load_uint16_m1(const uint16_t* p0) {
	return mipp_load_uint16(p0);
}
inline rvd_uint16_m2_t mipp_load_uint16_m2(const uint16_t* p0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_load_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint16_m4_t mipp_load_uint16_m4(const uint16_t* p0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_load_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint16_m8_t mipp_load_uint16_m8(const uint16_t* p0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_load_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint8_t mipp_load_uint8(const uint8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_load_uint8(p0);
#elif defined(__AVX__)
	return mipp_avx_load_uint8(p0);
#elif defined(__SSE__)
	return mipp_sse_load_uint8(p0);
#endif
}
inline rvd_uint8_m1_t mipp_load_uint8_m1(const uint8_t* p0) {
	return mipp_load_uint8(p0);
}
inline rvd_uint8_m2_t mipp_load_uint8_m2(const uint8_t* p0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_load_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_load_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint8_m4_t mipp_load_uint8_m4(const uint8_t* p0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_load_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_load_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint8_m8_t mipp_load_uint8_m8(const uint8_t* p0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_load_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_load_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_float64_t mipp_loadu_float64(const float64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_float64(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_float64(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_float64(p0);
#endif
}
inline rvd_float64_m1_t mipp_loadu_float64_m1(const float64_t* p0) {
	return mipp_loadu_float64(p0);
}
inline rvd_float64_m2_t mipp_loadu_float64_m2(const float64_t* p0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_loadu_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float64_m4_t mipp_loadu_float64_m4(const float64_t* p0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_loadu_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float64_m8_t mipp_loadu_float64_m8(const float64_t* p0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_loadu_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_float32_t mipp_loadu_float32(const float32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_float32(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_float32(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_float32(p0);
#endif
}
inline rvd_float32_m1_t mipp_loadu_float32_m1(const float32_t* p0) {
	return mipp_loadu_float32(p0);
}
inline rvd_float32_m2_t mipp_loadu_float32_m2(const float32_t* p0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_loadu_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float32_m4_t mipp_loadu_float32_m4(const float32_t* p0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_loadu_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float32_m8_t mipp_loadu_float32_m8(const float32_t* p0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_loadu_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int64_t mipp_loadu_int64(const int64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_int64(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_int64(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_int64(p0);
#endif
}
inline rvd_int64_m1_t mipp_loadu_int64_m1(const int64_t* p0) {
	return mipp_loadu_int64(p0);
}
inline rvd_int64_m2_t mipp_loadu_int64_m2(const int64_t* p0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_loadu_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int64_m4_t mipp_loadu_int64_m4(const int64_t* p0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_loadu_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int64_m8_t mipp_loadu_int64_m8(const int64_t* p0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_loadu_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int32_t mipp_loadu_int32(const int32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_int32(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_int32(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_int32(p0);
#endif
}
inline rvd_int32_m1_t mipp_loadu_int32_m1(const int32_t* p0) {
	return mipp_loadu_int32(p0);
}
inline rvd_int32_m2_t mipp_loadu_int32_m2(const int32_t* p0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_loadu_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int32_m4_t mipp_loadu_int32_m4(const int32_t* p0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_loadu_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int32_m8_t mipp_loadu_int32_m8(const int32_t* p0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_loadu_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int16_t mipp_loadu_int16(const int16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_int16(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_int16(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_int16(p0);
#endif
}
inline rvd_int16_m1_t mipp_loadu_int16_m1(const int16_t* p0) {
	return mipp_loadu_int16(p0);
}
inline rvd_int16_m2_t mipp_loadu_int16_m2(const int16_t* p0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_loadu_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int16_m4_t mipp_loadu_int16_m4(const int16_t* p0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_loadu_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int16_m8_t mipp_loadu_int16_m8(const int16_t* p0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_loadu_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int8_t mipp_loadu_int8(const int8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_int8(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_int8(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_int8(p0);
#endif
}
inline rvd_int8_m1_t mipp_loadu_int8_m1(const int8_t* p0) {
	return mipp_loadu_int8(p0);
}
inline rvd_int8_m2_t mipp_loadu_int8_m2(const int8_t* p0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_loadu_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int8_m4_t mipp_loadu_int8_m4(const int8_t* p0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_loadu_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int8_m8_t mipp_loadu_int8_m8(const int8_t* p0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_loadu_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint64_t mipp_loadu_uint64(const uint64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_uint64(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_uint64(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_uint64(p0);
#endif
}
inline rvd_uint64_m1_t mipp_loadu_uint64_m1(const uint64_t* p0) {
	return mipp_loadu_uint64(p0);
}
inline rvd_uint64_m2_t mipp_loadu_uint64_m2(const uint64_t* p0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_loadu_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint64_m4_t mipp_loadu_uint64_m4(const uint64_t* p0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_loadu_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint64_m8_t mipp_loadu_uint64_m8(const uint64_t* p0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_loadu_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint32_t mipp_loadu_uint32(const uint32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_uint32(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_uint32(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_uint32(p0);
#endif
}
inline rvd_uint32_m1_t mipp_loadu_uint32_m1(const uint32_t* p0) {
	return mipp_loadu_uint32(p0);
}
inline rvd_uint32_m2_t mipp_loadu_uint32_m2(const uint32_t* p0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_loadu_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint32_m4_t mipp_loadu_uint32_m4(const uint32_t* p0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_loadu_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint32_m8_t mipp_loadu_uint32_m8(const uint32_t* p0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_loadu_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint16_t mipp_loadu_uint16(const uint16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_uint16(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_uint16(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_uint16(p0);
#endif
}
inline rvd_uint16_m1_t mipp_loadu_uint16_m1(const uint16_t* p0) {
	return mipp_loadu_uint16(p0);
}
inline rvd_uint16_m2_t mipp_loadu_uint16_m2(const uint16_t* p0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_loadu_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint16_m4_t mipp_loadu_uint16_m4(const uint16_t* p0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_loadu_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint16_m8_t mipp_loadu_uint16_m8(const uint16_t* p0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_loadu_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint8_t mipp_loadu_uint8(const uint8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_loadu_uint8(p0);
#elif defined(__AVX__)
	return mipp_avx_loadu_uint8(p0);
#elif defined(__SSE__)
	return mipp_sse_loadu_uint8(p0);
#endif
}
inline rvd_uint8_m1_t mipp_loadu_uint8_m1(const uint8_t* p0) {
	return mipp_loadu_uint8(p0);
}
inline rvd_uint8_m2_t mipp_loadu_uint8_m2(const uint8_t* p0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_loadu_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_loadu_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint8_m4_t mipp_loadu_uint8_m4(const uint8_t* p0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_loadu_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_loadu_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint8_m8_t mipp_loadu_uint8_m8(const uint8_t* p0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_loadu_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_loadu_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline void mipp_store_float64(float64_t* p0, const rvd_float64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_float64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_float64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_float64(p0, r0);
#endif
}
inline void mipp_store_float64_m1(float64_t* p0, const rvd_float64_m1_t r0) {
	mipp_store_float64(p0, r0);
}
inline void mipp_store_float64_m2(float64_t* p0, const rvd_float64_m2_t r0) {
	mipp_store_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_float64_m4(float64_t* p0, const rvd_float64_m4_t r0) {
	mipp_store_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_float64_m8(float64_t* p0, const rvd_float64_m8_t r0) {
	mipp_store_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_float32(float32_t* p0, const rvd_float32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_float32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_float32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_float32(p0, r0);
#endif
}
inline void mipp_store_float32_m1(float32_t* p0, const rvd_float32_m1_t r0) {
	mipp_store_float32(p0, r0);
}
inline void mipp_store_float32_m2(float32_t* p0, const rvd_float32_m2_t r0) {
	mipp_store_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_float32_m4(float32_t* p0, const rvd_float32_m4_t r0) {
	mipp_store_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_float32_m8(float32_t* p0, const rvd_float32_m8_t r0) {
	mipp_store_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_int64(int64_t* p0, const rvd_int64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_int64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_int64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_int64(p0, r0);
#endif
}
inline void mipp_store_int64_m1(int64_t* p0, const rvd_int64_m1_t r0) {
	mipp_store_int64(p0, r0);
}
inline void mipp_store_int64_m2(int64_t* p0, const rvd_int64_m2_t r0) {
	mipp_store_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_int64_m4(int64_t* p0, const rvd_int64_m4_t r0) {
	mipp_store_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_int64_m8(int64_t* p0, const rvd_int64_m8_t r0) {
	mipp_store_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_int32(int32_t* p0, const rvd_int32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_int32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_int32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_int32(p0, r0);
#endif
}
inline void mipp_store_int32_m1(int32_t* p0, const rvd_int32_m1_t r0) {
	mipp_store_int32(p0, r0);
}
inline void mipp_store_int32_m2(int32_t* p0, const rvd_int32_m2_t r0) {
	mipp_store_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_int32_m4(int32_t* p0, const rvd_int32_m4_t r0) {
	mipp_store_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_int32_m8(int32_t* p0, const rvd_int32_m8_t r0) {
	mipp_store_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_int16(int16_t* p0, const rvd_int16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_int16(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_int16(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_int16(p0, r0);
#endif
}
inline void mipp_store_int16_m1(int16_t* p0, const rvd_int16_m1_t r0) {
	mipp_store_int16(p0, r0);
}
inline void mipp_store_int16_m2(int16_t* p0, const rvd_int16_m2_t r0) {
	mipp_store_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_int16_m4(int16_t* p0, const rvd_int16_m4_t r0) {
	mipp_store_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_int16_m8(int16_t* p0, const rvd_int16_m8_t r0) {
	mipp_store_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_int8(int8_t* p0, const rvd_int8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_int8(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_int8(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_int8(p0, r0);
#endif
}
inline void mipp_store_int8_m1(int8_t* p0, const rvd_int8_m1_t r0) {
	mipp_store_int8(p0, r0);
}
inline void mipp_store_int8_m2(int8_t* p0, const rvd_int8_m2_t r0) {
	mipp_store_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_int8_m4(int8_t* p0, const rvd_int8_m4_t r0) {
	mipp_store_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_int8_m8(int8_t* p0, const rvd_int8_m8_t r0) {
	mipp_store_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_uint64(uint64_t* p0, const rvd_uint64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_uint64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_uint64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_uint64(p0, r0);
#endif
}
inline void mipp_store_uint64_m1(uint64_t* p0, const rvd_uint64_m1_t r0) {
	mipp_store_uint64(p0, r0);
}
inline void mipp_store_uint64_m2(uint64_t* p0, const rvd_uint64_m2_t r0) {
	mipp_store_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_uint64_m4(uint64_t* p0, const rvd_uint64_m4_t r0) {
	mipp_store_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_uint64_m8(uint64_t* p0, const rvd_uint64_m8_t r0) {
	mipp_store_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_uint32(uint32_t* p0, const rvd_uint32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_uint32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_uint32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_uint32(p0, r0);
#endif
}
inline void mipp_store_uint32_m1(uint32_t* p0, const rvd_uint32_m1_t r0) {
	mipp_store_uint32(p0, r0);
}
inline void mipp_store_uint32_m2(uint32_t* p0, const rvd_uint32_m2_t r0) {
	mipp_store_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_uint32_m4(uint32_t* p0, const rvd_uint32_m4_t r0) {
	mipp_store_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_uint32_m8(uint32_t* p0, const rvd_uint32_m8_t r0) {
	mipp_store_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_uint16(uint16_t* p0, const rvd_uint16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_uint16(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_uint16(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_uint16(p0, r0);
#endif
}
inline void mipp_store_uint16_m1(uint16_t* p0, const rvd_uint16_m1_t r0) {
	mipp_store_uint16(p0, r0);
}
inline void mipp_store_uint16_m2(uint16_t* p0, const rvd_uint16_m2_t r0) {
	mipp_store_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_uint16_m4(uint16_t* p0, const rvd_uint16_m4_t r0) {
	mipp_store_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_uint16_m8(uint16_t* p0, const rvd_uint16_m8_t r0) {
	mipp_store_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_store_uint8(uint8_t* p0, const rvd_uint8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_store_uint8(p0, r0);
#elif defined(__AVX__)
	mipp_avx_store_uint8(p0, r0);
#elif defined(__SSE__)
	mipp_sse_store_uint8(p0, r0);
#endif
}
inline void mipp_store_uint8_m1(uint8_t* p0, const rvd_uint8_m1_t r0) {
	mipp_store_uint8(p0, r0);
}
inline void mipp_store_uint8_m2(uint8_t* p0, const rvd_uint8_m2_t r0) {
	mipp_store_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_store_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_store_uint8_m4(uint8_t* p0, const rvd_uint8_m4_t r0) {
	mipp_store_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_store_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_store_uint8_m8(uint8_t* p0, const rvd_uint8_m8_t r0) {
	mipp_store_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_store_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_float64(float64_t* p0, const rvd_float64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_float64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_float64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_float64(p0, r0);
#endif
}
inline void mipp_storeu_float64_m1(float64_t* p0, const rvd_float64_m1_t r0) {
	mipp_storeu_float64(p0, r0);
}
inline void mipp_storeu_float64_m2(float64_t* p0, const rvd_float64_m2_t r0) {
	mipp_storeu_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_float64_m4(float64_t* p0, const rvd_float64_m4_t r0) {
	mipp_storeu_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_float64_m8(float64_t* p0, const rvd_float64_m8_t r0) {
	mipp_storeu_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_float32(float32_t* p0, const rvd_float32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_float32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_float32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_float32(p0, r0);
#endif
}
inline void mipp_storeu_float32_m1(float32_t* p0, const rvd_float32_m1_t r0) {
	mipp_storeu_float32(p0, r0);
}
inline void mipp_storeu_float32_m2(float32_t* p0, const rvd_float32_m2_t r0) {
	mipp_storeu_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_float32_m4(float32_t* p0, const rvd_float32_m4_t r0) {
	mipp_storeu_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_float32_m8(float32_t* p0, const rvd_float32_m8_t r0) {
	mipp_storeu_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_int64(int64_t* p0, const rvd_int64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_int64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_int64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_int64(p0, r0);
#endif
}
inline void mipp_storeu_int64_m1(int64_t* p0, const rvd_int64_m1_t r0) {
	mipp_storeu_int64(p0, r0);
}
inline void mipp_storeu_int64_m2(int64_t* p0, const rvd_int64_m2_t r0) {
	mipp_storeu_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_int64_m4(int64_t* p0, const rvd_int64_m4_t r0) {
	mipp_storeu_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_int64_m8(int64_t* p0, const rvd_int64_m8_t r0) {
	mipp_storeu_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_int32(int32_t* p0, const rvd_int32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_int32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_int32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_int32(p0, r0);
#endif
}
inline void mipp_storeu_int32_m1(int32_t* p0, const rvd_int32_m1_t r0) {
	mipp_storeu_int32(p0, r0);
}
inline void mipp_storeu_int32_m2(int32_t* p0, const rvd_int32_m2_t r0) {
	mipp_storeu_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_int32_m4(int32_t* p0, const rvd_int32_m4_t r0) {
	mipp_storeu_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_int32_m8(int32_t* p0, const rvd_int32_m8_t r0) {
	mipp_storeu_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_int16(int16_t* p0, const rvd_int16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_int16(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_int16(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_int16(p0, r0);
#endif
}
inline void mipp_storeu_int16_m1(int16_t* p0, const rvd_int16_m1_t r0) {
	mipp_storeu_int16(p0, r0);
}
inline void mipp_storeu_int16_m2(int16_t* p0, const rvd_int16_m2_t r0) {
	mipp_storeu_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_int16_m4(int16_t* p0, const rvd_int16_m4_t r0) {
	mipp_storeu_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_int16_m8(int16_t* p0, const rvd_int16_m8_t r0) {
	mipp_storeu_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_int8(int8_t* p0, const rvd_int8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_int8(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_int8(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_int8(p0, r0);
#endif
}
inline void mipp_storeu_int8_m1(int8_t* p0, const rvd_int8_m1_t r0) {
	mipp_storeu_int8(p0, r0);
}
inline void mipp_storeu_int8_m2(int8_t* p0, const rvd_int8_m2_t r0) {
	mipp_storeu_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_int8_m4(int8_t* p0, const rvd_int8_m4_t r0) {
	mipp_storeu_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_int8_m8(int8_t* p0, const rvd_int8_m8_t r0) {
	mipp_storeu_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_uint64(uint64_t* p0, const rvd_uint64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_uint64(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_uint64(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_uint64(p0, r0);
#endif
}
inline void mipp_storeu_uint64_m1(uint64_t* p0, const rvd_uint64_m1_t r0) {
	mipp_storeu_uint64(p0, r0);
}
inline void mipp_storeu_uint64_m2(uint64_t* p0, const rvd_uint64_m2_t r0) {
	mipp_storeu_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_uint64_m4(uint64_t* p0, const rvd_uint64_m4_t r0) {
	mipp_storeu_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_uint64_m8(uint64_t* p0, const rvd_uint64_m8_t r0) {
	mipp_storeu_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_uint32(uint32_t* p0, const rvd_uint32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_uint32(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_uint32(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_uint32(p0, r0);
#endif
}
inline void mipp_storeu_uint32_m1(uint32_t* p0, const rvd_uint32_m1_t r0) {
	mipp_storeu_uint32(p0, r0);
}
inline void mipp_storeu_uint32_m2(uint32_t* p0, const rvd_uint32_m2_t r0) {
	mipp_storeu_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_uint32_m4(uint32_t* p0, const rvd_uint32_m4_t r0) {
	mipp_storeu_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_uint32_m8(uint32_t* p0, const rvd_uint32_m8_t r0) {
	mipp_storeu_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_uint16(uint16_t* p0, const rvd_uint16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_uint16(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_uint16(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_uint16(p0, r0);
#endif
}
inline void mipp_storeu_uint16_m1(uint16_t* p0, const rvd_uint16_m1_t r0) {
	mipp_storeu_uint16(p0, r0);
}
inline void mipp_storeu_uint16_m2(uint16_t* p0, const rvd_uint16_m2_t r0) {
	mipp_storeu_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_uint16_m4(uint16_t* p0, const rvd_uint16_m4_t r0) {
	mipp_storeu_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_uint16_m8(uint16_t* p0, const rvd_uint16_m8_t r0) {
	mipp_storeu_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline void mipp_storeu_uint8(uint8_t* p0, const rvd_uint8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_storeu_uint8(p0, r0);
#elif defined(__AVX__)
	mipp_avx_storeu_uint8(p0, r0);
#elif defined(__SSE__)
	mipp_sse_storeu_uint8(p0, r0);
#endif
}
inline void mipp_storeu_uint8_m1(uint8_t* p0, const rvd_uint8_m1_t r0) {
	mipp_storeu_uint8(p0, r0);
}
inline void mipp_storeu_uint8_m2(uint8_t* p0, const rvd_uint8_m2_t r0) {
	mipp_storeu_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r1);
	mipp_storeu_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), r0.r2);
}
inline void mipp_storeu_uint8_m4(uint8_t* p0, const rvd_uint8_m4_t r0) {
	mipp_storeu_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r1);
	mipp_storeu_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), r0.r2);
}
inline void mipp_storeu_uint8_m8(uint8_t* p0, const rvd_uint8_m8_t r0) {
	mipp_storeu_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r1);
	mipp_storeu_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), r0.r2);
}
inline rvd_float64_t mipp_set_float64(const float64_t vals[MIPP_N_FLOAT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_float64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_float64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_float64(vals);
#endif
}
inline rvd_float64_m1_t mipp_set_float64_m1(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_float64(vals);
}
inline rvd_float64_m2_t mipp_set_float64_m2(const float64_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_set_float64_m4(const float64_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_set_float64_m8(const float64_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_set_float32(const float32_t vals[MIPP_N_FLOAT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_float32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_float32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_float32(vals);
#endif
}
inline rvd_float32_m1_t mipp_set_float32_m1(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_float32(vals);
}
inline rvd_float32_m2_t mipp_set_float32_m2(const float32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_set_float32_m4(const float32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_set_float32_m8(const float32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_set_int64(const int64_t vals[MIPP_N_INT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_int64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_int64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_int64(vals);
#endif
}
inline rvd_int64_m1_t mipp_set_int64_m1(const int64_t vals[MIPP_N_INT64]) {
	return mipp_set_int64(vals);
}
inline rvd_int64_m2_t mipp_set_int64_m2(const int64_t vals[MIPP_N_INT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_set_int64_m4(const int64_t vals[MIPP_N_INT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_set_int64_m8(const int64_t vals[MIPP_N_INT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_set_int32(const int32_t vals[MIPP_N_INT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_int32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_int32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_int32(vals);
#endif
}
inline rvd_int32_m1_t mipp_set_int32_m1(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_int32(vals);
}
inline rvd_int32_m2_t mipp_set_int32_m2(const int32_t vals[MIPP_N_INT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_set_int32_m4(const int32_t vals[MIPP_N_INT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_set_int32_m8(const int32_t vals[MIPP_N_INT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_set_int16(const int16_t vals[MIPP_N_INT16]) {
#if defined(__AVX512__)
	return mipp_avx512_set_int16(vals);
#elif defined(__AVX__)
	return mipp_avx_set_int16(vals);
#elif defined(__SSE__)
	return mipp_sse_set_int16(vals);
#endif
}
inline rvd_int16_m1_t mipp_set_int16_m1(const int16_t vals[MIPP_N_INT16]) {
	return mipp_set_int16(vals);
}
inline rvd_int16_m2_t mipp_set_int16_m2(const int16_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_set_int16_m4(const int16_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_set_int16_m8(const int16_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_set_int8(const int8_t vals[MIPP_N_INT8]) {
#if defined(__AVX512__)
	return mipp_avx512_set_int8(vals);
#elif defined(__AVX__)
	return mipp_avx_set_int8(vals);
#elif defined(__SSE__)
	return mipp_sse_set_int8(vals);
#endif
}
inline rvd_int8_m1_t mipp_set_int8_m1(const int8_t vals[MIPP_N_INT8]) {
	return mipp_set_int8(vals);
}
inline rvd_int8_m2_t mipp_set_int8_m2(const int8_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_set_int8_m4(const int8_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_set_int8_m8(const int8_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_set_uint64(const uint64_t vals[MIPP_N_UINT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_uint64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_uint64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_uint64(vals);
#endif
}
inline rvd_uint64_m1_t mipp_set_uint64_m1(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_set_uint64(vals);
}
inline rvd_uint64_m2_t mipp_set_uint64_m2(const uint64_t vals[MIPP_N_UINT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_set_uint64_m4(const uint64_t vals[MIPP_N_UINT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_set_uint64_m8(const uint64_t vals[MIPP_N_UINT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_set_uint32(const uint32_t vals[MIPP_N_UINT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_uint32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_uint32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_uint32(vals);
#endif
}
inline rvd_uint32_m1_t mipp_set_uint32_m1(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_set_uint32(vals);
}
inline rvd_uint32_m2_t mipp_set_uint32_m2(const uint32_t vals[MIPP_N_UINT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_set_uint32_m4(const uint32_t vals[MIPP_N_UINT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_set_uint32_m8(const uint32_t vals[MIPP_N_UINT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_set_uint16(const uint16_t vals[MIPP_N_UINT16]) {
#if defined(__AVX512__)
	return mipp_avx512_set_uint16(vals);
#elif defined(__AVX__)
	return mipp_avx_set_uint16(vals);
#elif defined(__SSE__)
	return mipp_sse_set_uint16(vals);
#endif
}
inline rvd_uint16_m1_t mipp_set_uint16_m1(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_set_uint16(vals);
}
inline rvd_uint16_m2_t mipp_set_uint16_m2(const uint16_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_set_uint16_m4(const uint16_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_set_uint16_m8(const uint16_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_set_uint8(const uint8_t vals[MIPP_N_UINT8]) {
#if defined(__AVX512__)
	return mipp_avx512_set_uint8(vals);
#elif defined(__AVX__)
	return mipp_avx_set_uint8(vals);
#elif defined(__SSE__)
	return mipp_sse_set_uint8(vals);
#endif
}
inline rvd_uint8_m1_t mipp_set_uint8_m1(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_set_uint8(vals);
}
inline rvd_uint8_m2_t mipp_set_uint8_m2(const uint8_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_set_uint8_m4(const uint8_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_set_uint8_m8(const uint8_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_set_uint8_m8");
	exit(-1);
}
inline rvm_float64_t mipp_set_k_float64(const int32_t vals[MIPP_N_FLOAT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_float64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_float64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_float64(vals);
#endif
}
inline rvm_float64_m1_t mipp_set_k_float64_m1(const int32_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_k_float64(vals);
}
inline rvm_float64_m2_t mipp_set_k_float64_m2(const int32_t vals[MIPP_N_FLOAT64]) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_set_k_float64_m1(vals);
	msk.m2 = mipp_set_k_float64_m1(vals);
	return msk;
}
inline rvm_float64_m4_t mipp_set_k_float64_m4(const int32_t vals[MIPP_N_FLOAT64]) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_set_k_float64_m2(vals);
	msk.m2 = mipp_set_k_float64_m2(vals);
	return msk;
}
inline rvm_float64_m8_t mipp_set_k_float64_m8(const int32_t vals[MIPP_N_FLOAT64]) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_set_k_float64_m4(vals);
	msk.m2 = mipp_set_k_float64_m4(vals);
	return msk;
}
inline rvm_float32_t mipp_set_k_float32(const int32_t vals[MIPP_N_FLOAT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_float32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_float32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_float32(vals);
#endif
}
inline rvm_float32_m1_t mipp_set_k_float32_m1(const int32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_k_float32(vals);
}
inline rvm_float32_m2_t mipp_set_k_float32_m2(const int32_t vals[MIPP_N_FLOAT32]) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_set_k_float32_m1(vals);
	msk.m2 = mipp_set_k_float32_m1(vals);
	return msk;
}
inline rvm_float32_m4_t mipp_set_k_float32_m4(const int32_t vals[MIPP_N_FLOAT32]) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_set_k_float32_m2(vals);
	msk.m2 = mipp_set_k_float32_m2(vals);
	return msk;
}
inline rvm_float32_m8_t mipp_set_k_float32_m8(const int32_t vals[MIPP_N_FLOAT32]) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_set_k_float32_m4(vals);
	msk.m2 = mipp_set_k_float32_m4(vals);
	return msk;
}
inline rvm_int64_t mipp_set_k_int64(const int32_t vals[MIPP_N_INT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_int64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_int64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_int64(vals);
#endif
}
inline rvm_int64_m1_t mipp_set_k_int64_m1(const int32_t vals[MIPP_N_INT64]) {
	return mipp_set_k_int64(vals);
}
inline rvm_int64_m2_t mipp_set_k_int64_m2(const int32_t vals[MIPP_N_INT64]) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_set_k_int64_m1(vals);
	msk.m2 = mipp_set_k_int64_m1(vals);
	return msk;
}
inline rvm_int64_m4_t mipp_set_k_int64_m4(const int32_t vals[MIPP_N_INT64]) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_set_k_int64_m2(vals);
	msk.m2 = mipp_set_k_int64_m2(vals);
	return msk;
}
inline rvm_int64_m8_t mipp_set_k_int64_m8(const int32_t vals[MIPP_N_INT64]) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_set_k_int64_m4(vals);
	msk.m2 = mipp_set_k_int64_m4(vals);
	return msk;
}
inline rvm_int32_t mipp_set_k_int32(const int32_t vals[MIPP_N_INT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_int32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_int32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_int32(vals);
#endif
}
inline rvm_int32_m1_t mipp_set_k_int32_m1(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_k_int32(vals);
}
inline rvm_int32_m2_t mipp_set_k_int32_m2(const int32_t vals[MIPP_N_INT32]) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_set_k_int32_m1(vals);
	msk.m2 = mipp_set_k_int32_m1(vals);
	return msk;
}
inline rvm_int32_m4_t mipp_set_k_int32_m4(const int32_t vals[MIPP_N_INT32]) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_set_k_int32_m2(vals);
	msk.m2 = mipp_set_k_int32_m2(vals);
	return msk;
}
inline rvm_int32_m8_t mipp_set_k_int32_m8(const int32_t vals[MIPP_N_INT32]) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_set_k_int32_m4(vals);
	msk.m2 = mipp_set_k_int32_m4(vals);
	return msk;
}
inline rvm_int16_t mipp_set_k_int16(const int32_t vals[MIPP_N_INT16]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_int16(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_int16(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_int16(vals);
#endif
}
inline rvm_int16_m1_t mipp_set_k_int16_m1(const int32_t vals[MIPP_N_INT16]) {
	return mipp_set_k_int16(vals);
}
inline rvm_int16_m2_t mipp_set_k_int16_m2(const int32_t vals[MIPP_N_INT16]) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_set_k_int16_m1(vals);
	msk.m2 = mipp_set_k_int16_m1(vals);
	return msk;
}
inline rvm_int16_m4_t mipp_set_k_int16_m4(const int32_t vals[MIPP_N_INT16]) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_set_k_int16_m2(vals);
	msk.m2 = mipp_set_k_int16_m2(vals);
	return msk;
}
inline rvm_int16_m8_t mipp_set_k_int16_m8(const int32_t vals[MIPP_N_INT16]) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_set_k_int16_m4(vals);
	msk.m2 = mipp_set_k_int16_m4(vals);
	return msk;
}
inline rvm_int8_t mipp_set_k_int8(const int32_t vals[MIPP_N_INT8]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_int8(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_int8(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_int8(vals);
#endif
}
inline rvm_int8_m1_t mipp_set_k_int8_m1(const int32_t vals[MIPP_N_INT8]) {
	return mipp_set_k_int8(vals);
}
inline rvm_int8_m2_t mipp_set_k_int8_m2(const int32_t vals[MIPP_N_INT8]) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_set_k_int8_m1(vals);
	msk.m2 = mipp_set_k_int8_m1(vals);
	return msk;
}
inline rvm_int8_m4_t mipp_set_k_int8_m4(const int32_t vals[MIPP_N_INT8]) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_set_k_int8_m2(vals);
	msk.m2 = mipp_set_k_int8_m2(vals);
	return msk;
}
inline rvm_int8_m8_t mipp_set_k_int8_m8(const int32_t vals[MIPP_N_INT8]) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_set_k_int8_m4(vals);
	msk.m2 = mipp_set_k_int8_m4(vals);
	return msk;
}
inline rvm_uint64_t mipp_set_k_uint64(const int32_t vals[MIPP_N_UINT64]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_uint64(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_uint64(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_uint64(vals);
#endif
}
inline rvm_uint64_m1_t mipp_set_k_uint64_m1(const int32_t vals[MIPP_N_UINT64]) {
	return mipp_set_k_uint64(vals);
}
inline rvm_uint64_m2_t mipp_set_k_uint64_m2(const int32_t vals[MIPP_N_UINT64]) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_set_k_uint64_m1(vals);
	msk.m2 = mipp_set_k_uint64_m1(vals);
	return msk;
}
inline rvm_uint64_m4_t mipp_set_k_uint64_m4(const int32_t vals[MIPP_N_UINT64]) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_set_k_uint64_m2(vals);
	msk.m2 = mipp_set_k_uint64_m2(vals);
	return msk;
}
inline rvm_uint64_m8_t mipp_set_k_uint64_m8(const int32_t vals[MIPP_N_UINT64]) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_set_k_uint64_m4(vals);
	msk.m2 = mipp_set_k_uint64_m4(vals);
	return msk;
}
inline rvm_uint32_t mipp_set_k_uint32(const int32_t vals[MIPP_N_UINT32]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_uint32(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_uint32(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_uint32(vals);
#endif
}
inline rvm_uint32_m1_t mipp_set_k_uint32_m1(const int32_t vals[MIPP_N_UINT32]) {
	return mipp_set_k_uint32(vals);
}
inline rvm_uint32_m2_t mipp_set_k_uint32_m2(const int32_t vals[MIPP_N_UINT32]) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_set_k_uint32_m1(vals);
	msk.m2 = mipp_set_k_uint32_m1(vals);
	return msk;
}
inline rvm_uint32_m4_t mipp_set_k_uint32_m4(const int32_t vals[MIPP_N_UINT32]) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_set_k_uint32_m2(vals);
	msk.m2 = mipp_set_k_uint32_m2(vals);
	return msk;
}
inline rvm_uint32_m8_t mipp_set_k_uint32_m8(const int32_t vals[MIPP_N_UINT32]) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_set_k_uint32_m4(vals);
	msk.m2 = mipp_set_k_uint32_m4(vals);
	return msk;
}
inline rvm_uint16_t mipp_set_k_uint16(const int32_t vals[MIPP_N_UINT16]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_uint16(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_uint16(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_uint16(vals);
#endif
}
inline rvm_uint16_m1_t mipp_set_k_uint16_m1(const int32_t vals[MIPP_N_UINT16]) {
	return mipp_set_k_uint16(vals);
}
inline rvm_uint16_m2_t mipp_set_k_uint16_m2(const int32_t vals[MIPP_N_UINT16]) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_set_k_uint16_m1(vals);
	msk.m2 = mipp_set_k_uint16_m1(vals);
	return msk;
}
inline rvm_uint16_m4_t mipp_set_k_uint16_m4(const int32_t vals[MIPP_N_UINT16]) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_set_k_uint16_m2(vals);
	msk.m2 = mipp_set_k_uint16_m2(vals);
	return msk;
}
inline rvm_uint16_m8_t mipp_set_k_uint16_m8(const int32_t vals[MIPP_N_UINT16]) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_set_k_uint16_m4(vals);
	msk.m2 = mipp_set_k_uint16_m4(vals);
	return msk;
}
inline rvm_uint8_t mipp_set_k_uint8(const int32_t vals[MIPP_N_UINT8]) {
#if defined(__AVX512__)
	return mipp_avx512_set_k_uint8(vals);
#elif defined(__AVX__)
	return mipp_avx_set_k_uint8(vals);
#elif defined(__SSE__)
	return mipp_sse_set_k_uint8(vals);
#endif
}
inline rvm_uint8_m1_t mipp_set_k_uint8_m1(const int32_t vals[MIPP_N_UINT8]) {
	return mipp_set_k_uint8(vals);
}
inline rvm_uint8_m2_t mipp_set_k_uint8_m2(const int32_t vals[MIPP_N_UINT8]) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_set_k_uint8_m1(vals);
	msk.m2 = mipp_set_k_uint8_m1(vals);
	return msk;
}
inline rvm_uint8_m4_t mipp_set_k_uint8_m4(const int32_t vals[MIPP_N_UINT8]) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_set_k_uint8_m2(vals);
	msk.m2 = mipp_set_k_uint8_m2(vals);
	return msk;
}
inline rvm_uint8_m8_t mipp_set_k_uint8_m8(const int32_t vals[MIPP_N_UINT8]) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_set_k_uint8_m4(vals);
	msk.m2 = mipp_set_k_uint8_m4(vals);
	return msk;
}
inline rvd_float64_t mipp_set1_float64(const float64_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_float64(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_float64(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_float64(v0);
#endif
}
inline rvd_float64_m1_t mipp_set1_float64_m1(const float64_t v0) {
	return mipp_set1_float64(v0);
}
inline rvd_float64_m2_t mipp_set1_float64_m2(const float64_t v0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_set1_float64_m1(v0);
	res.r2 = mipp_set1_float64_m1(v0);
	return res;
}
inline rvd_float64_m4_t mipp_set1_float64_m4(const float64_t v0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_set1_float64_m2(v0);
	res.r2 = mipp_set1_float64_m2(v0);
	return res;
}
inline rvd_float64_m8_t mipp_set1_float64_m8(const float64_t v0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_set1_float64_m4(v0);
	res.r2 = mipp_set1_float64_m4(v0);
	return res;
}
inline rvd_float32_t mipp_set1_float32(const float32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_float32(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_float32(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_float32(v0);
#endif
}
inline rvd_float32_m1_t mipp_set1_float32_m1(const float32_t v0) {
	return mipp_set1_float32(v0);
}
inline rvd_float32_m2_t mipp_set1_float32_m2(const float32_t v0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_set1_float32_m1(v0);
	res.r2 = mipp_set1_float32_m1(v0);
	return res;
}
inline rvd_float32_m4_t mipp_set1_float32_m4(const float32_t v0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_set1_float32_m2(v0);
	res.r2 = mipp_set1_float32_m2(v0);
	return res;
}
inline rvd_float32_m8_t mipp_set1_float32_m8(const float32_t v0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_set1_float32_m4(v0);
	res.r2 = mipp_set1_float32_m4(v0);
	return res;
}
inline rvd_int64_t mipp_set1_int64(const int64_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_int64(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_int64(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_int64(v0);
#endif
}
inline rvd_int64_m1_t mipp_set1_int64_m1(const int64_t v0) {
	return mipp_set1_int64(v0);
}
inline rvd_int64_m2_t mipp_set1_int64_m2(const int64_t v0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_set1_int64_m1(v0);
	res.r2 = mipp_set1_int64_m1(v0);
	return res;
}
inline rvd_int64_m4_t mipp_set1_int64_m4(const int64_t v0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_set1_int64_m2(v0);
	res.r2 = mipp_set1_int64_m2(v0);
	return res;
}
inline rvd_int64_m8_t mipp_set1_int64_m8(const int64_t v0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_set1_int64_m4(v0);
	res.r2 = mipp_set1_int64_m4(v0);
	return res;
}
inline rvd_int32_t mipp_set1_int32(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_int32(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_int32(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_int32(v0);
#endif
}
inline rvd_int32_m1_t mipp_set1_int32_m1(const int32_t v0) {
	return mipp_set1_int32(v0);
}
inline rvd_int32_m2_t mipp_set1_int32_m2(const int32_t v0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_set1_int32_m1(v0);
	res.r2 = mipp_set1_int32_m1(v0);
	return res;
}
inline rvd_int32_m4_t mipp_set1_int32_m4(const int32_t v0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_set1_int32_m2(v0);
	res.r2 = mipp_set1_int32_m2(v0);
	return res;
}
inline rvd_int32_m8_t mipp_set1_int32_m8(const int32_t v0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_set1_int32_m4(v0);
	res.r2 = mipp_set1_int32_m4(v0);
	return res;
}
inline rvd_int16_t mipp_set1_int16(const int16_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_int16(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_int16(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_int16(v0);
#endif
}
inline rvd_int16_m1_t mipp_set1_int16_m1(const int16_t v0) {
	return mipp_set1_int16(v0);
}
inline rvd_int16_m2_t mipp_set1_int16_m2(const int16_t v0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_set1_int16_m1(v0);
	res.r2 = mipp_set1_int16_m1(v0);
	return res;
}
inline rvd_int16_m4_t mipp_set1_int16_m4(const int16_t v0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_set1_int16_m2(v0);
	res.r2 = mipp_set1_int16_m2(v0);
	return res;
}
inline rvd_int16_m8_t mipp_set1_int16_m8(const int16_t v0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_set1_int16_m4(v0);
	res.r2 = mipp_set1_int16_m4(v0);
	return res;
}
inline rvd_int8_t mipp_set1_int8(const int8_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_int8(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_int8(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_int8(v0);
#endif
}
inline rvd_int8_m1_t mipp_set1_int8_m1(const int8_t v0) {
	return mipp_set1_int8(v0);
}
inline rvd_int8_m2_t mipp_set1_int8_m2(const int8_t v0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_set1_int8_m1(v0);
	res.r2 = mipp_set1_int8_m1(v0);
	return res;
}
inline rvd_int8_m4_t mipp_set1_int8_m4(const int8_t v0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_set1_int8_m2(v0);
	res.r2 = mipp_set1_int8_m2(v0);
	return res;
}
inline rvd_int8_m8_t mipp_set1_int8_m8(const int8_t v0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_set1_int8_m4(v0);
	res.r2 = mipp_set1_int8_m4(v0);
	return res;
}
inline rvd_uint64_t mipp_set1_uint64(const uint64_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_uint64(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_uint64(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_uint64(v0);
#endif
}
inline rvd_uint64_m1_t mipp_set1_uint64_m1(const uint64_t v0) {
	return mipp_set1_uint64(v0);
}
inline rvd_uint64_m2_t mipp_set1_uint64_m2(const uint64_t v0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_set1_uint64_m1(v0);
	res.r2 = mipp_set1_uint64_m1(v0);
	return res;
}
inline rvd_uint64_m4_t mipp_set1_uint64_m4(const uint64_t v0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_set1_uint64_m2(v0);
	res.r2 = mipp_set1_uint64_m2(v0);
	return res;
}
inline rvd_uint64_m8_t mipp_set1_uint64_m8(const uint64_t v0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_set1_uint64_m4(v0);
	res.r2 = mipp_set1_uint64_m4(v0);
	return res;
}
inline rvd_uint32_t mipp_set1_uint32(const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_uint32(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_uint32(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_uint32(v0);
#endif
}
inline rvd_uint32_m1_t mipp_set1_uint32_m1(const uint32_t v0) {
	return mipp_set1_uint32(v0);
}
inline rvd_uint32_m2_t mipp_set1_uint32_m2(const uint32_t v0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_set1_uint32_m1(v0);
	res.r2 = mipp_set1_uint32_m1(v0);
	return res;
}
inline rvd_uint32_m4_t mipp_set1_uint32_m4(const uint32_t v0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_set1_uint32_m2(v0);
	res.r2 = mipp_set1_uint32_m2(v0);
	return res;
}
inline rvd_uint32_m8_t mipp_set1_uint32_m8(const uint32_t v0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_set1_uint32_m4(v0);
	res.r2 = mipp_set1_uint32_m4(v0);
	return res;
}
inline rvd_uint16_t mipp_set1_uint16(const uint16_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_uint16(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_uint16(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_uint16(v0);
#endif
}
inline rvd_uint16_m1_t mipp_set1_uint16_m1(const uint16_t v0) {
	return mipp_set1_uint16(v0);
}
inline rvd_uint16_m2_t mipp_set1_uint16_m2(const uint16_t v0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_set1_uint16_m1(v0);
	res.r2 = mipp_set1_uint16_m1(v0);
	return res;
}
inline rvd_uint16_m4_t mipp_set1_uint16_m4(const uint16_t v0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_set1_uint16_m2(v0);
	res.r2 = mipp_set1_uint16_m2(v0);
	return res;
}
inline rvd_uint16_m8_t mipp_set1_uint16_m8(const uint16_t v0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_set1_uint16_m4(v0);
	res.r2 = mipp_set1_uint16_m4(v0);
	return res;
}
inline rvd_uint8_t mipp_set1_uint8(const uint8_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_uint8(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_uint8(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_uint8(v0);
#endif
}
inline rvd_uint8_m1_t mipp_set1_uint8_m1(const uint8_t v0) {
	return mipp_set1_uint8(v0);
}
inline rvd_uint8_m2_t mipp_set1_uint8_m2(const uint8_t v0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_set1_uint8_m1(v0);
	res.r2 = mipp_set1_uint8_m1(v0);
	return res;
}
inline rvd_uint8_m4_t mipp_set1_uint8_m4(const uint8_t v0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_set1_uint8_m2(v0);
	res.r2 = mipp_set1_uint8_m2(v0);
	return res;
}
inline rvd_uint8_m8_t mipp_set1_uint8_m8(const uint8_t v0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_set1_uint8_m4(v0);
	res.r2 = mipp_set1_uint8_m4(v0);
	return res;
}
inline rvm_int64_t mipp_set1_k_int64(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_int64(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_int64(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_int64(v0);
#endif
}
inline rvm_int64_m1_t mipp_set1_k_int64_m1(const int32_t v0) {
	return mipp_set1_k_int64(v0);
}
inline rvm_int64_m2_t mipp_set1_k_int64_m2(const int32_t v0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_set1_k_int64_m1(v0);
	msk.m2 = mipp_set1_k_int64_m1(v0);
	return msk;
}
inline rvm_int64_m4_t mipp_set1_k_int64_m4(const int32_t v0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_set1_k_int64_m2(v0);
	msk.m2 = mipp_set1_k_int64_m2(v0);
	return msk;
}
inline rvm_int64_m8_t mipp_set1_k_int64_m8(const int32_t v0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_set1_k_int64_m4(v0);
	msk.m2 = mipp_set1_k_int64_m4(v0);
	return msk;
}
inline rvm_int32_t mipp_set1_k_int32(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_int32(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_int32(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_int32(v0);
#endif
}
inline rvm_int32_m1_t mipp_set1_k_int32_m1(const int32_t v0) {
	return mipp_set1_k_int32(v0);
}
inline rvm_int32_m2_t mipp_set1_k_int32_m2(const int32_t v0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_set1_k_int32_m1(v0);
	msk.m2 = mipp_set1_k_int32_m1(v0);
	return msk;
}
inline rvm_int32_m4_t mipp_set1_k_int32_m4(const int32_t v0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_set1_k_int32_m2(v0);
	msk.m2 = mipp_set1_k_int32_m2(v0);
	return msk;
}
inline rvm_int32_m8_t mipp_set1_k_int32_m8(const int32_t v0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_set1_k_int32_m4(v0);
	msk.m2 = mipp_set1_k_int32_m4(v0);
	return msk;
}
inline rvm_int16_t mipp_set1_k_int16(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_int16(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_int16(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_int16(v0);
#endif
}
inline rvm_int16_m1_t mipp_set1_k_int16_m1(const int32_t v0) {
	return mipp_set1_k_int16(v0);
}
inline rvm_int16_m2_t mipp_set1_k_int16_m2(const int32_t v0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_set1_k_int16_m1(v0);
	msk.m2 = mipp_set1_k_int16_m1(v0);
	return msk;
}
inline rvm_int16_m4_t mipp_set1_k_int16_m4(const int32_t v0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_set1_k_int16_m2(v0);
	msk.m2 = mipp_set1_k_int16_m2(v0);
	return msk;
}
inline rvm_int16_m8_t mipp_set1_k_int16_m8(const int32_t v0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_set1_k_int16_m4(v0);
	msk.m2 = mipp_set1_k_int16_m4(v0);
	return msk;
}
inline rvm_int8_t mipp_set1_k_int8(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_int8(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_int8(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_int8(v0);
#endif
}
inline rvm_int8_m1_t mipp_set1_k_int8_m1(const int32_t v0) {
	return mipp_set1_k_int8(v0);
}
inline rvm_int8_m2_t mipp_set1_k_int8_m2(const int32_t v0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_set1_k_int8_m1(v0);
	msk.m2 = mipp_set1_k_int8_m1(v0);
	return msk;
}
inline rvm_int8_m4_t mipp_set1_k_int8_m4(const int32_t v0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_set1_k_int8_m2(v0);
	msk.m2 = mipp_set1_k_int8_m2(v0);
	return msk;
}
inline rvm_int8_m8_t mipp_set1_k_int8_m8(const int32_t v0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_set1_k_int8_m4(v0);
	msk.m2 = mipp_set1_k_int8_m4(v0);
	return msk;
}
inline rvm_uint64_t mipp_set1_k_uint64(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_uint64(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_uint64(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_uint64(v0);
#endif
}
inline rvm_uint64_m1_t mipp_set1_k_uint64_m1(const int32_t v0) {
	return mipp_set1_k_uint64(v0);
}
inline rvm_uint64_m2_t mipp_set1_k_uint64_m2(const int32_t v0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_set1_k_uint64_m1(v0);
	msk.m2 = mipp_set1_k_uint64_m1(v0);
	return msk;
}
inline rvm_uint64_m4_t mipp_set1_k_uint64_m4(const int32_t v0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_set1_k_uint64_m2(v0);
	msk.m2 = mipp_set1_k_uint64_m2(v0);
	return msk;
}
inline rvm_uint64_m8_t mipp_set1_k_uint64_m8(const int32_t v0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_set1_k_uint64_m4(v0);
	msk.m2 = mipp_set1_k_uint64_m4(v0);
	return msk;
}
inline rvm_uint32_t mipp_set1_k_uint32(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_uint32(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_uint32(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_uint32(v0);
#endif
}
inline rvm_uint32_m1_t mipp_set1_k_uint32_m1(const int32_t v0) {
	return mipp_set1_k_uint32(v0);
}
inline rvm_uint32_m2_t mipp_set1_k_uint32_m2(const int32_t v0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_set1_k_uint32_m1(v0);
	msk.m2 = mipp_set1_k_uint32_m1(v0);
	return msk;
}
inline rvm_uint32_m4_t mipp_set1_k_uint32_m4(const int32_t v0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_set1_k_uint32_m2(v0);
	msk.m2 = mipp_set1_k_uint32_m2(v0);
	return msk;
}
inline rvm_uint32_m8_t mipp_set1_k_uint32_m8(const int32_t v0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_set1_k_uint32_m4(v0);
	msk.m2 = mipp_set1_k_uint32_m4(v0);
	return msk;
}
inline rvm_uint16_t mipp_set1_k_uint16(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_uint16(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_uint16(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_uint16(v0);
#endif
}
inline rvm_uint16_m1_t mipp_set1_k_uint16_m1(const int32_t v0) {
	return mipp_set1_k_uint16(v0);
}
inline rvm_uint16_m2_t mipp_set1_k_uint16_m2(const int32_t v0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_set1_k_uint16_m1(v0);
	msk.m2 = mipp_set1_k_uint16_m1(v0);
	return msk;
}
inline rvm_uint16_m4_t mipp_set1_k_uint16_m4(const int32_t v0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_set1_k_uint16_m2(v0);
	msk.m2 = mipp_set1_k_uint16_m2(v0);
	return msk;
}
inline rvm_uint16_m8_t mipp_set1_k_uint16_m8(const int32_t v0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_set1_k_uint16_m4(v0);
	msk.m2 = mipp_set1_k_uint16_m4(v0);
	return msk;
}
inline rvm_uint8_t mipp_set1_k_uint8(const int32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_set1_k_uint8(v0);
#elif defined(__AVX__)
	return mipp_avx_set1_k_uint8(v0);
#elif defined(__SSE__)
	return mipp_sse_set1_k_uint8(v0);
#endif
}
inline rvm_uint8_m1_t mipp_set1_k_uint8_m1(const int32_t v0) {
	return mipp_set1_k_uint8(v0);
}
inline rvm_uint8_m2_t mipp_set1_k_uint8_m2(const int32_t v0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_set1_k_uint8_m1(v0);
	msk.m2 = mipp_set1_k_uint8_m1(v0);
	return msk;
}
inline rvm_uint8_m4_t mipp_set1_k_uint8_m4(const int32_t v0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_set1_k_uint8_m2(v0);
	msk.m2 = mipp_set1_k_uint8_m2(v0);
	return msk;
}
inline rvm_uint8_m8_t mipp_set1_k_uint8_m8(const int32_t v0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_set1_k_uint8_m4(v0);
	msk.m2 = mipp_set1_k_uint8_m4(v0);
	return msk;
}
inline rvd_float64_t mipp_maskzld_float64(const rvm_int32_t m0, const float64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_float64(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_float64(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_float64(m0, p0);
#endif
}
inline rvd_float64_m1_t mipp_maskzld_float64_m1(const rvm_int32_m1_t m0, const float64_t* p0) {
	return mipp_maskzld_float64(m0, p0);
}
inline rvd_float64_m2_t mipp_maskzld_float64_m2(const rvm_int32_m2_t m0, const float64_t* p0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_maskzld_float64_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_float64_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float64_m4_t mipp_maskzld_float64_m4(const rvm_int32_m4_t m0, const float64_t* p0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_maskzld_float64_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_float64_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float64_m8_t mipp_maskzld_float64_m8(const rvm_int32_m8_t m0, const float64_t* p0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_maskzld_float64_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_float64_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_float32_t mipp_maskzld_float32(const rvm_int32_t m0, const float32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_float32(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_float32(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_float32(m0, p0);
#endif
}
inline rvd_float32_m1_t mipp_maskzld_float32_m1(const rvm_int32_m1_t m0, const float32_t* p0) {
	return mipp_maskzld_float32(m0, p0);
}
inline rvd_float32_m2_t mipp_maskzld_float32_m2(const rvm_int32_m2_t m0, const float32_t* p0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_maskzld_float32_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_float32_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_float32_m4_t mipp_maskzld_float32_m4(const rvm_int32_m4_t m0, const float32_t* p0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_maskzld_float32_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_float32_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_float32_m8_t mipp_maskzld_float32_m8(const rvm_int32_m8_t m0, const float32_t* p0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_maskzld_float32_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_float32_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int64_t mipp_maskzld_int64(const rvm_int32_t m0, const int64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_int64(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_int64(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_int64(m0, p0);
#endif
}
inline rvd_int64_m1_t mipp_maskzld_int64_m1(const rvm_int32_m1_t m0, const int64_t* p0) {
	return mipp_maskzld_int64(m0, p0);
}
inline rvd_int64_m2_t mipp_maskzld_int64_m2(const rvm_int32_m2_t m0, const int64_t* p0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_maskzld_int64_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_int64_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int64_m4_t mipp_maskzld_int64_m4(const rvm_int32_m4_t m0, const int64_t* p0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_maskzld_int64_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_int64_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int64_m8_t mipp_maskzld_int64_m8(const rvm_int32_m8_t m0, const int64_t* p0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_maskzld_int64_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_int64_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int32_t mipp_maskzld_int32(const rvm_int32_t m0, const int32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_int32(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_int32(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_int32(m0, p0);
#endif
}
inline rvd_int32_m1_t mipp_maskzld_int32_m1(const rvm_int32_m1_t m0, const int32_t* p0) {
	return mipp_maskzld_int32(m0, p0);
}
inline rvd_int32_m2_t mipp_maskzld_int32_m2(const rvm_int32_m2_t m0, const int32_t* p0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_maskzld_int32_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_int32_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int32_m4_t mipp_maskzld_int32_m4(const rvm_int32_m4_t m0, const int32_t* p0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_maskzld_int32_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_int32_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int32_m8_t mipp_maskzld_int32_m8(const rvm_int32_m8_t m0, const int32_t* p0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_maskzld_int32_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_int32_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int16_t mipp_maskzld_int16(const rvm_int32_t m0, const int16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_int16(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_int16(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_int16(m0, p0);
#endif
}
inline rvd_int16_m1_t mipp_maskzld_int16_m1(const rvm_int32_m1_t m0, const int16_t* p0) {
	return mipp_maskzld_int16(m0, p0);
}
inline rvd_int16_m2_t mipp_maskzld_int16_m2(const rvm_int32_m2_t m0, const int16_t* p0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_maskzld_int16_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_int16_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int16_m4_t mipp_maskzld_int16_m4(const rvm_int32_m4_t m0, const int16_t* p0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_maskzld_int16_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_int16_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int16_m8_t mipp_maskzld_int16_m8(const rvm_int32_m8_t m0, const int16_t* p0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_maskzld_int16_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_int16_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_int8_t mipp_maskzld_int8(const rvm_int32_t m0, const int8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_int8(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_int8(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_int8(m0, p0);
#endif
}
inline rvd_int8_m1_t mipp_maskzld_int8_m1(const rvm_int32_m1_t m0, const int8_t* p0) {
	return mipp_maskzld_int8(m0, p0);
}
inline rvd_int8_m2_t mipp_maskzld_int8_m2(const rvm_int32_m2_t m0, const int8_t* p0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_maskzld_int8_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_int8_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_int8_m4_t mipp_maskzld_int8_m4(const rvm_int32_m4_t m0, const int8_t* p0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_maskzld_int8_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_int8_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_int8_m8_t mipp_maskzld_int8_m8(const rvm_int32_m8_t m0, const int8_t* p0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_maskzld_int8_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_int8_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint64_t mipp_maskzld_uint64(const rvm_int32_t m0, const uint64_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_uint64(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_uint64(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_uint64(m0, p0);
#endif
}
inline rvd_uint64_m1_t mipp_maskzld_uint64_m1(const rvm_int32_m1_t m0, const uint64_t* p0) {
	return mipp_maskzld_uint64(m0, p0);
}
inline rvd_uint64_m2_t mipp_maskzld_uint64_m2(const rvm_int32_m2_t m0, const uint64_t* p0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_maskzld_uint64_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_uint64_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint64_m4_t mipp_maskzld_uint64_m4(const rvm_int32_m4_t m0, const uint64_t* p0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_maskzld_uint64_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_uint64_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint64_m8_t mipp_maskzld_uint64_m8(const rvm_int32_m8_t m0, const uint64_t* p0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_maskzld_uint64_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_uint64_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint32_t mipp_maskzld_uint32(const rvm_int32_t m0, const uint32_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_uint32(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_uint32(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_uint32(m0, p0);
#endif
}
inline rvd_uint32_m1_t mipp_maskzld_uint32_m1(const rvm_int32_m1_t m0, const uint32_t* p0) {
	return mipp_maskzld_uint32(m0, p0);
}
inline rvd_uint32_m2_t mipp_maskzld_uint32_m2(const rvm_int32_m2_t m0, const uint32_t* p0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_maskzld_uint32_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_uint32_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint32_m4_t mipp_maskzld_uint32_m4(const rvm_int32_m4_t m0, const uint32_t* p0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_maskzld_uint32_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_uint32_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint32_m8_t mipp_maskzld_uint32_m8(const rvm_int32_m8_t m0, const uint32_t* p0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_maskzld_uint32_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_uint32_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint16_t mipp_maskzld_uint16(const rvm_int32_t m0, const uint16_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_uint16(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_uint16(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_uint16(m0, p0);
#endif
}
inline rvd_uint16_m1_t mipp_maskzld_uint16_m1(const rvm_int32_m1_t m0, const uint16_t* p0) {
	return mipp_maskzld_uint16(m0, p0);
}
inline rvd_uint16_m2_t mipp_maskzld_uint16_m2(const rvm_int32_m2_t m0, const uint16_t* p0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_maskzld_uint16_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_uint16_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint16_m4_t mipp_maskzld_uint16_m4(const rvm_int32_m4_t m0, const uint16_t* p0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_maskzld_uint16_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_uint16_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint16_m8_t mipp_maskzld_uint16_m8(const rvm_int32_m8_t m0, const uint16_t* p0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_maskzld_uint16_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_uint16_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline rvd_uint8_t mipp_maskzld_uint8(const rvm_int32_t m0, const uint8_t* p0) {
#if defined(__AVX512__)
	return mipp_avx512_maskzld_uint8(m0, p0);
#elif defined(__AVX__)
	return mipp_avx_maskzld_uint8(m0, p0);
#elif defined(__SSE__)
	return mipp_sse_maskzld_uint8(m0, p0);
#endif
}
inline rvd_uint8_m1_t mipp_maskzld_uint8_m1(const rvm_int32_m1_t m0, const uint8_t* p0) {
	return mipp_maskzld_uint8(m0, p0);
}
inline rvd_uint8_m2_t mipp_maskzld_uint8_m2(const rvm_int32_m2_t m0, const uint8_t* p0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_maskzld_uint8_m1(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	res.r2 = mipp_maskzld_uint8_m1(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1));
	return res;
}
inline rvd_uint8_m4_t mipp_maskzld_uint8_m4(const rvm_int32_m4_t m0, const uint8_t* p0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_maskzld_uint8_m2(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	res.r2 = mipp_maskzld_uint8_m2(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2));
	return res;
}
inline rvd_uint8_m8_t mipp_maskzld_uint8_m8(const rvm_int32_m8_t m0, const uint8_t* p0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_maskzld_uint8_m4(m0.m1, p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	res.r2 = mipp_maskzld_uint8_m4(m0.m2, p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4));
	return res;
}
inline void mipp_maskst_float64(float64_t* p0, const rvm_int32_t m0, const rvd_float64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_float64(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_float64(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_float64(p0, m0, r0);
#endif
}
inline void mipp_maskst_float64_m1(float64_t* p0, const rvm_int32_m1_t m0, const rvd_float64_m1_t r0) {
	mipp_maskst_float64(p0, m0, r0);
}
inline void mipp_maskst_float64_m2(float64_t* p0, const rvm_int32_m2_t m0, const rvd_float64_m2_t r0) {
	mipp_maskst_float64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_float64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_float64_m4(float64_t* p0, const rvm_int32_m4_t m0, const rvd_float64_m4_t r0) {
	mipp_maskst_float64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_float64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_float64_m8(float64_t* p0, const rvm_int32_m8_t m0, const rvd_float64_m8_t r0) {
	mipp_maskst_float64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_float64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_float32(float32_t* p0, const rvm_int32_t m0, const rvd_float32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_float32(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_float32(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_float32(p0, m0, r0);
#endif
}
inline void mipp_maskst_float32_m1(float32_t* p0, const rvm_int32_m1_t m0, const rvd_float32_m1_t r0) {
	mipp_maskst_float32(p0, m0, r0);
}
inline void mipp_maskst_float32_m2(float32_t* p0, const rvm_int32_m2_t m0, const rvd_float32_m2_t r0) {
	mipp_maskst_float32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_float32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_float32_m4(float32_t* p0, const rvm_int32_m4_t m0, const rvd_float32_m4_t r0) {
	mipp_maskst_float32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_float32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_float32_m8(float32_t* p0, const rvm_int32_m8_t m0, const rvd_float32_m8_t r0) {
	mipp_maskst_float32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_float32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_int64(int64_t* p0, const rvm_int32_t m0, const rvd_int64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_int64(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_int64(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_int64(p0, m0, r0);
#endif
}
inline void mipp_maskst_int64_m1(int64_t* p0, const rvm_int32_m1_t m0, const rvd_int64_m1_t r0) {
	mipp_maskst_int64(p0, m0, r0);
}
inline void mipp_maskst_int64_m2(int64_t* p0, const rvm_int32_m2_t m0, const rvd_int64_m2_t r0) {
	mipp_maskst_int64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_int64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_int64_m4(int64_t* p0, const rvm_int32_m4_t m0, const rvd_int64_m4_t r0) {
	mipp_maskst_int64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_int64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_int64_m8(int64_t* p0, const rvm_int32_m8_t m0, const rvd_int64_m8_t r0) {
	mipp_maskst_int64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_int64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_int32(int32_t* p0, const rvm_int32_t m0, const rvd_int32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_int32(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_int32(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_int32(p0, m0, r0);
#endif
}
inline void mipp_maskst_int32_m1(int32_t* p0, const rvm_int32_m1_t m0, const rvd_int32_m1_t r0) {
	mipp_maskst_int32(p0, m0, r0);
}
inline void mipp_maskst_int32_m2(int32_t* p0, const rvm_int32_m2_t m0, const rvd_int32_m2_t r0) {
	mipp_maskst_int32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_int32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_int32_m4(int32_t* p0, const rvm_int32_m4_t m0, const rvd_int32_m4_t r0) {
	mipp_maskst_int32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_int32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_int32_m8(int32_t* p0, const rvm_int32_m8_t m0, const rvd_int32_m8_t r0) {
	mipp_maskst_int32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_int32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_int16(int16_t* p0, const rvm_int32_t m0, const rvd_int16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_int16(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_int16(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_int16(p0, m0, r0);
#endif
}
inline void mipp_maskst_int16_m1(int16_t* p0, const rvm_int32_m1_t m0, const rvd_int16_m1_t r0) {
	mipp_maskst_int16(p0, m0, r0);
}
inline void mipp_maskst_int16_m2(int16_t* p0, const rvm_int32_m2_t m0, const rvd_int16_m2_t r0) {
	mipp_maskst_int16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_int16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_int16_m4(int16_t* p0, const rvm_int32_m4_t m0, const rvd_int16_m4_t r0) {
	mipp_maskst_int16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_int16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_int16_m8(int16_t* p0, const rvm_int32_m8_t m0, const rvd_int16_m8_t r0) {
	mipp_maskst_int16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_int16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_int8(int8_t* p0, const rvm_int32_t m0, const rvd_int8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_int8(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_int8(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_int8(p0, m0, r0);
#endif
}
inline void mipp_maskst_int8_m1(int8_t* p0, const rvm_int32_m1_t m0, const rvd_int8_m1_t r0) {
	mipp_maskst_int8(p0, m0, r0);
}
inline void mipp_maskst_int8_m2(int8_t* p0, const rvm_int32_m2_t m0, const rvd_int8_m2_t r0) {
	mipp_maskst_int8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_int8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_int8_m4(int8_t* p0, const rvm_int32_m4_t m0, const rvd_int8_m4_t r0) {
	mipp_maskst_int8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_int8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_int8_m8(int8_t* p0, const rvm_int32_m8_t m0, const rvd_int8_m8_t r0) {
	mipp_maskst_int8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_int8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_uint64(uint64_t* p0, const rvm_int32_t m0, const rvd_uint64_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_uint64(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_uint64(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_uint64(p0, m0, r0);
#endif
}
inline void mipp_maskst_uint64_m1(uint64_t* p0, const rvm_int32_m1_t m0, const rvd_uint64_m1_t r0) {
	mipp_maskst_uint64(p0, m0, r0);
}
inline void mipp_maskst_uint64_m2(uint64_t* p0, const rvm_int32_m2_t m0, const rvd_uint64_m2_t r0) {
	mipp_maskst_uint64_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_uint64_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_uint64_m4(uint64_t* p0, const rvm_int32_m4_t m0, const rvd_uint64_m4_t r0) {
	mipp_maskst_uint64_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_uint64_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_uint64_m8(uint64_t* p0, const rvm_int32_m8_t m0, const rvd_uint64_m8_t r0) {
	mipp_maskst_uint64_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_uint64_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_uint32(uint32_t* p0, const rvm_int32_t m0, const rvd_uint32_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_uint32(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_uint32(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_uint32(p0, m0, r0);
#endif
}
inline void mipp_maskst_uint32_m1(uint32_t* p0, const rvm_int32_m1_t m0, const rvd_uint32_m1_t r0) {
	mipp_maskst_uint32(p0, m0, r0);
}
inline void mipp_maskst_uint32_m2(uint32_t* p0, const rvm_int32_m2_t m0, const rvd_uint32_m2_t r0) {
	mipp_maskst_uint32_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_uint32_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_uint32_m4(uint32_t* p0, const rvm_int32_m4_t m0, const rvd_uint32_m4_t r0) {
	mipp_maskst_uint32_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_uint32_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_uint32_m8(uint32_t* p0, const rvm_int32_m8_t m0, const rvd_uint32_m8_t r0) {
	mipp_maskst_uint32_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_uint32_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_uint16(uint16_t* p0, const rvm_int32_t m0, const rvd_uint16_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_uint16(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_uint16(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_uint16(p0, m0, r0);
#endif
}
inline void mipp_maskst_uint16_m1(uint16_t* p0, const rvm_int32_m1_t m0, const rvd_uint16_m1_t r0) {
	mipp_maskst_uint16(p0, m0, r0);
}
inline void mipp_maskst_uint16_m2(uint16_t* p0, const rvm_int32_m2_t m0, const rvd_uint16_m2_t r0) {
	mipp_maskst_uint16_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_uint16_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_uint16_m4(uint16_t* p0, const rvm_int32_m4_t m0, const rvd_uint16_m4_t r0) {
	mipp_maskst_uint16_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_uint16_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_uint16_m8(uint16_t* p0, const rvm_int32_m8_t m0, const rvd_uint16_m8_t r0) {
	mipp_maskst_uint16_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_uint16_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline void mipp_maskst_uint8(uint8_t* p0, const rvm_int32_t m0, const rvd_uint8_t r0) {
#if defined(__AVX512__)
	mipp_avx512_maskst_uint8(p0, m0, r0);
#elif defined(__AVX__)
	mipp_avx_maskst_uint8(p0, m0, r0);
#elif defined(__SSE__)
	mipp_sse_maskst_uint8(p0, m0, r0);
#endif
}
inline void mipp_maskst_uint8_m1(uint8_t* p0, const rvm_int32_m1_t m0, const rvd_uint8_m1_t r0) {
	mipp_maskst_uint8(p0, m0, r0);
}
inline void mipp_maskst_uint8_m2(uint8_t* p0, const rvm_int32_m2_t m0, const rvd_uint8_m2_t r0) {
	mipp_maskst_uint8_m1(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m1, r0.r1);
	mipp_maskst_uint8_m1(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 1), m0.m2, r0.r2);
}
inline void mipp_maskst_uint8_m4(uint8_t* p0, const rvm_int32_m4_t m0, const rvd_uint8_m4_t r0) {
	mipp_maskst_uint8_m2(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m1, r0.r1);
	mipp_maskst_uint8_m2(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 2), m0.m2, r0.r2);
}
inline void mipp_maskst_uint8_m8(uint8_t* p0, const rvm_int32_m8_t m0, const rvd_uint8_m8_t r0) {
	mipp_maskst_uint8_m4(p0 + 0*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m1, r0.r1);
	mipp_maskst_uint8_m4(p0 + 1*MIPP_LMUL_STRIDE(sizeof(*p0), 4), m0.m2, r0.r2);
}
inline rvd_float64_t mipp_set0_float64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_float64();
#elif defined(__AVX__)
	return mipp_avx_set0_float64();
#elif defined(__SSE__)
	return mipp_sse_set0_float64();
#endif
}
inline rvd_float64_m1_t mipp_set0_float64_m1() {
	return mipp_set0_float64();
}
inline rvd_float64_m2_t mipp_set0_float64_m2() {
	rvd_float64_m2_t res;
	res.r1 = mipp_set0_float64_m1();
	res.r2 = mipp_set0_float64_m1();
	return res;
}
inline rvd_float64_m4_t mipp_set0_float64_m4() {
	rvd_float64_m4_t res;
	res.r1 = mipp_set0_float64_m2();
	res.r2 = mipp_set0_float64_m2();
	return res;
}
inline rvd_float64_m8_t mipp_set0_float64_m8() {
	rvd_float64_m8_t res;
	res.r1 = mipp_set0_float64_m4();
	res.r2 = mipp_set0_float64_m4();
	return res;
}
inline rvd_float32_t mipp_set0_float32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_float32();
#elif defined(__AVX__)
	return mipp_avx_set0_float32();
#elif defined(__SSE__)
	return mipp_sse_set0_float32();
#endif
}
inline rvd_float32_m1_t mipp_set0_float32_m1() {
	return mipp_set0_float32();
}
inline rvd_float32_m2_t mipp_set0_float32_m2() {
	rvd_float32_m2_t res;
	res.r1 = mipp_set0_float32_m1();
	res.r2 = mipp_set0_float32_m1();
	return res;
}
inline rvd_float32_m4_t mipp_set0_float32_m4() {
	rvd_float32_m4_t res;
	res.r1 = mipp_set0_float32_m2();
	res.r2 = mipp_set0_float32_m2();
	return res;
}
inline rvd_float32_m8_t mipp_set0_float32_m8() {
	rvd_float32_m8_t res;
	res.r1 = mipp_set0_float32_m4();
	res.r2 = mipp_set0_float32_m4();
	return res;
}
inline rvd_int64_t mipp_set0_int64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_int64();
#elif defined(__AVX__)
	return mipp_avx_set0_int64();
#elif defined(__SSE__)
	return mipp_sse_set0_int64();
#endif
}
inline rvd_int64_m1_t mipp_set0_int64_m1() {
	return mipp_set0_int64();
}
inline rvd_int64_m2_t mipp_set0_int64_m2() {
	rvd_int64_m2_t res;
	res.r1 = mipp_set0_int64_m1();
	res.r2 = mipp_set0_int64_m1();
	return res;
}
inline rvd_int64_m4_t mipp_set0_int64_m4() {
	rvd_int64_m4_t res;
	res.r1 = mipp_set0_int64_m2();
	res.r2 = mipp_set0_int64_m2();
	return res;
}
inline rvd_int64_m8_t mipp_set0_int64_m8() {
	rvd_int64_m8_t res;
	res.r1 = mipp_set0_int64_m4();
	res.r2 = mipp_set0_int64_m4();
	return res;
}
inline rvd_int32_t mipp_set0_int32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_int32();
#elif defined(__AVX__)
	return mipp_avx_set0_int32();
#elif defined(__SSE__)
	return mipp_sse_set0_int32();
#endif
}
inline rvd_int32_m1_t mipp_set0_int32_m1() {
	return mipp_set0_int32();
}
inline rvd_int32_m2_t mipp_set0_int32_m2() {
	rvd_int32_m2_t res;
	res.r1 = mipp_set0_int32_m1();
	res.r2 = mipp_set0_int32_m1();
	return res;
}
inline rvd_int32_m4_t mipp_set0_int32_m4() {
	rvd_int32_m4_t res;
	res.r1 = mipp_set0_int32_m2();
	res.r2 = mipp_set0_int32_m2();
	return res;
}
inline rvd_int32_m8_t mipp_set0_int32_m8() {
	rvd_int32_m8_t res;
	res.r1 = mipp_set0_int32_m4();
	res.r2 = mipp_set0_int32_m4();
	return res;
}
inline rvd_int16_t mipp_set0_int16() {
#if defined(__AVX512__)
	return mipp_avx512_set0_int16();
#elif defined(__AVX__)
	return mipp_avx_set0_int16();
#elif defined(__SSE__)
	return mipp_sse_set0_int16();
#endif
}
inline rvd_int16_m1_t mipp_set0_int16_m1() {
	return mipp_set0_int16();
}
inline rvd_int16_m2_t mipp_set0_int16_m2() {
	rvd_int16_m2_t res;
	res.r1 = mipp_set0_int16_m1();
	res.r2 = mipp_set0_int16_m1();
	return res;
}
inline rvd_int16_m4_t mipp_set0_int16_m4() {
	rvd_int16_m4_t res;
	res.r1 = mipp_set0_int16_m2();
	res.r2 = mipp_set0_int16_m2();
	return res;
}
inline rvd_int16_m8_t mipp_set0_int16_m8() {
	rvd_int16_m8_t res;
	res.r1 = mipp_set0_int16_m4();
	res.r2 = mipp_set0_int16_m4();
	return res;
}
inline rvd_int8_t mipp_set0_int8() {
#if defined(__AVX512__)
	return mipp_avx512_set0_int8();
#elif defined(__AVX__)
	return mipp_avx_set0_int8();
#elif defined(__SSE__)
	return mipp_sse_set0_int8();
#endif
}
inline rvd_int8_m1_t mipp_set0_int8_m1() {
	return mipp_set0_int8();
}
inline rvd_int8_m2_t mipp_set0_int8_m2() {
	rvd_int8_m2_t res;
	res.r1 = mipp_set0_int8_m1();
	res.r2 = mipp_set0_int8_m1();
	return res;
}
inline rvd_int8_m4_t mipp_set0_int8_m4() {
	rvd_int8_m4_t res;
	res.r1 = mipp_set0_int8_m2();
	res.r2 = mipp_set0_int8_m2();
	return res;
}
inline rvd_int8_m8_t mipp_set0_int8_m8() {
	rvd_int8_m8_t res;
	res.r1 = mipp_set0_int8_m4();
	res.r2 = mipp_set0_int8_m4();
	return res;
}
inline rvd_uint64_t mipp_set0_uint64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_uint64();
#elif defined(__AVX__)
	return mipp_avx_set0_uint64();
#elif defined(__SSE__)
	return mipp_sse_set0_uint64();
#endif
}
inline rvd_uint64_m1_t mipp_set0_uint64_m1() {
	return mipp_set0_uint64();
}
inline rvd_uint64_m2_t mipp_set0_uint64_m2() {
	rvd_uint64_m2_t res;
	res.r1 = mipp_set0_uint64_m1();
	res.r2 = mipp_set0_uint64_m1();
	return res;
}
inline rvd_uint64_m4_t mipp_set0_uint64_m4() {
	rvd_uint64_m4_t res;
	res.r1 = mipp_set0_uint64_m2();
	res.r2 = mipp_set0_uint64_m2();
	return res;
}
inline rvd_uint64_m8_t mipp_set0_uint64_m8() {
	rvd_uint64_m8_t res;
	res.r1 = mipp_set0_uint64_m4();
	res.r2 = mipp_set0_uint64_m4();
	return res;
}
inline rvd_uint32_t mipp_set0_uint32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_uint32();
#elif defined(__AVX__)
	return mipp_avx_set0_uint32();
#elif defined(__SSE__)
	return mipp_sse_set0_uint32();
#endif
}
inline rvd_uint32_m1_t mipp_set0_uint32_m1() {
	return mipp_set0_uint32();
}
inline rvd_uint32_m2_t mipp_set0_uint32_m2() {
	rvd_uint32_m2_t res;
	res.r1 = mipp_set0_uint32_m1();
	res.r2 = mipp_set0_uint32_m1();
	return res;
}
inline rvd_uint32_m4_t mipp_set0_uint32_m4() {
	rvd_uint32_m4_t res;
	res.r1 = mipp_set0_uint32_m2();
	res.r2 = mipp_set0_uint32_m2();
	return res;
}
inline rvd_uint32_m8_t mipp_set0_uint32_m8() {
	rvd_uint32_m8_t res;
	res.r1 = mipp_set0_uint32_m4();
	res.r2 = mipp_set0_uint32_m4();
	return res;
}
inline rvd_uint16_t mipp_set0_uint16() {
#if defined(__AVX512__)
	return mipp_avx512_set0_uint16();
#elif defined(__AVX__)
	return mipp_avx_set0_uint16();
#elif defined(__SSE__)
	return mipp_sse_set0_uint16();
#endif
}
inline rvd_uint16_m1_t mipp_set0_uint16_m1() {
	return mipp_set0_uint16();
}
inline rvd_uint16_m2_t mipp_set0_uint16_m2() {
	rvd_uint16_m2_t res;
	res.r1 = mipp_set0_uint16_m1();
	res.r2 = mipp_set0_uint16_m1();
	return res;
}
inline rvd_uint16_m4_t mipp_set0_uint16_m4() {
	rvd_uint16_m4_t res;
	res.r1 = mipp_set0_uint16_m2();
	res.r2 = mipp_set0_uint16_m2();
	return res;
}
inline rvd_uint16_m8_t mipp_set0_uint16_m8() {
	rvd_uint16_m8_t res;
	res.r1 = mipp_set0_uint16_m4();
	res.r2 = mipp_set0_uint16_m4();
	return res;
}
inline rvd_uint8_t mipp_set0_uint8() {
#if defined(__AVX512__)
	return mipp_avx512_set0_uint8();
#elif defined(__AVX__)
	return mipp_avx_set0_uint8();
#elif defined(__SSE__)
	return mipp_sse_set0_uint8();
#endif
}
inline rvd_uint8_m1_t mipp_set0_uint8_m1() {
	return mipp_set0_uint8();
}
inline rvd_uint8_m2_t mipp_set0_uint8_m2() {
	rvd_uint8_m2_t res;
	res.r1 = mipp_set0_uint8_m1();
	res.r2 = mipp_set0_uint8_m1();
	return res;
}
inline rvd_uint8_m4_t mipp_set0_uint8_m4() {
	rvd_uint8_m4_t res;
	res.r1 = mipp_set0_uint8_m2();
	res.r2 = mipp_set0_uint8_m2();
	return res;
}
inline rvd_uint8_m8_t mipp_set0_uint8_m8() {
	rvd_uint8_m8_t res;
	res.r1 = mipp_set0_uint8_m4();
	res.r2 = mipp_set0_uint8_m4();
	return res;
}
inline rvm_float64_t mipp_set0_k_float64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_float64();
#elif defined(__AVX__)
	return mipp_avx_set0_k_float64();
#elif defined(__SSE__)
	return mipp_sse_set0_k_float64();
#endif
}
inline rvm_float64_m1_t mipp_set0_k_float64_m1() {
	return mipp_set0_k_float64();
}
inline rvm_float64_m2_t mipp_set0_k_float64_m2() {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_set0_k_float64_m1();
	msk.m2 = mipp_set0_k_float64_m1();
	return msk;
}
inline rvm_float64_m4_t mipp_set0_k_float64_m4() {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_set0_k_float64_m2();
	msk.m2 = mipp_set0_k_float64_m2();
	return msk;
}
inline rvm_float64_m8_t mipp_set0_k_float64_m8() {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_set0_k_float64_m4();
	msk.m2 = mipp_set0_k_float64_m4();
	return msk;
}
inline rvm_float32_t mipp_set0_k_float32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_float32();
#elif defined(__AVX__)
	return mipp_avx_set0_k_float32();
#elif defined(__SSE__)
	return mipp_sse_set0_k_float32();
#endif
}
inline rvm_float32_m1_t mipp_set0_k_float32_m1() {
	return mipp_set0_k_float32();
}
inline rvm_float32_m2_t mipp_set0_k_float32_m2() {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_set0_k_float32_m1();
	msk.m2 = mipp_set0_k_float32_m1();
	return msk;
}
inline rvm_float32_m4_t mipp_set0_k_float32_m4() {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_set0_k_float32_m2();
	msk.m2 = mipp_set0_k_float32_m2();
	return msk;
}
inline rvm_float32_m8_t mipp_set0_k_float32_m8() {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_set0_k_float32_m4();
	msk.m2 = mipp_set0_k_float32_m4();
	return msk;
}
inline rvm_int64_t mipp_set0_k_int64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_int64();
#elif defined(__AVX__)
	return mipp_avx_set0_k_int64();
#elif defined(__SSE__)
	return mipp_sse_set0_k_int64();
#endif
}
inline rvm_int64_m1_t mipp_set0_k_int64_m1() {
	return mipp_set0_k_int64();
}
inline rvm_int64_m2_t mipp_set0_k_int64_m2() {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_set0_k_int64_m1();
	msk.m2 = mipp_set0_k_int64_m1();
	return msk;
}
inline rvm_int64_m4_t mipp_set0_k_int64_m4() {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_set0_k_int64_m2();
	msk.m2 = mipp_set0_k_int64_m2();
	return msk;
}
inline rvm_int64_m8_t mipp_set0_k_int64_m8() {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_set0_k_int64_m4();
	msk.m2 = mipp_set0_k_int64_m4();
	return msk;
}
inline rvm_int32_t mipp_set0_k_int32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_int32();
#elif defined(__AVX__)
	return mipp_avx_set0_k_int32();
#elif defined(__SSE__)
	return mipp_sse_set0_k_int32();
#endif
}
inline rvm_int32_m1_t mipp_set0_k_int32_m1() {
	return mipp_set0_k_int32();
}
inline rvm_int32_m2_t mipp_set0_k_int32_m2() {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_set0_k_int32_m1();
	msk.m2 = mipp_set0_k_int32_m1();
	return msk;
}
inline rvm_int32_m4_t mipp_set0_k_int32_m4() {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_set0_k_int32_m2();
	msk.m2 = mipp_set0_k_int32_m2();
	return msk;
}
inline rvm_int32_m8_t mipp_set0_k_int32_m8() {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_set0_k_int32_m4();
	msk.m2 = mipp_set0_k_int32_m4();
	return msk;
}
inline rvm_int16_t mipp_set0_k_int16() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_int16();
#elif defined(__AVX__)
	return mipp_avx_set0_k_int16();
#elif defined(__SSE__)
	return mipp_sse_set0_k_int16();
#endif
}
inline rvm_int16_m1_t mipp_set0_k_int16_m1() {
	return mipp_set0_k_int16();
}
inline rvm_int16_m2_t mipp_set0_k_int16_m2() {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_set0_k_int16_m1();
	msk.m2 = mipp_set0_k_int16_m1();
	return msk;
}
inline rvm_int16_m4_t mipp_set0_k_int16_m4() {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_set0_k_int16_m2();
	msk.m2 = mipp_set0_k_int16_m2();
	return msk;
}
inline rvm_int16_m8_t mipp_set0_k_int16_m8() {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_set0_k_int16_m4();
	msk.m2 = mipp_set0_k_int16_m4();
	return msk;
}
inline rvm_int8_t mipp_set0_k_int8() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_int8();
#elif defined(__AVX__)
	return mipp_avx_set0_k_int8();
#elif defined(__SSE__)
	return mipp_sse_set0_k_int8();
#endif
}
inline rvm_int8_m1_t mipp_set0_k_int8_m1() {
	return mipp_set0_k_int8();
}
inline rvm_int8_m2_t mipp_set0_k_int8_m2() {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_set0_k_int8_m1();
	msk.m2 = mipp_set0_k_int8_m1();
	return msk;
}
inline rvm_int8_m4_t mipp_set0_k_int8_m4() {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_set0_k_int8_m2();
	msk.m2 = mipp_set0_k_int8_m2();
	return msk;
}
inline rvm_int8_m8_t mipp_set0_k_int8_m8() {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_set0_k_int8_m4();
	msk.m2 = mipp_set0_k_int8_m4();
	return msk;
}
inline rvm_uint64_t mipp_set0_k_uint64() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_uint64();
#elif defined(__AVX__)
	return mipp_avx_set0_k_uint64();
#elif defined(__SSE__)
	return mipp_sse_set0_k_uint64();
#endif
}
inline rvm_uint64_m1_t mipp_set0_k_uint64_m1() {
	return mipp_set0_k_uint64();
}
inline rvm_uint64_m2_t mipp_set0_k_uint64_m2() {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_set0_k_uint64_m1();
	msk.m2 = mipp_set0_k_uint64_m1();
	return msk;
}
inline rvm_uint64_m4_t mipp_set0_k_uint64_m4() {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_set0_k_uint64_m2();
	msk.m2 = mipp_set0_k_uint64_m2();
	return msk;
}
inline rvm_uint64_m8_t mipp_set0_k_uint64_m8() {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_set0_k_uint64_m4();
	msk.m2 = mipp_set0_k_uint64_m4();
	return msk;
}
inline rvm_uint32_t mipp_set0_k_uint32() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_uint32();
#elif defined(__AVX__)
	return mipp_avx_set0_k_uint32();
#elif defined(__SSE__)
	return mipp_sse_set0_k_uint32();
#endif
}
inline rvm_uint32_m1_t mipp_set0_k_uint32_m1() {
	return mipp_set0_k_uint32();
}
inline rvm_uint32_m2_t mipp_set0_k_uint32_m2() {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_set0_k_uint32_m1();
	msk.m2 = mipp_set0_k_uint32_m1();
	return msk;
}
inline rvm_uint32_m4_t mipp_set0_k_uint32_m4() {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_set0_k_uint32_m2();
	msk.m2 = mipp_set0_k_uint32_m2();
	return msk;
}
inline rvm_uint32_m8_t mipp_set0_k_uint32_m8() {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_set0_k_uint32_m4();
	msk.m2 = mipp_set0_k_uint32_m4();
	return msk;
}
inline rvm_uint16_t mipp_set0_k_uint16() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_uint16();
#elif defined(__AVX__)
	return mipp_avx_set0_k_uint16();
#elif defined(__SSE__)
	return mipp_sse_set0_k_uint16();
#endif
}
inline rvm_uint16_m1_t mipp_set0_k_uint16_m1() {
	return mipp_set0_k_uint16();
}
inline rvm_uint16_m2_t mipp_set0_k_uint16_m2() {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_set0_k_uint16_m1();
	msk.m2 = mipp_set0_k_uint16_m1();
	return msk;
}
inline rvm_uint16_m4_t mipp_set0_k_uint16_m4() {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_set0_k_uint16_m2();
	msk.m2 = mipp_set0_k_uint16_m2();
	return msk;
}
inline rvm_uint16_m8_t mipp_set0_k_uint16_m8() {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_set0_k_uint16_m4();
	msk.m2 = mipp_set0_k_uint16_m4();
	return msk;
}
inline rvm_uint8_t mipp_set0_k_uint8() {
#if defined(__AVX512__)
	return mipp_avx512_set0_k_uint8();
#elif defined(__AVX__)
	return mipp_avx_set0_k_uint8();
#elif defined(__SSE__)
	return mipp_sse_set0_k_uint8();
#endif
}
inline rvm_uint8_m1_t mipp_set0_k_uint8_m1() {
	return mipp_set0_k_uint8();
}
inline rvm_uint8_m2_t mipp_set0_k_uint8_m2() {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_set0_k_uint8_m1();
	msk.m2 = mipp_set0_k_uint8_m1();
	return msk;
}
inline rvm_uint8_m4_t mipp_set0_k_uint8_m4() {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_set0_k_uint8_m2();
	msk.m2 = mipp_set0_k_uint8_m2();
	return msk;
}
inline rvm_uint8_m8_t mipp_set0_k_uint8_m8() {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_set0_k_uint8_m4();
	msk.m2 = mipp_set0_k_uint8_m4();
	return msk;
}
inline float64_t mipp_get_float64(const rvd_float64_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_float64(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_float64(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_float64(r0, v0);
#endif
}
inline float64_t mipp_get_float64_m1(const rvd_float64_m1_t r0, const uint32_t v0) {
	return mipp_get_float64(r0, v0);
}
inline float64_t mipp_get_float64_m2(const rvd_float64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m2");
	exit(-1);
}
inline float64_t mipp_get_float64_m4(const rvd_float64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m4");
	exit(-1);
}
inline float64_t mipp_get_float64_m8(const rvd_float64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float64_m8");
	exit(-1);
}
inline float32_t mipp_get_float32(const rvd_float32_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_float32(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_float32(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_float32(r0, v0);
#endif
}
inline float32_t mipp_get_float32_m1(const rvd_float32_m1_t r0, const uint32_t v0) {
	return mipp_get_float32(r0, v0);
}
inline float32_t mipp_get_float32_m2(const rvd_float32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m2");
	exit(-1);
}
inline float32_t mipp_get_float32_m4(const rvd_float32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m4");
	exit(-1);
}
inline float32_t mipp_get_float32_m8(const rvd_float32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_float32_m8");
	exit(-1);
}
inline int64_t mipp_get_int64(const rvd_int64_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_int64(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_int64(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_int64(r0, v0);
#endif
}
inline int64_t mipp_get_int64_m1(const rvd_int64_m1_t r0, const uint32_t v0) {
	return mipp_get_int64(r0, v0);
}
inline int64_t mipp_get_int64_m2(const rvd_int64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m2");
	exit(-1);
}
inline int64_t mipp_get_int64_m4(const rvd_int64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m4");
	exit(-1);
}
inline int64_t mipp_get_int64_m8(const rvd_int64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int64_m8");
	exit(-1);
}
inline int32_t mipp_get_int32(const rvd_int32_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_int32(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_int32(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_int32(r0, v0);
#endif
}
inline int32_t mipp_get_int32_m1(const rvd_int32_m1_t r0, const uint32_t v0) {
	return mipp_get_int32(r0, v0);
}
inline int32_t mipp_get_int32_m2(const rvd_int32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m2");
	exit(-1);
}
inline int32_t mipp_get_int32_m4(const rvd_int32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m4");
	exit(-1);
}
inline int32_t mipp_get_int32_m8(const rvd_int32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int32_m8");
	exit(-1);
}
inline int16_t mipp_get_int16(const rvd_int16_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_int16(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_int16(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_int16(r0, v0);
#endif
}
inline int16_t mipp_get_int16_m1(const rvd_int16_m1_t r0, const uint32_t v0) {
	return mipp_get_int16(r0, v0);
}
inline int16_t mipp_get_int16_m2(const rvd_int16_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m2");
	exit(-1);
}
inline int16_t mipp_get_int16_m4(const rvd_int16_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m4");
	exit(-1);
}
inline int16_t mipp_get_int16_m8(const rvd_int16_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int16_m8");
	exit(-1);
}
inline int8_t mipp_get_int8(const rvd_int8_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_int8(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_int8(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_int8(r0, v0);
#endif
}
inline int8_t mipp_get_int8_m1(const rvd_int8_m1_t r0, const uint32_t v0) {
	return mipp_get_int8(r0, v0);
}
inline int8_t mipp_get_int8_m2(const rvd_int8_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m2");
	exit(-1);
}
inline int8_t mipp_get_int8_m4(const rvd_int8_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m4");
	exit(-1);
}
inline int8_t mipp_get_int8_m8(const rvd_int8_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_int8_m8");
	exit(-1);
}
inline uint64_t mipp_get_uint64(const rvd_uint64_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_uint64(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_uint64(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_uint64(r0, v0);
#endif
}
inline uint64_t mipp_get_uint64_m1(const rvd_uint64_m1_t r0, const uint32_t v0) {
	return mipp_get_uint64(r0, v0);
}
inline uint64_t mipp_get_uint64_m2(const rvd_uint64_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m2");
	exit(-1);
}
inline uint64_t mipp_get_uint64_m4(const rvd_uint64_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m4");
	exit(-1);
}
inline uint64_t mipp_get_uint64_m8(const rvd_uint64_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint64_m8");
	exit(-1);
}
inline uint32_t mipp_get_uint32(const rvd_uint32_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_uint32(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_uint32(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_uint32(r0, v0);
#endif
}
inline uint32_t mipp_get_uint32_m1(const rvd_uint32_m1_t r0, const uint32_t v0) {
	return mipp_get_uint32(r0, v0);
}
inline uint32_t mipp_get_uint32_m2(const rvd_uint32_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m2");
	exit(-1);
}
inline uint32_t mipp_get_uint32_m4(const rvd_uint32_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m4");
	exit(-1);
}
inline uint32_t mipp_get_uint32_m8(const rvd_uint32_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint32_m8");
	exit(-1);
}
inline uint16_t mipp_get_uint16(const rvd_uint16_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_uint16(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_uint16(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_uint16(r0, v0);
#endif
}
inline uint16_t mipp_get_uint16_m1(const rvd_uint16_m1_t r0, const uint32_t v0) {
	return mipp_get_uint16(r0, v0);
}
inline uint16_t mipp_get_uint16_m2(const rvd_uint16_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m2");
	exit(-1);
}
inline uint16_t mipp_get_uint16_m4(const rvd_uint16_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m4");
	exit(-1);
}
inline uint16_t mipp_get_uint16_m8(const rvd_uint16_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint16_m8");
	exit(-1);
}
inline uint8_t mipp_get_uint8(const rvd_uint8_t r0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_uint8(r0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_uint8(r0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_uint8(r0, v0);
#endif
}
inline uint8_t mipp_get_uint8_m1(const rvd_uint8_m1_t r0, const uint32_t v0) {
	return mipp_get_uint8(r0, v0);
}
inline uint8_t mipp_get_uint8_m2(const rvd_uint8_m2_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m2");
	exit(-1);
}
inline uint8_t mipp_get_uint8_m4(const rvd_uint8_m4_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m4");
	exit(-1);
}
inline uint8_t mipp_get_uint8_m8(const rvd_uint8_m8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_uint8_m8");
	exit(-1);
}
inline float64_t mipp_get_k_float64(const rvm_float64_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_float64(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_float64(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_float64(m0, v0);
#endif
}
inline float64_t mipp_get_k_float64_m1(const rvm_float64_m1_t m0, const uint32_t v0) {
	return mipp_get_k_float64(m0, v0);
}
inline float64_t mipp_get_k_float64_m2(const rvm_float64_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float64_m2");
	exit(-1);
}
inline float64_t mipp_get_k_float64_m4(const rvm_float64_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float64_m4");
	exit(-1);
}
inline float64_t mipp_get_k_float64_m8(const rvm_float64_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float64_m8");
	exit(-1);
}
inline float32_t mipp_get_k_float32(const rvm_float32_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_float32(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_float32(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_float32(m0, v0);
#endif
}
inline float32_t mipp_get_k_float32_m1(const rvm_float32_m1_t m0, const uint32_t v0) {
	return mipp_get_k_float32(m0, v0);
}
inline float32_t mipp_get_k_float32_m2(const rvm_float32_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float32_m2");
	exit(-1);
}
inline float32_t mipp_get_k_float32_m4(const rvm_float32_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float32_m4");
	exit(-1);
}
inline float32_t mipp_get_k_float32_m8(const rvm_float32_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_float32_m8");
	exit(-1);
}
inline int64_t mipp_get_k_int64(const rvm_int64_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_int64(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_int64(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_int64(m0, v0);
#endif
}
inline int64_t mipp_get_k_int64_m1(const rvm_int64_m1_t m0, const uint32_t v0) {
	return mipp_get_k_int64(m0, v0);
}
inline int64_t mipp_get_k_int64_m2(const rvm_int64_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int64_m2");
	exit(-1);
}
inline int64_t mipp_get_k_int64_m4(const rvm_int64_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int64_m4");
	exit(-1);
}
inline int64_t mipp_get_k_int64_m8(const rvm_int64_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int64_m8");
	exit(-1);
}
inline int32_t mipp_get_k_int32(const rvm_int32_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_int32(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_int32(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_int32(m0, v0);
#endif
}
inline int32_t mipp_get_k_int32_m1(const rvm_int32_m1_t m0, const uint32_t v0) {
	return mipp_get_k_int32(m0, v0);
}
inline int32_t mipp_get_k_int32_m2(const rvm_int32_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int32_m2");
	exit(-1);
}
inline int32_t mipp_get_k_int32_m4(const rvm_int32_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int32_m4");
	exit(-1);
}
inline int32_t mipp_get_k_int32_m8(const rvm_int32_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int32_m8");
	exit(-1);
}
inline int16_t mipp_get_k_int16(const rvm_int16_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_int16(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_int16(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_int16(m0, v0);
#endif
}
inline int16_t mipp_get_k_int16_m1(const rvm_int16_m1_t m0, const uint32_t v0) {
	return mipp_get_k_int16(m0, v0);
}
inline int16_t mipp_get_k_int16_m2(const rvm_int16_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int16_m2");
	exit(-1);
}
inline int16_t mipp_get_k_int16_m4(const rvm_int16_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int16_m4");
	exit(-1);
}
inline int16_t mipp_get_k_int16_m8(const rvm_int16_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int16_m8");
	exit(-1);
}
inline int8_t mipp_get_k_int8(const rvm_int8_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_int8(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_int8(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_int8(m0, v0);
#endif
}
inline int8_t mipp_get_k_int8_m1(const rvm_int8_m1_t m0, const uint32_t v0) {
	return mipp_get_k_int8(m0, v0);
}
inline int8_t mipp_get_k_int8_m2(const rvm_int8_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int8_m2");
	exit(-1);
}
inline int8_t mipp_get_k_int8_m4(const rvm_int8_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int8_m4");
	exit(-1);
}
inline int8_t mipp_get_k_int8_m8(const rvm_int8_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_int8_m8");
	exit(-1);
}
inline uint64_t mipp_get_k_uint64(const rvm_uint64_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_uint64(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_uint64(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_uint64(m0, v0);
#endif
}
inline uint64_t mipp_get_k_uint64_m1(const rvm_uint64_m1_t m0, const uint32_t v0) {
	return mipp_get_k_uint64(m0, v0);
}
inline uint64_t mipp_get_k_uint64_m2(const rvm_uint64_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint64_m2");
	exit(-1);
}
inline uint64_t mipp_get_k_uint64_m4(const rvm_uint64_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint64_m4");
	exit(-1);
}
inline uint64_t mipp_get_k_uint64_m8(const rvm_uint64_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint64_m8");
	exit(-1);
}
inline uint32_t mipp_get_k_uint32(const rvm_uint32_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_uint32(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_uint32(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_uint32(m0, v0);
#endif
}
inline uint32_t mipp_get_k_uint32_m1(const rvm_uint32_m1_t m0, const uint32_t v0) {
	return mipp_get_k_uint32(m0, v0);
}
inline uint32_t mipp_get_k_uint32_m2(const rvm_uint32_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint32_m2");
	exit(-1);
}
inline uint32_t mipp_get_k_uint32_m4(const rvm_uint32_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint32_m4");
	exit(-1);
}
inline uint32_t mipp_get_k_uint32_m8(const rvm_uint32_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint32_m8");
	exit(-1);
}
inline uint16_t mipp_get_k_uint16(const rvm_uint16_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_uint16(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_uint16(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_uint16(m0, v0);
#endif
}
inline uint16_t mipp_get_k_uint16_m1(const rvm_uint16_m1_t m0, const uint32_t v0) {
	return mipp_get_k_uint16(m0, v0);
}
inline uint16_t mipp_get_k_uint16_m2(const rvm_uint16_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint16_m2");
	exit(-1);
}
inline uint16_t mipp_get_k_uint16_m4(const rvm_uint16_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint16_m4");
	exit(-1);
}
inline uint16_t mipp_get_k_uint16_m8(const rvm_uint16_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint16_m8");
	exit(-1);
}
inline uint8_t mipp_get_k_uint8(const rvm_uint8_t m0, const uint32_t v0) {
#if defined(__AVX512__)
	return mipp_avx512_get_k_uint8(m0, v0);
#elif defined(__AVX__)
	return mipp_avx_get_k_uint8(m0, v0);
#elif defined(__SSE__)
	return mipp_sse_get_k_uint8(m0, v0);
#endif
}
inline uint8_t mipp_get_k_uint8_m1(const rvm_uint8_m1_t m0, const uint32_t v0) {
	return mipp_get_k_uint8(m0, v0);
}
inline uint8_t mipp_get_k_uint8_m2(const rvm_uint8_m2_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint8_m2");
	exit(-1);
}
inline uint8_t mipp_get_k_uint8_m4(const rvm_uint8_m4_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint8_m4");
	exit(-1);
}
inline uint8_t mipp_get_k_uint8_m8(const rvm_uint8_m8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_get_k_uint8_m8");
	exit(-1);
}
inline float64_t mipp_getfirst_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_float64(r0);
#endif
}
inline float64_t mipp_getfirst_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_getfirst_float64(r0);
}
inline float64_t mipp_getfirst_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m2");
	exit(-1);
}
inline float64_t mipp_getfirst_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m4");
	exit(-1);
}
inline float64_t mipp_getfirst_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float64_m8");
	exit(-1);
}
inline float32_t mipp_getfirst_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_float32(r0);
#endif
}
inline float32_t mipp_getfirst_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_getfirst_float32(r0);
}
inline float32_t mipp_getfirst_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m2");
	exit(-1);
}
inline float32_t mipp_getfirst_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m4");
	exit(-1);
}
inline float32_t mipp_getfirst_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_float32_m8");
	exit(-1);
}
inline int64_t mipp_getfirst_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_int64(r0);
#endif
}
inline int64_t mipp_getfirst_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_getfirst_int64(r0);
}
inline int64_t mipp_getfirst_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m2");
	exit(-1);
}
inline int64_t mipp_getfirst_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m4");
	exit(-1);
}
inline int64_t mipp_getfirst_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int64_m8");
	exit(-1);
}
inline int32_t mipp_getfirst_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_int32(r0);
#endif
}
inline int32_t mipp_getfirst_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_getfirst_int32(r0);
}
inline int32_t mipp_getfirst_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m2");
	exit(-1);
}
inline int32_t mipp_getfirst_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m4");
	exit(-1);
}
inline int32_t mipp_getfirst_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int32_m8");
	exit(-1);
}
inline int16_t mipp_getfirst_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_int16(r0);
#endif
}
inline int16_t mipp_getfirst_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_getfirst_int16(r0);
}
inline int16_t mipp_getfirst_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m2");
	exit(-1);
}
inline int16_t mipp_getfirst_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m4");
	exit(-1);
}
inline int16_t mipp_getfirst_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int16_m8");
	exit(-1);
}
inline int8_t mipp_getfirst_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_int8(r0);
#endif
}
inline int8_t mipp_getfirst_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_getfirst_int8(r0);
}
inline int8_t mipp_getfirst_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m2");
	exit(-1);
}
inline int8_t mipp_getfirst_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m4");
	exit(-1);
}
inline int8_t mipp_getfirst_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_int8_m8");
	exit(-1);
}
inline uint64_t mipp_getfirst_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_uint64(r0);
#endif
}
inline uint64_t mipp_getfirst_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_getfirst_uint64(r0);
}
inline uint64_t mipp_getfirst_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m2");
	exit(-1);
}
inline uint64_t mipp_getfirst_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m4");
	exit(-1);
}
inline uint64_t mipp_getfirst_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint64_m8");
	exit(-1);
}
inline uint32_t mipp_getfirst_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_uint32(r0);
#endif
}
inline uint32_t mipp_getfirst_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_getfirst_uint32(r0);
}
inline uint32_t mipp_getfirst_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m2");
	exit(-1);
}
inline uint32_t mipp_getfirst_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m4");
	exit(-1);
}
inline uint32_t mipp_getfirst_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint32_m8");
	exit(-1);
}
inline uint16_t mipp_getfirst_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_uint16(r0);
#endif
}
inline uint16_t mipp_getfirst_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_getfirst_uint16(r0);
}
inline uint16_t mipp_getfirst_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m2");
	exit(-1);
}
inline uint16_t mipp_getfirst_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m4");
	exit(-1);
}
inline uint16_t mipp_getfirst_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint16_m8");
	exit(-1);
}
inline uint8_t mipp_getfirst_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_getfirst_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_getfirst_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_getfirst_uint8(r0);
#endif
}
inline uint8_t mipp_getfirst_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_getfirst_uint8(r0);
}
inline uint8_t mipp_getfirst_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m2");
	exit(-1);
}
inline uint8_t mipp_getfirst_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m4");
	exit(-1);
}
inline uint8_t mipp_getfirst_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_getfirst_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_sqrt_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_sqrt_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_sqrt_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_sqrt_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_sqrt_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_sqrt_float64(r0);
}
inline rvd_float64_m2_t mipp_sqrt_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_sqrt_float64_m1(r0.r1);
	res.r2 = mipp_sqrt_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_sqrt_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_sqrt_float64_m2(r0.r1);
	res.r2 = mipp_sqrt_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_sqrt_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_sqrt_float64_m4(r0.r1);
	res.r2 = mipp_sqrt_float64_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_sqrt_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_sqrt_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_sqrt_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_sqrt_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_sqrt_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_sqrt_float32(r0);
}
inline rvd_float32_m2_t mipp_sqrt_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_sqrt_float32_m1(r0.r1);
	res.r2 = mipp_sqrt_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_sqrt_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_sqrt_float32_m2(r0.r1);
	res.r2 = mipp_sqrt_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_sqrt_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_sqrt_float32_m4(r0.r1);
	res.r2 = mipp_sqrt_float32_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_rsqrt_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_rsqrt_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_rsqrt_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_rsqrt_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_rsqrt_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_rsqrt_float64(r0);
}
inline rvd_float64_m2_t mipp_rsqrt_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_rsqrt_float64_m1(r0.r1);
	res.r2 = mipp_rsqrt_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_rsqrt_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_rsqrt_float64_m2(r0.r1);
	res.r2 = mipp_rsqrt_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_rsqrt_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_rsqrt_float64_m4(r0.r1);
	res.r2 = mipp_rsqrt_float64_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_rsqrt_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_rsqrt_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_rsqrt_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_rsqrt_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_rsqrt_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_rsqrt_float32(r0);
}
inline rvd_float32_m2_t mipp_rsqrt_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_rsqrt_float32_m1(r0.r1);
	res.r2 = mipp_rsqrt_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_rsqrt_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_rsqrt_float32_m2(r0.r1);
	res.r2 = mipp_rsqrt_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_rsqrt_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_rsqrt_float32_m4(r0.r1);
	res.r2 = mipp_rsqrt_float32_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_add_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_add_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_add_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_add_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_add_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_add_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_add_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_add_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_add_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_add_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_add_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_add_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_add_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_add_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_add_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_add_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_add_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_add_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_add_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_add_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_add_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_add_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_add_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_add_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_add_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_add_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_add_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_add_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_add_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_add_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_add_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_add_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_add_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_add_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_add_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_add_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_add_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_add_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_add_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_add_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_add_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_add_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_add_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_add_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_add_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_add_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_add_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_add_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_add_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_add_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_add_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_add_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_add_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_add_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_add_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_add_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_add_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_add_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_add_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_add_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_add_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_add_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_add_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_add_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_add_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_add_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_add_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_add_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_add_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_add_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_add_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_add_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_add_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_add_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_add_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_add_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_add_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_add_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_add_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_add_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_add_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_add_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_add_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_add_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_add_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_add_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_add_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_add_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_add_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_add_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_add_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_add_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_add_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_add_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_add_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_add_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_sub_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_sub_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_sub_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_sub_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_sub_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_sub_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_sub_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_sub_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_sub_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_sub_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_sub_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_sub_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_sub_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_sub_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_sub_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_sub_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_sub_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_sub_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_sub_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_sub_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_sub_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_sub_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_sub_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_sub_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_sub_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_sub_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_sub_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_sub_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_sub_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_sub_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_sub_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_sub_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_sub_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_sub_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_sub_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_sub_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_sub_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_sub_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_sub_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_sub_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_sub_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_sub_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_sub_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_sub_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_sub_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_sub_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_sub_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_sub_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_sub_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_sub_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_sub_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_sub_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_sub_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_sub_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_sub_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_sub_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_sub_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_sub_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_sub_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_sub_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_sub_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_sub_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_sub_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_sub_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_sub_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_sub_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_sub_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_sub_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_sub_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_sub_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_sub_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_sub_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_sub_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_sub_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_sub_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_sub_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_sub_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_sub_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_sub_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_sub_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_sub_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_sub_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_sub_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_sub_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_sub_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_sub_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_sub_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_sub_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_sub_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_sub_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_sub_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_sub_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_sub_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_sub_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_mul_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_mul_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_mul_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_mul_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_mul_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_mul_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_mul_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_mul_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_mul_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_mul_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_mul_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_mul_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_mul_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_mul_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_mul_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_mul_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_mul_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_mul_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_mul_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_mul_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_mul_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_mul_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_mul_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_mul_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_mul_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_mul_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_mul_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_mul_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_mul_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_mul_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_mul_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_mul_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_mul_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_mul_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_mul_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_mul_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_mul_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_mul_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_mul_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_mul_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_mul_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_mul_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_mul_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_mul_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_mul_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_mul_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_mul_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_mul_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_mul_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_mul_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_mul_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_mul_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_mul_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_mul_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_mul_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_mul_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_mul_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_mul_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_mul_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_mul_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_mul_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_mul_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_mul_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_mul_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_mul_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_mul_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_mul_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_mul_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_mul_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_mul_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_mul_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_mul_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_mul_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_mul_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_mul_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_mul_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_mul_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_mul_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_mul_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_mul_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_mul_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_mul_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_mul_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_mul_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_mul_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_mul_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_mul_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_mul_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_mul_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_mul_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_mul_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_mul_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_mul_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_mul_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_div_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_div_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_div_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_div_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_div_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_div_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_div_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_div_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_div_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_div_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_div_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_div_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_div_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_div_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_div_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_div_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_div_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_div_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_div_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_div_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_div_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_div_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_div_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_div_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_div_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_div_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_div_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_div_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_div_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_div_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_min_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_min_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_min_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_min_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_min_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_min_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_min_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_min_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_min_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_min_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_min_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_min_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_min_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_min_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_min_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_min_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_min_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_min_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_min_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_min_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_min_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_min_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_min_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_min_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_min_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_min_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_min_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_min_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_min_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_min_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_min_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_min_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_min_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_min_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_min_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_min_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_min_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_min_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_min_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_min_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_min_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_min_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_min_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_min_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_min_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_min_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_min_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_min_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_min_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_min_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_min_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_min_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_min_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_min_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_min_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_min_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_min_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_min_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_min_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_min_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_min_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_min_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_min_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_min_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_min_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_min_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_min_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_min_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_min_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_min_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_min_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_min_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_min_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_min_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_min_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_min_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_min_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_min_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_min_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_min_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_min_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_min_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_min_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_min_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_min_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_min_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_min_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_min_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_min_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_min_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_min_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_min_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_min_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_min_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_min_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_min_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_max_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_max_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_max_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_max_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_max_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_max_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_max_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_max_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_max_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_max_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_max_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_max_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_max_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_max_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_max_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_max_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_max_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_max_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_max_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_max_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_max_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_max_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_max_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_max_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_max_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_max_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_max_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_max_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_max_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_max_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_max_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_max_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_max_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_max_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_max_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_max_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_max_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_max_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_max_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_max_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_max_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_max_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_max_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_max_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_max_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_max_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_max_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_max_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_max_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_max_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_max_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_max_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_max_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_max_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_max_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_max_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_max_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_max_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_max_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_max_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_max_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_max_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_max_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_max_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_max_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_max_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_max_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_max_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_max_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_max_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_max_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_max_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_max_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_max_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_max_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_max_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_max_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_max_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_max_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_max_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_max_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_max_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_max_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_max_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_max_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_max_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_max_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_max_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_max_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_max_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_max_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_max_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_max_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_max_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_max_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_max_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_t mipp_fmadd_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvd_float64_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmadd_float64(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmadd_float64(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmadd_float64(r0, r1, r2);
#endif
}
inline rvd_float64_m1_t mipp_fmadd_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvd_float64_m1_t r2) {
	return mipp_fmadd_float64(r0, r1, r2);
}
inline rvd_float64_m2_t mipp_fmadd_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.r1 = mipp_fmadd_float64_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float64_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_m4_t mipp_fmadd_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.r1 = mipp_fmadd_float64_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float64_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_m8_t mipp_fmadd_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.r1 = mipp_fmadd_float64_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float64_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_t mipp_fmadd_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvd_float32_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmadd_float32(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmadd_float32(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmadd_float32(r0, r1, r2);
#endif
}
inline rvd_float32_m1_t mipp_fmadd_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvd_float32_m1_t r2) {
	return mipp_fmadd_float32(r0, r1, r2);
}
inline rvd_float32_m2_t mipp_fmadd_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.r1 = mipp_fmadd_float32_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float32_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_m4_t mipp_fmadd_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.r1 = mipp_fmadd_float32_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float32_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_m8_t mipp_fmadd_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.r1 = mipp_fmadd_float32_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_float32_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_t mipp_fmadd_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvd_int32_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmadd_int32(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmadd_int32(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmadd_int32(r0, r1, r2);
#endif
}
inline rvd_int32_m1_t mipp_fmadd_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvd_int32_m1_t r2) {
	return mipp_fmadd_int32(r0, r1, r2);
}
inline rvd_int32_m2_t mipp_fmadd_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.r1 = mipp_fmadd_int32_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_int32_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_m4_t mipp_fmadd_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.r1 = mipp_fmadd_int32_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_int32_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_m8_t mipp_fmadd_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.r1 = mipp_fmadd_int32_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmadd_int32_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_t mipp_fmsub_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvd_float64_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmsub_float64(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmsub_float64(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmsub_float64(r0, r1, r2);
#endif
}
inline rvd_float64_m1_t mipp_fmsub_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvd_float64_m1_t r2) {
	return mipp_fmsub_float64(r0, r1, r2);
}
inline rvd_float64_m2_t mipp_fmsub_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvd_float64_m2_t r2) {
	rvd_float64_m2_t res;
	res.r1 = mipp_fmsub_float64_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float64_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_m4_t mipp_fmsub_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvd_float64_m4_t r2) {
	rvd_float64_m4_t res;
	res.r1 = mipp_fmsub_float64_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float64_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_m8_t mipp_fmsub_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvd_float64_m8_t r2) {
	rvd_float64_m8_t res;
	res.r1 = mipp_fmsub_float64_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float64_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_t mipp_fmsub_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvd_float32_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmsub_float32(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmsub_float32(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmsub_float32(r0, r1, r2);
#endif
}
inline rvd_float32_m1_t mipp_fmsub_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvd_float32_m1_t r2) {
	return mipp_fmsub_float32(r0, r1, r2);
}
inline rvd_float32_m2_t mipp_fmsub_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvd_float32_m2_t r2) {
	rvd_float32_m2_t res;
	res.r1 = mipp_fmsub_float32_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float32_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_m4_t mipp_fmsub_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvd_float32_m4_t r2) {
	rvd_float32_m4_t res;
	res.r1 = mipp_fmsub_float32_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float32_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float32_m8_t mipp_fmsub_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvd_float32_m8_t r2) {
	rvd_float32_m8_t res;
	res.r1 = mipp_fmsub_float32_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_float32_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_t mipp_fmsub_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvd_int32_t r2) {
#if defined(__AVX512__)
	return mipp_avx512_fmsub_int32(r0, r1, r2);
#elif defined(__AVX__)
	return mipp_avx_fmsub_int32(r0, r1, r2);
#elif defined(__SSE__)
	return mipp_sse_fmsub_int32(r0, r1, r2);
#endif
}
inline rvd_int32_m1_t mipp_fmsub_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvd_int32_m1_t r2) {
	return mipp_fmsub_int32(r0, r1, r2);
}
inline rvd_int32_m2_t mipp_fmsub_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvd_int32_m2_t r2) {
	rvd_int32_m2_t res;
	res.r1 = mipp_fmsub_int32_m1(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_int32_m1(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_m4_t mipp_fmsub_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvd_int32_m4_t r2) {
	rvd_int32_m4_t res;
	res.r1 = mipp_fmsub_int32_m2(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_int32_m2(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_int32_m8_t mipp_fmsub_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvd_int32_m8_t r2) {
	rvd_int32_m8_t res;
	res.r1 = mipp_fmsub_int32_m4(r0.r1, r1.r1, r2.r1);
	res.r2 = mipp_fmsub_int32_m4(r0.r2, r1.r2, r2.r2);
	return res;
}
inline rvd_float64_t mipp_andb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_andb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_andb_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_andb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_andb_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_andb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_andb_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_andb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_andb_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_andb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_andb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_andb_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_andb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_andb_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_andb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_andb_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_andb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_andb_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_andb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_andb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_andb_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_andb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_andb_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_andb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_andb_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_andb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_andb_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_andb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_andb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_andb_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_andb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_andb_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_andb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_andb_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_andb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_andb_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_andb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_andb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_andb_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_andb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_andb_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_andb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_andb_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_andb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_andb_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_andb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_andb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_andb_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_andb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_andb_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_andb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_andb_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_andb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_andb_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_andb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_andb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_andb_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_andb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_andb_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_andb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_andb_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_andb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_andb_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_andb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_andb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_andb_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_andb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_andb_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_andb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_andb_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_andb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_andb_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_andb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_andb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_andb_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_andb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_andb_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_andb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_andb_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_andb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_andb_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_andb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andb_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andb_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_andb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_andb_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_andb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_andb_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_andb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_andb_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_andb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_andb_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_andb_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvm_float64_t mipp_andb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_float64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_float64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_float64(m0, m1);
#endif
}
inline rvm_float64_m1_t mipp_andb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_andb_k_float64(m0, m1);
}
inline rvm_float64_m2_t mipp_andb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_andb_k_float64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_andb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_andb_k_float64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_andb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_andb_k_float64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_t mipp_andb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_float32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_float32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_float32(m0, m1);
#endif
}
inline rvm_float32_m1_t mipp_andb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_andb_k_float32(m0, m1);
}
inline rvm_float32_m2_t mipp_andb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_andb_k_float32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_andb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_andb_k_float32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_andb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_andb_k_float32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_float32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_t mipp_andb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_int64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_int64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_int64(m0, m1);
#endif
}
inline rvm_int64_m1_t mipp_andb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_andb_k_int64(m0, m1);
}
inline rvm_int64_m2_t mipp_andb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_andb_k_int64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_andb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_andb_k_int64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_andb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_andb_k_int64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_t mipp_andb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_int32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_int32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_int32(m0, m1);
#endif
}
inline rvm_int32_m1_t mipp_andb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_andb_k_int32(m0, m1);
}
inline rvm_int32_m2_t mipp_andb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_andb_k_int32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_andb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_andb_k_int32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_andb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_andb_k_int32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_t mipp_andb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_int16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_int16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_int16(m0, m1);
#endif
}
inline rvm_int16_m1_t mipp_andb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_andb_k_int16(m0, m1);
}
inline rvm_int16_m2_t mipp_andb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_andb_k_int16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_andb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_andb_k_int16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_andb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_andb_k_int16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_t mipp_andb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_int8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_int8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_int8(m0, m1);
#endif
}
inline rvm_int8_m1_t mipp_andb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_andb_k_int8(m0, m1);
}
inline rvm_int8_m2_t mipp_andb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_andb_k_int8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_andb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_andb_k_int8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_andb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_andb_k_int8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_int8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_t mipp_andb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_uint64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_uint64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_uint64(m0, m1);
#endif
}
inline rvm_uint64_m1_t mipp_andb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_andb_k_uint64(m0, m1);
}
inline rvm_uint64_m2_t mipp_andb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_andb_k_uint64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_andb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_andb_k_uint64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_andb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_andb_k_uint64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_t mipp_andb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_uint32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_uint32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_uint32(m0, m1);
#endif
}
inline rvm_uint32_m1_t mipp_andb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_andb_k_uint32(m0, m1);
}
inline rvm_uint32_m2_t mipp_andb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_andb_k_uint32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_andb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_andb_k_uint32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_andb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_andb_k_uint32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_t mipp_andb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_uint16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_uint16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_uint16(m0, m1);
#endif
}
inline rvm_uint16_m1_t mipp_andb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_andb_k_uint16(m0, m1);
}
inline rvm_uint16_m2_t mipp_andb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_andb_k_uint16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_andb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_andb_k_uint16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_andb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_andb_k_uint16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_t mipp_andb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andb_k_uint8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andb_k_uint8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andb_k_uint8(m0, m1);
#endif
}
inline rvm_uint8_m1_t mipp_andb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_andb_k_uint8(m0, m1);
}
inline rvm_uint8_m2_t mipp_andb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_andb_k_uint8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_andb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_andb_k_uint8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_andb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_andb_k_uint8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andb_k_uint8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvd_float64_t mipp_andnb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_andnb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_andnb_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_andnb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_andnb_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_andnb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_andnb_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_andnb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_andnb_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_andnb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_andnb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_andnb_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_andnb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_andnb_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_andnb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_andnb_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_andnb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_andnb_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_andnb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_andnb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_andnb_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_andnb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_andnb_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_andnb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_andnb_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_andnb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_andnb_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_andnb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_andnb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_andnb_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_andnb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_andnb_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_andnb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_andnb_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_andnb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_andnb_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_andnb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_andnb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_andnb_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_andnb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_andnb_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_andnb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_andnb_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_andnb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_andnb_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_andnb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_andnb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_andnb_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_andnb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_andnb_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_andnb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_andnb_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_andnb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_andnb_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_andnb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_andnb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_andnb_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_andnb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_andnb_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_andnb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_andnb_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_andnb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_andnb_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_andnb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_andnb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_andnb_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_andnb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_andnb_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_andnb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_andnb_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_andnb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_andnb_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_andnb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_andnb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_andnb_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_andnb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_andnb_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_andnb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_andnb_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_andnb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_andnb_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_andnb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_andnb_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_andnb_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_andnb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_andnb_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_andnb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_andnb_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_andnb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_andnb_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_andnb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_andnb_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_andnb_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvm_float64_t mipp_andnb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_float64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_float64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_float64(m0, m1);
#endif
}
inline rvm_float64_m1_t mipp_andnb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_andnb_k_float64(m0, m1);
}
inline rvm_float64_m2_t mipp_andnb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_andnb_k_float64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_andnb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_andnb_k_float64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_andnb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_andnb_k_float64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_t mipp_andnb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_float32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_float32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_float32(m0, m1);
#endif
}
inline rvm_float32_m1_t mipp_andnb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_andnb_k_float32(m0, m1);
}
inline rvm_float32_m2_t mipp_andnb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_andnb_k_float32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_andnb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_andnb_k_float32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_andnb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_andnb_k_float32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_float32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_t mipp_andnb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_int64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_int64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_int64(m0, m1);
#endif
}
inline rvm_int64_m1_t mipp_andnb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_andnb_k_int64(m0, m1);
}
inline rvm_int64_m2_t mipp_andnb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_andnb_k_int64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_andnb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_andnb_k_int64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_andnb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_andnb_k_int64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_t mipp_andnb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_int32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_int32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_int32(m0, m1);
#endif
}
inline rvm_int32_m1_t mipp_andnb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_andnb_k_int32(m0, m1);
}
inline rvm_int32_m2_t mipp_andnb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_andnb_k_int32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_andnb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_andnb_k_int32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_andnb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_andnb_k_int32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_t mipp_andnb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_int16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_int16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_int16(m0, m1);
#endif
}
inline rvm_int16_m1_t mipp_andnb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_andnb_k_int16(m0, m1);
}
inline rvm_int16_m2_t mipp_andnb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_andnb_k_int16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_andnb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_andnb_k_int16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_andnb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_andnb_k_int16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_t mipp_andnb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_int8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_int8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_int8(m0, m1);
#endif
}
inline rvm_int8_m1_t mipp_andnb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_andnb_k_int8(m0, m1);
}
inline rvm_int8_m2_t mipp_andnb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_andnb_k_int8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_andnb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_andnb_k_int8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_andnb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_andnb_k_int8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_int8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_t mipp_andnb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_uint64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_uint64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_uint64(m0, m1);
#endif
}
inline rvm_uint64_m1_t mipp_andnb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_andnb_k_uint64(m0, m1);
}
inline rvm_uint64_m2_t mipp_andnb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_andnb_k_uint64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_andnb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_andnb_k_uint64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_andnb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_andnb_k_uint64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_t mipp_andnb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_uint32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_uint32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_uint32(m0, m1);
#endif
}
inline rvm_uint32_m1_t mipp_andnb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_andnb_k_uint32(m0, m1);
}
inline rvm_uint32_m2_t mipp_andnb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_andnb_k_uint32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_andnb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_andnb_k_uint32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_andnb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_andnb_k_uint32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_t mipp_andnb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_uint16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_uint16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_uint16(m0, m1);
#endif
}
inline rvm_uint16_m1_t mipp_andnb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_andnb_k_uint16(m0, m1);
}
inline rvm_uint16_m2_t mipp_andnb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_andnb_k_uint16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_andnb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_andnb_k_uint16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_andnb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_andnb_k_uint16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_t mipp_andnb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_andnb_k_uint8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_andnb_k_uint8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_andnb_k_uint8(m0, m1);
#endif
}
inline rvm_uint8_m1_t mipp_andnb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_andnb_k_uint8(m0, m1);
}
inline rvm_uint8_m2_t mipp_andnb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_andnb_k_uint8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_andnb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_andnb_k_uint8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_andnb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_andnb_k_uint8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_andnb_k_uint8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvd_float64_t mipp_orb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_orb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_orb_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_orb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_orb_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_orb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_orb_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_orb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_orb_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_orb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_orb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_orb_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_orb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_orb_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_orb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_orb_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_orb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_orb_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_orb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_orb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_orb_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_orb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_orb_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_orb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_orb_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_orb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_orb_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_orb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_orb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_orb_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_orb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_orb_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_orb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_orb_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_orb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_orb_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_orb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_orb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_orb_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_orb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_orb_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_orb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_orb_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_orb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_orb_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_orb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_orb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_orb_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_orb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_orb_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_orb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_orb_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_orb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_orb_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_orb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_orb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_orb_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_orb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_orb_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_orb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_orb_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_orb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_orb_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_orb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_orb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_orb_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_orb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_orb_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_orb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_orb_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_orb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_orb_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_orb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_orb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_orb_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_orb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_orb_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_orb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_orb_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_orb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_orb_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_orb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_orb_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_orb_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_orb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_orb_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_orb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_orb_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_orb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_orb_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_orb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_orb_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_orb_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvm_float64_t mipp_orb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_float64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_float64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_float64(m0, m1);
#endif
}
inline rvm_float64_m1_t mipp_orb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_orb_k_float64(m0, m1);
}
inline rvm_float64_m2_t mipp_orb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_orb_k_float64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_orb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_orb_k_float64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_orb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_orb_k_float64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_t mipp_orb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_float32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_float32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_float32(m0, m1);
#endif
}
inline rvm_float32_m1_t mipp_orb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_orb_k_float32(m0, m1);
}
inline rvm_float32_m2_t mipp_orb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_orb_k_float32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_orb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_orb_k_float32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_orb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_orb_k_float32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_float32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_t mipp_orb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_int64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_int64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_int64(m0, m1);
#endif
}
inline rvm_int64_m1_t mipp_orb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_orb_k_int64(m0, m1);
}
inline rvm_int64_m2_t mipp_orb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_orb_k_int64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_orb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_orb_k_int64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_orb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_orb_k_int64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_t mipp_orb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_int32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_int32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_int32(m0, m1);
#endif
}
inline rvm_int32_m1_t mipp_orb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_orb_k_int32(m0, m1);
}
inline rvm_int32_m2_t mipp_orb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_orb_k_int32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_orb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_orb_k_int32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_orb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_orb_k_int32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_t mipp_orb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_int16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_int16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_int16(m0, m1);
#endif
}
inline rvm_int16_m1_t mipp_orb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_orb_k_int16(m0, m1);
}
inline rvm_int16_m2_t mipp_orb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_orb_k_int16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_orb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_orb_k_int16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_orb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_orb_k_int16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_t mipp_orb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_int8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_int8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_int8(m0, m1);
#endif
}
inline rvm_int8_m1_t mipp_orb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_orb_k_int8(m0, m1);
}
inline rvm_int8_m2_t mipp_orb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_orb_k_int8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_orb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_orb_k_int8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_orb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_orb_k_int8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_int8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_t mipp_orb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_uint64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_uint64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_uint64(m0, m1);
#endif
}
inline rvm_uint64_m1_t mipp_orb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_orb_k_uint64(m0, m1);
}
inline rvm_uint64_m2_t mipp_orb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_orb_k_uint64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_orb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_orb_k_uint64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_orb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_orb_k_uint64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_t mipp_orb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_uint32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_uint32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_uint32(m0, m1);
#endif
}
inline rvm_uint32_m1_t mipp_orb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_orb_k_uint32(m0, m1);
}
inline rvm_uint32_m2_t mipp_orb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_orb_k_uint32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_orb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_orb_k_uint32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_orb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_orb_k_uint32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_t mipp_orb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_uint16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_uint16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_uint16(m0, m1);
#endif
}
inline rvm_uint16_m1_t mipp_orb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_orb_k_uint16(m0, m1);
}
inline rvm_uint16_m2_t mipp_orb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_orb_k_uint16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_orb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_orb_k_uint16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_orb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_orb_k_uint16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_t mipp_orb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_orb_k_uint8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_orb_k_uint8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_orb_k_uint8(m0, m1);
#endif
}
inline rvm_uint8_m1_t mipp_orb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_orb_k_uint8(m0, m1);
}
inline rvm_uint8_m2_t mipp_orb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_orb_k_uint8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_orb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_orb_k_uint8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_orb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_orb_k_uint8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_orb_k_uint8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvd_float64_t mipp_xorb_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_float64(r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_xorb_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_xorb_float64(r0, r1);
}
inline rvd_float64_m2_t mipp_xorb_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvd_float64_m2_t res;
	res.r1 = mipp_xorb_float64_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m4_t mipp_xorb_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvd_float64_m4_t res;
	res.r1 = mipp_xorb_float64_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float64_m8_t mipp_xorb_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvd_float64_m8_t res;
	res.r1 = mipp_xorb_float64_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_t mipp_xorb_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_float32(r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_xorb_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_xorb_float32(r0, r1);
}
inline rvd_float32_m2_t mipp_xorb_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvd_float32_m2_t res;
	res.r1 = mipp_xorb_float32_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m4_t mipp_xorb_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvd_float32_m4_t res;
	res.r1 = mipp_xorb_float32_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_float32_m8_t mipp_xorb_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvd_float32_m8_t res;
	res.r1 = mipp_xorb_float32_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_float32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_t mipp_xorb_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_int64(r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_xorb_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_xorb_int64(r0, r1);
}
inline rvd_int64_m2_t mipp_xorb_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvd_int64_m2_t res;
	res.r1 = mipp_xorb_int64_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m4_t mipp_xorb_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvd_int64_m4_t res;
	res.r1 = mipp_xorb_int64_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int64_m8_t mipp_xorb_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvd_int64_m8_t res;
	res.r1 = mipp_xorb_int64_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_t mipp_xorb_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_int32(r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_xorb_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_xorb_int32(r0, r1);
}
inline rvd_int32_m2_t mipp_xorb_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvd_int32_m2_t res;
	res.r1 = mipp_xorb_int32_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m4_t mipp_xorb_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvd_int32_m4_t res;
	res.r1 = mipp_xorb_int32_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int32_m8_t mipp_xorb_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvd_int32_m8_t res;
	res.r1 = mipp_xorb_int32_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_t mipp_xorb_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_int16(r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_xorb_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_xorb_int16(r0, r1);
}
inline rvd_int16_m2_t mipp_xorb_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvd_int16_m2_t res;
	res.r1 = mipp_xorb_int16_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m4_t mipp_xorb_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvd_int16_m4_t res;
	res.r1 = mipp_xorb_int16_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int16_m8_t mipp_xorb_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvd_int16_m8_t res;
	res.r1 = mipp_xorb_int16_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_t mipp_xorb_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_int8(r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_xorb_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_xorb_int8(r0, r1);
}
inline rvd_int8_m2_t mipp_xorb_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvd_int8_m2_t res;
	res.r1 = mipp_xorb_int8_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m4_t mipp_xorb_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvd_int8_m4_t res;
	res.r1 = mipp_xorb_int8_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_int8_m8_t mipp_xorb_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvd_int8_m8_t res;
	res.r1 = mipp_xorb_int8_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_int8_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_t mipp_xorb_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_uint64(r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_xorb_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_xorb_uint64(r0, r1);
}
inline rvd_uint64_m2_t mipp_xorb_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_xorb_uint64_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint64_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_xorb_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_xorb_uint64_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint64_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_xorb_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_xorb_uint64_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint64_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_t mipp_xorb_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_uint32(r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_xorb_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_xorb_uint32(r0, r1);
}
inline rvd_uint32_m2_t mipp_xorb_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_xorb_uint32_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint32_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_xorb_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_xorb_uint32_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint32_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_xorb_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_xorb_uint32_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint32_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_t mipp_xorb_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_uint16(r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_xorb_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_xorb_uint16(r0, r1);
}
inline rvd_uint16_m2_t mipp_xorb_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_xorb_uint16_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint16_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_xorb_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_xorb_uint16_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint16_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_xorb_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_xorb_uint16_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint16_m4(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_t mipp_xorb_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_xorb_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_xorb_uint8(r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_xorb_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_xorb_uint8(r0, r1);
}
inline rvd_uint8_m2_t mipp_xorb_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_xorb_uint8_m1(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint8_m1(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_xorb_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_xorb_uint8_m2(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint8_m2(r0.r2, r1.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_xorb_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_xorb_uint8_m4(r0.r1, r1.r1);
	res.r2 = mipp_xorb_uint8_m4(r0.r2, r1.r2);
	return res;
}
inline rvm_float64_t mipp_xorb_k_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_float64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_float64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_float64(m0, m1);
#endif
}
inline rvm_float64_m1_t mipp_xorb_k_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_xorb_k_float64(m0, m1);
}
inline rvm_float64_m2_t mipp_xorb_k_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_xorb_k_float64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_xorb_k_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_xorb_k_float64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_xorb_k_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_xorb_k_float64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_t mipp_xorb_k_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_float32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_float32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_float32(m0, m1);
#endif
}
inline rvm_float32_m1_t mipp_xorb_k_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_xorb_k_float32(m0, m1);
}
inline rvm_float32_m2_t mipp_xorb_k_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_xorb_k_float32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_xorb_k_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_xorb_k_float32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_xorb_k_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_xorb_k_float32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_float32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_t mipp_xorb_k_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_int64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_int64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_int64(m0, m1);
#endif
}
inline rvm_int64_m1_t mipp_xorb_k_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_xorb_k_int64(m0, m1);
}
inline rvm_int64_m2_t mipp_xorb_k_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_xorb_k_int64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_xorb_k_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_xorb_k_int64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_xorb_k_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_xorb_k_int64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_t mipp_xorb_k_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_int32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_int32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_int32(m0, m1);
#endif
}
inline rvm_int32_m1_t mipp_xorb_k_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_xorb_k_int32(m0, m1);
}
inline rvm_int32_m2_t mipp_xorb_k_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_xorb_k_int32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_xorb_k_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_xorb_k_int32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_xorb_k_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_xorb_k_int32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_t mipp_xorb_k_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_int16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_int16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_int16(m0, m1);
#endif
}
inline rvm_int16_m1_t mipp_xorb_k_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_xorb_k_int16(m0, m1);
}
inline rvm_int16_m2_t mipp_xorb_k_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_xorb_k_int16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_xorb_k_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_xorb_k_int16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_xorb_k_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_xorb_k_int16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_t mipp_xorb_k_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_int8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_int8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_int8(m0, m1);
#endif
}
inline rvm_int8_m1_t mipp_xorb_k_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_xorb_k_int8(m0, m1);
}
inline rvm_int8_m2_t mipp_xorb_k_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_xorb_k_int8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_xorb_k_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_xorb_k_int8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_xorb_k_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_xorb_k_int8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_int8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_t mipp_xorb_k_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_uint64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_uint64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_uint64(m0, m1);
#endif
}
inline rvm_uint64_m1_t mipp_xorb_k_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_xorb_k_uint64(m0, m1);
}
inline rvm_uint64_m2_t mipp_xorb_k_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_xorb_k_uint64_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint64_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_xorb_k_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_xorb_k_uint64_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint64_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_xorb_k_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_xorb_k_uint64_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint64_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_t mipp_xorb_k_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_uint32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_uint32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_uint32(m0, m1);
#endif
}
inline rvm_uint32_m1_t mipp_xorb_k_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_xorb_k_uint32(m0, m1);
}
inline rvm_uint32_m2_t mipp_xorb_k_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_xorb_k_uint32_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint32_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_xorb_k_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_xorb_k_uint32_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint32_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_xorb_k_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_xorb_k_uint32_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint32_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_t mipp_xorb_k_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_uint16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_uint16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_uint16(m0, m1);
#endif
}
inline rvm_uint16_m1_t mipp_xorb_k_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_xorb_k_uint16(m0, m1);
}
inline rvm_uint16_m2_t mipp_xorb_k_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_xorb_k_uint16_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint16_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_xorb_k_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_xorb_k_uint16_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint16_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_xorb_k_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_xorb_k_uint16_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint16_m4(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_t mipp_xorb_k_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_xorb_k_uint8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_xorb_k_uint8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_xorb_k_uint8(m0, m1);
#endif
}
inline rvm_uint8_m1_t mipp_xorb_k_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_xorb_k_uint8(m0, m1);
}
inline rvm_uint8_m2_t mipp_xorb_k_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_xorb_k_uint8_m1(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint8_m1(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_xorb_k_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_xorb_k_uint8_m2(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint8_m2(m0.m2, m1.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_xorb_k_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_xorb_k_uint8_m4(m0.m1, m1.m1);
	msk.m2 = mipp_xorb_k_uint8_m4(m0.m2, m1.m2);
	return msk;
}
inline rvd_float64_t mipp_msb_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_msb_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_msb_float64(r0);
}
inline rvd_float64_m2_t mipp_msb_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_msb_float64_m1(r0.r1);
	res.r2 = mipp_msb_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_msb_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_msb_float64_m2(r0.r1);
	res.r2 = mipp_msb_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_msb_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_msb_float64_m4(r0.r1);
	res.r2 = mipp_msb_float64_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_msb_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_msb_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_msb_float32(r0);
}
inline rvd_float32_m2_t mipp_msb_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_msb_float32_m1(r0.r1);
	res.r2 = mipp_msb_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_msb_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_msb_float32_m2(r0.r1);
	res.r2 = mipp_msb_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_msb_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_msb_float32_m4(r0.r1);
	res.r2 = mipp_msb_float32_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_msb_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_msb_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_msb_int64(r0);
}
inline rvd_int64_m2_t mipp_msb_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_msb_int64_m1(r0.r1);
	res.r2 = mipp_msb_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_msb_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_msb_int64_m2(r0.r1);
	res.r2 = mipp_msb_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_msb_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_msb_int64_m4(r0.r1);
	res.r2 = mipp_msb_int64_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_msb_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_msb_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_msb_int32(r0);
}
inline rvd_int32_m2_t mipp_msb_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_msb_int32_m1(r0.r1);
	res.r2 = mipp_msb_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_msb_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_msb_int32_m2(r0.r1);
	res.r2 = mipp_msb_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_msb_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_msb_int32_m4(r0.r1);
	res.r2 = mipp_msb_int32_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_msb_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_msb_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_msb_int16(r0);
}
inline rvd_int16_m2_t mipp_msb_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_msb_int16_m1(r0.r1);
	res.r2 = mipp_msb_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_msb_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_msb_int16_m2(r0.r1);
	res.r2 = mipp_msb_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_msb_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_msb_int16_m4(r0.r1);
	res.r2 = mipp_msb_int16_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_msb_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_msb_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_msb_int8(r0);
}
inline rvd_int8_m2_t mipp_msb_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_msb_int8_m1(r0.r1);
	res.r2 = mipp_msb_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_msb_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_msb_int8_m2(r0.r1);
	res.r2 = mipp_msb_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_msb_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_msb_int8_m4(r0.r1);
	res.r2 = mipp_msb_int8_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_msb_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_msb_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_msb_uint64(r0);
}
inline rvd_uint64_m2_t mipp_msb_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_msb_uint64_m1(r0.r1);
	res.r2 = mipp_msb_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_msb_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_msb_uint64_m2(r0.r1);
	res.r2 = mipp_msb_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_msb_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_msb_uint64_m4(r0.r1);
	res.r2 = mipp_msb_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_msb_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_msb_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_msb_uint32(r0);
}
inline rvd_uint32_m2_t mipp_msb_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_msb_uint32_m1(r0.r1);
	res.r2 = mipp_msb_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_msb_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_msb_uint32_m2(r0.r1);
	res.r2 = mipp_msb_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_msb_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_msb_uint32_m4(r0.r1);
	res.r2 = mipp_msb_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_msb_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_msb_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_msb_uint16(r0);
}
inline rvd_uint16_m2_t mipp_msb_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_msb_uint16_m1(r0.r1);
	res.r2 = mipp_msb_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_msb_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_msb_uint16_m2(r0.r1);
	res.r2 = mipp_msb_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_msb_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_msb_uint16_m4(r0.r1);
	res.r2 = mipp_msb_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_msb_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_msb_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_msb_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_msb_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_msb_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_msb_uint8(r0);
}
inline rvd_uint8_m2_t mipp_msb_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_msb_uint8_m1(r0.r1);
	res.r2 = mipp_msb_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_msb_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_msb_uint8_m2(r0.r1);
	res.r2 = mipp_msb_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_msb_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_msb_uint8_m4(r0.r1);
	res.r2 = mipp_msb_uint8_m4(r0.r2);
	return res;
}
inline rvd_float64_t mipp_notb_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_notb_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_notb_float64(r0);
}
inline rvd_float64_m2_t mipp_notb_float64_m2(const rvd_float64_m2_t r0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_notb_float64_m1(r0.r1);
	res.r2 = mipp_notb_float64_m1(r0.r2);
	return res;
}
inline rvd_float64_m4_t mipp_notb_float64_m4(const rvd_float64_m4_t r0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_notb_float64_m2(r0.r1);
	res.r2 = mipp_notb_float64_m2(r0.r2);
	return res;
}
inline rvd_float64_m8_t mipp_notb_float64_m8(const rvd_float64_m8_t r0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_notb_float64_m4(r0.r1);
	res.r2 = mipp_notb_float64_m4(r0.r2);
	return res;
}
inline rvd_float32_t mipp_notb_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_notb_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_notb_float32(r0);
}
inline rvd_float32_m2_t mipp_notb_float32_m2(const rvd_float32_m2_t r0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_notb_float32_m1(r0.r1);
	res.r2 = mipp_notb_float32_m1(r0.r2);
	return res;
}
inline rvd_float32_m4_t mipp_notb_float32_m4(const rvd_float32_m4_t r0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_notb_float32_m2(r0.r1);
	res.r2 = mipp_notb_float32_m2(r0.r2);
	return res;
}
inline rvd_float32_m8_t mipp_notb_float32_m8(const rvd_float32_m8_t r0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_notb_float32_m4(r0.r1);
	res.r2 = mipp_notb_float32_m4(r0.r2);
	return res;
}
inline rvd_int64_t mipp_notb_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_notb_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_notb_int64(r0);
}
inline rvd_int64_m2_t mipp_notb_int64_m2(const rvd_int64_m2_t r0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_notb_int64_m1(r0.r1);
	res.r2 = mipp_notb_int64_m1(r0.r2);
	return res;
}
inline rvd_int64_m4_t mipp_notb_int64_m4(const rvd_int64_m4_t r0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_notb_int64_m2(r0.r1);
	res.r2 = mipp_notb_int64_m2(r0.r2);
	return res;
}
inline rvd_int64_m8_t mipp_notb_int64_m8(const rvd_int64_m8_t r0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_notb_int64_m4(r0.r1);
	res.r2 = mipp_notb_int64_m4(r0.r2);
	return res;
}
inline rvd_int32_t mipp_notb_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_notb_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_notb_int32(r0);
}
inline rvd_int32_m2_t mipp_notb_int32_m2(const rvd_int32_m2_t r0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_notb_int32_m1(r0.r1);
	res.r2 = mipp_notb_int32_m1(r0.r2);
	return res;
}
inline rvd_int32_m4_t mipp_notb_int32_m4(const rvd_int32_m4_t r0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_notb_int32_m2(r0.r1);
	res.r2 = mipp_notb_int32_m2(r0.r2);
	return res;
}
inline rvd_int32_m8_t mipp_notb_int32_m8(const rvd_int32_m8_t r0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_notb_int32_m4(r0.r1);
	res.r2 = mipp_notb_int32_m4(r0.r2);
	return res;
}
inline rvd_int16_t mipp_notb_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_notb_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_notb_int16(r0);
}
inline rvd_int16_m2_t mipp_notb_int16_m2(const rvd_int16_m2_t r0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_notb_int16_m1(r0.r1);
	res.r2 = mipp_notb_int16_m1(r0.r2);
	return res;
}
inline rvd_int16_m4_t mipp_notb_int16_m4(const rvd_int16_m4_t r0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_notb_int16_m2(r0.r1);
	res.r2 = mipp_notb_int16_m2(r0.r2);
	return res;
}
inline rvd_int16_m8_t mipp_notb_int16_m8(const rvd_int16_m8_t r0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_notb_int16_m4(r0.r1);
	res.r2 = mipp_notb_int16_m4(r0.r2);
	return res;
}
inline rvd_int8_t mipp_notb_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_notb_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_notb_int8(r0);
}
inline rvd_int8_m2_t mipp_notb_int8_m2(const rvd_int8_m2_t r0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_notb_int8_m1(r0.r1);
	res.r2 = mipp_notb_int8_m1(r0.r2);
	return res;
}
inline rvd_int8_m4_t mipp_notb_int8_m4(const rvd_int8_m4_t r0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_notb_int8_m2(r0.r1);
	res.r2 = mipp_notb_int8_m2(r0.r2);
	return res;
}
inline rvd_int8_m8_t mipp_notb_int8_m8(const rvd_int8_m8_t r0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_notb_int8_m4(r0.r1);
	res.r2 = mipp_notb_int8_m4(r0.r2);
	return res;
}
inline rvd_uint64_t mipp_notb_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_notb_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_notb_uint64(r0);
}
inline rvd_uint64_m2_t mipp_notb_uint64_m2(const rvd_uint64_m2_t r0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_notb_uint64_m1(r0.r1);
	res.r2 = mipp_notb_uint64_m1(r0.r2);
	return res;
}
inline rvd_uint64_m4_t mipp_notb_uint64_m4(const rvd_uint64_m4_t r0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_notb_uint64_m2(r0.r1);
	res.r2 = mipp_notb_uint64_m2(r0.r2);
	return res;
}
inline rvd_uint64_m8_t mipp_notb_uint64_m8(const rvd_uint64_m8_t r0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_notb_uint64_m4(r0.r1);
	res.r2 = mipp_notb_uint64_m4(r0.r2);
	return res;
}
inline rvd_uint32_t mipp_notb_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_notb_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_notb_uint32(r0);
}
inline rvd_uint32_m2_t mipp_notb_uint32_m2(const rvd_uint32_m2_t r0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_notb_uint32_m1(r0.r1);
	res.r2 = mipp_notb_uint32_m1(r0.r2);
	return res;
}
inline rvd_uint32_m4_t mipp_notb_uint32_m4(const rvd_uint32_m4_t r0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_notb_uint32_m2(r0.r1);
	res.r2 = mipp_notb_uint32_m2(r0.r2);
	return res;
}
inline rvd_uint32_m8_t mipp_notb_uint32_m8(const rvd_uint32_m8_t r0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_notb_uint32_m4(r0.r1);
	res.r2 = mipp_notb_uint32_m4(r0.r2);
	return res;
}
inline rvd_uint16_t mipp_notb_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_notb_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_notb_uint16(r0);
}
inline rvd_uint16_m2_t mipp_notb_uint16_m2(const rvd_uint16_m2_t r0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_notb_uint16_m1(r0.r1);
	res.r2 = mipp_notb_uint16_m1(r0.r2);
	return res;
}
inline rvd_uint16_m4_t mipp_notb_uint16_m4(const rvd_uint16_m4_t r0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_notb_uint16_m2(r0.r1);
	res.r2 = mipp_notb_uint16_m2(r0.r2);
	return res;
}
inline rvd_uint16_m8_t mipp_notb_uint16_m8(const rvd_uint16_m8_t r0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_notb_uint16_m4(r0.r1);
	res.r2 = mipp_notb_uint16_m4(r0.r2);
	return res;
}
inline rvd_uint8_t mipp_notb_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_notb_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_notb_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_notb_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_notb_uint8(r0);
}
inline rvd_uint8_m2_t mipp_notb_uint8_m2(const rvd_uint8_m2_t r0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_notb_uint8_m1(r0.r1);
	res.r2 = mipp_notb_uint8_m1(r0.r2);
	return res;
}
inline rvd_uint8_m4_t mipp_notb_uint8_m4(const rvd_uint8_m4_t r0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_notb_uint8_m2(r0.r1);
	res.r2 = mipp_notb_uint8_m2(r0.r2);
	return res;
}
inline rvd_uint8_m8_t mipp_notb_uint8_m8(const rvd_uint8_m8_t r0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_notb_uint8_m4(r0.r1);
	res.r2 = mipp_notb_uint8_m4(r0.r2);
	return res;
}
inline rvm_float64_t mipp_notb_k_float64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_float64(m0);
#endif
}
inline rvm_float64_m1_t mipp_notb_k_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_notb_k_float64(m0);
}
inline rvm_float64_m2_t mipp_notb_k_float64_m2(const rvm_float64_m2_t m0) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_notb_k_float64_m1(m0.m1);
	msk.m2 = mipp_notb_k_float64_m1(m0.m2);
	return msk;
}
inline rvm_float64_m4_t mipp_notb_k_float64_m4(const rvm_float64_m4_t m0) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_notb_k_float64_m2(m0.m1);
	msk.m2 = mipp_notb_k_float64_m2(m0.m2);
	return msk;
}
inline rvm_float64_m8_t mipp_notb_k_float64_m8(const rvm_float64_m8_t m0) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_notb_k_float64_m4(m0.m1);
	msk.m2 = mipp_notb_k_float64_m4(m0.m2);
	return msk;
}
inline rvm_float32_t mipp_notb_k_float32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_float32(m0);
#endif
}
inline rvm_float32_m1_t mipp_notb_k_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_notb_k_float32(m0);
}
inline rvm_float32_m2_t mipp_notb_k_float32_m2(const rvm_float32_m2_t m0) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_notb_k_float32_m1(m0.m1);
	msk.m2 = mipp_notb_k_float32_m1(m0.m2);
	return msk;
}
inline rvm_float32_m4_t mipp_notb_k_float32_m4(const rvm_float32_m4_t m0) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_notb_k_float32_m2(m0.m1);
	msk.m2 = mipp_notb_k_float32_m2(m0.m2);
	return msk;
}
inline rvm_float32_m8_t mipp_notb_k_float32_m8(const rvm_float32_m8_t m0) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_notb_k_float32_m4(m0.m1);
	msk.m2 = mipp_notb_k_float32_m4(m0.m2);
	return msk;
}
inline rvm_int64_t mipp_notb_k_int64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_int64(m0);
#endif
}
inline rvm_int64_m1_t mipp_notb_k_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_notb_k_int64(m0);
}
inline rvm_int64_m2_t mipp_notb_k_int64_m2(const rvm_int64_m2_t m0) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_notb_k_int64_m1(m0.m1);
	msk.m2 = mipp_notb_k_int64_m1(m0.m2);
	return msk;
}
inline rvm_int64_m4_t mipp_notb_k_int64_m4(const rvm_int64_m4_t m0) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_notb_k_int64_m2(m0.m1);
	msk.m2 = mipp_notb_k_int64_m2(m0.m2);
	return msk;
}
inline rvm_int64_m8_t mipp_notb_k_int64_m8(const rvm_int64_m8_t m0) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_notb_k_int64_m4(m0.m1);
	msk.m2 = mipp_notb_k_int64_m4(m0.m2);
	return msk;
}
inline rvm_int32_t mipp_notb_k_int32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_int32(m0);
#endif
}
inline rvm_int32_m1_t mipp_notb_k_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_notb_k_int32(m0);
}
inline rvm_int32_m2_t mipp_notb_k_int32_m2(const rvm_int32_m2_t m0) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_notb_k_int32_m1(m0.m1);
	msk.m2 = mipp_notb_k_int32_m1(m0.m2);
	return msk;
}
inline rvm_int32_m4_t mipp_notb_k_int32_m4(const rvm_int32_m4_t m0) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_notb_k_int32_m2(m0.m1);
	msk.m2 = mipp_notb_k_int32_m2(m0.m2);
	return msk;
}
inline rvm_int32_m8_t mipp_notb_k_int32_m8(const rvm_int32_m8_t m0) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_notb_k_int32_m4(m0.m1);
	msk.m2 = mipp_notb_k_int32_m4(m0.m2);
	return msk;
}
inline rvm_int16_t mipp_notb_k_int16(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_int16(m0);
#endif
}
inline rvm_int16_m1_t mipp_notb_k_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_notb_k_int16(m0);
}
inline rvm_int16_m2_t mipp_notb_k_int16_m2(const rvm_int16_m2_t m0) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_notb_k_int16_m1(m0.m1);
	msk.m2 = mipp_notb_k_int16_m1(m0.m2);
	return msk;
}
inline rvm_int16_m4_t mipp_notb_k_int16_m4(const rvm_int16_m4_t m0) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_notb_k_int16_m2(m0.m1);
	msk.m2 = mipp_notb_k_int16_m2(m0.m2);
	return msk;
}
inline rvm_int16_m8_t mipp_notb_k_int16_m8(const rvm_int16_m8_t m0) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_notb_k_int16_m4(m0.m1);
	msk.m2 = mipp_notb_k_int16_m4(m0.m2);
	return msk;
}
inline rvm_int8_t mipp_notb_k_int8(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_int8(m0);
#endif
}
inline rvm_int8_m1_t mipp_notb_k_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_notb_k_int8(m0);
}
inline rvm_int8_m2_t mipp_notb_k_int8_m2(const rvm_int8_m2_t m0) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_notb_k_int8_m1(m0.m1);
	msk.m2 = mipp_notb_k_int8_m1(m0.m2);
	return msk;
}
inline rvm_int8_m4_t mipp_notb_k_int8_m4(const rvm_int8_m4_t m0) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_notb_k_int8_m2(m0.m1);
	msk.m2 = mipp_notb_k_int8_m2(m0.m2);
	return msk;
}
inline rvm_int8_m8_t mipp_notb_k_int8_m8(const rvm_int8_m8_t m0) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_notb_k_int8_m4(m0.m1);
	msk.m2 = mipp_notb_k_int8_m4(m0.m2);
	return msk;
}
inline rvm_uint64_t mipp_notb_k_uint64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_uint64(m0);
#endif
}
inline rvm_uint64_m1_t mipp_notb_k_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_notb_k_uint64(m0);
}
inline rvm_uint64_m2_t mipp_notb_k_uint64_m2(const rvm_uint64_m2_t m0) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_notb_k_uint64_m1(m0.m1);
	msk.m2 = mipp_notb_k_uint64_m1(m0.m2);
	return msk;
}
inline rvm_uint64_m4_t mipp_notb_k_uint64_m4(const rvm_uint64_m4_t m0) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_notb_k_uint64_m2(m0.m1);
	msk.m2 = mipp_notb_k_uint64_m2(m0.m2);
	return msk;
}
inline rvm_uint64_m8_t mipp_notb_k_uint64_m8(const rvm_uint64_m8_t m0) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_notb_k_uint64_m4(m0.m1);
	msk.m2 = mipp_notb_k_uint64_m4(m0.m2);
	return msk;
}
inline rvm_uint32_t mipp_notb_k_uint32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_uint32(m0);
#endif
}
inline rvm_uint32_m1_t mipp_notb_k_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_notb_k_uint32(m0);
}
inline rvm_uint32_m2_t mipp_notb_k_uint32_m2(const rvm_uint32_m2_t m0) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_notb_k_uint32_m1(m0.m1);
	msk.m2 = mipp_notb_k_uint32_m1(m0.m2);
	return msk;
}
inline rvm_uint32_m4_t mipp_notb_k_uint32_m4(const rvm_uint32_m4_t m0) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_notb_k_uint32_m2(m0.m1);
	msk.m2 = mipp_notb_k_uint32_m2(m0.m2);
	return msk;
}
inline rvm_uint32_m8_t mipp_notb_k_uint32_m8(const rvm_uint32_m8_t m0) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_notb_k_uint32_m4(m0.m1);
	msk.m2 = mipp_notb_k_uint32_m4(m0.m2);
	return msk;
}
inline rvm_uint16_t mipp_notb_k_uint16(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_uint16(m0);
#endif
}
inline rvm_uint16_m1_t mipp_notb_k_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_notb_k_uint16(m0);
}
inline rvm_uint16_m2_t mipp_notb_k_uint16_m2(const rvm_uint16_m2_t m0) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_notb_k_uint16_m1(m0.m1);
	msk.m2 = mipp_notb_k_uint16_m1(m0.m2);
	return msk;
}
inline rvm_uint16_m4_t mipp_notb_k_uint16_m4(const rvm_uint16_m4_t m0) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_notb_k_uint16_m2(m0.m1);
	msk.m2 = mipp_notb_k_uint16_m2(m0.m2);
	return msk;
}
inline rvm_uint16_m8_t mipp_notb_k_uint16_m8(const rvm_uint16_m8_t m0) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_notb_k_uint16_m4(m0.m1);
	msk.m2 = mipp_notb_k_uint16_m4(m0.m2);
	return msk;
}
inline rvm_uint8_t mipp_notb_k_uint8(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_notb_k_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_notb_k_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_notb_k_uint8(m0);
#endif
}
inline rvm_uint8_m1_t mipp_notb_k_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_notb_k_uint8(m0);
}
inline rvm_uint8_m2_t mipp_notb_k_uint8_m2(const rvm_uint8_m2_t m0) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_notb_k_uint8_m1(m0.m1);
	msk.m2 = mipp_notb_k_uint8_m1(m0.m2);
	return msk;
}
inline rvm_uint8_m4_t mipp_notb_k_uint8_m4(const rvm_uint8_m4_t m0) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_notb_k_uint8_m2(m0.m1);
	msk.m2 = mipp_notb_k_uint8_m2(m0.m2);
	return msk;
}
inline rvm_uint8_m8_t mipp_notb_k_uint8_m8(const rvm_uint8_m8_t m0) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_notb_k_uint8_m4(m0.m1);
	msk.m2 = mipp_notb_k_uint8_m4(m0.m2);
	return msk;
}
inline rvm_float64_t mipp_cmpeq_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmpeq_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpeq_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmpeq_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmpeq_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmpeq_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmpeq_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmpeq_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmpeq_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmpeq_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmpeq_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpeq_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmpeq_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmpeq_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmpeq_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmpeq_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmpeq_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmpeq_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmpeq_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmpeq_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpeq_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmpeq_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmpeq_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmpeq_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmpeq_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmpeq_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmpeq_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmpeq_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmpeq_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpeq_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmpeq_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmpeq_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmpeq_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmpeq_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmpeq_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmpeq_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmpeq_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmpeq_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpeq_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmpeq_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmpeq_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmpeq_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmpeq_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmpeq_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmpeq_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmpeq_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmpeq_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpeq_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmpeq_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmpeq_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmpeq_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmpeq_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmpeq_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmpeq_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmpeq_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmpeq_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpeq_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmpeq_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmpeq_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmpeq_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmpeq_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmpeq_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmpeq_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmpeq_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmpeq_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpeq_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmpeq_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmpeq_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmpeq_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmpeq_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmpeq_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmpeq_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmpeq_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmpeq_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpeq_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmpeq_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmpeq_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmpeq_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmpeq_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmpeq_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmpeq_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmpeq_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpeq_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpeq_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpeq_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmpeq_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpeq_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmpeq_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmpeq_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmpeq_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmpeq_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmpeq_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmpeq_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpeq_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_t mipp_cmpneq_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmpneq_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpneq_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmpneq_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmpneq_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmpneq_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmpneq_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmpneq_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmpneq_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmpneq_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmpneq_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpneq_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmpneq_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmpneq_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmpneq_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmpneq_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmpneq_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmpneq_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmpneq_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmpneq_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpneq_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmpneq_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmpneq_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmpneq_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmpneq_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmpneq_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmpneq_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmpneq_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmpneq_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpneq_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmpneq_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmpneq_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmpneq_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmpneq_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmpneq_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmpneq_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmpneq_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmpneq_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpneq_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmpneq_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmpneq_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmpneq_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmpneq_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmpneq_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmpneq_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmpneq_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmpneq_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpneq_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmpneq_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmpneq_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmpneq_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmpneq_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmpneq_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmpneq_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmpneq_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmpneq_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpneq_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmpneq_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmpneq_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmpneq_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmpneq_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmpneq_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmpneq_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmpneq_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmpneq_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpneq_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmpneq_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmpneq_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmpneq_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmpneq_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmpneq_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmpneq_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmpneq_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmpneq_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpneq_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmpneq_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmpneq_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmpneq_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmpneq_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmpneq_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmpneq_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmpneq_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpneq_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpneq_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpneq_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmpneq_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpneq_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmpneq_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmpneq_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmpneq_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmpneq_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmpneq_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmpneq_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpneq_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_t mipp_cmplt_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmplt_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmplt_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmplt_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmplt_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmplt_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmplt_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmplt_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmplt_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmplt_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmplt_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmplt_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmplt_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmplt_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmplt_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmplt_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmplt_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmplt_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmplt_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmplt_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmplt_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmplt_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmplt_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmplt_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmplt_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmplt_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmplt_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmplt_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmplt_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmplt_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmplt_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmplt_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmplt_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmplt_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmplt_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmplt_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmplt_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmplt_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmplt_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmplt_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmplt_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmplt_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmplt_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmplt_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmplt_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmplt_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmplt_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmplt_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmplt_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmplt_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmplt_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmplt_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmplt_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmplt_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmplt_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmplt_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmplt_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmplt_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmplt_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmplt_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmplt_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmplt_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmplt_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmplt_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmplt_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmplt_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmplt_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmplt_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmplt_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmplt_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmplt_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmplt_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmplt_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmplt_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmplt_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmplt_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmplt_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmplt_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmplt_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmplt_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmplt_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmplt_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmplt_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmplt_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmplt_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmplt_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmplt_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmplt_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmplt_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmplt_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmplt_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmplt_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmplt_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmplt_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_t mipp_cmple_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmple_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmple_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmple_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmple_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmple_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmple_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmple_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmple_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmple_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmple_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmple_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmple_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmple_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmple_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmple_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmple_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmple_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmple_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmple_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmple_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmple_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmple_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmple_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmple_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmple_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmple_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmple_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmple_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmple_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmple_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmple_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmple_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmple_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmple_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmple_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmple_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmple_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmple_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmple_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmple_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmple_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmple_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmple_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmple_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmple_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmple_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmple_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmple_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmple_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmple_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmple_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmple_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmple_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmple_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmple_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmple_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmple_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmple_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmple_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmple_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmple_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmple_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmple_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmple_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmple_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmple_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmple_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmple_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmple_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmple_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmple_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmple_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmple_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmple_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmple_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmple_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmple_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmple_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmple_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmple_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmple_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmple_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmple_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmple_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmple_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmple_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmple_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmple_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmple_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmple_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmple_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmple_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmple_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_t mipp_cmpge_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmpge_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpge_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmpge_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmpge_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmpge_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmpge_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmpge_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmpge_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmpge_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmpge_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpge_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmpge_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmpge_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmpge_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmpge_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmpge_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmpge_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmpge_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmpge_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpge_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmpge_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmpge_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmpge_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmpge_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmpge_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmpge_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmpge_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmpge_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpge_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmpge_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmpge_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmpge_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmpge_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmpge_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmpge_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmpge_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmpge_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpge_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmpge_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmpge_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmpge_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmpge_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmpge_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmpge_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmpge_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmpge_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpge_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmpge_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmpge_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmpge_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmpge_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmpge_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmpge_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmpge_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmpge_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpge_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmpge_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmpge_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmpge_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmpge_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmpge_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmpge_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmpge_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmpge_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpge_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmpge_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmpge_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmpge_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmpge_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmpge_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmpge_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmpge_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmpge_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpge_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmpge_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmpge_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmpge_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmpge_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmpge_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmpge_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmpge_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpge_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpge_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpge_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmpge_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpge_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmpge_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmpge_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmpge_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmpge_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmpge_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmpge_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpge_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_t mipp_cmpgt_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_float64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_float64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_float64(r0, r1);
#endif
}
inline rvm_float64_m1_t mipp_cmpgt_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_cmpgt_float64(r0, r1);
}
inline rvm_float64_m2_t mipp_cmpgt_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	rvm_float64_m2_t msk;
	msk.m1 = mipp_cmpgt_float64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m4_t mipp_cmpgt_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	rvm_float64_m4_t msk;
	msk.m1 = mipp_cmpgt_float64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float64_m8_t mipp_cmpgt_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	rvm_float64_m8_t msk;
	msk.m1 = mipp_cmpgt_float64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_t mipp_cmpgt_float32(const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_float32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_float32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_float32(r0, r1);
#endif
}
inline rvm_float32_m1_t mipp_cmpgt_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_cmpgt_float32(r0, r1);
}
inline rvm_float32_m2_t mipp_cmpgt_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	rvm_float32_m2_t msk;
	msk.m1 = mipp_cmpgt_float32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m4_t mipp_cmpgt_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	rvm_float32_m4_t msk;
	msk.m1 = mipp_cmpgt_float32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_float32_m8_t mipp_cmpgt_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	rvm_float32_m8_t msk;
	msk.m1 = mipp_cmpgt_float32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_float32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_t mipp_cmpgt_int64(const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_int64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_int64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_int64(r0, r1);
#endif
}
inline rvm_int64_m1_t mipp_cmpgt_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_cmpgt_int64(r0, r1);
}
inline rvm_int64_m2_t mipp_cmpgt_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	rvm_int64_m2_t msk;
	msk.m1 = mipp_cmpgt_int64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m4_t mipp_cmpgt_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	rvm_int64_m4_t msk;
	msk.m1 = mipp_cmpgt_int64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int64_m8_t mipp_cmpgt_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	rvm_int64_m8_t msk;
	msk.m1 = mipp_cmpgt_int64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_t mipp_cmpgt_int32(const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_int32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_int32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_int32(r0, r1);
#endif
}
inline rvm_int32_m1_t mipp_cmpgt_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_cmpgt_int32(r0, r1);
}
inline rvm_int32_m2_t mipp_cmpgt_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	rvm_int32_m2_t msk;
	msk.m1 = mipp_cmpgt_int32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m4_t mipp_cmpgt_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	rvm_int32_m4_t msk;
	msk.m1 = mipp_cmpgt_int32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int32_m8_t mipp_cmpgt_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	rvm_int32_m8_t msk;
	msk.m1 = mipp_cmpgt_int32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_t mipp_cmpgt_int16(const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_int16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_int16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_int16(r0, r1);
#endif
}
inline rvm_int16_m1_t mipp_cmpgt_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_cmpgt_int16(r0, r1);
}
inline rvm_int16_m2_t mipp_cmpgt_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	rvm_int16_m2_t msk;
	msk.m1 = mipp_cmpgt_int16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m4_t mipp_cmpgt_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	rvm_int16_m4_t msk;
	msk.m1 = mipp_cmpgt_int16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int16_m8_t mipp_cmpgt_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	rvm_int16_m8_t msk;
	msk.m1 = mipp_cmpgt_int16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_t mipp_cmpgt_int8(const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_int8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_int8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_int8(r0, r1);
#endif
}
inline rvm_int8_m1_t mipp_cmpgt_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_cmpgt_int8(r0, r1);
}
inline rvm_int8_m2_t mipp_cmpgt_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	rvm_int8_m2_t msk;
	msk.m1 = mipp_cmpgt_int8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m4_t mipp_cmpgt_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	rvm_int8_m4_t msk;
	msk.m1 = mipp_cmpgt_int8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_int8_m8_t mipp_cmpgt_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	rvm_int8_m8_t msk;
	msk.m1 = mipp_cmpgt_int8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_int8_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_t mipp_cmpgt_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_uint64(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_uint64(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_uint64(r0, r1);
#endif
}
inline rvm_uint64_m1_t mipp_cmpgt_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_cmpgt_uint64(r0, r1);
}
inline rvm_uint64_m2_t mipp_cmpgt_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	rvm_uint64_m2_t msk;
	msk.m1 = mipp_cmpgt_uint64_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint64_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m4_t mipp_cmpgt_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	rvm_uint64_m4_t msk;
	msk.m1 = mipp_cmpgt_uint64_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint64_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint64_m8_t mipp_cmpgt_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	rvm_uint64_m8_t msk;
	msk.m1 = mipp_cmpgt_uint64_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint64_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_t mipp_cmpgt_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_uint32(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_uint32(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_uint32(r0, r1);
#endif
}
inline rvm_uint32_m1_t mipp_cmpgt_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_cmpgt_uint32(r0, r1);
}
inline rvm_uint32_m2_t mipp_cmpgt_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	rvm_uint32_m2_t msk;
	msk.m1 = mipp_cmpgt_uint32_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint32_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m4_t mipp_cmpgt_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	rvm_uint32_m4_t msk;
	msk.m1 = mipp_cmpgt_uint32_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint32_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint32_m8_t mipp_cmpgt_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	rvm_uint32_m8_t msk;
	msk.m1 = mipp_cmpgt_uint32_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint32_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_t mipp_cmpgt_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_uint16(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_uint16(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_uint16(r0, r1);
#endif
}
inline rvm_uint16_m1_t mipp_cmpgt_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_cmpgt_uint16(r0, r1);
}
inline rvm_uint16_m2_t mipp_cmpgt_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	rvm_uint16_m2_t msk;
	msk.m1 = mipp_cmpgt_uint16_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint16_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m4_t mipp_cmpgt_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	rvm_uint16_m4_t msk;
	msk.m1 = mipp_cmpgt_uint16_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint16_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint16_m8_t mipp_cmpgt_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	rvm_uint16_m8_t msk;
	msk.m1 = mipp_cmpgt_uint16_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint16_m4(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_t mipp_cmpgt_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_cmpgt_uint8(r0, r1);
#elif defined(__AVX__)
	return mipp_avx_cmpgt_uint8(r0, r1);
#elif defined(__SSE__)
	return mipp_sse_cmpgt_uint8(r0, r1);
#endif
}
inline rvm_uint8_m1_t mipp_cmpgt_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_cmpgt_uint8(r0, r1);
}
inline rvm_uint8_m2_t mipp_cmpgt_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	rvm_uint8_m2_t msk;
	msk.m1 = mipp_cmpgt_uint8_m1(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint8_m1(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m4_t mipp_cmpgt_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	rvm_uint8_m4_t msk;
	msk.m1 = mipp_cmpgt_uint8_m2(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint8_m2(r0.r2, r1.r2);
	return msk;
}
inline rvm_uint8_m8_t mipp_cmpgt_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	rvm_uint8_m8_t msk;
	msk.m1 = mipp_cmpgt_uint8_m4(r0.r1, r1.r1);
	msk.m2 = mipp_cmpgt_uint8_m4(r0.r2, r1.r2);
	return msk;
}
inline float64_t mipp_round_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_round_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_round_float64(r0);
#endif
}
inline float64_t mipp_round_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_round_float64(r0);
}
inline float64_t mipp_round_float64_m2(const rvd_float64_m2_t r0) {
	mipp_round_float64_m1(r0.r1);
	mipp_round_float64_m1(r0.r2);
}
inline float64_t mipp_round_float64_m4(const rvd_float64_m4_t r0) {
	mipp_round_float64_m2(r0.r1);
	mipp_round_float64_m2(r0.r2);
}
inline float64_t mipp_round_float64_m8(const rvd_float64_m8_t r0) {
	mipp_round_float64_m4(r0.r1);
	mipp_round_float64_m4(r0.r2);
}
inline float32_t mipp_round_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_round_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_round_float32(r0);
#endif
}
inline float32_t mipp_round_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_round_float32(r0);
}
inline float32_t mipp_round_float32_m2(const rvd_float32_m2_t r0) {
	mipp_round_float32_m1(r0.r1);
	mipp_round_float32_m1(r0.r2);
}
inline float32_t mipp_round_float32_m4(const rvd_float32_m4_t r0) {
	mipp_round_float32_m2(r0.r1);
	mipp_round_float32_m2(r0.r2);
}
inline float32_t mipp_round_float32_m8(const rvd_float32_m8_t r0) {
	mipp_round_float32_m4(r0.r1);
	mipp_round_float32_m4(r0.r2);
}
inline int64_t mipp_round_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_round_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_round_int64(r0);
#endif
}
inline int64_t mipp_round_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_round_int64(r0);
}
inline int64_t mipp_round_int64_m2(const rvd_int64_m2_t r0) {
	mipp_round_int64_m1(r0.r1);
	mipp_round_int64_m1(r0.r2);
}
inline int64_t mipp_round_int64_m4(const rvd_int64_m4_t r0) {
	mipp_round_int64_m2(r0.r1);
	mipp_round_int64_m2(r0.r2);
}
inline int64_t mipp_round_int64_m8(const rvd_int64_m8_t r0) {
	mipp_round_int64_m4(r0.r1);
	mipp_round_int64_m4(r0.r2);
}
inline int32_t mipp_round_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_round_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_round_int32(r0);
#endif
}
inline int32_t mipp_round_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_round_int32(r0);
}
inline int32_t mipp_round_int32_m2(const rvd_int32_m2_t r0) {
	mipp_round_int32_m1(r0.r1);
	mipp_round_int32_m1(r0.r2);
}
inline int32_t mipp_round_int32_m4(const rvd_int32_m4_t r0) {
	mipp_round_int32_m2(r0.r1);
	mipp_round_int32_m2(r0.r2);
}
inline int32_t mipp_round_int32_m8(const rvd_int32_m8_t r0) {
	mipp_round_int32_m4(r0.r1);
	mipp_round_int32_m4(r0.r2);
}
inline int16_t mipp_round_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_round_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_round_int16(r0);
#endif
}
inline int16_t mipp_round_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_round_int16(r0);
}
inline int16_t mipp_round_int16_m2(const rvd_int16_m2_t r0) {
	mipp_round_int16_m1(r0.r1);
	mipp_round_int16_m1(r0.r2);
}
inline int16_t mipp_round_int16_m4(const rvd_int16_m4_t r0) {
	mipp_round_int16_m2(r0.r1);
	mipp_round_int16_m2(r0.r2);
}
inline int16_t mipp_round_int16_m8(const rvd_int16_m8_t r0) {
	mipp_round_int16_m4(r0.r1);
	mipp_round_int16_m4(r0.r2);
}
inline int8_t mipp_round_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_round_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_round_int8(r0);
#endif
}
inline int8_t mipp_round_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_round_int8(r0);
}
inline int8_t mipp_round_int8_m2(const rvd_int8_m2_t r0) {
	mipp_round_int8_m1(r0.r1);
	mipp_round_int8_m1(r0.r2);
}
inline int8_t mipp_round_int8_m4(const rvd_int8_m4_t r0) {
	mipp_round_int8_m2(r0.r1);
	mipp_round_int8_m2(r0.r2);
}
inline int8_t mipp_round_int8_m8(const rvd_int8_m8_t r0) {
	mipp_round_int8_m4(r0.r1);
	mipp_round_int8_m4(r0.r2);
}
inline uint64_t mipp_round_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_round_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_round_uint64(r0);
#endif
}
inline uint64_t mipp_round_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_round_uint64(r0);
}
inline uint64_t mipp_round_uint64_m2(const rvd_uint64_m2_t r0) {
	mipp_round_uint64_m1(r0.r1);
	mipp_round_uint64_m1(r0.r2);
}
inline uint64_t mipp_round_uint64_m4(const rvd_uint64_m4_t r0) {
	mipp_round_uint64_m2(r0.r1);
	mipp_round_uint64_m2(r0.r2);
}
inline uint64_t mipp_round_uint64_m8(const rvd_uint64_m8_t r0) {
	mipp_round_uint64_m4(r0.r1);
	mipp_round_uint64_m4(r0.r2);
}
inline uint32_t mipp_round_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_round_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_round_uint32(r0);
#endif
}
inline uint32_t mipp_round_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_round_uint32(r0);
}
inline uint32_t mipp_round_uint32_m2(const rvd_uint32_m2_t r0) {
	mipp_round_uint32_m1(r0.r1);
	mipp_round_uint32_m1(r0.r2);
}
inline uint32_t mipp_round_uint32_m4(const rvd_uint32_m4_t r0) {
	mipp_round_uint32_m2(r0.r1);
	mipp_round_uint32_m2(r0.r2);
}
inline uint32_t mipp_round_uint32_m8(const rvd_uint32_m8_t r0) {
	mipp_round_uint32_m4(r0.r1);
	mipp_round_uint32_m4(r0.r2);
}
inline uint16_t mipp_round_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_round_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_round_uint16(r0);
#endif
}
inline uint16_t mipp_round_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_round_uint16(r0);
}
inline uint16_t mipp_round_uint16_m2(const rvd_uint16_m2_t r0) {
	mipp_round_uint16_m1(r0.r1);
	mipp_round_uint16_m1(r0.r2);
}
inline uint16_t mipp_round_uint16_m4(const rvd_uint16_m4_t r0) {
	mipp_round_uint16_m2(r0.r1);
	mipp_round_uint16_m2(r0.r2);
}
inline uint16_t mipp_round_uint16_m8(const rvd_uint16_m8_t r0) {
	mipp_round_uint16_m4(r0.r1);
	mipp_round_uint16_m4(r0.r2);
}
inline uint8_t mipp_round_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_round_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_round_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_round_uint8(r0);
#endif
}
inline uint8_t mipp_round_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_round_uint8(r0);
}
inline uint8_t mipp_round_uint8_m2(const rvd_uint8_m2_t r0) {
	mipp_round_uint8_m1(r0.r1);
	mipp_round_uint8_m1(r0.r2);
}
inline uint8_t mipp_round_uint8_m4(const rvd_uint8_m4_t r0) {
	mipp_round_uint8_m2(r0.r1);
	mipp_round_uint8_m2(r0.r2);
}
inline uint8_t mipp_round_uint8_m8(const rvd_uint8_m8_t r0) {
	mipp_round_uint8_m4(r0.r1);
	mipp_round_uint8_m4(r0.r2);
}
inline rvd_float64_t mipp_blend_float64(const rvd_float64_t r0, const rvd_float64_t r1, const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_float64(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_float64(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_float64(r0, r1, m0);
#endif
}
inline rvd_float64_m1_t mipp_blend_float64_m1(const rvd_float64_m1_t r0, const rvd_float64_m1_t r1, const rvm_float64_m1_t m0) {
	return mipp_blend_float64(r0, r1, m0);
}
inline rvd_float64_m2_t mipp_blend_float64_m2(const rvd_float64_m2_t r0, const rvd_float64_m2_t r1, const rvm_float64_m2_t m0) {
	rvd_float64_m2_t res;
	res.r1 = mipp_blend_float64_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float64_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_float64_m4_t mipp_blend_float64_m4(const rvd_float64_m4_t r0, const rvd_float64_m4_t r1, const rvm_float64_m4_t m0) {
	rvd_float64_m4_t res;
	res.r1 = mipp_blend_float64_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float64_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_float64_m8_t mipp_blend_float64_m8(const rvd_float64_m8_t r0, const rvd_float64_m8_t r1, const rvm_float64_m8_t m0) {
	rvd_float64_m8_t res;
	res.r1 = mipp_blend_float64_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float64_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_float32_t mipp_blend_float32(const rvd_float32_t r0, const rvd_float32_t r1, const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_float32(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_float32(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_float32(r0, r1, m0);
#endif
}
inline rvd_float32_m1_t mipp_blend_float32_m1(const rvd_float32_m1_t r0, const rvd_float32_m1_t r1, const rvm_float32_m1_t m0) {
	return mipp_blend_float32(r0, r1, m0);
}
inline rvd_float32_m2_t mipp_blend_float32_m2(const rvd_float32_m2_t r0, const rvd_float32_m2_t r1, const rvm_float32_m2_t m0) {
	rvd_float32_m2_t res;
	res.r1 = mipp_blend_float32_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float32_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_float32_m4_t mipp_blend_float32_m4(const rvd_float32_m4_t r0, const rvd_float32_m4_t r1, const rvm_float32_m4_t m0) {
	rvd_float32_m4_t res;
	res.r1 = mipp_blend_float32_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float32_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_float32_m8_t mipp_blend_float32_m8(const rvd_float32_m8_t r0, const rvd_float32_m8_t r1, const rvm_float32_m8_t m0) {
	rvd_float32_m8_t res;
	res.r1 = mipp_blend_float32_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_float32_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int64_t mipp_blend_int64(const rvd_int64_t r0, const rvd_int64_t r1, const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_int64(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_int64(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_int64(r0, r1, m0);
#endif
}
inline rvd_int64_m1_t mipp_blend_int64_m1(const rvd_int64_m1_t r0, const rvd_int64_m1_t r1, const rvm_int64_m1_t m0) {
	return mipp_blend_int64(r0, r1, m0);
}
inline rvd_int64_m2_t mipp_blend_int64_m2(const rvd_int64_m2_t r0, const rvd_int64_m2_t r1, const rvm_int64_m2_t m0) {
	rvd_int64_m2_t res;
	res.r1 = mipp_blend_int64_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int64_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int64_m4_t mipp_blend_int64_m4(const rvd_int64_m4_t r0, const rvd_int64_m4_t r1, const rvm_int64_m4_t m0) {
	rvd_int64_m4_t res;
	res.r1 = mipp_blend_int64_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int64_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int64_m8_t mipp_blend_int64_m8(const rvd_int64_m8_t r0, const rvd_int64_m8_t r1, const rvm_int64_m8_t m0) {
	rvd_int64_m8_t res;
	res.r1 = mipp_blend_int64_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int64_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int32_t mipp_blend_int32(const rvd_int32_t r0, const rvd_int32_t r1, const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_int32(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_int32(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_int32(r0, r1, m0);
#endif
}
inline rvd_int32_m1_t mipp_blend_int32_m1(const rvd_int32_m1_t r0, const rvd_int32_m1_t r1, const rvm_int32_m1_t m0) {
	return mipp_blend_int32(r0, r1, m0);
}
inline rvd_int32_m2_t mipp_blend_int32_m2(const rvd_int32_m2_t r0, const rvd_int32_m2_t r1, const rvm_int32_m2_t m0) {
	rvd_int32_m2_t res;
	res.r1 = mipp_blend_int32_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int32_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int32_m4_t mipp_blend_int32_m4(const rvd_int32_m4_t r0, const rvd_int32_m4_t r1, const rvm_int32_m4_t m0) {
	rvd_int32_m4_t res;
	res.r1 = mipp_blend_int32_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int32_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int32_m8_t mipp_blend_int32_m8(const rvd_int32_m8_t r0, const rvd_int32_m8_t r1, const rvm_int32_m8_t m0) {
	rvd_int32_m8_t res;
	res.r1 = mipp_blend_int32_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int32_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int16_t mipp_blend_int16(const rvd_int16_t r0, const rvd_int16_t r1, const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_int16(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_int16(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_int16(r0, r1, m0);
#endif
}
inline rvd_int16_m1_t mipp_blend_int16_m1(const rvd_int16_m1_t r0, const rvd_int16_m1_t r1, const rvm_int16_m1_t m0) {
	return mipp_blend_int16(r0, r1, m0);
}
inline rvd_int16_m2_t mipp_blend_int16_m2(const rvd_int16_m2_t r0, const rvd_int16_m2_t r1, const rvm_int16_m2_t m0) {
	rvd_int16_m2_t res;
	res.r1 = mipp_blend_int16_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int16_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int16_m4_t mipp_blend_int16_m4(const rvd_int16_m4_t r0, const rvd_int16_m4_t r1, const rvm_int16_m4_t m0) {
	rvd_int16_m4_t res;
	res.r1 = mipp_blend_int16_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int16_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int16_m8_t mipp_blend_int16_m8(const rvd_int16_m8_t r0, const rvd_int16_m8_t r1, const rvm_int16_m8_t m0) {
	rvd_int16_m8_t res;
	res.r1 = mipp_blend_int16_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int16_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int8_t mipp_blend_int8(const rvd_int8_t r0, const rvd_int8_t r1, const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_int8(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_int8(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_int8(r0, r1, m0);
#endif
}
inline rvd_int8_m1_t mipp_blend_int8_m1(const rvd_int8_m1_t r0, const rvd_int8_m1_t r1, const rvm_int8_m1_t m0) {
	return mipp_blend_int8(r0, r1, m0);
}
inline rvd_int8_m2_t mipp_blend_int8_m2(const rvd_int8_m2_t r0, const rvd_int8_m2_t r1, const rvm_int8_m2_t m0) {
	rvd_int8_m2_t res;
	res.r1 = mipp_blend_int8_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int8_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int8_m4_t mipp_blend_int8_m4(const rvd_int8_m4_t r0, const rvd_int8_m4_t r1, const rvm_int8_m4_t m0) {
	rvd_int8_m4_t res;
	res.r1 = mipp_blend_int8_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int8_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_int8_m8_t mipp_blend_int8_m8(const rvd_int8_m8_t r0, const rvd_int8_m8_t r1, const rvm_int8_m8_t m0) {
	rvd_int8_m8_t res;
	res.r1 = mipp_blend_int8_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_int8_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint64_t mipp_blend_uint64(const rvd_uint64_t r0, const rvd_uint64_t r1, const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_uint64(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_uint64(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_uint64(r0, r1, m0);
#endif
}
inline rvd_uint64_m1_t mipp_blend_uint64_m1(const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1, const rvm_uint64_m1_t m0) {
	return mipp_blend_uint64(r0, r1, m0);
}
inline rvd_uint64_m2_t mipp_blend_uint64_m2(const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1, const rvm_uint64_m2_t m0) {
	rvd_uint64_m2_t res;
	res.r1 = mipp_blend_uint64_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint64_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint64_m4_t mipp_blend_uint64_m4(const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1, const rvm_uint64_m4_t m0) {
	rvd_uint64_m4_t res;
	res.r1 = mipp_blend_uint64_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint64_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint64_m8_t mipp_blend_uint64_m8(const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1, const rvm_uint64_m8_t m0) {
	rvd_uint64_m8_t res;
	res.r1 = mipp_blend_uint64_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint64_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint32_t mipp_blend_uint32(const rvd_uint32_t r0, const rvd_uint32_t r1, const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_uint32(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_uint32(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_uint32(r0, r1, m0);
#endif
}
inline rvd_uint32_m1_t mipp_blend_uint32_m1(const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1, const rvm_uint32_m1_t m0) {
	return mipp_blend_uint32(r0, r1, m0);
}
inline rvd_uint32_m2_t mipp_blend_uint32_m2(const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1, const rvm_uint32_m2_t m0) {
	rvd_uint32_m2_t res;
	res.r1 = mipp_blend_uint32_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint32_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint32_m4_t mipp_blend_uint32_m4(const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1, const rvm_uint32_m4_t m0) {
	rvd_uint32_m4_t res;
	res.r1 = mipp_blend_uint32_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint32_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint32_m8_t mipp_blend_uint32_m8(const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1, const rvm_uint32_m8_t m0) {
	rvd_uint32_m8_t res;
	res.r1 = mipp_blend_uint32_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint32_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint16_t mipp_blend_uint16(const rvd_uint16_t r0, const rvd_uint16_t r1, const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_uint16(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_uint16(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_uint16(r0, r1, m0);
#endif
}
inline rvd_uint16_m1_t mipp_blend_uint16_m1(const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1, const rvm_uint16_m1_t m0) {
	return mipp_blend_uint16(r0, r1, m0);
}
inline rvd_uint16_m2_t mipp_blend_uint16_m2(const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1, const rvm_uint16_m2_t m0) {
	rvd_uint16_m2_t res;
	res.r1 = mipp_blend_uint16_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint16_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint16_m4_t mipp_blend_uint16_m4(const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1, const rvm_uint16_m4_t m0) {
	rvd_uint16_m4_t res;
	res.r1 = mipp_blend_uint16_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint16_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint16_m8_t mipp_blend_uint16_m8(const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1, const rvm_uint16_m8_t m0) {
	rvd_uint16_m8_t res;
	res.r1 = mipp_blend_uint16_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint16_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint8_t mipp_blend_uint8(const rvd_uint8_t r0, const rvd_uint8_t r1, const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_blend_uint8(r0, r1, m0);
#elif defined(__AVX__)
	return mipp_avx_blend_uint8(r0, r1, m0);
#elif defined(__SSE__)
	return mipp_sse_blend_uint8(r0, r1, m0);
#endif
}
inline rvd_uint8_m1_t mipp_blend_uint8_m1(const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1, const rvm_uint8_m1_t m0) {
	return mipp_blend_uint8(r0, r1, m0);
}
inline rvd_uint8_m2_t mipp_blend_uint8_m2(const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1, const rvm_uint8_m2_t m0) {
	rvd_uint8_m2_t res;
	res.r1 = mipp_blend_uint8_m1(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint8_m1(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint8_m4_t mipp_blend_uint8_m4(const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1, const rvm_uint8_m4_t m0) {
	rvd_uint8_m4_t res;
	res.r1 = mipp_blend_uint8_m2(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint8_m2(r0.r2, r1.r2, m0.m2);
	return res;
}
inline rvd_uint8_m8_t mipp_blend_uint8_m8(const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1, const rvm_uint8_m8_t m0) {
	rvd_uint8_m8_t res;
	res.r1 = mipp_blend_uint8_m4(r0.r1, r1.r1, m0.m1);
	res.r2 = mipp_blend_uint8_m4(r0.r2, r1.r2, m0.m2);
	return res;
}
inline int32_t mipp_testz_float64(const rvm_float64_t m0, const rvm_float64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_float64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_float64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_float64(m0, m1);
#endif
}
inline int32_t mipp_testz_float64_m1(const rvm_float64_m1_t m0, const rvm_float64_m1_t m1) {
	return mipp_testz_float64(m0, m1);
}
inline int32_t mipp_testz_float64_m2(const rvm_float64_m2_t m0, const rvm_float64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m2");
	exit(-1);
}
inline int32_t mipp_testz_float64_m4(const rvm_float64_m4_t m0, const rvm_float64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m4");
	exit(-1);
}
inline int32_t mipp_testz_float64_m8(const rvm_float64_m8_t m0, const rvm_float64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float64_m8");
	exit(-1);
}
inline int32_t mipp_testz_float32(const rvm_float32_t m0, const rvm_float32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_float32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_float32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_float32(m0, m1);
#endif
}
inline int32_t mipp_testz_float32_m1(const rvm_float32_m1_t m0, const rvm_float32_m1_t m1) {
	return mipp_testz_float32(m0, m1);
}
inline int32_t mipp_testz_float32_m2(const rvm_float32_m2_t m0, const rvm_float32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m2");
	exit(-1);
}
inline int32_t mipp_testz_float32_m4(const rvm_float32_m4_t m0, const rvm_float32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m4");
	exit(-1);
}
inline int32_t mipp_testz_float32_m8(const rvm_float32_m8_t m0, const rvm_float32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_float32_m8");
	exit(-1);
}
inline int32_t mipp_testz_int64(const rvm_int64_t m0, const rvm_int64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_int64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_int64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_int64(m0, m1);
#endif
}
inline int32_t mipp_testz_int64_m1(const rvm_int64_m1_t m0, const rvm_int64_m1_t m1) {
	return mipp_testz_int64(m0, m1);
}
inline int32_t mipp_testz_int64_m2(const rvm_int64_m2_t m0, const rvm_int64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m2");
	exit(-1);
}
inline int32_t mipp_testz_int64_m4(const rvm_int64_m4_t m0, const rvm_int64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m4");
	exit(-1);
}
inline int32_t mipp_testz_int64_m8(const rvm_int64_m8_t m0, const rvm_int64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int64_m8");
	exit(-1);
}
inline int32_t mipp_testz_int32(const rvm_int32_t m0, const rvm_int32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_int32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_int32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_int32(m0, m1);
#endif
}
inline int32_t mipp_testz_int32_m1(const rvm_int32_m1_t m0, const rvm_int32_m1_t m1) {
	return mipp_testz_int32(m0, m1);
}
inline int32_t mipp_testz_int32_m2(const rvm_int32_m2_t m0, const rvm_int32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m2");
	exit(-1);
}
inline int32_t mipp_testz_int32_m4(const rvm_int32_m4_t m0, const rvm_int32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m4");
	exit(-1);
}
inline int32_t mipp_testz_int32_m8(const rvm_int32_m8_t m0, const rvm_int32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int32_m8");
	exit(-1);
}
inline int32_t mipp_testz_int16(const rvm_int16_t m0, const rvm_int16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_int16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_int16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_int16(m0, m1);
#endif
}
inline int32_t mipp_testz_int16_m1(const rvm_int16_m1_t m0, const rvm_int16_m1_t m1) {
	return mipp_testz_int16(m0, m1);
}
inline int32_t mipp_testz_int16_m2(const rvm_int16_m2_t m0, const rvm_int16_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m2");
	exit(-1);
}
inline int32_t mipp_testz_int16_m4(const rvm_int16_m4_t m0, const rvm_int16_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m4");
	exit(-1);
}
inline int32_t mipp_testz_int16_m8(const rvm_int16_m8_t m0, const rvm_int16_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int16_m8");
	exit(-1);
}
inline int32_t mipp_testz_int8(const rvm_int8_t m0, const rvm_int8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_int8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_int8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_int8(m0, m1);
#endif
}
inline int32_t mipp_testz_int8_m1(const rvm_int8_m1_t m0, const rvm_int8_m1_t m1) {
	return mipp_testz_int8(m0, m1);
}
inline int32_t mipp_testz_int8_m2(const rvm_int8_m2_t m0, const rvm_int8_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m2");
	exit(-1);
}
inline int32_t mipp_testz_int8_m4(const rvm_int8_m4_t m0, const rvm_int8_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m4");
	exit(-1);
}
inline int32_t mipp_testz_int8_m8(const rvm_int8_m8_t m0, const rvm_int8_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_int8_m8");
	exit(-1);
}
inline int32_t mipp_testz_uint64(const rvm_uint64_t m0, const rvm_uint64_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_uint64(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_uint64(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_uint64(m0, m1);
#endif
}
inline int32_t mipp_testz_uint64_m1(const rvm_uint64_m1_t m0, const rvm_uint64_m1_t m1) {
	return mipp_testz_uint64(m0, m1);
}
inline int32_t mipp_testz_uint64_m2(const rvm_uint64_m2_t m0, const rvm_uint64_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m2");
	exit(-1);
}
inline int32_t mipp_testz_uint64_m4(const rvm_uint64_m4_t m0, const rvm_uint64_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m4");
	exit(-1);
}
inline int32_t mipp_testz_uint64_m8(const rvm_uint64_m8_t m0, const rvm_uint64_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint64_m8");
	exit(-1);
}
inline int32_t mipp_testz_uint32(const rvm_uint32_t m0, const rvm_uint32_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_uint32(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_uint32(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_uint32(m0, m1);
#endif
}
inline int32_t mipp_testz_uint32_m1(const rvm_uint32_m1_t m0, const rvm_uint32_m1_t m1) {
	return mipp_testz_uint32(m0, m1);
}
inline int32_t mipp_testz_uint32_m2(const rvm_uint32_m2_t m0, const rvm_uint32_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m2");
	exit(-1);
}
inline int32_t mipp_testz_uint32_m4(const rvm_uint32_m4_t m0, const rvm_uint32_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m4");
	exit(-1);
}
inline int32_t mipp_testz_uint32_m8(const rvm_uint32_m8_t m0, const rvm_uint32_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint32_m8");
	exit(-1);
}
inline int32_t mipp_testz_uint16(const rvm_uint16_t m0, const rvm_uint16_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_uint16(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_uint16(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_uint16(m0, m1);
#endif
}
inline int32_t mipp_testz_uint16_m1(const rvm_uint16_m1_t m0, const rvm_uint16_m1_t m1) {
	return mipp_testz_uint16(m0, m1);
}
inline int32_t mipp_testz_uint16_m2(const rvm_uint16_m2_t m0, const rvm_uint16_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m2");
	exit(-1);
}
inline int32_t mipp_testz_uint16_m4(const rvm_uint16_m4_t m0, const rvm_uint16_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m4");
	exit(-1);
}
inline int32_t mipp_testz_uint16_m8(const rvm_uint16_m8_t m0, const rvm_uint16_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint16_m8");
	exit(-1);
}
inline int32_t mipp_testz_uint8(const rvm_uint8_t m0, const rvm_uint8_t m1) {
#if defined(__AVX512__)
	return mipp_avx512_testz_uint8(m0, m1);
#elif defined(__AVX__)
	return mipp_avx_testz_uint8(m0, m1);
#elif defined(__SSE__)
	return mipp_sse_testz_uint8(m0, m1);
#endif
}
inline int32_t mipp_testz_uint8_m1(const rvm_uint8_m1_t m0, const rvm_uint8_m1_t m1) {
	return mipp_testz_uint8(m0, m1);
}
inline int32_t mipp_testz_uint8_m2(const rvm_uint8_m2_t m0, const rvm_uint8_m2_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m2");
	exit(-1);
}
inline int32_t mipp_testz_uint8_m4(const rvm_uint8_m4_t m0, const rvm_uint8_m4_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m4");
	exit(-1);
}
inline int32_t mipp_testz_uint8_m8(const rvm_uint8_m8_t m0, const rvm_uint8_m8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_uint8_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_float64(const rvm_float64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_float64(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_float64(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_float64(m0);
#endif
}
inline int32_t mipp_testz_2_float64_m1(const rvm_float64_m1_t m0) {
	return mipp_testz_2_float64(m0);
}
inline int32_t mipp_testz_2_float64_m2(const rvm_float64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_float64_m4(const rvm_float64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_float64_m8(const rvm_float64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float64_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_float32(const rvm_float32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_float32(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_float32(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_float32(m0);
#endif
}
inline int32_t mipp_testz_2_float32_m1(const rvm_float32_m1_t m0) {
	return mipp_testz_2_float32(m0);
}
inline int32_t mipp_testz_2_float32_m2(const rvm_float32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_float32_m4(const rvm_float32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_float32_m8(const rvm_float32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_float32_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_int64(const rvm_int64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_int64(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_int64(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_int64(m0);
#endif
}
inline int32_t mipp_testz_2_int64_m1(const rvm_int64_m1_t m0) {
	return mipp_testz_2_int64(m0);
}
inline int32_t mipp_testz_2_int64_m2(const rvm_int64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_int64_m4(const rvm_int64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_int64_m8(const rvm_int64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int64_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_int32(const rvm_int32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_int32(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_int32(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_int32(m0);
#endif
}
inline int32_t mipp_testz_2_int32_m1(const rvm_int32_m1_t m0) {
	return mipp_testz_2_int32(m0);
}
inline int32_t mipp_testz_2_int32_m2(const rvm_int32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_int32_m4(const rvm_int32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_int32_m8(const rvm_int32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int32_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_int16(const rvm_int16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_int16(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_int16(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_int16(m0);
#endif
}
inline int32_t mipp_testz_2_int16_m1(const rvm_int16_m1_t m0) {
	return mipp_testz_2_int16(m0);
}
inline int32_t mipp_testz_2_int16_m2(const rvm_int16_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_int16_m4(const rvm_int16_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_int16_m8(const rvm_int16_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int16_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_int8(const rvm_int8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_int8(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_int8(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_int8(m0);
#endif
}
inline int32_t mipp_testz_2_int8_m1(const rvm_int8_m1_t m0) {
	return mipp_testz_2_int8(m0);
}
inline int32_t mipp_testz_2_int8_m2(const rvm_int8_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_int8_m4(const rvm_int8_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_int8_m8(const rvm_int8_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_int8_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_uint64(const rvm_uint64_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_uint64(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_uint64(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_uint64(m0);
#endif
}
inline int32_t mipp_testz_2_uint64_m1(const rvm_uint64_m1_t m0) {
	return mipp_testz_2_uint64(m0);
}
inline int32_t mipp_testz_2_uint64_m2(const rvm_uint64_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_uint64_m4(const rvm_uint64_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_uint64_m8(const rvm_uint64_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint64_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_uint32(const rvm_uint32_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_uint32(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_uint32(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_uint32(m0);
#endif
}
inline int32_t mipp_testz_2_uint32_m1(const rvm_uint32_m1_t m0) {
	return mipp_testz_2_uint32(m0);
}
inline int32_t mipp_testz_2_uint32_m2(const rvm_uint32_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_uint32_m4(const rvm_uint32_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_uint32_m8(const rvm_uint32_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint32_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_uint16(const rvm_uint16_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_uint16(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_uint16(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_uint16(m0);
#endif
}
inline int32_t mipp_testz_2_uint16_m1(const rvm_uint16_m1_t m0) {
	return mipp_testz_2_uint16(m0);
}
inline int32_t mipp_testz_2_uint16_m2(const rvm_uint16_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_uint16_m4(const rvm_uint16_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_uint16_m8(const rvm_uint16_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint16_m8");
	exit(-1);
}
inline int32_t mipp_testz_2_uint8(const rvm_uint8_t m0) {
#if defined(__AVX512__)
	return mipp_avx512_testz_2_uint8(m0);
#elif defined(__AVX__)
	return mipp_avx_testz_2_uint8(m0);
#elif defined(__SSE__)
	return mipp_sse_testz_2_uint8(m0);
#endif
}
inline int32_t mipp_testz_2_uint8_m1(const rvm_uint8_m1_t m0) {
	return mipp_testz_2_uint8(m0);
}
inline int32_t mipp_testz_2_uint8_m2(const rvm_uint8_m2_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m2");
	exit(-1);
}
inline int32_t mipp_testz_2_uint8_m4(const rvm_uint8_m4_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m4");
	exit(-1);
}
inline int32_t mipp_testz_2_uint8_m8(const rvm_uint8_m8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_testz_2_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_hadd_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_hadd_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hadd_float64(r0);
}
inline rvd_float64_m2_t mipp_hadd_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_hadd_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_hadd_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_hadd_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_hadd_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hadd_float32(r0);
}
inline rvd_float32_m2_t mipp_hadd_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_hadd_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_hadd_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_hadd_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_hadd_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hadd_int64(r0);
}
inline rvd_int64_m2_t mipp_hadd_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_hadd_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_hadd_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_hadd_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_hadd_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hadd_int32(r0);
}
inline rvd_int32_m2_t mipp_hadd_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_hadd_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_hadd_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_hadd_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_hadd_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hadd_int16(r0);
}
inline rvd_int16_m2_t mipp_hadd_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_hadd_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_hadd_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_hadd_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_hadd_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hadd_int8(r0);
}
inline rvd_int8_m2_t mipp_hadd_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_hadd_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_hadd_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_hadd_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_hadd_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hadd_uint64(r0);
}
inline rvd_uint64_m2_t mipp_hadd_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_hadd_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_hadd_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_hadd_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_hadd_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hadd_uint32(r0);
}
inline rvd_uint32_m2_t mipp_hadd_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_hadd_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_hadd_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_hadd_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_hadd_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hadd_uint16(r0);
}
inline rvd_uint16_m2_t mipp_hadd_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_hadd_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_hadd_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_hadd_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hadd_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_hadd_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_hadd_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_hadd_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hadd_uint8(r0);
}
inline rvd_uint8_m2_t mipp_hadd_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_hadd_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_hadd_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hadd_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_hmul_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_hmul_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmul_float64(r0);
}
inline rvd_float64_m2_t mipp_hmul_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_hmul_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_hmul_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_hmul_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_hmul_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmul_float32(r0);
}
inline rvd_float32_m2_t mipp_hmul_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_hmul_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_hmul_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_hmul_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_hmul_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmul_int64(r0);
}
inline rvd_int64_m2_t mipp_hmul_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_hmul_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_hmul_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_hmul_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_hmul_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmul_int32(r0);
}
inline rvd_int32_m2_t mipp_hmul_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_hmul_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_hmul_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_hmul_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_hmul_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmul_int16(r0);
}
inline rvd_int16_m2_t mipp_hmul_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_hmul_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_hmul_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_hmul_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_hmul_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmul_int8(r0);
}
inline rvd_int8_m2_t mipp_hmul_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_hmul_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_hmul_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_hmul_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_hmul_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmul_uint64(r0);
}
inline rvd_uint64_m2_t mipp_hmul_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_hmul_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_hmul_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_hmul_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_hmul_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmul_uint32(r0);
}
inline rvd_uint32_m2_t mipp_hmul_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_hmul_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_hmul_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_hmul_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_hmul_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmul_uint16(r0);
}
inline rvd_uint16_m2_t mipp_hmul_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_hmul_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_hmul_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_hmul_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmul_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmul_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmul_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_hmul_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmul_uint8(r0);
}
inline rvd_uint8_m2_t mipp_hmul_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_hmul_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_hmul_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmul_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_hmin_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_hmin_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmin_float64(r0);
}
inline rvd_float64_m2_t mipp_hmin_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_hmin_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_hmin_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_hmin_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_hmin_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmin_float32(r0);
}
inline rvd_float32_m2_t mipp_hmin_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_hmin_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_hmin_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_hmin_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_hmin_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmin_int64(r0);
}
inline rvd_int64_m2_t mipp_hmin_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_hmin_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_hmin_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_hmin_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_hmin_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmin_int32(r0);
}
inline rvd_int32_m2_t mipp_hmin_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_hmin_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_hmin_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_hmin_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_hmin_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmin_int16(r0);
}
inline rvd_int16_m2_t mipp_hmin_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_hmin_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_hmin_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_hmin_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_hmin_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmin_int8(r0);
}
inline rvd_int8_m2_t mipp_hmin_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_hmin_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_hmin_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_hmin_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_hmin_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmin_uint64(r0);
}
inline rvd_uint64_m2_t mipp_hmin_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_hmin_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_hmin_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_hmin_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_hmin_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmin_uint32(r0);
}
inline rvd_uint32_m2_t mipp_hmin_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_hmin_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_hmin_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_hmin_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_hmin_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmin_uint16(r0);
}
inline rvd_uint16_m2_t mipp_hmin_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_hmin_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_hmin_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_hmin_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmin_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmin_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmin_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_hmin_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmin_uint8(r0);
}
inline rvd_uint8_m2_t mipp_hmin_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_hmin_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_hmin_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmin_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_hmax_float64(const rvd_float64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_float64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_float64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_float64(r0);
#endif
}
inline rvd_float64_m1_t mipp_hmax_float64_m1(const rvd_float64_m1_t r0) {
	return mipp_hmax_float64(r0);
}
inline rvd_float64_m2_t mipp_hmax_float64_m2(const rvd_float64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_hmax_float64_m4(const rvd_float64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_hmax_float64_m8(const rvd_float64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_hmax_float32(const rvd_float32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_float32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_float32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_float32(r0);
#endif
}
inline rvd_float32_m1_t mipp_hmax_float32_m1(const rvd_float32_m1_t r0) {
	return mipp_hmax_float32(r0);
}
inline rvd_float32_m2_t mipp_hmax_float32_m2(const rvd_float32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_hmax_float32_m4(const rvd_float32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_hmax_float32_m8(const rvd_float32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_hmax_int64(const rvd_int64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_int64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_int64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_int64(r0);
#endif
}
inline rvd_int64_m1_t mipp_hmax_int64_m1(const rvd_int64_m1_t r0) {
	return mipp_hmax_int64(r0);
}
inline rvd_int64_m2_t mipp_hmax_int64_m2(const rvd_int64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_hmax_int64_m4(const rvd_int64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_hmax_int64_m8(const rvd_int64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_hmax_int32(const rvd_int32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_int32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_int32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_int32(r0);
#endif
}
inline rvd_int32_m1_t mipp_hmax_int32_m1(const rvd_int32_m1_t r0) {
	return mipp_hmax_int32(r0);
}
inline rvd_int32_m2_t mipp_hmax_int32_m2(const rvd_int32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_hmax_int32_m4(const rvd_int32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_hmax_int32_m8(const rvd_int32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_hmax_int16(const rvd_int16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_int16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_int16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_int16(r0);
#endif
}
inline rvd_int16_m1_t mipp_hmax_int16_m1(const rvd_int16_m1_t r0) {
	return mipp_hmax_int16(r0);
}
inline rvd_int16_m2_t mipp_hmax_int16_m2(const rvd_int16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_hmax_int16_m4(const rvd_int16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_hmax_int16_m8(const rvd_int16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_hmax_int8(const rvd_int8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_int8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_int8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_int8(r0);
#endif
}
inline rvd_int8_m1_t mipp_hmax_int8_m1(const rvd_int8_m1_t r0) {
	return mipp_hmax_int8(r0);
}
inline rvd_int8_m2_t mipp_hmax_int8_m2(const rvd_int8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_hmax_int8_m4(const rvd_int8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_hmax_int8_m8(const rvd_int8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_hmax_uint64(const rvd_uint64_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_uint64(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_uint64(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_uint64(r0);
#endif
}
inline rvd_uint64_m1_t mipp_hmax_uint64_m1(const rvd_uint64_m1_t r0) {
	return mipp_hmax_uint64(r0);
}
inline rvd_uint64_m2_t mipp_hmax_uint64_m2(const rvd_uint64_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_hmax_uint64_m4(const rvd_uint64_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_hmax_uint64_m8(const rvd_uint64_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_hmax_uint32(const rvd_uint32_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_uint32(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_uint32(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_uint32(r0);
#endif
}
inline rvd_uint32_m1_t mipp_hmax_uint32_m1(const rvd_uint32_m1_t r0) {
	return mipp_hmax_uint32(r0);
}
inline rvd_uint32_m2_t mipp_hmax_uint32_m2(const rvd_uint32_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_hmax_uint32_m4(const rvd_uint32_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_hmax_uint32_m8(const rvd_uint32_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_hmax_uint16(const rvd_uint16_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_uint16(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_uint16(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_uint16(r0);
#endif
}
inline rvd_uint16_m1_t mipp_hmax_uint16_m1(const rvd_uint16_m1_t r0) {
	return mipp_hmax_uint16(r0);
}
inline rvd_uint16_m2_t mipp_hmax_uint16_m2(const rvd_uint16_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_hmax_uint16_m4(const rvd_uint16_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_hmax_uint16_m8(const rvd_uint16_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_hmax_uint8(const rvd_uint8_t r0) {
#if defined(__AVX512__)
	return mipp_avx512_hmax_uint8(r0);
#elif defined(__AVX__)
	return mipp_avx_hmax_uint8(r0);
#elif defined(__SSE__)
	return mipp_sse_hmax_uint8(r0);
#endif
}
inline rvd_uint8_m1_t mipp_hmax_uint8_m1(const rvd_uint8_m1_t r0) {
	return mipp_hmax_uint8(r0);
}
inline rvd_uint8_m2_t mipp_hmax_uint8_m2(const rvd_uint8_m2_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_hmax_uint8_m4(const rvd_uint8_m4_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_hmax_uint8_m8(const rvd_uint8_m8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_hmax_uint8_m8");
	exit(-1);
}
inline rvd_float64_t mipp_maskz_add_float64(const rvm_float64_t m0, const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_float64(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_float64(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_float64(m0, r0, r1);
#endif
}
inline rvd_float64_m1_t mipp_maskz_add_float64_m1(const rvm_float64_m1_t m0, const rvd_float64_m1_t r0, const rvd_float64_m1_t r1) {
	return mipp_maskz_add_float64(m0, r0, r1);
}
inline rvd_float64_m2_t mipp_maskz_add_float64_m2(const rvm_float64_m2_t m0, const rvd_float64_m2_t r0, const rvd_float64_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float64_m2");
	exit(-1);
}
inline rvd_float64_m4_t mipp_maskz_add_float64_m4(const rvm_float64_m4_t m0, const rvd_float64_m4_t r0, const rvd_float64_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float64_m4");
	exit(-1);
}
inline rvd_float64_m8_t mipp_maskz_add_float64_m8(const rvm_float64_m8_t m0, const rvd_float64_m8_t r0, const rvd_float64_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float64_m8");
	exit(-1);
}
inline rvd_float32_t mipp_maskz_add_float32(const rvm_float32_t m0, const rvd_float32_t r0, const rvd_float32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_float32(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_float32(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_float32(m0, r0, r1);
#endif
}
inline rvd_float32_m1_t mipp_maskz_add_float32_m1(const rvm_float32_m1_t m0, const rvd_float32_m1_t r0, const rvd_float32_m1_t r1) {
	return mipp_maskz_add_float32(m0, r0, r1);
}
inline rvd_float32_m2_t mipp_maskz_add_float32_m2(const rvm_float32_m2_t m0, const rvd_float32_m2_t r0, const rvd_float32_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float32_m2");
	exit(-1);
}
inline rvd_float32_m4_t mipp_maskz_add_float32_m4(const rvm_float32_m4_t m0, const rvd_float32_m4_t r0, const rvd_float32_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float32_m4");
	exit(-1);
}
inline rvd_float32_m8_t mipp_maskz_add_float32_m8(const rvm_float32_m8_t m0, const rvd_float32_m8_t r0, const rvd_float32_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_float32_m8");
	exit(-1);
}
inline rvd_int64_t mipp_maskz_add_int64(const rvm_int64_t m0, const rvd_int64_t r0, const rvd_int64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_int64(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_int64(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_int64(m0, r0, r1);
#endif
}
inline rvd_int64_m1_t mipp_maskz_add_int64_m1(const rvm_int64_m1_t m0, const rvd_int64_m1_t r0, const rvd_int64_m1_t r1) {
	return mipp_maskz_add_int64(m0, r0, r1);
}
inline rvd_int64_m2_t mipp_maskz_add_int64_m2(const rvm_int64_m2_t m0, const rvd_int64_m2_t r0, const rvd_int64_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int64_m2");
	exit(-1);
}
inline rvd_int64_m4_t mipp_maskz_add_int64_m4(const rvm_int64_m4_t m0, const rvd_int64_m4_t r0, const rvd_int64_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int64_m4");
	exit(-1);
}
inline rvd_int64_m8_t mipp_maskz_add_int64_m8(const rvm_int64_m8_t m0, const rvd_int64_m8_t r0, const rvd_int64_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int64_m8");
	exit(-1);
}
inline rvd_int32_t mipp_maskz_add_int32(const rvm_int32_t m0, const rvd_int32_t r0, const rvd_int32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_int32(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_int32(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_int32(m0, r0, r1);
#endif
}
inline rvd_int32_m1_t mipp_maskz_add_int32_m1(const rvm_int32_m1_t m0, const rvd_int32_m1_t r0, const rvd_int32_m1_t r1) {
	return mipp_maskz_add_int32(m0, r0, r1);
}
inline rvd_int32_m2_t mipp_maskz_add_int32_m2(const rvm_int32_m2_t m0, const rvd_int32_m2_t r0, const rvd_int32_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int32_m2");
	exit(-1);
}
inline rvd_int32_m4_t mipp_maskz_add_int32_m4(const rvm_int32_m4_t m0, const rvd_int32_m4_t r0, const rvd_int32_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int32_m4");
	exit(-1);
}
inline rvd_int32_m8_t mipp_maskz_add_int32_m8(const rvm_int32_m8_t m0, const rvd_int32_m8_t r0, const rvd_int32_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int32_m8");
	exit(-1);
}
inline rvd_int16_t mipp_maskz_add_int16(const rvm_int16_t m0, const rvd_int16_t r0, const rvd_int16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_int16(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_int16(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_int16(m0, r0, r1);
#endif
}
inline rvd_int16_m1_t mipp_maskz_add_int16_m1(const rvm_int16_m1_t m0, const rvd_int16_m1_t r0, const rvd_int16_m1_t r1) {
	return mipp_maskz_add_int16(m0, r0, r1);
}
inline rvd_int16_m2_t mipp_maskz_add_int16_m2(const rvm_int16_m2_t m0, const rvd_int16_m2_t r0, const rvd_int16_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int16_m2");
	exit(-1);
}
inline rvd_int16_m4_t mipp_maskz_add_int16_m4(const rvm_int16_m4_t m0, const rvd_int16_m4_t r0, const rvd_int16_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int16_m4");
	exit(-1);
}
inline rvd_int16_m8_t mipp_maskz_add_int16_m8(const rvm_int16_m8_t m0, const rvd_int16_m8_t r0, const rvd_int16_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int16_m8");
	exit(-1);
}
inline rvd_int8_t mipp_maskz_add_int8(const rvm_int8_t m0, const rvd_int8_t r0, const rvd_int8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_int8(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_int8(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_int8(m0, r0, r1);
#endif
}
inline rvd_int8_m1_t mipp_maskz_add_int8_m1(const rvm_int8_m1_t m0, const rvd_int8_m1_t r0, const rvd_int8_m1_t r1) {
	return mipp_maskz_add_int8(m0, r0, r1);
}
inline rvd_int8_m2_t mipp_maskz_add_int8_m2(const rvm_int8_m2_t m0, const rvd_int8_m2_t r0, const rvd_int8_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int8_m2");
	exit(-1);
}
inline rvd_int8_m4_t mipp_maskz_add_int8_m4(const rvm_int8_m4_t m0, const rvd_int8_m4_t r0, const rvd_int8_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int8_m4");
	exit(-1);
}
inline rvd_int8_m8_t mipp_maskz_add_int8_m8(const rvm_int8_m8_t m0, const rvd_int8_m8_t r0, const rvd_int8_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_int8_m8");
	exit(-1);
}
inline rvd_uint64_t mipp_maskz_add_uint64(const rvm_uint64_t m0, const rvd_uint64_t r0, const rvd_uint64_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_uint64(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_uint64(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_uint64(m0, r0, r1);
#endif
}
inline rvd_uint64_m1_t mipp_maskz_add_uint64_m1(const rvm_uint64_m1_t m0, const rvd_uint64_m1_t r0, const rvd_uint64_m1_t r1) {
	return mipp_maskz_add_uint64(m0, r0, r1);
}
inline rvd_uint64_m2_t mipp_maskz_add_uint64_m2(const rvm_uint64_m2_t m0, const rvd_uint64_m2_t r0, const rvd_uint64_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint64_m2");
	exit(-1);
}
inline rvd_uint64_m4_t mipp_maskz_add_uint64_m4(const rvm_uint64_m4_t m0, const rvd_uint64_m4_t r0, const rvd_uint64_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint64_m4");
	exit(-1);
}
inline rvd_uint64_m8_t mipp_maskz_add_uint64_m8(const rvm_uint64_m8_t m0, const rvd_uint64_m8_t r0, const rvd_uint64_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint64_m8");
	exit(-1);
}
inline rvd_uint32_t mipp_maskz_add_uint32(const rvm_uint32_t m0, const rvd_uint32_t r0, const rvd_uint32_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_uint32(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_uint32(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_uint32(m0, r0, r1);
#endif
}
inline rvd_uint32_m1_t mipp_maskz_add_uint32_m1(const rvm_uint32_m1_t m0, const rvd_uint32_m1_t r0, const rvd_uint32_m1_t r1) {
	return mipp_maskz_add_uint32(m0, r0, r1);
}
inline rvd_uint32_m2_t mipp_maskz_add_uint32_m2(const rvm_uint32_m2_t m0, const rvd_uint32_m2_t r0, const rvd_uint32_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint32_m2");
	exit(-1);
}
inline rvd_uint32_m4_t mipp_maskz_add_uint32_m4(const rvm_uint32_m4_t m0, const rvd_uint32_m4_t r0, const rvd_uint32_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint32_m4");
	exit(-1);
}
inline rvd_uint32_m8_t mipp_maskz_add_uint32_m8(const rvm_uint32_m8_t m0, const rvd_uint32_m8_t r0, const rvd_uint32_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint32_m8");
	exit(-1);
}
inline rvd_uint16_t mipp_maskz_add_uint16(const rvm_uint16_t m0, const rvd_uint16_t r0, const rvd_uint16_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_uint16(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_uint16(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_uint16(m0, r0, r1);
#endif
}
inline rvd_uint16_m1_t mipp_maskz_add_uint16_m1(const rvm_uint16_m1_t m0, const rvd_uint16_m1_t r0, const rvd_uint16_m1_t r1) {
	return mipp_maskz_add_uint16(m0, r0, r1);
}
inline rvd_uint16_m2_t mipp_maskz_add_uint16_m2(const rvm_uint16_m2_t m0, const rvd_uint16_m2_t r0, const rvd_uint16_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint16_m2");
	exit(-1);
}
inline rvd_uint16_m4_t mipp_maskz_add_uint16_m4(const rvm_uint16_m4_t m0, const rvd_uint16_m4_t r0, const rvd_uint16_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint16_m4");
	exit(-1);
}
inline rvd_uint16_m8_t mipp_maskz_add_uint16_m8(const rvm_uint16_m8_t m0, const rvd_uint16_m8_t r0, const rvd_uint16_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint16_m8");
	exit(-1);
}
inline rvd_uint8_t mipp_maskz_add_uint8(const rvm_uint8_t m0, const rvd_uint8_t r0, const rvd_uint8_t r1) {
#if defined(__AVX512__)
	return mipp_avx512_maskz_add_uint8(m0, r0, r1);
#elif defined(__AVX__)
	return mipp_avx_maskz_add_uint8(m0, r0, r1);
#elif defined(__SSE__)
	return mipp_sse_maskz_add_uint8(m0, r0, r1);
#endif
}
inline rvd_uint8_m1_t mipp_maskz_add_uint8_m1(const rvm_uint8_m1_t m0, const rvd_uint8_m1_t r0, const rvd_uint8_m1_t r1) {
	return mipp_maskz_add_uint8(m0, r0, r1);
}
inline rvd_uint8_m2_t mipp_maskz_add_uint8_m2(const rvm_uint8_m2_t m0, const rvd_uint8_m2_t r0, const rvd_uint8_m2_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint8_m2");
	exit(-1);
}
inline rvd_uint8_m4_t mipp_maskz_add_uint8_m4(const rvm_uint8_m4_t m0, const rvd_uint8_m4_t r0, const rvd_uint8_m4_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint8_m4");
	exit(-1);
}
inline rvd_uint8_m8_t mipp_maskz_add_uint8_m8(const rvm_uint8_m8_t m0, const rvd_uint8_m8_t r0, const rvd_uint8_m8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_maskz_add_uint8_m8");
	exit(-1);
}
#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */
