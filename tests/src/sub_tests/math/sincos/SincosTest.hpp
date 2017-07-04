#ifndef SINCOSTEST_HPP_
#define SINCOSTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class SinsincosTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SinsincosTest);

#if !defined(MIPP_AVX512) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	CPPUNIT_TEST(test_reg_sincos_float);
	CPPUNIT_TEST(test_Reg_sincos_float);
#endif

#if defined(MIPP_64BIT) && (defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC))
	CPPUNIT_TEST(test_reg_sincos_double);
	CPPUNIT_TEST(test_Reg_sincos_double);
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T>
	void test_reg_sincos();
	void test_reg_sincos_float();
	void test_reg_sincos_double();

	template <typename T>
	void test_Reg_sincos();
	void test_Reg_sincos_float();
	void test_Reg_sincos_double();
};

#endif // SINCOSTEST_HPP_
