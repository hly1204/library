#pragma once

#include <cassert>
#include <type_traits>

// see:
// [1]: Richard P. Brent and Paul Zimmermann. Modern Computer Arithmetic.

// returns floor(m^(1/2))
template<typename Int> inline std::enable_if_t<std::is_integral_v<Int>, Int> sqrt_int(Int m) {
    assert(m >= 0);
    if (m == 0) return 0;
    for (Int u = m;;) {
        std::add_const_t<Int> s = u;
        u                       = (s + m / s) / 2;
        if (u >= s) return s;
    }
}
