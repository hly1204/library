// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k

#include "famous_sequence.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, k;
    std::cin >> n >> k;
    const auto S = signed_stirling_numbers_1st_column<mint>(k, n + 1);
    for (int i = k; i <= n; ++i) std::cout << S[i] << ' ';
    return 0;
}
