#pragma once

#include <type_traits>

template <typename Int>
struct XGcdResult {
    Int x, y, gcd;
};

template <typename Int>
inline std::enable_if_t<std::is_signed_v<Int>, XGcdResult<Int>> xgcd(Int a, Int b) {
    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;
    while (b) {
        Int q = a / b, x11_old = x11, x12_old = x12, a_old = a;
        x11 = x21, x21 = x11_old - x21 * q;
        x12 = x22, x22 = x12_old - x22 * q;
        a = b, b = a_old - b * q;
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
        Int q = a / b, x11_old = x11, a_old = a;
        x11 = x21, x21 = x11_old - x21 * q;
        a = b, b = a_old - b * q;
    }
    return InvGcdResult<Int>{x11, a};
}
