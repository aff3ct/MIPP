#pragma once

#include <cstring>
#include <type_traits>
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
	inline Rvd(const T val) : r(details::rvd_set1_op<T, LMUL>::apply(val)) {}
	inline Rvd(const T *p0) : r(details::rvd_loadu_op<T, LMUL>::apply(p0)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator rvd<T, LMUL>() const { return this->r; }
	inline Rvd& operator=(const rvd<T, LMUL>& r0) { this->r = r0; return *this; }
	inline Rvd& operator=(const T val) { this->r = details::rvd_set1_op<T, LMUL>::apply(val); return *this; }

	inline T operator[](const size_t index) const { return details::rvd_get_op<T, LMUL>::apply(this->r, index); }
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
	inline Rvm(const bool val) : m(details::rvm_set1_k_op<T, LMUL>::apply(val ? 1 : 0)) {}
	inline Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(details::rvm_set_k_op<T, LMUL>::apply(vals)) {}

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator rvm<T, LMUL>() const { return this->m; }
	inline Rvm& operator=(const rvm<T, LMUL>& m0) { this->m = m0; return *this; }
	inline Rvm& operator=(const bool val) { this->m = details::rvm_set1_k_op<T, LMUL>::apply(val ? 1 : 0); return *this; }

	inline bool operator[](const size_t index) const { return details::rvm_get_k_op<T, LMUL>::apply(this->m, index); }
};

} // namespace mipp
