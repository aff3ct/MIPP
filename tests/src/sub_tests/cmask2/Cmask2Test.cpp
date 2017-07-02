#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "Cmask2Test.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(Cmask2Test);

void 
Cmask2Test::setUp()
{
}

void 
Cmask2Test::tearDown()
{
}

template <typename T>
void Cmask2Test::test_reg_cmask2()
{
	try
	{
		uint32_t inputs[mipp::N<T>()/2];
		std::mt19937 g;
		std::iota   (inputs, inputs + mipp::N<T>(), 0);
		std::shuffle(inputs, inputs + mipp::N<T>(), g);

		mipp::reg r = mipp::cmask2<T>(inputs);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) +j), *((uint8_t*)&r + (i * sizeof(T)) +j));

		constexpr auto mid = mipp::N<int8_t>()/2;
		for (auto i = 0; i < mipp::N<T>()/2; i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) + mid +j),
				                     *((uint8_t*)&r + mid + (i * sizeof(T)) +j));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void Cmask2Test::test_reg_cmask2_int8  () { test_reg_cmask2<int8_t >(); }
void Cmask2Test::test_reg_cmask2_int16 () { test_reg_cmask2<int16_t>(); }
void Cmask2Test::test_reg_cmask2_int32 () { test_reg_cmask2<int32_t>(); }
void Cmask2Test::test_reg_cmask2_int64 () { test_reg_cmask2<int64_t>(); }
void Cmask2Test::test_reg_cmask2_float () { test_reg_cmask2<float  >(); }
void Cmask2Test::test_reg_cmask2_double() { test_reg_cmask2<double >(); }

template <typename T>
void Cmask2Test::test_Reg_cmask2()
{
	try
	{
		uint32_t inputs[mipp::N<T>()/2];
		std::mt19937 g;
		std::iota   (inputs, inputs + mipp::N<T>(), 0);
		std::shuffle(inputs, inputs + mipp::N<T>(), g);

		mipp::Reg<T> r = mipp::Reg<T>::cmask2(inputs);

		for (auto i = 0; i < mipp::N<T>()/2; i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) +j), *((uint8_t*)&r + (i * sizeof(T)) +j));

		constexpr auto mid = mipp::N<int8_t>()/2;
		for (auto i = 0; i < mipp::N<T>()/2; i++)
			for (auto j = 0; j < sizeof(T); j++)
				CPPUNIT_ASSERT_EQUAL((uint8_t)(inputs[i] * sizeof(T) + mid +j),
				                     *((uint8_t*)&r + mid + (i * sizeof(T)) +j));
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void Cmask2Test::test_Reg_cmask2_int8  () { test_Reg_cmask2<int8_t >(); }
void Cmask2Test::test_Reg_cmask2_int16 () { test_Reg_cmask2<int16_t>(); }
void Cmask2Test::test_Reg_cmask2_int32 () { test_Reg_cmask2<int32_t>(); }
void Cmask2Test::test_Reg_cmask2_int64 () { test_Reg_cmask2<int64_t>(); }
void Cmask2Test::test_Reg_cmask2_float () { test_Reg_cmask2<float  >(); }
void Cmask2Test::test_Reg_cmask2_double() { test_Reg_cmask2<double >(); }
