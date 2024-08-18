#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "fps_polya.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, t;
    std::cin >> n >> t;
    std::vector<mint> A(t + 1);
    while (n--) {
        int pos;
        std::cin >> pos;
        A[pos] += 1;
    }
    const auto res = polya_exp_m(A, t + 1);
    for (int i = 1; i <= t; ++i) std::cout << res[i] << ' ';
    return 0;
}
