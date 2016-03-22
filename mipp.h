/*
Copyright (c) 1998, Regents of the University of California
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the University of California, Berkeley nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * mipp.h
 *
 *  Created on: 5 oct. 2014
 *      Author: Adrien Cassagne
 */

#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#if defined(__ARM_NEON__) || defined(__ARM_NEON)
#include "arm_neon.h"
#elif defined(__SSE__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
#include "immintrin.h"
#ifdef __SSE__
#include "xmmintrin.h"
#endif
#ifdef __SSE2__
#include "emmintrin.h"
#endif
#ifdef __SSE3__
#include "pmmintrin.h"
#endif
#ifdef __SSSE3__
#include "tmmintrin.h"
#endif
#ifdef __SSE4_1__
#include "smmintrin.h"
#endif
#endif

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cassert>
#include <string>
#include <vector>
#include <map>

namespace mipp // My Intrinsics Plus Plus => mipp
{
// ------------------------------------------------------------------------------------------ myIntrinsics vector sizes
// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------- ARM NEON-128
#if defined(__ARM_NEON__) || defined(__ARM_NEON)
	#define REQUIRED_ALIGNMENT 16
	constexpr int RequiredAlignment = REQUIRED_ALIGNMENT;
	constexpr int RegisterSizeBit = 128;

	using reg = float32x4_t;

	const std::string IntructionsType = "ARM NEONv1-128";

// -------------------------------------------------------------------------------------------------------- X86 AVX-512
#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
	#define REQUIRED_ALIGNMENT 64
	constexpr int RequiredAlignment = REQUIRED_ALIGNMENT;
	constexpr int RegisterSizeBit = 512;

	using reg = __m512;

	const std::string IntructionsType = "x86 AVX-512";

// -------------------------------------------------------------------------------------------------------- X86 AVX-256
#elif defined(__AVX__)
	#define REQUIRED_ALIGNMENT 32
	constexpr int RequiredAlignment = REQUIRED_ALIGNMENT;
	constexpr int RegisterSizeBit = 256;

	using reg = __m256;

#ifdef __AVX2__
	const std::string IntructionsType = "x86 AVX2-256";
#else
	const std::string IntructionsType = "x86 AVX1-256";
#endif

// -------------------------------------------------------------------------------------------------------- X86 SSE-128
#elif defined(__SSE__)
	#define REQUIRED_ALIGNMENT 16
	constexpr int RequiredAlignment = REQUIRED_ALIGNMENT;
	constexpr int RegisterSizeBit = 128;

	using reg = __m128;

#ifdef __SSE4_2__
	const std::string IntructionsType = "x86 SSE4.2-128";
#elif defined(__SSE4_1__)
	const std::string IntructionsType = "x86 SSE4.1-128";
#elif defined(__SSSE3__)
	const std::string IntructionsType = "x86 SSSE3-128";
#elif defined(__SSE3__)
	const std::string IntructionsType = "x86 SSE3-128";
#elif defined(__SSE2__)
	const std::string IntructionsType = "x86 SSE2-128";
#else
	const std::string IntructionsType = "x86 SSE1-128";
#endif

// ---------------------------------------------------------------------------------------------------------- UNDEFINED
#else
	#define REQUIRED_ALIGNMENT 0
	constexpr int RequiredAlignment = REQUIRED_ALIGNMENT;
	constexpr int RegisterSizeBit = 0;

	using reg = int;

	const std::string IntructionsType = "UNDEFINED";

#endif

template <typename T>
constexpr int nElmtsPerRegister() { return RegisterSizeBit / (8 * sizeof(T)); }

template <typename T>
constexpr int nElReg() { return mipp::nElmtsPerRegister<T>(); }

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------- memory allocator
template <typename T>
T* malloc(int nData)
{
	T* ptr = nullptr;

#if defined(__SSE2__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
	ptr = (T*)_mm_malloc(nData * sizeof(T), mipp::RequiredAlignment);
#else
	ptr = new T[nData];
#endif

	return ptr;
}

template <typename T>
void free(T* ptr)
{
#if defined(__SSE2__) || defined(__AVX__) || defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
	_mm_free(ptr);
#else
	delete[] ptr;
#endif
}

template <class T>
struct AlignedAllocator
{
	typedef T value_type;
	AlignedAllocator() { }
	template <class C> AlignedAllocator(const AlignedAllocator<C>& other) { }
	T* allocate(std::size_t n) { return mipp::malloc<T>((int)n); }
	void deallocate(T* p, std::size_t n) { mipp::free<T>(p); }
};

// returns true if and only if storage allocated from ma1 can be deallocated from ma2, and vice versa.
// always returns true for stateless allocators.
template <class C1, class C2>
bool operator==(const AlignedAllocator<C1>& ma1, const AlignedAllocator<C2>& ma2) { return true; }

template <class C1, class C2>
bool operator!=(const AlignedAllocator<C1>& ma1, const AlignedAllocator<C2>& ma2) { return !(ma1 == ma2); }

// override vector type
template<class T> using vector = std::vector<T, AlignedAllocator<T>>;

// --------------------------------------------------------------------------------------------------- memory allocator
// --------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------- myIntrinsics prototypes
// --------------------------------------------------------------------------------------------------------------------

template <typename T>
static void errorMessage(std::string instr)
{
	// define type names
	std::unordered_map<std::type_index,std::string> type_names;
	type_names[typeid(char)]                   = "char";
	type_names[typeid(unsigned char)]          = "unsigned char";
	type_names[typeid(signed char)]            = "signed char";
	type_names[typeid(short)]                  = "short";
	type_names[typeid(short int)]              = "short int";
	type_names[typeid(unsigned short)]         = "unsigned short";
	type_names[typeid(unsigned short int)]     = "unsigned short int";
	type_names[typeid(signed short)]           = "signed short";
	type_names[typeid(signed short int)]       = "signed short int";
	type_names[typeid(int)]                    = "int";
	type_names[typeid(unsigned)]               = "unsigned";
	type_names[typeid(unsigned int)]           = "unsigned int";
	type_names[typeid(signed int)]             = "signed int";
	type_names[typeid(long)]                   = "long";
	type_names[typeid(long int)]               = "long int";
	type_names[typeid(unsigned long)]          = "unsigned long";
	type_names[typeid(unsigned long int)]      = "unsigned long int";
	type_names[typeid(signed long)]            = "signed long";
	type_names[typeid(signed long int)]        = "signed long int";
	type_names[typeid(long long)]              = "long long";
	type_names[typeid(long long int)]          = "long long int";
	type_names[typeid(unsigned long long)]     = "unsigned long long";
	type_names[typeid(unsigned long long int)] = "unsigned long long int";
	type_names[typeid(signed long long)]       = "signed long long";
	type_names[typeid(signed long long int)]   = "signed long long int";
	type_names[typeid(float)]                  = "float";
	type_names[typeid(double)]                 = "double";

	if (RegisterSizeBit == 0)
		std::cerr << "Undefined type of instructions, try to add -mfpu=neon, -msse4.2, -mavx, -march=native... "
		          << "at the compile time." << std::endl;
	std::cerr << "mipp::" << instr << "<" << type_names[typeid(T)] << "> (" << IntructionsType << ") is undefined! "
	          << "Program halting..." << std::endl;
}

template <typename T1, typename T2>
static void errorMessage(std::string instr)
{
	// define type names
	std::unordered_map<std::type_index,std::string> type_names;
	type_names[typeid(char)]                   = "char";
	type_names[typeid(unsigned char)]          = "unsigned char";
	type_names[typeid(signed char)]            = "signed char";
	type_names[typeid(short)]                  = "short";
	type_names[typeid(short int)]              = "short int";
	type_names[typeid(unsigned short)]         = "unsigned short";
	type_names[typeid(unsigned short int)]     = "unsigned short int";
	type_names[typeid(signed short)]           = "signed short";
	type_names[typeid(signed short int)]       = "signed short int";
	type_names[typeid(int)]                    = "int";
	type_names[typeid(unsigned)]               = "unsigned";
	type_names[typeid(unsigned int)]           = "unsigned int";
	type_names[typeid(signed int)]             = "signed int";
	type_names[typeid(long)]                   = "long";
	type_names[typeid(long int)]               = "long int";
	type_names[typeid(unsigned long)]          = "unsigned long";
	type_names[typeid(unsigned long int)]      = "unsigned long int";
	type_names[typeid(signed long)]            = "signed long";
	type_names[typeid(signed long int)]        = "signed long int";
	type_names[typeid(long long)]              = "long long";
	type_names[typeid(long long int)]          = "long long int";
	type_names[typeid(unsigned long long)]     = "unsigned long long";
	type_names[typeid(unsigned long long int)] = "unsigned long long int";
	type_names[typeid(signed long long)]       = "signed long long";
	type_names[typeid(signed long long int)]   = "signed long long int";
	type_names[typeid(float)]                  = "float";
	type_names[typeid(double)]                 = "double";

	if (RegisterSizeBit == 0)
		std::cerr << "Undefined type of instructions, try to add -mfpu=neon, -msse4.2, -mavx, -march=native... "
		          << "at the compile time." << std::endl;
	std::cerr << "mipp::" << instr << "<" << type_names[typeid(T1)] << "," << type_names[typeid(T2)] << "> (" 
	          << IntructionsType << ") is undefined! Program halting..." << std::endl;
}

template <typename T> inline reg  load  (const T*)                        { errorMessage<T>("load");   exit(-1); }
template <typename T> inline reg  loadu (const T*)                        { errorMessage<T>("loadu");  exit(-1); }
template <typename T> inline void store (T*, const reg)                   { errorMessage<T>("store");  exit(-1); }
template <typename T> inline void storeu(T*, const reg)                   { errorMessage<T>("storeu"); exit(-1); }
template <typename T> inline reg  set1  (const T)                         { errorMessage<T>("set1");   exit(-1); }
template <typename T> inline reg  set0  ()                                { errorMessage<T>("set0");   exit(-1); }
template <typename T> inline reg  andb  (const reg, const reg)            { errorMessage<T>("andb");   exit(-1); }
template <typename T> inline reg  andnb (const reg, const reg)            { errorMessage<T>("andnb");  exit(-1); }
template <typename T> inline reg  orb   (const reg, const reg)            { errorMessage<T>("orb");    exit(-1); }
template <typename T> inline reg  xorb  (const reg, const reg)            { errorMessage<T>("xorb");   exit(-1); }
template <typename T> inline reg  hxorb (const reg)                       { errorMessage<T>("hxorb");  exit(-1); }
template <typename T> inline reg  lshift(const reg, const int)            { errorMessage<T>("lshift"); exit(-1); }
template <typename T> inline reg  rshift(const reg, const int)            { errorMessage<T>("rshift"); exit(-1); }
template <typename T> inline reg  cmpeq (const reg, const reg)            { errorMessage<T>("cmpeq");  exit(-1); }
template <typename T> inline reg  cmpneq(const reg, const reg)            { errorMessage<T>("cmpneq"); exit(-1); }
template <typename T> inline reg  cmple (const reg, const reg)            { errorMessage<T>("cmple");  exit(-1); }
template <typename T> inline reg  cmplt (const reg, const reg)            { errorMessage<T>("cmplt");  exit(-1); }
template <typename T> inline reg  add   (const reg, const reg)            { errorMessage<T>("add");    exit(-1); }
template <typename T> inline reg  sum   (const reg)                       { errorMessage<T>("sum");    exit(-1); }
template <typename T> inline reg  sub   (const reg, const reg)            { errorMessage<T>("sub");    exit(-1); }
template <typename T> inline reg  mul   (const reg, const reg)            { errorMessage<T>("mul");    exit(-1); }
template <typename T> inline reg  div   (const reg, const reg)            { errorMessage<T>("div");    exit(-1); }
template <typename T> inline reg  min   (const reg, const reg)            { errorMessage<T>("min");    exit(-1); }
template <typename T> inline reg  hmin  (const reg)                       { errorMessage<T>("hmin");   exit(-1); }
template <typename T> inline reg  max   (const reg, const reg)            { errorMessage<T>("max");    exit(-1); }
template <typename T> inline reg  sign  (const reg)                       { errorMessage<T>("sign");   exit(-1); }
template <typename T> inline reg  sign  (const reg, const reg)            { errorMessage<T>("sign");   exit(-1); }
template <typename T> inline reg  neg   (const reg, const reg)            { errorMessage<T>("neg");    exit(-1); }
template <typename T> inline reg  abs   (const reg)                       { errorMessage<T>("abs");    exit(-1); }
template <typename T> inline reg  sqrt  (const reg)                       { errorMessage<T>("sqrt");   exit(-1); }
template <typename T> inline reg  rsqrt (const reg)                       { errorMessage<T>("rsqrt");  exit(-1); }
template <typename T> inline reg  fmadd (const reg, const reg, const reg) { errorMessage<T>("fmadd");  exit(-1); }
template <typename T> inline reg  fnmadd(const reg, const reg, const reg) { errorMessage<T>("fnmadd"); exit(-1); }
template <typename T> inline reg  fmsub (const reg, const reg, const reg) { errorMessage<T>("fmsub");  exit(-1); }
template <typename T> inline reg  rot   (const reg)                       { errorMessage<T>("rot");    exit(-1); }
template <typename T> inline reg  div2  (const reg)                       { errorMessage<T>("div2");   exit(-1); }
template <typename T> inline reg  div4  (const reg)                       { errorMessage<T>("div4");   exit(-1); }
template <typename T> inline reg  sat   (const reg, T, T)                 { errorMessage<T>("sat");    exit(-1); }
template <typename T> inline reg  round (const reg)                       { errorMessage<T>("round");  exit(-1); }

template <typename T1, typename T2> 
inline reg cvt(const reg) {
	errorMessage<T1,T2>("cvt");  
	exit(-1); 
}

template <typename T1, typename T2>
inline reg pack(const reg, const reg) {
	errorMessage<T1,T2>("pack");  
	exit(-1); 
}

// --------------------------------------------------------------------------------------- myIntrinsics implementations
// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------- ARM NEON-128
// --------------------------------------------------------------------------------------------------------------------
#if defined(__ARM_NEON__) || defined(__ARM_NEON)

