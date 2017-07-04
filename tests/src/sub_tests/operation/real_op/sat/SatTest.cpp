#include <exception>
#include <algorithm>
#include <random>
#include <mipp.h>

#include "SatTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(SatTest);

void 
SatTest::setUp()
{
}

void 
SatTest::tearDown()
{
}

template <typename T>
void SatTest::test_reg_sat_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::load<T>(inputs1);

		for (auto i = 0; i < 100; i++)
		{
			T n1 = dis(g);
			T n2 = dis(g);

			T m = std::min<T>(n1, n2);
			T M = std::max<T>(n1, n2);

			mipp::reg r2 = mipp::sat<T>(r1, m, M);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::min<T>(std::max<T>(inputs1[i], m), M);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void SatTest::test_reg_sat_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::reg r1 = mipp::load<T>(inputs1);

		for (auto i = 0; i < 100; i++)
		{
			T n1 = dis(g);
			T n2 = dis(g);

			T m = std::min<T>(n1, n2);
			T M = std::max<T>(n1, n2);

			mipp::reg r2 = mipp::sat<T>(r1, m, M);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::min<T>(std::max<T>(inputs1[i], m), M);
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SatTest::test_reg_sat_int8  () { test_reg_sat_int <int8_t >(); }
void SatTest::test_reg_sat_int16 () { test_reg_sat_int <int16_t>(); }
void SatTest::test_reg_sat_int32 () { test_reg_sat_int <int32_t>(); }
void SatTest::test_reg_sat_int64 () { test_reg_sat_int <int64_t>(); }
void SatTest::test_reg_sat_float () { test_reg_sat_real<float  >(); }
void SatTest::test_reg_sat_double() { test_reg_sat_real<double >(); }

template <typename T>
void SatTest::test_Reg_sat_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;

		for (auto i = 0; i < 100; i++)
		{
			T n1 = dis(g);
			T n2 = dis(g);

			T m = std::min<T>(n1, n2);
			T M = std::max<T>(n1, n2);

			mipp::Reg<T> r2 = mipp::sat(r1, m, M);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::min<T>(std::max<T>(inputs1[i], m), M);
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void SatTest::test_Reg_sat_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < N; i++)
			inputs1[i] = dis(g);

		mipp::Reg<T> r1 = inputs1;

		for (auto i = 0; i < 100; i++)
		{
			T n1 = dis(g);
			T n2 = dis(g);

			T m = std::min<T>(n1, n2);
			T M = std::max<T>(n1, n2);

			mipp::Reg<T> r2 = mipp::sat(r1, m, M);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = std::min<T>(std::max<T>(inputs1[i], m), M);
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
			}
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void SatTest::test_Reg_sat_int8  () { test_Reg_sat_int <int8_t >(); }
void SatTest::test_Reg_sat_int16 () { test_Reg_sat_int <int16_t>(); }
void SatTest::test_Reg_sat_int32 () { test_Reg_sat_int <int32_t>(); }
void SatTest::test_Reg_sat_int64 () { test_Reg_sat_int <int64_t>(); }
void SatTest::test_Reg_sat_float () { test_Reg_sat_real<float  >(); }
void SatTest::test_Reg_sat_double() { test_Reg_sat_real<double >(); }
