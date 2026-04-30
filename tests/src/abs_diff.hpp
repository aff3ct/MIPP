// abs_diff.hpp
#pragma once
#include <type_traits>
#include <limits>
#include <cstdlib>   // std::abs overloads for signed ints
#include <cmath>     // std::abs overloads for floats

namespace abs_diff {

// abs-like: works for signed ints, unsigned ints, and floats.
// For unsigned: returns the input unchanged (it is already non-negative).
template <class T>
constexpr T abs_diff(T x) noexcept {
    if constexpr (std::is_unsigned_v<T>) {
        return x;
    } else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        // Beware: abs(INT_MIN) is not representable; handle it explicitly.
        using Lim = std::numeric_limits<T>;
        if (x == Lim::min()) {
            // return magnitude as an unsigned of same width (see overload below),
            // but since we must return T here, clamp to max.
            return Lim::max();
        }
        return x < 0 ? -x : x;
    } else {
        // floating point (and anything else with std::abs)
        using std::abs;
        return abs(x);
    }
}

// Better: abs magnitude for signed integers returning an unsigned type of same width.
// This avoids the INT_MIN problem completely.
template <class T>
requires (std::is_integral_v<T> && std::is_signed_v<T>)
constexpr std::make_unsigned_t<T> uabs(T x) noexcept {
    using U = std::make_unsigned_t<T>;
    // two's complement safe magnitude:
    // for negative x, compute 0 - U(x) (wrap in unsigned), yields |x|
    U ux = static_cast<U>(x);
    return (x < 0) ? U{0} - ux : ux;
}

// Absolute difference: same “feel” as abs, but for two values.
// For unsigned: returns unsigned.
// For signed ints: returns unsigned magnitude to avoid UB/overflow.
// For floats: returns float type.
template <class T>
constexpr auto abs_diff(T a, T b) noexcept {
    if constexpr (std::is_unsigned_v<T>) {
        return (a < b) ? (b - a) : (a - b);               // type: T
    } else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        // return unsigned magnitude, safe even for INT_MIN cases
        using U = std::make_unsigned_t<T>;
        U ua = static_cast<U>(a);
        U ub = static_cast<U>(b);
        return (ua < ub) ? (ub - ua) : (ua - ub);         // type: U
    } else {
        // floating point
        using std::abs;
        return abs(a - b);                                 // type: T
    }
}

} // namespace abs_diff