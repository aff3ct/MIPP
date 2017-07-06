#ifndef RSHIFTTEST_HPP_
#define RSHIFTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class RshiftTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RshiftTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_rshift_int8);
	CPPUNIT_TEST(test_Reg_rshift_int8);
#if !defined(MIPP_AVX) && !defined(MIPP_AVX512)
	CPPUNIT_TEST(test_msk_rshift_int8);
	CPPUNIT_TEST(test_Msk_rshift_int8);
#endif

	CPPUNIT_TEST(test_reg_rshift_int16);
	CPPUNIT_TEST(test_Reg_rshift_int16);
#if !defined(MIPP_AVX) && !defined(MIPP_AVX512)
	CPPUNIT_TEST(test_msk_rshift_int16);
	CPPUNIT_TEST(test_Msk_rshift_int16);
#endif
#endif

	CPPUNIT_TEST(test_reg_rshift_int32);
	CPPUNIT_TEST(test_Reg_rshift_int32);
#if !defined(MIPP_AVX) && !defined(MIPP_AVX512)
	CPPUNIT_TEST(test_msk_rshift_int32);
	CPPUNIT_TEST(test_Msk_rshift_int32);
#endif

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_rshift_int64);
	CPPUNIT_TEST(test_Reg_rshift_int64);
#if !defined(MIPP_AVX) && !defined(MIPP_AVX512)
	CPPUNIT_TEST(test_msk_rshift_int64);
	CPPUNIT_TEST(test_Msk_rshift_int64);
#endif
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_reg_rshift_int8();
	void test_reg_rshift_int16();
	void test_reg_rshift_int32();
	void test_reg_rshift_int64();

	void test_Reg_rshift_int8();
	void test_Reg_rshift_int16();
	void test_Reg_rshift_int32();
	void test_Reg_rshift_int64();

	void test_msk_rshift_int8();
	void test_msk_rshift_int16();
	void test_msk_rshift_int32();
	void test_msk_rshift_int64();

	void test_Msk_rshift_int8();
	void test_Msk_rshift_int16();
	void test_Msk_rshift_int32();
	void test_Msk_rshift_int64();
};

#endif  // RSHIFTTEST_HPP_
