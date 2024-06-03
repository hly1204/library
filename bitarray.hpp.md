---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix_det_mod_2.0.test.cpp
    title: test/matrix_det_mod_2.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"bitarray.hpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <string>\n#include <type_traits>\n#include <vector>\n\nnamespace detail\
    \ {\n\n// |s| = 2^N\n// s[0..2^(N-1)) | s[2^(N-1)..2^N) << 2^(N-1)\ntemplate <int\
    \ N>\ninline unsigned long long from_bit_string(const char *s) {\n    return from_bit_string<N\
    \ / 2>(s + N / 2) << (N / 2) | from_bit_string<N / 2>(s);\n}\n\n// |s| = 2^0\n\
    template <>\ninline unsigned long long from_bit_string<1>(const char *s) {\n \
    \   return s[0] == '1';\n}\n\ntemplate <int N>\ninline void to_bit_string(unsigned\
    \ long long v, char *s) {\n    to_bit_string<N / 2>(v, s);\n    to_bit_string<N\
    \ / 2>(v >> (N / 2), s + N / 2);\n}\n\ntemplate <>\ninline void to_bit_string<1>(unsigned\
    \ long long v, char *s) {\n    s[0] = ((v & 1) + '0');\n}\n\n} // namespace detail\n\
    \n// TODO: operator<< operator>> ...\nclass BitArray {\npublic:\n    using ULL\
    \                          = unsigned long long;\n    static constexpr std::size_t\
    \ WIDTH = sizeof(ULL) * 8;\n    std::vector<ULL> D;\n    std::size_t S;\n\n  \
    \  BitArray() : S() {}\n    explicit BitArray(std::size_t L) : D(get_size(L)),\
    \ S(L) {}\n    explicit BitArray(std::string s) : D(get_size(s.size())), S(s.size())\
    \ {\n        s.resize(get_size(S) * WIDTH);\n        for (std::size_t i = 0; i\
    \ < s.size(); i += WIDTH)\n            D[i / WIDTH] = detail::from_bit_string<WIDTH>(s.data()\
    \ + i);\n    }\n\n    void swap(BitArray &other) {\n        D.swap(other.D);\n\
    \        std::swap(S, other.S);\n    }\n\nprivate:\n    static std::size_t get_size(std::size_t\
    \ L) {\n        if (L == 0) return 0;\n        return (L - 1) / WIDTH + 1;\n \
    \   }\n\npublic:\n    [[nodiscard]] std::size_t size() const { return S; }\n \
    \   [[nodiscard]] std::make_signed_t<std::size_t> ssize() const { return S; }\n\
    \n    void resize(std::size_t L, bool v = false) {\n        D.resize(get_size(L));\n\
    \        if (L > S) {\n            if (v) {\n                if (const std::size_t\
    \ SS = get_size(S)) D[SS - 1] |= ~((1ULL << (S % WIDTH)) - 1);\n             \
    \   for (std::size_t i = get_size(S); i < D.size(); ++i) D[i] = ~0ULL;\n     \
    \       } else {\n                if (const std::size_t SS = get_size(S)) D[SS\
    \ - 1] &= (1ULL << (S % WIDTH)) - 1;\n                for (std::size_t i = get_size(S);\
    \ i < D.size(); ++i) D[i] = 0ULL;\n            }\n        }\n        S = L;\n\
    \    }\n\n    void clear() {\n        D.clear();\n        S = 0;\n    }\n\n  \
    \  void assign(std::size_t L, bool v) { D.assign(get_size(L), v ? ~0ULL : 0ULL);\
    \ }\n\n    BitArray &set() {\n        for (std::size_t i = 0; i < D.size(); ++i)\
    \ D[i] = ~0ULL;\n        return *this;\n    }\n\n    BitArray &set(std::size_t\
    \ P, bool v = true) {\n        if (v) {\n            D[P / WIDTH] |= 1ULL << (P\
    \ % WIDTH);\n        } else {\n            D[P / WIDTH] &= ~(1ULL << (P % WIDTH));\n\
    \        }\n        return *this;\n    }\n\n    BitArray &reset() {\n        for\
    \ (std::size_t i = 0; i < D.size(); ++i) D[i] = 0ULL;\n        return *this;\n\
    \    }\n\n    BitArray &reset(std::size_t P) {\n        D[P / WIDTH] &= ~(1ULL\
    \ << (P % WIDTH));\n        return *this;\n    }\n\n    BitArray &flip() {\n \
    \       for (std::size_t i = 0; i < D.size(); ++i) D[i] = ~D[i];\n        return\
    \ *this;\n    }\n\n    BitArray &flip(std::size_t P) {\n        D[P / WIDTH] ^=\
    \ 1ULL << (P % WIDTH);\n        return *this;\n    }\n\n    [[nodiscard]] bool\
    \ test(std::size_t P) const { return D[P / WIDTH] >> (P % WIDTH) & 1; }\n\n  \
    \  [[nodiscard]] bool all() const {\n        if (S == 0) return true;\n      \
    \  if (D.size() > 1) {\n            for (std::size_t i = 0; i < D.size() - 1;\
    \ ++i)\n                if (~D[i] != 0) return false;\n        }\n        return\
    \ (~D.back() & ((1ULL << (S % WIDTH)) - 1)) == 0;\n    }\n    [[nodiscard]] bool\
    \ any() const {\n        if (S == 0) return true;\n        if (D.size() > 1) {\n\
    \            for (std::size_t i = 0; i < D.size() - 1; ++i)\n                if\
    \ (D[i] != 0) return true;\n        }\n        return (D.back() & ((1ULL << (S\
    \ % WIDTH)) - 1)) != 0;\n    }\n    [[nodiscard]] bool none() const {\n      \
    \  if (S == 0) return true;\n        return !any();\n    }\n\n    class Proxy\
    \ {\n        friend BitArray;\n        std::vector<ULL>::iterator I;\n       \
    \ unsigned O;\n\n        Proxy(std::vector<ULL>::iterator I, unsigned O) : I(I),\
    \ O(O) {}\n\n    public:\n        Proxy &operator=(bool v) {\n            v ?\
    \ (*I |= 1ULL << O) : (*I &= ~(1ULL << O));\n            return *this;\n     \
    \   }\n        operator bool() const { return *I & (1ULL << O); }\n    };\n\n\
    \    class ConstProxy {\n        friend BitArray;\n        std::vector<ULL>::const_iterator\
    \ I;\n        unsigned O;\n\n        ConstProxy(std::vector<ULL>::const_iterator\
    \ I, unsigned O) : I(I), O(O) {}\n\n    public:\n        ConstProxy(const Proxy\
    \ &P) : I(P.I), O(P.O) {}\n        operator bool() const { return *I & (1ULL <<\
    \ O); }\n    };\n\n    [[nodiscard]] Proxy operator[](std::size_t P) {\n     \
    \   return Proxy(D.begin() + P / WIDTH, P % WIDTH);\n    }\n    [[nodiscard]]\
    \ Proxy at(std::size_t P) {\n        assert(P < S);\n        return operator[](P);\n\
    \    }\n\n    [[nodiscard]] ConstProxy operator[](std::size_t P) const {\n   \
    \     return ConstProxy(D.begin() + P / WIDTH, P % WIDTH);\n    }\n    [[nodiscard]]\
    \ ConstProxy at(std::size_t P) const {\n        assert(P < S);\n        return\
    \ operator[](P);\n    }\n\n    BitArray &operator&=(const BitArray &R) {\n   \
    \     assert(S == R.S);\n        for (std::size_t i = 0; i < D.size(); ++i) D[i]\
    \ &= R.D[i];\n        return *this;\n    }\n\n    BitArray &operator|=(const BitArray\
    \ &R) {\n        assert(S == R.S);\n        for (std::size_t i = 0; i < D.size();\
    \ ++i) D[i] |= R.D[i];\n        return *this;\n    }\n\n    BitArray &operator^=(const\
    \ BitArray &R) {\n        assert(S == R.S);\n        for (std::size_t i = 0; i\
    \ < D.size(); ++i) D[i] ^= R.D[i];\n        return *this;\n    }\n\n    [[nodiscard]]\
    \ std::string to_string() const {\n        std::string res(D.size() * WIDTH, 0);\n\
    \        char *d = res.data();\n        for (std::size_t i = 0; i < D.size();\
    \ ++i)\n            detail::to_bit_string<WIDTH>(D[i], d + i * WIDTH);\n     \
    \   res.resize(S);\n        return res;\n    }\n\n    friend BitArray operator&(const\
    \ BitArray &L, const BitArray &R) { return BitArray(L) &= R; }\n    friend BitArray\
    \ operator|(const BitArray &L, const BitArray &R) { return BitArray(L) |= R; }\n\
    \    friend BitArray operator^(const BitArray &L, const BitArray &R) { return\
    \ BitArray(L) ^= R; }\n};\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cstddef>\n#include <string>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace detail {\n\n// |s| = 2^N\n\
    // s[0..2^(N-1)) | s[2^(N-1)..2^N) << 2^(N-1)\ntemplate <int N>\ninline unsigned\
    \ long long from_bit_string(const char *s) {\n    return from_bit_string<N / 2>(s\
    \ + N / 2) << (N / 2) | from_bit_string<N / 2>(s);\n}\n\n// |s| = 2^0\ntemplate\
    \ <>\ninline unsigned long long from_bit_string<1>(const char *s) {\n    return\
    \ s[0] == '1';\n}\n\ntemplate <int N>\ninline void to_bit_string(unsigned long\
    \ long v, char *s) {\n    to_bit_string<N / 2>(v, s);\n    to_bit_string<N / 2>(v\
    \ >> (N / 2), s + N / 2);\n}\n\ntemplate <>\ninline void to_bit_string<1>(unsigned\
    \ long long v, char *s) {\n    s[0] = ((v & 1) + '0');\n}\n\n} // namespace detail\n\
    \n// TODO: operator<< operator>> ...\nclass BitArray {\npublic:\n    using ULL\
    \                          = unsigned long long;\n    static constexpr std::size_t\
    \ WIDTH = sizeof(ULL) * 8;\n    std::vector<ULL> D;\n    std::size_t S;\n\n  \
    \  BitArray() : S() {}\n    explicit BitArray(std::size_t L) : D(get_size(L)),\
    \ S(L) {}\n    explicit BitArray(std::string s) : D(get_size(s.size())), S(s.size())\
    \ {\n        s.resize(get_size(S) * WIDTH);\n        for (std::size_t i = 0; i\
    \ < s.size(); i += WIDTH)\n            D[i / WIDTH] = detail::from_bit_string<WIDTH>(s.data()\
    \ + i);\n    }\n\n    void swap(BitArray &other) {\n        D.swap(other.D);\n\
    \        std::swap(S, other.S);\n    }\n\nprivate:\n    static std::size_t get_size(std::size_t\
    \ L) {\n        if (L == 0) return 0;\n        return (L - 1) / WIDTH + 1;\n \
    \   }\n\npublic:\n    [[nodiscard]] std::size_t size() const { return S; }\n \
    \   [[nodiscard]] std::make_signed_t<std::size_t> ssize() const { return S; }\n\
    \n    void resize(std::size_t L, bool v = false) {\n        D.resize(get_size(L));\n\
    \        if (L > S) {\n            if (v) {\n                if (const std::size_t\
    \ SS = get_size(S)) D[SS - 1] |= ~((1ULL << (S % WIDTH)) - 1);\n             \
    \   for (std::size_t i = get_size(S); i < D.size(); ++i) D[i] = ~0ULL;\n     \
    \       } else {\n                if (const std::size_t SS = get_size(S)) D[SS\
    \ - 1] &= (1ULL << (S % WIDTH)) - 1;\n                for (std::size_t i = get_size(S);\
    \ i < D.size(); ++i) D[i] = 0ULL;\n            }\n        }\n        S = L;\n\
    \    }\n\n    void clear() {\n        D.clear();\n        S = 0;\n    }\n\n  \
    \  void assign(std::size_t L, bool v) { D.assign(get_size(L), v ? ~0ULL : 0ULL);\
    \ }\n\n    BitArray &set() {\n        for (std::size_t i = 0; i < D.size(); ++i)\
    \ D[i] = ~0ULL;\n        return *this;\n    }\n\n    BitArray &set(std::size_t\
    \ P, bool v = true) {\n        if (v) {\n            D[P / WIDTH] |= 1ULL << (P\
    \ % WIDTH);\n        } else {\n            D[P / WIDTH] &= ~(1ULL << (P % WIDTH));\n\
    \        }\n        return *this;\n    }\n\n    BitArray &reset() {\n        for\
    \ (std::size_t i = 0; i < D.size(); ++i) D[i] = 0ULL;\n        return *this;\n\
    \    }\n\n    BitArray &reset(std::size_t P) {\n        D[P / WIDTH] &= ~(1ULL\
    \ << (P % WIDTH));\n        return *this;\n    }\n\n    BitArray &flip() {\n \
    \       for (std::size_t i = 0; i < D.size(); ++i) D[i] = ~D[i];\n        return\
    \ *this;\n    }\n\n    BitArray &flip(std::size_t P) {\n        D[P / WIDTH] ^=\
    \ 1ULL << (P % WIDTH);\n        return *this;\n    }\n\n    [[nodiscard]] bool\
    \ test(std::size_t P) const { return D[P / WIDTH] >> (P % WIDTH) & 1; }\n\n  \
    \  [[nodiscard]] bool all() const {\n        if (S == 0) return true;\n      \
    \  if (D.size() > 1) {\n            for (std::size_t i = 0; i < D.size() - 1;\
    \ ++i)\n                if (~D[i] != 0) return false;\n        }\n        return\
    \ (~D.back() & ((1ULL << (S % WIDTH)) - 1)) == 0;\n    }\n    [[nodiscard]] bool\
    \ any() const {\n        if (S == 0) return true;\n        if (D.size() > 1) {\n\
    \            for (std::size_t i = 0; i < D.size() - 1; ++i)\n                if\
    \ (D[i] != 0) return true;\n        }\n        return (D.back() & ((1ULL << (S\
    \ % WIDTH)) - 1)) != 0;\n    }\n    [[nodiscard]] bool none() const {\n      \
    \  if (S == 0) return true;\n        return !any();\n    }\n\n    class Proxy\
    \ {\n        friend BitArray;\n        std::vector<ULL>::iterator I;\n       \
    \ unsigned O;\n\n        Proxy(std::vector<ULL>::iterator I, unsigned O) : I(I),\
    \ O(O) {}\n\n    public:\n        Proxy &operator=(bool v) {\n            v ?\
    \ (*I |= 1ULL << O) : (*I &= ~(1ULL << O));\n            return *this;\n     \
    \   }\n        operator bool() const { return *I & (1ULL << O); }\n    };\n\n\
    \    class ConstProxy {\n        friend BitArray;\n        std::vector<ULL>::const_iterator\
    \ I;\n        unsigned O;\n\n        ConstProxy(std::vector<ULL>::const_iterator\
    \ I, unsigned O) : I(I), O(O) {}\n\n    public:\n        ConstProxy(const Proxy\
    \ &P) : I(P.I), O(P.O) {}\n        operator bool() const { return *I & (1ULL <<\
    \ O); }\n    };\n\n    [[nodiscard]] Proxy operator[](std::size_t P) {\n     \
    \   return Proxy(D.begin() + P / WIDTH, P % WIDTH);\n    }\n    [[nodiscard]]\
    \ Proxy at(std::size_t P) {\n        assert(P < S);\n        return operator[](P);\n\
    \    }\n\n    [[nodiscard]] ConstProxy operator[](std::size_t P) const {\n   \
    \     return ConstProxy(D.begin() + P / WIDTH, P % WIDTH);\n    }\n    [[nodiscard]]\
    \ ConstProxy at(std::size_t P) const {\n        assert(P < S);\n        return\
    \ operator[](P);\n    }\n\n    BitArray &operator&=(const BitArray &R) {\n   \
    \     assert(S == R.S);\n        for (std::size_t i = 0; i < D.size(); ++i) D[i]\
    \ &= R.D[i];\n        return *this;\n    }\n\n    BitArray &operator|=(const BitArray\
    \ &R) {\n        assert(S == R.S);\n        for (std::size_t i = 0; i < D.size();\
    \ ++i) D[i] |= R.D[i];\n        return *this;\n    }\n\n    BitArray &operator^=(const\
    \ BitArray &R) {\n        assert(S == R.S);\n        for (std::size_t i = 0; i\
    \ < D.size(); ++i) D[i] ^= R.D[i];\n        return *this;\n    }\n\n    [[nodiscard]]\
    \ std::string to_string() const {\n        std::string res(D.size() * WIDTH, 0);\n\
    \        char *d = res.data();\n        for (std::size_t i = 0; i < D.size();\
    \ ++i)\n            detail::to_bit_string<WIDTH>(D[i], d + i * WIDTH);\n     \
    \   res.resize(S);\n        return res;\n    }\n\n    friend BitArray operator&(const\
    \ BitArray &L, const BitArray &R) { return BitArray(L) &= R; }\n    friend BitArray\
    \ operator|(const BitArray &L, const BitArray &R) { return BitArray(L) |= R; }\n\
    \    friend BitArray operator^(const BitArray &L, const BitArray &R) { return\
    \ BitArray(L) ^= R; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: bitarray.hpp
  requiredBy: []
  timestamp: '2024-06-03 19:19:24+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix_det_mod_2.0.test.cpp
documentation_of: bitarray.hpp
layout: document
redirect_from:
- /library/bitarray.hpp
- /library/bitarray.hpp.html
title: bitarray.hpp
---