	// ----------------------------------------------------------------------------------------------------------- load
	template <>
	inline reg load<float>(const float *mem_addr) {
		return vld1q_f32(mem_addr);
	}

	template <>
	inline reg load<int>(const int *mem_addr) {
		return (reg) vld1q_s32(mem_addr);
	}

	template <>
	inline reg load<short>(const short *mem_addr) {
		return (reg) vld1q_s16((int16_t*) mem_addr);
	}

	template <>
	inline reg load<signed char>(const signed char *mem_addr) {
		return (reg) vld1q_s8((int8_t*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- loadu
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return vld1q_f32(mem_addr);
	}

	template <>
	inline reg loadu<int>(const int *mem_addr) {
		return (reg) vld1q_s32(mem_addr);
	}

	template <>
	inline reg loadu<short>(const short *mem_addr) {
		return (reg) vld1q_s16((int16_t*) mem_addr);
	}

	template <>
	inline reg loadu<signed char>(const signed char *mem_addr) {
		return (reg) vld1q_s8((int8_t*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- store
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		vst1q_f32(mem_addr, v);
	}

	template <>
	inline void store<int>(int *mem_addr, const reg v) {
		vst1q_f32((float*) mem_addr, v);
	}

	template <>
	inline void store<short>(short *mem_addr, const reg v) {
		vst1q_s16((int16_t*) mem_addr, (int16x8_t) v);
	}

	template <>
	inline void store<signed char>(signed char *mem_addr, const reg v) {
		vst1q_s8((int8_t*) mem_addr, (int8x16_t) v);
	}

	// --------------------------------------------------------------------------------------------------------- storeu
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		vst1q_f32(mem_addr, v);
	}

	template <>
	inline void storeu<int>(int *mem_addr, const reg v) {
		vst1q_f32((float*) mem_addr, v);
	}

	template <>
	inline void storeu<short>(short *mem_addr, const reg v) {
		vst1q_s16((int16_t*) mem_addr, (int16x8_t) v);
	}

	template <>
	inline void storeu<signed char>(signed char *mem_addr, const reg v) {
		vst1q_s8((int8_t*) mem_addr, (int8x16_t) v);
	}

	// ----------------------------------------------------------------------------------------------------------- set1
	template <>
	inline reg set1<float>(const float val) {
		return vdupq_n_f32(val);
	}

	template <>
	inline reg set1<int>(const int val) {
		return (reg) vdupq_n_s32(val);
	}

	template <>
	inline reg set1<short>(const short val) {
		return (reg) vdupq_n_s16(val);
	}

	template <>
	inline reg set1<signed char>(const signed char val) {
		return (reg) vdupq_n_s8(val);
	}

	// ----------------------------------------------------------------------------------------------------------- set0
	template <>
	inline reg set0<float>() {
		return vdupq_n_f32(0.f);
	}

	template <>
	inline reg set0<int>() {
		return (reg) vdupq_n_s32(0);
	}

	template <>
	inline reg set0<short>() {
		return (reg) vdupq_n_s16(0);
	}

	template <>
	inline reg set0<signed char>() {
		return (reg) vdupq_n_s8(0);
	}

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return (reg) vandq_u32((uint32x4_t) v1, (uint32x4_t) v2);
	}

	template <>
	inline reg andb<short>(const reg v1, const reg v2) {
		return (reg) vandq_u16((uint16x8_t) v1, (uint16x8_t) v2);
	}

	template <>
	inline reg andb<signed char>(const reg v1, const reg v2) {
		return (reg) vandq_u8((uint8x16_t) v1, (uint8x16_t) v2);
	}

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return (reg) vandq_u32(vmvnq_u32((uint32x4_t) v1), (uint32x4_t) v2);
	}

	template <>
	inline reg andnb<short>(const reg v1, const reg v2) {
		return (reg) vandq_u16(vmvnq_u16((uint16x8_t) v1), (uint16x8_t) v2);
	}

	template <>
	inline reg andnb<signed char>(const reg v1, const reg v2) {
		return (reg) vandq_u8(vmvnq_u8((uint8x16_t) v1), (uint8x16_t) v2);
	}


	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return (reg) vorrq_u32((uint32x4_t) v1, (uint32x4_t) v2);
	}

	template <>
	inline reg orb<int>(const reg v1, const reg v2) {
		return (reg) vorrq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg orb<short>(const reg v1, const reg v2) {
		return (reg) vorrq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg orb<signed char>(const reg v1, const reg v2) {
		return (reg) vorrq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return (reg) veorq_u32((uint32x4_t) v1, (uint32x4_t) v2);
	}

	template <>
	inline reg xorb<int>(const reg v1, const reg v2) {
		return (reg) veorq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg xorb<short>(const reg v1, const reg v2) {
		return (reg) veorq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg xorb<signed char>(const reg v1, const reg v2) {
		return (reg) veorq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// --------------------------------------------------------------------------------------------------------- lshift
	template <>
	inline reg lshift<int>(const reg v1, const int n) {
		return (reg) vshlq_u32((uint32x4_t) v1, (int32x4_t)mipp::set1<int>(n));
	}

	template <>
	inline reg lshift<short>(const reg v1, const int n) {
		return (reg) vshlq_u16((uint16x8_t) v1, (int16x8_t)mipp::set1<short>((short) n));
	}

	template <>
	inline reg lshift<signed char>(const reg v1, const int n) {
		return (reg) vshlq_u8((uint8x16_t) v1, (int8x16_t)mipp::set1<signed char>((signed char) n));
	}

	// --------------------------------------------------------------------------------------------------------- rshift
	template <>
	inline reg rshift<int>(const reg v1, const int n) {
		return (reg) vshlq_u32((uint32x4_t) v1, (int32x4_t)mipp::set1<int>(-n));
	}

	template <>
	inline reg rshift<short>(const reg v1, const int n) {
		return (reg) vshlq_u16((uint16x8_t) v1, (int16x8_t)mipp::set1<short>((short)-n));
	}

	template <>
	inline reg rshift<signed char>(const reg v1, const int n) {
		return (reg) vshlq_u8((uint8x16_t) v1, (int8x16_t)mipp::set1<signed char>((signed char)-n));
	}

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline reg cmpeq<float>(const reg v1, const reg v2) {
		return (reg) vceqq_f32(v1, v2);
	}

	template <>
	inline reg cmpeq<int>(const reg v1, const reg v2) {
		return (reg) vceqq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg cmpeq<short>(const reg v1, const reg v2) {
		return (reg) vceqq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg cmpeq<signed char>(const reg v1, const reg v2) {
		return (reg) vceqq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// --------------------------------------------------------------------------------------------------------- cmpneq
	template <>
	inline reg cmpneq<float>(const reg v1, const reg v2) {
		return (reg) vmvnq_u32((uint32x4_t) vceqq_f32(v1, v2));
	}

	template <>
	inline reg cmpneq<int>(const reg v1, const reg v2) {
		return (reg) vmvnq_u32((uint32x4_t) vceqq_s32((int32x4_t) v1, (int32x4_t) v2));
	}

	template <>
	inline reg cmpneq<short>(const reg v1, const reg v2) {
		return (reg) vmvnq_u16((uint16x8_t) vceqq_s16((int16x8_t) v1, (int16x8_t) v2));
	}

	template <>
	inline reg cmpneq<signed char>(const reg v1, const reg v2) {
		return (reg) vmvnq_u8((uint8x16_t) vceqq_s8((int8x16_t) v1, (int8x16_t) v2));
	}

	// ---------------------------------------------------------------------------------------------------------- cmple
	template <>
	inline reg cmple<float>(const reg v1, const reg v2) {
		return (reg) vcleq_f32(v1, v2);
	}

	template <>
	inline reg cmple<int>(const reg v1, const reg v2) {
		return (reg) vcleq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg cmple<short>(const reg v1, const reg v2) {
		return (reg) vcleq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg cmple<signed char>(const reg v1, const reg v2) {
		return (reg) vcleq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ---------------------------------------------------------------------------------------------------------- cmplt
	template <>
	inline reg cmplt<float>(const reg v1, const reg v2) {
		return (reg) vcltq_f32(v1, v2);
	}

	template <>
	inline reg cmplt<int>(const reg v1, const reg v2) {
		return (reg) vcltq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg cmplt<short>(const reg v1, const reg v2) {
		return (reg) vcltq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg cmplt<signed char>(const reg v1, const reg v2) {
		return (reg) vcltq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ add
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return vaddq_f32(v1, v2);
	}

	template <>
	inline reg add<int>(const reg v1, const reg v2) {
		return (reg) vaddq_s32((int32x4_t) v1, (int32x4_t)v2);
	}

	template <>
	inline reg add<short>(const reg v1, const reg v2) {
		return (reg) vqaddq_s16((int16x8_t) v1, (int16x8_t)v2);
	}

	template <>
	inline reg add<signed char>(const reg v1, const reg v2) {
		return (reg) vqaddq_s8((int8x16_t) v1, (int8x16_t)v2);
	}

	// ------------------------------------------------------------------------------------------------------------ sum
	template <>
	inline reg sum<float>(const reg v1) {
		reg v2, v3;
		v2 = add<float>(v1, vextq_f32(v1, v1, 2));
		float32x2_t low  = vrev64_f32(vget_low_f32(v2));
		float32x2_t high = vrev64_f32(vget_high_f32(v2));
		v3 = vcombine_f32(low, high);
		v2 = add<float>(v2, v3);
		return v2;
	}

	template <>
	inline reg sum<signed char>(const reg v1) {
		reg sum, v2;
		sum = add<signed char>(v1, (reg) vextq_s32((int32x4_t) v1, (int32x4_t) v1, 2));

		int32x2_t low1  = vrev64_s32((int32x2_t) vget_low_s32((int32x4_t) sum));
		int32x2_t high1 = vrev64_s32((int32x2_t) vget_high_s32((int32x4_t) sum));
		v2 = (reg) vcombine_s32((int32x2_t) low1, (int32x2_t) high1);
		sum = add<signed char>(sum, v2);

		int16x4_t low2  = vrev32_s16((int16x4_t) vget_low_s32((int32x4_t) sum));
		int16x4_t high2 = vrev32_s16((int16x4_t) vget_high_s32((int32x4_t) sum));
		v2 = (reg) vcombine_s32((int32x2_t) low2, (int32x2_t) high2);
		sum = add<signed char>(sum, v2);

		int8x8_t low3  = vrev16_s8((int8x8_t) vget_low_s32((int32x4_t) sum));
		int8x8_t high3 = vrev16_s8((int8x8_t) vget_high_s32((int32x4_t) sum));
		v2 = (reg) vcombine_s32((int32x2_t) low3, (int32x2_t) high3);
		sum = add<signed char>(sum, v2);

		return sum;
	}

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return vsubq_f32(v1, v2);
	}

	template <>
	inline reg sub<int>(const reg v1, const reg v2) {
		return (reg) vsubq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg sub<short>(const reg v1, const reg v2) {
		return (reg) vqsubq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg sub<signed char>(const reg v1, const reg v2) {
		return (reg) vqsubq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return vmulq_f32(v1, v2);
	}

	// ------------------------------------------------------------------------------------------------------------ div
	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return mul<float>(v1, vrecpeq_f32(v2));
	}

	// ------------------------------------------------------------------------------------------------------------ min
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return vminq_f32(v1, v2);
	}

	template <>
	inline reg min<int>(const reg v1, const reg v2) {
		return (reg) vminq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg min<short>(const reg v1, const reg v2) {
		return (reg) vminq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg min<signed char>(const reg v1, const reg v2) {
		return (reg) vminq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ max
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return vmaxq_f32(v1, v2);
	}

	template <>
	inline reg max<int>(const reg v1, const reg v2) {
		return (reg) vmaxq_s32((int32x4_t) v1, (int32x4_t) v2);
	}

	template <>
	inline reg max<short>(const reg v1, const reg v2) {
		return (reg) vmaxq_s16((int16x8_t) v1, (int16x8_t) v2);
	}

	template <>
	inline reg max<signed char>(const reg v1, const reg v2) {
		return (reg) vmaxq_s8((int8x16_t) v1, (int8x16_t) v2);
	}

	// ----------------------------------------------------------------------------------------------------------- sign
	template <>
	inline reg sign<float>(const reg v1) {
		// sign_mask = 10000000000000000000000000000000 // 32 bits
		const reg sign_mask = set1<int>(0x80000000);

		// indices   = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// sign_mask =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1        =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res       =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, sign_mask);
	}

	template <>
	inline reg sign<float>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<float>(v1, v2);
		    sign_v1_v2 = sign<float>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<short>(const reg v1) {
		const reg sign_mask = set1<short>(0x8000);
		return andb<short>(v1, sign_mask);
	}

	template <>
	inline reg sign<short>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<short>(v1, v2);
		    sign_v1_v2 = sign<short>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<signed char>(const reg v1) {
		const reg sign_mask = set1<signed char>(0x80);
		return andb<signed char>(v1, sign_mask);
	}

	template <>
	inline reg sign<signed char>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<signed char>(v1, v2);
		    sign_v1_v2 = sign<signed char>(sign_v1_v2);
		return sign_v1_v2;
	}

	// ------------------------------------------------------------------------------------------------------------ neg
	template <>
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, v2);
	}

	template <>
	inline reg neg<short>(const reg v1, const reg v2) {
		reg neg_v1 = (reg) vqnegq_s16((int16x8_t) v1);
		reg v2_2   = orb  <short>(v2, set1<short>(1)); // hack to avoid -0 case
		reg mask   = cmplt<short>(v2_2, set0<short>());
		reg res1   = andb <short>(mask, neg_v1);
		reg res2   = andb <short>((reg) vmvnq_s16((int16x8_t) mask), v1);
		reg res    = orb  <short>(res1, res2);
		return res;
	}

	template <>
	inline reg neg<signed char>(const reg v1, const reg v2) {
		reg neg_v1 = (reg) vqnegq_s8((int8x16_t) v1);
		reg v2_2   = orb  <signed char>(v2, set1<signed char>(1)); // hack to avoid -0 case
		reg mask   = cmplt<signed char>(v2_2, set0<signed char>());
		reg res1   = andb <signed char>(mask, neg_v1);
		reg res2   = andb <signed char>((reg) vmvnq_s8((int8x16_t) mask), v1);
		reg res    = orb  <signed char>(res1, res2);
		return res;
	}

	// ------------------------------------------------------------------------------------------------------------ abs
	template <>
	inline reg abs<float>(const reg v1) {
		return vabsq_f32(v1);
	}

	template <>
	inline reg abs<short>(const reg v1) {
		return (reg) vabsq_s16((int16x8_t)v1);
	}

	template <>
	inline reg abs<signed char>(const reg v1) {
		return (reg) vabsq_s8((int8x16_t)v1);
	}

	// ---------------------------------------------------------------------------------------------------------- rsqrt
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return vrsqrteq_f32(v1);
	}

	// ----------------------------------------------------------------------------------------------------------- sqrt
	template <>
	inline reg sqrt<float>(const reg v1) {
		return vrecpeq_f32(rsqrt<float>(v1));
	}

	// ---------------------------------------------------------------------------------------------------------- fmadd
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return add<float>(v3, mul<float>(v1, v2));
	}

	// --------------------------------------------------------------------------------------------------------- fnmadd
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(v3, mul<float>(v1, v2));
	}


	// ---------------------------------------------------------------------------------------------------------- fmsub
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(mul<float>(v1, v2), v3);
	}

	// ------------------------------------------------------------------------------------------------------------ rot
	template <>
	inline reg rot<float>(const reg v1) {
		// make a rotation in:[3, 2 , 1, 0] => out:[0, 3, 2, 1]
		return vextq_f32(v1, v1, 1);
	}

	// ----------------------------------------------------------------------------------------------------------- div2
	template <>
	inline reg div2<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.5f));
	}

	template <>
	inline reg div2<int>(const reg v1) {
		reg abs_v1 = abs<int>(v1);
		reg sh = rshift<int>(abs_v1, 1);
		return neg<int>(sh, v1);
	}

	template <>
	inline reg div2<short>(const reg v1) {
		reg abs_v1 = abs<short>(v1);
		reg sh = rshift<short>(abs_v1, 1);
		return neg<short>(sh, v1);
	}

	template <>
	inline reg div2<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh = rshift<signed char>(abs_v1, 1);
		return neg<signed char>(sh, v1);
	}

	// ----------------------------------------------------------------------------------------------------------- div4
	template <>
	inline reg div4<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.25f));
	}

