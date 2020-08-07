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


# :x: graph/directed/flow/base.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#13554c95f4603c3979d32881e43d19e6">graph/directed/flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow/base.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-07 21:13:26+09:00




## Required by

* :x: <a href="Dinic.hpp.html">graph/directed/flow/Dinic.hpp</a>


## Verified with

* :x: <a href="../../../../verify/test/library-checker/bipartitematching.test.cpp.html">test/library-checker/bipartitematching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <vector>
// the base class of flow algorithms.
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost; edge_t *rev;
        edge_t() {}
        edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev) : src(src), dst(dst), cap(cap), rev(rev) {}
        edge_t(size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        void flow(cap_t f) { cap -= f, rev->cap += f; }
    }; // class edge_t

    class adj_type
    {
        friend flow_base;
        edge_t *fst, *lst, *clst;
        template <class ...Args>
        edge_t *emplace(Args&& ...args)
        {
            if(lst == clst)
            {
                size_t len(clst - fst);
                edge_t *nfst = new edge_t[len << 1];
                lst = nfst;
                for(edge_t *p{fst}; p != clst; ++p, ++lst) p->rev->rev = lst, *lst = *p;
                delete[] fst;
                fst = nfst;
                clst = lst + len;
            }
            *lst = edge_t(args...);
            return lst++;
        }
    public:
        adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
        ~adj_type() { delete[] fst; }
        edge_t &operator[](size_t i) { assert(i < size()); return *(fst + i); }
        size_t size() const { return lst - fst; }
        edge_t *begin() const { return fst; }
        edge_t *end() const { return lst; }
    }; // class adj_type

    std::vector<adj_type> adjs;

public:
    flow_base(size_t n = 0) : adjs(n) {}

    flow_base(const flow_base& other) : adjs(other.size())
    {
        for(size_t node{}; node != size(); ++node)
        {
            for(const auto &[src, dst, cap, cost, rev] : other[node])
            {
                if(src == node)
                {
                    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
                    ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
                    rev->src = -1;
                }
                else rev->rev->src = node;
            }
        }
    }

    flow_base &operator=(const flow_base &rhs)
    {
        if(this != &rhs)
        {
            flow_base copy(rhs);
            std::swap(adjs, copy.adjs);
        }
        return *this;
    }

    size_t size() const { return adjs.size(); }

    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node]; }
    const adj_type &operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
        ptr->rev = adjs[dst].emplace(dst, src, 0, cost, ptr);
    }
}; // class flow_base

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/directed/flow/base.hpp"
#include <cassert>
#include <vector>
// the base class of flow algorithms.
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost; edge_t *rev;
        edge_t() {}
        edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev) : src(src), dst(dst), cap(cap), rev(rev) {}
        edge_t(size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        void flow(cap_t f) { cap -= f, rev->cap += f; }
    }; // class edge_t

    class adj_type
    {
        friend flow_base;
        edge_t *fst, *lst, *clst;
        template <class ...Args>
        edge_t *emplace(Args&& ...args)
        {
            if(lst == clst)
            {
                size_t len(clst - fst);
                edge_t *nfst = new edge_t[len << 1];
                lst = nfst;
                for(edge_t *p{fst}; p != clst; ++p, ++lst) p->rev->rev = lst, *lst = *p;
                delete[] fst;
                fst = nfst;
                clst = lst + len;
            }
            *lst = edge_t(args...);
            return lst++;
        }
    public:
        adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
        ~adj_type() { delete[] fst; }
        edge_t &operator[](size_t i) { assert(i < size()); return *(fst + i); }
        size_t size() const { return lst - fst; }
        edge_t *begin() const { return fst; }
        edge_t *end() const { return lst; }
    }; // class adj_type

    std::vector<adj_type> adjs;

public:
    flow_base(size_t n = 0) : adjs(n) {}

    flow_base(const flow_base& other) : adjs(other.size())
    {
        for(size_t node{}; node != size(); ++node)
        {
            for(const auto &[src, dst, cap, cost, rev] : other[node])
            {
                if(src == node)
                {
                    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
                    ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
                    rev->src = -1;
                }
                else rev->rev->src = node;
            }
        }
    }

    flow_base &operator=(const flow_base &rhs)
    {
        if(this != &rhs)
        {
            flow_base copy(rhs);
            std::swap(adjs, copy.adjs);
        }
        return *this;
    }

    size_t size() const { return adjs.size(); }

    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node]; }
    const adj_type &operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
        ptr->rev = adjs[dst].emplace(dst, src, 0, cost, ptr);
    }
}; // class flow_base

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

