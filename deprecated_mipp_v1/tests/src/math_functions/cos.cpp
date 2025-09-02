#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_cos()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::cos<T>(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = std::cos(inputs1[i]);
		// REQUIRE(mipp::get<T>(r2, i) == Approx(res).epsilon(0.001));
		REQUIRE(mipp::get<T>(r2, i) == Approx(res));
	}
}

#ifndef MIPP_NO
TEST_CASE("Cosine - mipp::reg", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_reg_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_reg_cos<double>(); }
#endif
}
#endif


template <typename T>
void test_Reg_cos()
{
	T inputs1[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = mipp::cos(r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = std::cos(inputs1[i]);
		// REQUIRE(r2[i] == Approx(res).epsilon(0.001));
		REQUIRE(r2[i] == Approx(res));
	}
}

TEST_CASE("Cosine - mipp::Reg", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_Reg_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_Reg_cos<double>(); }
#endif
}


template <typename T>
void test_reg_maskz_cos()
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

	mipp::reg r2 = mipp::maskz<T,mipp::cos<T>>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = std::cos(inputs1[i]);
			// REQUIRE(mipp::get<T>(r2, i) == Approx(res).epsilon(0.001));
			REQUIRE(mipp::get<T>(r2, i) == Approx(res));
		}
		else
			REQUIRE(mipp::get<T>(r2, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Cosine - mipp::reg - maskz", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_reg_maskz_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_reg_maskz_cos<double>(); }
#endif
}
#endif

template <typename T>
void test_Reg_maskz_cos()
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

	mipp::Reg<T> r2 = mipp::maskz<T,mipp::cos>(m, r1);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
		{
			T res = std::cos(inputs1[i]);
			// REQUIRE(r2[i] == Approx(res).epsilon(0.001));
			REQUIRE(r2[i] == Approx(res));
		}
		else
			REQUIRE(r2[i] == (T)0);
	}
}

TEST_CASE("Cosine - mipp::Reg - maskz", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_Reg_maskz_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_Reg_maskz_cos<double>(); }
#endif
}

template <typename T>
void test_reg_mask_cos()
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

	mipp::reg r3 = mipp::mask<T,mipp::cos<T>>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = std::cos(inputs1[i]);
			// REQUIRE(mipp::get<T>(r3, i) == Approx(res).epsilon(0.001));
			REQUIRE(mipp::get<T>(r3, i) == Approx(res));
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == inputs2[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Cosine - mipp::reg - mask", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_reg_mask_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_reg_mask_cos<double>(); }
#endif
}
#endif

template <typename T>
void test_Reg_mask_cos()
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

	mipp::Reg<T> r3 = mipp::mask<T,mipp::cos>(m, r2, r1);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = std::cos(inputs1[i]);
			// REQUIRE(r3[i] == Approx(res).epsilon(0.001));
			REQUIRE(r3[i] == Approx(res));
		}
		else
			REQUIRE(r2[i] == inputs2[i]);
	}
}

TEST_CASE("Cosine - mipp::Reg - mask", "[mipp::cos]")
{
	SECTION("datatype = float" ) { test_Reg_mask_cos<float>(); }
#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	SECTION("datatype = double") { test_Reg_mask_cos<double>(); }
#endif
}