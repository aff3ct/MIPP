#pragma once
// MIPP compile-time permutations of the C++ Object API (C++17): `permute<P>(r)` and `permute2<P>(a, b)` on the Vd
// registers, see mipp/cpp/patterns.hpp. Included by mipp_obj.hpp, not by mipp/obj/utils.hpp.
// Generated from generator/helpers_headers/templates/mipp_obj_patterns.tpl.hpp (utils_generator.py).

#if __cplusplus >= 201703L

#include "mipp/cpp/patterns.hpp"
#include "mipp/internal/interfaces/obj/common.hpp"

namespace mipp
{
template <typename P, typename T, int LMUL>
inline Vd<T, LMUL> permute(const Vd<T, LMUL>& r) { return Vd<T, LMUL>(mipp::permute<P>(r.vd)); }

template <typename P, typename T, int LMUL>
inline Vd<T, LMUL> permute2(const Vd<T, LMUL>& vd0, const Vd<T, LMUL>& vd1)
{ return Vd<T, LMUL>(mipp::permute2<P>(vd0.vd, vd1.vd)); }
} // namespace mipp

#endif // __cplusplus >= 201703L
