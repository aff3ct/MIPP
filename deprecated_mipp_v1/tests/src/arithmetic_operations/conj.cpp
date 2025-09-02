#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_conj()
{
	T inputs1[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);

	mipp::regx2 r1;

	r1.val[0] = mipp::load<T>(inputs1);
	r1.val[1] = mipp::load<T>(inputs1 + mipp::N<T>());

	mipp::regx2 r2 = mipp::conj<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res_re =  inputs1[              i];
		T res_im = -inputs1[mipp::N<T>() +i];

		REQUIRE(mipp::get<T>(r2.val[0], i) == res_re);
		REQUIRE(mipp::get<T>(r2.val[1], i) == res_im);
	}
}

#ifndef MIPP_NO
TEST_CASE("Complex conjugate - mipp::reg", "[mipp::conj]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_conj<double>(); }
#endif
	SECTION("datatype = float") { test_reg_conj<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_reg_conj<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_conj<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_conj<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_conj()
{
	T inputs1[2*mipp::N<T>()];

	std::iota(inputs1, inputs1 + 2*mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + 2*mipp::N<T>(), g);

	mipp::Regx2<T> r1 = inputs1;
	mipp::Regx2<T> r2 = mipp::conj(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res_re =  inputs1[              i];
		T res_im = -inputs1[mipp::N<T>() +i];

		REQUIRE(r2[0][i] == res_re);
		REQUIRE(r2[1][i] == res_im);
	}
}

TEST_CASE("Complex conjugate - mipp::Reg", "[mipp::conj]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_conj<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_conj<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_Reg_conj<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_conj<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_conj<int8_t>(); }
#endif
}
