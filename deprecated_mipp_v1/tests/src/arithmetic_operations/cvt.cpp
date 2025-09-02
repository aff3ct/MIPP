#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T1, typename T2>
void test_reg_cvt()
{
	constexpr int N1 = mipp::N<T1>();
	constexpr int N2 = mipp::N<T2>();

	T1 inputs1[N1];
	std::iota(inputs1, inputs1 + N1, (T1)-N1/2);

	for (auto i = 0; i < N1; i++)
		inputs1[i] += i % 2 ? (T1)0.4 : (T1)0.6;

	mipp::reg r1 = mipp::load<T1>(inputs1);
	mipp::reg r2 = N1 != N2 ? mipp::cvt<T1,T2>(mipp::low<T1>(r1)) : mipp::cvt<T1,T2>(r1);

	for (auto i = 0; i < N2; i++)
	{
		auto res = static_cast<T2>(std::round(inputs1[i]));
		REQUIRE(mipp::get<T2>(r2, i) == res);
	}
}

#ifndef MIPP_NO
TEST_CASE("Convert - mipp::reg", "[mipp::cvt]")
{
#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(__AVX512DQ__))
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t -> double") { test_reg_cvt<int64_t,double>(); }
	SECTION("datatype = double -> int64_t") { test_reg_cvt<double,int64_t>(); }
#endif
#endif
#endif
	SECTION("datatype = int32_t -> float") { test_reg_cvt<int32_t,float>(); }
	SECTION("datatype = float -> int32_t") { test_reg_cvt<float,int32_t>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#if defined(MIPP_64BIT)
	SECTION("datatype = int32_t -> int64_t") { test_reg_cvt<int32_t,int64_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t -> int32_t") { test_reg_cvt<int16_t,int32_t>(); }
	SECTION("datatype = int8_t -> int16_t") { test_reg_cvt<int8_t,int16_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T1, typename T2>
void test_Reg_cvt()
{
	constexpr int N1 = mipp::N<T1>();
	constexpr int N2 = mipp::N<T2>();

	T1 inputs1[N1];
	std::iota(inputs1, inputs1 + N1, (T1)-N1/2);

	for (auto i = 0; i < N1; i++)
		inputs1[i] += i % 2 ? (T1)0.4 : (T1)0.6;

	mipp::Reg<T1> r1 = inputs1;
	mipp::Reg<T2> r2 = N1 != N2 ? mipp::cvt<T1,T2>(r1.low()) : mipp::cvt<T1,T2>(r1);

	for (auto i = 0; i < N2; i++)
	{
		auto res = static_cast<T2>(std::round(inputs1[i]));
		REQUIRE(r2[i] == res);
	}
}

TEST_CASE("Convert - mipp::Reg", "[mipp::cvt]")
{
#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(__AVX512DQ__))
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	SECTION("datatype = int64_t -> double") { test_Reg_cvt<int64_t,double>(); }
	SECTION("datatype = double -> int64_t") { test_Reg_cvt<double,int64_t>(); }
#endif
#endif
#endif
	SECTION("datatype = int32_t -> float") { test_Reg_cvt<int32_t,float>(); }
	SECTION("datatype = float -> int32_t") { test_Reg_cvt<float,int32_t>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#if defined(MIPP_64BIT)
	SECTION("datatype = int32_t -> int64_t") { test_Reg_cvt<int32_t,int64_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t -> int32_t") { test_Reg_cvt<int16_t,int32_t>(); }
	SECTION("datatype = int8_t -> int16_t") { test_Reg_cvt<int8_t,int16_t>(); }
#endif
#endif
#endif
}
