#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <array>
#include <catch.hpp>

template <typename T>
void test_reg_compress()
{
	constexpr int N = mipp::N<T>();

	T inputs1[N];
	T expected[N];
	bool mask1[N];

	std::iota(inputs1, inputs1 + N, (T)1);
	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::set0<T>();

	std::mt19937 g;
	for (auto t = 0; t < 1000; t++)
	{
		// Generate random mask
		int k = 0;
		std::fill_n(expected, N, 0);
		for (int i = 0; i < N; i++)
		{
			bool bit = (g() & 1) ? false : true; // Generate random bit
			mask1[i] = bit;
			if (bit)
				expected[k++] = i + (T)1;
		}

		mipp::msk mask = mipp::set<N>(mask1);
		
		r2 = mipp::compress<T>(r1, mask);

		for (auto i = 0; i < N; i++)
			REQUIRE(mipp::get<T>(r2, i) == expected[i]);
	}
}

#if defined(MIPP_STATIC_LIB) && !defined(MIPP_NO)
TEST_CASE("Compress - mipp::reg", "[mipp::compress]")
{
#if (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31) || defined(MIPP_AVX512) || defined(MIPP_NEON) || (defined(MIPP_AVX2) && defined(MIPP_BMI2))
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_compress<double>(); }
#endif
	SECTION("datatype = float") { test_reg_compress<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_compress<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_compress<int32_t>(); }
#if defined(MIPP_BW) && !defined(MIPP_AVX)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI2))
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && defined(MIPP_BMI2))
	SECTION("datatype = int16_t") { test_reg_compress<int16_t>(); }
#endif
	SECTION("datatype = int8_t") { test_reg_compress<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_compress()
{
	constexpr int N = mipp::N<T>();

	T inputs1[N];
	T expected[N];
	bool mask1[N];

	std::iota(inputs1, inputs1 + N, (T)1);
	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = (T)0;

	std::mt19937 g;
	for (auto t = 0; t < 1000; t++)
	{
		// Generate random mask
		int k = 0;
		std::fill_n(expected, N, 0);
		for (int i = 0; i < N; i++)
		{
			bool bit = (g() & 1) ? false : true; // Generate random bit
			mask1[i] = bit;
			if (bit)
				expected[k++] = i + (T)1;
		}

		mipp::Msk<mipp::N<T>()> mask = mask1;

		r2 = mipp::compress(r1, mask);

		for (auto i = 0; i < N; i++)
			REQUIRE(r2[i] == expected[i]);
	}
}

#if defined(MIPP_STATIC_LIB) && !defined(MIPP_NO)
TEST_CASE("Compress - mipp::Reg", "[mipp::compress]")
{
#if (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31) || defined(MIPP_AVX512) || defined(MIPP_NEON) || (defined(MIPP_AVX2) && defined(MIPP_BMI2))
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_compress<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_compress<float>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_compress<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_compress<int32_t>(); }
#if defined(MIPP_BW) && !defined(MIPP_AVX)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI2))
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && defined(MIPP_BMI2))
	SECTION("datatype = int16_t") { test_Reg_compress<int16_t>(); }
#endif
	SECTION("datatype = int8_t") { test_Reg_compress<int8_t>(); }
#endif
#endif
#endif
}
#endif
