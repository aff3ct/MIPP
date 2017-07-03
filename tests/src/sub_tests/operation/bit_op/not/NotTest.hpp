#ifndef NOTTEST_HPP_
#define NOTTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class NotTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(NotTest);

	CPPUNIT_TEST(test_reg_not_int8);
	CPPUNIT_TEST(test_reg_not_int16);
	CPPUNIT_TEST(test_reg_not_int32);
	CPPUNIT_TEST(test_reg_not_int64);

	CPPUNIT_TEST(test_Reg_not_int8);
	CPPUNIT_TEST(test_Reg_not_int16);
	CPPUNIT_TEST(test_Reg_not_int32);
	CPPUNIT_TEST(test_Reg_not_int64);

	CPPUNIT_TEST(test_msk_not_int8);
	CPPUNIT_TEST(test_msk_not_int16);
	CPPUNIT_TEST(test_msk_not_int32);
	CPPUNIT_TEST(test_msk_not_int64);

	CPPUNIT_TEST(test_Msk_not_int8);
	CPPUNIT_TEST(test_Msk_not_int16);
	CPPUNIT_TEST(test_Msk_not_int32);
	CPPUNIT_TEST(test_Msk_not_int64);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_not();
	void test_reg_not_int8();
	void test_reg_not_int16();
	void test_reg_not_int32();
	void test_reg_not_int64();

	template <typename T>
	void test_Reg_not();
	void test_Reg_not_int8();
	void test_Reg_not_int16();
	void test_Reg_not_int32();
	void test_Reg_not_int64();

	template <typename T>
	void test_msk_not();
	void test_msk_not_int8();
	void test_msk_not_int16();
	void test_msk_not_int32();
	void test_msk_not_int64();

	template <typename T>
	void test_Msk_not();
	void test_Msk_not_int8();
	void test_Msk_not_int16();
	void test_Msk_not_int32();
	void test_Msk_not_int64();
};

#endif  // NOTTEST_HPP_
