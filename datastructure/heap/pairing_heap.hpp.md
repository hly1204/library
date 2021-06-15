---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: datastructure/heap/priority_queue.hpp
    title: "priority queue / \u4F18\u5148\u961F\u5217"
  - icon: ':x:'
    path: graph/single_source_shortest_path_Dijkstra.hpp
    title: "single source shortest path Dijkstra / \u5355\u6E90\u6700\u77ED\u8DEF\
      \ Dijkstra \u7B97\u6CD5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
    title: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
  - icon: ':x:'
    path: remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
    title: remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/graph/shortest_path.0.test.cpp
    title: remote_test/yosupo/graph/shortest_path.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "pairing heap / \u914D\u5BF9\u5806"
    links: []
  bundledCode: "#line 1 \"datastructure/heap/pairing_heap.hpp\"\n\n\n\n/**\n * @brief\
    \ pairing heap / \u914D\u5BF9\u5806\n *\n */\n\n#include <utility>\n\nnamespace\
    \ lib {\n\ntemplate <typename Type, typename Comp> class PairingHeap {\npublic:\n\
    \  struct Node {\n    Node *c, *s, *p; // first_child, sibling, parent\n    Type\
    \ it;\n    Node(const Type &it) : c(nullptr), s(nullptr), p(nullptr), it(it) {}\n\
    \    ~Node() {\n      delete s;\n      delete c;\n    }\n  };\n\n  using node_type\
    \ = Node;\n  using node_ptr_type = Node *;\n  using const_node_ptr_type = const\
    \ Node *;\n\n  PairingHeap(Comp cmp) : rt_(nullptr), cmp_(cmp) {}\n  PairingHeap()\
    \ : PairingHeap(Comp()) {}\n  PairingHeap(const PairingHeap &rhs) = delete;\n\
    \  ~PairingHeap() { delete rt_; }\n\n  PairingHeap &operator=(const PairingHeap\
    \ &rhs) = delete; // \u8D4B\u503C\u548C\u590D\u5236\u6784\u9020\u90FD\u4E0D\u5B9E\
    \u73B0\n  PairingHeap &meld(PairingHeap &h) {\n    if (&h != this) rt_ = meld(rt_,\
    \ h.rt_), h.rt_ = nullptr;\n    return *this;\n  }\n  const Node *insert(const\
    \ Type &it) {\n    Node *r = new Node(it);\n    rt_ = meld(rt_, r);\n    return\
    \ const_cast<const Node *>(r);\n  }\n  bool is_empty() const { return rt_ == nullptr;\
    \ }\n  Type find_min() const { return rt_->it; }\n  void delete_min() {\n    Node\
    \ *r = rt_;\n    if (r->c != nullptr) {\n      r->c->p = nullptr;\n      rt_ =\
    \ pair(r->c);\n      r->c = nullptr;\n    } else {\n      rt_ = nullptr;\n   \
    \ }\n    delete r;\n  }\n  void delete_arbitrary(const Node *x) {\n    if (x->p\
    \ == nullptr) return delete_min();\n    Node *y = const_cast<Node *>(x);\n   \
    \ cut(y);\n    Node *t = y->c;\n    if (t != nullptr) y->c = t->p = nullptr;\n\
    \    delete y;\n    meld(pair(t), rt_);\n  }\n  void decrease_key(const Node *x,\
    \ const Type &it) { // \u5FC5\u987B\u5728\u8BE5\u5806\u5185\n    if (x == rt_)\
    \ {\n      rt_->it = it;\n    } else {\n      Node *y = const_cast<Node *>(x);\n\
    \      cut(y);\n      y->it = it;\n      rt_ = meld(rt_, y);\n    }\n  }\n\nprivate:\n\
    \  Node *rt_;\n  Comp cmp_;\n\n  static void cut(Node *x) {\n    if (x->p != nullptr)\
    \ {\n      if ((((x->p->c == x) ? x->p->c : x->p->s) = x->s) != nullptr) {\n \
    \       x->s->p = x->p;\n        x->s = nullptr;\n      }\n      x->p = nullptr;\n\
    \    }\n  }\n  Node *meld(Node *x, Node *y) { // x, y \u4E3A\u4E0D\u540C\u7684\
    \u6839\n    if (x == nullptr) return y;\n    if (y == nullptr) return x;\n   \
    \ if (cmp_(y->it, x->it)) std::swap(x, y); // \u4F7F x->it <= y->it\n    if ((y->s\
    \ = x->c) != nullptr) x->c->p = y;\n    return (x->c = y)->p = x;\n  }\n  Node\
    \ *pair(Node *x) { // \u4ECE\u53F3\u5F80\u5DE6\u914D\u5BF9\uFF0C\u8BBA\u6587\u4E2D\
    \u6709\u5176\u4ED6\u53D8\u79CD\uFF0C\u4F46\u6709\u4E9B\u65F6\u95F4\u590D\u6742\
    \u5EA6\u4E0D\u660E\u786E\n    if (x == nullptr || x->s == nullptr) return x;\n\
    \    Node *y = x->s, *z = y->s;\n    x->s = y->p = y->s = nullptr;\n    if (z\
    \ != nullptr) z->p = nullptr;\n    return meld(pair(z), meld(x, y));\n  }\n};\n\
    \n} // namespace lib\n\n\n"
  code: "#ifndef PAIRING_HEAP_HEADER_HPP\n#define PAIRING_HEAP_HEADER_HPP\n\n/**\n\
    \ * @brief pairing heap / \u914D\u5BF9\u5806\n *\n */\n\n#include <utility>\n\n\
    namespace lib {\n\ntemplate <typename Type, typename Comp> class PairingHeap {\n\
    public:\n  struct Node {\n    Node *c, *s, *p; // first_child, sibling, parent\n\
    \    Type it;\n    Node(const Type &it) : c(nullptr), s(nullptr), p(nullptr),\
    \ it(it) {}\n    ~Node() {\n      delete s;\n      delete c;\n    }\n  };\n\n\
    \  using node_type = Node;\n  using node_ptr_type = Node *;\n  using const_node_ptr_type\
    \ = const Node *;\n\n  PairingHeap(Comp cmp) : rt_(nullptr), cmp_(cmp) {}\n  PairingHeap()\
    \ : PairingHeap(Comp()) {}\n  PairingHeap(const PairingHeap &rhs) = delete;\n\
    \  ~PairingHeap() { delete rt_; }\n\n  PairingHeap &operator=(const PairingHeap\
    \ &rhs) = delete; // \u8D4B\u503C\u548C\u590D\u5236\u6784\u9020\u90FD\u4E0D\u5B9E\
    \u73B0\n  PairingHeap &meld(PairingHeap &h) {\n    if (&h != this) rt_ = meld(rt_,\
    \ h.rt_), h.rt_ = nullptr;\n    return *this;\n  }\n  const Node *insert(const\
    \ Type &it) {\n    Node *r = new Node(it);\n    rt_ = meld(rt_, r);\n    return\
    \ const_cast<const Node *>(r);\n  }\n  bool is_empty() const { return rt_ == nullptr;\
    \ }\n  Type find_min() const { return rt_->it; }\n  void delete_min() {\n    Node\
    \ *r = rt_;\n    if (r->c != nullptr) {\n      r->c->p = nullptr;\n      rt_ =\
    \ pair(r->c);\n      r->c = nullptr;\n    } else {\n      rt_ = nullptr;\n   \
    \ }\n    delete r;\n  }\n  void delete_arbitrary(const Node *x) {\n    if (x->p\
    \ == nullptr) return delete_min();\n    Node *y = const_cast<Node *>(x);\n   \
    \ cut(y);\n    Node *t = y->c;\n    if (t != nullptr) y->c = t->p = nullptr;\n\
    \    delete y;\n    meld(pair(t), rt_);\n  }\n  void decrease_key(const Node *x,\
    \ const Type &it) { // \u5FC5\u987B\u5728\u8BE5\u5806\u5185\n    if (x == rt_)\
    \ {\n      rt_->it = it;\n    } else {\n      Node *y = const_cast<Node *>(x);\n\
    \      cut(y);\n      y->it = it;\n      rt_ = meld(rt_, y);\n    }\n  }\n\nprivate:\n\
    \  Node *rt_;\n  Comp cmp_;\n\n  static void cut(Node *x) {\n    if (x->p != nullptr)\
    \ {\n      if ((((x->p->c == x) ? x->p->c : x->p->s) = x->s) != nullptr) {\n \
    \       x->s->p = x->p;\n        x->s = nullptr;\n      }\n      x->p = nullptr;\n\
    \    }\n  }\n  Node *meld(Node *x, Node *y) { // x, y \u4E3A\u4E0D\u540C\u7684\
    \u6839\n    if (x == nullptr) return y;\n    if (y == nullptr) return x;\n   \
    \ if (cmp_(y->it, x->it)) std::swap(x, y); // \u4F7F x->it <= y->it\n    if ((y->s\
    \ = x->c) != nullptr) x->c->p = y;\n    return (x->c = y)->p = x;\n  }\n  Node\
    \ *pair(Node *x) { // \u4ECE\u53F3\u5F80\u5DE6\u914D\u5BF9\uFF0C\u8BBA\u6587\u4E2D\
    \u6709\u5176\u4ED6\u53D8\u79CD\uFF0C\u4F46\u6709\u4E9B\u65F6\u95F4\u590D\u6742\
    \u5EA6\u4E0D\u660E\u786E\n    if (x == nullptr || x->s == nullptr) return x;\n\
    \    Node *y = x->s, *z = y->s;\n    x->s = y->p = y->s = nullptr;\n    if (z\
    \ != nullptr) z->p = nullptr;\n    return meld(pair(z), meld(x, y));\n  }\n};\n\
    \n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/heap/pairing_heap.hpp
  requiredBy:
  - datastructure/heap/priority_queue.hpp
  - graph/single_source_shortest_path_Dijkstra.hpp
  timestamp: '2021-06-06 21:24:21+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/graph/shortest_path.0.test.cpp
  - remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
  - remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
documentation_of: datastructure/heap/pairing_heap.hpp
layout: document
redirect_from:
- /library/datastructure/heap/pairing_heap.hpp
- /library/datastructure/heap/pairing_heap.hpp.html
title: "pairing heap / \u914D\u5BF9\u5806"
---
