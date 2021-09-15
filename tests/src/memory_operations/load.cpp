#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load - mipp::reg", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_load<double>(); }
#endif
	SECTION("datatype = float") { test_reg_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_load<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.load(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load - mipp::Reg", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_load<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_load<int8_t>(); }
#endif
}

template <typename T>
void test_reg_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::loadu<T>(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get<T>(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load unaligned - mipp::reg", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_reg_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_loadu<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.loadu(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load unaligned - mipp::Reg", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_loadu<int8_t>(); }
#endif
}

template <typename T, mipp::proto_il<T> IL = mipp::loadu<T>>
void test_reg_maskzld()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N];
#else
	T inputs[N];
#endif

	std::iota(inputs, inputs + N, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);
	std::shuffle(mask,   mask   + N, g);

	mipp::msk m = mipp::set<N>(mask);
	mipp::reg r = mipp::maskzld<T,IL>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(mipp::get<T>(r, i) == inputs[i]);
		else
			REQUIRE(mipp::get<T>(r, i) == (T)0);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__))
#ifndef MIPP_NO
TEST_CASE("Masked load - mipp::reg", "[mipp::maskzld]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskzld<double, mipp::loadu<double>>(); }
	SECTION("datatype = double") { test_reg_maskzld<double, mipp::load<double>>(); }
#endif
	SECTION("datatype = float") { test_reg_maskzld<float, mipp::loadu<float>>(); }
	SECTION("datatype = float") { test_reg_maskzld<float, mipp::load<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskzld<int64_t, mipp::loadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_reg_maskzld<int64_t, mipp::load<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskzld<int32_t, mipp::loadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_reg_maskzld<int32_t, mipp::load<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskzld<int16_t, mipp::loadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_reg_maskzld<int16_t, mipp::load<int16_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskzld<int8_t, mipp::loadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskzld<int8_t, mipp::load<int8_t>>(); }
#endif
}
#endif
#endif

template <typename T, mipp::proto_IL<T> IL = mipp::oloadu<T>>
void test_Reg_maskzld()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N];
#else
	T inputs[N];
#endif
	std::iota(inputs, inputs + N, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs, inputs + N, g);
	std::shuffle(mask,   mask   + N, g);

	mipp::Msk<N> m = mipp::oset<N>(mask);
	mipp::Reg<T> r = mipp::maskzld<T,IL>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(r[i] == inputs[i]);
		else
			REQUIRE(r[i] == (T)0);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
TEST_CASE("Masked load - mipp::Reg", "[mipp::maskzld]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskzld<double, mipp::oloadu<double>>(); }
	SECTION("datatype = double") { test_Reg_maskzld<double, mipp::oload<double>>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskzld<float, mipp::oloadu<float>>(); }
	SECTION("datatype = float") { test_Reg_maskzld<float, mipp::oload<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskzld<int64_t, mipp::oloadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Reg_maskzld<int64_t, mipp::oload<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskzld<int32_t, mipp::oloadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Reg_maskzld<int32_t, mipp::oload<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskzld<int16_t, mipp::oloadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Reg_maskzld<int16_t, mipp::oload<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskzld<int8_t, mipp::oloadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskzld<int8_t, mipp::oload<int8_t>>(); }
#endif
}
#endif

template <typename T, mipp::proto_il<T> IL = mipp::loadu<T>, mipp::proto_is<T> IS = mipp::storeu<T>>
void test_reg_maskzlds()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N/2];
#else
	T inputs[N/2];
#endif
	std::iota(inputs, inputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	mipp::msk m = mipp::set<N>(mask);
	mipp::reg r = mipp::maskzlds<T,IL,IS>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(mipp::get<T>(r, i) == inputs[i]);
		else
			REQUIRE(mipp::get<T>(r, i) == (T)0);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked load safe - mipp::reg", "[mipp::maskzlds]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskzlds<double, mipp::loadu<double>, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_reg_maskzlds<double, mipp::load<double>, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_reg_maskzlds<float, mipp::loadu<float>, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_reg_maskzlds<float, mipp::load<float>, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskzlds<int64_t, mipp::loadu<int64_t>, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_reg_maskzlds<int64_t, mipp::load<int64_t>, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskzlds<int32_t, mipp::loadu<int32_t>, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_reg_maskzlds<int32_t, mipp::load<int32_t>, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskzlds<int16_t, mipp::loadu<int16_t>, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_reg_maskzlds<int16_t, mipp::load<int16_t>, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskzlds<int8_t, mipp::loadu<int8_t>, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskzlds<int8_t, mipp::load<int8_t>, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif

template <typename T, mipp::proto_IL<T> IL = mipp::oloadu<T>, mipp::proto_IS<T> IS = mipp::storeu<T>>
void test_Reg_maskzlds()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N/2];
#else
	T inputs[N/2];
#endif
	std::iota(inputs, inputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	mipp::Msk<N> m = mipp::oset<N>(mask);
	mipp::Reg<T> r = mipp::maskzlds<T,IL,IS>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(r[i] == inputs[i]);
		else
			REQUIRE(r[i] == (T)0);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked load safe - mipp::Reg", "[mipp::maskzlds]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskzlds<double, mipp::oloadu<double>, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_Reg_maskzlds<double, mipp::oload<double>, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskzlds<float, mipp::oloadu<float>, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_Reg_maskzlds<float, mipp::oload<float>, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskzlds<int64_t, mipp::oloadu<int64_t>, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Reg_maskzlds<int64_t, mipp::oload<int64_t>, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskzlds<int32_t, mipp::oloadu<int32_t>, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Reg_maskzlds<int32_t, mipp::oload<int32_t>, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskzlds<int16_t, mipp::oloadu<int16_t>, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Reg_maskzlds<int16_t, mipp::oload<int16_t>, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskzlds<int8_t, mipp::oloadu<int8_t>, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskzlds<int8_t, mipp::oload<int8_t>, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif
