#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_reg_mul()
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
	mipp::rvd<T> r3 = mipp::mul (r1, r2);


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
		T res = inputs1[i] * inputs2[i];
		REQUIRE(mipp::get(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Multiplication - mipp::reg", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mul<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_mul<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_mul<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_mul<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_mul<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_mul()
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
	mipp::Rvd<T> r3 = r1 * r2;
	


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
		T res = inputs1[i] * inputs2[i];
		REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Multiplication - mipp::Reg", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mul<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_mul<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_mul<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_mul<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_mul<int8_t>(); }
#endif
}

