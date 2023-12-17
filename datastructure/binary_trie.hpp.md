---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/set_xor_min.0.test.cpp
    title: remote_test/yosupo/datastructure/set_xor_min.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/binary_trie.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/binary_trie.hpp\"\n\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\n\
    LIB_BEGIN\n\ntemplate <int BitT>\nclass binary_trie {\n  class node {\n  public:\n\
    \    node *ch_[2]{};\n    int cnt_{};\n    ~node() {\n      delete ch_[0];\n \
    \     delete ch_[1];\n    }\n    bool is_leaf() const { return ch_[0] == ch_[1];\
    \ }\n  };\n\n  mutable std::array<node *, BitT + 1> s_;\n\npublic:\n  static_assert(BitT\
    \ > 0 && BitT <= 64);\n  using value_type = std::conditional_t<BitT <= 32, std::uint32_t,\
    \ std::uint64_t>;\n\n  binary_trie() { s_.back() = new node; }\n  binary_trie(const\
    \ binary_trie &) = delete;\n  binary_trie(binary_trie &&)      = delete;\n  ~binary_trie()\
    \ { delete s_.back(); }\n  binary_trie &operator=(const binary_trie &) = delete;\n\
    \  binary_trie &operator=(binary_trie &&)      = delete;\n\n  bool empty() const\
    \ { return s_.back()->ch_[0] == s_.back()->ch_[1]; }\n\n  void insert(value_type\
    \ a) {\n    auto c = s_.back();\n    for (int i = BitT - 1; i >= 0; --i) {\n \
    \     auto j = (a >> i) & 1;\n      if (c->ch_[j] == nullptr) c->ch_[j] = new\
    \ node;\n      c = c->ch_[j];\n    }\n    ++c->cnt_;\n  }\n\n  bool contains(value_type\
    \ a) const {\n    for (int i = BitT - 1; i >= 0; --i)\n      if ((s_[i] = s_[i\
    \ + 1]->ch_[(a >> i) & 1]) == nullptr) return false;\n    return true;\n  }\n\n\
    \  bool erase(value_type a) {\n    if (!contains(a)) return false;\n    --s_.front()->cnt_;\n\
    \    for (int i = 0; i != BitT; ++i) {\n      if (s_[i]->cnt_ || !s_[i]->is_leaf())\
    \ break;\n      auto p                             = s_[i + 1];\n      p->ch_[p->ch_[0]\
    \ == s_[i] ? 0 : 1] = nullptr;\n      delete s_[i];\n    }\n    return true;\n\
    \  }\n\n  value_type xor_max(value_type a) const {\n    assert(!empty());\n  \
    \  value_type r = 0;\n    auto c       = s_.back();\n    for (int i = BitT - 1;\
    \ i >= 0; --i) {\n      auto j = (a >> i) & 1;\n      r <<= 1;\n      if (c->ch_[j\
    \ ^ 1] != nullptr) {\n        c = c->ch_[j ^ 1], r |= 1;\n      } else {\n   \
    \     c = c->ch_[j];\n      }\n    }\n    return r;\n  }\n\n  value_type xor_min(value_type\
    \ a) const {\n    assert(!empty());\n    value_type r = 0;\n    auto c       =\
    \ s_.back();\n    for (int i = BitT - 1; i >= 0; --i) {\n      auto j = (a >>\
    \ i) & 1;\n      r <<= 1;\n      if (c->ch_[j] != nullptr) {\n        c = c->ch_[j];\n\
    \      } else {\n        c = c->ch_[j ^ 1], r |= 1;\n      }\n    }\n    return\
    \ r;\n  }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef BINARY_TRIE_HPP\n#define BINARY_TRIE_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\
    \nLIB_BEGIN\n\ntemplate <int BitT>\nclass binary_trie {\n  class node {\n  public:\n\
    \    node *ch_[2]{};\n    int cnt_{};\n    ~node() {\n      delete ch_[0];\n \
    \     delete ch_[1];\n    }\n    bool is_leaf() const { return ch_[0] == ch_[1];\
    \ }\n  };\n\n  mutable std::array<node *, BitT + 1> s_;\n\npublic:\n  static_assert(BitT\
    \ > 0 && BitT <= 64);\n  using value_type = std::conditional_t<BitT <= 32, std::uint32_t,\
    \ std::uint64_t>;\n\n  binary_trie() { s_.back() = new node; }\n  binary_trie(const\
    \ binary_trie &) = delete;\n  binary_trie(binary_trie &&)      = delete;\n  ~binary_trie()\
    \ { delete s_.back(); }\n  binary_trie &operator=(const binary_trie &) = delete;\n\
    \  binary_trie &operator=(binary_trie &&)      = delete;\n\n  bool empty() const\
    \ { return s_.back()->ch_[0] == s_.back()->ch_[1]; }\n\n  void insert(value_type\
    \ a) {\n    auto c = s_.back();\n    for (int i = BitT - 1; i >= 0; --i) {\n \
    \     auto j = (a >> i) & 1;\n      if (c->ch_[j] == nullptr) c->ch_[j] = new\
    \ node;\n      c = c->ch_[j];\n    }\n    ++c->cnt_;\n  }\n\n  bool contains(value_type\
    \ a) const {\n    for (int i = BitT - 1; i >= 0; --i)\n      if ((s_[i] = s_[i\
    \ + 1]->ch_[(a >> i) & 1]) == nullptr) return false;\n    return true;\n  }\n\n\
    \  bool erase(value_type a) {\n    if (!contains(a)) return false;\n    --s_.front()->cnt_;\n\
    \    for (int i = 0; i != BitT; ++i) {\n      if (s_[i]->cnt_ || !s_[i]->is_leaf())\
    \ break;\n      auto p                             = s_[i + 1];\n      p->ch_[p->ch_[0]\
    \ == s_[i] ? 0 : 1] = nullptr;\n      delete s_[i];\n    }\n    return true;\n\
    \  }\n\n  value_type xor_max(value_type a) const {\n    assert(!empty());\n  \
    \  value_type r = 0;\n    auto c       = s_.back();\n    for (int i = BitT - 1;\
    \ i >= 0; --i) {\n      auto j = (a >> i) & 1;\n      r <<= 1;\n      if (c->ch_[j\
    \ ^ 1] != nullptr) {\n        c = c->ch_[j ^ 1], r |= 1;\n      } else {\n   \
    \     c = c->ch_[j];\n      }\n    }\n    return r;\n  }\n\n  value_type xor_min(value_type\
    \ a) const {\n    assert(!empty());\n    value_type r = 0;\n    auto c       =\
    \ s_.back();\n    for (int i = BitT - 1; i >= 0; --i) {\n      auto j = (a >>\
    \ i) & 1;\n      r <<= 1;\n      if (c->ch_[j] != nullptr) {\n        c = c->ch_[j];\n\
    \      } else {\n        c = c->ch_[j ^ 1], r |= 1;\n      }\n    }\n    return\
    \ r;\n  }\n};\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/binary_trie.hpp
  requiredBy: []
  timestamp: '2023-12-16 22:20:59+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/set_xor_min.0.test.cpp
documentation_of: datastructure/binary_trie.hpp
layout: document
title: Binary Trie
---
