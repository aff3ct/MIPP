{% raw %}#pragma once
// MIPP compile-time permutations of the C++ Functional API (C++17): `permute<P>(r)` and `permute2<P>(a, b)`.
// Generated from generator/helpers_headers/templates/mipp_patterns.tpl.hpp (utils_generator.py).
//
// A pattern P is a type with a static constexpr function `int get(int i, int n)`: the index, in the source lanes,
// of the lane i of the result, n being the number of lanes of the group (N<T, LMUL>()); the index -1 gives a
// zero. The number of lanes is a constant of the compilation on every ISA (SVE and RVV with a fixed register
// size), so the indices are known at compile time: the pattern is recognized among the named rearrangements
// (reverse, rotate, bcast, slideup, slidedown, swap2, dupeven, dupodd for one register;
// slide, ziplo, ziphi, unziplo, unziphi for two registers), and otherwise computed by permute / permute2
// with a constant table of indices (then a select for the zeros).
//
//     struct reversed { static constexpr int get(int i, int n) { return n - 1 - i; } };
//     mipp::vd<float> r = mipp::permute<reversed>(a); // mipp::reverse(a)
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
#if __has_include("mipp/cpp/fun/u/bcast.hpp")
#include "mipp/cpp/fun/u/bcast.hpp"
#else
#include "mipp/cpp/fun/bcast.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slide.hpp")
#include "mipp/cpp/fun/u/slide.hpp"
#else
#include "mipp/cpp/fun/slide.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slideup.hpp")
#include "mipp/cpp/fun/u/slideup.hpp"
#else
#include "mipp/cpp/fun/slideup.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/slidedown.hpp")
#include "mipp/cpp/fun/u/slidedown.hpp"
#else
#include "mipp/cpp/fun/slidedown.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/swap2.hpp")
#include "mipp/cpp/fun/u/swap2.hpp"
#else
#include "mipp/cpp/fun/swap2.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/dupeven.hpp")
#include "mipp/cpp/fun/u/dupeven.hpp"
#else
#include "mipp/cpp/fun/dupeven.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/dupodd.hpp")
#include "mipp/cpp/fun/u/dupodd.hpp"
#else
#include "mipp/cpp/fun/dupodd.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/ziplo.hpp")
#include "mipp/cpp/fun/u/ziplo.hpp"
#else
#include "mipp/cpp/fun/ziplo.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/ziphi.hpp")
#include "mipp/cpp/fun/u/ziphi.hpp"
#else
#include "mipp/cpp/fun/ziphi.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/unziplo.hpp")
#include "mipp/cpp/fun/u/unziplo.hpp"
#else
#include "mipp/cpp/fun/unziplo.hpp"
#endif
#if __has_include("mipp/cpp/fun/u/unziphi.hpp")
#include "mipp/cpp/fun/u/unziphi.hpp"
#else
#include "mipp/cpp/fun/unziphi.hpp"
#endif

namespace mipp
{
namespace details
{
// element type and LMUL of a register type R (vd<T, LMUL> is an alias of a C type, not deducible): lmul = 0 when R
// is not a register of LMUL 1, 2, 4, 8 or -2 (half-vector)
template <typename T, int L, typename = void> struct vd_or_void { using type = void; }; // no such register
template <typename T, int L> struct vd_or_void<T, L, std::void_t<typename vd_type<T, L>::type>>
{ using type = typename vd_type<T, L>::type; };
template <typename R, int L, typename... Ts> struct vd_find { using type = void; };
template <typename R, int L, typename T, typename... Ts> struct vd_find<R, L, T, Ts...>
{
	using type = typename std::conditional<std::is_same<R, typename vd_or_void<T, L>::type>::value, T,
	                                       typename vd_find<R, L, Ts...>::type>::type;
};
template <typename R, int L> using vd_find_t = typename vd_find<R, L, float32_t, float64_t, int8_t, int16_t, int32_t,
                                                                  int64_t, uint8_t, uint16_t, uint32_t, uint64_t>::type;
template <typename R> struct vd_info
{
	static constexpr int lmul = !std::is_void<vd_find_t<R, 1>>::value ? 1 : !std::is_void<vd_find_t<R, 2>>::value ? 2 :
	                            !std::is_void<vd_find_t<R, 4>>::value ? 4 : !std::is_void<vd_find_t<R, 8>>::value ? 8 :
	                            !std::is_void<vd_find_t<R, -2>>::value ? -2 : 0;
	using type = vd_find_t<R, lmul == 0 ? 1 : lmul>;
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
template <std::size_t N_> constexpr int slidedown_of(const std::array<int, N_>& a) // 1 <= k < n: k = a[0]
{
	const int k = a[0];
	return k >= 1 && is(a, [k](int i) { return i + k < static_cast<int>(N_) ? i + k : -1; }) ? k : -1;
}
template <std::size_t N_> constexpr int slideup_of(const std::array<int, N_>& a) // k = number of leading zeros
{
	int k = 0;
	while (k < static_cast<int>(N_) && a[k] == -1) k++;
	return k >= 1 && k < static_cast<int>(N_) && is(a, [k](int i) { return i >= k ? i - k : -1; }) ? k : -1;
}
template <std::size_t N_> constexpr bool is_swap2(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i ^ 1; }); }
template <std::size_t N_> constexpr bool is_dupeven(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i & ~1; }); }
template <std::size_t N_> constexpr bool is_dupodd(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return i | 1; }); }

