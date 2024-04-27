/*
The MIT License (MIT)

Copyright (c) 2016 MIPP

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 * mipp.h
 *
 *  Created on: 5 oct. 2014
 *      Author: Adrien Cassagne
 */

#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#define MIPP

#ifndef MIPP_NO_INTRINSICS
#if defined(__ARM_FEATURE_SVE)
#include <arm_sve.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#include "math/neon_mathfun.h"
#elif defined(__SSE__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
// header for special functions: log, exp, sin, cos
#if !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC)
#if defined(__AVX512F__)
#include "math/avx512_mathfun.h"
#elif defined(__AVX__)
#include "math/avx_mathfun.h"
#elif defined(__SSE__)
#include "math/sse_mathfun.h"
#endif
#endif
#include <immintrin.h>
#ifdef __SSE__
#include <xmmintrin.h>
#endif
#ifdef __SSE2__
#include <emmintrin.h>
#endif
#ifdef __SSE3__
#include <pmmintrin.h>
#endif
#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
#ifdef __SSE4_1__
#include <smmintrin.h>
#endif
#else
#include "mipp_scalar_op.h"
#endif
#else
#include "mipp_scalar_op.h"
#endif

#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <map>

#if (defined(__GNUC__) || defined(__clang__) || defined(__llvm__)) && (defined(__linux__) || defined(__linux) || defined(__APPLE__)) && !defined(__ANDROID__)
#include <execinfo.h>
#include <unistd.h>
#endif

#ifdef _MSC_VER
#ifndef NOMINMAX
#define NOMINMAX
#endif
#undef min
#undef max
#endif

namespace mipp // My Intrinsics Plus Plus => mipp
{
// ------------------------------------------------------------------------------------------ myIntrinsics vector sizes
// --------------------------------------------------------------------------------------------------------------------
#ifndef MIPP_NO_INTRINSICS

// ------------------------------------------------------------------- ARM SVE (specific size in 128-256-512-1024-2048)
// ------------------------------------------------- Size is specified at compilation time using flag -msve-vector-bits
#if defined(__ARM_FEATURE_SVE)
#if __ARM_FEATURE_SVE_BITS
#define MIPP_REGISTER_SIZE __ARM_FEATURE_SVE_BITS
typedef svfloat32_t fixed_float32_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svfloat64_t fixed_float64_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint32_t fixed_int32_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));
typedef svint64_t fixed_int64_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));

typedef svbool_t fixed_bool_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));

#else
#error Only -msve-vector-bits = 128-256-512-1024-2048 is supported
#endif
const std::string InstructionType = "SVE-LS";
#define MIPP_SVE_LS

#define MIPP_FMA
#define MIPP_REQUIRED_ALIGNMENT 16
#define MIPP_64BIT

// activate when generator ok
//#define MIPP_BW

const std::string InstructionFullType = InstructionType;
const std::string InstructionVersion  = "1";

#define MIPP_INSTR_VERSION 1
#define MIPP_LANES 4

using msk   = fixed_bool_t;
using reg   = fixed_float32_t;
using reg_2 = fixed_int32_t; // half a full register (information is in the lower part of the 128 bit register)

template <int N>
inline reg toreg(const msk m) {
	throw std::runtime_error("mipp: Invalid mask size 'N' = " + std::to_string(N) + ".");
}

inline std::vector<std::string> InstructionExtensions()
{
	std::vector<std::string> ext;
	ext.push_back("SVE_LS");
	ext.push_back("FMA");
	return ext;
}

// ------------------------------------------------------------------------------------------------------- ARM NEON-128
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
	const std::string InstructionType = "NEON";
	#define MIPP_NEON

	#define MIPP_REQUIRED_ALIGNMENT 16
#ifdef __aarch64__
	const std::string InstructionFullType = InstructionType + "v2";
	const std::string InstructionVersion  = "2";
	#define MIPP_NEONV2
	#define MIPP_INSTR_VERSION 2
	#define MIPP_64BIT
#else
	const std::string InstructionFullType = InstructionType + "v1";
	const std::string InstructionVersion  = "1";
	#define MIPP_NEONV1
	#define MIPP_INSTR_VERSION 1
#endif
#ifdef __ARM_FEATURE_FMA
	#define MIPP_FMA
#endif

	#define MIPP_BW
	#define MIPP_REGISTER_SIZE 128
	#define MIPP_LANES 1

	using msk   = uint32x4_t;
	using reg   = float32x4_t;
	using reg_2 = float32x2_t; // half a full register

	template <int N>
	inline reg toreg(const msk m) {
		return (reg)m;
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
#ifdef __ARM_FEATURE_FMA
		ext.push_back("FMA");
#endif
		return ext;
	}

// -------------------------------------------------------------------------------------------------------- X86 AVX-512
#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
	const std::string InstructionType = "AVX512";
	#define MIPP_AVX512

	#define MIPP_REQUIRED_ALIGNMENT 64
	#define MIPP_64BIT

#if defined(__MIC__) || defined(__KNCNI__)
	#define MIPP_AVX512KNC
#endif
#ifdef __AVX512F__
	#define MIPP_AVX512F
#endif
#ifdef __AVX512BW__
	#define MIPP_AVX512BW
	#define MIPP_BW
#endif
#ifdef __AVX512CD__
	#define MIPP_AVX512CD
#endif
#ifdef __AVX512ER__
	#define MIPP_AVX512ER
#endif
#ifdef __AVX512PF__
	#define MIPP_AVX512PF
#endif
#ifdef __AVX512DQ__
	#define MIPP_AVX512DQ
#endif
#ifdef __AVX512VL__
	#define MIPP_AVX512VL
#endif
#ifdef __AVX512VBMI__
	#define MIPP_AVX512VBMI
#endif
#ifdef __AVX512VBMI2__
	#define MIPP_AVX512VBMI2
#endif
#ifdef __FMA__
	#define MIPP_FMA
