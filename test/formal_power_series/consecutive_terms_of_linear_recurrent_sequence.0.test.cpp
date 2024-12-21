#define PROBLEM "https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence"

#include "c_finite.hpp"
#include "fft.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int d;
    long long k;
    int M;
    std::cin >> d >> k >> M;
    std::vector<mint> Q(d + 1), init_v(d);
    for (int i = 0; i < d; ++i) std::cin >> init_v[i];
    Q[0] = 1;
    for (int i = 1; i <= d; ++i) {
        std::cin >> Q[i];
        Q[i] = -Q[i];
    }
    auto P = convolution(Q, init_v);
    P.resize(d);
    const auto res = slice_coeff_rational(P, Q, k, k + M);
    for (int i = 0; i < (int)res.size(); ++i) std::cout << res[i] << ' ';
    return 0;
}
