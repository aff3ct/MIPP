#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_sign()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + N, (T)-N/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + N, g);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::msk m  = mipp::sign<T>(r1);
	mipp::reg r2 = mipp::toreg<N>(m);

	for (auto i = 0; i < N; i++)
	{
		if (inputs1[i] >= 0)
			REQUIRE(mipp::get<T>(r2, i) == (T)0);
		else
			REQUIRE(mipp::get<T>(r2, i) != (T)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Sign - mipp::reg", "[mipp::sign]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_sign<double>(); }
#endif
	SECTION("datatype = float") { test_reg_sign<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
	SECTION("datatype = int64_t") { test_reg_sign<int64_t>(); }
#endif
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_reg_sign<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_sign<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_sign<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_sign()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + N, (T)-N/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + N, g);

	mipp::Reg<T> r1 = inputs1;
	mipp::Msk<N> m  = mipp::sign(r1);
	mipp::Reg<T> r2 = mipp::toreg<N>(m.m);

	for (auto i = 0; i < N; i++)
	{
		if (inputs1[i] >= 0)
			REQUIRE(r2[i] == (T)0);
		else
			REQUIRE(r2[i] != (T)0);
	}
}

TEST_CASE("Sign - mipp::Reg", "[mipp::sign]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_sign<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_sign<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
	SECTION("datatype = int64_t") { test_Reg_sign<int64_t>(); }
#endif
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int32_t") { test_Reg_sign<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_sign<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_sign<int8_t>(); }
#endif
}
