#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_v2.h>
#include <catch.hpp>

template <typename T>
void test_rvd_rsqrt()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::rsqrt(r1);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = 1/sqrt(inputs1[i]); 
		//REQUIRE(mipp::get(r2, i) == res);
        REQUIRE_THAT(mipp::get(r2,i), Catch::Matchers::WithinRel(res,0.1));
	}
}

#ifndef MIPP_NO
TEST_CASE("Inverse square root - mipp::reg", "[mipp::rsqrt]")
{
#if defined(MIPP_64BIT)
	//SECTION("datatype = double") { test_rvd_rsqrt<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_rsqrt<float>(); }
}
#endif

template <typename T>
void test_Rvd_rsqrt()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::Rvd<T> r1;
    r1.r = mipp::load(inputs1);

    mipp::Rvd<T> r2;
    r2.r = mipp::rsqrt(r1.r);
	

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = 1/sqrt(inputs1[i]); 
        REQUIRE_THAT(r2[i], Catch::Matchers::WithinRel(res,0.1));

	}
}

TEST_CASE("Inverse square root - mipp::Rvd", "[mipp::rsqrt]")
{
#if defined(MIPP_64BIT)
	//SECTION("datatype = double") { test_Rvd_rsqrt<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_rsqrt<float>(); }
}