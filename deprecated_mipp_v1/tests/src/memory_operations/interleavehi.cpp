#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_interleavehi()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);

	mipp::reg ri = mipp::interleavehi<T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(mipp::get<T>(ri, i) == inputs2[mipp::N<T>()/2 + i/2]);
		else
			REQUIRE(mipp::get<T>(ri, i) == inputs1[mipp::N<T>()/2 + i/2]);
}

#ifndef MIPP_NO
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave high - mipp::reg", "[mipp::interleavehi]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleavehi<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleavehi<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleavehi<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleavehi<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleavehi<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleavehi<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleavehi()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;

	mipp::Reg<T> ri = mipp::interleavehi(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(ri[i] == inputs2[mipp::N<T>()/2 + i/2]);
		else
			REQUIRE(ri[i] == inputs1[mipp::N<T>()/2 + i/2]);
}

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave high - mipp::Reg", "[mipp::interleavehi]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleavehi<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleavehi<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleavehi<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleavehi<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleavehi<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleavehi<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_reg_interleavehi2()
{
	if (mipp::N<T>() > 2)
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);

		mipp::reg ri = mipp::interleavehi2<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri, i) == inputs2[mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(mipp::get<T>(ri, i) == inputs1[mipp::N<T>()/4 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri, mipp::N<T>()/2 +i) == inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(mipp::get<T>(ri, mipp::N<T>()/2 +i) == inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
	}
}

#ifndef MIPP_NO
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave2 high - mipp::reg", "[mipp::interleavehi2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleavehi2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleavehi2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleavehi2<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleavehi2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleavehi2<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleavehi2<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleavehi2()
{
	if (mipp::N<T>() > 2)
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;

		mipp::Reg<T> ri = mipp::interleavehi2(r1, r2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(*((T*)&ri +i) == inputs2[mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(*((T*)&ri +i) == inputs1[mipp::N<T>()/4 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(ri[mipp::N<T>()/2 +i] == inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(ri[mipp::N<T>()/2 +i] == inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
	}
}

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave2 high - mipp::Reg", "[mipp::interleavehi2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleavehi2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleavehi2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleavehi2<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleavehi2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleavehi2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleavehi2<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_reg_interleavehi4()
{
	if (mipp::N<T>() > 4)
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);

		mipp::reg ri = mipp::interleavehi4<T>(r1, r2);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(mipp::get<T>(ri, j*mipp::N<T>()/4 +i) == inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
				else
					REQUIRE(mipp::get<T>(ri, j*mipp::N<T>()/4 +i) == inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
	}
}

#ifndef MIPP_NO
#if defined(MIPP_AVX512)
TEST_CASE("Interleave4 high - mipp::reg", "[mipp::interleavehi4]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleavehi4<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleavehi4<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleavehi4<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleavehi4<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleavehi4<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleavehi4<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleavehi4()
{
	if (mipp::N<T>() > 4)
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;

		mipp::Reg<T> ri = mipp::interleavehi4(r1, r2);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(ri[j*mipp::N<T>()/4 +i] == inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
				else
					REQUIRE(ri[j*mipp::N<T>()/4 +i] == inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
	}
}

#if defined(MIPP_AVX512)
TEST_CASE("Interleave4 high - mipp::Reg", "[mipp::interleavehi4]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleavehi4<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleavehi4<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleavehi4<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleavehi4<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleavehi4<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleavehi4<int8_t>(); }
#endif
}
#endif