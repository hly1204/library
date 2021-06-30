---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/basic/sparse_table.hpp
    title: "sparse table / \u7A00\u758F\u8868"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"remote_test/yosupo/datastructure/staticrmq.0.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include <iostream>\n\
    #include <vector>\n\n#line 1 \"datastructure/basic/sparse_table.hpp\"\n\n\n\n\
    /**\n * @brief sparse table / \u7A00\u758F\u8868\n *\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <functional>\n#line 14 \"datastructure/basic/sparse_table.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename Type, typename FoldFunc> class SparseTable\
    \ {\npublic:\n  static std::uint32_t log2_floor(std::uint32_t n) {\n    n >>=\
    \ 1, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, ++n;\n\
    \    static constexpr std::uint32_t deBruijn = 0x4653adf;\n    static constexpr\
    \ std::uint32_t convert[32] = {0,  1,  2,  6,  3,  11, 7,  16, 4,  14, 12,\n \
    \                                                 21, 8,  23, 17, 26, 31, 5, \
    \ 10, 15, 13, 20,\n                                                  22, 25, 30,\
    \ 9,  19, 24, 29, 18, 28, 27};\n    return convert[n * deBruijn >> 27];\n  }\n\
    \  template <typename Container>\n  SparseTable(const Container &init_v, const\
    \ FoldFunc &f = FoldFunc()) : N_(init_v.size()), f_(f) {\n    int level = log2_floor(N_);\n\
    \    table_.resize(level + 1);\n    table_[0].resize(N_);\n    std::copy_n(init_v.begin(),\
    \ N_, table_[0].begin());\n    for (int i = 0; i < level; ++i) {\n      int s\
    \ = N_ + 1 - (1 << (i + 1));\n      const std::vector<Type> &ti = table_[i];\n\
    \      std::vector<Type> &ti1 = table_[i + 1];\n      ti1.resize(s);\n      for\
    \ (int j = 0, offset = 1 << i; j < s; ++j) ti1[j] = f_(ti[j], ti[j + offset]);\n\
    \    }\n  }\n  ~SparseTable() = default;\n\n  Type fold(int l, int r) const {\
    \ // [l,r]\n    assert(l <= r);\n    int level = log2_floor(r + 1 - l);\n    return\
    \ f_(table_[level][l], table_[level][r + 1 - (1 << level)]);\n  }\n\nprivate:\n\
    \  const int N_;\n  FoldFunc f_;\n  std::vector<std::vector<Type>> table_;\n};\n\
    \ntemplate <typename Type, typename Comp = std::less<>>\nSparseTable<Type, std::function<Type(const\
    \ Type &, const Type &)>>\nmake_rmq_sparse_table(const std::vector<Type> &init_v,\
    \ Comp cmp = Comp()) {\n  return SparseTable<Type, std::function<Type(const Type\
    \ &, const Type &)>>(\n      init_v, [&cmp](const Type &x, const Type &y) { return\
    \ cmp(x, y) ? x : y; });\n}\n\n} // namespace lib\n\n\n#line 7 \"remote_test/yosupo/datastructure/staticrmq.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  std::vector<int> A(n);\n  for (auto &i\
    \ : A) std::cin >> i;\n  auto st = lib::make_rmq_sparse_table(A);\n  while (q--)\
    \ {\n    int l, r;\n    std::cin >> l >> r;\n    std::cout << st.fold(l, r - 1)\
    \ << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#include \"datastructure/basic/sparse_table.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  std::vector<int> A(n);\n  for (auto &i\
    \ : A) std::cin >> i;\n  auto st = lib::make_rmq_sparse_table(A);\n  while (q--)\
    \ {\n    int l, r;\n    std::cin >> l >> r;\n    std::cout << st.fold(l, r - 1)\
    \ << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - datastructure/basic/sparse_table.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/staticrmq.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-01 00:45:41+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/staticrmq.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/staticrmq.0.test.cpp
- /verify/remote_test/yosupo/datastructure/staticrmq.0.test.cpp.html
title: remote_test/yosupo/datastructure/staticrmq.0.test.cpp
---
