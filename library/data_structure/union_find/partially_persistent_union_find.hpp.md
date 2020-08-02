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


# :warning: data_structure/union_find/partially_persistent_union_find.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#179a1779a4b5d0e82b6c0fb4370c45e9">data_structure/union_find</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find/partially_persistent_union_find.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-07 14:10:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "Partially_persistent_union_find.hpp"
// veryfied at https://atcoder.jp/contests/agc002/submissions/9514048
#ifndef Partially_persistent_union_find_hpp
#define Partially_persistent_union_find_hpp
#include <cstdint>
#include <cstddef>
#include <numeric>
#include <vector>

class partially_persistent_union_find
{
    using time_type = uint32_t;
    struct log_type { time_type time; size_t size; };
    const size_t n;
    std::vector<size_t> parent;
    std::vector<time_type> last;
    std::vector<std::vector<log_type>> size_log;
    time_type clock;

public:
    explicit partially_persistent_union_find(size_t _n) : n(_n), parent(n), last(n, UINT32_MAX), size_log(n, std::vector<log_type>(1, {0, 1})), clock()
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    size_t size(size_t x, time_type t = UINT32_MAX)
    {
        size_t root = find(x, t);
        auto __ok{size_log[root].begin()}, __ng{size_log[root].end()};
        auto dist = __ng - __ok;
        while(dist > 1)
        {
            auto mid{__ok + (dist >> 1)};
            if(mid->time > t) __ng = mid, dist >>= 1;
            else __ok = mid, ++dist >>= 1;
        }
        return __ok->size;
    }

    size_t find(size_t x, size_t t = UINT32_MAX) { return last[x] >= t ? x : find(parent[x], t); }

    bool same(size_t x, size_t y, time_type t = UINT32_MAX) { return find(x, t) == find(y, t); }

    time_type unite(size_t x, size_t y)
    {
        if((x = find(x)) != (y = find(y)))
        {
            size_t size_x = size_log[x].back().size;
            size_t size_y = size_log[y].back().size;
            if(size_x < size_y) std::swap(x, y), std::swap(size_x, size_y);
            size_log[x].push_back({clock + 1, size_x + size_y});
            parent[y] = x;
            last[y] = clock;
        }
        return ++clock;
    }
}; // class partially_persistent_union_find

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/union_find/partially_persistent_union_find.hpp"
// #line 2 "Partially_persistent_union_find.hpp"
// veryfied at https://atcoder.jp/contests/agc002/submissions/9514048
#ifndef Partially_persistent_union_find_hpp
#define Partially_persistent_union_find_hpp
#include <cstdint>
#include <cstddef>
#include <numeric>
#include <vector>

class partially_persistent_union_find
{
    using time_type = uint32_t;
    struct log_type { time_type time; size_t size; };
    const size_t n;
    std::vector<size_t> parent;
    std::vector<time_type> last;
    std::vector<std::vector<log_type>> size_log;
    time_type clock;

public:
    explicit partially_persistent_union_find(size_t _n) : n(_n), parent(n), last(n, UINT32_MAX), size_log(n, std::vector<log_type>(1, {0, 1})), clock()
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    size_t size(size_t x, time_type t = UINT32_MAX)
    {
        size_t root = find(x, t);
        auto __ok{size_log[root].begin()}, __ng{size_log[root].end()};
        auto dist = __ng - __ok;
        while(dist > 1)
        {
            auto mid{__ok + (dist >> 1)};
            if(mid->time > t) __ng = mid, dist >>= 1;
            else __ok = mid, ++dist >>= 1;
        }
        return __ok->size;
    }

    size_t find(size_t x, size_t t = UINT32_MAX) { return last[x] >= t ? x : find(parent[x], t); }

    bool same(size_t x, size_t y, time_type t = UINT32_MAX) { return find(x, t) == find(y, t); }

    time_type unite(size_t x, size_t y)
    {
        if((x = find(x)) != (y = find(y)))
        {
            size_t size_x = size_log[x].back().size;
            size_t size_y = size_log[y].back().size;
            if(size_x < size_y) std::swap(x, y), std::swap(size_x, size_y);
            size_log[x].push_back({clock + 1, size_x + size_y});
            parent[y] = x;
            last[y] = clock;
        }
        return ++clock;
    }
}; // class partially_persistent_union_find

#endif

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

