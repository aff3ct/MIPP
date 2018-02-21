#ifndef INTERLEAVELOTEST_HPP_
#define INTERLEAVELOTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleaveloTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleaveloTest);

#if (!defined(MIPP_AVX) && !defined(MIPP_AVX512)) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_int8);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_int8);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_int16);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_int32);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_float);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_float);
#endif

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_int64);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_int64);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo2_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo2_double);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavelo4_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavelo4_double);
#endif
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_interleavelo();
	void test_reg_interleavelo_int8();
	void test_reg_interleavelo_int16();
	void test_reg_interleavelo_int32();
	void test_reg_interleavelo_int64();
	void test_reg_interleavelo_float();
	void test_reg_interleavelo_double();

	template <typename T>
	void test_Reg_interleavelo();
	void test_Reg_interleavelo_int8();
	void test_Reg_interleavelo_int16();
	void test_Reg_interleavelo_int32();
	void test_Reg_interleavelo_int64();
	void test_Reg_interleavelo_float();
	void test_Reg_interleavelo_double();

	template <typename T>
	void test_reg_interleavelo2();
	void test_reg_interleavelo2_int8();
	void test_reg_interleavelo2_int16();
	void test_reg_interleavelo2_int32();
	void test_reg_interleavelo2_int64();
	void test_reg_interleavelo2_float();
	void test_reg_interleavelo2_double();

	template <typename T>
	void test_Reg_interleavelo2();
	void test_Reg_interleavelo2_int8();
	void test_Reg_interleavelo2_int16();
	void test_Reg_interleavelo2_int32();
	void test_Reg_interleavelo2_int64();
	void test_Reg_interleavelo2_float();
	void test_Reg_interleavelo2_double();

	template <typename T>
	void test_reg_interleavelo4();
	void test_reg_interleavelo4_int8();
	void test_reg_interleavelo4_int16();
	void test_reg_interleavelo4_int32();
	void test_reg_interleavelo4_int64();
	void test_reg_interleavelo4_float();
	void test_reg_interleavelo4_double();

	template <typename T>
	void test_Reg_interleavelo4();
	void test_Reg_interleavelo4_int8();
	void test_Reg_interleavelo4_int16();
	void test_Reg_interleavelo4_int32();
	void test_Reg_interleavelo4_int64();
	void test_Reg_interleavelo4_float();
	void test_Reg_interleavelo4_double();
};

#endif  // INTERLEAVELOTEST_HPP_
