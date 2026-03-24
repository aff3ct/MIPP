/*#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_reg_msb()
{
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize], inputs2[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)0);
	std::iota(inputs2, inputs2 + vectorSize, (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::load(inputs2);
	mipp::rvd<T> r3 = mipp::andnb(r1, r2);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = (~inputs1[i]) & inputs2[i];
		REQUIRE(mipp::get(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not and - mipp::rvd", "[mipp::andnb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_andnb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_andnb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_andnb<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_andnb<int8_t>(); }
#endif
}
#endif*/