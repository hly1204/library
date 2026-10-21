// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/log_of_formal_power_series

#include "modint.hpp"
#include "relaxed_conv.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    RelaxedFPSLog<mint> a;
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << ' ';
        mint v;
        std::cin >> v;
        std::cout << a.push(v);
    }
    return 0;
}
