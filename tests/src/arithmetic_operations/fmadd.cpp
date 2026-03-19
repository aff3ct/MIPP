#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_v2.h>
#include <catch.hpp>

template <typename T>
void test_rvd_fmadd()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize],inputs2[vectorSize], inputs3[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
    std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);
    std::shuffle(inputs3, inputs3 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::load(inputs2);
    mipp::rvd<T> r3 = mipp::load(inputs3);
	mipp::rvd<T> r4 = mipp::fmadd(r1, r2, r3);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = (inputs1[i] * inputs2[i]) + inputs3[i];
		REQUIRE(mipp::get(r4, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Fmadd - mipp::rvd", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_fmadd<float>(); }
}
#endif

template <typename T>
void test_Rvd_fmadd()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize],inputs2[vectorSize], inputs3[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
    std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);
    std::shuffle(inputs3, inputs3 + vectorSize, g);
 
	mipp::Rvd<T> r1 = mipp::load(inputs1);
	mipp::Rvd<T> r2 = mipp::load(inputs2);
    mipp::Rvd<T> r3 = mipp::load(inputs3);
	mipp::Rvd<T> r4;
    r4.r = mipp::fmadd(r1.r,r2.r,r3.r);

	for (auto i = 0; i < vectorSize; i++)
	{
        T res = (inputs1[i] * inputs2[i]) + inputs3[i];
		REQUIRE(r4[i] == res);
	}
}

TEST_CASE("Fmadd - mipp::Rvd", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_fmadd<float>(); }
}

