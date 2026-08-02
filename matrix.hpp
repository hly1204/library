#pragma once

#include <algorithm>
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

    friend std::ostream &operator<<(std::ostream &a, const Matrix &b) {
        const int w = b.width();
        const int h = b.height();
        for (int i = 0; i < h; ++i) {
            if (i) a << '\n';
            for (int j = 0; j < w; ++j) {
                if (j) a << ' ';
                a << b[i][j];
            }
        }
        return a;
    }

    int width() const { return this->empty() ? 0 : (*this)[0].size(); }
    int height() const { return this->size(); }
    bool is_square() const { return width() == height(); }

    static Matrix identity(int n) {
        Matrix A(n, std::vector<Tp>(n));
        for (int i = 0; i < n; ++i) A[i][i] = 1;
        return A;
    }

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
    Matrix operator*(const Tp &b) { return Matrix(*this) *= b; }

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

    // returns B s.t. B = X*A in reduced row echelon form.
    Matrix gauss(std::vector<int> *pivot_seq = nullptr, Matrix *X = nullptr) const {
        Matrix B    = *this;
        const int m = B.height();
        const int n = B.width();
        if (X) *X = identity(m);
        for (int i = 0, r = -1 /* r = rank-1 */; i < n; ++i) {
            int pivot = r + 1;
            for (; pivot < m; ++pivot)
                if (B[pivot][i] != 0) break;
            if (pivot == m) continue;
            if (pivot != ++r) {
                B[pivot].swap(B[r]);
                if (X) (*X)[pivot].swap((*X)[r]);
            }
            if (pivot_seq) pivot_seq->push_back(i);
            if (B[r][i] != 1) {
                const auto iv = B[r][i].inv();
                for (int j = i; j < n; ++j) B[r][j] *= iv;
                if (X)
                    for (int j = 0; j < m; ++j) (*X)[r][j] *= iv;
            }
            for (int j = 0; j < m; ++j)
                if (j != r) {
                    const auto p = B[j][i];
                    if (p == 0) continue;
                    for (int k = i; k < n; ++k) B[j][k] -= p * B[r][k];
                    if (X)
                        for (int k = 0; k < m; ++k) (*X)[j][k] -= p * (*X)[r][k];
                }
        }
        return B;
    }

    Tp tr() const {
        assert(is_square());
        Tp s;
        for (int i = 0; i < height(); ++i) s += (*this)[i][i];
        return s;
    }

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

    int rank() const {
        std::vector<int> p;
        std::ignore = gauss(&p);
        return (int)p.size();
    }

    std::optional<Matrix<Tp>> inv() const {
        assert(is_square());
        std::vector<int> p;
        Matrix X;
        std::ignore = gauss(&p, &X);
        if ((int)p.size() < height()) return {};
        return X;
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

    Matrix adj() const {
        // We could reduce the constant factor by using a special Gaussian elimination procedure.
        assert(is_square());
        const int n = height();
        std::vector<int> p;
        Matrix L /* inv or basis of left kernel */, B = gauss(&p, &L);
        // A adj(A) = adj(A) A = det(A) I
        if ((int)p.size() == n) return L * det();
        if ((int)p.size() == n - 1) {
            L.erase(L.begin(), L.begin() + (n - 1));
            Matrix R(n, std::vector<Tp>(1)); // basis of right kernel
            int free = 0; // free column (column without pivot)
            while (free < (int)p.size() /* in case A = [0] */ && p[free] == free) ++free;
            // Read from rref
            for (int i = 0; i < n; ++i) R[i][0] = i != free ? -B[i][free] : Tp(1);
            // A adj(A) = adj(A) A = 0 => adj(A) = alpha R L
            Matrix RL = R * L;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    // find alpha by finding any non-zero entry of RL
                    if (RL[i][j] != 0) {
                        Matrix A = *this;
                        for (int k = 0; k < n; ++k) A[k].erase(A[k].begin() + i);
                        A.erase(A.begin() + j);
                        RL *= A.det() / RL[i][j];
                        if ((i + j) & 1) RL = -RL;
                        break;
                    }
            return RL;
        }
        return Matrix(n, std::vector<Tp>(n));
    }

    // randomized algorithm based on Elegia's trick
    // defined in basis.hpp
    inline std::vector<Tp> minpoly() const;

    // To find A^k(i, j) for large k, the O.G.F. of A^[0, inf)(i, j) is rational,
    // so we could apply Berlekamp--Massey's algorithm to e_i^T * A^[0, n*2) * e_j.
};
