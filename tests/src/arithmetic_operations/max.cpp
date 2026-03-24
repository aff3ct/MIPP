#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_rvd_max()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize],inputs2[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::load(inputs2);
	mipp::rvd<T> r3 = mipp::max (r1, r2);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = inputs1[i] > inputs2[i] ? inputs1[i] : inputs2[i];
        REQUIRE(mipp::get(r3,i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Maximal - mipp::reg", "[mipp::max]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_max<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_max<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_max<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_max<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_max<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_max<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_max()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize],inputs2[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)1);
	std::iota(inputs2, inputs2 + vectorSize, (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);

 
	mipp::Rvd<T> r1 = mipp::load(inputs1);
	mipp::Rvd<T> r2 = mipp::load(inputs2);
	mipp::Rvd<T> r3;
    r3.r = mipp::max(r1.r,r2.r);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = inputs1[i] > inputs2[i] ? inputs1[i] : inputs2[i];
        REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Maximal - mipp::Reg", "[mipp::max]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_max<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_max<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_max<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_max<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_max<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_max<int8_t>(); }
#endif
}
