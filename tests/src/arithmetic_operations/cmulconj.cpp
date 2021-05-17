#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_cmulconj()
{
	T inputs1[2*mipp::N<T>()];
	T inputs2[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + 2*mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + 2*mipp::N<T>(), g);

	mipp::regx2 r1;
	mipp::regx2 r2;

	r1.val[0] = mipp::load<T>(inputs1);
	r1.val[1] = mipp::load<T>(inputs1 + mipp::N<T>());
	r2.val[0] = mipp::load<T>(inputs2);
	r2.val[1] = mipp::load<T>(inputs2 + mipp::N<T>());

	mipp::regx2 r3 = mipp::cmulconj<T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res_re = inputs1[              i] * inputs2[i] + inputs1[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i];
		T res_im = inputs1[mipp::N<T>() +i] * inputs2[i] - inputs1[              i] * inputs2[mipp::N<T>() +i];

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r3.val[0], i) == Approx(res_re));
		REQUIRE(mipp::get<T>(r3.val[1], i) == Approx(res_im));
#else
		REQUIRE(mipp::get<T>(r3.val[0], i) == res_re);
		REQUIRE(mipp::get<T>(r3.val[1], i) == res_im);
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Complex multiplication conjugate - mipp::reg", "[mipp::cmulconj]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_cmulconj<double>(); }
#endif
	SECTION("datatype = float") { test_reg_cmulconj<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_cmulconj<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_reg_cmulconj<int16_t>(); }
#endif
#endif
// #if defined(MIPP_NEON)
// 	SECTION("datatype = int8_t") { test_reg_cmulconj<int8_t>(); }
// #endif
#endif
}
#endif

template <typename T>
void test_Reg_cmulconj()
{
	T inputs1[2*mipp::N<T>()];
	T inputs2[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + 2*mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + 2*mipp::N<T>(), g);

	mipp::Regx2<T> r1 = inputs1;
	mipp::Regx2<T> r2 = inputs2;
	mipp::Regx2<T> r3 = mipp::cmulconj(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res_re = inputs1[              i] * inputs2[i] + inputs1[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i];
		T res_im = inputs1[mipp::N<T>() +i] * inputs2[i] - inputs1[              i] * inputs2[mipp::N<T>() +i];

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r3[0][i] == Approx(res_re));
		REQUIRE(r3[1][i] == Approx(res_im));
#else
		REQUIRE(r3[0][i] == res_re);
		REQUIRE(r3[1][i] == res_im);
#endif
	}
}

TEST_CASE("Complex multiplication conjugate - mipp::Reg", "[mipp::cmulconj]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_cmulconj<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_cmulconj<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_cmulconj<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_Reg_cmulconj<int16_t>(); }
#endif
#endif
// #if defined(MIPP_NEON)
// 	SECTION("datatype = int8_t") { test_Reg_cmulconj<int8_t>(); }
// #endif
#endif
}
