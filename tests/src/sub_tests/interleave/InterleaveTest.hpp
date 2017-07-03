#ifndef INTERLEAVETEST_HPP_
#define INTERLEAVETEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleaveTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleaveTest);

	CPPUNIT_TEST(test_reg_interleave_int8);
	CPPUNIT_TEST(test_reg_interleave_int16);
	CPPUNIT_TEST(test_reg_interleave_int32);
	CPPUNIT_TEST(test_reg_interleave_int64);
	CPPUNIT_TEST(test_reg_interleave_float);
	CPPUNIT_TEST(test_reg_interleave_double);

	CPPUNIT_TEST(test_Reg_interleave_int8);
	CPPUNIT_TEST(test_Reg_interleave_int16);
	CPPUNIT_TEST(test_Reg_interleave_int32);
	CPPUNIT_TEST(test_Reg_interleave_int64);
	CPPUNIT_TEST(test_Reg_interleave_float);
	CPPUNIT_TEST(test_Reg_interleave_double);

	CPPUNIT_TEST(test_reg_interleave2_int8);
	CPPUNIT_TEST(test_reg_interleave2_int16);
	CPPUNIT_TEST(test_reg_interleave2_int32);
	CPPUNIT_TEST(test_reg_interleave2_int64);
	CPPUNIT_TEST(test_reg_interleave2_float);
	CPPUNIT_TEST(test_reg_interleave2_double);

	CPPUNIT_TEST(test_Reg_interleave2_int8);
	CPPUNIT_TEST(test_Reg_interleave2_int16);
	CPPUNIT_TEST(test_Reg_interleave2_int32);
	CPPUNIT_TEST(test_Reg_interleave2_int64);
	CPPUNIT_TEST(test_Reg_interleave2_float);
	CPPUNIT_TEST(test_Reg_interleave2_double);

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
