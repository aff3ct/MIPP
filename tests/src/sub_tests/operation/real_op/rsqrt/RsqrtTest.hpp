#ifndef RSQRTTEST_HPP_
#define RSQRTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RsqrtTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RsqrtTest);

	CPPUNIT_TEST(test_reg_rsqrt_float);
	CPPUNIT_TEST(test_reg_rsqrt_double);

	CPPUNIT_TEST(test_Reg_rsqrt_float);
	CPPUNIT_TEST(test_Reg_rsqrt_double);

	CPPUNIT_TEST(test_reg_maskz_rsqrt_float);
	CPPUNIT_TEST(test_reg_maskz_rsqrt_double);

	CPPUNIT_TEST(test_Reg_maskz_rsqrt_float);
	CPPUNIT_TEST(test_Reg_maskz_rsqrt_double);

	CPPUNIT_TEST(test_reg_mask_rsqrt_float);
	CPPUNIT_TEST(test_reg_mask_rsqrt_double);

	CPPUNIT_TEST(test_Reg_mask_rsqrt_float);
	CPPUNIT_TEST(test_Reg_mask_rsqrt_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_rsqrt();
	void test_reg_rsqrt_float();
	void test_reg_rsqrt_double();

	template <typename T>
	void test_Reg_rsqrt();
	void test_Reg_rsqrt_float();
	void test_Reg_rsqrt_double();

	template <typename T>
	void test_reg_maskz_rsqrt();
	void test_reg_maskz_rsqrt_float();
	void test_reg_maskz_rsqrt_double();

	template <typename T>
	void test_Reg_maskz_rsqrt();
	void test_Reg_maskz_rsqrt_float();
	void test_Reg_maskz_rsqrt_double();

	template <typename T>
	void test_reg_mask_rsqrt();
	void test_reg_mask_rsqrt_float();
	void test_reg_mask_rsqrt_double();

	template <typename T>
	void test_Reg_mask_rsqrt();
	void test_Reg_mask_rsqrt_float();
	void test_Reg_mask_rsqrt_double();
};

#endif // RSQRTTEST_HPP_
