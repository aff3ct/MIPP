#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_fmadd()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()], inputs3[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::load<T>(inputs3);
	mipp::reg r4 = mipp::fmadd<T>(r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i] + inputs3[i];
		REQUIRE(mipp::get<T>(r4, i) == Approx(res));
	}
}

#ifndef MIPP_NO
TEST_CASE("Fused multiplication and addition - mipp::reg", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_reg_fmadd<float>(); }
}
#endif

template <typename T>
void test_Reg_fmadd()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()], inputs3[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)2);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)3);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = inputs3;
	mipp::Reg<T> r4 = mipp::fmadd(r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] * inputs2[i] + inputs3[i];
		REQUIRE(r4[i] == Approx(res));
	}
}

TEST_CASE("Fused multiplication and addition - mipp::Reg", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_fmadd<float>(); }
}

template <typename T>
void test_reg_maskz_fmadd()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::load<T>(inputs3);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r4 = mipp::maskz<T,mipp::fmadd<T>>(m, r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			REQUIRE(mipp::get<T>(r4, i) == Approx(res));
		}
		else
			REQUIRE(mipp::get<T>(r4, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Fused multiplication and addition - mipp::reg - maskz", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_fmadd<float>(); }
}
#endif

template <typename T>
void test_Reg_maskz_fmadd()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = inputs3;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r4 = mipp::maskz<T,mipp::fmadd>(m, r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			REQUIRE(r4[i] == Approx(res));
		}
		else
			REQUIRE(r4[i] == (T)0);
	}
}

TEST_CASE("Fused multiplication and addition - mipp::Reg - maskz", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_fmadd<float>(); }
}

template <typename T>
void test_reg_mask_fmadd()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N], inputs4[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);
	std::iota(inputs4, inputs4 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::load<T>(inputs3);
	mipp::reg r4 = mipp::load<T>(inputs4);
	mipp::msk m  = mipp::set <N>(mask   );

	mipp::reg r5 = mipp::mask<T,mipp::fmadd<T>>(m, r4, r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			REQUIRE(mipp::get<T>(r5, i) == Approx(res));
		}
		else
			REQUIRE(mipp::get<T>(r5, i) == inputs4[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Fused multiplication and addition - mipp::reg - mask", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_fmadd<float>(); }
}
#endif

template <typename T>
void test_Reg_mask_fmadd()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N], inputs3[N], inputs4[N];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);
	std::iota(inputs3, inputs3 + mipp::N<T>(), (T)1);
	std::iota(inputs4, inputs4 + mipp::N<T>(), (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
	std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
	std::shuffle(mask,    mask    + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = inputs3;
	mipp::Reg<T> r4 = inputs4;
	mipp::Msk<N> m  = mask;

	mipp::Reg<T> r5 = mipp::mask<T,mipp::fmadd>(m, r4, r1, r2, r3);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			REQUIRE(r5[i] == Approx(res));
		}
		else
			REQUIRE(r5[i] == inputs4[i]);
	}
}

TEST_CASE("Fused multiplication and addition - mipp::Reg - mask", "[mipp::fmadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_fmadd<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_fmadd<float>(); }
}