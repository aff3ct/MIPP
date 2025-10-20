#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#include <stdint.h>
#include <iostream>
#include <cstdlib>

typedef double float64_t;
typedef float float32_t;

// ------------------------------------------------------------------------------------------------- includes files

#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
#include "avx512/mipp_v2_impl_AVX512_gen.h"
#endif
#if defined(__AVX__)
#include "avx/mipp_v2_impl_AVX_gen.h"
#endif

#if defined(__SSE__)
#include "sse/mipp_v2_impl_SSE_gen.h"
#endif

#if defined(__ARM_FEATURE_SVE)
#include "sve/mipp_v2_impl_SVE_gen.h"
#endif

#include "mipp_v2.hpp"

#include "mipp_v2_object_gen.hpp"

// utiles pour l'instant pour les tests
// pourrait clairement etre utile pour les generateurs au dela du if #define

#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
	#define MIPP_AVX512
	#define MIPP_INSTR_VERSION 1
	#define MIPP_64BIT
#ifdef __AVX512BW__
	#define MIPP_BW
#endif
#ifdef __AVX512VBMI2__
	#define MIPP_BMI2
#endif
#ifdef __FMA__
	#define MIPP_FMA
#endif

#elif defined(__AVX__)
    #define MIPP_AVX
	#define MIPP_64BIT
#ifdef __AVX2__
    #define MIPP_AVX2
	#define MIPP_INSTR_VERSION 2
	#define MIPP_BW
#else
	#define MIPP_INSTR_VERSION 1
#endif
#ifdef __BMI2__
	#define MIPP_BMI2
#endif
#ifdef __FMA__
	#define MIPP_FMA
#endif

#elif defined(__SSE__)
	#define MIPP_SSE
#ifdef __SSE2__
	#define MIPP_64BIT
	#define MIPP_BW
#endif

#elif defined(__ARM_FEATURE_SVE)
#define MIPP_FMA
#define MIPP_64BIT
// not yet generated
//#define MIPP_BW
#define MIPP_INSTR_VERSION 1
#endif

// end utiles pour l'instant pour les tests...

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */
