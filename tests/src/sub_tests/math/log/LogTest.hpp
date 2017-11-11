#ifndef LOGTEST_HPP_
#define LOGTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class LogTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(LogTest);

//#if !defined(MIPP_AVX512) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_log_float);
#endif
	CPPUNIT_TEST(test_Reg_log_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_maskz_log_float);
#endif
	CPPUNIT_TEST(test_Reg_maskz_log_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_mask_log_float);
#endif
	CPPUNIT_TEST(test_Reg_mask_log_float);
//#endif

#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_log_double);
#endif
	CPPUNIT_TEST(test_Reg_log_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_maskz_log_double);
#endif
	CPPUNIT_TEST(test_Reg_maskz_log_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_mask_log_double);
#endif
	CPPUNIT_TEST(test_Reg_mask_log_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_log();
	void test_reg_log_float();
	void test_reg_log_double();

	template <typename T>
	void test_Reg_log();
	void test_Reg_log_float();
	void test_Reg_log_double();

	template <typename T>
	void test_reg_maskz_log();
	void test_reg_maskz_log_float();
	void test_reg_maskz_log_double();

	template <typename T>
	void test_Reg_maskz_log();
	void test_Reg_maskz_log_float();
	void test_Reg_maskz_log_double();

	template <typename T>
	void test_reg_mask_log();
	void test_reg_mask_log_float();
	void test_reg_mask_log_double();

	template <typename T>
	void test_Reg_mask_log();
	void test_Reg_mask_log_float();
	void test_Reg_mask_log_double();
};

#endif // LOGTEST_HPP_
