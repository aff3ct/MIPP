#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_v2.h>
#include <catch.hpp>

template <typename T>
void test_reg_set1()
{
	const int vectorSize = mipp::N<T>();
	mipp::rvd<T> r = mipp::set1((T)12);
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r, i) == (T)12);
}

#ifndef MIPP_NO
TEST_CASE("Set1 - mipp::rvd<T>", "[mipp::set1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_set1<double>(); }
#endif
	SECTION("datatype = float") { test_reg_set1<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_set1<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_set1<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_set1<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_set1<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_set1()
{
	const int vectorSize = mipp::N<T>();
	mipp::Rvd<T> r = (T)12;
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(r[i] == (T)12);
}

TEST_CASE("Set1 - mipp::Rvd", "[mipp::set1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_set1<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_set1<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_set1<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_set1<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_set1<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_set1<int8_t>(); }
#endif
}

template <typename T>
void test_reg_set0()
{
	const int vectorSize = mipp::N<T>();
	mipp::rvd<T> r = mipp::set0<T>();
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r, i) == (T)0);
}

#ifndef MIPP_NO
TEST_CASE("Set0 - mipp::rvd<T>", "[mipp::set0]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_set0<double>(); }
#endif
	SECTION("datatype = float") { test_reg_set0<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_set0<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_set0<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_set0<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_set0<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_set0()
{
	const int vectorSize = mipp::N<T>();
	mipp::Rvd<T> r; r.set0();
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(r[i] == (T)0);
}

TEST_CASE("Set0 - mipp::Rvd", "[mipp::set0]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_set0<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_set0<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_set0<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_set0<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_set0<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_set0<int8_t>(); }
#endif
}

template <typename T>
void test_reg_set()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::rvd<T> r = mipp::set<T>(inputs);
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Set - mipp::rvd<T>", "[mipp::set]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_set<double>(); }
#endif
	SECTION("datatype = float") { test_reg_set<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_set<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_set<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_set<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_set<int8_t>(); }
#endif
}
#endif


template <typename T>
void test_Reg_set()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::Rvd<T> r = inputs;
	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Set - mipp::Rvd", "[mipp::set]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_set<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_set<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_set<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_set<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_set<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_set<int8_t>(); }
#endif
}

template <typename T>
void test_msk_set1()
{
	/*mipp::rvm<T> m0 = mipp::set1_k<T>(0);
	mipp::rvm<T> m1 = mipp::set1_k<T>(1);

	mipp::rvd<T> r0 = mipp::toreg(m0);
	mipp::rvd<T> r1 = mipp::toreg(m1);

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r0, i) == (T)0);

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r1, i) != (T)0);*/
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
TEST_CASE("Set1 - mipp::rvm<T>", "[mipp::set1_k]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_set1<double>(); }
#endif
	SECTION("datatype = float") { test_msk_set1<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_set1<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_set1<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_set1<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_set1<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Msk_set1()
{
	const int vectorSize = mipp::N<T>();
	mipp::Rvd<T> m0 = false;
	mipp::Rvd<T> m1 = true;

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(m0[i] == false);

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(m1[i] == true);
}

#ifndef MIPP_RVV
TEST_CASE("Set1 - mipp::Msk", "[mipp::set1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_set1<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_set1<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_set1<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_set1<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_set1<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_set1<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_msk_set0()
{
	const int vectorSize = mipp::N<T>();
	mipp::rvm<T> m0 = mipp::set0_k<T>();
	mipp::rvd<T> r0 = mipp::toreg(m0);

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(mipp::get(r0, i) == (T)0);
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
TEST_CASE("Set0 - mipp::rvm<T>", "[mipp::set0]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_set0<double>(); }
#endif
	SECTION("datatype = float") { test_msk_set0<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_set0<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_set0<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_set0<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_set0<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Msk_set0()
{
	const int vectorSize = mipp::N<T>();
	mipp::Rvd<T> m0; m0.set0();

	for (auto i = 0; i < vectorSize; i++)
		REQUIRE(m0[i] == false);
}

#ifndef MIPP_RVV
TEST_CASE("Set0 - mipp::Msk", "[mipp::set0]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_set0<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_set0<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_set0<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_set0<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_set0<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_set0<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_msk_set()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs[vectorSize];
	for (auto i = 0; i < vectorSize; i++)
		inputs[i] = i % 2 ? 1 : 0;

	mipp::rvm<T> m = mipp::set_k<T>(inputs);
	mipp::rvd<T> r = mipp::toreg(m);

	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(mipp::get(r, i) == (T)0);
		else
			REQUIRE(mipp::get(r, i) != (T)0);
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
TEST_CASE("Set - mipp::msk", "[mipp::set]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_set<double>(); }
#endif
	SECTION("datatype = float") { test_msk_set<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_set<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_set<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_set<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_set<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Msk_set()
{
		const int vectorSize = mipp::N<T>();
		int32_t inputs[vectorSize];

		for (auto i = 0; i < vectorSize; i++)
			inputs[i] = i % 2 ? -1 : 0;

		mipp::Rvm<T> m = inputs;

		for (auto i = 0; i < vectorSize; i++)
			REQUIRE(m[i] == inputs[i]);
}

#ifndef MIPP_RVV
TEST_CASE("Set - mipp::Msk", "[mipp::set]")
{
/*#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_set<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_set<float>(); }*/

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_set<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_set<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_set<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_set<int8_t>(); }
#endif
}
#endif
