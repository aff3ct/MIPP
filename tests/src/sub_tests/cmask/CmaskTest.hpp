#ifndef CMASKTEST_HPP_
#define CMASKTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmaskTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmaskTest);

	CPPUNIT_TEST(test_reg_cmask_int8);
	CPPUNIT_TEST(test_reg_cmask_int16);
	CPPUNIT_TEST(test_reg_cmask_int32);
	CPPUNIT_TEST(test_reg_cmask_int64);
	CPPUNIT_TEST(test_reg_cmask_float);
	CPPUNIT_TEST(test_reg_cmask_double);

	CPPUNIT_TEST(test_Reg_cmask_int8);
	CPPUNIT_TEST(test_Reg_cmask_int16);
	CPPUNIT_TEST(test_Reg_cmask_int32);
	CPPUNIT_TEST(test_Reg_cmask_int64);
	CPPUNIT_TEST(test_Reg_cmask_float);
	CPPUNIT_TEST(test_Reg_cmask_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmask();
	void test_reg_cmask_int8();
	void test_reg_cmask_int16();
	void test_reg_cmask_int32();
	void test_reg_cmask_int64();
	void test_reg_cmask_float();
	void test_reg_cmask_double();

	template <typename T>
	void test_Reg_cmask();
	void test_Reg_cmask_int8();
	void test_Reg_cmask_int16();
	void test_Reg_cmask_int32();
	void test_Reg_cmask_int64();
	void test_Reg_cmask_float();
	void test_Reg_cmask_double();
};

#endif  // CMASKTEST_HPP_
