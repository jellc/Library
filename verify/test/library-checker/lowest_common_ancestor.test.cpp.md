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


# :heavy_check_mark: test/library-checker/lowest_common_ancestor.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/lowest_common_ancestor.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-04 20:59:06+09:00


* see: <a href="https://judge.yosupo.jp/problem/lca">https://judge.yosupo.jp/problem/lca</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/undirected/tree/lowest_common_ancestor.hpp.html">graph/undirected/tree/lowest_common_ancestor.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <cstdio>
#include <ext/rope>

#include "graph/undirected/tree/lowest_common_ancestor.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  lowest_common_ancestor lca(n);
  for (int i = 1, p; i < n; i++) {
    scanf("%d", &p);
    lca.add_edge(i, p);
  }
  lca.make(0);
  for (int u, v; q--;) {
    scanf("%d%d", &u, &v);
    printf("%d\n", (int)lca.query(u, v));
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/lowest_common_ancestor.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <cstdio>
#include <ext/rope>

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
#line 6 "test/library-checker/lowest_common_ancestor.test.cpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  lowest_common_ancestor lca(n);
  for (int i = 1, p; i < n; i++) {
    scanf("%d", &p);
    lca.add_edge(i, p);
  }
  lca.make(0);
  for (int u, v; q--;) {
    scanf("%d%d", &u, &v);
    printf("%d\n", (int)lca.query(u, v));
  }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

