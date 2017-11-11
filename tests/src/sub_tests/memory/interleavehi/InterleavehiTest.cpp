#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "InterleavehiTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(InterleavehiTest);

void 
InterleavehiTest::setUp()
{
}

void 
InterleavehiTest::tearDown()
{
}

template <typename T>
void InterleavehiTest::test_reg_interleavehi()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);

		mipp::reg ri = mipp::interleavehi<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], *((T*)&ri +i));
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], *((T*)&ri +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleavehiTest::test_reg_interleavehi_int8  () { test_reg_interleavehi<int8_t >(); }
void InterleavehiTest::test_reg_interleavehi_int16 () { test_reg_interleavehi<int16_t>(); }
void InterleavehiTest::test_reg_interleavehi_int32 () { test_reg_interleavehi<int32_t>(); }
void InterleavehiTest::test_reg_interleavehi_int64 () { test_reg_interleavehi<int64_t>(); }
void InterleavehiTest::test_reg_interleavehi_float () { test_reg_interleavehi<float  >(); }
void InterleavehiTest::test_reg_interleavehi_double() { test_reg_interleavehi<double >(); }

template <typename T>
void InterleavehiTest::test_Reg_interleavehi()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;

		mipp::Reg<T> ri = mipp::interleavehi(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], ri[i]);
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], ri[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleavehiTest::test_Reg_interleavehi_int8  () { test_Reg_interleavehi<int8_t >(); }
void InterleavehiTest::test_Reg_interleavehi_int16 () { test_Reg_interleavehi<int16_t>(); }
void InterleavehiTest::test_Reg_interleavehi_int32 () { test_Reg_interleavehi<int32_t>(); }
void InterleavehiTest::test_Reg_interleavehi_int64 () { test_Reg_interleavehi<int64_t>(); }
void InterleavehiTest::test_Reg_interleavehi_float () { test_Reg_interleavehi<float  >(); }
void InterleavehiTest::test_Reg_interleavehi_double() { test_Reg_interleavehi<double >(); }

template <typename T>
void InterleavehiTest::test_reg_interleavehi2()
{
	if (mipp::N<T>() > 2)
	{
		try
		{
			T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
			std::mt19937 g;
			std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);

			mipp::reg ri = mipp::interleavehi2<T>(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/4 + i/2], *((T*)&ri +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/4 + i/2], *((T*)&ri +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], *((T*)&ri + mipp::N<T>()/2 +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], *((T*)&ri + mipp::N<T>()/2 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleavehiTest::test_reg_interleavehi2_int8  () { test_reg_interleavehi2<int8_t >(); }
void InterleavehiTest::test_reg_interleavehi2_int16 () { test_reg_interleavehi2<int16_t>(); }
void InterleavehiTest::test_reg_interleavehi2_int32 () { test_reg_interleavehi2<int32_t>(); }
void InterleavehiTest::test_reg_interleavehi2_int64 () { test_reg_interleavehi2<int64_t>(); }
void InterleavehiTest::test_reg_interleavehi2_float () { test_reg_interleavehi2<float  >(); }
void InterleavehiTest::test_reg_interleavehi2_double() { test_reg_interleavehi2<double >(); }

template <typename T>
void InterleavehiTest::test_Reg_interleavehi2()
{
	if (mipp::N<T>() > 2)
	{
		try
		{
			T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
			std::mt19937 g;
			std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;

			mipp::Reg<T> ri = mipp::interleavehi2(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/4 + i/2], *((T*)&ri +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/4 + i/2], *((T*)&ri +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], ri[mipp::N<T>()/2 +i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], ri[mipp::N<T>()/2 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleavehiTest::test_Reg_interleavehi2_int8  () { test_Reg_interleavehi2<int8_t >(); }
void InterleavehiTest::test_Reg_interleavehi2_int16 () { test_Reg_interleavehi2<int16_t>(); }
void InterleavehiTest::test_Reg_interleavehi2_int32 () { test_Reg_interleavehi2<int32_t>(); }
void InterleavehiTest::test_Reg_interleavehi2_int64 () { test_Reg_interleavehi2<int64_t>(); }
void InterleavehiTest::test_Reg_interleavehi2_float () { test_Reg_interleavehi2<float  >(); }
void InterleavehiTest::test_Reg_interleavehi2_double() { test_Reg_interleavehi2<double >(); }

template <typename T>
void InterleavehiTest::test_reg_interleavehi4()
{
	if (mipp::N<T>() > 4)
	{
		try
		{
			T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
			std::mt19937 g;
			std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);

			mipp::reg ri = mipp::interleavehi4<T>(r1, r2);

			for (auto j = 0; j < 4; j++)
				for (auto i = 0; i < mipp::N<T>()/4; i++)
					if (i % 2)
						CPPUNIT_ASSERT_EQUAL(inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2], *((T*)&ri + j*mipp::N<T>()/4 +i));
					else
						CPPUNIT_ASSERT_EQUAL(inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2], *((T*)&ri + j*mipp::N<T>()/4 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleavehiTest::test_reg_interleavehi4_int8  () { test_reg_interleavehi4<int8_t >(); }
void InterleavehiTest::test_reg_interleavehi4_int16 () { test_reg_interleavehi4<int16_t>(); }
void InterleavehiTest::test_reg_interleavehi4_int32 () { test_reg_interleavehi4<int32_t>(); }
void InterleavehiTest::test_reg_interleavehi4_int64 () { test_reg_interleavehi4<int64_t>(); }
void InterleavehiTest::test_reg_interleavehi4_float () { test_reg_interleavehi4<float  >(); }
void InterleavehiTest::test_reg_interleavehi4_double() { test_reg_interleavehi4<double >(); }

template <typename T>
void InterleavehiTest::test_Reg_interleavehi4()
{
	if (mipp::N<T>() > 4)
	{
		try
		{
			T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
			std::mt19937 g;
			std::iota   (inputs1, inputs1 + mipp::N<T>(), 0);
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::iota   (inputs2, inputs2 + mipp::N<T>(), 0);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;

			mipp::Reg<T> ri = mipp::interleavehi4(r1, r2);

			for (auto j = 0; j < 4; j++)
				for (auto i = 0; i < mipp::N<T>()/4; i++)
					if (i % 2)
						CPPUNIT_ASSERT_EQUAL(inputs2[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2], ri[j*mipp::N<T>()/4 +i]);
					else
						CPPUNIT_ASSERT_EQUAL(inputs1[j*mipp::N<T>()/4 + mipp::N<T>()/8 + i/2], ri[j*mipp::N<T>()/4 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleavehiTest::test_Reg_interleavehi4_int8  () { test_Reg_interleavehi4<int8_t >(); }
void InterleavehiTest::test_Reg_interleavehi4_int16 () { test_Reg_interleavehi4<int16_t>(); }
void InterleavehiTest::test_Reg_interleavehi4_int32 () { test_Reg_interleavehi4<int32_t>(); }
void InterleavehiTest::test_Reg_interleavehi4_int64 () { test_Reg_interleavehi4<int64_t>(); }
void InterleavehiTest::test_Reg_interleavehi4_float () { test_Reg_interleavehi4<float  >(); }
void InterleavehiTest::test_Reg_interleavehi4_double() { test_Reg_interleavehi4<double >(); }
