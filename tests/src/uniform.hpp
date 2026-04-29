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
T uniform(std::mt19937& rng) {
    if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
        // Full range of T (inclusive)
        using Lim = std::numeric_limits<T>;

        // Avoid int8_t/uint8_t being treated as char by distributions/streams
        using Wide = std::conditional_t<(sizeof(T) < 4),
                                        std::conditional_t<std::is_signed_v<T>, int, unsigned>,
                                        T>;

        std::uniform_int_distribution<Wide> dist(static_cast<Wide>(Lim::min()),
                                                 static_cast<Wide>(Lim::max()));
        return static_cast<T>(dist(rng));
    } else if constexpr (std::is_floating_point_v<T>) {
        // Default float/double range: [INT32_MIN, INT32_MAX)
        constexpr std::int32_t lo_i = std::numeric_limits<std::int32_t>::min();
        constexpr std::int32_t hi_i = std::numeric_limits<std::int32_t>::max();

        // Step 1: generate u in [0, 1) using integer RNG bits
        constexpr int digits = std::numeric_limits<T>::digits; // 24 for float, 53 for double
        using UInt = std::conditional_t<(digits <= 32), std::uint32_t, std::uint64_t>;
        constexpr UInt maxu = (digits == 64) ? ~UInt{0} : (UInt{1} << digits) - 1;

        std::uniform_int_distribution<UInt> dist(0, maxu);
        const UInt u = dist(rng);

        const long double unit = static_cast<long double>(u) /
                                 (static_cast<long double>(maxu) + 1.0L); // [0,1)

        // Step 2: scale into [lo_i, hi_i)
        const long double lo = static_cast<long double>(lo_i);
        const long double hi = static_cast<long double>(hi_i);

        return static_cast<T>(lo + (hi - lo) * unit);
    } else {
        static_assert(!std::is_same_v<T, T>, "rnd::uniform<T>: unsupported type (bool not supported)");
    }
}

} // namespace rnd