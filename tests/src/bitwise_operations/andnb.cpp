#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>


template <typename T>
void test_reg_andnb()
{
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize], inputs2[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)0);
	std::iota(inputs2, inputs2 + vectorSize, (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::load(inputs2);
	mipp::rvd<T> r3 = mipp::andnb(r1, r2);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = (~inputs1[i]) & inputs2[i];
		REQUIRE(mipp::get(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not and - mipp::rvd", "[mipp::andnb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_andnb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_andnb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_andnb<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_andnb<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_andnb()
{
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize], inputs2[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)0);
	std::iota(inputs2, inputs2 + vectorSize, (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);
	std::shuffle(inputs2, inputs2 + vectorSize, g);

	mipp::Rvd<T> r1 = inputs1;
	mipp::Rvd<T> r2 = inputs2;
	mipp::Rvd<T> r3;
    r3.r = mipp::andnb(r1.r,r2.r);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = (~inputs1[i]) & inputs2[i];
		REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Binary not and - mipp::Rvd", "[mipp::andnb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_andnb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_andnb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_andnb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_andnb<int8_t>(); }
#endif
}

template <typename T>
void test_msk_andnb()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs1[vectorSize], inputs2[vectorSize];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < vectorSize; i++)
		{
			inputs1[i] = dis(g) ? -1 : 0;
			inputs2[i] = dis(g) ? -1 : 0;
		}

		std::shuffle(inputs1, inputs1 + vectorSize, g);
		std::shuffle(inputs2, inputs2 + vectorSize, g);

		mipp::rvm<T> m1 = mipp::set_k<T>(inputs1);
		mipp::rvm<T> m2 = mipp::set_k<T>(inputs2);
		mipp::rvm<T> m3 = mipp::andnb(m1, m2);

		mipp::rvd<T> r = mipp::toreg(m3);

		for (auto i = 0; i < vectorSize; i++)
		{

			bool res = (~inputs1[i]) & inputs2[i];

			if (res)
				REQUIRE(mipp::get(r, i) != (T)0);
			else
				REQUIRE(mipp::get(r, i) == (T)res);
		}
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not and - mipp::rvm", "[mipp::andnb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_andnb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_andnb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_andnb<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_andnb<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_andnb()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs1[vectorSize], inputs2[vectorSize];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < vectorSize; i++)
		{
			inputs1[i] = dis(g) ? -1 : 0;
			inputs2[i] = dis(g) ? -1 : 0;
		}

		std::shuffle(inputs1, inputs1 + vectorSize, g);
		std::shuffle(inputs2, inputs2 + vectorSize, g);

		mipp::Rvm<T> m1 = inputs1;
		mipp::Rvm<T> m2 = inputs2;
		mipp::Rvm<T> m3;
        m3.m = mipp::andnb(m1.m, m2.m);

		for (auto i = 0; i < vectorSize; i++)
		{
			int32_t res = (~inputs1[i]) & inputs2[i];
			REQUIRE(m3[i] == res);
		}
	}
}

TEST_CASE("Binary not and - mipp::Msk", "[mipp::andnb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_andnb<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_andnb<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_andnb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_andnb<int8_t>(); }
#endif
}
