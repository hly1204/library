#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "modint.hpp"
#include "swag.hpp"
#include <array>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint              = ModInt<998244353>;
    using LinearFunction    = std::array<mint, 2>;
    const LinearFunction Id = {0, 1};
    // L(R)
    auto composition = [](const LinearFunction &L, const LinearFunction &R) {
        return LinearFunction{L[0] + L[1] * R[0], L[1] * R[1]};
    };
    // R(L)
    auto composition2 = [&](const LinearFunction &L, const LinearFunction &R) {
        return composition(R, L);
    };
    SWAG<LinearFunction, decltype(composition2)> swag(composition2);
    int Q;
    std::cin >> Q;
    while (Q--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            mint a, b;
            std::cin >> a >> b;
            swag.push_back({b, a});
        } else if (cmd == 1) {
            swag.pop_front();
        } else {
            mint x;
            std::cin >> x;
            std::cout << composition(swag.query().value_or(Id), {x, 0}).at(0) << '\n';
        }
    }
    return 0;
}
