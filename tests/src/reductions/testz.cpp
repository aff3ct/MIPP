#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_testz_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis(std::numeric_limits<T2>::min(), (T2)std::numeric_limits<T>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			inputs1[i] = dis(g);

			switch (j%3)
			{
				case 0: inputs2[i] = dis(g);      break;
				case 1: inputs2[i] = ~inputs1[i]; break;
				case 2: inputs2[i] = 0;           break;
			}
		}

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		auto val = mipp::testz<T>(r1, r2);

		for (auto i = 0; i < N; i++)
			inputs2[i] &= inputs1[i];

		auto res = inputs2[0];
		for (auto i = 1; i < N; i++)
			res |= inputs2[i];

		REQUIRE((res == 0) == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Testz - mipp::reg", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_testz_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_testz_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_testz_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_testz_int<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_testz_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N], inputs2[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis(std::numeric_limits<T2>::min(), std::numeric_limits<T2>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			inputs1[i] = dis(g);

			switch (j%3)
			{
				case 0:  inputs2[i] = dis(g);      break;
				case 1:  inputs2[i] = ~inputs1[i]; break;
				case 2:  inputs2[i] = 0;           break;
				default: inputs2[i] = 0;           break;
			}
		}

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		auto val = mipp::testz(r1, r2);

		for (auto i = 0; i < N; i++)
			inputs2[i] &= inputs1[i];

		auto res = inputs2[0];
		for (auto i = 1; i < N; i++)
			res |= inputs2[i];

		REQUIRE((res == 0) == val);
	}
}

TEST_CASE("Testz - mipp::Reg", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_testz_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_testz_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_testz_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_testz_int<int8_t>(); }
#endif
#endif
}

template <typename T>
void test_msk_testz_int()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N], inputs2[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis((T2)0, (T2)1);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			inputs1[i] = dis(g) ? true : false;

			switch (j%3)
			{
				case 0: inputs2[i] = dis(g) ? true : false; break;
				case 1: inputs2[i] = !inputs1[i];           break;
				case 2: inputs2[i] = false;                 break;
			}
		}

		mipp::msk r1 = mipp::set<N>(inputs1);
		mipp::msk r2 = mipp::set<N>(inputs2);
		auto val = mipp::testz<N>(r1, r2);

		for (auto i = 0; i < N; i++)
			inputs2[i] &= inputs1[i];

		auto res = inputs2[0];
		for (auto i = 1; i < N; i++)
			res |= inputs2[i];

		REQUIRE((res == 0) == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Testz - mipp::msk", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_testz_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_testz_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_msk_testz_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_testz_int<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Msk_testz_int()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N], inputs2[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis((T2)0, (T2)1);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			inputs1[i] = dis(g) ? true : false;

			switch (j%3)
			{
				case 0:  inputs2[i] = dis(g) ? true : false; break;
				case 1:  inputs2[i] = !inputs1[i];           break;
				case 2:  inputs2[i] = false;                 break;
				default: inputs2[i] = false;                 break;
			}
		}

		mipp::Msk<N> r1 = inputs1;
		mipp::Msk<N> r2 = inputs2;
		auto val = mipp::testz(r1, r2);

		for (auto i = 0; i < N; i++)
			inputs2[i] &= inputs1[i];

		auto res = inputs2[0];
		for (auto i = 1; i < N; i++)
			res |= inputs2[i];

		REQUIRE((res == 0) == val);
	}
}

TEST_CASE("Testz - mipp::Msk", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_testz_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_testz_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Msk_testz_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_testz_int<int8_t>(); }
#endif
#endif
}

template <typename T>
void test_reg_testz1_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis(std::numeric_limits<T2>::min(), std::numeric_limits<T2>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			switch (j%2)
			{
				case 0:  inputs1[i] = dis(g); break;
				case 1:  inputs1[i] = 0;      break;
				default: inputs1[i] = 0;      break;
			}
		}

		mipp::reg r1 = mipp::load<T>(inputs1);
		auto val = mipp::testz<T>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res |= inputs1[i];

		REQUIRE((res == 0) == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Testz1 - mipp::reg", "[mipp::testz1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_testz1_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_testz1_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_testz1_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_testz1_int<signed char>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Reg_testz1_int()
{
	constexpr int N = mipp::N<T>();
	T inputs1[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis(std::numeric_limits<T2>::min(), std::numeric_limits<T2>::max());

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			switch (j%2)
			{
				case 0:  inputs1[i] = dis(g); break;
				case 1:  inputs1[i] = 0;      break;
				default: inputs1[i] = 0;      break;
			}
		}

		mipp::Reg<T> r1 = inputs1;
		auto val = mipp::testz(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res |= inputs1[i];

		REQUIRE((res == 0) == val);
	}
}

TEST_CASE("Testz1 - mipp::Reg", "[mipp::testz1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_testz1_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_testz1_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_testz1_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_testz1_int<int8_t>(); }
#endif
#endif
}

template <typename T>
void test_msk_testz1_int()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis((T2)0, (T2)1);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			switch (j%3)
			{
				case 0:  inputs1[i] = dis(g) ? true : false; break;
				case 1:  inputs1[i] = true;                  break;
				case 2:  inputs1[i] = false;                 break;
				default: inputs1[i] = false;                 break;
			}
		}

		mipp::msk r1 = mipp::set<N>(inputs1);
		auto val = mipp::testz<N>(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res |= inputs1[i];

		REQUIRE((res == 0) == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Testz1 - mipp::msk", "[mipp::testz1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_testz1_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_testz1_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_msk_testz1_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_testz1_int<int8_t>(); }
#endif
#endif
}
#endif

template <typename T>
void test_Msk_testz1_int()
{
	constexpr int N = mipp::N<T>();
	bool inputs1[N];
	std::mt19937 g;

	typedef typename std::conditional<sizeof(T) == 1, signed char,
	        typename std::conditional<sizeof(T) == 2, short,
	        typename std::conditional<sizeof(T) == 4, int,
	                                                  long long>::type>::type>::type T2;

	std::uniform_int_distribution<T2> dis((T2)0, (T2)1);

	for (auto j = 0; j < 100; j++)
	{
		for (auto i = 0; i < N; i++)
		{
			switch (j%3)
			{
				case 0:  inputs1[i] = dis(g) ? true : false; break;
				case 1:  inputs1[i] = true;                  break;
				case 2:  inputs1[i] = false;                 break;
				default: inputs1[i] = false;                 break;
			}
		}

		mipp::Msk<N> r1 = inputs1;
		auto val = mipp::testz(r1);

		auto res = inputs1[0];
		for (auto i = 1; i < N; i++)
			res |= inputs1[i];

		REQUIRE((res == 0) == val);
	}
}

#ifndef MIPP_NO
TEST_CASE("Testz1 - mipp::Msk", "[mipp::testz1]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_testz1_int<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_testz1_int<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Msk_testz1_int<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_testz1_int<int8_t>(); }
#endif
#endif
}
#endif
