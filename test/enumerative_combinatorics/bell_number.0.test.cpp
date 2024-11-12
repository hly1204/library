#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "binomial.hpp"
#include "fps_basic.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

template <typename Tp>
inline std::vector<Tp> bell_numbers(int n) {
    auto &&bin = Binomial<Tp>::get(n);
    std::vector<Tp> ex(n);
    for (int i = 1; i < n; ++i) ex[i] = bin.inv_factorial(i);
    auto res = exp(ex, n);
    for (int i = 0; i < n; ++i) res[i] *= bin.factorial(i);
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    const auto B = bell_numbers<mint>(n + 1);
    for (int i = 0; i <= n; ++i) std::cout << B[i] << ' ';
    return 0;
}
