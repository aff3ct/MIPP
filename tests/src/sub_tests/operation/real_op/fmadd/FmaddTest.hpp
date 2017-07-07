#ifndef FMADDTEST_HPP_
#define FMADDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class FmaddTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FmaddTest);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_fmadd_float);
	CPPUNIT_TEST(test_reg_maskz_fmadd_float);
	CPPUNIT_TEST(test_reg_mask_fmadd_float);
#endif
	CPPUNIT_TEST(test_Reg_fmadd_float);
	CPPUNIT_TEST(test_Reg_maskz_fmadd_float);
	CPPUNIT_TEST(test_Reg_mask_fmadd_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_fmadd_double);
	CPPUNIT_TEST(test_reg_maskz_fmadd_double);
	CPPUNIT_TEST(test_reg_mask_fmadd_double);
#endif
	CPPUNIT_TEST(test_Reg_fmadd_double);
	CPPUNIT_TEST(test_Reg_maskz_fmadd_double);
	CPPUNIT_TEST(test_Reg_mask_fmadd_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_fmadd();
	void test_reg_fmadd_float();
	void test_reg_fmadd_double();

	template <typename T>
	void test_Reg_fmadd();
	void test_Reg_fmadd_float();
	void test_Reg_fmadd_double();

	template <typename T>
	void test_reg_maskz_fmadd();
	void test_reg_maskz_fmadd_float();
	void test_reg_maskz_fmadd_double();

	template <typename T>
	void test_Reg_maskz_fmadd();
	void test_Reg_maskz_fmadd_float();
	void test_Reg_maskz_fmadd_double();

	template <typename T>
	void test_reg_mask_fmadd();
	void test_reg_mask_fmadd_float();
	void test_reg_mask_fmadd_double();

	template <typename T>
	void test_Reg_mask_fmadd();
	void test_Reg_mask_fmadd_float();
	void test_Reg_mask_fmadd_double();
};

#endif // FMADDTEST_HPP_
