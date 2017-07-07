#ifndef INTERLEAVETEST_HPP_
#define INTERLEAVETEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleaveTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleaveTest);

#if !defined(MIPP_AVX) || (defined(MIPP_AVX) && MIPP_INSTR_VERSION >= 2)
#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleave_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_int8);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleave_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_int16);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleave_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_int32);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_float);
#endif
	CPPUNIT_TEST(test_Reg_interleave_float);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_float);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleave_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_int64);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave_double);
#endif
	CPPUNIT_TEST(test_Reg_interleave_double);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_interleave2_double);
#endif
	CPPUNIT_TEST(test_Reg_interleave2_double);
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_interleave();
	void test_reg_interleave_int8();
	void test_reg_interleave_int16();
	void test_reg_interleave_int32();
	void test_reg_interleave_int64();
	void test_reg_interleave_float();
	void test_reg_interleave_double();

	template <typename T>
	void test_Reg_interleave();
	void test_Reg_interleave_int8();
	void test_Reg_interleave_int16();
	void test_Reg_interleave_int32();
	void test_Reg_interleave_int64();
	void test_Reg_interleave_float();
	void test_Reg_interleave_double();

	template <typename T>
	void test_reg_interleave2();
	void test_reg_interleave2_int8();
	void test_reg_interleave2_int16();
	void test_reg_interleave2_int32();
	void test_reg_interleave2_int64();
	void test_reg_interleave2_float();
	void test_reg_interleave2_double();

	template <typename T>
	void test_Reg_interleave2();
	void test_Reg_interleave2_int8();
	void test_Reg_interleave2_int16();
	void test_Reg_interleave2_int32();
	void test_Reg_interleave2_int64();
	void test_Reg_interleave2_float();
	void test_Reg_interleave2_double();
};

#endif  // INTERLEAVETEST_HPP_
