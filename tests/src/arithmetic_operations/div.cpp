#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_reg_div()
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
	mipp::rvd<T> r3 = mipp::div(r1, r2);


	/*T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::add <T>(r1, r2);*/

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = inputs1[i] / inputs2[i];
		REQUIRE(mipp::get(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Division - mipp::reg", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_div<double>(); }
#endif
	SECTION("datatype = float") { test_reg_div<float>(); }
}
#endif

template <typename T>
void test_Reg_div()
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
	mipp::Rvd<T> r3 = r1 / r2;
	


	/*T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = r1 + r2;*/

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = inputs1[i] / inputs2[i];
		REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Division - mipp::Reg", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_div<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_div<float>(); }
}

