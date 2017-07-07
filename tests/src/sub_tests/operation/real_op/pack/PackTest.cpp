#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "PackTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(PackTest);

void 
PackTest::setUp()
{
}

void 
PackTest::tearDown()
{
}

template <typename T1, typename T2>
void PackTest::test_reg_pack()
{
#ifndef MIPP_NO
	try
	{
		constexpr int N1 = mipp::N<T1>();
		constexpr int N2 = mipp::N<T2>();

		static_assert(N1 < N2, "N1 has to be smaller than N2.");

		T1 inputs1[N1], inputs2[N1];
		std::iota(inputs1, inputs1 + N1, std::numeric_limits<T1>::max() - N1);
		std::iota(inputs2, inputs2 + N1, -N1/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + N1, g);
		std::shuffle(inputs2, inputs2 + N1, g);

		mipp::reg r1 = mipp::load<T1>(inputs1);
		mipp::reg r2 = mipp::load<T1>(inputs2);
		mipp::reg r3 = mipp::pack<T1,T2>(r1, r2);

		T1 m = (T1)std::numeric_limits<T2>::min();
		T1 M = (T1)std::numeric_limits<T2>::max();
		for (auto i = 0; i < N1; i++)
		{
			auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs1[i], m), M));
			CPPUNIT_ASSERT_EQUAL(res, *((T2*)&r3 +i));
		}

		for (auto i = 0; i < N1; i++)
		{
			auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs2[i], m), M));
			CPPUNIT_ASSERT_EQUAL(res, *((T2*)&r3 + N1 +i));
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
#endif
}

void PackTest::test_reg_pack_int16_int8  () { test_reg_pack<int16_t,int8_t >(); };
void PackTest::test_reg_pack_int32_int16 () { test_reg_pack<int32_t,int16_t>(); };

template <typename T1, typename T2>
void PackTest::test_Reg_pack()
{
#ifndef MIPP_NO
	try
	{
		constexpr int N1 = mipp::N<T1>();
		constexpr int N2 = mipp::N<T2>();

		static_assert(N1 < N2, "N1 has to be smaller than N2.");

		T1 inputs1[N1], inputs2[N1];
		std::iota(inputs1, inputs1 + N1, std::numeric_limits<T1>::max() - N1);
		std::iota(inputs2, inputs2 + N1, -N1/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + N1, g);
		std::shuffle(inputs2, inputs2 + N1, g);

		mipp::Reg<T1> r1 = inputs1;
		mipp::Reg<T1> r2 = inputs2;
		mipp::Reg<T2> r3 = mipp::pack<T1,T2>(r1, r2);

		T1 m = (T1)std::numeric_limits<T2>::min();
		T1 M = (T1)std::numeric_limits<T2>::max();
		for (auto i = 0; i < N1; i++)
		{
			auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs1[i], m), M));
			CPPUNIT_ASSERT_EQUAL(res, r3[i]);
		}

		for (auto i = 0; i < N1; i++)
		{
			auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs2[i], m), M));
			CPPUNIT_ASSERT_EQUAL(res, r3[N1 +i]);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
#endif
}

void PackTest::test_Reg_pack_int16_int8  () { test_Reg_pack<int16_t,int8_t >(); };
void PackTest::test_Reg_pack_int32_int16 () { test_Reg_pack<int32_t,int16_t>(); };
