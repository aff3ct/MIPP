#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_hadd_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis((T)-10, (T)10);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::loadu<T>(inputs1);
		auto val = mipp::hadd<T>(r1);

		int64_t acc = inputs1[0];
		for (auto i = 1; i < N; i++)
			acc += (int64_t)inputs1[i];

		T res = (T)std::max(std::min(acc, (int64_t)std::numeric_limits<T>::max()),
		                                  (int64_t)std::numeric_limits<T>::min());

		REQUIRE(res == val);
	}
}

template <typename T>
void test_reg_hadd_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(-100, 100);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::loadu<T>(inputs1);
		auto val = mipp::hadd<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res += inputs1[i];

		// REQUIRE(res == Approx(val).epsilon(0.001));
		REQUIRE(res == Approx(val));
	}
}

#ifndef MIPP_NO
TEST_CASE("Horizontal addition - mipp::reg", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_hadd_real<double>(); }
#endif
	SECTION("datatype = float") { test_reg_hadd_real<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_hadd_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_hadd_int<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_hadd_int<int16_t>(); }
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_reg_hadd_int<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_hadd_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_int_distribution<T> dis((T)-10, (T)10);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::hadd(r1);

		int64_t acc = inputs1[0];
		for (auto i = 1; i < N; i++)
			acc += (int64_t)inputs1[i];

		T res = (T)std::max(std::min(acc, (int64_t)std::numeric_limits<T>::max()),
		                                  (int64_t)std::numeric_limits<T>::min());

		REQUIRE(res == val);
	}
}

template <typename T>
void test_Reg_hadd_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(-100, 100);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::hadd(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res += inputs1[i];

		// REQUIRE(res == Approx(val).epsilon(0.001));
		REQUIRE(res == Approx(val));
	}
}

TEST_CASE("Horizontal addition - mipp::Reg", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_hadd_real<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_hadd_real<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_hadd_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_hadd_int<int32_t>(); }
#endif
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_hadd_int<int16_t>(); }
#ifndef _MSC_VER
	SECTION("datatype = int8_t") { test_Reg_hadd_int<int8_t>(); }
#endif
#endif
#endif
}