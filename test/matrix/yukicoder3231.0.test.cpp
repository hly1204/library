// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3231

#include "frobenius.hpp"
#include "mat_basic.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<1000000007>;
    Matrix<mint> A(2, std::vector<mint>(2)), B(2, std::vector<mint>(2));
    Frobenius<mint> F_A(A), F_B(B);
    if (F_A.frobenius_form() == F_B.frobenius_form()) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}
