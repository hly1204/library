---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mat_basic.hpp
    title: mat_basic.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inverse_matrix
    links:
    - https://judge.yosupo.jp/problem/inverse_matrix
  bundledCode: "#line 1 \"test/matrix/inverse_matrix.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/inverse_matrix\"\n\n#line 2 \"mat_basic.hpp\"\
    \n\n#include <cassert>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \ntemplate <typename Tp>\nusing Matrix = std::vector<std::vector<Tp>>;\n\ntemplate\
    \ <typename Tp>\ninline int width(const Matrix<Tp> &A) {\n    return A.empty()\
    \ ? 0 : (int)A[0].size();\n}\n\ntemplate <typename Tp>\ninline int height(const\
    \ Matrix<Tp> &A) {\n    return A.size();\n}\n\ntemplate <typename Tp>\ninline\
    \ bool is_square_matrix(const Matrix<Tp> &A) {\n    return width(A) == height(A);\n\
    }\n\ntemplate <typename Tp>\ninline Matrix<Tp> transpose(const Matrix<Tp> &A)\
    \ {\n    const int w = width(A);\n    const int h = height(A);\n    Matrix<Tp>\
    \ TA(w, std::vector<Tp>(h));\n    for (int i = 0; i < h; ++i)\n        for (int\
    \ j = 0; j < w; ++j) TA[j][i] = A[i][j];\n    return TA;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> apply(const Matrix<Tp> &A, const std::vector<Tp>\
    \ &b) {\n    const int w = width(A);\n    const int h = height(A);\n    assert((int)b.size()\
    \ == w);\n    std::vector<Tp> Ab(h);\n    for (int i = 0; i < h; ++i)\n      \
    \  for (int j = 0; j < w; ++j) Ab[i] += A[i][j] * b[j];\n    return Ab;\n}\n\n\
    template <typename Tp>\ninline Matrix<Tp> mat_mul(const Matrix<Tp> &A, const Matrix<Tp>\
    \ &B) {\n    const int wA = width(A);\n    const int hA = height(A);\n    assert(height(B)\
    \ == wA);\n    const int wB = width(B);\n    Matrix<Tp> res(hA, std::vector<Tp>(wB));\n\
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
    \ -= p * A[i][k];\n        }\n    }\n    for (int i = n - 2; i >= 0; --i) {\n\
    \        for (int j = i; j >= 0; --j) {\n            const auto p = A[j][i + 1];\n\
    \            if (p == 0) continue;\n            for (int k = n; k < n * 2; ++k)\
    \ A[j][k] -= p * A[i + 1][k];\n        }\n    }\n    for (int i = 0; i < n; ++i)\
    \ A[i].erase(A[i].begin(), A[i].begin() + n);\n    return A;\n}\n\ntemplate <typename\
    \ Tp>\ninline Tp det(Matrix<Tp> A) {\n    assert(is_square_matrix(A));\n    const\
    \ int n = height(A);\n    Tp det      = 1;\n    bool neg    = false;\n    for\
    \ (int i = 0; i < n; ++i) {\n        int pivot = i;\n        for (; pivot < n;\
    \ ++pivot)\n            if (A[pivot][i] != 0) break;\n        if (pivot == n)\
    \ return 0;\n        if (pivot != i) {\n            A[pivot].swap(A[i]);\n   \
    \         neg = !neg;\n        }\n        det *= A[i][i];\n        const auto\
    \ iv = A[i][i].inv();\n        for (int j = i + 1; j < n; ++j) {\n           \
    \ const auto p = A[j][i] * iv;\n            if (p == 0) continue;\n          \
    \  for (int k = i; k < n; ++k) A[j][k] -= p * A[i][k];\n        }\n    }\n   \
    \ return neg ? -det : det;\n}\n\ntemplate <typename Tp>\ninline Matrix<Tp> to_upper_hessenberg(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int pivot = i + 1;\n        for (; pivot\
    \ < n; ++pivot)\n            if (A[pivot][i] != 0) break;\n        if (pivot ==\
    \ n) continue;\n        if (pivot != i + 1) {\n            A[pivot].swap(A[i +\
    \ 1]);\n            for (int j = 0; j < n; ++j) std::swap(A[j][pivot], A[j][i\
    \ + 1]);\n        }\n        const auto iv = A[i + 1][i].inv();\n        for (int\
    \ j = i + 2; j < n; ++j) {\n            if (A[j][i] == 0) continue;\n        \
    \    const auto v = A[j][i] * iv;\n            for (int k = i; k < n; ++k) A[j][k]\
    \ -= v * A[i + 1][k];\n            for (int k = 0; k < n; ++k) A[k][i + 1] +=\
    \ v * A[k][j];\n        }\n    }\n    return A;\n}\n\ntemplate <typename Tp>\n\
    inline std::vector<Tp> charpoly(const Matrix<Tp> &A) {\n    const auto H = to_upper_hessenberg(A);\n\
    \    const int n  = height(A);\n    std::vector<std::vector<Tp>> P(n + 1);\n \
    \   P[0] = {1};\n    for (int i = 1; i <= n; ++i) {\n        P[i].resize(i + 1);\n\
    \        for (int j = 0; j < i; ++j)\n            P[i][j] -= H[i - 1][i - 1] *\
    \ P[i - 1][j], P[i][j + 1] += P[i - 1][j];\n        Tp t = 1;\n        for (int\
    \ j = 1; j < i; ++j) {\n            t *= H[i - j][i - j - 1];\n            const\
    \ auto prod = t * H[i - j - 1][i - 1];\n            if (prod == 0) continue;\n\
    \            for (int k = 0; k < i - j; ++k) P[i][k] -= prod * P[i - j - 1][k];\n\
    \        }\n    }\n    return P[n];\n}\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n\
    #include <type_traits>\n\ntemplate <unsigned Mod>\nclass ModInt {\n    static_assert((Mod\
    \ >> 31) == 0, \"`Mod` must less than 2^(31)\");\n    template <typename Int>\n\
    \    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v)\
    \ {\n        using D = std::common_type_t<Int, unsigned>;\n        return (v %=\
    \ (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n    struct PrivateConstructor\
    \ {};\n    static inline PrivateConstructor private_constructor{};\n    ModInt(PrivateConstructor,\
    \ unsigned v) : v_(v) {}\n\n    unsigned v_;\n\npublic:\n    static unsigned mod()\
    \ { return Mod; }\n    static ModInt from_raw(unsigned v) { return ModInt(private_constructor,\
    \ v); }\n    ModInt() : v_() {}\n    template <typename Int, typename std::enable_if_t<std::is_signed_v<Int>,\
    \ int> = 0>\n    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int,\
    \ typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int\
    \ v) : v_(v % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1 <\
    \ 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n    std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const {\n        if (v_ & 1) return from_raw((v_ + Mod) >>\
    \ 1);\n        return from_raw(v_ >> 1);\n    }\n\n    ModInt &operator+=(const\
    \ ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator-=(const ModInt &a) {\n        if ((v_ += Mod - a.v_)\
    \ >= Mod) v_ -= Mod;\n        return *this;\n    }\n    ModInt &operator*=(const\
    \ ModInt &a) {\n        v_ = (unsigned long long)v_ * a.v_ % Mod;\n        return\
    \ *this;\n    }\n    ModInt &operator/=(const ModInt &a) { return *this *= a.inv();\
    \ }\n\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n\
    #line 6 \"test/matrix/inverse_matrix.0.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n\
    \    std::cin >> n;\n    Matrix<mint> A(n, std::vector<mint>(n));\n    for (int\
    \ i = 0; i < n; ++i)\n        for (int j = 0; j < n; ++j) std::cin >> A[i][j];\n\
    \    if (const auto invA = mat_inv(A)) {\n        for (int i = 0; i < n; ++i)\n\
    \            for (int j = 0; j < n; ++j) std::cout << invA->at(i).at(j) << \"\
    \ \\n\"[j == n - 1];\n    } else {\n        std::cout << \"-1\";\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inverse_matrix\"\n\n#include\
    \ \"mat_basic.hpp\"\n#include \"modint.hpp\"\n#include <iostream>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    using\
    \ mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    Matrix<mint>\
    \ A(n, std::vector<mint>(n));\n    for (int i = 0; i < n; ++i)\n        for (int\
    \ j = 0; j < n; ++j) std::cin >> A[i][j];\n    if (const auto invA = mat_inv(A))\
    \ {\n        for (int i = 0; i < n; ++i)\n            for (int j = 0; j < n; ++j)\
    \ std::cout << invA->at(i).at(j) << \" \\n\"[j == n - 1];\n    } else {\n    \
    \    std::cout << \"-1\";\n    }\n    return 0;\n}\n"
  dependsOn:
  - mat_basic.hpp
  - modint.hpp
  isVerificationFile: true
  path: test/matrix/inverse_matrix.0.test.cpp
  requiredBy: []
  timestamp: '2024-06-22 10:58:08+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix/inverse_matrix.0.test.cpp
layout: document
redirect_from:
- /verify/test/matrix/inverse_matrix.0.test.cpp
- /verify/test/matrix/inverse_matrix.0.test.cpp.html
title: test/matrix/inverse_matrix.0.test.cpp
---
