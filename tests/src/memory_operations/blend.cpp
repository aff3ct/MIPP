#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_blend()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + N, (T)0);
	std::iota(inputs2, inputs2 + N, (T)N);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto t = 0; t < 100; t++)
	{
		std::shuffle(mask, mask + N, g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg ri = mipp::blend<T>(r1, r2, m);

		for (auto i = 0; i < N; i++)
			REQUIRE(mipp::get<T>(ri, i) == (mask[i] ? inputs1[i] : inputs2[i]));
	}
}

#ifndef MIPP_NO
TEST_CASE("Blend - mipp::reg", "[mipp::blend]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_blend<double>(); }
#endif
	SECTION("datatype = float") { test_reg_blend<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_blend<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_blend<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_blend<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_blend<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_blend()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::iota(inputs1, inputs1 + N, (T)0);
	std::iota(inputs2, inputs2 + N, (T)N);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto t = 0; t < 100; t++)
	{
		std::shuffle(mask, mask + N, g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> ri = mipp::blend(r1, r2, m);

		for (auto i = 0; i < N; i++)
			REQUIRE(ri[i] == (mask[i] ? inputs1[i] : inputs2[i]));
	}
}

TEST_CASE("Blend - mipp::Reg", "[mipp::blend]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_blend<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_blend<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_blend<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_blend<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_blend<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_blend<int8_t>(); }
#endif
}