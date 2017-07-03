#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "InterleaveloTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(InterleaveloTest);

void 
InterleaveloTest::setUp()
{
}

void 
InterleaveloTest::tearDown()
{
}

template <typename T>
void InterleaveloTest::test_reg_interleavelo()
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

		mipp::reg ri = mipp::interleavelo<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[i/2], *((T*)&ri +i));
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[i/2], *((T*)&ri +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleaveloTest::test_reg_interleavelo_int8  () { test_reg_interleavelo<int8_t >(); }
void InterleaveloTest::test_reg_interleavelo_int16 () { test_reg_interleavelo<int16_t>(); }
void InterleaveloTest::test_reg_interleavelo_int32 () { test_reg_interleavelo<int32_t>(); }
void InterleaveloTest::test_reg_interleavelo_int64 () { test_reg_interleavelo<int64_t>(); }
void InterleaveloTest::test_reg_interleavelo_float () { test_reg_interleavelo<float  >(); }
void InterleaveloTest::test_reg_interleavelo_double() { test_reg_interleavelo<double >(); }

template <typename T>
void InterleaveloTest::test_Reg_interleavelo()
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

		mipp::Reg<T> ri = mipp::interleavelo(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[i/2], ri[i]);
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[i/2], ri[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleaveloTest::test_Reg_interleavelo_int8  () { test_Reg_interleavelo<int8_t >(); }
void InterleaveloTest::test_Reg_interleavelo_int16 () { test_Reg_interleavelo<int16_t>(); }
void InterleaveloTest::test_Reg_interleavelo_int32 () { test_Reg_interleavelo<int32_t>(); }
void InterleaveloTest::test_Reg_interleavelo_int64 () { test_Reg_interleavelo<int64_t>(); }
void InterleaveloTest::test_Reg_interleavelo_float () { test_Reg_interleavelo<float  >(); }
void InterleaveloTest::test_Reg_interleavelo_double() { test_Reg_interleavelo<double >(); }

template <typename T>
void InterleaveloTest::test_reg_interleavelo2()
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

			mipp::reg ri = mipp::interleavelo2<T>(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[i/2], *((T*)&ri +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[i/2], *((T*)&ri +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], *((T*)&ri + mipp::N<T>()/2 +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], *((T*)&ri + mipp::N<T>()/2 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleaveloTest::test_reg_interleavelo2_int8  () { test_reg_interleavelo2<int8_t >(); }
void InterleaveloTest::test_reg_interleavelo2_int16 () { test_reg_interleavelo2<int16_t>(); }
void InterleaveloTest::test_reg_interleavelo2_int32 () { test_reg_interleavelo2<int32_t>(); }
void InterleaveloTest::test_reg_interleavelo2_int64 () { test_reg_interleavelo2<int64_t>(); }
void InterleaveloTest::test_reg_interleavelo2_float () { test_reg_interleavelo2<float  >(); }
void InterleaveloTest::test_reg_interleavelo2_double() { test_reg_interleavelo2<double >(); }

template <typename T>
void InterleaveloTest::test_Reg_interleavelo2()
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

			mipp::Reg<T> ri = mipp::interleavelo2(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[i/2], *((T*)&ri +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[i/2], *((T*)&ri +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], ri[mipp::N<T>()/2 +i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], ri[mipp::N<T>()/2 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleaveloTest::test_Reg_interleavelo2_int8  () { test_Reg_interleavelo2<int8_t >(); }
void InterleaveloTest::test_Reg_interleavelo2_int16 () { test_Reg_interleavelo2<int16_t>(); }
void InterleaveloTest::test_Reg_interleavelo2_int32 () { test_Reg_interleavelo2<int32_t>(); }
void InterleaveloTest::test_Reg_interleavelo2_int64 () { test_Reg_interleavelo2<int64_t>(); }
void InterleaveloTest::test_Reg_interleavelo2_float () { test_Reg_interleavelo2<float  >(); }
void InterleaveloTest::test_Reg_interleavelo2_double() { test_Reg_interleavelo2<double >(); }
