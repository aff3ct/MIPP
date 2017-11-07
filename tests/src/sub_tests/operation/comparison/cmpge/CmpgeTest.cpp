#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "CmpgeTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmpgeTest);

void 
CmpgeTest::setUp()
{
}

void 
CmpgeTest::tearDown()
{
}

template <typename T>
void CmpgeTest::test_reg_cmpge()
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
			mipp::msk m  = mipp::cmpge<T>(r1, r2);

			mipp::reg r3 = mipp::toreg<mipp::N<T>()>(m);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (inputs1[i] >= inputs2[i])
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

void CmpgeTest::test_reg_cmpge_int8  () { test_reg_cmpge<int8_t >(); }
void CmpgeTest::test_reg_cmpge_int16 () { test_reg_cmpge<int16_t>(); }
void CmpgeTest::test_reg_cmpge_int32 () { test_reg_cmpge<int32_t>(); }
void CmpgeTest::test_reg_cmpge_int64 () { test_reg_cmpge<int64_t>(); }
void CmpgeTest::test_reg_cmpge_float () { test_reg_cmpge<float  >(); }
void CmpgeTest::test_reg_cmpge_double() { test_reg_cmpge<double >(); }

template <typename T>
void CmpgeTest::test_Reg_cmpge()
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
			mipp::Msk<mipp::N<T>()> m = r1 >= r2;

			for (auto i = 0; i < mipp::N<T>(); i++)
				CPPUNIT_ASSERT_EQUAL(inputs1[i] >= inputs2[i], m[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpgeTest::test_Reg_cmpge_int8  () { test_Reg_cmpge<int8_t >(); }
void CmpgeTest::test_Reg_cmpge_int16 () { test_Reg_cmpge<int16_t>(); }
void CmpgeTest::test_Reg_cmpge_int32 () { test_Reg_cmpge<int32_t>(); }
void CmpgeTest::test_Reg_cmpge_int64 () { test_Reg_cmpge<int64_t>(); }
void CmpgeTest::test_Reg_cmpge_float () { test_Reg_cmpge<float  >(); }
void CmpgeTest::test_Reg_cmpge_double() { test_Reg_cmpge<double >(); }
