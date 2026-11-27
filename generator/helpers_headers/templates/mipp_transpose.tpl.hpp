#pragma once
// MIPP transpositions of the C++ Functional API: `transpose<T>(t)` and `transpose_b128<T>(t)`, in place on an array
// of registers (MIPPv1 `transpose`, `transpose2`, `transpose8x8`, `transpose28x8`).
// Generated from generator/helpers_headers/templates/mipp_transpose.tpl.hpp (utils_generator.py).
//
//     mipp::vd<float> t[mipp::N<float>()]; // the rows of a N x N matrix
//     mipp::transpose<float>(t);           // the rows of its transpose
//
// - transpose<T, LMUL>(t): t is an array of N<T, LMUL>() registers, the rows of a square matrix; they become the rows
//   of its transpose (t[i] lane j receives the former t[j] lane i).
// - transpose_b128<T, LMUL>(t): t is an array of K = 16 / sizeof(T) registers (4 float32, 8 int16, 16 int8...); each
//   block of 128 bits of the K registers is a K x K matrix, transposed independently (a register of 2 blocks holds 2
//   matrices side by side). It is `transpose` when the registers have 128 bits (SSE, NEON).
//
// The array sizes are part of the types (in parentheses: a template-id with a comma in an array bound of a
// parameter is read as an expression by Clang): a wrong number of registers does not compile. The number of lanes is a
// constant of the compilation on every ISA (SVE and RVV with a fixed register size), so the arrays are ordinary
// arrays; for large registers (64 lanes and more), they do not fit in the register file and live in memory.
//
// Both are log2(K) steps of K/2 ziplo/ziphi (_b128): K log2(K) rearrangements, the cost of the usual transpositions
// on SSE, NEON, AVX-512 and SVE. On AVX (LMUL 1), `ziplo` crosses the two blocks of 128 bits: `transpose` transposes
// the 128-bit blocks of each half of the rows with `transpose_b128`, then exchanges the halves of the registers
// (lo/hi/combine), as the transposition of MIPPv1.

#include <cstddef>

#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/cpp/fun/ziplo.hpp"
#include "mipp/cpp/fun/ziphi.hpp"
#include "mipp/cpp/fun/ziplo_b128.hpp"
#include "mipp/cpp/fun/ziphi_b128.hpp"
#include "mipp/cpp/fun/lo.hpp"
#include "mipp/cpp/fun/hi.hpp"
#include "mipp/cpp/fun/combine.hpp"

namespace mipp
{
namespace details
{
// One step: the pairs (t[i], t[i + K/2]) give (t'[2i], t'[2i + 1]) = (ziplo, ziphi). After log2(K) steps, the K x K
// matrix of the rows t[0..K-1] is transposed (the zip of the rows i and i + K/2 is a perfect shuffle of the
// indices). B128 = true: the same in each block of 128 bits.
template <bool B128> struct zip_step;
template <> struct zip_step<false>
{
	template <typename R> static R lo(const R& a, const R& b) { return mipp::ziplo(a, b); }
	template <typename R> static R hi(const R& a, const R& b) { return mipp::ziphi(a, b); }
};
template <> struct zip_step<true>
{
	template <typename R> static R lo(const R& a, const R& b) { return mipp::ziplo_b128(a, b); }
	template <typename R> static R hi(const R& a, const R& b) { return mipp::ziphi_b128(a, b); }
};

template <bool B128, std::size_t K, typename R>
inline void transpose_zip(R* t)
{
	static_assert(K >= 1 && (K & (K - 1)) == 0, "mipp::transpose: the number of registers is a power of 2");
	for (std::size_t s = 1; s < K; s *= 2)
	{
		R o[K];
		for (std::size_t i = 0; 2 * i + 1 < K; i++) // not i < K / 2: i < 0 for K = 1 (GCC -Wtype-limits)
		{
			o[2 * i]     = zip_step<B128>::lo(t[i], t[i + K / 2]);
			o[2 * i + 1] = zip_step<B128>::hi(t[i], t[i + K / 2]);
		}
		for (std::size_t i = 0; i < K; i++)
			t[i] = o[i];
	}
}

// AVX, LMUL 1 (2 blocks of 128 bits): the 128-bit blocks of the rows 0..K-1 and K..2K-1 are transposed
// (transpose_b128), the register i then holds in its block b the column bK + i of the rows of its half; the halves
// are exchanged: t[i] = [lo(t[i]) | lo(t[K + i])], t[K + i] = [hi(t[i]) | hi(t[K + i])].
template <bool HALVES> struct transpose_impl
{
	template <std::size_t N, typename R> static void apply(R* t) { transpose_zip<false, N>(t); }
};
template <> struct transpose_impl<true>
{
	template <std::size_t N, typename R> static void apply(R* t)
	{
		constexpr std::size_t K = N / 2;
		transpose_zip<true, K>(t);
		transpose_zip<true, K>(t + K);
		for (std::size_t i = 0; i < K; i++)
		{
			const R a = t[i], b = t[K + i];
			t[i]     = mipp::combine(mipp::lo(a), mipp::lo(b));
			t[K + i] = mipp::combine(mipp::hi(a), mipp::hi(b));
		}
	}
};
} // namespace details

// The N<T, LMUL>() rows of a square matrix become the rows of its transpose. T (and LMUL) are given, as for
// mipp::dump: the datatype of a register of the Functional API cannot be deduced.
template <typename T, int LMUL = 1>
inline void transpose(vd<T, LMUL> (&t)[(N<T, LMUL>())])
{
	details::transpose_impl<(DEFAULT_ISA == ISA::AVX && LMUL == 1)>::template apply<N<T, LMUL>()>(t);
}

// The K x K matrices of each block of 128 bits of the K = 16 / sizeof(T) registers are transposed.
template <typename T, int LMUL = 1>
inline void transpose_b128(vd<T, LMUL> (&t)[(16 / sizeof(T))])
{
	static_assert(N<T, LMUL>() * sizeof(T) >= 16, "mipp::transpose_b128: the registers have at least 128 bits");
	details::transpose_zip<true, 16 / sizeof(T)>(t);
}
} // namespace mipp
