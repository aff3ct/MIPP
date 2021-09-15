#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_hmul_int()
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
		auto val = mipp::hmul<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res *= inputs1[i];

		REQUIRE(res == val);
	}
}

template <typename T>
void test_reg_hmul_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(-2, 2);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::loadu<T>(inputs1);
		auto val = mipp::hmul<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res *= inputs1[i];

		// REQUIRE(res == Approx(val).epsilon(0.001));
		REQUIRE(res == Approx(val));
	}
}

#ifndef MIPP_NO
TEST_CASE("Horizontal multiplication - mipp::reg", "[mipp::hmul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_hmul_real<double>(); }
#endif
	SECTION("datatype = float") { test_reg_hmul_real<float>(); }
}
#endif

template <typename T>
void test_Reg_hmul_int()
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
		auto val = mipp::hmul(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res *= inputs1[i];

		REQUIRE(res == val);
	}
}

template <typename T>
void test_Reg_hmul_real()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;
	std::uniform_real_distribution<T> dis(-2, 2);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::hmul(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res *= inputs1[i];

		// REQUIRE(res == Approx(val).epsilon(0.001));
		REQUIRE(res == Approx(val));
	}
}

#ifndef MIPP_NO
TEST_CASE("Horizontal multiplication - mipp::Reg", "[mipp::hmul]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_hmul_real<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_hmul_real<float>(); }
}
#endif
