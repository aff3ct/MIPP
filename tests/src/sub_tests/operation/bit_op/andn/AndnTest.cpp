#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "AndnTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(AndnTest);

void 
AndnTest::setUp()
{
}

void 
AndnTest::tearDown()
{
}

template <typename T>
void AndnTest::test_reg_andn()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 0);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::andnb<T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = ~inputs1[i] & inputs2[i];
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AndnTest::test_reg_andn_int8 () { test_reg_andn<int8_t >(); }
void AndnTest::test_reg_andn_int16() { test_reg_andn<int16_t>(); }
void AndnTest::test_reg_andn_int32() { test_reg_andn<int32_t>(); }
void AndnTest::test_reg_andn_int64() { test_reg_andn<int64_t>(); }

template <typename T>
void AndnTest::test_Reg_andn()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 0);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = mipp::andnb(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = ~inputs1[i] & inputs2[i];
			CPPUNIT_ASSERT_EQUAL(res, r3[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AndnTest::test_Reg_andn_int8 () { test_Reg_andn<int8_t >(); }
void AndnTest::test_Reg_andn_int16() { test_Reg_andn<int16_t>(); }
void AndnTest::test_Reg_andn_int32() { test_Reg_andn<int32_t>(); }
void AndnTest::test_Reg_andn_int64() { test_Reg_andn<int64_t>(); }

template <typename T>
void AndnTest::test_msk_andn()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint8_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g) ? true : false;
				inputs2[i] = dis(g) ? true : false;
			}

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::msk m1 = mipp::set<N>(inputs1);
			mipp::msk m2 = mipp::set<N>(inputs2);
			mipp::msk m3 = mipp::andnb<N>(m1, m2);

			mipp::reg r = mipp::cvt_msk_reg<N>(m3);

			for (auto i = 0; i < N; i++)
			{
				bool res = ~inputs1[i] & inputs2[i];

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

void AndnTest::test_msk_andn_int8 () { test_msk_andn<int8_t >(); }
void AndnTest::test_msk_andn_int16() { test_msk_andn<int16_t>(); }
void AndnTest::test_msk_andn_int32() { test_msk_andn<int32_t>(); }
void AndnTest::test_msk_andn_int64() { test_msk_andn<int64_t>(); }

template <typename T>
void AndnTest::test_Msk_andn()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<uint8_t> dis(0, 1);

		for (auto t = 0; t < 100; t++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g) ? true : false;
				inputs2[i] = dis(g) ? true : false;
			}

			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
			std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

			mipp::Msk<N> m1 = inputs1;
			mipp::Msk<N> m2 = inputs2;
			mipp::Msk<N> m3 = mipp::andnb(m1, m2);

			mipp::reg r = mipp::cvt_msk_reg<N>(m3.m);

			for (auto i = 0; i < N; i++)
			{
				bool res = ~inputs1[i] & inputs2[i];

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

void AndnTest::test_Msk_andn_int8 () { test_Msk_andn<int8_t >(); }
void AndnTest::test_Msk_andn_int16() { test_Msk_andn<int16_t>(); }
void AndnTest::test_Msk_andn_int32() { test_Msk_andn<int32_t>(); }
void AndnTest::test_Msk_andn_int64() { test_Msk_andn<int64_t>(); }
