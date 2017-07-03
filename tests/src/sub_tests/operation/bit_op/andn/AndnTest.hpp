#ifndef ANDNTEST_HPP_
#define ANDNTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class AndnTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AndnTest);

	CPPUNIT_TEST(test_reg_andn_int8);
	CPPUNIT_TEST(test_reg_andn_int16);
	CPPUNIT_TEST(test_reg_andn_int32);
	CPPUNIT_TEST(test_reg_andn_int64);

	CPPUNIT_TEST(test_Reg_andn_int8);
	CPPUNIT_TEST(test_Reg_andn_int16);
	CPPUNIT_TEST(test_Reg_andn_int32);
	CPPUNIT_TEST(test_Reg_andn_int64);

	CPPUNIT_TEST(test_msk_andn_int8);
	CPPUNIT_TEST(test_msk_andn_int16);
	CPPUNIT_TEST(test_msk_andn_int32);
	CPPUNIT_TEST(test_msk_andn_int64);

	CPPUNIT_TEST(test_Msk_andn_int8);
	CPPUNIT_TEST(test_Msk_andn_int16);
	CPPUNIT_TEST(test_Msk_andn_int32);
	CPPUNIT_TEST(test_Msk_andn_int64);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_andn();
	void test_reg_andn_int8();
	void test_reg_andn_int16();
	void test_reg_andn_int32();
	void test_reg_andn_int64();

	template <typename T>
	void test_Reg_andn();
	void test_Reg_andn_int8();
	void test_Reg_andn_int16();
	void test_Reg_andn_int32();
	void test_Reg_andn_int64();

	template <typename T>
	void test_msk_andn();
	void test_msk_andn_int8();
	void test_msk_andn_int16();
	void test_msk_andn_int32();
	void test_msk_andn_int64();

	template <typename T>
	void test_Msk_andn();
	void test_Msk_andn_int8();
	void test_Msk_andn_int16();
	void test_Msk_andn_int32();
	void test_Msk_andn_int64();
};

#endif  // ANDNTEST_HPP_
