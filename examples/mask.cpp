#include <iostream>
#include <random>
#include <algorithm>

#include "../src/mipp.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 g(rd());

	using T = float;
	constexpr int N = mipp::N<T>();

	T t_1[N];
	for (auto i = 0; i < N; i++) t_1[i] = i+1;
	std::shuffle(t_1, t_1 + N, g);

	T t_2[N];
	for (auto i = 0; i < N; i++) t_2[i] = i+1;
	std::shuffle(t_2, t_2 + N, g);

	mipp::Reg<T> in_1 = t_1;
	mipp::Reg<T> in_2 = t_2;
	mipp::Reg<T> in_3 = (T)-1;
	mipp::Msk<N> m_1  = false;
	mipp::Msk<N> m_2  = true;
	mipp::Msk<N> m_3  = {true, false,true, true, false,true ,true ,true ,
	                     false,false,false,false,false,true ,false,true ,
	                     false,true ,true ,true ,false,true ,false,true ,
	                     true ,true ,false,true ,false,false,false,false};
	mipp::Msk<N> m_4  = {false,true ,false,false,true ,false,false,false,
	                     true ,true ,true ,true ,true ,false,true ,false,
	                     true ,false,false,false,true ,false,true ,false,
	                     false,false,true ,false,true ,true ,true ,true };

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

	auto out = mipp::maskz<T,mipp::sub>(m_3, in_1, in_2);
	std::cout << "Output vector (m_3 & (in_1 - in_2)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	auto m_5 = in_1 > in_2;
	std::cout << "Output mask (in_1 > in_2): " << std::endl;
	std::cout << "m_5  = " << m_5 << std::endl;
	std::cout << std::endl;

	out = mipp::mask<T,mipp::add>(m_5, in_3, in_1, in_2);
	std::cout << "Output vector ((m_5 & (in_1 + in_2)) | (~m_5 & in_3)): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	mout = m_3 | m_4;
	std::cout << "Output vector (m_3 ^ m_4): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	mout = m_3 ^ m_4;
	std::cout << "Output vector (m_3 | m_4): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	mout = m_3 & m_4;
	std::cout << "Output vector (m_3 & m_4): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	mout = ~mout;
	std::cout << "Output vector (~mout): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	auto out2 = in_1 - in_2;
	std::cout << "Output vector (in_1 - in_2): " << std::endl;
	std::cout << "out2 = " << out2 << std::endl;
	std::cout << std::endl;

	mout = mipp::sign(out2);
	std::cout << "Output vector (mipp::sign(out2)): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	out2 = mipp::neg(out2, mout);
	std::cout << "Output vector (mipp::neg(out2, mout)): " << std::endl;
	std::cout << "out2 = " << out2 << std::endl;
	std::cout << std::endl;

	mout = m_2 << 0;
	std::cout << "Output vector (m_2 << 0): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	mout = m_2 << 1;
	std::cout << "Output vector (m_2 << 1): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	mout = m_2 >> 2;
	std::cout << "Output vector (m_2 >> 2): " << std::endl;
	std::cout << "mout = " << mout << std::endl;
	std::cout << std::endl;

	return 0;
}
