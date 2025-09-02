#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_sqrt()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::sqrt<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
		REQUIRE(mipp::get<T>(r2, i) == Approx(res).epsilon(0.01));
#else
		REQUIRE(mipp::get<T>(r2, i) == Approx(res));
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Square root - mipp::reg", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_reg_sqrt<float>(); }
}
#endif

template <typename T>
void test_Reg_sqrt()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = mipp::sqrt(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
		REQUIRE(r2[i] == Approx(res).epsilon(0.01));
#else
		REQUIRE(r2[i] == Approx(res));
#endif
	}
}

TEST_CASE("Square root - mipp::Reg", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_sqrt<float>(); }
}

template <typename T>
void test_reg_maskz_sqrt()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r2 = mipp::maskz<T,mipp::sqrt<T>>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
			REQUIRE(mipp::get<T>(r2, i) == Approx(res).epsilon(0.01));
#else
			REQUIRE(mipp::get<T>(r2, i) == Approx(res));
#endif
		}
		else
			REQUIRE(mipp::get<T>(r2, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Square root - mipp::reg - maskz", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_sqrt<float>(); }
}
#endif

template <typename T>
void test_Reg_maskz_sqrt()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r2 = mipp::maskz<T,mipp::sqrt>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
			REQUIRE(r2[i] == Approx(res).epsilon(0.01));
#else
			REQUIRE(r2[i] == Approx(res));
#endif
		}
		else
			REQUIRE(r2[i] == (T)0);
	}
}

TEST_CASE("Square root - mipp::Reg - maskz", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_sqrt<float>(); }
}

template <typename T>
void test_reg_mask_sqrt()
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

	mipp::reg r3 = mipp::mask<T,mipp::sqrt<T>>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
			REQUIRE(mipp::get<T>(r3, i) == Approx(res).epsilon(0.01));
#else
			REQUIRE(mipp::get<T>(r3, i) == Approx(res));
#endif
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == inputs2[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Square root - mipp::reg - mask", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_sqrt<float>(); }
}
#endif

template <typename T>
void test_Reg_mask_sqrt()
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

	mipp::Reg<T> r3 = mipp::mask<T,mipp::sqrt>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = std::sqrt(inputs1[i]);
#ifdef MIPP_NEON
			REQUIRE(r3[i] == Approx(res).epsilon(0.01));
#else
			REQUIRE(r3[i] == Approx(res));
#endif
		}
		else
			REQUIRE(r3[i] == inputs2[i]);
	}
}

TEST_CASE("Square root - mipp::Reg - mask", "[mipp::sqrt]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_sqrt<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_sqrt<float>(); }
}