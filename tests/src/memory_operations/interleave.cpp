#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_interleave()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);

	mipp::regx2 ri = mipp::interleave<T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(mipp::get<T>(ri.val[0], i) == inputs2[i/2]);
		else
			REQUIRE(mipp::get<T>(ri.val[0], i) == inputs1[i/2]);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(mipp::get<T>(ri.val[1], i) == inputs2[mipp::N<T>()/2 + i/2]);
		else
			REQUIRE(mipp::get<T>(ri.val[1], i) == inputs1[mipp::N<T>()/2 + i/2]);
}

#ifndef MIPP_NO
#if !defined(MIPP_AVX) || (defined(MIPP_AVX))
TEST_CASE("Interleave - mipp::reg<float>", "[mipp::interleave_float]")
{
    SECTION("datatype = float") { test_reg_interleave<float>(); }
}
#endif
#endif


#ifndef MIPP_NO
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave - mipp::reg", "[mipp::interleave]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleave<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleave<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleave<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleave<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleave<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleave<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleave()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;

	mipp::Regx2<T> ri = mipp::interleave(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(ri[0][i] == inputs2[i/2]);
		else
			REQUIRE(ri[0][i] == inputs1[i/2]);

	for (auto i = 0; i < mipp::N<T>(); i++)
		if (i % 2)
			REQUIRE(ri[1][i] == inputs2[mipp::N<T>()/2 + i/2]);
		else
			REQUIRE(ri[1][i] == inputs1[mipp::N<T>()/2 + i/2]);
}

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave - mipp::Reg", "[mipp::interleave]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleave<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleave<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleave<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleave<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleave<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleave<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_reg_interleave2()
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

		mipp::regx2 ri = mipp::interleave2<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri.val[0], i) == inputs2[i/2]);
			else
				REQUIRE(mipp::get<T>(ri.val[0], i) == inputs1[i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri.val[0], mipp::N<T>()/2 +i) == inputs2[mipp::N<T>()/2 + i/2]);
			else
				REQUIRE(mipp::get<T>(ri.val[0], mipp::N<T>()/2 +i) == inputs1[mipp::N<T>()/2 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri.val[1], i) == inputs2[mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(mipp::get<T>(ri.val[1], i) == inputs1[mipp::N<T>()/4 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(mipp::get<T>(ri.val[1], mipp::N<T>()/2 +i)== inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(mipp::get<T>(ri.val[1], mipp::N<T>()/2 +i) == inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
	}
}

#ifndef MIPP_NO
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave2 - mipp::reg", "[mipp::interleave2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleave2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleave2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleave2<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleave2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleave2<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleave2<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleave2()
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

		mipp::Regx2<T> ri = mipp::interleave2(r1, r2);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(ri[0][i] == inputs2[i/2]);
			else
				REQUIRE(ri[0][i] == inputs1[i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(ri[0][mipp::N<T>()/2 +i] == inputs2[mipp::N<T>()/2 + i/2]);
			else
				REQUIRE(ri[0][mipp::N<T>()/2 +i] == inputs1[mipp::N<T>()/2 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(ri[1][i] == inputs2[mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(ri[1][i] == inputs1[mipp::N<T>()/4 + i/2]);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			if (i % 2)
				REQUIRE(ri[1][mipp::N<T>()/2 +i] == inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
			else
				REQUIRE(ri[1][mipp::N<T>()/2 +i] == inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2]);
	}
}

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
TEST_CASE("Interleave2 - mipp::Reg", "[mipp::interleave2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleave2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleave2<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleave2<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleave2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleave2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleave2<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_reg_interleave4()
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

		mipp::regx2 ri = mipp::interleave4<T>(r1, r2);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(mipp::get<T>(ri.val[0], j*mipp::N<T>()/4 +i) == inputs2[j*mipp::N<T>()/4 + i/2]);
				else
					REQUIRE(mipp::get<T>(ri.val[0], j*mipp::N<T>()/4 +i) == inputs1[j*mipp::N<T>()/4 + i/2]);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(mipp::get<T>(ri.val[1], j*mipp::N<T>()/4 +i) == inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
				else
					REQUIRE(mipp::get<T>(ri.val[1], j*mipp::N<T>()/4 +i) == inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
	}
}

#ifndef MIPP_NO
#if defined(MIPP_AVX512)
TEST_CASE("Interleave4 - mipp::reg", "[mipp::interleave4]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_interleave4<double>(); }
#endif
	SECTION("datatype = float") { test_reg_interleave4<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_interleave4<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_interleave4<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_interleave4<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_interleave4<int8_t>(); }
#endif
}
#endif
#endif

template <typename T>
void test_Reg_interleave4()
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

		mipp::Regx2<T> ri = mipp::interleave4(r1, r2);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(ri[0][j*mipp::N<T>()/4 +i] == inputs2[j*mipp::N<T>()/4 + i/2]);
				else
					REQUIRE(ri[0][j*mipp::N<T>()/4 +i] == inputs1[j*mipp::N<T>()/4 + i/2]);

		for (auto j = 0; j < 4; j++)
			for (auto i = 0; i < mipp::N<T>()/4; i++)
				if (i % 2)
					REQUIRE(ri[1][j*mipp::N<T>()/4 +i] == inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
				else
					REQUIRE(ri[1][j*mipp::N<T>()/4 +i] == inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2]);
	}
}

#if defined(MIPP_AVX512)
TEST_CASE("Interleave4 - mipp::Reg", "[mipp::interleave4]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_interleave4<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_interleave4<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_interleave4<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_interleave4<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_interleave4<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_interleave4<int8_t>(); }
#endif
}
#endif
