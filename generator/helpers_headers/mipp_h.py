from jinja2 import Template, StrictUndefined

def generate_mipp_h():

	file = open("../include/mipp.h", "w")

	template_file = """#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef double float64_t;
typedef float float32_t;

// ------------------------------------------------------------------------------------------------- includes files

#include "scalar/mipp_impl_scalar_gen.h"

#if !defined(MIPP_SCALAR)
	#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
		#include "avx512/mipp_impl_avx512_gen.h"
	#endif
	#if defined(__AVX__)
		#include "avx/mipp_impl_avx_gen.h"
	#endif
	#if defined(__SSE__)
		#include "sse/mipp_impl_sse_gen.h"
	#endif
	#if defined(__ARM_FEATURE_SVE)
		#include "sve/mipp_impl_sve_gen.h"
	#endif
	#if defined(__riscv_v_intrinsic)
		#include "rvv/mipp_impl_rvv_gen.h"
	#endif
	#if defined(__ARM_NEON__) || defined(__ARM_NEON)
		#include "neon/mipp_impl_neon_gen.h"
	#endif

	// utiles pour l'instant pour les tests
	// pourrait clairement etre utile pour les generateurs au dela du if #define

	#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
		#define MIPP_FOUND
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
		#define MIPP_FOUND
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
		#define MIPP_FOUND
		#define MIPP_SSE
		#ifdef __SSE2__
			#define MIPP_64BIT
			#define MIPP_BW
		#endif
	#elif defined(__ARM_FEATURE_SVE)
		#define MIPP_FOUND
		#define MIPP_SVE
		#define MIPP_FMA
		#define MIPP_64BIT
		// not yet generated
		// #define MIPP_BW
		#define MIPP_INSTR_VERSION 1
	#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
		#define MIPP_FOUND
		#define MIPP_NEON
		#define MIPP_BW
		#if defined(__ARM_FEATURE_FMA)
			#define MIPP_FMA
		#endif
		#if defined(__aarch64__)
			#define MIPP_64BIT
			#define MIPP_INSTR_VERSION 2
		#else
			#define MIPP_INSTR_VERSION 1
		#endif
	#elif defined(__riscv_v_intrinsic)
		#define MIPP_FOUND
		#define MIPP_RVV
		#define MIPP_64BIT
		#define MIPP_BW
	#endif
#endif // !defined(MIPP_SCALAR)

#if !defined(MIPP_FOUND) // MIPP_SCALAR case
	#define MIPP_FOUND
	#if !defined(MIPP_SCALAR)
		#define MIPP_SCALAR
	#endif
	#define MIPP_64BIT
	#define MIPP_BW
#endif

// end utiles pour l'instant pour les tests...

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */"""

	j2_template = Template(template_file, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	file.close()