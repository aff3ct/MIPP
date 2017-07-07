#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "RoundTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(RoundTest);

void 
RoundTest::setUp()
{
}

void 
RoundTest::tearDown()
{
}

template <typename T>
void RoundTest::test_reg_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::round<T>(r1);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::round(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_reg_round_float () { test_reg_round<float  >(); }
void RoundTest::test_reg_round_double() { test_reg_round<double >(); }

template <typename T>
void RoundTest::test_Reg_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = mipp::round(r1);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::round(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_Reg_round_float () { test_Reg_round<float  >(); }
void RoundTest::test_Reg_round_double() { test_Reg_round<double >(); }

template <typename T>
void RoundTest::test_reg_maskz_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			std::shuffle(mask, mask + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::msk m  = mipp::set <N>(mask   );

			mipp::reg r2 = mipp::maskz<T,mipp::round<T>>(m, r1);

			for (auto i = 0; i < N; i++)
			{
				if (mask[i])
				{
					T res = std::round(inputs1[i]);
					CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
				}
				else
					CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r2 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_reg_maskz_round_float () { test_reg_maskz_round<float  >(); }
void RoundTest::test_reg_maskz_round_double() { test_reg_maskz_round<double >(); }

template <typename T>
void RoundTest::test_Reg_maskz_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			std::shuffle(mask, mask + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Msk<N> m  = mask;

			mipp::Reg<T> r2 = mipp::maskz<T,mipp::round>(m, r1);

			for (auto i = 0; i < N; i++)
			{
				if (mask[i])
				{
					T res = std::round(inputs1[i]);
					CPPUNIT_ASSERT_EQUAL(res, r2[i]);
				}
				else
					CPPUNIT_ASSERT_EQUAL((T)0, r2[i]);
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_Reg_maskz_round_float () { test_Reg_maskz_round<float  >(); }
void RoundTest::test_Reg_maskz_round_double() { test_Reg_maskz_round<double >(); }

template <typename T>
void RoundTest::test_reg_mask_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			std::shuffle(mask, mask + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);
			mipp::msk m  = mipp::set <N>(mask   );

			mipp::reg r3 = mipp::mask<T,mipp::round<T>>(m, r2, r1);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (mask[i])
				{
					T res = std::round(inputs1[i]);
					CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
				}
				else
					CPPUNIT_ASSERT_EQUAL(inputs2[i], *((T*)&r3 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_reg_mask_round_float () { test_reg_mask_round<float  >(); }
void RoundTest::test_reg_mask_round_double() { test_reg_mask_round<double >(); }

template <typename T>
void RoundTest::test_Reg_mask_round()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis((T)-10, (T)10);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		for (auto l = 0; l < 100; l++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			std::shuffle(mask, mask + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;
			mipp::Msk<N> m  = mask;

			mipp::Reg<T> r3 = mipp::mask<T,mipp::round>(m, r2, r1);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				if (mask[i])
				{
					T res = std::round(inputs1[i]);
					CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
				}
				else
					CPPUNIT_ASSERT_EQUAL(inputs2[i], *((T*)&r3 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RoundTest::test_Reg_mask_round_float () { test_Reg_mask_round<float  >(); }
void RoundTest::test_Reg_mask_round_double() { test_Reg_mask_round<double >(); }
