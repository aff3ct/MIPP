#ifndef XORTEST_HPP_
#define XORTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class XorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(XorTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_xor_int8);
#endif
	CPPUNIT_TEST(test_Reg_xor_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_xor_int8);
#endif
	CPPUNIT_TEST(test_Msk_xor_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_xor_int16);
#endif
	CPPUNIT_TEST(test_Reg_xor_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_xor_int16);
#endif
	CPPUNIT_TEST(test_Msk_xor_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_xor_int32);
#endif
	CPPUNIT_TEST(test_Reg_xor_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_xor_int32);
#endif
	CPPUNIT_TEST(test_Msk_xor_int32);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_xor_int64);
#endif
	CPPUNIT_TEST(test_Reg_xor_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_xor_int64);
#endif
	CPPUNIT_TEST(test_Msk_xor_int64);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_xor();
	void test_reg_xor_int8();
	void test_reg_xor_int16();
	void test_reg_xor_int32();
	void test_reg_xor_int64();

	template <typename T>
	void test_Reg_xor();
	void test_Reg_xor_int8();
	void test_Reg_xor_int16();
	void test_Reg_xor_int32();
	void test_Reg_xor_int64();

	template <typename T>
	void test_msk_xor();
	void test_msk_xor_int8();
	void test_msk_xor_int16();
	void test_msk_xor_int32();
	void test_msk_xor_int64();

	template <typename T>
	void test_Msk_xor();
	void test_Msk_xor_int8();
	void test_Msk_xor_int16();
	void test_Msk_xor_int32();
	void test_Msk_xor_int64();
};

#endif  // XORTEST_HPP_
