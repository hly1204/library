#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

template<typename Tp> class Matrix : public std::vector<std::vector<Tp>> {
public:
    using std::vector<std::vector<Tp>>::vector;

    friend std::istream &operator>>(std::istream &a, Matrix &b) {
        const int w = b.width();
        const int h = b.height();
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) a >> b[i][j];
        return a;
    }

    int width() const { return this->empty() ? 0 : (*this)[0].size(); }
    int height() const { return this->size(); }
    bool is_square() const { return width() == height(); }

    Matrix transpose() const {
        const int w = width();
        const int h = height();
        Matrix<Tp> TA(w, std::vector<Tp>(h));
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) TA[j][i] = (*this)[i][j];
        return TA;
    }

    std::vector<Tp> apply(const std::vector<Tp> &b) const {
        const int w = width();
        const int h = height();
        assert((int)b.size() == w);
        std::vector<Tp> Ab(h);
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) Ab[i] += (*this)[i][j] * b[j];
        return Ab;
    }

    Matrix operator-() const {
        Matrix A    = *this;
        const int w = A.width();
        const int h = A.height();
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) A[i][j] = -A[i][j];
        return A;
    }

    Matrix &operator+=(const Matrix<Tp> &B) {
        const int w = width();
        const int h = height();
        assert(w == B.width());
        assert(h == B.height());
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) (*this)[i][j] += B[i][j];
        return *this;
    }

    Matrix &operator-=(const Matrix<Tp> &B) {
        const int w = width();
        const int h = height();
        assert(w == B.width());
        assert(h == B.height());
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) (*this)[i][j] -= B[i][j];
        return *this;
    }

    Matrix operator+(const Matrix<Tp> &B) { return Matrix(*this) += B; }
    Matrix operator-(const Matrix<Tp> &B) { return Matrix(*this) -= B; }

    Matrix &operator*=(const Tp &b) {
        const int w = width();
        const int h = height();
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) (*this)[i][j] *= b;
        return *this;
    }

    Matrix operator*(const Matrix<Tp> &B) const {
        const int wA = width();
        const int hA = height();
        assert(B.height() == wA);
        const int wB = B.width();
        Matrix<Tp> AB(hA, std::vector<Tp>(wB));
        for (int i = 0; i < hA; ++i)
            for (int k = 0; k < wA; ++k)
                for (int j = 0; j < wB; ++j) AB[i][j] += (*this)[i][k] * B[k][j];
        return AB;
    }

    Matrix &operator*=(const Matrix<Tp> &B) { return *this = (*this) * B; }

    Tp det() const {
        assert(is_square());
        Matrix A    = *this;
        const int n = A.height();
        Tp d        = 1;
        for (int i = 0; i < n; ++i) {
            int pivot = i;
            for (; pivot < n; ++pivot)
                if (A[pivot][i] != 0) break;
            if (pivot == n) return 0;
            if (pivot != i) {
                A[pivot].swap(A[i]);
                d = -d;
            }
            d *= A[i][i];
            const auto iv = A[i][i].inv();
            for (int j = i + 1; j < n; ++j) {
                const auto p = A[j][i] * iv;
                if (p == 0) continue;
                for (int k = i; k < n; ++k) A[j][k] -= p * A[i][k];
            }
        }
        return d;
    }

    std::optional<Matrix<Tp>> inv() const {
        assert(is_square());
        Matrix A    = *this;
        const int n = A.height();
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
        for (int i = n - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                const auto p = A[j][i];
                if (p == 0) continue;
                for (int k = n; k < n * 2; ++k) A[j][k] -= p * A[i][k];
            }
        }
        for (int i = 0; i < n; ++i) A[i].erase(A[i].begin(), A[i].begin() + n);
        return A;
    }

    Matrix to_upper_hessenberg() const {
        assert(is_square());
        Matrix A    = *this;
        const int n = A.height();
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

    // returns det(xI - A)
    std::vector<Tp> charpoly() const {
        const auto H = to_upper_hessenberg();
        const int n  = H.height();
        std::vector<std::vector<Tp>> P(n + 1);
        P[0] = {Tp(1)};
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

    // randomized algorithm based on Elegia's trick
    // defined in basis.hpp
    inline std::vector<Tp> minpoly() const;

    // To find A^k(i, j) for large k, the O.G.F. of A^[0, inf)(i, j) is rational,
    // so we could apply Berlekamp--Massey's algorithm to e_i^T * A[0, n*2) * e_j.
};
