#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <mipp.h>

#include "RshiftTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(RshiftTest);

void
RshiftTest::setUp()
{
}

void
RshiftTest::tearDown()
{
}

template <typename T, int n = (sizeof(T) * 8 -1)>
struct reg_rshift
{
	static void test()
	{
		reg_rshift<T,n-1>::test();
		try
		{
			T inputs1[mipp::N<T>()];
			std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());

			std::mt19937 g;
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::reg r1 = mipp::load<T>(inputs1);
			mipp::reg r2 = mipp::rshift<T>(r1, n);

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = inputs1[i] >> n;
				CPPUNIT_ASSERT_EQUAL(res, *((T*)&r2 +i));
			}
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
};

template <typename T>
struct reg_rshift<T,-1>
{
	static void test() {}
};

void RshiftTest::test_reg_rshift_int8 () { reg_rshift<int8_t >::test(); }
void RshiftTest::test_reg_rshift_int16() { reg_rshift<int16_t>::test(); }
void RshiftTest::test_reg_rshift_int32() { reg_rshift<int32_t>::test(); }
void RshiftTest::test_reg_rshift_int64() { reg_rshift<int64_t>::test(); }

template <typename T, int n = (sizeof(T) * 8 -1)>
struct Reg_rshift
{
	static void test()
	{
		Reg_rshift<T,n-1>::test();
		try
		{
			T inputs1[mipp::N<T>()];
			std::iota(inputs1, inputs1 + mipp::N<T>(), std::numeric_limits<T>::max() - mipp::N<T>());

			std::mt19937 g;
			std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

			mipp::Reg<T> r1 = inputs1;
			mipp::Reg<T> r2 = r1 >> n;

			for (auto i = 0; i < mipp::N<T>(); i++)
			{
				T res = inputs1[i] >> n;
				CPPUNIT_ASSERT_EQUAL(res, r2[i]);
			}
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
};

template <typename T>
struct Reg_rshift<T,-1>
{
	static void test() {}
};

void RshiftTest::test_Reg_rshift_int8 () { Reg_rshift<int8_t >::test(); }
void RshiftTest::test_Reg_rshift_int16() { Reg_rshift<int16_t>::test(); }
void RshiftTest::test_Reg_rshift_int32() { Reg_rshift<int32_t>::test(); }
void RshiftTest::test_Reg_rshift_int64() { Reg_rshift<int64_t>::test(); }

template <typename T, int n = mipp::N<T>()>
struct msk_rshift
{
	static void test()
	{
		msk_rshift<T,n-1>::test();
		try
		{
			constexpr int N = mipp::N<T>();
			bool inputs1[N], inputs2[N];
			std::mt19937 g;
			std::uniform_int_distribution<uint8_t> dis(0, 1);

			for (auto t = 0; t < 100; t++)
			{
				for (auto i = 0; i < N; i++)
					inputs1[i] = dis(g) ? true : false;

				std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

				mipp::msk m1 = mipp::set<N>(inputs1);
				mipp::msk m2 = mipp::rshift<N>(m1, n);

				std::fill(inputs2, inputs2 + N, 0);
				for (auto i = 0; i < N - n; i++)
					inputs2[i] = inputs1[i +n];

				mipp::reg r = mipp::toreg<N>(m2);

				for (auto i = 0; i < N; i++)
				{
					if (inputs2[i])
						CPPUNIT_ASSERT(*((T*)&r +i) != (T)0);
					else
						CPPUNIT_ASSERT_EQUAL((T)0, *((T*)&r +i));
				}
			}
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
};

template <typename T>
struct msk_rshift<T,-1>
{
	static void test() {}
};

void RshiftTest::test_msk_rshift_int8 () { msk_rshift<int8_t >::test(); }
void RshiftTest::test_msk_rshift_int16() { msk_rshift<int16_t>::test(); }
void RshiftTest::test_msk_rshift_int32() { msk_rshift<int32_t>::test(); }
void RshiftTest::test_msk_rshift_int64() { msk_rshift<int64_t>::test(); }

template <typename T, int n = mipp::N<T>()>
struct Msk_rshift
{
	static void test()
	{
		Msk_rshift<T,n-1>::test();
		try
		{
			constexpr int N = mipp::N<T>();
			bool inputs1[N], inputs2[N];
			std::mt19937 g;
			std::uniform_int_distribution<uint8_t> dis(0, 1);

			for (auto t = 0; t < 100; t++)
			{
				for (auto i = 0; i < N; i++)
					inputs1[i] = dis(g) ? true : false;

				std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);

				mipp::Msk<N> m1 = inputs1;
				mipp::Msk<N> m2 = m1 >> n;

				std::fill(inputs2, inputs2 + N, 0);
				for (auto i = 0; i < N - n; i++)
					inputs2[i] = inputs1[i +n];

				for (auto i = 0; i < N; i++)
				{
					CPPUNIT_ASSERT_EQUAL(inputs2[i], m2[i]);
				}
			}
		}
		catch(std::exception &e)
		{
			CPPUNIT_FAIL(e.what());
		}
	}
};

template <typename T>
struct Msk_rshift<T,-1>
{
	static void test() {}
};

void RshiftTest::test_Msk_rshift_int8 () { Msk_rshift<int8_t >::test(); }
void RshiftTest::test_Msk_rshift_int16() { Msk_rshift<int16_t>::test(); }
void RshiftTest::test_Msk_rshift_int32() { Msk_rshift<int32_t>::test(); }
void RshiftTest::test_Msk_rshift_int64() { Msk_rshift<int64_t>::test(); }

