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
	for (auto i = 0; i < mipp::N<type>(); i++) t_1[i] = 1;
	std::shuffle(t_1, t_1 + mipp::N<type>(), g);

	type t_2[mipp::N<type>()];
	for (auto i = 0; i < mipp::N<type>(); i++) t_2[i] = i+1;
	std::shuffle(t_2, t_2 + mipp::N<type>(), g);

	type t_3[mipp::N<type>()];
	for (auto i = 0; i < mipp::N<type>(); i++) t_3[i] = 3.14;
	std::shuffle(t_3, t_3 + mipp::N<type>(), g);

	mipp::Reg<type> in_1; in_1.loadu(t_1);
	mipp::Reg<type> in_2; in_2.loadu(t_2);
	mipp::Reg<type> in_3; in_3.loadu(t_3);

	std::cout << "Input vectors: " << std::endl;
	std::cout << "in_1 = " << in_1 << std::endl;
	std::cout << "in_2 = " << in_2 << std::endl;
	std::cout << std::endl;

	auto out = in_1.log();
	std::cout << "Output vectors (in_1.log()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = mipp::exp(in_1);
	std::cout << "Output vectors (mipp::exp(in_1)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_2.exp();
	std::cout << "Output vectors (in_2.exp()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_3.sin();
	std::cout << "Output vectors (in_3.sin()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_3.cos();
	std::cout << "Output vectors (in_3.cos()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	mipp::Reg<type> rsin, rcos;
	in_3.sincos(rsin, rcos);
	std::cout << "Output vectors (in_3.sincos(rsin, rcos)): " << std::endl;
	std::cout << "rsin  = " << rsin << std::endl;
	std::cout << "rcos  = " << rcos << std::endl;
	std::cout << std::endl;

	return 0;
}
