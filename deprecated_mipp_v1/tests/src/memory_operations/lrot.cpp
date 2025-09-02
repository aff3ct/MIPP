#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_lrot()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + N, (T)0);

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::lrot<T>(r1);

	for (auto i = 0; i < N; i++)
		REQUIRE(mipp::get<T>(r2, i) == (i == N-1 ? inputs1[0] : inputs1[i+1]));
}

#ifndef MIPP_NO
TEST_CASE("Left rotation (cyclic permutation) - mipp::reg", "[mipp::lrot]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_lrot<double>(); }
#endif
	SECTION("datatype = float") { test_reg_lrot<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_lrot<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_lrot<int32_t>(); }
#if defined(MIPP_BW)
#if (!defined(MIPP_SSE) && !defined(MIPP_AVX512)) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int16_t") { test_reg_lrot<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_lrot<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_lrot()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::iota(inputs1, inputs1 + N, (T)0);

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = mipp::lrot(r1);

	for (auto i = 0; i < N; i++)
		REQUIRE(r2[i] == (i == N-1 ? inputs1[0] : inputs1[i+1]));
}

TEST_CASE("Left rotation (cyclic permutation) - mipp::Reg", "[mipp::lrot]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_lrot<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_lrot<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_lrot<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_lrot<int32_t>(); }
#if defined(MIPP_BW)
#if (!defined(MIPP_SSE) && !defined(MIPP_AVX512)) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int16_t") { test_Reg_lrot<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_lrot<int8_t>(); }
#endif
#endif
}
