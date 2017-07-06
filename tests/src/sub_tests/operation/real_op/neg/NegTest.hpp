#ifndef NEGTEST_HPP_
#define NEGTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class NegTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(NegTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_neg_int8);
	CPPUNIT_TEST(test_Reg_neg_int8);
	CPPUNIT_TEST(test_reg_maskz_neg_int8);
	CPPUNIT_TEST(test_Reg_maskz_neg_int8);
	CPPUNIT_TEST(test_reg_mask_neg_int8);
	CPPUNIT_TEST(test_Reg_mask_neg_int8);

	CPPUNIT_TEST(test_reg_neg_int16);
	CPPUNIT_TEST(test_Reg_neg_int16);
	CPPUNIT_TEST(test_reg_maskz_neg_int16);
	CPPUNIT_TEST(test_Reg_maskz_neg_int16);
	CPPUNIT_TEST(test_reg_mask_neg_int16);
	CPPUNIT_TEST(test_Reg_mask_neg_int16);
#endif

	CPPUNIT_TEST(test_reg_neg_int32);
	CPPUNIT_TEST(test_Reg_neg_int32);
	CPPUNIT_TEST(test_reg_maskz_neg_int32);
	CPPUNIT_TEST(test_Reg_maskz_neg_int32);
	CPPUNIT_TEST(test_reg_mask_neg_int32);
	CPPUNIT_TEST(test_Reg_mask_neg_int32);
#endif
#endif

	CPPUNIT_TEST(test_reg_neg_float);
	CPPUNIT_TEST(test_Reg_neg_float);
	CPPUNIT_TEST(test_reg_maskz_neg_float);
	CPPUNIT_TEST(test_Reg_maskz_neg_float);
	CPPUNIT_TEST(test_reg_mask_neg_float);
	CPPUNIT_TEST(test_Reg_mask_neg_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	CPPUNIT_TEST(test_reg_neg_int64);
	CPPUNIT_TEST(test_Reg_neg_int64);
	CPPUNIT_TEST(test_reg_maskz_neg_int64);
	CPPUNIT_TEST(test_Reg_maskz_neg_int64);
	CPPUNIT_TEST(test_reg_mask_neg_int64);
	CPPUNIT_TEST(test_Reg_mask_neg_int64);
#endif

	CPPUNIT_TEST(test_reg_neg_double);
	CPPUNIT_TEST(test_Reg_neg_double);
	CPPUNIT_TEST(test_reg_maskz_neg_double);
	CPPUNIT_TEST(test_Reg_maskz_neg_double);
	CPPUNIT_TEST(test_reg_mask_neg_double);
	CPPUNIT_TEST(test_Reg_mask_neg_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_neg();
	void test_reg_neg_int8();
	void test_reg_neg_int16();
	void test_reg_neg_int32();
	void test_reg_neg_int64();
	void test_reg_neg_float();
	void test_reg_neg_double();

	template <typename T>
	void test_Reg_neg();
	void test_Reg_neg_int8();
	void test_Reg_neg_int16();
	void test_Reg_neg_int32();
	void test_Reg_neg_int64();
	void test_Reg_neg_float();
	void test_Reg_neg_double();

	template <typename T>
	void test_reg_maskz_neg();
	void test_reg_maskz_neg_int8();
	void test_reg_maskz_neg_int16();
	void test_reg_maskz_neg_int32();
	void test_reg_maskz_neg_int64();
	void test_reg_maskz_neg_float();
	void test_reg_maskz_neg_double();

	template <typename T>
	void test_Reg_maskz_neg();
	void test_Reg_maskz_neg_int8();
	void test_Reg_maskz_neg_int16();
	void test_Reg_maskz_neg_int32();
	void test_Reg_maskz_neg_int64();
	void test_Reg_maskz_neg_float();
	void test_Reg_maskz_neg_double();

	template <typename T>
	void test_reg_mask_neg();
	void test_reg_mask_neg_int8();
	void test_reg_mask_neg_int16();
	void test_reg_mask_neg_int32();
	void test_reg_mask_neg_int64();
	void test_reg_mask_neg_float();
	void test_reg_mask_neg_double();

	template <typename T>
	void test_Reg_mask_neg();
	void test_Reg_mask_neg_int8();
	void test_Reg_mask_neg_int16();
	void test_Reg_mask_neg_int32();
	void test_Reg_mask_neg_int64();
	void test_Reg_mask_neg_float();
	void test_Reg_mask_neg_double();
};

#endif // NEGTEST_HPP_
