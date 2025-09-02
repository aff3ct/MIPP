#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <iostream>
#include <mipp.h>

int main(int argc, char* argv[])
{
	std::cout << "MIPP tests" << std::endl;
	std::cout << "----------" << std::endl << std::endl;

	std::cout << "Instr. type:       " << mipp::InstructionType                  << std::endl;
	std::cout << "Instr. full type:  " << mipp::InstructionFullType              << std::endl;
	std::cout << "Instr. version:    " << mipp::InstructionVersion               << std::endl;
	std::cout << "Instr. size:       " << mipp::RegisterSizeBit       << " bits" << std::endl;
	std::cout << "Instr. lanes:      " << mipp::Lanes                            << std::endl;
	std::cout << "64-bit support:    " << (mipp::Support64Bit    ? "yes" : "no") << std::endl;
	std::cout << "Byte/word support: " << (mipp::SupportByteWord ? "yes" : "no") << std::endl;
	auto ext = mipp::InstructionExtensions();
	if (ext.size() > 0)
	{
		std::cout << "Instr. extensions: {";
		for (auto i = 0; i < (int)ext.size(); i++)
			std::cout << ext[i] << (i < ((int)ext.size() -1) ? ", " : "");
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;

	int result = Catch::Session().run(argc, argv);

	return result;
}
