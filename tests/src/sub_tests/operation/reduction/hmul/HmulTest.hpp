#ifndef HMULTEST_HPP_
#define HMULTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class HmulTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(HmulTest);

	CPPUNIT_TEST(test_reg_hmul_float);
	CPPUNIT_TEST(test_Reg_hmul_float);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_hmul_double);
	CPPUNIT_TEST(test_Reg_hmul_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_hmul_int();
	template <typename T>
	void test_reg_hmul_real();
	void test_reg_hmul_int8();
	void test_reg_hmul_int16();
	void test_reg_hmul_int32();
	void test_reg_hmul_int64();
	void test_reg_hmul_float();
	void test_reg_hmul_double();

	template <typename T>
	void test_Reg_hmul_int();
	template <typename T>
	void test_Reg_hmul_real();
	void test_Reg_hmul_int8();
	void test_Reg_hmul_int16();
	void test_Reg_hmul_int32();
	void test_Reg_hmul_int64();
	void test_Reg_hmul_float();
	void test_Reg_hmul_double();
};

#endif // HMULTEST_HPP_
