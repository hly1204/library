---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/heap/pairing_heap.hpp
    title: "pairing heap / \u914D\u5BF9\u5806"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
    title: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/graph/shortest_path.0.test.cpp
    title: remote_test/yosupo/graph/shortest_path.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "priority queue / \u4F18\u5148\u961F\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ datastructure/heap/priority_queue.hpp: line 11: unable to process #include in\
    \ #if / #ifdef / #ifndef other than include guards\n"
  code: "/**\n * @brief priority queue / \u4F18\u5148\u961F\u5217\n *\n */\n\n#ifndef\
    \ PRIORITY_QUEUE_HEADER_HPP\n#define PRIORITY_QUEUE_HEADER_HPP\n\n#include <functional>\n\
    \n#include \"pairing_heap.hpp\"\n\nnamespace lib {\n\ntemplate <typename Type,\
    \ typename Comp = std::less<>, typename Container = PairingHeap<Type, Comp>>\n\
    class PriorityQueue {\npublic:\n  using node_type = typename Container::node_type;\n\
    \  using node_ptr_type = typename Container::node_ptr_type;\n  using const_node_ptr_type\
    \ = typename Container::const_node_ptr_type;\n\n  PriorityQueue(Comp cmp) : heap_(new\
    \ Container(cmp)), sz_(0) {}\n  PriorityQueue() : PriorityQueue(Comp()) {}\n \
    \ ~PriorityQueue() { delete heap_; }\n\n  PriorityQueue(const PriorityQueue &)\
    \ = delete;\n  PriorityQueue &operator=(const PriorityQueue &) = delete;\n\n \
    \ int size() const { return sz_; }\n  bool is_empty() const { return sz_ == 0;\
    \ }\n\n  const_node_ptr_type insert(const Type &it) {\n    ++sz_;\n    return\
    \ heap_->insert(it);\n  }\n  void delete_min() {\n    if (is_empty()) return;\n\
    \    --sz_;\n    heap_->delete_min();\n  }\n  Type find_min() const { return heap_->find_min();\
    \ }\n  void decrease_key(const_node_ptr_type n, const Type &new_key) { heap_->decrease_key(n,\
    \ new_key); }\n  void delete_arbitrary(const_node_ptr_type n) {\n    --sz_;\n\
    \    heap_->delete_arbitrary(n);\n  }\n\nprivate:\n  Container *heap_;\n  int\
    \ sz_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: false
  path: datastructure/heap/priority_queue.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/graph/shortest_path.0.test.cpp
  - remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
documentation_of: datastructure/heap/priority_queue.hpp
layout: document
redirect_from:
- /library/datastructure/heap/priority_queue.hpp
- /library/datastructure/heap/priority_queue.hpp.html
title: "priority queue / \u4F18\u5148\u961F\u5217"
---
