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


# :warning: graph/undirected/tree/centroid_decomposition.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#3c61d25aab7013cc226acec7f73e0920">graph/undirected/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/undirected/tree/centroid_decomposition.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-03 02:30:23+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <vector>

class centroid_decomposition
{
    std::vector<std::vector<size_t>> tree, sub;
    std::vector<size_t> siz;
    std::vector<bool> chkd;

    bool dfs(size_t nod, size_t pre, size_t all, size_t rot)
    {
        siz[nod] = 1;
        bool cent = true;
        for(size_t to : tree[nod])
        {
            if(to == pre || chkd[to]) continue;
            if(dfs(to, nod, all, rot)) return true;
            siz[nod] += siz[to];
            if(siz[to] > all / 2) cent = false;
        }
        if(all - siz[nod] > all / 2) cent = false;
        if(!cent) return false;
        chkd[nod] = true;
        if(~rot) sub[rot].emplace_back(nod);
        else root = nod;
        for(size_t to : tree[nod])
        {
            if(chkd[to]) continue;
            if(to == pre) assert(dfs(to, nod, all - siz[nod], nod));
            else assert(dfs(to, nod, siz[to], nod));
        }
        return true;
    }

public:
    size_t root;

    centroid_decomposition(size_t _n = 0) : tree(_n), sub(_n), siz(_n), chkd(_n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    size_t make() { assert(dfs(0, 0, size(), -1)); return root; }

    decltype(sub)::const_reference operator[](size_t nod) const { return sub[nod]; }
}; // class centroid_decomposition

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/undirected/tree/centroid_decomposition.hpp"
#include <cassert>
#include <vector>

class centroid_decomposition
{
    std::vector<std::vector<size_t>> tree, sub;
    std::vector<size_t> siz;
    std::vector<bool> chkd;

    bool dfs(size_t nod, size_t pre, size_t all, size_t rot)
    {
        siz[nod] = 1;
        bool cent = true;
        for(size_t to : tree[nod])
        {
            if(to == pre || chkd[to]) continue;
            if(dfs(to, nod, all, rot)) return true;
            siz[nod] += siz[to];
            if(siz[to] > all / 2) cent = false;
        }
        if(all - siz[nod] > all / 2) cent = false;
        if(!cent) return false;
        chkd[nod] = true;
        if(~rot) sub[rot].emplace_back(nod);
        else root = nod;
        for(size_t to : tree[nod])
        {
            if(chkd[to]) continue;
            if(to == pre) assert(dfs(to, nod, all - siz[nod], nod));
            else assert(dfs(to, nod, siz[to], nod));
        }
        return true;
    }

public:
    size_t root;

    centroid_decomposition(size_t _n = 0) : tree(_n), sub(_n), siz(_n), chkd(_n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    size_t make() { assert(dfs(0, 0, size(), -1)); return root; }

    decltype(sub)::const_reference operator[](size_t nod) const { return sub[nod]; }
}; // class centroid_decomposition

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

