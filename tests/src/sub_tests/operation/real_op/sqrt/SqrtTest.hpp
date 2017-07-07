#ifndef SQRTTEST_HPP_
#define SQRTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SqrtTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SqrtTest);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sqrt_float);
	CPPUNIT_TEST(test_reg_maskz_sqrt_float);
	CPPUNIT_TEST(test_reg_mask_sqrt_float);
#endif
	CPPUNIT_TEST(test_Reg_sqrt_float);
	CPPUNIT_TEST(test_Reg_maskz_sqrt_float);
	CPPUNIT_TEST(test_Reg_mask_sqrt_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sqrt_double);
	CPPUNIT_TEST(test_reg_maskz_sqrt_double);
	CPPUNIT_TEST(test_reg_mask_sqrt_double);
#endif
	CPPUNIT_TEST(test_Reg_sqrt_double);
	CPPUNIT_TEST(test_Reg_maskz_sqrt_double);
	CPPUNIT_TEST(test_Reg_mask_sqrt_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_sqrt();
	void test_reg_sqrt_float();
	void test_reg_sqrt_double();

	template <typename T>
	void test_Reg_sqrt();
	void test_Reg_sqrt_float();
	void test_Reg_sqrt_double();

	template <typename T>
	void test_reg_maskz_sqrt();
	void test_reg_maskz_sqrt_float();
	void test_reg_maskz_sqrt_double();

	template <typename T>
	void test_Reg_maskz_sqrt();
	void test_Reg_maskz_sqrt_float();
	void test_Reg_maskz_sqrt_double();

	template <typename T>
	void test_reg_mask_sqrt();
	void test_reg_mask_sqrt_float();
	void test_reg_mask_sqrt_double();

	template <typename T>
	void test_Reg_mask_sqrt();
	void test_Reg_mask_sqrt_float();
	void test_Reg_mask_sqrt_double();
};

#endif // SQRTTEST_HPP_
