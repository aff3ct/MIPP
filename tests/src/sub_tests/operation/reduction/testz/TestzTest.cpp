#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "TestzTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestzTest);

void
TestzTest::setUp()
{
}

void
TestzTest::tearDown()
{
}

template <typename T>
void TestzTest::test_reg_testz_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)std::numeric_limits<T>::min(), (T)std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g);

				switch (j%3)
				{
					case 0: inputs2[i] = dis(g);      break;
					case 1: inputs2[i] = ~inputs1[i]; break;
					case 2: inputs2[i] = 0;           break;
				}
			}

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::load<T>(inputs2);
			auto val = mipp::testz<T>(r1, r2);

			for (auto i = 0; i < N; i++)
				inputs2[i] &= inputs1[i];

			auto res = inputs2[0];
			for (auto i = 1; i < N; i++)
				res |= inputs2[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_reg_testz_int8 (){ test_reg_testz_int <int8_t >(); }
void TestzTest::test_reg_testz_int16(){ test_reg_testz_int <int16_t>(); }
void TestzTest::test_reg_testz_int32(){ test_reg_testz_int <int32_t>(); }
void TestzTest::test_reg_testz_int64(){ test_reg_testz_int <int64_t>(); }

template <typename T>
void TestzTest::test_Reg_testz_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)std::numeric_limits<T>::min(), (T)std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g);

				switch (j%3)
				{
					case 0:  inputs2[i] = dis(g);      break;
					case 1:  inputs2[i] = ~inputs1[i]; break;
					case 2:  inputs2[i] = 0;           break;
					default: inputs2[i] = 0;           break;
				}
			}

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = inputs2;
			auto val = mipp::testz(r1, r2);

			for (auto i = 0; i < N; i++)
				inputs2[i] &= inputs1[i];

			auto res = inputs2[0];
			for (auto i = 1; i < N; i++)
				res |= inputs2[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_Reg_testz_int8 (){ test_Reg_testz_int <int8_t >(); }
void TestzTest::test_Reg_testz_int16(){ test_Reg_testz_int <int16_t>(); }
void TestzTest::test_Reg_testz_int32(){ test_Reg_testz_int <int32_t>(); }
void TestzTest::test_Reg_testz_int64(){ test_Reg_testz_int <int64_t>(); }

template <typename T>
void TestzTest::test_msk_testz_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(0, 1);

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g) ? true : false;

				switch (j%3)
				{
					case 0: inputs2[i] = dis(g) ? true : false; break;
					case 1: inputs2[i] = !inputs1[i];           break;
					case 2: inputs2[i] = false;                 break;
				}
			}

			mipp::msk r1 = mipp::set<N>(inputs1);
			mipp::msk r2 = mipp::set<N>(inputs2);
			auto val = mipp::testz<N>(r1, r2);

			for (auto i = 0; i < N; i++)
				inputs2[i] &= inputs1[i];

			auto res = inputs2[0];
			for (auto i = 1; i < N; i++)
				res |= inputs2[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_msk_testz_int8 (){ test_msk_testz_int <int8_t >(); }
void TestzTest::test_msk_testz_int16(){ test_msk_testz_int <int16_t>(); }
void TestzTest::test_msk_testz_int32(){ test_msk_testz_int <int32_t>(); }
void TestzTest::test_msk_testz_int64(){ test_msk_testz_int <int64_t>(); }

template <typename T>
void TestzTest::test_Msk_testz_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N], inputs2[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(0, 1);

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				inputs1[i] = dis(g) ? true : false;

				switch (j%3)
				{
					case 0:  inputs2[i] = dis(g) ? true : false; break;
					case 1:  inputs2[i] = !inputs1[i];           break;
					case 2:  inputs2[i] = false;                 break;
					default: inputs2[i] = false;                 break;
				}
			}

			mipp::Msk<N> r1 = inputs1;
			mipp::Msk<N> r2 = inputs2;
			auto val = mipp::testz(r1, r2);

			for (auto i = 0; i < N; i++)
				inputs2[i] &= inputs1[i];

			auto res = inputs2[0];
			for (auto i = 1; i < N; i++)
				res |= inputs2[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_Msk_testz_int8 (){ test_Msk_testz_int <int8_t >(); }
void TestzTest::test_Msk_testz_int16(){ test_Msk_testz_int <int16_t>(); }
void TestzTest::test_Msk_testz_int32(){ test_Msk_testz_int <int32_t>(); }
void TestzTest::test_Msk_testz_int64(){ test_Msk_testz_int <int64_t>(); }

template <typename T>
void TestzTest::test_reg_testz1_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)std::numeric_limits<T>::min(), (T)std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				switch (j%2)
				{
					case 0:  inputs1[i] = dis(g); break;
					case 1:  inputs1[i] = 0;      break;
					default: inputs1[i] = 0;      break;
				}
			}

			mipp::reg r1 = mipp::load<T>(inputs1);
			auto val = mipp::testz<T>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res |= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_reg_testz1_int8 (){ test_reg_testz1_int <int8_t >(); }
