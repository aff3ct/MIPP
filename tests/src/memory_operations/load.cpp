#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp_obj.hpp>
#include <catch_amalgamated.hpp>


template <typename T>
void test_rvd_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::rvd<T> r = mipp::load(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load - mipp::rvd", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_load<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_load<int8_t>(); }
#endif
}
#endif

/*//ask about the 2 type
template <typename T>
void test_rvd_2_load()
{
    constexpr auto N_2 = mipp::N<T>()/2;

    T inputs[N_2];
    std::iota(inputs, inputs + N_2, (T)0);

    mipp::rvd_2 r = mipp::load_2(inputs);

    for (auto i = 0; i < N_2; i++)
        REQUIRE(mipp::get(r, i) == inputs[i]);
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Load - mipp::rvd_2", "[mipp::load_2]")
{
    SECTION("datatype = int32_t") { test_rvd_2_load<int32_t>(); }
}
#endif
#endif
#endif
*/

template <typename T>
void test_Rvd_load()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	//mipp::Rvd<T> r; r.load(inputs);
	mipp::Rvd<T> r = mipp::load(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load - mipp::Rvd", "[mipp::load]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_load<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_load<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_load<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_load<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_load<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_load<int8_t>(); }
#endif
}
/*
template <typename T>
void test_Rvd_2_load()
{
    constexpr auto N_2 = mipp::N<T>()/2;

	T inputs[N_2];
	std::iota(inputs, inputs + N_2, (T)0);

	mipp::Rvd_2<T> r; r.load(inputs);

	for (auto i = 0; i < N_2; i++)
		REQUIRE(r[i] == inputs[i]);
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Load - mipp::Rvd_2", "[mipp::load]")
{
   SECTION("datatype = int32_t") { test_Rvd_2_load<int32_t>(); }
}
#endif
#endif
#endif
*/

