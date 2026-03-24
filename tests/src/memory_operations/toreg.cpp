#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>


//same as set test...
template <typename T>
void test_msk_toreg()
{
	const int vectorSize = mipp::N<T>();
	int32_t inputs[vectorSize];
	for (auto i = 0; i < vectorSize; i++)
		inputs[i] = i % 2 ? 1 : 0;

	mipp::rvm<T> m = mipp::set_k<T>(inputs);
	mipp::rvd<T> r = mipp::toreg(m);


	for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(mipp::get(r, i) == (T)0);
		else
			REQUIRE(mipp::get(r, i) != (T)0);
	
}

#ifndef MIPP_NO
TEST_CASE("Toreg - mipp::rvm<T>", "[mipp::toreg]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_msk_toreg<double>(); }
#endif
	SECTION("datatype = float") { test_msk_toreg<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_toreg<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_msk_toreg<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_toreg<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_toreg<int8_t>(); }
#endif
}
#endif

//same test as set
template <typename T>
void test_Msk_toreg()
{
		const int vectorSize = mipp::N<T>();
		int32_t inputs[vectorSize];

		for (auto i = 0; i < vectorSize; i++)
			inputs[i] = i % 2 ? -1 : 0;

		mipp::Rvm<T> m = inputs;
		//conversion from Rvm to Rvd not implemented :(
		//mipp::Rvd<T> r = m;
		mipp::Rvd<T> r;
		r.r = mipp::toreg(m.m);

			for (auto i = 0; i < vectorSize; i++)
		if (!inputs[i])
			REQUIRE(r[i] == (T)0);
		else
			REQUIRE( r[i] != (T)0);
}

TEST_CASE("Toreg - mipp::Rvm", "[mipp::toreg]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Msk_toreg<double>(); }
#endif
	SECTION("datatype = float") { test_Msk_toreg<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_toreg<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Msk_toreg<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_toreg<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_toreg<int8_t>(); }
#endif
}
