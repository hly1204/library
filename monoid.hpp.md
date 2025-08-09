---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: disjoint_sparse_table.hpp
    title: disjoint_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: sparse_table.hpp
    title: sparse_table.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/static_range_sum.0.test.cpp
    title: test/data_structure/static_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/staticrmq.0.test.cpp
    title: test/data_structure/staticrmq.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"monoid.hpp\"\n\n#include <type_traits>\n\ntemplate<typename\
    \ Tp, typename Op,\n         std::enable_if_t<std::is_invocable_r_v<Tp, Op, const\
    \ Tp &, const Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n    Tp Id;\n\
    \n    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\n    const\
    \ Tp &id() const { return Id; }\n    Tp operator()(const Tp &L, const Tp &R) const\
    \ { return F(L, R); }\n};\n"
  code: "#pragma once\n\n#include <type_traits>\n\ntemplate<typename Tp, typename\
    \ Op,\n         std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const\
    \ Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n    Tp Id;\n\n    explicit\
    \ Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\n    const Tp &id() const\
    \ { return Id; }\n    Tp operator()(const Tp &L, const Tp &R) const { return F(L,\
    \ R); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid.hpp
  requiredBy:
  - sparse_table.hpp
  - disjoint_sparse_table.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/staticrmq.0.test.cpp
  - test/data_structure/static_range_sum.0.test.cpp
documentation_of: monoid.hpp
layout: document
redirect_from:
- /library/monoid.hpp
- /library/monoid.hpp.html
title: monoid.hpp
---
