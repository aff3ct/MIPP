#include "mipp_v2.h"

#include <immintrin.h>

// ---------------------------------------------------------------- definitions

#define MIPP_RV_SIZE_BIT 256
#define MIPP_RV_SIZE_BYTE (MIPP_RV_SIZE_BIT/8)

#define MIPP_N_FLOAT64_M1  4
#define MIPP_N_FLOAT32_M1  8
#define   MIPP_N_INT64_M1  4
#define   MIPP_N_INT32_M1  8
#define   MIPP_N_INT16_M1 16
#define    MIPP_N_INT8_M1 32
#define  MIPP_N_UINT64_M1  4
#define  MIPP_N_UINT32_M1  8
#define  MIPP_N_UINT16_M1 16
#define   MIPP_N_UINT8_M1 32

#define MIPP_N_FLOAT64 MIPP_N_FLOAT64_M1
#define MIPP_N_FLOAT32 MIPP_N_FLOAT32_M1
#define   MIPP_N_INT64   MIPP_N_INT64_M1
#define   MIPP_N_INT32   MIPP_N_INT32_M1
#define   MIPP_N_INT16   MIPP_N_INT16_M1
#define    MIPP_N_INT8    MIPP_N_INT8_M1
#define  MIPP_N_UINT64  MIPP_N_UINT64_M1
#define  MIPP_N_UINT32  MIPP_N_UINT32_M1
#define  MIPP_N_UINT16  MIPP_N_UINT16_M1
#define   MIPP_N_UINT8   MIPP_N_UINT8_M1

#define MIPP_N_FLOAT64_M2 (MIPP_N_FLOAT64_M1 * 2)
#define MIPP_N_FLOAT32_M2 (MIPP_N_FLOAT32_M1 * 2)
#define   MIPP_N_INT64_M2 (  MIPP_N_INT64_M1 * 2)
#define   MIPP_N_INT32_M2 (  MIPP_N_INT32_M1 * 2)
#define   MIPP_N_INT16_M2 (  MIPP_N_INT16_M1 * 2)
#define    MIPP_N_INT8_M2 (   MIPP_N_INT8_M1 * 2)
#define  MIPP_N_UINT64_M2 ( MIPP_N_UINT64_M1 * 2)
#define  MIPP_N_UINT32_M2 ( MIPP_N_UINT32_M1 * 2)
#define  MIPP_N_UINT16_M2 ( MIPP_N_UINT16_M1 * 2)
#define   MIPP_N_UINT8_M2 (  MIPP_N_UINT8_M1 * 2)

#define MIPP_N_FLOAT64_M4 (MIPP_N_FLOAT64_M1 * 4)
#define MIPP_N_FLOAT32_M4 (MIPP_N_FLOAT32_M1 * 4)
#define   MIPP_N_INT64_M4 (  MIPP_N_INT64_M1 * 4)
#define   MIPP_N_INT32_M4 (  MIPP_N_INT32_M1 * 4)
#define   MIPP_N_INT16_M4 (  MIPP_N_INT16_M1 * 4)
#define    MIPP_N_INT8_M4 (   MIPP_N_INT8_M1 * 4)
#define  MIPP_N_UINT64_M4 ( MIPP_N_UINT64_M1 * 4)
#define  MIPP_N_UINT32_M4 ( MIPP_N_UINT32_M1 * 4)
#define  MIPP_N_UINT16_M4 ( MIPP_N_UINT16_M1 * 4)
#define   MIPP_N_UINT8_M4 (  MIPP_N_UINT8_M1 * 4)

#define MIPP_N_FLOAT64_M8 (MIPP_N_FLOAT64_M1 * 8)
#define MIPP_N_FLOAT32_M8 (MIPP_N_FLOAT32_M1 * 8)
#define   MIPP_N_INT64_M8 (  MIPP_N_INT64_M1 * 8)
#define   MIPP_N_INT32_M8 (  MIPP_N_INT32_M1 * 8)
#define   MIPP_N_INT16_M8 (  MIPP_N_INT16_M1 * 8)
#define    MIPP_N_INT8_M8 (   MIPP_N_INT8_M1 * 8)
#define  MIPP_N_UINT64_M8 ( MIPP_N_UINT64_M1 * 8)
#define  MIPP_N_UINT32_M8 ( MIPP_N_UINT32_M1 * 8)
#define  MIPP_N_UINT16_M8 ( MIPP_N_UINT16_M1 * 8)
#define   MIPP_N_UINT8_M8 (  MIPP_N_UINT8_M1 * 8)

#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RV_SIZE_BYTE) / (elmt_byte) * (m))

// ----------------------------- declaration of the data vector registers (rvd)

typedef __m256d rvd_float64_m1_t;
typedef __m256  rvd_float32_m1_t;
typedef __m256i rvd_int64_m1_t;
typedef __m256i rvd_int32_m1_t;
typedef __m256i rvd_int16_m1_t;
typedef __m256i rvd_int8_m1_t;
typedef __m256i rvd_uint64_m1_t;
typedef __m256i rvd_uint32_m1_t;
typedef __m256i rvd_uint16_m1_t;
typedef __m256i rvd_uint8_m1_t;

typedef rvd_float64_m1_t rvd_float64_t;
typedef rvd_float32_m1_t rvd_float32_t;
typedef rvd_int64_m1_t   rvd_int64_t;
typedef rvd_int32_m1_t   rvd_int32_t;
typedef rvd_int16_m1_t   rvd_int16_t;
typedef rvd_int8_m1_t    rvd_int8_t;
typedef rvd_uint64_m1_t  rvd_uint64_t;
typedef rvd_uint32_m1_t  rvd_uint32_t;
typedef rvd_uint16_m1_t  rvd_uint16_t;
typedef rvd_uint8_m1_t   rvd_uint8_t;

