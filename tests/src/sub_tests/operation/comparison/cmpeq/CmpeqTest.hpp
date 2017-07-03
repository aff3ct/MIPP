#ifndef CMPEQTEST_HPP_
#define CMPEQTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpeqTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpeqTest);

	CPPUNIT_TEST(test_reg_cmpeq_int8);
	CPPUNIT_TEST(test_reg_cmpeq_int16);
	CPPUNIT_TEST(test_reg_cmpeq_int32);
	CPPUNIT_TEST(test_reg_cmpeq_int64);
	CPPUNIT_TEST(test_reg_cmpeq_float);
	CPPUNIT_TEST(test_reg_cmpeq_double);

	CPPUNIT_TEST(test_Reg_cmpeq_int8);
	CPPUNIT_TEST(test_Reg_cmpeq_int16);
	CPPUNIT_TEST(test_Reg_cmpeq_int32);
	CPPUNIT_TEST(test_Reg_cmpeq_int64);
	CPPUNIT_TEST(test_Reg_cmpeq_float);
	CPPUNIT_TEST(test_Reg_cmpeq_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpeq();
	void test_reg_cmpeq_int8();
	void test_reg_cmpeq_int16();
	void test_reg_cmpeq_int32();
	void test_reg_cmpeq_int64();
	void test_reg_cmpeq_float();
	void test_reg_cmpeq_double();

	template <typename T>
	void test_Reg_cmpeq();
	void test_Reg_cmpeq_int8();
	void test_Reg_cmpeq_int16();
	void test_Reg_cmpeq_int32();
	void test_Reg_cmpeq_int64();
	void test_Reg_cmpeq_float();
	void test_Reg_cmpeq_double();
};

#endif  // CMPEQTEST_HPP_
