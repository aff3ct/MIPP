#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_add()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);
	mipp::reg r3 = mipp::add <T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] + inputs2[i];
		REQUIRE(mipp::get<T>(r3, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Addition - mipp::reg", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_add<double>(); }
#endif
	SECTION("datatype = float") { test_reg_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_add<int64_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_AVX512)&& !defined(MIPP_SVE_LS)
	SECTION("datatype = uint64_t") { test_reg_add<uint64_t>(); }
#endif
#endif
	SECTION("datatype = int32_t") { test_reg_add<int32_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_AVX512)&& !defined(MIPP_SVE_LS)
	SECTION("datatype = uint32_t") { test_reg_add<uint32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_add<int16_t>(); }
	SECTION("datatype = uint16_t") { test_reg_add<uint16_t>(); }
	SECTION("datatype = int8_t") { test_reg_add<int8_t>(); }
	SECTION("datatype = uint8_t") { test_reg_add<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_reg_2_add()
{
    constexpr auto N_2 = mipp::N<T>()/2;

    T inputs1[N_2], inputs2[N_2];
    std::iota(inputs1, inputs1 + N_2, (T)1);
    std::iota(inputs2, inputs2 + N_2, (T)1);

    std::mt19937 g;
    std::shuffle(inputs1, inputs1 + N_2, g);
    std::shuffle(inputs2, inputs2 + N_2, g);

    mipp::reg_2 r1 = mipp::load_2<T>(inputs1);
    mipp::reg_2 r2 = mipp::load_2<T>(inputs2);
    mipp::reg_2 r3 = mipp::add <T>(r1, r2);

    for (auto i = 0; i < N_2; i++)
    {
        T res = inputs1[i] + inputs2[i];
        REQUIRE(mipp::get<T>(r3, i) == res);
    }
}

#ifndef MIPP_NO
#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Addition - mipp::reg_2", "[mipp::add]")
{
	SECTION("datatype = int32_t") { test_reg_2_add<int32_t>(); }
}
#endif
#endif

template <typename T>
void test_Reg_add()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;
	mipp::Reg<T> r3 = r1 + r2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		T res = inputs1[i] + inputs2[i];
		REQUIRE(r3[i] == res);
	}
}

TEST_CASE("Addition - mipp::Reg", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_add<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_add<int64_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_AVX512)&& !defined(MIPP_SVE_LS)
	SECTION("datatype = uint64_t") { test_Reg_add<uint64_t>(); }
#endif
#endif
	SECTION("datatype = int32_t") { test_Reg_add<int32_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_AVX512) && !defined(MIPP_SVE_LS)
	SECTION("datatype = uint32_t") { test_Reg_add<uint32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_add<int16_t>(); }
	SECTION("datatype = uint16_t") { test_Reg_add<uint16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_add<int8_t>(); }
	SECTION("datatype = uint8_t") { test_Reg_add<uint8_t>(); }
#endif
}

template <typename T>
void test_Reg_2_add()
{
    constexpr auto N_2 = mipp::N<T>()/2;

    T inputs1[N_2], inputs2[N_2];
    std::iota(inputs1, inputs1 + N_2, (T)1);
    std::iota(inputs2, inputs2 + N_2, (T)1);

    std::mt19937 g;
    std::shuffle(inputs1, inputs1 + N_2, g);
    std::shuffle(inputs2, inputs2 + N_2, g);

    mipp::Reg_2<T> r1 = inputs1;
    mipp::Reg_2<T> r2 = inputs2;
    mipp::Reg_2<T> r3 = r1 + r2;

    for (auto i = 0; i < N_2; i++)
    {
        T res = inputs1[i] + inputs2[i];
        REQUIRE(r3[i] == res);
    }
}

#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Addition - mipp::Reg_2", "[mipp::add]")
{
    SECTION("datatype = int32_t") { test_Reg_2_add<int32_t>(); }
}
#endif

template <typename T>
void test_reg_maskz_add()
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

	mipp::reg r3 = mipp::maskz<T,mipp::add<T>>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] + inputs2[i];
			REQUIRE(mipp::get<T>(r3, i) == res);
		}
		else
			REQUIRE(mipp::get<T>(r3, i) == (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Addition - mipp::reg - maskz", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskz_add<double>(); }
#endif
	SECTION("datatype = float") { test_reg_maskz_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskz_add<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskz_add<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskz_add<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_maskz_add<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_maskz_add()
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

	mipp::Reg<T> r3 = mipp::maskz<T,mipp::add>(m, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] + inputs2[i];
			REQUIRE(r3[i] == res);
		}
		else
			REQUIRE(r3[i] == (T)0);
	}
}

TEST_CASE("Addition - mipp::Reg - maskz", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskz_add<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskz_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskz_add<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskz_add<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskz_add<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_maskz_add<int8_t>(); }
#endif
}

template <typename T>
void test_reg_mask_add()
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

	mipp::reg r4 = mipp::mask<T,mipp::add<T>>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] + inputs2[i];
			REQUIRE(mipp::get<T>(r4, i) == res);
		}
		else
			REQUIRE(mipp::get<T>(r4, i) == inputs3[i]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Addition - mipp::reg - mask", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_mask_add<double>(); }
#endif
	SECTION("datatype = float") { test_reg_mask_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_mask_add<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_mask_add<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_mask_add<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_mask_add<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_mask_add()
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

	mipp::Reg<T> r4 = mipp::mask<T,mipp::add>(m, r3, r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		if (mask[i])
		{
			T res = inputs1[i] + inputs2[i];
			REQUIRE(r4[i] == res);
		}
		else
			REQUIRE(r4[i] == inputs3[i]);
	}
}

TEST_CASE("Addition - mipp::Reg - mask", "[mipp::add]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_mask_add<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_mask_add<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_mask_add<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_mask_add<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_mask_add<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_mask_add<int8_t>(); }
#endif
}