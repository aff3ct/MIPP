#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch_amalgamated.hpp>


template <typename T>
void test_rvd_cmpneq()
{
    const int vectorSize = mipp::N<T>();
    T inputs1[vectorSize],inputs2[vectorSize];
    int32_t mask[vectorSize];

    for(int i = 0 ; i < vectorSize; i++){
        if(i%2){
            inputs1[i] = inputs2[i] = i;
            mask[i] = 0;
        }else{
            inputs1[i] = 0; 
            inputs2[i] = 1;
            mask[i] = 1;
        }
    }

    mipp::rvd<T> r1,r2;
    r1 = mipp::load(inputs1);
    r2 = mipp::load(inputs2);
    mipp::rvm<T> m = mipp::cmpneq(r1,r2);

    mipp::rvd<T> r3 = mipp::toreg(m);

    for (auto i = 0; i < vectorSize; i++)
	{
		if (mask[i])
		{
			REQUIRE(mipp::get(r3, i) != 0);
            REQUIRE(inputs1 != inputs2);
		}
		else
			REQUIRE(mipp::get(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Inequality- mipp::rvd", "[mipp::cmpneq]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_cmpneq<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_cmpneq<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_cmpneq<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_cmpneq<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_cmpneq<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_cmpneq<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_cmpneq()
{
const int vectorSize = mipp::N<T>();
    T inputs1[vectorSize],inputs2[vectorSize];
    int32_t mask[vectorSize];

    for(int i = 0 ; i < vectorSize; i++){
        if(i%2){
            inputs1[i] = inputs2[i] = i;
            mask[i] = 0;
        }else{
            inputs1[i] = 0; 
            inputs2[i] = 1;
            mask[i] = 1;
        }
    }

    mipp::Rvd<T> r1,r2;
    r1 = inputs1;
    r2 = inputs2;
    mipp::Rvm<T> m = r1 != r2;

    mipp::Rvd<T> r3 = m.toReg();

    for (auto i = 0; i < vectorSize; i++)
	{
		if (mask[i])
		{
			REQUIRE(r3[i] != 0);
            REQUIRE(inputs1 != inputs2);
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Inequality- mipp::Rvd", "[mipp::cmpneq]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_cmpneq<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_cmpneq<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_cmpneq<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_cmpneq<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_cmpneq<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_cmpneq<int8_t>(); }
#endif
}
#endif