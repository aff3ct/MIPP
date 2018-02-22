#ifndef SUFFTEST_HPP_
#define SUFFTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class ShuffTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ShuffTest);

#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#if defined(MIPP_BW)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_int8);
#endif
	CPPUNIT_TEST(test_Reg_shuff_int8);
#endif
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#ifndef MIPP_NO
	CPPUNIT_TEST(test_Reg_shuff2_int8);
#endif
	CPPUNIT_TEST(test_reg_shuff2_int8);
#endif
#ifndef MIPP_NO
	CPPUNIT_TEST(test_Reg_shuff4_int8);
#endif
	CPPUNIT_TEST(test_reg_shuff4_int8);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_int16);
#endif
	CPPUNIT_TEST(test_Reg_shuff_int16);
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff2_int16);
#endif
	CPPUNIT_TEST(test_Reg_shuff2_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff4_int16);
#endif
	CPPUNIT_TEST(test_Reg_shuff4_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_int32);
#endif
	CPPUNIT_TEST(test_Reg_shuff_int32);
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff2_int32);
#endif
	CPPUNIT_TEST(test_Reg_shuff2_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff4_int32);
#endif
	CPPUNIT_TEST(test_Reg_shuff4_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_float);
#endif
	CPPUNIT_TEST(test_Reg_shuff_float);
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff2_float);
#endif
	CPPUNIT_TEST(test_Reg_shuff2_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff4_float);
#endif
	CPPUNIT_TEST(test_Reg_shuff4_float);
#endif

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_int64);
#endif
	CPPUNIT_TEST(test_Reg_shuff_int64);
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff2_int64);
#endif
	CPPUNIT_TEST(test_Reg_shuff2_int64);
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff4_int64);
#endif
	CPPUNIT_TEST(test_Reg_shuff4_int64);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff_double);
#endif
	CPPUNIT_TEST(test_Reg_shuff_double);
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff2_double);
#endif
	CPPUNIT_TEST(test_Reg_shuff2_double);
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_shuff4_double);
#endif
	CPPUNIT_TEST(test_Reg_shuff4_double);
#endif
#endif
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_shuff();
	void test_reg_shuff_int8();
	void test_reg_shuff_int16();
	void test_reg_shuff_int32();
	void test_reg_shuff_int64();
	void test_reg_shuff_float();
	void test_reg_shuff_double();

	template <typename T>
	void test_Reg_shuff();
	void test_Reg_shuff_int8();
	void test_Reg_shuff_int16();
	void test_Reg_shuff_int32();
	void test_Reg_shuff_int64();
	void test_Reg_shuff_float();
	void test_Reg_shuff_double();

	template <typename T>
	void test_reg_shuff2();
	void test_reg_shuff2_int8();
	void test_reg_shuff2_int16();
	void test_reg_shuff2_int32();
	void test_reg_shuff2_int64();
	void test_reg_shuff2_float();
	void test_reg_shuff2_double();

	template <typename T>
	void test_Reg_shuff2();
	void test_Reg_shuff2_int8();
	void test_Reg_shuff2_int16();
	void test_Reg_shuff2_int32();
	void test_Reg_shuff2_int64();
	void test_Reg_shuff2_float();
	void test_Reg_shuff2_double();

	template <typename T>
	void test_reg_shuff4();
	void test_reg_shuff4_int8();
	void test_reg_shuff4_int16();
	void test_reg_shuff4_int32();
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	void test_reg_shuff4_int64();
#endif
	void test_reg_shuff4_float();
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	void test_reg_shuff4_double();
#endif

	template <typename T>
	void test_Reg_shuff4();
	void test_Reg_shuff4_int8();
	void test_Reg_shuff4_int16();
	void test_Reg_shuff4_int32();
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	void test_Reg_shuff4_int64();
#endif
	void test_Reg_shuff4_float();
#if !defined(MIPP_SSE) && !defined(MIPP_NEON)
	void test_Reg_shuff4_double();
#endif
};

#endif  // SUFFTEST_HPP_
