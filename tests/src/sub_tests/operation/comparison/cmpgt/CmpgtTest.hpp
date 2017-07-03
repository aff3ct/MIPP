#ifndef CMPGTTEST_HPP_
#define CMPGTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpgtTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpgtTest);

	CPPUNIT_TEST(test_reg_cmpgt_int8);
	CPPUNIT_TEST(test_reg_cmpgt_int16);
	CPPUNIT_TEST(test_reg_cmpgt_int32);
	CPPUNIT_TEST(test_reg_cmpgt_int64);
	CPPUNIT_TEST(test_reg_cmpgt_float);
	CPPUNIT_TEST(test_reg_cmpgt_double);

	CPPUNIT_TEST(test_Reg_cmpgt_int8);
	CPPUNIT_TEST(test_Reg_cmpgt_int16);
	CPPUNIT_TEST(test_Reg_cmpgt_int32);
	CPPUNIT_TEST(test_Reg_cmpgt_int64);
	CPPUNIT_TEST(test_Reg_cmpgt_float);
	CPPUNIT_TEST(test_Reg_cmpgt_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpgt();
	void test_reg_cmpgt_int8();
	void test_reg_cmpgt_int16();
	void test_reg_cmpgt_int32();
	void test_reg_cmpgt_int64();
	void test_reg_cmpgt_float();
	void test_reg_cmpgt_double();

	template <typename T>
	void test_Reg_cmpgt();
	void test_Reg_cmpgt_int8();
	void test_Reg_cmpgt_int16();
	void test_Reg_cmpgt_int32();
	void test_Reg_cmpgt_int64();
	void test_Reg_cmpgt_float();
	void test_Reg_cmpgt_double();
};

#endif  // CMPGTTEST_HPP_
