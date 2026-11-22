{% raw %}#pragma once
// MIPP compile-time permutations of the C++ Functional API (C++17): `permute<P>(r)` and `permute2<P>(a, b)`.
// Generated from generator/helpers_headers/templates/mipp_patterns.tpl.hpp (utils_generator.py).
//
// A pattern P is a type with a static constexpr function `int get(int i, int n)`: the index, in the source lanes,
// of the lane i of the result, n being the number of lanes of the group (N<T, LMUL>()); the index -1 gives a
// zero. The number of lanes is a constant of the compilation on every ISA (SVE and RVV with a fixed register
// size), so the indices are known at compile time: the pattern is recognized among the named rearrangements
// (reverse, rotate, broadcast_lane, slide_up, slide_down, swap_pairs, dup_even, dup_odd for one register;
// slide, zip_lo, zip_hi, unzip_even, unzip_odd for two registers), and otherwise computed by permute / permute2
// with a constant table of indices (then a select for the zeros).
//
//     struct reversed { static constexpr int get(int i, int n) { return n - 1 - i; } };
//     mipp::rvd<float> r = mipp::permute<reversed>(a); // mipp::reverse(a)
//
// The C++11 API keeps the functions with indices in a register (permute, permute2), which do not need C++17.
// Included by mipp.hpp (and mipp_obj.hpp), not by mipp/cpp/utils.hpp: it pulls about 20 rearrangement functions.

#if __cplusplus >= 201703L

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "mipp/internal/interfaces/cpp/common.hpp"
// only the unmasked versions (all the LMULs) when the headers are fine-grained (`--granularity fine`): the
// masked ones would double the parsing time; the whole functions otherwise
#if __has_include("mipp/cpp/fun/u/loadu.hpp")
#include "mipp/cpp/fun/u/loadu.hpp"
#else
#include "mipp/cpp/fun/loadu.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/storeu.hpp")
#include "mipp/cpp/fun/u/storeu.hpp"
#else
#include "mipp/cpp/fun/storeu.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/set0.hpp")
#include "mipp/cpp/fun/u/set0.hpp"
#else
#include "mipp/cpp/fun/set0.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/set_k.hpp")
#include "mipp/cpp/fun/u/set_k.hpp"
#else
#include "mipp/cpp/fun/set_k.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/select.hpp")
#include "mipp/cpp/fun/u/select.hpp"
#else
#include "mipp/cpp/fun/select.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/permute.hpp")
#include "mipp/cpp/fun/u/permute.hpp"
#else
#include "mipp/cpp/fun/permute.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/permute2.hpp")
#include "mipp/cpp/fun/u/permute2.hpp"
#else
#include "mipp/cpp/fun/permute2.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/reverse.hpp")
#include "mipp/cpp/fun/u/reverse.hpp"
#else
#include "mipp/cpp/fun/reverse.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/rotate.hpp")
#include "mipp/cpp/fun/u/rotate.hpp"
#else
#include "mipp/cpp/fun/rotate.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/broadcast_lane.hpp")
#include "mipp/cpp/fun/u/broadcast_lane.hpp"
#else
#include "mipp/cpp/fun/broadcast_lane.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slide.hpp")
#include "mipp/cpp/fun/u/slide.hpp"
#else
#include "mipp/cpp/fun/slide.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slide_up.hpp")
#include "mipp/cpp/fun/u/slide_up.hpp"
#else
#include "mipp/cpp/fun/slide_up.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slide_down.hpp")
#include "mipp/cpp/fun/u/slide_down.hpp"
#else
#include "mipp/cpp/fun/slide_down.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/swap_pairs.hpp")
#include "mipp/cpp/fun/u/swap_pairs.hpp"
#else
#include "mipp/cpp/fun/swap_pairs.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/dup_even.hpp")
#include "mipp/cpp/fun/u/dup_even.hpp"
#else
#include "mipp/cpp/fun/dup_even.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/dup_odd.hpp")
#include "mipp/cpp/fun/u/dup_odd.hpp"
#else
#include "mipp/cpp/fun/dup_odd.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/zip_lo.hpp")
#include "mipp/cpp/fun/u/zip_lo.hpp"
#else
#include "mipp/cpp/fun/zip_lo.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/zip_hi.hpp")
#include "mipp/cpp/fun/u/zip_hi.hpp"
#else
#include "mipp/cpp/fun/zip_hi.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/unzip_even.hpp")
#include "mipp/cpp/fun/u/unzip_even.hpp"
#else
#include "mipp/cpp/fun/unzip_even.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/unzip_odd.hpp")
#include "mipp/cpp/fun/u/unzip_odd.hpp"
#else
#include "mipp/cpp/fun/unzip_odd.hpp"
#endif

