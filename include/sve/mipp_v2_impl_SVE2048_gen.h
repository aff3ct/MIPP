#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE2048_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE2048_H_
#if defined(__ARM_FEATURE_SVE)
#include <arm_sve.h>
#define MIPP_SVE2048_RVD_SIZE_BIT 2048
#define MIPP_SVE2048_RVD_SIZE_BYTE 256
#define MIPP_SVE2048_N_FLOAT64 32
#define MIPP_SVE2048_N_FLOAT32 64
#define MIPP_SVE2048_N_INT64 32
#define MIPP_SVE2048_N_INT32 64
#define MIPP_SVE2048_N_INT16 128
#define MIPP_SVE2048_N_INT8 256
#define MIPP_SVE2048_N_UINT64 32
#define MIPP_SVE2048_N_UINT32 64
#define MIPP_SVE2048_N_UINT16 128
#define MIPP_SVE2048_N_UINT8 256
typedef svfloat64_t fixed_2048_float64_t __attribute__((arm_sve_vector_bits(2048)));
typedef svfloat32_t fixed_2048_float32_t __attribute__((arm_sve_vector_bits(2048)));
typedef svint64_t fixed_2048_int64_t __attribute__((arm_sve_vector_bits(2048)));
typedef svint32_t fixed_2048_int32_t __attribute__((arm_sve_vector_bits(2048)));
typedef svint16_t fixed_2048_int16_t __attribute__((arm_sve_vector_bits(2048)));
typedef svint8_t fixed_2048_int8_t __attribute__((arm_sve_vector_bits(2048)));
typedef svuint64_t fixed_2048_uint64_t __attribute__((arm_sve_vector_bits(2048)));
typedef svuint32_t fixed_2048_uint32_t __attribute__((arm_sve_vector_bits(2048)));
typedef svuint16_t fixed_2048_uint16_t __attribute__((arm_sve_vector_bits(2048)));
typedef svuint8_t fixed_2048_uint8_t __attribute__((arm_sve_vector_bits(2048)));
typedef svbool_t fixed_2048_bool_t __attribute__((arm_sve_vector_bits(2048)));
typedef struct { fixed_2048_float64_t r; } rvd_sve2048_float64_t;
typedef struct { fixed_2048_float32_t r; } rvd_sve2048_float32_t;
typedef struct { fixed_2048_int64_t r; } rvd_sve2048_int64_t;
typedef struct { fixed_2048_int32_t r; } rvd_sve2048_int32_t;
typedef struct { fixed_2048_int16_t r; } rvd_sve2048_int16_t;
typedef struct { fixed_2048_int8_t r; } rvd_sve2048_int8_t;
typedef struct { fixed_2048_uint64_t r; } rvd_sve2048_uint64_t;
typedef struct { fixed_2048_uint32_t r; } rvd_sve2048_uint32_t;
typedef struct { fixed_2048_uint16_t r; } rvd_sve2048_uint16_t;
typedef struct { fixed_2048_uint8_t r; } rvd_sve2048_uint8_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_float64_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_float32_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_int64_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_int32_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_int16_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_int8_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_uint64_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_uint32_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_uint16_t;
typedef struct { fixed_2048_bool_t m; } rvm_sve2048_uint8_t;
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_float64_float64(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_float64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_float32_float64(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_int64_float64(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_int32_float64(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_int16_float64(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_int8_float64(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_uint64_float64(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_uint32_float64(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_uint16_float64(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float64_t mipp_sve2048_cast_uint8_float64(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_float64_t res;
	res.r= svreinterpret_f64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_float64_float32(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_float32_float32(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_float32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_int64_float32(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_int32_float32(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_int16_float32(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_int8_float32(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_uint64_float32(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_uint32_float32(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_uint16_float32(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_float32_t mipp_sve2048_cast_uint8_float32(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_float32_t res;
	res.r= svreinterpret_f32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_float64_int64(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_float32_int64(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_int64_int64(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_int32_int64(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_int16_int64(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_int8_int64(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_uint64_int64(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_uint32_int64(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_uint16_int64(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int64_t mipp_sve2048_cast_uint8_int64(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_int64_t res;
	res.r= svreinterpret_s64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_float64_int32(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_float32_int32(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_int64_int32(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_int32_int32(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_int16_int32(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_int8_int32(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_uint64_int32(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_uint32_int32(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_uint16_int32(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int32_t mipp_sve2048_cast_uint8_int32(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_int32_t res;
	res.r= svreinterpret_s32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_float64_int16(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_float32_int16(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_int64_int16(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_int32_int16(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_int16_int16(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_int8_int16(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_uint64_int16(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_uint32_int16(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_uint16_int16(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int16_t mipp_sve2048_cast_uint8_int16(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_int16_t res;
	res.r= svreinterpret_s16_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_float64_int8(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_float32_int8(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_int64_int8(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_int32_int8(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_int16_int8(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_int8_int8(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_uint64_int8(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_uint32_int8(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_uint16_int8(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_int8_t mipp_sve2048_cast_uint8_int8(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_int8_t res;
	res.r= svreinterpret_s8_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_float64_uint64(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_float32_uint64(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_int64_uint64(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_int32_uint64(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_int16_uint64(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_int8_uint64(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_uint64_uint64(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_uint32_uint64(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_uint16_uint64(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint64_t mipp_sve2048_cast_uint8_uint64(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_uint64_t res;
	res.r= svreinterpret_u64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_float64_uint32(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_float32_uint32(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_int64_uint32(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_int32_uint32(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_int16_uint32(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_int8_uint32(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_uint64_uint32(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_uint32_uint32(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_uint16_uint32(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint32_t mipp_sve2048_cast_uint8_uint32(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_uint32_t res;
	res.r= svreinterpret_u32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_float64_uint16(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_float32_uint16(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_int64_uint16(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_int32_uint16(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_int16_uint16(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_int8_uint16(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_uint64_uint16(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_uint32_uint16(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_uint16_uint16(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint16_t mipp_sve2048_cast_uint8_uint16(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_uint16_t res;
	res.r= svreinterpret_u16_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_float64_uint8(const rvd_sve2048_float64_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_float32_uint8(const rvd_sve2048_float32_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_int64_uint8(const rvd_sve2048_int64_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_int32_uint8(const rvd_sve2048_int32_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_int16_uint8(const rvd_sve2048_int16_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_int8_uint8(const rvd_sve2048_int8_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_uint64_uint8(const rvd_sve2048_uint64_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_uint32_uint8(const rvd_sve2048_uint32_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_uint16_uint8(const rvd_sve2048_uint16_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= svreinterpret_u8_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve2048_uint8_t mipp_sve2048_cast_uint8_uint8(const rvd_sve2048_uint8_t r0) {
	rvd_sve2048_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_float64_float64(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_float32_float64(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_int64_float64(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_int32_float64(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_int16_float64(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_int8_float64(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_uint64_float64(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_uint32_float64(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_uint16_float64(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float64_t mipp_sve2048_cast_k_uint8_float64(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_float64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_float64_float32(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_float32_float32(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_int64_float32(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_int32_float32(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_int16_float32(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_int8_float32(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_uint64_float32(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_uint32_float32(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_uint16_float32(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_float32_t mipp_sve2048_cast_k_uint8_float32(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_float32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_float64_int64(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_float32_int64(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_int64_int64(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_int32_int64(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_int16_int64(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_int8_int64(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_uint64_int64(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_uint32_int64(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_uint16_int64(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int64_t mipp_sve2048_cast_k_uint8_int64(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_int64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_float64_int32(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_float32_int32(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_int64_int32(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_int32_int32(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_int16_int32(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_int8_int32(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_uint64_int32(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_uint32_int32(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_uint16_int32(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int32_t mipp_sve2048_cast_k_uint8_int32(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_int32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_float64_int16(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_float32_int16(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_int64_int16(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_int32_int16(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_int16_int16(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_int8_int16(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_uint64_int16(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_uint32_int16(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_uint16_int16(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int16_t mipp_sve2048_cast_k_uint8_int16(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_int16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_float64_int8(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_float32_int8(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_int64_int8(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_int32_int8(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_int16_int8(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_int8_int8(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_uint64_int8(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_uint32_int8(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_uint16_int8(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_int8_t mipp_sve2048_cast_k_uint8_int8(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_int8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_float64_uint64(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_float32_uint64(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_int64_uint64(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_int32_uint64(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_int16_uint64(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_int8_uint64(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_uint64_uint64(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_uint32_uint64(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_uint16_uint64(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint64_t mipp_sve2048_cast_k_uint8_uint64(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_uint64_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_float64_uint32(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_float32_uint32(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_int64_uint32(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_int32_uint32(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_int16_uint32(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_int8_uint32(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_uint64_uint32(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_uint32_uint32(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_uint16_uint32(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint32_t mipp_sve2048_cast_k_uint8_uint32(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_uint32_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_float64_uint16(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_float32_uint16(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_int64_uint16(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_int32_uint16(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_int16_uint16(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_int8_uint16(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_uint64_uint16(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_uint32_uint16(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_uint16_uint16(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint16_t mipp_sve2048_cast_k_uint8_uint16(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_uint16_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_float64_uint8(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_float32_uint8(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_int64_uint8(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_int32_uint8(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_int16_uint8(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_int8_uint8(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_uint64_uint8(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_uint32_uint8(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_uint16_uint8(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast_k
static inline rvm_sve2048_uint8_t mipp_sve2048_cast_k_uint8_uint8(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_uint8_t res;
	res.m=  m0.m;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_float64_t mipp_sve2048_blend_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1, const rvm_sve2048_float64_t m0) {
	rvd_sve2048_float64_t res;
	res.r= svsel_f64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_float32_t mipp_sve2048_blend_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1, const rvm_sve2048_float32_t m0) {
	rvd_sve2048_float32_t res;
	res.r= svsel_f32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_int64_t mipp_sve2048_blend_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1, const rvm_sve2048_int64_t m0) {
	rvd_sve2048_int64_t res;
	res.r= svsel_s64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_int32_t mipp_sve2048_blend_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1, const rvm_sve2048_int32_t m0) {
	rvd_sve2048_int32_t res;
	res.r= svsel_s32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_int16_t mipp_sve2048_blend_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1, const rvm_sve2048_int16_t m0) {
	rvd_sve2048_int16_t res;
	res.r= svsel_s16(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_int8_t mipp_sve2048_blend_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1, const rvm_sve2048_int8_t m0) {
	rvd_sve2048_int8_t res;
	res.r= svsel_s8(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_uint64_t mipp_sve2048_blend_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1, const rvm_sve2048_uint64_t m0) {
	rvd_sve2048_uint64_t res;
	res.r= svsel_u64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_uint32_t mipp_sve2048_blend_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1, const rvm_sve2048_uint32_t m0) {
	rvd_sve2048_uint32_t res;
	res.r= svsel_u32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_uint16_t mipp_sve2048_blend_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1, const rvm_sve2048_uint16_t m0) {
	rvd_sve2048_uint16_t res;
	res.r= svsel_u16(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve2048_uint8_t mipp_sve2048_blend_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1, const rvm_sve2048_uint8_t m0) {
	rvd_sve2048_uint8_t res;
	res.r= svsel_u8(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_float64_t mipp_sve2048_load_float64(const float64_t* p0) {
	rvd_sve2048_float64_t res;
	res.r= svld1_f64(svptrue_b64(), (float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_float32_t mipp_sve2048_load_float32(const float32_t* p0) {
	rvd_sve2048_float32_t res;
	res.r= svld1_f32(svptrue_b32(), (float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_int64_t mipp_sve2048_load_int64(const int64_t* p0) {
	rvd_sve2048_int64_t res;
	res.r= svld1_s64(svptrue_b64(), (int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_int32_t mipp_sve2048_load_int32(const int32_t* p0) {
	rvd_sve2048_int32_t res;
	res.r= svld1_s32(svptrue_b32(), (int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_int16_t mipp_sve2048_load_int16(const int16_t* p0) {
	rvd_sve2048_int16_t res;
	res.r= svld1_s16(svptrue_b16(), (int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_int8_t mipp_sve2048_load_int8(const int8_t* p0) {
	rvd_sve2048_int8_t res;
	res.r= svld1_s8(svptrue_b8(), (int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_uint64_t mipp_sve2048_load_uint64(const uint64_t* p0) {
	rvd_sve2048_uint64_t res;
	res.r= svld1_u64(svptrue_b64(), (uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_uint32_t mipp_sve2048_load_uint32(const uint32_t* p0) {
	rvd_sve2048_uint32_t res;
	res.r= svld1_u32(svptrue_b32(), (uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_uint16_t mipp_sve2048_load_uint16(const uint16_t* p0) {
	rvd_sve2048_uint16_t res;
	res.r= svld1_u16(svptrue_b16(), (uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve2048_uint8_t mipp_sve2048_load_uint8(const uint8_t* p0) {
	rvd_sve2048_uint8_t res;
	res.r= svld1_u8(svptrue_b8(), (uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_float64_t mipp_sve2048_maskzld_float64(const rvm_sve2048_int32_t m0, const float64_t* p0) {
	rvd_sve2048_float64_t res;
	res.r= svld1_f64(m0.m, (float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_float32_t mipp_sve2048_maskzld_float32(const rvm_sve2048_int32_t m0, const float32_t* p0) {
	rvd_sve2048_float32_t res;
	res.r= svld1_f32(m0.m, (float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_int64_t mipp_sve2048_maskzld_int64(const rvm_sve2048_int32_t m0, const int64_t* p0) {
	rvd_sve2048_int64_t res;
	res.r= svld1_s64(m0.m, (int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_int32_t mipp_sve2048_maskzld_int32(const rvm_sve2048_int32_t m0, const int32_t* p0) {
	rvd_sve2048_int32_t res;
	res.r= svld1_s32(m0.m, (int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_int16_t mipp_sve2048_maskzld_int16(const rvm_sve2048_int32_t m0, const int16_t* p0) {
	rvd_sve2048_int16_t res;
	res.r= svld1_s16(m0.m, (int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_int8_t mipp_sve2048_maskzld_int8(const rvm_sve2048_int32_t m0, const int8_t* p0) {
	rvd_sve2048_int8_t res;
	res.r= svld1_s8(m0.m, (int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_uint64_t mipp_sve2048_maskzld_uint64(const rvm_sve2048_int32_t m0, const uint64_t* p0) {
	rvd_sve2048_uint64_t res;
	res.r= svld1_u64(m0.m, (uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_uint32_t mipp_sve2048_maskzld_uint32(const rvm_sve2048_int32_t m0, const uint32_t* p0) {
	rvd_sve2048_uint32_t res;
	res.r= svld1_u32(m0.m, (uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_uint16_t mipp_sve2048_maskzld_uint16(const rvm_sve2048_int32_t m0, const uint16_t* p0) {
	rvd_sve2048_uint16_t res;
	res.r= svld1_u16(m0.m, (uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve2048_uint8_t mipp_sve2048_maskzld_uint8(const rvm_sve2048_int32_t m0, const uint8_t* p0) {
	rvd_sve2048_uint8_t res;
	res.r= svld1_u8(m0.m, (uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_float64_t mipp_sve2048_loadu_float64(const float64_t* p0) {
	rvd_sve2048_float64_t res;
	res.r= svld1_f64(svptrue_b64(), (float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_float32_t mipp_sve2048_loadu_float32(const float32_t* p0) {
	rvd_sve2048_float32_t res;
	res.r= svld1_f32(svptrue_b32(), (float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_int64_t mipp_sve2048_loadu_int64(const int64_t* p0) {
	rvd_sve2048_int64_t res;
	res.r= svld1_s64(svptrue_b64(), (int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_int32_t mipp_sve2048_loadu_int32(const int32_t* p0) {
	rvd_sve2048_int32_t res;
	res.r= svld1_s32(svptrue_b32(), (int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_int16_t mipp_sve2048_loadu_int16(const int16_t* p0) {
	rvd_sve2048_int16_t res;
	res.r= svld1_s16(svptrue_b16(), (int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_int8_t mipp_sve2048_loadu_int8(const int8_t* p0) {
	rvd_sve2048_int8_t res;
	res.r= svld1_s8(svptrue_b8(), (int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_uint64_t mipp_sve2048_loadu_uint64(const uint64_t* p0) {
	rvd_sve2048_uint64_t res;
	res.r= svld1_u64(svptrue_b64(), (uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_uint32_t mipp_sve2048_loadu_uint32(const uint32_t* p0) {
	rvd_sve2048_uint32_t res;
	res.r= svld1_u32(svptrue_b32(), (uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_uint16_t mipp_sve2048_loadu_uint16(const uint16_t* p0) {
	rvd_sve2048_uint16_t res;
	res.r= svld1_u16(svptrue_b16(), (uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
static inline rvd_sve2048_uint8_t mipp_sve2048_loadu_uint8(const uint8_t* p0) {
	rvd_sve2048_uint8_t res;
	res.r= svld1_u8(svptrue_b8(), (uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_float64(float64_t* p0, const rvd_sve2048_float64_t r0) {
svst1_f64(svptrue_b64(), (float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_float32(float32_t* p0, const rvd_sve2048_float32_t r0) {
svst1_f32(svptrue_b32(), (float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_int64(int64_t* p0, const rvd_sve2048_int64_t r0) {
svst1_s64(svptrue_b64(), (int64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_int32(int32_t* p0, const rvd_sve2048_int32_t r0) {
svst1_s32(svptrue_b32(), (int32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_int16(int16_t* p0, const rvd_sve2048_int16_t r0) {
svst1_s16(svptrue_b16(), (int16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_int8(int8_t* p0, const rvd_sve2048_int8_t r0) {
svst1_s8(svptrue_b8(), (int8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_uint64(uint64_t* p0, const rvd_sve2048_uint64_t r0) {
svst1_u64(svptrue_b64(), (uint64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_uint32(uint32_t* p0, const rvd_sve2048_uint32_t r0) {
svst1_u32(svptrue_b32(), (uint32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_uint16(uint16_t* p0, const rvd_sve2048_uint16_t r0) {
svst1_u16(svptrue_b16(), (uint16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve2048_store_uint8(uint8_t* p0, const rvd_sve2048_uint8_t r0) {
svst1_u8(svptrue_b8(), (uint8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_float64(float64_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_float64_t r0) {
svst1_f64(m0.m, (float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_float32(float32_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_float32_t r0) {
svst1_f32(m0.m, (float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_int64(int64_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_int64_t r0) {
svst1_s64(m0.m, (int64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_int32(int32_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_int32_t r0) {
svst1_s32(m0.m, (int32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_int16(int16_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_int16_t r0) {
svst1_s16(m0.m, (int16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_int8(int8_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_int8_t r0) {
svst1_s8(m0.m, (int8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_uint64(uint64_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_uint64_t r0) {
svst1_u64(m0.m, (uint64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_uint32(uint32_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_uint32_t r0) {
svst1_u32(m0.m, (uint32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_uint16(uint16_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_uint16_t r0) {
svst1_u16(m0.m, (uint16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve2048_maskst_uint8(uint8_t* p0, const rvm_sve2048_int32_t m0, const rvd_sve2048_uint8_t r0) {
svst1_u8(m0.m, (uint8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_float64(float64_t* p0, const rvd_sve2048_float64_t r0) {
svst1_f64(svptrue_b64(), (float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_float32(float32_t* p0, const rvd_sve2048_float32_t r0) {
svst1_f32(svptrue_b32(), (float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_int64(int64_t* p0, const rvd_sve2048_int64_t r0) {
svst1_s64(svptrue_b64(), (int64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_int32(int32_t* p0, const rvd_sve2048_int32_t r0) {
svst1_s32(svptrue_b32(), (int32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_int16(int16_t* p0, const rvd_sve2048_int16_t r0) {
svst1_s16(svptrue_b16(), (int16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_int8(int8_t* p0, const rvd_sve2048_int8_t r0) {
svst1_s8(svptrue_b8(), (int8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_uint64(uint64_t* p0, const rvd_sve2048_uint64_t r0) {
svst1_u64(svptrue_b64(), (uint64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_uint32(uint32_t* p0, const rvd_sve2048_uint32_t r0) {
svst1_u32(svptrue_b32(), (uint32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_uint16(uint16_t* p0, const rvd_sve2048_uint16_t r0) {
svst1_u16(svptrue_b16(), (uint16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
static inline void mipp_sve2048_storeu_uint8(uint8_t* p0, const rvd_sve2048_uint8_t r0) {
svst1_u8(svptrue_b8(), (uint8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_float64_t mipp_sve2048_set1_float64(const float64_t v0) {
	rvd_sve2048_float64_t res;
	res.r= svdup_f64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_float32_t mipp_sve2048_set1_float32(const float32_t v0) {
	rvd_sve2048_float32_t res;
	res.r= svdup_f32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_int64_t mipp_sve2048_set1_int64(const int64_t v0) {
	rvd_sve2048_int64_t res;
	res.r= svdup_s64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_int32_t mipp_sve2048_set1_int32(const int32_t v0) {
	rvd_sve2048_int32_t res;
	res.r= svdup_s32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_int16_t mipp_sve2048_set1_int16(const int16_t v0) {
	rvd_sve2048_int16_t res;
	res.r= svdup_s16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_int8_t mipp_sve2048_set1_int8(const int8_t v0) {
	rvd_sve2048_int8_t res;
	res.r= svdup_s8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_uint64_t mipp_sve2048_set1_uint64(const uint64_t v0) {
	rvd_sve2048_uint64_t res;
	res.r= svdup_u64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_uint32_t mipp_sve2048_set1_uint32(const uint32_t v0) {
	rvd_sve2048_uint32_t res;
	res.r= svdup_u32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_uint16_t mipp_sve2048_set1_uint16(const uint16_t v0) {
	rvd_sve2048_uint16_t res;
	res.r= svdup_u16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve2048_uint8_t mipp_sve2048_set1_uint8(const uint8_t v0) {
	rvd_sve2048_uint8_t res;
	res.r= svdup_u8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_int64_t mipp_sve2048_set1_k_int64(const int32_t v0) {
	rvm_sve2048_int64_t res;
	res.m= svdup_b64((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_int32_t mipp_sve2048_set1_k_int32(const int32_t v0) {
	rvm_sve2048_int32_t res;
	res.m= svdup_b32((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_int16_t mipp_sve2048_set1_k_int16(const int32_t v0) {
	rvm_sve2048_int16_t res;
	res.m= svdup_b16((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_int8_t mipp_sve2048_set1_k_int8(const int32_t v0) {
	rvm_sve2048_int8_t res;
	res.m= svdup_b8((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_uint64_t mipp_sve2048_set1_k_uint64(const int32_t v0) {
	rvm_sve2048_uint64_t res;
	res.m= svdup_b64((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_uint32_t mipp_sve2048_set1_k_uint32(const int32_t v0) {
	rvm_sve2048_uint32_t res;
	res.m= svdup_b32((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_uint16_t mipp_sve2048_set1_k_uint16(const int32_t v0) {
	rvm_sve2048_uint16_t res;
	res.m= svdup_b16((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve2048_uint8_t mipp_sve2048_set1_k_uint8(const int32_t v0) {
	rvm_sve2048_uint8_t res;
	res.m= svdup_b8((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_float64_t mipp_sve2048_set0_float64() {
	rvd_sve2048_float64_t res;
	res.r= svdup_f64(0.0d);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_float32_t mipp_sve2048_set0_float32() {
	rvd_sve2048_float32_t res;
	res.r= svdup_f32(0.0f);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_int64_t mipp_sve2048_set0_int64() {
	rvd_sve2048_int64_t res;
	res.r= svdup_s64(0LL);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_int32_t mipp_sve2048_set0_int32() {
	rvd_sve2048_int32_t res;
	res.r= svdup_s32(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_int16_t mipp_sve2048_set0_int16() {
	rvd_sve2048_int16_t res;
	res.r= svdup_s16(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_int8_t mipp_sve2048_set0_int8() {
	rvd_sve2048_int8_t res;
	res.r= svdup_s8(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_uint64_t mipp_sve2048_set0_uint64() {
	rvd_sve2048_uint64_t res;
	res.r= svdup_u64(0UL);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_uint32_t mipp_sve2048_set0_uint32() {
	rvd_sve2048_uint32_t res;
	res.r= svdup_u32(0U);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_uint16_t mipp_sve2048_set0_uint16() {
	rvd_sve2048_uint16_t res;
	res.r= svdup_u16(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve2048_uint8_t mipp_sve2048_set0_uint8() {
	rvd_sve2048_uint8_t res;
	res.r= svdup_u8(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_float64_t mipp_sve2048_set0_k_float64() {
	rvm_sve2048_float64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_float32_t mipp_sve2048_set0_k_float32() {
	rvm_sve2048_float32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_int64_t mipp_sve2048_set0_k_int64() {
	rvm_sve2048_int64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_int32_t mipp_sve2048_set0_k_int32() {
	rvm_sve2048_int32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_int16_t mipp_sve2048_set0_k_int16() {
	rvm_sve2048_int16_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_int8_t mipp_sve2048_set0_k_int8() {
	rvm_sve2048_int8_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_uint64_t mipp_sve2048_set0_k_uint64() {
	rvm_sve2048_uint64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_uint32_t mipp_sve2048_set0_k_uint32() {
	rvm_sve2048_uint32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_uint16_t mipp_sve2048_set0_k_uint16() {
	rvm_sve2048_uint16_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve2048_uint8_t mipp_sve2048_set0_k_uint8() {
	rvm_sve2048_uint8_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_int64_t mipp_sve2048_andb_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvd_sve2048_int64_t res;
	res.r= svand_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_int32_t mipp_sve2048_andb_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvd_sve2048_int32_t res;
	res.r= svand_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_int16_t mipp_sve2048_andb_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvd_sve2048_int16_t res;
	res.r= svand_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_int8_t mipp_sve2048_andb_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvd_sve2048_int8_t res;
	res.r= svand_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_uint64_t mipp_sve2048_andb_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvd_sve2048_uint64_t res;
	res.r= svand_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_uint32_t mipp_sve2048_andb_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvd_sve2048_uint32_t res;
	res.r= svand_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_uint16_t mipp_sve2048_andb_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvd_sve2048_uint16_t res;
	res.r= svand_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_uint8_t mipp_sve2048_andb_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvd_sve2048_uint8_t res;
	res.r= svand_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_float64_t mipp_sve2048_andb_k_float64(const rvm_sve2048_float64_t m0, const rvm_sve2048_float64_t m1) {
	rvm_sve2048_float64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_float32_t mipp_sve2048_andb_k_float32(const rvm_sve2048_float32_t m0, const rvm_sve2048_float32_t m1) {
	rvm_sve2048_float32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_int64_t mipp_sve2048_andb_k_int64(const rvm_sve2048_int64_t m0, const rvm_sve2048_int64_t m1) {
	rvm_sve2048_int64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_int32_t mipp_sve2048_andb_k_int32(const rvm_sve2048_int32_t m0, const rvm_sve2048_int32_t m1) {
	rvm_sve2048_int32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_int16_t mipp_sve2048_andb_k_int16(const rvm_sve2048_int16_t m0, const rvm_sve2048_int16_t m1) {
	rvm_sve2048_int16_t res;
	res.m= svand_z(svptrue_b16(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_int8_t mipp_sve2048_andb_k_int8(const rvm_sve2048_int8_t m0, const rvm_sve2048_int8_t m1) {
	rvm_sve2048_int8_t res;
	res.m= svand_z(svptrue_b8(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_uint64_t mipp_sve2048_andb_k_uint64(const rvm_sve2048_uint64_t m0, const rvm_sve2048_uint64_t m1) {
	rvm_sve2048_uint64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_uint32_t mipp_sve2048_andb_k_uint32(const rvm_sve2048_uint32_t m0, const rvm_sve2048_uint32_t m1) {
	rvm_sve2048_uint32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_uint16_t mipp_sve2048_andb_k_uint16(const rvm_sve2048_uint16_t m0, const rvm_sve2048_uint16_t m1) {
	rvm_sve2048_uint16_t res;
	res.m= svand_z(svptrue_b16(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve2048_uint8_t mipp_sve2048_andb_k_uint8(const rvm_sve2048_uint8_t m0, const rvm_sve2048_uint8_t m1) {
	rvm_sve2048_uint8_t res;
	res.m= svand_z(svptrue_b8(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_float64_t mipp_sve2048_notb_k_float64(const rvm_sve2048_float64_t m0) {
	rvm_sve2048_float64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_float32_t mipp_sve2048_notb_k_float32(const rvm_sve2048_float32_t m0) {
	rvm_sve2048_float32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_int64_t mipp_sve2048_notb_k_int64(const rvm_sve2048_int64_t m0) {
	rvm_sve2048_int64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_int32_t mipp_sve2048_notb_k_int32(const rvm_sve2048_int32_t m0) {
	rvm_sve2048_int32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_int16_t mipp_sve2048_notb_k_int16(const rvm_sve2048_int16_t m0) {
	rvm_sve2048_int16_t res;
	res.m= svnot_z(svptrue_b16(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_int8_t mipp_sve2048_notb_k_int8(const rvm_sve2048_int8_t m0) {
	rvm_sve2048_int8_t res;
	res.m= svnot_z(svptrue_b8(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_uint64_t mipp_sve2048_notb_k_uint64(const rvm_sve2048_uint64_t m0) {
	rvm_sve2048_uint64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_uint32_t mipp_sve2048_notb_k_uint32(const rvm_sve2048_uint32_t m0) {
	rvm_sve2048_uint32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_uint16_t mipp_sve2048_notb_k_uint16(const rvm_sve2048_uint16_t m0) {
	rvm_sve2048_uint16_t res;
	res.m= svnot_z(svptrue_b16(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve2048_uint8_t mipp_sve2048_notb_k_uint8(const rvm_sve2048_uint8_t m0) {
	rvm_sve2048_uint8_t res;
	res.m= svnot_z(svptrue_b8(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_float64(const rvm_sve2048_float64_t m0, const rvm_sve2048_float64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_float32(const rvm_sve2048_float32_t m0, const rvm_sve2048_float32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_int64(const rvm_sve2048_int64_t m0, const rvm_sve2048_int64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_int32(const rvm_sve2048_int32_t m0, const rvm_sve2048_int32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_int16(const rvm_sve2048_int16_t m0, const rvm_sve2048_int16_t m1) {
	return !svptest_any(svptrue_b16(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_int8(const rvm_sve2048_int8_t m0, const rvm_sve2048_int8_t m1) {
	return !svptest_any(svptrue_b8(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_uint64(const rvm_sve2048_uint64_t m0, const rvm_sve2048_uint64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_uint32(const rvm_sve2048_uint32_t m0, const rvm_sve2048_uint32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_uint16(const rvm_sve2048_uint16_t m0, const rvm_sve2048_uint16_t m1) {
	return !svptest_any(svptrue_b16(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve2048_testz_uint8(const rvm_sve2048_uint8_t m0, const rvm_sve2048_uint8_t m1) {
	return !svptest_any(svptrue_b8(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_float64_t mipp_sve2048_add_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_float64_t res;
	res.r= svadd_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_float32_t mipp_sve2048_add_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_float32_t res;
	res.r= svadd_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_int64_t mipp_sve2048_add_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvd_sve2048_int64_t res;
	res.r= svadd_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_int32_t mipp_sve2048_add_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvd_sve2048_int32_t res;
	res.r= svadd_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_int16_t mipp_sve2048_add_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvd_sve2048_int16_t res;
	res.r= svadd_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_int8_t mipp_sve2048_add_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvd_sve2048_int8_t res;
	res.r= svadd_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_uint64_t mipp_sve2048_add_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvd_sve2048_uint64_t res;
	res.r= svadd_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_uint32_t mipp_sve2048_add_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvd_sve2048_uint32_t res;
	res.r= svadd_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_uint16_t mipp_sve2048_add_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvd_sve2048_uint16_t res;
	res.r= svadd_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve2048_uint8_t mipp_sve2048_add_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvd_sve2048_uint8_t res;
	res.r= svadd_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_float64_t mipp_sve2048_maskz_add_float64(const rvm_sve2048_float64_t m0, const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_float64_t res;
	res.r= svadd_f64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_float32_t mipp_sve2048_maskz_add_float32(const rvm_sve2048_float32_t m0, const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_float32_t res;
	res.r= svadd_f32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_int64_t mipp_sve2048_maskz_add_int64(const rvm_sve2048_int64_t m0, const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvd_sve2048_int64_t res;
	res.r= svadd_s64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_int32_t mipp_sve2048_maskz_add_int32(const rvm_sve2048_int32_t m0, const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvd_sve2048_int32_t res;
	res.r= svadd_s32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_int16_t mipp_sve2048_maskz_add_int16(const rvm_sve2048_int16_t m0, const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvd_sve2048_int16_t res;
	res.r= svadd_s16_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_int8_t mipp_sve2048_maskz_add_int8(const rvm_sve2048_int8_t m0, const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvd_sve2048_int8_t res;
	res.r= svadd_s8_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_uint64_t mipp_sve2048_maskz_add_uint64(const rvm_sve2048_uint64_t m0, const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvd_sve2048_uint64_t res;
	res.r= svadd_u64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_uint32_t mipp_sve2048_maskz_add_uint32(const rvm_sve2048_uint32_t m0, const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvd_sve2048_uint32_t res;
	res.r= svadd_u32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_uint16_t mipp_sve2048_maskz_add_uint16(const rvm_sve2048_uint16_t m0, const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvd_sve2048_uint16_t res;
	res.r= svadd_u16_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve2048_uint8_t mipp_sve2048_maskz_add_uint8(const rvm_sve2048_uint8_t m0, const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvd_sve2048_uint8_t res;
	res.r= svadd_u8_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_float64_t mipp_sve2048_sub_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_float64_t res;
	res.r= svsub_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_float32_t mipp_sve2048_sub_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_float32_t res;
	res.r= svsub_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_int64_t mipp_sve2048_sub_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvd_sve2048_int64_t res;
	res.r= svsub_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_int32_t mipp_sve2048_sub_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvd_sve2048_int32_t res;
	res.r= svsub_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_int16_t mipp_sve2048_sub_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvd_sve2048_int16_t res;
	res.r= svsub_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_int8_t mipp_sve2048_sub_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvd_sve2048_int8_t res;
	res.r= svsub_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_uint64_t mipp_sve2048_sub_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvd_sve2048_uint64_t res;
	res.r= svsub_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_uint32_t mipp_sve2048_sub_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvd_sve2048_uint32_t res;
	res.r= svsub_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_uint16_t mipp_sve2048_sub_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvd_sve2048_uint16_t res;
	res.r= svsub_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve2048_uint8_t mipp_sve2048_sub_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvd_sve2048_uint8_t res;
	res.r= svsub_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_float64_t mipp_sve2048_mul_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_float64_t res;
	res.r= svmul_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_float32_t mipp_sve2048_mul_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_float32_t res;
	res.r= svmul_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_int64_t mipp_sve2048_mul_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvd_sve2048_int64_t res;
	res.r= svmul_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_int32_t mipp_sve2048_mul_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvd_sve2048_int32_t res;
	res.r= svmul_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_int16_t mipp_sve2048_mul_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvd_sve2048_int16_t res;
	res.r= svmul_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_int8_t mipp_sve2048_mul_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvd_sve2048_int8_t res;
	res.r= svmul_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_uint64_t mipp_sve2048_mul_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvd_sve2048_uint64_t res;
	res.r= svmul_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_uint32_t mipp_sve2048_mul_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvd_sve2048_uint32_t res;
	res.r= svmul_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_uint16_t mipp_sve2048_mul_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvd_sve2048_uint16_t res;
	res.r= svmul_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve2048_uint8_t mipp_sve2048_mul_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvd_sve2048_uint8_t res;
	res.r= svmul_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
static inline rvd_sve2048_float64_t mipp_sve2048_div_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_float64_t res;
	res.r= svdiv_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
static inline rvd_sve2048_float32_t mipp_sve2048_div_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_float32_t res;
	res.r= svdiv_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
static inline rvd_sve2048_float64_t mipp_sve2048_fmadd_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1, const rvd_sve2048_float64_t r2) {
	rvd_sve2048_float64_t res;
	res.r= svmla_f64_z(svptrue_b64(), r0.r, r1.r, r2.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
static inline rvd_sve2048_float32_t mipp_sve2048_fmadd_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1, const rvd_sve2048_float32_t r2) {
	rvd_sve2048_float32_t res;
	res.r= svmla_f32_z(svptrue_b32(), r0.r, r1.r, r2.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_float64_t mipp_sve2048_cmpeq_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvm_sve2048_float64_t res;
	res.m= svcmpeq_f64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_float32_t mipp_sve2048_cmpeq_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvm_sve2048_float32_t res;
	res.m= svcmpeq_f32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_int64_t mipp_sve2048_cmpeq_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvm_sve2048_int64_t res;
	res.m= svcmpeq_s64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_int32_t mipp_sve2048_cmpeq_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvm_sve2048_int32_t res;
	res.m= svcmpeq_s32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_int16_t mipp_sve2048_cmpeq_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvm_sve2048_int16_t res;
	res.m= svcmpeq_s16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_int8_t mipp_sve2048_cmpeq_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvm_sve2048_int8_t res;
	res.m= svcmpeq_s8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_uint64_t mipp_sve2048_cmpeq_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvm_sve2048_uint64_t res;
	res.m= svcmpeq_u64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_uint32_t mipp_sve2048_cmpeq_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvm_sve2048_uint32_t res;
	res.m= svcmpeq_u32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_uint16_t mipp_sve2048_cmpeq_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvm_sve2048_uint16_t res;
	res.m= svcmpeq_u16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve2048_uint8_t mipp_sve2048_cmpeq_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvm_sve2048_uint8_t res;
	res.m= svcmpeq_u8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_float64_t mipp_sve2048_cmpneq_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvm_sve2048_float64_t res;
	res.m= svcmpne_f64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_float32_t mipp_sve2048_cmpneq_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvm_sve2048_float32_t res;
	res.m= svcmpne_f32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_int64_t mipp_sve2048_cmpneq_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	rvm_sve2048_int64_t res;
	res.m= svcmpne_s64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_int32_t mipp_sve2048_cmpneq_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	rvm_sve2048_int32_t res;
	res.m= svcmpne_s32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_int16_t mipp_sve2048_cmpneq_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	rvm_sve2048_int16_t res;
	res.m= svcmpne_s16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_int8_t mipp_sve2048_cmpneq_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	rvm_sve2048_int8_t res;
	res.m= svcmpne_s8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_uint64_t mipp_sve2048_cmpneq_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	rvm_sve2048_uint64_t res;
	res.m= svcmpne_u64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_uint32_t mipp_sve2048_cmpneq_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	rvm_sve2048_uint32_t res;
	res.m= svcmpne_u32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_uint16_t mipp_sve2048_cmpneq_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	rvm_sve2048_uint16_t res;
	res.m= svcmpne_u16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve2048_uint8_t mipp_sve2048_cmpneq_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	rvm_sve2048_uint8_t res;
	res.m= svcmpne_u8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline float64_t mipp_sve2048_hadd_to_scal_float64(const rvd_sve2048_float64_t r0) {
	return svaddv_f64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline float32_t mipp_sve2048_hadd_to_scal_float32(const rvd_sve2048_float32_t r0) {
	return svaddv_f32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int64_t mipp_sve2048_hadd_to_scal_int64(const rvd_sve2048_int64_t r0) {
	return svaddv_s64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int32_t mipp_sve2048_hadd_to_scal_int32(const rvd_sve2048_int32_t r0) {
	return svaddv_s32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int16_t mipp_sve2048_hadd_to_scal_int16(const rvd_sve2048_int16_t r0) {
	return svaddv_s16(svptrue_b16(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int8_t mipp_sve2048_hadd_to_scal_int8(const rvd_sve2048_int8_t r0) {
	return svaddv_s8(svptrue_b8(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint64_t mipp_sve2048_hadd_to_scal_uint64(const rvd_sve2048_uint64_t r0) {
	return svaddv_u64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint32_t mipp_sve2048_hadd_to_scal_uint32(const rvd_sve2048_uint32_t r0) {
	return svaddv_u32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint16_t mipp_sve2048_hadd_to_scal_uint16(const rvd_sve2048_uint16_t r0) {
	return svaddv_u16(svptrue_b16(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint8_t mipp_sve2048_hadd_to_scal_uint8(const rvd_sve2048_uint8_t r0) {
	return svaddv_u8(svptrue_b8(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_uint64_t mipp_sve2048_toreg_uint64(const rvm_sve2048_uint64_t m0) {
	rvd_sve2048_uint64_t one  = mipp_sve2048_set1_uint64(0xFFFFFFFFFFFFFFFF);
    rvd_sve2048_uint64_t zero = mipp_sve2048_set1_uint64(0);
    return mipp_sve2048_blend_uint64(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_int64_t mipp_sve2048_toreg_int64(const rvm_sve2048_int64_t m0) {
	rvd_sve2048_int64_t one  = mipp_sve2048_set1_int64(0xFFFFFFFFFFFFFFFF);
    rvd_sve2048_int64_t zero = mipp_sve2048_set1_int64(0);
    return mipp_sve2048_blend_int64(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_float64_t mipp_sve2048_toreg_float64(const rvm_sve2048_float64_t m0) {
	rvd_sve2048_float64_t one  = mipp_sve2048_set1_float64(0xFFFFFFFFFFFFFFFF);
    rvd_sve2048_float64_t zero = mipp_sve2048_set1_float64(0);
    return mipp_sve2048_blend_float64(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_uint32_t mipp_sve2048_toreg_uint32(const rvm_sve2048_uint32_t m0) {
	rvd_sve2048_uint32_t one  = mipp_sve2048_set1_uint32(0xFFFFFFFF);
    rvd_sve2048_uint32_t zero = mipp_sve2048_set1_uint32(0);
    return mipp_sve2048_blend_uint32(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_int32_t mipp_sve2048_toreg_int32(const rvm_sve2048_int32_t m0) {
	rvd_sve2048_int32_t one  = mipp_sve2048_set1_int32(0xFFFFFFFF);
    rvd_sve2048_int32_t zero = mipp_sve2048_set1_int32(0);
    return mipp_sve2048_blend_int32(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve2048_float32_t mipp_sve2048_toreg_float32(const rvm_sve2048_float32_t m0) {
	rvd_sve2048_float32_t one  = mipp_sve2048_set1_float32(0xFFFFFFFF);
    rvd_sve2048_float32_t zero = mipp_sve2048_set1_float32(0);
    return mipp_sve2048_blend_float32(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_float64_t mipp_sve2048_andb_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	rvd_sve2048_int64_t a = mipp_sve2048_cast_float64_int64(r0);
    rvd_sve2048_int64_t b = mipp_sve2048_cast_float64_int64(r1);
    rvd_sve2048_int64_t res = mipp_sve2048_andb_int64(a,b);
    return mipp_sve2048_cast_int64_float64(res);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve2048_float32_t mipp_sve2048_andb_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	rvd_sve2048_int32_t a = mipp_sve2048_cast_float32_int32(r0);
    rvd_sve2048_int32_t b = mipp_sve2048_cast_float32_int32(r1);
    rvd_sve2048_int32_t res = mipp_sve2048_andb_int32(a,b);
    return mipp_sve2048_cast_int32_float32(res);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_float64_t mipp_sve2048_set_float64(const float64_t vals[MIPP_SVE2048_N_FLOAT64]) {
	return mipp_sve2048_load_float64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_float32_t mipp_sve2048_set_float32(const float32_t vals[MIPP_SVE2048_N_FLOAT32]) {
	return mipp_sve2048_load_float32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_int64_t mipp_sve2048_set_int64(const int64_t vals[MIPP_SVE2048_N_INT64]) {
	return mipp_sve2048_load_int64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_int32_t mipp_sve2048_set_int32(const int32_t vals[MIPP_SVE2048_N_INT32]) {
	return mipp_sve2048_load_int32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_int16_t mipp_sve2048_set_int16(const int16_t vals[MIPP_SVE2048_N_INT16]) {
	return mipp_sve2048_load_int16(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_int8_t mipp_sve2048_set_int8(const int8_t vals[MIPP_SVE2048_N_INT8]) {
	return mipp_sve2048_load_int8(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_uint64_t mipp_sve2048_set_uint64(const uint64_t vals[MIPP_SVE2048_N_UINT64]) {
	return mipp_sve2048_load_uint64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_uint32_t mipp_sve2048_set_uint32(const uint32_t vals[MIPP_SVE2048_N_UINT32]) {
	return mipp_sve2048_load_uint32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_uint16_t mipp_sve2048_set_uint16(const uint16_t vals[MIPP_SVE2048_N_UINT16]) {
	return mipp_sve2048_load_uint16(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve2048_uint8_t mipp_sve2048_set_uint8(const uint8_t vals[MIPP_SVE2048_N_UINT8]) {
	return mipp_sve2048_load_uint8(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_uint64_t mipp_sve2048_set_k_uint64(const int32_t vals[MIPP_SVE2048_N_UINT64]) {
	uint64_t t[MIPP_SVE2048_N_UINT64] = {  
        t[0] = vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[1] = vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[2] = vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[3] = vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[4] = vals[4] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[5] = vals[5] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[6] = vals[6] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[7] = vals[7] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[8] = vals[8] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[9] = vals[9] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[10] = vals[10] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[11] = vals[11] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[12] = vals[12] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[13] = vals[13] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[14] = vals[14] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[15] = vals[15] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[16] = vals[16] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[17] = vals[17] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[18] = vals[18] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[19] = vals[19] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[20] = vals[20] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[21] = vals[21] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[22] = vals[22] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[23] = vals[23] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[24] = vals[24] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[25] = vals[25] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[26] = vals[26] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[27] = vals[27] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[28] = vals[28] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[29] = vals[29] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[30] = vals[30] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[31] = vals[31] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0 };
    rvd_sve2048_uint64_t r0_32 = mipp_sve2048_set_uint64((uint64_t*) t);
    rvd_sve2048_uint64_t r1_32 = mipp_sve2048_set1_uint64((uint64_t) 0xFFFFFFFFFFFFFFFF);
    return mipp_sve2048_cast_k_uint64_uint64(mipp_sve2048_cmpeq_uint64(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_int64_t mipp_sve2048_set_k_int64(const int32_t vals[MIPP_SVE2048_N_INT64]) {
	uint64_t t[MIPP_SVE2048_N_INT64] = {  
        t[0] = vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[1] = vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[2] = vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[3] = vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[4] = vals[4] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[5] = vals[5] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[6] = vals[6] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[7] = vals[7] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[8] = vals[8] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[9] = vals[9] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[10] = vals[10] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[11] = vals[11] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[12] = vals[12] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[13] = vals[13] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[14] = vals[14] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[15] = vals[15] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[16] = vals[16] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[17] = vals[17] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[18] = vals[18] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[19] = vals[19] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[20] = vals[20] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[21] = vals[21] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[22] = vals[22] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[23] = vals[23] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[24] = vals[24] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[25] = vals[25] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[26] = vals[26] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[27] = vals[27] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[28] = vals[28] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[29] = vals[29] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[30] = vals[30] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[31] = vals[31] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0 };
    rvd_sve2048_uint64_t r0_32 = mipp_sve2048_set_uint64((uint64_t*) t);
    rvd_sve2048_uint64_t r1_32 = mipp_sve2048_set1_uint64((uint64_t) 0xFFFFFFFFFFFFFFFF);
    return mipp_sve2048_cast_k_uint64_int64(mipp_sve2048_cmpeq_uint64(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_float64_t mipp_sve2048_set_k_float64(const int32_t vals[MIPP_SVE2048_N_FLOAT64]) {
	uint64_t t[MIPP_SVE2048_N_FLOAT64] = {  
        t[0] = vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[1] = vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[2] = vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[3] = vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[4] = vals[4] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[5] = vals[5] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[6] = vals[6] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[7] = vals[7] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[8] = vals[8] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[9] = vals[9] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[10] = vals[10] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[11] = vals[11] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[12] = vals[12] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[13] = vals[13] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[14] = vals[14] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[15] = vals[15] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[16] = vals[16] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[17] = vals[17] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[18] = vals[18] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[19] = vals[19] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[20] = vals[20] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[21] = vals[21] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[22] = vals[22] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[23] = vals[23] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[24] = vals[24] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[25] = vals[25] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[26] = vals[26] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[27] = vals[27] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[28] = vals[28] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[29] = vals[29] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[30] = vals[30] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, 
        t[31] = vals[31] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0 };
    rvd_sve2048_uint64_t r0_32 = mipp_sve2048_set_uint64((uint64_t*) t);
    rvd_sve2048_uint64_t r1_32 = mipp_sve2048_set1_uint64((uint64_t) 0xFFFFFFFFFFFFFFFF);
    return mipp_sve2048_cast_k_uint64_float64(mipp_sve2048_cmpeq_uint64(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_uint32_t mipp_sve2048_set_k_uint32(const int32_t vals[MIPP_SVE2048_N_UINT32]) {
	uint32_t t[MIPP_SVE2048_N_UINT32] = {  
        t[0] = vals[0] ? 0xFFFFFFFF : 0, 
        t[1] = vals[1] ? 0xFFFFFFFF : 0, 
        t[2] = vals[2] ? 0xFFFFFFFF : 0, 
        t[3] = vals[3] ? 0xFFFFFFFF : 0, 
        t[4] = vals[4] ? 0xFFFFFFFF : 0, 
        t[5] = vals[5] ? 0xFFFFFFFF : 0, 
        t[6] = vals[6] ? 0xFFFFFFFF : 0, 
        t[7] = vals[7] ? 0xFFFFFFFF : 0, 
        t[8] = vals[8] ? 0xFFFFFFFF : 0, 
        t[9] = vals[9] ? 0xFFFFFFFF : 0, 
        t[10] = vals[10] ? 0xFFFFFFFF : 0, 
        t[11] = vals[11] ? 0xFFFFFFFF : 0, 
        t[12] = vals[12] ? 0xFFFFFFFF : 0, 
        t[13] = vals[13] ? 0xFFFFFFFF : 0, 
        t[14] = vals[14] ? 0xFFFFFFFF : 0, 
        t[15] = vals[15] ? 0xFFFFFFFF : 0, 
        t[16] = vals[16] ? 0xFFFFFFFF : 0, 
        t[17] = vals[17] ? 0xFFFFFFFF : 0, 
        t[18] = vals[18] ? 0xFFFFFFFF : 0, 
        t[19] = vals[19] ? 0xFFFFFFFF : 0, 
        t[20] = vals[20] ? 0xFFFFFFFF : 0, 
        t[21] = vals[21] ? 0xFFFFFFFF : 0, 
        t[22] = vals[22] ? 0xFFFFFFFF : 0, 
        t[23] = vals[23] ? 0xFFFFFFFF : 0, 
        t[24] = vals[24] ? 0xFFFFFFFF : 0, 
        t[25] = vals[25] ? 0xFFFFFFFF : 0, 
        t[26] = vals[26] ? 0xFFFFFFFF : 0, 
        t[27] = vals[27] ? 0xFFFFFFFF : 0, 
        t[28] = vals[28] ? 0xFFFFFFFF : 0, 
        t[29] = vals[29] ? 0xFFFFFFFF : 0, 
        t[30] = vals[30] ? 0xFFFFFFFF : 0, 
        t[31] = vals[31] ? 0xFFFFFFFF : 0, 
        t[32] = vals[32] ? 0xFFFFFFFF : 0, 
        t[33] = vals[33] ? 0xFFFFFFFF : 0, 
        t[34] = vals[34] ? 0xFFFFFFFF : 0, 
        t[35] = vals[35] ? 0xFFFFFFFF : 0, 
        t[36] = vals[36] ? 0xFFFFFFFF : 0, 
        t[37] = vals[37] ? 0xFFFFFFFF : 0, 
        t[38] = vals[38] ? 0xFFFFFFFF : 0, 
        t[39] = vals[39] ? 0xFFFFFFFF : 0, 
        t[40] = vals[40] ? 0xFFFFFFFF : 0, 
        t[41] = vals[41] ? 0xFFFFFFFF : 0, 
        t[42] = vals[42] ? 0xFFFFFFFF : 0, 
        t[43] = vals[43] ? 0xFFFFFFFF : 0, 
        t[44] = vals[44] ? 0xFFFFFFFF : 0, 
        t[45] = vals[45] ? 0xFFFFFFFF : 0, 
        t[46] = vals[46] ? 0xFFFFFFFF : 0, 
        t[47] = vals[47] ? 0xFFFFFFFF : 0, 
        t[48] = vals[48] ? 0xFFFFFFFF : 0, 
        t[49] = vals[49] ? 0xFFFFFFFF : 0, 
        t[50] = vals[50] ? 0xFFFFFFFF : 0, 
        t[51] = vals[51] ? 0xFFFFFFFF : 0, 
        t[52] = vals[52] ? 0xFFFFFFFF : 0, 
        t[53] = vals[53] ? 0xFFFFFFFF : 0, 
        t[54] = vals[54] ? 0xFFFFFFFF : 0, 
        t[55] = vals[55] ? 0xFFFFFFFF : 0, 
        t[56] = vals[56] ? 0xFFFFFFFF : 0, 
        t[57] = vals[57] ? 0xFFFFFFFF : 0, 
        t[58] = vals[58] ? 0xFFFFFFFF : 0, 
        t[59] = vals[59] ? 0xFFFFFFFF : 0, 
        t[60] = vals[60] ? 0xFFFFFFFF : 0, 
        t[61] = vals[61] ? 0xFFFFFFFF : 0, 
        t[62] = vals[62] ? 0xFFFFFFFF : 0, 
        t[63] = vals[63] ? 0xFFFFFFFF : 0 };
    rvd_sve2048_uint32_t r0_32 = mipp_sve2048_set_uint32((uint32_t*) t);
    rvd_sve2048_uint32_t r1_32 = mipp_sve2048_set1_uint32(0xFFFFFFFF);
    return mipp_sve2048_cast_k_uint32_uint32(mipp_sve2048_cmpeq_uint32(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_int32_t mipp_sve2048_set_k_int32(const int32_t vals[MIPP_SVE2048_N_INT32]) {
	uint32_t t[MIPP_SVE2048_N_INT32] = {  
        t[0] = vals[0] ? 0xFFFFFFFF : 0, 
        t[1] = vals[1] ? 0xFFFFFFFF : 0, 
        t[2] = vals[2] ? 0xFFFFFFFF : 0, 
        t[3] = vals[3] ? 0xFFFFFFFF : 0, 
        t[4] = vals[4] ? 0xFFFFFFFF : 0, 
        t[5] = vals[5] ? 0xFFFFFFFF : 0, 
        t[6] = vals[6] ? 0xFFFFFFFF : 0, 
        t[7] = vals[7] ? 0xFFFFFFFF : 0, 
        t[8] = vals[8] ? 0xFFFFFFFF : 0, 
        t[9] = vals[9] ? 0xFFFFFFFF : 0, 
        t[10] = vals[10] ? 0xFFFFFFFF : 0, 
        t[11] = vals[11] ? 0xFFFFFFFF : 0, 
        t[12] = vals[12] ? 0xFFFFFFFF : 0, 
        t[13] = vals[13] ? 0xFFFFFFFF : 0, 
        t[14] = vals[14] ? 0xFFFFFFFF : 0, 
        t[15] = vals[15] ? 0xFFFFFFFF : 0, 
        t[16] = vals[16] ? 0xFFFFFFFF : 0, 
        t[17] = vals[17] ? 0xFFFFFFFF : 0, 
        t[18] = vals[18] ? 0xFFFFFFFF : 0, 
        t[19] = vals[19] ? 0xFFFFFFFF : 0, 
        t[20] = vals[20] ? 0xFFFFFFFF : 0, 
        t[21] = vals[21] ? 0xFFFFFFFF : 0, 
        t[22] = vals[22] ? 0xFFFFFFFF : 0, 
        t[23] = vals[23] ? 0xFFFFFFFF : 0, 
        t[24] = vals[24] ? 0xFFFFFFFF : 0, 
        t[25] = vals[25] ? 0xFFFFFFFF : 0, 
        t[26] = vals[26] ? 0xFFFFFFFF : 0, 
        t[27] = vals[27] ? 0xFFFFFFFF : 0, 
        t[28] = vals[28] ? 0xFFFFFFFF : 0, 
        t[29] = vals[29] ? 0xFFFFFFFF : 0, 
        t[30] = vals[30] ? 0xFFFFFFFF : 0, 
        t[31] = vals[31] ? 0xFFFFFFFF : 0, 
        t[32] = vals[32] ? 0xFFFFFFFF : 0, 
        t[33] = vals[33] ? 0xFFFFFFFF : 0, 
        t[34] = vals[34] ? 0xFFFFFFFF : 0, 
        t[35] = vals[35] ? 0xFFFFFFFF : 0, 
        t[36] = vals[36] ? 0xFFFFFFFF : 0, 
        t[37] = vals[37] ? 0xFFFFFFFF : 0, 
        t[38] = vals[38] ? 0xFFFFFFFF : 0, 
        t[39] = vals[39] ? 0xFFFFFFFF : 0, 
        t[40] = vals[40] ? 0xFFFFFFFF : 0, 
        t[41] = vals[41] ? 0xFFFFFFFF : 0, 
        t[42] = vals[42] ? 0xFFFFFFFF : 0, 
        t[43] = vals[43] ? 0xFFFFFFFF : 0, 
        t[44] = vals[44] ? 0xFFFFFFFF : 0, 
        t[45] = vals[45] ? 0xFFFFFFFF : 0, 
        t[46] = vals[46] ? 0xFFFFFFFF : 0, 
        t[47] = vals[47] ? 0xFFFFFFFF : 0, 
        t[48] = vals[48] ? 0xFFFFFFFF : 0, 
        t[49] = vals[49] ? 0xFFFFFFFF : 0, 
        t[50] = vals[50] ? 0xFFFFFFFF : 0, 
        t[51] = vals[51] ? 0xFFFFFFFF : 0, 
        t[52] = vals[52] ? 0xFFFFFFFF : 0, 
        t[53] = vals[53] ? 0xFFFFFFFF : 0, 
        t[54] = vals[54] ? 0xFFFFFFFF : 0, 
        t[55] = vals[55] ? 0xFFFFFFFF : 0, 
        t[56] = vals[56] ? 0xFFFFFFFF : 0, 
        t[57] = vals[57] ? 0xFFFFFFFF : 0, 
        t[58] = vals[58] ? 0xFFFFFFFF : 0, 
        t[59] = vals[59] ? 0xFFFFFFFF : 0, 
        t[60] = vals[60] ? 0xFFFFFFFF : 0, 
        t[61] = vals[61] ? 0xFFFFFFFF : 0, 
        t[62] = vals[62] ? 0xFFFFFFFF : 0, 
        t[63] = vals[63] ? 0xFFFFFFFF : 0 };
    rvd_sve2048_uint32_t r0_32 = mipp_sve2048_set_uint32((uint32_t*) t);
    rvd_sve2048_uint32_t r1_32 = mipp_sve2048_set1_uint32(0xFFFFFFFF);
    return mipp_sve2048_cast_k_uint32_int32(mipp_sve2048_cmpeq_uint32(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve2048_float32_t mipp_sve2048_set_k_float32(const int32_t vals[MIPP_SVE2048_N_FLOAT32]) {
	uint32_t t[MIPP_SVE2048_N_FLOAT32] = {  
        t[0] = vals[0] ? 0xFFFFFFFF : 0, 
        t[1] = vals[1] ? 0xFFFFFFFF : 0, 
        t[2] = vals[2] ? 0xFFFFFFFF : 0, 
        t[3] = vals[3] ? 0xFFFFFFFF : 0, 
        t[4] = vals[4] ? 0xFFFFFFFF : 0, 
        t[5] = vals[5] ? 0xFFFFFFFF : 0, 
        t[6] = vals[6] ? 0xFFFFFFFF : 0, 
        t[7] = vals[7] ? 0xFFFFFFFF : 0, 
        t[8] = vals[8] ? 0xFFFFFFFF : 0, 
        t[9] = vals[9] ? 0xFFFFFFFF : 0, 
        t[10] = vals[10] ? 0xFFFFFFFF : 0, 
        t[11] = vals[11] ? 0xFFFFFFFF : 0, 
        t[12] = vals[12] ? 0xFFFFFFFF : 0, 
        t[13] = vals[13] ? 0xFFFFFFFF : 0, 
        t[14] = vals[14] ? 0xFFFFFFFF : 0, 
        t[15] = vals[15] ? 0xFFFFFFFF : 0, 
        t[16] = vals[16] ? 0xFFFFFFFF : 0, 
        t[17] = vals[17] ? 0xFFFFFFFF : 0, 
        t[18] = vals[18] ? 0xFFFFFFFF : 0, 
        t[19] = vals[19] ? 0xFFFFFFFF : 0, 
        t[20] = vals[20] ? 0xFFFFFFFF : 0, 
        t[21] = vals[21] ? 0xFFFFFFFF : 0, 
        t[22] = vals[22] ? 0xFFFFFFFF : 0, 
        t[23] = vals[23] ? 0xFFFFFFFF : 0, 
        t[24] = vals[24] ? 0xFFFFFFFF : 0, 
        t[25] = vals[25] ? 0xFFFFFFFF : 0, 
        t[26] = vals[26] ? 0xFFFFFFFF : 0, 
        t[27] = vals[27] ? 0xFFFFFFFF : 0, 
        t[28] = vals[28] ? 0xFFFFFFFF : 0, 
        t[29] = vals[29] ? 0xFFFFFFFF : 0, 
        t[30] = vals[30] ? 0xFFFFFFFF : 0, 
        t[31] = vals[31] ? 0xFFFFFFFF : 0, 
        t[32] = vals[32] ? 0xFFFFFFFF : 0, 
        t[33] = vals[33] ? 0xFFFFFFFF : 0, 
        t[34] = vals[34] ? 0xFFFFFFFF : 0, 
        t[35] = vals[35] ? 0xFFFFFFFF : 0, 
        t[36] = vals[36] ? 0xFFFFFFFF : 0, 
        t[37] = vals[37] ? 0xFFFFFFFF : 0, 
        t[38] = vals[38] ? 0xFFFFFFFF : 0, 
        t[39] = vals[39] ? 0xFFFFFFFF : 0, 
        t[40] = vals[40] ? 0xFFFFFFFF : 0, 
        t[41] = vals[41] ? 0xFFFFFFFF : 0, 
        t[42] = vals[42] ? 0xFFFFFFFF : 0, 
        t[43] = vals[43] ? 0xFFFFFFFF : 0, 
        t[44] = vals[44] ? 0xFFFFFFFF : 0, 
        t[45] = vals[45] ? 0xFFFFFFFF : 0, 
        t[46] = vals[46] ? 0xFFFFFFFF : 0, 
        t[47] = vals[47] ? 0xFFFFFFFF : 0, 
        t[48] = vals[48] ? 0xFFFFFFFF : 0, 
        t[49] = vals[49] ? 0xFFFFFFFF : 0, 
        t[50] = vals[50] ? 0xFFFFFFFF : 0, 
        t[51] = vals[51] ? 0xFFFFFFFF : 0, 
        t[52] = vals[52] ? 0xFFFFFFFF : 0, 
        t[53] = vals[53] ? 0xFFFFFFFF : 0, 
        t[54] = vals[54] ? 0xFFFFFFFF : 0, 
        t[55] = vals[55] ? 0xFFFFFFFF : 0, 
        t[56] = vals[56] ? 0xFFFFFFFF : 0, 
        t[57] = vals[57] ? 0xFFFFFFFF : 0, 
        t[58] = vals[58] ? 0xFFFFFFFF : 0, 
        t[59] = vals[59] ? 0xFFFFFFFF : 0, 
        t[60] = vals[60] ? 0xFFFFFFFF : 0, 
        t[61] = vals[61] ? 0xFFFFFFFF : 0, 
        t[62] = vals[62] ? 0xFFFFFFFF : 0, 
        t[63] = vals[63] ? 0xFFFFFFFF : 0 };
    rvd_sve2048_uint32_t r0_32 = mipp_sve2048_set_uint32((uint32_t*) t);
    rvd_sve2048_uint32_t r1_32 = mipp_sve2048_set1_uint32(0xFFFFFFFF);
    return mipp_sve2048_cast_k_uint32_float32(mipp_sve2048_cmpeq_uint32(r0_32, r1_32));
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_float64_t mipp_sve2048_hadd_float64(const rvd_sve2048_float64_t r0) {
	const float64_t val = mipp_sve2048_hadd_to_scal_float64(r0);
    return mipp_sve2048_set1_float64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_float32_t mipp_sve2048_hadd_float32(const rvd_sve2048_float32_t r0) {
	const float32_t val = mipp_sve2048_hadd_to_scal_float32(r0);
    return mipp_sve2048_set1_float32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_int64_t mipp_sve2048_hadd_int64(const rvd_sve2048_int64_t r0) {
	const int64_t val = mipp_sve2048_hadd_to_scal_int64(r0);
    return mipp_sve2048_set1_int64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_int32_t mipp_sve2048_hadd_int32(const rvd_sve2048_int32_t r0) {
	const int32_t val = mipp_sve2048_hadd_to_scal_int32(r0);
    return mipp_sve2048_set1_int32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_int16_t mipp_sve2048_hadd_int16(const rvd_sve2048_int16_t r0) {
	const int16_t val = mipp_sve2048_hadd_to_scal_int16(r0);
    return mipp_sve2048_set1_int16(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_int8_t mipp_sve2048_hadd_int8(const rvd_sve2048_int8_t r0) {
	const int8_t val = mipp_sve2048_hadd_to_scal_int8(r0);
    return mipp_sve2048_set1_int8(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_uint64_t mipp_sve2048_hadd_uint64(const rvd_sve2048_uint64_t r0) {
	const uint64_t val = mipp_sve2048_hadd_to_scal_uint64(r0);
    return mipp_sve2048_set1_uint64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_uint32_t mipp_sve2048_hadd_uint32(const rvd_sve2048_uint32_t r0) {
	const uint32_t val = mipp_sve2048_hadd_to_scal_uint32(r0);
    return mipp_sve2048_set1_uint32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_uint16_t mipp_sve2048_hadd_uint16(const rvd_sve2048_uint16_t r0) {
	const uint16_t val = mipp_sve2048_hadd_to_scal_uint16(r0);
    return mipp_sve2048_set1_uint16(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve2048_uint8_t mipp_sve2048_hadd_uint8(const rvd_sve2048_uint8_t r0) {
	const uint8_t val = mipp_sve2048_hadd_to_scal_uint8(r0);
    return mipp_sve2048_set1_uint8(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline float64_t mipp_sve2048_get_float64(const rvd_sve2048_float64_t r0, const uint32_t v0) {
	float64_t t[MIPP_SVE2048_N_FLOAT64];
    mipp_sve2048_storeu_float64(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline float32_t mipp_sve2048_get_float32(const rvd_sve2048_float32_t r0, const uint32_t v0) {
	float32_t t[MIPP_SVE2048_N_FLOAT32];
    mipp_sve2048_storeu_float32(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline int64_t mipp_sve2048_get_int64(const rvd_sve2048_int64_t r0, const uint32_t v0) {
	int64_t t[MIPP_SVE2048_N_INT64];
    mipp_sve2048_storeu_int64(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline int32_t mipp_sve2048_get_int32(const rvd_sve2048_int32_t r0, const uint32_t v0) {
	int32_t t[MIPP_SVE2048_N_INT32];
    mipp_sve2048_storeu_int32(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline int16_t mipp_sve2048_get_int16(const rvd_sve2048_int16_t r0, const uint32_t v0) {
	int16_t t[MIPP_SVE2048_N_INT16];
    mipp_sve2048_storeu_int16(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline int8_t mipp_sve2048_get_int8(const rvd_sve2048_int8_t r0, const uint32_t v0) {
	int8_t t[MIPP_SVE2048_N_INT8];
    mipp_sve2048_storeu_int8(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline uint64_t mipp_sve2048_get_uint64(const rvd_sve2048_uint64_t r0, const uint32_t v0) {
	uint64_t t[MIPP_SVE2048_N_UINT64];
    mipp_sve2048_storeu_uint64(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline uint32_t mipp_sve2048_get_uint32(const rvd_sve2048_uint32_t r0, const uint32_t v0) {
	uint32_t t[MIPP_SVE2048_N_UINT32];
    mipp_sve2048_storeu_uint32(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline uint16_t mipp_sve2048_get_uint16(const rvd_sve2048_uint16_t r0, const uint32_t v0) {
	uint16_t t[MIPP_SVE2048_N_UINT16];
    mipp_sve2048_storeu_uint16(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
static inline uint8_t mipp_sve2048_get_uint8(const rvd_sve2048_uint8_t r0, const uint32_t v0) {
	uint8_t t[MIPP_SVE2048_N_UINT8];
    mipp_sve2048_storeu_uint8(t, r0);
    return t[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline float64_t mipp_sve2048_getfirst_float64(const rvd_sve2048_float64_t r0) {
	  return mipp_sve2048_get_float64(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline float32_t mipp_sve2048_getfirst_float32(const rvd_sve2048_float32_t r0) {
	  return mipp_sve2048_get_float32(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline int64_t mipp_sve2048_getfirst_int64(const rvd_sve2048_int64_t r0) {
	  return mipp_sve2048_get_int64(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline int32_t mipp_sve2048_getfirst_int32(const rvd_sve2048_int32_t r0) {
	  return mipp_sve2048_get_int32(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline int16_t mipp_sve2048_getfirst_int16(const rvd_sve2048_int16_t r0) {
	  return mipp_sve2048_get_int16(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline int8_t mipp_sve2048_getfirst_int8(const rvd_sve2048_int8_t r0) {
	  return mipp_sve2048_get_int8(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline uint64_t mipp_sve2048_getfirst_uint64(const rvd_sve2048_uint64_t r0) {
	  return mipp_sve2048_get_uint64(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline uint32_t mipp_sve2048_getfirst_uint32(const rvd_sve2048_uint32_t r0) {
	  return mipp_sve2048_get_uint32(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline uint16_t mipp_sve2048_getfirst_uint16(const rvd_sve2048_uint16_t r0) {
	  return mipp_sve2048_get_uint16(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
static inline uint8_t mipp_sve2048_getfirst_uint8(const rvd_sve2048_uint8_t r0) {
	  return mipp_sve2048_get_uint8(r0, 0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline float64_t mipp_sve2048_get_k_float64(const rvm_sve2048_float64_t m0, const uint32_t v0) {
	 float64_t tmp[MIPP_SVE2048_N_FLOAT64];
    rvd_sve2048_float64_t rmsk =mipp_sve2048_toreg_float64(m0);
    mipp_sve2048_storeu_float64(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline float32_t mipp_sve2048_get_k_float32(const rvm_sve2048_float32_t m0, const uint32_t v0) {
	 float32_t tmp[MIPP_SVE2048_N_FLOAT32];
    rvd_sve2048_float32_t rmsk =mipp_sve2048_toreg_float32(m0);
    mipp_sve2048_storeu_float32(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline int64_t mipp_sve2048_get_k_int64(const rvm_sve2048_int64_t m0, const uint32_t v0) {
	 int64_t tmp[MIPP_SVE2048_N_INT64];
    rvd_sve2048_int64_t rmsk =mipp_sve2048_toreg_int64(m0);
    mipp_sve2048_storeu_int64(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline int32_t mipp_sve2048_get_k_int32(const rvm_sve2048_int32_t m0, const uint32_t v0) {
	 int32_t tmp[MIPP_SVE2048_N_INT32];
    rvd_sve2048_int32_t rmsk =mipp_sve2048_toreg_int32(m0);
    mipp_sve2048_storeu_int32(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline uint64_t mipp_sve2048_get_k_uint64(const rvm_sve2048_uint64_t m0, const uint32_t v0) {
	 uint64_t tmp[MIPP_SVE2048_N_UINT64];
    rvd_sve2048_uint64_t rmsk =mipp_sve2048_toreg_uint64(m0);
    mipp_sve2048_storeu_uint64(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline uint32_t mipp_sve2048_get_k_uint32(const rvm_sve2048_uint32_t m0, const uint32_t v0) {
	 uint32_t tmp[MIPP_SVE2048_N_UINT32];
    rvd_sve2048_uint32_t rmsk =mipp_sve2048_toreg_uint32(m0);
    mipp_sve2048_storeu_uint32(tmp, rmsk);
    return (int32_t) tmp[v0];
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
// ---------------------------------------------------------------------------------------------------------------------------------------------- get_k
static inline rvd_sve2048_int16_t mipp_sve2048_toreg_int16(const rvm_sve2048_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_toreg_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_toreg_int8(const rvm_sve2048_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_toreg_int8");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_toreg_uint16(const rvm_sve2048_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_toreg_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_toreg_uint8(const rvm_sve2048_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_toreg_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_tomsk_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_tomsk_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_tomsk_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_tomsk_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_tomsk_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_tomsk_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_tomsk_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_tomsk_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_tomsk_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_tomsk_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_tomsk_uint8");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_set_k_int16(const int32_t vals[MIPP_SVE2048_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_set_k_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_set_k_int8(const int32_t vals[MIPP_SVE2048_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_set_k_int8");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_set_k_uint16(const int32_t vals[MIPP_SVE2048_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_set_k_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_set_k_uint8(const int32_t vals[MIPP_SVE2048_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_set_k_uint8");
	exit(-1);
}
static inline int16_t mipp_sve2048_get_k_int16(const rvm_sve2048_int16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_get_k_int16");
	exit(-1);
}
static inline int8_t mipp_sve2048_get_k_int8(const rvm_sve2048_int8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_get_k_int8");
	exit(-1);
}
static inline uint16_t mipp_sve2048_get_k_uint16(const rvm_sve2048_uint16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_get_k_uint16");
	exit(-1);
}
static inline uint8_t mipp_sve2048_get_k_uint8(const rvm_sve2048_uint8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_get_k_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_sqrt_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_sqrt_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_sqrt_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_sqrt_float32");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_rsqrt_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_rsqrt_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_rsqrt_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_rsqrt_float32");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_min_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_min_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_min_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_min_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_min_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_min_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_min_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_min_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_min_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_min_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_min_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_max_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_max_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_max_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_max_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_max_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_max_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_max_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_max_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_max_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_max_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_max_uint8");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_fmadd_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1, const rvd_sve2048_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_fmadd_int32");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_fmsub_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1, const rvd_sve2048_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_fmsub_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_fmsub_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1, const rvd_sve2048_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_fmsub_float32");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_fmsub_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1, const rvd_sve2048_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_fmsub_int32");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_andnb_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_andnb_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_andnb_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_andnb_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_andnb_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_andnb_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_andnb_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_andnb_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_andnb_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_andnb_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_andnb_k_float64(const rvm_sve2048_float64_t m0, const rvm_sve2048_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_andnb_k_float32(const rvm_sve2048_float32_t m0, const rvm_sve2048_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_andnb_k_int64(const rvm_sve2048_int64_t m0, const rvm_sve2048_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_andnb_k_int32(const rvm_sve2048_int32_t m0, const rvm_sve2048_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_andnb_k_int16(const rvm_sve2048_int16_t m0, const rvm_sve2048_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_andnb_k_int8(const rvm_sve2048_int8_t m0, const rvm_sve2048_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_andnb_k_uint64(const rvm_sve2048_uint64_t m0, const rvm_sve2048_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_andnb_k_uint32(const rvm_sve2048_uint32_t m0, const rvm_sve2048_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_andnb_k_uint16(const rvm_sve2048_uint16_t m0, const rvm_sve2048_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_andnb_k_uint8(const rvm_sve2048_uint8_t m0, const rvm_sve2048_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_andnb_k_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_orb_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_orb_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_orb_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_orb_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_orb_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_orb_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_orb_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_orb_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_orb_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_orb_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_orb_k_float64(const rvm_sve2048_float64_t m0, const rvm_sve2048_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_orb_k_float32(const rvm_sve2048_float32_t m0, const rvm_sve2048_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_orb_k_int64(const rvm_sve2048_int64_t m0, const rvm_sve2048_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_orb_k_int32(const rvm_sve2048_int32_t m0, const rvm_sve2048_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_orb_k_int16(const rvm_sve2048_int16_t m0, const rvm_sve2048_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_orb_k_int8(const rvm_sve2048_int8_t m0, const rvm_sve2048_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_orb_k_uint64(const rvm_sve2048_uint64_t m0, const rvm_sve2048_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_orb_k_uint32(const rvm_sve2048_uint32_t m0, const rvm_sve2048_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_orb_k_uint16(const rvm_sve2048_uint16_t m0, const rvm_sve2048_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_orb_k_uint8(const rvm_sve2048_uint8_t m0, const rvm_sve2048_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_orb_k_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_xorb_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_xorb_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_xorb_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_xorb_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_xorb_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_xorb_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_xorb_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_xorb_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_xorb_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_xorb_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_xorb_k_float64(const rvm_sve2048_float64_t m0, const rvm_sve2048_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_xorb_k_float32(const rvm_sve2048_float32_t m0, const rvm_sve2048_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_xorb_k_int64(const rvm_sve2048_int64_t m0, const rvm_sve2048_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_xorb_k_int32(const rvm_sve2048_int32_t m0, const rvm_sve2048_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_xorb_k_int16(const rvm_sve2048_int16_t m0, const rvm_sve2048_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_xorb_k_int8(const rvm_sve2048_int8_t m0, const rvm_sve2048_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_xorb_k_uint64(const rvm_sve2048_uint64_t m0, const rvm_sve2048_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_xorb_k_uint32(const rvm_sve2048_uint32_t m0, const rvm_sve2048_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_xorb_k_uint16(const rvm_sve2048_uint16_t m0, const rvm_sve2048_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_xorb_k_uint8(const rvm_sve2048_uint8_t m0, const rvm_sve2048_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_xorb_k_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_msb_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_msb_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_msb_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_msb_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_msb_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_msb_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_msb_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_msb_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_msb_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_msb_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_msb_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_notb_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_notb_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_notb_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_notb_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_notb_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_notb_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_notb_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_notb_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_notb_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_notb_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_notb_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_cmplt_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_cmplt_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_cmplt_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_cmplt_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_cmplt_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_cmplt_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_cmplt_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_cmplt_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_cmplt_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_cmplt_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmplt_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_cmple_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_cmple_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_cmple_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_cmple_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_cmple_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_cmple_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_cmple_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_cmple_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_cmple_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_cmple_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmple_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_cmpge_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_cmpge_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_cmpge_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_cmpge_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_cmpge_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_cmpge_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_cmpge_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_cmpge_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_cmpge_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_cmpge_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpge_uint8");
	exit(-1);
}
static inline rvm_sve2048_float64_t mipp_sve2048_cmpgt_float64(const rvd_sve2048_float64_t r0, const rvd_sve2048_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_float64");
	exit(-1);
}
static inline rvm_sve2048_float32_t mipp_sve2048_cmpgt_float32(const rvd_sve2048_float32_t r0, const rvd_sve2048_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_float32");
	exit(-1);
}
static inline rvm_sve2048_int64_t mipp_sve2048_cmpgt_int64(const rvd_sve2048_int64_t r0, const rvd_sve2048_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_int64");
	exit(-1);
}
static inline rvm_sve2048_int32_t mipp_sve2048_cmpgt_int32(const rvd_sve2048_int32_t r0, const rvd_sve2048_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_int32");
	exit(-1);
}
static inline rvm_sve2048_int16_t mipp_sve2048_cmpgt_int16(const rvd_sve2048_int16_t r0, const rvd_sve2048_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_int16");
	exit(-1);
}
static inline rvm_sve2048_int8_t mipp_sve2048_cmpgt_int8(const rvd_sve2048_int8_t r0, const rvd_sve2048_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_int8");
	exit(-1);
}
static inline rvm_sve2048_uint64_t mipp_sve2048_cmpgt_uint64(const rvd_sve2048_uint64_t r0, const rvd_sve2048_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_uint64");
	exit(-1);
}
static inline rvm_sve2048_uint32_t mipp_sve2048_cmpgt_uint32(const rvd_sve2048_uint32_t r0, const rvd_sve2048_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_uint32");
	exit(-1);
}
static inline rvm_sve2048_uint16_t mipp_sve2048_cmpgt_uint16(const rvd_sve2048_uint16_t r0, const rvd_sve2048_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_uint16");
	exit(-1);
}
static inline rvm_sve2048_uint8_t mipp_sve2048_cmpgt_uint8(const rvd_sve2048_uint8_t r0, const rvd_sve2048_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_cmpgt_uint8");
	exit(-1);
}
static inline float64_t mipp_sve2048_round_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_float64");
	exit(-1);
}
static inline float32_t mipp_sve2048_round_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_float32");
	exit(-1);
}
static inline int64_t mipp_sve2048_round_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_int64");
	exit(-1);
}
static inline int32_t mipp_sve2048_round_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_int32");
	exit(-1);
}
static inline int16_t mipp_sve2048_round_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_int16");
	exit(-1);
}
static inline int8_t mipp_sve2048_round_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_int8");
	exit(-1);
}
static inline uint64_t mipp_sve2048_round_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_uint64");
	exit(-1);
}
static inline uint32_t mipp_sve2048_round_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_uint32");
	exit(-1);
}
static inline uint16_t mipp_sve2048_round_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_uint16");
	exit(-1);
}
static inline uint8_t mipp_sve2048_round_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_round_uint8");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_float64(const rvm_sve2048_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_float64");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_float32(const rvm_sve2048_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_float32");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_int64(const rvm_sve2048_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_int64");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_int32(const rvm_sve2048_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_int32");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_int16(const rvm_sve2048_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_int16");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_int8(const rvm_sve2048_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_int8");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_uint64(const rvm_sve2048_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_uint64");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_uint32(const rvm_sve2048_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_uint32");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_uint16(const rvm_sve2048_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_uint16");
	exit(-1);
}
static inline int32_t mipp_sve2048_testz_2_uint8(const rvm_sve2048_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_testz_2_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_hmul_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_hmul_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_hmul_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_hmul_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_hmul_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_hmul_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_hmul_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_hmul_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_hmul_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_hmul_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmul_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_hmin_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_hmin_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_hmin_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_hmin_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_hmin_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_hmin_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_hmin_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_hmin_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_hmin_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_hmin_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmin_uint8");
	exit(-1);
}
static inline rvd_sve2048_float64_t mipp_sve2048_hmax_float64(const rvd_sve2048_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_float64");
	exit(-1);
}
static inline rvd_sve2048_float32_t mipp_sve2048_hmax_float32(const rvd_sve2048_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_float32");
	exit(-1);
}
static inline rvd_sve2048_int64_t mipp_sve2048_hmax_int64(const rvd_sve2048_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_int64");
	exit(-1);
}
static inline rvd_sve2048_int32_t mipp_sve2048_hmax_int32(const rvd_sve2048_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_int32");
	exit(-1);
}
static inline rvd_sve2048_int16_t mipp_sve2048_hmax_int16(const rvd_sve2048_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_int16");
	exit(-1);
}
static inline rvd_sve2048_int8_t mipp_sve2048_hmax_int8(const rvd_sve2048_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_int8");
	exit(-1);
}
static inline rvd_sve2048_uint64_t mipp_sve2048_hmax_uint64(const rvd_sve2048_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_uint64");
	exit(-1);
}
static inline rvd_sve2048_uint32_t mipp_sve2048_hmax_uint32(const rvd_sve2048_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_uint32");
	exit(-1);
}
static inline rvd_sve2048_uint16_t mipp_sve2048_hmax_uint16(const rvd_sve2048_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_uint16");
	exit(-1);
}
static inline rvd_sve2048_uint8_t mipp_sve2048_hmax_uint8(const rvd_sve2048_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve2048_hmax_uint8");
	exit(-1);
}
#endif /* __ARM_FEATURE_SVE */
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE2048_H_ */
