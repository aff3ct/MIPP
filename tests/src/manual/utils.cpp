// Tests of the hand-written utilities (generator/helpers_headers/utils_generator.py): aligned allocation,
// printing of the registers, reduce and the initializer lists of the Object API.
// Not generated: tests/src/manual/ is kept by gen_mipp_tests.py.
#include <cstdio>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include <mipp.h>
#include <mipp.hpp>
#include <mipp_obj.hpp>

#include <catch2/catch_test_macros.hpp>

namespace
{
// "[0, 1, 2, 3 | 4, ...]" for the lanes 0..n-1 of a type with `per_block` lanes per 128 bits
std::string expected_lanes(const int n, const int per_block, const bool alternate_mask = false)
{
	std::string s = "[";
	for (int i = 0; i < n; i++)
	{
		if (i)
			s += (i % per_block) ? ", " : " | ";
		s += alternate_mask ? ((i % 2 == 0) ? "1" : "0") : std::to_string(i);
	}
	return s + "]";
}
} // namespace

TEST_CASE("utils - aligned allocation", "[utils]")
{
	void* p = mipp_malloc(100);
	REQUIRE(p != nullptr);
	REQUIRE(mipp_is_aligned(p));
	mipp_free(p);

	float* q = mipp::malloc<float>(33);
	REQUIRE(q != nullptr);
	REQUIRE(mipp::is_aligned(q));
	mipp::free(q);

	mipp::vector<double> v(1000, 1.0);
	REQUIRE(mipp::is_aligned(v.data()));
	mipp::vector<int8_t> w;
	for (int i = 0; i < 1000; i++)
		w.push_back(static_cast<int8_t>(i));
	REQUIRE(mipp::is_aligned(w.data()));
	REQUIRE(mipp::required_alignment() == static_cast<std::size_t>(MIPP_REQUIRED_ALIGNMENT));
}

TEST_CASE("utils - dump", "[utils]")
{
	constexpr int n = MIPP_N_INT32;
	int32_t in[n];
	int32_t mk[n];
	for (int i = 0; i < n; i++)
	{
		in[i] = i;
		mk[i] = (i % 2 == 0) ? -1 : 0;
	}
	const std::string lanes = expected_lanes(n, 4);
	const std::string lanes_k = expected_lanes(n, 4, true);

	// C API: written to a temporary file
	vd_int32_t r = mipp_loadu_int32(in);
	vm_int32_t m = mipp_set_k_int32(mk);
	FILE* f = std::tmpfile();
	REQUIRE(f != nullptr);
	mipp_fdump_int32(f, r);
	mipp_fdump_k_int32(f, m);
	std::rewind(f);
	std::string out;
	for (int c = std::fgetc(f); c != EOF; c = std::fgetc(f))
		out += static_cast<char>(c);
	std::fclose(f);
	REQUIRE(out == lanes + "\n" + lanes_k + "\n");

	// C++ Functional API
	std::ostringstream fun;
	mipp::dump<int32_t>(mipp::loadu<int32_t>(in), fun);
	mipp::dump_k<int32_t>(mipp::set_k<int32_t>(mk), fun);
	REQUIRE(fun.str() == lanes + "\n" + lanes_k + "\n");

	// C++ Object API
	std::ostringstream obj;
	obj << mipp::Vd<int32_t>(in) << ";" << mipp::Vm<int32_t>(mk);
	REQUIRE(obj.str() == lanes + ";" + lanes_k);

	// 8-bit lanes are printed as numbers, 16 lanes per 128-bit block
	int8_t in8[MIPP_N_INT8];
	for (int i = 0; i < MIPP_N_INT8; i++)
		in8[i] = static_cast<int8_t>(i);
	std::ostringstream o8;
	o8 << mipp::Vd<int8_t>(in8);
	REQUIRE(o8.str() == expected_lanes(MIPP_N_INT8, 16));
}

TEST_CASE("utils - reduce", "[utils]")
{
	std::vector<int32_t> data(103);
	for (size_t i = 0; i < data.size(); i++)
		data[i] = static_cast<int32_t>((i * 7919) % 211) - 100;
	const int32_t sum = std::accumulate(data.begin(), data.end(), 0);
	const int32_t mx = *std::max_element(data.begin(), data.end());
	const int32_t mn = *std::min_element(data.begin(), data.end());

	// one register, several LMULs
	const mipp::Vd<int32_t, 2> vd2(data.data());
	REQUIRE(mipp::reduce(vd2, mipp::op::add()) == std::accumulate(data.begin(), data.begin() + vd2.N(), 0));
	const mipp::Vd<int32_t> vd1(data.data());
	REQUIRE(mipp::reduce(vd1, mipp::op::max()) == *std::max_element(data.begin(), data.begin() + vd1.N()));

	// arrays: a length that is not a multiple of the register, and shorter than a register
	REQUIRE(mipp::reduce(data.data(), data.size(), mipp::op::add()) == sum);
	REQUIRE((mipp::reduce<int32_t, 2>(data.data(), data.size(), mipp::op::max())) == mx);
	REQUIRE(mipp::reduce(data.data(), data.size(), mipp::op::min()) == mn);
	REQUIRE(mipp::reduce(data.data(), 3, mipp::op::add()) == data[0] + data[1] + data[2]);
	REQUIRE(mipp::reduce(data.data(), 1, mipp::op::mul()) == data[0]);
}

TEST_CASE("utils - initializer lists", "[utils]")
{
	// a single value is broadcast, as Vd(val) / Vm(val)
	const mipp::Vd<int32_t> b = {5};
	const mipp::Vm<int32_t> t = {true};
	for (int i = 0; i < b.N(); i++)
	{
		REQUIRE(b[i] == 5);
		REQUIRE(t[i]);
	}
	// N values: the lanes in order
	if constexpr (mipp::N<int32_t>() == 4)
	{
		const mipp::Vd<int32_t> r = {1, 2, 3, 4};
		const mipp::Vm<int32_t> m = {true, false, false, true};
		REQUIRE((r[0] == 1 && r[1] == 2 && r[2] == 3 && r[3] == 4));
		REQUIRE((m[0] && !m[1] && !m[2] && m[3]));
	}
	else if constexpr (mipp::N<int32_t>() == 8)
	{
		const mipp::Vd<int32_t> r = {1, 2, 3, 4, 5, 6, 7, 8};
		for (int i = 0; i < 8; i++)
			REQUIRE(r[i] == i + 1);
	}
	else if constexpr (mipp::N<int32_t>() == 16)
	{
		const mipp::Vd<int32_t> r = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		for (int i = 0; i < 16; i++)
			REQUIRE(r[i] == i + 1);
	}
	// any other count is an error
	REQUIRE_THROWS_AS((mipp::Vd<int32_t>{1, 2}), std::invalid_argument);
}
