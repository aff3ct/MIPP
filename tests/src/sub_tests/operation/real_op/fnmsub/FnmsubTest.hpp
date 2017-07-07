#ifndef FNMSUBTEST_HPP_
#define FNMSUBTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class FnmsubTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FnmsubTest);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_fnmsub_float);
	CPPUNIT_TEST(test_reg_maskz_fnmsub_float);
	CPPUNIT_TEST(test_reg_mask_fnmsub_float);
#endif
	CPPUNIT_TEST(test_Reg_fnmsub_float);
	CPPUNIT_TEST(test_Reg_maskz_fnmsub_float);
	CPPUNIT_TEST(test_Reg_mask_fnmsub_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_fnmsub_double);
	CPPUNIT_TEST(test_reg_maskz_fnmsub_double);
	CPPUNIT_TEST(test_reg_mask_fnmsub_double);
#endif
	CPPUNIT_TEST(test_Reg_fnmsub_double);
	CPPUNIT_TEST(test_Reg_maskz_fnmsub_double);
	CPPUNIT_TEST(test_Reg_mask_fnmsub_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_fnmsub();
	void test_reg_fnmsub_float();
	void test_reg_fnmsub_double();

	template <typename T>
	void test_Reg_fnmsub();
	void test_Reg_fnmsub_float();
	void test_Reg_fnmsub_double();

	template <typename T>
	void test_reg_maskz_fnmsub();
	void test_reg_maskz_fnmsub_float();
	void test_reg_maskz_fnmsub_double();

	template <typename T>
	void test_Reg_maskz_fnmsub();
	void test_Reg_maskz_fnmsub_float();
	void test_Reg_maskz_fnmsub_double();

	template <typename T>
	void test_reg_mask_fnmsub();
	void test_reg_mask_fnmsub_float();
	void test_reg_mask_fnmsub_double();

	template <typename T>
	void test_Reg_mask_fnmsub();
	void test_Reg_mask_fnmsub_float();
	void test_Reg_mask_fnmsub_double();
};

#endif // FNMSUBTEST_HPP_
