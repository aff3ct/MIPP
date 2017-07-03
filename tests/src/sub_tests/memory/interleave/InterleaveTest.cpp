#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "InterleaveTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(InterleaveTest);

void 
InterleaveTest::setUp()
{
}

void 
InterleaveTest::tearDown()
{
}

template <typename T>
void InterleaveTest::test_reg_interleave()
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

		mipp::regx2 ri = mipp::interleave<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[i/2], *((T*)&ri.val[0] +i));
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[i/2], *((T*)&ri.val[0] +i));

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], *((T*)&ri.val[1] +i));
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], *((T*)&ri.val[1] +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleaveTest::test_reg_interleave_int8  () { test_reg_interleave<int8_t >(); }
void InterleaveTest::test_reg_interleave_int16 () { test_reg_interleave<int16_t>(); }
void InterleaveTest::test_reg_interleave_int32 () { test_reg_interleave<int32_t>(); }
void InterleaveTest::test_reg_interleave_int64 () { test_reg_interleave<int64_t>(); }
void InterleaveTest::test_reg_interleave_float () { test_reg_interleave<float  >(); }
void InterleaveTest::test_reg_interleave_double() { test_reg_interleave<double >(); }

template <typename T>
void InterleaveTest::test_Reg_interleave()
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

		mipp::Regx2<T> ri = mipp::interleave(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[i/2], ri[0][i]);
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[i/2], ri[0][i]);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (i % 2)
				CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], ri[1][i]);
			else
				CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], ri[1][i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void InterleaveTest::test_Reg_interleave_int8  () { test_Reg_interleave<int8_t >(); }
void InterleaveTest::test_Reg_interleave_int16 () { test_Reg_interleave<int16_t>(); }
void InterleaveTest::test_Reg_interleave_int32 () { test_Reg_interleave<int32_t>(); }
void InterleaveTest::test_Reg_interleave_int64 () { test_Reg_interleave<int64_t>(); }
void InterleaveTest::test_Reg_interleave_float () { test_Reg_interleave<float  >(); }
void InterleaveTest::test_Reg_interleave_double() { test_Reg_interleave<double >(); }

template <typename T>
void InterleaveTest::test_reg_interleave2()
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

			mipp::regx2 ri = mipp::interleave2<T>(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[i/2], *((T*)&ri.val[0] +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[i/2], *((T*)&ri.val[0] +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], *((T*)&ri.val[0] + mipp::N<T>()/2 +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], *((T*)&ri.val[0] + mipp::N<T>()/2 +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/4 + i/2], *((T*)&ri.val[1] +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/4 + i/2], *((T*)&ri.val[1] +i));

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2],
					                     *((T*)&ri.val[1] + mipp::N<T>()/2 +i));
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2],
					                     *((T*)&ri.val[1] + mipp::N<T>()/2 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleaveTest::test_reg_interleave2_int8  () { test_reg_interleave2<int8_t >(); }
void InterleaveTest::test_reg_interleave2_int16 () { test_reg_interleave2<int16_t>(); }
void InterleaveTest::test_reg_interleave2_int32 () { test_reg_interleave2<int32_t>(); }
void InterleaveTest::test_reg_interleave2_int64 () { test_reg_interleave2<int64_t>(); }
void InterleaveTest::test_reg_interleave2_float () { test_reg_interleave2<float  >(); }
void InterleaveTest::test_reg_interleave2_double() { test_reg_interleave2<double >(); }

template <typename T>
void InterleaveTest::test_Reg_interleave2()
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

			mipp::Regx2<T> ri = mipp::interleave2(r1, r2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[i/2], ri[0][i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[i/2], ri[0][i]);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + i/2], ri[0][mipp::N<T>()/2 +i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + i/2], ri[0][mipp::N<T>()/2 +i]);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/4 + i/2], ri[1][i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/4 + i/2], ri[1][i]);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				if (i % 2)
					CPPUNIT_ASSERT_EQUAL(inputs2[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], ri[1][mipp::N<T>()/2 +i]);
				else
					CPPUNIT_ASSERT_EQUAL(inputs1[mipp::N<T>()/2 + mipp::N<T>()/4 + i/2], ri[1][mipp::N<T>()/2 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void InterleaveTest::test_Reg_interleave2_int8  () { test_Reg_interleave2<int8_t >(); }
void InterleaveTest::test_Reg_interleave2_int16 () { test_Reg_interleave2<int16_t>(); }
void InterleaveTest::test_Reg_interleave2_int32 () { test_Reg_interleave2<int32_t>(); }
void InterleaveTest::test_Reg_interleave2_int64 () { test_Reg_interleave2<int64_t>(); }
void InterleaveTest::test_Reg_interleave2_float () { test_Reg_interleave2<float  >(); }
void InterleaveTest::test_Reg_interleave2_double() { test_Reg_interleave2<double >(); }
