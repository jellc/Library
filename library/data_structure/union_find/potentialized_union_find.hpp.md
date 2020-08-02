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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: data_structure/union_find/potentialized_union_find.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#179a1779a4b5d0e82b6c0fb4370c45e9">data_structure/union_find</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find/potentialized_union_find.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-07 14:11:41+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "potentialized_union_find.hpp"
// verified at https://atcoder.jp/contests/abc087/submissions/9511701
#ifndef Potentialized_union_find_hpp
#define Potentialized_union_find_hpp
#include <cassert>
#include <cstddef>
#include <vector>

template <class Abelian>
class potentialized_union_find
{
    size_t n;
    std::vector<int> link;
    std::vector<Abelian> diff_weight;

public:
    explicit potentialized_union_find(size_t _n) : n(_n), link(n, -1), diff_weight(n) {}

    size_t find(const size_t x)
    {
        assert(x < n);
        if(link[x] < 0) return x;
        const size_t root = find(link[x]);
        diff_weight[x] += diff_weight[link[x]];
        return link[x] = root;
    }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    Abelian weight(size_t x) { return find(x), diff_weight[x]; }

    Abelian diff(size_t x, size_t y) { return weight(y) - weight(x); }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y, Abelian w)
    {
        w += weight(x) - weight(y);
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y), w = -w;
        link[x] += link[y], link[y] = x;
        diff_weight[y] = w;
        return true;
    }
}; // class potentialized_union_find

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/union_find/potentialized_union_find.hpp"
// #line 2 "potentialized_union_find.hpp"
// verified at https://atcoder.jp/contests/abc087/submissions/9511701
#ifndef Potentialized_union_find_hpp
#define Potentialized_union_find_hpp
#include <cassert>
#include <cstddef>
#include <vector>

template <class Abelian>
class potentialized_union_find
{
    size_t n;
    std::vector<int> link;
    std::vector<Abelian> diff_weight;

public:
    explicit potentialized_union_find(size_t _n) : n(_n), link(n, -1), diff_weight(n) {}

    size_t find(const size_t x)
    {
        assert(x < n);
        if(link[x] < 0) return x;
        const size_t root = find(link[x]);
        diff_weight[x] += diff_weight[link[x]];
        return link[x] = root;
    }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    Abelian weight(size_t x) { return find(x), diff_weight[x]; }

    Abelian diff(size_t x, size_t y) { return weight(y) - weight(x); }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y, Abelian w)
    {
        w += weight(x) - weight(y);
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y), w = -w;
        link[x] += link[y], link[y] = x;
        diff_weight[y] = w;
        return true;
    }
}; // class potentialized_union_find

#endif

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

