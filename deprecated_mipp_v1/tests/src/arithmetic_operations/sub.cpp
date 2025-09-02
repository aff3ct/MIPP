#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_sub()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::sub <T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] - inputs2[i];
		REQUIRE(mipp::get<T>(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Subtraction - mipp::reg", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_sub<double>(); }
#endif
	SECTION("datatype = float") { test_reg_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_sub<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_sub()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = r1 - r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] - inputs2[i];
		REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Subtraction - mipp::Reg", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_sub<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_sub<int8_t>(); }
#endif
}

template <typename T>
void test_reg_maskz_sub()
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

	mipp::reg r3 = mipp::maskz<T,mipp::sub<T>>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] - inputs2[i];
			REQUIRE(mipp::get<T>(r3, i) == res);
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Subtraction - mipp::reg - maskz", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_sub<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskz_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskz_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskz_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_maskz_sub<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_maskz_sub()
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

	mipp::Reg<T> r3 = mipp::maskz<T,mipp::sub>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] - inputs2[i];
			REQUIRE(r3[i] == res);
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

TEST_CASE("Subtraction - mipp::Reg - maskz", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_sub<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskz_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskz_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskz_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_maskz_sub<int8_t>(); }
#endif
}

template <typename T>
void test_reg_mask_sub()
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

	mipp::reg r4 = mipp::mask<T,mipp::sub<T>>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] - inputs2[i];
			REQUIRE(mipp::get<T>(r4, i) == res);
		}
		else
			REQUIRE(mipp::get<T>(r4, i) == inputs3[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Subtraction - mipp::reg - mask", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_sub<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_mask_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_mask_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_mask_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_mask_sub<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_mask_sub()
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

	mipp::Reg<T> r4 = mipp::mask<T,mipp::sub>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] - inputs2[i];
			REQUIRE(r4[i] == res);
		}
		else
			REQUIRE(r4[i] == inputs3[i]);
	}
}

TEST_CASE("Subtraction - mipp::Reg - mask", "[mipp::sub]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_sub<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_sub<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_mask_sub<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_mask_sub<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_mask_sub<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_mask_sub<int8_t>(); }
#endif
}