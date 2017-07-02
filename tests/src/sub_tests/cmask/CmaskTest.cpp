#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "CmaskTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmaskTest);

void 
CmaskTest::setUp()
{
}

void 
CmaskTest::tearDown()
{
}

template <typename T>
void CmaskTest::test_reg_cmask()
{
	try
	{
		uint32_t inputs[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs, inputs + mipp::N<T>(), 0);
		std::shuffle(inputs, inputs + mipp::N<T>(), g);

		mipp::reg r = mipp::cmask<T>(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) +j), *((uint8_t*)&r + (i * sizeof(T)) +j));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmaskTest::test_reg_cmask_int8  () { test_reg_cmask<int8_t >(); }
void CmaskTest::test_reg_cmask_int16 () { test_reg_cmask<int16_t>(); }
void CmaskTest::test_reg_cmask_int32 () { test_reg_cmask<int32_t>(); }
void CmaskTest::test_reg_cmask_int64 () { test_reg_cmask<int64_t>(); }
void CmaskTest::test_reg_cmask_float () { test_reg_cmask<float  >(); }
void CmaskTest::test_reg_cmask_double() { test_reg_cmask<double >(); }

template <typename T>
void CmaskTest::test_Reg_cmask()
{
	try
	{
		uint32_t inputs[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs, inputs + mipp::N<T>(), 0);
		std::shuffle(inputs, inputs + mipp::N<T>(), g);

		mipp::Reg<T> r = mipp::Reg<T>::cmask(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) +j), *((uint8_t*)&r + (i * sizeof(T)) +j));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmaskTest::test_Reg_cmask_int8  () { test_Reg_cmask<int8_t >(); }
void CmaskTest::test_Reg_cmask_int16 () { test_Reg_cmask<int16_t>(); }
void CmaskTest::test_Reg_cmask_int32 () { test_Reg_cmask<int32_t>(); }
void CmaskTest::test_Reg_cmask_int64 () { test_Reg_cmask<int64_t>(); }
void CmaskTest::test_Reg_cmask_float () { test_Reg_cmask<float  >(); }
void CmaskTest::test_Reg_cmask_double() { test_Reg_cmask<double >(); }
