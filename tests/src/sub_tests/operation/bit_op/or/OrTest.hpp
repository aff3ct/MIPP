#ifndef ORTEST_HPP_
#define ORTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class OrTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(OrTest);

#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_or_int8);
	CPPUNIT_TEST(test_Reg_or_int8);
	CPPUNIT_TEST(test_msk_or_int8);
	CPPUNIT_TEST(test_Msk_or_int8);

	CPPUNIT_TEST(test_reg_or_int16);
	CPPUNIT_TEST(test_Reg_or_int16);
	CPPUNIT_TEST(test_msk_or_int16);
	CPPUNIT_TEST(test_Msk_or_int16);
#endif

	CPPUNIT_TEST(test_reg_or_int32);
	CPPUNIT_TEST(test_Reg_or_int32);
	CPPUNIT_TEST(test_msk_or_int32);
	CPPUNIT_TEST(test_Msk_or_int32);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_or_int64);
	CPPUNIT_TEST(test_Reg_or_int64);
	CPPUNIT_TEST(test_msk_or_int64);
	CPPUNIT_TEST(test_Msk_or_int64);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_or();
	void test_reg_or_int8();
	void test_reg_or_int16();
	void test_reg_or_int32();
	void test_reg_or_int64();

	template <typename T>
	void test_Reg_or();
	void test_Reg_or_int8();
	void test_Reg_or_int16();
	void test_Reg_or_int32();
	void test_Reg_or_int64();

	template <typename T>
	void test_msk_or();
	void test_msk_or_int8();
	void test_msk_or_int16();
	void test_msk_or_int32();
	void test_msk_or_int64();

	template <typename T>
	void test_Msk_or();
	void test_Msk_or_int8();
	void test_Msk_or_int16();
	void test_Msk_or_int32();
	void test_Msk_or_int64();
};

#endif  // ORTEST_HPP_
