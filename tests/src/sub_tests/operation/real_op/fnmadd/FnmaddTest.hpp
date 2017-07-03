#ifndef FNMADDTEST_HPP_
#define FNMADDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class FnmaddTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FnmaddTest);

	CPPUNIT_TEST(test_reg_fnmadd_float);
	CPPUNIT_TEST(test_reg_fnmadd_double);

	CPPUNIT_TEST(test_Reg_fnmadd_float);
	CPPUNIT_TEST(test_Reg_fnmadd_double);

	CPPUNIT_TEST(test_reg_maskz_fnmadd_float);
	CPPUNIT_TEST(test_reg_maskz_fnmadd_double);

	CPPUNIT_TEST(test_Reg_maskz_fnmadd_float);
	CPPUNIT_TEST(test_Reg_maskz_fnmadd_double);

	CPPUNIT_TEST(test_reg_mask_fnmadd_float);
	CPPUNIT_TEST(test_reg_mask_fnmadd_double);

	CPPUNIT_TEST(test_Reg_mask_fnmadd_float);
	CPPUNIT_TEST(test_Reg_mask_fnmadd_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_fnmadd();
	void test_reg_fnmadd_float();
	void test_reg_fnmadd_double();

	template <typename T>
	void test_Reg_fnmadd();
	void test_Reg_fnmadd_float();
	void test_Reg_fnmadd_double();

	template <typename T>
	void test_reg_maskz_fnmadd();
	void test_reg_maskz_fnmadd_float();
	void test_reg_maskz_fnmadd_double();

	template <typename T>
	void test_Reg_maskz_fnmadd();
	void test_Reg_maskz_fnmadd_float();
	void test_Reg_maskz_fnmadd_double();

	template <typename T>
	void test_reg_mask_fnmadd();
	void test_reg_mask_fnmadd_float();
	void test_reg_mask_fnmadd_double();

	template <typename T>
	void test_Reg_mask_fnmadd();
	void test_Reg_mask_fnmadd_float();
	void test_Reg_mask_fnmadd_double();
};

#endif // FNMADDTEST_HPP_
