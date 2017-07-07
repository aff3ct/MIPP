#include <exception>
#include <algorithm>
#include <mipp.h>

#include "MaxTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(MaxTest);

void 
MaxTest::setUp()
{
}

void 
MaxTest::tearDown()
{
}

template <typename T>
void MaxTest::test_reg_max()
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
		mipp::reg r3 = mipp::max <T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::max(inputs1[i], inputs2[i]);
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void MaxTest::test_reg_max_int8  () { test_reg_max<int8_t >(); }
void MaxTest::test_reg_max_int16 () { test_reg_max<int16_t>(); }
void MaxTest::test_reg_max_int32 () { test_reg_max<int32_t>(); }
void MaxTest::test_reg_max_int64 () { test_reg_max<int64_t>(); }
void MaxTest::test_reg_max_float () { test_reg_max<float  >(); }
void MaxTest::test_reg_max_double() { test_reg_max<double >(); }

template <typename T>
void MaxTest::test_Reg_max()
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
		mipp::Reg<T> r3 = mipp::max(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = std::max(inputs1[i], inputs2[i]);
			CPPUNIT_ASSERT_EQUAL(res, r3[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void MaxTest::test_Reg_max_int8  () { test_Reg_max<int8_t >(); }
void MaxTest::test_Reg_max_int16 () { test_Reg_max<int16_t>(); }
void MaxTest::test_Reg_max_int32 () { test_Reg_max<int32_t>(); }
void MaxTest::test_Reg_max_int64 () { test_Reg_max<int64_t>(); }
void MaxTest::test_Reg_max_float () { test_Reg_max<float  >(); }
void MaxTest::test_Reg_max_double() { test_Reg_max<double >(); }

template <typename T>
void MaxTest::test_reg_maskz_max()
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

		mipp::reg r3 = mipp::maskz<T,mipp::max<T>>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::max(inputs1[i], inputs2[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
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

void MaxTest::test_reg_maskz_max_int8  () { test_reg_maskz_max<int8_t >(); }
void MaxTest::test_reg_maskz_max_int16 () { test_reg_maskz_max<int16_t>(); }
void MaxTest::test_reg_maskz_max_int32 () { test_reg_maskz_max<int32_t>(); }
void MaxTest::test_reg_maskz_max_int64 () { test_reg_maskz_max<int64_t>(); }
void MaxTest::test_reg_maskz_max_float () { test_reg_maskz_max<float  >(); }
void MaxTest::test_reg_maskz_max_double() { test_reg_maskz_max<double >(); }

template <typename T>
void MaxTest::test_Reg_maskz_max()
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

		mipp::Reg<T> r3 = mipp::maskz<T,mipp::max>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::max(inputs1[i], inputs2[i]);
				CPPUNIT_ASSERT_EQUAL(res, r3[i]);
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

void MaxTest::test_Reg_maskz_max_int8  () { test_Reg_maskz_max<int8_t >(); }
void MaxTest::test_Reg_maskz_max_int16 () { test_Reg_maskz_max<int16_t>(); }
void MaxTest::test_Reg_maskz_max_int32 () { test_Reg_maskz_max<int32_t>(); }
void MaxTest::test_Reg_maskz_max_int64 () { test_Reg_maskz_max<int64_t>(); }
void MaxTest::test_Reg_maskz_max_float () { test_Reg_maskz_max<float  >(); }
void MaxTest::test_Reg_maskz_max_double() { test_Reg_maskz_max<double >(); }

template <typename T>
void MaxTest::test_reg_mask_max()
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

		mipp::reg r4 = mipp::mask<T,mipp::max<T>>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::max(inputs1[i], inputs2[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r4 +i));
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

void MaxTest::test_reg_mask_max_int8  () { test_reg_mask_max<int8_t >(); }
void MaxTest::test_reg_mask_max_int16 () { test_reg_mask_max<int16_t>(); }
void MaxTest::test_reg_mask_max_int32 () { test_reg_mask_max<int32_t>(); }
void MaxTest::test_reg_mask_max_int64 () { test_reg_mask_max<int64_t>(); }
void MaxTest::test_reg_mask_max_float () { test_reg_mask_max<float  >(); }
void MaxTest::test_reg_mask_max_double() { test_reg_mask_max<double >(); }

template <typename T>
void MaxTest::test_Reg_mask_max()
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

		mipp::Reg<T> r4 = mipp::mask<T,mipp::max>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = std::max(inputs1[i], inputs2[i]);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r4 +i));
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

void MaxTest::test_Reg_mask_max_int8  () { test_Reg_mask_max<int8_t >(); }
void MaxTest::test_Reg_mask_max_int16 () { test_Reg_mask_max<int16_t>(); }
void MaxTest::test_Reg_mask_max_int32 () { test_Reg_mask_max<int32_t>(); }
void MaxTest::test_Reg_mask_max_int64 () { test_Reg_mask_max<int64_t>(); }
void MaxTest::test_Reg_mask_max_float () { test_Reg_mask_max<float  >(); }
void MaxTest::test_Reg_mask_max_double() { test_Reg_mask_max<double >(); }
