#include <iostream>
#include <random>
#include <algorithm>

#include "../src/mipp.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 g(rd());

	signed char t_1[mipp::nElReg<signed char>()];
	for (auto i = 0; i < mipp::nElReg<signed char>(); i++) t_1[i] = i+1;
	// std::shuffle(t_1, t_1 + mipp::nElReg<signed char>(), g);

	mipp::Reg<signed char> in_1; in_1.loadu(t_1);

	std::cout << "---------------------------- int8" << std::endl << std::endl;

	std::cout << "Input vectors (signed char): " << std::endl;
	std::cout << "in_1  = " << in_1 << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------------- int16" << std::endl << std::endl;

	auto low  = in_1.low ();
	auto high = in_1.high();

	auto low_short = low.template cvt<short>();
	std::cout << "Output vectors (low.cvt<short>()): " << std::endl;
	std::cout << "low  = " << low_short << std::endl;
	std::cout << std::endl;

	auto high_short = high.template cvt<short>();
	std::cout << "Output vectors (hight.cvt<short>()): " << std::endl;
	std::cout << "high = " << high_short << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------------- int32" << std::endl << std::endl;

	auto low_low_short  = low_short.low();
	auto high_low_short = low_short.high();

	auto low_low_int = low_low_short.template cvt<int>();
	std::cout << "Output vectors (low_low_short.cvt<int>()): " << std::endl;
	std::cout << "low  = " << low_low_int << std::endl;
	std::cout << std::endl;

	auto high_low_int = high_low_short.template cvt<int>();
	std::cout << "Output vectors (high_low_short.cvt<int>()): " << std::endl;
	std::cout << "high = " << high_low_int << std::endl;
	std::cout << std::endl;

	auto low_high_short  = high_short.low();
	auto high_high_short = high_short.high();

	auto low_high_int = low_high_short.template cvt<int>();
	std::cout << "Output vectors (low_high_short.cvt<int>()): " << std::endl;
	std::cout << "low  = " << low_high_int << std::endl;
	std::cout << std::endl;

	auto high_high_int = high_high_short.template cvt<int>();
	std::cout << "Output vectors (high_high_short.cvt<int>()): " << std::endl;
	std::cout << "high = " << high_high_int << std::endl;
	std::cout << std::endl;

	std::cout << "------------------------- float32" << std::endl << std::endl;

	auto low_low_float = low_low_int.template cvt<float>() + 0.1f;
	std::cout << "Output vectors (low_low_int.cvt<float>() + 0.1f): " << std::endl;
	std::cout << "p1   = " << low_low_float << std::endl;
	std::cout << std::endl;

	auto high_low_float = high_low_int.template cvt<float>() + 0.1f;
	std::cout << "Output vectors (high_low_int.cvt<float>() + 0.1f): " << std::endl;
	std::cout << "p2   = " << high_low_float << std::endl;
	std::cout << std::endl;

	auto low_high_float = low_high_int.template cvt<float>() + 0.1f;
	std::cout << "Output vectors (low_high_int.cvt<float>() + 0.1f): " << std::endl;
	std::cout << "p3   = " << low_high_float << std::endl;
	std::cout << std::endl;

	auto high_high_float = high_high_int.template cvt<float>() + 0.1f;
	std::cout << "Output vectors (high_high_int.cvt<float>() + 0.1f): " << std::endl;
	std::cout << "p4   = " << high_high_float << std::endl;
	std::cout << std::endl;

	return 0;
}
