// g++ mipp_object.cpp -I../include -Wall -mavx2 -o mipp_object_cpp.bin

#include <iostream>
#include <numeric>
#include <string>

#include <mipp_obj.hpp>

#define LMUL 1

void print_v(float32_t* v, const std::string &name)
{
	std::cout << name << " = [";
	for (uint32_t i = 0; i < mipp::N<float32_t,LMUL>(); i++)
		std::cout << v[i] << ",";
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv)
{
	mipp::Rvd<float32_t,LMUL> rvd1, rvd2, rvd3;

	float32_t a1[mipp::Rvd<float32_t,LMUL>::size()];
	float32_t a2[mipp::Rvd<float32_t,LMUL>::size()];
	float32_t a3[mipp::Rvd<float32_t,LMUL>::size()];

	std::iota(a1, a1 + mipp::Rvd<float32_t,LMUL>::size(), 0);
	std::iota(a2, a2 + mipp::Rvd<float32_t,LMUL>::size(), 1);

	print_v(a1, "a1");
	print_v(a2, "a2");

	// rvd1.load(a1); // does not exist yet in mipp_obj.hpp
	// rvd2.load(a2); // does not exist yet in mipp_obj.hpp
	rvd1.r = mipp::load<float32_t,LMUL>(a1);
	rvd2.r = mipp::load<float32_t,LMUL>(a2);

	rvd3 = rvd1 + rvd2;

	// rvd3.store(a3); // does not exist yet in mipp_obj.hpp
	mipp::store(a3, rvd3.r);

	print_v(a3, "a3");

	return 0;
}
