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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: Mo.hpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/Mo.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-04 02:37:44+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cmath>
#include <functional>
#include <vector>
#include <numeric>

class Mo
{
    using updater = std::function<void(size_t)>;
    updater add, rmv;
    std::vector<size_t> lft, rgt, ord;
    bool is_built;
    const size_t width;
    size_t nl, nr;
    std::vector<size_t>::iterator itr;

public:
    Mo(size_t _n, updater _add, updater _rmv)
        : add(_add), rmv(_rmv), is_built(), width(std::sqrt(_n)), nl(0), nr(0)
    {}

    size_t left() const { return nl; }
    size_t right() const { return nr; }

    void insert(size_t l, size_t r)
    {
        lft.emplace_back(l), rgt.emplace_back(r);
        is_built = false;
    }

    void build()
    {
        is_built = true;
        ord.resize(lft.size());
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

    size_t process()
    {
        if(!is_built) build();
        if(itr == ord.end()) return ord.size();
        const size_t now = *itr;
        while(nl > lft[now]) add(--nl);
        while(nr < rgt[now]) add(nr++);
        while(nl < lft[now]) rmv(nl++);
        while(nr > rgt[now]) rmv(--nr);
        return *itr++;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Mo.hpp"
#include <cmath>
#include <functional>
#include <vector>
#include <numeric>

class Mo
{
    using updater = std::function<void(size_t)>;
    updater add, rmv;
    std::vector<size_t> lft, rgt, ord;
    bool is_built;
    const size_t width;
    size_t nl, nr;
    std::vector<size_t>::iterator itr;

public:
    Mo(size_t _n, updater _add, updater _rmv)
        : add(_add), rmv(_rmv), is_built(), width(std::sqrt(_n)), nl(0), nr(0)
    {}

    size_t left() const { return nl; }
    size_t right() const { return nr; }

    void insert(size_t l, size_t r)
    {
        lft.emplace_back(l), rgt.emplace_back(r);
        is_built = false;
    }

    void build()
    {
        is_built = true;
        ord.resize(lft.size());
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

    size_t process()
    {
        if(!is_built) build();
        if(itr == ord.end()) return ord.size();
        const size_t now = *itr;
        while(nl > lft[now]) add(--nl);
        while(nr < rgt[now]) add(nr++);
        while(nl < lft[now]) rmv(nl++);
        while(nr > rgt[now]) rmv(--nr);
        return *itr++;
    }
};

```
{% endraw %}

<a href="../index.html">Back to top page</a>

