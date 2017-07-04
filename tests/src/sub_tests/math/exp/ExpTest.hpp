#ifndef EXPTEST_HPP_
#define EXPTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class ExpTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ExpTest);

#if !defined(MIPP_AVX512) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	CPPUNIT_TEST(test_reg_exp_float);
	CPPUNIT_TEST(test_Reg_exp_float);
	CPPUNIT_TEST(test_reg_maskz_exp_float);
	CPPUNIT_TEST(test_Reg_maskz_exp_float);
	CPPUNIT_TEST(test_reg_mask_exp_float);
	CPPUNIT_TEST(test_Reg_mask_exp_float);
#endif

#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	CPPUNIT_TEST(test_reg_exp_double);
	CPPUNIT_TEST(test_Reg_exp_double);
	CPPUNIT_TEST(test_reg_maskz_exp_double);
	CPPUNIT_TEST(test_Reg_maskz_exp_double);
	CPPUNIT_TEST(test_reg_mask_exp_double);
	CPPUNIT_TEST(test_Reg_mask_exp_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_exp();
	void test_reg_exp_float();
	void test_reg_exp_double();

	template <typename T>
	void test_Reg_exp();
	void test_Reg_exp_float();
	void test_Reg_exp_double();

	template <typename T>
	void test_reg_maskz_exp();
	void test_reg_maskz_exp_float();
	void test_reg_maskz_exp_double();

	template <typename T>
	void test_Reg_maskz_exp();
	void test_Reg_maskz_exp_float();
	void test_Reg_maskz_exp_double();

	template <typename T>
	void test_reg_mask_exp();
	void test_reg_mask_exp_float();
	void test_reg_mask_exp_double();

	template <typename T>
	void test_Reg_mask_exp();
	void test_Reg_mask_exp_float();
	void test_Reg_mask_exp_double();
};

#endif // EXPTEST_HPP_
