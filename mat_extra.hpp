#pragma once

#include "mat_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

/*
test case generator:
```sage
import random
R.<x> = GF(998244353)[]
N = 5
d = 4
if __name__ == '__main__':
    print(N, d)
    A = zero_matrix(GF(998244353), N)
    L = []
    for _ in range(d):
        B = random_matrix(GF(998244353), N, algorithm='echelonizable', rank=random.randint(1,N))
        L.append(B)
        A = x*A + B
    L.reverse()
    for i in range(len(L)):
        for j in range(N):
            print(' '.join([str(k) for k in L[i][j].list()]), end='\n')
    print(det(A).list())
```
*/

// returns det(A0 + xA1 + ... + x^(d-1) Ad-1)
// test: https://qoj.ac/contest/1536/problem/59
// see:
// [1]: Elegia's comment.
//      https://codeforces.com/blog/entry/92248?#comment-818786
template<typename Tp> inline std::vector<Tp> det_d(Matrix<std::vector<Tp>> A) {
    assert(A.is_square());
    const int n = A.height();
    const int d = (n == 0 ? 0 : (int)A[0][0].size());
    auto sub    = [n, d](auto &&a, auto &&b, Tp v) {
        if (v == 0) return;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < d; ++j) a[i][j] -= v * b[i][j];
    };
    auto mul = [n, d](auto &&a, Tp v) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < d; ++j) a[i][j] *= v;
    };
    Tp m = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot][i][d - 1] != 0) break;
        if (pivot == n) continue;
        if (pivot != i) {
            A[pivot].swap(A[i]);
            m = -m;
        }
        m *= A[i][i][d - 1];
        mul(A[i], A[i][i][d - 1].inv());
        for (int j = 0; j < n; ++j)
            if (j != i) sub(A[j], A[i], A[j][i][d - 1]);
    }
    int t = 0;
    for (; t <= n * (d - 1); ++t) {
        int s = 0;
        for (; s < n; ++s)
            if (std::all_of(A[s].begin(), A[s].end(), [d](const auto &a) { return a[d - 1] == 0; }))
                break;
        if (s == n) break;
        for (int i = 0; i < n; ++i)
            std::rotate(A[s][i].rbegin(), A[s][i].rbegin() + 1, A[s][i].rend());
        for (int i = 0; i < n; ++i)
            if (i != s) sub(A[s], A[i], A[s][i][d - 1]);
        int pivot = 0;
        for (; pivot < n; ++pivot)
            if (A[s][pivot][d - 1] != 0) break;
        if (pivot == n) continue;
        m *= A[s][pivot][d - 1];
        mul(A[s], A[s][pivot][d - 1].inv());
        for (int i = 0; i < n; ++i)
            if (i != s) sub(A[i], A[s], A[i][pivot][d - 1]);
        if (pivot == s) continue;
        A[pivot].swap(A[s]);
        m = -m;
        if (A[s][s][d - 1] == 0) continue;
        m *= A[s][s][d - 1];
        mul(A[s], A[s][s][d - 1].inv());
        for (int i = 0; i < n; ++i)
            if (i != s) sub(A[i], A[s], A[i][s][d - 1]);
    }
    if (t > n * (d - 1)) return {};
    //     [      I            ]
    //     [         ...       ]
    // B = [             ...   ]
    //     [                  I]
    //     [C_0 C_1 ... C_(d-2)]
    // charpoly(B) = det(x^(d-1)I - ... - C_0) (Elegia, zx2003, mayaohua2003).
    Matrix<Tp> B(n * (d - 1), std::vector<Tp>(n * (d - 1)));
    for (int i = 0; i < d - 1; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k) B[(d - 2) * n + j][i * n + k] = -A[j][k][i];
    for (int i = 0; i < d - 2; ++i)
        for (int j = 0; j < n; ++j) B[i * n + j][(i + 1) * n + j] = 1;
    auto res = B.charpoly();
    res.erase(res.begin(), res.begin() + t);
    for (int i = 0; i < (int)res.size(); ++i) res[i] *= m;
    return res;
}
