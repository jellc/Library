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
<script type="text/javascript" src="../../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../../assets/css/copy-button.css" />


# :heavy_check_mark: graph/undirected/tree/lowest_common_ancestor.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#3c61d25aab7013cc226acec7f73e0920">graph/undirected/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/undirected/tree/lowest_common_ancestor.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-02 22:26:27+09:00




## Verified with

* :heavy_check_mark: <a href="../../../../verify/test/library-checker/lowest_common_ancestor.test.cpp.html">test/library-checker/lowest_common_ancestor.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <vector>

// query: O(1)
// build: O(nlog(n))
class lowest_common_ancestor
{
    std::vector<std::vector<size_t>> tree, tab;
    std::vector<size_t> idx;

    void tour(size_t node, size_t pre)
    {
        idx[node] = tab[0].size();
        tab[0].emplace_back(node);
        for(size_t to : tree[node])
        {
            if(to != pre)
            {
                tour(to, node);
                tab[0].emplace_back(node);
            }
        }
    }

    void make_table()
    {
        const size_t len = tab[0].size();
        for(size_t w = 2; w < len; w <<= 1)
        {
            std::vector<size_t> &crt(tab.back()), nxt(crt);
            for(size_t i = 0, j = w >> 1; j != len; ++i, ++j) if(idx[crt[i]] > idx[crt[j]]) nxt[i] = crt[j];
            tab.emplace_back(nxt);
        }
    }

public:
    lowest_common_ancestor(size_t n) : tree(n), tab(1), idx(n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    void make(size_t root)
    {
        assert(root < size());
        tour(root, root);
        make_table();
    }

    size_t query(size_t u, size_t v) const
    {
        assert(u < size()); assert(v < size());
        if(u == v) return u;
        if(idx[u] > idx[v]) std::swap(u, v);
        u = idx[u], v = idx[v];
        size_t h = std::__lg(v - u);
        return std::min(tab[h][u], tab[h][v - (1 << h)]);
    }
}; // class lowest_common_ancestor
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/undirected/tree/lowest_common_ancestor.hpp"
#include <cassert>
#include <vector>

// query: O(1)
// build: O(nlog(n))
class lowest_common_ancestor
{
    std::vector<std::vector<size_t>> tree, tab;
    std::vector<size_t> idx;

    void tour(size_t node, size_t pre)
    {
        idx[node] = tab[0].size();
        tab[0].emplace_back(node);
        for(size_t to : tree[node])
        {
            if(to != pre)
            {
                tour(to, node);
                tab[0].emplace_back(node);
            }
        }
    }

    void make_table()
    {
        const size_t len = tab[0].size();
        for(size_t w = 2; w < len; w <<= 1)
        {
            std::vector<size_t> &crt(tab.back()), nxt(crt);
            for(size_t i = 0, j = w >> 1; j != len; ++i, ++j) if(idx[crt[i]] > idx[crt[j]]) nxt[i] = crt[j];
            tab.emplace_back(nxt);
        }
    }

public:
    lowest_common_ancestor(size_t n) : tree(n), tab(1), idx(n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    void make(size_t root)
    {
        assert(root < size());
        tour(root, root);
        make_table();
    }

    size_t query(size_t u, size_t v) const
    {
        assert(u < size()); assert(v < size());
        if(u == v) return u;
        if(idx[u] > idx[v]) std::swap(u, v);
        u = idx[u], v = idx[v];
        size_t h = std::__lg(v - u);
        return std::min(tab[h][u], tab[h][v - (1 << h)]);
    }
}; // class lowest_common_ancestor

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

