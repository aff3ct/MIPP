#include <exception>
#include <mipp.h>

#include "HighTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(HighTest);

void 
HighTest::setUp()
{
}

void 
HighTest::tearDown()
{
}

template <typename T>
void HighTest::test_reg_high()
{
	try
	{
		T inputs[mipp::N<T>()];
		for (auto i = 0; i < mipp::N<T>(); i++)
			inputs[i] = (T)i;

		mipp::reg   r   = mipp::load<T>(inputs);
		mipp::reg_2 r_2 = mipp::high <T>(r);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			CPPUNIT_ASSERT_EQUAL(inputs[mipp::N<T>()/2 +i], *((T*)&r_2 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HighTest::test_reg_high_int8  () { test_reg_high<int8_t >(); }
void HighTest::test_reg_high_int16 () { test_reg_high<int16_t>(); }
void HighTest::test_reg_high_int32 () { test_reg_high<int32_t>(); }
void HighTest::test_reg_high_int64 () { test_reg_high<int64_t>(); }
void HighTest::test_reg_high_float () { test_reg_high<float  >(); }
void HighTest::test_reg_high_double() { test_reg_high<double >(); }

template <typename T>
void HighTest::test_Reg_high()
{
	try
	{
		T inputs[mipp::N<T>()];
		for (auto i = 0; i < mipp::N<T>(); i++)
			inputs[i] = (T)i;

		mipp::Reg  <T> r   = inputs;
		mipp::Reg_2<T> r_2 = r.high();

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			CPPUNIT_ASSERT_EQUAL(inputs[mipp::N<T>()/2 +i], *((T*)&r_2.r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HighTest::test_Reg_high_int8  () { test_Reg_high<int8_t >(); }
void HighTest::test_Reg_high_int16 () { test_Reg_high<int16_t>(); }
void HighTest::test_Reg_high_int32 () { test_Reg_high<int32_t>(); }
void HighTest::test_Reg_high_int64 () { test_Reg_high<int64_t>(); }
void HighTest::test_Reg_high_float () { test_Reg_high<float  >(); }
void HighTest::test_Reg_high_double() { test_Reg_high<double >(); }
