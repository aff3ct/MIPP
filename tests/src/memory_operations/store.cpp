#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);
	mipp::store<T>(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store - mipp::reg", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_store<double>(); }
#endif
	SECTION("datatype = float") { test_reg_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_store<int32_t>(); }
	SECTION("datatype = uint32_t") { test_reg_store<uint32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_store<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.load(inputs);
	r.store(outputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store - mipp::Reg", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_store<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_store<int32_t>(); }
	SECTION("datatype = uint32_t") { test_Reg_store<uint32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_store<int8_t>(); }
#endif
}

template <typename T>
void test_reg_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::loadu<T>(inputs);
	mipp::storeu<T>(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store unaligned - mipp::reg", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_reg_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_storeu<int32_t>(); }
	SECTION("datatype = uint32_t") { test_reg_storeu<uint32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_storeu<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.loadu(inputs);
	r.storeu(outputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store unaligned - mipp::Reg", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_storeu<int32_t>(); }
	SECTION("datatype = uint32_t") { test_Reg_storeu<uint32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_storeu<int8_t>(); }
#endif
}