typedef struct { rvd_float64_m1_t sp1, sp2; } rvd_float64_m2_t;
typedef struct { rvd_float32_m1_t sp1, sp2; } rvd_float32_m2_t;
typedef struct { rvd_int64_m1_t   sp1, sp2; } rvd_int64_m2_t;
typedef struct { rvd_int32_m1_t   sp1, sp2; } rvd_int32_m2_t;
typedef struct { rvd_int16_m1_t   sp1, sp2; } rvd_int16_m2_t;
typedef struct { rvd_int8_m1_t    sp1, sp2; } rvd_int8_m2_t;
typedef struct { rvd_uint64_m1_t  sp1, sp2; } rvd_uint64_m2_t;
typedef struct { rvd_uint32_m1_t  sp1, sp2; } rvd_uint32_m2_t;
typedef struct { rvd_uint16_m1_t  sp1, sp2; } rvd_uint16_m2_t;
typedef struct { rvd_uint8_m1_t   sp1, sp2; } rvd_uint8_m2_t;

typedef struct { rvd_float64_m2_t sp1, sp2; } rvd_float64_m4_t;
typedef struct { rvd_float32_m2_t sp1, sp2; } rvd_float32_m4_t;
typedef struct { rvd_int64_m2_t   sp1, sp2; } rvd_int64_m4_t;
typedef struct { rvd_int32_m2_t   sp1, sp2; } rvd_int32_m4_t;
typedef struct { rvd_int16_m2_t   sp1, sp2; } rvd_int16_m4_t;
typedef struct { rvd_int8_m2_t    sp1, sp2; } rvd_int8_m4_t;
typedef struct { rvd_uint64_m2_t  sp1, sp2; } rvd_uint64_m4_t;
typedef struct { rvd_uint32_m2_t  sp1, sp2; } rvd_uint32_m4_t;
typedef struct { rvd_uint16_m2_t  sp1, sp2; } rvd_uint16_m4_t;
typedef struct { rvd_uint8_m2_t   sp1, sp2; } rvd_uint8_m4_t;

typedef struct { rvd_float64_m4_t sp1, sp2; } rvd_float64_m8_t;
typedef struct { rvd_float32_m4_t sp1, sp2; } rvd_float32_m8_t;
typedef struct { rvd_int64_m4_t   sp1, sp2; } rvd_int64_m8_t;
typedef struct { rvd_int32_m4_t   sp1, sp2; } rvd_int32_m8_t;
typedef struct { rvd_int16_m4_t   sp1, sp2; } rvd_int16_m8_t;
typedef struct { rvd_int8_m4_t    sp1, sp2; } rvd_int8_m8_t;
typedef struct { rvd_uint64_m4_t  sp1, sp2; } rvd_uint64_m8_t;
typedef struct { rvd_uint32_m4_t  sp1, sp2; } rvd_uint32_m8_t;
typedef struct { rvd_uint16_m4_t  sp1, sp2; } rvd_uint16_m8_t;
typedef struct { rvd_uint8_m4_t   sp1, sp2; } rvd_uint8_m8_t;

// ----------------------------- declaration of the mask vector registers (rvm)

typedef __m256d rvm_float64_m1_t;
typedef __m256  rvm_float32_m1_t;
typedef __m256i rvm_int64_m1_t;
typedef __m256i rvm_int32_m1_t;
typedef __m256i rvm_int16_m1_t;
typedef __m256i rvm_int8_m1_t;
typedef __m256i rvm_uint64_m1_t;
typedef __m256i rvm_uint32_m1_t;
typedef __m256i rvm_uint16_m1_t;
typedef __m256i rvm_uint8_m1_t;

typedef rvm_float64_m1_t rvm_float64_t;
typedef rvm_float32_m1_t rvm_float32_t;
typedef rvm_int64_m1_t   rvm_int64_t;
typedef rvm_int32_m1_t   rvm_int32_t;
typedef rvm_int16_m1_t   rvm_int16_t;
typedef rvm_int8_m1_t    rvm_int8_t;
typedef rvm_uint64_m1_t  rvm_uint64_t;
typedef rvm_uint32_m1_t  rvm_uint32_t;
typedef rvm_uint16_m1_t  rvm_uint16_t;
typedef rvm_uint8_m1_t   rvm_uint8_t;

typedef struct { rvm_float64_m1_t sp1, sp2; } rvm_float64_m2_t;
typedef struct { rvm_float32_m1_t sp1, sp2; } rvm_float32_m2_t;
typedef struct { rvm_int64_m1_t   sp1, sp2; } rvm_int64_m2_t;
typedef struct { rvm_int32_m1_t   sp1, sp2; } rvm_int32_m2_t;
typedef struct { rvm_int16_m1_t   sp1, sp2; } rvm_int16_m2_t;
typedef struct { rvm_int8_m1_t    sp1, sp2; } rvm_int8_m2_t;
typedef struct { rvm_uint64_m1_t  sp1, sp2; } rvm_uint64_m2_t;
typedef struct { rvm_uint32_m1_t  sp1, sp2; } rvm_uint32_m2_t;
typedef struct { rvm_uint16_m1_t  sp1, sp2; } rvm_uint16_m2_t;
typedef struct { rvm_uint8_m1_t   sp1, sp2; } rvm_uint8_m2_t;

typedef struct { rvm_float64_m2_t sp1, sp2; } rvm_float64_m4_t;
typedef struct { rvm_float32_m2_t sp1, sp2; } rvm_float32_m4_t;
typedef struct { rvm_int64_m2_t   sp1, sp2; } rvm_int64_m4_t;
typedef struct { rvm_int32_m2_t   sp1, sp2; } rvm_int32_m4_t;
typedef struct { rvm_int16_m2_t   sp1, sp2; } rvm_int16_m4_t;
typedef struct { rvm_int8_m2_t    sp1, sp2; } rvm_int8_m4_t;
typedef struct { rvm_uint64_m2_t  sp1, sp2; } rvm_uint64_m4_t;
typedef struct { rvm_uint32_m2_t  sp1, sp2; } rvm_uint32_m4_t;
typedef struct { rvm_uint16_m2_t  sp1, sp2; } rvm_uint16_m4_t;
typedef struct { rvm_uint8_m2_t   sp1, sp2; } rvm_uint8_m4_t;

