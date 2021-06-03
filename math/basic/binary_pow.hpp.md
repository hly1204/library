---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: math/basic/binary_mul.hpp
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: traits/base.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "\u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod.hpp
    title: "\u6A21\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
    title: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\n#include <cassert>\n\
    #include <type_traits>\n\n#line 1 \"traits/base.hpp\"\n\n\n\n#include <cstdint>\n\
    \nnamespace lib {\n\ntemplate <typename Type> struct promote_integral;\ntemplate\
    \ <> struct promote_integral<std::int32_t> { using type = std::int64_t; };\ntemplate\
    \ <> struct promote_integral<std::uint32_t> { using type = std::uint64_t; };\n\
    \n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U,\n\
    \          bool = (sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\n\
    struct longer_integral;\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, true> { using type = T; };\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, false> { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ T, typename U> using longer_integral_t = typename longer_integral<T, U>::type;\n\
    \n} // namespace lib\n\n\n#line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n#line 5\
    \ \"math/basic/binary_mul.hpp\"\n\n#line 7 \"math/basic/binary_mul.hpp\"\n\nnamespace\
    \ lib {\n\nnamespace internal {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> mul_mod(T x, T y, T mod) {\n  if ((x %= mod) < 0) x += mod;\n  if ((y %=\
    \ mod) < 0) y += mod;\n  if constexpr (sizeof(T) < 8) {\n    return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  } else {\n    T res = 0;\n    for (; y != 0; y >>= 1) {\n   \
    \   if ((y & 1) && (res += x) >= mod) res -= mod;\n      if ((x <<= 1) >= mod)\
    \ x -= mod;\n    }\n    return res;\n  }\n}\n\n} // namespace internal\n\ntemplate\
    \ <typename T1, typename T2, typename T3,\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  if constexpr\
    \ (std::is_signed_v<T1> || std::is_signed_v<T2>) {\n    return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n  } else {\n    return internal::mul_mod<T>(x, y, mod);\n  }\n}\n\n\
    } // namespace lib\n\n\n#line 9 \"math/basic/binary_pow.hpp\"\n\nnamespace lib\
    \ {\n\ntemplate <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res\
    \ = 1;\n  for (; y != 0; y >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return\
    \ res;\n}\n\ntemplate <typename T1, typename T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\n  assert(y >= 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1)\
    \ < 8) {\n    using S = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x\
    \ = static_cast<S>(x) * x % mod)\n      if (y & 1) res = static_cast<S>(res) *\
    \ x % mod;\n  } else {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\
    \u4E5F\u80FD\u5DE5\u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n\
    \      if (y & 1) res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace\
    \ lib\n\n\n"
  code: "#ifndef BINARY_POW_HEADER_HPP\n#define BINARY_POW_HEADER_HPP\n\n#include\
    \ <cassert>\n#include <type_traits>\n\n#include \"../../traits/base.hpp\"\n#include\
    \ \"binary_mul.hpp\"\n\nnamespace lib {\n\ntemplate <typename T1, typename T2>\n\
    std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T1> pow(T1\
    \ x, T2 y) {\n  assert(y >= 0);\n  T1 res = 1;\n  for (; y != 0; y >>= 1, x *=\
    \ x)\n    if (y & 1) res *= x;\n  return res;\n}\n\ntemplate <typename T1, typename\
    \ T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y, T3 mod) {\n  assert(y >=\
    \ 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1) < 8) {\n    using S\
    \ = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x = static_cast<S>(x)\
    \ * x % mod)\n      if (y & 1) res = static_cast<S>(res) * x % mod;\n  } else\
    \ {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\u4E5F\u80FD\u5DE5\
    \u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n      if (y & 1)\
    \ res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace lib\n\n\
    #endif\n"
  dependsOn:
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  isVerificationFile: false
  path: math/basic/binary_pow.hpp
  requiredBy:
  - math/modulo/sqrt_mod.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
documentation_of: math/basic/binary_pow.hpp
layout: document
redirect_from:
- /library/math/basic/binary_pow.hpp
- /library/math/basic/binary_pow.hpp.html
title: math/basic/binary_pow.hpp
---
