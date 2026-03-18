// g++ mipp.cpp -mavx2 -o mipp_cpp.bin

#include <iostream>
#include <string>

#include "../../include/mipp_v2.hpp"

void print_v(int32_t* v, const std::string &name)
{
	std::cout << name << " = [";
	for (uint32_t i = 0; i < mipp::N<int32_t,4>(); i++)
		std::cout << v[i] << ",";
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv)
{
	int32_t a1[mipp::N<int32_t,4>()];
	int32_t a2[mipp::N<int32_t,4>()];
	int32_t a3[mipp::N<int32_t,4>()];

	for (uint32_t i = 0; i < mipp::N<int32_t,4>(); i++) {
		a1[i] = i+0;
		a2[i] = i+1;
	}

	print_v(a1, "a1");
	print_v(a2, "a2");

	std::cout << "mipp::N<int32_t,1>() = " << mipp::N<int32_t,1>() << std::endl;
	std::cout << "mipp::N<int32_t,2>() = " << mipp::N<int32_t,2>() << std::endl;
	std::cout << "mipp::N<int32_t,4>() = " << mipp::N<int32_t,4>() << std::endl;
	std::cout << "mipp::N<int32_t,8>() = " << mipp::N<int32_t,8>() << std::endl;

	mipp::rvd<int32_t,4> rvd1, rvd2, rvd3;

	mipp::loadu(a1, rvd1);
	mipp::loadu(a2, rvd2);

	rvd3 = mipp::add(rvd1, rvd2);

	mipp::storeu(a3, rvd3);

	print_v(a3, "a3");

	return 0;
}
