#ifndef CMPGTTEST_HPP_
#define CMPGTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class CmpgtTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CmpgtTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_int8);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_int16);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_int32);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_float);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_int64);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_int64);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_cmpgt_double);
#endif
	CPPUNIT_TEST(test_Reg_cmpgt_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_cmpgt();
	void test_reg_cmpgt_int8();
	void test_reg_cmpgt_int16();
	void test_reg_cmpgt_int32();
	void test_reg_cmpgt_int64();
	void test_reg_cmpgt_float();
	void test_reg_cmpgt_double();

	template <typename T>
	void test_Reg_cmpgt();
	void test_Reg_cmpgt_int8();
	void test_Reg_cmpgt_int16();
	void test_Reg_cmpgt_int32();
	void test_Reg_cmpgt_int64();
	void test_Reg_cmpgt_float();
	void test_Reg_cmpgt_double();
};

#endif  // CMPGTTEST_HPP_
