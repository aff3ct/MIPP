#ifndef PACKTEST_HPP_
#define PACKTEST_HPP_

#include <cppunit/extensions/HelperMacros.h>

class PackTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(PackTest);

#ifndef MIPP_NO
#if defined(MIPP_BW)
#if !defined(MIPP_AVX512) || (defined(MIPP_AVX512) && defined(MIPP_AVX512VBMI))
	CPPUNIT_TEST(test_reg_pack_int16_int8);
	CPPUNIT_TEST(test_Reg_pack_int16_int8);
#endif

	CPPUNIT_TEST(test_reg_pack_int32_int16);
	CPPUNIT_TEST(test_Reg_pack_int32_int16);
#endif
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	template <typename T1, typename T2>
	void test_reg_pack();
	void test_reg_pack_int16_int8();
	void test_reg_pack_int32_int16();

	template <typename T1, typename T2>
	void test_Reg_pack();
	void test_Reg_pack_int16_int8();
	void test_Reg_pack_int32_int16();
};

#endif // PACKTEST_HPP_
