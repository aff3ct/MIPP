#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "HmaxTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(HmaxTest);

void 
HmaxTest::setUp()
{
}

void 
HmaxTest::tearDown()
{
}

template <typename T>
void HmaxTest::test_reg_hmax_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hmax<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::max(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HmaxTest::test_reg_hmax_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hmax<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::max(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HmaxTest::test_reg_hmax_int8  () { test_reg_hmax_int <int8_t >(); }
void HmaxTest::test_reg_hmax_int16 () { test_reg_hmax_int <int16_t>(); }
void HmaxTest::test_reg_hmax_int32 () { test_reg_hmax_int <int32_t>(); }
void HmaxTest::test_reg_hmax_int64 () { test_reg_hmax_int <int64_t>(); }
void HmaxTest::test_reg_hmax_float () { test_reg_hmax_real<float  >(); }
void HmaxTest::test_reg_hmax_double() { test_reg_hmax_real<double >(); }

template <typename T>
void HmaxTest::test_Reg_hmax_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hmax(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::max(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HmaxTest::test_Reg_hmax_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hmax(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res = std::max(res, inputs1[i]);

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HmaxTest::test_Reg_hmax_int8  () { test_Reg_hmax_int <int8_t >(); }
void HmaxTest::test_Reg_hmax_int16 () { test_Reg_hmax_int <int16_t>(); }
void HmaxTest::test_Reg_hmax_int32 () { test_Reg_hmax_int <int32_t>(); }
void HmaxTest::test_Reg_hmax_int64 () { test_Reg_hmax_int <int64_t>(); }
void HmaxTest::test_Reg_hmax_float () { test_Reg_hmax_real<float  >(); }
void HmaxTest::test_Reg_hmax_double() { test_Reg_hmax_real<double >(); }
