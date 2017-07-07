#ifndef CMPGETEST_HPP_
#define CMPGETEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpgeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpgeTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_int8);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_int16);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_int32);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_float);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_int64);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_int64);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpge_double);
#endif
	CPPUNIT_TEST(test_Reg_cmpge_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpge();
	void test_reg_cmpge_int8();
	void test_reg_cmpge_int16();
	void test_reg_cmpge_int32();
	void test_reg_cmpge_int64();
	void test_reg_cmpge_float();
	void test_reg_cmpge_double();

	template <typename T>
	void test_Reg_cmpge();
	void test_Reg_cmpge_int8();
	void test_Reg_cmpge_int16();
	void test_Reg_cmpge_int32();
	void test_Reg_cmpge_int64();
	void test_Reg_cmpge_float();
	void test_Reg_cmpge_double();
};

#endif  // CMPGETEST_HPP_