void TestzTest::test_reg_testz1_int16(){ test_reg_testz1_int <int16_t>(); }
void TestzTest::test_reg_testz1_int32(){ test_reg_testz1_int <int32_t>(); }
void TestzTest::test_reg_testz1_int64(){ test_reg_testz1_int <int64_t>(); }

template <typename T>
void TestzTest::test_Reg_testz1_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		T inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis((T)std::numeric_limits<T>::min(), (T)std::numeric_limits<T>::max());

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				switch (j%2)
				{
					case 0:  inputs1[i] = dis(g); break;
					case 1:  inputs1[i] = 0;      break;
					default: inputs1[i] = 0;      break;
				}
			}

			mipp::Reg<T> r1 = inputs1;
			auto val = mipp::testz(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res |= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_Reg_testz1_int8 (){ test_Reg_testz1_int <int8_t >(); }
void TestzTest::test_Reg_testz1_int16(){ test_Reg_testz1_int <int16_t>(); }
void TestzTest::test_Reg_testz1_int32(){ test_Reg_testz1_int <int32_t>(); }
void TestzTest::test_Reg_testz1_int64(){ test_Reg_testz1_int <int64_t>(); }

template <typename T>
void TestzTest::test_msk_testz1_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(0, 1);

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				switch (j%3)
				{
					case 0:  inputs1[i] = dis(g) ? true : false; break;
					case 1:  inputs1[i] = true;                  break;
					case 2:  inputs1[i] = false;                 break;
					default: inputs1[i] = false;                 break;
				}
			}

			mipp::msk r1 = mipp::set<N>(inputs1);
			auto val = mipp::testz<N>(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res |= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_msk_testz1_int8 (){ test_msk_testz1_int <int8_t >(); }
void TestzTest::test_msk_testz1_int16(){ test_msk_testz1_int <int16_t>(); }
void TestzTest::test_msk_testz1_int32(){ test_msk_testz1_int <int32_t>(); }
void TestzTest::test_msk_testz1_int64(){ test_msk_testz1_int <int64_t>(); }

template <typename T>
void TestzTest::test_Msk_testz1_int()
{
	try
	{
		constexpr int N = mipp::N<T>();
		bool inputs1[N];
		std::mt19937 g;
		std::uniform_int_distribution<T> dis(0, 1);

		for (auto j = 0; j < 100; j++)
		{
			for (auto i = 0; i < N; i++)
			{
				switch (j%3)
				{
					case 0:  inputs1[i] = dis(g) ? true : false; break;
					case 1:  inputs1[i] = true;                  break;
					case 2:  inputs1[i] = false;                 break;
					default: inputs1[i] = false;                 break;
				}
			}

			mipp::Msk<N> r1 = inputs1;
			auto val = mipp::testz(r1);

			auto res = inputs1[0];
			for (auto i = 1; i < N; i++)
				res |= inputs1[i];

			CPPUNIT_ASSERT_EQUAL(res == 0, val);
		}
	}
	catch(std::exception &e)
	{
		CPPUNIT_FAIL(e.what());
	}
}

void TestzTest::test_Msk_testz1_int8 (){ test_Msk_testz1_int <int8_t >(); }
void TestzTest::test_Msk_testz1_int16(){ test_Msk_testz1_int <int16_t>(); }
void TestzTest::test_Msk_testz1_int32(){ test_Msk_testz1_int <int32_t>(); }
void TestzTest::test_Msk_testz1_int64(){ test_Msk_testz1_int <int64_t>(); }

