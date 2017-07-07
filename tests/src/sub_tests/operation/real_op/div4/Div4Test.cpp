#include <exception>
#include <algorithm>
#include <mipp.h>

#include "Div4Test.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(Div4Test);

void 
Div4Test::setUp()
{
}

void 
Div4Test::tearDown()
{
}

template <typename T>
void Div4Test::test_reg_div4()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), -mipp::N<T>()/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::div4<T>(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			T diff = std::abs(res - *((T*)&r2 +i));
			CPPUNIT_ASSERT(diff < 0.01);
#else 
			CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void Div4Test::test_reg_div4_int8  () { test_reg_div4<int8_t >(); }
void Div4Test::test_reg_div4_int16 () { test_reg_div4<int16_t>(); }
void Div4Test::test_reg_div4_int32 () { test_reg_div4<int32_t>(); }
void Div4Test::test_reg_div4_int64 () { test_reg_div4<int64_t>(); }
void Div4Test::test_reg_div4_float () { test_reg_div4<float  >(); }
void Div4Test::test_reg_div4_double() { test_reg_div4<double >(); }

template <typename T>
void Div4Test::test_Reg_div4()
{
	try
	{
		T inputs1[mipp::N<T>()];
		std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max());

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = mipp::div4(r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
			T diff = std::abs(res - r2[i]);
			CPPUNIT_ASSERT(diff < 0.01);
#else 
			CPPUNIT_ASSERT_EQUAL(res, r2[i]);
#endif
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void Div4Test::test_Reg_div4_int8  () { test_Reg_div4<int8_t >(); }
void Div4Test::test_Reg_div4_int16 () { test_Reg_div4<int16_t>(); }
void Div4Test::test_Reg_div4_int32 () { test_Reg_div4<int32_t>(); }
void Div4Test::test_Reg_div4_int64 () { test_Reg_div4<int64_t>(); }
void Div4Test::test_Reg_div4_float () { test_Reg_div4<float  >(); }
void Div4Test::test_Reg_div4_double() { test_Reg_div4<double >(); }

template <typename T>
void Div4Test::test_reg_maskz_div4()
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

		mipp::reg r2 = mipp::maskz<T,mipp::div4<T>>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - *((T*)&r2 +i));
				CPPUNIT_ASSERT(diff < 0.01);
#else 
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
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

void Div4Test::test_reg_maskz_div4_int8  () { test_reg_maskz_div4<int8_t >(); }
void Div4Test::test_reg_maskz_div4_int16 () { test_reg_maskz_div4<int16_t>(); }
void Div4Test::test_reg_maskz_div4_int32 () { test_reg_maskz_div4<int32_t>(); }
void Div4Test::test_reg_maskz_div4_int64 () { test_reg_maskz_div4<int64_t>(); }
void Div4Test::test_reg_maskz_div4_float () { test_reg_maskz_div4<float  >(); }
void Div4Test::test_reg_maskz_div4_double() { test_reg_maskz_div4<double >(); }

template <typename T>
void Div4Test::test_Reg_maskz_div4()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::min());

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(mask,    mask    + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Msk<N> m  = mask;

		mipp::Reg<T> r2 = mipp::maskz<T,mipp::div4>(m, r1);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - r2[i]);
				CPPUNIT_ASSERT(diff < 0.01);
#else 
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
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

void Div4Test::test_Reg_maskz_div4_int8  () { test_Reg_maskz_div4<int8_t >(); }
void Div4Test::test_Reg_maskz_div4_int16 () { test_Reg_maskz_div4<int16_t>(); }
void Div4Test::test_Reg_maskz_div4_int32 () { test_Reg_maskz_div4<int32_t>(); }
void Div4Test::test_Reg_maskz_div4_int64 () { test_Reg_maskz_div4<int64_t>(); }
void Div4Test::test_Reg_maskz_div4_float () { test_Reg_maskz_div4<float  >(); }
void Div4Test::test_Reg_maskz_div4_double() { test_Reg_maskz_div4<double >(); }

template <typename T>
void Div4Test::test_reg_mask_div4()
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

		mipp::reg r3 = mipp::mask<T,mipp::div4<T>>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - *((T*)&r3 +i));
				CPPUNIT_ASSERT(diff < 0.01);
#else 
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r3 +i));
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

void Div4Test::test_reg_mask_div4_int8  () { test_reg_mask_div4<int8_t >(); }
void Div4Test::test_reg_mask_div4_int16 () { test_reg_mask_div4<int16_t>(); }
void Div4Test::test_reg_mask_div4_int32 () { test_reg_mask_div4<int32_t>(); }
void Div4Test::test_reg_mask_div4_int64 () { test_reg_mask_div4<int64_t>(); }
void Div4Test::test_reg_mask_div4_float () { test_reg_mask_div4<float  >(); }
void Div4Test::test_reg_mask_div4_double() { test_reg_mask_div4<double >(); }

template <typename T>
void Div4Test::test_Reg_mask_div4()
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

		mipp::Reg<T> r3 = mipp::mask<T,mipp::div4>(m, r2, r1);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (mask[i])
			{
				T res = inputs1[i] / (T)4;
#if defined(MIPP_NEON) && MIPP_INSTR_VERSION == 1
				T diff = std::abs(res - r3[i]);
				CPPUNIT_ASSERT(diff < 0.01);
#else 
				CPPUNIT_ASSERT_EQUAL(res, r3[i]);
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

void Div4Test::test_Reg_mask_div4_int8  () { test_Reg_mask_div4<int8_t >(); }
void Div4Test::test_Reg_mask_div4_int16 () { test_Reg_mask_div4<int16_t>(); }
void Div4Test::test_Reg_mask_div4_int32 () { test_Reg_mask_div4<int32_t>(); }
void Div4Test::test_Reg_mask_div4_int64 () { test_Reg_mask_div4<int64_t>(); }
void Div4Test::test_Reg_mask_div4_float () { test_Reg_mask_div4<float  >(); }
void Div4Test::test_Reg_mask_div4_double() { test_Reg_mask_div4<double >(); }
