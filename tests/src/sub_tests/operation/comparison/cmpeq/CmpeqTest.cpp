#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "CmpeqTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CmpeqTest);

void 
CmpeqTest::setUp()
{
}

void 
CmpeqTest::tearDown()
{
}

template <typename T>
void CmpeqTest::test_reg_cmpeq()
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
			mipp::msk m  = mipp::cmpeq<T>(r1, r2);

			mipp::reg r3 = mipp::toreg<mipp::N<T>()>(m);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (inputs1[i] == inputs2[i])
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

void CmpeqTest::test_reg_cmpeq_int8  () { test_reg_cmpeq<int8_t >(); }
void CmpeqTest::test_reg_cmpeq_int16 () { test_reg_cmpeq<int16_t>(); }
void CmpeqTest::test_reg_cmpeq_int32 () { test_reg_cmpeq<int32_t>(); }
void CmpeqTest::test_reg_cmpeq_int64 () { test_reg_cmpeq<int64_t>(); }
void CmpeqTest::test_reg_cmpeq_float () { test_reg_cmpeq<float  >(); }
void CmpeqTest::test_reg_cmpeq_double() { test_reg_cmpeq<double >(); }

template <typename T>
void CmpeqTest::test_Reg_cmpeq()
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
			mipp::Msk<mipp::N<T>()> m = r1 == r2;

			for (auto i = 0; i < mipp::N<T>(); i++)
				CPPUNIT_ASSERT_EQUAL(inputs1[i] == inputs2[i], m[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void CmpeqTest::test_Reg_cmpeq_int8  () { test_Reg_cmpeq<int8_t >(); }
void CmpeqTest::test_Reg_cmpeq_int16 () { test_Reg_cmpeq<int16_t>(); }
void CmpeqTest::test_Reg_cmpeq_int32 () { test_Reg_cmpeq<int32_t>(); }
void CmpeqTest::test_Reg_cmpeq_int64 () { test_Reg_cmpeq<int64_t>(); }
void CmpeqTest::test_Reg_cmpeq_float () { test_Reg_cmpeq<float  >(); }
void CmpeqTest::test_Reg_cmpeq_double() { test_Reg_cmpeq<double >(); }
