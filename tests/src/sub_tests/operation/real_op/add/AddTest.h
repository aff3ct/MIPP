#ifndef ADDTEST_H
#define ADDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class AddTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( AddTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConstructor();
};

#endif  // ADDTEST_H
