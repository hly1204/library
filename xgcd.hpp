#pragma once

#include <type_traits>
#include <utility>

template <typename Int>
struct XGcdResult {
    Int x, y, gcd;
};

template <typename Int>
inline std::enable_if_t<std::is_signed_v<Int>, XGcdResult<Int>> xgcd(Int a, Int b) {
    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;
    while (b) {
        std::add_const_t<Int> q = a / b;
        x11                     = std::exchange(x21, x11 - x21 * q);
        x12                     = std::exchange(x22, x12 - x22 * q);
        a                       = std::exchange(b, a - b * q);
    }
    return XGcdResult<Int>{x11, x12, a};
}

template <typename Int>
struct InvGcdResult {
    Int inv, gcd;
};

template <typename Int>
inline std::enable_if_t<std::is_signed_v<Int>, InvGcdResult<Int>> inv_gcd(Int a, Int b) {
    Int x11 = 1, x21 = 0;
    while (b) {
        std::add_const_t<Int> q = a / b;
        x11                     = std::exchange(x21, x11 - x21 * q);
        a                       = std::exchange(b, a - b * q);
    }
    return InvGcdResult<Int>{x11, a};
}
