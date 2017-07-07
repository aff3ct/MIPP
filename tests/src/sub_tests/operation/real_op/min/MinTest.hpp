#ifndef MINTEST_HPP_
#define MINTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class MinTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MinTest);

#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_int8);
	CPPUNIT_TEST(test_reg_maskz_min_int8);
	CPPUNIT_TEST(test_reg_mask_min_int8);
#endif
	CPPUNIT_TEST(test_Reg_min_int8);
	CPPUNIT_TEST(test_Reg_maskz_min_int8);
	CPPUNIT_TEST(test_Reg_mask_min_int8);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_int16);
	CPPUNIT_TEST(test_reg_maskz_min_int16);
	CPPUNIT_TEST(test_reg_mask_min_int16);
#endif
	CPPUNIT_TEST(test_Reg_min_int16);
	CPPUNIT_TEST(test_Reg_maskz_min_int16);
	CPPUNIT_TEST(test_Reg_mask_min_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_int32);
	CPPUNIT_TEST(test_reg_maskz_min_int32);
	CPPUNIT_TEST(test_reg_mask_min_int32);
#endif
	CPPUNIT_TEST(test_Reg_min_int32);
	CPPUNIT_TEST(test_Reg_maskz_min_int32);
	CPPUNIT_TEST(test_Reg_mask_min_int32);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_float);
	CPPUNIT_TEST(test_reg_maskz_min_float);
	CPPUNIT_TEST(test_reg_mask_min_float);
#endif
	CPPUNIT_TEST(test_Reg_min_float);
	CPPUNIT_TEST(test_Reg_maskz_min_float);
	CPPUNIT_TEST(test_Reg_mask_min_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_int64);
	CPPUNIT_TEST(test_reg_maskz_min_int64);
	CPPUNIT_TEST(test_reg_mask_min_int64);
#endif
	CPPUNIT_TEST(test_Reg_min_int64);
	CPPUNIT_TEST(test_Reg_maskz_min_int64);
	CPPUNIT_TEST(test_Reg_mask_min_int64);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_min_double);
	CPPUNIT_TEST(test_reg_maskz_min_double);
	CPPUNIT_TEST(test_reg_mask_min_double);
#endif
	CPPUNIT_TEST(test_Reg_min_double);
	CPPUNIT_TEST(test_Reg_maskz_min_double);
	CPPUNIT_TEST(test_Reg_mask_min_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_min();
	void test_reg_min_int8();
	void test_reg_min_int16();
	void test_reg_min_int32();
	void test_reg_min_int64();
	void test_reg_min_float();
	void test_reg_min_double();

	template <typename T>
	void test_Reg_min();
	void test_Reg_min_int8();
	void test_Reg_min_int16();
	void test_Reg_min_int32();
	void test_Reg_min_int64();
	void test_Reg_min_float();
	void test_Reg_min_double();

	template <typename T>
	void test_reg_maskz_min();
	void test_reg_maskz_min_int8();
	void test_reg_maskz_min_int16();
	void test_reg_maskz_min_int32();
	void test_reg_maskz_min_int64();
	void test_reg_maskz_min_float();
	void test_reg_maskz_min_double();

	template <typename T>
	void test_Reg_maskz_min();
	void test_Reg_maskz_min_int8();
	void test_Reg_maskz_min_int16();
	void test_Reg_maskz_min_int32();
	void test_Reg_maskz_min_int64();
	void test_Reg_maskz_min_float();
	void test_Reg_maskz_min_double();

	template <typename T>
	void test_reg_mask_min();
	void test_reg_mask_min_int8();
	void test_reg_mask_min_int16();
	void test_reg_mask_min_int32();
	void test_reg_mask_min_int64();
	void test_reg_mask_min_float();
	void test_reg_mask_min_double();

	template <typename T>
	void test_Reg_mask_min();
	void test_Reg_mask_min_int8();
	void test_Reg_mask_min_int16();
	void test_Reg_mask_min_int32();
	void test_Reg_mask_min_int64();
	void test_Reg_mask_min_float();
	void test_Reg_mask_min_double();
};

#endif // MINTEST_HPP_
