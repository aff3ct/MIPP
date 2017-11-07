#include <exception>
#include <algorithm>
#include <numeric>
#include <mipp.h>

#include "SetTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(SetTest);

void 
SetTest::setUp()
{
}

void 
SetTest::tearDown()
{
}

template <typename T>
void SetTest::test_reg_set1()
{
	try
	{
		mipp::reg r = mipp::set1<T>((T)12);
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)12, *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_reg_set1_int8  () { test_reg_set1<int8_t >(); }
void SetTest::test_reg_set1_int16 () { test_reg_set1<int16_t>(); }
void SetTest::test_reg_set1_int32 () { test_reg_set1<int32_t>(); }
void SetTest::test_reg_set1_int64 () { test_reg_set1<int64_t>(); }
void SetTest::test_reg_set1_float () { test_reg_set1<float  >(); }
void SetTest::test_reg_set1_double() { test_reg_set1<double >(); }

template <typename T>
void SetTest::test_reg_set0()
{
	try
	{
		mipp::reg r = mipp::set0<T>();
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_reg_set0_int8  () { test_reg_set0<int8_t >(); }
void SetTest::test_reg_set0_int16 () { test_reg_set0<int16_t>(); }
void SetTest::test_reg_set0_int32 () { test_reg_set0<int32_t>(); }
void SetTest::test_reg_set0_int64 () { test_reg_set0<int64_t>(); }
void SetTest::test_reg_set0_float () { test_reg_set0<float  >(); }
void SetTest::test_reg_set0_double() { test_reg_set0<double >(); }

template <typename T>
void SetTest::test_reg_set()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::set<T>(inputs);
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_reg_set_int8  () { test_reg_set<int8_t >(); }
void SetTest::test_reg_set_int16 () { test_reg_set<int16_t>(); }
void SetTest::test_reg_set_int32 () { test_reg_set<int32_t>(); }
void SetTest::test_reg_set_int64 () { test_reg_set<int64_t>(); }
void SetTest::test_reg_set_float () { test_reg_set<float  >(); }
void SetTest::test_reg_set_double() { test_reg_set<double >(); }

template <typename T>
void SetTest::test_Reg_set1()
{
	try
	{
		mipp::Reg<T> r = (T)12;
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)12, r[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Reg_set1_int8  () { test_Reg_set1<int8_t >(); }
void SetTest::test_Reg_set1_int16 () { test_Reg_set1<int16_t>(); }
void SetTest::test_Reg_set1_int32 () { test_Reg_set1<int32_t>(); }
void SetTest::test_Reg_set1_int64 () { test_Reg_set1<int64_t>(); }
void SetTest::test_Reg_set1_float () { test_Reg_set1<float  >(); }
void SetTest::test_Reg_set1_double() { test_Reg_set1<double >(); }

template <typename T>
void SetTest::test_Reg_set0()
{
	try
	{
		mipp::Reg<T> r; r.set0();
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)0, r[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Reg_set0_int8  () { test_Reg_set0<int8_t >(); }
void SetTest::test_Reg_set0_int16 () { test_Reg_set0<int16_t>(); }
void SetTest::test_Reg_set0_int32 () { test_Reg_set0<int32_t>(); }
void SetTest::test_Reg_set0_int64 () { test_Reg_set0<int64_t>(); }
void SetTest::test_Reg_set0_float () { test_Reg_set0<float  >(); }
void SetTest::test_Reg_set0_double() { test_Reg_set0<double >(); }

template <typename T>
void SetTest::test_Reg_set()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r = inputs;
		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], r[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Reg_set_int8  () { test_Reg_set<int8_t >(); }
void SetTest::test_Reg_set_int16 () { test_Reg_set<int16_t>(); }
void SetTest::test_Reg_set_int32 () { test_Reg_set<int32_t>(); }
void SetTest::test_Reg_set_int64 () { test_Reg_set<int64_t>(); }
void SetTest::test_Reg_set_float () { test_Reg_set<float  >(); }
void SetTest::test_Reg_set_double() { test_Reg_set<double >(); }

template <typename T>
void SetTest::test_msk_set1()
{
	try
	{
		mipp::msk m0 = mipp::set1<mipp::N<T>()>(false);
		mipp::msk m1 = mipp::set1<mipp::N<T>()>(true );

		mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0);
		mipp::reg r1 = mipp::toreg<mipp::N<T>()>(m1);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r0 +i));

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT((T)0 != *((T*)&r1 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_msk_set1_int8  () { test_msk_set1<int8_t >(); }
void SetTest::test_msk_set1_int16 () { test_msk_set1<int16_t>(); }
void SetTest::test_msk_set1_int32 () { test_msk_set1<int32_t>(); }
void SetTest::test_msk_set1_int64 () { test_msk_set1<int64_t>(); }
void SetTest::test_msk_set1_float () { test_msk_set1<float  >(); }
void SetTest::test_msk_set1_double() { test_msk_set1<double >(); }

template <typename T>
void SetTest::test_msk_set0()
{
	try
	{
		mipp::msk m0 = mipp::set0<mipp::N<T>()>();
		mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r0 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_msk_set0_int8  () { test_msk_set0<int8_t >(); }
void SetTest::test_msk_set0_int16 () { test_msk_set0<int16_t>(); }
void SetTest::test_msk_set0_int32 () { test_msk_set0<int32_t>(); }
void SetTest::test_msk_set0_int64 () { test_msk_set0<int64_t>(); }
void SetTest::test_msk_set0_float () { test_msk_set0<float  >(); }
void SetTest::test_msk_set0_double() { test_msk_set0<double >(); }

template <typename T>
void SetTest::test_msk_set()
{
	try
	{
		bool inputs[mipp::N<T>()];

		for (auto i = 0; i < mipp::N<T>(); i++)
			inputs[i] = i % 2 ? true : false;

		mipp::msk m = mipp::set<mipp::N<T>()>(inputs);
		mipp::reg r = mipp::toreg<mipp::N<T>()>(m);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (!inputs[i])
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r +i));
			else
				CPPUNIT_ASSERT((T)0 != *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_msk_set_int8  () { test_msk_set<int8_t >(); }
void SetTest::test_msk_set_int16 () { test_msk_set<int16_t>(); }
void SetTest::test_msk_set_int32 () { test_msk_set<int32_t>(); }
void SetTest::test_msk_set_int64 () { test_msk_set<int64_t>(); }
void SetTest::test_msk_set_float () { test_msk_set<float  >(); }
void SetTest::test_msk_set_double() { test_msk_set<double >(); }

template <typename T>
void SetTest::test_Msk_set1()
{
	try
	{
		mipp::Msk<mipp::N<T>()> m0 = false;
		mipp::Msk<mipp::N<T>()> m1 = true;

		mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0.m);
		mipp::reg r1 = mipp::toreg<mipp::N<T>()>(m1.m);

		for (auto i = 0; i < mipp::N<T>(); i++)
#ifndef MIPP_NO
			CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r0 +i));
#else
			CPPUNIT_ASSERT_EQUAL((mipp::reg)0, r0);
#endif

		for (auto i = 0; i < mipp::N<T>(); i++)
#ifndef MIPP_NO
			CPPUNIT_ASSERT((T)0 != *((T*)&r1 +i));
#else
			CPPUNIT_ASSERT((mipp::reg)0 != r1);
#endif
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Msk_set1_int8  () { test_Msk_set1<int8_t >(); }
void SetTest::test_Msk_set1_int16 () { test_Msk_set1<int16_t>(); }
void SetTest::test_Msk_set1_int32 () { test_Msk_set1<int32_t>(); }
void SetTest::test_Msk_set1_int64 () { test_Msk_set1<int64_t>(); }
void SetTest::test_Msk_set1_float () { test_Msk_set1<float  >(); }
void SetTest::test_Msk_set1_double() { test_Msk_set1<double >(); }

template <typename T>
void SetTest::test_Msk_set0()
{
	try
	{
		mipp::Msk<mipp::N<T>()> m0; m0.set0();
		mipp::reg r0 = mipp::toreg<mipp::N<T>()>(m0.m);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r0 +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Msk_set0_int8  () { test_Msk_set0<int8_t >(); }
void SetTest::test_Msk_set0_int16 () { test_Msk_set0<int16_t>(); }
void SetTest::test_Msk_set0_int32 () { test_Msk_set0<int32_t>(); }
void SetTest::test_Msk_set0_int64 () { test_Msk_set0<int64_t>(); }
void SetTest::test_Msk_set0_float () { test_Msk_set0<float  >(); }
void SetTest::test_Msk_set0_double() { test_Msk_set0<double >(); }

template <typename T>
void SetTest::test_Msk_set()
{
	try
	{
		bool inputs[mipp::N<T>()];

		for (auto i = 0; i < mipp::N<T>(); i++)
			inputs[i] = i % 2 ? true : false;

		mipp::Msk<mipp::N<T>()> m = inputs;
		mipp::reg r = mipp::toreg<mipp::N<T>()>(m.m);

		for (auto i = 0; i < mipp::N<T>(); i++)
			if (!inputs[i])
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r +i));
			else
				CPPUNIT_ASSERT((T)0 != *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SetTest::test_Msk_set_int8  () { test_Msk_set<int8_t >(); }
void SetTest::test_Msk_set_int16 () { test_Msk_set<int16_t>(); }
void SetTest::test_Msk_set_int32 () { test_Msk_set<int32_t>(); }
void SetTest::test_Msk_set_int64 () { test_Msk_set<int64_t>(); }
void SetTest::test_Msk_set_float () { test_Msk_set<float  >(); }
void SetTest::test_Msk_set_double() { test_Msk_set<double >(); }
