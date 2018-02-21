#ifndef RROTTEST_HPP_
#define RROTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RrotTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RrotTest);

#if defined(MIPP_BW)
#if (!defined(MIPP_SSE) && !defined(MIPP_AVX512)) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_int8);
#endif
	CPPUNIT_TEST(test_Reg_rrot_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_int16);
#endif
	CPPUNIT_TEST(test_Reg_rrot_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_int32);
#endif
	CPPUNIT_TEST(test_Reg_rrot_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_float);
#endif
	CPPUNIT_TEST(test_Reg_rrot_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_int64);
#endif
	CPPUNIT_TEST(test_Reg_rrot_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_rrot_double);
#endif
	CPPUNIT_TEST(test_Reg_rrot_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_rrot();
	void test_reg_rrot_int8();
	void test_reg_rrot_int16();
	void test_reg_rrot_int32();
	void test_reg_rrot_int64();
	void test_reg_rrot_float();
	void test_reg_rrot_double();

	template <typename T>
	void test_Reg_rrot();
	void test_Reg_rrot_int8();
	void test_Reg_rrot_int16();
	void test_Reg_rrot_int32();
	void test_Reg_rrot_int64();
	void test_Reg_rrot_float();
	void test_Reg_rrot_double();
};

#endif  // RROTTEST_HPP_
