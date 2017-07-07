#ifndef STORETEST_HPP_
#define STORETEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class StoreTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(StoreTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_int8);
	CPPUNIT_TEST(test_reg_storeu_int8);
#endif
	CPPUNIT_TEST(test_Reg_store_int8);
	CPPUNIT_TEST(test_Reg_storeu_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_int16);
	CPPUNIT_TEST(test_reg_storeu_int16);
#endif
	CPPUNIT_TEST(test_Reg_store_int16);
	CPPUNIT_TEST(test_Reg_storeu_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_int32);
	CPPUNIT_TEST(test_reg_storeu_int32);
#endif
	CPPUNIT_TEST(test_Reg_store_int32);
	CPPUNIT_TEST(test_Reg_storeu_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_float);
	CPPUNIT_TEST(test_reg_storeu_float);
#endif
	CPPUNIT_TEST(test_Reg_store_float);
	CPPUNIT_TEST(test_Reg_storeu_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_int64);
	CPPUNIT_TEST(test_reg_storeu_int64);
#endif
	CPPUNIT_TEST(test_Reg_store_int64);
	CPPUNIT_TEST(test_Reg_storeu_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_store_double);
	CPPUNIT_TEST(test_reg_storeu_double);
#endif
	CPPUNIT_TEST(test_Reg_store_double);
	CPPUNIT_TEST(test_Reg_storeu_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_store();
	void test_reg_store_int8();
	void test_reg_store_int16();
	void test_reg_store_int32();
	void test_reg_store_int64();
	void test_reg_store_float();
	void test_reg_store_double();

	template <typename T>
	void test_reg_storeu();
	void test_reg_storeu_int8();
	void test_reg_storeu_int16();
	void test_reg_storeu_int32();
	void test_reg_storeu_int64();
	void test_reg_storeu_float();
	void test_reg_storeu_double();

	template <typename T>
	void test_Reg_store();
	void test_Reg_store_int8();
	void test_Reg_store_int16();
	void test_Reg_store_int32();
	void test_Reg_store_int64();
	void test_Reg_store_float();
	void test_Reg_store_double();

	template <typename T>
	void test_Reg_storeu();
	void test_Reg_storeu_int8();
	void test_Reg_storeu_int16();
	void test_Reg_storeu_int32();
	void test_Reg_storeu_int64();
	void test_Reg_storeu_float();
	void test_Reg_storeu_double();
};

#endif  // STORETEST_HPP_
