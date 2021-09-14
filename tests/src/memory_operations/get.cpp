#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_get()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == (T)i);
}

#ifndef MIPP_NO
TEST_CASE("Get - mipp::reg", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_get<double>(); }
#endif
	SECTION("datatype = float") { test_reg_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_get<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_get()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r = mipp::oload<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get(r, i) == (T)i);
}

TEST_CASE("Get - mipp::Reg", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_get<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_get<int8_t>(); }
#endif
}

template <typename T>
void test_reg_2_get()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);

	mipp::reg_2 rl = mipp::low<T>(r);
	mipp::reg_2 rh = mipp::high<T>(r);

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(mipp::get<T>(rl, i) == (T)i);

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(mipp::get<T>(rh, i) == (T)(i+mipp::N<T>()/2));
}

#ifndef MIPP_NO
TEST_CASE("Get - mipp::reg_2", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_2_get<double>(); }
#endif
	SECTION("datatype = float") { test_reg_2_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_2_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_2_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_2_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_2_get<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_2_get()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r = mipp::oload<T>(inputs);

	mipp::Reg_2<T> rl = mipp::low<T>(r);
	mipp::Reg_2<T> rh = mipp::high<T>(r);

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(mipp::get(rl, i) == (T)i);

	for (auto i = 0; i < mipp::N<T>()/2; i++)
		REQUIRE(mipp::get(rh, i) == (T)(i+mipp::N<T>()/2));
}

TEST_CASE("Get - mipp::Reg_2", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_2_get<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_2_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_2_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_2_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_2_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_2_get<int8_t>(); }
#endif
}

template <typename T>
void test_msk_get()
{
	constexpr int N = mipp::N<T>();

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(mask, mask + N, g);

	mipp::msk m = mipp::set<N>(mask);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<N>(m, i) == mask[i]);
}

#ifndef MIPP_NO
TEST_CASE("Get - mipp::msk", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_get<double>(); }
#endif
	SECTION("datatype = float") { test_msk_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_get<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_get()
{
	constexpr int N = mipp::N<T>();

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(mask, mask + N, g);

	mipp::Msk<N> m = mipp::oset<N>(mask);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get(m, i) == mask[i]);
}

TEST_CASE("Get - mipp::Msk", "[mipp::get]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_get<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_get<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_get<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_get<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_get<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_get<int8_t>(); }
#endif
}
