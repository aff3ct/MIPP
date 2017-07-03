#ifndef INTERLEAVEHITEST_HPP_
#define INTERLEAVEHITEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class InterleavehiTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InterleavehiTest);

	CPPUNIT_TEST(test_reg_interleavehi_int8);
	CPPUNIT_TEST(test_reg_interleavehi_int16);
	CPPUNIT_TEST(test_reg_interleavehi_int32);
	CPPUNIT_TEST(test_reg_interleavehi_int64);
	CPPUNIT_TEST(test_reg_interleavehi_float);
	CPPUNIT_TEST(test_reg_interleavehi_double);

	CPPUNIT_TEST(test_Reg_interleavehi_int8);
	CPPUNIT_TEST(test_Reg_interleavehi_int16);
	CPPUNIT_TEST(test_Reg_interleavehi_int32);
	CPPUNIT_TEST(test_Reg_interleavehi_int64);
	CPPUNIT_TEST(test_Reg_interleavehi_float);
	CPPUNIT_TEST(test_Reg_interleavehi_double);

	CPPUNIT_TEST(test_reg_interleavehi2_int8);
	CPPUNIT_TEST(test_reg_interleavehi2_int16);
	CPPUNIT_TEST(test_reg_interleavehi2_int32);
	CPPUNIT_TEST(test_reg_interleavehi2_int64);
	CPPUNIT_TEST(test_reg_interleavehi2_float);
	CPPUNIT_TEST(test_reg_interleavehi2_double);

	CPPUNIT_TEST(test_Reg_interleavehi2_int8);
	CPPUNIT_TEST(test_Reg_interleavehi2_int16);
	CPPUNIT_TEST(test_Reg_interleavehi2_int32);
	CPPUNIT_TEST(test_Reg_interleavehi2_int64);
	CPPUNIT_TEST(test_Reg_interleavehi2_float);
	CPPUNIT_TEST(test_Reg_interleavehi2_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_interleavehi();
	void test_reg_interleavehi_int8();
	void test_reg_interleavehi_int16();
	void test_reg_interleavehi_int32();
	void test_reg_interleavehi_int64();
	void test_reg_interleavehi_float();
	void test_reg_interleavehi_double();

	template <typename T>
	void test_Reg_interleavehi();
	void test_Reg_interleavehi_int8();
	void test_Reg_interleavehi_int16();
	void test_Reg_interleavehi_int32();
	void test_Reg_interleavehi_int64();
	void test_Reg_interleavehi_float();
	void test_Reg_interleavehi_double();

	template <typename T>
	void test_reg_interleavehi2();
	void test_reg_interleavehi2_int8();
	void test_reg_interleavehi2_int16();
	void test_reg_interleavehi2_int32();
	void test_reg_interleavehi2_int64();
	void test_reg_interleavehi2_float();
	void test_reg_interleavehi2_double();

	template <typename T>
	void test_Reg_interleavehi2();
	void test_Reg_interleavehi2_int8();
	void test_Reg_interleavehi2_int16();
	void test_Reg_interleavehi2_int32();
	void test_Reg_interleavehi2_int64();
	void test_Reg_interleavehi2_float();
	void test_Reg_interleavehi2_double();
};

#endif  // INTERLEAVEHITEST_HPP_
