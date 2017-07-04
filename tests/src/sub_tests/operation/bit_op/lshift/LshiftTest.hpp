#ifndef LSHIFTTEST_HPP_
#define LSHIFTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class LshiftTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(LshiftTest);

#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_lshift_int8);
	CPPUNIT_TEST(test_Reg_lshift_int8);
	CPPUNIT_TEST(test_msk_lshift_int8);
	CPPUNIT_TEST(test_Msk_lshift_int8);

	CPPUNIT_TEST(test_reg_lshift_int16);
	CPPUNIT_TEST(test_Reg_lshift_int16);
	CPPUNIT_TEST(test_msk_lshift_int16);
	CPPUNIT_TEST(test_Msk_lshift_int16);
#endif

	CPPUNIT_TEST(test_reg_lshift_int32);
	CPPUNIT_TEST(test_Reg_lshift_int32);
	CPPUNIT_TEST(test_msk_lshift_int32);
	CPPUNIT_TEST(test_Msk_lshift_int32);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_lshift_int64);
	CPPUNIT_TEST(test_Reg_lshift_int64);
	CPPUNIT_TEST(test_msk_lshift_int64);
	CPPUNIT_TEST(test_Msk_lshift_int64);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_reg_lshift_int8();
	void test_reg_lshift_int16();
	void test_reg_lshift_int32();
	void test_reg_lshift_int64();

	void test_Reg_lshift_int8();
	void test_Reg_lshift_int16();
	void test_Reg_lshift_int32();
	void test_Reg_lshift_int64();

	void test_msk_lshift_int8();
	void test_msk_lshift_int16();
	void test_msk_lshift_int32();
	void test_msk_lshift_int64();

	void test_Msk_lshift_int8();
	void test_Msk_lshift_int16();
	void test_Msk_lshift_int32();
	void test_Msk_lshift_int64();
};

#endif  // LSHIFTTEST_HPP_
