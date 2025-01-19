#pragma once

#include <array>
#include <type_traits>
#include <utility>

// returns [x, y, gcd(a, b)] s.t. ax+by = gcd(a, b)
template<typename Int>
inline std::enable_if_t<std::is_signed_v<Int>, std::array<Int, 3>> xgcd(Int a, Int b) {
    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;
    while (b) {
        std::add_const_t<Int> q = a / b;
        x11                     = std::exchange(x21, x11 - x21 * q);
        x12                     = std::exchange(x22, x12 - x22 * q);
        a                       = std::exchange(b, a - b * q);
    }
    return {x11, x12, a};
}

// returns [a^(-1) mod b, gcd(a, b)]
template<typename Int>
inline std::enable_if_t<std::is_signed_v<Int>, std::array<Int, 2>> inv_gcd(Int a, Int b) {
    Int x11 = 1, x21 = 0;
    while (b) {
        std::add_const_t<Int> q = a / b;
        x11                     = std::exchange(x21, x11 - x21 * q);
        a                       = std::exchange(b, a - b * q);
    }
    return {x11, a}; // check x11 < 0, check a = 1
}
