#include <iostream>
#include <random>
#include <algorithm>

#include <mipp.h>

int main(int argc, char** argv)
{
	// ------------------------------------------------------------------------
	std::cout << "MIPP example" << std::endl;
	std::cout << "------------" << std::endl;
	std::cout << " - Instr. type:       " << mipp::InstructionType                  << std::endl;
	std::cout << " - Instr. full type:  " << mipp::InstructionFullType              << std::endl;
	std::cout << " - Instr. version:    " << mipp::InstructionVersion               << std::endl;
	std::cout << " - Reg. size:         " << mipp::RegisterSizeBit       << " bits" << std::endl;
	std::cout << " - Reg. lanes:        " << mipp::Lanes                            << std::endl;
	std::cout << " - 64-bit support:    " << (mipp::Support64Bit    ? "yes" : "no") << std::endl;
	std::cout << " - Byte/word support: " << (mipp::SupportByteWord ? "yes" : "no") << std::endl;
	auto ext = mipp::InstructionExtensions();
	if (ext.size() > 0)
	{
		std::cout << " - Instr. extensions: {";
		for (auto i = 0; i < (int)ext.size(); i++)
			std::cout << ext[i] << (i < ((int)ext.size() -1) ? ", " : "");
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;
	// ------------------------------------------------------------------------

	std::random_device rd;
	std::mt19937 g(rd());

#ifdef MIPP_64BIT
	double t_64[mipp::N<double>()];
	for (auto i = 0; i < mipp::N<double>(); i++) t_64[i] = i;
	std::shuffle(t_64, t_64 + mipp::N<double>(), g);
#endif

	float t_32[mipp::N<float>()];
	for (auto i = 0; i < mipp::N<float>(); i++) t_32[i] = i;
	std::shuffle(t_32, t_32 + mipp::N<float>(), g);

	int t_32i[mipp::N<int>()];
	for (auto i = 0; i < mipp::N<int>(); i++) t_32i[i] = i;
	std::shuffle(t_32i, t_32i + mipp::N<int>(), g);

#ifdef MIPP_BW
	short t_16i[mipp::N<short>()];
	for (auto i = 0; i < mipp::N<short>(); i++) t_16i[i] = i;
	std::shuffle(t_16i, t_16i + mipp::N<short>(), g);

	signed char t_8i[mipp::N<signed char>()];
	for (auto i = 0; i < mipp::N<signed char>(); i++) t_8i[i] = i;
	std::shuffle(t_8i, t_8i + mipp::N<signed char>(), g);
#endif

#ifdef MIPP_64BIT
	const auto in_64  = mipp::Reg<double     >(t_64 );
#endif
	const auto in_32  = mipp::Reg<float      >(t_32 );
	const auto in_32i = mipp::Reg<int        >(t_32i);
#ifdef MIPP_BW
	const auto in_16i = mipp::Reg<short      >(t_16i);
	const auto in_8i  = mipp::Reg<signed char>(t_8i );
#endif

	std::cout << "Input vectors: " << std::endl;
#ifdef MIPP_64BIT
	std::cout << "double      = " << in_64  << std::endl;
#endif
	std::cout << "float       = " << in_32  << std::endl;
	std::cout << "int         = " << in_32i << std::endl;
#ifdef MIPP_BW
	std::cout << "short       = " << in_16i << std::endl;
	std::cout << "signed char = " << in_8i  << std::endl;
#endif
	std::cout << std::endl;

#ifdef MIPP_64BIT
	auto out_64  = mipp::Reduction<double,      mipp::add>::apply(in_64 );
#endif
	auto out_32  = mipp::Reduction<float,       mipp::add>::apply(in_32 );
	auto out_32i = mipp::Reduction<int,         mipp::add>::apply(in_32i);
#ifdef MIPP_BW
	auto out_16i = mipp::Reduction<short,       mipp::add>::apply(in_16i);
	auto out_8i  = mipp::Reduction<signed char, mipp::add>::apply(in_8i );
#endif

	std::cout << "Output vectors (reduction add): " << std::endl;
#ifdef MIPP_64BIT
	std::cout << "double      = " << out_64  << std::endl;
#endif
	std::cout << "float       = " << out_32  << std::endl;
	std::cout << "int         = " << out_32i << std::endl;
#ifdef MIPP_BW
	std::cout << "short       = " << out_16i << std::endl;
	std::cout << "signed char = " << out_8i  << std::endl;
#endif
	std::cout << std::endl;

#ifdef MIPP_64BIT
	out_64  = mipp::Reduction<double,      mipp::min>::apply(in_64 );
#endif
	out_32  = mipp::Reduction<float,       mipp::min>::apply(in_32 );
	out_32i = mipp::Reduction<int,         mipp::min>::apply(in_32i);
#ifdef MIPP_BW
	out_16i = mipp::Reduction<short,       mipp::min>::apply(in_16i);
	out_8i  = mipp::Reduction<signed char, mipp::min>::apply(in_8i );
#endif

	std::cout << "Output vectors (reduction min): " << std::endl;
#ifdef MIPP_64BIT
	std::cout << "double      = " << out_64  << std::endl;
#endif
	std::cout << "float       = " << out_32  << std::endl;
	std::cout << "int         = " << out_32i << std::endl;
#ifdef MIPP_BW
	std::cout << "short       = " << out_16i << std::endl;
	std::cout << "signed char = " << out_8i  << std::endl;
#endif
	std::cout << std::endl;

#ifdef MIPP_64BIT
	out_64  = mipp::Reduction<double,      mipp::max>::apply(in_64 );
#endif
	out_32  = mipp::Reduction<float,       mipp::max>::apply(in_32 );
	out_32i = mipp::Reduction<int,         mipp::max>::apply(in_32i);
#ifdef MIPP_BW
	out_16i = mipp::Reduction<short,       mipp::max>::apply(in_16i);
	out_8i  = mipp::Reduction<signed char, mipp::max>::apply(in_8i );
#endif

	std::cout << "Output vectors (reduction max): " << std::endl;
#ifdef MIPP_64BIT
	std::cout << "double      = " << out_64  << std::endl;
#endif
	std::cout << "float       = " << out_32  << std::endl;
	std::cout << "int         = " << out_32i << std::endl;
#ifdef MIPP_BW
	std::cout << "short       = " << out_16i << std::endl;
	std::cout << "signed char = " << out_8i  << std::endl;
#endif
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

	auto red = mipp::Reduction<type, mipp::add>::apply(vec);

	auto expected_red = vec[0];
	for (auto i = 1; i < vec_size; i++)
		expected_red += vec[i];
	
	std::cout << "Output reduction          (add) = " << +red          << std::endl;
	std::cout << "Expected output reduction (add) = " << +expected_red << std::endl;

	return 0;
}
