// overflow_helpers.hpp
#pragma once
#include <type_traits>
#include <limits>
#include <cstdint>
#include <cmath>    // std::isinf

namespace ovf {

enum class Op { Add, Sub, Mul, Div };

namespace detail {

template <class T>
inline constexpr bool is_supported_int_v =
    std::is_integral_v<T> && !std::is_same_v<T, bool>;

template <class T>
inline constexpr bool is_supported_fp_v =
    std::is_floating_point_v<T>;

template <class T>
using lim = std::numeric_limits<T>;

#if defined(__SIZEOF_INT128__)
using i128 = __int128_t;
using u128 = __uint128_t;
#endif

template <class T>
struct wider;

template <> struct wider<std::int8_t>   { using type = std::int16_t; };
template <> struct wider<std::uint8_t>  { using type = std::uint16_t; };
template <> struct wider<std::int16_t>  { using type = std::int32_t; };
template <> struct wider<std::uint16_t> { using type = std::uint32_t; };
template <> struct wider<std::int32_t>  { using type = std::int64_t; };
template <> struct wider<std::uint32_t> { using type = std::uint64_t; };

#if defined(__SIZEOF_INT128__)
template <> struct wider<std::int64_t>  { using type = i128; };
template <> struct wider<std::uint64_t> { using type = u128; };
#endif

template <class T>
using wider_t = typename wider<T>::type;

template <class T, class = void>
struct has_wider : std::false_type {};
template <class T>
struct has_wider<T, std::void_t<wider_t<T>>> : std::true_type {};
template <class T>
inline constexpr bool has_wider_v = has_wider<T>::value;

} // namespace detail

// ======================= INTEGRAL =======================

template <class T>
requires detail::is_supported_int_v<T>
bool will_add_overflow(T a, T b) {
#if defined(__clang__) || defined(__GNUC__)
    T out;
    return __builtin_add_overflow(a, b, &out);
#else
    if constexpr (std::is_unsigned_v<T>) {
        return a > detail::lim<T>::max() - b;
    } else {
        using L = detail::lim<T>;
        if (b > 0) return a > L::max() - b;
        if (b < 0) return a < L::min() - b;
        return false;
    }
#endif
}

template <class T>
requires detail::is_supported_int_v<T>
bool will_sub_overflow(T a, T b) {
#if defined(__clang__) || defined(__GNUC__)
    T out;
    return __builtin_sub_overflow(a, b, &out);
#else
    if constexpr (std::is_unsigned_v<T>) {
        return a < b;
    } else {
        using L = detail::lim<T>;
        if (b > 0) return a < L::min() + b;
        if (b < 0) return a > L::max() + b;
        return false;
    }
#endif
}

template <class T>
requires detail::is_supported_int_v<T>
bool will_mul_overflow(T a, T b) {
#if defined(__clang__) || defined(__GNUC__)
    T out;
    return __builtin_mul_overflow(a, b, &out);
#else
    if constexpr (detail::has_wider_v<T>) {
        using W = detail::wider_t<T>;
        W prod = static_cast<W>(a) * static_cast<W>(b);
        return prod < static_cast<W>(detail::lim<T>::min()) ||
               prod > static_cast<W>(detail::lim<T>::max());
    } else {
        // Conservative fallback (mainly for int64 on platforms without int128)
        if (a == 0 || b == 0) return false;

        if constexpr (std::is_unsigned_v<T>) {
            using L = detail::lim<T>;
            return a > (L::max() / b);
        } else {
            using L = detail::lim<T>;
            if (a == -1) return b == L::min();
            if (b == -1) return a == L::min();

            if (a > 0) {
                if (b > 0) return a > (L::max() / b);
                else       return b < (L::min() / a);
            } else { // a < 0
                if (b > 0) return a < (L::min() / b);
                else       return a != 0 && b < (L::max() / a);
            }
        }
    }
#endif
}

template <class T>
requires detail::is_supported_int_v<T>
bool will_div_overflow(T a, T b) {
    // div-by-zero is not "overflow" here; handle separately if you want
    if (b == 0) return false;
    if constexpr (std::is_signed_v<T>) {
        return (a == detail::lim<T>::min() && b == T{-1});
    } else {
        return false;
    }
}

// ======================= FLOATING-POINT =======================
// Definition here: "overflow happened" iff the operation result is +/-inf.
// (This matches IEEE-754 overflow behavior.)

template <class T>
requires detail::is_supported_fp_v<T>
bool will_add_overflow(T a, T b) {
    return std::isinf(a + b);
}

template <class T>
requires detail::is_supported_fp_v<T>
bool will_sub_overflow(T a, T b) {
    return std::isinf(a - b);
}

template <class T>
requires detail::is_supported_fp_v<T>
bool will_mul_overflow(T a, T b) {
    return std::isinf(a * b);
}

template <class T>
requires detail::is_supported_fp_v<T>
bool will_div_overflow(T a, T b) {
    return std::isinf(a / b);
}

// ======================= GENERIC DISPATCH =======================

template <class T>
requires (detail::is_supported_int_v<T> || detail::is_supported_fp_v<T>)
bool will_overflow(Op op, T a, T b) {
    switch (op) {
        case Op::Add: return will_add_overflow<T>(a, b);
        case Op::Sub: return will_sub_overflow<T>(a, b);
        case Op::Mul: return will_mul_overflow<T>(a, b);
        case Op::Div: return will_div_overflow<T>(a, b);
    }
    return false;
}

} // namespace ovf