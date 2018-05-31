#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), 0);

	mipp::reg r = mipp::load<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(*((T*)&r +i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load - mipp::reg", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_load<double>(); }
#endif
	SECTION("datatype = float") { test_reg_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_load<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), 0);

	mipp::Reg<T> r; r.load(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load - mipp::Reg", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_load<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_load<int8_t>(); }
#endif
}

template <typename T>
void test_reg_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), 0);

	mipp::reg r = mipp::loadu<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE( *((T*)&r +i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load unaligned - mipp::reg", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_reg_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_loadu<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), 0);

	mipp::Reg<T> r; r.loadu(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load unaligned - mipp::Reg", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_loadu<int8_t>(); }
#endif
}
