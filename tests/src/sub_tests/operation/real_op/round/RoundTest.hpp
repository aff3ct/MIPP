#ifndef ROUNDTEST_HPP_
#define ROUNDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RoundTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RoundTest);

	CPPUNIT_TEST(test_reg_round_float);
	CPPUNIT_TEST(test_Reg_round_float);
	CPPUNIT_TEST(test_reg_maskz_round_float);
	CPPUNIT_TEST(test_Reg_maskz_round_float);
	CPPUNIT_TEST(test_reg_mask_round_float);
	CPPUNIT_TEST(test_Reg_mask_round_float);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_round_double);
	CPPUNIT_TEST(test_Reg_round_double);
	CPPUNIT_TEST(test_reg_maskz_round_double);
	CPPUNIT_TEST(test_Reg_maskz_round_double);
	CPPUNIT_TEST(test_reg_mask_round_double);
	CPPUNIT_TEST(test_Reg_mask_round_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_round();
	void test_reg_round_float();
	void test_reg_round_double();

	template <typename T>
	void test_Reg_round();
	void test_Reg_round_float();
	void test_Reg_round_double();

	template <typename T>
	void test_reg_maskz_round();
	void test_reg_maskz_round_float();
	void test_reg_maskz_round_double();

	template <typename T>
	void test_Reg_maskz_round();
	void test_Reg_maskz_round_float();
	void test_Reg_maskz_round_double();

	template <typename T>
	void test_reg_mask_round();
	void test_reg_mask_round_float();
	void test_reg_mask_round_double();

	template <typename T>
	void test_Reg_mask_round();
	void test_Reg_mask_round_float();
	void test_Reg_mask_round_double();
};

#endif // ROUNDTEST_HPP_
