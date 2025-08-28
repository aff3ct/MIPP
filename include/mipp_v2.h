
#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP



#include <stdint.h>
#include <iostream>
#include <cstdlib>

typedef double float64_t;
typedef float float32_t;

#ifndef MIPP_NO_INTRINSICS


#if defined(__AVX__)

// utiles pour l'instant pour les tests
// pourrait clairement etre utile pour les generateurs au dela du if #define
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
// end utiles pour l'instant pour les tests...

#include "avx/mipp_v2_impl_AVX_gen.h"

#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)

// utiles pour l'instant pour les tests
// pourrait clairement etre utile pour les generateurs au dela du if #define
// idem __AVX512F__ __AVX512VBMI__ ...
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
// end utiles pour l'instant pour les tests...

#include "avx512/mipp_v2_impl_AVX512_gen.h"

#elif defined(__SSE__)
// utiles pour l'instant pour les tests
// pourrait clairement etre utile pour les generateurs au dela du if #define
	#define MIPP_SSE
#ifdef __SSE2__
	#define MIPP_64BIT
	#define MIPP_BW
#endif
// end utiles pour l'instant pour les tests...

#include "sse/mipp_v2_impl_SSE_gen.h"

#endif

// ------------------------------------------------------------------------------------------------- MIPP_NO_INTRINSICS
#else
// do something
#endif

// -------------------------------------------------------------------------------------------------- complex functions
// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------- includes files

#include "mipp_v2.hpp"

#include "mipp_v2_object_gen.hpp"

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */
