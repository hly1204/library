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
  bundledCode: "#line 1 \"datastructure/heap/priority_queue.hpp\"\n\n\n\n#include\
    \ <functional>\n\n#line 1 \"datastructure/heap/pairing_heap.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace lib {\n\ntemplate <typename Type, typename Comp> class\
    \ PairingHeap {\npublic:\n  struct Node {\n    Node *c, *s, *p; // first_child,\
    \ sibling, parent\n    Type it;\n    Node(const Type &it) : c(nullptr), s(nullptr),\
    \ p(nullptr), it(it) {}\n    ~Node() {\n      delete s;\n      delete c;\n   \
    \ }\n  };\n\n  using node_type = Node;\n  using node_ptr_type = Node *;\n  using\
    \ const_node_ptr_type = const Node *;\n\n  PairingHeap(Comp cmp) : rt_(nullptr),\
    \ cmp_(cmp) {}\n  PairingHeap() : PairingHeap(Comp()) {}\n  PairingHeap(const\
    \ PairingHeap &rhs) = delete;\n  ~PairingHeap() { delete rt_; }\n\n  PairingHeap\
    \ &operator=(const PairingHeap &rhs) = delete; // \u8D4B\u503C\u548C\u590D\u5236\
    \u6784\u9020\u90FD\u4E0D\u5B9E\u73B0\n  PairingHeap &meld(PairingHeap &h) {\n\
    \    if (&h != this) rt_ = meld(rt_, h.rt_), h.rt_ = nullptr;\n    return *this;\n\
    \  }\n  const Node *insert(const Type &it) {\n    Node *r = new Node(it);\n  \
    \  rt_ = meld(rt_, r);\n    return const_cast<const Node *>(r);\n  }\n  bool is_empty()\
    \ const { return rt_ == nullptr; }\n  Type find_min() const { return rt_->it;\
    \ }\n  void delete_min() {\n    Node *r = rt_;\n    if (r->c != nullptr) {\n \
    \     r->c->p = nullptr;\n      rt_ = pair(r->c);\n      r->c = nullptr;\n   \
    \ } else {\n      rt_ = nullptr;\n    }\n    delete r;\n  }\n  void delete_arbitrary(const\
    \ Node *x) {\n    if (x->p == nullptr) return delete_min();\n    Node *y = const_cast<Node\
    \ *>(x);\n    cut(y);\n    Node *t = y->c;\n    if (t != nullptr) y->c = t->p\
    \ = nullptr;\n    delete y;\n    meld(pair(t), rt_);\n  }\n  void decrease_key(const\
    \ Node *x, const Type &it) { // \u5FC5\u987B\u5728\u8BE5\u5806\u5185\n    if (x\
    \ == rt_) {\n      rt_->it = it;\n    } else {\n      Node *y = const_cast<Node\
    \ *>(x);\n      cut(y);\n      y->it = it;\n      rt_ = meld(rt_, y);\n    }\n\
    \  }\n\nprivate:\n  Node *rt_;\n  Comp cmp_;\n\n  static void cut(Node *x) {\n\
    \    if (x->p != nullptr) {\n      if ((((x->p->c == x) ? x->p->c : x->p->s) =\
    \ x->s) != nullptr) {\n        x->s->p = x->p;\n        x->s = nullptr;\n    \
    \  }\n      x->p = nullptr;\n    }\n  }\n  Node *meld(Node *x, Node *y) { // x,\
    \ y \u4E3A\u4E0D\u540C\u7684\u6839\n    if (x == nullptr) return y;\n    if (y\
    \ == nullptr) return x;\n    if (cmp_(y->it, x->it)) std::swap(x, y); // \u4F7F\
    \ x->it <= y->it\n    if ((y->s = x->c) != nullptr) x->c->p = y;\n    return (x->c\
    \ = y)->p = x;\n  }\n  Node *pair(Node *x) { // \u4ECE\u53F3\u5F80\u5DE6\u914D\
    \u5BF9\uFF0C\u8BBA\u6587\u4E2D\u6709\u5176\u4ED6\u53D8\u79CD\uFF0C\u4F46\u6709\
    \u4E9B\u65F6\u95F4\u590D\u6742\u5EA6\u4E0D\u660E\u786E\n    if (x == nullptr ||\
    \ x->s == nullptr) return x;\n    Node *y = x->s, *z = y->s;\n    x->s = y->p\
    \ = y->s = nullptr;\n    if (z != nullptr) z->p = nullptr;\n    return meld(pair(z),\
    \ meld(x, y));\n  }\n};\n\n} // namespace lib\n\n/**\n * @brief pairing heap /\
    \ \u914D\u5BF9\u5806\n *\n */\n\n\n#line 7 \"datastructure/heap/priority_queue.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename Type, typename Comp = std::less<>, typename\
    \ Container = PairingHeap<Type, Comp>>\nclass PriorityQueue {\npublic:\n  using\
    \ node_type = typename Container::node_type;\n  using node_ptr_type = typename\
    \ Container::node_ptr_type;\n  using const_node_ptr_type = typename Container::const_node_ptr_type;\n\
    \n  PriorityQueue(Comp cmp) : heap_(new Container(cmp)), sz_(0) {}\n  PriorityQueue()\
    \ : PriorityQueue(Comp()) {}\n  ~PriorityQueue() { delete heap_; }\n\n  PriorityQueue(const\
    \ PriorityQueue &) = delete;\n  PriorityQueue &operator=(const PriorityQueue &)\
    \ = delete;\n\n  int size() const { return sz_; }\n  bool is_empty() const { return\
    \ sz_ == 0; }\n\n  const_node_ptr_type insert(const Type &it) {\n    ++sz_;\n\
    \    return heap_->insert(it);\n  }\n  void delete_min() {\n    if (is_empty())\
    \ return;\n    --sz_;\n    heap_->delete_min();\n  }\n  Type find_min() const\
    \ { return heap_->find_min(); }\n  void decrease_key(const_node_ptr_type n, const\
    \ Type &new_key) { heap_->decrease_key(n, new_key); }\n  void delete_arbitrary(const_node_ptr_type\
    \ n) {\n    --sz_;\n    heap_->delete_arbitrary(n);\n  }\n\nprivate:\n  Container\
    \ *heap_;\n  int sz_;\n};\n\n} // namespace lib\n\n/**\n * @brief priority queue\
    \ / \u4F18\u5148\u961F\u5217\n *\n */\n\n\n"
  code: "#ifndef PRIORITY_QUEUE_HEADER_HPP\n#define PRIORITY_QUEUE_HEADER_HPP\n\n\
    #include <functional>\n\n#include \"pairing_heap.hpp\"\n\nnamespace lib {\n\n\
    template <typename Type, typename Comp = std::less<>, typename Container = PairingHeap<Type,\
    \ Comp>>\nclass PriorityQueue {\npublic:\n  using node_type = typename Container::node_type;\n\
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
    \ sz_;\n};\n\n} // namespace lib\n\n/**\n * @brief priority queue / \u4F18\u5148\
    \u961F\u5217\n *\n */\n\n#endif"
  dependsOn:
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: false
  path: datastructure/heap/priority_queue.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:47:15+08:00'
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
