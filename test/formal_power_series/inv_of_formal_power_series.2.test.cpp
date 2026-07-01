// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include "modint.hpp"
#include "poly_portable.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const std::vector<mint> invA = fps_inv(A, n);
    for (int i = 0; i < n; ++i) std::cout << invA[i] << ' ';
    return 0;
}
