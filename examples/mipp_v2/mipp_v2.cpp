// g++ mipp_v2.cpp -mavx2 -o mipp_v2_cpp.bin

#include <iostream>
#include <string>

#include "../../include/mipp_v2.hpp"

void print_v(float32_t* v, const std::string &name)
{
	std::cout << name << " = [";
	for (int i = 0; i < mipp::N<float32_t,4>(); i++)
		std::cout << v[i] << ",";
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv)
{
	int i;
	float32_t a1[mipp::N<float32_t,4>()];
	float32_t a2[mipp::N<float32_t,4>()];
	float32_t a3[mipp::N<float32_t,4>()];

	for (int i = 0; i < mipp::N<float32_t,4>(); i++) {
		a1[i] = i+0;
		a2[i] = i+1;
	}

	print_v(a1, "a1");
	print_v(a2, "a2");

	std::cout << "mipp::N<float32_t,1>() = " << mipp::N<float32_t,1>() << std::endl;
	std::cout << "mipp::N<float32_t,2>() = " << mipp::N<float32_t,2>() << std::endl;
	std::cout << "mipp::N<float32_t,4>() = " << mipp::N<float32_t,4>() << std::endl;
	std::cout << "mipp::N<float32_t,8>() = " << mipp::N<float32_t,8>() << std::endl;

	mipp::rvd<float32_t,4> rvd1, rvd2, rvd3;

	mipp::loadu(a1, rvd1);
	mipp::loadu(a1, rvd2);

	rvd3 = mipp::add(rvd1, rvd2);

	mipp::storeu(a3, rvd3);

	print_v(a3, "a3");

	return 0;
}
