#pragma once
// MIPP compile-time permutations of the C++ Object API (C++17): `permute<P>(r)` and `permute2<P>(a, b)` on the Rvd
// registers, see mipp/cpp/patterns.hpp. Included by mipp_obj.hpp, not by mipp/obj/utils.hpp.
// Generated from generator/helpers_headers/templates/mipp_obj_patterns.tpl.hpp (utils_generator.py).

#if __cplusplus >= 201703L

#include "mipp/cpp/patterns.hpp"
#include "mipp/internal/interfaces/obj/common.hpp"

namespace mipp
{
template <typename P, typename T, int LMUL>
inline Rvd<T, LMUL> permute(const Rvd<T, LMUL>& r) { return Rvd<T, LMUL>(mipp::permute<P>(r.r)); }

template <typename P, typename T, int LMUL>
inline Rvd<T, LMUL> permute2(const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)
{ return Rvd<T, LMUL>(mipp::permute2<P>(r0.r, r1.r)); }
} // namespace mipp

#endif // __cplusplus >= 201703L