    template <>
    inline reg div4<int>(const reg v1) {
        reg abs_v1 = abs<int>(v1);
        reg sh = rshift<int>(abs_v1, 2);
        return neg<int>(sh, v1); 
    }    

    template <>
    inline reg div4<short>(const reg v1) {
        reg abs_v1 = abs<short>(v1);
        reg sh = rshift<short>(abs_v1, 2);
        return neg<short>(sh, v1); 
    }    

    template <>
    inline reg div4<signed char>(const reg v1) {
        reg abs_v1 = abs<signed char>(v1);
        reg sh = rshift<signed char>(abs_v1, 2);
        return neg<signed char>(sh, v1); 
    }

	// ------------------------------------------------------------------------------------------------------------ sat
	template <>
	inline reg sat<float>(const reg v1, float min, float max) {
		return mipp::min<float>(mipp::max<float>(v1, set1<float>(min)), set1<float>(max));
	}

	template <>
	inline reg sat<double>(const reg v1, double min, double max) {
		return mipp::min<double>(mipp::max<double>(v1, set1<double>(min)), set1<double>(max));
	}

	template <>
	inline reg sat<int>(const reg v1, int min, int max) {
		return mipp::min<int>(mipp::max<int>(v1, set1<int>(min)), set1<int>(max));
	}

	template <>
	inline reg sat<short>(const reg v1, short min, short max) {
		return mipp::min<short>(mipp::max<short>(v1, set1<short>(min)), set1<short>(max));
	}

	template <>
	inline reg sat<signed char>(const reg v1, signed char min, signed char max) {
		return mipp::min<signed char>(mipp::max<signed char>(v1, set1<signed char>(min)), set1<signed char>(max));
	}

	// ------------------------------------------------------------------------------------------------------------ cvt
	template <>
	inline reg cvt<float,int>(const reg v) {
		return (reg) vcvtq_s32_f32((float32x4_t) v);
	}

	template <>
	inline reg cvt<int,float>(const reg v) {
		return (reg) vcvtq_f32_s32((int32x4_t) v);
	}

	// ---------------------------------------------------------------------------------------------------------- round
	template <>
	inline reg round<float>(const reg v) {
		auto half = mipp::orb<float>(mipp::sign<float>(v), mipp::set1<float>(0.5f));
		auto tmp = mipp::add<float>(v, half);
		return mipp::cvt<int,float>(mipp::cvt<float,int>(tmp));
	}

	// ----------------------------------------------------------------------------------------------------------- pack
	template <>
	inline reg pack<int,short>(const reg v1, const reg v2) {
		return (reg) vcombine_s16(vqmovn_s32((int32x4_t) v1), vqmovn_s32((int32x4_t) v2));
	}

