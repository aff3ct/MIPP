#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_getfirst()
{
	constexpr int N = mipp::N<T>();

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);

	mipp::reg r = mipp::load<T>(inputs);

	REQUIRE(mipp::getfirst<T>(r) == inputs[0]);
}

#ifndef MIPP_NO
TEST_CASE("Get first - mipp::reg", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_reg_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_getfirst<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_getfirst()
{
	constexpr int N = mipp::N<T>();

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);

	mipp::Reg<T> r = mipp::oload<T>(inputs);

	REQUIRE(mipp::getfirst(r) == inputs[0]);
}

TEST_CASE("Get first - mipp::Reg", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_getfirst<int8_t>(); }
#endif
}

template <typename T>
void test_reg_2_getfirst()
{
	constexpr int N = mipp::N<T>();

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);

	mipp::reg r = mipp::load<T>(inputs);

	mipp::reg_2 rl = mipp::low<T>(r);
	mipp::reg_2 rh = mipp::high<T>(r);

	REQUIRE(mipp::getfirst<T>(rl) == (T)inputs[0]);
	REQUIRE(mipp::getfirst<T>(rh) == (T)inputs[mipp::N<T>()/2]);
}

#ifndef MIPP_NO
TEST_CASE("Get first - mipp::reg_2", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_2_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_reg_2_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_2_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_2_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_2_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_2_getfirst<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_2_getfirst()
{
	constexpr int N = mipp::N<T>();

	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);

	mipp::Reg<T> r = mipp::oload<T>(inputs);

	mipp::Reg_2<T> rl = mipp::low<T>(r);
	mipp::Reg_2<T> rh = mipp::high<T>(r);

	REQUIRE(mipp::getfirst(rl) == (T)inputs[0]);
	REQUIRE(mipp::getfirst(rh) == (T)inputs[mipp::N<T>()/2]);
}

TEST_CASE("Get first - mipp::Reg_2", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_2_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_2_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_2_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_2_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_2_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_2_getfirst<int8_t>(); }
#endif
}

template <typename T>
void test_msk_getfirst()
{
	constexpr int N = mipp::N<T>();

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(mask, mask + N, g);

	mipp::msk m = mipp::set<N>(mask);

	REQUIRE(mipp::getfirst<N>(m) == mask[0]);
}

#ifndef MIPP_NO
TEST_CASE("Get first - mipp::msk", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_msk_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_getfirst<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_getfirst()
{
	constexpr int N = mipp::N<T>();

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(mask, mask + N, g);

	mipp::Msk<N> m = mipp::oset<N>(mask);

	REQUIRE(mipp::getfirst(m) == mask[0]);
}

TEST_CASE("Get first - mipp::Msk", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_getfirst<int8_t>(); }
#endif
}
