#ifndef CMPGETEST_HPP_
#define CMPGETEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpgeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpgeTest);

	CPPUNIT_TEST(test_reg_cmpge_int8);
	CPPUNIT_TEST(test_reg_cmpge_int16);
	CPPUNIT_TEST(test_reg_cmpge_int32);
	CPPUNIT_TEST(test_reg_cmpge_int64);
	CPPUNIT_TEST(test_reg_cmpge_float);
	CPPUNIT_TEST(test_reg_cmpge_double);

	CPPUNIT_TEST(test_Reg_cmpge_int8);
	CPPUNIT_TEST(test_Reg_cmpge_int16);
	CPPUNIT_TEST(test_Reg_cmpge_int32);
	CPPUNIT_TEST(test_Reg_cmpge_int64);
	CPPUNIT_TEST(test_Reg_cmpge_float);
	CPPUNIT_TEST(test_Reg_cmpge_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpge();
	void test_reg_cmpge_int8();
	void test_reg_cmpge_int16();
	void test_reg_cmpge_int32();
	void test_reg_cmpge_int64();
	void test_reg_cmpge_float();
	void test_reg_cmpge_double();

	template <typename T>
	void test_Reg_cmpge();
	void test_Reg_cmpge_int8();
	void test_Reg_cmpge_int16();
	void test_Reg_cmpge_int32();
	void test_Reg_cmpge_int64();
	void test_Reg_cmpge_float();
	void test_Reg_cmpge_double();
};

#endif  // CMPGETEST_HPP_
