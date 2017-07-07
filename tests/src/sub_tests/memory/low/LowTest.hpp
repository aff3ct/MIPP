#ifndef LOWTEST_HPP_
#define LOWTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class LowTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(LowTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_int8);
#endif
	CPPUNIT_TEST(test_Reg_low_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_int16);
#endif
	CPPUNIT_TEST(test_Reg_low_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_int32);
#endif
	CPPUNIT_TEST(test_Reg_low_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_float);
#endif
	CPPUNIT_TEST(test_Reg_low_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_int64);
#endif
	CPPUNIT_TEST(test_Reg_low_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_low_double);
#endif
	CPPUNIT_TEST(test_Reg_low_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_low();
	void test_reg_low_int8();
	void test_reg_low_int16();
	void test_reg_low_int32();
	void test_reg_low_int64();
	void test_reg_low_float();
	void test_reg_low_double();

	template <typename T>
	void test_Reg_low();
	void test_Reg_low_int8();
	void test_Reg_low_int16();
	void test_Reg_low_int32();
	void test_Reg_low_int64();
	void test_Reg_low_float();
	void test_Reg_low_double();
};

#endif  // LOWTEST_HPP_