namespace mipp
{
namespace details
{
// element type and LMUL of a register type R (rvd<T, LMUL> is an alias of a C type, not deducible): lmul = 0 when R
// is not a register of LMUL 1, 2, 4, 8 or -2 (half-vector)
template <typename T, int L, typename = void> struct rvd_or_void { using type = void; }; // no such register
template <typename T, int L> struct rvd_or_void<T, L, std::void_t<typename rvd_type<T, L>::type>>
{ using type = typename rvd_type<T, L>::type; };
template <typename R, int L, typename... Ts> struct rvd_find { using type = void; };
template <typename R, int L, typename T, typename... Ts> struct rvd_find<R, L, T, Ts...>
{
	using type = typename std::conditional<std::is_same<R, typename rvd_or_void<T, L>::type>::value, T,
	                                       typename rvd_find<R, L, Ts...>::type>::type;
};
template <typename R, int L> using rvd_find_t = typename rvd_find<R, L, float32_t, float64_t, int8_t, int16_t, int32_t,
                                                                  int64_t, uint8_t, uint16_t, uint32_t, uint64_t>::type;
template <typename R> struct rvd_info
{
	static constexpr int lmul = !std::is_void<rvd_find_t<R, 1>>::value ? 1 : !std::is_void<rvd_find_t<R, 2>>::value ? 2 :
	                            !std::is_void<rvd_find_t<R, 4>>::value ? 4 : !std::is_void<rvd_find_t<R, 8>>::value ? 8 :
	                            !std::is_void<rvd_find_t<R, -2>>::value ? -2 : 0;
	using type = rvd_find_t<R, lmul == 0 ? 1 : lmul>;
};

// not constexpr: called by the constant evaluation of a pattern with an index out of [-1, n) ([-1, 2n) for permute2),
// it makes the compilation fail (a `throw` would not compile with -fno-exceptions)
inline void pattern_index_out_of_range() {}

// indices of the pattern P for n lanes: { P::get(0, n), ..., P::get(n - 1, n) }
template <typename P, int N_, std::size_t... I>
constexpr std::array<int, sizeof...(I)> pattern_indices(std::index_sequence<I...>)
{
	return std::array<int, sizeof...(I)>{ { P::get(static_cast<int>(I), N_)... } };
}

template <typename P, int N_, int TOP>
constexpr std::array<int, N_> pattern_checked()
{
	constexpr std::array<int, N_> a = pattern_indices<P, N_>(std::make_index_sequence<N_>());
	for (int i = 0; i < N_; i++)
		if (a[i] < -1 || a[i] >= TOP)
			pattern_index_out_of_range();
	return a;
}

// the lanes of the first (LO) or of the second (HI) register of a pattern of permute2, as a pattern of permute
template <typename P> struct pattern_lo { static constexpr int get(int i, int n) { return P::get(i, n); } };
template <typename P> struct pattern_hi
{ static constexpr int get(int i, int n) { return P::get(i, n) < 0 ? -1 : P::get(i, n) - n; } };

template <std::size_t N_> constexpr bool all_in(const std::array<int, N_>& a, int lo, int hi)
{
	for (std::size_t i = 0; i < N_; i++) if (a[i] != -1 && (a[i] < lo || a[i] >= hi)) return false;
	return true;
}
template <std::size_t N_> constexpr bool has_zero(const std::array<int, N_>& a)
{
	for (std::size_t i = 0; i < N_; i++) if (a[i] == -1) return true;
	return false;
}
template <std::size_t N_> constexpr bool all_zero(const std::array<int, N_>& a)
{
	for (std::size_t i = 0; i < N_; i++) if (a[i] != -1) return false;
	return true;
}
// a[i] == f(i) for every lane, f giving -1 for a zero
template <std::size_t N_, typename F> constexpr bool is(const std::array<int, N_>& a, F f)
{
	for (std::size_t i = 0; i < N_; i++) if (a[i] != f(static_cast<int>(i))) return false;
	return true;
}

// the named rearrangements of one register of n lanes; *k receives the number of lanes of rotate, slide...
template <std::size_t N_> constexpr bool is_identity(const std::array<int, N_>& a)
{ return is(a, [](int i) { return i; }); }
template <std::size_t N_> constexpr bool is_reverse(const std::array<int, N_>& a)
{ return is(a, [](int i) { return static_cast<int>(N_) - 1 - i; }); }
template <std::size_t N_> constexpr int rotate_of(const std::array<int, N_>& a) // -1: not a rotation
{
	const int k = a[0];
	return k >= 0 && is(a, [k](int i) { return (i + k) % static_cast<int>(N_); }) ? k : -1;
}
template <std::size_t N_> constexpr int broadcast_of(const std::array<int, N_>& a)
{
	const int k = a[0];
	return k >= 0 && is(a, [k](int) { return k; }) ? k : -1;
}
template <std::size_t N_> constexpr int slide_down_of(const std::array<int, N_>& a) // 1 <= k < n: k = a[0]
{
	const int k = a[0];
	return k >= 1 && is(a, [k](int i) { return i + k < static_cast<int>(N_) ? i + k : -1; }) ? k : -1;
}
template <std::size_t N_> constexpr int slide_up_of(const std::array<int, N_>& a) // k = number of leading zeros
{
	int k = 0;
	while (k < static_cast<int>(N_) && a[k] == -1) k++;
	return k >= 1 && k < static_cast<int>(N_) && is(a, [k](int i) { return i >= k ? i - k : -1; }) ? k : -1;
}
template <std::size_t N_> constexpr bool is_swap_pairs(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i ^ 1; }); }
template <std::size_t N_> constexpr bool is_dup_even(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i & ~1; }); }
template <std::size_t N_> constexpr bool is_dup_odd(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i | 1; }); }

