// uniform.hpp
#pragma once

#include <random>
#include <type_traits>
#include <limits>
#include <cstdint>
#include <concepts>

namespace rnd {

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform(std::mt19937& rng, T min_val, T max_val) {
    if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        return dist(rng);
    } else {
        using Wide = std::conditional_t<(sizeof(T) < 4),
                                        std::conditional_t<std::is_signed_v<T>, int, unsigned>,
                                        T>;
        std::uniform_int_distribution<Wide> dist(static_cast<Wide>(min_val), static_cast<Wide>(max_val));
        return static_cast<T>(dist(rng));
    }
}

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        return uniform<T>(rng, (T)-1.0, (T)1.0);
    } else {
        return uniform<T>(rng, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }
}

inline bool uniform_bool(std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(rng) != 0;
}

// --- Strictly Positive (> 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_strictly_positive(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        return uniform<T>(rng, std::numeric_limits<T>::min(), (T)1.0);
    } else {
        return uniform<T>(rng, (T)1, std::numeric_limits<T>::max());
    }
}

// --- Positive (>= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_positive(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        return uniform<T>(rng, (T)0, (T)1.0);
    } else {
        return uniform<T>(rng, (T)0, std::numeric_limits<T>::max());
    }
}

// --- Strictly Negative (< 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_strictly_negative(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        return uniform<T>(rng, (T)-1.0, -std::numeric_limits<T>::min());
    } else {
        return uniform<T>(rng, std::numeric_limits<T>::min(), (T)-1);
    }
}

// --- Negative (<= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_negative(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        return uniform<T>(rng, (T)-1.0, (T)0);
    } else {
        return uniform<T>(rng, std::numeric_limits<T>::min(), (T)0);
    }
}

// --- Exclude Zero (!= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_exclude_zero(std::mt19937& rng) {
    T val = uniform<T>(rng);
    if (val == (T)0) val = (T)1;
    return val;
}

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform_exclude_zero(std::mt19937& rng, T min_val, T max_val) {
    T val = uniform<T>(rng, min_val, max_val);
    if (val == (T)0) val = (T)1;
    return val;
}

} // namespace rnd