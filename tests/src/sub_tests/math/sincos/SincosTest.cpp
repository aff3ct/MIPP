#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>

#include "SincosTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(SinsincosTest);

void 
SinsincosTest::setUp()
{
}

void 
SinsincosTest::tearDown()
{
}

template <typename T>
void SinsincosTest::test_reg_sincos()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2, r3;
		mipp::sincos<T>(r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res1 = std::sin(inputs1[i]);
			T res2 = std::cos(inputs1[i]);

			T diff = std::abs(res1 - *((T*)&r2 +i));
			CPPUNIT_ASSERT(diff < 0.001);

			diff = std::abs(res2 - *((T*)&r3 +i));
			CPPUNIT_ASSERT(diff < 0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SinsincosTest::test_reg_sincos_float () { test_reg_sincos<float >(); }
void SinsincosTest::test_reg_sincos_double() { test_reg_sincos<double>(); }

template <typename T>
void SinsincosTest::test_Reg_sincos()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2, r3;
		mipp::sincos(r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res1 = std::sin(inputs1[i]);
			T res2 = std::cos(inputs1[i]);

			T diff = std::abs(res1 - r2[i]);
			CPPUNIT_ASSERT(diff < 0.001);

			diff = std::abs(res2 - r3[i]);
			CPPUNIT_ASSERT(diff < 0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SinsincosTest::test_Reg_sincos_float () { test_Reg_sincos<float >(); }
void SinsincosTest::test_Reg_sincos_double() { test_Reg_sincos<double>(); }
