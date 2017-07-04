#ifndef COSTEST_HPP_
#define COSTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CosTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CosTest);

#if !defined(MIPP_AVX512) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	CPPUNIT_TEST(test_reg_cos_float);
	CPPUNIT_TEST(test_Reg_cos_float);
	CPPUNIT_TEST(test_reg_maskz_cos_float);
	CPPUNIT_TEST(test_Reg_maskz_cos_float);
	CPPUNIT_TEST(test_reg_mask_cos_float);
	CPPUNIT_TEST(test_Reg_mask_cos_float);
#endif

#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	CPPUNIT_TEST(test_reg_cos_double);
	CPPUNIT_TEST(test_Reg_cos_double);
	CPPUNIT_TEST(test_reg_maskz_cos_double);
	CPPUNIT_TEST(test_Reg_maskz_cos_double);
	CPPUNIT_TEST(test_reg_mask_cos_double);
	CPPUNIT_TEST(test_Reg_mask_cos_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cos();
	void test_reg_cos_float();
	void test_reg_cos_double();

	template <typename T>
	void test_Reg_cos();
	void test_Reg_cos_float();
	void test_Reg_cos_double();

	template <typename T>
	void test_reg_maskz_cos();
	void test_reg_maskz_cos_float();
	void test_reg_maskz_cos_double();

	template <typename T>
	void test_Reg_maskz_cos();
	void test_Reg_maskz_cos_float();
	void test_Reg_maskz_cos_double();

	template <typename T>
	void test_reg_mask_cos();
	void test_reg_mask_cos_float();
	void test_reg_mask_cos_double();

	template <typename T>
	void test_Reg_mask_cos();
	void test_Reg_mask_cos_float();
	void test_Reg_mask_cos_double();
};

#endif // COSTEST_HPP_
