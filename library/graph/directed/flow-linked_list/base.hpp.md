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


# :warning: graph/directed/flow-linked_list/base.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#b98bdf6a8292f4ca195ed397b75cf977">graph/directed/flow-linked_list</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow-linked_list/base.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 16:17:19+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <list>
#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost;
        edge_t *rev;
        edge_t(size_t _src, size_t _dst, cap_t _cap, cost_t _cost, edge_t *_rev)
            : src(_src), dst(_dst), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

protected:
    using adj_type = std::vector<std::list<edge_t>>;
    adj_type adj;

public:
    flow_base(size_t _n = 0) : adj(_n) {}

    flow_base(const flow_base& other) : adj(other.size())
    {
        for(size_t node{0}; node != other.size(); ++node)
        {
            for(const auto &e : other[node])
            {
                if(e.src == node)
                {
                    adj[e.src].emplace_back(e);
                    adj[e.dst].emplace_back(*e.rev);
                    adj[e.src].back().rev = &adj[e.dst].back();
                    adj[e.dst].back().rev = &adj[e.src].back();
                    e.rev->src = -1;
                }
                else
                {
                    e.rev->rev->src = node;
                }
            }
        }
    }

    flow_base &operator=(const flow_base &other)
    {
        if(this != &other)
        {
            flow_base cop(other);
            std::swap(adj, cop.adj);
        }
        return *this;
    }

    size_t size() const { return adj.size(); }

    typename decltype(adj)::reference operator[](size_t node) { assert(node < size()); return adj[node]; }
    typename decltype(adj)::const_reference operator[](size_t node) const { assert(node < size()); return adj[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(cap <= 0) return;
        adj[src].emplace_back(src, dst, cap, cost, nullptr);
        adj[dst].emplace_back(dst, src, 0, -cost, nullptr);
        adj[src].back().rev = &adj[dst].back();
        adj[dst].back().rev = &adj[src].back();
    }
}; // struct flow_base

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/directed/flow-linked_list/base.hpp"
#include <cassert>
#include <list>
#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost;
        edge_t *rev;
        edge_t(size_t _src, size_t _dst, cap_t _cap, cost_t _cost, edge_t *_rev)
            : src(_src), dst(_dst), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

protected:
    using adj_type = std::vector<std::list<edge_t>>;
    adj_type adj;

public:
    flow_base(size_t _n = 0) : adj(_n) {}

    flow_base(const flow_base& other) : adj(other.size())
    {
        for(size_t node{0}; node != other.size(); ++node)
        {
            for(const auto &e : other[node])
            {
                if(e.src == node)
                {
                    adj[e.src].emplace_back(e);
                    adj[e.dst].emplace_back(*e.rev);
                    adj[e.src].back().rev = &adj[e.dst].back();
                    adj[e.dst].back().rev = &adj[e.src].back();
                    e.rev->src = -1;
                }
                else
                {
                    e.rev->rev->src = node;
                }
            }
        }
    }

    flow_base &operator=(const flow_base &other)
    {
        if(this != &other)
        {
            flow_base cop(other);
            std::swap(adj, cop.adj);
        }
        return *this;
    }

    size_t size() const { return adj.size(); }

    typename decltype(adj)::reference operator[](size_t node) { assert(node < size()); return adj[node]; }
    typename decltype(adj)::const_reference operator[](size_t node) const { assert(node < size()); return adj[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(cap <= 0) return;
        adj[src].emplace_back(src, dst, cap, cost, nullptr);
        adj[dst].emplace_back(dst, src, 0, -cost, nullptr);
        adj[src].back().rev = &adj[dst].back();
        adj[dst].back().rev = &adj[src].back();
    }
}; // struct flow_base

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

