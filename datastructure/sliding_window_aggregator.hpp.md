---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
    title: remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://www.hirzels.com/martin/papers/debs17-tutorial.pdf
  bundledCode: "#line 1 \"datastructure/sliding_window_aggregator.hpp\"\n\n\n\n#line\
    \ 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib\
    \ {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/sliding_window_aggregator.hpp\"\
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
    \ OpT>;\n\nLIB_END\n\n\n"
  code: "#ifndef SLIDING_WINDOW_AGGREGATOR_HPP\n#define SLIDING_WINDOW_AGGREGATOR_HPP\n\
    \n#include \"../common.hpp\"\n\n#include <cassert>\n#include <functional>\n#include\
    \ <optional>\n#include <stack>\n#include <utility>\n#include <vector>\n\nLIB_BEGIN\n\
    \n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\ntemplate\
    \ <typename T, typename OpT>\nclass sliding_window_aggregator {\n  OpT f_ = {};\n\
    \  std::stack<T, std::vector<T>> front_, back_;\n  std::optional<T> back_agg_;\n\
    \npublic:\n  sliding_window_aggregator() = default;\n  explicit sliding_window_aggregator(OpT\
    \ op) : f_(op) {}\n  void push(const T &v) { push_back(v); }\n  void pop() { pop_front();\
    \ }\n  auto size() const { return front_.size() + back_.size(); }\n  bool empty()\
    \ const { return front_.empty() && back_.empty(); }\n  void push_back(const T\
    \ &v) {\n    back_.push(v);\n    if (back_agg_) {\n      back_agg_.emplace(std::invoke(f_,\
    \ *back_agg_, v));\n    } else {\n      back_agg_.emplace(v);\n    }\n  }\n\n\
    \  void pop_front() {\n    assert(!empty());\n    if (front_.empty()) {\n    \
    \  front_.push(back_.top());\n      back_.pop();\n      while (!back_.empty())\
    \ {\n        front_.push(std::invoke(f_, back_.top(), front_.top()));\n      \
    \  back_.pop();\n      }\n      back_agg_.reset();\n    }\n    front_.pop();\n\
    \  }\n\n  std::optional<T> query() const {\n    if (empty()) return {};\n    if\
    \ (front_.empty()) return back_agg_;\n    if (!back_agg_) return front_.top();\n\
    \    return std::invoke(f_, front_.top(), *back_agg_);\n  }\n};\n\ntemplate <typename\
    \ T, typename OpT>\nusing swag = sliding_window_aggregator<T, OpT>;\n\nLIB_END\n\
    \n#endif\n"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/sliding_window_aggregator.hpp
  requiredBy: []
  timestamp: '2024-01-13 13:59:37+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/queue_operate_all_composite.0.test.cpp
documentation_of: datastructure/sliding_window_aggregator.hpp
layout: document
title: Sliding Window Aggregator (FIFO)
---
