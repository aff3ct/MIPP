#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_
#include <arm_sve.h>
#if __ARM_FEATURE_SVE_BITS
#define MIPP_REGISTER_SIZE __ARM_FEATURE_SVE_BITS
#define MIPP_SVE_RVD_SIZE_BIT __ARM_FEATURE_SVE_BITS
#define MIPP_SVE_RVD_SIZE_BYTE MIPP_SVE_RVD_SIZE_BIT/8
#define MIPP_N_FLOAT64 MIPP_SVE_RVD_SIZE_BIT/64
#define MIPP_N_FLOAT32 MIPP_SVE_RVD_SIZE_BIT/32
#define MIPP_N_INT64 MIPP_SVE_RVD_SIZE_BIT/64
#define MIPP_N_INT32 MIPP_SVE_RVD_SIZE_BIT/32
#define MIPP_N_INT16 MIPP_SVE_RVD_SIZE_BIT/16
#define MIPP_N_INT8 MIPP_SVE_RVD_SIZE_BIT/8
#define MIPP_N_UINT64 MIPP_SVE_RVD_SIZE_BIT/64
#define MIPP_N_UINT32 MIPP_SVE_RVD_SIZE_BIT/32
#define MIPP_N_UINT16 MIPP_SVE_RVD_SIZE_BIT/16
#define MIPP_N_UINT8 MIPP_SVE_RVD_SIZE_BIT/8
#else
// autre possibilite genere un fichier SVE par taille supportee
#error Only -msve-vector-bits = 128-256-512-1024-2048 is supported
#endif
typedef svfloat64_t fixed_float64_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svfloat32_t fixed_float32_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint64_t fixed_int64_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint32_t fixed_int32_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint16_t fixed_int16_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint8_t fixed_int8_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svuint64_t fixed_uint64_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svuint32_t fixed_uint32_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svuint16_t fixed_uint16_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svuint8_t fixed_uint8_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svbool_t fixed_bool_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef struct { fixed_float64_t r; } rvd_sve_float64_t;
typedef struct { fixed_float32_t r; } rvd_sve_float32_t;
typedef struct { fixed_int64_t r; } rvd_sve_int64_t;
typedef struct { fixed_int32_t r; } rvd_sve_int32_t;
typedef struct { fixed_int16_t r; } rvd_sve_int16_t;
typedef struct { fixed_int8_t r; } rvd_sve_int8_t;
typedef struct { fixed_uint64_t r; } rvd_sve_uint64_t;
typedef struct { fixed_uint32_t r; } rvd_sve_uint32_t;
typedef struct { fixed_uint16_t r; } rvd_sve_uint16_t;
typedef struct { fixed_uint8_t r; } rvd_sve_uint8_t;
typedef struct { fixed_bool_t m; } rvm_sve_float64_t;
typedef struct { fixed_bool_t m; } rvm_sve_float32_t;
typedef struct { fixed_bool_t m; } rvm_sve_int64_t;
typedef struct { fixed_bool_t m; } rvm_sve_int32_t;
typedef struct { fixed_bool_t m; } rvm_sve_int16_t;
typedef struct { fixed_bool_t m; } rvm_sve_int8_t;
typedef struct { fixed_bool_t m; } rvm_sve_uint64_t;
typedef struct { fixed_bool_t m; } rvm_sve_uint32_t;
typedef struct { fixed_bool_t m; } rvm_sve_uint16_t;
typedef struct { fixed_bool_t m; } rvm_sve_uint8_t;
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_float64_float64(const rvd_sve_float64_t r0) {
	rvd_sve_float64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_float32_float64(const rvd_sve_float32_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_int64_float64(const rvd_sve_int64_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_int32_float64(const rvd_sve_int32_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_int16_float64(const rvd_sve_int16_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_int8_float64(const rvd_sve_int8_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_uint64_float64(const rvd_sve_uint64_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_uint32_float64(const rvd_sve_uint32_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_uint16_float64(const rvd_sve_uint16_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float64_t mipp_sve_cast_uint8_float64(const rvd_sve_uint8_t r0) {
	rvd_sve_float64_t res;
	res.r= svreinterpret_f64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_float64_float32(const rvd_sve_float64_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_float32_float32(const rvd_sve_float32_t r0) {
	rvd_sve_float32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_int64_float32(const rvd_sve_int64_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_int32_float32(const rvd_sve_int32_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_int16_float32(const rvd_sve_int16_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_int8_float32(const rvd_sve_int8_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_uint64_float32(const rvd_sve_uint64_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_uint32_float32(const rvd_sve_uint32_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_uint16_float32(const rvd_sve_uint16_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_float32_t mipp_sve_cast_uint8_float32(const rvd_sve_uint8_t r0) {
	rvd_sve_float32_t res;
	res.r= svreinterpret_f32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_float64_int64(const rvd_sve_float64_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_float32_int64(const rvd_sve_float32_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_int64_int64(const rvd_sve_int64_t r0) {
	rvd_sve_int64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_int32_int64(const rvd_sve_int32_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_int16_int64(const rvd_sve_int16_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_int8_int64(const rvd_sve_int8_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_uint64_int64(const rvd_sve_uint64_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_uint32_int64(const rvd_sve_uint32_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_uint16_int64(const rvd_sve_uint16_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int64_t mipp_sve_cast_uint8_int64(const rvd_sve_uint8_t r0) {
	rvd_sve_int64_t res;
	res.r= svreinterpret_s64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_float64_int32(const rvd_sve_float64_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_float32_int32(const rvd_sve_float32_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_int64_int32(const rvd_sve_int64_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_int32_int32(const rvd_sve_int32_t r0) {
	rvd_sve_int32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_int16_int32(const rvd_sve_int16_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_int8_int32(const rvd_sve_int8_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_uint64_int32(const rvd_sve_uint64_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_uint32_int32(const rvd_sve_uint32_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_uint16_int32(const rvd_sve_uint16_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int32_t mipp_sve_cast_uint8_int32(const rvd_sve_uint8_t r0) {
	rvd_sve_int32_t res;
	res.r= svreinterpret_s32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_float64_int16(const rvd_sve_float64_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_float32_int16(const rvd_sve_float32_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_int64_int16(const rvd_sve_int64_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_int32_int16(const rvd_sve_int32_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_int16_int16(const rvd_sve_int16_t r0) {
	rvd_sve_int16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_int8_int16(const rvd_sve_int8_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_uint64_int16(const rvd_sve_uint64_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_uint32_int16(const rvd_sve_uint32_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_uint16_int16(const rvd_sve_uint16_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int16_t mipp_sve_cast_uint8_int16(const rvd_sve_uint8_t r0) {
	rvd_sve_int16_t res;
	res.r= svreinterpret_s16_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_float64_int8(const rvd_sve_float64_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_float32_int8(const rvd_sve_float32_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_int64_int8(const rvd_sve_int64_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_int32_int8(const rvd_sve_int32_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_int16_int8(const rvd_sve_int16_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_int8_int8(const rvd_sve_int8_t r0) {
	rvd_sve_int8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_uint64_int8(const rvd_sve_uint64_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_uint32_int8(const rvd_sve_uint32_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_uint16_int8(const rvd_sve_uint16_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_int8_t mipp_sve_cast_uint8_int8(const rvd_sve_uint8_t r0) {
	rvd_sve_int8_t res;
	res.r= svreinterpret_s8_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_float64_uint64(const rvd_sve_float64_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_float32_uint64(const rvd_sve_float32_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_int64_uint64(const rvd_sve_int64_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_int32_uint64(const rvd_sve_int32_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_int16_uint64(const rvd_sve_int16_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_int8_uint64(const rvd_sve_int8_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_uint64_uint64(const rvd_sve_uint64_t r0) {
	rvd_sve_uint64_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_uint32_uint64(const rvd_sve_uint32_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_uint16_uint64(const rvd_sve_uint16_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint64_t mipp_sve_cast_uint8_uint64(const rvd_sve_uint8_t r0) {
	rvd_sve_uint64_t res;
	res.r= svreinterpret_u64_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_float64_uint32(const rvd_sve_float64_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_float32_uint32(const rvd_sve_float32_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_int64_uint32(const rvd_sve_int64_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_int32_uint32(const rvd_sve_int32_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_int16_uint32(const rvd_sve_int16_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_int8_uint32(const rvd_sve_int8_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_uint64_uint32(const rvd_sve_uint64_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_uint32_uint32(const rvd_sve_uint32_t r0) {
	rvd_sve_uint32_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_uint16_uint32(const rvd_sve_uint16_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint32_t mipp_sve_cast_uint8_uint32(const rvd_sve_uint8_t r0) {
	rvd_sve_uint32_t res;
	res.r= svreinterpret_u32_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_float64_uint16(const rvd_sve_float64_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_float32_uint16(const rvd_sve_float32_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_int64_uint16(const rvd_sve_int64_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_int32_uint16(const rvd_sve_int32_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_int16_uint16(const rvd_sve_int16_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_int8_uint16(const rvd_sve_int8_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_uint64_uint16(const rvd_sve_uint64_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_uint32_uint16(const rvd_sve_uint32_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_uint16_uint16(const rvd_sve_uint16_t r0) {
	rvd_sve_uint16_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint16_t mipp_sve_cast_uint8_uint16(const rvd_sve_uint8_t r0) {
	rvd_sve_uint16_t res;
	res.r= svreinterpret_u16_u8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_float64_uint8(const rvd_sve_float64_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_f64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_float32_uint8(const rvd_sve_float32_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_f32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_int64_uint8(const rvd_sve_int64_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_s64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_int32_uint8(const rvd_sve_int32_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_s32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_int16_uint8(const rvd_sve_int16_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_s16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_int8_uint8(const rvd_sve_int8_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_s8(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_uint64_uint8(const rvd_sve_uint64_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_u64(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_uint32_uint8(const rvd_sve_uint32_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_u32(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_uint16_uint8(const rvd_sve_uint16_t r0) {
	rvd_sve_uint8_t res;
	res.r= svreinterpret_u8_u16(r0.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cast
static inline rvd_sve_uint8_t mipp_sve_cast_uint8_uint8(const rvd_sve_uint8_t r0) {
	rvd_sve_uint8_t res;
	res.r= r0.r;
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_float64_t mipp_sve_blend_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1, const rvm_sve_float64_t m0) {
	rvd_sve_float64_t res;
	res.r= svsel_f64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_float32_t mipp_sve_blend_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1, const rvm_sve_float32_t m0) {
	rvd_sve_float32_t res;
	res.r= svsel_f32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_int64_t mipp_sve_blend_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1, const rvm_sve_int64_t m0) {
	rvd_sve_int64_t res;
	res.r= svsel_s64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_int32_t mipp_sve_blend_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1, const rvm_sve_int32_t m0) {
	rvd_sve_int32_t res;
	res.r= svsel_s32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_int16_t mipp_sve_blend_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1, const rvm_sve_int16_t m0) {
	rvd_sve_int16_t res;
	res.r= svsel_s16(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_int8_t mipp_sve_blend_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1, const rvm_sve_int8_t m0) {
	rvd_sve_int8_t res;
	res.r= svsel_s8(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_uint64_t mipp_sve_blend_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1, const rvm_sve_uint64_t m0) {
	rvd_sve_uint64_t res;
	res.r= svsel_u64(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_uint32_t mipp_sve_blend_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1, const rvm_sve_uint32_t m0) {
	rvd_sve_uint32_t res;
	res.r= svsel_u32(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_uint16_t mipp_sve_blend_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1, const rvm_sve_uint16_t m0) {
	rvd_sve_uint16_t res;
	res.r= svsel_u16(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- blend
static inline rvd_sve_uint8_t mipp_sve_blend_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1, const rvm_sve_uint8_t m0) {
	rvd_sve_uint8_t res;
	res.r= svsel_u8(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_float64_t mipp_sve_load_float64(const float64_t* p0) {
	rvd_sve_float64_t res;
	res.r= svld1_f64(svptrue_b64(), (float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_float32_t mipp_sve_load_float32(const float32_t* p0) {
	rvd_sve_float32_t res;
	res.r= svld1_f32(svptrue_b32(), (float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_int64_t mipp_sve_load_int64(const int64_t* p0) {
	rvd_sve_int64_t res;
	res.r= svld1_s64(svptrue_b64(), (int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_int32_t mipp_sve_load_int32(const int32_t* p0) {
	rvd_sve_int32_t res;
	res.r= svld1_s32(svptrue_b32(), (int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_int16_t mipp_sve_load_int16(const int16_t* p0) {
	rvd_sve_int16_t res;
	res.r= svld1_s16(svptrue_b16(), (int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_int8_t mipp_sve_load_int8(const int8_t* p0) {
	rvd_sve_int8_t res;
	res.r= svld1_s8(svptrue_b8(), (int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_uint64_t mipp_sve_load_uint64(const uint64_t* p0) {
	rvd_sve_uint64_t res;
	res.r= svld1_u64(svptrue_b64(), (uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_uint32_t mipp_sve_load_uint32(const uint32_t* p0) {
	rvd_sve_uint32_t res;
	res.r= svld1_u32(svptrue_b32(), (uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_uint16_t mipp_sve_load_uint16(const uint16_t* p0) {
	rvd_sve_uint16_t res;
	res.r= svld1_u16(svptrue_b16(), (uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- load
static inline rvd_sve_uint8_t mipp_sve_load_uint8(const uint8_t* p0) {
	rvd_sve_uint8_t res;
	res.r= svld1_u8(svptrue_b8(), (uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_float64_t mipp_sve_maskzld_float64(const rvm_sve_int32_t m0, const float64_t* p0) {
	rvd_sve_float64_t res;
	res.r= svld1_f64(m0.m, (float64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_float32_t mipp_sve_maskzld_float32(const rvm_sve_int32_t m0, const float32_t* p0) {
	rvd_sve_float32_t res;
	res.r= svld1_f32(m0.m, (float32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_int64_t mipp_sve_maskzld_int64(const rvm_sve_int32_t m0, const int64_t* p0) {
	rvd_sve_int64_t res;
	res.r= svld1_s64(m0.m, (int64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_int32_t mipp_sve_maskzld_int32(const rvm_sve_int32_t m0, const int32_t* p0) {
	rvd_sve_int32_t res;
	res.r= svld1_s32(m0.m, (int32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_int16_t mipp_sve_maskzld_int16(const rvm_sve_int32_t m0, const int16_t* p0) {
	rvd_sve_int16_t res;
	res.r= svld1_s16(m0.m, (int16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_int8_t mipp_sve_maskzld_int8(const rvm_sve_int32_t m0, const int8_t* p0) {
	rvd_sve_int8_t res;
	res.r= svld1_s8(m0.m, (int8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_uint64_t mipp_sve_maskzld_uint64(const rvm_sve_int32_t m0, const uint64_t* p0) {
	rvd_sve_uint64_t res;
	res.r= svld1_u64(m0.m, (uint64_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_uint32_t mipp_sve_maskzld_uint32(const rvm_sve_int32_t m0, const uint32_t* p0) {
	rvd_sve_uint32_t res;
	res.r= svld1_u32(m0.m, (uint32_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_uint16_t mipp_sve_maskzld_uint16(const rvm_sve_int32_t m0, const uint16_t* p0) {
	rvd_sve_uint16_t res;
	res.r= svld1_u16(m0.m, (uint16_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskzld
static inline rvd_sve_uint8_t mipp_sve_maskzld_uint8(const rvm_sve_int32_t m0, const uint8_t* p0) {
	rvd_sve_uint8_t res;
	res.r= svld1_u8(m0.m, (uint8_t*) p0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_float64_t mipp_sve_loadu_float64(const float64_t* p0) {
	rvd_sve_float64_t res;
	res.r= svld1_f64(svptrue_b64(), (float64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_float32_t mipp_sve_loadu_float32(const float32_t* p0) {
	rvd_sve_float32_t res;
	res.r= svld1_f32(svptrue_b32(), (float32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_int64_t mipp_sve_loadu_int64(const int64_t* p0) {
	rvd_sve_int64_t res;
	res.r= svld1_s64(svptrue_b64(), (int64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_int32_t mipp_sve_loadu_int32(const int32_t* p0) {
	rvd_sve_int32_t res;
	res.r= svld1_s32(svptrue_b32(), (int32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_int16_t mipp_sve_loadu_int16(const int16_t* p0) {
	rvd_sve_int16_t res;
	res.r= svld1_s16(svptrue_b16(), (int16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_int8_t mipp_sve_loadu_int8(const int8_t* p0) {
	rvd_sve_int8_t res;
	res.r= svld1_s8(svptrue_b8(), (int8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_uint64_t mipp_sve_loadu_uint64(const uint64_t* p0) {
	rvd_sve_uint64_t res;
	res.r= svld1_u64(svptrue_b64(), (uint64_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_uint32_t mipp_sve_loadu_uint32(const uint32_t* p0) {
	rvd_sve_uint32_t res;
	res.r= svld1_u32(svptrue_b32(), (uint32_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_uint16_t mipp_sve_loadu_uint16(const uint16_t* p0) {
	rvd_sve_uint16_t res;
	res.r= svld1_u16(svptrue_b16(), (uint16_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- loadu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline rvd_sve_uint8_t mipp_sve_loadu_uint8(const uint8_t* p0) {
	rvd_sve_uint8_t res;
	res.r= svld1_u8(svptrue_b8(), (uint8_t*) p0);
	return res;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_float64(float64_t* p0, const rvd_sve_float64_t r0) {
svst1_f64(svptrue_b64(), (float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_float32(float32_t* p0, const rvd_sve_float32_t r0) {
svst1_f32(svptrue_b32(), (float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_int64(int64_t* p0, const rvd_sve_int64_t r0) {
svst1_s64(svptrue_b64(), (int64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_int32(int32_t* p0, const rvd_sve_int32_t r0) {
svst1_s32(svptrue_b32(), (int32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_int16(int16_t* p0, const rvd_sve_int16_t r0) {
svst1_s16(svptrue_b16(), (int16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_int8(int8_t* p0, const rvd_sve_int8_t r0) {
svst1_s8(svptrue_b8(), (int8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_uint64(uint64_t* p0, const rvd_sve_uint64_t r0) {
svst1_u64(svptrue_b64(), (uint64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_uint32(uint32_t* p0, const rvd_sve_uint32_t r0) {
svst1_u32(svptrue_b32(), (uint32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_uint16(uint16_t* p0, const rvd_sve_uint16_t r0) {
svst1_u16(svptrue_b16(), (uint16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- store
static inline void mipp_sve_store_uint8(uint8_t* p0, const rvd_sve_uint8_t r0) {
svst1_u8(svptrue_b8(), (uint8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_float64(float64_t* p0, const rvm_sve_int32_t m0, const rvd_sve_float64_t r0) {
svst1_f64(m0.m, (float64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_float32(float32_t* p0, const rvm_sve_int32_t m0, const rvd_sve_float32_t r0) {
svst1_f32(m0.m, (float32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_int64(int64_t* p0, const rvm_sve_int32_t m0, const rvd_sve_int64_t r0) {
svst1_s64(m0.m, (int64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_int32(int32_t* p0, const rvm_sve_int32_t m0, const rvd_sve_int32_t r0) {
svst1_s32(m0.m, (int32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_int16(int16_t* p0, const rvm_sve_int32_t m0, const rvd_sve_int16_t r0) {
svst1_s16(m0.m, (int16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_int8(int8_t* p0, const rvm_sve_int32_t m0, const rvd_sve_int8_t r0) {
svst1_s8(m0.m, (int8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_uint64(uint64_t* p0, const rvm_sve_int32_t m0, const rvd_sve_uint64_t r0) {
svst1_u64(m0.m, (uint64_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_uint32(uint32_t* p0, const rvm_sve_int32_t m0, const rvd_sve_uint32_t r0) {
svst1_u32(m0.m, (uint32_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_uint16(uint16_t* p0, const rvm_sve_int32_t m0, const rvd_sve_uint16_t r0) {
svst1_u16(m0.m, (uint16_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskst
static inline void mipp_sve_maskst_uint8(uint8_t* p0, const rvm_sve_int32_t m0, const rvd_sve_uint8_t r0) {
svst1_u8(m0.m, (uint8_t*) p0, r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_float64(float64_t* p0, const rvd_sve_float64_t r0) {
svst1_f64(svptrue_b64(), (float64_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_float32(float32_t* p0, const rvd_sve_float32_t r0) {
svst1_f32(svptrue_b32(), (float32_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_int64(int64_t* p0, const rvd_sve_int64_t r0) {
svst1_s64(svptrue_b64(), (int64_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_int32(int32_t* p0, const rvd_sve_int32_t r0) {
svst1_s32(svptrue_b32(), (int32_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_int16(int16_t* p0, const rvd_sve_int16_t r0) {
svst1_s16(svptrue_b16(), (int16_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_int8(int8_t* p0, const rvd_sve_int8_t r0) {
svst1_s8(svptrue_b8(), (int8_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_uint64(uint64_t* p0, const rvd_sve_uint64_t r0) {
svst1_u64(svptrue_b64(), (uint64_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_uint32(uint32_t* p0, const rvd_sve_uint32_t r0) {
svst1_u32(svptrue_b32(), (uint32_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_uint16(uint16_t* p0, const rvd_sve_uint16_t r0) {
svst1_u16(svptrue_b16(), (uint16_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- storeu
#if defined(_ARM_FEATURE_UNALIGNED)
static inline void mipp_sve_storeu_uint8(uint8_t* p0, const rvd_sve_uint8_t r0) {
svst1_u8(svptrue_b8(), (uint8_t*) p0, r0.r);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_float64_t mipp_sve_set1_float64(const float64_t v0) {
	rvd_sve_float64_t res;
	res.r= svdup_f64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_float32_t mipp_sve_set1_float32(const float32_t v0) {
	rvd_sve_float32_t res;
	res.r= svdup_f32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_int64_t mipp_sve_set1_int64(const int64_t v0) {
	rvd_sve_int64_t res;
	res.r= svdup_s64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_int32_t mipp_sve_set1_int32(const int32_t v0) {
	rvd_sve_int32_t res;
	res.r= svdup_s32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_int16_t mipp_sve_set1_int16(const int16_t v0) {
	rvd_sve_int16_t res;
	res.r= svdup_s16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_int8_t mipp_sve_set1_int8(const int8_t v0) {
	rvd_sve_int8_t res;
	res.r= svdup_s8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_uint64_t mipp_sve_set1_uint64(const uint64_t v0) {
	rvd_sve_uint64_t res;
	res.r= svdup_u64(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_uint32_t mipp_sve_set1_uint32(const uint32_t v0) {
	rvd_sve_uint32_t res;
	res.r= svdup_u32(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_uint16_t mipp_sve_set1_uint16(const uint16_t v0) {
	rvd_sve_uint16_t res;
	res.r= svdup_u16(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1
static inline rvd_sve_uint8_t mipp_sve_set1_uint8(const uint8_t v0) {
	rvd_sve_uint8_t res;
	res.r= svdup_u8(v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_int64_t mipp_sve_set1_k_int64(const int32_t v0) {
	rvm_sve_int64_t res;
	res.m= svdup_b64((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_int32_t mipp_sve_set1_k_int32(const int32_t v0) {
	rvm_sve_int32_t res;
	res.m= svdup_b32((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_int16_t mipp_sve_set1_k_int16(const int32_t v0) {
	rvm_sve_int16_t res;
	res.m= svdup_b16((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_int8_t mipp_sve_set1_k_int8(const int32_t v0) {
	rvm_sve_int8_t res;
	res.m= svdup_b8((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_uint64_t mipp_sve_set1_k_uint64(const int32_t v0) {
	rvm_sve_uint64_t res;
	res.m= svdup_b64((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_uint32_t mipp_sve_set1_k_uint32(const int32_t v0) {
	rvm_sve_uint32_t res;
	res.m= svdup_b32((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_uint16_t mipp_sve_set1_k_uint16(const int32_t v0) {
	rvm_sve_uint16_t res;
	res.m= svdup_b16((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set1_k
static inline rvm_sve_uint8_t mipp_sve_set1_k_uint8(const int32_t v0) {
	rvm_sve_uint8_t res;
	res.m= svdup_b8((const bool) v0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_float64_t mipp_sve_set0_float64() {
	rvd_sve_float64_t res;
	res.r= svdup_f64(0.0d);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_float32_t mipp_sve_set0_float32() {
	rvd_sve_float32_t res;
	res.r= svdup_f32(0.0f);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_int64_t mipp_sve_set0_int64() {
	rvd_sve_int64_t res;
	res.r= svdup_s64(0LL);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_int32_t mipp_sve_set0_int32() {
	rvd_sve_int32_t res;
	res.r= svdup_s32(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_int16_t mipp_sve_set0_int16() {
	rvd_sve_int16_t res;
	res.r= svdup_s16(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_int8_t mipp_sve_set0_int8() {
	rvd_sve_int8_t res;
	res.r= svdup_s8(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_uint64_t mipp_sve_set0_uint64() {
	rvd_sve_uint64_t res;
	res.r= svdup_u64(0UL);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_uint32_t mipp_sve_set0_uint32() {
	rvd_sve_uint32_t res;
	res.r= svdup_u32(0U);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_uint16_t mipp_sve_set0_uint16() {
	rvd_sve_uint16_t res;
	res.r= svdup_u16(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0
static inline rvd_sve_uint8_t mipp_sve_set0_uint8() {
	rvd_sve_uint8_t res;
	res.r= svdup_u8(0);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_float64_t mipp_sve_set0_k_float64() {
	rvm_sve_float64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_float32_t mipp_sve_set0_k_float32() {
	rvm_sve_float32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_int64_t mipp_sve_set0_k_int64() {
	rvm_sve_int64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_int32_t mipp_sve_set0_k_int32() {
	rvm_sve_int32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_int16_t mipp_sve_set0_k_int16() {
	rvm_sve_int16_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_int8_t mipp_sve_set0_k_int8() {
	rvm_sve_int8_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_uint64_t mipp_sve_set0_k_uint64() {
	rvm_sve_uint64_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_uint32_t mipp_sve_set0_k_uint32() {
	rvm_sve_uint32_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_uint16_t mipp_sve_set0_k_uint16() {
	rvm_sve_uint16_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set0_k
static inline rvm_sve_uint8_t mipp_sve_set0_k_uint8() {
	rvm_sve_uint8_t res;
	res.m= svpfalse_b();
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_int64_t mipp_sve_andb_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvd_sve_int64_t res;
	res.r= svand_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_int32_t mipp_sve_andb_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvd_sve_int32_t res;
	res.r= svand_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_int16_t mipp_sve_andb_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvd_sve_int16_t res;
	res.r= svand_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_int8_t mipp_sve_andb_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvd_sve_int8_t res;
	res.r= svand_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_uint64_t mipp_sve_andb_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvd_sve_uint64_t res;
	res.r= svand_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_uint32_t mipp_sve_andb_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvd_sve_uint32_t res;
	res.r= svand_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_uint16_t mipp_sve_andb_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvd_sve_uint16_t res;
	res.r= svand_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_uint8_t mipp_sve_andb_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvd_sve_uint8_t res;
	res.r= svand_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_float64_t mipp_sve_andb_k_float64(const rvm_sve_float64_t m0, const rvm_sve_float64_t m1) {
	rvm_sve_float64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_float32_t mipp_sve_andb_k_float32(const rvm_sve_float32_t m0, const rvm_sve_float32_t m1) {
	rvm_sve_float32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_int64_t mipp_sve_andb_k_int64(const rvm_sve_int64_t m0, const rvm_sve_int64_t m1) {
	rvm_sve_int64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_int32_t mipp_sve_andb_k_int32(const rvm_sve_int32_t m0, const rvm_sve_int32_t m1) {
	rvm_sve_int32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_int16_t mipp_sve_andb_k_int16(const rvm_sve_int16_t m0, const rvm_sve_int16_t m1) {
	rvm_sve_int16_t res;
	res.m= svand_z(svptrue_b16(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_int8_t mipp_sve_andb_k_int8(const rvm_sve_int8_t m0, const rvm_sve_int8_t m1) {
	rvm_sve_int8_t res;
	res.m= svand_z(svptrue_b8(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_uint64_t mipp_sve_andb_k_uint64(const rvm_sve_uint64_t m0, const rvm_sve_uint64_t m1) {
	rvm_sve_uint64_t res;
	res.m= svand_z(svptrue_b64(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_uint32_t mipp_sve_andb_k_uint32(const rvm_sve_uint32_t m0, const rvm_sve_uint32_t m1) {
	rvm_sve_uint32_t res;
	res.m= svand_z(svptrue_b32(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_uint16_t mipp_sve_andb_k_uint16(const rvm_sve_uint16_t m0, const rvm_sve_uint16_t m1) {
	rvm_sve_uint16_t res;
	res.m= svand_z(svptrue_b16(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb_k
static inline rvm_sve_uint8_t mipp_sve_andb_k_uint8(const rvm_sve_uint8_t m0, const rvm_sve_uint8_t m1) {
	rvm_sve_uint8_t res;
	res.m= svand_z(svptrue_b8(), m0.m, m1.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_float64_t mipp_sve_notb_k_float64(const rvm_sve_float64_t m0) {
	rvm_sve_float64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_float32_t mipp_sve_notb_k_float32(const rvm_sve_float32_t m0) {
	rvm_sve_float32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_int64_t mipp_sve_notb_k_int64(const rvm_sve_int64_t m0) {
	rvm_sve_int64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_int32_t mipp_sve_notb_k_int32(const rvm_sve_int32_t m0) {
	rvm_sve_int32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_int16_t mipp_sve_notb_k_int16(const rvm_sve_int16_t m0) {
	rvm_sve_int16_t res;
	res.m= svnot_z(svptrue_b16(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_int8_t mipp_sve_notb_k_int8(const rvm_sve_int8_t m0) {
	rvm_sve_int8_t res;
	res.m= svnot_z(svptrue_b8(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_uint64_t mipp_sve_notb_k_uint64(const rvm_sve_uint64_t m0) {
	rvm_sve_uint64_t res;
	res.m= svnot_z(svptrue_b64(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_uint32_t mipp_sve_notb_k_uint32(const rvm_sve_uint32_t m0) {
	rvm_sve_uint32_t res;
	res.m= svnot_z(svptrue_b32(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_uint16_t mipp_sve_notb_k_uint16(const rvm_sve_uint16_t m0) {
	rvm_sve_uint16_t res;
	res.m= svnot_z(svptrue_b16(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- notb_k
static inline rvm_sve_uint8_t mipp_sve_notb_k_uint8(const rvm_sve_uint8_t m0) {
	rvm_sve_uint8_t res;
	res.m= svnot_z(svptrue_b8(), m0.m);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_float64(const rvm_sve_float64_t m0, const rvm_sve_float64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_float32(const rvm_sve_float32_t m0, const rvm_sve_float32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_int64(const rvm_sve_int64_t m0, const rvm_sve_int64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_int32(const rvm_sve_int32_t m0, const rvm_sve_int32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_int16(const rvm_sve_int16_t m0, const rvm_sve_int16_t m1) {
	return !svptest_any(svptrue_b16(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_int8(const rvm_sve_int8_t m0, const rvm_sve_int8_t m1) {
	return !svptest_any(svptrue_b8(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_uint64(const rvm_sve_uint64_t m0, const rvm_sve_uint64_t m1) {
	return !svptest_any(svptrue_b64(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_uint32(const rvm_sve_uint32_t m0, const rvm_sve_uint32_t m1) {
	return !svptest_any(svptrue_b32(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_uint16(const rvm_sve_uint16_t m0, const rvm_sve_uint16_t m1) {
	return !svptest_any(svptrue_b16(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- testz
static inline int32_t mipp_sve_testz_uint8(const rvm_sve_uint8_t m0, const rvm_sve_uint8_t m1) {
	return !svptest_any(svptrue_b8(), m0.m);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_float64_t mipp_sve_add_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_float64_t res;
	res.r= svadd_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_float32_t mipp_sve_add_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_float32_t res;
	res.r= svadd_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_int64_t mipp_sve_add_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvd_sve_int64_t res;
	res.r= svadd_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_int32_t mipp_sve_add_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvd_sve_int32_t res;
	res.r= svadd_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_int16_t mipp_sve_add_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvd_sve_int16_t res;
	res.r= svadd_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_int8_t mipp_sve_add_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvd_sve_int8_t res;
	res.r= svadd_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_uint64_t mipp_sve_add_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvd_sve_uint64_t res;
	res.r= svadd_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_uint32_t mipp_sve_add_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvd_sve_uint32_t res;
	res.r= svadd_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_uint16_t mipp_sve_add_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvd_sve_uint16_t res;
	res.r= svadd_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- add
static inline rvd_sve_uint8_t mipp_sve_add_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvd_sve_uint8_t res;
	res.r= svadd_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_float64_t mipp_sve_maskz_add_float64(const rvm_sve_float64_t m0, const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_float64_t res;
	res.r= svadd_f64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_float32_t mipp_sve_maskz_add_float32(const rvm_sve_float32_t m0, const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_float32_t res;
	res.r= svadd_f32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_int64_t mipp_sve_maskz_add_int64(const rvm_sve_int64_t m0, const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvd_sve_int64_t res;
	res.r= svadd_s64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_int32_t mipp_sve_maskz_add_int32(const rvm_sve_int32_t m0, const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvd_sve_int32_t res;
	res.r= svadd_s32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_int16_t mipp_sve_maskz_add_int16(const rvm_sve_int16_t m0, const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvd_sve_int16_t res;
	res.r= svadd_s16_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_int8_t mipp_sve_maskz_add_int8(const rvm_sve_int8_t m0, const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvd_sve_int8_t res;
	res.r= svadd_s8_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_uint64_t mipp_sve_maskz_add_uint64(const rvm_sve_uint64_t m0, const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvd_sve_uint64_t res;
	res.r= svadd_u64_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_uint32_t mipp_sve_maskz_add_uint32(const rvm_sve_uint32_t m0, const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvd_sve_uint32_t res;
	res.r= svadd_u32_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_uint16_t mipp_sve_maskz_add_uint16(const rvm_sve_uint16_t m0, const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvd_sve_uint16_t res;
	res.r= svadd_u16_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- maskz_add
static inline rvd_sve_uint8_t mipp_sve_maskz_add_uint8(const rvm_sve_uint8_t m0, const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvd_sve_uint8_t res;
	res.r= svadd_u8_z(m0.m, r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_float64_t mipp_sve_sub_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_float64_t res;
	res.r= svsub_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_float32_t mipp_sve_sub_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_float32_t res;
	res.r= svsub_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_int64_t mipp_sve_sub_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvd_sve_int64_t res;
	res.r= svsub_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_int32_t mipp_sve_sub_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvd_sve_int32_t res;
	res.r= svsub_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_int16_t mipp_sve_sub_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvd_sve_int16_t res;
	res.r= svsub_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_int8_t mipp_sve_sub_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvd_sve_int8_t res;
	res.r= svsub_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_uint64_t mipp_sve_sub_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvd_sve_uint64_t res;
	res.r= svsub_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_uint32_t mipp_sve_sub_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvd_sve_uint32_t res;
	res.r= svsub_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_uint16_t mipp_sve_sub_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvd_sve_uint16_t res;
	res.r= svsub_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- sub
static inline rvd_sve_uint8_t mipp_sve_sub_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvd_sve_uint8_t res;
	res.r= svsub_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_float64_t mipp_sve_mul_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_float64_t res;
	res.r= svmul_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_float32_t mipp_sve_mul_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_float32_t res;
	res.r= svmul_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_int64_t mipp_sve_mul_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvd_sve_int64_t res;
	res.r= svmul_s64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_int32_t mipp_sve_mul_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvd_sve_int32_t res;
	res.r= svmul_s32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_int16_t mipp_sve_mul_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvd_sve_int16_t res;
	res.r= svmul_s16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_int8_t mipp_sve_mul_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvd_sve_int8_t res;
	res.r= svmul_s8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_uint64_t mipp_sve_mul_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvd_sve_uint64_t res;
	res.r= svmul_u64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_uint32_t mipp_sve_mul_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvd_sve_uint32_t res;
	res.r= svmul_u32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_uint16_t mipp_sve_mul_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvd_sve_uint16_t res;
	res.r= svmul_u16_z(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- mul
static inline rvd_sve_uint8_t mipp_sve_mul_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvd_sve_uint8_t res;
	res.r= svmul_u8_z(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
static inline rvd_sve_float64_t mipp_sve_div_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_float64_t res;
	res.r= svdiv_f64_z(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- div
static inline rvd_sve_float32_t mipp_sve_div_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_float32_t res;
	res.r= svdiv_f32_z(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
static inline rvd_sve_float64_t mipp_sve_fmadd_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1, const rvd_sve_float64_t r2) {
	rvd_sve_float64_t res;
	res.r= svmla_f64_z(svptrue_b64(), r0.r, r1.r, r2.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- fmadd
static inline rvd_sve_float32_t mipp_sve_fmadd_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1, const rvd_sve_float32_t r2) {
	rvd_sve_float32_t res;
	res.r= svmla_f32_z(svptrue_b32(), r0.r, r1.r, r2.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_float64_t mipp_sve_cmpeq_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvm_sve_float64_t res;
	res.m= svcmpeq_f64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_float32_t mipp_sve_cmpeq_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvm_sve_float32_t res;
	res.m= svcmpeq_f32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_int64_t mipp_sve_cmpeq_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvm_sve_int64_t res;
	res.m= svcmpeq_s64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_int32_t mipp_sve_cmpeq_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvm_sve_int32_t res;
	res.m= svcmpeq_s32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_int16_t mipp_sve_cmpeq_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvm_sve_int16_t res;
	res.m= svcmpeq_s16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_int8_t mipp_sve_cmpeq_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvm_sve_int8_t res;
	res.m= svcmpeq_s8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_uint64_t mipp_sve_cmpeq_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvm_sve_uint64_t res;
	res.m= svcmpeq_u64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_uint32_t mipp_sve_cmpeq_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvm_sve_uint32_t res;
	res.m= svcmpeq_u32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_uint16_t mipp_sve_cmpeq_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvm_sve_uint16_t res;
	res.m= svcmpeq_u16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpeq
static inline rvm_sve_uint8_t mipp_sve_cmpeq_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvm_sve_uint8_t res;
	res.m= svcmpeq_u8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_float64_t mipp_sve_cmpneq_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvm_sve_float64_t res;
	res.m= svcmpne_f64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_float32_t mipp_sve_cmpneq_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvm_sve_float32_t res;
	res.m= svcmpne_f32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_int64_t mipp_sve_cmpneq_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	rvm_sve_int64_t res;
	res.m= svcmpne_s64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_int32_t mipp_sve_cmpneq_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	rvm_sve_int32_t res;
	res.m= svcmpne_s32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_int16_t mipp_sve_cmpneq_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	rvm_sve_int16_t res;
	res.m= svcmpne_s16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_int8_t mipp_sve_cmpneq_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	rvm_sve_int8_t res;
	res.m= svcmpne_s8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_uint64_t mipp_sve_cmpneq_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	rvm_sve_uint64_t res;
	res.m= svcmpne_u64(svptrue_b64(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_uint32_t mipp_sve_cmpneq_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	rvm_sve_uint32_t res;
	res.m= svcmpne_u32(svptrue_b32(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_uint16_t mipp_sve_cmpneq_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	rvm_sve_uint16_t res;
	res.m= svcmpne_u16(svptrue_b16(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- cmpneq
static inline rvm_sve_uint8_t mipp_sve_cmpneq_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	rvm_sve_uint8_t res;
	res.m= svcmpne_u8(svptrue_b8(), r0.r, r1.r);
	return res;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline float64_t mipp_sve_hadd_to_scal_float64(const rvd_sve_float64_t r0) {
	return svaddv_f64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline float32_t mipp_sve_hadd_to_scal_float32(const rvd_sve_float32_t r0) {
	return svaddv_f32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int64_t mipp_sve_hadd_to_scal_int64(const rvd_sve_int64_t r0) {
	return svaddv_s64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int32_t mipp_sve_hadd_to_scal_int32(const rvd_sve_int32_t r0) {
	return svaddv_s32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int16_t mipp_sve_hadd_to_scal_int16(const rvd_sve_int16_t r0) {
	return svaddv_s16(svptrue_b16(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline int8_t mipp_sve_hadd_to_scal_int8(const rvd_sve_int8_t r0) {
	return svaddv_s8(svptrue_b8(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint64_t mipp_sve_hadd_to_scal_uint64(const rvd_sve_uint64_t r0) {
	return svaddv_u64(svptrue_b64(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint32_t mipp_sve_hadd_to_scal_uint32(const rvd_sve_uint32_t r0) {
	return svaddv_u32(svptrue_b32(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint16_t mipp_sve_hadd_to_scal_uint16(const rvd_sve_uint16_t r0) {
	return svaddv_u16(svptrue_b16(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd_to_scal
static inline uint8_t mipp_sve_hadd_to_scal_uint8(const rvd_sve_uint8_t r0) {
	return svaddv_u8(svptrue_b8(), r0.r);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve_uint64_t mipp_sve_toreg_uint64(const rvm_sve_uint64_t m0) {
	rvd_sve_uint64_t one  = mipp_sve_set1_uint64(0xFFFFFFFFFFFFFFFF);
    rvd_sve_uint64_t zero = mipp_sve_set1_uint64(0);
    return mipp_sve_blend_uint64(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve_int64_t mipp_sve_toreg_int64(const rvm_sve_int64_t m0) {
	rvd_sve_int64_t one  = mipp_sve_set1_int64(0xFFFFFFFFFFFFFFFF);
    rvd_sve_int64_t zero = mipp_sve_set1_int64(0);
    return mipp_sve_blend_int64(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve_uint32_t mipp_sve_toreg_uint32(const rvm_sve_uint32_t m0) {
	rvd_sve_uint32_t one  = mipp_sve_set1_uint32(0xFFFFFFFF);
    rvd_sve_uint32_t zero = mipp_sve_set1_uint32(0);
    return mipp_sve_blend_uint32(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- toreg
static inline rvd_sve_int32_t mipp_sve_toreg_int32(const rvm_sve_int32_t m0) {
	rvd_sve_int32_t one  = mipp_sve_set1_int32(0xFFFFFFFF);
    rvd_sve_int32_t zero = mipp_sve_set1_int32(0);
    return mipp_sve_blend_int32(one, zero, m0);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_float64_t mipp_sve_andb_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	rvd_sve_int64_t a = mipp_sve_cast_float64_int64(r0);
    rvd_sve_int64_t b = mipp_sve_cast_float64_int64(r1);
    rvd_sve_int64_t res = mipp_sve_andb_int64(a,b);
    return mipp_sve_cast_int64_float64(res);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- andb
static inline rvd_sve_float32_t mipp_sve_andb_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	rvd_sve_int32_t a = mipp_sve_cast_float32_int32(r0);
    rvd_sve_int32_t b = mipp_sve_cast_float32_int32(r1);
    rvd_sve_int32_t res = mipp_sve_andb_int32(a,b);
    return mipp_sve_cast_int32_float32(res);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_float64_t mipp_sve_set_float64(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_sve_load_float64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_float32_t mipp_sve_set_float32(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_sve_load_float32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_int64_t mipp_sve_set_int64(const int64_t vals[MIPP_N_INT64]) {
	return mipp_sve_load_int64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_int32_t mipp_sve_set_int32(const int32_t vals[MIPP_N_INT32]) {
	return mipp_sve_load_int32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_int16_t mipp_sve_set_int16(const int16_t vals[MIPP_N_INT16]) {
	return mipp_sve_load_int16(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_int8_t mipp_sve_set_int8(const int8_t vals[MIPP_N_INT8]) {
	return mipp_sve_load_int8(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_uint64_t mipp_sve_set_uint64(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_sve_load_uint64(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_uint32_t mipp_sve_set_uint32(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_sve_load_uint32(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_uint16_t mipp_sve_set_uint16(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_sve_load_uint16(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set
static inline rvd_sve_uint8_t mipp_sve_set_uint8(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_sve_load_uint8(vals);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve_uint64_t mipp_sve_set_k_uint64(const int32_t vals[MIPP_N_UINT64]) {
	uint64_t v[MIPP_N_UINT64];
    for (int i = 0; i < MIPP_N_UINT64; i++)
        v[i] = vals[i] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0;
    rvd_sve_uint64_t r1 = mipp_sve_set_uint64(v);
    rvd_sve_uint64_t r2 = mipp_sve_set1_uint64(0);
    return mipp_sve_cmpeq_uint64(r1, r2);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve_int64_t mipp_sve_set_k_int64(const int32_t vals[MIPP_N_INT64]) {
	int64_t v[MIPP_N_INT64];
    for (int i = 0; i < MIPP_N_INT64; i++)
        v[i] = vals[i] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0;
    rvd_sve_int64_t r1 = mipp_sve_set_int64(v);
    rvd_sve_int64_t r2 = mipp_sve_set1_int64(0);
    return mipp_sve_cmpeq_int64(r1, r2);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve_uint32_t mipp_sve_set_k_uint32(const int32_t vals[MIPP_N_UINT32]) {
	uint32_t v[MIPP_N_UINT32];
    for (int i = 0; i < MIPP_N_UINT32; i++)
        v[i] = vals[i] ? 0xFFFFFFFF : 0;
    rvd_sve_uint32_t r1 = mipp_sve_set_uint32(v);
    rvd_sve_uint32_t r2 = mipp_sve_set1_uint32(0);
    return mipp_sve_cmpeq_uint32(r1, r2);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- set_k
static inline rvm_sve_int32_t mipp_sve_set_k_int32(const int32_t vals[MIPP_N_INT32]) {
	int32_t v[MIPP_N_INT32];
    for (int i = 0; i < MIPP_N_INT32; i++)
        v[i] = vals[i] ? 0xFFFFFFFF : 0;
    rvd_sve_int32_t r1 = mipp_sve_set_int32(v);
    rvd_sve_int32_t r2 = mipp_sve_set1_int32(0);
    return mipp_sve_cmpeq_int32(r1, r2);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_float64_t mipp_sve_hadd_float64(const rvd_sve_float64_t r0) {
	const float64_t val = mipp_sve_hadd_to_scal_float64(r0);
    return mipp_sve_set1_float64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_float32_t mipp_sve_hadd_float32(const rvd_sve_float32_t r0) {
	const float32_t val = mipp_sve_hadd_to_scal_float32(r0);
    return mipp_sve_set1_float32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_int64_t mipp_sve_hadd_int64(const rvd_sve_int64_t r0) {
	const int64_t val = mipp_sve_hadd_to_scal_int64(r0);
    return mipp_sve_set1_int64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_int32_t mipp_sve_hadd_int32(const rvd_sve_int32_t r0) {
	const int32_t val = mipp_sve_hadd_to_scal_int32(r0);
    return mipp_sve_set1_int32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_int16_t mipp_sve_hadd_int16(const rvd_sve_int16_t r0) {
	const int16_t val = mipp_sve_hadd_to_scal_int16(r0);
    return mipp_sve_set1_int16(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_int8_t mipp_sve_hadd_int8(const rvd_sve_int8_t r0) {
	const int8_t val = mipp_sve_hadd_to_scal_int8(r0);
    return mipp_sve_set1_int8(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_uint64_t mipp_sve_hadd_uint64(const rvd_sve_uint64_t r0) {
	const uint64_t val = mipp_sve_hadd_to_scal_uint64(r0);
    return mipp_sve_set1_uint64(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_uint32_t mipp_sve_hadd_uint32(const rvd_sve_uint32_t r0) {
	const uint32_t val = mipp_sve_hadd_to_scal_uint32(r0);
    return mipp_sve_set1_uint32(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_uint16_t mipp_sve_hadd_uint16(const rvd_sve_uint16_t r0) {
	const uint16_t val = mipp_sve_hadd_to_scal_uint16(r0);
    return mipp_sve_set1_uint16(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- hadd
static inline rvd_sve_uint8_t mipp_sve_hadd_uint8(const rvd_sve_uint8_t r0) {
	const uint8_t val = mipp_sve_hadd_to_scal_uint8(r0);
    return mipp_sve_set1_uint8(val);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline float64_t mipp_sve_get_float64(const rvd_sve_float64_t r0, const uint32_t v0) {
	float64_t t[MIPP_N_FLOAT64];
    mipp_sve_storeu_float64(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline float32_t mipp_sve_get_float32(const rvd_sve_float32_t r0, const uint32_t v0) {
	float32_t t[MIPP_N_FLOAT32];
    mipp_sve_storeu_float32(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline int64_t mipp_sve_get_int64(const rvd_sve_int64_t r0, const uint32_t v0) {
	int64_t t[MIPP_N_INT64];
    mipp_sve_storeu_int64(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline int32_t mipp_sve_get_int32(const rvd_sve_int32_t r0, const uint32_t v0) {
	int32_t t[MIPP_N_INT32];
    mipp_sve_storeu_int32(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline int16_t mipp_sve_get_int16(const rvd_sve_int16_t r0, const uint32_t v0) {
	int16_t t[MIPP_N_INT16];
    mipp_sve_storeu_int16(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline int8_t mipp_sve_get_int8(const rvd_sve_int8_t r0, const uint32_t v0) {
	int8_t t[MIPP_N_INT8];
    mipp_sve_storeu_int8(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline uint64_t mipp_sve_get_uint64(const rvd_sve_uint64_t r0, const uint32_t v0) {
	uint64_t t[MIPP_N_UINT64];
    mipp_sve_storeu_uint64(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline uint32_t mipp_sve_get_uint32(const rvd_sve_uint32_t r0, const uint32_t v0) {
	uint32_t t[MIPP_N_UINT32];
    mipp_sve_storeu_uint32(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline uint16_t mipp_sve_get_uint16(const rvd_sve_uint16_t r0, const uint32_t v0) {
	uint16_t t[MIPP_N_UINT16];
    mipp_sve_storeu_uint16(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- get
#if defined(_ARM_FEATURE_UNALIGNED)
static inline uint8_t mipp_sve_get_uint8(const rvd_sve_uint8_t r0, const uint32_t v0) {
	uint8_t t[MIPP_N_UINT8];
    mipp_sve_storeu_uint8(t, r0);
    return t[v0];
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline float64_t mipp_sve_getfirst_float64(const rvd_sve_float64_t r0) {
	  return mipp_sve_get_float64(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline float32_t mipp_sve_getfirst_float32(const rvd_sve_float32_t r0) {
	  return mipp_sve_get_float32(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline int64_t mipp_sve_getfirst_int64(const rvd_sve_int64_t r0) {
	  return mipp_sve_get_int64(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline int32_t mipp_sve_getfirst_int32(const rvd_sve_int32_t r0) {
	  return mipp_sve_get_int32(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline int16_t mipp_sve_getfirst_int16(const rvd_sve_int16_t r0) {
	  return mipp_sve_get_int16(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline int8_t mipp_sve_getfirst_int8(const rvd_sve_int8_t r0) {
	  return mipp_sve_get_int8(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline uint64_t mipp_sve_getfirst_uint64(const rvd_sve_uint64_t r0) {
	  return mipp_sve_get_uint64(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline uint32_t mipp_sve_getfirst_uint32(const rvd_sve_uint32_t r0) {
	  return mipp_sve_get_uint32(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline uint16_t mipp_sve_getfirst_uint16(const rvd_sve_uint16_t r0) {
	  return mipp_sve_get_uint16(r0, 0);
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------- getfirst
#if defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED)
static inline uint8_t mipp_sve_getfirst_uint8(const rvd_sve_uint8_t r0) {
	  return mipp_sve_get_uint8(r0, 0);
}
#endif
static inline rvm_sve_float64_t mipp_sve_cast_k_float64_float64(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_float32_float64(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_int64_float64(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_int32_float64(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_int16_float64(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_int8_float64(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_uint64_float64(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_uint32_float64(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_uint16_float64(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_float64");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cast_k_uint8_float64(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_float64_float32(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_float32_float32(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_int64_float32(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_int32_float32(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_int16_float32(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_int8_float32(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_uint64_float32(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_uint32_float32(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_uint16_float32(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_float32");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cast_k_uint8_float32(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_float64_int64(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_float32_int64(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_int64_int64(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_int32_int64(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_int16_int64(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_int8_int64(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_uint64_int64(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_uint32_int64(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_uint16_int64(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_int64");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cast_k_uint8_int64(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_float64_int32(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_float32_int32(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_int64_int32(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_int32_int32(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_int16_int32(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_int8_int32(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_uint64_int32(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_uint32_int32(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_uint16_int32(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_int32");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cast_k_uint8_int32(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_float64_int16(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_float32_int16(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_int64_int16(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_int32_int16(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_int16_int16(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_int8_int16(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_uint64_int16(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_uint32_int16(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_uint16_int16(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_int16");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cast_k_uint8_int16(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_float64_int8(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_float32_int8(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_int64_int8(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_int32_int8(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_int16_int8(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_int8_int8(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_uint64_int8(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_uint32_int8(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_uint16_int8(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_int8");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cast_k_uint8_int8(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_float64_uint64(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_float32_uint64(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_int64_uint64(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_int32_uint64(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_int16_uint64(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_int8_uint64(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_uint64_uint64(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_uint32_uint64(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_uint16_uint64(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_uint64");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cast_k_uint8_uint64(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_float64_uint32(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_float32_uint32(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_int64_uint32(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_int32_uint32(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_int16_uint32(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_int8_uint32(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_uint64_uint32(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_uint32_uint32(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_uint16_uint32(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_uint32");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cast_k_uint8_uint32(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_float64_uint16(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_float32_uint16(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_int64_uint16(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_int32_uint16(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_int16_uint16(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_int8_uint16(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_uint64_uint16(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_uint32_uint16(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_uint16_uint16(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_uint16");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cast_k_uint8_uint16(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_float64_uint8(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float64_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_float32_uint8(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_float32_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_int64_uint8(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int64_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_int32_uint8(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int32_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_int16_uint8(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int16_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_int8_uint8(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_int8_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_uint64_uint8(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint64_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_uint32_uint8(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint32_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_uint16_uint8(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint16_uint8");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cast_k_uint8_uint8(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cast_k_uint8_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_toreg_float64(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_toreg_float32(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_float32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_toreg_int16(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_toreg_int8(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_int8");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_toreg_uint16(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_toreg_uint8(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_toreg_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_tomsk_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_tomsk_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_tomsk_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_tomsk_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_tomsk_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_tomsk_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_tomsk_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_tomsk_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_tomsk_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_tomsk_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_tomsk_uint8");
	exit(-1);
}
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_float64_t mipp_sve_loadu_float64(const float64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_float64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_float32_t mipp_sve_loadu_float32(const float32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_float32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_int64_t mipp_sve_loadu_int64(const int64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_int64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_int32_t mipp_sve_loadu_int32(const int32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_int32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_int16_t mipp_sve_loadu_int16(const int16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_int16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_int8_t mipp_sve_loadu_int8(const int8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_int8");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_uint64_t mipp_sve_loadu_uint64(const uint64_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_uint64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_uint32_t mipp_sve_loadu_uint32(const uint32_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_uint32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_uint16_t mipp_sve_loadu_uint16(const uint16_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_uint16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline rvd_sve_uint8_t mipp_sve_loadu_uint8(const uint8_t* p0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_loadu_uint8");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_float64(float64_t* p0, const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_float64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_float32(float32_t* p0, const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_float32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_int64(int64_t* p0, const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_int64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_int32(int32_t* p0, const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_int32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_int16(int16_t* p0, const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_int16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_int8(int8_t* p0, const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_int8");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_uint64(uint64_t* p0, const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_uint64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_uint32(uint32_t* p0, const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_uint32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_uint16(uint16_t* p0, const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_uint16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) )
static inline void mipp_sve_storeu_uint8(uint8_t* p0, const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_storeu_uint8");
	exit(-1);
}
#endif
static inline rvm_sve_float64_t mipp_sve_set_k_float64(const int32_t vals[MIPP_N_FLOAT64]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_set_k_float32(const int32_t vals[MIPP_N_FLOAT32]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_float32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_set_k_int16(const int32_t vals[MIPP_N_INT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_set_k_int8(const int32_t vals[MIPP_N_INT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_int8");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_set_k_uint16(const int32_t vals[MIPP_N_UINT16]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_set_k_uint8(const int32_t vals[MIPP_N_UINT8]) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_set_k_uint8");
	exit(-1);
}
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline float64_t mipp_sve_get_float64(const rvd_sve_float64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_float64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline float32_t mipp_sve_get_float32(const rvd_sve_float32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_float32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int64_t mipp_sve_get_int64(const rvd_sve_int64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_int64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int32_t mipp_sve_get_int32(const rvd_sve_int32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_int32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int16_t mipp_sve_get_int16(const rvd_sve_int16_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_int16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int8_t mipp_sve_get_int8(const rvd_sve_int8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_int8");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint64_t mipp_sve_get_uint64(const rvd_sve_uint64_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_uint64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint32_t mipp_sve_get_uint32(const rvd_sve_uint32_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_uint32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint16_t mipp_sve_get_uint16(const rvd_sve_uint16_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_uint16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint8_t mipp_sve_get_uint8(const rvd_sve_uint8_t r0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_uint8");
	exit(-1);
}
#endif
static inline float64_t mipp_sve_get_k_float64(const rvm_sve_float64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_float64");
	exit(-1);
}
static inline float32_t mipp_sve_get_k_float32(const rvm_sve_float32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_float32");
	exit(-1);
}
static inline int64_t mipp_sve_get_k_int64(const rvm_sve_int64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_int64");
	exit(-1);
}
static inline int32_t mipp_sve_get_k_int32(const rvm_sve_int32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_int32");
	exit(-1);
}
static inline int16_t mipp_sve_get_k_int16(const rvm_sve_int16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_int16");
	exit(-1);
}
static inline int8_t mipp_sve_get_k_int8(const rvm_sve_int8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_int8");
	exit(-1);
}
static inline uint64_t mipp_sve_get_k_uint64(const rvm_sve_uint64_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_uint64");
	exit(-1);
}
static inline uint32_t mipp_sve_get_k_uint32(const rvm_sve_uint32_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_uint32");
	exit(-1);
}
static inline uint16_t mipp_sve_get_k_uint16(const rvm_sve_uint16_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_uint16");
	exit(-1);
}
static inline uint8_t mipp_sve_get_k_uint8(const rvm_sve_uint8_t m0, const uint32_t v0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_get_k_uint8");
	exit(-1);
}
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline float64_t mipp_sve_getfirst_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_float64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline float32_t mipp_sve_getfirst_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_float32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int64_t mipp_sve_getfirst_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_int64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int32_t mipp_sve_getfirst_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_int32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int16_t mipp_sve_getfirst_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_int16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline int8_t mipp_sve_getfirst_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_int8");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint64_t mipp_sve_getfirst_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_uint64");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint32_t mipp_sve_getfirst_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_uint32");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint16_t mipp_sve_getfirst_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_uint16");
	exit(-1);
}
#endif
#if !( defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) && defined(_ARM_FEATURE_UNALIGNED) )
static inline uint8_t mipp_sve_getfirst_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_getfirst_uint8");
	exit(-1);
}
#endif
static inline rvd_sve_float64_t mipp_sve_sqrt_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_sqrt_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_sqrt_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_sqrt_float32");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_rsqrt_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_rsqrt_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_rsqrt_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_rsqrt_float32");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_min_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_min_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_min_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_min_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_min_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_min_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_min_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_min_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_min_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_min_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_min_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_max_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_max_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_max_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_max_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_max_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_max_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_max_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_max_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_max_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_max_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_max_uint8");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_fmadd_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1, const rvd_sve_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_fmadd_int32");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_fmsub_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1, const rvd_sve_float64_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_fmsub_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_fmsub_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1, const rvd_sve_float32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_fmsub_float32");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_fmsub_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1, const rvd_sve_int32_t r2) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_fmsub_int32");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_andnb_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_andnb_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_andnb_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_andnb_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_andnb_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_andnb_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_andnb_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_andnb_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_andnb_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_andnb_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_andnb_k_float64(const rvm_sve_float64_t m0, const rvm_sve_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_andnb_k_float32(const rvm_sve_float32_t m0, const rvm_sve_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_andnb_k_int64(const rvm_sve_int64_t m0, const rvm_sve_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_andnb_k_int32(const rvm_sve_int32_t m0, const rvm_sve_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_andnb_k_int16(const rvm_sve_int16_t m0, const rvm_sve_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_andnb_k_int8(const rvm_sve_int8_t m0, const rvm_sve_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_andnb_k_uint64(const rvm_sve_uint64_t m0, const rvm_sve_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_andnb_k_uint32(const rvm_sve_uint32_t m0, const rvm_sve_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_andnb_k_uint16(const rvm_sve_uint16_t m0, const rvm_sve_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_andnb_k_uint8(const rvm_sve_uint8_t m0, const rvm_sve_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_andnb_k_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_orb_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_orb_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_orb_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_orb_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_orb_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_orb_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_orb_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_orb_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_orb_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_orb_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_orb_k_float64(const rvm_sve_float64_t m0, const rvm_sve_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_orb_k_float32(const rvm_sve_float32_t m0, const rvm_sve_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_orb_k_int64(const rvm_sve_int64_t m0, const rvm_sve_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_orb_k_int32(const rvm_sve_int32_t m0, const rvm_sve_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_orb_k_int16(const rvm_sve_int16_t m0, const rvm_sve_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_orb_k_int8(const rvm_sve_int8_t m0, const rvm_sve_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_orb_k_uint64(const rvm_sve_uint64_t m0, const rvm_sve_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_orb_k_uint32(const rvm_sve_uint32_t m0, const rvm_sve_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_orb_k_uint16(const rvm_sve_uint16_t m0, const rvm_sve_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_orb_k_uint8(const rvm_sve_uint8_t m0, const rvm_sve_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_orb_k_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_xorb_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_xorb_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_xorb_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_xorb_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_xorb_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_xorb_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_xorb_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_xorb_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_xorb_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_xorb_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_xorb_k_float64(const rvm_sve_float64_t m0, const rvm_sve_float64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_xorb_k_float32(const rvm_sve_float32_t m0, const rvm_sve_float32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_xorb_k_int64(const rvm_sve_int64_t m0, const rvm_sve_int64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_xorb_k_int32(const rvm_sve_int32_t m0, const rvm_sve_int32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_xorb_k_int16(const rvm_sve_int16_t m0, const rvm_sve_int16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_xorb_k_int8(const rvm_sve_int8_t m0, const rvm_sve_int8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_xorb_k_uint64(const rvm_sve_uint64_t m0, const rvm_sve_uint64_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_xorb_k_uint32(const rvm_sve_uint32_t m0, const rvm_sve_uint32_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_xorb_k_uint16(const rvm_sve_uint16_t m0, const rvm_sve_uint16_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_xorb_k_uint8(const rvm_sve_uint8_t m0, const rvm_sve_uint8_t m1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_xorb_k_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_msb_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_msb_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_msb_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_msb_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_msb_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_msb_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_msb_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_msb_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_msb_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_msb_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_msb_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_notb_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_notb_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_notb_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_notb_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_notb_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_notb_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_notb_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_notb_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_notb_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_notb_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_notb_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cmplt_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cmplt_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cmplt_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cmplt_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cmplt_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cmplt_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cmplt_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cmplt_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cmplt_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cmplt_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmplt_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cmple_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cmple_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cmple_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cmple_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cmple_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cmple_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cmple_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cmple_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cmple_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cmple_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmple_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cmpge_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cmpge_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cmpge_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cmpge_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cmpge_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cmpge_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cmpge_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cmpge_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cmpge_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cmpge_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpge_uint8");
	exit(-1);
}
static inline rvm_sve_float64_t mipp_sve_cmpgt_float64(const rvd_sve_float64_t r0, const rvd_sve_float64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_float64");
	exit(-1);
}
static inline rvm_sve_float32_t mipp_sve_cmpgt_float32(const rvd_sve_float32_t r0, const rvd_sve_float32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_float32");
	exit(-1);
}
static inline rvm_sve_int64_t mipp_sve_cmpgt_int64(const rvd_sve_int64_t r0, const rvd_sve_int64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_int64");
	exit(-1);
}
static inline rvm_sve_int32_t mipp_sve_cmpgt_int32(const rvd_sve_int32_t r0, const rvd_sve_int32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_int32");
	exit(-1);
}
static inline rvm_sve_int16_t mipp_sve_cmpgt_int16(const rvd_sve_int16_t r0, const rvd_sve_int16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_int16");
	exit(-1);
}
static inline rvm_sve_int8_t mipp_sve_cmpgt_int8(const rvd_sve_int8_t r0, const rvd_sve_int8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_int8");
	exit(-1);
}
static inline rvm_sve_uint64_t mipp_sve_cmpgt_uint64(const rvd_sve_uint64_t r0, const rvd_sve_uint64_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_uint64");
	exit(-1);
}
static inline rvm_sve_uint32_t mipp_sve_cmpgt_uint32(const rvd_sve_uint32_t r0, const rvd_sve_uint32_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_uint32");
	exit(-1);
}
static inline rvm_sve_uint16_t mipp_sve_cmpgt_uint16(const rvd_sve_uint16_t r0, const rvd_sve_uint16_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_uint16");
	exit(-1);
}
static inline rvm_sve_uint8_t mipp_sve_cmpgt_uint8(const rvd_sve_uint8_t r0, const rvd_sve_uint8_t r1) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_cmpgt_uint8");
	exit(-1);
}
static inline float64_t mipp_sve_round_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_float64");
	exit(-1);
}
static inline float32_t mipp_sve_round_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_float32");
	exit(-1);
}
static inline int64_t mipp_sve_round_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_int64");
	exit(-1);
}
static inline int32_t mipp_sve_round_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_int32");
	exit(-1);
}
static inline int16_t mipp_sve_round_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_int16");
	exit(-1);
}
static inline int8_t mipp_sve_round_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_int8");
	exit(-1);
}
static inline uint64_t mipp_sve_round_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_uint64");
	exit(-1);
}
static inline uint32_t mipp_sve_round_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_uint32");
	exit(-1);
}
static inline uint16_t mipp_sve_round_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_uint16");
	exit(-1);
}
static inline uint8_t mipp_sve_round_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_round_uint8");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_float64(const rvm_sve_float64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_float64");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_float32(const rvm_sve_float32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_float32");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_int64(const rvm_sve_int64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_int64");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_int32(const rvm_sve_int32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_int32");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_int16(const rvm_sve_int16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_int16");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_int8(const rvm_sve_int8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_int8");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_uint64(const rvm_sve_uint64_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_uint64");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_uint32(const rvm_sve_uint32_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_uint32");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_uint16(const rvm_sve_uint16_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_uint16");
	exit(-1);
}
static inline int32_t mipp_sve_testz_2_uint8(const rvm_sve_uint8_t m0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_testz_2_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_hmul_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_hmul_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_hmul_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_hmul_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_hmul_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_hmul_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_hmul_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_hmul_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_hmul_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_hmul_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmul_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_hmin_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_hmin_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_hmin_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_hmin_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_hmin_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_hmin_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_hmin_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_hmin_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_hmin_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_hmin_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmin_uint8");
	exit(-1);
}
static inline rvd_sve_float64_t mipp_sve_hmax_float64(const rvd_sve_float64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_float64");
	exit(-1);
}
static inline rvd_sve_float32_t mipp_sve_hmax_float32(const rvd_sve_float32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_float32");
	exit(-1);
}
static inline rvd_sve_int64_t mipp_sve_hmax_int64(const rvd_sve_int64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_int64");
	exit(-1);
}
static inline rvd_sve_int32_t mipp_sve_hmax_int32(const rvd_sve_int32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_int32");
	exit(-1);
}
static inline rvd_sve_int16_t mipp_sve_hmax_int16(const rvd_sve_int16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_int16");
	exit(-1);
}
static inline rvd_sve_int8_t mipp_sve_hmax_int8(const rvd_sve_int8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_int8");
	exit(-1);
}
static inline rvd_sve_uint64_t mipp_sve_hmax_uint64(const rvd_sve_uint64_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_uint64");
	exit(-1);
}
static inline rvd_sve_uint32_t mipp_sve_hmax_uint32(const rvd_sve_uint32_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_uint32");
	exit(-1);
}
static inline rvd_sve_uint16_t mipp_sve_hmax_uint16(const rvd_sve_uint16_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_uint16");
	exit(-1);
}
static inline rvd_sve_uint8_t mipp_sve_hmax_uint8(const rvd_sve_uint8_t r0) {
	printf("MIPP panic: '%s' is unimplemented.\n", "mipp_sve_hmax_uint8");
	exit(-1);
}
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_ */
