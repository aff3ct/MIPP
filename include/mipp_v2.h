
#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP



#include <stdint.h>

typedef double float64_t;
typedef float float32_t;


#if defined(__AVX__)
// RG a l'envers
#include "avx/mipp_v2_impl_AVX_gen.h"
#include "avx/mipp_v2_AVX_gen.hpp"
#endif


#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
const std::string InstructionType = "AVX512";
	#define MIPP_AVX512

	#define MIPP_REQUIRED_ALIGNMENT 64
	#define MIPP_64BIT

	const std::string InstructionFullType = InstructionType;
	const std::string InstructionVersion  = "1";

	#define MIPP_INSTR_VERSION 1
	#define MIPP_REGISTER_SIZE 512
	#define MIPP_LANES 4

#ifdef __AVX512BW__
	using msk   = __mmask64;
#else
	using msk   = __mmask16;
#endif
	using reg   = __m512;

	template <int N>
	//inline rvd<T,N> toreg(const rvm<T,N> m)
	inline reg toreg(const msk m) {
		throw std::runtime_error("mipp: Invalid mask size 'N' = " + std::to_string(N) + ".");
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
#if defined(__MIC__) || defined(__KNCNI__)
		ext.push_back("KNC");
#endif
#ifdef __AVX512F__
		ext.push_back("F");
#endif
#ifdef __AVX512BW__
		ext.push_back("BW");
#endif
#ifdef __AVX512CD__
		ext.push_back("CD");
#endif
#ifdef __AVX512ER__
		ext.push_back("ER");
#endif
#ifdef __AVX512PF__
		ext.push_back("PF");
#endif
#ifdef __AVX512DQ__
		ext.push_back("DQ");
#endif
#ifdef __AVX512VL__
		ext.push_back("VL");
#endif
		return ext;
	}
// -------------------------------------------------------------------------------------------------------- X86 AVX-256
#elif defined(__AVX__)
	const std::string InstructionType = "AVX";
	#define MIPP_AVX

	#define MIPP_REQUIRED_ALIGNMENT 32
	#define MIPP_64BIT
#ifdef __AVX2__
	const std::string InstructionFullType = InstructionType + "2";
	const std::string InstructionVersion  = "2";
	#define MIPP_AVX2
	#define MIPP_INSTR_VERSION 2
	#define MIPP_BW
#else
	const std::string InstructionFullType = InstructionType;
	const std::string InstructionVersion  = "1";
	#define MIPP_AVX1
	#define MIPP_INSTR_VERSION 1
#endif
	#define MIPP_REGISTER_SIZE 256
	#define MIPP_LANES 2

	using msk   = __m256i;
	using reg   = __m256;
	using reg_2 = __m128; // half a full register

	template <int N>
	//inline rvd<T,N> toreg(const rvm<T,N> m)
	inline reg toreg(const msk m) {
		return _mm256_castsi256_ps(m);
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
#ifdef __FMA__
		ext.push_back("FMA");
#endif
		return ext;
	}
// ------------------------------------------------------------------------------------------------- MIPP_NO_INTRINSICS
#else
	const std::string InstructionType     = "NO";
	#define MIPP_NO

	const std::string InstructionFullType = "NO_INTRINSICS";
	const std::string InstructionVersion  = "1";

#define MIPP_REQUIRED_ALIGNMENT 1
#if UINTPTR_MAX == 0xffffffffffffffff
#define MIPP_64BIT
#endif
	#define MIPP_BW
	#define MIPP_INSTR_VERSION 1
	#define MIPP_REGISTER_SIZE 0
	#define MIPP_LANES 1

	using msk   = uint8_t;
	using reg   = uint32_t;
	using reg_2 = uint16_t;

	template <int N>
	inline reg toreg(const msk m) {
		return (reg)m;
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
		return ext;
	}
#endif

// ------------------------------------------------------------------------------------------------- includes files
#include "mipp_v2_tools.h"
#include "mipp_operator_v2_gen.hpp"
#include "mipp_v2_func_gen.h"


#ifndef MIPP_NO_INTRINSICS
// -------------------------------------------------------------------------------------------------------- X86 AVX-512
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
#include "avx/mipp_v2_impl_AVX512_gen.h"
#include "avx/mipp_v2_AVX512_gen.hpp"
// -------------------------------------------------------------------------------------------------------- X86 AVX-256
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__AVX__)
#include "avx/mipp_v2_impl_AVX_gen.h"
#include "avx/mipp_v2_AVX_gen.hpp"


#endif

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */