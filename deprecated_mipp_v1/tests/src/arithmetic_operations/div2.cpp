#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_div2()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)-mipp::N<T>()/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::div2<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r2, i) == Approx(res).margin(0.01));
#else
		REQUIRE(mipp::get<T>(r2, i) == res);
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Division by 2 - mipp::reg", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_div2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_reg_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_reg_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_div2<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_div2()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)-mipp::N<T>()/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = mipp::div2(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r2[i] == Approx(res).margin(0.01));
#else
		REQUIRE(r2[i] == res);
#endif
	}
}

TEST_CASE("Division by 2 - mipp::Reg", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_div2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_Reg_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_Reg_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_div2<int8_t>(); }
#endif
#endif
#endif
}

template <typename T>
void test_reg_maskz_div2()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max());

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r2 = mipp::maskz<T,mipp::div2<T>>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r2, i) == Approx(res).margin(0.01));
#else
			REQUIRE(mipp::get<T>(r2, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r2, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Division by 2 - mipp::reg - maskz", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_div2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_reg_maskz_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_reg_maskz_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskz_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_maskz_div2<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_maskz_div2()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::min());

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r2 = mipp::maskz<T,mipp::div2>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r2[i] == Approx(res).margin(0.01));
#else
			REQUIRE(r2[i] == res);
#endif
		}
		else
			REQUIRE(r2[i] == (T)0);
	}
}

TEST_CASE("Division by 2 - mipp::Reg - maskz", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_div2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_Reg_maskz_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_Reg_maskz_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskz_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_maskz_div2<int8_t>(); }
#endif
#endif
#endif
}

template <typename T>
void test_reg_mask_div2()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r3 = mipp::mask<T,mipp::div2<T>>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r3, i) == Approx(res).margin(0.01));
#else
			REQUIRE(mipp::get<T>(r3, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == inputs2[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Division by 2 - mipp::reg - mask", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_div2<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_reg_mask_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_reg_mask_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_mask_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_mask_div2<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_mask_div2()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r3 = mipp::mask<T,mipp::div2>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / (T)2;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r3[i] == Approx(res).margin(0.01));
#else
			REQUIRE(r3[i] == res);
#endif
		}
		else
			REQUIRE(r3[i] == inputs2[i]);
	}
}

TEST_CASE("Division by 2 - mipp::Reg - mask", "[mipp::div2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_div2<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_div2<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t") { test_Reg_mask_div2<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int32_t") { test_Reg_mask_div2<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_mask_div2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_mask_div2<int8_t>(); }
#endif
#endif
#endif
}
