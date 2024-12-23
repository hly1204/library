#define PROBLEM "https://yukicoder.me/problems/448"

#include "chinese_remainder.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> rem(n), mod(n);
    for (int i = 0; i < n; ++i) std::cin >> rem[i] >> mod[i];
    if (const auto res = chinese_remainder_mod(rem, mod, 1000000007)) {
        if (std::all_of(rem.begin(), rem.end(), [](int n) { return n == 0; })) {
            std::cout << std::get<1>(*res) << '\n';
        } else {
            std::cout << std::get<0>(*res) << '\n';
        }
    } else {
        std::cout << "-1\n";
    }
    return 0;
}
