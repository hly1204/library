---
title: Disjoint Set
documentation_of: ./disjoint_set.hpp
---

## 并查集

使用路径对折和按大小合并（ `parent` 和 `size` 数组可以合在一起节省空间），注意 Tarjan 的按秩合并是按大小合并的一种变种，按高度合并是另一种理解方式，但似乎不是原先的定义。

在 C++17 中写出 `a = b = c` 这样的表达式求值顺序是确定的，见 <https://zh.cppreference.com/w/cpp/language/eval_order> 。