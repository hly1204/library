#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "poly_998244353_portable.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n, m;
    std::cin >> n >> m;
    Poly A(n), B(m);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    for (int i = 0; i < m; ++i) std::cin >> B[i];
    auto [Q, R] = A.euclid_div(B);
    assert(Q == A / B);
    assert(R == A % B);
    std::cout << Q.deg() + 1 << ' ' << R.deg() + 1 << '\n';
    for (int i = 0; i <= Q.deg(); ++i) std::cout << Q[i] << " \n"[i == Q.deg()];
    for (int i = 0; i <= R.deg(); ++i) std::cout << R[i] << " \n"[i == R.deg()];
    return 0;
}
