#include <exception>
#include <algorithm>
#include <mipp.h>

#include "CmpltTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmpltTest);

void 
CmpltTest::setUp()
{
}

void 
CmpltTest::tearDown()
{
}

template <typename T>
void CmpltTest::test_reg_cmplt()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::msk m  = mipp::cmplt<T>(r1, r2);

		mipp::reg r3 = mipp::cvt_msk_reg<mipp::N<T>()>(m);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (inputs1[i] < inputs2[i])
				CPPUNIT_ASSERT(*((T*)&r3 +i) != (T)0);
			else
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpltTest::test_reg_cmplt_int8  () { test_reg_cmplt<int8_t >(); }
void CmpltTest::test_reg_cmplt_int16 () { test_reg_cmplt<int16_t>(); }
void CmpltTest::test_reg_cmplt_int32 () { test_reg_cmplt<int32_t>(); }
void CmpltTest::test_reg_cmplt_int64 () { test_reg_cmplt<int64_t>(); }
void CmpltTest::test_reg_cmplt_float () { test_reg_cmplt<float  >(); }
void CmpltTest::test_reg_cmplt_double() { test_reg_cmplt<double >(); }

template <typename T>
void CmpltTest::test_Reg_cmplt()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Msk<mipp::N<T>()> m = r1 < r2;

		mipp::reg r3 = mipp::cvt_msk_reg<mipp::N<T>()>(m.m);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (inputs1[i] < inputs2[i])
				CPPUNIT_ASSERT(*((T*)&r3 +i) != (T)0);
			else
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpltTest::test_Reg_cmplt_int8  () { test_Reg_cmplt<int8_t >(); }
void CmpltTest::test_Reg_cmplt_int16 () { test_Reg_cmplt<int16_t>(); }
void CmpltTest::test_Reg_cmplt_int32 () { test_Reg_cmplt<int32_t>(); }
void CmpltTest::test_Reg_cmplt_int64 () { test_Reg_cmplt<int64_t>(); }
void CmpltTest::test_Reg_cmplt_float () { test_Reg_cmplt<float  >(); }
void CmpltTest::test_Reg_cmplt_double() { test_Reg_cmplt<double >(); }
