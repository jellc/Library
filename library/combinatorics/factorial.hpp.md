---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :x: combinatorics/factorial.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ac1ed416572b96a9f5d69740d174ef3d">combinatorics</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/factorial.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-16 13:02:00+09:00




## Required by

* :x: <a href="binomial.hpp.html">combinatorics/binomial.hpp</a>


## Verified with

* :x: <a href="../../verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp.html">test/aizu-online-judge/balls_and_boxes_4.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <functional>
#include <vector>
template <class T, class Op = std::multiplies<T>>
class factorial
{
    std::vector<T> fact;
    Op op;
public:
    factorial(T init = 1, Op op = Op()) : fact{init}, op{op} {}
    T operator()(const int &n)
    {
        if(n < 0) return 0;
        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(), m));
        return fact[n];
    }
}; // class factorial

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "combinatorics/factorial.hpp"
#include <functional>
#include <vector>
template <class T, class Op = std::multiplies<T>>
class factorial
{
    std::vector<T> fact;
    Op op;
public:
    factorial(T init = 1, Op op = Op()) : fact{init}, op{op} {}
    T operator()(const int &n)
    {
        if(n < 0) return 0;
        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(), m));
        return fact[n];
    }
}; // class factorial

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

