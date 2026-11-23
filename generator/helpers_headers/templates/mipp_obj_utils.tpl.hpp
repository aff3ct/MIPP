#pragma once
// MIPP utilities of the C++ Object API: printing (operator<<), saturating `pack`, and generic reductions of
// a register or of an array with any associative operation (MIPPv1 `Reduction<T, OP>`).
// Generated from generator/helpers_headers/templates/mipp_obj_utils.tpl.hpp (utils_generator.py).

#include <cstddef>
#include <ostream>
#include <type_traits>

#include "mipp/cpp/utils.hpp"
#include "mipp/internal/interfaces/obj/common.hpp"
#include "mipp/obj/fun/add.hpp"
#include "mipp/obj/fun/mul.hpp"
#include "mipp/obj/fun/min.hpp"
#include "mipp/obj/fun/max.hpp"
#include "mipp/obj/fun/andb.hpp"
#include "mipp/obj/fun/orb.hpp"
#include "mipp/obj/fun/xorb.hpp"

namespace mipp
{
// "[l0, l1, l2, l3 | l4, ...]", a '|' between the 128-bit blocks; masks: 1 (active) / 0 (inactive)
template <typename T, int LMUL>
inline std::ostream& operator<<(std::ostream& os, const Rvd<T, LMUL>& r)
{
	T buf[Rvd<T, LMUL>::N()];
	mipp::storeu(buf, r.r);
	details::print_lanes(os, buf, Rvd<T, LMUL>::N(), false);
	return os;
}

template <typename T, int LMUL>
inline std::ostream& operator<<(std::ostream& os, const Rvm<T, LMUL>& m)
{
	T buf[Rvd<T, LMUL>::N()];
	mipp::storeu(buf, mipp::torvd(m.m));
	details::print_lanes(os, buf, Rvd<T, LMUL>::N(), true);
	return os;
}

// Saturating narrowing of two registers into one (the lanes of `a`, then the lanes of `b`).
template <typename T_DST, typename T, int LMUL>
inline Rvd<T_DST, LMUL> pack(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)
{
	return Rvd<T_DST, LMUL>(mipp::pack<T_DST>(a.r, b.r));
}

// ---------------------------------------------------------------------------------------------------------
// Reductions with an associative operation: `op(Rvd, Rvd) -> Rvd`, callable for every LMUL (a functor with
// a template operator(), or a generic lambda in C++14). Predefined operations: mipp::op::add, mul, min,
// max, andb, orb, xorb.
// ---------------------------------------------------------------------------------------------------------

namespace op
{
struct add  { template <typename R> R operator()(const R& a, const R& b) const { return mipp::add(a, b); } };
struct mul  { template <typename R> R operator()(const R& a, const R& b) const { return mipp::mul(a, b); } };
struct min  { template <typename R> R operator()(const R& a, const R& b) const { return mipp::min(a, b); } };
struct max  { template <typename R> R operator()(const R& a, const R& b) const { return mipp::max(a, b); } };
struct andb { template <typename R> R operator()(const R& a, const R& b) const { return mipp::andb(a, b); } };
struct orb  { template <typename R> R operator()(const R& a, const R& b) const { return mipp::orb(a, b); } };
struct xorb { template <typename R> R operator()(const R& a, const R& b) const { return mipp::xorb(a, b); } };
} // namespace op

namespace details
{
// The register is halved (lo / hi) down to the smallest LMUL (d2 when available), then its lanes are
// folded one by one, each lane broadcast to a register (the operation only works on registers).
#if defined(MIPP_LDIV_2)
constexpr int reduce_last_lmul = -2;
#else
constexpr int reduce_last_lmul = 1;
#endif

template <typename T, int LMUL, typename OP>
inline T reduce_rvd(const Rvd<T, LMUL>& r, OP op, std::true_type /* smallest LMUL */)
{
	T buf[Rvd<T, LMUL>::N()];
	mipp::storeu(buf, r.r);
	T acc = buf[0];
	for (std::size_t i = 1; i < Rvd<T, LMUL>::N(); i++)
		acc = op(Rvd<T, LMUL>(acc), Rvd<T, LMUL>(buf[i]))[0];
	return acc;
}

template <typename T, int LMUL, typename OP>
inline T reduce_rvd(const Rvd<T, LMUL>& r, OP op, std::false_type)
{
	const Rvd<T, lmul_down(LMUL)> h = op(r.lo(), r.hi());
	return reduce_rvd(h, op, std::integral_constant<bool, lmul_down(LMUL) == reduce_last_lmul>());
}
} // namespace details

// op(r[0], op(r[1], ...)) in an unspecified order (the operation must be associative and commutative).
template <typename T, int LMUL, typename OP>
inline T reduce(const Rvd<T, LMUL>& r, OP op)
{
	return details::reduce_rvd(r, op, std::integral_constant<bool, LMUL == details::reduce_last_lmul>());
}

// Reduction of the `n` elements of `data` (n >= 1; `data` needs no alignment), with registers of LMUL `LMUL`.
template <typename T, int LMUL = 1, typename OP>
inline T reduce(const T* data, const std::size_t n, OP op)
{
	const std::size_t w = Rvd<T, LMUL>::N();
	std::size_t i = 0;
	T res = data[0];
	if (n >= w)
	{
		Rvd<T, LMUL> acc(data);
		for (i = w; i + w <= n; i += w)
			acc = op(acc, Rvd<T, LMUL>(data + i));
		res = mipp::reduce(acc, op);
	}
	else
		i = 1;
	for (; i < n; i++)
		res = op(Rvd<T, 1>(res), Rvd<T, 1>(data[i]))[0];
	return res;
}

} // namespace mipp
