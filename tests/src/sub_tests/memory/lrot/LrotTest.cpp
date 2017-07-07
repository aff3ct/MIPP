#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "LrotTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(LrotTest);

void 
LrotTest::setUp()
{
}

void 
LrotTest::tearDown()
{
}

template <typename T>
void LrotTest::test_reg_lrot()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, 0);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::lrot<T>(r1);

		for (auto i = 0; i < N; i++)
			CPPUNIT_ASSERT_EQUAL(i == N-1 ? inputs1[0] : inputs1[i+1], *((T*)&r2 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LrotTest::test_reg_lrot_int8  () { test_reg_lrot<int8_t >(); }
void LrotTest::test_reg_lrot_int16 () { test_reg_lrot<int16_t>(); }
void LrotTest::test_reg_lrot_int32 () { test_reg_lrot<int32_t>(); }
void LrotTest::test_reg_lrot_int64 () { test_reg_lrot<int64_t>(); }
void LrotTest::test_reg_lrot_float () { test_reg_lrot<float  >(); }
void LrotTest::test_reg_lrot_double() { test_reg_lrot<double >(); }

template <typename T>
void LrotTest::test_Reg_lrot()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, 0);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::lrot(r1);

		for (auto i = 0; i < N; i++)
			CPPUNIT_ASSERT_EQUAL(i == N-1 ? inputs1[0] : inputs1[i+1], r2[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LrotTest::test_Reg_lrot_int8  () { test_Reg_lrot<int8_t >(); }
void LrotTest::test_Reg_lrot_int16 () { test_Reg_lrot<int16_t>(); }
void LrotTest::test_Reg_lrot_int32 () { test_Reg_lrot<int32_t>(); }
void LrotTest::test_Reg_lrot_int64 () { test_Reg_lrot<int64_t>(); }
void LrotTest::test_Reg_lrot_float () { test_Reg_lrot<float  >(); }
void LrotTest::test_Reg_lrot_double() { test_Reg_lrot<double >(); }
