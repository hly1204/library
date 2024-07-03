#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "basis.hpp"
#include "mat_basic.hpp"
#include "modint.hpp"
#include "random.hpp"
#include "sbpoly.hpp"
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
    SBPoly<mint> cp = {mint(1)};
    while (B.size() < n) {
        int deg = 0;
        for (auto R = random_vector<mint>(n);; R = mat_apply(A, R)) {
            if (auto comb = B.insert(R)) {
                SBPoly<mint> p(comb->begin() + (B.size() - deg), comb->begin() + B.size());
                p.emplace_back(1);
                cp *= p;
                break;
            }
            ++deg;
        }
    }
    for (int i = 0; i <= n; ++i) std::cout << cp[i] << ' ';
    return 0;
}
