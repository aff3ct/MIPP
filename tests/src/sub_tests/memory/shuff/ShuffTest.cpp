#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "ShuffTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(ShuffTest);

void
ShuffTest::setUp()
{
}

void
ShuffTest::tearDown()
{
}

template <typename T>
void ShuffTest::test_reg_shuff()
{
	try
	{
		uint32_t cm_inputs[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (cm_inputs, cm_inputs + mipp::N<T>(), 0);
		std::shuffle(cm_inputs, cm_inputs + mipp::N<T>(), g);

		mipp::reg cm = mipp::cmask<T>(cm_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::load<T>(inputs);
		mipp::reg s = mipp::shuff<T>(r, cm);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[cm_inputs[i]], *((T*)&s +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void ShuffTest::test_reg_shuff_int8  () { test_reg_shuff<int8_t >(); }
void ShuffTest::test_reg_shuff_int16 () { test_reg_shuff<int16_t>(); }
void ShuffTest::test_reg_shuff_int32 () { test_reg_shuff<int32_t>(); }
void ShuffTest::test_reg_shuff_int64 () { test_reg_shuff<int64_t>(); }
void ShuffTest::test_reg_shuff_float () { test_reg_shuff<float  >(); }
void ShuffTest::test_reg_shuff_double() { test_reg_shuff<double >(); }

template <typename T>
void ShuffTest::test_Reg_shuff()
{
	try
	{
		uint32_t cm_inputs[mipp::N<T>()];
		std::mt19937 g;
		std::iota   (cm_inputs, cm_inputs + mipp::N<T>(), 0);
		std::shuffle(cm_inputs, cm_inputs + mipp::N<T>(), g);

		mipp::Reg<T> cm = mipp::Reg<T>::cmask(cm_inputs);

		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r = inputs;
		mipp::Reg<T> s = r.shuff(cm);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[cm_inputs[i]], s[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void ShuffTest::test_Reg_shuff_int8  () { test_Reg_shuff<int8_t >(); }
void ShuffTest::test_Reg_shuff_int16 () { test_Reg_shuff<int16_t>(); }
void ShuffTest::test_Reg_shuff_int32 () { test_Reg_shuff<int32_t>(); }
void ShuffTest::test_Reg_shuff_int64 () { test_Reg_shuff<int64_t>(); }
void ShuffTest::test_Reg_shuff_float () { test_Reg_shuff<float  >(); }
void ShuffTest::test_Reg_shuff_double() { test_Reg_shuff<double >(); }

template <typename T>
void ShuffTest::test_reg_shuff2()
{
	if (mipp::N<T>() >= 2)
	{
		try
		{
			uint32_t cm2_inputs[mipp::N<T>()/2];
			std::mt19937 g;
			std::iota   (cm2_inputs, cm2_inputs + mipp::N<T>()/2, 0);
			std::shuffle(cm2_inputs, cm2_inputs + mipp::N<T>()/2, g);

			mipp::reg cm2 = mipp::cmask2<T>(cm2_inputs);

			T inputs[mipp::N<T>()];
			std::iota(inputs, inputs + mipp::N<T>(), 0);

			mipp::reg r = mipp::load<T>(inputs);
			mipp::reg s = mipp::shuff2<T>(r, cm2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				CPPUNIT_ASSERT_EQUAL(inputs[cm2_inputs[i]], *((T*)&s +i));
			for (auto i = 0; i < mipp::N<T>()/2; i++)
				CPPUNIT_ASSERT_EQUAL(inputs[mipp::N<T>()/2 + cm2_inputs[i]], *((T*)&s + mipp::N<T>()/2 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void ShuffTest::test_reg_shuff2_int8  () { test_reg_shuff2<int8_t >(); }
void ShuffTest::test_reg_shuff2_int16 () { test_reg_shuff2<int16_t>(); }
void ShuffTest::test_reg_shuff2_int32 () { test_reg_shuff2<int32_t>(); }
void ShuffTest::test_reg_shuff2_int64 () { test_reg_shuff2<int64_t>(); }
void ShuffTest::test_reg_shuff2_float () { test_reg_shuff2<float  >(); }
void ShuffTest::test_reg_shuff2_double() { test_reg_shuff2<double >(); }

template <typename T>
void ShuffTest::test_Reg_shuff2()
{
	if (mipp::N<T>() >= 2)
	{
		try
		{
			uint32_t cm2_inputs[mipp::N<T>()/2];
			std::mt19937 g;
			std::iota   (cm2_inputs, cm2_inputs + mipp::N<T>()/2, 0);
			std::shuffle(cm2_inputs, cm2_inputs + mipp::N<T>()/2, g);

			mipp::Reg<T> cm2 = mipp::Reg<T>::cmask2(cm2_inputs);

			T inputs[mipp::N<T>()];
			std::iota(inputs, inputs + mipp::N<T>(), 0);

			mipp::Reg<T> r = inputs;
			mipp::Reg<T> s = r.shuff2(cm2);

			for (auto i = 0; i < mipp::N<T>()/2; i++)
				CPPUNIT_ASSERT_EQUAL(inputs[cm2_inputs[i]], s[i]);
			for (auto i = 0; i < mipp::N<T>()/2; i++)
				CPPUNIT_ASSERT_EQUAL(inputs[mipp::N<T>()/2 + cm2_inputs[i]], s[mipp::N<T>()/2 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void ShuffTest::test_Reg_shuff2_int8  () { test_Reg_shuff2<int8_t >(); }
void ShuffTest::test_Reg_shuff2_int16 () { test_Reg_shuff2<int16_t>(); }
void ShuffTest::test_Reg_shuff2_int32 () { test_Reg_shuff2<int32_t>(); }
void ShuffTest::test_Reg_shuff2_int64 () { test_Reg_shuff2<int64_t>(); }
void ShuffTest::test_Reg_shuff2_float () { test_Reg_shuff2<float  >(); }
void ShuffTest::test_Reg_shuff2_double() { test_Reg_shuff2<double >(); }

template <typename T>
void ShuffTest::test_reg_shuff4()
{
	if (mipp::N<T>() >= 4)
	{
		try
		{
			uint32_t cm4_inputs[mipp::N<T>()/4];
			std::mt19937 g;
			std::iota   (cm4_inputs, cm4_inputs + mipp::N<T>()/4, 0);
			std::shuffle(cm4_inputs, cm4_inputs + mipp::N<T>()/4, g);

			mipp::reg cm4 = mipp::cmask4<T>(cm4_inputs);

			T inputs[mipp::N<T>()];
			std::iota(inputs, inputs + mipp::N<T>(), 0);

			mipp::reg r = mipp::load<T>(inputs);
			mipp::reg s = mipp::shuff4<T>(r, cm4);

			for (auto j = 0; j < 4; j++)
				for (auto i = 0; i < mipp::N<T>()/4; i++)
					CPPUNIT_ASSERT_EQUAL(inputs[j*mipp::N<T>()/4 + cm4_inputs[i]], *((T*)&s + j*mipp::N<T>()/4 +i));
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void ShuffTest::test_reg_shuff4_int8  () { test_reg_shuff4<int8_t >(); }
void ShuffTest::test_reg_shuff4_int16 () { test_reg_shuff4<int16_t>(); }
void ShuffTest::test_reg_shuff4_int32 () { test_reg_shuff4<int32_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
void ShuffTest::test_reg_shuff4_int64 () { test_reg_shuff4<int64_t>(); }
#endif
void ShuffTest::test_reg_shuff4_float () { test_reg_shuff4<float  >(); }
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
void ShuffTest::test_reg_shuff4_double() { test_reg_shuff4<double >(); }
#endif

template <typename T>
void ShuffTest::test_Reg_shuff4()
{
	if (mipp::N<T>() >= 4)
	{
		try
		{
			uint32_t cm4_inputs[mipp::N<T>()/4];
			std::mt19937 g;
			std::iota   (cm4_inputs, cm4_inputs + mipp::N<T>()/4, 0);
			std::shuffle(cm4_inputs, cm4_inputs + mipp::N<T>()/4, g);

			mipp::Reg<T> cm4 = mipp::Reg<T>::cmask4(cm4_inputs);

			T inputs[mipp::N<T>()];
			std::iota(inputs, inputs + mipp::N<T>(), 0);

			mipp::Reg<T> r = inputs;
			mipp::Reg<T> s = r.shuff4(cm4);

			for (auto j = 0; j < 4; j++)
				for (auto i = 0; i < mipp::N<T>()/4; i++)
					CPPUNIT_ASSERT_EQUAL(inputs[j*mipp::N<T>()/4 + cm4_inputs[i]], s[j*mipp::N<T>()/4 +i]);
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
}

void ShuffTest::test_Reg_shuff4_int8  () { test_Reg_shuff4<int8_t >(); }
void ShuffTest::test_Reg_shuff4_int16 () { test_Reg_shuff4<int16_t>(); }
void ShuffTest::test_Reg_shuff4_int32 () { test_Reg_shuff4<int32_t>(); }
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
void ShuffTest::test_Reg_shuff4_int64 () { test_Reg_shuff4<int64_t>(); }
#endif
void ShuffTest::test_Reg_shuff4_float () { test_Reg_shuff4<float  >(); }
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
void ShuffTest::test_Reg_shuff4_double() { test_Reg_shuff4<double >(); }
#endif
