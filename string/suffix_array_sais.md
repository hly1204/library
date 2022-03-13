---
title: Suffix Array (SA-IS)
documentation_of: ./suffix_array_sais.hpp
---

## 后缀数组

后缀数组即对于串 $S$ 每个字符开头的后缀都进行排序后按顺序在数组中存储后缀开始的索引。

## 诱导排序

在 SA-IS 即诱导排序中我们假设 $S$ 末尾有一个为零的最小字典序的字符。

诱导排序的主旨为我们只需要选择 $S$ 所有后缀这个集合中的一组“恰当”的子集（这个子集为所有 LMS-型后缀），只要子集已经有序，那么就可以在线性时间内“诱导”出所有后缀的相对顺序。

- L-型后缀意为 larger 即其字典序比它右边一个字符开头的后缀大；
- S-型后缀意为 smaller 即其字典序比它右边一个字符开头的后缀小；
- LMS-型后缀本身是 S-型后缀但该后缀的左侧为 L-型后缀，所以 LMS 为 left most S-type 的缩写。

我们注意 LMS-型后缀的定义，其左侧必须为 L-型后缀，这也意味着字符串本身这个后缀如果为 S-型后缀那么其也不属于 LMS-型后缀。

我们将整个后缀数组按照每个后缀的首字母划分为多个“桶”，每个桶中首字母必定相同，更进一步的，在每个桶中 L-型后缀必然排名在 S-型后缀前。

在代码中我们计算每个桶的开头和结尾，放入有序的 LMS-型后缀，从桶的末尾依次放入。后对 L-型后缀进行诱导，从桶的开头依次放入，注意此时 LMS-型后缀也未必在其恰当的位置，我们需要利用 L-型后缀之间的相对顺序对 S-型后缀进行诱导。

证明略。注意我们对 LMS-子串也使用该方法进行排序后重新命名，那么 LMS-后缀间的相对顺序只需要求解这个新的字符串的后缀数组即可，此时问题至少被减少为原先的一半，那么 $T(n)=T(n/2)+O(n)$ 有 $T(n)=O(n)$ 。

诱导排序的思想由 P. Ko 和 S. Aluru 提出，但是他们对于 LMS-子串的排序使用了更为复杂的另一种方法且需要使用到他们定义的数据结构，而 G. Nong 、 S. Zhang 和 W. H. Chan 则是提出 LMS-子串也可以使用诱导排序。

## 部分注释的代码

```cpp
void SA_IS(const int *s, int *SA, int n, int K) {
  // s 为字符串数组[0..n-1] 必须保证 s[n-1]=0 且为最小值
  // SA 为存储后缀数组[0..n-1]
  // n 为字符串长度
  // K 为值域

  bool *t = new bool[n]; // 类型数组
  int *bkt = new int[K]; // 桶
  int *bkt_l = new int[K];
  int *bkt_r = new int[K];
  int n1 = 0; // LMS-后缀的数量
  int *p1;    //按出现顺序存储所有 LMS-后缀的索引

#define is_S_type(x) (t[x])
#define is_L_type(x) (!t[x])
#define is_LMS_type(x) (is_S_type(x) && x != 0 && is_L_type(x - 1))

  // 预处理每一个后缀的类型
  t[n - 1] = true; // 0 为 S-型后缀且为 LMS-型后缀
  for (int i = n - 2; i >= 0; --i) {
    t[i] = (s[i] < s[i + 1] || (is_S_type(i + 1) && s[i] == s[i + 1]));
    n1 += is_LMS_type(i + 1); // s[0] 必然不是 LMS-型后缀，不会影响
  }

  // 预处理桶的边界
  for (int i = 0; i != K; ++i) bkt[i] = 0;
  for (int i = 0; i != n; ++i) ++bkt[s[i]];
  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];

#define induced_sort()                                                                             \
  do {                                                                                             \
    for (int i = 0; i != K; ++i) bkt[i] = bkt_l[i];                                                \
    for (int i = 0, j; i != n; ++i)                                                                \
      if ((j = SA[i] - 1) >= 0 && is_L_type(j)) SA[bkt[s[j]]++] = j;                               \
    for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];                                                \
    for (int i = n - 1, j; i >= 0; --i)                                                            \
      if ((j = SA[i] - 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j;                               \
  } while (0)

  // 将所有 LMS-后缀放入 SA 对应桶的末尾并诱导排序
  p1 = new int[n1];
  for (int i = 0, j = 0; i != n; ++i) {
    SA[i] = -1;
    if (is_LMS_type(i)) p1[j++] = i;
  }
  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];
  induced_sort();

  int *s1 = new int[n1];  // 新的字符串
  int *SA1 = new int[n1]; // 存储新的字符串排的后缀数组
  for (int i = 0, j = 0; i != n; ++i)
    if (is_LMS_type(SA[i])) SA1[j++] = SA[i]; // 存储 LMS-子串的相对顺序
  int name = 0;
  // 对所有 LMS-子串命名
  for (int i = 0, prev = -1; i != n1; ++i) {
    int pos = SA1[i];
    for (int j = 0;; ++j) // 无需设置范围，因为 s[n-1]=0 为最小值且不会出现在其余位置
      if (prev == -1 || s[pos + j] != s[prev + j] || is_S_type(pos + j) != is_S_type(prev + j)) {
        prev = pos, ++name;
        break;
      } else if (j != 0 && (is_LMS_type(pos + j) || is_LMS_type(prev + j))) // 到末尾了停止比较
        break;
    SA[pos] = name - 1; // 利用 SA 暂时存储新字符串的 name
  }
  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];

  if (name != n1)
    SA_IS(s1, SA1, n1, name);
  else
    for (int i = 0; i != n1; ++i) SA1[s1[i]] = i;

  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];
  for (int i = 0; i != n; ++i) SA[i] = -1;
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];
  induced_sort();

  delete[] SA1;
  delete[] s1;
  delete[] p1;
  delete[] bkt_r;
  delete[] bkt_l;
  delete[] bkt;
  delete[] t;

#undef is_S_type
#undef is_L_type
#undef is_LMS_type
#undef induced_sort
}
```

## 参考文献

- G. Nong, S. Zhang, and W. H. Chan, “Linear suffix array construction by almost pure induced-sorting,” in Proceedings of DCC, U.S.A., Mar. 2009.