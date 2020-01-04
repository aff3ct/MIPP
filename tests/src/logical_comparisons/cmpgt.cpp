#include <mipp.h>

#include <algorithm>
#include <catch.hpp>
#include <cmath>
#include <exception>
#include <numeric>
#include <random>

template <typename T>
void test_reg_cmpgt() {
   T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
   std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
   std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

   std::mt19937 g;
   for (auto t = 0; t < 100; t++) {
      std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
      std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

      mipp::reg r1 = mipp::load<T>(inputs1);
      mipp::reg r2 = mipp::load<T>(inputs2);
      mipp::msk m = mipp::cmpgt<T>(r1, r2);

      mipp::reg r3 = mipp::toreg<mipp::N<T>()>(m);

      for (auto i = 0; i < mipp::N<T>(); i++) {
         if (inputs1[i] > inputs2[i])
            REQUIRE(*((T*)&r3 + i) != (T)0);
         else
            REQUIRE(*((T*)&r3 + i) == (T)0);
      }
   }
}

#ifndef MIPP_NO
TEST_CASE("Compare greater than - mipp::reg", "[mipp::cmpgt]") {
#if defined(MIPP_64BIT)
   SECTION("datatype = double") { test_reg_cmpgt<double>(); }
#endif
   SECTION("datatype = float") { test_reg_cmpgt<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
#if defined(MIPP_64BIT)
   SECTION("datatype = int64_t") { test_reg_cmpgt<int64_t>(); }
#endif
#endif
   SECTION("datatype = int32_t") { test_reg_cmpgt<int32_t>(); }
#endif
#if defined(MIPP_BW)
   SECTION("datatype = int16_t") { test_reg_cmpgt<int16_t>(); }
   SECTION("datatype = int8_t") { test_reg_cmpgt<int8_t>(); }
#endif
#if defined(MIPP_AVX2) || defined(MIPP_AVX512)
   SECTION("datatype = uint32_t") { test_reg_cmpgt<uint32_t>(); }
#endif
}
#endif

#if defined(MIPP_AVX512)
void test_Reg_cmpgt_uint32_t() {
	mipp::Reg<uint32_t> a({4294967281, 4294967283, 4294967295, 3, 4, 5, 6, 7,9,10,11,12,13,14,15,16});
	mipp::Reg<uint32_t> b(4294967291);
	mipp::Msk<mipp::N<uint32_t>()> m = a > b;
	for (int i = 0; i < 16; i++) {
		if (i == 2)
			REQUIRE(m[i]);
		else
			REQUIRE(!m[i]);
	}
}
#elif defined(MIPP_AVX)
void test_Reg_cmpgt_uint32_t() {
	mipp::Reg<uint32_t> a({4294967281, 4294967283, 4294967295, 3, 4, 5, 6, 7});
	mipp::Reg<uint32_t> b(4294967291);
	mipp::Msk<mipp::N<uint32_t>()> m = a > b;
	for (int i = 0; i < 8; i++) {
		if (i == 2)
			REQUIRE(m[i]);
		else
			REQUIRE(!m[i]);
	}
}
#endif
template <typename T>
void test_Reg_cmpgt() {
   T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
   std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
   std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

   std::mt19937 g;
   for (auto t = 0; t < 100; t++) {
      std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
      std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

      mipp::Reg<T> r1 = inputs1;
      mipp::Reg<T> r2 = inputs2;
      mipp::Msk<mipp::N<T>()> m = r1 > r2;

      for (auto i = 0; i < mipp::N<T>(); i++)
         REQUIRE(m[i] == (inputs1[i] > inputs2[i]));
   }
}

TEST_CASE("Compare greater than - mipp::Reg", "[mipp::cmpgt]") {
#if defined(MIPP_64BIT)
   SECTION("datatype = double") { test_Reg_cmpgt<double>(); }
#endif
   SECTION("datatype = float") { test_Reg_cmpgt<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
#if defined(MIPP_64BIT)
   SECTION("datatype = int64_t") { test_Reg_cmpgt<int64_t>(); }
#endif
#endif
   SECTION("datatype = int32_t") { test_Reg_cmpgt<int32_t>(); }
#endif
#if defined(MIPP_BW)
   SECTION("datatype = int16_t") { test_Reg_cmpgt<int16_t>(); }
   SECTION("datatype = int8_t") { test_Reg_cmpgt<int8_t>(); }
#endif
#if defined(MIPP_AVX2) || defined(MIPP_AVX512)
   SECTION("datatype = uint32_t") { test_Reg_cmpgt<uint32_t>(); }
   SECTION("datatype = uint32_t") { test_Reg_cmpgt_uint32_t(); }
#endif
}
