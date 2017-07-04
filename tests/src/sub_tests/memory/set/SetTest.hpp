#ifndef SETTEST_HPP_
#define SETTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SetTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SetTest);

#if defined(MIPP_BW)
	CPPUNIT_TEST(test_reg_set1_int8);
	CPPUNIT_TEST(test_reg_set0_int8);
	CPPUNIT_TEST(test_reg_set_int8);
	CPPUNIT_TEST(test_Reg_set1_int8);
	CPPUNIT_TEST(test_Reg_set0_int8);
	CPPUNIT_TEST(test_Reg_set_int8);
	CPPUNIT_TEST(test_msk_set1_int8);
	CPPUNIT_TEST(test_msk_set0_int8);
	CPPUNIT_TEST(test_msk_set_int8);
	CPPUNIT_TEST(test_Msk_set1_int8);
	CPPUNIT_TEST(test_Msk_set0_int8);
	CPPUNIT_TEST(test_Msk_set_int8);

	CPPUNIT_TEST(test_reg_set1_int16);
	CPPUNIT_TEST(test_reg_set0_int16);
	CPPUNIT_TEST(test_reg_set_int16);
	CPPUNIT_TEST(test_Reg_set1_int16);
	CPPUNIT_TEST(test_Reg_set0_int16);
	CPPUNIT_TEST(test_Reg_set_int16);
	CPPUNIT_TEST(test_msk_set1_int16);
	CPPUNIT_TEST(test_msk_set0_int16);
	CPPUNIT_TEST(test_msk_set_int16);
	CPPUNIT_TEST(test_Msk_set1_int16);
	CPPUNIT_TEST(test_Msk_set0_int16);
	CPPUNIT_TEST(test_Msk_set_int16);
#endif

	CPPUNIT_TEST(test_reg_set1_int32);
	CPPUNIT_TEST(test_reg_set0_int32);
	CPPUNIT_TEST(test_reg_set_int32);
	CPPUNIT_TEST(test_Reg_set1_int32);
	CPPUNIT_TEST(test_Reg_set0_int32);
	CPPUNIT_TEST(test_Reg_set_int32);
	CPPUNIT_TEST(test_msk_set1_int32);
	CPPUNIT_TEST(test_msk_set0_int32);
	CPPUNIT_TEST(test_msk_set_int32);
	CPPUNIT_TEST(test_Msk_set1_int32);
	CPPUNIT_TEST(test_Msk_set0_int32);
	CPPUNIT_TEST(test_Msk_set_int32);

	CPPUNIT_TEST(test_reg_set1_float);
	CPPUNIT_TEST(test_reg_set0_float);
	CPPUNIT_TEST(test_reg_set_float);
	CPPUNIT_TEST(test_Reg_set1_float);
	CPPUNIT_TEST(test_Reg_set0_float);
	CPPUNIT_TEST(test_Reg_set_float);
	CPPUNIT_TEST(test_msk_set1_float);
	CPPUNIT_TEST(test_msk_set0_float);
	CPPUNIT_TEST(test_msk_set_float);
	CPPUNIT_TEST(test_Msk_set1_float);
	CPPUNIT_TEST(test_Msk_set0_float);
	CPPUNIT_TEST(test_Msk_set_float);

