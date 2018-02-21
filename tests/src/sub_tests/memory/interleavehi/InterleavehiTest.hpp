#ifndef INTERLEAVEHITEST_HPP_
#define INTERLEAVEHITEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleavehiTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleavehiTest);

#if (!defined(MIPP_AVX) && !defined(MIPP_AVX512)) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_int8);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_int8);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_int16);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_int32);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_float);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_float);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_float);
#endif

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_int64);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_int64);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi2_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi2_double);
#if defined(MIPP_AVX512)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleavehi4_double);
#endif
	CPPUNIT_TEST(test_Reg_interleavehi4_double);
#endif
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_interleavehi();
	void test_reg_interleavehi_int8();
	void test_reg_interleavehi_int16();
	void test_reg_interleavehi_int32();
	void test_reg_interleavehi_int64();
	void test_reg_interleavehi_float();
	void test_reg_interleavehi_double();

	template <typename T>
	void test_Reg_interleavehi();
	void test_Reg_interleavehi_int8();
	void test_Reg_interleavehi_int16();
	void test_Reg_interleavehi_int32();
	void test_Reg_interleavehi_int64();
	void test_Reg_interleavehi_float();
	void test_Reg_interleavehi_double();

	template <typename T>
	void test_reg_interleavehi2();
	void test_reg_interleavehi2_int8();
	void test_reg_interleavehi2_int16();
	void test_reg_interleavehi2_int32();
	void test_reg_interleavehi2_int64();
	void test_reg_interleavehi2_float();
	void test_reg_interleavehi2_double();

	template <typename T>
	void test_Reg_interleavehi2();
	void test_Reg_interleavehi2_int8();
	void test_Reg_interleavehi2_int16();
	void test_Reg_interleavehi2_int32();
	void test_Reg_interleavehi2_int64();
	void test_Reg_interleavehi2_float();
	void test_Reg_interleavehi2_double();

	template <typename T>
	void test_reg_interleavehi4();
	void test_reg_interleavehi4_int8();
	void test_reg_interleavehi4_int16();
	void test_reg_interleavehi4_int32();
	void test_reg_interleavehi4_int64();
	void test_reg_interleavehi4_float();
	void test_reg_interleavehi4_double();

	template <typename T>
	void test_Reg_interleavehi4();
	void test_Reg_interleavehi4_int8();
	void test_Reg_interleavehi4_int16();
	void test_Reg_interleavehi4_int32();
	void test_Reg_interleavehi4_int64();
	void test_Reg_interleavehi4_float();
	void test_Reg_interleavehi4_double();
};

#endif  // INTERLEAVEHITEST_HPP_
