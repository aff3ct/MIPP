#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch2/catch_test_macros.hpp>


template <typename T>
void test_msk_testz_2()
{

	mipp::rvm<T> r1 = mipp::set1_k<T>((int32_t)1);
	mipp::rvm<T> r2 = mipp::set1_k<T>((int32_t)0);
	
	REQUIRE(mipp::testz_2(r1) == (T)0);
	REQUIRE(mipp::testz_2(r2) != (T)0);	
}

#ifndef MIPP_NO
TEST_CASE("Binary testz_2 - mipp::rvm", "[mipp::testz_2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_testz_2<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_msk_testz_2<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_msk_testz_2<int32_t>(); }
	//SECTION("datatype = uint32_t") { test_msk_testz_2<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_testz_2<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_testz_2<int8_t>(); }
	//SECTION("datatype = uint16_t") { test_msk_testz_2<uint16_t>(); }
	//SECTION("datatype = uint8_t") { test_msk_testz_2<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_testz_2()
{

	mipp::Rvm<T> r1 = mipp::set1_k<T>((int32_t)1);
	mipp::Rvm<T> r2 = mipp::set1_k<T>((int32_t)0);
	
	REQUIRE(mipp::testz_2(r1.m) == (T)0);
	REQUIRE(mipp::testz_2(r2.m) != (T)0);	
}

#ifndef MIPP_NO
TEST_CASE("Binary testz_2 - mipp::Rvm", "[mipp::testz_2]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_testz_2<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_Msk_testz_2<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_Msk_testz_2<int32_t>(); }
	//SECTION("datatype = uint32_t") { test_Msk_testz_2<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_testz_2<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_testz_2<int8_t>(); }
	//SECTION("datatype = uint16_t") { test_Msk_testz_2<uint16_t>(); }
	//SECTION("datatype = uint8_t") { test_Msk_testz_2<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_msk_testz()
{

	mipp::rvm<T> r1 = mipp::set1_k<T>((int32_t)1);
	mipp::rvm<T> r2 = mipp::set1_k<T>((int32_t)0);
	
	REQUIRE(mipp::testz(r1,r2) == (T)0);
	REQUIRE(mipp::testz(r2,r2) != (T)0);	
}

#ifndef MIPP_NO
TEST_CASE("Binary testz - mipp::rvm", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_msk_testz<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_msk_testz<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_msk_testz<int32_t>(); }
	//SECTION("datatype = uint32_t") { test_msk_testz<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_msk_testz<int16_t>(); }
	SECTION("datatype = int8_t") { test_msk_testz<int8_t>(); }
	//SECTION("datatype = uint16_t") { test_msk_testz<uint16_t>(); }
	//SECTION("datatype = uint8_t") { test_msk_testz<uint8_t>(); }
#endif
}
#endif

template <typename T>
void test_Msk_testz()
{

	mipp::Rvm<T> r1 = mipp::set1_k<T>((int32_t)1);
	mipp::Rvm<T> r2 = mipp::set1_k<T>((int32_t)0);
	
	REQUIRE(mipp::testz(r1.m, r2.m) == (T)0);
	REQUIRE(mipp::testz(r2.m, r2.m) != (T)0);	
}

#ifndef MIPP_NO
TEST_CASE("Binary testz - mipp::Rvm", "[mipp::testz]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Msk_testz<int64_t>(); }
	//SECTION("datatype = uint64_t") { test_Msk_testz<uint64_t>(); }

#endif
	SECTION("datatype = int32_t") { test_Msk_testz<int32_t>(); }
	//SECTION("datatype = uint32_t") { test_Msk_testz<uint32_t>(); }

#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Msk_testz<int16_t>(); }
	SECTION("datatype = int8_t") { test_Msk_testz<int8_t>(); }
	//SECTION("datatype = uint16_t") { test_Msk_testz<uint16_t>(); }
	//SECTION("datatype = uint8_t") { test_Msk_testz<uint8_t>(); }
#endif
}
#endif
