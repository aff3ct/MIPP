#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_rvd_round()
{   
	/*const int vectorSize = mipp::N<T>();
	T inputs[vectorSize];
	std::iota(inputs, inputs + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs, inputs + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs);
	mipp::rvd<T> r2 = mipp::round(r1);



	for (auto i = 0; i < vectorSize; i++)
	{
		T res = round(inputs[i]);
		REQUIRE(mipp::get(r2, i) == res);
	}*/
}

//no u32/u64 on avx2
#ifndef MIPP_NO
TEST_CASE("Rounding - mipp::rvd", "[mipp::round]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_round<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_round<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_round<int64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_rvd_round<int32_t>(); }
#endif

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_round<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_round<int8_t>(); }
	SECTION("datatype = uint16_t") { test_rvd_round<uint16_t>(); }
	SECTION("datatype = uint8_t") { test_rvd_round<uint8_t>(); }
#endif

#if defined(MIPP_RVV)
	SECTION("datatype = uint64_t") { test_rvd_round<uint64_t>(); }
	SECTION("datatype = uint32_t") { test_rvd_round<uint32_t>(); }

#endif
}
#endif