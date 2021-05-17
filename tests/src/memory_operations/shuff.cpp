#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_shuff()
{
	uint32_t cm_inputs[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (cm_inputs, cm_inputs + mipp::N<T>(), (uint32_t)0);
	std::shuffle(cm_inputs, cm_inputs + mipp::N<T>(), g);

	mipp::reg cm = mipp::cmask<T>(cm_inputs);

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);
	mipp::reg s = mipp::shuff<T>(r, cm);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(s, i) == inputs[cm_inputs[i]]);
}

#ifndef MIPP_NO
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle - mipp::reg", "[mipp::shuff]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_shuff<double>(); }
#endif
	SECTION("datatype = float") { test_reg_shuff<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_shuff<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_shuff<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_shuff<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int8_t") { test_reg_shuff<int8_t>(); }
#endif
#endif
}
#endif
#endif

template <typename T>
void test_Reg_shuff()
{
	uint32_t cm_inputs[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (cm_inputs, cm_inputs + mipp::N<T>(), (uint32_t)0);
	std::shuffle(cm_inputs, cm_inputs + mipp::N<T>(), g);

	mipp::Reg<T> cm = mipp::Reg<T>::cmask(cm_inputs);

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r = inputs;
	mipp::Reg<T> s = r.shuff(cm);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(s[i] == inputs[cm_inputs[i]]);
}

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle - mipp::Reg", "[mipp::shuff]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_shuff<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_shuff<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_shuff<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_shuff<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_shuff<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int8_t") { test_Reg_shuff<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_reg_shuff2()
{
	if (mipp::N<T>() >= 2)
	{
#ifdef _MSC_VER
		uint32_t cm2_inputs[mipp::N<T>()];
#else
		uint32_t cm2_inputs[mipp::N<T>()/2];
#endif
		std::mt19937 g;
		std::iota   (cm2_inputs, cm2_inputs + mipp::N<T>()/2, (uint32_t)0);
		std::shuffle(cm2_inputs, cm2_inputs + mipp::N<T>()/2, g);

		mipp::reg cm2 = mipp::cmask2<T>(cm2_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), (T)0);

		mipp::reg r = mipp::load<T>(inputs);
		mipp::reg s = mipp::shuff2<T>(r, cm2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			REQUIRE(mipp::get<T>(s, i) == inputs[cm2_inputs[i]]);
		for (auto i = 0; i < mipp::N<T>()/2; i++)
			REQUIRE(mipp::get<T>(s, mipp::N<T>()/2 +i) == inputs[mipp::N<T>()/2 + cm2_inputs[i]]);
	}
}

#ifndef MIPP_NO
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle2 - mipp::reg", "[mipp::shuff2]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_shuff2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_shuff2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_shuff2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_reg_shuff2<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_shuff2<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { test_reg_shuff2<int8_t>(); }
#endif
#endif
#endif
}
#endif
#endif

template <typename T>
void test_Reg_shuff2()
{
	if (mipp::N<T>() >= 2)
	{
#ifdef _MSC_VER
		uint32_t cm2_inputs[mipp::N<T>()];
#else
		uint32_t cm2_inputs[mipp::N<T>()/2];
#endif
		std::mt19937 g;
		std::iota   (cm2_inputs, cm2_inputs + mipp::N<T>()/2, (uint32_t)0);
		std::shuffle(cm2_inputs, cm2_inputs + mipp::N<T>()/2, g);

		mipp::Reg<T> cm2 = mipp::Reg<T>::cmask2(cm2_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), (T)0);

		mipp::Reg<T> r = inputs;
		mipp::Reg<T> s = r.shuff2(cm2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			REQUIRE(s[i] == inputs[cm2_inputs[i]]);
		for (auto i = 0; i < mipp::N<T>()/2; i++)
			REQUIRE(s[mipp::N<T>()/2 +i] == inputs[mipp::N<T>()/2 + cm2_inputs[i]]);
	}
}

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle2 - mipp::Reg", "[mipp::shuff2]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_shuff2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_shuff2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_shuff2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_Reg_shuff2<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_shuff2<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { test_Reg_shuff2<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_reg_shuff4()
{
	if (mipp::N<T>() >= 4)
	{
#ifdef _MSC_VER
		uint32_t cm4_inputs[mipp::N<T>()];
#else
		uint32_t cm4_inputs[mipp::N<T>()/4];
#endif
		std::mt19937 g;
		std::iota   (cm4_inputs, cm4_inputs + mipp::N<T>()/4, (uint32_t)0);
		std::shuffle(cm4_inputs, cm4_inputs + mipp::N<T>()/4, g);

		mipp::reg cm4 = mipp::cmask4<T>(cm4_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), (T)0);

		mipp::reg r = mipp::load<T>(inputs);
		mipp::reg s = mipp::shuff4<T>(r, cm4);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				REQUIRE(mipp::get<T>(s, j*mipp::N<T>()/4 +i) == inputs[j*mipp::N<T>()/4 + cm4_inputs[i]]);
	}
}

#ifndef MIPP_NO
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle4 - mipp::reg", "[mipp::shuff4]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	SECTION("datatype = double") { test_reg_shuff4<double>(); }
#endif
#endif
	SECTION("datatype = float") { test_reg_shuff4<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_reg_shuff4<int64_t>(); }
#endif
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_reg_shuff4<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_shuff4<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { test_reg_shuff4<int8_t>(); }
#endif
#endif
#endif
}
#endif
#endif

template <typename T>
void test_Reg_shuff4()
{
	if (mipp::N<T>() >= 4)
	{
#ifdef _MSC_VER
		uint32_t cm4_inputs[mipp::N<T>()];
#else
		uint32_t cm4_inputs[mipp::N<T>()/4];
#endif
		std::mt19937 g;
		std::iota   (cm4_inputs, cm4_inputs + mipp::N<T>()/4, (uint32_t)0);
		std::shuffle(cm4_inputs, cm4_inputs + mipp::N<T>()/4, g);

		mipp::Reg<T> cm4 = mipp::Reg<T>::cmask4(cm4_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), (T)0);

		mipp::Reg<T> r = inputs;
		mipp::Reg<T> s = r.shuff4(cm4);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				REQUIRE(s[j*mipp::N<T>()/4 +i] == inputs[j*mipp::N<T>()/4 + cm4_inputs[i]]);
	}
}

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
TEST_CASE("Shuffle4 - mipp::Reg", "[mipp::shuff4]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	SECTION("datatype = double") { test_Reg_shuff4<double>(); }
#endif
#endif
	SECTION("datatype = float") { test_Reg_shuff4<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_Reg_shuff4<int64_t>(); }
#endif
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_Reg_shuff4<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_shuff4<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { test_Reg_shuff4<int8_t>(); }
#endif
#endif
#endif
}
#endif
