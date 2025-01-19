#pragma once

#include "mat_basic.hpp"
#include <cassert>
#include <optional>
#include <vector>

template<typename Tp> class Basis {
public:
    const int Dim;
    Matrix<Tp> Vectors; // v_0, v_1, ...
    Matrix<Tp> Augmented;
    Matrix<Tp> Reduced; // upper triangular matrix, diagonal of Reduced = (1,...,1)
    // Augmented * Vectors = Reduced

    explicit Basis(int dim) : Dim(dim), Augmented(dim), Reduced(dim) {}

    int size() const { return Vectors.size(); }
    int dim() const { return Dim; }

    // if V is linear combination of v_0, ..., v_(k-1) then
    // returns coefficients (a_0, ..., a_(k-1)) s.t. -(a_0v_0 + ... + a_(k-1)v_(k-1)) = V
    std::optional<std::vector<Tp>> insert(const std::vector<Tp> &V) {
        std::vector<Tp> Aug(dim()), RV = V;
        for (int i = 0; i < dim(); ++i) {
            if (RV[i] == 0) continue;
            if (Reduced[i].empty()) {
                Aug[size()]    = 1;
                const auto inv = RV[i].inv();
                for (int j = i; j < dim(); ++j) RV[j] *= inv;
                for (int j = 0; j < dim(); ++j) Aug[j] *= inv;
                Augmented[i] = Aug, Reduced[i] = RV, Vectors.push_back(V);
                return {};
            }
            const auto v = RV[i];
            for (int j = i; j < dim(); ++j) RV[j] -= v * Reduced[i][j];
            for (int j = 0; j < dim(); ++j) Aug[j] -= v * Augmented[i][j];
        }
        return Aug;
    }

    // returns A s.t. A^(-1)MA is the linear transform respect to the basis
    Matrix<Tp> transition_matrix() const {
        assert(size() == dim());
        return transpose(Vectors);
    }

    // returns A^(-1) s.t. A^(-1)MA is the linear transform respect to the basis
    Matrix<Tp> inv_transition_matrix() const {
        assert(size() == dim());
        auto res = Augmented;
        for (int i = dim() - 1; i > 0; --i)
            for (int j = i - 1; j >= 0; --j)
                for (int k = 0; k < dim(); ++k) res[j][k] -= Reduced[j][i] * res[i][k];
        return transpose(res);
    }
};
