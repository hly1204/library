---
title: Discrete Logarithm (Shanks' Baby Step-Giant Step algorithm)
documentation_of: ./discrete_log_BSGS.hpp
---

## 离散对数

离散对数一般指求解关于 $x$ 的同余式

$$
a^x\equiv b\pmod{m}
$$

的最小可行解，但解未必存在。这里认为 $0^0=1$。

## Baby-Step Giant-Step 算法

令 $x=np-q$ 的形式，其中 $n$ 为固定值，其中 $x\in \lbrace 0,1,2,\dots ,m-1\rbrace$，我们通过枚举 $n$ 来测试是否满足等式，所以 $p\in \lbrace 1,2,\dots ,\left\lceil \frac{m}{n}\right\rceil \rbrace$ 且 $q\in \lbrace 0,1,\dots ,n\rbrace$

此时同余式变为

$$
a^{np-q}\equiv b\pmod{m}
$$

有

$$
a^{np}\equiv ba^q\pmod{m}
$$

我们提前计算所有 $a^{np}$ 并存储在类似于 `std::map<int, int>` 的容器中，以 $a^{np}$ 为关键字，值为 $np$ 后枚举 $ba^q$ 计算即可，但因我们希望找到 **最小** 的 $x$ 满足 $a^x\equiv b\pmod{m}$，所以提前计算所有的 $ba^q$ 后枚举 $a^{np}$，可以通过 `std::unordered_map<int, int>` 来避免平衡树/二分查找所需的额外时间。我们希望让 $p$ 和 $q$ 的枚举都尽可能小，所以选择 $n=\left\lceil \sqrt{m}\right\rceil$。其中枚举 $q$ 的过程称为 Baby-Step 而枚举 $p$ 的过程称为 Giant-Step。

考虑 $a\equiv b\equiv 1\pmod{m}$ 的情况，此时 `std::unordered_map<int, int>` 中其实只有一个值为 $n$，然后在枚举 $p$ 时返回为零，也就是说如果对于所有 $ba^q$ 有相同值时在哈希表中会保留 $q$ 较大的值，因为我们是减去 $q$ 所以这样是正确的，当然，这也提示我们可以用 `std::unordered_map<int, std::vector<int>>` 来保留所有可能的结果。

## $\gcd(a,m)\neq 1$ 时

令 $g=\gcd(a,m)$，若 $g\nmid b$ 则无解，因为 $(a\bmod m)\bmod g=a\bmod g$ 所以右边 $b\bmod g$ 如果不等于零那么必然无解。在有解时我们记 $a=g\alpha$ 和 $b=g\beta$ 那么

$$
a^x\equiv b\pmod{m}\implies g^{x-1}\alpha^x\equiv \beta \pmod{(m/g)}
$$

若 $\gcd(\alpha ,m/g)=1$ 则求解 $(g\alpha )^{x-1}\equiv \beta \alpha^{-1}\pmod{(m/g)}$ 即可，否则重复上述步骤。

实际上不用求出 $\alpha ^{-1}\bmod{(m/g)}$，只需考虑求解问题 $k\cdot a^x\equiv b\pmod{m}$。

## 参考文献

- [cp-algorithms](https://cp-algorithms.com/algebra/discrete-log.html)