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


# :warning: utils/hash.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/hash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-24 16:14:11+09:00




## Required by

* :warning: <a href="../template.cpp.html">template.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <functional>
namespace workspace {
template <class T> class hash : std::hash<T> { size_t operator()(const T&) const; };
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    std_hash_combine comb;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const { return comb(comb(0, pair.first), pair.second); }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hasher { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(tuple_hasher<Tuple, index - 1>::apply(seed, t, comb), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hasher<Tuple, 0> { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(seed, std::get<0>(t)); } };
    std_hash_combine comb;
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hasher<std::tuple<T...>>::apply(0, t, comb); }
};
} // namespace workspace

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "utils/hash.hpp"
#include <functional>
namespace workspace {
template <class T> class hash : std::hash<T> { size_t operator()(const T&) const; };
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    std_hash_combine comb;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const { return comb(comb(0, pair.first), pair.second); }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hasher { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(tuple_hasher<Tuple, index - 1>::apply(seed, t, comb), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hasher<Tuple, 0> { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(seed, std::get<0>(t)); } };
    std_hash_combine comb;
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hasher<std::tuple<T...>>::apply(0, t, comb); }
};
} // namespace workspace

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