// the named rearrangements of two registers (indices in [0, 2n))
template <std::size_t N_> constexpr int slide_of(const std::array<int, N_>& a) // 0 <= k <= n
{
	const int k = a[0];
	return k >= 0 && is(a, [k](int i) { return i + k; }) ? k : -1;
}
template <std::size_t N_> constexpr bool is_ziplo(const std::array<int, N_>& a)
{ return N_ % 2 == 0 && is(a, [](int i) { return (i & 1) ? static_cast<int>(N_) + i / 2 : i / 2; }); }
template <std::size_t N_> constexpr bool is_ziphi(const std::array<int, N_>& a)
{
	return N_ % 2 == 0 && is(a, [](int i) {
		return (i & 1) ? 3 * static_cast<int>(N_) / 2 + i / 2 : static_cast<int>(N_) / 2 + i / 2; });
}
template <std::size_t N_> constexpr bool is_unziplo(const std::array<int, N_>& a)
{ return is(a, [](int i) { return 2 * i; }); }
template <std::size_t N_> constexpr bool is_unziphi(const std::array<int, N_>& a)
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
inline vd<T, LMUL> permute_memory(const T* src, const std::array<int, N_>& a)
{
	T out[N_];
	for (std::size_t i = 0; i < N_; i++) out[i] = a[i] < 0 ? T(0) : src[a[i]];
	return mipp::loadu<T, LMUL>(out);
}

} // namespace details

template <typename P, typename R, typename std::enable_if<details::vd_info<R>::lmul != 0, int>::type = 0>
inline R permute(const R& r)
{
	using T = typename details::vd_info<R>::type;
	constexpr int LMUL = details::vd_info<R>::lmul;
	constexpr int n = static_cast<int>(N<T, LMUL>());
	constexpr std::array<int, n> a = details::pattern_checked<P, n, n>();
	using U = typename details::uint_of<T>::type;
	if constexpr (details::all_zero(a))             return mipp::set0<T, LMUL>();
	else if constexpr (details::is_identity(a))     return r;
	else if constexpr (details::is_reverse(a))      return mipp::reverse(r);
	else if constexpr (details::rotate_of(a) > 0)   return mipp::rotate(r, details::rotate_of(a));
	else if constexpr (details::broadcast_of(a) >= 0) return mipp::bcast(r, details::broadcast_of(a));
	else if constexpr (details::slidedown_of(a) > 0) return mipp::slidedown(r, details::slidedown_of(a));
	else if constexpr (details::slideup_of(a) > 0) return mipp::slideup(r, details::slideup_of(a));
	else if constexpr (details::is_swap2(a))   return mipp::swap2(r);
	else if constexpr (details::is_dupeven(a))     return mipp::dupeven(r);
	else if constexpr (details::is_dupodd(a))      return mipp::dupodd(r);
	else if constexpr (static_cast<std::uint64_t>(n) - 1 > static_cast<std::uint64_t>(static_cast<U>(~U(0))))
	{
		T buf[n];
		mipp::storeu(buf, r);
		return details::permute_memory<T, LMUL>(buf, a);
	}
	else
	{
		static constexpr std::array<U, n> t = details::pattern_table<U>(a, 0);
		const vd<T, LMUL> p = mipp::permute(r, mipp::loadu<U, LMUL>(t.data()));
		if constexpr (!details::has_zero(a))
			return p;
		else
		{
			static constexpr std::array<int32_t, n> m = details::pattern_mask(a);
			return mipp::select(mipp::set_k<T, LMUL>(m.data()), p, mipp::set0<T, LMUL>());
		}
	}
}

template <typename P, typename R, typename std::enable_if<details::vd_info<R>::lmul != 0, int>::type = 0>
inline R permute2(const R& r0, const R& r1)
{
	using T = typename details::vd_info<R>::type;
	constexpr int LMUL = details::vd_info<R>::lmul;
	constexpr int n = static_cast<int>(N<T, LMUL>());
	constexpr std::array<int, n> a = details::pattern_checked<P, n, 2 * n>();
	using U = typename details::uint_of<T>::type;
	if constexpr (details::all_in(a, 0, n))          return mipp::permute<details::pattern_lo<P>>(r0);
	else if constexpr (details::all_in(a, n, 2 * n)) return mipp::permute<details::pattern_hi<P>>(r1);
	else if constexpr (details::slide_of(a) >= 0)    return mipp::slide(r0, r1, details::slide_of(a));
	else if constexpr (details::is_ziplo(a))        return mipp::ziplo(r0, r1);
	else if constexpr (details::is_ziphi(a))        return mipp::ziphi(r0, r1);
	else if constexpr (details::is_unziplo(a))    return mipp::unziplo(r0, r1);
	else if constexpr (details::is_unziphi(a))     return mipp::unziphi(r0, r1);
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
		const vd<T, LMUL> p = mipp::permute2(r0, r1, mipp::loadu<U, LMUL>(t.data()));
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