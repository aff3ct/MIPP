#ifndef RSHIFTTEST_HPP_
#define RSHIFTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RshiftTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RshiftTest);

	CPPUNIT_TEST(test_reg_rshift_int8);
	CPPUNIT_TEST(test_reg_rshift_int16);
	CPPUNIT_TEST(test_reg_rshift_int32);
	CPPUNIT_TEST(test_reg_rshift_int64);

	CPPUNIT_TEST(test_Reg_rshift_int8);
	CPPUNIT_TEST(test_Reg_rshift_int16);
	CPPUNIT_TEST(test_Reg_rshift_int32);
	CPPUNIT_TEST(test_Reg_rshift_int64);

	CPPUNIT_TEST(test_msk_rshift_int8);
	CPPUNIT_TEST(test_msk_rshift_int16);
	CPPUNIT_TEST(test_msk_rshift_int32);
	CPPUNIT_TEST(test_msk_rshift_int64);

	CPPUNIT_TEST(test_Msk_rshift_int8);
	CPPUNIT_TEST(test_Msk_rshift_int16);
	CPPUNIT_TEST(test_Msk_rshift_int32);
	CPPUNIT_TEST(test_Msk_rshift_int64);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_reg_rshift_int8();
	void test_reg_rshift_int16();
	void test_reg_rshift_int32();
	void test_reg_rshift_int64();

	void test_Reg_rshift_int8();
	void test_Reg_rshift_int16();
	void test_Reg_rshift_int32();
	void test_Reg_rshift_int64();

	void test_msk_rshift_int8();
	void test_msk_rshift_int16();
	void test_msk_rshift_int32();
	void test_msk_rshift_int64();

	void test_Msk_rshift_int8();
	void test_Msk_rshift_int16();
	void test_Msk_rshift_int32();
	void test_Msk_rshift_int64();
};

#endif  // RSHIFTTEST_HPP_
