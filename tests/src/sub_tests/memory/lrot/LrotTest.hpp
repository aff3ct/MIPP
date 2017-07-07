#ifndef LROTTEST_HPP_
#define LROTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class LrotTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(LrotTest);

#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_int8);
#endif
	CPPUNIT_TEST(test_Reg_lrot_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_int16);
#endif
	CPPUNIT_TEST(test_Reg_lrot_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_int32);
#endif
	CPPUNIT_TEST(test_Reg_lrot_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_float);
#endif
	CPPUNIT_TEST(test_Reg_lrot_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_int64);
#endif
	CPPUNIT_TEST(test_Reg_lrot_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_lrot_double);
#endif
	CPPUNIT_TEST(test_Reg_lrot_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_lrot();
	void test_reg_lrot_int8();
	void test_reg_lrot_int16();
	void test_reg_lrot_int32();
	void test_reg_lrot_int64();
	void test_reg_lrot_float();
	void test_reg_lrot_double();

	template <typename T>
	void test_Reg_lrot();
	void test_Reg_lrot_int8();
	void test_Reg_lrot_int16();
	void test_Reg_lrot_int32();
	void test_Reg_lrot_int64();
	void test_Reg_lrot_float();
	void test_Reg_lrot_double();
};

#endif  // LROTTEST_HPP_
