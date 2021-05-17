#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_div()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::div <T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(mipp::get<T>(r3, i) == Approx(res).epsilon(0.01));
#else
		REQUIRE(mipp::get<T>(r3, i) == res);
#endif
	}
}

#ifndef MIPP_NO
TEST_CASE("Division - mipp::reg", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_div<double>(); }
#endif
	SECTION("datatype = float") { test_reg_div<float>(); }
}
#endif

template <typename T>
void test_Reg_div()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = r1 / r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
		REQUIRE(r3[i] == Approx(res).epsilon(0.01));
#else
		REQUIRE(r3[i] == res);
#endif
	}
}

TEST_CASE("Division - mipp::Reg", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_div<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_div<float>(); }
}

template <typename T>
void test_reg_maskz_div()
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

	mipp::reg r3 = mipp::maskz<T,mipp::div<T>>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r3, i) == Approx(res).epsilon(0.01));
#else
			REQUIRE(mipp::get<T>(r3, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Division - mipp::reg - maskz", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_div<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_div<float>(); }
}
#endif

template <typename T>
void test_Reg_maskz_div()
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

	mipp::Reg<T> r3 = mipp::maskz<T,mipp::div>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r3[i] == Approx(res).epsilon(0.01));
#else
			REQUIRE(r3[i] == res);
#endif
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

TEST_CASE("Division - mipp::Reg - maskz", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_div<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_div<float>(); }
}

template <typename T>
void test_reg_mask_div()
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

	mipp::reg r4 = mipp::mask<T,mipp::div<T>>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(mipp::get<T>(r4, i) == Approx(res).epsilon(0.01));
#else
			REQUIRE(mipp::get<T>(r4, i) == res);
#endif
		}
		else
			REQUIRE(mipp::get<T>(r4, i) == inputs3[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Division - mipp::reg - mask", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_div<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_div<float>(); }
}
#endif

template <typename T>
void test_Reg_mask_div()
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

	mipp::Reg<T> r4 = mipp::mask<T,mipp::div>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			REQUIRE(r4[i] == Approx(res).epsilon(0.01));
#else
			REQUIRE(r4[i] == res);
#endif
		}
		else
			REQUIRE(r4[i] == inputs3[i]);
	}
}

TEST_CASE("Division - mipp::Reg - mask", "[mipp::div]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_div<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_div<float>(); }
}
