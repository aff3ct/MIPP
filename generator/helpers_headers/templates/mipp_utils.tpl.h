#pragma once
// MIPP utilities of the C API: aligned memory allocation and printing of the registers.
// Generated from generator/helpers_headers/templates/mipp_utils.tpl.h (utils_generator.py).

#include "mipp/internal/interfaces/c/common.h"
#include "mipp/c/fun/storeu.h"
#include "mipp/c/fun/torvd.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Alignment required by the aligned loads and stores (mipp_load_*, mipp_store_*): the size of a register. */
#define MIPP_REQUIRED_ALIGNMENT (MIPP_RVD_SIZE_BYTE)

/* Allocates `bytes` bytes aligned on MIPP_REQUIRED_ALIGNMENT (the size is rounded up to a multiple of the
 * alignment). Returns NULL on failure. The memory is released with mipp_free. */
static inline void* mipp_malloc(size_t bytes)
{
	const size_t a = MIPP_REQUIRED_ALIGNMENT;
	const size_t sz = bytes ? (bytes + a - 1) / a * a : a;
#if defined(_MSC_VER)
	return _aligned_malloc(sz, a);
#elif defined(__cplusplus) && __cplusplus < 201703L
	/* aligned_alloc is C11 and C++17: posix_memalign for the older C++ */
	void* p = NULL;
	return posix_memalign(&p, a, sz) == 0 ? p : NULL;
#else
	return aligned_alloc(a, sz);
#endif
}

/* Releases the memory allocated by mipp_malloc. */
static inline void mipp_free(void* p)
{
#if defined(_MSC_VER)
	_aligned_free(p);
#else
	free(p);
#endif
}

/* 1 if `p` is aligned on MIPP_REQUIRED_ALIGNMENT (suitable for mipp_load_* / mipp_store_*), 0 otherwise. */
static inline int mipp_is_aligned(const void* p)
{
	return ((uintptr_t)p % (uintptr_t)MIPP_REQUIRED_ALIGNMENT) == 0;
}

/* Printing of the lanes of a register: "[l0, l1, l2, l3 | l4, ...]", a '|' between the 128-bit blocks.
 * mipp_fdump_<type>[_<lmul>](f, r) writes to `f`, mipp_dump_<type>[_<lmul>](r) to stdout; the `_k` versions
 * print the lanes of a mask (1: active, 0: inactive). */
{% for d in datatypes %}
static inline void mipp_fdump_lanes_{{ d.name }}_(FILE* f, const {{ d.cstd }}* p, size_t n, int is_mask)
{
	const size_t per_block = 16 / sizeof({{ d.cstd }});
	fputc('[', f);
	for (size_t i = 0; i < n; i++) {
		if (i)
			fputs((i % per_block) ? ", " : " | ", f);
		if (is_mask)
			fputs(p[i] != 0 ? "1" : "0", f);
		else
			fprintf(f, "{{ d.fmt }}", ({{ d.cast }})p[i]);
	}
	fputs("]\n", f);
}
{% endfor %}
{% for l in lmuls %}{% if l.guard %}
#if {{ l.guard }}{% endif %}
{% for d in datatypes %}
static inline void mipp_fdump_{{ d.name }}{{ l.sfx }}(FILE* f, const rvd_{{ d.name }}{{ l.sfx }}_t r)
{
	{{ d.cstd }} buf[MIPP_N_{{ d.name | upper }}{{ l.n }}];
	mipp_storeu_{{ d.name }}{{ l.sfx }}(buf, r);
	mipp_fdump_lanes_{{ d.name }}_(f, buf, MIPP_N_{{ d.name | upper }}{{ l.n }}, 0);
}
static inline void mipp_dump_{{ d.name }}{{ l.sfx }}(const rvd_{{ d.name }}{{ l.sfx }}_t r) { mipp_fdump_{{ d.name }}{{ l.sfx }}(stdout, r); }
static inline void mipp_fdump_k_{{ d.name }}{{ l.sfx }}(FILE* f, const rvm_{{ d.name }}{{ l.sfx }}_t m)
{
	{{ d.cstd }} buf[MIPP_N_{{ d.name | upper }}{{ l.n }}];
	mipp_storeu_{{ d.name }}{{ l.sfx }}(buf, mipp_torvd_{{ d.name }}{{ l.sfx }}(m));
	mipp_fdump_lanes_{{ d.name }}_(f, buf, MIPP_N_{{ d.name | upper }}{{ l.n }}, 1);
}
static inline void mipp_dump_k_{{ d.name }}{{ l.sfx }}(const rvm_{{ d.name }}{{ l.sfx }}_t m) { mipp_fdump_k_{{ d.name }}{{ l.sfx }}(stdout, m); }
{% endfor %}{% if l.guard %}#endif // {{ l.guard }}
{% endif %}{% endfor %}
