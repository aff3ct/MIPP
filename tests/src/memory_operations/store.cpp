#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch_amalgamated.hpp>


template <typename T>
void test_rvd_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::rvd<T> r = mipp::load(inputs);
	mipp::store(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store - mipp::rvd", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_store<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_store<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_store<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	//mipp::Rvd<T> r; r.load(inputs);
	mipp::Rvd<T> r = mipp::load(inputs);
	//r.store(outputs);
	mipp::store(outputs, r.r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store - mipp::Rvd", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_store<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_store<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_store<int8_t>(); }
#endif
}

template <typename T>
void test_rvd_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::rvd<T> r = mipp::loadu(inputs);
	mipp::storeu(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store unaligned - mipp::rvd", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_rvd_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_storeu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_rvd_storeu<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Rvd_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Rvd<T> r; 
	r.r = mipp::loadu(inputs);
	//r.storeu(outputs);
	mipp::storeu(outputs, r.r);//breaks the tests on AVX2 

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store unaligned - mipp::Rvd", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_Rvd_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_storeu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Rvd_storeu<int8_t>(); }
#endif
}
/*
template <typename T, mipp::proto_is<T> IS = mipp::storeu<T>, mipp::proto_il<T> IL = mipp::loadu<T>>
void test_rvd_maskst()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N], outputs[N], outputs_cpy[N];
#else
	T inputs[N], outputs[N], outputs_cpy[N];
#endif
	std::iota(inputs,  inputs  + N, (T)0);
	std::iota(outputs, outputs + N, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs,  inputs  + N, g);
	std::shuffle(outputs, outputs + N, g);
	std::shuffle(mask,    mask    + N, g);

	std::copy(outputs, outputs + N, outputs_cpy);

	mipp::msk m = mipp::set<N>(mask);
	mipp::rvd r = mipp::loadu<T>(inputs);
	mipp::maskst<T,IS,IL>(m, outputs, r);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(outputs[i] == inputs[i]);
		else
			REQUIRE(outputs[i] == outputs_cpy[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked store - mipp::rvd", "[mipp::maskst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_maskst<double, mipp::storeu<double>, mipp::loadu<double>>(); }
	SECTION("datatype = double") { test_rvd_maskst<double, mipp::store<double>, mipp::load<double>>(); }
#endif
	SECTION("datatype = float") { test_rvd_maskst<float, mipp::storeu<float>, mipp::loadu<float>>(); }
	SECTION("datatype = float") { test_rvd_maskst<float, mipp::store<float>, mipp::load<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_maskst<int64_t, mipp::storeu<int64_t>, mipp::loadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_rvd_maskst<int64_t, mipp::store<int64_t>, mipp::load<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_maskst<int32_t, mipp::storeu<int32_t>, mipp::loadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_rvd_maskst<int32_t, mipp::store<int32_t>, mipp::load<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_maskst<int16_t, mipp::storeu<int16_t>, mipp::loadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_rvd_maskst<int16_t, mipp::store<int16_t>, mipp::load<int16_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskst<int8_t, mipp::storeu<int8_t>, mipp::loadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_maskst<int8_t, mipp::store<int8_t>, mipp::load<int8_t>>(); }
#endif
}
#endif
#endif

template <typename T, mipp::proto_IS<T> IS = mipp::storeu<T>, mipp::proto_IL<T> IL = mipp::oloadu<T>>
void test_Rvd_maskst()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N], outputs[N], outputs_cpy[N];
#else
	T inputs[N], outputs[N], outputs_cpy[N];
#endif
	std::iota(inputs,  inputs  + N, (T)0);
	std::iota(outputs, outputs + N, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs,  inputs  + N, g);
	std::shuffle(outputs, outputs + N, g);
	std::shuffle(mask,    mask    + N, g);

	std::copy(outputs, outputs + N, outputs_cpy);

	mipp::Msk<N> m = mipp::oset<N>(mask);
	mipp::Rvd<T> r = mipp::oloadu<T>(inputs);
	mipp::maskst<T,IS,IL>(m, outputs, r);

	for (auto i = 0; i < N; i++)
	{
		if (mask[i])
			REQUIRE(outputs[i] == inputs[i]);
		else
			REQUIRE(outputs[i] == outputs_cpy[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
TEST_CASE("Masked store - mipp::Rvd", "[mipp::maskst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_maskst<double, mipp::storeu<double>, mipp::oloadu<double>>(); }
	SECTION("datatype = double") { test_Rvd_maskst<double, mipp::store<double>, mipp::oload<double>>(); }
#endif
	SECTION("datatype = float") { test_Rvd_maskst<float, mipp::storeu<float>, mipp::oloadu<float>>(); }
	SECTION("datatype = float") { test_Rvd_maskst<float, mipp::store<float>, mipp::oload<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_maskst<int64_t, mipp::storeu<int64_t>, mipp::oloadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Rvd_maskst<int64_t, mipp::store<int64_t>, mipp::oload<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_maskst<int32_t, mipp::storeu<int32_t>, mipp::oloadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Rvd_maskst<int32_t, mipp::store<int32_t>, mipp::oload<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_maskst<int16_t, mipp::storeu<int16_t>, mipp::oloadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Rvd_maskst<int16_t, mipp::store<int16_t>, mipp::oload<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskst<int8_t, mipp::storeu<int8_t>, mipp::oloadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_maskst<int8_t, mipp::store<int8_t>, mipp::oload<int8_t>>(); }
#endif
}
#endif

template <typename T, mipp::proto_is<T> IS = mipp::storeu<T>>
void test_rvd_masksts()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N], outputs[N/2], outputs_cpy[N/2];
#else
	T inputs[N], outputs[N/2], outputs_cpy[N/2];
#endif
	std::iota(inputs,  inputs  + N,   (T)0);
	std::iota(outputs, outputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs,  inputs  + N,   g);
	std::shuffle(outputs, outputs + N/2, g);

	std::copy(outputs, outputs + N/2, outputs_cpy);

	mipp::msk m = mipp::set<N>(mask);
	mipp::rvd r = mipp::loadu<T>(inputs);
	mipp::masksts<T,IS>(m, outputs, r);

	for (auto i = 0; i < N/2; i++)
	{
		REQUIRE(outputs[i] == inputs[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked store safe - mipp::rvd", "[mipp::masksts]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_rvd_masksts<double, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_rvd_masksts<double, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_rvd_masksts<float, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_rvd_masksts<float, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_rvd_masksts<int64_t, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_rvd_masksts<int64_t, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_rvd_masksts<int32_t, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_rvd_masksts<int32_t, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_rvd_masksts<int16_t, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_rvd_masksts<int16_t, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_masksts<int8_t, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_rvd_masksts<int8_t, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif

#ifndef MIPP_NO
template <typename T, mipp::proto_IS<T> IS = mipp::storeu<T>>
void test_Rvd_masksts()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::rvd)) T inputs[N], outputs[N/2], outputs_cpy[N/2];
#else
	T inputs[N], outputs[N/2], outputs_cpy[N/2];
#endif
	std::iota(inputs,  inputs  + N,   (T)0);
	std::iota(outputs, outputs + N/2, (T)0);

	bool mask[N];
	std::fill(mask,       mask + N/2, true );
	std::fill(mask + N/2, mask + N,   false);

	std::mt19937 g;
	std::shuffle(inputs,  inputs  + N,   g);
	std::shuffle(outputs, outputs + N/2, g);

	std::copy(outputs, outputs + N/2, outputs_cpy);

	mipp::Msk<N> m = mipp::oset<N>(mask);
	mipp::Rvd<T> r = mipp::oloadu<T>(inputs);
	mipp::masksts<T,IS>(m, outputs, r);

	for (auto i = 0; i < N/2; i++)
	{
		REQUIRE(outputs[i] == inputs[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
TEST_CASE("Masked store safe - mipp::Rvd", "[mipp::masksts]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Rvd_masksts<double, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_Rvd_masksts<double, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_Rvd_masksts<float, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_Rvd_masksts<float, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Rvd_masksts<int64_t, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Rvd_masksts<int64_t, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Rvd_masksts<int32_t, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Rvd_masksts<int32_t, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Rvd_masksts<int16_t, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Rvd_masksts<int16_t, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_masksts<int8_t, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Rvd_masksts<int8_t, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif
*/