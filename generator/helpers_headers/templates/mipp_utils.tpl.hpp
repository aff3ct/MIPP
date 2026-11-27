#pragma once
// MIPP utilities of the C++ Functional API: aligned memory (malloc, allocator, vector), printing of the
// registers and `sum`.
// Generated from generator/helpers_headers/templates/mipp_utils.tpl.hpp (utils_generator.py).

#include <cstddef>
#include <cstdint>
#include <limits>
#include <new>
#include <ostream>
#include <iostream>
#include <vector>

#include "mipp/c/utils.h"
#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/cpp/fun/storeu.hpp"
#include "mipp/cpp/fun/tovd.hpp"
#include "mipp/cpp/fun/hadd.hpp"

namespace mipp
{
// ---------------------------------------------------------------------------------------------------------
// Aligned memory (MIPP_REQUIRED_ALIGNMENT: the size of a register)
// ---------------------------------------------------------------------------------------------------------

constexpr std::size_t required_alignment() { return MIPP_REQUIRED_ALIGNMENT; }

// `n` elements of type T, aligned for the aligned loads and stores; nullptr on failure. Release with mipp::free.
template <typename T>
inline T* malloc(const std::size_t n) { return static_cast<T*>(mipp_malloc(n * sizeof(T))); }

inline void free(void* p) { mipp_free(p); }

inline bool is_aligned(const void* p) { return mipp_is_aligned(p) != 0; }

// Standard allocator that aligns the storage on MIPP_REQUIRED_ALIGNMENT (e.g. for std::vector, see mipp::vector).
template <typename T>
struct allocator
{
	using value_type = T;
	template <typename U> struct rebind { using other = allocator<U>; };

	allocator() noexcept {}
	template <typename U> allocator(const allocator<U>&) noexcept {}

	T* allocate(const std::size_t n)
	{
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
			throw std::bad_alloc();
		T* p = mipp::malloc<T>(n);
		if (p == nullptr)
			throw std::bad_alloc();
		return p;
	}
	void deallocate(T* p, std::size_t) noexcept { mipp::free(p); }
};

template <typename T, typename U>
inline bool operator==(const allocator<T>&, const allocator<U>&) noexcept { return true; }
template <typename T, typename U>
inline bool operator!=(const allocator<T>&, const allocator<U>&) noexcept { return false; }

// std::vector whose data() is aligned for mipp::load / mipp::store.
template <typename T>
using vector = std::vector<T, allocator<T>>;

// ---------------------------------------------------------------------------------------------------------
// Printing: "[l0, l1, l2, l3 | l4, ...]", a '|' between the 128-bit blocks
// ---------------------------------------------------------------------------------------------------------

namespace details
{
template <typename T>
inline void print_lanes(std::ostream& os, const T* p, const std::size_t n, const bool is_mask)
{
	// the 8-bit integers are printed as numbers, not as characters
	using P = typename std::conditional<(sizeof(T) == 1), int, T>::type;
	const std::size_t per_block = 16 / sizeof(T);
	os << '[';
	for (std::size_t i = 0; i < n; i++)
	{
		if (i)
			os << ((i % per_block) ? ", " : " | ");
		if (is_mask)
			os << (p[i] != 0 ? 1 : 0);
		else
			os << static_cast<P>(p[i]);
	}
	os << ']';
}
} // namespace details

// The datatype and the LMUL of a register of the Functional API cannot be deduced: give them,
// e.g. mipp::dump<float, 2>(r). The Object API has operator<< (mipp/obj/utils.hpp).
template <typename T, int LMUL = 1>
inline std::ostream& dump(const vd<T, LMUL>& r, std::ostream& os = std::cout)
{
	T buf[N<T, LMUL>()];
	mipp::storeu(buf, r);
	details::print_lanes(os, buf, N<T, LMUL>(), false);
	return os << '\n';
}

template <typename T, int LMUL = 1>
inline std::ostream& dump_k(const vm<T, LMUL>& m, std::ostream& os = std::cout)
{
	T buf[N<T, LMUL>()];
	mipp::storeu(buf, mipp::tovd(m));
	details::print_lanes(os, buf, N<T, LMUL>(), true);
	return os << '\n';
}

// ---------------------------------------------------------------------------------------------------------
// sum: alias of hadd (MIPPv1)
// ---------------------------------------------------------------------------------------------------------

template <typename R>
inline auto sum(const R& r) -> decltype(hadd(r)) { return hadd(r); }

} // namespace mipp

