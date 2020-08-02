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


# :warning: graph/directed/flow/base.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#13554c95f4603c3979d32881e43d19e6">graph/directed/flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow/base.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 15:58:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost;
        size_t rev;
        edge_t(size_t _src, size_t _dst, cap_t _cap, cost_t _cost, size_t _rev)
            : src(_src), dst(_dst), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

protected:
    using adj_type = std::vector<std::vector<edge_t>>;
    adj_type adj;

public:
    flow_base(size_t _n = 0) : adj(_n) {}

    size_t size() const { return adj.size(); }
    typename decltype(adj)::reference operator[](size_t node) { assert(node < size()); return adj[node]; }
    typename decltype(adj)::const_reference operator[](size_t node) const { assert(node < size()); return adj[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(cap <= 0) return;
        adj[src].emplace_back(src, dst, cap, cost, adj[dst].size());
        adj[dst].emplace_back(dst, src, 0, -cost, adj[src].size() - 1);
    }
}; // struct flow_base

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/directed/flow/base.hpp"
#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost;
        size_t rev;
        edge_t(size_t _src, size_t _dst, cap_t _cap, cost_t _cost, size_t _rev)
            : src(_src), dst(_dst), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

protected:
    using adj_type = std::vector<std::vector<edge_t>>;
    adj_type adj;

public:
    flow_base(size_t _n = 0) : adj(_n) {}

    size_t size() const { return adj.size(); }
    typename decltype(adj)::reference operator[](size_t node) { assert(node < size()); return adj[node]; }
    typename decltype(adj)::const_reference operator[](size_t node) const { assert(node < size()); return adj[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(cap <= 0) return;
        adj[src].emplace_back(src, dst, cap, cost, adj[dst].size());
        adj[dst].emplace_back(dst, src, 0, -cost, adj[src].size() - 1);
    }
}; // struct flow_base

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

