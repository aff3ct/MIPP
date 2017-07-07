#include <exception>
#include <algorithm>
#include <numeric>
#include <mipp.h>

#include "CvtTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CvtTest);

void 
CvtTest::setUp()
{
}

void 
CvtTest::tearDown()
{
}

template <typename T1, typename T2>
void CvtTest::test_reg_cvt()
{
	try
	{
		constexpr int N1 = mipp::N<T1>();
		constexpr int N2 = mipp::N<T2>();

		T1 inputs1[N1];
		std::iota(inputs1, inputs1 + N1, -N1/2);

		for (auto i = 0; i < N1; i++)
			inputs1[i] += i % 2 ? (T1)0.4 : (T1)0.6;

		mipp::reg r1 = mipp::load<T1>(inputs1);
		mipp::reg r2 = N1 != N2 ? mipp::cvt<T1,T2>(mipp::low<T1>(r1)) : mipp::cvt<T1,T2>(r1);

		for (auto i = 0; i < N2; i++)
		{
			auto res = static_cast<T2>(std::round(inputs1[i]));
			CPPUNIT_ASSERT_EQUAL(res, *((T2*)&r2 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CvtTest::test_reg_cvt_int8_int16  () { test_reg_cvt<int8_t ,int16_t>(); };
void CvtTest::test_reg_cvt_int16_int32 () { test_reg_cvt<int16_t,int32_t>(); };
void CvtTest::test_reg_cvt_int32_int64 () { test_reg_cvt<int32_t,int64_t>(); };
void CvtTest::test_reg_cvt_int32_float () { test_reg_cvt<int32_t,float  >(); };
void CvtTest::test_reg_cvt_float_int32 () { test_reg_cvt<float  ,int32_t>(); };
void CvtTest::test_reg_cvt_int64_double() { test_reg_cvt<int64_t,double >(); };
void CvtTest::test_reg_cvt_double_int64() { test_reg_cvt<double ,int64_t>(); };

template <typename T1, typename T2>
void CvtTest::test_Reg_cvt()
{
	try
	{
		constexpr int N1 = mipp::N<T1>();
		constexpr int N2 = mipp::N<T2>();

		T1 inputs1[N1];
		std::iota(inputs1, inputs1 + N1, -N1/2);

		for (auto i = 0; i < N1; i++)
			inputs1[i] += i % 2 ? (T1)0.4 : (T1)0.6;

		mipp::Reg<T1> r1 = inputs1;
		mipp::Reg<T2> r2 = N1 != N2 ? mipp::cvt<T1,T2>(r1.low()) : mipp::cvt<T1,T2>(r1);

		for (auto i = 0; i < N2; i++)
		{
			auto res = static_cast<T2>(std::round(inputs1[i]));
			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CvtTest::test_Reg_cvt_int8_int16  () { test_Reg_cvt<int8_t ,int16_t>(); };
void CvtTest::test_Reg_cvt_int16_int32 () { test_Reg_cvt<int16_t,int32_t>(); };
void CvtTest::test_Reg_cvt_int32_int64 () { test_Reg_cvt<int32_t,int64_t>(); };
void CvtTest::test_Reg_cvt_int32_float () { test_Reg_cvt<int32_t,float  >(); };
void CvtTest::test_Reg_cvt_float_int32 () { test_Reg_cvt<float  ,int32_t>(); };
void CvtTest::test_Reg_cvt_int64_double() { test_Reg_cvt<int64_t,double >(); };
void CvtTest::test_Reg_cvt_double_int64() { test_Reg_cvt<double ,int64_t>(); };