	template <>
	inline reg pack<short,signed char>(const reg v1, const reg v2) {
		return (reg) vcombine_s8(vqmovn_s16((int16x8_t) v1), vqmovn_s16((int16x8_t) v2));
	}

// -------------------------------------------------------------------------------------------------------- X86 AVX-512
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)

	// ----------------------------------------------------------------------------------------------------------- load
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _mm512_load_ps(mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return (__m512) _mm512_load_pd(mem_addr);
	}

	template <>
	inline reg load<int>(const int *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<short>(const short *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<signed char>(const signed char *mem_addr) {
		return (__m512) _mm512_load_ps((const float*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- loadu
#if defined(__AVX512F__)
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return _mm512_loadu_ps(mem_addr);
	}

	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return (__m512) _mm512_loadu_pd(mem_addr);
	}

	template <>
	inline reg loadu<int>(const int *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<short>(const short *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<signed char>(const signed char *mem_addr) {
		return (__m512) _mm512_loadu_ps((const float*) mem_addr);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- store
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_mm512_store_ps(mem_addr, v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_mm512_store_pd(mem_addr, (__m512d) v);
	}

	template <>
	inline void store<int>(int *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<short>(short *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<signed char>(signed char *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	// --------------------------------------------------------------------------------------------------------- storeu
#if defined(__AVX512F__)
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		_mm512_storeu_ps(mem_addr, v);
	}

	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		_mm512_storeu_pd(mem_addr, (__m512d) v);
	}

	template <>
	inline void storeu<int>(int *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<short>(short *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<signed char>(signed char *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set1
#if defined(__AVX512F__)
	template <>
	inline reg set1<float>(const float val) {
		return _mm512_set1_ps(val);
	}

	template <>
	inline reg set1<double>(const double val) {
		return (__m512) _mm512_set1_pd(val);
	}

	template <>
	inline reg set1<int>(const int val) {
		return (reg) _mm512_set1_epi32(val);
	}

	template <>
	inline reg set1<long long>(const long long val) {
		return (reg) _mm512_set1_epi64(val);
	}

	template <>
	inline reg set1<short>(const short val) {
		return (reg) _mm512_set1_epi16(val);
	}

	template <>
	inline reg set1<signed char>(const signed char val) {
		return (reg) _mm512_set1_epi8(val);
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg set1<float>(const float val) {
		float init[16] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val, 
		                                               val, val, val, val, val, val, val, val};
		return load<float>(init);
	}

	template <>
	inline reg set1<double>(const double val) {
		double init[8] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val};
		return load<double>(init);
	}

	template <>
	inline reg set1<int>(const int val) {
		int init[16] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val, 
		                                             val, val, val, val, val, val, val, val};
		return load<int>(init);
	}

	template <>
	inline reg set1<long long>(const long long val) {
		long long init[8] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val};
		return load<long long>(init);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set0
#if defined(__AVX512F__)
	template <>
	inline reg set0<float>() {
		return _mm512_setzero_ps();
	}

	template <>
	inline reg set0<double>() {
		return (__m512) _mm512_setzero_pd();
	}

	template <>
	inline reg set0<int>() {
		return (__m512) _mm512_setzero_si512();
	}

	template <>
	inline reg set0<short>() {
		return (__m512) _mm512_setzero_si512();
	}

	template <>
	inline reg set0<signed char>() {
		return (__m512) _mm512_setzero_si512();
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg set0<float>() {
		return set1<float>(0.f);
	}

	template <>
	inline reg set0<double>() {
		return set1<double>(0.0);
	}

	template <>
	inline reg set0<int>() {
		return set1<int>(0);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return (__m512) _mm512_and_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_and_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andb<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_and_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andb<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_and_si512((__m512i) v1, (__m512i) v2);
	}

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return (__m512) _mm512_andnot_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andnb<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_andnot_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andnb<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_andnot_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg andnb<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_andnot_si512((__m512i) v1, (__m512i) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return (reg) _mm512_or_si512((__m512i)v1, (__m512i)v2);
	}

	template <>
	inline reg orb<double>(const reg v1, const reg v2) {
		return (reg) _mm512_or_si512((__m512i)v1, (__m512i)v2);
	}

	template <>
	inline reg orb<int>(const reg v1, const reg v2) {
		return (reg) _mm512_or_si512((__m512i)v1, (__m512i)v2);
	}

	template <>
	inline reg orb<short>(const reg v1, const reg v2) {
		return (reg) _mm512_or_si512((__m512i)v1, (__m512i)v2);
	}

	template <>
	inline reg orb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm512_or_si512((__m512i)v1, (__m512i)v2);
	}

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return (reg) _mm512_xor_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg xorb<double>(const reg v1, const reg v2) {
		return (reg) _mm512_xor_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg xorb<int>(const reg v1, const reg v2) {
		return (reg) _mm512_xor_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg xorb<short>(const reg v1, const reg v2) {
		return (reg) _mm512_xor_si512((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg xorb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm512_xor_si512((__m512i) v1, (__m512i) v2);
	}

	// --------------------------------------------------------------------------------------------------------- lshift
	template <>
	inline reg lshift<int>(const reg v1, const int n) {
		return (reg) _mm512_slli_epi32 ((__m512i) v1, n);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg lshift<short>(const reg v1, const int n) {
		return (reg) _mm512_slli_epi16 ((__m512i) v1, n);
	}

	template <>
	inline reg lshift<signed char>(const reg v1, const int n) {
		return (reg) _mm512_slli_epi16 ((__m512i) v1, n); // TODO: be carefull here, this is a 16bit shift
	}
#endif

	// --------------------------------------------------------------------------------------------------------- rshift
	template <>
	inline reg rshift<int>(const reg v1, const int n) {
		return (reg) _mm512_srli_epi32 ((__m512i) v1, n);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg rshift<short>(const reg v1, const int n) {
		return (reg) _mm512_srli_epi16 ((__m512i) v1, n);
	}

	template <>
	inline reg rshift<signed char>(const reg v1, const int n) {
		return (reg) _mm512_srli_epi16 ((__m512i) v1, n); // TODO: be carefull here, this is a 16bit shift
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	/*
	template <>
	inline reg cmpeq<float>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_ps_mask(v1, v2, _CMP_EQ_OQ); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpeq<double>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_pd_mask((__m512d) v1, (__m512d) v2, _CMP_EQ_OQ); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpeq<int>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpeq_epi32_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}

#if defined(__AVX512BW__)
	template <>
	inline reg cmpeq<short>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpeq_epi16_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpeq<signed char>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpeq_epi8_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}
#endif
	*/
	// --------------------------------------------------------------------------------------------------------- cmpneq
	/*
	template <>
	inline reg cmpneq<float>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_ps_mask(v1, v2, _CMP_NEQ_OQ); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpneq<double>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_pd_mask((__m512d) v1, (__m512d) v2, _CMP_NEQ_OQ); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpneq<int>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpneq_epi32_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}

#if defined(__AVX512BW__)
	template <>
	inline reg cmpneq<short>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpneq_epi16_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmpneq<signed char>(const reg v1, const reg v2) {
		return (reg) _mm512_cmpneq_epi8_mask((__m512i) v1, (__m512i) v2); // TODO: this intrinsic return a mask...
	}
#endif
	*/
	// ---------------------------------------------------------------------------------------------------------- cmple
	/*
	template <>
	inline reg cmple<float>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_ps_mask(v1, v2, _CMP_LE_OS); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmple<double>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_pd_mask((__m512d) v1, (__m512d) v2, _CMP_LE_OS); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmple<int>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_epi32_mask((__m512d) v1, (__m512d) v2, _CMP_LE_OS); // TODO: this intrinsic return a mask...
	}

#if defined(__AVX512BW__)
	template <>
	inline reg cmple<short>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_epi16_mask((__m512d) v1, (__m512d) v2, _CMP_LE_OS); // TODO: this intrinsic return a mask...
	}

	template <>
	inline reg cmple<signed char>(const reg v1, const reg v2) {
		return (reg) _mm512_cmp_epi8_mask((__m512d) v1, (__m512d) v2, _CMP_LE_OS); // TODO: this intrinsic return a mask...
	}
#endif
	*/
	// ------------------------------------------------------------------------------------------------------------ add
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return _mm512_add_ps(v1, v2);
	}

	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_add_pd((__m512d) v1, (__m512d) v2);
	}

	template <>
	inline reg add<int>(const reg v1, const reg v2) {
		return (__m512) _mm512_add_epi32((__m512i) v1, (__m512i) v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg add<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_adds_epi16((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg add<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_adds_epi16((__m512i) v1, (__m512i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return _mm512_sub_ps(v1, v2);
	}

	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_sub_pd((__m512d) v1, (__m512d) v2);
	}

	template <>
	inline reg sub<int>(const reg v1, const reg v2) {
		return (__m512) _mm512_sub_epi32((__m512i) v1, (__m512i) v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg sub<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_subs_epi16((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg sub<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_subs_epi8((__m512i) v1, (__m512i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return _mm512_mul_ps(v1, v2);
	}

	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_mul_pd((__m512d) v1, (__m512d) v2);
	}

#if defined(__AVX512F__)
	template <>
	inline reg mul<int>(const reg v1, const reg v2) {
		return (__m512) _mm512_mul_epi32((__m512i) v1, (__m512i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ div
#if defined(__AVX512F__)
	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return _mm512_div_ps(v1, v2);
	}

	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_div_pd((__m512d) v1, (__m512d) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ min
#if defined(__AVX512F__)
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm512_min_ps(v1, v2);
	}

	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_min_pd((__m512d) v1, (__m512d) v2);
	}

	template <>
	inline reg min<int>(const reg v1, const reg v2) {
		return (__m512) _mm512_min_epi32((__m512i) v1, (__m512i) v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg min<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_min_epi16((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg min<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_min_epi8((__m512i) v1, (__m512i) v2);
	}
#endif

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm512_gmin_ps(v1, v2);
	}

	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_gmax_pd((__m512d) v1, (__m512d) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ max
#if defined(__AVX512F__)
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm512_max_ps(v1, v2);
	}

	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_max_pd((__m512d) v1, (__m512d) v2);
	}

	template <>
	inline reg max<int>(const reg v1, const reg v2) {
		return (__m512) _mm512_max_epi32((__m512i) v1, (__m512i) v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg max<short>(const reg v1, const reg v2) {
		return (__m512) _mm512_max_epi16((__m512i) v1, (__m512i) v2);
	}

	template <>
	inline reg max<signed char>(const reg v1, const reg v2) {
		return (__m512) _mm512_max_epi8((__m512i) v1, (__m512i) v2);
	}
#endif

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm512_gmax_ps(v1, v2);
	}

	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return (__m512) _mm512_gmax_pd((__m512d) v1, (__m512d) v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sign
	template <>
	inline reg sign<float>(const reg v1) {
		// sign_mask = 10000000000000000000000000000000 // 32 bits
		const reg sign_mask = set1<int>(0x80000000);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, sign_mask);
	}

	template <>
	inline reg sign<float>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<float>(v1, v2);
		    sign_v1_v2 = sign<float>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<double>(const reg v1) {
		// sign_mask = 1000000000000000000000000000000000000000000000000000000000000000 // 64 bits
		const reg sign_mask = set1<long long>(0x8000000000000000);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, sign_mask);
	}

	template <>
	inline reg sign<double>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<double>(v1, v2);
		    sign_v1_v2 = sign<double>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<short>(const reg v1) {
		const reg sign_mask = set1<short>(0x8000);
		return andb<short>(v1, sign_mask);
	}

	template <>
	inline reg sign<signed char>(const reg v1) {
		// sign_mask = 10000000 // 8 bits
		const reg sign_mask = set1<signed char>(0x80);

		// indices = 7  6  5  4  3  2  1  0
		// mask    = 1  0  0  0  0  0  0  0
		// v1      = h  g  f  e  d  c  b  a
		// res     = h  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<signed char>(v1, sign_mask);
	}

	template <>
	inline reg sign<short>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<short>(v1, v2);
		    sign_v1_v2 = sign<short>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<signed char>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<signed char>(v1, v2);
		    sign_v1_v2 = sign<signed char>(sign_v1_v2);
		return sign_v1_v2;
	}

	// ------------------------------------------------------------------------------------------------------------ neg
	template <>
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, v2);
	}

	template <>
	inline reg neg<double>(const reg v1, const reg v2) {
		return xorb<double>(v1, v2);
	}

	// ------------------------------------------------------------------------------------------------------------ abs
	template <>
	inline reg abs<float>(const reg v1) {
		return _mm512_abs_ps(v1);
	}

	template <>
	inline reg abs<double>(const reg v1) {
		return (reg) _mm512_abs_pd((__m512d) v1);
	}

	// ----------------------------------------------------------------------------------------------------------- sqrt
#if defined(__AVX512F__)
	template <>
	inline reg sqrt<float>(const reg v1) {
		return _mm512_sqrt_ps(v1);
	}

	template <>
	inline reg sqrt<double>(const reg v1) {
		return (__m512) _mm512_sqrt_pd((__m512d) v1);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- rsqrt
#if defined(__AVX512F__)
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm512_rsqrt14_ps(v1);
	}

	template <>
	inline reg rsqrt<double>(const reg v1) {
		return (__m512) _mm512_rsqrt14_pd((__m512d) v1)
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm512_rsqrt23_ps(v1);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- fmadd
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return (__m512) _mm512_fmadd_pd((__m512d) v1, (__m512d) v2, (__m512d) v3);
	}

	// --------------------------------------------------------------------------------------------------------- fnmadd
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fnmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return (__m512) _mm512_fnmadd_pd((__m512d) v1, (__m512d) v2, (__m512d) v3);
	}

	// ---------------------------------------------------------------------------------------------------------- fmsub
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fmsub_ps(v1, v2, v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return (__m512) _mm512_fmsub_pd((__m512d) v1, (__m512d) v2, (__m512d) v3);
	}

	// ----------------------------------------------------------------------------------------------------------- div2
	template <>
	inline reg div2<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.5f));
	}

	template <>
	inline reg div2<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.5));
	}

	template <>
	inline reg div2<int>(const reg v1) {
		return (reg) _mm512_srai_epi32 ((__m512i) v1, 1);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg div2<short>(const reg v1) {
		return (reg) _mm512_srai_epi16 ((__m512i) v1, 1);
	}

	template <>
	inline reg div2<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 1);
		sh16 = andnb<signed char>(set1<signed char>(0x80), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div4
	template <>
	inline reg div4<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.25f));
	}

	template <>
	inline reg div4<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.25));
	}

	template <>
	inline reg div4<int>(const reg v1) {
		return (reg) _mm512_srai_epi32 ((__m512i) v1, 2);
	}

#if defined(__AVX512BW__)
	template <>
	inline reg div4<short>(const reg v1) {
		return (reg) _mm512_srai_epi16 ((__m512i) v1, 2);
	}

	template <>
	inline reg div4<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 2);
		sh16 = andnb<signed char>(set1<signed char>(0xc0), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sat
	template <>
	inline reg sat<float>(const reg v1, float min, float max) {
		return mipp::min<float>(mipp::max<float>(v1, set1<float>(min)), set1<float>(max));
	}

	template <>
	inline reg sat<double>(const reg v1, double min, double max) {
		return mipp::min<double>(mipp::max<double>(v1, set1<double>(min)), set1<double>(max));
	}

	template <>
	inline reg sat<int>(const reg v1, int min, int max) {
		return mipp::min<int>(mipp::max<int>(v1, set1<int>(min)), set1<int>(max));
	}

	template <>
	inline reg sat<short>(const reg v1, short min, short max) {
		return mipp::min<short>(mipp::max<short>(v1, set1<short>(min)), set1<short>(max));
	}

	template <>
	inline reg sat<signed char>(const reg v1, signed char min, signed char max) {
		return mipp::min<signed char>(mipp::max<signed char>(v1, set1<signed char>(min)), set1<signed char>(max));
	}

// -------------------------------------------------------------------------------------------------------- X86 AVX-256
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__AVX__)

	// ----------------------------------------------------------------------------------------------------------- load
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _mm256_load_ps(mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return (__m256) _mm256_load_pd(mem_addr);
	}

	template <>
	inline reg load<int>(const int *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<short>(const short *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<signed char>(const signed char *mem_addr) {
		return (__m256) _mm256_load_ps((const float*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- loadu
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return _mm256_loadu_ps(mem_addr);
	}

	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return (__m256) _mm256_loadu_pd(mem_addr);
	}

	template <>
	inline reg loadu<int>(const int *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<short>(const short *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<signed char>(const signed char *mem_addr) {
		return (__m256) _mm256_loadu_ps((const float*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- store
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_mm256_store_ps(mem_addr, v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_mm256_store_pd(mem_addr, (__m256d) v);
	}

	template <>
	inline void store<int>(int *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<short>(short *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<signed char>(signed char *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	// --------------------------------------------------------------------------------------------------------- storeu
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		_mm256_storeu_ps(mem_addr, v);
	}

	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		_mm256_storeu_pd(mem_addr, (__m256d) v);
	}

	template <>
	inline void storeu<int>(int *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<short>(short *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<signed char>(signed char *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	// ----------------------------------------------------------------------------------------------------------- set1
	template <>
	inline reg set1<float>(const float val) {
		return _mm256_set1_ps(val);
	}

	template <>
	inline reg set1<double>(const double val) {
		return (__m256) _mm256_set1_pd(val);
	}

	template <>
	inline reg set1<int>(const int val) {
		return (reg) _mm256_set1_epi32(val);
	}

	template <>
	inline reg set1<long long>(const long long val) {
		return (reg) _mm256_set1_epi64x(val);
	}

#ifdef __AVX2__
	template <>
	inline reg set1<short>(const short val) {
		return (reg) _mm256_set1_epi16(val);
	}

	template <>
	inline reg set1<signed char>(const signed char val) {
		return (reg) _mm256_set1_epi8(val);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set0
	template <>
	inline reg set0<float>() {
		return _mm256_setzero_ps();
	}

	template <>
	inline reg set0<double>() {
		return (__m256) _mm256_setzero_pd();
	}

	template <>
	inline reg set0<int>() {
		return (__m256) _mm256_setzero_si256();
	}

	template <>
	inline reg set0<short>() {
		return (__m256) _mm256_setzero_si256();
	}

	template <>
	inline reg set0<signed char>() {
		return (__m256) _mm256_setzero_si256();
	}

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return _mm256_and_ps(v1, v2);
	}

	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_and_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg andb<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_and_si256((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg andb<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_and_si256((__m256i) v1, (__m256i) v2);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return _mm256_andnot_ps(v1, v2);
	}

	template <>
	inline reg andnb<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_andnot_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg andnb<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_andnot_si256((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg andnb<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_andnot_si256((__m256i) v1, (__m256i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return _mm256_or_ps(v1, v2);
	}

	template <>
	inline reg orb<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_or_pd((__m256d) v1, (__m256d) v2);
	}

	template <>
	inline reg orb<int>(const reg v1, const reg v2) {
		return _mm256_or_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg orb<short>(const reg v1, const reg v2) {
		return (reg) _mm256_or_si256((__m256i)v1, (__m256i)v2);
	}

	template <>
	inline reg orb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm256_or_si256((__m256i)v1, (__m256i)v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return _mm256_xor_ps(v1, v2);
	}

	template <>
	inline reg xorb<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_xor_pd((__m256d) v1, (__m256d) v2);
	}

	template <>
	inline reg xorb<int>(const reg v1, const reg v2) {
		return _mm256_xor_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg xorb<short>(const reg v1, const reg v2) {
		return (reg) _mm256_xor_si256((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg xorb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm256_xor_si256((__m256i) v1, (__m256i) v2);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- hxorb
	template <>
	inline reg hxorb<float>(const reg v1) {
		// make an horizontal xor, in:[a, b , c, d, e, f, g, h] =>
		// out:[a^b^c^d^e^f^g^h, a^b^c^d^e^f^g^h, a^b^c^d^e^f^g^h, a^b^c^d^e^f^g^h, ..., ..., ..., ...]
		reg v2;
		v2 = xorb<float>(v1, _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1)));
		v2 = xorb<float>(v2, _mm256_permute_ps     (v2,     _MM_SHUFFLE(1, 0, 3, 2)));
		v2 = xorb<float>(v2, _mm256_permute_ps     (v2,     _MM_SHUFFLE(2, 3, 0, 1)));
		return v2;
	}

	template <>
	inline reg hxorb<double>(const reg v1) {
		// make an horizontal xor, in:[a, b , c, d] => out:[a^b^c^d, a^b^c^d, a^b^c^d, a^b^c^d]
		reg v2;
		v2 = xorb<double>(v1, (reg)_mm256_permute2f128_pd((__m256d) v1, (__m256d) v1, _MM_SHUFFLE(0, 0, 0, 1)));
		v2 = xorb<double>(v2, (reg)_mm256_permute_pd     ((__m256d) v2,               _MM_SHUFFLE(0, 1, 0, 1)));
		return v2;
	}

	// --------------------------------------------------------------------------------------------------------- lshift
#ifdef __AVX2__
	template <>
	inline reg lshift<int>(const reg v1, const int n) {
		return (reg) _mm256_slli_epi32 ((__m256i) v1, n);
	}

	template <>
	inline reg lshift<short>(const reg v1, const int n) {
		return (reg) _mm256_slli_epi16 ((__m256i) v1, n);
	}

	template <>
	inline reg lshift<signed char>(const reg v1, const int n) {
		// TODO: Be careful this is not a shift 8 but a shift 16 bits...
		return (reg) _mm256_slli_epi16 ((__m256i) v1, n);
	}
#else
	template <>
	inline reg lshift<int>(const reg v1, const int n) {
		__m128 v1_lane0, v1_lane1;
		__m256 res = v1;

		// apply left shift on lane 0
		v1_lane0 = _mm256_castps256_ps128(v1);
		v1_lane0 = (__m128) _mm_slli_epi32 ((__m128i) v1_lane0, n);

		// permute lane 0 with lane 1
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1)
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		res = _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));

		// apply left shift on lane 1
		v1_lane1 = _mm256_castps256_ps128(res);
		v1_lane1 = (__m128) _mm_slli_epi32 ((__m128i) v1_lane1, n);

		// convert two SSE-128 registers into one AVX-256 register
		res = _mm256_castps128_ps256(v1_lane0);
		res = _mm256_insertf128_ps(res, v1_lane1, 1);

		return res;
	}
#endif

	// --------------------------------------------------------------------------------------------------------- rshift
#ifdef __AVX2__
	template <>
	inline reg rshift<int>(const reg v1, const int n) {
		return (reg) _mm256_srli_epi32 ((__m256i) v1, n);
	}

	template <>
	inline reg rshift<short>(const reg v1, const int n) {
		return (reg) _mm256_srli_epi16 ((__m256i) v1, n);
	}

	template <>
	inline reg rshift<signed char>(const reg v1, const int n) {
		// TODO: Be careful this is not a shift 8 but a shift 16 bits...
		return (reg) _mm256_srli_epi16 ((__m256i) v1, n);
	}
#else
	template <>
	inline reg rshift<int>(const reg v1, const int n) {
		__m128 v1_lane0, v1_lane1;
		__m256 res = v1;

		// apply left shift on lane 0
		v1_lane0 = _mm256_castps256_ps128(v1);
		v1_lane0 = (__m128) _mm_srli_epi32 ((__m128i) v1_lane0, n);

		// permute lane 0 with lane 1
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1))
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		res = _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));

		// apply left shift on lane 1
		v1_lane1 = _mm256_castps256_ps128(res);
		v1_lane1 = (__m128) _mm_srli_epi32 ((__m128i) v1_lane1, n);

		// convert two SSE-128 registers into one AVX-256 register
		res = _mm256_castps128_ps256(v1_lane0);
		res = _mm256_insertf128_ps(res, v1_lane1, 1);

		return res;
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline reg cmpeq<float>(const reg v1, const reg v2) {
		return _mm256_cmp_ps(v1, v2, _CMP_EQ_OQ);
	}

	template <>
	inline reg cmpeq<double>(const reg v1, const reg v2) {
		return (reg) _mm256_cmp_pd((__m256d) v1, (__m256d) v2, _CMP_EQ_OQ);
	}

#ifdef __AVX2__
	template <>
	inline reg cmpeq<int>(const reg v1, const reg v2) {
		return (reg) _mm256_cmpeq_epi32((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg cmpeq<short>(const reg v1, const reg v2) {
		return (reg) _mm256_cmpeq_epi16((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg cmpeq<signed char>(const reg v1, const reg v2) {
		return (reg) _mm256_cmpeq_epi8((__m256i) v1, (__m256i) v2);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmpneq
	template <>
	inline reg cmpneq<float>(const reg v1, const reg v2) {
		return _mm256_cmp_ps(v1, v2, _CMP_NEQ_OQ);
	}

	template <>
	inline reg cmpneq<double>(const reg v1, const reg v2) {
		return (reg) _mm256_cmp_pd((__m256d) v1, (__m256d) v2, _CMP_NEQ_OQ);
	}

	template <>
	inline reg cmpneq<int>(const reg v1, const reg v2) {
		return _mm256_cmp_ps(v1, v2, _CMP_NEQ_OQ);
	}

	// ---------------------------------------------------------------------------------------------------------- cmple
	template <>
	inline reg cmple<float>(const reg v1, const reg v2) {
		return _mm256_cmp_ps(v1, v2, _CMP_LE_OS);
	}

	template <>
	inline reg cmple<double>(const reg v1, const reg v2) {
		return (reg) _mm256_cmp_pd((__m256d) v1, (__m256d) v2, _CMP_LE_OS);
	}

	// ------------------------------------------------------------------------------------------------------------ add
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return _mm256_add_ps(v1, v2);
	}

	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_add_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg add<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_adds_epi16((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg add<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_adds_epi8((__m256i) v1, (__m256i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sum
	template <>
	inline reg sum<float>(const reg v1) {
		reg v1_switch_lanes = _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));
		reg sum = _mm256_hadd_ps(v1, v1_switch_lanes);
		    sum = _mm256_hadd_ps(sum, sum);
		return _mm256_hadd_ps(sum, sum);
	}

	template <>
	inline reg sum<double>(const reg v1) {
		// make a summation in:[a, b , c, d] => out:[a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
		//
		//   -> _mm256_permute2f128_pd(v1, v1, _MM_SHUFFLE(0, 0, 0, 1)) # switch lanes
		//           l0      l1
		//       in[a, b, | c, d] =>
		//      out[c, d, | a, b]
		//
		//   -> _mm256_hadd_pd(v1, v1_s) # horizontal addition
		//                  l0                      l1
		//      in1[a11      , b11      , | c11      , d11      ] # info: a11 = a21, b11 = b21, c11 = c21, d11 = d21
		//      in2[c21      , d21      , | a21      , b21      ] =>
		//      out[a11 + b11, c21 + d21, | c11 + d11, a21 + b21]
		//
		//   -> _mm256_hadd_pd(sum, sum) # horizontal addition
		//                              l0                                              l1
		//      in1[a11 + b11            , c21 + d21            , | c11 + d11            , a21 + b21            ]
		//      in1[a12 + b12            , c22 + d22            , | c12 + d12            , a22 + b22            ] =>
		//      out[a11 + b11 + c21 + d21, a12 + b12 + c22 + d22, | c11 + d11 + a21 + b21, c12 + d12 + a22 + b22]
		reg v1_switch_lanes = (reg) _mm256_permute2f128_pd((__m256d) v1, (__m256d) v1, _MM_SHUFFLE(0, 0, 0, 1));
		reg sum = (reg) _mm256_hadd_pd((__m256d) v1, (__m256d) v1_switch_lanes);
		return (reg) _mm256_hadd_pd((__m256d) sum, (__m256d) sum);
	}

#ifdef __AVX2__
	template <>
	inline reg sum<signed char>(const reg v1) {
		__m256i mask_16 = _mm256_set_epi8(29, 28, 31, 30, 25, 24, 27, 26, 21, 20, 23, 22, 17, 16, 19, 18, 13, 12, 15,
		                                  14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);
		__m256i mask_8  = _mm256_set_epi8(30, 31, 28, 29, 26, 27, 24, 25, 22, 23, 20, 21, 18, 19, 16, 17, 14, 15, 12,
		                                  13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

		reg sum = v1;
		sum = add<signed char>(sum, (reg)_mm256_permute2f128_si256((__m256i)sum, (__m256i)sum, _MM_SHUFFLE(0,0,0,1)));
		sum = add<signed char>(sum, (reg)_mm256_permute4x64_epi64 ((__m256i)sum,               _MM_SHUFFLE(2,3,0,1)));
		sum = add<signed char>(sum, (reg)_mm256_shuffle_epi32     ((__m256i)sum,               _MM_SHUFFLE(2,3,0,1)));
		sum = add<signed char>(sum, (reg)_mm256_shuffle_epi8      ((__m256i)sum,               mask_16));
		sum = add<signed char>(sum, (reg)_mm256_shuffle_epi8      ((__m256i)sum,               mask_8));
		return sum;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return _mm256_sub_ps(v1, v2);
	}

	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_sub_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg sub<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_subs_epi16 ((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg sub<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_subs_epi8 ((__m256i) v1, (__m256i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return _mm256_mul_ps(v1, v2);
	}

	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_mul_pd((__m256d) v1, (__m256d) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ div
	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return _mm256_div_ps(v1, v2);
	}

	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_div_pd((__m256d) v1, (__m256d) v2);
	}

	// ------------------------------------------------------------------------------------------------------------ min
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm256_min_ps(v1, v2);
	}

	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_min_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg min<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_min_epi16((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg min<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_min_epi8((__m256i) v1, (__m256i) v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- hmin
	template <>
	inline reg hmin<float>(const reg v1) {
		// make an horizontal reduction min, if "a" is the smallest value in the regtor
		// => in:[a, b , c, d, e, f, g, h] => out:[a, a, a, a, a, a, a, a]
		reg v2;
		v2 = min<float>(v1, _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1)));
		v2 = min<float>(v2, _mm256_permute_ps     (v2,     _MM_SHUFFLE(1, 0, 3, 2)));
		v2 = min<float>(v2, _mm256_permute_ps     (v2,     _MM_SHUFFLE(2, 3, 0, 1)));
		return v2;
	}

	template <>
	inline reg hmin<double>(const reg v1) {
		// make an horizontal reduction min, if "a" is the smallest value in the regtor
		// => in:[a, b , c, d] => out:[a, a, a, a]
		reg v2;
		v2 = min<double>(v1, (reg)_mm256_permute2f128_pd((__m256d) v1, (__m256d) v1, _MM_SHUFFLE(0, 0, 0, 1)));
		v2 = min<double>(v2, (reg)_mm256_permute_pd     ((__m256d) v2,               _MM_SHUFFLE(0, 1, 0, 1)));
		return v2;
	}

	// ------------------------------------------------------------------------------------------------------------ max
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm256_max_ps(v1, v2);
	}

	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return (__m256) _mm256_max_pd((__m256d) v1, (__m256d) v2);
	}

#ifdef __AVX2__
	template <>
	inline reg max<short>(const reg v1, const reg v2) {
		return (__m256) _mm256_max_epi16((__m256i) v1, (__m256i) v2);
	}

	template <>
	inline reg max<signed char>(const reg v1, const reg v2) {
		return (__m256) _mm256_max_epi8((__m256i) v1, (__m256i) v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sign
	template <>
	inline reg sign<float>(const reg v1) {
		// sign_mask = 10000000000000000000000000000000 // 32 bits
		const reg sign_mask = set1<int>(0x80000000);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, sign_mask);
	}

	template <>
	inline reg sign<float>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<float>(v1, v2);
		    sign_v1_v2 = sign<float>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<double>(const reg v1) {
		// sign_mask = 1000000000000000000000000000000000000000000000000000000000000000 // 64 bits
		const reg sign_mask = set1<long long>(0x8000000000000000);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, sign_mask);
	}

	template <>
	inline reg sign<double>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<double>(v1, v2);
		    sign_v1_v2 = sign<double>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<short>(const reg v1) {
		const reg sign_mask = set1<short>(0x8000);
		return andb<short>(v1, sign_mask);
	}

	template <>
	inline reg sign<signed char>(const reg v1) {
		// sign_mask = 10000000 // 8 bits
		const reg sign_mask = set1<signed char>(0x80);

		// indices = 7  6  5  4  3  2  1  0
		// mask    = 1  0  0  0  0  0  0  0
		// v1      = h  g  f  e  d  c  b  a
		// res     = h  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<signed char>(v1, sign_mask);
	}

	template <>
	inline reg sign<short>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<short>(v1, v2);
		    sign_v1_v2 = sign<short>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<signed char>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<signed char>(v1, v2);
		    sign_v1_v2 = sign<signed char>(sign_v1_v2);
		return sign_v1_v2;
	}

	// ------------------------------------------------------------------------------------------------------------ neg
	template <>
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, v2);
	}

	template <>
	inline reg neg<double>(const reg v1, const reg v2) {
		return xorb<double>(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg neg<int>(const reg v1, const reg v2) {
		reg v2_2 = orb<int>(v2, set1<int>(1)); // hack to avoid -0 case
		return (reg) _mm256_sign_epi32((__m256i) v1, (__m256i) v2_2);
	}

	template <>
	inline reg neg<short>(const reg v1, const reg v2) {
		reg v2_2 = orb<short>(v2, set1<short>(1)); // hack to avoid -0 case
		return (reg) _mm256_sign_epi16((__m256i) v1, (__m256i) v2_2);
	}

	template <>
	inline reg neg<signed char>(const reg v1, const reg v2) {
		reg v2_2 = orb<signed char>(v2, set1<signed char>(1)); // hack to avoid -0 case
		return (reg) _mm256_sign_epi8((__m256i) v1, (__m256i) v2_2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ abs
	template <>
	inline reg abs<float>(const reg v1) {
		// abs_mask = 01111111111111111111111111111111 // 32 bits
		const reg abs_mask = set1<int>(0x7FFFFFFF);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, abs_mask);
	}

	template <>
	inline reg abs<double>(const reg v1) {
		// abs_mask = 0111111111111111111111111111111111111111111111111111111111111111 // 64 bits
		const reg abs_mask = set1<long long>(0x7FFFFFFFFFFFFFFF);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, abs_mask);
	}

#ifdef __AVX2__
	template <>
	inline reg abs<short>(const reg v1) {
		return (reg) _mm256_abs_epi16((__m256i) v1);
	}

	template <>
	inline reg abs<signed char>(const reg v1) {
		return (reg) _mm256_abs_epi8((__m256i) v1);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sqrt
	template <>
	inline reg sqrt<float>(const reg v1) {
		return _mm256_sqrt_ps(v1);
	}

	template <>
	inline reg sqrt<double>(const reg v1) {
		return (__m256) _mm256_sqrt_pd((__m256d) v1);
	}

	// ---------------------------------------------------------------------------------------------------------- rsqrt
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm256_rsqrt_ps(v1);
	}

	template <>
	inline reg rsqrt<double>(const reg v1) {
		return div<double>(set1<double>(1.0), sqrt<double>(v1));
	}

	// ---------------------------------------------------------------------------------------------------------- fmadd
#ifdef __FMA__
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return (__m256) _mm256_fmadd_pd((__m256d) v1, (__m256d) v2, (__m256d) v3);
	}
#else
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return add<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return add<double>(v3, mul<double>(v1, v2));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- fnmadd
#ifdef __FMA__
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fnmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return (__m256) _mm256_fnmadd_pd((__m256d) v1, (__m256d) v2, (__m256d) v3);
	}
#else
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(v3, mul<double>(v1, v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- fmsub
#ifdef __FMA__
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fmsub_ps(v1, v2, v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return (__m256) _mm256_fmsub_pd((__m256d) v1, (__m256d) v2, (__m256d) v3);
	}
#else
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(mul<float>(v1, v2), v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(mul<double>(v1, v2), v3);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ rot
#ifdef __AVX2__
	template <>
	inline reg rot<float>(const reg v1) {
		// make a rotation in:[7, 6, 5, 4, 3, 2 , 1, 0] => out:[0, 7, 6, 5, 4, 3, 2, 1]
		return _mm256_permutevar8x32_ps(v1, _mm256_setr_epi32(7, 0, 1, 2, 3, 4, 5, 6));
	}

	template <>
	inline reg rot<double>(const reg v1) {
		// make a rotation in:[3, 2 , 1, 0] => out:[0, 3, 2, 1]
		return (__m256) _mm256_permute4x64_pd ((__m256d) v1, _MM_SHUFFLE(2 ,1, 0, 3));
	}
#else
	template <>
	inline reg rot<float>(const reg v1) {
		// make a rotation in:[7, 6, 5, 4, 3, 2 , 1, 0] =>  out:[0, 7, 6, 5, 4, 3, 2, 1]
		//
		//   -> _mm256_permute_ps(a, _MM_SHUFFLE(0, 3, 2, 1)) # rotation per lane of 128 bits
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[4, 5, 6, 7, | 0, 3, 2, 1]
		//
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1)) # switch lanes
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		//
		//   -> _mm256_blend_ps(a, b, _MM_SHUFFLE(2, 0, 2, 0))
		//         ina[7a, 6a, 5a, 4a, 3a, 2a, 1a, 0a]
		//         inb[7b, 6b, 5b, 4b, 3b, 2b, 1b, 0b] =>
		//         out[7b, 6a, 5a, 4a, 3b, 2a, 1a, 0a]
		reg rTmp = _mm256_permute_ps(v1, _MM_SHUFFLE(0, 3, 2, 1));
		return _mm256_blend_ps(rTmp,
							   _mm256_permute2f128_ps(rTmp, rTmp, _MM_SHUFFLE(0, 0, 0, 1)),
							   _MM_SHUFFLE(2, 0, 2, 0));
	}

	template <>
	inline reg rot<double>(const reg v1) {
		// make a rotation in:[3, 2 , 1, 0] => out:[0, 3, 2, 1]
		//
		//   -> _mm256_permute_pd(a, _MM_SHUFFLE(1, 1, 1, 1)) # rotation per lane of 128 bits
		//      /!\ I think this is a wrong shuffle and the good one is: _MM_SHUFFLE(0, 1, 0, 1)
		//           l0      l1
		//       in[3, 2, | 1, 0] =>
		//      out[2, 3, | 0, 1]
		//
		//   -> _mm256_permute2f128_pd(a, a, _MM_SHUFFLE(0, 0, 0, 1)) # switch lanes
		//           l0     l1
		//       in[3, 2, | 1, 0] =>
		//      out[1, 0, | 3, 2]
		//
		//   -> _mm256_blend_pd(a, b, _MM_SHUFFLE(0, 0, 2, 2))
		//      ina[3a, 2a, 1a, 0a] and inb[3b, 2b, 1b, 0b] => out[3b, 2a, 1b, 0a]
		reg rTmp = (__m256) _mm256_permute_pd((__m256d) v1, _MM_SHUFFLE(1, 1, 1, 1));
		return (__m256) _mm256_blend_pd((__m256d) rTmp,
										_mm256_permute2f128_pd((__m256d) rTmp,
															   (__m256d) rTmp,
															   _MM_SHUFFLE(0, 0, 0, 1)),
										_MM_SHUFFLE(0, 0, 2, 2));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div2
	template <>
	inline reg div2<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.5f));
	}

	template <>
	inline reg div2<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.5));
	}

#ifdef __AVX2__
	template <>
	inline reg div2<int>(const reg v1) {
		return (reg) _mm256_srai_epi32 ((__m256i) v1, 1);
	}

	template <>
	inline reg div2<short>(const reg v1) {
		return (reg) _mm256_srai_epi16 ((__m256i) v1, 1);
	}

	template <>
	inline reg div2<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 1);
		sh16 = andnb<signed char>(set1<signed char>(0x80), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div4
	template <>
	inline reg div4<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.25f));
	}

	template <>
	inline reg div4<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.25));
	}

#ifdef __AVX2__
	template <>
	inline reg div4<int>(const reg v1) {
		return (reg) _mm256_srai_epi32 ((__m256i) v1, 2);
	}

	template <>
	inline reg div4<short>(const reg v1) {
		return (reg) _mm256_srai_epi16 ((__m256i) v1, 2);
	}

	template <>
	inline reg div4<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 2);
		sh16 = andnb<signed char>(set1<signed char>(0xc0), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sat
	template <>
	inline reg sat<float>(const reg v1, float min, float max) {
		return mipp::min<float>(mipp::max<float>(v1, set1<float>(min)), set1<float>(max));
	}

	template <>
	inline reg sat<double>(const reg v1, double min, double max) {
		return mipp::min<double>(mipp::max<double>(v1, set1<double>(min)), set1<double>(max));
	}

	template <>
	inline reg sat<int>(const reg v1, int min, int max) {
		return mipp::min<int>(mipp::max<int>(v1, set1<int>(min)), set1<int>(max));
	}

	template <>
	inline reg sat<short>(const reg v1, short min, short max) {
		return mipp::min<short>(mipp::max<short>(v1, set1<short>(min)), set1<short>(max));
	}

	template <>
	inline reg sat<signed char>(const reg v1, signed char min, signed char max) {
		return mipp::min<signed char>(mipp::max<signed char>(v1, set1<signed char>(min)), set1<signed char>(max));
	}

	// ---------------------------------------------------------------------------------------------------------- round
	template <>
	inline reg round<float>(const reg v) {
		return (reg) _mm256_round_ps(v, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
	}

	template <>
	inline reg round<double>(const reg v) {
		return (reg) _mm256_round_pd((__m256d) v, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
	}

	// ------------------------------------------------------------------------------------------------------------ cvt
	template <>
	inline reg cvt<float,int>(const reg v) {
		return (reg) _mm256_cvtps_epi32(v);
	}

	// ----------------------------------------------------------------------------------------------------------- pack
#ifdef __AVX2__
	template <>
	inline reg pack<int,short>(const reg v1, const reg v2) {
		return (reg) _mm256_permute4x64_epi64(_mm256_packs_epi32((__m256i) v1, (__m256i) v2), _MM_SHUFFLE(3, 1, 2, 0));
	}

	template <>
	inline reg pack<short,signed char>(const reg v1, const reg v2) {
		return (reg) _mm256_permute4x64_epi64(_mm256_packs_epi16((__m256i) v1, (__m256i) v2), _MM_SHUFFLE(3, 1, 2, 0));
	}
#endif

// -------------------------------------------------------------------------------------------------------- X86 SSE-128
// --------------------------------------------------------------------------------------------------------------------
#elif defined(__SSE__)

	// ----------------------------------------------------------------------------------------------------------- load
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _mm_load_ps(mem_addr);
	}

#ifdef __SSE2__
	template <>
	inline reg load<double>(const double *mem_addr) {
		return (__m128) _mm_load_pd(mem_addr);
	}
#endif

	template <>
	inline reg load<int>(const int *mem_addr) {
		return _mm_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<short>(const short *mem_addr) {
		return _mm_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<signed char>(const signed char *mem_addr) {
		return _mm_load_ps((const float*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- loadu
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return _mm_loadu_ps(mem_addr);
	}

#ifdef __SSE2__
	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return (__m128) _mm_loadu_pd(mem_addr);
	}
#endif

	template <>
	inline reg loadu<int>(const int *mem_addr) {
		return _mm_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<short>(const short *mem_addr) {
		return _mm_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<signed char>(const signed char *mem_addr) {
		return _mm_loadu_ps((const float*) mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- store
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_mm_store_ps(mem_addr, v);
	}

#ifdef __SSE2__
	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_mm_store_pd(mem_addr, (__m128d) v);
	}
#endif

	template <>
	inline void store<int>(int *mem_addr, const reg v) {
		_mm_store_ps((float*) mem_addr, v);
	}

	template <>
	inline void store<short>(short *mem_addr, const reg v) {
		_mm_store_ps((float*) mem_addr, v);
	}

	template <>
	inline void store<signed char>(signed char *mem_addr, const reg v) {
		_mm_store_ps((float*) mem_addr, v);
	}

	// --------------------------------------------------------------------------------------------------------- storeu
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		_mm_storeu_ps(mem_addr, v);
	}

#ifdef __SSE2__
	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		_mm_storeu_pd(mem_addr, (__m128d) v);
	}
#endif

	template <>
	inline void storeu<int>(int *mem_addr, const reg v) {
		_mm_storeu_ps((float*) mem_addr, v);
	}

	template <>
	inline void storeu<short>(short *mem_addr, const reg v) {
		_mm_storeu_ps((float*) mem_addr, v);
	}

	template <>
	inline void storeu<signed char>(signed char *mem_addr, const reg v) {
		_mm_storeu_ps((float*) mem_addr, v);
	}

	// ----------------------------------------------------------------------------------------------------------- set1
	template <>
	inline reg set1<float>(const float val) {
		return _mm_set1_ps(val);
	}

#ifdef __SSE2__
	template <>
	inline reg set1<double>(const double val) {
		return (__m128) _mm_set1_pd(val);
	}

	template <>
	inline reg set1<int>(const int val) {
		return (reg) _mm_set1_epi32(val);
	}

	template <>
	inline reg set1<short>(const short val) {
		return (reg) _mm_set1_epi16(val);
	}

	template <>
	inline reg set1<signed char>(const signed char val) {
		return (reg) _mm_set1_epi8(val);
	}

	template <>
	inline reg set1<long long>(const long long val) {
		return (reg) _mm_set1_epi64x(val);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set0
	template <>
	inline reg set0<float>() {
		return _mm_setzero_ps();
	}

#ifdef __SSE2__
	template <>
	inline reg set0<double>() {
		return (reg) _mm_setzero_pd();
	}

	template <>
	inline reg set0<int>() {
		return (reg) _mm_setzero_si128();
	}

	template <>
	inline reg set0<short>() {
		return (reg) _mm_setzero_si128();
	}

	template <>
	inline reg set0<signed char>() {
		return (reg) _mm_setzero_si128();
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return _mm_and_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return (__m128) _mm_and_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg andb<int>(const reg v1, const reg v2) {
		return (__m128) _mm_and_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg andb<short>(const reg v1, const reg v2) {
		return (__m128) _mm_and_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg andb<signed char>(const reg v1, const reg v2) {
		return (__m128) _mm_and_si128((__m128i) v1, (__m128i) v2);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return _mm_andnot_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg andnb<double>(const reg v1, const reg v2) {
		return (reg) _mm_andnot_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg andnb<int>(const reg v1, const reg v2) {
		return (reg) _mm_andnot_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg andnb<short>(const reg v1, const reg v2) {
		return (reg) _mm_andnot_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg andnb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm_andnot_si128((__m128i) v1, (__m128i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return _mm_or_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg orb<double>(const reg v1, const reg v2) {
		return (__m128) _mm_or_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg orb<int>(const reg v1, const reg v2) {
		return (reg) _mm_or_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg orb<short>(const reg v1, const reg v2) {
		return (reg) _mm_or_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg orb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm_or_si128((__m128i) v1, (__m128i) v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return _mm_xor_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg xorb<double>(const reg v1, const reg v2) {
		return (__m128) _mm_xor_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg xorb<int>(const reg v1, const reg v2) {
		return (reg) _mm_xor_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg xorb<short>(const reg v1, const reg v2) {
		return (reg) _mm_xor_si128((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg xorb<signed char>(const reg v1, const reg v2) {
		return (reg) _mm_xor_si128((__m128i) v1, (__m128i) v2);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- lshift
#ifdef __SSE2__
	template <>
	inline reg lshift<int>(const reg v1, const int n) {
		return (reg) _mm_slli_epi32 ((__m128i) v1, n);
	}

	template <>
	inline reg lshift<short>(const reg v1, const int n) {
		return (reg) _mm_slli_epi16 ((__m128i) v1, n);
	}

	template <>
	inline reg lshift<signed char>(const reg v1, const int n) {
		return (reg) _mm_slli_epi16 ((__m128i) v1, n); // TODO: Be careful this is not a shift 8 but a shift 16 bits...
	}
#endif

	// --------------------------------------------------------------------------------------------------------- rshift
#ifdef __SSE2__
	template <>
	inline reg rshift<int>(const reg v1, const int n) {
		return (reg) _mm_srli_epi32 ((__m128i) v1, n);
	}

	template <>
	inline reg rshift<short>(const reg v1, const int n) {
		return (reg) _mm_srli_epi16 ((__m128i) v1, n);
	}

	template <>
	inline reg rshift<signed char>(const reg v1, const int n) {
		return (reg) _mm_srli_epi16 ((__m128i) v1, n); // TODO: Be careful this is not a shift 8 but a shift 16 bits...
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline reg cmpeq<float>(const reg v1, const reg v2) {
		return _mm_cmpeq_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg cmpeq<double>(const reg v1, const reg v2) {
		return (reg) _mm_cmpeq_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg cmpeq<int>(const reg v1, const reg v2) {
		return (reg) _mm_cmpeq_epi32((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg cmpeq<short>(const reg v1, const reg v2) {
		return (reg) _mm_cmpeq_epi16((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg cmpeq<signed char>(const reg v1, const reg v2) {
		return (reg) _mm_cmpeq_epi8((__m128i) v1, (__m128i) v2);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmpneq
	template <>
	inline reg cmpneq<float>(const reg v1, const reg v2) {
		return _mm_cmpneq_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg cmpneq<double>(const reg v1, const reg v2) {
		return (reg) _mm_cmpneq_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg cmpneq<int>(const reg v1, const reg v2) {
		return (reg) _mm_cmpneq_ps(v1, v2);
	}

	template <>
	inline reg cmpneq<short>(const reg v1, const reg v2) {
		return (reg) andnb<short>(cmpeq<short>(v1, v2), set1<int>(0xFFFFFFFF));
	}

	template <>
	inline reg cmpneq<signed char>(const reg v1, const reg v2) {
		return (reg) andnb<signed char>(cmpeq<signed char>(v1, v2), set1<int>(0xFFFFFFFF));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmple
	template <>
	inline reg cmple<float>(const reg v1, const reg v2) {
		return _mm_cmple_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg cmple<double>(const reg v1, const reg v2) {
		return (reg) _mm_cmple_pd((__m128d) v1, (__m128d) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ add
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return _mm_add_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return (__m128) _mm_add_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg add<int>(const reg v1, const reg v2) {
		return (__m128) _mm_add_epi32((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg add<short>(const reg v1, const reg v2) {
		return (__m128) _mm_adds_epi16((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg add<signed char>(const reg v1, const reg v2) {
		return (__m128) _mm_adds_epi8((__m128i) v1, (__m128i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sum
#ifdef __SSE3__
	template <>
	inline reg sum<float>(const reg v1) {
		// make a summation in:[a, b , c, d] => out:[a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
		//
		//   -> _mm_hadd_ps(v1, v1) # horizontal addition
		//                  l0                      l1
		//      in1[a11      , b11      , | c11      , d11      ] # info: a11 = a21, b11 = b21, c11 = c21, d11 = d21
		//      in2[a21      , b21      , | c21      , d21      ] =>
		//      out[a11 + b11, c11 + d11, | a21 + b21, c21 + d21]
		//
		//   -> _mm_hadd_ps(out, out) # horizontal addition
		//                              l0                                              l1
		//      in1[a11 + b11            , c11 + d11            , | a21 + b21            , c21 + d21            ]
		//      in2[a12 + b12            , c12 + d12            , | a22 + b22            , c22 + d22            ] =>
		//      out[a11 + b11 + c11 + d11, a21 + b21 + c21 + d21, | a12 + b12 + c12 + d12, a22 + b22 + c22 + d22]
		reg sum = _mm_hadd_ps(v1, v1);
		return _mm_hadd_ps(sum, sum);
	}

	template <>
	inline reg sum<double>(const reg v1) {
		// make a summation in:[a, b] => out:[a+b, a+b]
		//
		//   -> _mm_hadd_pd(v1, v1) # horizontal addition
		//             l0         l1
		//      in1[a1     , | b1     ] # info: a1 = a2, b1 = b2
		//      in2[a2     , | b2     ] =>
		//      out[a1 + b1, | a2 + b2]
		return (__m128) _mm_hadd_pd((__m128d) v1, (__m128d) v1);
	}
#endif

#ifdef __SSSE3__
	template <>
	inline reg sum<int>(const reg v1) {
		reg sum = (reg) _mm_hadd_epi32((__m128i) v1, (__m128i) v1);
		return (reg) _mm_hadd_epi32((__m128i) sum, (__m128i) sum);
	}
#endif

#ifdef __SSSE3__
	template <>
	inline reg sum<signed char>(const reg v1) {
		reg v2, sum;
		v2  = (reg) _mm_shuffle_epi32((__m128i)  v1, _MM_SHUFFLE(1, 0, 3, 2));
		sum = add<signed char>(v1, v2);
		v2  = (reg) _mm_shuffle_epi32((__m128i) sum, _MM_SHUFFLE(2, 3, 0, 1));
		sum = add<signed char>(sum, v2);
		v2  = (reg) _mm_shuffle_epi8 ((__m128i) sum, 
		                              _mm_set_epi8(13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2));
		sum = add<signed char>(sum, v2);
		v2  = (reg) _mm_shuffle_epi8 ((__m128i) sum, 
		                              _mm_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1));
		sum = add<signed char>(sum, v2);
		return sum;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return _mm_sub_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return (__m128) _mm_sub_pd((__m128d) v1, (__m128d) v2);
	}

	template <>
	inline reg sub<int>(const reg v1, const reg v2) {
		return (reg) _mm_sub_epi32((__m128i) v1,(__m128i) v2);
	}

	template <>
	inline reg sub<short>(const reg v1, const reg v2) {
		return (reg) _mm_subs_epi16((__m128i) v1,(__m128i) v2);
	}

	template <>
	inline reg sub<signed char>(const reg v1, const reg v2) {
		return (reg) _mm_subs_epi8((__m128i) v1,(__m128i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return _mm_mul_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return (__m128) _mm_mul_pd((__m128d) v1, (__m128d) v2);
	}
#endif

#ifdef __SSE4_1__
	template <>
	inline reg mul<int>(const reg v1, const reg v2) {
		return (__m128) _mm_mul_epi32((__m128i) v1, (__m128i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ div
	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return _mm_div_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return (__m128) _mm_div_pd((__m128d) v1, (__m128d) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ min
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm_min_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return (__m128) _mm_min_pd((__m128d) v1, (__m128d) v2);
	}
#endif

#ifdef __SSE4_1__
	template <>
	inline reg min<int>(const reg v1, const reg v2) {
		return (__m128) _mm_min_epi32((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg min<short>(const reg v1, const reg v2) {
		return (__m128) _mm_min_epi16((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg min<signed char>(const reg v1, const reg v2) {
		return (__m128) _mm_min_epi8((__m128i) v1, (__m128i) v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ max
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm_max_ps(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return (__m128) _mm_max_pd((__m128d) v1, (__m128d) v2);
	}
#endif

#ifdef __SSE4_1__
	template <>
	inline reg max<int>(const reg v1, const reg v2) {
		return (__m128) _mm_max_epi32((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg max<short>(const reg v1, const reg v2) {
		return (__m128) _mm_max_epi16((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg max<signed char>(const reg v1, const reg v2) {
		return (__m128) _mm_max_epi8((__m128i) v1, (__m128i) v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sign
	template <>
	inline reg sign<float>(const reg v1) {
		// sign_mask = 10000000000000000000000000000000 // 32 bits
		const reg sign_mask = set1<int>(0x80000000);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, sign_mask);
	}

	template <>
	inline reg sign<float>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<float>(v1, v2);
		    sign_v1_v2 = sign<float>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<double>(const reg v1) {
		// sign_mask = 1000000000000000000000000000000000000000000000000000000000000000 // 64 bits
		const reg sign_mask = set1<long long>(0x8000000000000000);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, sign_mask);
	}
	
	template <>
	inline reg sign<double>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<double>(v1, v2);
		    sign_v1_v2 = sign<double>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<int>(const reg v1) {
		// sign_mask = 10000000000000000000000000000000 // 32 bits
		const reg sign_mask = set1<int>(0x80000000);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<int>(v1, sign_mask);
	}

	template <>
	inline reg sign<int>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<int>(v1, v2);
		    sign_v1_v2 = sign<int>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<short>(const reg v1) {
		const reg sign_mask = set1<short>(0x8000);
		return andb<short>(v1, sign_mask);
	}

	template <>
	inline reg sign<short>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<short>(v1, v2);
		    sign_v1_v2 = sign<short>(sign_v1_v2);
		return sign_v1_v2;
	}

	template <>
	inline reg sign<signed char>(const reg v1) {
		// sign_mask = 10000000 // 8 bits
		const reg sign_mask = set1<signed char>(0x80);

		// indices = 7  6  5  4  3  2  1  0
		// mask    = 1  0  0  0  0  0  0  0
		// v1      = h  g  f  e  d  c  b  a
		// res     = h  0  0  0  0  0  0  0
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<signed char>(v1, sign_mask);
	}

	template <>
	inline reg sign<signed char>(const reg v1, const reg v2) {
		reg sign_v1_v2 = xorb<signed char>(v1, v2);
		    sign_v1_v2 = sign<signed char>(sign_v1_v2);
		return sign_v1_v2;
	}

	// ------------------------------------------------------------------------------------------------------------ neg
	template <>
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, v2);
	}

#ifdef __SSE2__
	template <>
	inline reg neg<double>(const reg v1, const reg v2) {
		return xorb<double>(v1, v2);
	}
#endif

#ifdef __SSSE3__
	template <>
	inline reg neg<int>(const reg v1, const reg v2) {
		reg v2_2 = orb<int>(v2, set1<int>(1)); // hack to avoid -0 case
		return (reg) _mm_sign_epi32((__m128i) v1, (__m128i) v2_2);
	}

	template <>
	inline reg neg<short>(const reg v1, const reg v2) {
		reg v2_2 = orb<short>(v2, set1<short>(1)); // hack to avoid -0 case
		return (reg) _mm_sign_epi16((__m128i) v1, (__m128i) v2_2);
	}

	template <>
	inline reg neg<signed char>(const reg v1, const reg v2) {
		reg v2_2 = orb<signed char>(v2, set1<signed char>(1)); // hack to avoid -0 case
		return (reg) _mm_sign_epi8((__m128i) v1, (__m128i) v2_2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ abs
	template <>
	inline reg abs<float>(const reg v1) {
		// abs_mask = 01111111111111111111111111111111 // 32 bits
		const reg abs_mask = set1<int>(0x7FFFFFFF);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, abs_mask);
	}

	template <>
	inline reg abs<double>(const reg v1) {
		// abs_mask = 0111111111111111111111111111111111111111111111111111111111111111 // 64 bits
		const reg abs_mask = set1<long long>(0x7FFFFFFFFFFFFFFF);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, abs_mask);
	}

#ifdef __SSSE3__
	template <>
	inline reg abs<int>(const reg v1) {
		return (reg) _mm_abs_epi32((__m128i) v1);
	}

	template <>
	inline reg abs<short>(const reg v1) {
		return (reg) _mm_abs_epi16((__m128i) v1);
	}

	template <>
	inline reg abs<signed char>(const reg v1) {
		return (reg) _mm_abs_epi8((__m128i) v1);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sqrt
	template <>
	inline reg sqrt<float>(const reg v1) {
		return _mm_sqrt_ps(v1);
	}

#ifdef __SSE2__
	template <>
	inline reg sqrt<double>(const reg v1) {
		return (__m128) _mm_sqrt_pd((__m128d) v1);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- rsqrt
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm_rsqrt_ps(v1);
	}

	template <>
	inline reg rsqrt<double>(const reg v1) {
		return div<double>(set1<double>(1.0), sqrt<double>(v1));
	}

	// ---------------------------------------------------------------------------------------------------------- fmadd
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return add<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return add<double>(v3, mul<double>(v1, v2));
	}

	// --------------------------------------------------------------------------------------------------------- fnmadd
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(v3, mul<double>(v1, v2));
	}

	// ---------------------------------------------------------------------------------------------------------- fmsub
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(mul<float>(v1, v2), v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(mul<double>(v1, v2), v3);
	}

	// ------------------------------------------------------------------------------------------------------------ rot
#ifdef __SSE2__
	template <>
	inline reg rot<float>(const reg v1) {
		// make a rotation in:[3, 2 , 1, 0] => out:[0, 3, 2, 1]
		return (__m128) _mm_shuffle_epi32 ((__m128i) v1, _MM_SHUFFLE(0, 3, 2, 1));
	}

	template <>
	inline reg rot<double>(const reg v1) {
		// make a rotation in:[1, 0] => out:[0, 1]
		return (__m128) _mm_shuffle_epi32 ((__m128i) v1, _MM_SHUFFLE(1, 0, 3, 2));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div2
	template <>
	inline reg div2<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.5f));
	}

	template <>
	inline reg div2<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.5));
	}

#ifdef __SSE2__
	template <>
	inline reg div2<int>(const reg v1) {
		return (reg) _mm_srai_epi32 ((__m128i) v1, 1);
	}

	template <>
	inline reg div2<short>(const reg v1) {
		return (reg) _mm_srai_epi16 ((__m128i) v1, 1);
	}

	template <>
	inline reg div2<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 1);
		sh16 = andnb<signed char>(set1<signed char>(0x80), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div4
	template <>
	inline reg div4<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.25f));
	}

	template <>
	inline reg div4<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.25));
	}

#ifdef __SSE2__
	template <>
	inline reg div4<int>(const reg v1) {
		return (reg) _mm_srai_epi32 ((__m128i) v1, 2);
	}

	template <>
	inline reg div4<short>(const reg v1) {
		return (reg) _mm_srai_epi16 ((__m128i) v1, 2);
	}

	template <>
	inline reg div4<signed char>(const reg v1) {
		reg abs_v1 = abs<signed char>(v1);
		reg sh16 = rshift<short>(abs_v1, 2);
		sh16 = andnb<signed char>(set1<signed char>(0xc0), sh16);
		reg sh8 = neg<signed char>(sh16, v1);
		return sh8;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sat
	template <>
	inline reg sat<float>(const reg v1, float min, float max) {
		return mipp::min<float>(mipp::max<float>(v1, set1<float>(min)), set1<float>(max));
	}

	template <>
	inline reg sat<double>(const reg v1, double min, double max) {
		return mipp::min<double>(mipp::max<double>(v1, set1<double>(min)), set1<double>(max));
	}

	template <>
	inline reg sat<int>(const reg v1, int min, int max) {
		return mipp::min<int>(mipp::max<int>(v1, set1<int>(min)), set1<int>(max));
	}

	template <>
	inline reg sat<short>(const reg v1, short min, short max) {
		return mipp::min<short>(mipp::max<short>(v1, set1<short>(min)), set1<short>(max));
	}

	template <>
	inline reg sat<signed char>(const reg v1, signed char min, signed char max) {
		return mipp::min<signed char>(mipp::max<signed char>(v1, set1<signed char>(min)), set1<signed char>(max));
	}

	// ---------------------------------------------------------------------------------------------------------- round
#ifdef __SSE4_1__
	template <>
	inline reg round<float>(const reg v) {
		return (reg) _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
	}

	template <>
	inline reg round<double>(const reg v) {
		return (reg) _mm_round_pd((__m128d) v, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ cvt
#ifdef __SSE2__
	template <>
	inline reg cvt<float,int>(const reg v) {
		return (reg) _mm_cvtps_epi32(v);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- pack
#ifdef __SSE2__
	template <>
	inline reg pack<int,short>(const reg v1, const reg v2) {
		return (reg) _mm_packs_epi32((__m128i) v1, (__m128i) v2);
	}

	template <>
	inline reg pack<short,signed char>(const reg v1, const reg v2) {
		return (reg) _mm_packs_epi16((__m128i) v1, (__m128i) v2);
	}
#endif

#endif

	template <typename T>
	void dump(const mipp::reg r, std::ostream &stream = std::cout, const int elmtWidth = 3)
	{
		T dumpArray[mipp::nElReg<T>()];
		mipp::store<T>(dumpArray, r);

		stream << "[";
		if (typeid(char) == typeid(T) || typeid(signed char) == typeid(T))
			for (auto i = 0; i < mipp::nElReg<T>(); i++)
				stream << std::setw(elmtWidth) << (int)dumpArray[i] << ((i < mipp::nElReg<T>()-1) ? ", " : "");
		else if (typeid(unsigned char) == typeid(T))
			for (auto i = 0; i < mipp::nElReg<T>(); i++)
				stream << std::setw(elmtWidth) << (unsigned)dumpArray[i] << ((i < mipp::nElReg<T>()-1) ? ", " : "");
		else
			for (auto i = 0; i < mipp::nElReg<T>(); i++)
				stream << std::setw(elmtWidth) << dumpArray[i] << ((i < mipp::nElReg<T>()-1) ? ", " : "");

		stream << "]";
	}
}

#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */