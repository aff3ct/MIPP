#ifndef ROUNDTEST_HPP_
#define ROUNDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RoundTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RoundTest);

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_round_float);
	CPPUNIT_TEST(test_reg_maskz_round_float);
	CPPUNIT_TEST(test_reg_mask_round_float);
#endif
	CPPUNIT_TEST(test_Reg_round_float);
	CPPUNIT_TEST(test_Reg_maskz_round_float);
	CPPUNIT_TEST(test_Reg_mask_round_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_round_double);
	CPPUNIT_TEST(test_reg_maskz_round_double);
	CPPUNIT_TEST(test_reg_maskz_round_double);
#endif
	CPPUNIT_TEST(test_Reg_round_double);
	CPPUNIT_TEST(test_Reg_maskz_round_double);
	CPPUNIT_TEST(test_Reg_mask_round_double);
#endif
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
