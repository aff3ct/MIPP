#ifndef ANDTEST_HPP_
#define ANDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class AndTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AndTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_and_int8);
#endif
	CPPUNIT_TEST(test_Reg_and_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_and_int8);
#endif
	CPPUNIT_TEST(test_Msk_and_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_and_int16);
#endif
	CPPUNIT_TEST(test_Reg_and_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_and_int16);
#endif
	CPPUNIT_TEST(test_Msk_and_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_and_int32);
#endif
	CPPUNIT_TEST(test_Reg_and_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_and_int32);
#endif
	CPPUNIT_TEST(test_Msk_and_int32);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_and_int64);
#endif
	CPPUNIT_TEST(test_Reg_and_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_and_int64);
#endif
	CPPUNIT_TEST(test_Msk_and_int64);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_and();
	void test_reg_and_int8();
	void test_reg_and_int16();
	void test_reg_and_int32();
	void test_reg_and_int64();

	template <typename T>
	void test_Reg_and();
	void test_Reg_and_int8();
	void test_Reg_and_int16();
	void test_Reg_and_int32();
	void test_Reg_and_int64();

	template <typename T>
	void test_msk_and();
	void test_msk_and_int8();
	void test_msk_and_int16();
	void test_msk_and_int32();
	void test_msk_and_int64();

	template <typename T>
	void test_Msk_and();
	void test_Msk_and_int8();
	void test_Msk_and_int16();
	void test_Msk_and_int32();
	void test_Msk_and_int64();
};

#endif  // ANDTEST_HPP_
