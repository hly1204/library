// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod

#include <cassert>
#include <iostream>
#include <vector>

int det(std::vector<std::vector<int>> a, int mod) {
    assert(mod > 1);
    const int n = a.size();
    int det     = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (a[pivot][i] != 0) break;
        if (pivot == n) return 0;
        if (pivot != i) {
            a[pivot].swap(a[i]);
            det = mod - det;
        }
        for (int j = i + 1; j < n; ++j) {
            int aii = a[i][i], aji = a[j][i];
            if (aji == 0) continue;
            // `a0` * `a[i][i]` + `a1` * `a[j][i]`     (1)
            // `b0` * `a[i][i]` + `b1` * `a[j][i]`     (2)
            // Use Euclidean algorithm to compute `a0, a1, b0, b1` s.t. (1) = 0 or (2) = 0
            int a0 = 1, a1 = 0, b0 = 0, b1 = 1;
            while (aii != 0 && aji != 0) {
                if (aii < aji) {
                    const int q = aji / aii;
                    aji -= aii * q, b0 -= a0 * q, b1 -= a1 * q;
                } else {
                    const int q = aii / aji;
                    aii -= aji * q, a0 -= b0 * q, a1 -= b1 * q;
                }
            }
            if (a0 < mod) a0 += mod;
            if (a1 < mod) a1 += mod;
            if (b0 < mod) b0 += mod;
            if (b1 < mod) b1 += mod;
            for (int k = i; k < n; ++k) {
                const long long aik = a[i][k], ajk = a[j][k];
                a[i][k] = (aik * a0 + ajk * a1) % mod;
                a[j][k] = (aik * b0 + ajk * b1) % mod;
            }
            if (aii == 0) {
                a[i].swap(a[j]);
                det = mod - det;
            }
        }
        if ((det = (long long)det * a[i][i] % mod) == 0) return 0;
    }
    return det;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, mod;
    std::cin >> n >> mod;
    std::vector a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> a[i][j];
    std::cout << det(a, mod) << '\n';
    return 0;
}
