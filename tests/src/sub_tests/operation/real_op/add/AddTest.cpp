#include <exception>
#include <algorithm>
#include <mipp.h>

#include "AddTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(AddTest);

void 
AddTest::setUp()
{
}

void 
AddTest::tearDown()
{
}

template <typename T>
void AddTest::test_reg_add()
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
		mipp::reg r3 = mipp::add <T>(r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] + inputs2[i];
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AddTest::test_reg_add_int8  () { test_reg_add<int8_t >(); }
void AddTest::test_reg_add_int16 () { test_reg_add<int16_t>(); }
void AddTest::test_reg_add_int32 () { test_reg_add<int32_t>(); }
void AddTest::test_reg_add_int64 () { test_reg_add<int64_t>(); }
void AddTest::test_reg_add_float () { test_reg_add<float  >(); }
void AddTest::test_reg_add_double() { test_reg_add<double >(); }

template <typename T>
void AddTest::test_Reg_add()
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
		mipp::Reg<T> r3 = r1 + r2;

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] + inputs2[i];
			CPPUNIT_ASSERT_EQUAL(res, r3[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void AddTest::test_Reg_add_int8  () { test_Reg_add<int8_t >(); }
void AddTest::test_Reg_add_int16 () { test_Reg_add<int16_t>(); }
void AddTest::test_Reg_add_int32 () { test_Reg_add<int32_t>(); }
void AddTest::test_Reg_add_int64 () { test_Reg_add<int64_t>(); }
void AddTest::test_Reg_add_float () { test_Reg_add<float  >(); }
void AddTest::test_Reg_add_double() { test_Reg_add<double >(); }

template <typename T>
void AddTest::test_reg_maskz_add()
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

		mipp::reg r3 = mipp::maskz<T,mipp::add<T>>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] + inputs2[i];
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

void AddTest::test_reg_maskz_add_int8  () { test_reg_maskz_add<int8_t >(); }
void AddTest::test_reg_maskz_add_int16 () { test_reg_maskz_add<int16_t>(); }
void AddTest::test_reg_maskz_add_int32 () { test_reg_maskz_add<int32_t>(); }
void AddTest::test_reg_maskz_add_int64 () { test_reg_maskz_add<int64_t>(); }
void AddTest::test_reg_maskz_add_float () { test_reg_maskz_add<float  >(); }
void AddTest::test_reg_maskz_add_double() { test_reg_maskz_add<double >(); }

template <typename T>
void AddTest::test_Reg_maskz_add()
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

		mipp::Reg<T> r3 = mipp::maskz<T,mipp::add>(m, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] + inputs2[i];
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

void AddTest::test_Reg_maskz_add_int8  () { test_Reg_maskz_add<int8_t >(); }
void AddTest::test_Reg_maskz_add_int16 () { test_Reg_maskz_add<int16_t>(); }
void AddTest::test_Reg_maskz_add_int32 () { test_Reg_maskz_add<int32_t>(); }
void AddTest::test_Reg_maskz_add_int64 () { test_Reg_maskz_add<int64_t>(); }
void AddTest::test_Reg_maskz_add_float () { test_Reg_maskz_add<float  >(); }
void AddTest::test_Reg_maskz_add_double() { test_Reg_maskz_add<double >(); }

template <typename T>
void AddTest::test_reg_mask_add()
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

		mipp::reg r4 = mipp::mask<T,mipp::add<T>>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] + inputs2[i];
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

void AddTest::test_reg_mask_add_int8  () { test_reg_mask_add<int8_t >(); }
void AddTest::test_reg_mask_add_int16 () { test_reg_mask_add<int16_t>(); }
void AddTest::test_reg_mask_add_int32 () { test_reg_mask_add<int32_t>(); }
void AddTest::test_reg_mask_add_int64 () { test_reg_mask_add<int64_t>(); }
void AddTest::test_reg_mask_add_float () { test_reg_mask_add<float  >(); }
void AddTest::test_reg_mask_add_double() { test_reg_mask_add<double >(); }

template <typename T>
void AddTest::test_Reg_mask_add()
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

		mipp::Reg<T> r4 = mipp::mask<T,mipp::add>(m, r3, r1, r2);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] + inputs2[i];
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

void AddTest::test_Reg_mask_add_int8  () { test_Reg_mask_add<int8_t >(); }
void AddTest::test_Reg_mask_add_int16 () { test_Reg_mask_add<int16_t>(); }
void AddTest::test_Reg_mask_add_int32 () { test_Reg_mask_add<int32_t>(); }
void AddTest::test_Reg_mask_add_int64 () { test_Reg_mask_add<int64_t>(); }
void AddTest::test_Reg_mask_add_float () { test_Reg_mask_add<float  >(); }
void AddTest::test_Reg_mask_add_double() { test_Reg_mask_add<double >(); }
