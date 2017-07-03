#ifndef HIGHTEST_HPP_
#define HIGHTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class HighTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(HighTest);

	CPPUNIT_TEST(test_reg_high_int8);
	CPPUNIT_TEST(test_reg_high_int16);
	CPPUNIT_TEST(test_reg_high_int32);
	CPPUNIT_TEST(test_reg_high_int64);
	CPPUNIT_TEST(test_reg_high_float);
	CPPUNIT_TEST(test_reg_high_double);

	CPPUNIT_TEST(test_Reg_high_int8);
	CPPUNIT_TEST(test_Reg_high_int16);
	CPPUNIT_TEST(test_Reg_high_int32);
	CPPUNIT_TEST(test_Reg_high_int64);
	CPPUNIT_TEST(test_Reg_high_float);
	CPPUNIT_TEST(test_Reg_high_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_high();
	void test_reg_high_int8();
	void test_reg_high_int16();
	void test_reg_high_int32();
	void test_reg_high_int64();
	void test_reg_high_float();
	void test_reg_high_double();

	template <typename T>
	void test_Reg_high();
	void test_Reg_high_int8();
	void test_Reg_high_int16();
	void test_Reg_high_int32();
	void test_Reg_high_int64();
	void test_Reg_high_float();
	void test_Reg_high_double();
};

#endif  // HIGHTEST_HPP_
