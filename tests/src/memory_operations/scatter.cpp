#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename TD, typename TI>
void test_reg_scatter()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N,    (TD)1);
	std::iota(indexes, indexes + N*10, (TI)0);
	TD outputs[N*10];

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::fill(outputs, outputs + N*10, (TD)0);
		std::shuffle(indexes, indexes + N*10, g);

		mipp::reg idx = mipp::loadu<TI>(indexes);
		mipp::reg r = mipp::loadu<TD>(inputs);
		mipp::scatter<TD,TI>(outputs, idx, r);

		for (auto i = 0; i < N; i++)
			REQUIRE(+outputs[indexes[i]] == +mipp::get<TD>(r, i));
		for (auto i = 0; i < N*10; i++)
			if (std::find(std::begin(indexes), std::end(indexes), (TI)i) == std::end(indexes))
				REQUIRE(+outputs[i] == +(TD)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Scatter - mipp::reg", "[mipp::scatter]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_scatter<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_reg_scatter<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_scatter<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_scatter<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_scatter<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_reg_scatter<int8_t,int8_t>(); }
#endif
}
#endif

template <typename TD, typename TI>
void test_Reg_scatter()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N,    (TD)1);
	std::iota(indexes, indexes + N*10, (TI)0);
	TD outputs[N*10];

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::fill(outputs, outputs + N*10, (TD)0);
		std::shuffle(indexes, indexes + N*10, g);

		mipp::Reg<TI> idx = mipp::oloadu(indexes);
		mipp::Reg<TD> r = mipp::oloadu(inputs);
		mipp::scatter(outputs, idx, r);

		for (auto i = 0; i < N; i++)
			REQUIRE(+outputs[indexes[i]] == +r[i]);
		for (auto i = 0; i < N*10; i++)
			if (std::find(std::begin(indexes), std::end(indexes), (TI)i) == std::end(indexes))
				REQUIRE(+outputs[i] == +(TD)0);
	}
}

TEST_CASE("Scatter - mipp::Reg", "[mipp::scatter]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_scatter<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_Reg_scatter<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_scatter<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_scatter<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_scatter<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_Reg_scatter<int8_t,int8_t>(); }
#endif
}

template <typename TD, typename TI>
void test_reg_masksca()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N,    (TD)1);
	std::iota(indexes, indexes + N*10, (TI)0);
	TD outputs[N*10];

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::fill(outputs, outputs + N*10, (TD)0);
		std::shuffle(indexes, indexes + N*10, g);
		std::shuffle(mask,    mask    + N,    g);

		mipp::msk m = mipp::set<N>(mask);
		mipp::reg idx = mipp::loadu<TI>(indexes);
		mipp::reg r = mipp::loadu<TD>(inputs);
		mipp::masksca<TD,TI>(m, outputs, idx, r);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
				REQUIRE(+outputs[indexes[i]] == +mipp::get<TD>(r, i));
			else
				REQUIRE(+outputs[indexes[i]] == +(TD)0);
		}
		for (auto i = 0; i < N*10; i++)
			if (std::find(std::begin(indexes), std::end(indexes), (TI)i) == std::end(indexes))
				REQUIRE(+outputs[i] == +(TD)0);
	}
}

#ifndef MIPP_NO
TEST_CASE("Masked scatter - mipp::reg", "[mipp::masksca]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_masksca<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_reg_masksca<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_masksca<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_masksca<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_masksca<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_reg_masksca<int8_t,int8_t>(); }
#endif
}
#endif

template <typename TD, typename TI>
void test_Reg_masksca()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N,    (TD)1);
	std::iota(indexes, indexes + N*10, (TI)0);
	TD outputs[N*10];

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::fill(outputs, outputs + N*10, (TD)127);
		std::shuffle(indexes, indexes + N*10, g);
		std::shuffle(mask,    mask    + N,    g);

		mipp::Msk<N> m = mipp::oset<N>(mask);
		mipp::Reg<TI> idx = mipp::oloadu(indexes);
		mipp::Reg<TD> r = mipp::oloadu(inputs);
		mipp::masksca(m, outputs, idx, r);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
				REQUIRE(+outputs[indexes[i]] == +r[i]);
			else
				REQUIRE(+outputs[indexes[i]] == +(TD)127);
		}
		for (auto i = 0; i < N*10; i++)
			if (std::find(std::begin(indexes), std::end(indexes), (TI)i) == std::end(indexes))
				REQUIRE(+outputs[i] == +(TD)127);
	}
}

TEST_CASE("Masked scatter - mipp::Reg", "[mipp::masksca]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_masksca<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_Reg_masksca<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_masksca<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_masksca<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_masksca<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_Reg_masksca<int8_t,int8_t>(); }
#endif
}