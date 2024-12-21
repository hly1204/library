#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "c_finite.hpp"
#include "fps_basic.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    mint c;
    std::cin >> n >> m >> c;
    std::vector<mint> A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const auto Q = fps_pow(std::vector{mint(1), mint(-1)}, n, n + 1);
    auto P       = convolution(A, Q);
    P.resize(n);
    const auto res = slice_coeff_rational(P, Q, c.val(), c.val() + m);
    for (int i = 0; i < (int)res.size(); ++i) std::cout << res[i] << ' ';
    return 0;
}
