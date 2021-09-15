#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_hmax_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::loadu<T>(inputs1);
		auto val = mipp::hmax<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::max(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

template <typename T>
void test_reg_hmax_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::loadu<T>(inputs1);
		auto val = mipp::hmax<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::max(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Horizontal maximum - mipp::reg", "[mipp::hmax]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_hmax_real<double>(); }
#endif
	SECTION("datatype = float") { test_reg_hmax_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_reg_hmax_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_hmax_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_hmax_int<int16_t>(); }
#endif
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_reg_hmax_int<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_hmax_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::hmax(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::max(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

template <typename T>
void test_Reg_hmax_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::hmax(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::max(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

TEST_CASE("Horizontal maximum - mipp::Reg", "[mipp::hmax]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_hmax_real<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_hmax_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_Reg_hmax_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_hmax_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_hmax_int<int16_t>(); }
#endif
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_Reg_hmax_int<int8_t>(); }
#endif
#endif
#endif
}