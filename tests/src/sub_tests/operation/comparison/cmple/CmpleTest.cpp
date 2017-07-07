#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "CmpleTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmpleTest);

void 
CmpleTest::setUp()
{
}

void 
CmpleTest::tearDown()
{
}

template <typename T>
void CmpleTest::test_reg_cmple()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		for (auto t = 0; t < 100; t++)
		{
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);
			mipp::msk m  = mipp::cmple<T>(r1, r2);

			mipp::reg r3 = mipp::cvt_msk_reg<mipp::N<T>()>(m);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (inputs1[i] <= inputs2[i])
					CPPUNIT_ASSERT(*((T*)&r3 +i) != (T)0);
				else
					CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r3 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpleTest::test_reg_cmple_int8  () { test_reg_cmple<int8_t >(); }
void CmpleTest::test_reg_cmple_int16 () { test_reg_cmple<int16_t>(); }
void CmpleTest::test_reg_cmple_int32 () { test_reg_cmple<int32_t>(); }
void CmpleTest::test_reg_cmple_int64 () { test_reg_cmple<int64_t>(); }
void CmpleTest::test_reg_cmple_float () { test_reg_cmple<float  >(); }
void CmpleTest::test_reg_cmple_double() { test_reg_cmple<double >(); }

template <typename T>
void CmpleTest::test_Reg_cmple()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		for (auto t = 0; t < 100; t++)
		{
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;
			mipp::Msk<mipp::N<T>()> m = r1 <= r2;

			mipp::reg r3 = mipp::cvt_msk_reg<mipp::N<T>()>(m.m);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (inputs1[i] <= inputs2[i])
					CPPUNIT_ASSERT(*((T*)&r3 +i) != (T)0);
				else
					CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r3 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpleTest::test_Reg_cmple_int8  () { test_Reg_cmple<int8_t >(); }
void CmpleTest::test_Reg_cmple_int16 () { test_Reg_cmple<int16_t>(); }
void CmpleTest::test_Reg_cmple_int32 () { test_Reg_cmple<int32_t>(); }
void CmpleTest::test_Reg_cmple_int64 () { test_Reg_cmple<int64_t>(); }
void CmpleTest::test_Reg_cmple_float () { test_Reg_cmple<float  >(); }
void CmpleTest::test_Reg_cmple_double() { test_Reg_cmple<double >(); }
