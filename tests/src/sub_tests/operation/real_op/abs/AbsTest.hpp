#ifndef ABSTEST_HPP_
#define ABSTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class AbsTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AbsTest);

	CPPUNIT_TEST(test_reg_abs_int8);
	CPPUNIT_TEST(test_reg_abs_int16);
	CPPUNIT_TEST(test_reg_abs_int32);
//	CPPUNIT_TEST(test_reg_abs_int64);
	CPPUNIT_TEST(test_reg_abs_float);
	CPPUNIT_TEST(test_reg_abs_double);

	CPPUNIT_TEST(test_Reg_abs_int8);
	CPPUNIT_TEST(test_Reg_abs_int16);
	CPPUNIT_TEST(test_Reg_abs_int32);
//	CPPUNIT_TEST(test_Reg_abs_int64);
	CPPUNIT_TEST(test_Reg_abs_float);
	CPPUNIT_TEST(test_Reg_abs_double);

	CPPUNIT_TEST(test_reg_maskz_abs_int8);
	CPPUNIT_TEST(test_reg_maskz_abs_int16);
	CPPUNIT_TEST(test_reg_maskz_abs_int32);
//	CPPUNIT_TEST(test_reg_maskz_abs_int64);
	CPPUNIT_TEST(test_reg_maskz_abs_float);
	CPPUNIT_TEST(test_reg_maskz_abs_double);

	CPPUNIT_TEST(test_Reg_maskz_abs_int8);
	CPPUNIT_TEST(test_Reg_maskz_abs_int16);
	CPPUNIT_TEST(test_Reg_maskz_abs_int32);
//	CPPUNIT_TEST(test_Reg_maskz_abs_int64);
	CPPUNIT_TEST(test_Reg_maskz_abs_float);
	CPPUNIT_TEST(test_Reg_maskz_abs_double);

	CPPUNIT_TEST(test_reg_mask_abs_int8);
	CPPUNIT_TEST(test_reg_mask_abs_int16);
	CPPUNIT_TEST(test_reg_mask_abs_int32);
//	CPPUNIT_TEST(test_reg_mask_abs_int64);
	CPPUNIT_TEST(test_reg_mask_abs_float);
	CPPUNIT_TEST(test_reg_mask_abs_double);

	CPPUNIT_TEST(test_Reg_mask_abs_int8);
	CPPUNIT_TEST(test_Reg_mask_abs_int16);
	CPPUNIT_TEST(test_Reg_mask_abs_int32);
//	CPPUNIT_TEST(test_Reg_mask_abs_int64);
	CPPUNIT_TEST(test_Reg_mask_abs_float);
	CPPUNIT_TEST(test_Reg_mask_abs_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_abs();
	void test_reg_abs_int8();
	void test_reg_abs_int16();
	void test_reg_abs_int32();
	void test_reg_abs_int64();
	void test_reg_abs_float();
	void test_reg_abs_double();

	template <typename T>
	void test_Reg_abs();
	void test_Reg_abs_int8();
	void test_Reg_abs_int16();
	void test_Reg_abs_int32();
	void test_Reg_abs_int64();
	void test_Reg_abs_float();
	void test_Reg_abs_double();

	template <typename T>
	void test_reg_maskz_abs();
	void test_reg_maskz_abs_int8();
	void test_reg_maskz_abs_int16();
	void test_reg_maskz_abs_int32();
	void test_reg_maskz_abs_int64();
	void test_reg_maskz_abs_float();
	void test_reg_maskz_abs_double();

	template <typename T>
	void test_Reg_maskz_abs();
	void test_Reg_maskz_abs_int8();
	void test_Reg_maskz_abs_int16();
	void test_Reg_maskz_abs_int32();
	void test_Reg_maskz_abs_int64();
	void test_Reg_maskz_abs_float();
	void test_Reg_maskz_abs_double();

	template <typename T>
	void test_reg_mask_abs();
	void test_reg_mask_abs_int8();
	void test_reg_mask_abs_int16();
	void test_reg_mask_abs_int32();
	void test_reg_mask_abs_int64();
	void test_reg_mask_abs_float();
	void test_reg_mask_abs_double();

	template <typename T>
	void test_Reg_mask_abs();
	void test_Reg_mask_abs_int8();
	void test_Reg_mask_abs_int16();
	void test_Reg_mask_abs_int32();
	void test_Reg_mask_abs_int64();
	void test_Reg_mask_abs_float();
	void test_Reg_mask_abs_double();
};

#endif // ABSTEST_HPP_
