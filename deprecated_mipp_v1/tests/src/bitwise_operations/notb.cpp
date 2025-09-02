#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_notb()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::notb<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = ~inputs1[i];
		REQUIRE(mipp::get<T>(r2, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not - mipp::reg", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_notb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_notb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_notb<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_notb()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = ~r1;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = ~inputs1[i];
		REQUIRE(r2[i] == res);
	}
}

TEST_CASE("Binary not - mipp::Reg", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_notb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_notb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_notb<int8_t>(); }
#endif
}

template <typename T>
void test_msk_notb()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g) ? true : false;

		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::msk m1 = mipp::set<N>(inputs1);
		mipp::msk m2 = mipp::notb<N>(m1);

		mipp::reg r = mipp::toreg<N>(m2);

		for (auto i = 0; i < N; i++)
		{
			bool res = !inputs1[i];

			if (res)
				REQUIRE(mipp::get<T>(r, i) != (T)0);
			else
				REQUIRE(mipp::get<T>(r, i) == (T)res);
		}
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not - mipp::msk", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_notb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_notb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_notb<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_notb()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g) ? true : false;

		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Msk<N> m1 = inputs1;
		mipp::Msk<N> m2 = ~m1;

		for (auto i = 0; i < N; i++)
		{
			bool res = !inputs1[i];
			REQUIRE(m2[i] == res);
		}
	}
}

TEST_CASE("Binary not - mipp::Msk", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_notb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_notb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_notb<int8_t>(); }
#endif
}