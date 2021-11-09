// g++ mipp_v2.cpp -mavx2 -o mipp_v2_cpp.bin

#include <iostream>
#include <numeric>
#include <string>

#include "../../include/mipp_v2_object.hpp"

void print_v(float32_t* v, const std::string &name)
{
	std::cout << name << " = [";
	for (uint32_t i = 0; i < mipp::N<float32_t,4>(); i++)
		std::cout << v[i] << ",";
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv)
{
	mipp::Rvd<float32_t,4> rvd1, rvd2, rvd3;

	float32_t a1[mipp::Rvd<float32_t,4>::size()];
	float32_t a2[mipp::Rvd<float32_t,4>::size()];
	float32_t a3[mipp::Rvd<float32_t,4>::size()];

	std::iota(a1, a1 + mipp::Rvd<float32_t,4>::size(), 0);
	std::iota(a2, a2 + mipp::Rvd<float32_t,4>::size(), 1);

	print_v(a1, "a1");
	print_v(a2, "a2");

	rvd1.loadu(a1);
	rvd2.loadu(a2);

	rvd3 = rvd1 + rvd2;

	rvd3.storeu(a3);

	print_v(a3, "a3");

	return 0;
}
