#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_mul()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::mul <T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r3, i) == Approx(res));
#else
		REQUIRE(mipp::get<T>(r3, i) == res);
#endif
	}

	std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());
	std::iota(inputs2, inputs2 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());

	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	r1 = mipp::load<T>(inputs1);
	r2 = mipp::load<T>(inputs2);
	r3 = mipp::mul <T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r3, i) == Approx(res));
#else
		REQUIRE(mipp::get<T>(r3, i) == res);
#endif
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
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_mul<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_reg_mul<int16_t>(); }
#endif
#endif
#if defined(MIPP_NEON)
	SECTION("datatype = int8_t") { test_reg_mul<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_mul()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = r1 * r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r3[i] == Approx(res));
#else
		REQUIRE(r3[i] == res);
#endif
	}

	std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());
	std::iota(inputs2, inputs2 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());

	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	r1 = inputs1;
	r2 = inputs2;
	r3 = r1 * r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r3[i] == Approx(res));
#else
		REQUIRE(r3[i] == res);
#endif
	}
}

TEST_CASE("Multiplication - mipp::Reg", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mul<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_mul<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int16_t") { test_Reg_mul<int16_t>(); }
#endif
#endif
#if defined(MIPP_NEON)
	SECTION("datatype = int8_t") { test_Reg_mul<int8_t>(); }
#endif
#endif
}

template <typename T>
void test_reg_maskz_mul()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r3 = mipp::maskz<T,mipp::mul<T>>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r3, i) == Approx(res));
#else
			REQUIRE(mipp::get<T>(r3, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Multiplication - mipp::reg - maskz", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_mul<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_maskz_mul<int32_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_maskz_mul()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r3 = mipp::maskz<T,mipp::mul>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r3[i] == Approx(res));
#else
			REQUIRE(r3[i] == res);
#endif
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

TEST_CASE("Multiplication - mipp::Reg - maskz", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_mul<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_maskz_mul<int32_t>(); }
#endif
#endif
}

template <typename T>
void test_reg_mask_mul()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::load<T>(inputs3);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r4 = mipp::mask<T,mipp::mul<T>>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r4, i) == Approx(res));
#else
			REQUIRE(mipp::get<T>(r4, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r4, i) == inputs3[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Multiplication - mipp::reg - mask", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_mul<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_mask_mul<int32_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_mask_mul()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = inputs3;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r4 = mipp::mask<T,mipp::mul>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r4[i] == Approx(res));
#else
			REQUIRE(r4[i] == res);
#endif
		}
		else
			REQUIRE(r4[i] == inputs3[i]);
	}
}

TEST_CASE("Multiplication - mipp::Reg - mask", "[mipp::mul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_mul<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_mul<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_mask_mul<int32_t>(); }
#endif
#endif
}
