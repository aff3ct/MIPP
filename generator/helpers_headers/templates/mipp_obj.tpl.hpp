#pragma once

#include <cstring>
#include <type_traits>
#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/loadu.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/low.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/low_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/high.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/high_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/combine.hpp"
#include "mipp/internal/interfaces/cpp/functions/lmul/combine_k.hpp"

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

// low / high / combine: the LMUL of the result is the one below / above the LMUL of the argument(s)
// (m4 -> m2 -> m1 -> d2, d2 is -2). The functions are found by argument-dependent lookup when instantiated,
// so that they do not need to be declared yet (they only exist for the ISAs and LMULs that provide them).
constexpr int lmul_down(int lmul) { return lmul == 1 ? -2 : lmul / 2; }
constexpr int lmul_up(int lmul) { return lmul == -2 ? 1 : lmul * 2; }
template <typename R> inline auto low_call(const R& r) -> decltype(low(r)) { return low(r); }
template <typename R> inline auto high_call(const R& r) -> decltype(high(r)) { return high(r); }
template <typename R> inline auto combine_call(const R& r0, const R& r1) -> decltype(combine(r0, r1)) { return combine(r0, r1); }
} // namespace details

template <typename T, int LMUL = 1>
struct Rvd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvd<T, LMUL> r;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	inline Rvd() = default;
	inline Rvd(rvd<T, LMUL> r0) : r(r0) {}
	inline Rvd(const T val) : r(mipp::set1<T, LMUL>(val)) {}
	inline Rvd(const T *p0) : r(mipp::loadu<T, LMUL>(p0)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator rvd<T, LMUL>() const { return this->r; }
	inline Rvd& operator=(const rvd<T, LMUL>& r0) { this->r = r0; return *this; }
	inline Rvd& operator=(const T val) { this->r = mipp::set1<T, LMUL>(val); return *this; }

	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Rvd<T, details::lmul_down(LMUL)> low() const { return Rvd<T, details::lmul_down(LMUL)>(details::low_call(this->r)); }
	inline Rvd<T, details::lmul_down(LMUL)> high() const { return Rvd<T, details::lmul_down(LMUL)>(details::high_call(this->r)); }
	// Register of the LMUL above made of this register (low half) and `hi` (high half)
	inline Rvd<T, details::lmul_up(LMUL)> combine(const Rvd& hi) const { return Rvd<T, details::lmul_up(LMUL)>(details::combine_call(this->r, hi.r)); }
};

template <typename T, int LMUL = 1>
struct Rvm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvm<T, LMUL> m;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	inline Rvm() = default;
	inline Rvm(rvm<T, LMUL> m0) : m(m0) {}
	inline Rvm(const bool val) : m(mipp::set1_k<T, LMUL>(val ? 1 : 0)) {}
	inline Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(mipp::set_k<T, LMUL>(vals)) {}
	// A bool array would decay to bool* then silently convert to `true` through Rvm(bool): forbid it
	Rvm(const bool*) = delete;

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator rvm<T, LMUL>() const { return this->m; }
	inline Rvm& operator=(const rvm<T, LMUL>& m0) { this->m = m0; return *this; }
	inline Rvm& operator=(const bool val) { this->m = mipp::set1_k<T, LMUL>(val ? 1 : 0); return *this; }
	Rvm& operator=(const bool*) = delete;

	inline bool operator[](const size_t index) const {
		return details::mask_get_val<T>(mipp::get(this->m, index), typename std::is_floating_point<T>::type());
	}

	// Lower / upper half (LMUL below): m2 -> m1, m1 -> d2, ... (not defined for d2)
	inline Rvm<T, details::lmul_down(LMUL)> low() const { return Rvm<T, details::lmul_down(LMUL)>(details::low_call(this->m)); }
	inline Rvm<T, details::lmul_down(LMUL)> high() const { return Rvm<T, details::lmul_down(LMUL)>(details::high_call(this->m)); }
	// Mask of the LMUL above made of this mask (low half) and `hi` (high half)
	inline Rvm<T, details::lmul_up(LMUL)> combine(const Rvm& hi) const { return Rvm<T, details::lmul_up(LMUL)>(details::combine_call(this->m, hi.m)); }
};

} // namespace mipp
