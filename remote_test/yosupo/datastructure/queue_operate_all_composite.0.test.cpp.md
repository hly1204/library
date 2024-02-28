---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: datastructure/sliding_window_aggregator.hpp
    title: Sliding Window Aggregator (FIFO)
  - icon: ':question:'
    path: modint/montgomery_modint.hpp
    title: Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 1 \"datastructure/sliding_window_aggregator.hpp\"\n\n\n\n#line 1 \"\
    common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define\
    \ LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/sliding_window_aggregator.hpp\"\
    \n\n#include <cassert>\n#include <functional>\n#include <optional>\n#include <stack>\n\
    #include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\n\
    template <typename T, typename OpT>\nclass sliding_window_aggregator {\n  OpT\
    \ f_ = {};\n  std::stack<T, std::vector<T>> front_, back_;\n  std::optional<T>\
    \ back_agg_;\n\npublic:\n  sliding_window_aggregator() = default;\n  explicit\
    \ sliding_window_aggregator(OpT op) : f_(op) {}\n  void push(const T &v) { push_back(v);\
    \ }\n  void pop() { pop_front(); }\n  auto size() const { return front_.size()\
    \ + back_.size(); }\n  bool empty() const { return front_.empty() && back_.empty();\
    \ }\n  void push_back(const T &v) {\n    back_.push(v);\n    if (back_agg_) {\n\
    \      back_agg_.emplace(std::invoke(f_, *back_agg_, v));\n    } else {\n    \
    \  back_agg_.emplace(v);\n    }\n  }\n\n  void pop_front() {\n    assert(!empty());\n\
    \    if (front_.empty()) {\n      front_.push(back_.top());\n      back_.pop();\n\
    \      while (!back_.empty()) {\n        front_.push(std::invoke(f_, back_.top(),\
    \ front_.top()));\n        back_.pop();\n      }\n      back_agg_.reset();\n \
    \   }\n    front_.pop();\n  }\n\n  std::optional<T> query() const {\n    if (empty())\
    \ return {};\n    if (front_.empty()) return back_agg_;\n    if (!back_agg_) return\
    \ front_.top();\n    return std::invoke(f_, front_.top(), *back_agg_);\n  }\n\
    };\n\ntemplate <typename T, typename OpT>\nusing swag = sliding_window_aggregator<T,\
    \ OpT>;\n\nLIB_END\n\n\n#line 1 \"modint/montgomery_modint.hpp\"\n\n\n\n#line\
    \ 5 \"modint/montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n\
    #endif\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\
    \ntemplate <std::uint32_t ModT>\nclass montgomery_modint30 {\n  using i32 = std::int32_t;\n\
    \  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\n  u32 v_{};\n\n\
    \  static constexpr u32 get_r() {\n    u32 t = 2, iv = MOD * (t - MOD * MOD);\n\
    \    iv *= t - MOD * iv, iv *= t - MOD * iv;\n    return iv * (MOD * iv - t);\n\
    \  }\n  static constexpr u32 redc(u64 x) {\n    return (x + static_cast<u64>(static_cast<u32>(x)\
    \ * R) * MOD) >> 32;\n  }\n  static constexpr u32 norm(u32 x) { return x - (MOD\
    \ & -((MOD - 1 - x) >> 31)); }\n\n  static constexpr u32 MOD  = ModT;\n  static\
    \ constexpr u32 MOD2 = MOD << 1;\n  static constexpr u32 R    = get_r();\n  static\
    \ constexpr u32 R2   = -static_cast<u64>(MOD) % MOD;\n  static constexpr i32 SMOD\
    \ = static_cast<i32>(MOD);\n\n  static_assert(MOD & 1);\n  static_assert(-R *\
    \ MOD == 1);\n  static_assert((MOD >> 30) == 0);\n  static_assert(MOD != 1);\n\
    \npublic:\n  static constexpr u32 mod() { return MOD; }\n  static constexpr i32\
    \ smod() { return SMOD; }\n  constexpr montgomery_modint30() {}\n  template <typename\
    \ IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  constexpr montgomery_modint30(IntT\
    \ v) : v_(redc(static_cast<u64>(v % SMOD + SMOD) * R2)) {}\n  constexpr u32 val()\
    \ const { return norm(redc(v_)); }\n  constexpr i32 sval() const { return norm(redc(v_));\
    \ }\n  constexpr bool is_zero() const { return v_ == 0 || v_ == MOD; }\n  template\
    \ <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  explicit\
    \ constexpr operator IntT() const {\n    return static_cast<IntT>(val());\n  }\n\
    \  constexpr montgomery_modint30 operator-() const {\n    montgomery_modint30\
    \ res;\n    res.v_ = (MOD2 & -(v_ != 0)) - v_;\n    return res;\n  }\n  constexpr\
    \ montgomery_modint30 inv() const {\n    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n\
    \    while (b != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n\
    \    if (a != 1) throw std::runtime_error(\"modular inverse error\");\n#endif\n\
    \    return montgomery_modint30(x1);\n  }\n  constexpr montgomery_modint30 &operator+=(const\
    \ montgomery_modint30 &rhs) {\n    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);\n\
    \    return *this;\n  }\n  constexpr montgomery_modint30 &operator-=(const montgomery_modint30\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);\n    return *this;\n  }\n\
    \  constexpr montgomery_modint30 &operator*=(const montgomery_modint30 &rhs) {\n\
    \    v_ = redc(static_cast<u64>(v_) * rhs.v_);\n    return *this;\n  }\n  constexpr\
    \ montgomery_modint30 &operator/=(const montgomery_modint30 &rhs) {\n    return\
    \ operator*=(rhs.inv());\n  }\n  constexpr montgomery_modint30 pow(u64 e) const\
    \ {\n    for (montgomery_modint30 res(1), x(*this);; x *= x) {\n      if (e &\
    \ 1) res *= x;\n      if ((e >>= 1) == 0) return res;\n    }\n  }\n  constexpr\
    \ void swap(montgomery_modint30 &rhs) {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_\
    \ = v;\n  }\n  friend constexpr montgomery_modint30 operator+(const montgomery_modint30\
    \ &lhs,\n                                                 const montgomery_modint30\
    \ &rhs) {\n    return montgomery_modint30(lhs) += rhs;\n  }\n  friend constexpr\
    \ montgomery_modint30 operator-(const montgomery_modint30 &lhs,\n            \
    \                                     const montgomery_modint30 &rhs) {\n    return\
    \ montgomery_modint30(lhs) -= rhs;\n  }\n  friend constexpr montgomery_modint30\
    \ operator*(const montgomery_modint30 &lhs,\n                                \
    \                 const montgomery_modint30 &rhs) {\n    return montgomery_modint30(lhs)\
    \ *= rhs;\n  }\n  friend constexpr montgomery_modint30 operator/(const montgomery_modint30\
    \ &lhs,\n                                                 const montgomery_modint30\
    \ &rhs) {\n    return montgomery_modint30(lhs) /= rhs;\n  }\n  friend constexpr\
    \ bool operator==(const montgomery_modint30 &lhs, const montgomery_modint30 &rhs)\
    \ {\n    return norm(lhs.v_) == norm(rhs.v_);\n  }\n  friend constexpr bool operator!=(const\
    \ montgomery_modint30 &lhs, const montgomery_modint30 &rhs) {\n    return norm(lhs.v_)\
    \ != norm(rhs.v_);\n  }\n  friend std::istream &operator>>(std::istream &is, montgomery_modint30\
    \ &rhs) {\n    i32 x;\n    is >> x;\n    rhs = montgomery_modint30(x);\n    return\
    \ is;\n  }\n  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint30\
    \ &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate <std::uint32_t ModT>\n\
    using mm30 = montgomery_modint30<ModT>;\n\nLIB_END\n\n\n#line 5 \"remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp\"\
    \n\n#line 7 \"remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \n  using mint = lib::mm30<998244353>;\n  struct linear_function {\n    mint a,\
    \ b;\n    mint operator()(const mint &x) const { return a * x + b; }\n    linear_function\
    \ operator()(const linear_function &rhs) const {\n      return {a * rhs.a, a *\
    \ rhs.b + b};\n    }\n  };\n\n  int Q;\n  std::cin >> Q;\n\n  auto c = [](const\
    \ linear_function &lhs, const linear_function &rhs) { return rhs(lhs); };\n  lib::swag<linear_function,\
    \ decltype(c)> agg(c);\n  while (Q--) {\n    int cmd;\n    std::cin >> cmd;\n\
    \    if (cmd == 0) {\n      mint a, b;\n      std::cin >> a >> b;\n      agg.push({a,\
    \ b});\n    } else if (cmd == 1) {\n      agg.pop();\n    } else {\n      mint\
    \ x;\n      std::cin >> x;\n      std::cout << agg.query().value_or(linear_function{1,\
    \ 0})(x) << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"datastructure/sliding_window_aggregator.hpp\"\n#include \"modint/montgomery_modint.hpp\"\
    \n\n#include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\",\
    \ \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n\n  using mint = lib::mm30<998244353>;\n  struct linear_function\
    \ {\n    mint a, b;\n    mint operator()(const mint &x) const { return a * x +\
    \ b; }\n    linear_function operator()(const linear_function &rhs) const {\n \
    \     return {a * rhs.a, a * rhs.b + b};\n    }\n  };\n\n  int Q;\n  std::cin\
    \ >> Q;\n\n  auto c = [](const linear_function &lhs, const linear_function &rhs)\
    \ { return rhs(lhs); };\n  lib::swag<linear_function, decltype(c)> agg(c);\n \
    \ while (Q--) {\n    int cmd;\n    std::cin >> cmd;\n    if (cmd == 0) {\n   \
    \   mint a, b;\n      std::cin >> a >> b;\n      agg.push({a, b});\n    } else\
    \ if (cmd == 1) {\n      agg.pop();\n    } else {\n      mint x;\n      std::cin\
    \ >> x;\n      std::cout << agg.query().value_or(linear_function{1, 0})(x) <<\
    \ '\\n';\n    }\n  }\n  return 0;\n}\n"
  dependsOn:
  - datastructure/sliding_window_aggregator.hpp
  - common.hpp
  - modint/montgomery_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
  requiredBy: []
  timestamp: '2024-01-13 13:59:37+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
- /verify/remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp.html
title: remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
---
