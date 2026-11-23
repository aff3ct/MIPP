#pragma once

#include <cstring>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/loadu.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/lo.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/lo_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/hi.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/hi_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/combine.hpp"
#include "mipp/internal/interfaces/cpp/functions/combine/combine_k.hpp"

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
struct Vd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	vd<T, LMUL> r;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline vd<T, LMUL> from_list(std::initializer_list<T> l)
	{
		if (l.size() == 1)
			return mipp::set1<T, LMUL>(*l.begin());
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Vd: the initializer list must have 1 or N() values");
		T buf[N()];
		size_t i = 0;
		for (const T v : l)
			buf[i++] = v;
		return mipp::loadu<T, LMUL>(buf);
	}

	inline Vd() = default;
	inline Vd(vd<T, LMUL> r0) : r(r0) {}
	inline Vd(const T val) : r(mipp::set1<T, LMUL>(val)) {}
	inline Vd(const T *p0) : r(mipp::loadu<T, LMUL>(p0)) {}
	// The lanes in order, {l0, l1, ...} (N() values), or a single value broadcast to every lane ({val}, as Vd(val))
	inline Vd(std::initializer_list<T> l) : r(from_list(l)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator vd<T, LMUL>() const { return this->r; }
	inline Vd& operator=(const vd<T, LMUL>& r0) { this->r = r0; return *this; }
	inline Vd& operator=(const T val) { this->r = mipp::set1<T, LMUL>(val); return *this; }

	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Vd<T, details::lmul_down(LMUL)> lo() const { return Vd<T, details::lmul_down(LMUL)>(details::lo_call(this->r)); }
	inline Vd<T, details::lmul_down(LMUL)> hi() const { return Vd<T, details::lmul_down(LMUL)>(details::hi_call(this->r)); }
	// Register of the LMUL above made of this register (low half) and `hi` (high half)
	inline Vd<T, details::lmul_up(LMUL)> combine(const Vd& hi) const { return Vd<T, details::lmul_up(LMUL)>(details::combine_call(this->r, hi.r)); }
};

template <typename T, int LMUL = 1>
struct Vm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	vm<T, LMUL> m;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	static inline vm<T, LMUL> from_list(std::initializer_list<bool> l)
	{
		if (l.size() == 1)
			return mipp::set1_k<T, LMUL>(*l.begin() ? 1 : 0);
		if (l.size() != (size_t)N())
			throw std::invalid_argument("mipp::Vm: the initializer list must have 1 or N() values");
		int32_t vals[N()];
		size_t i = 0;
		for (const bool b : l)
			vals[i++] = b ? -1 : 0;
		return mipp::set_k<T, LMUL>(vals);
	}

	inline Vm() = default;
	inline Vm(vm<T, LMUL> m0) : m(m0) {}
	inline Vm(const bool val) : m(mipp::set1_k<T, LMUL>(val ? 1 : 0)) {}
	inline Vm(const int32_t vals[mipp::N<T, LMUL>()]) : m(mipp::set_k<T, LMUL>(vals)) {}
	// The lanes in order, {b0, b1, ...} (N() values), or a single value broadcast to every lane ({b}, as Vm(b))
	inline Vm(std::initializer_list<bool> l) : m(from_list(l)) {}
	// A bool array would decay to bool* then silently convert to `true` through Vm(bool): forbid it
	Vm(const bool*) = delete;

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator vm<T, LMUL>() const { return this->m; }
	inline Vm& operator=(const vm<T, LMUL>& m0) { this->m = m0; return *this; }
	inline Vm& operator=(const bool val) { this->m = mipp::set1_k<T, LMUL>(val ? 1 : 0); return *this; }
	Vm& operator=(const bool*) = delete;

	inline bool operator[](const size_t index) const {
		return details::mask_get_val<T>(mipp::get(this->m, index), typename std::is_floating_point<T>::type());
	}

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Vm<T, details::lmul_down(LMUL)> lo() const { return Vm<T, details::lmul_down(LMUL)>(details::lo_call(this->m)); }
	inline Vm<T, details::lmul_down(LMUL)> hi() const { return Vm<T, details::lmul_down(LMUL)>(details::hi_call(this->m)); }
	// Mask of the LMUL above made of this mask (low half) and `hi` (high half)
	inline Vm<T, details::lmul_up(LMUL)> combine(const Vm& hi) const { return Vm<T, details::lmul_up(LMUL)>(details::combine_call(this->m, hi.m)); }
};

} // namespace mipp
