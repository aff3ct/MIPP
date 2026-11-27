#pragma once
// MIPP transpositions of the C API: mipp_transpose_<type>[_<lmul>](t) and mipp_transpose_b128_<type>[_<lmul>](t),
// in place on an array of registers (see mipp/cpp/transpose.hpp for the C++ APIs).
// Generated from generator/helpers_headers/templates/mipp_transpose.tpl.h (utils_generator.py).
//
//     vd_float32_t t[MIPP_N_FLOAT32]; // the rows of a N x N matrix
//     mipp_transpose_float32(t);      // the rows of its transpose
//
// - mipp_transpose_<type>[_<lmul>](t): t is an array of MIPP_N_<TYPE>[_<LMUL>] registers, the rows of a square
//   matrix; they become the rows of its transpose (t[i] lane j receives the former t[j] lane i).
// - mipp_transpose_b128_<type>[_<lmul>](t): t is an array of K = 16 / sizeof(<type>) registers (4 float32, 8 int16,
//   16 int8...); the K x K matrix of each block of 128 bits is transposed independently. No `_d2` version when the
//   registers have 128 bits (SSE, NEON): a half register is smaller than a block.
//
// In C, an array parameter is a pointer: the number of registers is not checked. Both are log2(K) steps of K/2
// ziplo/ziphi (_b128); on AVX (LMUL 1), transpose_b128 of each half of the rows, then the halves of the registers
// exchanged (lo/hi/combine), as the C++ version.

#include <stddef.h>

#include "mipp/internal/interfaces/c/common.h"
#include "mipp/c/fun/ziplo.h"
#include "mipp/c/fun/ziphi.h"
#include "mipp/c/fun/ziplo_b128.h"
#include "mipp/c/fun/ziphi_b128.h"
#include "mipp/c/fun/lo.h"
#include "mipp/c/fun/hi.h"
#include "mipp/c/fun/combine.h"

/* log2(K) steps on the K registers of type VT from t: the pairs (t[i], t[i + K/2]) give (t'[2i], t'[2i + 1]) =
 * (ZLO, ZHI); the K x K matrix of the rows is then transposed. K is a constant of the compilation, 1 for the
 * half-registers of 64-bit elements on 128 bits: `2i + 1 < K` rather than `i < K / 2`, which would be
 * `i < 0` (GCC -Wtype-limits, an error with -Werror). */
#define MIPP_TRANSPOSE_ZIP_(VT, K, ZLO, ZHI, t)                                                  \
	do {                                                                                         \
		size_t mipp_s_, mipp_i_;                                                                 \
		for (mipp_s_ = 1; mipp_s_ < (size_t)(K); mipp_s_ *= 2) {                                 \
			VT mipp_o_[K];                                                                       \
			for (mipp_i_ = 0; 2 * mipp_i_ + 1 < (size_t)(K); mipp_i_++) {                        \
				mipp_o_[2 * mipp_i_] = ZLO((t)[mipp_i_], (t)[mipp_i_ + (size_t)(K) / 2]);        \
				mipp_o_[2 * mipp_i_ + 1] = ZHI((t)[mipp_i_], (t)[mipp_i_ + (size_t)(K) / 2]);    \
			}                                                                                    \
			for (mipp_i_ = 0; mipp_i_ < (size_t)(K); mipp_i_++)                                  \
				(t)[mipp_i_] = mipp_o_[mipp_i_];                                                 \
		}                                                                                        \
	} while (0)
{% for l in lmuls %}{% if l.guard %}
#if {{ l.guard }}{% endif %}
{% for d in datatypes %}
static inline void mipp_transpose_{{ d.name }}{{ l.sfx }}(vd_{{ d.name }}{{ l.sfx }}_t t[MIPP_N_{{ d.name | upper }}{{ l.n }}])
{
{%- if l.sfx == "" %}
#if defined(MIPP_AVX)
	/* the 128-bit blocks of each half of the rows, then the halves of the registers exchanged */
	size_t i;
	MIPP_TRANSPOSE_ZIP_(vd_{{ d.name }}_t, MIPP_N_{{ d.name | upper }} / 2, mipp_ziplo_b128_{{ d.name }}, mipp_ziphi_b128_{{ d.name }}, t);
	MIPP_TRANSPOSE_ZIP_(vd_{{ d.name }}_t, MIPP_N_{{ d.name | upper }} / 2, mipp_ziplo_b128_{{ d.name }}, mipp_ziphi_b128_{{ d.name }}, t + MIPP_N_{{ d.name | upper }} / 2);
	for (i = 0; i < MIPP_N_{{ d.name | upper }} / 2; i++) {
		const vd_{{ d.name }}_t a = t[i], b = t[MIPP_N_{{ d.name | upper }} / 2 + i];
		t[i] = mipp_combine_{{ d.name }}_d2(mipp_lo_{{ d.name }}(a), mipp_lo_{{ d.name }}(b));
		t[MIPP_N_{{ d.name | upper }} / 2 + i] = mipp_combine_{{ d.name }}_d2(mipp_hi_{{ d.name }}(a), mipp_hi_{{ d.name }}(b));
	}
#else
	MIPP_TRANSPOSE_ZIP_(vd_{{ d.name }}_t, MIPP_N_{{ d.name | upper }}, mipp_ziplo_{{ d.name }}, mipp_ziphi_{{ d.name }}, t);
#endif
{%- else %}
	MIPP_TRANSPOSE_ZIP_(vd_{{ d.name }}{{ l.sfx }}_t, MIPP_N_{{ d.name | upper }}{{ l.n }}, mipp_ziplo_{{ d.name }}{{ l.sfx }}, mipp_ziphi_{{ d.name }}{{ l.sfx }}, t);
{%- endif %}
}
{% if l.sfx == "_d2" %}#if MIPP_RVD_SIZE_BYTE >= 32
{% endif -%}
static inline void mipp_transpose_b128_{{ d.name }}{{ l.sfx }}(vd_{{ d.name }}{{ l.sfx }}_t t[16 / sizeof({{ d.cstd }})])
{
	MIPP_TRANSPOSE_ZIP_(vd_{{ d.name }}{{ l.sfx }}_t, 16 / sizeof({{ d.cstd }}), mipp_ziplo_b128_{{ d.name }}{{ l.sfx }}, mipp_ziphi_b128_{{ d.name }}{{ l.sfx }}, t);
}
{% if l.sfx == "_d2" %}#endif // MIPP_RVD_SIZE_BYTE >= 32
{% endif -%}
{% endfor %}{% if l.guard %}#endif // {{ l.guard }}
{% endif %}{% endfor %}