// the named rearrangements of two registers (indices in [0, 2n))
template <std::size_t N_> constexpr int slide_of(const std::array<int, N_>& a) // 0 <= k <= n
{
	const int k = a[0];
	return k >= 0 && is(a, [k](int i) { return i + k; }) ? k : -1;
}
template <std::size_t N_> constexpr bool is_zip_lo(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return (i & 1) ? static_cast<int>(N_) + i / 2 : i / 2; }); }
template <std::size_t N_> constexpr bool is_zip_hi(const std::array<int, N_>& a)
{
	return N_ % 2 == 0 && is(a, [](int i) {
		return (i & 1) ? 3 * static_cast<int>(N_) / 2 + i / 2 : static_cast<int>(N_) / 2 + i / 2; });
}
template <std::size_t N_> constexpr bool is_unzip_even(const std::array<int, N_>& a)
{ return is(a, [](int i) { return 2 * i; }); }
template <std::size_t N_> constexpr bool is_unzip_odd(const std::array<int, N_>& a)
{ return is(a, [](int i) { return 2 * i + 1; }); }

// constant tables of the fallback: the indices (the zeros read the lane 0) and the mask of the non-zero lanes
template <typename U, std::size_t N_>
constexpr std::array<U, N_> pattern_table(const std::array<int, N_>& a, int offset)
{
	std::array<U, N_> t{};
	for (std::size_t i = 0; i < N_; i++) t[i] = static_cast<U>(a[i] < 0 ? 0 : a[i] - offset);
	return t;
}
template <std::size_t N_> constexpr std::array<int32_t, N_> pattern_mask(const std::array<int, N_>& a)
{
	std::array<int32_t, N_> m{};
	for (std::size_t i = 0; i < N_; i++) m[i] = a[i] < 0 ? 0 : -1;
	return m;
}

// the patterns whose indices do not fit in the index type (8-bit elements, more than 256 lanes): through memory
template <typename T, int LMUL, std::size_t N_>
inline rvd<T, LMUL> permute_memory(const T* src, const std::array<int, N_>& a)
{
	T out[N_];
	for (std::size_t i = 0; i < N_; i++) out[i] = a[i] < 0 ? T(0) : src[a[i]];
	return mipp::loadu<T, LMUL>(out);
}

} // namespace details

