#pragma once

#include <cstring>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include "mipp/internal/interfaces/cpp/common.hpp"

// Fine-grained obj layer: this header deliberately includes NO cpp function header.
// Rvd/Rvm only need the register/mask types (cpp/common.hpp). The few operations their members rely on
// (loadu, set1, get, set1_k, set_k, get_k) go through the `details::*_op<T, LMUL>` traits below. They are only
// declared here and are specialised, per LMUL, by the matching obj atom:
//
//   Rvd(const T*)          -> mipp/obj/fun/u/m<LMUL>/loadu.hpp
//   Rvd(T), Rvd = T        -> mipp/obj/fun/u/m<LMUL>/set1.hpp
//   Rvd::operator[]        -> mipp/obj/fun/u/m<LMUL>/get.hpp
//   Rvm(bool), Rvm = bool  -> mipp/obj/fun/u/m<LMUL>/set1_k.hpp
//   Rvm(const int32_t[])   -> mipp/obj/fun/u/m<LMUL>/set_k.hpp
//   Rvm::operator[]        -> mipp/obj/fun/u/m<LMUL>/get_k.hpp
//
// Member functions of class templates are instantiated on use only: a translation unit pays for (and must include)
// exactly the operations it uses. The traits are looked up when a member is instantiated, so there is no
// dependency on include order beyond "include the atom before using the member".

