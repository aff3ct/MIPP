#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_low()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg   r   = mipp::load<T>(inputs);
	mipp::reg_2 r_2 = mipp::low <T>(r);

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(mipp::get<T>(r_2, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Low - mipp::reg", "[mipp::low]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_low<double>(); }
#endif
	SECTION("datatype = float") { test_reg_low<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_low<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_low<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_low<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_low<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_low()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg  <T> r   = inputs;
	mipp::Reg_2<T> r_2 = r.low();

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(r_2[i] == inputs[i]);
}

TEST_CASE("Low - mipp::Reg", "[mipp::low]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_low<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_low<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_low<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_low<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_low<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_low<int8_t>(); }
#endif
}
