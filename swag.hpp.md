---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/data_structure/queue_operate_all_composite.0.test.cpp
    title: test/data_structure/queue_operate_all_composite.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://www.hirzels.com/martin/papers/debs17-tutorial.pdf
  bundledCode: "#line 2 \"swag.hpp\"\n\n#include <cassert>\n#include <cstddef>\n#include\
    \ <optional>\n#include <stack>\n#include <type_traits>\n#include <vector>\n\n\
    // see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\ntemplate <typename\
    \ Tp, typename Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const\
    \ Tp &, const Tp &>, int> = 0>\nclass SWAG {\npublic:\n    Op F;\n    std::stack<Tp,\
    \ std::vector<Tp>> Front, Back;\n    std::optional<Tp> Agg;\n\n    explicit SWAG(Op\
    \ F) : F(F) {}\n    bool empty() const { return Front.empty() && Back.empty();\
    \ }\n    std::size_t size() const { return Front.size() + Back.size(); }\n   \
    \ void push_back(const Tp &v) {\n        Back.push(v);\n        Agg.emplace(Agg\
    \ ? F(*Agg, v) : v);\n    }\n    void pop_front() {\n        assert(!empty());\n\
    \        if (Front.empty()) {\n            Front.push(Back.top());\n         \
    \   Back.pop();\n            while (!Back.empty()) {\n                Front.push(F(Back.top(),\
    \ Front.top()));\n                Back.pop();\n            }\n            Agg.reset();\n\
    \        }\n        Front.pop();\n    }\n\n    // returns F(Q[0],F(...,F(Q[N-2],Q[N-1]))\n\
    \    std::optional<Tp> query() const {\n        if (empty()) return {};\n    \
    \    if (Front.empty()) return Agg;\n        if (!Agg) return Front.top();\n \
    \       return F(Front.top(), *Agg);\n    }\n};\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cstddef>\n#include <optional>\n\
    #include <stack>\n#include <type_traits>\n#include <vector>\n\n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\n\
    template <typename Tp, typename Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Op, const Tp &, const Tp &>, int> = 0>\nclass SWAG {\npublic:\n    Op F;\n \
    \   std::stack<Tp, std::vector<Tp>> Front, Back;\n    std::optional<Tp> Agg;\n\
    \n    explicit SWAG(Op F) : F(F) {}\n    bool empty() const { return Front.empty()\
    \ && Back.empty(); }\n    std::size_t size() const { return Front.size() + Back.size();\
    \ }\n    void push_back(const Tp &v) {\n        Back.push(v);\n        Agg.emplace(Agg\
    \ ? F(*Agg, v) : v);\n    }\n    void pop_front() {\n        assert(!empty());\n\
    \        if (Front.empty()) {\n            Front.push(Back.top());\n         \
    \   Back.pop();\n            while (!Back.empty()) {\n                Front.push(F(Back.top(),\
    \ Front.top()));\n                Back.pop();\n            }\n            Agg.reset();\n\
    \        }\n        Front.pop();\n    }\n\n    // returns F(Q[0],F(...,F(Q[N-2],Q[N-1]))\n\
    \    std::optional<Tp> query() const {\n        if (empty()) return {};\n    \
    \    if (Front.empty()) return Agg;\n        if (!Agg) return Front.top();\n \
    \       return F(Front.top(), *Agg);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: swag.hpp
  requiredBy: []
  timestamp: '2024-08-25 15:01:57+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/data_structure/queue_operate_all_composite.0.test.cpp
documentation_of: swag.hpp
layout: document
redirect_from:
- /library/swag.hpp
- /library/swag.hpp.html
title: swag.hpp
---
