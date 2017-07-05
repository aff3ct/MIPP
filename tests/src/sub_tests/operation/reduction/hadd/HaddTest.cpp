#include <exception>
#include <algorithm>
#include <mipp.h>

#include "HaddTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(HaddTest);

void 
HaddTest::setUp()
{
}

void 
HaddTest::tearDown()
{
}

template <typename T>
void HaddTest::test_reg_hadd_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)-10, (T)10);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hadd<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res += inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HaddTest::test_reg_hadd_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(-100, 100);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hadd<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res += inputs1[i];

			auto diff = std::abs(res - val);
			CPPUNIT_ASSERT(diff < (T)0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HaddTest::test_reg_hadd_int8  () { test_reg_hadd_int <int8_t >(); }
void HaddTest::test_reg_hadd_int16 () { test_reg_hadd_int <int16_t>(); }
void HaddTest::test_reg_hadd_int32 () { test_reg_hadd_int <int32_t>(); }
void HaddTest::test_reg_hadd_int64 () { test_reg_hadd_int <int64_t>(); }
void HaddTest::test_reg_hadd_float () { test_reg_hadd_real<float  >(); }
void HaddTest::test_reg_hadd_double() { test_reg_hadd_real<double >(); }

template <typename T>
void HaddTest::test_Reg_hadd_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)-10, (T)10);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hadd(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res += inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HaddTest::test_Reg_hadd_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(-100, 100);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hadd(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res += inputs1[i];

			auto diff = std::abs(res - val);
			CPPUNIT_ASSERT(diff < (T)0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HaddTest::test_Reg_hadd_int8  () { test_Reg_hadd_int <int8_t >(); }
void HaddTest::test_Reg_hadd_int16 () { test_Reg_hadd_int <int16_t>(); }
void HaddTest::test_Reg_hadd_int32 () { test_Reg_hadd_int <int32_t>(); }
void HaddTest::test_Reg_hadd_int64 () { test_Reg_hadd_int <int64_t>(); }
void HaddTest::test_Reg_hadd_float () { test_Reg_hadd_real<float  >(); }
void HaddTest::test_Reg_hadd_double() { test_Reg_hadd_real<double >(); }
