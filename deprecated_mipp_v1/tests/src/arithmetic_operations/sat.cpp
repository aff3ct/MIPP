#include <type_traits>
#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_sat_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto i = 0; i < 100; i++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::load<T>(inputs1);

		T n1 = dis(g);
		T n2 = dis(g);

		T m = std::min<T>(n1, n2);
		T M = std::max<T>(n1, n2);

		mipp::reg r2 = mipp::sat<T>(r1, m, M);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::min<T>(std::max<T>(inputs1[i], m), M);
			REQUIRE(mipp::get<T>(r2, i) == res);
		}
	}
}

template <typename T>
void test_reg_sat_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto i = 0; i < 100; i++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::load<T>(inputs1);

		T n1 = dis(g);
		T n2 = dis(g);

		T m = std::min<T>(n1, n2);
		T M = std::max<T>(n1, n2);

		mipp::reg r2 = mipp::sat<T>(r1, m, M);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::min<T>(std::max<T>(inputs1[i], m), M);
			REQUIRE(mipp::get<T>(r2, i) == res);
		}
	}
}

#ifndef MIPP_NO
TEST_CASE("Saturation - mipp::reg", "[mipp::sat]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_sat_real<double>(); }
#endif
	SECTION("datatype = float") { test_reg_sat_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_reg_sat_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_sat_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_sat_int<int16_t>(); }
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_reg_sat_int<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_sat_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto i = 0; i < 100; i++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;

		T n1 = dis(g);
		T n2 = dis(g);

		T m = std::min<T>(n1, n2);
		T M = std::max<T>(n1, n2);

		mipp::Reg<T> r2 = mipp::sat(r1, m, M);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::min<T>(std::max<T>(inputs1[i], m), M);
			REQUIRE(r2[i] == res);
		}
	}
}

template <typename T>
void test_Reg_sat_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto i = 0; i < 100; i++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;

		T n1 = dis(g);
		T n2 = dis(g);

		T m = std::min<T>(n1, n2);
		T M = std::max<T>(n1, n2);

		mipp::Reg<T> r2 = mipp::sat(r1, m, M);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::min<T>(std::max<T>(inputs1[i], m), M);
			REQUIRE(r2[i] == res);
		}
	}
}

TEST_CASE("Saturation - mipp::Reg", "[mipp::sat]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_sat_real<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_sat_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_Reg_sat_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_sat_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_sat_int<int16_t>(); }
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_Reg_sat_int<int8_t>(); }
#endif
#endif
#endif
}
