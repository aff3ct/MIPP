#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_hmin_int()
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
		auto val = mipp::hmin<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::min(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

template <typename T>
void test_reg_hmin_real()
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
		auto val = mipp::hmin<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::min(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Horizontal minimum - mipp::reg", "[mipp::hmin]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_hmin_real<double>(); }
#endif
	SECTION("datatype = float") { test_reg_hmin_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_reg_hmin_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_reg_hmin_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_hmin_int<int16_t>(); }
#endif
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_reg_hmin_int<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_hmin_int()
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
		auto val = mipp::hmin(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::min(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

template <typename T>
void test_Reg_hmin_real()
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
		auto val = mipp::hmin(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res = std::min(res, inputs1[i]);

		REQUIRE(res == val);
	}
}

TEST_CASE("Horizontal minimum - mipp::Reg", "[mipp::hmin]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_hmin_real<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_hmin_real<float>(); }

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_Reg_hmin_int<int64_t>(); }
#endif
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int32_t") { test_Reg_hmin_int<int32_t>(); }
#endif
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_hmin_int<int16_t>(); }
#endif
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_Reg_hmin_int<int8_t>(); }
#endif
#endif
#endif
}