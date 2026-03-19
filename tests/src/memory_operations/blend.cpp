#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_v2.h>
#include <catch.hpp>
//this file is relevant to test get_k (mask get operation)

//same test as set
template <typename T>
void test_reg_blend()
{
    const int vectorSize = mipp::N<T>();
	int32_t inputs[vectorSize];
	for (auto i = 0; i < vectorSize; i++)
		inputs[i] = i % 2 ? 1 : 0;

	mipp::rvm<T> m = mipp::set_k<T>(inputs);

    mipp::rvd<T> r1 = mipp::set1((T)1);
    mipp::rvd<T> r2 = mipp::set1((T)2);

    mipp::rvd<T> r3 = mipp::blend(r1,r2,m);

	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(mipp::get(r3, i) == mipp::get(r2,i));
		else
			REQUIRE(mipp::get(r3, i) == mipp::get(r1,i));
}

#ifndef MIPP_NO
TEST_CASE("Blend - mipp::rvd<T>", "[mipp::blend]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_blend<double>(); }
#endif
	SECTION("datatype = float") { test_reg_blend<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_blend<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_blend<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_blend<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_blend<int8_t>(); }
#endif
}
#endif

//same test as set
template <typename T>
void test_Reg_blend()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::Rvd<T> r = inputs;
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Blend - mipp::Rvd", "[mipp::blend]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_blend<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_blend<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_blend<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_blend<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_blend<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_blend<int8_t>(); }
#endif
}

