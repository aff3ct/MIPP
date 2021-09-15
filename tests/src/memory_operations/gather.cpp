#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename TD, typename TI>
void test_reg_gather()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N*10];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N*10, (TD)0);
	std::iota(indexes, indexes + N*10, (TI)0);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::shuffle(indexes, indexes + N*10, g);

		mipp::reg idx = mipp::loadu<TI>(indexes);
		mipp::reg r = mipp::gather<TD,TI>(inputs, idx);

		for (auto i = 0; i < N; i++)
			REQUIRE(+mipp::get<TD>(r, i) == +inputs[indexes[i]]);
	}
}

#ifndef MIPP_NO
TEST_CASE("Gather - mipp::reg", "[mipp::gather]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_gather<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_reg_gather<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_gather<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_gather<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_gather<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_reg_gather<int8_t,int8_t>(); }
#endif
}
#endif

template <typename TD, typename TI>
void test_Reg_gather()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N*10];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N*10, (TD)0);
	std::iota(indexes, indexes + N*10, (TI)0);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::shuffle(indexes, indexes + N*10, g);

		mipp::Reg<TI> idx = mipp::oloadu(indexes);
		mipp::Reg<TD> r = mipp::gather<TD>(inputs, idx);

		for (auto i = 0; i < N; i++)
			REQUIRE(+r[i] == +inputs[indexes[i]]);
	}
}

TEST_CASE("Gather - mipp::Reg", "[mipp::gather]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_gather<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_Reg_gather<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_gather<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_gather<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_gather<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_Reg_gather<int8_t,int8_t>(); }
#endif
}

template <typename TD, typename TI>
void test_reg_maskzgat()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N*10];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N*10, (TD)0);
	std::iota(indexes, indexes + N*10, (TI)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::shuffle(indexes, indexes + N*10, g);
		std::shuffle(mask,    mask    + N,    g);

		mipp::msk m = mipp::set<N>(mask);
		mipp::reg idx = mipp::loadu<TI>(indexes);
		mipp::reg r = mipp::maskzgat<TD,TI>(m, inputs, idx);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
				REQUIRE(+mipp::get<TD>(r, i) == +inputs[indexes[i]]);
			else
				REQUIRE(+mipp::get<TD>(r, i) == (TD)0);
		}
	}
}

#ifndef MIPP_NO
TEST_CASE("Masked gather - mipp::reg", "[mipp::maskzgat]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskzgat<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_reg_maskzgat<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskzgat<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskzgat<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskzgat<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_reg_maskzgat<int8_t,int8_t>(); }
#endif
}
#endif

template <typename TD, typename TI>
void test_Reg_maskzgat()
{
	constexpr int N = mipp::N<TD>();
	TD inputs [N*10];
	TI indexes[N*10];
	std::iota(inputs,  inputs  + N*10, (TD)0);
	std::iota(indexes, indexes + N*10, (TI)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	for (auto i = 0; i < 20; i++)
	{
		std::shuffle(indexes, indexes + N*10, g);
		std::shuffle(mask,    mask    + N,    g);

		mipp::Msk<N> m = mipp::oset<N>(mask);
		mipp::Reg<TI> idx = mipp::oloadu(indexes);
		mipp::Reg<TD> r = mipp::maskzgat(m, inputs, idx);

		for (auto i = 0; i < N; i++)
		{
			if (mask[i])
				REQUIRE(+r[i] == +inputs[indexes[i]]);
			else
				REQUIRE(+r[i] == (TD)0);
		}
	}
}

TEST_CASE("Masked gather - mipp::Reg", "[mipp::maskzgat]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskzgat<double,int64_t>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskzgat<float,int32_t>(); }
#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskzgat<int64_t,int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskzgat<int32_t,int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskzgat<int16_t,int16_t>(); }
	//SECTION("datatype = int8_t") { test_Reg_maskzgat<int8_t,int8_t>(); }
#endif
}