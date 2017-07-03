#include "mipp.h"

#include "AddTest.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( AddTest );


void 
AddTest::setUp()
{
}


void 
AddTest::tearDown()
{
}


void 
AddTest::testConstructor()
{
	using T = float;

	mipp::Reg<T> in_1 = 1;
	mipp::Reg<T> in_2 = 2;

	auto res = in_1 + in_2;

	for (auto i = 0; i < mipp::N<T>(); i++)
	{
		CPPUNIT_ASSERT_EQUAL(res[i], (T)3);
	}
}
