---
title: Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$ for FFT prime $p$)
documentation_of: ./formal_power_series.hpp
---

I got wrong answer when I was testing my library locally. Check [Wandbox](https://wandbox.org/permlink/smgnVZ0lcZvk6ZYJ). It seems okay when compiling with Clang.

The reason I found was the lambda expression in `main` function, but I don't know why.