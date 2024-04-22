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
	
	std::iota(inputs1, inputs1 + N, (T)0);
	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::set0<T>();
	mipp::reg rexpected = mipp::set0<T>();
		
	std::mt19937 g;
	for (auto t = 0; t < 100; t++)
	{
		// Generate random mask
		int k = 0;
		std::fill_n(expected, N, 0);
		for (int i = 0; i < N; i++) {
			bool bit = (g() & 1) ? false : true; // Generate random bit
			mask1[i] = bit;
			if (bit) {
				expected[k] = i;
				k++;
			}
		}

		mipp::msk mask = mipp::set<N>(mask1);
		
		r2 = mipp::compress<T>(r1, mask);

		for (auto i = 0; i < N; i++) {
			REQUIRE(mipp::get<T>(r2, i) == expected[i]);
		}
	}
}


#if !defined(MIPP_NO) && !defined(MIPP_SVE_LS)
TEST_CASE("Compress - mipp::reg", "[mipp::compress]")
{
#if defined(MIPP_SSE) || defined(MIPP_AVX512) || defined(MIPP_NEON)
	SECTION("datatype = int64_t") { test_reg_compress<int64_t>(); }
	SECTION("datatype = int32_t") { test_reg_compress<int32_t>(); }
#if defined(MIPP_SSE) || defined(MIPP_AVX512VBMI) || defined(MIPP_NEON)
	SECTION("datatype = int16_t") { test_reg_compress<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_compress<int8_t>(); }
#endif
#endif
}
#endif
