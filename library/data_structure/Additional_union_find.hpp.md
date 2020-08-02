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


# :warning: data_structure/Additional_union_find.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/Additional_union_find.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 19:06:22+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "Additional_union_find.hpp"
#ifndef Additional_union_find_hpp
#define Additional_union_find_hpp
#include <cassert>
#include <functional>
#include <vector>

template <class T>
class additional_union_find
{
    size_t n;
    std::vector<int> link;
    T *const dat;
    const std::function<void(T&, T&)> merge;

public:
    additional_union_find(const size_t _n, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n]()), merge(f) {}
    additional_union_find(const size_t _n, const T &x, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n](x)), merge(f) {}
    ~additional_union_find() { delete[] dat; }

    size_t find(const size_t x) { assert(x < n); return link[x] < 0 ? x : (link[x] = find(link[x])); }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y)
    {
        if((x = find(x)) == (y = find(y))) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y], link[y] = x;
        merge(dat[x], dat[y]);
        return true;
    }

    T &operator[](const size_t x) { return dat[find(x)]; }
}; // class additional_union_find

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/Additional_union_find.hpp"
// #line 2 "Additional_union_find.hpp"
#ifndef Additional_union_find_hpp
#define Additional_union_find_hpp
#include <cassert>
#include <functional>
#include <vector>

template <class T>
class additional_union_find
{
    size_t n;
    std::vector<int> link;
    T *const dat;
    const std::function<void(T&, T&)> merge;

public:
    additional_union_find(const size_t _n, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n]()), merge(f) {}
    additional_union_find(const size_t _n, const T &x, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n](x)), merge(f) {}
    ~additional_union_find() { delete[] dat; }

    size_t find(const size_t x) { assert(x < n); return link[x] < 0 ? x : (link[x] = find(link[x])); }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y)
    {
        if((x = find(x)) == (y = find(y))) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y], link[y] = x;
        merge(dat[x], dat[y]);
        return true;
    }

    T &operator[](const size_t x) { return dat[find(x)]; }
}; // class additional_union_find

#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

