#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "NotTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(NotTest);

void 
NotTest::setUp()
{
}

void 
NotTest::tearDown()
{
}

template <typename T>
void NotTest::test_reg_not()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 0);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::notb<T>(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = ~inputs1[i];
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void NotTest::test_reg_not_int8 () { test_reg_not<int8_t >(); }
void NotTest::test_reg_not_int16() { test_reg_not<int16_t>(); }
void NotTest::test_reg_not_int32() { test_reg_not<int32_t>(); }
void NotTest::test_reg_not_int64() { test_reg_not<int64_t>(); }

template <typename T>
void NotTest::test_Reg_not()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 0);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = ~r1;

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = ~inputs1[i];
			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void NotTest::test_Reg_not_int8 () { test_Reg_not<int8_t >(); }
void NotTest::test_Reg_not_int16() { test_Reg_not<int16_t>(); }
void NotTest::test_Reg_not_int32() { test_Reg_not<int32_t>(); }
void NotTest::test_Reg_not_int64() { test_Reg_not<int64_t>(); }

template <typename T>
void NotTest::test_msk_not()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint8_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g) ? true : false;

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::msk m1 = mipp::set<N>(inputs1);
			mipp::msk m2 = mipp::notb<N>(m1);

			mipp::reg r = mipp::cvt_reg<N>(m2);

			for (auto i = 0; i < N; i++)
			{
				bool res = !inputs1[i];

				if (res)
					CPPUNIT_ASSERT(*((T*)&r +i) != (T)0);
				else
					CPPUNIT_ASSERT_EQUAL((T)res, *((T*)&r +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void NotTest::test_msk_not_int8 () { test_msk_not<int8_t >(); }
void NotTest::test_msk_not_int16() { test_msk_not<int16_t>(); }
void NotTest::test_msk_not_int32() { test_msk_not<int32_t>(); }
void NotTest::test_msk_not_int64() { test_msk_not<int64_t>(); }

template <typename T>
void NotTest::test_Msk_not()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint8_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g) ? true : false;

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::Msk<N> m1 = inputs1;
			mipp::Msk<N> m2 = ~m1;

			mipp::reg r = mipp::cvt_reg<N>(m2.m);

			for (auto i = 0; i < N; i++)
			{
				bool res = !inputs1[i];

				if (res)
					CPPUNIT_ASSERT(*((T*)&r +i) != (T)0);
				else
					CPPUNIT_ASSERT_EQUAL((T)res, *((T*)&r +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void NotTest::test_Msk_not_int8 () { test_Msk_not<int8_t >(); }
void NotTest::test_Msk_not_int16() { test_Msk_not<int16_t>(); }
void NotTest::test_Msk_not_int32() { test_Msk_not<int32_t>(); }
void NotTest::test_Msk_not_int64() { test_Msk_not<int64_t>(); }