#endif

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
	using reg_2 = __m256; // half a full register

	template <int N>
	inline reg toreg(const msk m) {
		throw std::runtime_error("mipp: Invalid mask size 'N' = " + std::to_string(N) + ".");
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
		ext.push_back("FMA");
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
#ifdef __AVX512VBMI__
		ext.push_back("VBMI");
#endif
#ifdef __AVX512VBMI2__
		ext.push_back("VBMI2");
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
#ifdef __BMI2__
	#define MIPP_BMI2
#endif
#ifdef __FMA__
	#define MIPP_FMA
#endif

	#define MIPP_REGISTER_SIZE 256
	#define MIPP_LANES 2

	using msk   = __m256i;
	using reg   = __m256;
	using reg_2 = __m128; // half a full register

	template <int N>
	inline reg toreg(const msk m) {
		return _mm256_castsi256_ps(m);
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
#ifdef __FMA__
		ext.push_back("FMA");
#endif
#ifdef __BMI2__
	ext.push_back("BMI2");
#endif
		return ext;
	}

// -------------------------------------------------------------------------------------------------------- X86 SSE-128
#elif defined(__SSE__)
	const std::string InstructionType = "SSE";
	#define MIPP_SSE

	#define MIPP_REQUIRED_ALIGNMENT 16
#ifdef __SSE2__
	#define MIPP_64BIT
	#define MIPP_BW
#endif
#ifdef __SSE4_2__
	const std::string InstructionFullType = InstructionType + "4.2";
	const std::string InstructionVersion  = "4.2";
	#define MIPP_SSE4_2
	#define MIPP_INSTR_VERSION 42
#elif defined(__SSE4_1__)
	const std::string InstructionFullType = InstructionType + "4.1";
	const std::string InstructionVersion  = "4.1";
	#define MIPP_SSE4_1
	#define MIPP_INSTR_VERSION 41
#elif defined(__SSSE3__)
	const std::string InstructionFullType = "SSSE3";
	const std::string InstructionVersion  = "3";
	#define MIPP_SSSE3
	#define MIPP_INSTR_VERSION 31
#elif defined(__SSE3__)
	const std::string InstructionFullType = InstructionType + "3";
	const std::string InstructionVersion  = "3";
	#define MIPP_SSE3
	#define MIPP_INSTR_VERSION 3
#elif defined(__SSE2__)
	const std::string InstructionFullType = InstructionType + "2";
	const std::string InstructionVersion  = "2";
	#define MIPP_SSE2
	#define MIPP_INSTR_VERSION 2
#else
	const std::string InstructionFullType = InstructionType;
	const std::string InstructionVersion  = "1";
	#define MIPP_SSE1
	#define MIPP_INSTR_VERSION 1
#endif
#ifdef __FMA__
	#define MIPP_FMA
#endif
#ifdef __BMI2__
	#define MIPP_BMI2
#endif

	#define MIPP_REGISTER_SIZE 128
	#define MIPP_LANES 1

	using msk   = __m128i;
	using reg   = __m128;
	using reg_2 = __m128d; // half a full register (information is in the lower part of the 128 bit register)

	template <int N>
	inline reg toreg(const msk m) {
		return _mm_castsi128_ps(m);
	}

	inline std::vector<std::string> InstructionExtensions()
	{
		std::vector<std::string> ext;
#ifdef __FMA__
		ext.push_back("FMA");
#endif
#ifdef __BMI2__
		ext.push_back("BMI2");
#endif
		return ext;
	}

// ------------------------------------------------------------------------------------------------- MIPP_NO_INTRINSICS
#else
	const std::string InstructionType = "NO";
	#define MIPP_NO

	const std::string InstructionFullType = "NO_INTRINSICS";
	const std::string InstructionVersion  = "1";

	#define MIPP_NO_INTRINSICS
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

constexpr uint32_t RequiredAlignment = MIPP_REQUIRED_ALIGNMENT;
constexpr uint32_t RegisterSizeBit   = MIPP_REGISTER_SIZE;
constexpr uint32_t Lanes             = MIPP_LANES;

#ifdef MIPP_64BIT
const bool Support64Bit = true;
#else
const bool Support64Bit = false;
#endif
#ifdef MIPP_BW
const bool SupportByteWord = true;
#else
const bool SupportByteWord = false;
#endif

typedef struct regx2 { reg val[2]; } regx2;

template <typename T>
constexpr int32_t nElmtsPerRegister()
{
#ifdef MIPP_NO_INTRINSICS
	return 1;
#else
	return RegisterSizeBit / (8 * sizeof(T));
#endif
}

template <typename T>
constexpr int32_t nElReg()
{
#ifdef MIPP_NO_INTRINSICS
	return 1;
#else
	return RegisterSizeBit / (8 * sizeof(T));
#endif
}

template <typename T>
constexpr int32_t N()
{
#ifndef MIPP_NO_INTRINSICS
	return mipp::nElReg<T>();
#else
	return 1;
#endif
}

template <typename T>
inline bool isAligned(const T *ptr)
{
#ifdef MIPP_ALIGNED_LOADS
	return RegisterSizeBit >= 8 ? (((uintptr_t)ptr) % (RegisterSizeBit / 8)) == 0 : true;
#else
	return true;
#endif
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------- memory allocator

template <typename T>
T* malloc(uint32_t nData)
{
	T* ptr = nullptr;

#if !defined(MIPP_NO_INTRINSICS) && (defined(__SSE2__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__))
	ptr = (T*)_mm_malloc(nData * sizeof(T), mipp::RequiredAlignment);
#else
	ptr = (T*)std::malloc((size_t)(sizeof(T) * nData));
#endif

	return ptr;
}

template <typename T>
void free(T* ptr)
{
#if !defined(MIPP_NO_INTRINSICS) && (defined(__SSE2__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__))
	_mm_free(ptr);
#else
	std::free(ptr);
#endif
}

template <class T>
struct allocator
{
	typedef T value_type;
	allocator() { }
	template <class C> allocator(const allocator<C>& other) { }
	T* allocate(std::size_t n) { return mipp::malloc<T>((int)n); }
	void deallocate(T* p, std::size_t n) { mipp::free<T>(p); }
};

// returns true if and only if storage allocated from ma1 can be deallocated from ma2, and vice versa.
// always returns true for stateless allocators.
template <class C1, class C2>
bool operator==(const allocator<C1>& ma1, const allocator<C2>& ma2) { return true; }

template <class C1, class C2>
bool operator!=(const allocator<C1>& ma1, const allocator<C2>& ma2) { return !(ma1 == ma2); }

// override vector type
template<class T> using vector = std::vector<T, allocator<T>>;

// --------------------------------------------------------------------------------------------------- memory allocator
// --------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------- myIntrinsics prototypes
// --------------------------------------------------------------------------------------------------------------------

static inline std::string get_back_trace()
{
	std::string bt_str;
#if defined(MIPP_ENABLE_BACKTRACE) && (defined(__GNUC__) || defined(__clang__) || defined(__llvm__)) && (defined(__linux__) || defined(__linux) || defined(__APPLE__)) && !defined(__ANDROID__)
	const int bt_max_depth = 32;
	void *bt_array[bt_max_depth];

	size_t size = backtrace(bt_array, bt_max_depth);
	char** bt_symbs = backtrace_symbols(bt_array, size);

	bt_str += "\nBacktrace:";
	for (size_t i = 0; i < size; i++)
		bt_str += "\n" + std::string(bt_symbs[i]);
	free(bt_symbs);
#endif

	return bt_str;
}

template <typename T>
static inline void errorMessage(std::string instr)
{
	// define type names
	std::unordered_map<std::type_index,std::string> type_names;
	type_names[typeid(int8_t)  ] = "int8_t";
	type_names[typeid(uint8_t) ] = "uint8_t";
	type_names[typeid(int16_t) ] = "int16_t";
	type_names[typeid(uint16_t)] = "uint16_t";
	type_names[typeid(int32_t) ] = "int32_t";
	type_names[typeid(uint32_t)] = "uint32_t";
	type_names[typeid(int64_t) ] = "int64_t";
	type_names[typeid(uint64_t)] = "uint64_t";
	type_names[typeid(float)   ] = "float";
	type_names[typeid(double)  ] = "double";

	std::string message;
#if __cplusplus >= 201703L
	if constexpr (RegisterSizeBit == 0)
#else
	if (RegisterSizeBit == 0)
#endif
		message = "mipp::" + instr + "<" + type_names[typeid(T)] + "> (" + InstructionFullType + ") is undefined!, "
		          "try to add -mfpu=neon-vfpv4, -msse4.2, -mavx, -march=native... at the compile time.";
	else
		message = "mipp::" + instr + "<" + type_names[typeid(T)] + "> (" + InstructionFullType + ") is undefined!";

	message += get_back_trace();

	throw std::runtime_error(message);
}

template <int N>
static inline void errorMessage(std::string instr)
{
	std::string message;
#if __cplusplus >= 201703L
	if constexpr (RegisterSizeBit == 0)
#else
	if (RegisterSizeBit == 0)
#endif
		message = "mipp::" + instr + "<" + std::to_string(N) + "> (" + InstructionFullType + ") is undefined!, "
		          "try to add -mfpu=neon-vfpv4, -msse4.2, -mavx, -march=native... at the compile time.";
	else
		message = "mipp::" + instr + "<" + std::to_string(N) + "> (" + InstructionFullType + ") is undefined!";

	message += get_back_trace();

	throw std::runtime_error(message);
}

template <typename T1, typename T2>
static inline void errorMessage(std::string instr)
{
	// define type names
	std::unordered_map<std::type_index,std::string> type_names;
	type_names[typeid(int8_t  )] = "int8_t";
	type_names[typeid(uint8_t )] = "uint8_t";
	type_names[typeid(int16_t )] = "int16_t";
	type_names[typeid(uint16_t)] = "uint16_t";
	type_names[typeid(int32_t )] = "int32_t";
	type_names[typeid(uint32_t)] = "uint32_t";
	type_names[typeid(int64_t )] = "int64_t";
	type_names[typeid(uint64_t)] = "uint64_t";
	type_names[typeid(float   )] = "float";
	type_names[typeid(double  )] = "double";

	std::string message;
	if (RegisterSizeBit == 0)
		message = "mipp::" + instr + "<" + type_names[typeid(T1)] + "," + type_names[typeid(T2)] + "> (" +
		          InstructionFullType + ") is undefined!, try to add -mfpu=neon, -msse4.2, -mavx, -march=native... "
		          "at the compile time.";
	else
		message = "mipp::" + instr + "<" + type_names[typeid(T1)] + "," + type_names[typeid(T2)] + "> (" +
		          InstructionFullType + ") is undefined!";

	message += get_back_trace();

	throw std::runtime_error(message);
}

template <typename T> inline reg   load         (const T*)                        { errorMessage<T>("load");          exit(-1); }
template <typename T> inline reg_2 load_2       (const T*)                        { errorMessage<T>("load_2");        exit(-1); }
template <typename T> inline reg   loadu        (const T*)                        { errorMessage<T>("loadu");         exit(-1); }
template <typename T> inline reg_2 loadu_2      (const T*)                        { errorMessage<T>("loadu_2");       exit(-1); }
template <typename T> inline void  store        (T*, const reg)                   { errorMessage<T>("store");         exit(-1); }
template <typename T> inline void  storeu       (T*, const reg)                   { errorMessage<T>("storeu");        exit(-1); }
template <typename T> inline reg   set          (const T[nElReg<T>()])            { errorMessage<T>("set");           exit(-1); }
#ifdef _MSC_VER
template <int      N> inline msk   set          (const bool[])                    { errorMessage<N>("set");           exit(-1); }
#else
template <int      N> inline msk   set          (const bool[N])                   { errorMessage<N>("set");           exit(-1); }
#endif
template <typename T> inline reg   set1         (const T)                         { errorMessage<T>("set1");          exit(-1); }
template <int      N> inline msk   set1         (const bool)                      { errorMessage<N>("set1");          exit(-1); }
template <typename T> inline reg   set0         ()                                { errorMessage<T>("set0");          exit(-1); }
template <int      N> inline msk   set0         ()                                { errorMessage<N>("set0");          exit(-1); }
template <typename T> inline reg_2 low          (const reg)                       { errorMessage<T>("low");           exit(-1); }
template <typename T> inline reg_2 high         (const reg)                       { errorMessage<T>("high");          exit(-1); }
template <typename T> inline reg   combine      (const reg_2, const reg_2)        { errorMessage<T>("combine");       exit(-1); }
template <typename T> inline reg   compress     (const reg, const msk m)          { errorMessage<T>("compress");      exit(-1); }
#ifdef MIPP_NO_INTRINSICS // tricks to avoid compiling errors with Clang...
template <typename T> inline reg   cmask        (const uint32_t[1])               { errorMessage<T>("cmask");         exit(-1); }
template <typename T> inline reg   cmask2       (const uint32_t[1])               { errorMessage<T>("cmask2");        exit(-1); }
template <typename T> inline reg   cmask4       (const uint32_t[1])               { errorMessage<T>("cmask4");        exit(-1); }
#else
template <typename T> inline reg   cmask        (const uint32_t[nElReg<T>()])     { errorMessage<T>("cmask");         exit(-1); }
template <typename T> inline reg   cmask2       (const uint32_t[nElReg<T>()/2])   { errorMessage<T>("cmask2");        exit(-1); }
template <typename T> inline reg   cmask4       (const uint32_t[nElReg<T>()/4])   { errorMessage<T>("cmask4");        exit(-1); }
#endif
template <typename T> inline reg   shuff        (const reg, const reg)            { errorMessage<T>("shuff");         exit(-1); }
template <typename T> inline reg   shuff2       (const reg, const reg)            { errorMessage<T>("shuff2");        exit(-1); }
template <typename T> inline reg   shuff4       (const reg, const reg)            { errorMessage<T>("shuff4");        exit(-1); }
template <typename T> inline reg   interleavelo (const reg, const reg)            { errorMessage<T>("interleavelo");  exit(-1); }
template <typename T> inline reg   interleavehi (const reg, const reg)            { errorMessage<T>("interleavehi");  exit(-1); }
template <typename T> inline reg   interleavelo2(const reg, const reg)            { errorMessage<T>("interleavelo2"); exit(-1); }
template <typename T> inline reg   interleavehi2(const reg, const reg)            { errorMessage<T>("interleavehi2"); exit(-1); }
template <typename T> inline reg   interleavelo4(const reg, const reg)            { errorMessage<T>("interleavelo4"); exit(-1); }
template <typename T> inline reg   interleavehi4(const reg, const reg)            { errorMessage<T>("interleavehi4"); exit(-1); }
template <typename T> inline regx2 interleave   (const reg, const reg)            { errorMessage<T>("interleave");    exit(-1); }
template <typename T> inline regx2 deinterleave (const reg, const reg)            { errorMessage<T>("deinterleave");  exit(-1); }
template <typename T> inline regx2 interleave2  (const reg, const reg)            { errorMessage<T>("interleave2");   exit(-1); }
template <typename T> inline regx2 interleave4  (const reg, const reg)            { errorMessage<T>("interleave4");   exit(-1); }
template <typename T> inline reg   interleave   (const reg)                       { errorMessage<T>("interleave");    exit(-1); }
template <typename T> inline regx2 interleavex2 (const reg, const reg)            { errorMessage<T>("interleavex2");  exit(-1); }
template <typename T> inline reg   interleavex4 (const reg)                       { errorMessage<T>("interleavex4");  exit(-1); }
template <typename T> inline reg   interleavex16(const reg)                       { errorMessage<T>("interleavex16"); exit(-1); }
template <typename T> inline void  transpose    (      reg[nElReg<T>()])          { errorMessage<T>("transpose");     exit(-1); }
template <typename T> inline void  transpose8x8 (      reg[8])                    { errorMessage<T>("transpose8x8");  exit(-1); }
template <typename T> inline void  transpose2   (      reg[nElReg<T>()/2])        { errorMessage<T>("transpose2");    exit(-1); }
template <typename T> inline void  transpose28x8(      reg[8])                    { errorMessage<T>("transpose28x8"); exit(-1); }
template <typename T> inline void  transpose4   (      reg[nElReg<T>()/2])        { errorMessage<T>("transpose4");    exit(-1); }
template <typename T> inline void  transpose48x8(      reg[8])                    { errorMessage<T>("transpose48x8"); exit(-1); }
template <typename T> inline reg   andb         (const reg, const reg)            { errorMessage<T>("andb");          exit(-1); }
template <int      N> inline msk   andb         (const msk, const msk)            { errorMessage<N>("andb");          exit(-1); }
template <typename T> inline reg   andnb        (const reg, const reg)            { errorMessage<T>("andnb");         exit(-1); }
template <int      N> inline msk   andnb        (const msk, const msk)            { errorMessage<N>("andnb");         exit(-1); }
template <typename T> inline reg   notb         (const reg)                       { errorMessage<T>("notb");          exit(-1); }
template <int      N> inline msk   notb         (const msk)                       { errorMessage<N>("notb");          exit(-1); }
template <typename T> inline reg   orb          (const reg, const reg)            { errorMessage<T>("orb");           exit(-1); }
template <int      N> inline msk   orb          (const msk, const msk)            { errorMessage<N>("orb");           exit(-1); }
template <typename T> inline reg   xorb         (const reg, const reg)            { errorMessage<T>("xorb");          exit(-1); }
template <int      N> inline msk   xorb         (const msk, const msk)            { errorMessage<N>("xorb");          exit(-1); }
template <typename T> inline reg   lshift       (const reg, const uint32_t)       { errorMessage<T>("lshift");        exit(-1); }
template <typename T> inline reg   lshiftr      (const reg, const reg)            { errorMessage<T>("lshiftr");       exit(-1); }
template <int      N> inline msk   lshift       (const msk, const uint32_t)       { errorMessage<N>("lshift");        exit(-1); }
template <typename T> inline reg   rshift       (const reg, const uint32_t)       { errorMessage<T>("rshift");        exit(-1); }
template <typename T> inline reg   rshiftr      (const reg, const reg)            { errorMessage<T>("rshiftr");       exit(-1); }
template <int      N> inline msk   rshift       (const msk, const uint32_t)       { errorMessage<N>("rshift");        exit(-1); }
template <typename T> inline msk   cmpeq        (const reg, const reg)            { errorMessage<T>("cmpeq");         exit(-1); }
template <typename T> inline msk   cmpneq       (const reg, const reg)            { errorMessage<T>("cmpneq");        exit(-1); }
template <typename T> inline msk   cmplt        (const reg, const reg)            { errorMessage<T>("cmplt");         exit(-1); }
template <typename T> inline msk   cmple        (const reg, const reg)            { errorMessage<T>("cmple");         exit(-1); }
template <typename T> inline msk   cmpgt        (const reg, const reg)            { errorMessage<T>("cmpgt");         exit(-1); }
template <typename T> inline msk   cmpge        (const reg, const reg)            { errorMessage<T>("cmpge");         exit(-1); }
template <typename T> inline reg   add          (const reg, const reg)            { errorMessage<T>("add");           exit(-1); }
template <typename T> inline reg_2 add          (const reg_2, const reg_2)        { errorMessage<T>("add");           exit(-1); }
template <typename T> inline reg   sub          (const reg, const reg)            { errorMessage<T>("sub");           exit(-1); }
template <typename T> inline reg_2 sub          (const reg_2, const reg_2)        { errorMessage<T>("sub");           exit(-1); }
template <typename T> inline reg   mul          (const reg, const reg)            { errorMessage<T>("mul");           exit(-1); }
template <typename T> inline reg_2 mul          (const reg_2, const reg_2)        { errorMessage<T>("mul");           exit(-1); }
template <typename T> inline reg   div          (const reg, const reg)            { errorMessage<T>("div");           exit(-1); }
template <typename T> inline reg   min          (const reg, const reg)            { errorMessage<T>("min");           exit(-1); }
template <typename T> inline reg   max          (const reg, const reg)            { errorMessage<T>("max");           exit(-1); }
template <typename T> inline reg   msb          (const reg)                       { errorMessage<T>("msb");           exit(-1); }
template <typename T> inline reg   msb          (const reg, const reg)            { errorMessage<T>("msb");           exit(-1); }
template <typename T> inline msk   sign         (const reg)                       { errorMessage<T>("sign");          exit(-1); }
template <typename T> inline reg   neg          (const reg, const reg)            { errorMessage<T>("neg");           exit(-1); }
#if !(defined(_MSC_VER) && defined(_M_ARM))  //Avoid compiling error with MSVC for ARM
template <typename T> inline reg   neg          (const reg, const msk)            { errorMessage<T>("neg");           exit(-1); }
#endif
template <typename T> inline reg   abs          (const reg)                       { errorMessage<T>("abs");           exit(-1); }
template <typename T> inline reg   sqrt         (const reg)                       { errorMessage<T>("sqrt");          exit(-1); }
template <typename T> inline reg   rsqrt        (const reg)                       { errorMessage<T>("rsqrt");         exit(-1); }
template <typename T> inline reg   log          (const reg)                       { errorMessage<T>("log");           exit(-1); }
template <typename T> inline reg   exp          (const reg)                       { errorMessage<T>("exp");           exit(-1); }
template <typename T> inline reg   sin          (const reg)                       { errorMessage<T>("sin");           exit(-1); }
template <typename T> inline reg   cos          (const reg)                       { errorMessage<T>("cos");           exit(-1); }
template <typename T> inline void  sincos       (const reg, reg&, reg&)           { errorMessage<T>("sincos");        exit(-1); }
template <typename T> inline reg   fmadd        (const reg, const reg, const reg) { errorMessage<T>("fmadd");         exit(-1); }
template <typename T> inline reg   fnmadd       (const reg, const reg, const reg) { errorMessage<T>("fnmadd");        exit(-1); }
template <typename T> inline reg   fmsub        (const reg, const reg, const reg) { errorMessage<T>("fmsub");         exit(-1); }
template <typename T> inline reg   fnmsub       (const reg, const reg, const reg) { errorMessage<T>("fnmsub");        exit(-1); }
template <typename T> inline reg   blend        (const reg, const reg, const msk) { errorMessage<T>("blend");         exit(-1); }
template <typename T> inline reg   lrot         (const reg)                       { errorMessage<T>("lrot");          exit(-1); }
template <typename T> inline reg   rrot         (const reg)                       { errorMessage<T>("rrot");          exit(-1); }
template <typename T> inline reg   div2         (const reg)                       { errorMessage<T>("div2");          exit(-1); }
template <typename T> inline reg   div4         (const reg)                       { errorMessage<T>("div4");          exit(-1); }
template <typename T> inline reg   sat          (const reg, T, T)                 { errorMessage<T>("sat");           exit(-1); }
template <typename T> inline reg   round        (const reg)                       { errorMessage<T>("round");         exit(-1); }
template <typename T> inline reg   trunc        (const reg)                       { errorMessage<T>("trunc");         exit(-1); }
template <typename T> inline bool  testz        (const reg, const reg)            { errorMessage<T>("testz");         exit(-1); }
template <int      N> inline bool  testz        (const msk, const msk)            { errorMessage<N>("testz");         exit(-1); }
template <typename T> inline bool  testz        (const reg)                       { errorMessage<T>("testz");         exit(-1); }
template <int      N> inline bool  testz        (const msk)                       { errorMessage<N>("testz");         exit(-1); }

template <typename TD, typename TI>
inline reg gather(const TD*, const reg) {
	errorMessage<TD,TI>("gather");
	exit(-1);
}

template <typename TD, typename TI>
inline void scatter(TD*, const reg, const reg) {
	errorMessage<TD,TI>("scatter");
	exit(-1);
}

template <typename T1, typename T2>
inline reg cvt(const reg) {
	errorMessage<T1,T2>("cvt");
	exit(-1);
}

template <typename T1, typename T2>
inline reg cvt(const reg_2) {
	errorMessage<T1,T2>("cvt");
	exit(-1);
}

template <typename T1, typename T2>
inline reg pack(const reg, const reg) {
	errorMessage<T1,T2>("pack");
	exit(-1);
}

template <int S, typename T>
inline reg combine(const reg, const reg) {
	errorMessage<T>("combine");
	exit(-1);
}

template <typename T>
inline regx2 sincos(const reg v)
{
	regx2 sin_cos;
	mipp::sincos<T>(v, sin_cos.val[0], sin_cos.val[1]);
	return sin_cos;
}

template <typename T>
inline regx2 cossin(const reg v)
{
	regx2 sin_cos;
	mipp::sincos<T>(v, sin_cos.val[1], sin_cos.val[0]);
	return sin_cos;
}

template <typename T>
inline regx2 interleave(const regx2 v)
{
	return mipp::interleave<T>(v.val[0], v.val[1]);
}

template <typename T>
inline regx2 deinterleave(const regx2 v)
{
	return mipp::deinterleave<T>(v.val[0], v.val[1]);
}

// ------------------------------------------------------------------------------------------------------------ aliases
// --------------------------------------------------------------------------------------------------------------------
template <typename T> inline reg copysign(const reg r1, const reg r2) { return neg<T>(r1, r2); }
#if !(defined(_MSC_VER) && defined(_M_ARM))  //Avoid compiling error with MSVC for ARM
template <typename T> inline reg copysign(const reg r1, const msk r2) { return neg<T>(r1, r2); }
#endif
template <typename T> inline reg select(const msk m1, const reg r1, const reg r2)
{
	return mipp::blend<T>(r1, r2, m1);
}

// --------------------------------------------------------------------------------- hyperbolic trigonometric functions
// --------------------------------------------------------------------------------------------------------------------
template <typename T>
inline reg tan(const reg r)
{
	mipp::reg sin, cos;
	mipp::sincos<T>(r, sin, cos);
	return mipp::div<T>(sin, cos);
}

template <typename T>
inline reg sinh(const reg r)
{
	mipp::reg zero = mipp::set0<T>();
	mipp::reg half = mipp::set1<T>((T)0.5);
	return mipp::mul<T>(mipp::sub<T>(mipp::exp<T>(r), mipp::exp<T>(mipp::sub<T>(zero,r))), half);
}

template <typename T>
inline reg cosh(const reg r)
{
	mipp::reg zero = mipp::set0<T>();
	mipp::reg half = mipp::set1<T>((T)0.5);
	return mipp::mul<T>(mipp::add<T>(mipp::exp<T>(r), mipp::exp<T>(mipp::sub<T>(zero,r))), half);
}

template <typename T>
inline reg tanh(const reg r)
{
	mipp::reg zero = mipp::set0<T>();
	auto epx = mipp::exp<T>(r);
	auto emx = mipp::exp<T>(mipp::sub<T>(zero,r));
	return mipp::div<T>(mipp::sub<T>(epx, emx), mipp::add<T>(epx, emx));
}

template <typename T>
inline reg asinh(const reg r)
{
	mipp::reg one = mipp::set1<T>((T)1);
	return mipp::log<T>(mipp::add<T>(r, mipp::sqrt<T>(mipp::add<T>(mipp::mul<T>(r, r), one))));
}

template <typename T>
inline reg acosh(const reg r)
{
	mipp::reg one = mipp::set1<T>((T)1);
	return mipp::log<T>(mipp::add<T>(r, mipp::sqrt<T>(mipp::sub<T>(mipp::mul<T>(r, r), one))));
}

template <typename T>
inline reg atanh(const reg r)
{
	mipp::reg one = mipp::set1<T>((T)1);
	mipp::reg half = mipp::set1<T>((T)0.5);
	return mipp::mul<T>(half, mipp::log<T>(mipp::div<T>(mipp::add<T>(one, r), mipp::sub<T>(one, r))));
}

// template <typename T>
// inline reg csch(const reg r)
// {
// 	mipp::reg zero = mipp::set0<T>();
// 	mipp::reg two = mipp::set1<T>((T)2);
// 	return mipp::div<T>(two, mipp::sub<T>(mipp::exp<T>(r), mipp::exp<T>(mipp::sub<T>(zero,r))));
// }

// template <typename T>
// inline reg sech(const reg r)
// {
// 	mipp::reg zero = mipp::set0<T>();
// 	mipp::reg two = mipp::set1<T>((T)2);
// 	return mipp::div<T>(two, mipp::add<T>(mipp::exp<T>(r), mipp::exp<T>(mipp::sub<T>(zero,r))));
// }

// template <typename T>
// inline reg coth(const reg r)
// {
// 	mipp::reg zero = mipp::set0<T>();
// 	auto epx = mipp::exp<T>(r);
// 	auto emx = mipp::exp<T>(mipp::sub<T>(zero,r));
// 	return mipp::div<T>(mipp::add<T>(epx, emx), mipp::sub<T>(epx, emx));
// }

// template <typename T>
// inline reg acsch(const reg r)
// {
// 	mipp::reg one = mipp::set1<T>((T)1);
// 	return mipp::log<T>(mipp::div<T>(mipp::add<T>(one, mipp::sqrt<T>(mipp::add<T>(one, mipp::mul<T>(r, r)))), r));
// }

// template <typename T>
// inline reg asech(const reg r)
// {
// 	mipp::reg one = mipp::set1<T>((T)1);
// 	return mipp::log<T>(mipp::div<T>(mipp::add<T>(one, mipp::sqrt<T>(mipp::sub<T>(one, mipp::mul<T>(r, r)))), r));
// }

// template <typename T>
// inline reg acoth(const reg r)
// {
// 	mipp::reg one = mipp::set1<T>((T)1);
// 	mipp::reg half = mipp::set1<T>((T)0.5);
// 	return mipp::mul<T>(half, mipp::log<T>(mipp::div<T>(mipp::add<T>(r, one), mipp::sub<T>(r, one))));
// }

// -------------------------------------------------------------------------------------------------- complex functions
// --------------------------------------------------------------------------------------------------------------------

template <typename T>
inline regx2 cadd(const regx2 v1, const regx2 v2)
{
	return {{mipp::add<T>(v1.val[0], v2.val[0]), mipp::add<T>(v1.val[1], v2.val[1])}};
}

template <typename T>
inline regx2 csub(const regx2 v1, const regx2 v2)
{
	return {{mipp::sub<T>(v1.val[0], v2.val[0]), mipp::sub<T>(v1.val[1], v2.val[1])}};
}

template <typename T>
inline regx2 cmul(const regx2 v1, const regx2 v2)
{
	auto v3_re = mipp::sub<T>(mipp::mul<T>(v1.val[0], v2.val[0]), mipp::mul<T>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::add<T>(mipp::mul<T>(v1.val[0], v2.val[1]), mipp::mul<T>(v1.val[1], v2.val[0]));

	return {{v3_re, v3_im}};
}

template <typename T>
inline regx2 cmulconj(const regx2 v1, const regx2 v2)
{
	auto v3_re = mipp::add<T>(mipp::mul<T>(v1.val[0], v2.val[0]), mipp::mul<T>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::sub<T>(mipp::mul<T>(v1.val[1], v2.val[0]), mipp::mul<T>(v1.val[0], v2.val[1]));

	return {{v3_re, v3_im}};
}

template <typename T>
inline regx2 cdiv(const regx2 v1, const regx2 v2)
{
	auto norm = mipp::add<T>(mipp::mul<T>(v2.val[0], v2.val[0]), mipp::mul<T>(v2.val[1], v2.val[1]));

	auto v3_re = mipp::add<T>(mipp::mul<T>(v1.val[0], v2.val[0]), mipp::mul<T>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::sub<T>(mipp::mul<T>(v1.val[1], v2.val[0]), mipp::mul<T>(v1.val[0], v2.val[1]));

	v3_re = mipp::div<T>(v3_re, norm);
	v3_im = mipp::div<T>(v3_im, norm);

	return {{v3_re, v3_im}};
}

template <typename T>
inline regx2 conj(const regx2 v)
{
	const auto zeros = mipp::set0<T>();
	return {{v.val[0], mipp::sub<T>(zeros, v.val[1])}};
}

template <typename T>
inline reg norm(const regx2 v)
{
	return mipp::add<T>(mipp::mul<T>(v.val[0], v.val[0]), mipp::mul<T>(v.val[1], v.val[1]));
}

// ------------------------------------------------------------------------------------------------------------ masking
// --------------------------------------------------------------------------------------------------------------------

template <typename T> using proto_i1 = reg  (*)(const reg a);
template <typename T> using proto_i2 = reg  (*)(const reg a, const reg b);
template <typename T> using proto_i3 = reg  (*)(const reg a, const reg b, const reg c);
template <typename T> using proto_il = reg  (*)(const T*);
template <typename T> using proto_is = void (*)(T*, const reg);

template <typename T, proto_i1<T> I1>
inline reg mask(const msk m, const reg src, const reg a)
{
	return blend<T>(I1(a), src, m);
}

template <typename T, proto_i2<T> I2>
inline reg mask(const msk m, const reg src, const reg a, const reg b)
{
	return blend<T>(I2(a, b), src, m);
}

template <typename T, proto_i3<T> I3>
inline reg mask(const msk m, const reg src, const reg a, const reg b, const reg c)
{
	return blend<T>(I3(a, b, c), src, m);
}

template <typename T, proto_i1<T> I1>
inline reg maskz(const msk m, const reg a)
{
	auto m_reg = toreg<N<T>()>(m);
	auto a_modif = I1(a);
	return andb<T>(m_reg, a_modif);
}

template <typename T, proto_i2<T> I2>
inline reg maskz(const msk m, const reg a, const reg b)
{
	auto m_reg = toreg<N<T>()>(m);
	auto a_modif = I2(a, b);
	return andb<T>(m_reg, a_modif);
}

template <typename T, proto_i3<T> I3>
inline reg maskz(const msk m, const reg a, const reg b, const reg c)
{
	auto m_reg = toreg<N<T>()>(m);
	auto a_modif = I3(a, b, c);
	return andb<T>(m_reg, a_modif);
}

template <typename T, proto_il<T> IL = mipp::loadu<T>>
inline reg maskzld(const msk m, const T* memp)
{
	auto rl = IL(memp);
	auto rm = toreg<N<T>()>(m);
	return andb<T>(rm, rl);
}

template <typename T, proto_il<T> IL = mipp::loadu<T>, proto_is<T> IS = mipp::storeu<T>>
inline reg maskzlds(const msk m, const T* memp)
{
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T mask[mipp::N<T>()], data[mipp::N<T>()];
#else
	T mask[mipp::N<T>()], data[mipp::N<T>()];
#endif
	auto rm = toreg<N<T>()>(m);
	IS(mask, rm);
	for (int i = 0; i < mipp::N<T>(); i++)
		data[i] = mask[i] != (T)0 ? memp[i] : (T)0;
	return IL(data);
}

template <typename T, proto_is<T> IS = mipp::storeu<T>, proto_il<T> IL = mipp::loadu<T>>
inline void maskst(const msk m, T* memp, const reg a)
{
	auto rl = IL(memp);
	auto rres = mipp::blend<T>(a, rl, m);
	IS(memp, rres);
}

template <typename T, proto_is<T> IS = mipp::storeu<T>>
inline void masksts(const msk m, T* memp, const reg a)
{
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T mask[mipp::N<T>()], data[mipp::N<T>()];
#else
	T mask[mipp::N<T>()], data[mipp::N<T>()];
#endif
	auto rm = toreg<N<T>()>(m);
	IS(mask, rm);
	IS(data, a);
	for (int i = 0; i < mipp::N<T>(); i++)
		if (mask[i] != (T)0)
			memp[i] = data[i];
}

template <typename TD, typename TI>
inline reg maskzgat(const msk m, const TD* memp, const reg idx)
{
	auto rg = mipp::gather<TD,TI>(memp, idx);
	auto rm = toreg<N<TD>()>(m);
	return mipp::andb<TD>(rg, rm);
}

template <typename TD, typename TI>
inline void masksca(const msk m, TD* memp, const reg idx, const reg r)
{
	auto rg = mipp::gather<TD,TI>(memp, idx);
	auto rs = mipp::blend<TD>(r, rg, m);
	mipp::scatter<TD,TI>(memp, idx, rs);
}

// -------------------------------------------------------------------------------------------------------- obj masking

template <typename T>
class Reg;

template <int N>
class Msk;

template <typename T> inline Reg<T> blend (const Reg<T> v1, const Reg<T> v2, const Msk<N<T>()> m);
template <typename T> inline Reg<T> andb  (const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> oloadu(const T* memp);
template <typename T> inline void   storeu(      T* memp, const Reg<T> v1);

template <typename T> using proto_I1 = Reg<T> (*)(const Reg<T> a);
template <typename T> using proto_I2 = Reg<T> (*)(const Reg<T> a, const Reg<T> b);
template <typename T> using proto_I3 = Reg<T> (*)(const Reg<T> a, const Reg<T> b, const Reg<T> c);
template <typename T> using proto_IL = Reg<T> (*)(const T*);
template <typename T> using proto_IS = void (*)(T*, const Reg<T>);

template <typename T, proto_I1<T> I1>
inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src, const Reg<T> a)
{
#ifndef MIPP_NO
	return blend<T>(I1(a), src, m);
#else
	return m.m ? I1(a) : src;
#endif
}

template <typename T, proto_I2<T> I2>
inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src, const Reg<T> a, const Reg<T> b)
{
#ifndef MIPP_NO
	return blend<T>(I2(a, b), src, m);
#else
	return m.m ? I2(a, b) : src;
#endif
}

template <typename T, proto_I3<T> I3>
inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src, const Reg<T> a, const Reg<T> b, const Reg<T> c)
{
#ifndef MIPP_NO
	return blend<T>(I3(a, b, c), src, m);
#else
	return m.m ? I3(a, b, c) : src;
#endif
}

template <typename T, proto_I1<T> I1>
inline Reg<T> maskz(const Msk<N<T>()> m, const Reg<T> a)
{
#ifndef MIPP_NO
	auto m_reg = m.template toReg<T>();
	auto a_modif = I1(a);
	return andb<T>(m_reg, a_modif);
#else
	return m.m ? I1(a) : Reg<T>((T)0);
#endif
}

template <typename T, proto_I2<T> I2>
inline Reg<T> maskz(const Msk<N<T>()> m, const Reg<T> a, const Reg<T> b)
{
#ifndef MIPP_NO
	auto m_reg = m.template toReg<T>();
	auto a_modif = I2(a, b);
	return andb<T>(m_reg, a_modif);
#else
	return m.m ? I2(a, b) : Reg<T>((T)0);
#endif
}

template <typename T, proto_I3<T> I3>
inline Reg<T> maskz(const Msk<N<T>()> m, const Reg<T> a, const Reg<T> b, const Reg<T> c)
{
#ifndef MIPP_NO
	auto m_reg = m.template toReg<T>();
	auto a_modif = I3(a, b, c);
	return andb<T>(m_reg, a_modif);
#else
	return m.m ? I3(a, b, c) : Reg<T>((T)0);
#endif
}

template <typename T, proto_IL<T> IL = mipp::oloadu<T>>
inline Reg<T> maskzld(const Msk<N<T>()> m, const T* memp)
{
#ifndef MIPP_NO
	auto rl = IL(memp);
	auto rm = m.template toReg<T>();
	return andb<T>(rm, rl);
#else
	return m.m ? Reg<T>((T)*memp) : Reg<T>((T)0);
#endif
}

template <typename T, proto_IL<T> IL = mipp::oloadu<T>, proto_IS<T> IS = mipp::storeu<T>>
inline Reg<T> maskzlds(const Msk<N<T>()> m, const T* memp)
{
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T mask[mipp::N<T>()], data[mipp::N<T>()];
	auto rm = m.template toReg<T>();
	IS(mask, rm);
	for (int i = 0; i < mipp::N<T>(); i++)
		data[i] = mask[i] != (T)0 ? memp[i] : (T)0;
	return IL(data);
#else
	return m.m ? Reg<T>((T)*memp) : Reg<T>((T)0);
#endif
}

template <typename T, proto_IS<T> IS = mipp::storeu<T>, proto_IL<T> IL = mipp::oloadu<T>>
inline void maskst(const Msk<N<T>()> m, T* memp, const Reg<T> a)
{
#ifndef MIPP_NO
	auto rl = IL(memp);
	auto rres = mipp::blend<T>(a, rl, m);
	IS(memp, rres);
#else
	if (m.m) memp[0] = a.r;
#endif
}

template <typename T, proto_IS<T> IS = mipp::storeu<T>>
inline void masksts(const Msk<N<T>()> m, T* memp, const Reg<T> a)
{
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T mask[mipp::N<T>()], data[mipp::N<T>()];
	auto rm = m.template toReg<T>();
	IS(mask, rm);
	IS(data, a);
	for (int i = 0; i < mipp::N<T>(); i++)
		if (mask[i] != (T)0)
			memp[i] = data[i];
#else
	if (m.m) memp[0] = a.r;
#endif
}

template <typename TD, typename TI>
inline Reg<TD> maskzgat(const Msk<N<TD>()> m, const TD* memp, const Reg<TI> idx)
{
#ifndef MIPP_NO
	return Reg<TD>(mipp::maskzgat<TD,TI>(m.m, memp, idx.r));
#else
	return m.m ? Reg<TD>(memp[idx.r]) : Reg<TD>((TD)0);
#endif
}

template <typename TD, typename TI>
inline void masksca(const Msk<N<TD>()> m, TD* memp, const Reg<TI> idx, const Reg<TD> r)
{
#ifndef MIPP_NO
	mipp::masksca<TD,TI>(m.m, memp, idx.r, r.r);
#else
	if (m.m)
		memp[idx.r] = r.r;
#endif
}

// --------------------------------------------------------------------------------------- myIntrinsics implementations
// --------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------- get
template <typename T>
T get(const mipp::reg r, const size_t index)
{
	T tmp[mipp::N<T>()];
	mipp::storeu<T>(tmp, r);
	return tmp[index % mipp::N<T>()];
}

template <typename T>
T get(const mipp::reg_2 r, const size_t index)
{
	mipp::reg_2 rosef = r;
	auto r_full = mipp::combine<T>(r, rosef);
	T tmp[mipp::N<T>()];
	mipp::storeu<T>(tmp, r_full);
	return tmp[index % (mipp::N<T>()/2)];
}

template <int N>
bool get(const mipp::msk m, const size_t index)
{
#ifdef MIPP_AVX512
		return (m >> (index % N)) & 0x1;
#else
		uint8_t tmp[mipp::RegisterSizeBit / 8];
		mipp::storeu<float>((float*)tmp, mipp::toreg<N>(m));
		return tmp[index * (mipp::RegisterSizeBit / (N * 8))];
#endif
}

// ----------------------------------------------------------------------------------------------------------- getfirst
template <typename T>
T getfirst(const mipp::reg r)
{
	return get<T>(r, 0);
}

template <typename T>
T getfirst(const mipp::reg_2 r)
{
	return get<T>(r, 0);
}

template <int N>
bool getfirst(const mipp::msk m)
{
	return get<N>(m, 0);
}

// --------------------------------------------------------------------------------------------------------------- dump

template <typename T>
void dump(const mipp::reg r, std::ostream &stream = std::cout, const uint32_t elmtWidth = 6)
{
	constexpr int32_t lane_size = (int32_t)(mipp::N<T>() / mipp::Lanes);

//	const T* data = (T*)&r;
#ifdef MIPP_ALIGNED_LOADS
   	T* data = malloc<T>(mipp::N<T>());
#else
   	T data[mipp::nElReg<T>()];
#endif
	store<T>(data, r);

	stream << "[";
	for (uint32_t l = 0; l < mipp::Lanes; l++)
	{
		for (auto i = 0; i < lane_size; i++)
			stream << std::setw(elmtWidth) << +data[l * lane_size +i] << ((i < lane_size -1) ? ", " : "");
		stream << (((int)l < (int)mipp::Lanes -1) ? " | " : "");
	}
	stream << "]";
#ifdef MIPP_ALIGNED_LOADS
	free(data);
#endif
}

template <int N>
void dump(const mipp::msk m, std::ostream &stream = std::cout, const uint32_t elmtWidth = 6)
{
	constexpr int32_t lane_size = (int32_t)(N / mipp::Lanes);
	constexpr int bits = mipp::RegisterSizeBit / N;

	const auto r = toreg<N>(m);

	stream << "[";
	if (bits == 8)
	{
		// const int8_t* data = (int8_t*)&r;
#ifdef MIPP_ALIGNED_LOADS
		int8_t* data = malloc<int8_t>(N);
#else
		int8_t data[N];
#endif
		store<int8_t>(data, r);

		for (uint32_t l = 0; l < mipp::Lanes; l++)
		{
			for (auto i = 0; i < lane_size; i++)
				stream << std::setw(elmtWidth) << (data[l * lane_size +i] ? 1 : 0) << ((i < lane_size -1) ? ", " : "");
			stream << (((int)l < (int)mipp::Lanes -1) ? " | " : "");
		}
#ifdef MIPP_ALIGNED_LOADS
		free(data);
#endif
	}
	else if (bits == 16)
	{
		// const int16_t* data = (int16_t*)&r;
#ifdef MIPP_ALIGNED_LOADS
		int16_t* data = malloc<int8_t>(N);
#else
		int16_t data[N];
#endif
		store<int16_t>(data, r);

		for (uint32_t l = 0; l < (int)mipp::Lanes; l++)
		{
			for (auto i = 0; i < lane_size; i++)
				stream << std::setw(elmtWidth) << (data[l * lane_size +i] ? 1 : 0) << ((i < lane_size -1) ? ", " : "");
			stream << (((int)l < (int)mipp::Lanes -1) ? " | " : "");
		}
#ifdef MIPP_ALIGNED_LOADS
		free(data);
#endif
	}
	else if (bits == 32)
	{
		// const int32_t* data = (int32_t*)&r;
#ifdef MIPP_ALIGNED_LOADS
		int32_t* data = malloc<int8_t>(N);
#else
		int32_t data[N];
#endif
		store<int32_t>(data, r);

		for (uint32_t l = 0; l < (int)mipp::Lanes; l++)
		{
			for (auto i = 0; i < lane_size; i++)
				stream << std::setw(elmtWidth) << (data[l * lane_size +i] ? 1 : 0) << ((i < lane_size -1) ? ", " : "");
			stream << (((int)l < (int)mipp::Lanes -1) ? " | " : "");
		}
#ifdef MIPP_ALIGNED_LOADS
		free(data);
#endif
	}
	else if (bits == 64)
	{
		// const int64_t* data = (int64_t*)&r;
#ifdef MIPP_ALIGNED_LOADS
		int64_t* data = malloc<int8_t>(N);
#else
		int64_t data[N];
#endif
		store<int64_t>(data, r);

		for (uint32_t l = 0; l < (int)mipp::Lanes; l++)
		{
			for (auto i = 0; i < lane_size; i++)
				stream << std::setw(elmtWidth) << (data[l * lane_size +i] ? 1 : 0) << ((i < lane_size -1) ? ", " : "");
			stream << (((int)l < (int)mipp::Lanes -1) ? " | " : "");
		}
#ifdef MIPP_ALIGNED_LOADS
		free(data);
#endif
	}

	stream << "]";
}

// ---------------------------------------------------------------------------------------------------------- reduction

template <typename T>
using red_op = reg (*)(const reg, const reg);

template <typename T>
using Red_op = Reg<T> (*)(const Reg<T>, const Reg<T>);

template <typename T>
using ld_op = reg (*)(const T*);

template <typename T, red_op<T> OP>
struct _reduction
{
	static reg apply(const reg) {
		errorMessage<T>("_reduction::apply");
		exit(-1);
	}

	static T sapply(const reg) {
		errorMessage<T>("_reduction::sapply");
		exit(-1);
	}
};

template <typename T, Red_op<T> OP>
struct _Reduction
{
	static Reg<T> apply(const Reg<T> r) {
#ifndef MIPP_NO_INTRINSICS
		errorMessage<T>("_Reduction::apply");
		exit(-1);
#else
		return r;
#endif
	}

	static T sapply(const Reg<T> r) {
#ifndef MIPP_NO_INTRINSICS
		errorMessage<T>("_Reduction::sapply");
		exit(-1);
#else
		return r.r;
#endif
	}
};

template <typename T, red_op<T> OP>
struct reduction
{
	static reg apply(const reg r)
	{
#ifdef __ARM_FEATURE_SVE
		return mipp::set1<T>(_reduction<T,OP>::sapply(r));
#else
		return _reduction<T,OP>::apply(r);
#endif
	}

	static T sapply(const reg r)
	{
#ifdef __ARM_FEATURE_SVE
		return _reduction<T,OP>::sapply(r);
#else
		auto red = reduction<T,OP>::apply(r);
#ifdef _MSC_VER
		return *((T*)&red);
#else
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
		return *((T*)&red);
#endif
#endif
	}

	template <ld_op<T> LD = mipp::load<T>>
	static T apply(const mipp::vector<T> &data)
	{
		return reduction<T,OP>::template apply<LD>(data.data(), data.size());
	}

	template <ld_op<T> LD = mipp::loadu<T>>
	static T apply(const std::vector<T> &data)
	{
		return reduction<T,OP>::template apply<LD>(data.data(), data.size());
	}

	template <ld_op<T> LD = mipp::loadu<T>>
	static T apply(const T *data, const uint32_t dataSize)
	{
		assert(dataSize > 0);
		assert(dataSize % mipp::nElReg<T>() == 0);

		auto rRed = LD(&data[0]);
		for (auto i = mipp::nElReg<T>(); i < dataSize; i += mipp::nElReg<T>())
			rRed = OP(rRed, LD(&data[i]));
		rRed = reduction<T,OP>::apply(rRed);

		T tRed[mipp::nElReg<T>()];
		mipp::store<T>(tRed, rRed);

		return tRed[0];
	}
};

template <typename T, Red_op<T> OP>
struct Reduction
{
	static Reg<T> apply(const Reg<T> r)
	{
#ifdef __ARM_FEATURE_SVE
		return mipp::set1<T>(_Reduction<T,OP>::sapply(r));
#else
		return _Reduction<T,OP>::apply(r);
#endif
	}

	static T sapply(const Reg<T> r)
	{
#ifdef __ARM_FEATURE_SVE
		return _Reduction<T,OP>::sapply(r);
#else
		auto red = Reduction<T,OP>::apply(r);
		return getfirst<T>(red);
#endif
	}

	template <ld_op<T> LD = mipp::load<T>>
	static T apply(const mipp::vector<T> &data)
	{
		return Reduction<T,OP>::template apply<LD>(data.data(), data.size());
	}

	template <ld_op<T> LD = mipp::loadu<T>>
	static T apply(const std::vector<T> &data)
	{
		return Reduction<T,OP>::template apply<LD>(data.data(), data.size());
	}

	template <ld_op<T> LD = mipp::loadu<T>>
	static T apply(const T *data, const uint32_t dataSize)
	{
		assert(dataSize > 0);
		assert(dataSize % mipp::nElReg<T>() == 0);

#ifndef MIPP_NO_INTRINSICS
		auto rRed = Reg<T>(LD(&data[0]));
#else
		auto rRed = Reg<T>(data[0]);
#endif
		for (uint32_t i = mipp::nElReg<T>(); i < dataSize; i += mipp::nElReg<T>())
#ifndef MIPP_NO_INTRINSICS
			rRed = OP(rRed, Reg<T>(LD(&data[i])));
#else
			rRed = OP(rRed, Reg<T>(data[i]));
#endif
		rRed = Reduction<T,OP>::apply(rRed);

		T tRed[mipp::nElReg<T>()];
		rRed.store(tRed);

		return tRed[0];
	}
};

// ------------------------------------------------------------------------- special reduction functions implementation

template <typename T> inline T sum (const reg v) { return reduction<T,mipp::add<T>>::sapply(v); }
template <typename T> inline T hadd(const reg v) { return reduction<T,mipp::add<T>>::sapply(v); }
template <typename T> inline T hmul(const reg v) { return reduction<T,mipp::mul<T>>::sapply(v); }
template <typename T> inline T hmin(const reg v) { return reduction<T,mipp::min<T>>::sapply(v); }
template <typename T> inline T hmax(const reg v) { return reduction<T,mipp::max<T>>::sapply(v); }

// ---------------------------------------------------------------------------------------- sequential gather & scatter

template <typename TD, typename TI>
inline reg gather_seq(const TD *mem_addr, const reg idx) {
	constexpr int N = mipp::N<TI>();
	TI indexes[N];
	mipp::storeu<TI>(indexes, idx);
	TD data[N];
	for (int i = 0; i < N; i++)
		data[i] = mem_addr[indexes[i]];
	return mipp::loadu<TD>(data);
}

template <typename TD, typename TI>
inline void scatter_seq(TD *mem_addr, const reg idx, const reg r) {
	constexpr int N = mipp::N<TI>();
	TI indexes[N];
	TD data[N];
	mipp::storeu<TI>(indexes, idx);
	mipp::storeu<TD>(data, r);
	for (int i = 0; i < N; i++)
		mem_addr[indexes[i]] = data[i];
}

// ------------------------------------------------------------------------------------------------- wrapper to objects
#include "mipp_object.hxx"

#ifndef MIPP_NO_INTRINSICS
// ------------------------------------------------------------------------------------------------------- ARM SVE LS()
// --------------------------------------------------------------------------------------------------------------------
#if defined(__ARM_FEATURE_SVE)
#include "mipp_impl_SVE.hxx"
// ------------------------------------------------------------------------------------------------------- ARM NEON-128
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include "mipp_impl_NEON.hxx"
// -------------------------------------------------------------------------------------------------------- X86 AVX-512
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
#include "mipp_impl_AVX512.hxx"
// -------------------------------------------------------------------------------------------------------- X86 AVX-256
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__AVX__)
#include "mipp_impl_AVX.hxx"
// -------------------------------------------------------------------------------------------------------- X86 SSE-128
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__SSE__)
#include "mipp_impl_SSE.hxx"
#endif
#endif


template <>
inline regx2 cmul<float>(const regx2 v1, const regx2 v2)
{
	auto v3_re = mipp::fmsub<float>(v1.val[0], v2.val[0], mipp::mul<float>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::fmadd<float>(v1.val[0], v2.val[1], mipp::mul<float>(v1.val[1], v2.val[0]));

	return {{v3_re, v3_im}};
}

template <>
inline regx2 cmulconj<float>(const regx2 v1, const regx2 v2)
{
	auto v3_re = mipp::fmadd<float>(v1.val[0], v2.val[0], mipp::mul<float>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::fmsub<float>(v1.val[1], v2.val[0], mipp::mul<float>(v1.val[0], v2.val[1]));

	return {{v3_re, v3_im}};
}

template <>
inline regx2 cdiv<float>(const regx2 v1, const regx2 v2)
{
	auto norm = mipp::fmadd<float>(v2.val[0], v2.val[0], mipp::mul<float>(v2.val[1], v2.val[1]));

	auto v3_re = mipp::fmadd<float>(v1.val[0], v2.val[0], mipp::mul<float>(v1.val[1], v2.val[1]));
	auto v3_im = mipp::fmsub<float>(v1.val[1], v2.val[0], mipp::mul<float>(v1.val[0], v2.val[1]));

	v3_re = mipp::div<float>(v3_re, norm);
	v3_im = mipp::div<float>(v3_im, norm);

	return {{v3_re, v3_im}};
}
template <>
inline reg norm<float>(const regx2 v)
{
	return mipp::fmadd<float>(v.val[0], v.val[0], mipp::mul<float>(v.val[1], v.val[1]));
}

// ------------------------------------------------------------------------------- myIntrinsics default specializations
// --------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------- loadu
#ifdef MIPP_64BIT
template <> inline reg loadu<uint64_t>(const uint64_t *mem_addr) { return loadu<int64_t>((const int64_t*) mem_addr); }
#endif
template <> inline reg loadu<uint32_t>(const uint32_t *mem_addr) { return loadu<int32_t>((const int32_t*) mem_addr); }
#ifdef MIPP_BW
template <> inline reg loadu<uint16_t>(const uint16_t *mem_addr) { return loadu<int16_t>((const int16_t*) mem_addr); }
template <> inline reg loadu<uint8_t >(const uint8_t  *mem_addr) { return loadu<int8_t >((const int8_t* ) mem_addr); }
#endif

// --------------------------------------------------------------------------------------------------------------- load
#ifdef MIPP_64BIT
template <> inline reg load<uint64_t>(const uint64_t *mem_addr) { return load<int64_t>((const int64_t*) mem_addr); }
#endif
template <> inline reg load<uint32_t>(const uint32_t *mem_addr) { return load<int32_t>((const int32_t*) mem_addr); }
#ifdef MIPP_BW
template <> inline reg load<uint16_t>(const uint16_t *mem_addr) { return load<int16_t>((const int16_t*) mem_addr); }
template <> inline reg load<uint8_t >(const uint8_t  *mem_addr) { return load<int8_t >((const int8_t* ) mem_addr); }
#endif

// ------------------------------------------------------------------------------------------------------------- storeu
#ifdef MIPP_64BIT
template <> inline void storeu<uint64_t>(uint64_t *mem_addr, const reg v) { storeu<int64_t>((int64_t*) mem_addr, v); }
#endif
template <> inline void storeu<uint32_t>(uint32_t *mem_addr, const reg v) { storeu<int32_t>((int32_t*) mem_addr, v); }
#ifdef MIPP_BW
template <> inline void storeu<uint16_t>(uint16_t *mem_addr, const reg v) { storeu<int16_t>((int16_t*) mem_addr, v); }
template <> inline void storeu<uint8_t >(uint8_t  *mem_addr, const reg v) { storeu<int8_t >((int8_t* ) mem_addr, v); }
#endif

// -------------------------------------------------------------------------------------------------------------- store
#ifdef MIPP_64BIT
template <> inline void store<uint64_t>(uint64_t *mem_addr, const reg v) { store<int64_t>((int64_t*) mem_addr, v); }
#endif
template <> inline void store<uint32_t>(uint32_t *mem_addr, const reg v) { store<int32_t>((int32_t*) mem_addr, v); }
#ifdef MIPP_BW
template <> inline void store<uint16_t>(uint16_t *mem_addr, const reg v) { store<int16_t>((int16_t*) mem_addr, v); }
template <> inline void store<uint8_t >(uint8_t  *mem_addr, const reg v) { store<int8_t >((int8_t* ) mem_addr, v); }
#endif

// ---------------------------------------------------------------------------------------------------------------- set
#ifdef MIPP_64BIT
template <> inline reg set<uint64_t>(const uint64_t vals[N<uint64_t>()]) { return loadu<uint64_t>(vals); }
#endif
template <> inline reg set<uint32_t>(const uint32_t vals[N<uint32_t>()]) { return loadu<uint32_t>(vals); }
#ifdef MIPP_BW
template <> inline reg set<uint16_t>(const uint16_t vals[N<uint16_t>()]) { return loadu<uint16_t>(vals); }
template <> inline reg set<uint8_t> (const uint8_t  vals[N<uint8_t >()]) { return loadu<uint8_t >(vals); }
#endif

// ---------------------------------------------------------------------------------------------------------------- low
#ifdef MIPP_64BIT
template <> inline reg_2 low<uint64_t>(const reg v) { return low<int64_t>(v); }
#endif
template <> inline reg_2 low<uint32_t>(const reg v) { return low<int32_t>(v); }
#ifdef MIPP_BW
template <> inline reg_2 low<uint16_t>(const reg v) { return low<int16_t>(v); }
template <> inline reg_2 low<uint8_t >(const reg v) { return low<int8_t >(v); }
#endif

// --------------------------------------------------------------------------------------------------------------- high
#ifdef MIPP_64BIT
template <> inline reg_2 high<uint64_t>(const reg v) { return high<int64_t>(v); }
#endif
template <> inline reg_2 high<uint32_t>(const reg v) { return high<int32_t>(v); }
#ifdef MIPP_BW
template <> inline reg_2 high<uint16_t>(const reg v) { return high<int16_t>(v); }
template <> inline reg_2 high<uint8_t >(const reg v) { return high<int8_t >(v); }
#endif

// ------------------------------------------------------------------------------------------------------------ combine
#ifdef MIPP_64BIT
template <> inline reg combine<uint64_t>(const reg_2 v1, const reg_2 v2) { return combine<int64_t>(v1, v2); }
#endif
template <> inline reg combine<uint32_t>(const reg_2 v1, const reg_2 v2) { return combine<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg combine<uint16_t>(const reg_2 v1, const reg_2 v2) { return combine<int16_t>(v1, v2); }
template <> inline reg combine<uint8_t >(const reg_2 v1, const reg_2 v2) { return combine<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------ combine (bis)
#ifdef MIPP_64BIT
template <> inline reg combine< 0, uint64_t>(const reg v1, const reg v2) { return combine< 0, int64_t>(v1, v2); }
template <> inline reg combine< 1, uint64_t>(const reg v1, const reg v2) { return combine< 1, int64_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 256
template <> inline reg combine< 2, uint64_t>(const reg v1, const reg v2) { return combine< 2, int64_t>(v1, v2); }
template <> inline reg combine< 3, uint64_t>(const reg v1, const reg v2) { return combine< 3, int64_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 512
template <> inline reg combine< 4, uint64_t>(const reg v1, const reg v2) { return combine< 4, int64_t>(v1, v2); }
template <> inline reg combine< 5, uint64_t>(const reg v1, const reg v2) { return combine< 5, int64_t>(v1, v2); }
template <> inline reg combine< 6, uint64_t>(const reg v1, const reg v2) { return combine< 6, int64_t>(v1, v2); }
template <> inline reg combine< 7, uint64_t>(const reg v1, const reg v2) { return combine< 7, int64_t>(v1, v2); }
#endif /* MIPP_REGISTER_SIZE >= 512 */
#endif /* MIPP_REGISTER_SIZE >= 256 */
#endif

template <> inline reg combine< 0, uint32_t>(const reg v1, const reg v2) { return combine< 0, int32_t>(v1, v2); }
template <> inline reg combine< 1, uint32_t>(const reg v1, const reg v2) { return combine< 1, int32_t>(v1, v2); }
template <> inline reg combine< 2, uint32_t>(const reg v1, const reg v2) { return combine< 2, int32_t>(v1, v2); }
template <> inline reg combine< 3, uint32_t>(const reg v1, const reg v2) { return combine< 3, int32_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 256
template <> inline reg combine< 4, uint32_t>(const reg v1, const reg v2) { return combine< 4, int32_t>(v1, v2); }
template <> inline reg combine< 5, uint32_t>(const reg v1, const reg v2) { return combine< 5, int32_t>(v1, v2); }
template <> inline reg combine< 6, uint32_t>(const reg v1, const reg v2) { return combine< 6, int32_t>(v1, v2); }
template <> inline reg combine< 7, uint32_t>(const reg v1, const reg v2) { return combine< 7, int32_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 512
template <> inline reg combine< 8, uint32_t>(const reg v1, const reg v2) { return combine< 8, int32_t>(v1, v2); }
template <> inline reg combine< 9, uint32_t>(const reg v1, const reg v2) { return combine< 9, int32_t>(v1, v2); }
template <> inline reg combine<10, uint32_t>(const reg v1, const reg v2) { return combine<10, int32_t>(v1, v2); }
template <> inline reg combine<11, uint32_t>(const reg v1, const reg v2) { return combine<11, int32_t>(v1, v2); }
template <> inline reg combine<12, uint32_t>(const reg v1, const reg v2) { return combine<12, int32_t>(v1, v2); }
template <> inline reg combine<13, uint32_t>(const reg v1, const reg v2) { return combine<13, int32_t>(v1, v2); }
template <> inline reg combine<14, uint32_t>(const reg v1, const reg v2) { return combine<14, int32_t>(v1, v2); }
template <> inline reg combine<15, uint32_t>(const reg v1, const reg v2) { return combine<15, int32_t>(v1, v2); }
#endif /* MIPP_REGISTER_SIZE >= 512 */
#endif /* MIPP_REGISTER_SIZE >= 256 */

#ifdef MIPP_BW
template <> inline reg combine< 0, uint16_t>(const reg v1, const reg v2) { return combine< 0, int16_t>(v1, v2); }
template <> inline reg combine< 1, uint16_t>(const reg v1, const reg v2) { return combine< 1, int16_t>(v1, v2); }
template <> inline reg combine< 2, uint16_t>(const reg v1, const reg v2) { return combine< 2, int16_t>(v1, v2); }
template <> inline reg combine< 3, uint16_t>(const reg v1, const reg v2) { return combine< 3, int16_t>(v1, v2); }
template <> inline reg combine< 4, uint16_t>(const reg v1, const reg v2) { return combine< 4, int16_t>(v1, v2); }
template <> inline reg combine< 5, uint16_t>(const reg v1, const reg v2) { return combine< 5, int16_t>(v1, v2); }
template <> inline reg combine< 6, uint16_t>(const reg v1, const reg v2) { return combine< 6, int16_t>(v1, v2); }
template <> inline reg combine< 7, uint16_t>(const reg v1, const reg v2) { return combine< 7, int16_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 256
template <> inline reg combine< 8, uint16_t>(const reg v1, const reg v2) { return combine< 8, int16_t>(v1, v2); }
template <> inline reg combine< 9, uint16_t>(const reg v1, const reg v2) { return combine< 9, int16_t>(v1, v2); }
template <> inline reg combine<10, uint16_t>(const reg v1, const reg v2) { return combine<10, int16_t>(v1, v2); }
template <> inline reg combine<11, uint16_t>(const reg v1, const reg v2) { return combine<11, int16_t>(v1, v2); }
template <> inline reg combine<12, uint16_t>(const reg v1, const reg v2) { return combine<12, int16_t>(v1, v2); }
template <> inline reg combine<13, uint16_t>(const reg v1, const reg v2) { return combine<13, int16_t>(v1, v2); }
template <> inline reg combine<14, uint16_t>(const reg v1, const reg v2) { return combine<14, int16_t>(v1, v2); }
template <> inline reg combine<15, uint16_t>(const reg v1, const reg v2) { return combine<15, int16_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 512
template <> inline reg combine<16, uint16_t>(const reg v1, const reg v2) { return combine<16, int16_t>(v1, v2); }
template <> inline reg combine<17, uint16_t>(const reg v1, const reg v2) { return combine<17, int16_t>(v1, v2); }
template <> inline reg combine<18, uint16_t>(const reg v1, const reg v2) { return combine<18, int16_t>(v1, v2); }
template <> inline reg combine<19, uint16_t>(const reg v1, const reg v2) { return combine<19, int16_t>(v1, v2); }
template <> inline reg combine<20, uint16_t>(const reg v1, const reg v2) { return combine<20, int16_t>(v1, v2); }
template <> inline reg combine<21, uint16_t>(const reg v1, const reg v2) { return combine<21, int16_t>(v1, v2); }
template <> inline reg combine<22, uint16_t>(const reg v1, const reg v2) { return combine<22, int16_t>(v1, v2); }
template <> inline reg combine<23, uint16_t>(const reg v1, const reg v2) { return combine<23, int16_t>(v1, v2); }
template <> inline reg combine<24, uint16_t>(const reg v1, const reg v2) { return combine<24, int16_t>(v1, v2); }
template <> inline reg combine<25, uint16_t>(const reg v1, const reg v2) { return combine<25, int16_t>(v1, v2); }
template <> inline reg combine<26, uint16_t>(const reg v1, const reg v2) { return combine<26, int16_t>(v1, v2); }
template <> inline reg combine<27, uint16_t>(const reg v1, const reg v2) { return combine<27, int16_t>(v1, v2); }
template <> inline reg combine<28, uint16_t>(const reg v1, const reg v2) { return combine<28, int16_t>(v1, v2); }
template <> inline reg combine<29, uint16_t>(const reg v1, const reg v2) { return combine<29, int16_t>(v1, v2); }
template <> inline reg combine<30, uint16_t>(const reg v1, const reg v2) { return combine<30, int16_t>(v1, v2); }
template <> inline reg combine<31, uint16_t>(const reg v1, const reg v2) { return combine<31, int16_t>(v1, v2); }
#endif /* MIPP_REGISTER_SIZE >= 512 */
#endif /* MIPP_REGISTER_SIZE >= 256 */

template <> inline reg combine< 0, uint8_t>(const reg v1, const reg v2) { return combine< 0, int8_t>(v1, v2); }
template <> inline reg combine< 1, uint8_t>(const reg v1, const reg v2) { return combine< 1, int8_t>(v1, v2); }
template <> inline reg combine< 2, uint8_t>(const reg v1, const reg v2) { return combine< 2, int8_t>(v1, v2); }
template <> inline reg combine< 3, uint8_t>(const reg v1, const reg v2) { return combine< 3, int8_t>(v1, v2); }
template <> inline reg combine< 4, uint8_t>(const reg v1, const reg v2) { return combine< 4, int8_t>(v1, v2); }
template <> inline reg combine< 5, uint8_t>(const reg v1, const reg v2) { return combine< 5, int8_t>(v1, v2); }
template <> inline reg combine< 6, uint8_t>(const reg v1, const reg v2) { return combine< 6, int8_t>(v1, v2); }
template <> inline reg combine< 7, uint8_t>(const reg v1, const reg v2) { return combine< 7, int8_t>(v1, v2); }
template <> inline reg combine< 8, uint8_t>(const reg v1, const reg v2) { return combine< 8, int8_t>(v1, v2); }
template <> inline reg combine< 9, uint8_t>(const reg v1, const reg v2) { return combine< 9, int8_t>(v1, v2); }
template <> inline reg combine<10, uint8_t>(const reg v1, const reg v2) { return combine<10, int8_t>(v1, v2); }
template <> inline reg combine<11, uint8_t>(const reg v1, const reg v2) { return combine<11, int8_t>(v1, v2); }
template <> inline reg combine<12, uint8_t>(const reg v1, const reg v2) { return combine<12, int8_t>(v1, v2); }
template <> inline reg combine<13, uint8_t>(const reg v1, const reg v2) { return combine<13, int8_t>(v1, v2); }
template <> inline reg combine<14, uint8_t>(const reg v1, const reg v2) { return combine<14, int8_t>(v1, v2); }
template <> inline reg combine<15, uint8_t>(const reg v1, const reg v2) { return combine<15, int8_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 256
template <> inline reg combine<16, uint8_t>(const reg v1, const reg v2) { return combine<16, int8_t>(v1, v2); }
template <> inline reg combine<17, uint8_t>(const reg v1, const reg v2) { return combine<17, int8_t>(v1, v2); }
template <> inline reg combine<18, uint8_t>(const reg v1, const reg v2) { return combine<18, int8_t>(v1, v2); }
template <> inline reg combine<19, uint8_t>(const reg v1, const reg v2) { return combine<19, int8_t>(v1, v2); }
template <> inline reg combine<20, uint8_t>(const reg v1, const reg v2) { return combine<20, int8_t>(v1, v2); }
template <> inline reg combine<21, uint8_t>(const reg v1, const reg v2) { return combine<21, int8_t>(v1, v2); }
template <> inline reg combine<22, uint8_t>(const reg v1, const reg v2) { return combine<22, int8_t>(v1, v2); }
template <> inline reg combine<23, uint8_t>(const reg v1, const reg v2) { return combine<23, int8_t>(v1, v2); }
template <> inline reg combine<24, uint8_t>(const reg v1, const reg v2) { return combine<24, int8_t>(v1, v2); }
template <> inline reg combine<25, uint8_t>(const reg v1, const reg v2) { return combine<25, int8_t>(v1, v2); }
template <> inline reg combine<26, uint8_t>(const reg v1, const reg v2) { return combine<26, int8_t>(v1, v2); }
template <> inline reg combine<27, uint8_t>(const reg v1, const reg v2) { return combine<27, int8_t>(v1, v2); }
template <> inline reg combine<28, uint8_t>(const reg v1, const reg v2) { return combine<28, int8_t>(v1, v2); }
template <> inline reg combine<29, uint8_t>(const reg v1, const reg v2) { return combine<29, int8_t>(v1, v2); }
template <> inline reg combine<30, uint8_t>(const reg v1, const reg v2) { return combine<30, int8_t>(v1, v2); }
template <> inline reg combine<31, uint8_t>(const reg v1, const reg v2) { return combine<31, int8_t>(v1, v2); }
#if MIPP_REGISTER_SIZE >= 512
template <> inline reg combine<32, uint8_t>(const reg v1, const reg v2) { return combine<32, int8_t>(v1, v2); }
template <> inline reg combine<33, uint8_t>(const reg v1, const reg v2) { return combine<33, int8_t>(v1, v2); }
template <> inline reg combine<34, uint8_t>(const reg v1, const reg v2) { return combine<34, int8_t>(v1, v2); }
template <> inline reg combine<35, uint8_t>(const reg v1, const reg v2) { return combine<35, int8_t>(v1, v2); }
template <> inline reg combine<36, uint8_t>(const reg v1, const reg v2) { return combine<36, int8_t>(v1, v2); }
template <> inline reg combine<37, uint8_t>(const reg v1, const reg v2) { return combine<37, int8_t>(v1, v2); }
template <> inline reg combine<38, uint8_t>(const reg v1, const reg v2) { return combine<38, int8_t>(v1, v2); }
template <> inline reg combine<39, uint8_t>(const reg v1, const reg v2) { return combine<39, int8_t>(v1, v2); }
template <> inline reg combine<40, uint8_t>(const reg v1, const reg v2) { return combine<40, int8_t>(v1, v2); }
template <> inline reg combine<41, uint8_t>(const reg v1, const reg v2) { return combine<41, int8_t>(v1, v2); }
template <> inline reg combine<42, uint8_t>(const reg v1, const reg v2) { return combine<42, int8_t>(v1, v2); }
template <> inline reg combine<43, uint8_t>(const reg v1, const reg v2) { return combine<43, int8_t>(v1, v2); }
template <> inline reg combine<44, uint8_t>(const reg v1, const reg v2) { return combine<44, int8_t>(v1, v2); }
template <> inline reg combine<45, uint8_t>(const reg v1, const reg v2) { return combine<45, int8_t>(v1, v2); }
template <> inline reg combine<46, uint8_t>(const reg v1, const reg v2) { return combine<46, int8_t>(v1, v2); }
template <> inline reg combine<47, uint8_t>(const reg v1, const reg v2) { return combine<47, int8_t>(v1, v2); }
template <> inline reg combine<48, uint8_t>(const reg v1, const reg v2) { return combine<48, int8_t>(v1, v2); }
template <> inline reg combine<49, uint8_t>(const reg v1, const reg v2) { return combine<49, int8_t>(v1, v2); }
template <> inline reg combine<50, uint8_t>(const reg v1, const reg v2) { return combine<50, int8_t>(v1, v2); }
template <> inline reg combine<51, uint8_t>(const reg v1, const reg v2) { return combine<51, int8_t>(v1, v2); }
template <> inline reg combine<52, uint8_t>(const reg v1, const reg v2) { return combine<52, int8_t>(v1, v2); }
template <> inline reg combine<53, uint8_t>(const reg v1, const reg v2) { return combine<53, int8_t>(v1, v2); }
template <> inline reg combine<54, uint8_t>(const reg v1, const reg v2) { return combine<54, int8_t>(v1, v2); }
template <> inline reg combine<55, uint8_t>(const reg v1, const reg v2) { return combine<55, int8_t>(v1, v2); }
template <> inline reg combine<56, uint8_t>(const reg v1, const reg v2) { return combine<56, int8_t>(v1, v2); }
template <> inline reg combine<57, uint8_t>(const reg v1, const reg v2) { return combine<57, int8_t>(v1, v2); }
template <> inline reg combine<58, uint8_t>(const reg v1, const reg v2) { return combine<58, int8_t>(v1, v2); }
template <> inline reg combine<59, uint8_t>(const reg v1, const reg v2) { return combine<59, int8_t>(v1, v2); }
template <> inline reg combine<60, uint8_t>(const reg v1, const reg v2) { return combine<60, int8_t>(v1, v2); }
template <> inline reg combine<61, uint8_t>(const reg v1, const reg v2) { return combine<61, int8_t>(v1, v2); }
template <> inline reg combine<62, uint8_t>(const reg v1, const reg v2) { return combine<62, int8_t>(v1, v2); }
template <> inline reg combine<63, uint8_t>(const reg v1, const reg v2) { return combine<63, int8_t>(v1, v2); }
#endif /* MIPP_REGISTER_SIZE >= 512 */
#endif /* MIPP_REGISTER_SIZE >= 256 */
#endif /* MIPP_BW */

// ----------------------------------------------------------------------------------------------------------- compress
#ifdef MIPP_64BIT
template <> inline reg compress<uint64_t>(const reg v, const msk m) { return compress<int64_t>(v, m); }
#endif
template <> inline reg compress<uint32_t>(const reg v, const msk m) { return compress<int32_t>(v, m); }
#ifdef MIPP_BW
template <> inline reg compress<uint16_t>(const reg v, const msk m) { return compress<int16_t>(v, m); }
template <> inline reg compress<uint8_t >(const reg v, const msk m) { return compress<int8_t >(v, m); }
#endif

// -------------------------------------------------------------------------------------------------------------- cmask
#ifdef MIPP_64BIT
template <> inline reg cmask<uint64_t>(const uint32_t val[N<int64_t>()]) { return cmask<int64_t>(val); }
#endif
template <> inline reg cmask<uint32_t>(const uint32_t val[N<int32_t>()]) { return cmask<int32_t>(val); }
#ifdef MIPP_BW
template <> inline reg cmask<uint16_t>(const uint32_t val[N<int16_t>()]) { return cmask<int16_t>(val); }
template <> inline reg cmask<uint8_t >(const uint32_t val[N<int8_t >()]) { return cmask<int8_t >(val); }
#endif

// ------------------------------------------------------------------------------------------------------------- cmask2
#ifndef MIPP_NO_INTRINSICS
#ifdef MIPP_64BIT
template <> inline reg cmask2<uint64_t>(const uint32_t val[N<int64_t>()/2]) { return cmask2<int64_t>(val); }
#endif
template <> inline reg cmask2<uint32_t>(const uint32_t val[N<int32_t>()/2]) { return cmask2<int32_t>(val); }
#ifdef MIPP_BW
template <> inline reg cmask2<uint16_t>(const uint32_t val[N<int16_t>()/2]) { return cmask2<int16_t>(val); }
template <> inline reg cmask2<uint8_t >(const uint32_t val[N<int8_t >()/2]) { return cmask2<int8_t >(val); }
#endif
#endif

// ------------------------------------------------------------------------------------------------------------- cmask4
#ifndef MIPP_NO_INTRINSICS
#if(!MIPP_REGISTER_SIZE == 128)
#ifdef MIPP_64BIT
template <> inline reg cmask4<uint64_t>(const uint32_t val[N<int64_t>()/4]) { return cmask4<int64_t>(val); }
#endif
#endif
template <> inline reg cmask4<uint32_t>(const uint32_t val[N<int32_t>()/4]) { return cmask4<int32_t>(val); }
#ifdef MIPP_BW
template <> inline reg cmask4<uint16_t>(const uint32_t val[N<int16_t>()/4]) { return cmask4<int16_t>(val); }
template <> inline reg cmask4<uint8_t >(const uint32_t val[N<int8_t >()/4]) { return cmask4<int8_t >(val); }
#endif
#endif

// -------------------------------------------------------------------------------------------------------------- shuff
#ifdef MIPP_64BIT
template <> inline reg shuff<uint64_t>(const reg v, const reg cm) { return shuff<int64_t>(v, cm); }
#endif
template <> inline reg shuff<uint32_t>(const reg v, const reg cm) { return shuff<int32_t>(v, cm); }
#ifdef MIPP_BW
template <> inline reg shuff<uint16_t>(const reg v, const reg cm) { return shuff<int16_t>(v, cm); }
template <> inline reg shuff<uint8_t >(const reg v, const reg cm) { return shuff<int8_t >(v, cm); }
#endif

// ------------------------------------------------------------------------------------------------------------- shuff2
#ifdef MIPP_64BIT
template <> inline reg shuff2<uint64_t>(const reg v, const reg cm) { return shuff2<int64_t>(v, cm); }
#endif
template <> inline reg shuff2<uint32_t>(const reg v, const reg cm) { return shuff2<int32_t>(v, cm); }
#ifdef MIPP_BW
template <> inline reg shuff2<uint16_t>(const reg v, const reg cm) { return shuff2<int16_t>(v, cm); }
template <> inline reg shuff2<uint8_t >(const reg v, const reg cm) { return shuff2<int8_t >(v, cm); }
#endif

// ------------------------------------------------------------------------------------------------------------- shuff4
#if(!MIPP_REGISTER_SIZE == 128)
#ifdef MIPP_64BIT
template <> inline reg shuff4<uint64_t>(const reg v, const reg cm) { return shuff4<int64_t>(v, cm); }
#endif
#endif
template <> inline reg shuff4<uint32_t>(const reg v, const reg cm) { return shuff4<int32_t>(v, cm); }
#ifdef MIPP_BW
template <> inline reg shuff4<uint16_t>(const reg v, const reg cm) { return shuff4<int16_t>(v, cm); }
template <> inline reg shuff4<uint8_t >(const reg v, const reg cm) { return shuff4<int8_t >(v, cm); }
#endif

// ------------------------------------------------------------------------------------------------------- interleavelo
#ifdef MIPP_64BIT
template <> inline reg interleavelo<uint64_t>(const reg v1, const reg v2) { return interleavelo<int64_t>(v1, v2); }
#endif
template <> inline reg interleavelo<uint32_t>(const reg v1, const reg v2) { return interleavelo<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg interleavelo<uint16_t>(const reg v1, const reg v2) { return interleavelo<int16_t>(v1, v2); }
template <> inline reg interleavelo<uint8_t >(const reg v1, const reg v2) { return interleavelo<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------- interleavehi
#ifdef MIPP_64BIT
template <> inline reg interleavehi<uint64_t>(const reg v1, const reg v2) { return interleavehi<int64_t>(v1, v2); }
#endif
template <> inline reg interleavehi<uint32_t>(const reg v1, const reg v2) { return interleavehi<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg interleavehi<uint16_t>(const reg v1, const reg v2) { return interleavehi<int16_t>(v1, v2); }
template <> inline reg interleavehi<uint8_t >(const reg v1, const reg v2) { return interleavehi<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------ interleavelo2
#ifdef MIPP_64BIT
template <> inline reg interleavelo2<uint64_t>(const reg v1, const reg v2) { return interleavelo2<int64_t>(v1, v2); }
#endif
template <> inline reg interleavelo2<uint32_t>(const reg v1, const reg v2) { return interleavelo2<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg interleavelo2<uint16_t>(const reg v1, const reg v2) { return interleavelo2<int16_t>(v1, v2); }
template <> inline reg interleavelo2<uint8_t >(const reg v1, const reg v2) { return interleavelo2<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------ interleavehi2
#ifdef MIPP_64BIT
template <> inline reg interleavehi2<uint64_t>(const reg v1, const reg v2) { return interleavehi2<int64_t>(v1, v2); }
#endif
template <> inline reg interleavehi2<uint32_t>(const reg v1, const reg v2) { return interleavehi2<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg interleavehi2<uint16_t>(const reg v1, const reg v2) { return interleavehi2<int16_t>(v1, v2); }
template <> inline reg interleavehi2<uint8_t >(const reg v1, const reg v2) { return interleavehi2<int8_t >(v1, v2); }
#endif

// --------------------------------------------------------------------------------------------------------- interleave
#ifdef MIPP_64BIT
template <> inline regx2 interleave<uint64_t>(const reg v1, const reg v2) { return interleave<int64_t>(v1, v2); }
#endif
template <> inline regx2 interleave<uint32_t>(const reg v1, const reg v2) { return interleave<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline regx2 interleave<uint16_t>(const reg v1, const reg v2) { return interleave<int16_t>(v1, v2); }
template <> inline regx2 interleave<uint8_t >(const reg v1, const reg v2) { return interleave<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------- deinterleave
#ifdef MIPP_64BIT
template <> inline regx2 deinterleave<uint64_t>(const reg v1, const reg v2) { return deinterleave<int64_t>(v1, v2); }
#endif
template <> inline regx2 deinterleave<uint32_t>(const reg v1, const reg v2) { return deinterleave<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline regx2 deinterleave<uint16_t>(const reg v1, const reg v2) { return deinterleave<int16_t>(v1, v2); }
template <> inline regx2 deinterleave<uint8_t >(const reg v1, const reg v2) { return deinterleave<int8_t >(v1, v2); }
#endif

// -------------------------------------------------------------------------------------------------------- interleave2
#ifdef MIPP_64BIT
template <> inline regx2 interleave2<uint64_t>(const reg v1, const reg v2) { return interleave2<int64_t>(v1, v2); }
#endif
template <> inline regx2 interleave2<uint32_t>(const reg v1, const reg v2) { return interleave2<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline regx2 interleave2<uint16_t>(const reg v1, const reg v2) { return interleave2<int16_t>(v1, v2); }
template <> inline regx2 interleave2<uint8_t >(const reg v1, const reg v2) { return interleave2<int8_t >(v1, v2); }
#endif

// --------------------------------------------------------------------------------------------------------------- andb
#ifdef MIPP_64BIT
template <> inline reg andb<uint64_t>(const reg v1, const reg v2) { return andb<int64_t>(v1, v2); }
#endif
template <> inline reg andb<uint32_t>(const reg v1, const reg v2) { return andb<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg andb<uint16_t>(const reg v1, const reg v2) { return andb<int16_t>(v1, v2); }
template <> inline reg andb<uint8_t >(const reg v1, const reg v2) { return andb<int8_t >(v1, v2); }
#endif

// --------------------------------------------------------------------------------------------------------------- notb
#ifdef MIPP_64BIT
template <> inline reg notb<uint64_t>(const reg v1) { return notb<int64_t>(v1); }
#endif
template <> inline reg notb<uint32_t>(const reg v1) { return notb<int32_t>(v1); }
#ifdef MIPP_BW
template <> inline reg notb<uint16_t>(const reg v1) { return notb<int16_t>(v1); }
template <> inline reg notb<uint8_t >(const reg v1) { return notb<int8_t >(v1); }
#endif

// -------------------------------------------------------------------------------------------------------------- andnb
#ifdef MIPP_64BIT
template <> inline reg andnb<uint64_t>(const reg v1, const reg v2) { return andnb<int64_t>(v1, v2); }
#endif
template <> inline reg andnb<uint32_t>(const reg v1, const reg v2) { return andnb<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg andnb<uint16_t>(const reg v1, const reg v2) { return andnb<int16_t>(v1, v2); }
template <> inline reg andnb<uint8_t >(const reg v1, const reg v2) { return andnb<int8_t >(v1, v2); }
#endif

// ---------------------------------------------------------------------------------------------------------------- orb
#ifdef MIPP_64BIT
template <> inline reg orb<uint64_t>(const reg v1, const reg v2) { return orb<int64_t>(v1, v2); }
#endif
template <> inline reg orb<uint32_t>(const reg v1, const reg v2) { return orb<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg orb<uint16_t>(const reg v1, const reg v2) { return orb<int16_t>(v1, v2); }
template <> inline reg orb<uint8_t >(const reg v1, const reg v2) { return orb<int8_t >(v1, v2); }
#endif

// --------------------------------------------------------------------------------------------------------------- xorb
#ifdef MIPP_64BIT
template <> inline reg xorb<uint64_t>(const reg v1, const reg v2) { return xorb<int64_t>(v1, v2); }
#endif
template <> inline reg xorb<uint32_t>(const reg v1, const reg v2) { return xorb<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg xorb<uint16_t>(const reg v1, const reg v2) { return xorb<int16_t>(v1, v2); }
template <> inline reg xorb<uint8_t >(const reg v1, const reg v2) { return xorb<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------------- lshift
#ifdef MIPP_64BIT
template <> inline reg lshift<uint64_t>(const reg v1, const uint32_t n) { return lshift<int64_t>(v1, n); }
#endif
template <> inline reg lshift<uint32_t>(const reg v1, const uint32_t n) { return lshift<int32_t>(v1, n); }
#ifdef MIPP_BW
template <> inline reg lshift<uint16_t>(const reg v1, const uint32_t n) { return lshift<int16_t>(v1, n); }
template <> inline reg lshift<uint8_t >(const reg v1, const uint32_t n) { return lshift<int8_t >(v1, n); }
#endif

// ------------------------------------------------------------------------------------------------------------ lshiftr
#ifdef MIPP_64BIT
template <> inline reg lshiftr<uint64_t>(const reg v1, const reg v2) { return lshiftr<int64_t>(v1, v2); }
#endif
template <> inline reg lshiftr<uint32_t>(const reg v1, const reg v2) { return lshiftr<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg lshiftr<uint16_t>(const reg v1, const reg v2) { return lshiftr<int16_t>(v1, v2); }
template <> inline reg lshiftr<uint8_t >(const reg v1, const reg v2) { return lshiftr<int8_t >(v1, v2); }
#endif

// ------------------------------------------------------------------------------------------------------------- rshift
#ifdef MIPP_64BIT
template <> inline reg rshift<uint64_t>(const reg v1, const uint32_t n) { return rshift<int64_t>(v1, n); }
#endif
template <> inline reg rshift<uint32_t>(const reg v1, const uint32_t n) { return rshift<int32_t>(v1, n); }
#ifdef MIPP_BW
template <> inline reg rshift<uint16_t>(const reg v1, const uint32_t n) { return rshift<int16_t>(v1, n); }
template <> inline reg rshift<uint8_t >(const reg v1, const uint32_t n) { return rshift<int8_t >(v1, n); }
#endif

// ------------------------------------------------------------------------------------------------------------ rshiftr
#ifdef MIPP_64BIT
template <> inline reg rshiftr<uint64_t>(const reg v1, const reg v2) { return rshiftr<int64_t>(v1, v2); }
#endif
template <> inline reg rshiftr<uint32_t>(const reg v1, const reg v2) { return rshiftr<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline reg rshiftr<uint16_t>(const reg v1, const reg v2) { return rshiftr<int16_t>(v1, v2); }
template <> inline reg rshiftr<uint8_t >(const reg v1, const reg v2) { return rshiftr<int8_t >(v1, v2); }
#endif

// -------------------------------------------------------------------------------------------------------------- blend
#ifdef MIPP_64BIT
template <> inline reg blend<uint64_t>(const reg v1, const reg v2, const msk m) { return blend<int64_t>(v1, v2, m); }
#endif
template <> inline reg blend<uint32_t>(const reg v1, const reg v2, const msk m) { return blend<int32_t>(v1, v2, m); }
#ifdef MIPP_BW
template <> inline reg blend<uint16_t>(const reg v1, const reg v2, const msk m) { return blend<int16_t>(v1, v2, m); }
template <> inline reg blend<uint8_t >(const reg v1, const reg v2, const msk m) { return blend<int8_t >(v1, v2, m); }
#endif

// -------------------------------------------------------------------------------------------------------------- cmpeq
#ifdef MIPP_64BIT
template <> inline msk cmpeq<uint64_t>(const reg v1, const reg v2) { return cmpeq<int64_t>(v1, v2); };
#endif
template <> inline msk cmpeq<uint32_t>(const reg v1, const reg v2) { return cmpeq<int32_t>(v1, v2); };
#ifdef MIPP_BW
template <> inline msk cmpeq<uint16_t>(const reg v1, const reg v2) { return cmpeq<int16_t>(v1, v2); };
template <> inline msk cmpeq<uint8_t >(const reg v1, const reg v2) { return cmpeq<int8_t >(v1, v2); };
#endif

// ------------------------------------------------------------------------------------------------------------- cmpneq
#ifdef MIPP_64BIT
template <> inline msk cmpneq<uint64_t>(const reg v1, const reg v2) { return cmpneq<int64_t>(v1, v2); };
#endif
template <> inline msk cmpneq<uint32_t>(const reg v1, const reg v2) { return cmpneq<int32_t>(v1, v2); };
#ifdef MIPP_BW
template <> inline msk cmpneq<uint16_t>(const reg v1, const reg v2) { return cmpneq<int16_t>(v1, v2); };
template <> inline msk cmpneq<uint8_t >(const reg v1, const reg v2) { return cmpneq<int8_t >(v1, v2); };
#endif

// ---------------------------------------------------------------------------------------------------------------- msb
#ifdef MIPP_64BIT
template <> inline reg msb<uint64_t>(const reg v1) { return msb<int64_t>(v1); }
#endif
template <> inline reg msb<uint32_t>(const reg v1) { return msb<int32_t>(v1); }
#ifdef MIPP_BW
template <> inline reg msb<uint16_t>(const reg v1) { return msb<int16_t>(v1); }
template <> inline reg msb<uint8_t >(const reg v1) { return msb<int8_t >(v1); }
#endif

// --------------------------------------------------------------------------------------------------------------- sign
#ifdef MIPP_64BIT
template <> inline msk sign<uint64_t>(const reg v1) { return sign<int64_t>(v1); }
#endif
template <> inline msk sign<uint32_t>(const reg v1) { return sign<int32_t>(v1); }
#ifdef MIPP_BW
template <> inline msk sign<uint16_t>(const reg v1) { return sign<int16_t>(v1); }
template <> inline msk sign<uint8_t >(const reg v1) { return sign<int8_t >(v1); }
#endif

// --------------------------------------------------------------------------------------------------------------- lrot
#ifdef MIPP_64BIT
template <> inline reg lrot<uint64_t>(const reg v1) { return lrot<int64_t>(v1); }
#endif
template <> inline reg lrot<uint32_t>(const reg v1) { return lrot<int32_t>(v1); }
#ifdef MIPP_BW
template <> inline reg lrot<uint16_t>(const reg v1) { return lrot<int16_t>(v1); }
template <> inline reg lrot<uint8_t >(const reg v1) { return lrot<int8_t >(v1); }
#endif

// --------------------------------------------------------------------------------------------------------------- rrot
#ifdef MIPP_64BIT
template <> inline reg rrot<uint64_t>(const reg v1) { return rrot<int64_t>(v1); }
#endif
template <> inline reg rrot<uint32_t>(const reg v1) { return rrot<int32_t>(v1); }
#ifdef MIPP_BW
template <> inline reg rrot<uint16_t>(const reg v1) { return rrot<int16_t>(v1); }
template <> inline reg rrot<uint8_t >(const reg v1) { return rrot<int8_t >(v1); }
#endif

// --------------------------------------------------------------------------------------------------------------- div2
#ifdef MIPP_64BIT
template <> inline reg div2<uint64_t>(const reg v1) { return rshift<uint64_t>(v1, 1); }
#endif
template <> inline reg div2<uint32_t>(const reg v1) { return rshift<uint32_t>(v1, 1); }
#ifdef MIPP_BW
template <> inline reg div2<uint16_t>(const reg v1) { return rshift<uint16_t>(v1, 1); }
template <> inline reg div2<uint8_t >(const reg v1) { return rshift<uint8_t >(v1, 1); }
#endif

// --------------------------------------------------------------------------------------------------------------- div4
#ifdef MIPP_64BIT
template <> inline reg div4<uint64_t>(const reg v1) { return rshift<uint64_t>(v1, 2); }
#endif
template <> inline reg div4<uint32_t>(const reg v1) { return rshift<uint32_t>(v1, 2); }
#ifdef MIPP_BW
template <> inline reg div4<uint16_t>(const reg v1) { return rshift<uint16_t>(v1, 2); }
template <> inline reg div4<uint8_t >(const reg v1) { return rshift<uint8_t >(v1, 2); }
#endif

// -------------------------------------------------------------------------------------------------------------- testz
#ifdef MIPP_64BIT
template <> inline bool testz<uint64_t>(const reg v1, const reg v2) { return testz<int64_t>(v1, v2); }
#endif
template <> inline bool testz<uint32_t>(const reg v1, const reg v2) { return testz<int32_t>(v1, v2); }
#ifdef MIPP_BW
template <> inline bool testz<uint16_t>(const reg v1, const reg v2) { return testz<int16_t>(v1, v2); }
template <> inline bool testz<uint8_t >(const reg v1, const reg v2) { return testz<int8_t >(v1, v2); }
#endif

// ----------------------------------------------------------------------------------- implicit conversions and packing
#ifndef MIPP_NO_INTRINSICS
template <> inline mipp::Reg<double  >::Reg(const mipp::Reg_2<float   > r_2) : r(mipp::cvt<float,    double  >(r_2.r)) {}
template <> inline mipp::Reg<int64_t >::Reg(const mipp::Reg_2<int32_t > r_2) : r(mipp::cvt<int32_t,  int64_t >(r_2.r)) {}
template <> inline mipp::Reg<int32_t >::Reg(const mipp::Reg_2<int16_t > r_2) : r(mipp::cvt<int16_t,  int32_t >(r_2.r)) {}
template <> inline mipp::Reg<int16_t >::Reg(const mipp::Reg_2<int8_t  > r_2) : r(mipp::cvt<int8_t,   int16_t >(r_2.r)) {}
template <> inline mipp::Reg<uint64_t>::Reg(const mipp::Reg_2<uint32_t> r_2) : r(mipp::cvt<uint32_t, uint64_t>(r_2.r)) {}
template <> inline mipp::Reg<uint32_t>::Reg(const mipp::Reg_2<uint16_t> r_2) : r(mipp::cvt<uint16_t, uint32_t>(r_2.r)) {}
template <> inline mipp::Reg<uint16_t>::Reg(const mipp::Reg_2<uint8_t > r_2) : r(mipp::cvt<uint8_t,  uint16_t>(r_2.r)) {}

template <> inline mipp::Reg<float   >::Reg(const mipp::Regx2<double  > rx2) : r(mipp::pack<float,    double  >(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<int32_t >::Reg(const mipp::Regx2<int64_t > rx2) : r(mipp::pack<int64_t,  int32_t >(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<int16_t >::Reg(const mipp::Regx2<int32_t > rx2) : r(mipp::pack<int32_t,  int16_t >(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<int8_t  >::Reg(const mipp::Regx2<int16_t > rx2) : r(mipp::pack<int16_t,  int8_t  >(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<uint32_t>::Reg(const mipp::Regx2<uint64_t> rx2) : r(mipp::pack<uint64_t, uint32_t>(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<uint16_t>::Reg(const mipp::Regx2<uint32_t> rx2) : r(mipp::pack<uint32_t, uint16_t>(rx2.val[0].r, rx2.val[1].r)) {}
template <> inline mipp::Reg<uint8_t >::Reg(const mipp::Regx2<uint16_t> rx2) : r(mipp::pack<uint16_t, uint8_t >(rx2.val[0].r, rx2.val[1].r)) {}

template <> inline mipp::Reg<float   >::Reg(const mipp::Reg<double  > r1, const mipp::Reg<double  > r2) : r(mipp::pack<float,    double  >(r1.r, r2.r)) {}
template <> inline mipp::Reg<int32_t >::Reg(const mipp::Reg<int64_t > r1, const mipp::Reg<int64_t > r2) : r(mipp::pack<int64_t,  int32_t >(r1.r, r2.r)) {}
template <> inline mipp::Reg<int16_t >::Reg(const mipp::Reg<int32_t > r1, const mipp::Reg<int32_t > r2) : r(mipp::pack<int32_t,  int16_t >(r1.r, r2.r)) {}
template <> inline mipp::Reg<int8_t  >::Reg(const mipp::Reg<int16_t > r1, const mipp::Reg<int16_t > r2) : r(mipp::pack<int16_t,  int8_t  >(r1.r, r2.r)) {}
template <> inline mipp::Reg<uint32_t>::Reg(const mipp::Reg<uint64_t> r1, const mipp::Reg<uint64_t> r2) : r(mipp::pack<uint64_t, uint32_t>(r1.r, r2.r)) {}
template <> inline mipp::Reg<uint16_t>::Reg(const mipp::Reg<uint32_t> r1, const mipp::Reg<uint32_t> r2) : r(mipp::pack<uint32_t, uint16_t>(r1.r, r2.r)) {}
template <> inline mipp::Reg<uint8_t >::Reg(const mipp::Reg<uint16_t> r1, const mipp::Reg<uint16_t> r2) : r(mipp::pack<uint16_t, uint8_t >(r1.r, r2.r)) {}
#endif
}
#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */
