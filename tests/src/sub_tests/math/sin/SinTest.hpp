#ifndef SINTEST_HPP_
#define SINTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SinTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SinTest);

#if !defined(MIPP_AVX512) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sin_float);
#endif
	CPPUNIT_TEST(test_Reg_sin_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_maskz_sin_float);
#endif
	CPPUNIT_TEST(test_Reg_maskz_sin_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_mask_sin_float);
#endif
	CPPUNIT_TEST(test_Reg_mask_sin_float);
#endif

#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sin_double);
#endif
	CPPUNIT_TEST(test_Reg_sin_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_maskz_sin_double);
#endif
	CPPUNIT_TEST(test_Reg_maskz_sin_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_mask_sin_double);
#endif
	CPPUNIT_TEST(test_Reg_mask_sin_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_sin();
	void test_reg_sin_float();
	void test_reg_sin_double();

	template <typename T>
	void test_Reg_sin();
	void test_Reg_sin_float();
	void test_Reg_sin_double();

	template <typename T>
	void test_reg_maskz_sin();
	void test_reg_maskz_sin_float();
	void test_reg_maskz_sin_double();

	template <typename T>
	void test_Reg_maskz_sin();
	void test_Reg_maskz_sin_float();
	void test_Reg_maskz_sin_double();

	template <typename T>
	void test_reg_mask_sin();
	void test_reg_mask_sin_float();
	void test_reg_mask_sin_double();

	template <typename T>
	void test_Reg_mask_sin();
	void test_Reg_mask_sin_float();
	void test_Reg_mask_sin_double();
};

#endif // SINTEST_HPP_
