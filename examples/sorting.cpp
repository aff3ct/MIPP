#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <numeric>

#include <mipp.h>

#include "sort/LC_sorter.hpp"
#include "sort/LC_sorter_simd.hpp"
#include "sort/Quick_sorter.hpp"

using type = float;

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

	const auto n_elmts = (argc > 1) ? std::atoi(argv[1]) : 512;
	const auto k       = (argc > 2) ? std::atoi(argv[2]) : 2;
	const auto n_tests = (argc > 3) ? std::atoi(argv[3]) : 1000;

	std::cout << "n_elmts = " << n_elmts << std::endl;
	std::cout << "k       = " << k       << std::endl;
	std::cout << "n_tests = " << n_tests << std::endl << std::endl;

	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(123);

	std::vector<std::vector<float>> values(n_tests, std::vector<float>(n_elmts));
	for (auto i = 0; i < n_tests; i++)
	{
		std::iota   (values[i].begin(), values[i].end(), 0);
		std::shuffle(values[i].begin(), values[i].end(), g);
	}

	// -------------------------------------------------------------------------

	std::cout << "values: ";
	for (auto i = 0; i < n_elmts; i++)
		std::cout << values[n_tests -1][i] << ",";
	std::cout << std::endl;

	std::cout << std::endl << "Lewis Carroll:" << std::endl;
	std::vector<int> pos(k, -1);
	LC_sorter<float> lc(n_elmts);
	std::fill(pos.begin(), pos.end(), -1);
	auto t_before = std::chrono::steady_clock::now();
	auto csum = 0;
	for (auto i = 0; i < n_tests; i++)
	{
		lc.partial_sort(values[i].data(), pos, n_elmts);
		csum += pos[k -1];
	}
	auto t_after = std::chrono::steady_clock::now();
	auto d_delta = t_after - t_before;
	auto decod_time_ms = (float)d_delta.count() * 0.000001f;

	std::cout << "min pos: "; for (auto i = 0; i < k; i++) std::cout <<                    pos[i]  << ","; std::cout << std::endl;
	std::cout << "min: ";     for (auto i = 0; i < k; i++) std::cout << values[n_tests -1][pos[i]] << ","; std::cout << std::endl;
	std::cout << "time: " << decod_time_ms << "ms" << std::endl;
	std::cout << "csum: " << csum << std::endl;

	std::cout << std::endl << "Lewis Carroll SIMD:" << std::endl;
	LC_sorter_simd<float> lc_simd(n_elmts);
	std::fill(pos.begin(), pos.end(), -1);
	t_before = std::chrono::steady_clock::now();
	csum = 0;
	for (auto i = 0; i < n_tests; i++)
	{
		lc_simd.partial_sort(values[i].data(), pos);
		csum += pos[k -1];
	}
	t_after = std::chrono::steady_clock::now();
	d_delta = t_after - t_before;
	decod_time_ms = (float)d_delta.count() * 0.000001f;

	std::cout << "min pos: "; for (auto i = 0; i < k; i++) std::cout <<                    pos[i]  << ","; std::cout << std::endl;
	std::cout << "min: ";     for (auto i = 0; i < k; i++) std::cout << values[n_tests -1][pos[i]] << ","; std::cout << std::endl;
	std::cout << "time: " << decod_time_ms << "ms" << std::endl;
	std::cout << "csum: " << csum << std::endl;

	std::cout << std::endl << "Partial Quicksort:" << std::endl;
	Quick_sorter<type> qs(n_elmts);
	std::fill(pos.begin(), pos.end(), -1);
	t_before = std::chrono::steady_clock::now();
	csum = 0;
	for (auto i = 0; i < n_tests; i++)
	{
		qs.sort(values[i].data(), pos);
		csum += pos[k -1];
	}
	t_after = std::chrono::steady_clock::now();
	d_delta = t_after - t_before;
	decod_time_ms = (float)d_delta.count() * 0.000001f;

	std::cout << "min pos: "; for (auto i = 0; i < k; i++) std::cout <<                    pos[i]  << ","; std::cout << std::endl;
	std::cout << "min: ";     for (auto i = 0; i < k; i++) std::cout << values[n_tests -1][pos[i]] << ","; std::cout << std::endl;
	std::cout << "time: " << decod_time_ms << "ms" << std::endl;
	std::cout << "csum: " << csum << std::endl;

	// std::cout << std::endl << "C++11 partial sort:" << std::endl;
	// mipp::vector<int> indices(n_elmts);
	// std::iota(indices.begin(), indices.end(), 0);
	// t_before = std::chrono::steady_clock::now();
	// csum = 0;
	// for (auto i = 0; i < n_tests; i++)
	// {
	// 	std::partial_sort(indices.begin(), indices.begin() +k, indices.end(),
	// 	[values, i](int x, int y) {
	// 		return values[i][x] < values[i][y];
	// 	});
	// 	csum += indices[k -1];
	// }
	
	// t_after = std::chrono::steady_clock::now();
	// d_delta = t_after - t_before;
	// decod_time_ms = (float)d_delta.count() * 0.000001f;

	// std::cout << "min pos: "; for (auto i = 0; i < k; i++) std::cout << indices[i]                     << ","; std::cout << std::endl;
	// std::cout << "min: ";     for (auto i = 0; i < k; i++) std::cout << values[n_tests -1][indices[i]] << ","; std::cout << std::endl;
	// std::cout << "time: " << decod_time_ms << "ms" << std::endl;
	// std::cout << "csum: " << csum << std::endl;

	return 0;
}
