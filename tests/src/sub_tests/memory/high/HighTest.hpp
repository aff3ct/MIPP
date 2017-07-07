#ifndef HIGHTEST_HPP_
#define HIGHTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class HighTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(HighTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_int8);
#endif
	CPPUNIT_TEST(test_Reg_high_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_int16);
#endif
	CPPUNIT_TEST(test_Reg_high_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_int32);
#endif
	CPPUNIT_TEST(test_Reg_high_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_float);
#endif
	CPPUNIT_TEST(test_Reg_high_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_int64);
#endif
	CPPUNIT_TEST(test_Reg_high_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_high_double);
#endif
	CPPUNIT_TEST(test_Reg_high_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_high();
	void test_reg_high_int8();
	void test_reg_high_int16();
	void test_reg_high_int32();
	void test_reg_high_int64();
	void test_reg_high_float();
	void test_reg_high_double();

	template <typename T>
	void test_Reg_high();
	void test_Reg_high_int8();
	void test_Reg_high_int16();
	void test_Reg_high_int32();
	void test_Reg_high_int64();
	void test_Reg_high_float();
	void test_Reg_high_double();
};

#endif  // HIGHTEST_HPP_
