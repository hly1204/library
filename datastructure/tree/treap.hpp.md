---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: datastructure/tree/binary_search_tree_base.hpp
    title: "binary search tree base / \u4E8C\u53C9\u641C\u7D22\u6811\u57FA\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "Treap / \u6811\u5806"
    links: []
  bundledCode: "#line 1 \"datastructure/tree/treap.hpp\"\n\n\n\n/**\n * @brief Treap\
    \ / \u6811\u5806\n *\n */\n\n#line 1 \"datastructure/tree/binary_search_tree_base.hpp\"\
    \n\n\n\n/**\n * @brief binary search tree base / \u4E8C\u53C9\u641C\u7D22\u6811\
    \u57FA\u7C7B\n *\n */\n\n#include <cassert>\n#include <functional>\n#include <optional>\n\
    \nnamespace lib {\n\n/**\n * @brief \u4E8C\u53C9\u641C\u7D22\u6811\u8282\u70B9\
    \u7684\u57FA\u7C7B\n */\ntemplate <typename DataType> struct BSTNodeBase1 {\n\
    public:\n  using node_ptr_type = BSTNodeBase1 *;\n  using value_type = DataType;\n\
    \n  BSTNodeBase1(const value_type &v)\n      : left(nullptr), right(nullptr),\
    \ parent(nullptr), size(1), data(v) {}\n  ~BSTNodeBase1() {\n    delete left;\n\
    \    delete right;\n  }\n\n  node_ptr_type left, right, parent;\n  int size;\n\
    \  value_type data;\n};\n\ntemplate <typename NodeType, typename Comp = std::less<>>\
    \ class BinarySearchTreeBase1 {\npublic:\n  using node_ptr_type = typename NodeType::node_ptr_type;\n\
    \  using const_node_ptr_type = const node_ptr_type;\n  using value_type = typename\
    \ NodeType::value_type;\n\n#ifdef LOCAL\n\n  void test() {\n    dfs(root_);\n\
    \    std::cout << \"\\ntest over\\n\";\n  }\n\n  void dfs(const_node_ptr_type\
    \ x) {\n    if (x == nullptr) return;\n    if (x->left != nullptr) dfs(x->left);\n\
    \    std::cout << x->data << ' ';\n    if (x->right != nullptr) dfs(x->right);\n\
    \  }\n\n#endif\n\n  BinarySearchTreeBase1(const Comp &cmp) : root_(nullptr), cmp_(cmp)\
    \ {}\n  BinarySearchTreeBase1() : BinarySearchTreeBase1(Comp()) {}\n  ~BinarySearchTreeBase1()\
    \ { delete root_; }\n\n  bool is_empty() const { return root == nullptr; }\n \
    \ int size() const { return get_size(root); }\n  bool is_in_tree(const value_type\
    \ &v) const { return find_node(v) != nullptr; }\n\n  /**\n   * @brief \u9009\u62E9\
    \u7B2C k \u4E2A\u5143\u7D20\n   * @note \u7D22\u5F15\u4ECE 0 \u5F00\u59CB\n  \
    \ * @param k\n   * @return std::opetional<value_type>\n   */\n  std::optional<value_type>\
    \ select(int k) const {\n    const_node_ptr_type x = select_node(k);\n    if (x\
    \ == nullptr) return {};\n    return x->data;\n  }\n\n  /**\n   * @brief \u6C42\
    \u51FA v \u5728\u6811\u4E2D\u7684\u6392\u540D\n   * @note \u5728\u6811\u4E2D\u6709\
    \u591A\u5C11\u6BD4 v \u5C0F\u7684\u5143\u7D20\uFF0C v \u4E0D\u5FC5\u5728\u6811\
    \u4E2D\n   * @param v\n   * @return int\n   */\n  int get_rank(const value_type\
    \ &v) const {\n    int res = 0;\n    node_ptr_type x = root_;\n    while (x !=\
    \ nullptr) {\n      if (cmp_(v, x->data)) {\n        x = x->left;\n      } else\
    \ if (cmp_(x->data, v)) {\n        res += get_size(x->left) + 1;\n        x =\
    \ x->right;\n      } else {\n        x = x->left;\n      }\n    }\n    return\
    \ res;\n  }\n\n  std::optional<value_type> less_than(const value_type &v) const\
    \ {\n    node_ptr_type x = root_, res = nullptr;\n    while (x != nullptr) {\n\
    \      if (cmp_(x->data, v)) {\n        res = x, x = x->right;\n      } else {\n\
    \        x = x->left;\n      }\n    }\n    if (res == nullptr) return {};\n  \
    \  return res->data;\n  }\n  std::optional<value_type> less_equal(const value_type\
    \ &v) const {\n    node_ptr_type x = root_, res = nullptr;\n    while (x != nullptr)\
    \ {\n      if (cmp_(v, x->data)) {\n        x = x->left;\n      } else {\n   \
    \     res = x, x = x->right;\n      }\n    }\n    if (res == nullptr) return {};\n\
    \    return res->data;\n  }\n  std::optional<value_type> greater_than(const value_type\
    \ &v) const {\n    node_ptr_type x = root_, res = nullptr;\n    while (x != nullptr)\
    \ {\n      if (cmp_(v, x->data)) {\n        res = x, x = x->left;\n      } else\
    \ {\n        x = x->right;\n      }\n    }\n    if (res == nullptr) return {};\n\
    \    return res->data;\n  }\n  std::optional<value_type> greater_equal(const value_type\
    \ &v) const {\n    node_ptr_type x = root_, res = nullptr;\n    while (x != nullptr)\
    \ {\n      if (cmp_(x->data, v)) {\n        x = x->right;\n      } else {\n  \
    \      res = x, x = x->left;\n      }\n    }\n    if (res == nullptr) return {};\n\
    \    return res->data;\n  }\n\n  const_node_ptr_type insert_at_value(const value_type\
    \ &v) {\n    node_ptr_type x = new NodeType(v);\n    insert_at_value(x);\n   \
    \ return x;\n  }\n  bool delete_at_value(const value_type &v) {\n    node_ptr_type\
    \ x = find_node(v);\n    if (x == nullptr) return false;\n    delete_at_node(x);\n\
    \    return true;\n  }\n  const_node_ptr_type insert_at_rank(const value_type\
    \ &v, int k) {\n    node_ptr_type x = new NodeType(v);\n    insert_at_rank(x,\
    \ k);\n    return x;\n  }\n  bool delete_at_rank(int k) {\n    node_ptr_type x\
    \ = select_node(k);\n    if (x == nullptr) return false;\n    delete_at_node(x);\n\
    \    return true;\n  }\n\n  /**\n   * @brief \u5220\u9664\u8282\u70B9\u8F85\u52A9\
    \u51FD\u6570\n   * @note \u7528\u53F3\u5B50\u6811\u7684\u6700\u5C0F\u503C\uFF08\
    \u6216\u5DE6\u5B50\u6811\u7684\u6700\u5927\u503C\uFF09\u66FF\u4EE3\u5F53\u524D\
    \u8282\u70B9\n   * @param x\n   */\n  void delete_at_node(node_ptr_type x) {\n\
    \    assert(x != nullptr);\n    for (node_ptr_type t = x; t != nullptr; t = t->parent)\
    \ --(t->size);\n    if (x->left == nullptr) { // x \u5DE6\u5B50\u6811\u4E3A\u7A7A\
    \u6216\u5DE6\u53F3\u5B50\u6811\u90FD\u4E3A\u7A7A\n      if (x->parent != nullptr)\
    \ {\n        if (x == x->parent->left) {\n          x->parent->left = x->right;\n\
    \        } else {\n          x->parent->right = x->right;\n        }\n       \
    \ if (x->right != nullptr) x->right->parent = x->parent;\n      } else {\n   \
    \     if ((root_ = x->right) != nullptr) x->right->parent = nullptr;\n      }\n\
    \    } else if (x->right == nullptr) { // x \u53EA\u6709\u53F3\u5B50\u6811\u4E3A\
    \u7A7A\n      if (x->parent != nullptr) {\n        if (x == x->parent->left) {\n\
    \          x->parent->left = x->left;\n        } else {\n          x->parent->right\
    \ = x->left;\n        }\n        x->left->parent = x->parent;\n      } else {\n\
    \        (root_ = x->left)->parent = nullptr;\n      }\n    } else { // x \u5DE6\
    \u53F3\u5B50\u6811\u90FD\u4E0D\u4E3A\u7A7A\n      node_ptr_type r = x->right;\n\
    \      while (r->left != nullptr) { // \u7528\u53F3\u5B50\u6811\u7684\u6700\u5C0F\
    \u8282\u70B9 r \u66FF\u6362 x \uFF0C\u5E76\u4E00\u8DEF\u4FEE\u6539\u5BF9\u5E94\
    \ size\n        --(r->size);\n        r = r->left;\n      }\n      if (r->parent\
    \ == x) { // \u53F3\u5B50\u6811\u6700\u5C0F\u8282\u70B9\u5C31\u662F x \u7684\u53F3\
    \u5B69\u5B50\n        x->right = nullptr;\n      } else {\n        r->parent->left\
    \ = nullptr;\n      }\n      r->parent = x->parent;\n      (r->left = x->left)->parent\
    \ = r;\n      if ((r->right = x->right) != nullptr) r->right->parent = r;\n  \
    \    r->size = x->size;\n      if (x->parent != nullptr) {\n        if (x == x->parent->left)\
    \ {\n          x->parent->left = r;\n        } else {\n          x->parent->right\
    \ = r;\n        }\n      } else {\n        root_ = r;\n      }\n    }\n    x->left\
    \ = x->right = nullptr;\n    delete x;\n  }\n\nprotected:\n  node_ptr_type root_;\n\
    \  Comp cmp_;\n\n  node_ptr_type find_node(const value_type &v) const {\n    node_ptr_type\
    \ x = root_;\n    while (x != nullptr) {\n      if (cmp_(x->data, v)) {\n    \
    \    x = x->right;\n      } else if (cmp_(v, x->data)) {\n        x = x->left;\n\
    \      } else {\n        return x;\n      }\n    }\n    return x;\n  }\n\n  node_ptr_type\
    \ select_node(int k) const {\n    if (k < 0 || k >= size()) return {};\n    node_ptr_type\
    \ x = root_;\n    while (get_size(x->l) != k) {\n      if (get_size(x->l) < k)\
    \ {\n        k -= get_size(x->l) + 1;\n        x = x->r;\n      } else {\n   \
    \     x = x->l;\n      }\n    }\n    return x;\n  }\n\n  void insert_at_value(node_ptr_type\
    \ x) {\n    node_ptr_type p = nullptr, y = root_;\n    int dir = -1;\n    while\
    \ (y != nullptr) {\n      p = y;\n      ++(y->size);\n      if (cmp_(x->data,\
    \ y->data)) {\n        y = y->left;\n        dir = 0;\n      } else {\n      \
    \  y = y->right;\n        dir = 1;\n      }\n    }\n    if (p == nullptr) {\n\
    \      root_ = x;\n    } else {\n      if (dir == 0) {\n        p->left = x;\n\
    \      } else {\n        p->right = x;\n      }\n      x->parent = p;\n    }\n\
    \  }\n\n  /**\n   * @brief \u5728\u6392\u540D k \u7684\u5143\u7D20\u524D\u63D2\
    \u5165\u4E00\u4E2A\u5143\u7D20\n   * @note \u6392\u540D\u4ECE 0 \u5F00\u59CB\n\
    \   * @param x\n   */\n  void insert_at_rank(node_ptr_type x, int k) {\n    assert(k\
    \ >= 0);\n    assert(k < size());\n    node_ptr_type p = nullptr, y = root_;\n\
    \    int dir = -1;\n    while (y != nullptr) {\n      p = y;\n      ++(y->size);\n\
    \      if (k <= get_size(y->left)) {\n        y = y->left;\n        dir = 0;\n\
    \      } else {\n        y = y->right;\n        k -= get_size(y->left) + 1;\n\
    \        dir = 1;\n      }\n    }\n    if (p == nullptr) {\n      root_ = x;\n\
    \    } else {\n      if (dir == 0) {\n        p->left = x;\n      } else {\n \
    \       p->right = x;\n      }\n      x->parent = p;\n    }\n  }\n\n  static int\
    \ get_size(const_node_ptr_type x) { return x == nullptr ? 0 : x->size; }\n\n \
    \ void rotate_left(node_ptr_type x) {\n    assert(x != nullptr);\n    assert(x->right\
    \ != nullptr);\n    node_ptr_type r = x->right, rl = r->left;\n    int rs = r->size;\n\
    \    r->size = x->size;\n    x->size -= rs;\n    if ((x->right = rl) != nullptr)\
    \ (rl->parent = x)->size += rl->size;\n    if ((r->parent = x->parent) != nullptr)\
    \ {\n      if (x->parent->left == x) {\n        x->parent->left = r;\n      }\
    \ else {\n        x->parent->right = r;\n      }\n    } else {\n      root_ =\
    \ r;\n    }\n    (r->left = x)->parent = r;\n  }\n  void rotate_right(node_ptr_type\
    \ x) {\n    assert(x != nullptr);\n    assert(x->left != nullptr);\n    node_ptr_type\
    \ l = x->left, lr = l->right;\n    int ls = l->size;\n    l->size = x->size;\n\
    \    x->size -= ls;\n    if ((x->left = lr) != nullptr) (lr->parent = x)->size\
    \ += lr->size;\n    if ((l->parent = x->parent) != nullptr) {\n      if (x->parent->left\
    \ == x) {\n        x->parent->left = l;\n      } else {\n        x->parent->right\
    \ = l;\n      }\n    } else {\n      root_ = l;\n    }\n    (l->right = x)->parent\
    \ = l;\n  }\n};\n\n} // namespace lib\n\n\n#line 10 \"datastructure/tree/treap.hpp\"\
    \n\n// TODO\nnamespace lib {} // namespace lib\n\n\n"
  code: "#ifndef TREAP_HEADER_HPP\n#define TREAP_HEADER_HPP\n\n/**\n * @brief Treap\
    \ / \u6811\u5806\n *\n */\n\n#include \"binary_search_tree_base.hpp\"\n\n// TODO\n\
    namespace lib {} // namespace lib\n\n#endif"
  dependsOn:
  - datastructure/tree/binary_search_tree_base.hpp
  isVerificationFile: false
  path: datastructure/tree/treap.hpp
  requiredBy: []
  timestamp: '2021-06-17 19:06:03+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/tree/treap.hpp
layout: document
redirect_from:
- /library/datastructure/tree/treap.hpp
- /library/datastructure/tree/treap.hpp.html
title: "Treap / \u6811\u5806"
---
