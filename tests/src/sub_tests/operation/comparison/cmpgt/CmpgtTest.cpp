#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "CmpgtTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmpgtTest);

void 
CmpgtTest::setUp()
{
}

void 
CmpgtTest::tearDown()
{
}

template <typename T>
void CmpgtTest::test_reg_cmpgt()
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
			mipp::msk m  = mipp::cmpgt<T>(r1, r2);

			mipp::reg r3 = mipp::cvt_reg<mipp::N<T>()>(m);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (inputs1[i] > inputs2[i])
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

void CmpgtTest::test_reg_cmpgt_int8  () { test_reg_cmpgt<int8_t >(); }
void CmpgtTest::test_reg_cmpgt_int16 () { test_reg_cmpgt<int16_t>(); }
void CmpgtTest::test_reg_cmpgt_int32 () { test_reg_cmpgt<int32_t>(); }
void CmpgtTest::test_reg_cmpgt_int64 () { test_reg_cmpgt<int64_t>(); }
void CmpgtTest::test_reg_cmpgt_float () { test_reg_cmpgt<float  >(); }
void CmpgtTest::test_reg_cmpgt_double() { test_reg_cmpgt<double >(); }

template <typename T>
void CmpgtTest::test_Reg_cmpgt()
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
			mipp::Msk<mipp::N<T>()> m = r1 > r2;

			for (auto i = 0; i < mipp::N<T>(); i++)
				CPPUNIT_ASSERT_EQUAL(inputs1[i] > inputs2[i], m[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpgtTest::test_Reg_cmpgt_int8  () { test_Reg_cmpgt<int8_t >(); }
void CmpgtTest::test_Reg_cmpgt_int16 () { test_Reg_cmpgt<int16_t>(); }
void CmpgtTest::test_Reg_cmpgt_int32 () { test_Reg_cmpgt<int32_t>(); }
void CmpgtTest::test_Reg_cmpgt_int64 () { test_Reg_cmpgt<int64_t>(); }
void CmpgtTest::test_Reg_cmpgt_float () { test_Reg_cmpgt<float  >(); }
void CmpgtTest::test_Reg_cmpgt_double() { test_Reg_cmpgt<double >(); }
