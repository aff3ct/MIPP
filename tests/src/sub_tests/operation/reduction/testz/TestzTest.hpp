#ifndef TESTZTEST_HPP_
#define TESTZTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class TestzTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestzTest);

#if defined(MIPP_BW)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 31)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_testz_int8);
#endif
	CPPUNIT_TEST(test_Reg_testz_int8);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_testz_int8);
#endif
	CPPUNIT_TEST(test_Msk_testz_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_testz_int16);
#endif
	CPPUNIT_TEST(test_Reg_testz_int16);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_testz_int16);
#endif
	CPPUNIT_TEST(test_Msk_testz_int16);
#endif
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_testz_int32);
#endif
	CPPUNIT_TEST(test_Reg_testz_int32);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_testz_int32);
#endif
	CPPUNIT_TEST(test_Msk_testz_int32);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_testz_int64);
#endif
	CPPUNIT_TEST(test_Reg_testz_int64);
#ifndef MIPP_NO
	CPPUNIT_TEST(test_msk_testz_int64);
#endif
	CPPUNIT_TEST(test_Msk_testz_int64);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_testz_int();
	void test_reg_testz_int8();
	void test_reg_testz_int16();
	void test_reg_testz_int32();
	void test_reg_testz_int64();

	template <typename T>
	void test_Reg_testz_int();
	void test_Reg_testz_int8();
	void test_Reg_testz_int16();
	void test_Reg_testz_int32();
	void test_Reg_testz_int64();

	template <typename T>
	void test_msk_testz_int();
	void test_msk_testz_int8();
	void test_msk_testz_int16();
	void test_msk_testz_int32();
	void test_msk_testz_int64();

	template <typename T>
	void test_Msk_testz_int();
	void test_Msk_testz_int8();
	void test_Msk_testz_int16();
	void test_Msk_testz_int32();
	void test_Msk_testz_int64();
};

#endif // TESTZTEST_HPP_
