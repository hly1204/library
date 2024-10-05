#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "rng.hpp"
#include <array>
#include <iostream>
#include <random>
#include <utility>

std::array<int, 2> inv_gcd(int a, int b) {
    int x11 = 1, x21 = 0;
    while (b) {
        const int q = a / b;
        x11         = std::exchange(x21, x11 - x21 * q);
        a           = std::exchange(b, a - b * q);
    }
    return {x11, a};
}

int inv_mod(int a, int mod) {
    const int res = std::get<0>(inv_gcd(a, mod));
    return res < 0 ? res + mod : res;
}

int pow_mod(int a, int e, int mod) {
    if (e < 0) return pow_mod(inv_mod(a, mod), -e, mod);
    for (int res = 1;; a = (long long)a * a % mod) {
        if (e & 1) res = (long long)res * a % mod;
        if ((e /= 2) == 0) return res;
    }
}

// Tonelli--Shanks's algorithm
// see:
// [1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.
int sqrt_mod(int a, int mod) {
    // mod must be prime
    if (a == 0 || mod == 2) return a;

    auto is_square = [](int a, int mod) { return pow_mod(a, (mod - 1) / 2, mod) == 1; };

    if (!is_square(a, mod)) return -1;

    static xoshiro256starstar rng{std::random_device{}()};
    std::uniform_int_distribution<> dis(2, mod - 1);

    int r;
    do { r = dis(rng); } while (is_square(r, mod));

    int n = 1, m = (mod - 1) / 2;
    while (m % 2 == 0) ++n, m /= 2;
    // mod = 2^n m

    const int am = pow_mod(a, m, mod);
    // ord(c) = 2^n
    const int c = pow_mod(r, m, mod);

    // find e such that a^m=c^e
    int e = 0;
    for (int i = 1, j = 2; i < n; ++i, j *= 2) {
        // One can reduce the constant factor by
        // calculating something during the iteration,
        // but it is not necessary.
        if (pow_mod((long long)am * pow_mod(c, -e, mod) % mod, (mod - 1) / (m * j * 2), mod) == 1)
            continue;
        e += j;
    }

    // now set m=2j+1 => a^(2j)a=c^e => a=c^ea^(-2j)
    return (long long)pow_mod(c, e / 2, mod) * pow_mod(a, -(m / 2), mod) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int a, mod;
        std::cin >> a >> mod;
        std::cout << sqrt_mod(a, mod) << '\n';
    }
    return 0;
}
