// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind

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
    const auto S = stirling_numbers_2nd_row<mint>(n);
    for (int i = 0; i <= n; ++i) std::cout << S[i] << ' ';
    return 0;
}
