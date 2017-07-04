#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "RrotTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(RrotTest);

void 
RrotTest::setUp()
{
}

void 
RrotTest::tearDown()
{
}

template <typename T>
void RrotTest::test_reg_rrot()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, 0);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::rrot<T>(r1);

		for (auto i = 0; i < N; i++)
			CPPUNIT_ASSERT_EQUAL(i == 0 ? inputs1[N-1] : inputs1[i-1], *((T*)&r2 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RrotTest::test_reg_rrot_int8  () { test_reg_rrot<int8_t >(); }
void RrotTest::test_reg_rrot_int16 () { test_reg_rrot<int16_t>(); }
void RrotTest::test_reg_rrot_int32 () { test_reg_rrot<int32_t>(); }
void RrotTest::test_reg_rrot_int64 () { test_reg_rrot<int64_t>(); }
void RrotTest::test_reg_rrot_float () { test_reg_rrot<float  >(); }
void RrotTest::test_reg_rrot_double() { test_reg_rrot<double >(); }

template <typename T>
void RrotTest::test_Reg_rrot()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, 0);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::rrot(r1);

		for (auto i = 0; i < N; i++)
			CPPUNIT_ASSERT_EQUAL(i == 0 ? inputs1[N-1] : inputs1[i-1], r2[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RrotTest::test_Reg_rrot_int8  () { test_Reg_rrot<int8_t >(); }
void RrotTest::test_Reg_rrot_int16 () { test_Reg_rrot<int16_t>(); }
void RrotTest::test_Reg_rrot_int32 () { test_Reg_rrot<int32_t>(); }
void RrotTest::test_Reg_rrot_int64 () { test_Reg_rrot<int64_t>(); }
void RrotTest::test_Reg_rrot_float () { test_Reg_rrot<float  >(); }
void RrotTest::test_Reg_rrot_double() { test_Reg_rrot<double >(); }
