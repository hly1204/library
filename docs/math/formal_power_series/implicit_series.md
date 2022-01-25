## 隐式级数

在 [Philippe Flajolet](http://algo.inria.fr/flajolet/) 和 Robert Sedgewick 的 Analytic Combinatorics 一书中提到生成函数的隐式形式，我参考 Hoeven 的论文中的描述使用 C++ 中的 lambda 和在线卷积实现了部分相当简单的功能。

例如 Catalan 数的 OGF （ Analytic Combinatorics 第 36 页）为

$$
T(z)=1+zT^2(z)\implies T(z)=\frac{1-\sqrt{1-4z}}{2z}
$$

右侧是闭形式可以使用形式幂级数简单的计算，左侧就是隐式的形式了。隐式级数一般容易找到，而找到闭形式有可能比较困难（或者不一定存在？）。

```cpp
#include <functional>
#include <iostream>

#include "math/formal_power_series/implicit_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  using mint = lib::MontModInt<998244353>;
  std::function<mint(int)> f;
  lib::ImplicitSeries<mint> T([&f](int i) { return i == 0 ? 1 : f(i); });
  f = [TT = T * T](int i) { return TT[i - 1]; };
  for (int i = 0; i < 10; ++i) std::cout << T[i] << ' ';
  return 0;
}
```

隐式级数的快速计算可以直接解决 [LOJ 6538. 烷基计数 加强版 加强版](https://loj.ac/p/6538) 等问题，尽管在时间复杂度上并无优势。

另外 Elegia 指出在线卷积也可以扩展到任意模数的二项卷积上，那么隐式级数的计算可能也可以扩展，但由于过于复杂我也不会！

## 参考文献

- Elegia. [《生成函数的一点进展》重置版](https://www.bilibili.com/video/BV1U5411N7Uc).
- 同 [在线卷积](https://hly1204.github.io/library/math/formal_power_series/relaxed_convolution.hpp) 的参考文献.