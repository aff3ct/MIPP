#ifndef CMPEQTEST_HPP_
#define CMPEQTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpeqTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpeqTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_int8);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_int16);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_int32);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_float);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_int64);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_int64);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpeq_double);
#endif
	CPPUNIT_TEST(test_Reg_cmpeq_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpeq();
	void test_reg_cmpeq_int8();
	void test_reg_cmpeq_int16();
	void test_reg_cmpeq_int32();
	void test_reg_cmpeq_int64();
	void test_reg_cmpeq_float();
	void test_reg_cmpeq_double();

	template <typename T>
	void test_Reg_cmpeq();
	void test_Reg_cmpeq_int8();
	void test_Reg_cmpeq_int16();
	void test_Reg_cmpeq_int32();
	void test_Reg_cmpeq_int64();
	void test_Reg_cmpeq_float();
	void test_Reg_cmpeq_double();
};

#endif  // CMPEQTEST_HPP_
