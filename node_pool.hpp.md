---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
    title: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/point_set_range_composite.0.test.cpp
    title: test/data_structure/point_set_range_composite.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_point_get.0.test.cpp
    title: test/data_structure/range_affine_point_get.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_range_sum.0.test.cpp
    title: test/data_structure/range_affine_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_reverse_range_sum.0.test.cpp
    title: test/data_structure/range_reverse_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
    title: test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tree/dynamic_tree_vertex_set_path_composite.0.test.cpp
    title: test/tree/dynamic_tree_vertex_set_path_composite.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tree/jump_on_tree.0.test.cpp
    title: test/tree/jump_on_tree.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tree/lca.0.test.cpp
    title: test/tree/lca.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"node_pool.hpp\"\n\n#include <list>\n#include <memory>\n\
    #include <utility>\n#include <vector>\n\ntemplate<typename NodeT> class FixedSizeNodePool\
    \ {\n    std::vector<NodeT> pool;\n\npublic:\n    explicit FixedSizeNodePool(int\
    \ n) : pool(n) {}\n    NodeT *at(int ind) { return pool.data() + ind; }\n    int\
    \ id(NodeT *a) const { return a - pool.data(); }\n    auto get_func() {\n    \
    \    return std::make_pair([this](int ind) { return at(ind); },\n            \
    \                  [this](NodeT *a) { return id(a); });\n    }\n};\n\ntemplate<typename\
    \ NodeT> class DynamicSizeNodePool {\n    struct Wrapped : public NodeT {\n  \
    \      using NodeT::NodeT;\n        typename std::list<Wrapped>::iterator i;\n\
    \    };\n    std::list<Wrapped> used_list;\n    std::list<Wrapped> free_list;\n\
    \npublic:\n    template<typename... Args> NodeT *make(Args &&...arg) {\n     \
    \   if (free_list.empty()) {\n            auto &&node = used_list.emplace_back(std::forward<Args>(arg)...);\n\
    \            node.i      = std::prev(used_list.end());\n            return std::addressof(node);\n\
    \        }\n        used_list.splice(used_list.end(), free_list, std::prev(free_list.end()));\n\
    \        auto &&node = used_list.back();\n        node.~NodeT(); // i remains\
    \ unchanged\n        new (std::addressof(node)) NodeT(std::forward<Args>(arg)...);\n\
    \        return std::addressof(node);\n    }\n    // this is lazy, if sth. relies\
    \ on the order of dtor, do NOT use\n    void retrieve(NodeT *node) {\n       \
    \ free_list.splice(free_list.end(), used_list, ((Wrapped *)node)->i);\n    }\n\
    };\n"
  code: "#pragma once\n\n#include <list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\ntemplate<typename NodeT> class FixedSizeNodePool {\n    std::vector<NodeT>\
    \ pool;\n\npublic:\n    explicit FixedSizeNodePool(int n) : pool(n) {}\n    NodeT\
    \ *at(int ind) { return pool.data() + ind; }\n    int id(NodeT *a) const { return\
    \ a - pool.data(); }\n    auto get_func() {\n        return std::make_pair([this](int\
    \ ind) { return at(ind); },\n                              [this](NodeT *a) {\
    \ return id(a); });\n    }\n};\n\ntemplate<typename NodeT> class DynamicSizeNodePool\
    \ {\n    struct Wrapped : public NodeT {\n        using NodeT::NodeT;\n      \
    \  typename std::list<Wrapped>::iterator i;\n    };\n    std::list<Wrapped> used_list;\n\
    \    std::list<Wrapped> free_list;\n\npublic:\n    template<typename... Args>\
    \ NodeT *make(Args &&...arg) {\n        if (free_list.empty()) {\n           \
    \ auto &&node = used_list.emplace_back(std::forward<Args>(arg)...);\n        \
    \    node.i      = std::prev(used_list.end());\n            return std::addressof(node);\n\
    \        }\n        used_list.splice(used_list.end(), free_list, std::prev(free_list.end()));\n\
    \        auto &&node = used_list.back();\n        node.~NodeT(); // i remains\
    \ unchanged\n        new (std::addressof(node)) NodeT(std::forward<Args>(arg)...);\n\
    \        return std::addressof(node);\n    }\n    // this is lazy, if sth. relies\
    \ on the order of dtor, do NOT use\n    void retrieve(NodeT *node) {\n       \
    \ free_list.splice(free_list.end(), used_list, ((Wrapped *)node)->i);\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: node_pool.hpp
  requiredBy: []
  timestamp: '2025-09-15 19:13:13+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - test/data_structure/range_affine_range_sum.0.test.cpp
  - test/data_structure/point_set_range_composite.0.test.cpp
  - test/data_structure/range_affine_point_get.0.test.cpp
  - test/data_structure/range_reverse_range_sum.0.test.cpp
  - test/tree/dynamic_tree_vertex_set_path_composite.0.test.cpp
  - test/tree/jump_on_tree.0.test.cpp
  - test/tree/lca.0.test.cpp
  - test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
documentation_of: node_pool.hpp
layout: document
redirect_from:
- /library/node_pool.hpp
- /library/node_pool.hpp.html
title: node_pool.hpp
---
