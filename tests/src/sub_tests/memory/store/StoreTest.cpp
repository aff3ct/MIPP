#include <exception>
#include <algorithm>
#include <numeric>
#include <mipp.h>

#include "StoreTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(StoreTest);

void 
StoreTest::setUp()
{
}

void 
StoreTest::tearDown()
{
}

template <typename T>
void StoreTest::test_reg_store()
{
	try
	{
		T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::load<T>(inputs);
		mipp::store<T>(outputs, r);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], outputs[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void StoreTest::test_reg_store_int8  () { test_reg_store<int8_t >(); }
void StoreTest::test_reg_store_int16 () { test_reg_store<int16_t>(); }
void StoreTest::test_reg_store_int32 () { test_reg_store<int32_t>(); }
void StoreTest::test_reg_store_int64 () { test_reg_store<int64_t>(); }
void StoreTest::test_reg_store_float () { test_reg_store<float  >(); }
void StoreTest::test_reg_store_double() { test_reg_store<double >(); }

template <typename T>
void StoreTest::test_reg_storeu()
{
	try
	{
		T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::reg r = mipp::loadu<T>(inputs);
		mipp::storeu<T>(outputs, r);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], outputs[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void StoreTest::test_reg_storeu_int8  () { test_reg_storeu<int8_t >(); }
void StoreTest::test_reg_storeu_int16 () { test_reg_storeu<int16_t>(); }
void StoreTest::test_reg_storeu_int32 () { test_reg_storeu<int32_t>(); }
void StoreTest::test_reg_storeu_int64 () { test_reg_storeu<int64_t>(); }
void StoreTest::test_reg_storeu_float () { test_reg_storeu<float  >(); }
void StoreTest::test_reg_storeu_double() { test_reg_storeu<double >(); }

template <typename T>
void StoreTest::test_Reg_store()
{
	try
	{
		T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r; r.load(inputs);
		r.store(outputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], outputs[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void StoreTest::test_Reg_store_int8  () { test_Reg_store<int8_t >(); }
void StoreTest::test_Reg_store_int16 () { test_Reg_store<int16_t>(); }
void StoreTest::test_Reg_store_int32 () { test_Reg_store<int32_t>(); }
void StoreTest::test_Reg_store_int64 () { test_Reg_store<int64_t>(); }
void StoreTest::test_Reg_store_float () { test_Reg_store<float  >(); }
void StoreTest::test_Reg_store_double() { test_Reg_store<double >(); }

template <typename T>
void StoreTest::test_Reg_storeu()
{
	try
	{
		T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
		std::iota(inputs, inputs + mipp::N<T>(), 0);

		mipp::Reg<T> r; r.loadu(inputs);
		r.storeu(outputs);

		for (auto i = 0; i < mipp::N<T>(); i++)
			CPPUNIT_ASSERT_EQUAL(inputs[i], outputs[i]);
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void StoreTest::test_Reg_storeu_int8  () { test_Reg_storeu<int8_t >(); }
void StoreTest::test_Reg_storeu_int16 () { test_Reg_storeu<int16_t>(); }
void StoreTest::test_Reg_storeu_int32 () { test_Reg_storeu<int32_t>(); }
void StoreTest::test_Reg_storeu_int64 () { test_Reg_storeu<int64_t>(); }
void StoreTest::test_Reg_storeu_float () { test_Reg_storeu<float  >(); }
void StoreTest::test_Reg_storeu_double() { test_Reg_storeu<double >(); }
