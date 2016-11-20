#ifndef SATTEST_HPP_
#define SATTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SatTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SatTest);

#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	CPPUNIT_TEST(test_reg_sat_int8);
	CPPUNIT_TEST(test_Reg_sat_int8);
#endif

	CPPUNIT_TEST(test_reg_sat_int16);
	CPPUNIT_TEST(test_Reg_sat_int16);
#endif

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	CPPUNIT_TEST(test_reg_sat_int32);
	CPPUNIT_TEST(test_Reg_sat_int32);
#endif
#endif

	CPPUNIT_TEST(test_reg_sat_float);
	CPPUNIT_TEST(test_Reg_sat_float);

#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) && !defined(MIPP_AVX) && !defined(MIPP_NEON)
	CPPUNIT_TEST(test_reg_sat_int64);
	CPPUNIT_TEST(test_Reg_sat_int64);
#endif

	CPPUNIT_TEST(test_reg_sat_double);
	CPPUNIT_TEST(test_Reg_sat_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_sat_int();
	template <typename T>
	void test_reg_sat_real();
	void test_reg_sat_int8();
	void test_reg_sat_int16();
	void test_reg_sat_int32();
	void test_reg_sat_int64();
	void test_reg_sat_float();
	void test_reg_sat_double();

	template <typename T>
	void test_Reg_sat_int();
	template <typename T>
	void test_Reg_sat_real();
	void test_Reg_sat_int8();
	void test_Reg_sat_int16();
	void test_Reg_sat_int32();
	void test_Reg_sat_int64();
	void test_Reg_sat_float();
	void test_Reg_sat_double();
};

#endif // SATTEST_HPP_
