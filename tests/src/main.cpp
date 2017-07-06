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

	std::cout << "Instr. type:        " << mipp::InstructionType                  << std::endl;
	std::cout << "Instr. full type:   " << mipp::InstructionFullType              << std::endl;
	std::cout << "Instr. version:     " << mipp::InstructionVersion               << std::endl;
	std::cout << "Instr. size (bits): " << mipp::RegisterSizeBit                  << std::endl;
	std::cout << "Instr. lanes:       " << mipp::Lanes                            << std::endl;
	std::cout << "64-bit support:     " << (mipp::Support64Bit    ? "yes" : "no") << std::endl;
	std::cout << "Byte/word support:  " << (mipp::SupportByteWord ? "yes" : "no") << std::endl;

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