template <typename T>
void test_rvd_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::rvd<T> r = mipp::loadu(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(mipp::get(r, i) == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Load unaligned - mipp::rvd", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_loadu<int8_t>(); }
#endif
}
#endif
/*
template <typename T>
void test_rvd_2_loadu()
{
    constexpr auto N_2 = mipp::N<T>()/2;

    T inputs[N_2];
    std::iota(inputs, inputs + N_2, (T)0);

    mipp::rvd_2 r = mipp::loadu_2<T>(inputs);

    for (auto i = 0; i < N_2; i++)
        REQUIRE(mipp::get<T>(r, i) == inputs[i]);
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Load unaligned - mipp::rvd_2", "[mipp::loadu_2]")
{
    SECTION("datatype = int32_t") { test_rvd_2_loadu<int32_t>(); }
}
#endif
#endif
#endif
*/
template <typename T>
void test_Rvd_loadu()
{
	T inputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	//mipp::Rvd<T> r; r.loadu(inputs);
	mipp::Rvd<T> r = mipp::loadu(inputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(r[i] == inputs[i]);
}

TEST_CASE("Load unaligned - mipp::Rvd", "[mipp::loadu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_loadu<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_loadu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_loadu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_loadu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_loadu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_loadu<int8_t>(); }
#endif
}
/*
template <typename T>
void test_Rvd_2_loadu()
{
    constexpr auto N_2 = mipp::N<T>()/2;

    T inputs[N_2];
    std::iota(inputs, inputs + N_2, (T)0);

    mipp::Rvd_2<T> r; r.loadu(inputs);

    for (auto i = 0; i < N_2; i++)
        REQUIRE(r[i] == inputs[i]);
}

#ifndef MIPP_RVV
#if defined(MIPP_NEON) || defined(MIPP_AVX512) || defined(MIPP_AVX2) || defined(MIPP_AVX)
TEST_CASE("Load unaligned - mipp::Rvd_2", "[mipp::loadu_2]")
{
    SECTION("datatype = int32_t") { test_Rvd_2_loadu<int32_t>(); }
}
#endif
#endif


template <typename T, mipp::proto_il<T> IL = mipp::loadu<T>>
void test_rvd_maskzld()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N];
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

	mipp::msk m = mipp::set(mask);
	mipp::rvd r = mipp::maskzld(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(mipp::get(r, i) == inputs[i]);
		else
			REQUIRE(mipp::get(r, i) == (T)0);
	}
}

#ifndef MIPP_RVV
#ifndef MIPP_NO
// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__))
#ifndef MIPP_NO
TEST_CASE("Masked load - mipp::rvd", "[mipp::maskzld]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_maskzld<double, mipp::loadu<double>>(); }
	SECTION("datatype = double") { test_rvd_maskzld<double, mipp::load<double>>(); }
#endif
	SECTION("datatype = float") { test_rvd_maskzld<float, mipp::loadu<float>>(); }
	SECTION("datatype = float") { test_rvd_maskzld<float, mipp::load<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_maskzld<int64_t, mipp::loadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_rvd_maskzld<int64_t, mipp::load<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_maskzld<int32_t, mipp::loadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_rvd_maskzld<int32_t, mipp::load<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_maskzld<int16_t, mipp::loadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_rvd_maskzld<int16_t, mipp::load<int16_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskzld<int8_t, mipp::loadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskzld<int8_t, mipp::load<int8_t>>(); }
#endif
}
#endif
#endif
#endif
#endif

template <typename T, mipp::proto_IL<T> IL = mipp::oloadu<T>>
void test_Rvd_maskzld()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N];
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
	mipp::Rvd<T> r = mipp::maskzld<T,IL>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(r[i] == inputs[i]);
		else
			REQUIRE(r[i] == (T)0);
	}
}

#ifndef MIPP_NO
// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
TEST_CASE("Masked load - mipp::Rvd", "[mipp::maskzld]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_maskzld<double, mipp::oloadu<double>>(); }
	SECTION("datatype = double") { test_Rvd_maskzld<double, mipp::oload<double>>(); }
#endif
	SECTION("datatype = float") { test_Rvd_maskzld<float, mipp::oloadu<float>>(); }
	SECTION("datatype = float") { test_Rvd_maskzld<float, mipp::oload<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_maskzld<int64_t, mipp::oloadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Rvd_maskzld<int64_t, mipp::oload<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_maskzld<int32_t, mipp::oloadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Rvd_maskzld<int32_t, mipp::oload<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_maskzld<int16_t, mipp::oloadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Rvd_maskzld<int16_t, mipp::oload<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskzld<int8_t, mipp::oloadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskzld<int8_t, mipp::oload<int8_t>>(); }
#endif
}
#endif
#endif
*/
/*
template <typename T, mipp::proto_il<T> IL = mipp::loadu<T>, mipp::proto_is<T> IS = mipp::storeu<T>>
void test_rvd_maskzlds()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N/2];
#else
	T inputs[N/2];
#endif
	std::iota(inputs, inputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	mipp::msk m = mipp::set<N>(mask);
	mipp::rvd r = mipp::maskzlds<T,IL,IS>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(mipp::get<T>(r, i) == inputs[i]);
		else
			REQUIRE(mipp::get<T>(r, i) == (T)0);
	}
}

#ifndef MIPP_RVV
// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked load safe - mipp::rvd", "[mipp::maskzlds]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_maskzlds<double, mipp::loadu<double>, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_rvd_maskzlds<double, mipp::load<double>, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_rvd_maskzlds<float, mipp::loadu<float>, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_rvd_maskzlds<float, mipp::load<float>, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_maskzlds<int64_t, mipp::loadu<int64_t>, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_rvd_maskzlds<int64_t, mipp::load<int64_t>, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_maskzlds<int32_t, mipp::loadu<int32_t>, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_rvd_maskzlds<int32_t, mipp::load<int32_t>, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_maskzlds<int16_t, mipp::loadu<int16_t>, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_rvd_maskzlds<int16_t, mipp::load<int16_t>, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskzlds<int8_t, mipp::loadu<int8_t>, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskzlds<int8_t, mipp::load<int8_t>, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif
#endif

template <typename T, mipp::proto_IL<T> IL = mipp::oloadu<T>, mipp::proto_IS<T> IS = mipp::storeu<T>>
void test_Rvd_maskzlds()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N/2];
#else
	T inputs[N/2];
#endif
	std::iota(inputs, inputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	mipp::Msk<N> m = mipp::oset<N>(mask);
	mipp::Rvd<T> r = mipp::maskzlds<T,IL,IS>(m, inputs);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(r[i] == inputs[i]);
		else
			REQUIRE(r[i] == (T)0);
	}
}

#ifndef MIPP_RVV
// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked load safe - mipp::Rvd", "[mipp::maskzlds]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_maskzlds<double, mipp::oloadu<double>, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_Rvd_maskzlds<double, mipp::oload<double>, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_Rvd_maskzlds<float, mipp::oloadu<float>, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_Rvd_maskzlds<float, mipp::oload<float>, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_maskzlds<int64_t, mipp::oloadu<int64_t>, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Rvd_maskzlds<int64_t, mipp::oload<int64_t>, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_maskzlds<int32_t, mipp::oloadu<int32_t>, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Rvd_maskzlds<int32_t, mipp::oload<int32_t>, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_maskzlds<int16_t, mipp::oloadu<int16_t>, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Rvd_maskzlds<int16_t, mipp::oload<int16_t>, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskzlds<int8_t, mipp::oloadu<int8_t>, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskzlds<int8_t, mipp::oload<int8_t>, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif
#endif
*/