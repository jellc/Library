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


# :heavy_check_mark: data_structure/union_find/unbalanced.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#179a1779a4b5d0e82b6c0fb4370c45e9">data_structure/union_find</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find/unbalanced.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-30 00:35:46+09:00




## Depends on

* :heavy_check_mark: <a href="basic.hpp.html">data_structure/union_find/basic.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/library-checker/unionfind.test.cpp.html">test/library-checker/unionfind.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "basic.hpp"
struct union_find_unbalanced : union_find
{
    using union_find::union_find;
    
    bool unite(size_t x, size_t y) override
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        link[x] += link[y];
        link[y] = x;
        return true;
    }
}; // class union_find_unbalanced

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/union_find/basic.hpp"
#include <cassert>
#include <vector>
struct union_find
{
    union_find(const size_t &n = 0) : link(n, -1) {}

    size_t find(const size_t &x)
    {
        assert(x < size());
        return link[x] < 0 ? x : (link[x] = find(link[x]));
    }

    size_t size() const { return link.size(); }

    size_t size(const size_t &x)
    {
        assert(x < size());
        return -link[find(x)];
    }

    bool same(const size_t &x, const size_t &y)
    {
        assert(x < size() && y < size());
        return find(x) == find(y);
    }

    virtual bool unite(size_t x, size_t y)
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y];
        link[y] = x;
        return true;
    }

protected:
    std::vector<int> link;
}; // class union_find
#line 3 "data_structure/union_find/unbalanced.hpp"
struct union_find_unbalanced : union_find
{
    using union_find::union_find;
    
    bool unite(size_t x, size_t y) override
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        link[x] += link[y];
        link[y] = x;
        return true;
    }
}; // class union_find_unbalanced

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

