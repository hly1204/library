#ifndef SUFFIX_ARRAY_HPP
#define SUFFIX_ARRAY_HPP

#include "../common.hpp"

#include <algorithm>
#include <vector>

LIB_BEGIN

namespace detail {

// Input:  String `s` and integer `K`, where `s[i]` ∈ [0, `K`).
//         `s` must ends with '\0' and `s[i]` > 0 for all rest `i`.
// Output: Suffix array of `s`.
std::vector<int> SA_IS(const std::vector<int> &s, int K) {
  const int n = static_cast<int>(s.size());
  std::vector<bool> t(n);
  std::vector<int> bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;
#define IS_S_TYPE(x) (t[x])
#define IS_L_TYPE(x) (!t[x])
#define IS_LMS_TYPE(x) (IS_S_TYPE(x) && x != 0 && IS_L_TYPE(x - 1))
  t.back() = true;
  for (int i = n - 2; i >= 0; --i) {
    t[i] = (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i + 1]));
    if (IS_LMS_TYPE(i + 1)) p1.push_back(i + 1);
  }
  std::reverse(p1.begin(), p1.end());
  const int n1 = static_cast<int>(p1.size());
  for (int i = 0; i != n; ++i) ++bkt[s[i]];
  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];
  std::vector<int> s1(n1), SA1(n1);
  std::fill_n(SA.begin(), n, -1);
  std::copy_n(bkt_r.begin(), K, bkt.begin());
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];
  std::copy_n(bkt_l.begin(), K, bkt.begin());
  for (int i = 0; i != n; ++i)
    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++] = j;
  std::copy_n(bkt_r.begin(), K, bkt.begin());
  for (int i = n - 1; i >= 0; --i)
    if (int j = SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]] = j;
  for (int i = 0, j = 0; i != n; ++i)
    if (IS_LMS_TYPE(SA[i])) SA1[j++] = SA[i];
  int name = 0;
  for (int i = 0, prev = -1; i != n1; ++i) {
    int pos = SA1[i];
    for (int j = 0;; ++j)
      if (prev == -1 || s[pos + j] != s[prev + j] || IS_S_TYPE(pos + j) != IS_S_TYPE(prev + j)) {
        prev = pos, ++name;
        break;
      } else if (j != 0 && (IS_LMS_TYPE(pos + j) || IS_LMS_TYPE(prev + j)))
        break;
    SA[pos] = name - 1;
  }
  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];
  if (name != n1) {
    SA1 = SA_IS(s1, name);
  } else {
    for (int i = 0; i != n1; ++i) SA1[s1[i]] = i;
  }
  std::copy_n(bkt_r.begin(), K, bkt.begin());
  std::fill_n(SA.begin(), n, -1);
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];
  for (int i = 0; i != n; ++i)
    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j)) SA[bkt_l[s[j]]++] = j;
  for (int i = n - 1; i >= 0; --i)
    if (int j = SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;
#undef IS_S_TYPE
#undef IS_L_TYPE
#undef IS_LMS_TYPE
  return SA;
}

} // namespace detail

template <typename ContainerT>
std::vector<int> suffix_array(ContainerT &&s) {
  std::vector<int> s_cpy(s.size() + 1);
  std::copy(s.cbegin(), s.cend(), s_cpy.begin());
  s_cpy.back() = 0;
  auto SA      = detail::SA_IS(s_cpy, *std::max_element(s_cpy.cbegin(), s_cpy.cend()) + 1);
  SA.erase(SA.begin());
  return SA;
}

LIB_END

#endif