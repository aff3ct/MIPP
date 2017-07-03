#ifndef CMPLTTEST_HPP_
#define CMPLTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpltTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpltTest);

	CPPUNIT_TEST(test_reg_cmplt_int8);
	CPPUNIT_TEST(test_reg_cmplt_int16);
	CPPUNIT_TEST(test_reg_cmplt_int32);
//	CPPUNIT_TEST(test_reg_cmplt_int64);
	CPPUNIT_TEST(test_reg_cmplt_float);
	CPPUNIT_TEST(test_reg_cmplt_double);

	CPPUNIT_TEST(test_Reg_cmplt_int8);
	CPPUNIT_TEST(test_Reg_cmplt_int16);
	CPPUNIT_TEST(test_Reg_cmplt_int32);
//	CPPUNIT_TEST(test_Reg_cmplt_int64);
	CPPUNIT_TEST(test_Reg_cmplt_float);
	CPPUNIT_TEST(test_Reg_cmplt_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmplt();
	void test_reg_cmplt_int8();
	void test_reg_cmplt_int16();
	void test_reg_cmplt_int32();
	void test_reg_cmplt_int64();
	void test_reg_cmplt_float();
	void test_reg_cmplt_double();

	template <typename T>
	void test_Reg_cmplt();
	void test_Reg_cmplt_int8();
	void test_Reg_cmplt_int16();
	void test_Reg_cmplt_int32();
	void test_Reg_cmplt_int64();
	void test_Reg_cmplt_float();
	void test_Reg_cmplt_double();
};

#endif  // CMPLTTEST_HPP_
