#ifndef SUFFIX_ARRAY_SAIS_HEADER_HPP
#define SUFFIX_ARRAY_SAIS_HEADER_HPP

/**
 * @brief suffix array SA-IS
 * @docs docs/string/suffix_array_sais.md
 */

#include <algorithm>
#include <string>
#include <vector>

namespace lib::internal {

/**
 * @brief 诱导排序
 * @ref Ge Nong, Sen Zhang and Wai Hong Chan.
 *      Linear Suffix Array Construction by Almost Pure Induced-Sorting.
 *
 * @param s 字符串数组，必须保证末尾为 0 且 0 是整个字符串数组中只出现在末尾的最小字符！
 * @param K 字符串数组的值域，由 [0, K)
 * @return std::vector<int>
 */
std::vector<int> SA_IS(const std::vector<int> &s, int K) {
  const int n = s.size();
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
  const int n1 = p1.size();
  for (int i = 0; i != n; ++i) ++bkt[s[i]];
  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];
  std::vector<int> s1(n1), SA1(n1);
  std::fill_n(SA.begin(), n, -1);
  std::copy_n(bkt_r.begin(), K, bkt.begin());
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];
  std::copy_n(bkt_l.begin(), K, bkt.begin());
  for (int i = 0, j; i != n; ++i)
    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++] = j;
  std::copy_n(bkt_r.begin(), K, bkt.begin());
  for (int i = n - 1, j; i >= 0; --i)
    if ((j = SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]] = j;
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
  for (int i = 0, j; i != n; ++i)
    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j)) SA[bkt_l[s[j]]++] = j;
  for (int i = n - 1, j; i >= 0; --i)
    if ((j = SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;
#undef IS_S_TYPE
#undef IS_L_TYPE
#undef IS_LMS_TYPE
  return SA;
}

} // namespace lib::internal

namespace lib {

/**
 * @brief 获取后缀数组（ 0-indexed ）
 * @param s 字符串，一般为 string 或 std::vector<int>
 * @return std::vector<int> 后缀数组
 */
template <typename Container>
std::vector<int> get_sa(const Container &s) {
  std::vector<int> s_cpy(s.size() + 1);
  std::copy(s.begin(), s.end(), s_cpy.begin());
  s_cpy.back() = 0;
  std::vector<int> SA(internal::SA_IS(s_cpy, *std::max_element(s.begin(), s.end()) + 1));
  SA.erase(SA.begin());
  return SA;
}

/**
 * @brief 获取后缀数组（ 0-indexed ）的特化
 * @note 容器为 std::string 时特化！
 * @param s 字符串
 * @return std::vector<int>
 */
template <>
std::vector<int> get_sa<std::string>(const std::string &s) {
  std::vector<int> s_cpy(s.size() + 1);
  std::copy(s.begin(), s.end(), s_cpy.begin());
  s_cpy.back() = 0;
  std::vector<int> SA(internal::SA_IS(s_cpy, 128));
  SA.erase(SA.begin());
  return SA;
}

/**
 * @brief 获取 LCP 数组
 * @see https://cp-algorithms.com/string/suffix-array.html
 * @param s 字符串
 * @param SA 计算完毕的 s 的后缀数组（ 0-indexed ）
 * @return std::vector<int> LCP 数组
 */
template <typename Container>
std::vector<int> get_lcp(const Container &s, const std::vector<int> &SA) {
  int n = s.size();
  std::vector<int> rk(n), height(n - 1, 0);
  // height[i] = s[SA[i]..n-1] 与 s[SA[i+1]..n-1] 的最长公共前缀（ longest common prefix ）
  // Kasai 的论文中称其为 lcp 数组或 height 数组
  for (int i = 0; i != n; ++i) rk[SA[i]] = i;
  for (int i = 0, h = 0; i != n; ++i) {
    if (rk[i] == n - 1) {
      h = 0;
      continue;
    }
    int j = SA[rk[i] + 1];
    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
    height[rk[i]] = h;
    if (h != 0) --h;
  }
  return height;
}

} // namespace lib

#endif