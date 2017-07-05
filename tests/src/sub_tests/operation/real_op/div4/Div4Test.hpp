#ifndef DIV4TEST_HPP_
#define DIV4TEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class Div4Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Div4Test);

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_div4_int8);
	CPPUNIT_TEST(test_Reg_div4_int8);
	CPPUNIT_TEST(test_reg_maskz_div4_int8);
	CPPUNIT_TEST(test_Reg_maskz_div4_int8);
	CPPUNIT_TEST(test_reg_mask_div4_int8);
	CPPUNIT_TEST(test_Reg_mask_div4_int8);

	CPPUNIT_TEST(test_reg_div4_int16);
	CPPUNIT_TEST(test_Reg_div4_int16);
	CPPUNIT_TEST(test_reg_maskz_div4_int16);
	CPPUNIT_TEST(test_Reg_maskz_div4_int16);
	CPPUNIT_TEST(test_reg_mask_div4_int16);
	CPPUNIT_TEST(test_Reg_mask_div4_int16);
#endif

	CPPUNIT_TEST(test_reg_div4_int32);
	CPPUNIT_TEST(test_Reg_div4_int32);
	CPPUNIT_TEST(test_reg_maskz_div4_int32);
	CPPUNIT_TEST(test_Reg_maskz_div4_int32);
	CPPUNIT_TEST(test_reg_mask_div4_int32);
	CPPUNIT_TEST(test_Reg_mask_div4_int32);
#endif

	CPPUNIT_TEST(test_reg_div4_float);
	CPPUNIT_TEST(test_Reg_div4_float);
	CPPUNIT_TEST(test_reg_maskz_div4_float);
	CPPUNIT_TEST(test_Reg_maskz_div4_float);
	CPPUNIT_TEST(test_reg_mask_div4_float);
	CPPUNIT_TEST(test_Reg_mask_div4_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
	CPPUNIT_TEST(test_reg_div4_int64);
	CPPUNIT_TEST(test_Reg_div4_int64);
	CPPUNIT_TEST(test_reg_maskz_div4_int64);
	CPPUNIT_TEST(test_Reg_maskz_div4_int64);
	CPPUNIT_TEST(test_reg_mask_div4_int64);
	CPPUNIT_TEST(test_Reg_mask_div4_int64);
#endif

	CPPUNIT_TEST(test_reg_div4_double);
	CPPUNIT_TEST(test_Reg_div4_double);
	CPPUNIT_TEST(test_reg_maskz_div4_double);
	CPPUNIT_TEST(test_Reg_maskz_div4_double);
	CPPUNIT_TEST(test_reg_mask_div4_double);
	CPPUNIT_TEST(test_Reg_mask_div4_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_div4();
	void test_reg_div4_int8();
	void test_reg_div4_int16();
	void test_reg_div4_int32();
	void test_reg_div4_int64();
	void test_reg_div4_float();
	void test_reg_div4_double();

	template <typename T>
	void test_Reg_div4();
	void test_Reg_div4_int8();
	void test_Reg_div4_int16();
	void test_Reg_div4_int32();
	void test_Reg_div4_int64();
	void test_Reg_div4_float();
	void test_Reg_div4_double();

	template <typename T>
	void test_reg_maskz_div4();
	void test_reg_maskz_div4_int8();
	void test_reg_maskz_div4_int16();
	void test_reg_maskz_div4_int32();
	void test_reg_maskz_div4_int64();
	void test_reg_maskz_div4_float();
	void test_reg_maskz_div4_double();

	template <typename T>
	void test_Reg_maskz_div4();
	void test_Reg_maskz_div4_int8();
	void test_Reg_maskz_div4_int16();
	void test_Reg_maskz_div4_int32();
	void test_Reg_maskz_div4_int64();
	void test_Reg_maskz_div4_float();
	void test_Reg_maskz_div4_double();

	template <typename T>
	void test_reg_mask_div4();
	void test_reg_mask_div4_int8();
	void test_reg_mask_div4_int16();
	void test_reg_mask_div4_int32();
	void test_reg_mask_div4_int64();
	void test_reg_mask_div4_float();
	void test_reg_mask_div4_double();

	template <typename T>
	void test_Reg_mask_div4();
	void test_Reg_mask_div4_int8();
	void test_Reg_mask_div4_int16();
	void test_Reg_mask_div4_int32();
	void test_Reg_mask_div4_int64();
	void test_Reg_mask_div4_float();
	void test_Reg_mask_div4_double();
};

#endif // DIV4TEST_HPP_
