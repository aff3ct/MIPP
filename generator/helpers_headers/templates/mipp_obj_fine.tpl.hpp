#pragma once

#include <cstring>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include "mipp/internal/interfaces/cpp/common.hpp"

// Fine-grained obj layer: this header deliberately includes NO cpp function header.
// Vd/Vm only need the register/mask types (cpp/common.hpp). The few operations their members rely on
// (loadu, set1, get, set1_k, set_k, get_k) go through the `details::*_op<T, LMUL>` traits below. They are only
// declared here and are specialised, per LMUL, by the matching obj atom:
//
//   Vd(const T*)          -> mipp/obj/fun/u/m<LMUL>/loadu.hpp
//   Vd(T), Vd = T        -> mipp/obj/fun/u/m<LMUL>/set1.hpp
//   Vd::operator[]        -> mipp/obj/fun/u/m<LMUL>/get.hpp
//   Vm(bool), Vm = bool  -> mipp/obj/fun/u/m<LMUL>/set1_k.hpp
//   Vm(const int32_t[])   -> mipp/obj/fun/u/m<LMUL>/set_k.hpp
//   Vm::operator[]        -> mipp/obj/fun/u/m<LMUL>/get_k.hpp
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

template <typename T, int LMUL> struct vd_loadu_op
{ static_assert(sizeof(T) == 0, "Vd(const T*): include <mipp/obj/fun/u/m<LMUL>/loadu.hpp> (obj loadu atom of this LMUL)"); };
template <typename T, int LMUL> struct vd_set1_op
{ static_assert(sizeof(T) == 0, "Vd(const T)/Vd = T: include <mipp/obj/fun/u/m<LMUL>/set1.hpp> (obj set1 atom of this LMUL)"); };
template <typename T, int LMUL> struct vd_get_op
{ static_assert(sizeof(T) == 0, "Vd::operator[]: include <mipp/obj/fun/u/m<LMUL>/get.hpp> (obj get atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_set1_k_op
{ static_assert(sizeof(T) == 0, "Vm(bool)/Vm = bool: include <mipp/obj/fun/u/m<LMUL>/set1_k.hpp> (obj set1_k atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_set_k_op
{ static_assert(sizeof(T) == 0, "Vm(const int32_t[]): include <mipp/obj/fun/u/m<LMUL>/set_k.hpp> (obj set_k atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_get_k_op
{ static_assert(sizeof(T) == 0, "Vm::operator[]: include <mipp/obj/fun/u/m<LMUL>/get_k.hpp> (obj get_k atom of this LMUL)"); };
template <typename T, int LMUL> struct vd_lo_op
{ static_assert(sizeof(T) == 0, "Vd::lo(): include <mipp/obj/fun/u/m<LMUL>/lo.hpp> (obj lo atom of this LMUL)"); };
template <typename T, int LMUL> struct vd_hi_op
{ static_assert(sizeof(T) == 0, "Vd::hi(): include <mipp/obj/fun/u/m<LMUL>/hi.hpp> (obj hi atom of this LMUL)"); };
template <typename T, int LMUL> struct vd_combine_op
{ static_assert(sizeof(T) == 0, "Vd::combine(): include <mipp/obj/fun/u/m<LMUL>/combine.hpp> (obj combine atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_lo_op
{ static_assert(sizeof(T) == 0, "Vm::lo(): include <mipp/obj/fun/u/m<LMUL>/lo_k.hpp> (obj lo_k atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_hi_op
{ static_assert(sizeof(T) == 0, "Vm::hi(): include <mipp/obj/fun/u/m<LMUL>/hi_k.hpp> (obj hi_k atom of this LMUL)"); };
template <typename T, int LMUL> struct vm_combine_op
{ static_assert(sizeof(T) == 0, "Vm::combine(): include <mipp/obj/fun/u/m<LMUL>/combine_k.hpp> (obj combine_k atom of this LMUL)"); };

// lo / hi / combine: the LMUL of the result is the one below / above the LMUL of the argument(s)
// (m4 -> m2 -> m1 -> d2, d2 is -2). The functions are found by argument-dependent lookup when instantiated,
// so that they do not need to be declared yet (they only exist for the ISAs and LMULs that provide them).
constexpr int lmul_down(int lmul) { return lmul == 1 ? -2 : lmul / 2; }
constexpr int lmul_up(int lmul) { return lmul == -2 ? 1 : lmul * 2; }
template <typename R> inline auto lo_call(const R& r) -> decltype(lo(r)) { return lo(r); }
template <typename R> inline auto hi_call(const R& r) -> decltype(hi(r)) { return hi(r); }
template <typename R> inline auto combine_call(const R& vd0, const R& vd1) -> decltype(combine(vd0, vd1)) { return combine(vd0, vd1); }
} // namespace details

template <typename T, int LMUL = 1>
struct Vd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	mipp::vd<T, LMUL> vd;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline mipp::vd<T, LMUL> from_list(std::initializer_list<T> l)
	{
		if (l.size() == 1)
			return details::vd_set1_op<T, LMUL>::apply(*l.begin());
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Vd: the initializer list must have 1 or N() values");
		T buf[N()];
		size_t i = 0;
		for (const T v : l)
			buf[i++] = v;
		return details::vd_loadu_op<T, LMUL>::apply(buf);
	}

	inline Vd() = default;
	inline Vd(mipp::vd<T, LMUL> vd0) : vd(vd0) {}
	inline Vd(const T val) : vd(details::vd_set1_op<T, LMUL>::apply(val)) {}
	inline Vd(const T *p0) : vd(details::vd_loadu_op<T, LMUL>::apply(p0)) {}
	// The lanes in order, {l0, l1, ...} (N() values), or a single value broadcast to every lane ({val}, as Vd(val))
	inline Vd(std::initializer_list<T> l) : vd(from_list(l)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator mipp::vd<T, LMUL>() const { return this->vd; }
	inline Vd& operator=(const mipp::vd<T, LMUL>& vd0) { this->vd = vd0; return *this; }
	inline Vd& operator=(const T val) { this->vd = details::vd_set1_op<T, LMUL>::apply(val); return *this; }

	inline T operator[](const size_t index) const { return details::vd_get_op<T, LMUL>::apply(this->vd, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Vd<T, details::lmul_down(LMUL)> lo() const { return details::vd_lo_op<T, LMUL>::apply(this->vd); }
	inline Vd<T, details::lmul_down(LMUL)> hi() const { return details::vd_hi_op<T, LMUL>::apply(this->vd); }
	// Register of the LMUL above made of this register (low half) and `hi` (high half)
	inline Vd<T, details::lmul_up(LMUL)> combine(const Vd& hi) const { return details::vd_combine_op<T, LMUL>::apply(this->vd, hi.vd); }
};

template <typename T, int LMUL = 1>
struct Vm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	mipp::vm<T, LMUL> vm;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline mipp::vm<T, LMUL> from_list(std::initializer_list<bool> l)
	{
		if (l.size() == 1)
			return details::vm_set1_k_op<T, LMUL>::apply(*l.begin() ? 1 : 0);
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Vm: the initializer list must have 1 or N() values");
		int32_t vals[N()];
		size_t i = 0;
		for (const bool b : l)
			vals[i++] = b ? -1 : 0;
		return details::vm_set_k_op<T, LMUL>::apply(vals);
	}

	inline Vm() = default;
	inline Vm(mipp::vm<T, LMUL> vm0) : vm(vm0) {}
	inline Vm(const bool val) : vm(details::vm_set1_k_op<T, LMUL>::apply(val ? 1 : 0)) {}
	inline Vm(const int32_t vals[mipp::N<T, LMUL>()]) : vm(details::vm_set_k_op<T, LMUL>::apply(vals)) {}
	// The lanes in order, {b0, b1, ...} (N() values), or a single value broadcast to every lane ({b}, as Vm(b))
	inline Vm(std::initializer_list<bool> l) : vm(from_list(l)) {}
	// A bool array would decay to bool* then silently convert to `true` through Vm(bool): forbid it
	Vm(const bool*) = delete;

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator mipp::vm<T, LMUL>() const { return this->vm; }
	inline Vm& operator=(const mipp::vm<T, LMUL>& vm0) { this->vm = vm0; return *this; }
	inline Vm& operator=(const bool val) { this->vm = details::vm_set1_k_op<T, LMUL>::apply(val ? 1 : 0); return *this; }
	Vm& operator=(const bool*) = delete;

	inline bool operator[](const size_t index) const { return details::vm_get_k_op<T, LMUL>::apply(this->vm, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Vm<T, details::lmul_down(LMUL)> lo() const { return details::vm_lo_op<T, LMUL>::apply(this->vm); }
	inline Vm<T, details::lmul_down(LMUL)> hi() const { return details::vm_hi_op<T, LMUL>::apply(this->vm); }
	// Mask of the LMUL above made of this mask (low half) and `hi` (high half)
	inline Vm<T, details::lmul_up(LMUL)> combine(const Vm& hi) const { return details::vm_combine_op<T, LMUL>::apply(this->vm, hi.vm); }
};

} // namespace mipp
