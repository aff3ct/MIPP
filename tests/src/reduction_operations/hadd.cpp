#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch_amalgamated.hpp>



template <typename T>
void test_rvd_hadd()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	mipp::rvd<T> r2 = mipp::hadd (r1);

    T res = 0;

	for (auto i = 0; i < vectorSize; i++)
	{
		res += inputs1[i];
	}
    REQUIRE(mipp::get(r2, 0) == res);

}

#ifndef MIPP_NO
TEST_CASE("Reduction sum - mipp::rvd", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_hadd<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_hadd<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_hadd<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_hadd<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_hadd<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_hadd<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_hadd()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::Rvd<T> r1; 
    r1.r = mipp::load(inputs1);
	
    mipp::Rvd<T> r2;
    r2.r = mipp::hadd(r1.r);
    //r1.load(inputs1);
    //r2 = r1.hadd();
    
    T res = 0;
	for (auto i = 0; i < vectorSize; i++)
	{
		res += inputs1[i];
	}
    REQUIRE(r2[0] == res);
}

TEST_CASE("Reduction sum - mipp::Rvd", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_hadd<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_hadd<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_hadd<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_hadd<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_hadd<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_hadd<int8_t>(); }
#endif
}

template <typename T>
void test_rvd_hadd_to_scal()
{   
	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::rvd<T> r1 = mipp::load(inputs1);
	T s0 = mipp::hadd_to_scal(r1);

    T res = 0;

	for (auto i = 0; i < vectorSize; i++)
	{
		res += inputs1[i];
	}
    REQUIRE( s0 == res);

}

#ifndef MIPP_NO
TEST_CASE("Reduction sum to scal - mipp::rvd", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_hadd_to_scal<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_hadd_to_scal<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_hadd_to_scal<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_hadd_to_scal<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_hadd_to_scal<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_hadd_to_scal<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_hadd_to_scal()
{

	const int vectorSize = mipp::N<T>();
	T inputs1[vectorSize];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + vectorSize, g);

	mipp::Rvd<T> r1; 
    r1.r = mipp::load(inputs1);
	
    T s0 = mipp::hadd_to_scal(r1.r);
    //r1.load(inputs1);
    //r2 = r1.hadd();
    
    T res = 0;
	for (auto i = 0; i < vectorSize; i++)
	{
		res += inputs1[i];
	}
    REQUIRE(s0 == res);
}

TEST_CASE("Reduction sum to scal - mipp::Rvd", "[mipp::hadd]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_hadd_to_scal<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_hadd_to_scal<float>(); }

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_hadd_to_scal<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_hadd_to_scal<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_hadd_to_scal<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_hadd_to_scal<int8_t>(); }
#endif
}