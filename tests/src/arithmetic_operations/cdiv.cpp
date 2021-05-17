#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_cdiv()
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

	mipp::regx2 r3 = mipp::cdiv<T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T norm = inputs2[i] * inputs2[i] + inputs2[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i];

		T res_re = (inputs1[i              ] * inputs2[i] + inputs1[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i]) / norm;
		T res_im = (inputs1[mipp::N<T>() +i] * inputs2[i] - inputs1[              i] * inputs2[mipp::N<T>() +i]) / norm;

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r3.val[0], i) == Approx(res_re).epsilon(0.01));
		REQUIRE(mipp::get<T>(r3.val[1], i) == Approx(res_im).epsilon(0.01));
#else
		REQUIRE(mipp::get<T>(r3.val[0], i) == res_re);
		REQUIRE(mipp::get<T>(r3.val[1], i) == res_im);
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Complex division - mipp::reg", "[mipp::cdiv]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_cdiv<double>(); }
#endif
	SECTION("datatype = float") { test_reg_cdiv<float>(); }
}
#endif

template <typename T>
void test_Reg_cdiv()
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
	mipp::Regx2<T> r3 = r1 / r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T norm = inputs2[i] * inputs2[i] + inputs2[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i];

		T res_re = (inputs1[i              ] * inputs2[i] + inputs1[mipp::N<T>() +i] * inputs2[mipp::N<T>() +i]) / norm;
		T res_im = (inputs1[mipp::N<T>() +i] * inputs2[i] - inputs1[              i] * inputs2[mipp::N<T>() +i]) / norm;

#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r3[0][i] == Approx(res_re).epsilon(0.01));
		REQUIRE(r3[1][i] == Approx(res_im).epsilon(0.01));
#else
		REQUIRE(r3[0][i] == res_re);
		REQUIRE(r3[1][i] == res_im);
#endif
	}
}

TEST_CASE("Complex division - mipp::Reg", "[mipp::cdiv]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_cdiv<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_cdiv<float>(); }
}
