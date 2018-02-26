#include <iostream>
#include <exception>
#include <algorithm>
#include <chrono>
#include <tuple>
#include <sstream>
#include <numeric>

#include <mipp.h>

constexpr int Trials = 10000000;
float CPUFreq = 0.;

template <typename T1, typename T2>
void subBenchmarkSeries(std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> &benchResults)
{
	std::string grp = "conversion";

	// conversion
	{
		mipp::reg r1, r2;
		mipp::reg_2 r_2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::cvt<T1,T2>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(93, "cvt", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::cvt<T1,T2>(r_2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(94, "cvt_2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::pack<T1,T2>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(95, "pack", grp, duration));
		}
		catch(std::exception&) {}
	}
}

template <typename T>
void benchmarkSeries(std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> &benchResults)
{
	constexpr int N = mipp::N<T>();

	std::string grp = "memop";

	// unaligned load and store
	{
		std::vector<T> data(N * Trials);
		T* d = data.data();
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::loadu(d + t * N);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(0, "loadu", grp, duration));
		}
		catch(std::exception&) {}

		volatile mipp::reg r;
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::storeu(d + t * N, r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(1, "storeu", grp, duration));
		}
		catch(std::exception&) {}

		data.resize(0);
	}

	// aligned load and store
	{
		mipp::vector<T> data(N * Trials);
		T* d = data.data();
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::load(d + t * N);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(2, "load", grp, duration));
		}
		catch(std::exception&) {}

		volatile mipp::reg r;
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::store(d + t * N, r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(3, "store", grp, duration));
		}
		catch(std::exception&) {}
		data.resize(0);
	}

	// sets
	{
		T vals[N];
		std::iota(vals, vals + N, (T)0);
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::set<T>(vals);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(4, "set", grp, duration));
		}
		catch(std::exception&) {}

		bool bits[N];
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::set<N>(bits);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(5, "set_m", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::set1<T>((T)1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(6, "set1", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::set1<N>(true);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(7, "set1_m", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::set0<T>();
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(8, "set0", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::set0<N>();
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(9, "set0_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// low and high
	{
		mipp::reg r;
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r_2 = mipp::low<T>(r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(10, "low", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r_2 = mipp::high<T>(r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(11, "high", grp, duration));
		}
		catch(std::exception&) {}
	}

	// cmask
	{
		uint32_t valsN[N];
		std::iota(valsN, valsN + N, (uint32_t)0);
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto cm1 = mipp::cmask<T>(valsN);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(12, "cmask", grp, duration));
		}
		catch(std::exception&) {}

		uint32_t valsN2[N/2];
		std::iota(valsN2, valsN2 + N/2, (uint32_t)0);
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto cm2 = mipp::cmask2<T>(valsN2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(13, "cmask2", grp, duration));
		}
		catch(std::exception&) {}

		uint32_t valsN4[N/4];
		std::iota(valsN4, valsN4 + N/4, (uint32_t)0);
		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto cm4 = mipp::cmask4<T>(valsN4);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(14, "cmask4", grp, duration));
		}
		catch(std::exception&) {}
	}

	// shuffle
	{
		mipp::reg r;

		uint32_t valsN[N];
		std::iota(valsN, valsN + N, (uint32_t)0);
		try {
			volatile auto cm1 = mipp::cmask<T>(valsN);
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::shuff<T>(r, cm1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(15, "shuff", grp, duration));
		}
		catch(std::exception&) {}

		uint32_t valsN2[N/2];
		std::iota(valsN2, valsN2 + N/2, (uint32_t)0);
		try {
			volatile auto cm2 = mipp::cmask2<T>(valsN2);
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::shuff2<T>(r, cm2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(16, "shuff2", grp, duration));
		}
		catch(std::exception&) {}

		uint32_t valsN4[N/4];
		std::iota(valsN4, valsN4 + N/4, (uint32_t)0);
		try {
			volatile auto cm4 = mipp::cmask4<T>(valsN4);
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::shuff4<T>(r, cm4);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(17, "shuff4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::lrot<T>(r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(18, "lrot", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::rrot<T>(r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(19, "rrot", grp, duration));
		}
		catch(std::exception&) {}
	}

	// interleave
	{
		mipp::reg r1, r2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavelo<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(20, "interleavelo", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavehi<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(21, "interleavehi", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavelo2<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(22, "interleavelo2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavehi2<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(23, "interleavehi2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavelo4<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(24, "interleavelo4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavehi4<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(25, "interleavehi4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleave<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(26, "interleave_1", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleave<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(27, "interleave", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleave2<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(28, "interleave2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleave4<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(29, "interleave4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavex2<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(30, "interleavex2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavex4<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(31, "interleavex4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::interleavex16<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(32, "interleavex16", grp, duration));
		}
		catch(std::exception&) {}
	}

	// transpose
	{
		mipp::reg rN[N], rN2[N/2], r8[8];

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose<T>(rN);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(33, "transpose", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose8x8<T>(r8);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(34, "transpose8x8", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose2<T>(rN2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(35, "transpose2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose28x8<T>(r8);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(36, "transpose28x8", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose4<T>(rN2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(37, "transpose4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::transpose48x8<T>(r8);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(38, "transpose48x8", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "bitwise";

	// bitwise and
	{
		mipp::reg r1, r2;
		mipp::msk m1, m2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::andb<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(39, "andb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::andb<N>(m1, m2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(40, "andb_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// bitwise and not
	{
		mipp::reg r1, r2;
		mipp::msk m1, m2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::andnb<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(41, "andnb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::andnb<N>(m1, m2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(42, "andnb_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// bitwise not
	{
		mipp::reg r;
		mipp::msk m;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::notb<T>(r);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(43, "notb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::notb<N>(m);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(44, "notb_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// bitwise or
	{
		mipp::reg r1, r2;
		mipp::msk m1, m2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::orb<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(45, "orb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::orb<N>(m1, m2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(46, "orb_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// bitwise xor
	{
		mipp::reg r1, r2;
		mipp::msk m1, m2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::xorb<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(47, "xorb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::xorb<N>(m1, m2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(48, "xorb_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	// bitwise shift
	{
		mipp::reg r;
		mipp::msk m;

		constexpr int nr = (int)sizeof(T) -2;
		constexpr int nm = N -1;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::lshift<T>(r, nr);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(49, "lshift", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::lshift<N>(m, nm);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(50, "lshift_m", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::rshift<T>(r, nr);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(51, "rshift", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto s = mipp::rshift<N>(m, nm);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(52, "rshift_m", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "compare";

	// compare
	{
		mipp::reg r1, r2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmpeq<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(53, "cmpeq", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmpneq<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(54, "cmpneq", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmplt<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(55, "cmplt", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmple<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(56, "cmple", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmpgt<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(57, "cmpgt", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::cmpge<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(58, "cmpge", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "arithmetic";

	// arithmetic
	{
		mipp::reg r1, r2, r3;
		mipp::msk m1;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::add<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(59, "add", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::sub<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(60, "sub", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::mul<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(61, "mul", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::div<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(62, "div", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::min<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(63, "min", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::max<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(64, "max", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::msb<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(65, "msb", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::msb<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(66, "msb_1", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto m = mipp::sign<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(67, "sign", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::neg<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(68, "neg", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::neg<T>(r1, m1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(69, "neg_m", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::abs<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(70, "abs", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::sqrt<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(71, "sqrt", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::rsqrt<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(72, "rsqrt", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::fmadd<T>(r1, r2, r3);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(73, "fmadd", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::fnmadd<T>(r1, r2, r3);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(74, "fnmadd", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::fmsub<T>(r1, r2, r3);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(75, "fmsub", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::fnmsub<T>(r1, r2, r3);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(76, "fnmsub", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::div2<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(77, "div2", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::div4<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(78, "div4", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::round<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(79, "round", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::sat<T>(r1, (T)-12, (T)+12);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(80, "sat", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "math";

	// math functions
	{
		mipp::reg r1, r2, r3;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::exp<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(81, "exp", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::log<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(82, "log", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::sin<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(83, "sin", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::cos<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(84, "cos", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				mipp::sincos<T>(r1, r2, r3);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(85, "sincos", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "blend";

	// blend
	{
		mipp::reg r1, r2;
		mipp::msk m;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto r = mipp::blend<T>(r1, r2, m);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(86, "blend", grp, duration));
		}
		catch(std::exception&) {}
	}

	grp = "reduction";

	// reduction
	{
		mipp::reg r1, r2;

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::hadd<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(87, "hadd", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::hmul<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(88, "hmul", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::hmin<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(89, "hmin", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::hmax<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(90, "hmax", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::testz<T>(r1, r2);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(91, "testz", grp, duration));
		}
		catch(std::exception&) {}

		try {
			auto start = std::chrono::steady_clock::now();
			for (auto t = 0; t < Trials; t++)
				volatile auto v = mipp::testz<T>(r1);
			auto duration = std::chrono::steady_clock::now() - start;
			benchResults.push_back(std::make_tuple(92, "testz_1", grp, duration));
		}
		catch(std::exception&) {}
	}

	if (typeid(T) == typeid(float  )) subBenchmarkSeries<float,  int32_t>(benchResults);
	if (typeid(T) == typeid(double )) subBenchmarkSeries<double, int64_t>(benchResults);
	if (typeid(T) == typeid(int32_t)) subBenchmarkSeries<int32_t,int16_t>(benchResults);
	if (typeid(T) == typeid(int16_t)) subBenchmarkSeries<int16_t,int8_t >(benchResults);
}

int main(int argc, char* argv[])
{
	std::cout << "MIPP Benchmark" << std::endl;
	std::cout << "--------------" << std::endl << std::endl;

	std::cout << "Instr. type:       " << mipp::InstructionType                  << std::endl;
	std::cout << "Instr. full type:  " << mipp::InstructionFullType              << std::endl;
	std::cout << "Instr. version:    " << mipp::InstructionVersion               << std::endl;
	std::cout << "Instr. size:       " << mipp::RegisterSizeBit       << " bits" << std::endl;
	std::cout << "Instr. lanes:      " << mipp::Lanes                            << std::endl;
	std::cout << "64-bit support:    " << (mipp::Support64Bit    ? "yes" : "no") << std::endl;
	std::cout << "Byte/word support: " << (mipp::SupportByteWord ? "yes" : "no") << std::endl;

	auto ext = mipp::InstructionExtensions();
	if (ext.size() > 0)
	{
		std::cout << "Instr. extensions: {";
		for (auto i = 0; i < (int)ext.size(); i++)
			std::cout << ext[i] << (i < ((int)ext.size() -1) ? ", " : "");
		std::cout << "}" << std::endl;
	}

	if (argc >= 2)
	{
		CPUFreq = std::atof(argv[1]);
		std::cout << "CPU frequency:     " << CPUFreq << " GHz" << std::endl;
	}

	std::cout << std::endl << "CPU warm-up... ";
	std::flush(std::cout);
	volatile uint64_t burner = 0;
	while (burner < 5000000000) burner++;
	std::cout << "Done." << std::endl;

	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsDouble;
	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsFloat;
	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsInt64;
	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsInt32;
	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsInt16;
	std::vector<std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>> benchsInt8;

	std::cout << std::endl << "Running benchmark... ";
	std::flush(std::cout);
	benchmarkSeries<double >(benchsDouble);
	benchmarkSeries<float  >(benchsFloat);
	benchmarkSeries<int64_t>(benchsInt64);
	benchmarkSeries<int32_t>(benchsInt32);
	benchmarkSeries<int16_t>(benchsInt16);
	benchmarkSeries<int8_t >(benchsInt8);
	std::cout << "Done." << std::endl << std::endl;

	std::cout << std::setw(                     3) << "id"                                          << " | "
	          << std::setw(                    16) << "name"                                        << " | "
	          << std::setw(                    12) << "group"                                       << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Double" : "type -> Double") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Float"  : "type -> Float" ) << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Int64"  : "type -> Int64" ) << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Int32"  : "type -> Int32" ) << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Int16"  : "type -> Int16" ) << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "Int8"   : "type -> Int8"  )
	          << std::endl;
	std::cout << std::setw( 3) << "  "                                                                                                            << " | "
	          << std::setw(16) << "    "                                                                                                          << " | "
	          << std::setw(12) << "     "                                                                                                         << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI") << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI") << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI") << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI") << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI") << " | "
	          << std::setw( 9) << "time (ns)" << (CPUFreq == 0. ? "" : " | ") << std::setw(CPUFreq == 0. ? 0 : 4) << (CPUFreq == 0. ? "" : "CPI")
	          << std::endl;
	std::cout << std::setw( 3)                     << "---"                                              << " | "
	          << std::setw(16)                     << "----------------"                                 << " | "
	          << std::setw(12)                     << "------------"                                     << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------") << " | "
	          << std::setw(CPUFreq == 0. ? 9 : 16) << (CPUFreq == 0. ? "---------" : "----------------")
	          << std::endl;

	auto iDouble = 0, iFloat = 0, iInt64 = 0, iInt32 = 0, iInt16 = 0, iInt8 = 0;
	for (auto i = 0; i <= 95; i++)
	{
		unsigned id       =  0;
		std::string name  = "";
		std::string group = "";

		// compute the duration of a MIPP instruction
		auto computeDuration = [&](const std::tuple<unsigned, std::string, std::string, std::chrono::nanoseconds>& bench, int &iType) -> float
		{
			if (std::get<0>(bench) == i)
			{
				id    = std::get<0>(bench);
				name  = std::get<1>(bench);
				group = std::get<2>(bench);
				iType++;

				return ((float)std::get<3>(bench).count()) / (float)Trials;
			}
			else
				return 0.;
		};

		const auto durationDouble = computeDuration(benchsDouble[iDouble], iDouble);
		const auto durationFloat  = computeDuration(benchsFloat [iFloat ], iFloat );
		const auto durationInt64  = computeDuration(benchsInt64 [iInt64 ], iInt64 );
		const auto durationInt32  = computeDuration(benchsInt32 [iInt32 ], iInt32 );
		const auto durationInt16  = computeDuration(benchsInt16 [iInt16 ], iInt16 );
		const auto durationInt8   = computeDuration(benchsInt8  [iInt8  ], iInt8  );

		if (!name.empty())
		{
			// converts float duration in string
			auto cvtDuration = [&](const float duration) -> std::string
			{
				std::stringstream tmpDuration;
				if (duration)
					tmpDuration << std::fixed << std::setprecision(2) << duration;
				return tmpDuration.str();
			};

			// CPI = Cycles Per Instruction
			auto computeCPI = [&](const float duration)->std::string
			{
				std::stringstream tmpCPI;
				if (duration && CPUFreq != 0.)
					tmpCPI << std::fixed << std::setprecision(1) << (CPUFreq * duration);
				return tmpCPI.str();
			};

			const auto strDurationDouble = cvtDuration(durationDouble);
			const auto strDurationFloat  = cvtDuration(durationFloat );
			const auto strDurationInt64  = cvtDuration(durationInt64 );
			const auto strDurationInt32  = cvtDuration(durationInt32 );
			const auto strDurationInt16  = cvtDuration(durationInt16 );
			const auto strDurationInt8   = cvtDuration(durationInt8  );

			const auto strCPIDouble = computeCPI(durationDouble);
			const auto strCPIFloat  = computeCPI(durationFloat );
			const auto strCPIInt64  = computeCPI(durationInt64 );
			const auto strCPIInt32  = computeCPI(durationInt32 );
			const auto strCPIInt16  = computeCPI(durationInt16 );
			const auto strCPIInt8   = computeCPI(durationInt8  );

			std::cout << std::fixed << std::setprecision(2);
			std::cout << std::setw( 3) << id                                                                                                      << " | "
			          << std::setw(16) << name                                                                                                    << " | "
			          << std::setw(12) << group                                                                                                   << " | "
			          << std::setw( 9) << strDurationDouble << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIDouble << " | "
			          << std::setw( 9) << strDurationFloat  << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIFloat  << " | "
			          << std::setw( 9) << strDurationInt64  << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIInt64  << " | "
			          << std::setw( 9) << strDurationInt32  << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIInt32  << " | "
			          << std::setw( 9) << strDurationInt16  << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIInt16  << " | "
			          << std::setw( 9) << strDurationInt8   << (CPUFreq == 0. ? "" : "   ") << std::setw((CPUFreq == 0. ? 0 : 4)) << strCPIInt8
			          << std::endl;
		}
	}

	return 0;
}
