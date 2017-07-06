#ifndef INTERLEAVELOTEST_HPP_
#define INTERLEAVELOTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleaveloTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleaveloTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_interleavelo_int8);
	CPPUNIT_TEST(test_Reg_interleavelo_int8);
	CPPUNIT_TEST(test_reg_interleavelo2_int8);
	CPPUNIT_TEST(test_Reg_interleavelo2_int8);

	CPPUNIT_TEST(test_reg_interleavelo_int16);
	CPPUNIT_TEST(test_Reg_interleavelo_int16);
	CPPUNIT_TEST(test_reg_interleavelo2_int16);
	CPPUNIT_TEST(test_Reg_interleavelo2_int16);
#endif

	CPPUNIT_TEST(test_reg_interleavelo_int32);
	CPPUNIT_TEST(test_Reg_interleavelo_int32);
	CPPUNIT_TEST(test_reg_interleavelo2_int32);
	CPPUNIT_TEST(test_Reg_interleavelo2_int32);

	CPPUNIT_TEST(test_reg_interleavelo_float);
	CPPUNIT_TEST(test_Reg_interleavelo_float);
	CPPUNIT_TEST(test_reg_interleavelo2_float);
	CPPUNIT_TEST(test_Reg_interleavelo2_float);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_interleavelo_int64);
	CPPUNIT_TEST(test_Reg_interleavelo_int64);
	CPPUNIT_TEST(test_reg_interleavelo2_int64);
	CPPUNIT_TEST(test_Reg_interleavelo2_int64);

	CPPUNIT_TEST(test_reg_interleavelo_double);
	CPPUNIT_TEST(test_Reg_interleavelo_double);
	CPPUNIT_TEST(test_reg_interleavelo2_double);
	CPPUNIT_TEST(test_Reg_interleavelo2_double);
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
};

#endif  // INTERLEAVELOTEST_HPP_
