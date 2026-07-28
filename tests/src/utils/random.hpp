// random.hpp — Unified random number generation for MIPP tests.
// Provides uniform and normal (Gaussian) distributions for both
// integer and floating-point types, with named variants (positive,
// negative, exclude_zero, truncated).
#pragma once

#include <cmath>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <limits>
#include <cstdint>
#include <concepts>

#include "n_iter.hpp"

namespace rnd {

// ---------------------------------------------------------------------------
// Uniform distribution
// ---------------------------------------------------------------------------

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform(std::mt19937& rng) {
    if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist((T)-1.0, (T)1.0);
        return dist(rng);
    } else {
        using Wide = std::conditional_t<(sizeof(T) < 4),
                                        std::conditional_t<std::is_signed_v<T>, int, unsigned>,
                                        T>;
        std::uniform_int_distribution<Wide> dist(
            static_cast<Wide>(std::numeric_limits<T>::min()),
            static_cast<Wide>(std::numeric_limits<T>::max()));
        return static_cast<T>(dist(rng));
    }
}

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T uniform(std::mt19937& rng, T min_val, T max_val) {
    if (min_val > max_val) {
        throw std::invalid_argument(
            "rnd::uniform: min_val must be <= max_val. "
            "Did you pass a negative bound for an unsigned type?");
    }
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

// ---------------------------------------------------------------------------
// Normal (Gaussian) distribution
// Supports both floating-point and integer types.
// For integers: samples a double normal, rounds, and clamps to type limits.
// ---------------------------------------------------------------------------

// --- Unconstrained normal ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal(std::mt19937& rng, T mean = (T)0, T stddev = (T)1) {
    if constexpr (std::is_floating_point_v<T>) {
        std::normal_distribution<T> dist(mean, stddev);
        return dist(rng);
    } else {
        // For integers: sample double normal, round, clamp to type limits
        std::normal_distribution<double> dist(static_cast<double>(mean),
                                               static_cast<double>(stddev));
        double val = std::round(dist(rng));
        val = std::max(val, static_cast<double>(std::numeric_limits<T>::min()));
        val = std::min(val, static_cast<double>(std::numeric_limits<T>::max()));
        return static_cast<T>(val);
    }
}

// --- Truncated normal within [min_val, max_val] (rejection sampling) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal(std::mt19937& rng, T min_val, T max_val, T mu, T sigma) {
    if (min_val > max_val) {
        throw std::invalid_argument(
            "rnd::normal: min_val must be <= max_val. "
            "Did you pass a negative bound for an unsigned type?");
    }
    if constexpr (std::is_floating_point_v<T>) {
        std::normal_distribution<T> dist(mu, sigma);
        T val;
        do { val = dist(rng); } while (val < min_val || val > max_val);
        return val;
    } else {
        std::normal_distribution<double> dist(static_cast<double>(mu),
                                               static_cast<double>(sigma));
        double val;
        do { val = std::round(dist(rng)); } while (val < static_cast<double>(min_val)
                                                 || val > static_cast<double>(max_val));
        return static_cast<T>(val);
    }
}

// --- Strictly Positive (> 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_strictly_positive(std::mt19937& rng, T sigma = (T)1) {
    if constexpr (std::is_floating_point_v<T>) {
        T val;
        do { val = std::abs(normal<T>(rng, (T)0, sigma)); } while (val == (T)0);
        return val;
    } else {
        return std::max((T)1, static_cast<T>(std::abs(normal<double>(rng, 0.0, static_cast<double>(sigma)))));
    }
}

// --- Positive (>= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_positive(std::mt19937& rng, T sigma = (T)1) {
    if constexpr (std::is_floating_point_v<T>) {
        return std::abs(normal<T>(rng, (T)0, sigma));
    } else {
        return static_cast<T>(std::abs(normal<double>(rng, 0.0, static_cast<double>(sigma))));
    }
}

// --- Strictly Negative (< 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_strictly_negative(std::mt19937& rng, T sigma = (T)1) {
    return -normal_strictly_positive<T>(rng, sigma);
}

// --- Negative (<= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_negative(std::mt19937& rng, T sigma = (T)1) {
    return -normal_positive<T>(rng, sigma);
}

// --- Exclude Zero (!= 0) ---
template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_exclude_zero(std::mt19937& rng, T sigma = (T)1) {
    T val = normal<T>(rng, (T)0, sigma);
    if (val == (T)0) val = (T)1;
    return val;
}

template <class T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T normal_exclude_zero(std::mt19937& rng, T min_val, T max_val, T mu, T sigma) {
    T val = normal<T>(rng, min_val, max_val, mu, sigma);
    if (val == (T)0) val = (T)1;
    return val;
}

} // namespace rnd
