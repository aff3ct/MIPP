#include <exception>
#include <algorithm>
#include <mipp.h>

#include "HmulTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(HmulTest);

void 
HmulTest::setUp()
{
}

void 
HmulTest::tearDown()
{
}

template <typename T>
void HmulTest::test_reg_hmul_int()
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
			auto val = mipp::hmul<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res *= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HmulTest::test_reg_hmul_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(-2, 2);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::hmul<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res *= inputs1[i];

			auto diff = std::abs(res - val);
			CPPUNIT_ASSERT(diff < (T)0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HmulTest::test_reg_hmul_int8  () { test_reg_hmul_int <int8_t >(); }
void HmulTest::test_reg_hmul_int16 () { test_reg_hmul_int <int16_t>(); }
void HmulTest::test_reg_hmul_int32 () { test_reg_hmul_int <int32_t>(); }
void HmulTest::test_reg_hmul_int64 () { test_reg_hmul_int <int64_t>(); }
void HmulTest::test_reg_hmul_float () { test_reg_hmul_real<float  >(); }
void HmulTest::test_reg_hmul_double() { test_reg_hmul_real<double >(); }

template <typename T>
void HmulTest::test_Reg_hmul_int()
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
			auto val = mipp::hmul(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res *= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

template <typename T>
void HmulTest::test_Reg_hmul_real()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_real_distribution<T> dis(-2, 2);

		for (auto i = 0; i < 100; i++)
		{
			for (auto i = 0; i < N; i++)
				inputs1[i] = dis(g);

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::hmul(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res *= inputs1[i];

			auto diff = std::abs(res - val);

			CPPUNIT_ASSERT(diff < (T)0.001);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void HmulTest::test_Reg_hmul_int8  () { test_Reg_hmul_int <int8_t >(); }
void HmulTest::test_Reg_hmul_int16 () { test_Reg_hmul_int <int16_t>(); }
void HmulTest::test_Reg_hmul_int32 () { test_Reg_hmul_int <int32_t>(); }
void HmulTest::test_Reg_hmul_int64 () { test_Reg_hmul_int <int64_t>(); }
void HmulTest::test_Reg_hmul_float () { test_Reg_hmul_real<float  >(); }
void HmulTest::test_Reg_hmul_double() { test_Reg_hmul_real<double >(); }
