#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_deinterleave()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	T inputs[2*mipp::N<T>()];
	std::copy(inputs1, inputs1 + mipp::N<T>(), inputs               );
	std::copy(inputs2, inputs2 + mipp::N<T>(), inputs + mipp::N<T>());

	mipp::reg r1 = mipp::load<T>(inputs1);
	mipp::reg r2 = mipp::load<T>(inputs2);

	mipp::regx2 ri = mipp::deinterleave<T>(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(ri.val[0], i) == inputs[2 * i +0]);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(ri.val[1], i) == inputs[2 * i +1]);
}

#ifndef MIPP_NO
TEST_CASE("Deinterleave - mipp::reg", "[mipp::deinterleave]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_deinterleave<double>(); }
#endif
	SECTION("datatype = float") { test_reg_deinterleave<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_deinterleave<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_deinterleave<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_reg_deinterleave<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int8_t") { test_reg_deinterleave<int8_t>(); }
#endif
#endif
#endif
}
#endif

template <typename T>
void test_Reg_deinterleave()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::mt19937 g;
	std::iota   (inputs1, inputs1 + mipp::N<T>(), (T)0);
	std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
	std::iota   (inputs2, inputs2 + mipp::N<T>(), (T)0);
	std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

	T inputs[2*mipp::N<T>()];
	std::copy(inputs1, inputs1 + mipp::N<T>(), inputs               );
	std::copy(inputs2, inputs2 + mipp::N<T>(), inputs + mipp::N<T>());

	mipp::Reg<T> r1 = inputs1;
	mipp::Reg<T> r2 = inputs2;

	mipp::Regx2<T> ri = mipp::deinterleave(r1, r2);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(ri[0][i] == inputs[2 * i +0]);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(ri[1][i] == inputs[2 * i +1]);
}

TEST_CASE("Deinterleave - mipp::Reg", "[mipp::deinterleave]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_deinterleave<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_deinterleave<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_deinterleave<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_deinterleave<int32_t>(); }
#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
	SECTION("datatype = int16_t") { test_Reg_deinterleave<int16_t>(); }
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	SECTION("datatype = int8_t") { test_Reg_deinterleave<int8_t>(); }
#endif
#endif
#endif
}
