#include <iostream>
#include <random>
#include <algorithm>

#include "../src/mipp.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 g(rd());

	using type = float;

	type t_1[mipp::nElReg<type>()];
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_1[i] = i+1;
	std::shuffle(t_1, t_1 + mipp::nElReg<type>(), g);

	type t_2[mipp::nElReg<type>()];
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_2[i] = i+1;
	std::shuffle(t_2, t_2 + mipp::nElReg<type>(), g);

	mipp::Reg<type> in_1 = t_1;
	mipp::Reg<type> in_2 = t_2;
	mipp::Reg<type> in_3 = (type)-1;
	mipp::Msk<type> m_1  = 0;
	mipp::Msk<type> m_2  = 1;
	mipp::Msk<type> m_3  = {1,0,1,1,0,1,1,1,0,0,0,0,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0};
	mipp::Msk<type> m_4  = {0,1,0,0,1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1};

	std::cout << "Input vectors: " << std::endl;
	std::cout << "in_1 = " << in_1 << std::endl;
	std::cout << "in_2 = " << in_2 << std::endl;
	std::cout << "in_3 = " << in_3 << std::endl;
	std::cout << "m_1  = " << m_1  << std::endl;
	std::cout << "m_2  = " << m_2  << std::endl;
	std::cout << "m_3  = " << m_3  << std::endl;
	std::cout << "m_4  = " << m_4  << std::endl;
	std::cout << std::endl;

	auto mout = m_3;
	mout.set0();
	std::cout << "Output vector (mout = m_3; mout.set0()): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	auto out = mipp::maskz<mipp::add<type>>(m_1, in_1, in_2);
	std::cout << "Output vector (m_1 & (in_1 + in_2)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	auto m_5 = in_1 > in_2;
	std::cout << "Output mask (in_1 > in_2): " << std::endl;
	std::cout << "m_5  = " << m_5 << std::endl;
	std::cout << std::endl;

	out = mipp::mask<mipp::add<type>>(m_5, in_3, in_1, in_2);
	std::cout << "Output vector ((m_5 & (in_1 + in_2)) | (~m_5 & in_3)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	return 0;
}
