#ifndef BLENDTEST_HPP_
#define BLENDTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class BlendTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BlendTest);

#if defined(MIPP_BW)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_int8);
#endif
	CPPUNIT_TEST(test_Reg_blend_int8);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_int16);
#endif
	CPPUNIT_TEST(test_Reg_blend_int16);
#endif

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_int32);
#endif
	CPPUNIT_TEST(test_Reg_blend_int32);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_float);
#endif
	CPPUNIT_TEST(test_Reg_blend_float);

#if defined(MIPP_64BIT)
#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_int64);
#endif
	CPPUNIT_TEST(test_Reg_blend_int64);

#ifndef MIPP_NO
	CPPUNIT_TEST(test_reg_blend_double);
#endif
	CPPUNIT_TEST(test_Reg_blend_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_blend();
	void test_reg_blend_int8();
	void test_reg_blend_int16();
	void test_reg_blend_int32();
	void test_reg_blend_int64();
	void test_reg_blend_float();
	void test_reg_blend_double();

	template <typename T>
	void test_Reg_blend();
	void test_Reg_blend_int8();
	void test_Reg_blend_int16();
	void test_Reg_blend_int32();
	void test_Reg_blend_int64();
	void test_Reg_blend_float();
	void test_Reg_blend_double();
};

#endif  // BLENDTEST_HPP_
