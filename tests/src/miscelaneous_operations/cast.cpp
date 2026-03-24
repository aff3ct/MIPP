#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


#include <iostream>

template <typename T>
void test_reg_cast()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
    void * ptr = inputs;
	std::iota(inputs, inputs + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs, inputs + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs);

    mipp::rvd<int32_t> r2 = mipp::cast_int32(r1);


	for (auto i = 0; i < mipp::N<int32_t>(); i++){
		REQUIRE(mipp::get(r2, i) == ((int32_t*)ptr)[i]);
    }
	
}

#ifndef MIPP_NO
TEST_CASE("Cast - mipp::rvd<T>", "[mipp::cast]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_cast<double>(); }
#endif
	SECTION("datatype = float") { test_reg_cast<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_cast<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_cast<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_cast<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_cast<int8_t>(); }
#endif
}
#endif