// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/partition_function

#include "famous_sequence.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    const auto P = partition_function<mint>(n + 1);
    for (int i = 0; i <= n; ++i) std::cout << P[i] << ' ';
    return 0;
}
