---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: datastructure/tree/binary_search_tree_base.hpp
    title: "binary search tree base / \u4E8C\u53C9\u641C\u7D22\u6811\u57FA\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/datastructure/predecessor_problem.1.test.cpp
    title: remote_test/yosupo/datastructure/predecessor_problem.1.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "AVL tree / AVL \u6811"
    links: []
  bundledCode: "#line 1 \"datastructure/tree/AVL_tree.hpp\"\n\n\n\n/**\n * @brief\
    \ AVL tree / AVL \u6811\n *\n */\n\n#include <algorithm>\n\n#line 1 \"datastructure/tree/binary_search_tree_base.hpp\"\
    \n\n\n\n/**\n * @brief binary search tree base / \u4E8C\u53C9\u641C\u7D22\u6811\
    \u57FA\u7C7B\n *\n */\n\n#include <cassert>\n#include <functional>\n#include <optional>\n\
    \nnamespace lib {\n\n/**\n * @brief \u4E8C\u53C9\u641C\u7D22\u6811\u8282\u70B9\
    \u7C7B\n */\ntemplate <typename DataType, typename Base> struct BSTNodeType1 :\
    \ public Base {\npublic:\n  using node_ptr_type = BSTNodeType1 *;\n  using value_type\
    \ = DataType;\n\n  BSTNodeType1(const value_type &v)\n      : left(nullptr), right(nullptr),\
    \ parent(nullptr), size(1), data(v) {}\n  ~BSTNodeType1() {\n    delete left;\n\
    \    delete right;\n  }\n\n  node_ptr_type left, right, parent;\n  int size;\n\
    \  value_type data;\n};\n\n/**\n * @brief \u4E8C\u53C9\u641C\u7D22\u6811\u57FA\
    \u7C7B\n */\ntemplate <typename NodeType, typename Comp = std::less<>> class BSTType1\
    \ {\npublic:\n  using node_ptr_type = typename NodeType::node_ptr_type;\n  using\
    \ const_node_ptr_type = const node_ptr_type;\n  using value_type = typename NodeType::value_type;\n\
    \n#ifdef LOCAL\n\n  virtual void test() {\n    dfs(root_);\n    std::cout << \"\
    \\ntest over\\n\";\n  }\n\n  virtual void dfs(const_node_ptr_type x) {\n    if\
    \ (x == nullptr) return;\n    if (x->left != nullptr) dfs(x->left);\n    std::cout\
    \ << x->data << ' ';\n    if (x->right != nullptr) dfs(x->right);\n  }\n\n#endif\n\
    \n  BSTType1(const Comp &cmp) : root_(nullptr), cmp_(cmp) {}\n  BSTType1() : BSTType1(Comp())\
    \ {}\n  virtual ~BSTType1() { delete root_; }\n\n  bool is_empty() const { return\
    \ root_ == nullptr; }\n  int size() const { return get_size(root_); }\n  bool\
    \ is_in_tree(const value_type &v) const { return find_node(v) != nullptr; }\n\n\
    \  /**\n   * @brief \u9009\u62E9\u7B2C k \u4E2A\u5143\u7D20\n   * @note \u7D22\
    \u5F15\u4ECE 0 \u5F00\u59CB\n   * @param k\n   * @return std::opetional<value_type>\n\
    \   */\n  virtual std::optional<value_type> select(int k) const {\n    const_node_ptr_type\
    \ x = select_node(k);\n    if (x == nullptr) return {};\n    return x->data;\n\
    \  }\n\n  /**\n   * @brief \u6C42\u51FA v \u5728\u6811\u4E2D\u7684\u6392\u540D\
    \n   * @note \u5728\u6811\u4E2D\u6709\u591A\u5C11\u6BD4 v \u5C0F\u7684\u5143\u7D20\
    \uFF0C v \u4E0D\u5FC5\u5728\u6811\u4E2D\n   * @param v\n   * @return int\n   */\n\
    \  virtual int get_rank(const value_type &v) const {\n    int res = 0;\n    node_ptr_type\
    \ x = root_;\n    while (x != nullptr) {\n      if (cmp_(v, x->data)) {\n    \
    \    x = x->left;\n      } else if (cmp_(x->data, v)) {\n        res += get_size(x->left)\
    \ + 1;\n        x = x->right;\n      } else {\n        x = x->left;\n      }\n\
    \    }\n    return res;\n  }\n\n  virtual std::optional<value_type> less_than(const\
    \ value_type &v) const {\n    node_ptr_type x = root_, res = nullptr;\n    while\
    \ (x != nullptr) {\n      if (cmp_(x->data, v)) {\n        res = x, x = x->right;\n\
    \      } else {\n        x = x->left;\n      }\n    }\n    if (res == nullptr)\
    \ return {};\n    return res->data;\n  }\n  virtual std::optional<value_type>\
    \ less_equal(const value_type &v) const {\n    node_ptr_type x = root_, res =\
    \ nullptr;\n    while (x != nullptr) {\n      if (cmp_(v, x->data)) {\n      \
    \  x = x->left;\n      } else {\n        res = x, x = x->right;\n      }\n   \
    \ }\n    if (res == nullptr) return {};\n    return res->data;\n  }\n  virtual\
    \ std::optional<value_type> greater_than(const value_type &v) const {\n    node_ptr_type\
    \ x = root_, res = nullptr;\n    while (x != nullptr) {\n      if (cmp_(v, x->data))\
    \ {\n        res = x, x = x->left;\n      } else {\n        x = x->right;\n  \
    \    }\n    }\n    if (res == nullptr) return {};\n    return res->data;\n  }\n\
    \  virtual std::optional<value_type> greater_equal(const value_type &v) const\
    \ {\n    node_ptr_type x = root_, res = nullptr;\n    while (x != nullptr) {\n\
    \      if (cmp_(x->data, v)) {\n        x = x->right;\n      } else {\n      \
    \  res = x, x = x->left;\n      }\n    }\n    if (res == nullptr) return {};\n\
    \    return res->data;\n  }\n\n  virtual const_node_ptr_type insert_at_value(const\
    \ value_type &v) {\n    node_ptr_type x = new NodeType(v);\n    insert_at_value(x);\n\
    \    return x;\n  }\n  virtual bool delete_at_value(const value_type &v) {\n \
    \   node_ptr_type x = find_node(v);\n    if (x == nullptr) return false;\n   \
    \ delete_at_node(x);\n    return true;\n  }\n  virtual const_node_ptr_type insert_at_rank(const\
    \ value_type &v, int k) {\n    node_ptr_type x = new NodeType(v);\n    insert_at_rank(x,\
    \ k);\n    return x;\n  }\n  virtual bool delete_at_rank(int k) {\n    node_ptr_type\
    \ x = select_node(k);\n    if (x == nullptr) return false;\n    delete_at_node(x);\n\
    \    return true;\n  }\n\n  /**\n   * @brief \u5220\u9664\u8282\u70B9\u8F85\u52A9\
    \u51FD\u6570\n   * @note \u7528\u53F3\u5B50\u6811\u7684\u6700\u5C0F\u503C\uFF08\
    \u6216\u5DE6\u5B50\u6811\u7684\u6700\u5927\u503C\uFF09\u66FF\u4EE3\u5F53\u524D\
    \u8282\u70B9\n   * @param x\n   */\n  virtual void delete_at_node(node_ptr_type\
    \ x) {\n    assert(x != nullptr);\n    for (node_ptr_type t = x; t != nullptr;\
    \ t = t->parent) --(t->size);\n    if (x->left == nullptr) { // x \u5DE6\u5B50\
    \u6811\u4E3A\u7A7A\u6216\u5DE6\u53F3\u5B50\u6811\u90FD\u4E3A\u7A7A\n      node_ptr_type\
    \ r = x->right;\n      if (x->parent != nullptr) {\n        if (x == x->parent->left)\
    \ {\n          x->parent->left = r;\n        } else {\n          x->parent->right\
    \ = r;\n        }\n        if (r != nullptr) r->parent = x->parent;\n      } else\
    \ {\n        if ((root_ = r) != nullptr) r->parent = nullptr;\n      }\n    }\
    \ else if (x->right == nullptr) { // x \u53EA\u6709\u53F3\u5B50\u6811\u4E3A\u7A7A\
    \n      node_ptr_type l = x->left;\n      if (x->parent != nullptr) {\n      \
    \  if (x == x->parent->left) {\n          x->parent->left = l;\n        } else\
    \ {\n          x->parent->right = l;\n        }\n        l->parent = x->parent;\n\
    \      } else {\n        (root_ = l)->parent = nullptr;\n      }\n    } else {\
    \ // x \u5DE6\u53F3\u5B50\u6811\u90FD\u4E0D\u4E3A\u7A7A\n      node_ptr_type r\
    \ = x->right;\n      while (r->left != nullptr) { // \u7528\u53F3\u5B50\u6811\u7684\
    \u6700\u5C0F\u8282\u70B9 r \u66FF\u6362 x \uFF0C\u5E76\u4E00\u8DEF\u4FEE\u6539\
    \u5BF9\u5E94 size\n        --(r->size);\n        r = r->left;\n      }\n     \
    \ if (r->parent == x) { // \u53F3\u5B50\u6811\u6700\u5C0F\u8282\u70B9\u5C31\u662F\
    \ x \u7684\u53F3\u5B69\u5B50\n        x->right = nullptr;\n      } else {\n  \
    \      r->parent->left = nullptr;\n      }\n      r->parent = x->parent;\n   \
    \   (r->left = x->left)->parent = r;\n      if (x->right != nullptr) (r->right\
    \ = x->right)->parent = r;\n      r->size = x->size;\n      if (x->parent != nullptr)\
    \ {\n        if (x == x->parent->left) {\n          x->parent->left = r;\n   \
    \     } else {\n          x->parent->right = r;\n        }\n      } else {\n \
    \       root_ = r;\n      }\n    }\n    x->left = x->right = nullptr;\n    delete\
    \ x;\n  }\n\nprotected:\n  mutable node_ptr_type root_;\n  Comp cmp_;\n\n  /**\n\
    \   * @brief \u63D2\u5165\u8282\u70B9\u8F85\u52A9\u51FD\u6570\n   * @note \u4F7F\
    \u7528\u8BE5\u51FD\u6570\u53EF\u4EE5\u51CF\u5C11\u7EE7\u627F\u540E override \u7684\
    \u51FD\u6570\n   * @param x \u5F85\u63D2\u5165\u8282\u70B9\n   * @param p \u5F85\
    \u63D2\u5165\u8282\u70B9\u7684\u53CC\u4EB2\u8282\u70B9\n   * @param dir \u82E5\
    \ dir=0 \u5219 x \u6210\u4E3A p \u7684\u5DE6\u5B69\u5B50\uFF0C\u5426\u5219\u6210\
    \u4E3A\u53F3\u5B69\u5B50\n   */\n  virtual void insert_at_node(node_ptr_type x,\
    \ node_ptr_type p, int dir) {\n    if (p == nullptr) {\n      root_ = x;\n   \
    \ } else {\n      if (dir == 0) {\n        p->left = x;\n      } else {\n    \
    \    p->right = x;\n      }\n      x->parent = p;\n    }\n  }\n\n  virtual node_ptr_type\
    \ find_node(const value_type &v) const {\n    node_ptr_type x = root_;\n    while\
    \ (x != nullptr) {\n      if (cmp_(x->data, v)) {\n        x = x->right;\n   \
    \   } else if (cmp_(v, x->data)) {\n        x = x->left;\n      } else {\n   \
    \     return x;\n      }\n    }\n    return x;\n  }\n\n  virtual node_ptr_type\
    \ select_node(int k) const {\n    if (k < 0 || k >= size()) return {};\n    node_ptr_type\
    \ x = root_;\n    while (get_size(x->left) != k) {\n      if (get_size(x->left)\
    \ < k) {\n        k -= get_size(x->left) + 1;\n        x = x->right;\n      }\
    \ else {\n        x = x->left;\n      }\n    }\n    return x;\n  }\n\n  virtual\
    \ void insert_at_value(node_ptr_type x) {\n    node_ptr_type p = nullptr, y =\
    \ root_;\n    int dir = -1;\n    while (y != nullptr) {\n      p = y;\n      ++(y->size);\n\
    \      if (cmp_(x->data, y->data)) {\n        y = y->left;\n        dir = 0;\n\
    \      } else {\n        y = y->right;\n        dir = 1;\n      }\n    }\n   \
    \ insert_at_node(x, p, dir);\n  }\n\n  /**\n   * @brief \u5728\u6392\u540D k \u7684\
    \u5143\u7D20\u524D\u63D2\u5165\u4E00\u4E2A\u5143\u7D20\n   * @note \u6392\u540D\
    \u4ECE 0 \u5F00\u59CB\n   * @param x\n   */\n  virtual void insert_at_rank(node_ptr_type\
    \ x, int k) {\n    assert(k >= 0);\n    assert(k < size());\n    node_ptr_type\
    \ p = nullptr, y = root_;\n    int dir = -1;\n    while (y != nullptr) {\n   \
    \   p = y;\n      ++(y->size);\n      if (k <= get_size(y->left)) {\n        y\
    \ = y->left;\n        dir = 0;\n      } else {\n        y = y->right;\n      \
    \  k -= get_size(y->left) + 1;\n        dir = 1;\n      }\n    }\n    insert_at_node(x,\
    \ p, dir);\n  }\n\n  static int get_size(const_node_ptr_type x) { return x ==\
    \ nullptr ? 0 : x->size; }\n\n  virtual void rotate_left(node_ptr_type x) const\
    \ {\n    assert(x != nullptr);\n    assert(x->right != nullptr);\n    node_ptr_type\
    \ r = x->right, rl = r->left;\n    int rs = r->size;\n    r->size = x->size;\n\
    \    x->size -= rs;\n    if ((x->right = rl) != nullptr) (rl->parent = x)->size\
    \ += rl->size;\n    if ((r->parent = x->parent) != nullptr) {\n      if (x->parent->left\
    \ == x) {\n        x->parent->left = r;\n      } else {\n        x->parent->right\
    \ = r;\n      }\n    } else {\n      root_ = r;\n    }\n    (r->left = x)->parent\
    \ = r;\n  }\n  virtual void rotate_right(node_ptr_type x) const {\n    assert(x\
    \ != nullptr);\n    assert(x->left != nullptr);\n    node_ptr_type l = x->left,\
    \ lr = l->right;\n    int ls = l->size;\n    l->size = x->size;\n    x->size -=\
    \ ls;\n    if ((x->left = lr) != nullptr) (lr->parent = x)->size += lr->size;\n\
    \    if ((l->parent = x->parent) != nullptr) {\n      if (x->parent->left == x)\
    \ {\n        x->parent->left = l;\n      } else {\n        x->parent->right =\
    \ l;\n      }\n    } else {\n      root_ = l;\n    }\n    (l->right = x)->parent\
    \ = l;\n  }\n};\n\n} // namespace lib\n\n\n#line 12 \"datastructure/tree/AVL_tree.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief AVL \u6811\u8282\u70B9\u7C7B\n */\nstruct\
    \ AVLTreeNode {\npublic:\n  AVLTreeNode() : height(1) {}\n  ~AVLTreeNode() = default;\n\
    \  int height;\n};\n\n/**\n * @brief AVL \u6811\n */\ntemplate <typename DataType,\
    \ typename Comp = std::less<>>\nclass AVLTree final : public BSTType1<BSTNodeType1<DataType,\
    \ AVLTreeNode>, Comp> {\npublic:\n  using base = BSTType1<BSTNodeType1<DataType,\
    \ AVLTreeNode>, Comp>;\n  using base::base;\n  using value_type = typename base::value_type;\n\
    \  using node_ptr_type = typename base::node_ptr_type;\n  using const_node_ptr_type\
    \ = typename base::const_node_ptr_type;\n\n  static int get_height(const_node_ptr_type\
    \ x) { return x == nullptr ? 0 : x->height; }\n\n  void insert_at_node(node_ptr_type\
    \ x, node_ptr_type p, int dir) override {\n    base::insert_at_node(x, p, dir);\n\
    \    fix_up(p);\n  }\n  void delete_at_node(node_ptr_type x) override {\n    node_ptr_type\
    \ y;\n    if (x->left == nullptr || x->right == nullptr) {\n      y = x->parent;\n\
    \    } else {\n      y = x->right;\n      while (y->left != nullptr) y = y->left;\n\
    \      if (y->parent != x) y = y->parent;\n    }\n    base::delete_at_node(x);\n\
    \    fix_up(y);\n  }\n\nprotected:\n  static void fix_height(node_ptr_type x)\
    \ {\n    if (x == nullptr) return;\n    x->height = std::max(get_height(x->left),\
    \ get_height(x->right)) + 1;\n  }\n\n  void fix_up(node_ptr_type x) {\n    fix_height(x);\n\
    \    for (node_ptr_type y = x; y != nullptr && !is_balanced(y);) {\n      node_ptr_type\
    \ t = y->parent;\n      balance(y);\n      fix_height(t);\n      y = t;\n    }\n\
    \  }\n\n  void rotate_left(node_ptr_type x) const override {\n    node_ptr_type\
    \ r = x->right;\n    base::rotate_left(x);\n    fix_height(x);\n    fix_height(r);\n\
    \  }\n\n  void rotate_right(node_ptr_type x) const override {\n    node_ptr_type\
    \ l = x->left;\n    base::rotate_right(x);\n    fix_height(x);\n    fix_height(l);\n\
    \  }\n\n  /**\n   * @brief \u5224\u65AD\u662F\u5426\u5E73\u8861\n   * @note \u5E73\
    \u8861\u7684\u8BDD\u5DE6\u53F3\u5B50\u6811\u9AD8\u5EA6\u76F8\u51CF\u7684\u7EDD\
    \u5BF9\u503C\u5C0F\u4E8E 2 \u4E0D\u5E73\u8861\u7684\u8BDD\u5219\u7B49\u4E8E 2\n\
    \   */\n  static bool is_balanced(node_ptr_type x) {\n    assert(x != nullptr);\n\
    \    int d = get_height(x->left) - get_height(x->right);\n    return d >= -1 &&\
    \ d <= 1;\n  }\n  /**\n   * @brief \u8FD4\u56DE\u66F4\u9AD8\u7684\u4E00\u4E2A\u5B69\
    \u5B50\u8282\u70B9\n   * @return std::pair<node_ptr_type, int> \u4E3A\u5B69\u5B50\
    \u8282\u70B9\u548C\u5176\u4E3A\u5DE6\u5B69\u5B50\u8FD8\u662F\u53F3\u5B69\u5B50\
    \n   */\n  static std::pair<node_ptr_type, int> get_taller_child(node_ptr_type\
    \ x) {\n    assert(x != nullptr);\n    return get_height(x->left) > get_height(x->right)\
    \ ? std::make_pair(x->left, 0)\n                                             \
    \         : std::make_pair(x->right, 1);\n  }\n  void balance(node_ptr_type z)\
    \ {\n    auto [y, dy] = get_taller_child(z);\n    auto [x, dx] = get_taller_child(y);\n\
    \    /*     z           z\n          / \\         / \\\n         y   ?   or  ?\
    \   y      case 1: dx=dy\n        / \\             / \\\n       x   ?        \
    \   ?   x   */\n    if (dx != dy) dy == 0 ? rotate_left(y) : rotate_right(y);\n\
    \    /*     z           z\n          / \\         / \\\n         y   ?   or  ?\
    \   y      case 2: dx!=dy\n        / \\             / \\\n       ?   x       \
    \    x   ?   */\n    dy == 0 ? rotate_right(z) : rotate_left(z);\n  }\n};\n\n\
    } // namespace lib\n\n\n"
  code: "#ifndef AVL_TREE_HEADER_HPP\n#define AVL_TREE_HEADER_HPP\n\n/**\n * @brief\
    \ AVL tree / AVL \u6811\n *\n */\n\n#include <algorithm>\n\n#include \"binary_search_tree_base.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief AVL \u6811\u8282\u70B9\u7C7B\n */\nstruct\
    \ AVLTreeNode {\npublic:\n  AVLTreeNode() : height(1) {}\n  ~AVLTreeNode() = default;\n\
    \  int height;\n};\n\n/**\n * @brief AVL \u6811\n */\ntemplate <typename DataType,\
    \ typename Comp = std::less<>>\nclass AVLTree final : public BSTType1<BSTNodeType1<DataType,\
    \ AVLTreeNode>, Comp> {\npublic:\n  using base = BSTType1<BSTNodeType1<DataType,\
    \ AVLTreeNode>, Comp>;\n  using base::base;\n  using value_type = typename base::value_type;\n\
    \  using node_ptr_type = typename base::node_ptr_type;\n  using const_node_ptr_type\
    \ = typename base::const_node_ptr_type;\n\n  static int get_height(const_node_ptr_type\
    \ x) { return x == nullptr ? 0 : x->height; }\n\n  void insert_at_node(node_ptr_type\
    \ x, node_ptr_type p, int dir) override {\n    base::insert_at_node(x, p, dir);\n\
    \    fix_up(p);\n  }\n  void delete_at_node(node_ptr_type x) override {\n    node_ptr_type\
    \ y;\n    if (x->left == nullptr || x->right == nullptr) {\n      y = x->parent;\n\
    \    } else {\n      y = x->right;\n      while (y->left != nullptr) y = y->left;\n\
    \      if (y->parent != x) y = y->parent;\n    }\n    base::delete_at_node(x);\n\
    \    fix_up(y);\n  }\n\nprotected:\n  static void fix_height(node_ptr_type x)\
    \ {\n    if (x == nullptr) return;\n    x->height = std::max(get_height(x->left),\
    \ get_height(x->right)) + 1;\n  }\n\n  void fix_up(node_ptr_type x) {\n    fix_height(x);\n\
    \    for (node_ptr_type y = x; y != nullptr && !is_balanced(y);) {\n      node_ptr_type\
    \ t = y->parent;\n      balance(y);\n      fix_height(t);\n      y = t;\n    }\n\
    \  }\n\n  void rotate_left(node_ptr_type x) const override {\n    node_ptr_type\
    \ r = x->right;\n    base::rotate_left(x);\n    fix_height(x);\n    fix_height(r);\n\
    \  }\n\n  void rotate_right(node_ptr_type x) const override {\n    node_ptr_type\
    \ l = x->left;\n    base::rotate_right(x);\n    fix_height(x);\n    fix_height(l);\n\
    \  }\n\n  /**\n   * @brief \u5224\u65AD\u662F\u5426\u5E73\u8861\n   * @note \u5E73\
    \u8861\u7684\u8BDD\u5DE6\u53F3\u5B50\u6811\u9AD8\u5EA6\u76F8\u51CF\u7684\u7EDD\
    \u5BF9\u503C\u5C0F\u4E8E 2 \u4E0D\u5E73\u8861\u7684\u8BDD\u5219\u7B49\u4E8E 2\n\
    \   */\n  static bool is_balanced(node_ptr_type x) {\n    assert(x != nullptr);\n\
    \    int d = get_height(x->left) - get_height(x->right);\n    return d >= -1 &&\
    \ d <= 1;\n  }\n  /**\n   * @brief \u8FD4\u56DE\u66F4\u9AD8\u7684\u4E00\u4E2A\u5B69\
    \u5B50\u8282\u70B9\n   * @return std::pair<node_ptr_type, int> \u4E3A\u5B69\u5B50\
    \u8282\u70B9\u548C\u5176\u4E3A\u5DE6\u5B69\u5B50\u8FD8\u662F\u53F3\u5B69\u5B50\
    \n   */\n  static std::pair<node_ptr_type, int> get_taller_child(node_ptr_type\
    \ x) {\n    assert(x != nullptr);\n    return get_height(x->left) > get_height(x->right)\
    \ ? std::make_pair(x->left, 0)\n                                             \
    \         : std::make_pair(x->right, 1);\n  }\n  void balance(node_ptr_type z)\
    \ {\n    auto [y, dy] = get_taller_child(z);\n    auto [x, dx] = get_taller_child(y);\n\
    \    /*     z           z\n          / \\         / \\\n         y   ?   or  ?\
    \   y      case 1: dx=dy\n        / \\             / \\\n       x   ?        \
    \   ?   x   */\n    if (dx != dy) dy == 0 ? rotate_left(y) : rotate_right(y);\n\
    \    /*     z           z\n          / \\         / \\\n         y   ?   or  ?\
    \   y      case 2: dx!=dy\n        / \\             / \\\n       ?   x       \
    \    x   ?   */\n    dy == 0 ? rotate_right(z) : rotate_left(z);\n  }\n};\n\n\
    } // namespace lib\n\n#endif"
  dependsOn:
  - datastructure/tree/binary_search_tree_base.hpp
  isVerificationFile: false
  path: datastructure/tree/AVL_tree.hpp
  requiredBy: []
  timestamp: '2021-06-20 13:23:41+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/datastructure/predecessor_problem.1.test.cpp
documentation_of: datastructure/tree/AVL_tree.hpp
layout: document
redirect_from:
- /library/datastructure/tree/AVL_tree.hpp
- /library/datastructure/tree/AVL_tree.hpp.html
title: "AVL tree / AVL \u6811"
---
