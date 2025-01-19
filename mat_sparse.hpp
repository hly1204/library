#pragma once

#include "poly.hpp"
#include "random.hpp"
#include <cassert>
#include <tuple>
#include <vector>

template<typename Tp> using SparseMatrix = std::vector<std::tuple<int, int, Tp>>;

template<typename Tp>
inline std::vector<Tp> mat_apply(const SparseMatrix<Tp> &A, const std::vector<Tp> &b) {
    const int n = b.size();
    std::vector<Tp> Ab(n);
    for (auto &&[x, y, z] : A) Ab[x] += z * b[y];
    return Ab;
}

template<typename Tp> inline std::vector<Tp> minpoly(const SparseMatrix<Tp> &A, int n) {
    const auto u = random_vector<Tp>(n);
    auto v       = random_vector<Tp>(n);
    // u^T A^([0..2n)) v
    std::vector<Tp> proj(n * 2);
    for (int i = 0; i < n * 2; v = mat_apply(A, v), ++i)
        for (int j = 0; j < n; ++j) proj[i] += u[j] * v[j];
    const auto [P, Q] = rational_reconstruction(proj);
    assert(Q.deg() <= n);
    return Q.monic();
}

template<typename Tp> inline Tp det(SparseMatrix<Tp> A, int n) {
    const auto D = random_vector_without_zero<Tp>(n);
    Tp detD      = 1;
    for (int i = 0; i < n; ++i) detD *= D[i];
    // preconditioner D = diag(D[0], ..., D[n-1])
    for (auto &&[x, y, z] : A) z *= D[x];
    return Tp((n & 1) ? -1 : 1) * minpoly(A, n).at(0) / detD;
}
