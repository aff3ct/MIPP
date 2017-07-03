#ifndef ADDTEST_HPP_
#define ADDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class AddTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AddTest);

	CPPUNIT_TEST(test_reg_add_int8);
	CPPUNIT_TEST(test_reg_add_int16);
	CPPUNIT_TEST(test_reg_add_int32);
	CPPUNIT_TEST(test_reg_add_int64);
	CPPUNIT_TEST(test_reg_add_float);
	CPPUNIT_TEST(test_reg_add_double);

	CPPUNIT_TEST(test_Reg_add_int8);
	CPPUNIT_TEST(test_Reg_add_int16);
	CPPUNIT_TEST(test_Reg_add_int32);
	CPPUNIT_TEST(test_Reg_add_int64);
	CPPUNIT_TEST(test_Reg_add_float);
	CPPUNIT_TEST(test_Reg_add_double);

	CPPUNIT_TEST(test_reg_maskz_add_int8);
	CPPUNIT_TEST(test_reg_maskz_add_int16);
	CPPUNIT_TEST(test_reg_maskz_add_int32);
	CPPUNIT_TEST(test_reg_maskz_add_int64);
	CPPUNIT_TEST(test_reg_maskz_add_float);
	CPPUNIT_TEST(test_reg_maskz_add_double);

	CPPUNIT_TEST(test_Reg_maskz_add_int8);
	CPPUNIT_TEST(test_Reg_maskz_add_int16);
	CPPUNIT_TEST(test_Reg_maskz_add_int32);
	CPPUNIT_TEST(test_Reg_maskz_add_int64);
	CPPUNIT_TEST(test_Reg_maskz_add_float);
	CPPUNIT_TEST(test_Reg_maskz_add_double);

	CPPUNIT_TEST(test_reg_mask_add_int8);
	CPPUNIT_TEST(test_reg_mask_add_int16);
	CPPUNIT_TEST(test_reg_mask_add_int32);
	CPPUNIT_TEST(test_reg_mask_add_int64);
	CPPUNIT_TEST(test_reg_mask_add_float);
	CPPUNIT_TEST(test_reg_mask_add_double);

	CPPUNIT_TEST(test_Reg_mask_add_int8);
	CPPUNIT_TEST(test_Reg_mask_add_int16);
	CPPUNIT_TEST(test_Reg_mask_add_int32);
	CPPUNIT_TEST(test_Reg_mask_add_int64);
	CPPUNIT_TEST(test_Reg_mask_add_float);
	CPPUNIT_TEST(test_Reg_mask_add_double);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_add();
	void test_reg_add_int8();
	void test_reg_add_int16();
	void test_reg_add_int32();
	void test_reg_add_int64();
	void test_reg_add_float();
	void test_reg_add_double();

	template <typename T>
	void test_Reg_add();
	void test_Reg_add_int8();
	void test_Reg_add_int16();
	void test_Reg_add_int32();
	void test_Reg_add_int64();
	void test_Reg_add_float();
	void test_Reg_add_double();

	template <typename T>
	void test_reg_maskz_add();
	void test_reg_maskz_add_int8();
	void test_reg_maskz_add_int16();
	void test_reg_maskz_add_int32();
	void test_reg_maskz_add_int64();
	void test_reg_maskz_add_float();
	void test_reg_maskz_add_double();

	template <typename T>
	void test_Reg_maskz_add();
	void test_Reg_maskz_add_int8();
	void test_Reg_maskz_add_int16();
	void test_Reg_maskz_add_int32();
	void test_Reg_maskz_add_int64();
	void test_Reg_maskz_add_float();
	void test_Reg_maskz_add_double();

	template <typename T>
	void test_reg_mask_add();
	void test_reg_mask_add_int8();
	void test_reg_mask_add_int16();
	void test_reg_mask_add_int32();
	void test_reg_mask_add_int64();
	void test_reg_mask_add_float();
	void test_reg_mask_add_double();

	template <typename T>
	void test_Reg_mask_add();
	void test_Reg_mask_add_int8();
	void test_Reg_mask_add_int16();
	void test_Reg_mask_add_int32();
	void test_Reg_mask_add_int64();
	void test_Reg_mask_add_float();
	void test_Reg_mask_add_double();
};

#endif // ADDTEST_HPP_
