#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "BlendTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(BlendTest);

void 
BlendTest::setUp()
{
}

void 
BlendTest::tearDown()
{
}

template <typename T>
void BlendTest::test_reg_blend()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + N, 0);
		std::iota(inputs2, inputs2 + N, N);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		for (auto t = 0; t < 100; t++)
		{
			std::shuffle(mask, mask + N, g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);
			mipp::msk m  = mipp::set <N>(mask   );

			mipp::reg ri = mipp::blend<T>(r1, r2, m);

			for (auto i = 0; i < N; i++)
				CPPUNIT_ASSERT_EQUAL(mask[i] ? inputs1[i] : inputs2[i], *((T*)&ri +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void BlendTest::test_reg_blend_int8  () { test_reg_blend<int8_t >(); }
void BlendTest::test_reg_blend_int16 () { test_reg_blend<int16_t>(); }
void BlendTest::test_reg_blend_int32 () { test_reg_blend<int32_t>(); }
void BlendTest::test_reg_blend_int64 () { test_reg_blend<int64_t>(); }
void BlendTest::test_reg_blend_float () { test_reg_blend<float  >(); }
void BlendTest::test_reg_blend_double() { test_reg_blend<double >(); }

template <typename T>
void BlendTest::test_Reg_blend()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::iota(inputs1, inputs1 + N, 0);
		std::iota(inputs2, inputs2 + N, N);

		bool mask[N];
		std::fill(mask,       mask + N/2, true );
		std::fill(mask + N/2, mask + N,   false);

		std::mt19937 g;
		for (auto t = 0; t < 100; t++)
		{
			std::shuffle(mask, mask + N, g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;
			mipp::Msk<N> m  = mask;

			mipp::Reg<T> ri = mipp::blend(r1, r2, m);

			for (auto i = 0; i < N; i++)
				CPPUNIT_ASSERT_EQUAL(mask[i] ? inputs1[i] : inputs2[i], ri[i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void BlendTest::test_Reg_blend_int8  () { test_Reg_blend<int8_t >(); }
void BlendTest::test_Reg_blend_int16 () { test_Reg_blend<int16_t>(); }
void BlendTest::test_Reg_blend_int32 () { test_Reg_blend<int32_t>(); }
void BlendTest::test_Reg_blend_int64 () { test_Reg_blend<int64_t>(); }
void BlendTest::test_Reg_blend_float () { test_Reg_blend<float  >(); }
void BlendTest::test_Reg_blend_double() { test_Reg_blend<double >(); }
