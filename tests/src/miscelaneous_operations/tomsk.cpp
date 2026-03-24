#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>


template <typename T>
void test_reg_tomsk()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs, inputs + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs);

    mipp::rvm<T> r2 = mipp::tomsk(r1);


	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(mipp::get(r2, i) == (T)0);
		else
			REQUIRE(mipp::get(r2, i) != (T)0);
	
}

#ifndef MIPP_NO
TEST_CASE("Tomsk - mipp::rvd<T>", "[mipp::tomsk]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_tomsk<double>(); }
#endif
	SECTION("datatype = float") { test_reg_tomsk<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_tomsk<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_tomsk<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_tomsk<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_tomsk<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_tomsk()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs, inputs + vectorSize, g);

	mipp::Rvd<T> r1 = mipp::load(inputs);

    mipp::Rvm<T> r2 = mipp::tomsk(r1.r);


	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(r2[i] == (T)0);
		else
			REQUIRE( r2[i] != (T)0);
	
}

#ifndef MIPP_NO
TEST_CASE("Tomsk - mipp::Rvd<T>", "[mipp::tomsk]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_tomsk<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_tomsk<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_tomsk<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_tomsk<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_tomsk<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_tomsk<int8_t>(); }
#endif
}
#endif
