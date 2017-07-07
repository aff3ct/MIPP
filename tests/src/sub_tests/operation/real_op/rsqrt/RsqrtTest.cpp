#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>

#include "RsqrtTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(RsqrtTest);

void 
RsqrtTest::setUp()
{
}

void 
RsqrtTest::tearDown()
{
}

template <typename T>
void RsqrtTest::test_reg_rsqrt()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::rsqrt<T>(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = (T)1 / std::sqrt(inputs1[i]);
//			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
			T diff = std::abs(res - *((T*)&r2 +i));
#ifdef MIPP_NEON
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT(diff < 0.001);
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_reg_rsqrt_float () { test_reg_rsqrt<float >(); }
void RsqrtTest::test_reg_rsqrt_double() { test_reg_rsqrt<double>(); }

template <typename T>
void RsqrtTest::test_Reg_rsqrt()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::rsqrt(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = (T)1 / std::sqrt(inputs1[i]);
//			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
			T diff = std::abs(res - *((T*)&r2 +i));
#ifdef MIPP_NEON
			CPPUNIT_ASSERT(diff < 0.01);
#else
			CPPUNIT_ASSERT(diff < 0.001);
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_Reg_rsqrt_float () { test_Reg_rsqrt<float >(); }
void RsqrtTest::test_Reg_rsqrt_double() { test_Reg_rsqrt<double>(); }

template <typename T>
void RsqrtTest::test_reg_maskz_rsqrt()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r2 = mipp::maskz<T,mipp::rsqrt<T>>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = (T)1 / std::sqrt(inputs1[i]);
//				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
				T diff = std::abs(res - *((T*)&r2 +i));
#ifdef MIPP_NEON
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT(diff < 0.001);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r2 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_reg_maskz_rsqrt_float () { test_reg_maskz_rsqrt<float >(); }
void RsqrtTest::test_reg_maskz_rsqrt_double() { test_reg_maskz_rsqrt<double>(); }

template <typename T>
void RsqrtTest::test_Reg_maskz_rsqrt()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r2 = mipp::maskz<T,mipp::rsqrt>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = (T)1 / std::sqrt(inputs1[i]);
//				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
				T diff = std::abs(res - *((T*)&r2 +i));
#ifdef MIPP_NEON
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT(diff < 0.001);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, r2[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_Reg_maskz_rsqrt_float () { test_Reg_maskz_rsqrt<float >(); }
void RsqrtTest::test_Reg_maskz_rsqrt_double() { test_Reg_maskz_rsqrt<double>(); }

template <typename T>
void RsqrtTest::test_reg_mask_rsqrt()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r3 = mipp::mask<T,mipp::rsqrt<T>>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = (T)1 / std::sqrt(inputs1[i]);
//				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
				T diff = std::abs(res - *((T*)&r3 +i));
#ifdef MIPP_NEON
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT(diff < 0.001);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs2[i], *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_reg_mask_rsqrt_float () { test_reg_mask_rsqrt<float >(); }
void RsqrtTest::test_reg_mask_rsqrt_double() { test_reg_mask_rsqrt<double>(); }

template <typename T>
void RsqrtTest::test_Reg_mask_rsqrt()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r3 = mipp::mask<T,mipp::rsqrt>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = (T)1 / std::sqrt(inputs1[i]);
//				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
				T diff = std::abs(res - *((T*)&r3 +i));
#ifdef MIPP_NEON
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT(diff < 0.001);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs2[i], *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void RsqrtTest::test_Reg_mask_rsqrt_float () { test_Reg_mask_rsqrt<float >(); }
void RsqrtTest::test_Reg_mask_rsqrt_double() { test_Reg_mask_rsqrt<double>(); }
