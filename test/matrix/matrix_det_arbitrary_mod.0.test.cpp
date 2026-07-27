// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod

#include "xgcd.hpp"
#include <cassert>
#include <iostream>
#include <vector>

int det(std::vector<std::vector<int>> A, int mod) {
    assert(mod > 1);
    const int n = A.size();
    int det     = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot][i] != 0) break;
        if (pivot == n) return 0;
        if (pivot != i) {
            A[pivot].swap(A[i]);
            det = mod - det;
        }
        for (int j = i + 1; j < n; ++j) {
            if (A[j][i] == 0) continue;
            const auto [s, t, d] = xgcd(A[i][i], A[j][i]);
            const int a = -A[j][i] / d, b = A[i][i] / d;
            // (row(i), row(j)) <- (s*row(i) + t*row(j), -A(j,i)/d*row(i) + A(i,i)/d*row(j))
            for (int k = i; k < n; ++k) {
                const long long Aik = A[i][k], Ajk = A[j][k];
                if ((A[i][k] = (s * Aik + t * Ajk) % mod) < 0) A[i][k] += mod;
                if ((A[j][k] = (a * Aik + b * Ajk) % mod) < 0) A[j][k] += mod;
            }
            // A(i,i) = d, A(j,i) = 0
        }
        if ((det = (long long)det * A[i][i] % mod) == 0) return 0;
    }
    return det;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, mod;
    std::cin >> n >> mod;
    std::vector A(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> A[i][j];
    std::cout << det(A, mod) << '\n';
    return 0;
}
