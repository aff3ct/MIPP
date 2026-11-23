// g++ mipp.cpp -I../include -Wall -mavx2 -o mipp_cpp.bin

#include <iostream>
#include <string>

#include <mipp.hpp>

#define LMUL 1

void print_v(float32_t* v, const std::string &name)
{
	std::cout << name << " = [";
	for (size_t i = 0; i < mipp::N<float32_t,LMUL>(); i++)
		std::cout << v[i] << ",";
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv)
{
#if defined(MIPP_PRINT_INFO)
	mipp_info();
	std::cout << std::endl;
#endif

	// load/store require a pointer aligned on the register size (64 bytes covers every target)
	alignas(64) float32_t a1[mipp::N<float32_t,LMUL>()];
	alignas(64) float32_t a2[mipp::N<float32_t,LMUL>()];
	alignas(64) float32_t a3[mipp::N<float32_t,LMUL>()];

	for (size_t i = 0; i < mipp::N<float32_t,LMUL>(); i++) {
		a1[i] = i+0;
		a2[i] = i+1;
	}

	print_v(a1, "a1");
	print_v(a2, "a2");

	std::cout << "mipp::N<float32_t,1>() = " << mipp::N<float32_t,1>() << std::endl;
	std::cout << "mipp::N<float32_t,2>() = " << mipp::N<float32_t,2>() << std::endl;
	std::cout << "mipp::N<float32_t,4>() = " << mipp::N<float32_t,4>() << std::endl;
	std::cout << "mipp::N<float32_t,8>() = " << mipp::N<float32_t,8>() << std::endl;

	mipp::vd<float32_t,LMUL> vd1, vd2, vd3;

	vd1 = mipp::load<float32_t,LMUL>(a1);
	vd2 = mipp::load<float32_t,LMUL>(a2);

	vd3 = mipp::add(vd1, vd2);

	mipp::store(a3, vd3);

	print_v(a3, "a3");

	return 0;
}
