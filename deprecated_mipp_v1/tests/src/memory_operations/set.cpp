#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_set1()
{
	mipp::reg r = mipp::set1<T>((T)12);
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == (T)12);
}

#ifndef MIPP_NO
TEST_CASE("Set1 - mipp::reg", "[mipp::set1]")
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
	mipp::Reg<T> r = (T)12;
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == (T)12);
}

TEST_CASE("Set1 - mipp::Reg", "[mipp::set1]")
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
	mipp::reg r = mipp::set0<T>();
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == (T)0);
}

#ifndef MIPP_NO
TEST_CASE("Set0 - mipp::reg", "[mipp::set0]")
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
	mipp::Reg<T> r; r.set0();
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == (T)0);
}

TEST_CASE("Set0 - mipp::Reg", "[mipp::set0]")
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
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::set<T>(inputs);
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Set - mipp::reg", "[mipp::set]")
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
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r = inputs;
	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Set - mipp::Reg", "[mipp::set]")
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
	mipp::msk m0 = mipp::set1<mipp::N<T>()>(false);
	mipp::msk m1 = mipp::set1<mipp::N<T>()>(true );

	mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0);
	mipp::reg r1 = mipp::toreg<mipp::N<T>()>(m1);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r0, i) == (T)0);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r1, i) != (T)0);
}

#ifndef MIPP_NO
TEST_CASE("Set1 - mipp::msk", "[mipp::set1]")
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

template <typename T>
void test_Msk_set1()
{
	mipp::Msk<mipp::N<T>()> m0 = false;
	mipp::Msk<mipp::N<T>()> m1 = true;

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(m0[i] == false);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(m1[i] == true);
}

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

template <typename T>
void test_msk_set0()
{
	mipp::msk m0 = mipp::set0<mipp::N<T>()>();
	mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r0, i) == (T)0);
}

#ifndef MIPP_NO
TEST_CASE("Set0 - mipp::msk", "[mipp::set0]")
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

template <typename T>
void test_Msk_set0()
{
	mipp::Msk<mipp::N<T>()> m0; m0.set0();

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(m0[i] == false);
}

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

template <typename T>
void test_msk_set()
{
	bool inputs[mipp::N<T>()];

	for (auto i = 0; i < mipp::N<T>(); i++)
		inputs[i] = i % 2 ? true : false;

	mipp::msk m = mipp::set<mipp::N<T>()>(inputs);
	mipp::reg r = mipp::toreg<mipp::N<T>()>(m);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (!inputs[i])
			REQUIRE(mipp::get<T>(r, i) == (T)0);
		else
			REQUIRE(mipp::get<T>(r, i) != (T)0);
}

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

template <typename T>
void test_Msk_set()
{
		bool inputs[mipp::N<T>()];

		for (auto i = 0; i < mipp::N<T>(); i++)
			inputs[i] = i % 2 ? true : false;

		mipp::Msk<mipp::N<T>()> m = inputs;

		for (auto i = 0; i < mipp::N<T>(); i++)
			REQUIRE(m[i] == inputs[i]);
}

TEST_CASE("Set - mipp::Msk", "[mipp::set]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_set<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_set<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_set<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_set<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_set<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_set<int8_t>(); }
#endif
}
