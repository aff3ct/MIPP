#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>

//this file is relevant to test get_k (mask get operation)

//same test as set
template <typename T>
void test_rvd_getfirst()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::rvd<T> r = mipp::set<T>(inputs);
	REQUIRE(mipp::getfirst(r) == inputs[0]);
}

#ifndef MIPP_NO
TEST_CASE("Getfirst - mipp::rvd<T>", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_getfirst<int8_t>(); }
#endif
}
#endif

//same test as set
template <typename T>
void test_Rvd_getfirst()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + vectorSize, (T)0);

	mipp::Rvd<T> r = inputs;
	REQUIRE(r[0] == inputs[0]);
    REQUIRE(mipp::getfirst(r.r) == inputs[0]);

}

TEST_CASE("Getfirst - mipp::Rvd", "[mipp::getfirst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_getfirst<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_getfirst<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_getfirst<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_getfirst<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_getfirst<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_getfirst<int8_t>(); }
#endif
}
