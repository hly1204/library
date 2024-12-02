#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "c_recursive.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int d;
    long long k;
    std::cin >> d >> k;
    std::vector<mint> Q(d + 1), init_v(d);
    for (int i = 0; i < d; ++i) std::cin >> init_v[i];
    Q[0] = 1;
    for (int i = 1; i <= d; ++i) {
        std::cin >> Q[i];
        Q[i] = -Q[i];
    }
    const auto M = xk_mod(k, std::vector(Q.rbegin(), Q.rend()));
    mint res;
    for (int i = 0; i < (int)M.size(); ++i) res += M[i] * init_v[i];
    std::cout << res << '\n';
    return 0;
}
