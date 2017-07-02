#ifndef CMASK2TEST_HPP_
#define CMASK2TEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class Cmask2Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Cmask2Test);

	CPPUNIT_TEST(test_reg_cmask2_int8);
	CPPUNIT_TEST(test_reg_cmask2_int16);
	CPPUNIT_TEST(test_reg_cmask2_int32);
	CPPUNIT_TEST(test_reg_cmask2_int64);
	CPPUNIT_TEST(test_reg_cmask2_float);
	CPPUNIT_TEST(test_reg_cmask2_double);

	CPPUNIT_TEST(test_Reg_cmask2_int8);
	CPPUNIT_TEST(test_Reg_cmask2_int16);
	CPPUNIT_TEST(test_Reg_cmask2_int32);
	CPPUNIT_TEST(test_Reg_cmask2_int64);
	CPPUNIT_TEST(test_Reg_cmask2_float);
	CPPUNIT_TEST(test_Reg_cmask2_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmask2();
	void test_reg_cmask2_int8();
	void test_reg_cmask2_int16();
	void test_reg_cmask2_int32();
	void test_reg_cmask2_int64();
	void test_reg_cmask2_float();
	void test_reg_cmask2_double();

	template <typename T>
	void test_Reg_cmask2();
	void test_Reg_cmask2_int8();
	void test_Reg_cmask2_int16();
	void test_Reg_cmask2_int32();
	void test_Reg_cmask2_int64();
	void test_Reg_cmask2_float();
	void test_Reg_cmask2_double();
};

#endif  // CMASK2TEST_HPP_
