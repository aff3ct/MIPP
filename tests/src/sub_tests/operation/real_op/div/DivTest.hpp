#ifndef DIVTEST_HPP_
#define DIVTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class DivTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(DivTest);

#if defined(MIPP_BW)
//	CPPUNIT_TEST(test_reg_div_int8);
//	CPPUNIT_TEST(test_Reg_div_int8);
//	CPPUNIT_TEST(test_reg_maskz_div_int8);
//	CPPUNIT_TEST(test_Reg_maskz_div_int8);
//	CPPUNIT_TEST(test_reg_mask_div_int8);
//	CPPUNIT_TEST(test_Reg_mask_div_int8);

//	CPPUNIT_TEST(test_reg_div_int16);
//	CPPUNIT_TEST(test_Reg_div_int16);
//	CPPUNIT_TEST(test_reg_maskz_div_int16);
//	CPPUNIT_TEST(test_Reg_maskz_div_int16);
//	CPPUNIT_TEST(test_reg_mask_div_int16);
//	CPPUNIT_TEST(test_Reg_mask_div_int16);
#endif

//	CPPUNIT_TEST(test_reg_div_int32);
//	CPPUNIT_TEST(test_Reg_div_int32);
//	CPPUNIT_TEST(test_reg_maskz_div_int32);
//	CPPUNIT_TEST(test_Reg_maskz_div_int32);
//	CPPUNIT_TEST(test_reg_mask_div_int32);
//	CPPUNIT_TEST(test_Reg_mask_div_int32);

	CPPUNIT_TEST(test_reg_div_float);
	CPPUNIT_TEST(test_Reg_div_float);
	CPPUNIT_TEST(test_reg_maskz_div_float);
	CPPUNIT_TEST(test_Reg_maskz_div_float);
	CPPUNIT_TEST(test_reg_mask_div_float);
	CPPUNIT_TEST(test_Reg_mask_div_float);

#if defined(MIPP_64BIT)
//	CPPUNIT_TEST(test_reg_div_int64);
//	CPPUNIT_TEST(test_Reg_div_int64);
//	CPPUNIT_TEST(test_reg_maskz_div_int64);
//	CPPUNIT_TEST(test_Reg_maskz_div_int64);
//	CPPUNIT_TEST(test_reg_mask_div_int64);
//	CPPUNIT_TEST(test_Reg_mask_div_int64);

	CPPUNIT_TEST(test_reg_div_double);
	CPPUNIT_TEST(test_Reg_div_double);
	CPPUNIT_TEST(test_reg_maskz_div_double);
	CPPUNIT_TEST(test_Reg_maskz_div_double);
	CPPUNIT_TEST(test_reg_mask_div_double);
	CPPUNIT_TEST(test_Reg_mask_div_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_div();
	void test_reg_div_int8();
	void test_reg_div_int16();
	void test_reg_div_int32();
	void test_reg_div_int64();
	void test_reg_div_float();
	void test_reg_div_double();

	template <typename T>
	void test_Reg_div();
	void test_Reg_div_int8();
	void test_Reg_div_int16();
	void test_Reg_div_int32();
	void test_Reg_div_int64();
	void test_Reg_div_float();
	void test_Reg_div_double();

	template <typename T>
	void test_reg_maskz_div();
	void test_reg_maskz_div_int8();
	void test_reg_maskz_div_int16();
	void test_reg_maskz_div_int32();
	void test_reg_maskz_div_int64();
	void test_reg_maskz_div_float();
	void test_reg_maskz_div_double();

	template <typename T>
	void test_Reg_maskz_div();
	void test_Reg_maskz_div_int8();
	void test_Reg_maskz_div_int16();
	void test_Reg_maskz_div_int32();
	void test_Reg_maskz_div_int64();
	void test_Reg_maskz_div_float();
	void test_Reg_maskz_div_double();

	template <typename T>
	void test_reg_mask_div();
	void test_reg_mask_div_int8();
	void test_reg_mask_div_int16();
	void test_reg_mask_div_int32();
	void test_reg_mask_div_int64();
	void test_reg_mask_div_float();
	void test_reg_mask_div_double();

	template <typename T>
	void test_Reg_mask_div();
	void test_Reg_mask_div_int8();
	void test_Reg_mask_div_int16();
	void test_Reg_mask_div_int32();
	void test_Reg_mask_div_int64();
	void test_Reg_mask_div_float();
	void test_Reg_mask_div_double();
};

#endif // DIVTEST_HPP_
