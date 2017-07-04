#include <exception>
#include <algorithm>
#include <cmath>
#include <mipp.h>

#include "SqrtTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(SqrtTest);

void 
SqrtTest::setUp()
{
}

void 
SqrtTest::tearDown()
{
}

template <typename T>
void SqrtTest::test_reg_sqrt()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::sqrt<T>(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::sqrt(inputs1[i]);
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SqrtTest::test_reg_sqrt_float () { test_reg_sqrt<float >(); }
void SqrtTest::test_reg_sqrt_double() { test_reg_sqrt<double>(); }

template <typename T>
void SqrtTest::test_Reg_sqrt()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::sqrt(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::sqrt(inputs1[i]);
			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SqrtTest::test_Reg_sqrt_float () { test_Reg_sqrt<float >(); }
void SqrtTest::test_Reg_sqrt_double() { test_Reg_sqrt<double>(); }

template <typename T>
void SqrtTest::test_reg_maskz_sqrt()
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

		mipp::reg r2 = mipp::maskz<mipp::sqrt<T>, T>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = std::sqrt(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
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

void SqrtTest::test_reg_maskz_sqrt_float () { test_reg_maskz_sqrt<float >(); }
void SqrtTest::test_reg_maskz_sqrt_double() { test_reg_maskz_sqrt<double>(); }

template <typename T>
void SqrtTest::test_Reg_maskz_sqrt()
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

		mipp::Reg<T> r2 = mipp::maskz<mipp::sqrt<T>>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = std::sqrt(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
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

void SqrtTest::test_Reg_maskz_sqrt_float () { test_Reg_maskz_sqrt<float >(); }
void SqrtTest::test_Reg_maskz_sqrt_double() { test_Reg_maskz_sqrt<double>(); }

template <typename T>
void SqrtTest::test_reg_mask_sqrt()
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

		mipp::reg r3 = mipp::mask<mipp::sqrt<T>, T>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::sqrt(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
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

void SqrtTest::test_reg_mask_sqrt_float () { test_reg_mask_sqrt<float >(); }
void SqrtTest::test_reg_mask_sqrt_double() { test_reg_mask_sqrt<double>(); }

template <typename T>
void SqrtTest::test_Reg_mask_sqrt()
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

		mipp::Reg<T> r3 = mipp::mask<mipp::sqrt<T>>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::sqrt(inputs1[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
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

void SqrtTest::test_Reg_mask_sqrt_float () { test_Reg_mask_sqrt<float >(); }
void SqrtTest::test_Reg_mask_sqrt_double() { test_Reg_mask_sqrt<double>(); }
