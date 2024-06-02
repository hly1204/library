#pragma once

#include <cassert>
#include <optional>
#include <vector>

template <typename Tp>
using Matrix = std::vector<std::vector<Tp>>;

template <typename Tp>
inline int width(const Matrix<Tp> &A) {
    return A.empty() ? 0 : (int)A[0].size();
}

template <typename Tp>
inline int height(const Matrix<Tp> &A) {
    return A.size();
}

template <typename Tp>
inline bool is_square_matrix(const Matrix<Tp> &A) {
    return width(A) == height(A);
}

template <typename Tp>
inline Matrix<Tp> transpose(const Matrix<Tp> &A) {
    const int w = width(A);
    const int h = height(A);
    Matrix<Tp> TA(w, std::vector<Tp>(h));
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) TA[j][i] = A[i][j];
    return TA;
}

template <typename Tp>
inline std::vector<Tp> apply(const Matrix<Tp> &A, const std::vector<Tp> &b) {
    const int w = width(A);
    const int h = height(A);
    assert((int)b.size() == w);
    std::vector<Tp> Ab(h);
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) Ab[i] += A[i][j] * b[j];
    return Ab;
}

template <typename Tp>
inline Matrix<Tp> mat_mul(const Matrix<Tp> &A, const Matrix<Tp> &B) {
    const int wA = width(A);
    const int hA = height(A);
    assert(height(B) == wA);
    const int wB = width(B);
    Matrix<Tp> res(hA, std::vector<Tp>(wB));
    for (int i = 0; i < hA; ++i)
        for (int k = 0; k < wA; ++k)
            for (int j = 0; j < wB; ++j) res[i][j] += A[i][k] * B[k][j];
    return res;
}

template <typename Tp>
inline std::optional<Matrix<Tp>> mat_inv(Matrix<Tp> A) {
    assert(is_square_matrix(A));
    const int n = height(A);
    for (int i = 0; i < n; ++i) {
        A[i].resize(n * 2);
        A[i][n + i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot][i] != 0) break;
        if (pivot == n) return {};
        if (pivot != i) A[pivot].swap(A[i]);
        if (A[i][i] != 1) {
            const auto iv = A[i][i].inv();
            for (int j = i; j < n * 2; ++j) A[i][j] *= iv;
        }
        for (int j = i + 1; j < n; ++j) {
            const auto p = A[j][i];
            if (p == 0) continue;
            for (int k = i + 1; k < n * 2; ++k) A[j][k] -= p * A[i][k];
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = i; j >= 0; --j) {
            const auto p = A[j][i + 1];
            if (p == 0) continue;
            for (int k = n; k < n * 2; ++k) A[j][k] -= p * A[i + 1][k];
        }
    }
    for (int i = 0; i < n; ++i) A[i].erase(A[i].begin(), A[i].begin() + n);
    return A;
}

template <typename Tp>
inline Matrix<Tp> to_upper_hessenberg(Matrix<Tp> A) {
    assert(is_square_matrix(A));
    const int n = height(A);
    for (int i = 0; i < n - 1; ++i) {
        int pivot = i + 1;
        for (; pivot < n; ++pivot)
            if (A[pivot][i] != 0) break;
        if (pivot == n) continue;
        if (pivot != i + 1) {
            A[pivot].swap(A[i + 1]);
            for (int j = 0; j < n; ++j) std::swap(A[j][pivot], A[j][i + 1]);
        }
        const auto iv = A[i + 1][i].inv();
        for (int j = i + 2; j < n; ++j) {
            if (A[j][i] == 0) continue;
            const auto v = A[j][i] * iv;
            for (int k = i; k < n; ++k) A[j][k] -= v * A[i + 1][k];
            for (int k = 0; k < n; ++k) A[k][i + 1] += v * A[k][j];
        }
    }
    return A;
}

template <typename Tp>
inline std::vector<Tp> charpoly(const Matrix<Tp> &A) {
    const auto H = to_upper_hessenberg(A);
    const int n  = height(A);
    std::vector<std::vector<Tp>> P(n + 1);
    P[0] = {1};
    for (int i = 1; i <= n; ++i) {
        P[i].resize(i + 1);
        for (int j = 0; j < i; ++j)
            P[i][j] -= H[i - 1][i - 1] * P[i - 1][j], P[i][j + 1] += P[i - 1][j];
        Tp t = 1;
        for (int j = 1; j < i; ++j) {
            t *= H[i - j][i - j - 1];
            const auto prod = t * H[i - j - 1][i - 1];
            if (prod == 0) continue;
            for (int k = 0; k < i - j; ++k) P[i][k] -= prod * P[i - j - 1][k];
        }
    }
    return P[n];
}
