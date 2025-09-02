#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>


template <typename T, int n = (sizeof(T) * 8 -1)>
struct reg_rshift
{
	static void test()
	{
		reg_rshift<T,n-1>::test();

		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - (T)mipp::N<T>());

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::rshift<T>(r1, n);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] >> n;
			REQUIRE(mipp::get<T>(r2, i) == res);
		}
	}
};

template <typename T>
struct reg_rshift<T,-1>
{
	static void test() {}
};

#ifndef MIPP_NO
TEST_CASE("Binary right shift - mipp::reg", "[mipp::rshift]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { reg_rshift<int64_t>::test(); }
#endif
	SECTION("datatype = int32_t") { reg_rshift<int32_t>::test(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { reg_rshift<int16_t>::test(); }
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { reg_rshift<int8_t >::test(); }
#endif
#endif
#endif
}
#endif

template <typename T, int n = (sizeof(T) * 8 -1)>
struct Reg_rshift
{
	static void test()
	{
		Reg_rshift<T,n-1>::test();

		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - (T)mipp::N<T>());

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = r1 >> n;

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] >> n;
			REQUIRE(r2[i] == res);
		}
	}
};

template <typename T>
struct Reg_rshift<T,-1>
{
	static void test() {}
};

TEST_CASE("Binary right shift - mipp::Reg", "[mipp::rshift]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { Reg_rshift<int64_t>::test(); }
#endif
	SECTION("datatype = int32_t") { Reg_rshift<int32_t>::test(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { Reg_rshift<int16_t>::test(); }
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { Reg_rshift<int8_t >::test(); }
#endif
#endif
#endif
}

template <typename T, int n = mipp::N<T>()>
struct msk_rshift
{
	static void test()
	{
		msk_rshift<T,n-1>::test();

		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint16_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g) ? true : false;

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::msk m1 = mipp::set<N>(inputs1);
			mipp::msk m2 = mipp::rshift<N>(m1, n);

			std::fill(inputs2, inputs2 + N, 0);
			for (auto i = 0; i < N - n; i++)
				inputs2[i] = inputs1[i +n];

			mipp::reg r = mipp::toreg<N>(m2);

			for (auto i = 0; i < N; i++)
			{
				if (inputs2[i])
					REQUIRE(mipp::get<T>(r, i) != (T)0);
				else
					REQUIRE(mipp::get<T>(r, i) == (T)0);
			}
		}
	}
};

template <typename T>
struct msk_rshift<T,-1>
{
	static void test() {}
};

#ifndef MIPP_NO
#if !defined(MIPP_AVX) && !defined(__clang__) && !defined(_MSC_VER) && !defined(__GNUC__)
TEST_CASE("Binary right shift - mipp::msk", "[mipp::rshift]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { msk_rshift<int64_t>::test(); }
#endif
	SECTION("datatype = int32_t") { msk_rshift<int32_t>::test(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { msk_rshift<int16_t>::test(); }
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { msk_rshift<int8_t >::test(); }
#endif
#endif
#endif
}
#endif
#endif

template <typename T, int n = mipp::N<T>()>
struct Msk_rshift
{
	static void test()
	{
		Msk_rshift<T,n-1>::test();

		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint16_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g) ? true : false;

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::Msk<N> m1 = inputs1;
			mipp::Msk<N> m2 = m1 >> n;

			std::fill(inputs2, inputs2 + N, 0);
			for (auto i = 0; i < N - n; i++)
				inputs2[i] = inputs1[i +n];

			for (auto i = 0; i < N; i++)
			{
				REQUIRE(m2[i] == inputs2[i]);
			}
		}
	}
};

template <typename T>
struct Msk_rshift<T,-1>
{
	static void test() {}
};

#if !defined(MIPP_AVX) && !defined(__clang__) && !defined(_MSC_VER) && !defined(__GNUC__)
TEST_CASE("Binary right shift - mipp::Msk", "[mipp::rshift]")
{
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { Msk_rshift<int64_t>::test(); }
#endif
	SECTION("datatype = int32_t") { Msk_rshift<int32_t>::test(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { Msk_rshift<int16_t>::test(); }
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
	SECTION("datatype = int8_t") { Msk_rshift<int8_t >::test(); }
#endif
#endif
#endif
}
#endif