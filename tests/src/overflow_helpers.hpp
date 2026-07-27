// overflow_helpers.hpp
#pragma once
#include <type_traits>
#include <limits>
#include <cstdint>
#include <cmath>    // std::isinf

#include <vector>

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

template <class T>
requires (detail::is_supported_int_v<T> || detail::is_supported_fp_v<T>)
bool will_reduction_hadd_overflow(const T* inputs, size_t size, const int32_t* mask = nullptr, bool is_maskz = false, const T* inputs_src = nullptr) {
    if constexpr (detail::is_supported_fp_v<T>) return false;
    else {
        using L = detail::lim<T>;
        int64_t sum_pos = 0;
        int64_t sum_neg = 0;
        for (size_t i = 0; i < size; i++) {
            T val = inputs[i];
            if (mask) {
                if (is_maskz) {
                    val = mask[i] ? inputs[i] : static_cast<T>(0);
                } else if (inputs_src) {
                    val = mask[i] ? inputs[i] : inputs_src[i];
                }
            }
            if (val > 0) {
                sum_pos += static_cast<int64_t>(val);
            } else if (val < 0) {
                sum_neg += static_cast<int64_t>(val);
            }
        }
        return (sum_pos > static_cast<int64_t>(L::max()) ||
                sum_neg < static_cast<int64_t>(L::min()));
    }
}

template <class T>
requires (detail::is_supported_int_v<T> || detail::is_supported_fp_v<T>)
bool will_reduction_hadds_overflow(const T* inputs, size_t size, const int32_t* mask = nullptr, bool is_maskz = false, const T* inputs_src = nullptr) {
    if constexpr (detail::is_supported_fp_v<T>) return false;
    else {
        using L = detail::lim<T>;
        auto sat_add = [](T a, T b) -> T {
            if constexpr (std::is_signed_v<T>) {
                int64_t sum = static_cast<int64_t>(a) + static_cast<int64_t>(b);
                if (sum > static_cast<int64_t>(L::max())) return L::max();
                if (sum < static_cast<int64_t>(L::min())) return L::min();
                return static_cast<T>(sum);
            } else {
                uint64_t sum = static_cast<uint64_t>(a) + static_cast<uint64_t>(b);
                if (sum > static_cast<uint64_t>(L::max())) return L::max();
                return static_cast<T>(sum);
            }
        };

        auto is_sat_overflow = [](T a, T b) -> bool {
            if constexpr (std::is_signed_v<T>) {
                int64_t sum = static_cast<int64_t>(a) + static_cast<int64_t>(b);
                return (sum > static_cast<int64_t>(L::max()) || sum < static_cast<int64_t>(L::min()));
            } else {
                uint64_t sum = static_cast<uint64_t>(a) + static_cast<uint64_t>(b);
                return (sum > static_cast<uint64_t>(L::max()));
            }
        };

        std::vector<T> v(size);
        for (size_t i = 0; i < size; i++) {
            T val = inputs[i];
            if (mask) {
                if (is_maskz) {
                    val = mask[i] ? inputs[i] : static_cast<T>(0);
                } else if (inputs_src) {
                    val = mask[i] ? inputs[i] : inputs_src[i];
                }
            }
            v[i] = val;
        }

        // 1. Check sequential linear saturation
        T acc_seq = v[0];
        for (size_t i = 1; i < size; i++) {
            if (is_sat_overflow(acc_seq, v[i])) return true;
            acc_seq = sat_add(acc_seq, v[i]);
        }

        // 2. Check chunk-wise (LMUL sub-vector) saturation
        size_t chunk_size = 16;
        if (chunk_size > size) chunk_size = size;

        std::vector<T> chunk_sums;
        for (size_t c = 0; c < size; c += chunk_size) {
            size_t end = std::min(size, c + chunk_size);
            T acc_chunk = v[c];
            for (size_t i = c + 1; i < end; i++) {
                if (is_sat_overflow(acc_chunk, v[i])) return true;
                acc_chunk = sat_add(acc_chunk, v[i]);
            }
            chunk_sums.push_back(acc_chunk);
        }

        // 3. Check combination of chunk sums
        T acc_chunks = chunk_sums[0];
        for (size_t i = 1; i < chunk_sums.size(); i++) {
            if (is_sat_overflow(acc_chunks, chunk_sums[i])) return true;
            acc_chunks = sat_add(acc_chunks, chunk_sums[i]);
        }

        return false;
    }
}

} // namespace ovf