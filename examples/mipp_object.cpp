// g++ mipp_object.cpp -I../include -Wall -mavx2 -o mipp_object_cpp.bin

#include <iostream>
#include <numeric>
#include <string>

#include <mipp_obj.hpp>

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

	mipp::Vd<float32_t,LMUL> vd1, vd2, vd3;

	// load/store require a pointer aligned on the register size (64 bytes covers every target)
	alignas(64) float32_t a1[mipp::Vd<float32_t,LMUL>::N()];
	alignas(64) float32_t a2[mipp::Vd<float32_t,LMUL>::N()];
	alignas(64) float32_t a3[mipp::Vd<float32_t,LMUL>::N()];

	std::iota(a1, a1 + mipp::Vd<float32_t,LMUL>::N(), 0);
	std::iota(a2, a2 + mipp::Vd<float32_t,LMUL>::N(), 1);

	print_v(a1, "a1");
	print_v(a2, "a2");

	// vd1.load(a1); // does not exist yet in mipp_obj.hpp
	// vd2.load(a2); // does not exist yet in mipp_obj.hpp
	vd1.r = mipp::load<float32_t,LMUL>(a1);
	vd2.r = mipp::load<float32_t,LMUL>(a2);

	vd3 = vd1 + vd2;

	mipp::store(a3, vd3);

	print_v(a3, "a3");

	return 0;
}
