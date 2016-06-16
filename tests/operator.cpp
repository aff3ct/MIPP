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
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_1[i] = i+1;
	std::shuffle(t_1, t_1 + mipp::nElReg<type>(), g);

	type t_2[mipp::nElReg<type>()];
	for (auto i = 0; i < mipp::nElReg<type>(); i++) t_2[i] = i+1;
	std::shuffle(t_2, t_2 + mipp::nElReg<type>(), g);

	mipp::Reg<type> in_1(t_1);
	mipp::Reg<type> in_2(t_2);

	std::cout << "Input vectors: " << std::endl;
	std::cout << "in_1 = " << in_1 << std::endl;
	std::cout << "in_2 = " << in_2 << std::endl;
	std::cout << std::endl;

	auto out = in_1 + in_2;
	// auto out = in_1.add(in_2);
	std::cout << "Output vectors (in_1 + in_2): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_1 - in_2;
	std::cout << "Output vectors (in_1 - in_2): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	if (typeid(type) == typeid(int) || typeid(type) == typeid(short) || typeid(type) == typeid(signed char))
	{
		out = in_1;
		out = ~out;
		std::cout << "Output vectors (~in_1): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = in_1 | in_2;
		std::cout << "Output vectors (in_1 | in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = in_1 << 1;
		std::cout << "Output vectors (in_1 << 1): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = in_1 >> 1;
		std::cout << "Output vectors (in_1 >> 1): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;
	}

	out = (in_1 == in_2);
	std::cout << "Output vectors (in_1 == in_2): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = (in_1 > in_2);
	std::cout << "Output vectors (in_1 > in_2): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	if (typeid(type) == typeid(double) || typeid(type) == typeid(float))
	{
		out = (in_1 != in_2);
		std::cout << "Output vectors (in_1 != in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = (in_1 < in_2);
		std::cout << "Output vectors (in_1 < in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = (in_1 <= in_2);
		std::cout << "Output vectors (in_1 <= in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = (in_1 >= in_2);
		std::cout << "Output vectors (in_1 >= in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = in_1 * in_2;
		std::cout << "Output vectors (in_1 * in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		out = in_1 / in_2;
		std::cout << "Output vectors (in_1 / in_2): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;

		auto two = mipp::Reg<type>(2);
		out = in_1 + in_2 * two;
		std::cout << "Output vectors (in_1 + in_2 * two): " << std::endl;
		std::cout << "out  = " << out << std::endl;
		std::cout << std::endl;
	}

	out = in_1.hmin();
	std::cout << "Output vectors (in_1.hmin()): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	out = in_1 * 3 + 2;
	std::cout << "Output vectors (in_1 * 3 + 2): " << std::endl;
	std::cout << "out  = " << out << std::endl;
	std::cout << std::endl;

	return 0;
}