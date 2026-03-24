#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch_amalgamated.hpp>

#include <limits>



template <typename T>
void test_rvd_hmax()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::hmax (r1);

    T res = std::numeric_limits<T>::min();

	for (auto i = 0; i < vectorSize; i++)
	{
        if(inputs1[i] > res) res = inputs1[i];
	}
    REQUIRE(mipp::get(r2, 0) == res);

}

#ifndef MIPP_NO
TEST_CASE("Reduction max - mipp::rvd", "[mipp::hmax]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_hmax<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_hmax<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_hmax<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_hmax<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_hmax<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_hmax<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_hmax()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::Rvd<T> r1; 
    r1.r = mipp::load(inputs1);
	
    mipp::Rvd<T> r2;
    r2.r = mipp::hmax(r1.r);
    //r1.load(inputs1);
    //r2 = r1.hadd();
    
    T res = std::numeric_limits<T>::min();
	for (auto i = 0; i < vectorSize; i++)
	{
        if(inputs1[i] > res) res = inputs1[i];
	}
    REQUIRE(r2[0] == res);
}

TEST_CASE("Reduction max - mipp::Rvd", "[mipp::hmax]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_hmax<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_hmax<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_hmax<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_hmax<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_hmax<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_hmax<int8_t>(); }
#endif
}