typedef struct { rvm_float64_m4_t sp1, sp2; } rvm_float64_m8_t;
typedef struct { rvm_float32_m4_t sp1, sp2; } rvm_float32_m8_t;
typedef struct { rvm_int64_m4_t   sp1, sp2; } rvm_int64_m8_t;
typedef struct { rvm_int32_m4_t   sp1, sp2; } rvm_int32_m8_t;
typedef struct { rvm_int16_m4_t   sp1, sp2; } rvm_int16_m8_t;
typedef struct { rvm_int8_m4_t    sp1, sp2; } rvm_int8_m8_t;
typedef struct { rvm_uint64_m4_t  sp1, sp2; } rvm_uint64_m8_t;
typedef struct { rvm_uint32_m4_t  sp1, sp2; } rvm_uint32_m8_t;
typedef struct { rvm_uint16_m4_t  sp1, sp2; } rvm_uint16_m8_t;
typedef struct { rvm_uint8_m4_t   sp1, sp2; } rvm_uint8_m8_t;

// ---------------------------------------------------------------------- loadu
// ----------------------------------------------------------------------------

// --------------------------------------------------------------------- LMUL=1

rvd_float64_m1_t mipp_loadu_float64_m1(float64_t *mem_addr) { return (rvd_float64_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
rvd_float32_m1_t mipp_loadu_float32_m1(float32_t *mem_addr) { return (rvd_float32_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
  rvd_int64_m1_t   mipp_loadu_int64_m1(  int64_t *mem_addr) { return (  rvd_int64_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
  rvd_int32_m1_t   mipp_loadu_int32_m1(  int32_t *mem_addr) { return (  rvd_int32_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
  rvd_int16_m1_t   mipp_loadu_int16_m1(  int16_t *mem_addr) { return (  rvd_int16_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
   rvd_int8_m1_t    mipp_loadu_int8_m1(   int8_t *mem_addr) { return (   rvd_int8_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
 rvd_uint64_m1_t  mipp_loadu_uint64_m1( uint64_t *mem_addr) { return ( rvd_uint64_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
 rvd_uint32_m1_t  mipp_loadu_uint32_m1( uint32_t *mem_addr) { return ( rvd_uint32_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
 rvd_uint16_m1_t  mipp_loadu_uint16_m1( uint16_t *mem_addr) { return ( rvd_uint16_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }
  rvd_uint8_m1_t   mipp_loadu_uint8_m1(  uint8_t *mem_addr) { return (  rvd_uint8_m1_t) _mm256_loadu_ps((float32_t*) mem_addr); }

// ---------------------------------------------------------------------- ALIAS

rvd_float64_t mipp_loadu_float64(float64_t *mem_addr) { return mipp_loadu_float64_m1(mem_addr); }
rvd_float32_t mipp_loadu_float32(float32_t *mem_addr) { return mipp_loadu_float32_m1(mem_addr); }
  rvd_int64_t   mipp_loadu_int64(  int64_t *mem_addr) { return   mipp_loadu_int64_m1(mem_addr); }
  rvd_int32_t   mipp_loadu_int32(  int32_t *mem_addr) { return   mipp_loadu_int32_m1(mem_addr); }
  rvd_int16_t   mipp_loadu_int16(  int16_t *mem_addr) { return   mipp_loadu_int16_m1(mem_addr); }
   rvd_int8_t    mipp_loadu_int8(   int8_t *mem_addr) { return    mipp_loadu_int8_m1(mem_addr); }
 rvd_uint64_t  mipp_loadu_uint64( uint64_t *mem_addr) { return  mipp_loadu_uint64_m1(mem_addr); }
 rvd_uint32_t  mipp_loadu_uint32( uint32_t *mem_addr) { return  mipp_loadu_uint32_m1(mem_addr); }
 rvd_uint16_t  mipp_loadu_uint16( uint16_t *mem_addr) { return  mipp_loadu_uint16_m1(mem_addr); }
  rvd_uint8_t   mipp_loadu_uint8(  uint8_t *mem_addr) { return   mipp_loadu_uint8_m1(mem_addr); }

// --------------------------------------------------------------------- LMUL=2

rvd_float64_m2_t mipp_loadu_float64_m2(float64_t *mem_addr) { rvd_float64_m2_t rvd; rvd.sp1 = mipp_loadu_float64_m1(mem_addr); rvd.sp2 = mipp_loadu_float64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
rvd_float32_m2_t mipp_loadu_float32_m2(float32_t *mem_addr) { rvd_float32_m2_t rvd; rvd.sp1 = mipp_loadu_float32_m1(mem_addr); rvd.sp2 = mipp_loadu_float32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
  rvd_int64_m2_t   mipp_loadu_int64_m2(  int64_t *mem_addr) {   rvd_int64_m2_t rvd; rvd.sp1 =   mipp_loadu_int64_m1(mem_addr); rvd.sp2 =   mipp_loadu_int64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
  rvd_int32_m2_t   mipp_loadu_int32_m2(  int32_t *mem_addr) {   rvd_int32_m2_t rvd; rvd.sp1 =   mipp_loadu_int32_m1(mem_addr); rvd.sp2 =   mipp_loadu_int32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
  rvd_int16_m2_t   mipp_loadu_int16_m2(  int16_t *mem_addr) {   rvd_int16_m2_t rvd; rvd.sp1 =   mipp_loadu_int16_m1(mem_addr); rvd.sp2 =   mipp_loadu_int16_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
   rvd_int8_m2_t    mipp_loadu_int8_m2(   int8_t *mem_addr) {    rvd_int8_m2_t rvd; rvd.sp1 =    mipp_loadu_int8_m1(mem_addr); rvd.sp2 =    mipp_loadu_int8_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
 rvd_uint64_m2_t  mipp_loadu_uint64_m2( uint64_t *mem_addr) {  rvd_uint64_m2_t rvd; rvd.sp1 =  mipp_loadu_uint64_m1(mem_addr); rvd.sp2 =  mipp_loadu_uint64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
 rvd_uint32_m2_t  mipp_loadu_uint32_m2( uint32_t *mem_addr) {  rvd_uint32_m2_t rvd; rvd.sp1 =  mipp_loadu_uint32_m1(mem_addr); rvd.sp2 =  mipp_loadu_uint32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
 rvd_uint16_m2_t  mipp_loadu_uint16_m2( uint16_t *mem_addr) {  rvd_uint16_m2_t rvd; rvd.sp1 =  mipp_loadu_uint16_m1(mem_addr); rvd.sp2 =  mipp_loadu_uint16_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }
  rvd_uint8_m2_t   mipp_loadu_uint8_m2(  uint8_t *mem_addr) {   rvd_uint8_m2_t rvd; rvd.sp1 =   mipp_loadu_uint8_m1(mem_addr); rvd.sp2 =   mipp_loadu_uint8_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1)); return rvd; }

// --------------------------------------------------------------------- LMUL=4

rvd_float64_m4_t mipp_loadu_float64_m4(float64_t *mem_addr) { rvd_float64_m4_t rvd; rvd.sp1 = mipp_loadu_float64_m2(mem_addr); rvd.sp2 = mipp_loadu_float64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
rvd_float32_m4_t mipp_loadu_float32_m4(float32_t *mem_addr) { rvd_float32_m4_t rvd; rvd.sp1 = mipp_loadu_float32_m2(mem_addr); rvd.sp2 = mipp_loadu_float32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
  rvd_int64_m4_t   mipp_loadu_int64_m4(  int64_t *mem_addr) {   rvd_int64_m4_t rvd; rvd.sp1 =   mipp_loadu_int64_m2(mem_addr); rvd.sp2 =   mipp_loadu_int64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
  rvd_int32_m4_t   mipp_loadu_int32_m4(  int32_t *mem_addr) {   rvd_int32_m4_t rvd; rvd.sp1 =   mipp_loadu_int32_m2(mem_addr); rvd.sp2 =   mipp_loadu_int32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
  rvd_int16_m4_t   mipp_loadu_int16_m4(  int16_t *mem_addr) {   rvd_int16_m4_t rvd; rvd.sp1 =   mipp_loadu_int16_m2(mem_addr); rvd.sp2 =   mipp_loadu_int16_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
   rvd_int8_m4_t    mipp_loadu_int8_m4(   int8_t *mem_addr) {    rvd_int8_m4_t rvd; rvd.sp1 =    mipp_loadu_int8_m2(mem_addr); rvd.sp2 =    mipp_loadu_int8_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
 rvd_uint64_m4_t  mipp_loadu_uint64_m4( uint64_t *mem_addr) {  rvd_uint64_m4_t rvd; rvd.sp1 =  mipp_loadu_uint64_m2(mem_addr); rvd.sp2 =  mipp_loadu_uint64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
 rvd_uint32_m4_t  mipp_loadu_uint32_m4( uint32_t *mem_addr) {  rvd_uint32_m4_t rvd; rvd.sp1 =  mipp_loadu_uint32_m2(mem_addr); rvd.sp2 =  mipp_loadu_uint32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
 rvd_uint16_m4_t  mipp_loadu_uint16_m4( uint16_t *mem_addr) {  rvd_uint16_m4_t rvd; rvd.sp1 =  mipp_loadu_uint16_m2(mem_addr); rvd.sp2 =  mipp_loadu_uint16_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }
  rvd_uint8_m4_t   mipp_loadu_uint8_m4(  uint8_t *mem_addr) {   rvd_uint8_m4_t rvd; rvd.sp1 =   mipp_loadu_uint8_m2(mem_addr); rvd.sp2 =   mipp_loadu_uint8_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2)); return rvd; }

// --------------------------------------------------------------------- LMUL=8

rvd_float64_m8_t mipp_loadu_float64_m8(float64_t *mem_addr) { rvd_float64_m8_t rvd; rvd.sp1 = mipp_loadu_float64_m4(mem_addr); rvd.sp2 = mipp_loadu_float64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
rvd_float32_m8_t mipp_loadu_float32_m8(float32_t *mem_addr) { rvd_float32_m8_t rvd; rvd.sp1 = mipp_loadu_float32_m4(mem_addr); rvd.sp2 = mipp_loadu_float32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
  rvd_int64_m8_t   mipp_loadu_int64_m8(  int64_t *mem_addr) {   rvd_int64_m8_t rvd; rvd.sp1 =   mipp_loadu_int64_m4(mem_addr); rvd.sp2 =   mipp_loadu_int64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
  rvd_int32_m8_t   mipp_loadu_int32_m8(  int32_t *mem_addr) {   rvd_int32_m8_t rvd; rvd.sp1 =   mipp_loadu_int32_m4(mem_addr); rvd.sp2 =   mipp_loadu_int32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
  rvd_int16_m8_t   mipp_loadu_int16_m8(  int16_t *mem_addr) {   rvd_int16_m8_t rvd; rvd.sp1 =   mipp_loadu_int16_m4(mem_addr); rvd.sp2 =   mipp_loadu_int16_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
   rvd_int8_m8_t    mipp_loadu_int8_m8(   int8_t *mem_addr) {    rvd_int8_m8_t rvd; rvd.sp1 =    mipp_loadu_int8_m4(mem_addr); rvd.sp2 =    mipp_loadu_int8_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
 rvd_uint64_m8_t  mipp_loadu_uint64_m8( uint64_t *mem_addr) {  rvd_uint64_m8_t rvd; rvd.sp1 =  mipp_loadu_uint64_m4(mem_addr); rvd.sp2 =  mipp_loadu_uint64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
 rvd_uint32_m8_t  mipp_loadu_uint32_m8( uint32_t *mem_addr) {  rvd_uint32_m8_t rvd; rvd.sp1 =  mipp_loadu_uint32_m4(mem_addr); rvd.sp2 =  mipp_loadu_uint32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
 rvd_uint16_m8_t  mipp_loadu_uint16_m8( uint16_t *mem_addr) {  rvd_uint16_m8_t rvd; rvd.sp1 =  mipp_loadu_uint16_m4(mem_addr); rvd.sp2 =  mipp_loadu_uint16_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }
  rvd_uint8_m8_t   mipp_loadu_uint8_m8(  uint8_t *mem_addr) {   rvd_uint8_m8_t rvd; rvd.sp1 =   mipp_loadu_uint8_m4(mem_addr); rvd.sp2 =   mipp_loadu_uint8_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4)); return rvd; }

// --------------------------------------------------------------------- storeu
// ----------------------------------------------------------------------------

// --------------------------------------------------------------------- LMUL=1

void mipp_storeu_float64_m1(float64_t *mem_addr, rvd_float64_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void mipp_storeu_float32_m1(float32_t *mem_addr, rvd_float32_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void   mipp_storeu_int64_m1(  int64_t *mem_addr,   rvd_int64_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void   mipp_storeu_int32_m1(  int32_t *mem_addr,   rvd_int32_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void   mipp_storeu_int16_m1(  int16_t *mem_addr,   rvd_int16_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void    mipp_storeu_int8_m1(   int8_t *mem_addr,    rvd_int8_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void  mipp_storeu_uint64_m1( uint64_t *mem_addr,  rvd_uint64_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void  mipp_storeu_uint32_m1( uint32_t *mem_addr,  rvd_uint32_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void  mipp_storeu_uint16_m1( uint16_t *mem_addr,  rvd_uint16_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }
void   mipp_storeu_uint8_m1(  uint8_t *mem_addr,   rvd_uint8_m1_t rvd) { _mm256_storeu_ps((float32_t*) mem_addr, (rvd_float32_t) rvd); }

// ---------------------------------------------------------------------- ALIAS

void mipp_storeu_float64(float64_t *mem_addr, rvd_float64_t rvd) { mipp_storeu_float64_m1(mem_addr, rvd); }
void mipp_storeu_float32(float32_t *mem_addr, rvd_float32_t rvd) { mipp_storeu_float32_m1(mem_addr, rvd); }
void   mipp_storeu_int64(  int64_t *mem_addr,   rvd_int64_t rvd) {   mipp_storeu_int64_m1(mem_addr, rvd); }
void   mipp_storeu_int32(  int32_t *mem_addr,   rvd_int32_t rvd) {   mipp_storeu_int32_m1(mem_addr, rvd); }
void   mipp_storeu_int16(  int16_t *mem_addr,   rvd_int16_t rvd) {   mipp_storeu_int16_m1(mem_addr, rvd); }
void    mipp_storeu_int8(   int8_t *mem_addr,    rvd_int8_t rvd) {    mipp_storeu_int8_m1(mem_addr, rvd); }
void  mipp_storeu_uint64( uint64_t *mem_addr,  rvd_uint64_t rvd) {  mipp_storeu_uint64_m1(mem_addr, rvd); }
void  mipp_storeu_uint32( uint32_t *mem_addr,  rvd_uint32_t rvd) {  mipp_storeu_uint32_m1(mem_addr, rvd); }
void  mipp_storeu_uint16( uint16_t *mem_addr,  rvd_uint16_t rvd) {  mipp_storeu_uint16_m1(mem_addr, rvd); }
void   mipp_storeu_uint8(  uint8_t *mem_addr,   rvd_uint8_t rvd) {   mipp_storeu_uint8_m1(mem_addr, rvd); }

// --------------------------------------------------------------------- LMUL=2

void mipp_storeu_float64_m2(float64_t *mem_addr, rvd_float64_m2_t rvd) { mipp_storeu_float64_m1(mem_addr, rvd.sp1); mipp_storeu_float64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void mipp_storeu_float32_m2(float32_t *mem_addr, rvd_float32_m2_t rvd) { mipp_storeu_float32_m1(mem_addr, rvd.sp1); mipp_storeu_float32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void   mipp_storeu_int64_m2(  int64_t *mem_addr,   rvd_int64_m2_t rvd) {   mipp_storeu_int64_m1(mem_addr, rvd.sp1);   mipp_storeu_int64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void   mipp_storeu_int32_m2(  int32_t *mem_addr,   rvd_int32_m2_t rvd) {   mipp_storeu_int32_m1(mem_addr, rvd.sp1);   mipp_storeu_int32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void   mipp_storeu_int16_m2(  int16_t *mem_addr,   rvd_int16_m2_t rvd) {   mipp_storeu_int16_m1(mem_addr, rvd.sp1);   mipp_storeu_int16_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void    mipp_storeu_int8_m2(   int8_t *mem_addr,    rvd_int8_m2_t rvd) {    mipp_storeu_int8_m1(mem_addr, rvd.sp1);    mipp_storeu_int8_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void  mipp_storeu_uint64_m2( uint64_t *mem_addr,  rvd_uint64_m2_t rvd) {  mipp_storeu_uint64_m1(mem_addr, rvd.sp1);  mipp_storeu_uint64_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void  mipp_storeu_uint32_m2( uint32_t *mem_addr,  rvd_uint32_m2_t rvd) {  mipp_storeu_uint32_m1(mem_addr, rvd.sp1);  mipp_storeu_uint32_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void  mipp_storeu_uint16_m2( uint16_t *mem_addr,  rvd_uint16_m2_t rvd) {  mipp_storeu_uint16_m1(mem_addr, rvd.sp1);  mipp_storeu_uint16_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }
void   mipp_storeu_uint8_m2(  uint8_t *mem_addr,   rvd_uint8_m2_t rvd) {   mipp_storeu_uint8_m1(mem_addr, rvd.sp1);   mipp_storeu_uint8_m1(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 1), rvd.sp2); }

// --------------------------------------------------------------------- LMUL=4

void mipp_storeu_float64_m4(float64_t *mem_addr, rvd_float64_m4_t rvd) { mipp_storeu_float64_m2(mem_addr, rvd.sp1); mipp_storeu_float64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void mipp_storeu_float32_m4(float32_t *mem_addr, rvd_float32_m4_t rvd) { mipp_storeu_float32_m2(mem_addr, rvd.sp1); mipp_storeu_float32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void   mipp_storeu_int64_m4(  int64_t *mem_addr,   rvd_int64_m4_t rvd) {   mipp_storeu_int64_m2(mem_addr, rvd.sp1);   mipp_storeu_int64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void   mipp_storeu_int32_m4(  int32_t *mem_addr,   rvd_int32_m4_t rvd) {   mipp_storeu_int32_m2(mem_addr, rvd.sp1);   mipp_storeu_int32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void   mipp_storeu_int16_m4(  int16_t *mem_addr,   rvd_int16_m4_t rvd) {   mipp_storeu_int16_m2(mem_addr, rvd.sp1);   mipp_storeu_int16_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void    mipp_storeu_int8_m4(   int8_t *mem_addr,    rvd_int8_m4_t rvd) {    mipp_storeu_int8_m2(mem_addr, rvd.sp1);    mipp_storeu_int8_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void  mipp_storeu_uint64_m4( uint64_t *mem_addr,  rvd_uint64_m4_t rvd) {  mipp_storeu_uint64_m2(mem_addr, rvd.sp1);  mipp_storeu_uint64_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void  mipp_storeu_uint32_m4( uint32_t *mem_addr,  rvd_uint32_m4_t rvd) {  mipp_storeu_uint32_m2(mem_addr, rvd.sp1);  mipp_storeu_uint32_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void  mipp_storeu_uint16_m4( uint16_t *mem_addr,  rvd_uint16_m4_t rvd) {  mipp_storeu_uint16_m2(mem_addr, rvd.sp1);  mipp_storeu_uint16_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }
void   mipp_storeu_uint8_m4(  uint8_t *mem_addr,   rvd_uint8_m4_t rvd) {   mipp_storeu_uint8_m2(mem_addr, rvd.sp1);   mipp_storeu_uint8_m2(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 2), rvd.sp2); }

// --------------------------------------------------------------------- LMUL=8

void mipp_storeu_float64_m8(float64_t *mem_addr, rvd_float64_m8_t rvd) { mipp_storeu_float64_m4(mem_addr, rvd.sp1); mipp_storeu_float64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void mipp_storeu_float32_m8(float32_t *mem_addr, rvd_float32_m8_t rvd) { mipp_storeu_float32_m4(mem_addr, rvd.sp1); mipp_storeu_float32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void   mipp_storeu_int64_m8(  int64_t *mem_addr,   rvd_int64_m8_t rvd) {   mipp_storeu_int64_m4(mem_addr, rvd.sp1);   mipp_storeu_int64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void   mipp_storeu_int32_m8(  int32_t *mem_addr,   rvd_int32_m8_t rvd) {   mipp_storeu_int32_m4(mem_addr, rvd.sp1);   mipp_storeu_int32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void   mipp_storeu_int16_m8(  int16_t *mem_addr,   rvd_int16_m8_t rvd) {   mipp_storeu_int16_m4(mem_addr, rvd.sp1);   mipp_storeu_int16_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void    mipp_storeu_int8_m8(   int8_t *mem_addr,    rvd_int8_m8_t rvd) {    mipp_storeu_int8_m4(mem_addr, rvd.sp1);    mipp_storeu_int8_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void  mipp_storeu_uint64_m8( uint64_t *mem_addr,  rvd_uint64_m8_t rvd) {  mipp_storeu_uint64_m4(mem_addr, rvd.sp1);  mipp_storeu_uint64_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void  mipp_storeu_uint32_m8( uint32_t *mem_addr,  rvd_uint32_m8_t rvd) {  mipp_storeu_uint32_m4(mem_addr, rvd.sp1);  mipp_storeu_uint32_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void  mipp_storeu_uint16_m8( uint16_t *mem_addr,  rvd_uint16_m8_t rvd) {  mipp_storeu_uint16_m4(mem_addr, rvd.sp1);  mipp_storeu_uint16_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }
void   mipp_storeu_uint8_m8(  uint8_t *mem_addr,   rvd_uint8_m8_t rvd) {   mipp_storeu_uint8_m4(mem_addr, rvd.sp1);   mipp_storeu_uint8_m4(mem_addr + MIPP_LMUL_STRIDE(sizeof(*mem_addr), 4), rvd.sp2); }

// ------------------------------------------------------------------------ add
// ----------------------------------------------------------------------------

// --------------------------------------------------------------------- LMUL=1

rvd_float64_m1_t mipp_add_float64_m1(rvd_float64_m1_t rvd1, rvd_float64_m1_t rvd2) { return     _mm256_add_pd(rvd1, rvd2); }
rvd_float32_m1_t mipp_add_float32_m1(rvd_float32_m1_t rvd1, rvd_float32_m1_t rvd2) { return     _mm256_add_ps(rvd1, rvd2); }
#ifdef __AVX2__
  rvd_int64_m1_t   mipp_add_int64_m1(  rvd_int64_m1_t rvd1,   rvd_int64_m1_t rvd2) { return  _mm256_add_epi64(rvd1, rvd2); }
  rvd_int32_m1_t   mipp_add_int32_m1(  rvd_int32_m1_t rvd1,   rvd_int32_m1_t rvd2) { return  _mm256_add_epi32(rvd1, rvd2); }
  rvd_int16_m1_t   mipp_add_int16_m1(  rvd_int16_m1_t rvd1,   rvd_int16_m1_t rvd2) { return  _mm256_add_epi16(rvd1, rvd2); }
   rvd_int8_m1_t    mipp_add_int8_m1(   rvd_int8_m1_t rvd1,    rvd_int8_m1_t rvd2) { return   _mm256_add_epi8(rvd1, rvd2); }
 rvd_uint64_m1_t  mipp_add_uint64_m1( rvd_uint64_m1_t rvd1,  rvd_uint64_m1_t rvd2) { return  _mm256_add_epi64(rvd1, rvd2); }
 rvd_uint32_m1_t  mipp_add_uint32_m1( rvd_uint32_m1_t rvd1,  rvd_uint32_m1_t rvd2) { return  _mm256_add_epi32(rvd1, rvd2); }
 rvd_uint16_m1_t  mipp_add_uint16_m1( rvd_uint16_m1_t rvd1,  rvd_uint16_m1_t rvd2) { return _mm256_adds_epu16(rvd1, rvd2); }
  rvd_uint8_m1_t   mipp_add_uint8_m1(  rvd_uint8_m1_t rvd1,   rvd_uint8_m1_t rvd2) { return  _mm256_adds_epu8(rvd1, rvd2); }
#endif

// ---------------------------------------------------------------------- ALIAS

rvd_float64_t mipp_add_float64(rvd_float64_t rvd1, rvd_float64_t rvd2) { return mipp_add_float64_m1(rvd1, rvd2); }
rvd_float32_t mipp_add_float32(rvd_float32_t rvd1, rvd_float32_t rvd2) { return mipp_add_float32_m1(rvd1, rvd2); }
#ifdef __AVX2__
  rvd_int64_t   mipp_add_int64(  rvd_int64_t rvd1,   rvd_int64_t rvd2) { return   mipp_add_int64_m1(rvd1, rvd2); }
  rvd_int32_t   mipp_add_int32(  rvd_int32_t rvd1,   rvd_int32_t rvd2) { return   mipp_add_int32_m1(rvd1, rvd2); }
  rvd_int16_t   mipp_add_int16(  rvd_int16_t rvd1,   rvd_int16_t rvd2) { return   mipp_add_int16_m1(rvd1, rvd2); }
   rvd_int8_t    mipp_add_int8(   rvd_int8_t rvd1,    rvd_int8_t rvd2) { return    mipp_add_int8_m1(rvd1, rvd2); }
 rvd_uint64_t  mipp_add_uint64( rvd_uint64_t rvd1,  rvd_uint64_t rvd2) { return  mipp_add_uint64_m1(rvd1, rvd2); }
 rvd_uint32_t  mipp_add_uint32( rvd_uint32_t rvd1,  rvd_uint32_t rvd2) { return  mipp_add_uint32_m1(rvd1, rvd2); }
 rvd_uint16_t  mipp_add_uint16( rvd_uint16_t rvd1,  rvd_uint16_t rvd2) { return  mipp_add_uint16_m1(rvd1, rvd2); }
  rvd_uint8_t   mipp_add_uint8(  rvd_uint8_t rvd1,   rvd_uint8_t rvd2) { return   mipp_add_uint8_m1(rvd1, rvd2); }
#endif

// --------------------------------------------------------------------- LMUL=2

rvd_float64_m2_t mipp_add_float64_m2(rvd_float64_m2_t rvd1, rvd_float64_m2_t rvd2) { rvd_float64_m2_t rvd; rvd.sp1 = mipp_add_float64_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float64_m1(rvd1.sp2, rvd2.sp2); return rvd; }
rvd_float32_m2_t mipp_add_float32_m2(rvd_float32_m2_t rvd1, rvd_float32_m2_t rvd2) { rvd_float32_m2_t rvd; rvd.sp1 = mipp_add_float32_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float32_m1(rvd1.sp2, rvd2.sp2); return rvd; }
#ifdef __AVX2__
  rvd_int64_m2_t   mipp_add_int64_m2(  rvd_int64_m2_t rvd1,   rvd_int64_m2_t rvd2) {   rvd_int64_m2_t rvd; rvd.sp1 =   mipp_add_int64_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int64_m1(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int32_m2_t   mipp_add_int32_m2(  rvd_int32_m2_t rvd1,   rvd_int32_m2_t rvd2) {   rvd_int32_m2_t rvd; rvd.sp1 =   mipp_add_int32_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int32_m1(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int16_m2_t   mipp_add_int16_m2(  rvd_int16_m2_t rvd1,   rvd_int16_m2_t rvd2) {   rvd_int16_m2_t rvd; rvd.sp1 =   mipp_add_int16_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int16_m1(rvd1.sp2, rvd2.sp2); return rvd; }
   rvd_int8_m2_t    mipp_add_int8_m2(   rvd_int8_m2_t rvd1,    rvd_int8_m2_t rvd2) {    rvd_int8_m2_t rvd; rvd.sp1 =    mipp_add_int8_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =    mipp_add_int8_m1(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint64_m2_t  mipp_add_uint64_m2( rvd_uint64_m2_t rvd1,  rvd_uint64_m2_t rvd2) {  rvd_uint64_m2_t rvd; rvd.sp1 =  mipp_add_uint64_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint64_m1(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint32_m2_t  mipp_add_uint32_m2( rvd_uint32_m2_t rvd1,  rvd_uint32_m2_t rvd2) {  rvd_uint32_m2_t rvd; rvd.sp1 =  mipp_add_uint32_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint32_m1(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint16_m2_t  mipp_add_uint16_m2( rvd_uint16_m2_t rvd1,  rvd_uint16_m2_t rvd2) {  rvd_uint16_m2_t rvd; rvd.sp1 =  mipp_add_uint16_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint16_m1(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_uint8_m2_t   mipp_add_uint8_m2(  rvd_uint8_m2_t rvd1,   rvd_uint8_m2_t rvd2) {   rvd_uint8_m2_t rvd; rvd.sp1 =   mipp_add_uint8_m1(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_uint8_m1(rvd1.sp2, rvd2.sp2); return rvd; }
#endif

// --------------------------------------------------------------------- LMUL=4

rvd_float64_m4_t mipp_add_float64_m4(rvd_float64_m4_t rvd1, rvd_float64_m4_t rvd2) { rvd_float64_m4_t rvd; rvd.sp1 = mipp_add_float64_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float64_m2(rvd1.sp2, rvd2.sp2); return rvd; }
rvd_float32_m4_t mipp_add_float32_m4(rvd_float32_m4_t rvd1, rvd_float32_m4_t rvd2) { rvd_float32_m4_t rvd; rvd.sp1 = mipp_add_float32_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float32_m2(rvd1.sp2, rvd2.sp2); return rvd; }
#ifdef __AVX2__
  rvd_int64_m4_t   mipp_add_int64_m4(  rvd_int64_m4_t rvd1,   rvd_int64_m4_t rvd2) {   rvd_int64_m4_t rvd; rvd.sp1 =   mipp_add_int64_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int64_m2(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int32_m4_t   mipp_add_int32_m4(  rvd_int32_m4_t rvd1,   rvd_int32_m4_t rvd2) {   rvd_int32_m4_t rvd; rvd.sp1 =   mipp_add_int32_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int32_m2(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int16_m4_t   mipp_add_int16_m4(  rvd_int16_m4_t rvd1,   rvd_int16_m4_t rvd2) {   rvd_int16_m4_t rvd; rvd.sp1 =   mipp_add_int16_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int16_m2(rvd1.sp2, rvd2.sp2); return rvd; }
   rvd_int8_m4_t    mipp_add_int8_m4(   rvd_int8_m4_t rvd1,    rvd_int8_m4_t rvd2) {    rvd_int8_m4_t rvd; rvd.sp1 =    mipp_add_int8_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =    mipp_add_int8_m2(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint64_m4_t  mipp_add_uint64_m4( rvd_uint64_m4_t rvd1,  rvd_uint64_m4_t rvd2) {  rvd_uint64_m4_t rvd; rvd.sp1 =  mipp_add_uint64_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint64_m2(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint32_m4_t  mipp_add_uint32_m4( rvd_uint32_m4_t rvd1,  rvd_uint32_m4_t rvd2) {  rvd_uint32_m4_t rvd; rvd.sp1 =  mipp_add_uint32_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint32_m2(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint16_m4_t  mipp_add_uint16_m4( rvd_uint16_m4_t rvd1,  rvd_uint16_m4_t rvd2) {  rvd_uint16_m4_t rvd; rvd.sp1 =  mipp_add_uint16_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint16_m2(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_uint8_m4_t   mipp_add_uint8_m4(  rvd_uint8_m4_t rvd1,   rvd_uint8_m4_t rvd2) {   rvd_uint8_m4_t rvd; rvd.sp1 =   mipp_add_uint8_m2(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_uint8_m2(rvd1.sp2, rvd2.sp2); return rvd; }
#endif

// --------------------------------------------------------------------- LMUL=8

rvd_float64_m8_t mipp_add_float64_m8(rvd_float64_m8_t rvd1, rvd_float64_m8_t rvd2) { rvd_float64_m8_t rvd; rvd.sp1 = mipp_add_float64_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float64_m4(rvd1.sp2, rvd2.sp2); return rvd; }
rvd_float32_m8_t mipp_add_float32_m8(rvd_float32_m8_t rvd1, rvd_float32_m8_t rvd2) { rvd_float32_m8_t rvd; rvd.sp1 = mipp_add_float32_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 = mipp_add_float32_m4(rvd1.sp2, rvd2.sp2); return rvd; }
#ifdef __AVX2__
  rvd_int64_m8_t   mipp_add_int64_m8(  rvd_int64_m8_t rvd1,   rvd_int64_m8_t rvd2) {   rvd_int64_m8_t rvd; rvd.sp1 =   mipp_add_int64_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int64_m4(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int32_m8_t   mipp_add_int32_m8(  rvd_int32_m8_t rvd1,   rvd_int32_m8_t rvd2) {   rvd_int32_m8_t rvd; rvd.sp1 =   mipp_add_int32_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int32_m4(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_int16_m8_t   mipp_add_int16_m8(  rvd_int16_m8_t rvd1,   rvd_int16_m8_t rvd2) {   rvd_int16_m8_t rvd; rvd.sp1 =   mipp_add_int16_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_int16_m4(rvd1.sp2, rvd2.sp2); return rvd; }
   rvd_int8_m8_t    mipp_add_int8_m8(   rvd_int8_m8_t rvd1,    rvd_int8_m8_t rvd2) {    rvd_int8_m8_t rvd; rvd.sp1 =    mipp_add_int8_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =    mipp_add_int8_m4(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint64_m8_t  mipp_add_uint64_m8( rvd_uint64_m8_t rvd1,  rvd_uint64_m8_t rvd2) {  rvd_uint64_m8_t rvd; rvd.sp1 =  mipp_add_uint64_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint64_m4(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint32_m8_t  mipp_add_uint32_m8( rvd_uint32_m8_t rvd1,  rvd_uint32_m8_t rvd2) {  rvd_uint32_m8_t rvd; rvd.sp1 =  mipp_add_uint32_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint32_m4(rvd1.sp2, rvd2.sp2); return rvd; }
 rvd_uint16_m8_t  mipp_add_uint16_m8( rvd_uint16_m8_t rvd1,  rvd_uint16_m8_t rvd2) {  rvd_uint16_m8_t rvd; rvd.sp1 =  mipp_add_uint16_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =  mipp_add_uint16_m4(rvd1.sp2, rvd2.sp2); return rvd; }
  rvd_uint8_m8_t   mipp_add_uint8_m8(  rvd_uint8_m8_t rvd1,   rvd_uint8_m8_t rvd2) {   rvd_uint8_m8_t rvd; rvd.sp1 =   mipp_add_uint8_m4(rvd1.sp1, rvd2.sp1); rvd.sp2 =   mipp_add_uint8_m4(rvd1.sp2, rvd2.sp2); return rvd; }
#endif