#ifndef ABSTEST_HPP_
#define ABSTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class AbsTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AbsTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_int8);
	CPPUNIT_TEST(test_reg_maskz_abs_int8);
	CPPUNIT_TEST(test_reg_mask_abs_int8);
#endif
	CPPUNIT_TEST(test_Reg_abs_int8);
	CPPUNIT_TEST(test_Reg_maskz_abs_int8);
	CPPUNIT_TEST(test_Reg_mask_abs_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_int16);
	CPPUNIT_TEST(test_reg_maskz_abs_int16);
	CPPUNIT_TEST(test_reg_mask_abs_int16);
#endif
	CPPUNIT_TEST(test_Reg_abs_int16);
	CPPUNIT_TEST(test_Reg_maskz_abs_int16);
	CPPUNIT_TEST(test_Reg_mask_abs_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_int32);
	CPPUNIT_TEST(test_reg_maskz_abs_int32);
	CPPUNIT_TEST(test_reg_mask_abs_int32);
#endif
	CPPUNIT_TEST(test_Reg_abs_int32);
	CPPUNIT_TEST(test_Reg_maskz_abs_int32);
	CPPUNIT_TEST(test_Reg_mask_abs_int32);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_float);
	CPPUNIT_TEST(test_reg_maskz_abs_float);
	CPPUNIT_TEST(test_reg_mask_abs_float);
#endif
	CPPUNIT_TEST(test_Reg_abs_float);
	CPPUNIT_TEST(test_Reg_maskz_abs_float);
	CPPUNIT_TEST(test_Reg_mask_abs_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_int64);
	CPPUNIT_TEST(test_reg_maskz_abs_int64);
	CPPUNIT_TEST(test_reg_mask_abs_int64);
#endif
	CPPUNIT_TEST(test_Reg_abs_int64);
	CPPUNIT_TEST(test_Reg_maskz_abs_int64);
	CPPUNIT_TEST(test_Reg_mask_abs_int64);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_abs_double);
	CPPUNIT_TEST(test_reg_maskz_abs_double);
	CPPUNIT_TEST(test_reg_mask_abs_double);
#endif
	CPPUNIT_TEST(test_Reg_abs_double);
	CPPUNIT_TEST(test_Reg_maskz_abs_double);
	CPPUNIT_TEST(test_Reg_mask_abs_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_abs();
	void test_reg_abs_int8();
	void test_reg_abs_int16();
	void test_reg_abs_int32();
	void test_reg_abs_int64();
	void test_reg_abs_float();
	void test_reg_abs_double();

	template <typename T>
	void test_Reg_abs();
	void test_Reg_abs_int8();
	void test_Reg_abs_int16();
	void test_Reg_abs_int32();
	void test_Reg_abs_int64();
	void test_Reg_abs_float();
	void test_Reg_abs_double();

	template <typename T>
	void test_reg_maskz_abs();
	void test_reg_maskz_abs_int8();
	void test_reg_maskz_abs_int16();
	void test_reg_maskz_abs_int32();
	void test_reg_maskz_abs_int64();
	void test_reg_maskz_abs_float();
	void test_reg_maskz_abs_double();

	template <typename T>
	void test_Reg_maskz_abs();
	void test_Reg_maskz_abs_int8();
	void test_Reg_maskz_abs_int16();
	void test_Reg_maskz_abs_int32();
	void test_Reg_maskz_abs_int64();
	void test_Reg_maskz_abs_float();
	void test_Reg_maskz_abs_double();

	template <typename T>
	void test_reg_mask_abs();
	void test_reg_mask_abs_int8();
	void test_reg_mask_abs_int16();
	void test_reg_mask_abs_int32();
	void test_reg_mask_abs_int64();
	void test_reg_mask_abs_float();
	void test_reg_mask_abs_double();

	template <typename T>
	void test_Reg_mask_abs();
	void test_Reg_mask_abs_int8();
	void test_Reg_mask_abs_int16();
	void test_Reg_mask_abs_int32();
	void test_Reg_mask_abs_int64();
	void test_Reg_mask_abs_float();
	void test_Reg_mask_abs_double();
};

#endif // ABSTEST_HPP_
