// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bell_number

#include "famous_sequence.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    const auto B = bell_numbers<mint>(n + 1);
    for (int i = 0; i <= n; ++i) std::cout << B[i] << ' ';
    return 0;
}
