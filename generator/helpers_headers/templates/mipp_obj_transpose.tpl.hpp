#pragma once
// MIPP transpositions of the C++ Object API: `transpose(t)` and `transpose_b128(t)` on an array of Vd registers,
// see mipp/cpp/transpose.hpp. T and LMUL are deduced from the array.
// Generated from generator/helpers_headers/templates/mipp_obj_transpose.tpl.hpp (utils_generator.py).

#include <cstddef>

#include "mipp/cpp/transpose.hpp"
#include "mipp/internal/interfaces/obj/common.hpp"

namespace mipp
{
// The Vd::N() rows of a square matrix become the rows of its transpose.
template <typename T, int LMUL>
inline void transpose(Vd<T, LMUL> (&t)[(Vd<T, LMUL>::N())])
{
	constexpr std::size_t K = Vd<T, LMUL>::N();
	vd<T, LMUL> r[K];
	for (std::size_t i = 0; i < K; i++)
		r[i] = t[i].vd;
	mipp::transpose<T, LMUL>(r);
	for (std::size_t i = 0; i < K; i++)
		t[i].vd = r[i];
}

// The K x K matrices of each block of 128 bits of the K = 16 / sizeof(T) registers are transposed.
template <typename T, int LMUL>
inline void transpose_b128(Vd<T, LMUL> (&t)[(16 / sizeof(T))])
{
	constexpr std::size_t K = 16 / sizeof(T);
	vd<T, LMUL> r[K];
	for (std::size_t i = 0; i < K; i++)
		r[i] = t[i].vd;
	mipp::transpose_b128<T, LMUL>(r);
	for (std::size_t i = 0; i < K; i++)
		t[i].vd = r[i];
}
} // namespace mipp
