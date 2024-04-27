#include <iostream>
#include <random>
#include <algorithm>

#include <mipp.h>

int main(int argc, char** argv)
{
	// ------------------------------------------------------------------------
	std::cout << "MIPP example" << std::endl;
	std::cout << "------------" << std::endl;
	std::cout << " - Instr. type:       " << mipp::InstructionType                  << std::endl;
	std::cout << " - Instr. full type:  " << mipp::InstructionFullType              << std::endl;
	std::cout << " - Instr. version:    " << mipp::InstructionVersion               << std::endl;
	std::cout << " - Reg. size:         " << mipp::RegisterSizeBit       << " bits" << std::endl;
	std::cout << " - Reg. lanes:        " << mipp::Lanes                            << std::endl;
	std::cout << " - 64-bit support:    " << (mipp::Support64Bit    ? "yes" : "no") << std::endl;
	std::cout << " - Byte/word support: " << (mipp::SupportByteWord ? "yes" : "no") << std::endl;
	auto ext = mipp::InstructionExtensions();
	if (ext.size() > 0)
	{
		std::cout << " - Instr. extensions: {";
		for (auto i = 0; i < (int)ext.size(); i++)
			std::cout << ext[i] << (i < ((int)ext.size() -1) ? ", " : "");
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;
	// ------------------------------------------------------------------------

	std::random_device rd;
	std::mt19937 g(rd());

	using type = float;

	type t_1[mipp::N<type>()];
	for (auto i = 0; i < mipp::N<type>(); i++) t_1[i] = i;
	std::shuffle(t_1, t_1 + mipp::N<type>(), g);

	mipp::Reg<type> in_1 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
	mipp::Reg<type> in_2 = 12;
	mipp::Reg<type> in_3 = t_1;

	std::cout << "Input vectors: " << std::endl;
	std::cout << "in_1 = " << in_1 << std::endl;
	std::cout << "in_2 = " << in_2 << std::endl;
	std::cout << "in_3 = " << in_3 << std::endl;

	return 0;
}
