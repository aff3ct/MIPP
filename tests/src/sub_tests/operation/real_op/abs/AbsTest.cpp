#include <exception>
#include <algorithm>
#include <mipp.h>

#include "AbsTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(AbsTest);

void 
AbsTest::setUp()
{
}

void 
AbsTest::tearDown()
{
}

template <typename T>
void AbsTest::test_reg_abs()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), -mipp::N<T>()/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::abs<T>(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::abs(inputs1[i]);
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AbsTest::test_reg_abs_int8  () { test_reg_abs<int8_t >(); }
void AbsTest::test_reg_abs_int16 () { test_reg_abs<int16_t>(); }
void AbsTest::test_reg_abs_int32 () { test_reg_abs<int32_t>(); }
void AbsTest::test_reg_abs_int64 () { test_reg_abs<int64_t>(); }
void AbsTest::test_reg_abs_float () { test_reg_abs<float  >(); }
void AbsTest::test_reg_abs_double() { test_reg_abs<double >(); }

template <typename T>
void AbsTest::test_Reg_abs()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), -mipp::N<T>()/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::abs(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::abs(inputs1[i]);
			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AbsTest::test_Reg_abs_int8  () { test_Reg_abs<int8_t >(); }
void AbsTest::test_Reg_abs_int16 () { test_Reg_abs<int16_t>(); }
void AbsTest::test_Reg_abs_int32 () { test_Reg_abs<int32_t>(); }
void AbsTest::test_Reg_abs_int64 () { test_Reg_abs<int64_t>(); }
void AbsTest::test_Reg_abs_float () { test_Reg_abs<float  >(); }
void AbsTest::test_Reg_abs_double() { test_Reg_abs<double >(); }

template <typename T>
void AbsTest::test_reg_maskz_abs()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), -N/2);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::msk m  = mipp::set <N>(mask   );

		mipp::reg r2 = mipp::maskz<mipp::abs<T>, T>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = std::abs(inputs1[i]);
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

void AbsTest::test_reg_maskz_abs_int8  () { test_reg_maskz_abs<int8_t >(); }
void AbsTest::test_reg_maskz_abs_int16 () { test_reg_maskz_abs<int16_t>(); }
void AbsTest::test_reg_maskz_abs_int32 () { test_reg_maskz_abs<int32_t>(); }
void AbsTest::test_reg_maskz_abs_int64 () { test_reg_maskz_abs<int64_t>(); }
void AbsTest::test_reg_maskz_abs_float () { test_reg_maskz_abs<float  >(); }
void AbsTest::test_reg_maskz_abs_double() { test_reg_maskz_abs<double >(); }

template <typename T>
void AbsTest::test_Reg_maskz_abs()
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

		mipp::Reg<T> r2 = mipp::maskz<mipp::abs<T>>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = std::abs(inputs1[i]);
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

void AbsTest::test_Reg_maskz_abs_int8  () { test_Reg_maskz_abs<int8_t >(); }
void AbsTest::test_Reg_maskz_abs_int16 () { test_Reg_maskz_abs<int16_t>(); }
void AbsTest::test_Reg_maskz_abs_int32 () { test_Reg_maskz_abs<int32_t>(); }
void AbsTest::test_Reg_maskz_abs_int64 () { test_Reg_maskz_abs<int64_t>(); }
void AbsTest::test_Reg_maskz_abs_float () { test_Reg_maskz_abs<float  >(); }
void AbsTest::test_Reg_maskz_abs_double() { test_Reg_maskz_abs<double >(); }

template <typename T>
void AbsTest::test_reg_mask_abs()
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

		mipp::reg r3 = mipp::mask<mipp::abs<T>, T>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::abs(inputs1[i]);
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

void AbsTest::test_reg_mask_abs_int8  () { test_reg_mask_abs<int8_t >(); }
void AbsTest::test_reg_mask_abs_int16 () { test_reg_mask_abs<int16_t>(); }
void AbsTest::test_reg_mask_abs_int32 () { test_reg_mask_abs<int32_t>(); }
void AbsTest::test_reg_mask_abs_int64 () { test_reg_mask_abs<int64_t>(); }
void AbsTest::test_reg_mask_abs_float () { test_reg_mask_abs<float  >(); }
void AbsTest::test_reg_mask_abs_double() { test_reg_mask_abs<double >(); }

template <typename T>
void AbsTest::test_Reg_mask_abs()
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

		mipp::Reg<T> r3 = mipp::mask<mipp::abs<T>>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::abs(inputs1[i]);
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

void AbsTest::test_Reg_mask_abs_int8  () { test_Reg_mask_abs<int8_t >(); }
void AbsTest::test_Reg_mask_abs_int16 () { test_Reg_mask_abs<int16_t>(); }
void AbsTest::test_Reg_mask_abs_int32 () { test_Reg_mask_abs<int32_t>(); }
void AbsTest::test_Reg_mask_abs_int64 () { test_Reg_mask_abs<int64_t>(); }
void AbsTest::test_Reg_mask_abs_float () { test_Reg_mask_abs<float  >(); }
void AbsTest::test_Reg_mask_abs_double() { test_Reg_mask_abs<double >(); }