namespace mipp
{

namespace details
{
template <typename T>
inline bool mask_get_val(T val, std::true_type)
{
	typedef typename std::conditional<sizeof(T) == 8, uint64_t, uint32_t>::type uint_t;
	uint_t bits = 0;
	std::memcpy(&bits, &val, sizeof(bits));
	return bits != 0;
}

template <typename T>
inline bool mask_get_val(T val, std::false_type)
{
	return val != 0;
}

template <typename T, int LMUL> struct rvd_loadu_op
{ static_assert(sizeof(T) == 0, "Rvd(const T*): include <mipp/obj/fun/u/m<LMUL>/loadu.hpp> (obj loadu atom of this LMUL)"); };
template <typename T, int LMUL> struct rvd_set1_op
{ static_assert(sizeof(T) == 0, "Rvd(const T)/Rvd = T: include <mipp/obj/fun/u/m<LMUL>/set1.hpp> (obj set1 atom of this LMUL)"); };
template <typename T, int LMUL> struct rvd_get_op
{ static_assert(sizeof(T) == 0, "Rvd::operator[]: include <mipp/obj/fun/u/m<LMUL>/get.hpp> (obj get atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_set1_k_op
{ static_assert(sizeof(T) == 0, "Rvm(bool)/Rvm = bool: include <mipp/obj/fun/u/m<LMUL>/set1_k.hpp> (obj set1_k atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_set_k_op
{ static_assert(sizeof(T) == 0, "Rvm(const int32_t[]): include <mipp/obj/fun/u/m<LMUL>/set_k.hpp> (obj set_k atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_get_k_op
{ static_assert(sizeof(T) == 0, "Rvm::operator[]: include <mipp/obj/fun/u/m<LMUL>/get_k.hpp> (obj get_k atom of this LMUL)"); };
template <typename T, int LMUL> struct rvd_lo_op
{ static_assert(sizeof(T) == 0, "Rvd::lo(): include <mipp/obj/fun/u/m<LMUL>/lo.hpp> (obj lo atom of this LMUL)"); };
template <typename T, int LMUL> struct rvd_hi_op
{ static_assert(sizeof(T) == 0, "Rvd::hi(): include <mipp/obj/fun/u/m<LMUL>/hi.hpp> (obj hi atom of this LMUL)"); };
template <typename T, int LMUL> struct rvd_combine_op
{ static_assert(sizeof(T) == 0, "Rvd::combine(): include <mipp/obj/fun/u/m<LMUL>/combine.hpp> (obj combine atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_lo_op
{ static_assert(sizeof(T) == 0, "Rvm::lo(): include <mipp/obj/fun/u/m<LMUL>/lo_k.hpp> (obj lo_k atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_hi_op
{ static_assert(sizeof(T) == 0, "Rvm::hi(): include <mipp/obj/fun/u/m<LMUL>/hi_k.hpp> (obj hi_k atom of this LMUL)"); };
template <typename T, int LMUL> struct rvm_combine_op
{ static_assert(sizeof(T) == 0, "Rvm::combine(): include <mipp/obj/fun/u/m<LMUL>/combine_k.hpp> (obj combine_k atom of this LMUL)"); };

// lo / hi / combine: the LMUL of the result is the one below / above the LMUL of the argument(s)
// (m4 -> m2 -> m1 -> d2, d2 is -2). The functions are found by argument-dependent lookup when instantiated,
// so that they do not need to be declared yet (they only exist for the ISAs and LMULs that provide them).
constexpr int lmul_down(int lmul) { return lmul == 1 ? -2 : lmul / 2; }
constexpr int lmul_up(int lmul) { return lmul == -2 ? 1 : lmul * 2; }
template <typename R> inline auto lo_call(const R& r) -> decltype(lo(r)) { return lo(r); }
template <typename R> inline auto hi_call(const R& r) -> decltype(hi(r)) { return hi(r); }
template <typename R> inline auto combine_call(const R& r0, const R& r1) -> decltype(combine(r0, r1)) { return combine(r0, r1); }
} // namespace details

template <typename T, int LMUL = 1>
struct Rvd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvd<T, LMUL> r;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline rvd<T, LMUL> from_list(std::initializer_list<T> l)
	{
		if (l.size() == 1)
			return details::rvd_set1_op<T, LMUL>::apply(*l.begin());
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Rvd: the initializer list must have 1 or N() values");
		T buf[N()];
		size_t i = 0;
		for (const T v : l)
			buf[i++] = v;
		return details::rvd_loadu_op<T, LMUL>::apply(buf);
	}

	inline Rvd() = default;
	inline Rvd(rvd<T, LMUL> r0) : r(r0) {}
	inline Rvd(const T val) : r(details::rvd_set1_op<T, LMUL>::apply(val)) {}
	inline Rvd(const T *p0) : r(details::rvd_loadu_op<T, LMUL>::apply(p0)) {}
	// The lanes in order, {l0, l1, ...} (N() values), or a single value broadcast to every lane ({val}, as Rvd(val))
	inline Rvd(std::initializer_list<T> l) : r(from_list(l)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator rvd<T, LMUL>() const { return this->r; }
	inline Rvd& operator=(const rvd<T, LMUL>& r0) { this->r = r0; return *this; }
	inline Rvd& operator=(const T val) { this->r = details::rvd_set1_op<T, LMUL>::apply(val); return *this; }

	inline T operator[](const size_t index) const { return details::rvd_get_op<T, LMUL>::apply(this->r, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Rvd<T, details::lmul_down(LMUL)> lo() const { return details::rvd_lo_op<T, LMUL>::apply(this->r); }
	inline Rvd<T, details::lmul_down(LMUL)> hi() const { return details::rvd_hi_op<T, LMUL>::apply(this->r); }
	// Register of the LMUL above made of this register (low half) and `hi` (high half)
	inline Rvd<T, details::lmul_up(LMUL)> combine(const Rvd& hi) const { return details::rvd_combine_op<T, LMUL>::apply(this->r, hi.r); }
};

template <typename T, int LMUL = 1>
struct Rvm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvm<T, LMUL> m;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline rvm<T, LMUL> from_list(std::initializer_list<bool> l)
	{
		if (l.size() == 1)
			return details::rvm_set1_k_op<T, LMUL>::apply(*l.begin() ? 1 : 0);
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Rvm: the initializer list must have 1 or N() values");
		int32_t vals[N()];
		size_t i = 0;
		for (const bool b : l)
			vals[i++] = b ? -1 : 0;
		return details::rvm_set_k_op<T, LMUL>::apply(vals);
	}

	inline Rvm() = default;
	inline Rvm(rvm<T, LMUL> m0) : m(m0) {}
	inline Rvm(const bool val) : m(details::rvm_set1_k_op<T, LMUL>::apply(val ? 1 : 0)) {}
	inline Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(details::rvm_set_k_op<T, LMUL>::apply(vals)) {}
	// The lanes in order, {b0, b1, ...} (N() values), or a single value broadcast to every lane ({b}, as Rvm(b))
	inline Rvm(std::initializer_list<bool> l) : m(from_list(l)) {}
	// A bool array would decay to bool* then silently convert to `true` through Rvm(bool): forbid it
	Rvm(const bool*) = delete;

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator rvm<T, LMUL>() const { return this->m; }
	inline Rvm& operator=(const rvm<T, LMUL>& m0) { this->m = m0; return *this; }
	inline Rvm& operator=(const bool val) { this->m = details::rvm_set1_k_op<T, LMUL>::apply(val ? 1 : 0); return *this; }
	Rvm& operator=(const bool*) = delete;

	inline bool operator[](const size_t index) const { return details::rvm_get_k_op<T, LMUL>::apply(this->m, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Rvm<T, details::lmul_down(LMUL)> lo() const { return details::rvm_lo_op<T, LMUL>::apply(this->m); }
	inline Rvm<T, details::lmul_down(LMUL)> hi() const { return details::rvm_hi_op<T, LMUL>::apply(this->m); }
	// Mask of the LMUL above made of this mask (low half) and `hi` (high half)
	inline Rvm<T, details::lmul_up(LMUL)> combine(const Rvm& hi) const { return details::rvm_combine_op<T, LMUL>::apply(this->m, hi.m); }
};

} // namespace mipp
