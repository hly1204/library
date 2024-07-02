#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "basis.hpp"
#include "fft.hpp"
#include "mat_basic.hpp"
#include "modint.hpp"
#include "random.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    Matrix<mint> A(n, std::vector<mint>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> A[i][j];
    Basis<mint> B(n);
    std::vector<mint> cp = {1};
    while (B.size() < n) {
        int deg = 0;
        for (auto R = random_vector<mint>(n);; R = mat_apply(A, R)) {
            if (auto comb = B.insert(R)) {
                std::vector p(comb->begin() + (B.size() - deg), comb->begin() + B.size());
                p.emplace_back(1);
                cp = convolution(cp, p);
                break;
            }
            ++deg;
        }
    }
    for (int i = 0; i <= n; ++i) std::cout << cp[i] << ' ';
    return 0;
}
