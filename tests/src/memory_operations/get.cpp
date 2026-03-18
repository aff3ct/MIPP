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
void test_reg_get()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::rvd<T> r = mipp::set<T>(inputs);
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Get - mipp::rvd<T>", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_get<double>(); }
#endif
	SECTION("datatype = float") { test_reg_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_get<int8_t>(); }
#endif
}
#endif

//same test as set
template <typename T>
void test_Reg_get()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::Rvd<T> r = inputs;
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Get - mipp::Rvd", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_get<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_get<int8_t>(); }
#endif
}

template <typename T>
void test_msk_get()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs[vectorSize];
	for (auto i = 0; i < vectorSize; i++)
		inputs[i] = i % 2 ? 1 : 0;

	mipp::rvm<T> m = mipp::set_k<T>(inputs);


	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(mipp::get(m, i) == (T)0);
		else
			REQUIRE(mipp::get(m, i) != (T)0);
}

#ifndef MIPP_NO
TEST_CASE("Get - mipp::msk", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_get<double>(); }
#endif
	SECTION("datatype = float") { test_msk_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_get<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_get()
{
		const int vectorSize = mipp::N<T>();
		int32_t inputs[vectorSize];

		for (auto i = 0; i < vectorSize; i++)
			inputs[i] = i % 2 ? -1 : 0;

		mipp::Rvm<T> m = inputs;

		for (auto i = 0; i < vectorSize; i++)
			REQUIRE(m[i] == inputs[i]);
}

TEST_CASE("Get - mipp::Msk", "[mipp::get]")
{
/*#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_get<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_get<float>(); }*/

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_get<int8_t>(); }
#endif
}
