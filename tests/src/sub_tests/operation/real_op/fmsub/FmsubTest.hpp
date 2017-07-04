#ifndef FMSUBTEST_HPP_
#define FMSUBTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class FmsubTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FmsubTest);

	CPPUNIT_TEST(test_reg_fmsub_float);
	CPPUNIT_TEST(test_Reg_fmsub_float);
	CPPUNIT_TEST(test_reg_maskz_fmsub_float);
	CPPUNIT_TEST(test_Reg_maskz_fmsub_float);
	CPPUNIT_TEST(test_reg_mask_fmsub_float);
	CPPUNIT_TEST(test_Reg_mask_fmsub_float);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_fmsub_double);
	CPPUNIT_TEST(test_Reg_fmsub_double);
	CPPUNIT_TEST(test_reg_maskz_fmsub_double);
	CPPUNIT_TEST(test_Reg_maskz_fmsub_double);
	CPPUNIT_TEST(test_reg_mask_fmsub_double);
	CPPUNIT_TEST(test_Reg_mask_fmsub_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_fmsub();
	void test_reg_fmsub_float();
	void test_reg_fmsub_double();

	template <typename T>
	void test_Reg_fmsub();
	void test_Reg_fmsub_float();
	void test_Reg_fmsub_double();

	template <typename T>
	void test_reg_maskz_fmsub();
	void test_reg_maskz_fmsub_float();
	void test_reg_maskz_fmsub_double();

	template <typename T>
	void test_Reg_maskz_fmsub();
	void test_Reg_maskz_fmsub_float();
	void test_Reg_maskz_fmsub_double();

	template <typename T>
	void test_reg_mask_fmsub();
	void test_reg_mask_fmsub_float();
	void test_reg_mask_fmsub_double();

	template <typename T>
	void test_Reg_mask_fmsub();
	void test_Reg_mask_fmsub_float();
	void test_Reg_mask_fmsub_double();
};

#endif // FMSUBTEST_HPP_
