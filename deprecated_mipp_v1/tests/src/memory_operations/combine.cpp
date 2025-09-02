#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_combine()
{
	T inputs[mipp::N<T>()];

	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r1 = mipp::load<T>(inputs);

	mipp::reg_2 r1_lo = mipp::low <T>(r1);
	mipp::reg_2 r1_hi = mipp::high<T>(r1);

	mipp::reg r2 = mipp::combine<T>(r1_lo, r1_hi);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r2, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Combine - mipp::reg", "[mipp::combine]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_combine<double>(); }
#endif
	SECTION("datatype = float") { test_reg_combine<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_combine<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_combine<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_combine<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_combine<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_combine()
{
	T inputs[mipp::N<T>()];

	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r1 = inputs;

	mipp::Reg_2<T> r1_lo = r1.low ();
	mipp::Reg_2<T> r1_hi = r1.high();

	mipp::Reg<T> r2 = mipp::combine(r1_lo, r1_hi);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r2[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Combine - mipp::Reg", "[mipp::combine]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_combine<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_combine<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_combine<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_combine<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_combine<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_combine<int8_t>(); }
#endif
}
#endif
