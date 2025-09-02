#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

#ifndef MIPP_NO
template <typename T1, typename T2>
void test_reg_pack()
{
	constexpr int N1 = mipp::N<T1>();
	constexpr int N2 = mipp::N<T2>();

	static_assert(N1 < N2, "N1 has to be smaller than N2.");

	T1 inputs1[N1], inputs2[N1];
	std::iota(inputs1, inputs1 + N1, std::numeric_limits<T1>::max() - (T1)N1);
	std::iota(inputs2, inputs2 + N1, (T1)-N1/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + N1, g);
	std::shuffle(inputs2, inputs2 + N1, g);

	mipp::reg r1 = mipp::load<T1>(inputs1);
	mipp::reg r2 = mipp::load<T1>(inputs2);
	mipp::reg r3 = mipp::pack<T1,T2>(r1, r2);

	T1 m = (T1)std::numeric_limits<T2>::min();
	T1 M = (T1)std::numeric_limits<T2>::max();
	for (auto i = 0; i < N1; i++)
	{
		auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs1[i], m), M));
		REQUIRE(mipp::get<T2>(r3, i) == res);
	}

	for (auto i = 0; i < N1; i++)
	{
		auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs2[i], m), M));
		REQUIRE(mipp::get<T2>(r3, N1 +i) == res);
	}
}
#endif

#ifndef MIPP_NO
TEST_CASE("Pack - mipp::reg", "[mipp::pack]")
{
#if defined(MIPP_BW)
	SECTION("datatype = int32_t -> int16_t") { test_reg_pack<int32_t,int16_t>(); }
	SECTION("datatype = int16_t -> int8_t") { test_reg_pack<int16_t,int8_t>(); }
#endif
}
#endif

#ifndef MIPP_NO
template <typename T1, typename T2>
void test_Reg_pack()
{
	constexpr int N1 = mipp::N<T1>();
	constexpr int N2 = mipp::N<T2>();

	static_assert(N1 < N2, "N1 has to be smaller than N2.");

	T1 inputs1[N1], inputs2[N1];
	std::iota(inputs1, inputs1 + N1, std::numeric_limits<T1>::max() - (T1)N1);
	std::iota(inputs2, inputs2 + N1, (T1)-N1/2);

	std::mt19937 g;
	std::shuffle(inputs1, inputs1 + N1, g);
	std::shuffle(inputs2, inputs2 + N1, g);

	mipp::Reg<T1> r1 = inputs1;
	mipp::Reg<T1> r2 = inputs2;
	mipp::Reg<T2> r3 = mipp::pack<T1,T2>(r1, r2);

	T1 m = (T1)std::numeric_limits<T2>::min();
	T1 M = (T1)std::numeric_limits<T2>::max();
	for (auto i = 0; i < N1; i++)
	{
		auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs1[i], m), M));
		REQUIRE(r3[i] == res);
	}

	for (auto i = 0; i < N1; i++)
	{
		auto res = static_cast<T2>(std::min<T1>(std::max<T1>(inputs2[i], m), M));
		REQUIRE(r3[N1 +i] == res);
	}
}
#endif

#ifndef MIPP_NO
TEST_CASE("Pack - mipp::Reg", "[mipp::pack]")
{
#if defined(MIPP_BW)
	SECTION("datatype = int32_t -> int16_t") { test_Reg_pack<int32_t,int16_t>(); }
	SECTION("datatype = int16_t -> int8_t") { test_Reg_pack<int16_t,int8_t>(); }
#endif
}
#endif
