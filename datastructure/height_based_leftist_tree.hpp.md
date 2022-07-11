---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizu/datastructure/priority_queue.0.test.cpp
    title: remote_test/aizu/datastructure/priority_queue.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/height_based_leftist_tree.hpp\"\n\n\n\n#line\
    \ 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib\
    \ {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/height_based_leftist_tree.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <functional>\n\
    #include <iterator>\n#include <memory>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n\nLIB_BEGIN\n\n// Min Heap\ntemplate <typename T, typename\
    \ CmpT>\nclass height_based_leftist_tree {\n  static_assert(std::is_copy_constructible_v<T>);\n\
    \n  class node {\n  public:\n    node *left_{}, *right_{}, *parent_{};\n    int\
    \ rank_{1}; // a.k.a. s value\n    T value_;\n    explicit node(const T &value)\
    \ : value_(value) {}\n    ~node() {\n      delete left_;\n      delete right_;\n\
    \    }\n  } * root_{};\n  CmpT cmp_;\n  std::size_t size_{};\n\n  static std::size_t\
    \ s(node *a) { return a != nullptr ? a->rank_ : 0; }\n\n  node *meld(node *a,\
    \ node *b) {\n    if (a == nullptr) return b;\n    if (b == nullptr) return a;\n\
    \    if (!cmp_(a->value_, b->value_)) std::swap(a, b);\n    if (a->right_ != nullptr)\
    \ a->right_->parent_ = nullptr;\n    if (((a->right_ = meld(a->right_, b))->parent_\
    \ = a)->left_ == nullptr ||\n        a->left_->rank_ < a->right_->rank_)\n   \
    \   std::swap(a->left_, a->right_);\n    a->rank_ = s(a->right_) + 1;\n    return\
    \ a;\n  }\n\npublic:\n  using value_type       = T;\n  using pointer         \
    \ = node *;\n  using const_pointer    = const node *;\n  using size_type     \
    \   = std::size_t;\n  using signed_size_type = std::make_signed_t<std::size_t>;\n\
    \n  class wrapper {\n    const node *p_{};\n\n  public:\n    wrapper() = default;\n\
    \    wrapper(const node *p) : p_(p) {}\n    const T &operator*() const { return\
    \ *p_; }\n    const node *data() const { return p_; }\n  };\n\n  explicit height_based_leftist_tree(CmpT\
    \ cmp = CmpT()) : cmp_(cmp) {}\n  template <\n      typename IterT,\n      std::enable_if_t<std::is_convertible_v<typename\
    \ std::iterator_traits<IterT>::value_type, T>,\n                       int> =\
    \ 0>\n  height_based_leftist_tree(IterT begin, IterT end, CmpT cmp = CmpT())\n\
    \      : cmp_(cmp), size_(end - begin) {\n    std::queue<node *> q;\n    for (;\
    \ begin != end; ++begin) q.push(new node(*begin));\n    while (q.size() > 1) {\n\
    \      node *a = q.front();\n      q.pop();\n      node *b = q.front();\n    \
    \  q.pop();\n      q.push(meld(a, b));\n    }\n    if (!q.empty()) root_ = q.front();\n\
    \  }\n  height_based_leftist_tree(const height_based_leftist_tree &) = delete;\n\
    \  ~height_based_leftist_tree() { delete root_; }\n  height_based_leftist_tree\
    \ &operator=(const height_based_leftist_tree &) = delete;\n\n  bool empty() const\
    \ { return root_ == nullptr; }\n  std::size_t size() const { return size_; }\n\
    \  std::make_signed_t<std::size_t> ssize() const { return size_; }\n  wrapper\
    \ push(const T &value) {\n    node *p = new node(value);\n    root_   = meld(root_,\
    \ p);\n    ++size_;\n    return wrapper(p);\n  }\n  T top() const { return root_->value_;\
    \ }\n  T pop(wrapper wp) {\n    node *p = const_cast<node *>(wp.data()), *pp =\
    \ p->parent_;\n    if (p->left_ != nullptr) {\n      p->left_->parent_ = nullptr;\n\
    \      if (p->right_ != nullptr) p->right_->parent_ = nullptr;\n    }\n    if\
    \ (pp != nullptr) {\n      if (pp->left_ == p) {\n        if ((pp->left_ = meld(p->left_,\
    \ p->right_)) != nullptr) pp->left_->parent_ = pp;\n      } else {\n        if\
    \ ((pp->right_ = meld(p->left_, p->right_)) != nullptr) pp->right_->parent_ =\
    \ pp;\n      }\n      // Only could be done with height-based variant?\n     \
    \ for (; pp != nullptr; pp = pp->parent_) {\n        if (s(pp->left_) < s(pp->right_))\
    \ std::swap(pp->left_, pp->right_);\n        if (pp->rank_ != s(pp->right_) +\
    \ 1) {\n          pp->rank_ = s(pp->right_) + 1;\n        } else {\n         \
    \ break;\n        }\n      }\n    } else {\n      root_ = meld(p->left_, p->right_);\n\
    \    }\n    T res(p->value_);\n    p->left_ = p->right_ = nullptr;\n    delete\
    \ p;\n    --size_;\n    return res;\n  }\n  T pop() {\n    assert(!empty());\n\
    \    node *p = root_;\n    T res(p->value_);\n    if (p->left_ != nullptr) {\n\
    \      p->left_->parent_ = nullptr;\n      if (p->right_ != nullptr) p->right_->parent_\
    \ = nullptr;\n    }\n    root_    = meld(p->left_, p->right_);\n    p->left_ =\
    \ p->right_ = nullptr;\n    delete p;\n    --size_;\n    return res;\n  }\n  height_based_leftist_tree\
    \ &meld(height_based_leftist_tree &rhs) {\n    if (this != std::addressof(rhs))\
    \ {\n      size_ += rhs.size_;\n      root_     = meld(root_, rhs.root_);\n  \
    \    rhs.root_ = nullptr;\n      rhs.size_ = 0;\n    }\n    return *this;\n  }\n\
    };\n\ntemplate <typename T, typename CmpT = std::less<>>\nusing hblt = height_based_leftist_tree<T,\
    \ CmpT>;\n\nLIB_END\n\n\n"
  code: "#ifndef HEIGHT_BASED_LEFTIST_TREE_HPP\n#define HEIGHT_BASED_LEFTIST_TREE_HPP\n\
    \n#include \"../common.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <functional>\n#include <iterator>\n#include <memory>\n#include\
    \ <queue>\n#include <type_traits>\n#include <utility>\n\nLIB_BEGIN\n\n// Min Heap\n\
    template <typename T, typename CmpT>\nclass height_based_leftist_tree {\n  static_assert(std::is_copy_constructible_v<T>);\n\
    \n  class node {\n  public:\n    node *left_{}, *right_{}, *parent_{};\n    int\
    \ rank_{1}; // a.k.a. s value\n    T value_;\n    explicit node(const T &value)\
    \ : value_(value) {}\n    ~node() {\n      delete left_;\n      delete right_;\n\
    \    }\n  } * root_{};\n  CmpT cmp_;\n  std::size_t size_{};\n\n  static std::size_t\
    \ s(node *a) { return a != nullptr ? a->rank_ : 0; }\n\n  node *meld(node *a,\
    \ node *b) {\n    if (a == nullptr) return b;\n    if (b == nullptr) return a;\n\
    \    if (!cmp_(a->value_, b->value_)) std::swap(a, b);\n    if (a->right_ != nullptr)\
    \ a->right_->parent_ = nullptr;\n    if (((a->right_ = meld(a->right_, b))->parent_\
    \ = a)->left_ == nullptr ||\n        a->left_->rank_ < a->right_->rank_)\n   \
    \   std::swap(a->left_, a->right_);\n    a->rank_ = s(a->right_) + 1;\n    return\
    \ a;\n  }\n\npublic:\n  using value_type       = T;\n  using pointer         \
    \ = node *;\n  using const_pointer    = const node *;\n  using size_type     \
    \   = std::size_t;\n  using signed_size_type = std::make_signed_t<std::size_t>;\n\
    \n  class wrapper {\n    const node *p_{};\n\n  public:\n    wrapper() = default;\n\
    \    wrapper(const node *p) : p_(p) {}\n    const T &operator*() const { return\
    \ *p_; }\n    const node *data() const { return p_; }\n  };\n\n  explicit height_based_leftist_tree(CmpT\
    \ cmp = CmpT()) : cmp_(cmp) {}\n  template <\n      typename IterT,\n      std::enable_if_t<std::is_convertible_v<typename\
    \ std::iterator_traits<IterT>::value_type, T>,\n                       int> =\
    \ 0>\n  height_based_leftist_tree(IterT begin, IterT end, CmpT cmp = CmpT())\n\
    \      : cmp_(cmp), size_(end - begin) {\n    std::queue<node *> q;\n    for (;\
    \ begin != end; ++begin) q.push(new node(*begin));\n    while (q.size() > 1) {\n\
    \      node *a = q.front();\n      q.pop();\n      node *b = q.front();\n    \
    \  q.pop();\n      q.push(meld(a, b));\n    }\n    if (!q.empty()) root_ = q.front();\n\
    \  }\n  height_based_leftist_tree(const height_based_leftist_tree &) = delete;\n\
    \  ~height_based_leftist_tree() { delete root_; }\n  height_based_leftist_tree\
    \ &operator=(const height_based_leftist_tree &) = delete;\n\n  bool empty() const\
    \ { return root_ == nullptr; }\n  std::size_t size() const { return size_; }\n\
    \  std::make_signed_t<std::size_t> ssize() const { return size_; }\n  wrapper\
    \ push(const T &value) {\n    node *p = new node(value);\n    root_   = meld(root_,\
    \ p);\n    ++size_;\n    return wrapper(p);\n  }\n  T top() const { return root_->value_;\
    \ }\n  T pop(wrapper wp) {\n    node *p = const_cast<node *>(wp.data()), *pp =\
    \ p->parent_;\n    if (p->left_ != nullptr) {\n      p->left_->parent_ = nullptr;\n\
    \      if (p->right_ != nullptr) p->right_->parent_ = nullptr;\n    }\n    if\
    \ (pp != nullptr) {\n      if (pp->left_ == p) {\n        if ((pp->left_ = meld(p->left_,\
    \ p->right_)) != nullptr) pp->left_->parent_ = pp;\n      } else {\n        if\
    \ ((pp->right_ = meld(p->left_, p->right_)) != nullptr) pp->right_->parent_ =\
    \ pp;\n      }\n      // Only could be done with height-based variant?\n     \
    \ for (; pp != nullptr; pp = pp->parent_) {\n        if (s(pp->left_) < s(pp->right_))\
    \ std::swap(pp->left_, pp->right_);\n        if (pp->rank_ != s(pp->right_) +\
    \ 1) {\n          pp->rank_ = s(pp->right_) + 1;\n        } else {\n         \
    \ break;\n        }\n      }\n    } else {\n      root_ = meld(p->left_, p->right_);\n\
    \    }\n    T res(p->value_);\n    p->left_ = p->right_ = nullptr;\n    delete\
    \ p;\n    --size_;\n    return res;\n  }\n  T pop() {\n    assert(!empty());\n\
    \    node *p = root_;\n    T res(p->value_);\n    if (p->left_ != nullptr) {\n\
    \      p->left_->parent_ = nullptr;\n      if (p->right_ != nullptr) p->right_->parent_\
    \ = nullptr;\n    }\n    root_    = meld(p->left_, p->right_);\n    p->left_ =\
    \ p->right_ = nullptr;\n    delete p;\n    --size_;\n    return res;\n  }\n  height_based_leftist_tree\
    \ &meld(height_based_leftist_tree &rhs) {\n    if (this != std::addressof(rhs))\
    \ {\n      size_ += rhs.size_;\n      root_     = meld(root_, rhs.root_);\n  \
    \    rhs.root_ = nullptr;\n      rhs.size_ = 0;\n    }\n    return *this;\n  }\n\
    };\n\ntemplate <typename T, typename CmpT = std::less<>>\nusing hblt = height_based_leftist_tree<T,\
    \ CmpT>;\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/height_based_leftist_tree.hpp
  requiredBy: []
  timestamp: '2022-07-11 21:13:24+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizu/datastructure/priority_queue.0.test.cpp
documentation_of: datastructure/height_based_leftist_tree.hpp
layout: document
title: Height-Based Leftist Tree
---
