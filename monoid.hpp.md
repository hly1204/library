---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"monoid.hpp\"\n\n#include <type_traits>\n\ntemplate <typename\
    \ Tp, typename Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const\
    \ Tp &, const Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n    Tp Id;\n\
    \n    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\n    const\
    \ Tp &id() const { return Id; }\n    Tp operator()(const Tp &L, const Tp &R) const\
    \ { return F(L, R); }\n};\n"
  code: "#pragma once\n\n#include <type_traits>\n\ntemplate <typename Tp, typename\
    \ Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const\
    \ Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n    Tp Id;\n\n    explicit\
    \ Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\n    const Tp &id() const\
    \ { return Id; }\n    Tp operator()(const Tp &L, const Tp &R) const { return F(L,\
    \ R); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid.hpp
  requiredBy: []
  timestamp: '2024-08-26 22:07:33+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid.hpp
layout: document
redirect_from:
- /library/monoid.hpp
- /library/monoid.hpp.html
title: monoid.hpp
---
