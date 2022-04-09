#ifndef Z_ALGORITHM_HEADER_HPP
#define Z_ALGORITHM_HEADER_HPP

#include <vector>

namespace lib {

template <typename Container>
std::vector<int> get_z(const Container &s) {
  const int n = static_cast<int>(s.size());
  std::vector<int> z(n, 0);
  if (n == 0) return z;
  if ((z[0] = n) == 1) return z;
  int zi = 0, l = -1, r = -1, i = 2;
  for (auto s0 = s[0]; zi + 1 < n && s[zi + 1] == s0; ++zi) {}
  if ((z[1] = r = zi) > 0)
    for (l = 1; i < n && zi >= 0;) z[i++] = --zi;
  for (; i < n; ++i)
    if (r < i) {
      for (zi = 0; zi + i < n && s[zi] == s[zi + i]; ++zi) {}
      if ((z[i] = zi) > 0) l = i, r = zi + i - 1;
    } else if ((z[i] = z[i - l]) >= r - i + 1) {
      for (zi = r - i + 1; zi + i < n && s[zi] == s[zi + i]; ++zi) {}
      z[i] = zi, l = i, r = zi + i - 1;
    }
  return z;
}

} // namespace lib

#endif