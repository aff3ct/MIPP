#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_v2.h>
#include <catch.hpp>

template <typename T>
void test_rvd_cmpge()
{
    const int vectorSize = mipp::N<T>();
    T inputs1[vectorSize],inputs2[vectorSize];
    int32_t mask[vectorSize];

    for(int i = 0 ; i < vectorSize; i++){
        if(i%2){
            inputs1[i] = 0;
            inputs2[i] = 1;
            mask[i] = 0;
        }else{
            inputs1[i] = 1; 
            inputs2[i] = 0;
            mask[i] = 1;
        }
    }
    inputs1[1] = 1;
    inputs2[1] = 1;
    mask[1] = 1;

    mipp::rvd<T> r1,r2;
    r1 = mipp::load(inputs1);
    r2 = mipp::load(inputs2);
    mipp::rvm<T> m = mipp::cmpge(r1,r2);

    mipp::rvd<T> r3 = mipp::toreg(m);

    for (auto i = 0; i < vectorSize; i++)
	{
		if (mask[i])
		{
			REQUIRE(mipp::get(r3, i) != 0);
		}
		else
			REQUIRE(mipp::get(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Greater equal than- mipp::rvd", "[mipp::cmpge]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_cmpge<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_cmpge<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_cmpge<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_cmpge<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_cmpge<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_cmpge<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_cmpge()
{
    const int vectorSize = mipp::N<T>();
    T inputs1[vectorSize],inputs2[vectorSize];
    int32_t mask[vectorSize];

    for(int i = 0 ; i < vectorSize; i++){
        if(i%2){
            inputs1[i] = 0;
            inputs2[i] = 1;
            mask[i] = 0;
        }else{
            inputs1[i] = 1; 
            inputs2[i] = 0;
            mask[i] = 1;
        }
    }
    inputs1[1] = 1;
    inputs2[1] = 1;
    mask[1] = 1;

    mipp::Rvd<T> r1,r2;
    r1 = inputs1;
    r2 = inputs2;
    mipp::Rvm<T> m = r1 >= r2;

    mipp::Rvd<T> r3 = m.toReg();

    for (auto i = 0; i < vectorSize; i++)
	{
		if (mask[i])
		{
			REQUIRE(r3[i] != 0);
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Greater equal than- mipp::Rvd", "[mipp::cmpge]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_cmpge<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_cmpge<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_cmpge<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_cmpge<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_cmpge<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_cmpge<int8_t>(); }
#endif
}
#endif