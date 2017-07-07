#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "DivTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(DivTest);

void 
DivTest::setUp()
{
}

void 
DivTest::tearDown()
{
}

template <typename T>
void DivTest::test_reg_div()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::div <T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			T diff = std::abs(res - *((T*)&r3 +i));
			CPPUNIT_ASSERT(diff < 0.01);
#else
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_reg_div_int8  () { test_reg_div<int8_t >(); }
void DivTest::test_reg_div_int16 () { test_reg_div<int16_t>(); }
void DivTest::test_reg_div_int32 () { test_reg_div<int32_t>(); }
void DivTest::test_reg_div_int64 () { test_reg_div<int64_t>(); }
void DivTest::test_reg_div_float () { test_reg_div<float  >(); }
void DivTest::test_reg_div_double() { test_reg_div<double >(); }

template <typename T>
void DivTest::test_Reg_div()
{
	try
	{
		T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = r1 / r2;

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			T diff = std::abs(res - r3[i]);
			CPPUNIT_ASSERT(diff < 0.01);
#else
			CPPUNIT_ASSERT_EQUAL(res, r3[i]);
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_Reg_div_int8  () { test_Reg_div<int8_t >(); }
void DivTest::test_Reg_div_int16 () { test_Reg_div<int16_t>(); }
void DivTest::test_Reg_div_int32 () { test_Reg_div<int32_t>(); }
void DivTest::test_Reg_div_int64 () { test_Reg_div<int64_t>(); }
void DivTest::test_Reg_div_float () { test_Reg_div<float  >(); }
void DivTest::test_Reg_div_double() { test_Reg_div<double >(); }

template <typename T>
void DivTest::test_reg_maskz_div()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r3 = mipp::maskz<T,mipp::div<T>>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - *((T*)&r3 +i));
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_reg_maskz_div_int8  () { test_reg_maskz_div<int8_t >(); }
void DivTest::test_reg_maskz_div_int16 () { test_reg_maskz_div<int16_t>(); }
void DivTest::test_reg_maskz_div_int32 () { test_reg_maskz_div<int32_t>(); }
void DivTest::test_reg_maskz_div_int64 () { test_reg_maskz_div<int64_t>(); }
void DivTest::test_reg_maskz_div_float () { test_reg_maskz_div<float  >(); }
void DivTest::test_reg_maskz_div_double() { test_reg_maskz_div<double >(); }

template <typename T>
void DivTest::test_Reg_maskz_div()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r3 = mipp::maskz<T,mipp::div>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - r3[i]);
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT_EQUAL(res, r3[i]);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL((T)0, r3[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_Reg_maskz_div_int8  () { test_Reg_maskz_div<int8_t >(); }
void DivTest::test_Reg_maskz_div_int16 () { test_Reg_maskz_div<int16_t>(); }
void DivTest::test_Reg_maskz_div_int32 () { test_Reg_maskz_div<int32_t>(); }
void DivTest::test_Reg_maskz_div_int64 () { test_Reg_maskz_div<int64_t>(); }
void DivTest::test_Reg_maskz_div_float () { test_Reg_maskz_div<float  >(); }
void DivTest::test_Reg_maskz_div_double() { test_Reg_maskz_div<double >(); }

template <typename T>
void DivTest::test_reg_mask_div()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::reg r3 = mipp::load<T>(inputs3);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r4 = mipp::mask<T,mipp::div<T>>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - *((T*)&r4 +i));
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r4 +i));
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs3[i], *((T*)&r4 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_reg_mask_div_int8  () { test_reg_mask_div<int8_t >(); }
void DivTest::test_reg_mask_div_int16 () { test_reg_mask_div<int16_t>(); }
void DivTest::test_reg_mask_div_int32 () { test_reg_mask_div<int32_t>(); }
void DivTest::test_reg_mask_div_int64 () { test_reg_mask_div<int64_t>(); }
void DivTest::test_reg_mask_div_float () { test_reg_mask_div<float  >(); }
void DivTest::test_reg_mask_div_double() { test_reg_mask_div<double >(); }

template <typename T>
void DivTest::test_Reg_mask_div()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N], inputs3[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), 1);
		std::iota(inputs2, inputs2 + mipp::N<T>(), 1);
		std::iota(inputs3, inputs3 + mipp::N<T>(), 0);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Reg<T> r3 = inputs3;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r4 = mipp::mask<T,mipp::div>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / inputs2[i];
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - r4[i]);
				CPPUNIT_ASSERT(diff < 0.01);
#else
				CPPUNIT_ASSERT_EQUAL(res, r4[i]);
#endif
			}
			else
				CPPUNIT_ASSERT_EQUAL(inputs3[i], r4[i]);
		}
	}	
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void DivTest::test_Reg_mask_div_int8  () { test_Reg_mask_div<int8_t >(); }
void DivTest::test_Reg_mask_div_int16 () { test_Reg_mask_div<int16_t>(); }
void DivTest::test_Reg_mask_div_int32 () { test_Reg_mask_div<int32_t>(); }
void DivTest::test_Reg_mask_div_int64 () { test_Reg_mask_div<int64_t>(); }
void DivTest::test_Reg_mask_div_float () { test_Reg_mask_div<float  >(); }
void DivTest::test_Reg_mask_div_double() { test_Reg_mask_div<double >(); }