template <typename P, typename R, typename std::enable_if<details::rvd_info<R>::lmul != 0, int>::type = 0>
inline R permute(const R& r)
{
	using T = typename details::rvd_info<R>::type;
	constexpr int LMUL = details::rvd_info<R>::lmul;
	constexpr int n = static_cast<int>(N<T, LMUL>());
	constexpr std::array<int, n> a = details::pattern_checked<P, n, n>();
	using U = typename details::uint_of<T>::type;
	if constexpr (details::all_zero(a))             return mipp::set0<T, LMUL>();
	else if constexpr (details::is_identity(a))     return r;
	else if constexpr (details::is_reverse(a))      return mipp::reverse(r);
	else if constexpr (details::rotate_of(a) > 0)   return mipp::rotate(r, details::rotate_of(a));
	else if constexpr (details::broadcast_of(a) >= 0) return mipp::broadcast_lane(r, details::broadcast_of(a));
	else if constexpr (details::slide_down_of(a) > 0) return mipp::slide_down(r, details::slide_down_of(a));
	else if constexpr (details::slide_up_of(a) > 0) return mipp::slide_up(r, details::slide_up_of(a));
	else if constexpr (details::is_swap_pairs(a))   return mipp::swap_pairs(r);
	else if constexpr (details::is_dup_even(a))     return mipp::dup_even(r);
	else if constexpr (details::is_dup_odd(a))      return mipp::dup_odd(r);
	else if constexpr (static_cast<std::uint64_t>(n) - 1 > static_cast<std::uint64_t>(static_cast<U>(~U(0))))
	{
		T buf[n];
		mipp::storeu(buf, r);
		return details::permute_memory<T, LMUL>(buf, a);
	}
	else
	{
		static constexpr std::array<U, n> t = details::pattern_table<U>(a, 0);
		const rvd<T, LMUL> p = mipp::permute(r, mipp::loadu<U, LMUL>(t.data()));
		if constexpr (!details::has_zero(a))
			return p;
		else
		{
			static constexpr std::array<int32_t, n> m = details::pattern_mask(a);
			return mipp::select(mipp::set_k<T, LMUL>(m.data()), p, mipp::set0<T, LMUL>());
		}
	}
}

template <typename P, typename R, typename std::enable_if<details::rvd_info<R>::lmul != 0, int>::type = 0>
inline R permute2(const R& r0, const R& r1)
{
	using T = typename details::rvd_info<R>::type;
	constexpr int LMUL = details::rvd_info<R>::lmul;
	constexpr int n = static_cast<int>(N<T, LMUL>());
	constexpr std::array<int, n> a = details::pattern_checked<P, n, 2 * n>();
	using U = typename details::uint_of<T>::type;
	if constexpr (details::all_in(a, 0, n))          return mipp::permute<details::pattern_lo<P>>(r0);
	else if constexpr (details::all_in(a, n, 2 * n)) return mipp::permute<details::pattern_hi<P>>(r1);
	else if constexpr (details::slide_of(a) >= 0)    return mipp::slide(r0, r1, details::slide_of(a));
	else if constexpr (details::is_zip_lo(a))        return mipp::zip_lo(r0, r1);
	else if constexpr (details::is_zip_hi(a))        return mipp::zip_hi(r0, r1);
	else if constexpr (details::is_unzip_even(a))    return mipp::unzip_even(r0, r1);
	else if constexpr (details::is_unzip_odd(a))     return mipp::unzip_odd(r0, r1);
	else if constexpr (static_cast<std::uint64_t>(2 * n) - 1 > static_cast<std::uint64_t>(static_cast<U>(~U(0))))
	{
		T buf[2 * n];
		mipp::storeu(buf, r0);
		mipp::storeu(buf + n, r1);
		return details::permute_memory<T, LMUL>(buf, a);
	}
	else
	{
		static constexpr std::array<U, n> t = details::pattern_table<U>(a, 0);
		const rvd<T, LMUL> p = mipp::permute2(r0, r1, mipp::loadu<U, LMUL>(t.data()));
		if constexpr (!details::has_zero(a))
			return p;
		else
		{
			static constexpr std::array<int32_t, n> m = details::pattern_mask(a);
			return mipp::select(mipp::set_k<T, LMUL>(m.data()), p, mipp::set0<T, LMUL>());
		}
	}
}
} // namespace mipp

#endif // __cplusplus >= 201703L
{% endraw %}