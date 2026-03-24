#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


#include <iostream>

template <typename T>
void test_reg_cast_k()
{
	const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
    void * ptr = inputs;
	std::iota(inputs, inputs + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs, inputs + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs);
    mipp::rvm<T> m1 = mipp::tomsk(r1);

    mipp::rvm<int32_t> m2 = mipp::cast_int32(m1);
	
    for (auto i = 0; i < mipp::N<int32_t>(); i++){
		
        if((i%2) == 0 && sizeof(int32_t) != sizeof(T)){
            REQUIRE(mipp::get(m2, i) == 0);
        }else{
            REQUIRE( (!(!(mipp::get(m2, i)))) == (!(!(((int32_t*)ptr)[i]))) );
        }
    }
}

#ifndef MIPP_NO
TEST_CASE("Cast_k - mipp::rvm<T>", "[mipp::cast_k]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_cast_k<double>(); }
#endif
	SECTION("datatype = float") { test_reg_cast_k<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_cast_k<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_cast_k<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_cast_k<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_cast_k<int8_t>(); }
#endif
}
#endif