#if defined(MIPP_64BIT)
	CPPUNIT_TEST(test_reg_set1_int64);
	CPPUNIT_TEST(test_reg_set0_int64);
	CPPUNIT_TEST(test_Reg_set1_int64);
	CPPUNIT_TEST(test_reg_set_int64);
	CPPUNIT_TEST(test_Reg_set0_int64);
	CPPUNIT_TEST(test_Reg_set_int64);
	CPPUNIT_TEST(test_msk_set1_int64);
	CPPUNIT_TEST(test_msk_set0_int64);
	CPPUNIT_TEST(test_msk_set_int64);
	CPPUNIT_TEST(test_Msk_set1_int64);
	CPPUNIT_TEST(test_Msk_set0_int64);
	CPPUNIT_TEST(test_Msk_set_int64);

	CPPUNIT_TEST(test_reg_set1_double);
	CPPUNIT_TEST(test_reg_set0_double);
	CPPUNIT_TEST(test_reg_set_double);
	CPPUNIT_TEST(test_Reg_set1_double);
	CPPUNIT_TEST(test_Reg_set0_double);
	CPPUNIT_TEST(test_Reg_set_double);
	CPPUNIT_TEST(test_msk_set1_double);
	CPPUNIT_TEST(test_msk_set0_double);
	CPPUNIT_TEST(test_msk_set_double);
	CPPUNIT_TEST(test_Msk_set1_double);
	CPPUNIT_TEST(test_Msk_set0_double);
	CPPUNIT_TEST(test_Msk_set_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_set1();
	void test_reg_set1_int8();
	void test_reg_set1_int16();
	void test_reg_set1_int32();
	void test_reg_set1_int64();
	void test_reg_set1_float();
	void test_reg_set1_double();

	template <typename T>
	void test_reg_set0();
	void test_reg_set0_int8();
	void test_reg_set0_int16();
	void test_reg_set0_int32();
	void test_reg_set0_int64();
	void test_reg_set0_float();
	void test_reg_set0_double();

	template <typename T>
	void test_reg_set();
	void test_reg_set_int8();
	void test_reg_set_int16();
	void test_reg_set_int32();
	void test_reg_set_int64();
	void test_reg_set_float();
	void test_reg_set_double();

	template <typename T>
	void test_Reg_set1();
	void test_Reg_set1_int8();
	void test_Reg_set1_int16();
	void test_Reg_set1_int32();
	void test_Reg_set1_int64();
	void test_Reg_set1_float();
	void test_Reg_set1_double();

	template <typename T>
	void test_Reg_set0();
	void test_Reg_set0_int8();
	void test_Reg_set0_int16();
	void test_Reg_set0_int32();
	void test_Reg_set0_int64();
	void test_Reg_set0_float();
	void test_Reg_set0_double();

	template <typename T>
	void test_Reg_set();
	void test_Reg_set_int8();
	void test_Reg_set_int16();
	void test_Reg_set_int32();
	void test_Reg_set_int64();
	void test_Reg_set_float();
	void test_Reg_set_double();

	template <typename T>
	void test_msk_set1();
	void test_msk_set1_int8();
	void test_msk_set1_int16();
	void test_msk_set1_int32();
	void test_msk_set1_int64();
	void test_msk_set1_float();
	void test_msk_set1_double();

	template <typename T>
	void test_msk_set0();
	void test_msk_set0_int8();
	void test_msk_set0_int16();
	void test_msk_set0_int32();
	void test_msk_set0_int64();
	void test_msk_set0_float();
	void test_msk_set0_double();

	template <typename T>
	void test_msk_set();
	void test_msk_set_int8();
	void test_msk_set_int16();
	void test_msk_set_int32();
	void test_msk_set_int64();
	void test_msk_set_float();
	void test_msk_set_double();

	template <typename T>
	void test_Msk_set1();
	void test_Msk_set1_int8();
	void test_Msk_set1_int16();
	void test_Msk_set1_int32();
	void test_Msk_set1_int64();
	void test_Msk_set1_float();
	void test_Msk_set1_double();

	template <typename T>
	void test_Msk_set0();
	void test_Msk_set0_int8();
	void test_Msk_set0_int16();
	void test_Msk_set0_int32();
	void test_Msk_set0_int64();
	void test_Msk_set0_float();
	void test_Msk_set0_double();

	template <typename T>
	void test_Msk_set();
	void test_Msk_set_int8();
	void test_Msk_set_int16();
	void test_Msk_set_int32();
	void test_Msk_set_int64();
	void test_Msk_set_float();
	void test_Msk_set_double();
};

#endif  // SETTEST_HPP_
