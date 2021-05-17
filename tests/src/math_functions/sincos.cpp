#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_sincos()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2, r3;
	mipp::sincos<T>(r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res1 = std::sin(inputs1[i]);
		T res2 = std::cos(inputs1[i]);

		// REQUIRE(mipp::get<T>(r2, i) == Approx(res1).epsilon(0.001));
		REQUIRE(mipp::get<T>(r2, i) == Approx(res1));

		// REQUIRE(mipp::get<T>(r3, i) == Approx(res2).epsilon(0.001));
		REQUIRE(mipp::get<T>(r3, i) == Approx(res2));
	}
}

#ifndef MIPP_NO
TEST_CASE("Sine & Cosine - mipp::reg", "[mipp::sincos]")
{
	SECTION("datatype = float" ) { test_reg_sincos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_reg_sincos<double>(); }
#endif
}
#endif

template <typename T>
void test_Reg_sincos()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2, r3;
	mipp::sincos(r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res1 = std::sin(inputs1[i]);
		T res2 = std::cos(inputs1[i]);

		// REQUIRE(r2[i] == Approx(res1).epsilon(0.001));
		REQUIRE(r2[i] == Approx(res1));

		// REQUIRE(r3[i] == Approx(res2).epsilon(0.001));
		REQUIRE(r3[i] == Approx(res2));
	}
}

TEST_CASE("Sine & Cosine - mipp::Reg", "[mipp::sincos]")
{
	SECTION("datatype = float" ) { test_Reg_sincos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_Reg_sincos<double>(); }
#endif
}