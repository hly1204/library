---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/heap/pairing_heap.hpp
    title: "pairing heap / \u914D\u5BF9\u5806"
  - icon: ':heavy_check_mark:'
    path: datastructure/heap/priority_queue.hpp
    title: "priority queue / \u4F18\u5148\u961F\u5217"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C
  bundledCode: "#line 1 \"remote_test/aizuoj/data_structures/priority_queue.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C\"\
    \r\n\r\n#include <iostream>\r\n\r\n#line 1 \"datastructure/heap/priority_queue.hpp\"\
    \n\n\n\r\n/**\r\n * @brief priority queue / \u4F18\u5148\u961F\u5217\r\n *\r\n\
    \ */\r\n\r\n#include <functional>\r\n\r\n#line 1 \"datastructure/heap/pairing_heap.hpp\"\
    \n\n\n\r\n/**\r\n * @brief pairing heap / \u914D\u5BF9\u5806\r\n *\r\n */\r\n\r\
    \n#include <utility>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type, typename\
    \ Comp>\r\nclass PairingHeap {\r\npublic:\r\n  struct Node {\r\n    Node *c, *s,\
    \ *p; // first_child, sibling, parent\r\n    Type it;\r\n    Node(const Type &it)\
    \ : c(nullptr), s(nullptr), p(nullptr), it(it) {}\r\n    ~Node() {\r\n      delete\
    \ s;\r\n      delete c;\r\n    }\r\n  };\r\n\r\n  using node_type           =\
    \ Node;\r\n  using node_ptr_type       = Node *;\r\n  using const_node_ptr_type\
    \ = const Node *;\r\n\r\n  PairingHeap(Comp cmp) : rt_(nullptr), cmp_(cmp) {}\r\
    \n  PairingHeap() : PairingHeap(Comp()) {}\r\n  PairingHeap(const PairingHeap\
    \ &rhs) = delete;\r\n  ~PairingHeap() { delete rt_; }\r\n\r\n  PairingHeap &operator=(const\
    \ PairingHeap &rhs) = delete; // \u8D4B\u503C\u548C\u590D\u5236\u6784\u9020\u90FD\
    \u4E0D\u5B9E\u73B0\r\n  PairingHeap &meld(PairingHeap &h) {\r\n    if (&h != this)\
    \ rt_ = meld(rt_, h.rt_), h.rt_ = nullptr;\r\n    return *this;\r\n  }\r\n  const\
    \ Node *insert(const Type &it) {\r\n    Node *r = new Node(it);\r\n    rt_   \
    \  = meld(rt_, r);\r\n    return const_cast<const Node *>(r);\r\n  }\r\n  bool\
    \ is_empty() const { return rt_ == nullptr; }\r\n  Type find_min() const { return\
    \ rt_->it; }\r\n  void delete_min() {\r\n    Node *r = rt_;\r\n    if (r->c !=\
    \ nullptr) {\r\n      r->c->p = nullptr;\r\n      rt_     = pair(r->c);\r\n  \
    \    r->c    = nullptr;\r\n    } else {\r\n      rt_ = nullptr;\r\n    }\r\n \
    \   delete r;\r\n  }\r\n  void delete_arbitrary(const Node *x) {\r\n    if (x->p\
    \ == nullptr) return delete_min();\r\n    Node *y = const_cast<Node *>(x);\r\n\
    \    cut(y);\r\n    Node *t = y->c;\r\n    if (t != nullptr) y->c = t->p = nullptr;\r\
    \n    delete y;\r\n    meld(pair(t), rt_);\r\n  }\r\n  void decrease_key(const\
    \ Node *x, const Type &it) { // \u5FC5\u987B\u5728\u8BE5\u5806\u5185\r\n    if\
    \ (x == rt_) {\r\n      rt_->it = it;\r\n    } else {\r\n      Node *y = const_cast<Node\
    \ *>(x);\r\n      cut(y);\r\n      y->it = it;\r\n      rt_   = meld(rt_, y);\r\
    \n    }\r\n  }\r\n\r\nprivate:\r\n  Node *rt_;\r\n  Comp cmp_;\r\n\r\n  static\
    \ void cut(Node *x) {\r\n    if (x->p != nullptr) {\r\n      if ((((x->p->c ==\
    \ x) ? x->p->c : x->p->s) = x->s) != nullptr) {\r\n        x->s->p = x->p;\r\n\
    \        x->s    = nullptr;\r\n      }\r\n      x->p = nullptr;\r\n    }\r\n \
    \ }\r\n  Node *meld(Node *x, Node *y) { // x, y \u4E3A\u4E0D\u540C\u7684\u6839\
    \r\n    if (x == nullptr) return y;\r\n    if (y == nullptr) return x;\r\n   \
    \ if (cmp_(y->it, x->it)) std::swap(x, y); // \u4F7F x->it <= y->it\r\n    if\
    \ ((y->s = x->c) != nullptr) x->c->p = y;\r\n    return (x->c = y)->p = x;\r\n\
    \  }\r\n  Node *pair(Node *x) { // \u4ECE\u53F3\u5F80\u5DE6\u914D\u5BF9\uFF0C\u8BBA\
    \u6587\u4E2D\u6709\u5176\u4ED6\u53D8\u79CD\uFF0C\u4F46\u6709\u4E9B\u65F6\u95F4\
    \u590D\u6742\u5EA6\u4E0D\u660E\u786E\r\n    if (x == nullptr || x->s == nullptr)\
    \ return x;\r\n    Node *y = x->s, *z = y->s;\r\n    x->s = y->p = y->s = nullptr;\r\
    \n    if (z != nullptr) z->p = nullptr;\r\n    return meld(pair(z), meld(x, y));\r\
    \n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 12 \"datastructure/heap/priority_queue.hpp\"\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename Type, typename Comp = std::less<>,\
    \ typename Container = PairingHeap<Type, Comp>>\r\nclass PriorityQueue {\r\npublic:\r\
    \n  using node_type           = typename Container::node_type;\r\n  using node_ptr_type\
    \       = typename Container::node_ptr_type;\r\n  using const_node_ptr_type =\
    \ typename Container::const_node_ptr_type;\r\n\r\n  PriorityQueue(Comp cmp) :\
    \ heap_(new Container(cmp)), sz_(0) {}\r\n  PriorityQueue() : PriorityQueue(Comp())\
    \ {}\r\n  ~PriorityQueue() { delete heap_; }\r\n\r\n  PriorityQueue(const PriorityQueue\
    \ &) = delete;\r\n  PriorityQueue &operator=(const PriorityQueue &) = delete;\r\
    \n\r\n  int size() const { return sz_; }\r\n  bool is_empty() const { return sz_\
    \ == 0; }\r\n\r\n  const_node_ptr_type insert(const Type &it) {\r\n    ++sz_;\r\
    \n    return heap_->insert(it);\r\n  }\r\n  void delete_min() {\r\n    if (is_empty())\
    \ return;\r\n    --sz_;\r\n    heap_->delete_min();\r\n  }\r\n  Type find_min()\
    \ const { return heap_->find_min(); }\r\n  void decrease_key(const_node_ptr_type\
    \ n, const Type &new_key) { heap_->decrease_key(n, new_key); }\r\n  void delete_arbitrary(const_node_ptr_type\
    \ n) {\r\n    --sz_;\r\n    heap_->delete_arbitrary(n);\r\n  }\r\n\r\nprivate:\r\
    \n  Container *heap_;\r\n  int sz_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n\
    #line 6 \"remote_test/aizuoj/data_structures/priority_queue.0.test.cpp\"\n\r\n\
    int main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  auto cmp = [](long long a, long long b) -> bool { return a > b; };\r\n  lib::PriorityQueue<long\
    \ long, decltype(cmp)> pq(cmp);\r\n  char cmd[10];\r\n  while (std::cin >> cmd\
    \ && cmd[2] != 'd') {\r\n    if (cmd[0] == 'i') {\r\n      long long v;\r\n  \
    \    std::cin >> v;\r\n      pq.insert(v);\r\n    } else {\r\n      std::cout\
    \ << pq.find_min() << '\\n';\r\n      pq.delete_min();\r\n    }\r\n  }\r\n  return\
    \ 0;\r\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C\"\
    \r\n\r\n#include <iostream>\r\n\r\n#include \"datastructure/heap/priority_queue.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  auto cmp = [](long long a, long long b) -> bool { return\
    \ a > b; };\r\n  lib::PriorityQueue<long long, decltype(cmp)> pq(cmp);\r\n  char\
    \ cmd[10];\r\n  while (std::cin >> cmd && cmd[2] != 'd') {\r\n    if (cmd[0] ==\
    \ 'i') {\r\n      long long v;\r\n      std::cin >> v;\r\n      pq.insert(v);\r\
    \n    } else {\r\n      std::cout << pq.find_min() << '\\n';\r\n      pq.delete_min();\r\
    \n    }\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - datastructure/heap/priority_queue.hpp
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
- /verify/remote_test/aizuoj/data_structures/priority_queue.0.test.cpp.html
title: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
---
