#pragma once

#include "mat_basic.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <utility>
#include <vector>

// returns det(A0 + xA1)
template <typename Tp>
inline std::vector<Tp> det2(Matrix<std::array<Tp, 2>> A) {
    assert(is_square_matrix(A));
    auto sub = [](auto &a, const auto &b, Tp v, int n) {
        if (v == 0) return;
        for (int i = 0; i < n; ++i) a[i][0] -= v * b[i][0], a[i][1] -= v * b[i][1];
    };
    const int n = height(A);
    Tp m        = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot][i][1] != 0) break;
        if (pivot == n) continue;
        if (pivot != i) {
            A[pivot].swap(A[i]);
            m = -m;
        }
        m *= A[i][i][1];
        const auto iv = A[i][i][1].inv();
        for (int j = 0; j < n; ++j) A[i][j][0] *= iv, A[i][j][1] *= iv;
        for (int j = 0; j < i; ++j) sub(A[j], A[i], A[j][i][1], n);
        for (int j = i + 1; j < n; ++j) sub(A[j], A[i], A[j][i][1], n);
    }
    // now set A = A0 + xA1, then A1 is an upper triangular matrix
    int t = 0;
    for (; t <= n; ++t) {
        int s = 0;
        for (; s < n; ++s)
            if (std::all_of(A[s].begin(), A[s].end(), [](const auto &a) { return a[1] == 0; }))
                break;
        if (s == n) break;
        for (int i = 0; i < n; ++i) A[s][i][1] = std::exchange(A[s][i][0], Tp(0));
        for (int i = 0; i < s; ++i) sub(A[s], A[i], A[s][i][1], n);
        for (int i = s + 1; i < n; ++i) sub(A[s], A[i], A[s][i][1], n);
        if (A[s][s][1] != 0) {
            m *= A[s][s][1];
            const auto iv = A[s][s][1].inv();
            for (int j = 0; j < n; ++j) A[s][j][0] *= iv, A[s][j][1] *= iv;
            for (int i = 0; i < s; ++i) sub(A[i], A[s], A[i][s][1], n);
            for (int i = s + 1; i < n; ++i) sub(A[i], A[s], A[i][s][1], n);
        }
    }
    if (t > n) return {};
    Matrix<Tp> AA(n, std::vector<Tp>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) AA[i][j] = -A[i][j][0];
    auto res = charpoly(AA);
    res.erase(res.begin(), res.begin() + t);
    for (int i = 0; i < (int)res.size(); ++i) res[i] *= m;
    return res;
}
