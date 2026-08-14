// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3621

#include "fft.hpp"
#include "fps_basic.hpp"
#include "fps_composition.hpp"
#include "modint.hpp"
#include <cassert>
#include <iostream>
#include <vector>

// returns V(z) s.t. V(U(z)) = uV(z)
// We ensure Schroeder function of U exists.
template<typename Tp> std::vector<Tp> schroeder_function(const std::vector<Tp> &U, int n) {
    // see: TAOCP Vol 2 Chap 4.7.
    // returns V(z) s.t. V(U(z)) = W(z)V(z) + S(z) + O(z^n)
    auto brent_traub = [](auto &&brent_traub, const std::vector<Tp> &U, const std::vector<Tp> &W,
                          const std::vector<Tp> &S, int n) -> std::vector<Tp> {
        assert((n & (n - 1)) == 0);
        if (n == 1) {
            auto S0 = S.empty() ? Tp() : S[0];
            auto W0 = W.empty() ? Tp() : W[0];
            if (S0 == 0 && W0 == 1) return {Tp(1)};
            return {S0 / (1 - W0)};
        }
        auto V  = brent_traub(brent_traub, U, W, S, n / 2);
        auto VU = composition(V, U, n);
        auto WV = convolution_trunc(W, V, n);
        std::vector<Tp> R(n / 2);
        for (int i = n / 2; i < n; ++i)
            R[i - n / 2] = WV[i] + (i < (int)S.size() ? S[i] : Tp(0)) - VU[i];
        std::vector U_hat = U;
        U_hat.erase(U_hat.begin());
        U_hat      = fps_pow(fps_inv(U_hat, n / 2), n / 2, n / 2);
        auto W_hat = convolution_trunc(W, U_hat, n / 2);
        auto S_hat = convolution_trunc(R, U_hat, n / 2);
        auto V_hat = brent_traub(brent_traub, U, W_hat, S_hat, n / 2);
        V.insert(V.end(), V_hat.begin(), V_hat.end());
        return V;
    };
    auto V = brent_traub(brent_traub, U, {U.at(1)}, {}, fft_len(n));
    V.resize(n);
    return V;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> f(n);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    const auto g = schroeder_function(f, n);
    const auto h = reversion(g, n);
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << ' ';
        std::cout << g[i];
    }
    std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << ' ';
        std::cout << h[i];
    }
    std::cout << '\n';
    return 0;
}
