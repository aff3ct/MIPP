#include <iostream>
#include <random>
#include <algorithm>

#include "../mipp.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 g(rd());

#ifndef __ARM_NEON__
	double t_64[mipp::nElReg<double>()];
	for (auto i = 0; i < mipp::nElReg<double>(); i++) t_64[i] = i;
	std::shuffle(t_64, t_64 + mipp::nElReg<double>(), g);
#endif

	float t_32[mipp::nElReg<float>()];
	for (auto i = 0; i < mipp::nElReg<float>(); i++) t_32[i] = i;
	std::shuffle(t_32, t_32 + mipp::nElReg<float>(), g);

	int t_32i[mipp::nElReg<int>()];
	for (auto i = 0; i < mipp::nElReg<int>(); i++) t_32i[i] = i;
	std::shuffle(t_32i, t_32i + mipp::nElReg<int>(), g);

	short t_16i[mipp::nElReg<short>()];
	for (auto i = 0; i < mipp::nElReg<short>(); i++) t_16i[i] = i;
	std::shuffle(t_16i, t_16i + mipp::nElReg<short>(), g);

	signed char t_8i[mipp::nElReg<signed char>()];
	for (auto i = 0; i < mipp::nElReg<signed char>(); i++) t_8i[i] = i;
	std::shuffle(t_8i, t_8i + mipp::nElReg<signed char>(), g);

#ifndef __ARM_NEON__
	const auto in_64  = mipp::set<double     >(t_64 );
#endif
	const auto in_32  = mipp::set<float      >(t_32 );
	const auto in_32i = mipp::set<int        >(t_32i);
	const auto in_16i = mipp::set<short      >(t_16i);
	const auto in_8i  = mipp::set<signed char>(t_8i );

	std::cout << "Input vectors: " << std::endl;
#ifndef __ARM_NEON__
	std::cout << "double      = "; mipp::dump<double     >(in_64 ); std::cout << std::endl;
#endif
	std::cout << "float       = "; mipp::dump<float      >(in_32 ); std::cout << std::endl;
	std::cout << "int         = "; mipp::dump<int        >(in_32i); std::cout << std::endl;
	std::cout << "short       = "; mipp::dump<short      >(in_16i); std::cout << std::endl;
	std::cout << "signed char = "; mipp::dump<signed char>(in_8i ); std::cout << std::endl;
	std::cout << std::endl;

#ifndef __ARM_NEON__
	auto out_64  = mipp::Reduction<double,      mipp::add<double     >>::apply(in_64 );
#endif
	auto out_32  = mipp::Reduction<float,       mipp::add<float      >>::apply(in_32 );
	auto out_32i = mipp::Reduction<int,         mipp::add<int        >>::apply(in_32i);
	auto out_16i = mipp::Reduction<short,       mipp::add<short      >>::apply(in_16i);
	auto out_8i  = mipp::Reduction<signed char, mipp::add<signed char>>::apply(in_8i );

	std::cout << "Output vectors (reduction add): " << std::endl;
#ifndef __ARM_NEON__
	std::cout << "double      = "; mipp::dump<double     >(out_64 ); std::cout << std::endl;
#endif
	std::cout << "float       = "; mipp::dump<float      >(out_32 ); std::cout << std::endl;
	std::cout << "int         = "; mipp::dump<int        >(out_32i); std::cout << std::endl;
	std::cout << "short       = "; mipp::dump<short      >(out_16i); std::cout << std::endl;
	std::cout << "signed char = "; mipp::dump<signed char>(out_8i ); std::cout << std::endl;
	std::cout << std::endl;

#ifndef __ARM_NEON__
	out_64  = mipp::Reduction<double,      mipp::min<double     >>::apply(in_64 );
#endif
	out_32  = mipp::Reduction<float,       mipp::min<float      >>::apply(in_32 );
	out_32i = mipp::Reduction<int,         mipp::min<int        >>::apply(in_32i);
	out_16i = mipp::Reduction<short,       mipp::min<short      >>::apply(in_16i);
	out_8i  = mipp::Reduction<signed char, mipp::min<signed char>>::apply(in_8i );

	std::cout << "Output vectors (reduction min): " << std::endl;
#ifndef __ARM_NEON__
	std::cout << "double      = "; mipp::dump<double     >(out_64 ); std::cout << std::endl;
#endif
	std::cout << "float       = "; mipp::dump<float      >(out_32 ); std::cout << std::endl;
	std::cout << "int         = "; mipp::dump<int        >(out_32i); std::cout << std::endl;
	std::cout << "short       = "; mipp::dump<short      >(out_16i); std::cout << std::endl;
	std::cout << "signed char = "; mipp::dump<signed char>(out_8i ); std::cout << std::endl;
	std::cout << std::endl;

#ifndef __ARM_NEON__
	out_64  = mipp::Reduction<double,      mipp::max<double     >>::apply(in_64 );
#endif
	out_32  = mipp::Reduction<float,       mipp::max<float      >>::apply(in_32 );
	out_32i = mipp::Reduction<int,         mipp::max<int        >>::apply(in_32i);
	out_16i = mipp::Reduction<short,       mipp::max<short      >>::apply(in_16i);
	out_8i  = mipp::Reduction<signed char, mipp::max<signed char>>::apply(in_8i );

	std::cout << "Output vectors (reduction max): " << std::endl;
#ifndef __ARM_NEON__
	std::cout << "double      = "; mipp::dump<double     >(out_64 ); std::cout << std::endl;
#endif
	std::cout << "float       = "; mipp::dump<float      >(out_32 ); std::cout << std::endl;
	std::cout << "int         = "; mipp::dump<int        >(out_32i); std::cout << std::endl;
	std::cout << "short       = "; mipp::dump<short      >(out_16i); std::cout << std::endl;
	std::cout << "signed char = "; mipp::dump<signed char>(out_8i ); std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "=========================================================================" << std::endl << std::endl;

	using type = float;

	std::uniform_int_distribution<int> uniform_dist(-127,127);
	auto vec_size = 32;
	std::vector<type> vec(vec_size);

	std::cout << "Input vec = [";
	for (auto i = 0; i < vec_size; i++)
	{
		vec[i] = (type)uniform_dist(g);
		std::cout << ", " << +vec[i];
	}
	std::cout << "]" << std::endl;

	auto red = mipp::Reduction<type, mipp::add<type>>::apply(vec);
	
	std::cout << "Output reduction (add) = " << +red << std::endl;

	return 0;
}