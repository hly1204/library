---
title: Weighted Disjoint Set
documentation_of: ./weighted_disjoint_set.hpp
---

## 带权并查集

在函数 `relate(u, v, w)` 中表示 `val(v) - val(u)` 的结果为 `w`，我们用一个值将 `u, v` 关联，通过 `diff(u, v)` 来获取 `val(v) - val(u)`，显然只有在 `u, v` 被 `relate()` 之后才能回答。