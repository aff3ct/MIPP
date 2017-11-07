#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "SignTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(SignTest);

void 
SignTest::setUp()
{
}

void 
SignTest::tearDown()
{
}

template <typename T>
void SignTest::test_reg_sign()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, -N/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + N, g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::msk m  = mipp::sign<T>(r1);
		mipp::reg r2 = mipp::toreg<N>(m);

		for (auto i = 0; i < N; i++)
		{
			if (inputs1[i] >= 0)
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r2 +i));
			else
				CPPUNIT_ASSERT(*((T*)&r2 +i) != (T)0);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SignTest::test_reg_sign_int8  () { test_reg_sign<int8_t >(); }
void SignTest::test_reg_sign_int16 () { test_reg_sign<int16_t>(); }
void SignTest::test_reg_sign_int32 () { test_reg_sign<int32_t>(); }
void SignTest::test_reg_sign_int64 () { test_reg_sign<int64_t>(); }
void SignTest::test_reg_sign_float () { test_reg_sign<float  >(); }
void SignTest::test_reg_sign_double() { test_reg_sign<double >(); }

template <typename T>
void SignTest::test_Reg_sign()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::iota(inputs1, inputs1 + N, -N/2);

		std::mt19937 g;
		std::shuffle(inputs1, inputs1 + N, g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Msk<N> m  = mipp::sign(r1);
		mipp::Reg<T> r2 = mipp::toreg<N>(m.m);

		for (auto i = 0; i < N; i++)
		{
			if (inputs1[i] >= 0)
				CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r2 +i));
			else
				CPPUNIT_ASSERT(*((T*)&r2 +i) != (T)0);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SignTest::test_Reg_sign_int8  () { test_Reg_sign<int8_t >(); }
void SignTest::test_Reg_sign_int16 () { test_Reg_sign<int16_t>(); }
void SignTest::test_Reg_sign_int32 () { test_Reg_sign<int32_t>(); }
void SignTest::test_Reg_sign_int64 () { test_Reg_sign<int64_t>(); }
void SignTest::test_Reg_sign_float () { test_Reg_sign<float  >(); }
void SignTest::test_Reg_sign_double() { test_Reg_sign<double >(); }
