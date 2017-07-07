#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "HminTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(HminTest);

void 
HminTest::setUp()
{
}

void 
HminTest::tearDown()
{
}

template <typename T>
void HminTest::test_reg_hmin_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hmin<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::min(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HminTest::test_reg_hmin_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hmin<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::min(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HminTest::test_reg_hmin_int8  () { test_reg_hmin_int <int8_t >(); }
void HminTest::test_reg_hmin_int16 () { test_reg_hmin_int <int16_t>(); }
void HminTest::test_reg_hmin_int32 () { test_reg_hmin_int <int32_t>(); }
void HminTest::test_reg_hmin_int64 () { test_reg_hmin_int <int64_t>(); }
void HminTest::test_reg_hmin_float () { test_reg_hmin_real<float  >(); }
void HminTest::test_reg_hmin_double() { test_reg_hmin_real<double >(); }

template <typename T>
void HminTest::test_Reg_hmin_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hmin(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::min(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HminTest::test_Reg_hmin_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hmin(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::min(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HminTest::test_Reg_hmin_int8  () { test_Reg_hmin_int <int8_t >(); }
void HminTest::test_Reg_hmin_int16 () { test_Reg_hmin_int <int16_t>(); }
void HminTest::test_Reg_hmin_int32 () { test_Reg_hmin_int <int32_t>(); }
void HminTest::test_Reg_hmin_int64 () { test_Reg_hmin_int <int64_t>(); }
void HminTest::test_Reg_hmin_float () { test_Reg_hmin_real<float  >(); }
void HminTest::test_Reg_hmin_double() { test_Reg_hmin_real<double >(); }
