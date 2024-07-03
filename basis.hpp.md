---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mat_basic.hpp
    title: mat_basic.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: frobenius.hpp
    title: frobenius.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.1.test.cpp
    title: test/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/pow_of_matrix.0.test.cpp
    title: test/matrix/pow_of_matrix.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"basis.hpp\"\n\n#line 2 \"mat_basic.hpp\"\n\n#include <cassert>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\nusing Matrix = std::vector<std::vector<Tp>>;\n\ntemplate <typename Tp>\n\
    inline int width(const Matrix<Tp> &A) {\n    return A.empty() ? 0 : (int)A[0].size();\n\
    }\n\ntemplate <typename Tp>\ninline int height(const Matrix<Tp> &A) {\n    return\
    \ A.size();\n}\n\ntemplate <typename Tp>\ninline bool is_square_matrix(const Matrix<Tp>\
    \ &A) {\n    return width(A) == height(A);\n}\n\ntemplate <typename Tp>\ninline\
    \ Matrix<Tp> transpose(const Matrix<Tp> &A) {\n    const int w = width(A);\n \
    \   const int h = height(A);\n    Matrix<Tp> TA(w, std::vector<Tp>(h));\n    for\
    \ (int i = 0; i < h; ++i)\n        for (int j = 0; j < w; ++j) TA[j][i] = A[i][j];\n\
    \    return TA;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> mat_apply(const\
    \ Matrix<Tp> &A, const std::vector<Tp> &b) {\n    const int w = width(A);\n  \
    \  const int h = height(A);\n    assert((int)b.size() == w);\n    std::vector<Tp>\
    \ Ab(h);\n    for (int i = 0; i < h; ++i)\n        for (int j = 0; j < w; ++j)\
    \ Ab[i] += A[i][j] * b[j];\n    return Ab;\n}\n\ntemplate <typename Tp>\ninline\
    \ Matrix<Tp> mat_mul(const Matrix<Tp> &A, const Matrix<Tp> &B) {\n    const int\
    \ wA = width(A);\n    const int hA = height(A);\n    assert(height(B) == wA);\n\
    \    const int wB = width(B);\n    Matrix<Tp> res(hA, std::vector<Tp>(wB));\n\
    \    for (int i = 0; i < hA; ++i)\n        for (int k = 0; k < wA; ++k)\n    \
    \        for (int j = 0; j < wB; ++j) res[i][j] += A[i][k] * B[k][j];\n    return\
    \ res;\n}\n\ntemplate <typename Tp>\ninline std::optional<Matrix<Tp>> mat_inv(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    for\
    \ (int i = 0; i < n; ++i) {\n        A[i].resize(n * 2);\n        A[i][n + i]\
    \ = 1;\n    }\n    for (int i = 0; i < n; ++i) {\n        int pivot = i;\n   \
    \     for (; pivot < n; ++pivot)\n            if (A[pivot][i] != 0) break;\n \
    \       if (pivot == n) return {};\n        if (pivot != i) A[pivot].swap(A[i]);\n\
    \        if (A[i][i] != 1) {\n            const auto iv = A[i][i].inv();\n   \
    \         for (int j = i; j < n * 2; ++j) A[i][j] *= iv;\n        }\n        for\
    \ (int j = i + 1; j < n; ++j) {\n            const auto p = A[j][i];\n       \
    \     if (p == 0) continue;\n            for (int k = i + 1; k < n * 2; ++k) A[j][k]\
    \ -= p * A[i][k];\n        }\n    }\n    for (int i = n - 1; i > 0; --i) {\n \
    \       for (int j = i - 1; j >= 0; --j) {\n            const auto p = A[j][i];\n\
    \            if (p == 0) continue;\n            for (int k = n; k < n * 2; ++k)\
    \ A[j][k] -= p * A[i][k];\n        }\n    }\n    for (int i = 0; i < n; ++i) A[i].erase(A[i].begin(),\
    \ A[i].begin() + n);\n    return A;\n}\n\ntemplate <typename Tp>\ninline Tp det(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    Tp\
    \ det      = 1;\n    bool neg    = false;\n    for (int i = 0; i < n; ++i) {\n\
    \        int pivot = i;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i]\
    \ != 0) break;\n        if (pivot == n) return 0;\n        if (pivot != i) {\n\
    \            A[pivot].swap(A[i]);\n            neg = !neg;\n        }\n      \
    \  det *= A[i][i];\n        const auto iv = A[i][i].inv();\n        for (int j\
    \ = i + 1; j < n; ++j) {\n            const auto p = A[j][i] * iv;\n         \
    \   if (p == 0) continue;\n            for (int k = i; k < n; ++k) A[j][k] -=\
    \ p * A[i][k];\n        }\n    }\n    return neg ? -det : det;\n}\n\ntemplate\
    \ <typename Tp>\ninline Matrix<Tp> to_upper_hessenberg(Matrix<Tp> A) {\n    assert(is_square_matrix(A));\n\
    \    const int n = height(A);\n    for (int i = 0; i < n - 1; ++i) {\n       \
    \ int pivot = i + 1;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i]\
    \ != 0) break;\n        if (pivot == n) continue;\n        if (pivot != i + 1)\
    \ {\n            A[pivot].swap(A[i + 1]);\n            for (int j = 0; j < n;\
    \ ++j) std::swap(A[j][pivot], A[j][i + 1]);\n        }\n        const auto iv\
    \ = A[i + 1][i].inv();\n        for (int j = i + 2; j < n; ++j) {\n          \
    \  if (A[j][i] == 0) continue;\n            const auto v = A[j][i] * iv;\n   \
    \         for (int k = i; k < n; ++k) A[j][k] -= v * A[i + 1][k];\n          \
    \  for (int k = 0; k < n; ++k) A[k][i + 1] += v * A[k][j];\n        }\n    }\n\
    \    return A;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> charpoly(const\
    \ Matrix<Tp> &A) {\n    const auto H = to_upper_hessenberg(A);\n    const int\
    \ n  = height(A);\n    std::vector<std::vector<Tp>> P(n + 1);\n    P[0] = {Tp(1)};\n\
    \    for (int i = 1; i <= n; ++i) {\n        P[i].resize(i + 1);\n        for\
    \ (int j = 0; j < i; ++j)\n            P[i][j] -= H[i - 1][i - 1] * P[i - 1][j],\
    \ P[i][j + 1] += P[i - 1][j];\n        Tp t = 1;\n        for (int j = 1; j <\
    \ i; ++j) {\n            t *= H[i - j][i - j - 1];\n            const auto prod\
    \ = t * H[i - j - 1][i - 1];\n            if (prod == 0) continue;\n         \
    \   for (int k = 0; k < i - j; ++k) P[i][k] -= prod * P[i - j - 1][k];\n     \
    \   }\n    }\n    return P[n];\n}\n#line 7 \"basis.hpp\"\n\ntemplate <typename\
    \ Tp>\nclass Basis {\npublic:\n    const int Dim;\n    Matrix<Tp> Vectors; //\
    \ v_0, v_1, ...\n    Matrix<Tp> Augmented;\n    Matrix<Tp> Reduced; // upper triangular\
    \ matrix diag(Reduced)=(1,...,1)\n    // Augmented * Vectors = Reduced\n\n   \
    \ explicit Basis(int dim) : Dim(dim), Augmented(dim), Reduced(dim) {}\n\n    int\
    \ size() const { return Vectors.size(); }\n    int dim() const { return Dim; }\n\
    \n    // if V is linear combination of v_0, ..., v_k then\n    // returns coefficients\
    \ (a_0, ..., a_k) s.t. -(a_0v_0 + ... + a_kv_k) = V\n    std::optional<std::vector<Tp>>\
    \ insert(const std::vector<Tp> &V) {\n        std::vector<Tp> Aug(dim()), RV =\
    \ V;\n        for (int i = 0; i < dim(); ++i) {\n            if (RV[i] == 0) continue;\n\
    \            if (Reduced[i].empty()) {\n                Aug[size()]    = 1;\n\
    \                const auto inv = RV[i].inv();\n                for (int j = i;\
    \ j < dim(); ++j) RV[j] *= inv;\n                for (int j = 0; j < dim(); ++j)\
    \ Aug[j] *= inv;\n                Augmented[i] = Aug;\n                Reduced[i]\
    \   = RV;\n                Vectors.push_back(V);\n                return {};\n\
    \            }\n            const auto v = RV[i];\n            for (int j = i;\
    \ j < dim(); ++j) RV[j] -= v * Reduced[i][j];\n            for (int j = 0; j <\
    \ dim(); ++j) Aug[j] -= v * Augmented[i][j];\n        }\n        return Aug;\n\
    \    }\n\n    // returns A s.t. A^(-1)MA is the linear transform respect to the\
    \ basis\n    Matrix<Tp> transition_matrix() const {\n        assert(size() ==\
    \ dim());\n        return transpose(Vectors);\n    }\n\n    // returns A^(-1)\
    \ s.t. A^(-1)MA is the linear transform respect to the basis\n    Matrix<Tp> inv_transition_matrix()\
    \ const {\n        assert(size() == dim());\n        auto res = Augmented;\n \
    \       for (int i = dim() - 1; i > 0; --i)\n            for (int j = i - 1; j\
    \ >= 0; --j)\n                for (int k = 0; k < dim(); ++k) res[j][k] -= Reduced[j][i]\
    \ * res[i][k];\n        return transpose(res);\n    }\n};\n"
  code: "#pragma once\n\n#include \"mat_basic.hpp\"\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\ntemplate <typename Tp>\nclass Basis {\npublic:\n\
    \    const int Dim;\n    Matrix<Tp> Vectors; // v_0, v_1, ...\n    Matrix<Tp>\
    \ Augmented;\n    Matrix<Tp> Reduced; // upper triangular matrix diag(Reduced)=(1,...,1)\n\
    \    // Augmented * Vectors = Reduced\n\n    explicit Basis(int dim) : Dim(dim),\
    \ Augmented(dim), Reduced(dim) {}\n\n    int size() const { return Vectors.size();\
    \ }\n    int dim() const { return Dim; }\n\n    // if V is linear combination\
    \ of v_0, ..., v_k then\n    // returns coefficients (a_0, ..., a_k) s.t. -(a_0v_0\
    \ + ... + a_kv_k) = V\n    std::optional<std::vector<Tp>> insert(const std::vector<Tp>\
    \ &V) {\n        std::vector<Tp> Aug(dim()), RV = V;\n        for (int i = 0;\
    \ i < dim(); ++i) {\n            if (RV[i] == 0) continue;\n            if (Reduced[i].empty())\
    \ {\n                Aug[size()]    = 1;\n                const auto inv = RV[i].inv();\n\
    \                for (int j = i; j < dim(); ++j) RV[j] *= inv;\n             \
    \   for (int j = 0; j < dim(); ++j) Aug[j] *= inv;\n                Augmented[i]\
    \ = Aug;\n                Reduced[i]   = RV;\n                Vectors.push_back(V);\n\
    \                return {};\n            }\n            const auto v = RV[i];\n\
    \            for (int j = i; j < dim(); ++j) RV[j] -= v * Reduced[i][j];\n   \
    \         for (int j = 0; j < dim(); ++j) Aug[j] -= v * Augmented[i][j];\n   \
    \     }\n        return Aug;\n    }\n\n    // returns A s.t. A^(-1)MA is the linear\
    \ transform respect to the basis\n    Matrix<Tp> transition_matrix() const {\n\
    \        assert(size() == dim());\n        return transpose(Vectors);\n    }\n\
    \n    // returns A^(-1) s.t. A^(-1)MA is the linear transform respect to the basis\n\
    \    Matrix<Tp> inv_transition_matrix() const {\n        assert(size() == dim());\n\
    \        auto res = Augmented;\n        for (int i = dim() - 1; i > 0; --i)\n\
    \            for (int j = i - 1; j >= 0; --j)\n                for (int k = 0;\
    \ k < dim(); ++k) res[j][k] -= Reduced[j][i] * res[i][k];\n        return transpose(res);\n\
    \    }\n};\n"
  dependsOn:
  - mat_basic.hpp
  isVerificationFile: false
  path: basis.hpp
  requiredBy:
  - frobenius.hpp
  timestamp: '2024-07-03 19:37:20+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix/characteristic_polynomial.1.test.cpp
  - test/matrix/pow_of_matrix.0.test.cpp
documentation_of: basis.hpp
layout: document
redirect_from:
- /library/basis.hpp
- /library/basis.hpp.html
title: basis.hpp
---
