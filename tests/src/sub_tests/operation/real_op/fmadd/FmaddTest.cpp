#include <exception>
#include <algorithm>
#include <mipp.h>

#include "FmaddTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(FmaddTest);

void 
FmaddTest::setUp()
{
}

void 
FmaddTest::tearDown()
{
}

template <typename T>
void FmaddTest::test_reg_fmadd()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()], inputs3[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::load<T>(inputs3);
		mipp::reg r4 = mipp::fmadd<T>(r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r4 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_reg_fmadd_float () { test_reg_fmadd<float >(); }
void FmaddTest::test_reg_fmadd_double() { test_reg_fmadd<double>(); }

template <typename T>
void FmaddTest::test_Reg_fmadd()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()], inputs3[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 2);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 3);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = inputs3;
		mipp::Reg<T> r4 = mipp::fmadd(r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] * inputs2[i] + inputs3[i];
			CPPUNIT_ASSERT_EQUAL(res, r4[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_Reg_fmadd_float () { test_Reg_fmadd<float >(); }
void FmaddTest::test_Reg_fmadd_double() { test_Reg_fmadd<double>(); }

template <typename T>
void FmaddTest::test_reg_maskz_fmadd()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::load<T>(inputs3);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r4 = mipp::maskz<mipp::fmadd<T>, T>(m, r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] * inputs2[i] + inputs3[i];
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r4 +i));
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r4 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_reg_maskz_fmadd_float () { test_reg_maskz_fmadd<float >(); }
void FmaddTest::test_reg_maskz_fmadd_double() { test_reg_maskz_fmadd<double>(); }

template <typename T>
void FmaddTest::test_Reg_maskz_fmadd()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = inputs3;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r4 = mipp::maskz<mipp::fmadd<T>>(m, r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] * inputs2[i] + inputs3[i];
				CPPUNIT_ASSERT_EQUAL(res, r4[i]);
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, r4[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_Reg_maskz_fmadd_float () { test_Reg_maskz_fmadd<float >(); }
void FmaddTest::test_Reg_maskz_fmadd_double() { test_Reg_maskz_fmadd<double>(); }

template <typename T>
void FmaddTest::test_reg_mask_fmadd()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N], inputs4[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 1);
		std::iota(inputs4, inputs4 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::load<T>(inputs3);
		mipp::reg r4 = mipp::load<T>(inputs4);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r5 = mipp::mask<mipp::fmadd<T>, T>(m, r4, r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] * inputs2[i] + inputs3[i];
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r5 +i));
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs4[i], *((T*)&r5 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_reg_mask_fmadd_float () { test_reg_mask_fmadd<float >(); }
void FmaddTest::test_reg_mask_fmadd_double() { test_reg_mask_fmadd<double>(); }

template <typename T>
void FmaddTest::test_Reg_mask_fmadd()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N], inputs4[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 1);
		std::iota(inputs4, inputs4 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(inputs3, inputs3 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = inputs3;
		mipp::Reg<T> r4 = inputs4;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r5 = mipp::mask<mipp::fmadd<T>>(m, r4, r1, r2, r3);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] * inputs2[i] + inputs3[i];
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r5 +i));
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs4[i], *((T*)&r5 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void FmaddTest::test_Reg_mask_fmadd_float () { test_Reg_mask_fmadd<float >(); }
void FmaddTest::test_Reg_mask_fmadd_double() { test_Reg_mask_fmadd<double>(); }
