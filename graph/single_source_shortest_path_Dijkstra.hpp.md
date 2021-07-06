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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
    title: remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/graph/shortest_path.0.test.cpp
    title: remote_test/yosupo/graph/shortest_path.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "single source shortest path Dijkstra / \u5355\u6E90\u6700\u77ED\
      \u8DEF Dijkstra \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/single_source_shortest_path_Dijkstra.hpp\"\n\n\n\n\
    /**\n * @brief single source shortest path Dijkstra / \u5355\u6E90\u6700\u77ED\
    \u8DEF Dijkstra \u7B97\u6CD5\n *\n */\n\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"datastructure/heap/priority_queue.hpp\"\n\n\n\n\
    /**\n * @brief priority queue / \u4F18\u5148\u961F\u5217\n *\n */\n\n#include\
    \ <functional>\n\n#line 1 \"datastructure/heap/pairing_heap.hpp\"\n\n\n\n/**\n\
    \ * @brief pairing heap / \u914D\u5BF9\u5806\n *\n */\n\n#line 10 \"datastructure/heap/pairing_heap.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename Type, typename Comp> class PairingHeap\
    \ {\npublic:\n  struct Node {\n    Node *c, *s, *p; // first_child, sibling, parent\n\
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
    \n} // namespace lib\n\n\n#line 12 \"datastructure/heap/priority_queue.hpp\"\n\
    \nnamespace lib {\n\ntemplate <typename Type, typename Comp = std::less<>, typename\
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
    \ *heap_;\n  int sz_;\n};\n\n} // namespace lib\n\n\n#line 14 \"graph/single_source_shortest_path_Dijkstra.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename DistType> class NonnegativeShortestPathGraph\
    \ {\npublic:\n  struct InputEdge {\n    int from, to;\n    DistType dist;\n  \
    \  InputEdge(int from, int to, DistType dist) : from(from), to(to), dist(dist)\
    \ {}\n    ~InputEdge() = default;\n  };\n\n  struct Edge {\n    int to;\n    DistType\
    \ dist;\n  };\n\n  NonnegativeShortestPathGraph(int n) : n_(n) {}\n  ~NonnegativeShortestPathGraph()\
    \ = default;\n\n  void add_directed_edge(int from, int to, DistType dist) {\n\
    \    input_edge_.emplace_back(from, to, dist);\n  }\n\n  std::pair<std::vector<DistType>,\
    \ std::vector<int>> get_sssp(int source) const {\n    std::vector<int> idx(n_\
    \ + 1, 0);\n    std::vector<Edge> edge(input_edge_.size());\n    for (auto &i\
    \ : input_edge_) ++idx[i.from];\n    for (int i = 0, sum = 0; i <= n_; ++i) sum\
    \ += idx[i], idx[i] = sum - idx[i];\n    for (auto &i : input_edge_) edge[idx[i.from]++]\
    \ = Edge{i.to, i.dist};\n    for (int i = n_ - 1; i > 0; --i) idx[i] = idx[i -\
    \ 1];\n    idx[0] = 0;\n    const DistType INF = std::numeric_limits<DistType>::max();\n\
    \    std::vector<DistType> dist(n_, INF);\n    std::vector<int> pred(n_, -1);\n\
    \    auto cmp = [&dist](int x, int y) -> bool { return dist[x] < dist[y]; };\n\
    \    lib::PriorityQueue<int, decltype(cmp)> pq(cmp);\n    std::vector<typename\
    \ PriorityQueue<int, decltype(cmp)>::const_node_ptr_type> box(n_);\n    dist[source]\
    \ = 0;\n    pq.insert(source);\n    while (!pq.is_empty()) {\n      auto x = pq.find_min();\n\
    \      pq.delete_min();\n      auto dx = dist[x];\n      for (int i = idx[x],\
    \ ie = idx[x + 1]; i < ie; ++i) {\n        int j = edge[i].to;\n        DistType\
    \ d = edge[i].dist;\n        if (dist[j] > dx + d) {\n          if (dist[j] ==\
    \ INF) {\n            dist[j] = dx + d;\n            box[j] = pq.insert(j);\n\
    \          } else {\n            dist[j] = dx + d;\n            pq.decrease_key(box[j],\
    \ j);\n          }\n          pred[j] = x;\n        }\n      }\n    }\n    return\
    \ {dist, pred};\n  }\n\nprivate:\n  const int n_; // \u8282\u70B9\u7F16\u53F7\u5728\
    \ [0, n-1] \u4E2D\uFF01\n  std::vector<InputEdge> input_edge_;\n};\n\n} // namespace\
    \ lib\n\n\n"
  code: "#ifndef SINGLE_SOURCE_SHORTEST_PATH_DIJKSTRA_HEADER_HPP\n#define SINGLE_SOURCE_SHORTEST_PATH_DIJKSTRA_HEADER_HPP\n\
    \n/**\n * @brief single source shortest path Dijkstra / \u5355\u6E90\u6700\u77ED\
    \u8DEF Dijkstra \u7B97\u6CD5\n *\n */\n\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#include \"../datastructure/heap/priority_queue.hpp\"\n\n\
    namespace lib {\n\ntemplate <typename DistType> class NonnegativeShortestPathGraph\
    \ {\npublic:\n  struct InputEdge {\n    int from, to;\n    DistType dist;\n  \
    \  InputEdge(int from, int to, DistType dist) : from(from), to(to), dist(dist)\
    \ {}\n    ~InputEdge() = default;\n  };\n\n  struct Edge {\n    int to;\n    DistType\
    \ dist;\n  };\n\n  NonnegativeShortestPathGraph(int n) : n_(n) {}\n  ~NonnegativeShortestPathGraph()\
    \ = default;\n\n  void add_directed_edge(int from, int to, DistType dist) {\n\
    \    input_edge_.emplace_back(from, to, dist);\n  }\n\n  std::pair<std::vector<DistType>,\
    \ std::vector<int>> get_sssp(int source) const {\n    std::vector<int> idx(n_\
    \ + 1, 0);\n    std::vector<Edge> edge(input_edge_.size());\n    for (auto &i\
    \ : input_edge_) ++idx[i.from];\n    for (int i = 0, sum = 0; i <= n_; ++i) sum\
    \ += idx[i], idx[i] = sum - idx[i];\n    for (auto &i : input_edge_) edge[idx[i.from]++]\
    \ = Edge{i.to, i.dist};\n    for (int i = n_ - 1; i > 0; --i) idx[i] = idx[i -\
    \ 1];\n    idx[0] = 0;\n    const DistType INF = std::numeric_limits<DistType>::max();\n\
    \    std::vector<DistType> dist(n_, INF);\n    std::vector<int> pred(n_, -1);\n\
    \    auto cmp = [&dist](int x, int y) -> bool { return dist[x] < dist[y]; };\n\
    \    lib::PriorityQueue<int, decltype(cmp)> pq(cmp);\n    std::vector<typename\
    \ PriorityQueue<int, decltype(cmp)>::const_node_ptr_type> box(n_);\n    dist[source]\
    \ = 0;\n    pq.insert(source);\n    while (!pq.is_empty()) {\n      auto x = pq.find_min();\n\
    \      pq.delete_min();\n      auto dx = dist[x];\n      for (int i = idx[x],\
    \ ie = idx[x + 1]; i < ie; ++i) {\n        int j = edge[i].to;\n        DistType\
    \ d = edge[i].dist;\n        if (dist[j] > dx + d) {\n          if (dist[j] ==\
    \ INF) {\n            dist[j] = dx + d;\n            box[j] = pq.insert(j);\n\
    \          } else {\n            dist[j] = dx + d;\n            pq.decrease_key(box[j],\
    \ j);\n          }\n          pred[j] = x;\n        }\n      }\n    }\n    return\
    \ {dist, pred};\n  }\n\nprivate:\n  const int n_; // \u8282\u70B9\u7F16\u53F7\u5728\
    \ [0, n-1] \u4E2D\uFF01\n  std::vector<InputEdge> input_edge_;\n};\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn:
  - datastructure/heap/priority_queue.hpp
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: false
  path: graph/single_source_shortest_path_Dijkstra.hpp
  requiredBy: []
  timestamp: '2021-07-06 15:14:37+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/graph/shortest_path_nonnegative.0.test.cpp
  - remote_test/yosupo/graph/shortest_path.0.test.cpp
documentation_of: graph/single_source_shortest_path_Dijkstra.hpp
layout: document
redirect_from:
- /library/graph/single_source_shortest_path_Dijkstra.hpp
- /library/graph/single_source_shortest_path_Dijkstra.hpp.html
title: "single source shortest path Dijkstra / \u5355\u6E90\u6700\u77ED\u8DEF Dijkstra\
  \ \u7B97\u6CD5"
---
