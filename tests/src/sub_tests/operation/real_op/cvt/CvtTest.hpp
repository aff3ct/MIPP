#ifndef CVTTEST_HPP_
#define CVTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CvtTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CvtTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_int8_int16);
#endif
	CPPUNIT_TEST(test_Reg_cvt_int8_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_int16_int32);
#endif
	CPPUNIT_TEST(test_Reg_cvt_int16_int32);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_int32_float);
#endif
	CPPUNIT_TEST(test_Reg_cvt_int32_float);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_float_int32);
#endif
	CPPUNIT_TEST(test_Reg_cvt_float_int32);

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_int32_int64);
#endif
	CPPUNIT_TEST(test_Reg_cvt_int32_int64);
#endif
#endif

#if !defined(MIPP_SSE) && !defined(MIPP_AVX)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_int64_double);
#endif
	CPPUNIT_TEST(test_Reg_cvt_int64_double);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cvt_double_int64);
#endif
	CPPUNIT_TEST(test_Reg_cvt_double_int64);
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T1, typename T2>
	void test_reg_cvt();
	void test_reg_cvt_int8_int16();
	void test_reg_cvt_int16_int32();
	void test_reg_cvt_int32_int64();
	void test_reg_cvt_int32_float();
	void test_reg_cvt_float_int32();
	void test_reg_cvt_int64_double();
	void test_reg_cvt_double_int64();

	template <typename T1, typename T2>
	void test_Reg_cvt();
	void test_Reg_cvt_int8_int16();
	void test_Reg_cvt_int16_int32();
	void test_Reg_cvt_int32_int64();
	void test_Reg_cvt_int32_float();
	void test_Reg_cvt_float_int32();
	void test_Reg_cvt_int64_double();
	void test_Reg_cvt_double_int64();
};

#endif // CVTTEST_HPP_
