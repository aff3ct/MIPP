#ifndef SIGNTEST_HPP_
#define SIGNTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SignTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SignTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_int8);
#endif
	CPPUNIT_TEST(test_Reg_sign_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_int16);
#endif
	CPPUNIT_TEST(test_Reg_sign_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_int32);
#endif
	CPPUNIT_TEST(test_Reg_sign_int32);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_float);
#endif
	CPPUNIT_TEST(test_Reg_sign_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_int64);
#endif
	CPPUNIT_TEST(test_Reg_sign_int64);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_sign_double);
#endif
	CPPUNIT_TEST(test_Reg_sign_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_sign();
	void test_reg_sign_int8();
	void test_reg_sign_int16();
	void test_reg_sign_int32();
	void test_reg_sign_int64();
	void test_reg_sign_float();
	void test_reg_sign_double();

	template <typename T>
	void test_Reg_sign();
	void test_Reg_sign_int8();
	void test_Reg_sign_int16();
	void test_Reg_sign_int32();
	void test_Reg_sign_int64();
	void test_Reg_sign_float();
	void test_Reg_sign_double();
};

#endif // SIGNTEST_HPP_
