#ifndef SUFFTEST_HPP_
#define SUFFTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class ShuffTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ShuffTest);

	CPPUNIT_TEST(test_reg_shuff_int8);
	CPPUNIT_TEST(test_reg_shuff_int16);
	CPPUNIT_TEST(test_reg_shuff_int32);
	CPPUNIT_TEST(test_reg_shuff_int64);
	CPPUNIT_TEST(test_reg_shuff_float);
	CPPUNIT_TEST(test_reg_shuff_double);

	CPPUNIT_TEST(test_Reg_shuff_int8);
	CPPUNIT_TEST(test_Reg_shuff_int16);
	CPPUNIT_TEST(test_Reg_shuff_int32);
	CPPUNIT_TEST(test_Reg_shuff_int64);
	CPPUNIT_TEST(test_Reg_shuff_float);
	CPPUNIT_TEST(test_Reg_shuff_double);

	CPPUNIT_TEST(test_reg_shuff2_int8);
	CPPUNIT_TEST(test_reg_shuff2_int16);
	CPPUNIT_TEST(test_reg_shuff2_int32);
	CPPUNIT_TEST(test_reg_shuff2_int64);
	CPPUNIT_TEST(test_reg_shuff2_float);
	CPPUNIT_TEST(test_reg_shuff2_double);

	CPPUNIT_TEST(test_Reg_shuff2_int8);
	CPPUNIT_TEST(test_Reg_shuff2_int16);
	CPPUNIT_TEST(test_Reg_shuff2_int32);
	CPPUNIT_TEST(test_Reg_shuff2_int64);
	CPPUNIT_TEST(test_Reg_shuff2_float);
	CPPUNIT_TEST(test_Reg_shuff2_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_shuff();
	void test_reg_shuff_int8();
	void test_reg_shuff_int16();
	void test_reg_shuff_int32();
	void test_reg_shuff_int64();
	void test_reg_shuff_float();
	void test_reg_shuff_double();

	template <typename T>
	void test_Reg_shuff();
	void test_Reg_shuff_int8();
	void test_Reg_shuff_int16();
	void test_Reg_shuff_int32();
	void test_Reg_shuff_int64();
	void test_Reg_shuff_float();
	void test_Reg_shuff_double();

	template <typename T>
	void test_reg_shuff2();
	void test_reg_shuff2_int8();
	void test_reg_shuff2_int16();
	void test_reg_shuff2_int32();
	void test_reg_shuff2_int64();
	void test_reg_shuff2_float();
	void test_reg_shuff2_double();

	template <typename T>
	void test_Reg_shuff2();
	void test_Reg_shuff2_int8();
	void test_Reg_shuff2_int16();
	void test_Reg_shuff2_int32();
	void test_Reg_shuff2_int64();
	void test_Reg_shuff2_float();
	void test_Reg_shuff2_double();
};

#endif  // SUFFTEST_HPP_
