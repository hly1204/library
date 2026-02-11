// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_taylor_shift

#include "binomial.hpp"
#include "fps_as_operator.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

template<typename Tp>
std::vector<Tp> taylor_shift_via_linear_operator(const std::vector<Tp> &a, Tp c) {
    const int n = a.size();
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> f(n);
    Tp cc = 1;
    for (int i = 0; i < n; ++i) f[i] = cc * bin.inv_factorial(i), cc *= c;
    return apply_fps(f, a);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    mint c;
    std::cin >> n >> c;
    std::vector<mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto res = taylor_shift_via_linear_operator(a, c);
    for (int i = 0; i < n; ++i) std::cout << res[i] << ' ';
    return 0;
}
