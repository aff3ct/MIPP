#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_norm()
{
	T inputs1[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);

	mipp::regx2 r1;

	r1.val[0] = mipp::load<T>(inputs1);
	r1.val[1] = mipp::load<T>(inputs1 + mipp::N<T>());

	mipp::reg r2 = mipp::norm<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs1[i] + inputs1[mipp::N<T>() +i] * inputs1[mipp::N<T>() +i];

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r2, i) == Approx(res));
#else
		REQUIRE(mipp::get<T>(r2, i) == res);
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Complex norm - mipp::reg", "[mipp::norm]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_norm<double>(); }
#endif
	SECTION("datatype = float") { test_reg_norm<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_norm<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_reg_norm<int16_t>(); }
#endif
#endif
// #if defined(MIPP_NEON)
// 	SECTION("datatype = int8_t") { test_reg_norm<int8_t>(); }
// #endif
#endif
}
#endif

template <typename T>
void test_Reg_norm()
{
	T inputs1[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);

	mipp::Regx2<T> r1 = inputs1;
	mipp::Reg<T> r2 = mipp::norm(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs1[i] + inputs1[mipp::N<T>() +i] * inputs1[mipp::N<T>() +i];

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r2[i] == Approx(res));
#else
		REQUIRE(r2[i] == res);
#endif
	}
}

TEST_CASE("Complex norm - mipp::Reg", "[mipp::norm]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_norm<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_norm<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_norm<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_Reg_norm<int16_t>(); }
#endif
#endif
// #if defined(MIPP_NEON)
// 	SECTION("datatype = int8_t") { test_Reg_norm<int8_t>(); }
// #endif
#endif
}
