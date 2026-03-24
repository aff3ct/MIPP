#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>


template <typename T>
void test_reg_notb()
{
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::notb(r1);

	for (auto i = 0; i < vectorSize; i++)
	{
		T res = ~inputs1[i];
		REQUIRE(mipp::get(r2, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Binary not - mipp::rvd", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_notb<int64_t>(); }
	SECTION("datatype = uint64_t") { test_reg_notb<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_reg_notb<int32_t>(); }
	SECTION("datatype = uint32_t") { test_reg_notb<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_notb<int8_t>(); }
	SECTION("datatype = uint16_t") { test_reg_notb<uint16_t>(); }
	SECTION("datatype = uint8_t") { test_reg_notb<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_notb()
{
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + vectorSize, (T)0);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::Rvd<T> r1 = mipp::load(inputs1);
	mipp::Rvd<T> r2;// = ~r1;
    r2.r = mipp::notb(r1.r);
	for (auto i = 0; i < vectorSize; i++)
	{
		T res = ~inputs1[i];
		REQUIRE(r2[i] == res);
	}
}

TEST_CASE("Binary not - mipp::Rvd", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_notb<int64_t>(); }
	SECTION("datatype = uint64_t") { test_Reg_notb<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_Reg_notb<int32_t>(); }
	SECTION("datatype = uint32_t") { test_Reg_notb<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_notb<int8_t>(); }
	SECTION("datatype = uint16_t") { test_Reg_notb<uint16_t>(); }
	SECTION("datatype = uint8_t") { test_Reg_notb<uint8_t>(); }
#endif
}

template <typename T>
void test_msk_notb()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs1[vectorSize];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < vectorSize; i++)
		{
			inputs1[i] = dis(g) ? -1 : 0;
		}

		std::shuffle(inputs1, inputs1 + vectorSize, g);

		mipp::rvm<T> m1 = mipp::set_k<T>(inputs1);
		mipp::rvm<T> m2 = mipp::notb(m1);

		mipp::rvd<T> r = mipp::toreg(m2);

		for (auto i = 0; i < vectorSize; i++)
		{

			bool res = ~inputs1[i];

			if (res)
				REQUIRE(mipp::get(r, i) != (T)0);
			else
				REQUIRE(mipp::get(r, i) == (T)res);
		}
	}
}
#ifndef MIPP_NO
TEST_CASE("Binary notb - mipp::rvm", "[mipp::notb]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_notb<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_msk_notb<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_msk_notb<int32_t>(); }
	SECTION("datatype = uint32_t") { test_msk_notb<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_notb<int8_t>(); }
	SECTION("datatype = uint16_t") { test_msk_notb<uint16_t>(); }
	SECTION("datatype = uint8_t") { test_msk_notb<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_notb()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs1[vectorSize];
	std::mt19937 g;
	std::uniform_int_distribution<uint16_t> dis(0, 1);

	for (auto t = 0; t < 100; t++)
	{
		for (auto i = 0; i < vectorSize; i++)
		{
			inputs1[i] = dis(g) ? -1 : 0;
		}

		std::shuffle(inputs1, inputs1 + vectorSize, g);

		mipp::Rvm<T> m1 = inputs1;
		mipp::Rvm<T> m2; // = ~m1;
		m2.m = mipp::notb(m1.m);

		for (auto i = 0; i < vectorSize; i++)
		{

			bool res = ~inputs1[i];

			if (res)
				REQUIRE(m2[i] != (T)0);
			else
				REQUIRE( m2[i] == (T)res);
		}
	}
}

TEST_CASE("Binary notb - mipp::Msk", "[mipp::notb]")
//no uint for avx2
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_notb<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_Msk_notb<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_Msk_notb<int32_t>(); }
	SECTION("datatype = uint32_t") { test_Msk_notb<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_notb<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_notb<int8_t>(); }
	SECTION("datatype = uint16_t") { test_Msk_notb<uint16_t>(); }
	SECTION("datatype = uint8_t") { test_Msk_notb<uint8_t>(); }
#endif
}
