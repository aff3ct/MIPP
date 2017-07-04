#ifndef MULTEST_HPP_
#define MULTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class MulTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MulTest);

#if defined(MIPP_BW)
//	CPPUNIT_TEST(test_reg_mul_int8);
//	CPPUNIT_TEST(test_Reg_mul_int8);
//	CPPUNIT_TEST(test_reg_maskz_mul_int8);
//	CPPUNIT_TEST(test_Reg_maskz_mul_int8);
//	CPPUNIT_TEST(test_reg_mask_mul_int8);
//	CPPUNIT_TEST(test_Reg_mask_mul_int8);

//	CPPUNIT_TEST(test_reg_mul_int16);
//	CPPUNIT_TEST(test_Reg_mul_int16);
//	CPPUNIT_TEST(test_reg_maskz_mul_int16);
//	CPPUNIT_TEST(test_Reg_maskz_mul_int16);
//	CPPUNIT_TEST(test_reg_mask_mul_int16);
//	CPPUNIT_TEST(test_Reg_mask_mul_int16);
#endif

//	CPPUNIT_TEST(test_reg_mul_int32);
//	CPPUNIT_TEST(test_Reg_mul_int32);
//	CPPUNIT_TEST(test_reg_maskz_mul_int32);
//	CPPUNIT_TEST(test_Reg_maskz_mul_int32);
//	CPPUNIT_TEST(test_reg_mask_mul_int32);
//	CPPUNIT_TEST(test_Reg_mask_mul_int32);

	CPPUNIT_TEST(test_reg_mul_float);
	CPPUNIT_TEST(test_Reg_mul_float);
	CPPUNIT_TEST(test_reg_maskz_mul_float);
	CPPUNIT_TEST(test_Reg_maskz_mul_float);
	CPPUNIT_TEST(test_reg_mask_mul_float);
	CPPUNIT_TEST(test_Reg_mask_mul_float);

#if defined(MIPP_64BIT)
//	CPPUNIT_TEST(test_reg_mul_int64);
//	CPPUNIT_TEST(test_Reg_mul_int64);
//	CPPUNIT_TEST(test_reg_maskz_mul_int64);
//	CPPUNIT_TEST(test_Reg_maskz_mul_int64);
//	CPPUNIT_TEST(test_reg_mask_mul_int64);
//	CPPUNIT_TEST(test_Reg_mask_mul_int64);

	CPPUNIT_TEST(test_reg_mul_double);
	CPPUNIT_TEST(test_Reg_mul_double);
	CPPUNIT_TEST(test_reg_maskz_mul_double);
	CPPUNIT_TEST(test_Reg_maskz_mul_double);
	CPPUNIT_TEST(test_reg_mask_mul_double);
	CPPUNIT_TEST(test_Reg_mask_mul_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_mul();
	void test_reg_mul_int8();
	void test_reg_mul_int16();
	void test_reg_mul_int32();
	void test_reg_mul_int64();
	void test_reg_mul_float();
	void test_reg_mul_double();

	template <typename T>
	void test_Reg_mul();
	void test_Reg_mul_int8();
	void test_Reg_mul_int16();
	void test_Reg_mul_int32();
	void test_Reg_mul_int64();
	void test_Reg_mul_float();
	void test_Reg_mul_double();

	template <typename T>
	void test_reg_maskz_mul();
	void test_reg_maskz_mul_int8();
	void test_reg_maskz_mul_int16();
	void test_reg_maskz_mul_int32();
	void test_reg_maskz_mul_int64();
	void test_reg_maskz_mul_float();
	void test_reg_maskz_mul_double();

	template <typename T>
	void test_Reg_maskz_mul();
	void test_Reg_maskz_mul_int8();
	void test_Reg_maskz_mul_int16();
	void test_Reg_maskz_mul_int32();
	void test_Reg_maskz_mul_int64();
	void test_Reg_maskz_mul_float();
	void test_Reg_maskz_mul_double();

	template <typename T>
	void test_reg_mask_mul();
	void test_reg_mask_mul_int8();
	void test_reg_mask_mul_int16();
	void test_reg_mask_mul_int32();
	void test_reg_mask_mul_int64();
	void test_reg_mask_mul_float();
	void test_reg_mask_mul_double();

	template <typename T>
	void test_Reg_mask_mul();
	void test_Reg_mask_mul_int8();
	void test_Reg_mask_mul_int16();
	void test_Reg_mask_mul_int32();
	void test_Reg_mask_mul_int64();
	void test_Reg_mask_mul_float();
	void test_Reg_mask_mul_double();
};

#endif // MULTEST_HPP_
