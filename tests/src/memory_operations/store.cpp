#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::load<T>(inputs);
	mipp::store<T>(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store - mipp::reg", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_store<double>(); }
#endif
	SECTION("datatype = float") { test_reg_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_store<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_store<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_store()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.load(inputs);
	r.store(outputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store - mipp::Reg", "[mipp::store]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_store<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_store<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_store<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_store<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_store<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_store<int8_t>(); }
#endif
}

template <typename T>
void test_reg_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::reg r = mipp::loadu<T>(inputs);
	mipp::storeu<T>(outputs, r);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

#ifndef MIPP_NO
TEST_CASE("Store unaligned - mipp::reg", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_reg_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_storeu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_storeu<int8_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_storeu()
{
	T inputs[mipp::N<T>()], outputs[mipp::N<T>()];
	std::iota(inputs, inputs + mipp::N<T>(), (T)0);

	mipp::Reg<T> r; r.loadu(inputs);
	r.storeu(outputs);

	for (auto i = 0; i < mipp::N<T>(); i++)
		REQUIRE(outputs[i] == inputs[i]);
}

TEST_CASE("Store unaligned - mipp::Reg", "[mipp::storeu]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_storeu<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_storeu<float>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_storeu<int64_t>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_storeu<int32_t>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_storeu<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_storeu<int8_t>(); }
#endif
}

template <typename T, mipp::proto_is<T> IS = mipp::storeu<T>, mipp::proto_il<T> IL = mipp::loadu<T>>
void test_reg_maskst()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N], outputs[N], outputs_cpy[N];
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
	mipp::reg r = mipp::loadu<T>(inputs);
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
TEST_CASE("Masked store - mipp::reg", "[mipp::maskst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_maskst<double, mipp::storeu<double>, mipp::loadu<double>>(); }
	SECTION("datatype = double") { test_reg_maskst<double, mipp::store<double>, mipp::load<double>>(); }
#endif
	SECTION("datatype = float") { test_reg_maskst<float, mipp::storeu<float>, mipp::loadu<float>>(); }
	SECTION("datatype = float") { test_reg_maskst<float, mipp::store<float>, mipp::load<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_maskst<int64_t, mipp::storeu<int64_t>, mipp::loadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_reg_maskst<int64_t, mipp::store<int64_t>, mipp::load<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_maskst<int32_t, mipp::storeu<int32_t>, mipp::loadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_reg_maskst<int32_t, mipp::store<int32_t>, mipp::load<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_maskst<int16_t, mipp::storeu<int16_t>, mipp::loadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_reg_maskst<int16_t, mipp::store<int16_t>, mipp::load<int16_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskst<int8_t, mipp::storeu<int8_t>, mipp::loadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_reg_maskst<int8_t, mipp::store<int8_t>, mipp::load<int8_t>>(); }
#endif
}
#endif
#endif

template <typename T, mipp::proto_IS<T> IS = mipp::storeu<T>, mipp::proto_IL<T> IL = mipp::oloadu<T>>
void test_Reg_maskst()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N], outputs[N], outputs_cpy[N];
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
	mipp::Reg<T> r = mipp::oloadu<T>(inputs);
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
TEST_CASE("Masked store - mipp::Reg", "[mipp::maskst]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_maskst<double, mipp::storeu<double>, mipp::oloadu<double>>(); }
	SECTION("datatype = double") { test_Reg_maskst<double, mipp::store<double>, mipp::oload<double>>(); }
#endif
	SECTION("datatype = float") { test_Reg_maskst<float, mipp::storeu<float>, mipp::oloadu<float>>(); }
	SECTION("datatype = float") { test_Reg_maskst<float, mipp::store<float>, mipp::oload<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_maskst<int64_t, mipp::storeu<int64_t>, mipp::oloadu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Reg_maskst<int64_t, mipp::store<int64_t>, mipp::oload<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_maskst<int32_t, mipp::storeu<int32_t>, mipp::oloadu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Reg_maskst<int32_t, mipp::store<int32_t>, mipp::oload<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_maskst<int16_t, mipp::storeu<int16_t>, mipp::oloadu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Reg_maskst<int16_t, mipp::store<int16_t>, mipp::oload<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskst<int8_t, mipp::storeu<int8_t>, mipp::oloadu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_maskst<int8_t, mipp::store<int8_t>, mipp::oload<int8_t>>(); }
#endif
}
#endif

template <typename T, mipp::proto_is<T> IS = mipp::storeu<T>>
void test_reg_masksts()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N], outputs[N/2], outputs_cpy[N/2];
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
	mipp::reg r = mipp::loadu<T>(inputs);
	mipp::masksts<T,IS>(m, outputs, r);

	for (auto i = 0; i < N/2; i++)
	{
		REQUIRE(outputs[i] == inputs[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
#ifndef MIPP_NO
TEST_CASE("Masked store safe - mipp::reg", "[mipp::masksts]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_masksts<double, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_reg_masksts<double, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_reg_masksts<float, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_reg_masksts<float, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_reg_masksts<int64_t, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_reg_masksts<int64_t, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_reg_masksts<int32_t, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_reg_masksts<int32_t, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_masksts<int16_t, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_reg_masksts<int16_t, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_reg_masksts<int8_t, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_reg_masksts<int8_t, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif

#ifndef MIPP_NO
template <typename T, mipp::proto_IS<T> IS = mipp::storeu<T>>
void test_Reg_masksts()
{
	constexpr int N = mipp::N<T>();
#ifndef MIPP_NO
	alignas(alignof(mipp::reg)) T inputs[N], outputs[N/2], outputs_cpy[N/2];
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
	mipp::Reg<T> r = mipp::oloadu<T>(inputs);
	mipp::masksts<T,IS>(m, outputs, r);

	for (auto i = 0; i < N/2; i++)
	{
		REQUIRE(outputs[i] == inputs[i]);
	}
}

// this is a hack, I don't know why there is a segfault on Windows + GCC when this is enabled...
#if !(defined(_WIN32) && defined(__GNUC__)) 
TEST_CASE("Masked store safe - mipp::Reg", "[mipp::masksts]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_masksts<double, mipp::storeu<double>>(); }
	SECTION("datatype = double") { test_Reg_masksts<double, mipp::store<double>>(); }
#endif
	SECTION("datatype = float") { test_Reg_masksts<float, mipp::storeu<float>>(); }
	SECTION("datatype = float") { test_Reg_masksts<float, mipp::store<float>>(); }

#if defined(MIPP_64BIT)
	SECTION("datatype = int64_t") { test_Reg_masksts<int64_t, mipp::storeu<int64_t>>(); }
	SECTION("datatype = int64_t") { test_Reg_masksts<int64_t, mipp::store<int64_t>>(); }
#endif
	SECTION("datatype = int32_t") { test_Reg_masksts<int32_t, mipp::storeu<int32_t>>(); }
	SECTION("datatype = int32_t") { test_Reg_masksts<int32_t, mipp::store<int32_t>>(); }
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_masksts<int16_t, mipp::storeu<int16_t>>(); }
	SECTION("datatype = int16_t") { test_Reg_masksts<int16_t, mipp::store<int16_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_masksts<int8_t, mipp::storeu<int8_t>>(); }
	SECTION("datatype = int8_t") { test_Reg_masksts<int8_t, mipp::store<int8_t>>(); }
#endif
}
#endif
#endif