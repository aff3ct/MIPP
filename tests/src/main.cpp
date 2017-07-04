//#include "stdafx.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include <mipp.h>

int main(int argc, char* argv[])
{
	std::cout << "MIPP tests" << std::endl;
	std::cout << "----------" << std::endl << std::endl;

	std::cout << "Instruction name:        " << mipp::IntructionsName                  << std::endl;
	std::cout << "Instruction version:     " << mipp::IntructionsVersion               << std::endl;
	std::cout << "Instruction size (bits): " << mipp::RegisterSizeBit                  << std::endl;
	std::cout << "Instruction lanes:       " << mipp::Lanes                            << std::endl;
	std::cout << "64-bit support:          " << (mipp::support64Bit    ? "yes" : "no") << std::endl;
	std::cout << "Byte words support:      " << (mipp::supportByteWord ? "yes" : "no") << std::endl;

	std::cout << std::endl << "Running tests: ";

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

	// Run the tests.
	bool wasSucessful = runner.run();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}
