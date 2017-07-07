#include <exception>
#include <algorithm>
#include <numeric>
#include <mipp.h>

#include "LoadTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(LoadTest);

void 
LoadTest::setUp()
{
}

void 
LoadTest::tearDown()
{
}

template <typename T>
void LoadTest::test_reg_load()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::load<T>(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LoadTest::test_reg_load_int8  () { test_reg_load<int8_t >(); }
void LoadTest::test_reg_load_int16 () { test_reg_load<int16_t>(); }
void LoadTest::test_reg_load_int32 () { test_reg_load<int32_t>(); }
void LoadTest::test_reg_load_int64 () { test_reg_load<int64_t>(); }
void LoadTest::test_reg_load_float () { test_reg_load<float  >(); }
void LoadTest::test_reg_load_double() { test_reg_load<double >(); }

template <typename T>
void LoadTest::test_reg_loadu()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::loadu<T>(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], *((T*)&r +i));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LoadTest::test_reg_loadu_int8  () { test_reg_loadu<int8_t >(); }
void LoadTest::test_reg_loadu_int16 () { test_reg_loadu<int16_t>(); }
void LoadTest::test_reg_loadu_int32 () { test_reg_loadu<int32_t>(); }
void LoadTest::test_reg_loadu_int64 () { test_reg_loadu<int64_t>(); }
void LoadTest::test_reg_loadu_float () { test_reg_loadu<float  >(); }
void LoadTest::test_reg_loadu_double() { test_reg_loadu<double >(); }

template <typename T>
void LoadTest::test_Reg_load()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r; r.load(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], r[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LoadTest::test_Reg_load_int8  () { test_Reg_load<int8_t >(); }
void LoadTest::test_Reg_load_int16 () { test_Reg_load<int16_t>(); }
void LoadTest::test_Reg_load_int32 () { test_Reg_load<int32_t>(); }
void LoadTest::test_Reg_load_int64 () { test_Reg_load<int64_t>(); }
void LoadTest::test_Reg_load_float () { test_Reg_load<float  >(); }
void LoadTest::test_Reg_load_double() { test_Reg_load<double >(); }

template <typename T>
void LoadTest::test_Reg_loadu()
{
	try
	{
		T inputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r; r.loadu(inputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], r[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void LoadTest::test_Reg_loadu_int8  () { test_Reg_loadu<int8_t >(); }
void LoadTest::test_Reg_loadu_int16 () { test_Reg_loadu<int16_t>(); }
void LoadTest::test_Reg_loadu_int32 () { test_Reg_loadu<int32_t>(); }
void LoadTest::test_Reg_loadu_int64 () { test_Reg_loadu<int64_t>(); }
void LoadTest::test_Reg_loadu_float () { test_Reg_loadu<float  >(); }
void LoadTest::test_Reg_loadu_double() { test_Reg_loadu<double >(); }
