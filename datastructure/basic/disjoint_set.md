---
title: Disjoint Set
documentation_of: ./disjoint_set.hpp
---

## 并查集

感觉最近脑子不太清楚，似乎写了一些迷惑内容。。虽然平时也不一定就清楚。

使用路径对折和按大小合并（`parent` 和 `size` 数组可以合在一起节省空间），Tarjan 的按秩合并是按大小合并的一种变种，按高度合并是另一种理解方式，秩为高度的上界。

考虑对每个节点 $x$ 都定义 $\operatorname{rank}(x)$ 映射为一个非负整数，开始时只有一个节点的树其根的秩为 $0$，而直到其 $\operatorname{parent}(x)$ 发生变化后，$\operatorname{rank}(x)$ 就不再发生变化了。根据定义可以发现 $x$ 为根的（子）树有至少 $2^{\operatorname{rank}(x)}$ 个节点，而沿着一个节点一路走到根时，秩是单调不减的，而因为我们对于一个根节点 $r$ 将 $\operatorname{parent}(r)$ 设置为了 $r$，如果不考虑 $r$，那么秩是单调递增的，而这告诉我们沿着当前节点到根路径上每次都至少使得当前节点为根的（子）树的大小为之前的两倍，只应用按秩合并的时间复杂度已经得证，这与轻重路径分解（heavy path decomposition）的证明似乎很相似。

根据 Tarjan 在论文中所说，可以发现对于整数 $k\geq 0$，秩为 $k$ 的节点最多有 $n/2^k$ 个。

在 C++17 中写出 `a = b = c` 这样的表达式求值顺序是确定的，见 <https://zh.cppreference.com/w/cpp/language/eval_order>。