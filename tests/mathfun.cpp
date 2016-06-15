#include <iostream>
#include <random>
#include <algorithm>

#include "../mipp.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 g(rd());

	using type = float;

	type t_1[mipp::nElReg<type>()];
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_1[i] = 1;
	std::shuffle(t_1, t_1 + mipp::nElReg<type>(), g);

	type t_2[mipp::nElReg<type>()];
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_2[i] = i+1;
	std::shuffle(t_2, t_2 + mipp::nElReg<type>(), g);

	mipp::Reg<type> in_1; in_1.loadu(t_1);
	mipp::Reg<type> in_2; in_2.loadu(t_2);

	std::cout << "Input vectors: " << std::endl;
	std::cout << "in_1 = " << in_1 << std::endl;
	std::cout << "in_2 = " << in_2 << std::endl;
	std::cout << std::endl;

	auto out = mipp::exp(in_1);
	std::cout << "Output vectors (mipp::exp(in_1)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_2.exp();
	std::cout << "Output vectors (in_2.exp()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	return 0;
}