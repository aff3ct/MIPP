#include <exception>
#include <algorithm>
#include <numeric>
#include <mipp.h>

#include "LowTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(LowTest);

void 
LowTest::setUp()
{
}

void 
LowTest::tearDown()
{
}

template <typename T>
void LowTest::test_reg_low()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg   r   = mipp::load<T>(inputs);
		mipp::reg_2 r_2 = mipp::low <T>(r);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], *((T*)&r_2 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LowTest::test_reg_low_int8  () { test_reg_low<int8_t >(); }
void LowTest::test_reg_low_int16 () { test_reg_low<int16_t>(); }
void LowTest::test_reg_low_int32 () { test_reg_low<int32_t>(); }
void LowTest::test_reg_low_int64 () { test_reg_low<int64_t>(); }
void LowTest::test_reg_low_float () { test_reg_low<float  >(); }
void LowTest::test_reg_low_double() { test_reg_low<double >(); }

template <typename T>
void LowTest::test_Reg_low()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg  <T> r   = inputs;
		mipp::Reg_2<T> r_2 = r.low();

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], r_2[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LowTest::test_Reg_low_int8  () { test_Reg_low<int8_t >(); }
void LowTest::test_Reg_low_int16 () { test_Reg_low<int16_t>(); }
void LowTest::test_Reg_low_int32 () { test_Reg_low<int32_t>(); }
void LowTest::test_Reg_low_int64 () { test_Reg_low<int64_t>(); }
void LowTest::test_Reg_low_float () { test_Reg_low<float  >(); }
void LowTest::test_Reg_low_double() { test_Reg_low<double >(); }
