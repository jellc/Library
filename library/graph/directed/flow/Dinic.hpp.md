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


# :heavy_check_mark: graph/directed/flow/Dinic.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#13554c95f4603c3979d32881e43d19e6">graph/directed/flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow/Dinic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-04 04:48:51+09:00




## Depends on

* :heavy_check_mark: <a href="base.hpp.html">graph/directed/flow/base.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../../verify/test/library-checker/bipartitematching.test.cpp.html">test/library-checker/bipartitematching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "base.hpp"
// compute the maximum flow.
template <class cap_t = int>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    std::vector<size_t> level;
    std::vector<edge_t*> itr;
    constexpr static size_t level_infty = -1;

    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)
    {
        if(src == dst || bound == 0) return bound;
        cap_t flow(0);
        for(edge_t* &e{itr[dst]}; e != adjs[dst].end(); ++e)
            if(e->rev->avbl() && level[e->dst] < level[dst])
                if(cap_t achv = dfs(src, e->dst, std::min(bound, e->rev->cap)); achv > 0)
                {
                    e->rev->flow(achv);
                    flow += achv, bound -= achv;
                    if(bound == 0) break;
                }
        return flow;
    }

public:
    using base::size;

    Dinic(size_t n = 0) : base::flow_base(n), level(n, level_infty), itr(n) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.level), itr(other.itr)  {}

    Dinic &operator=(const Dinic &rhs)
    {
        if(this != &rhs) base::operator=(rhs), level = rhs.level, itr = rhs.itr;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap) { base::add_edge(src, dst, cap, false); }

    void add_undirected_edge(size_t src, size_t dst, cap_t cap) { base::add_undirected_edge(src, dst, cap, false); }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0), bound(0);
        for(const edge_t &e : adjs[src]) bound += e.cap;
        for(std::vector<size_t> que(size()); ; std::fill(level.begin(), level.end(), level_infty))
        {
            level[que.front() = src] = 0;
            for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty && ql != qr; ++ql)
                for(const edge_t &e : adjs[*ql])
                    if(e.avbl() && level[e.dst] == level_infty)
                        level[*qr++ = e.dst] = level[*ql] + 1;
            if(level[dst] == level_infty) break;
            for(size_t node{}; node != size(); ++node) itr[node] = adjs[node].begin();
            flow += dfs(src, dst, bound);
        }
        return flow;
    }
}; // class Dinic

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/directed/flow/base.hpp"
#include <cassert>
#include <vector>
// the base class of flow algorithms.
template <class cap_t, class cost_t> struct flow_base {
  struct edge_t {
    size_t src, dst;
    cap_t cap;
    cost_t cost;
    edge_t *rev;
    edge_t() = default;
    edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev)
        : src(src), dst(dst), cap(cap), rev(rev) {}
    edge_t(size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev)
        : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
    void flow(cap_t f) { cap -= f, rev->cap += f; }
    bool avbl() const { return cap > 0; }
  };  // class edge_t

  class adj_type {
    edge_t *fst, *lst, *clst;

   public:
    template <class... Args> edge_t *emplace(Args &&... args) {
      if (lst == clst) {
        size_t len(clst - fst);
        edge_t *nfst = lst = new edge_t[len << 1];
        for (edge_t *p{fst}; p != clst; ++p, ++lst)
          p->rev->rev = lst, *lst = *p;
        delete[] fst;
        fst = nfst;
        clst = lst + len;
      }
      *lst = edge_t(args...);
      return lst++;
    }
    adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
    ~adj_type() { delete[] fst; }
    edge_t &operator[](size_t i) {
      assert(i < size());
      return *(fst + i);
    }
    size_t size() const { return lst - fst; }
    edge_t *begin() const { return fst; }
    edge_t *end() const { return lst; }
  };  // class adj_type

  flow_base(size_t n = 0) : adjs(n) {}

  flow_base(const flow_base &other) : adjs(other.size()) {
    for (size_t node{}; node != size(); ++node)
      for (const auto &[src, dst, cap, cost, rev] : other[node])
        if (src == node) {
          edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
          ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
          rev->src = -1;
        } else {
          rev->rev->src = node;
        }
  }

  flow_base &operator=(const flow_base &rhs) {
    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);
    return *this;
  }

  size_t size() const { return adjs.size(); }

  adj_type &operator[](size_t node) {
    assert(node < size());
    return adjs[node];
  }
  const adj_type &operator[](size_t node) const {
    assert(node < size());
    return adjs[node];
  }

  virtual void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost) {
    assert(src < size());
    assert(dst < size());
    if (!(cap > 0) || src == dst) return;
    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);
  }

 protected:
  std::vector<adj_type> adjs;
};  // class flow_base
#line 3 "graph/directed/flow/Dinic.hpp"
// compute the maximum flow.
template <class cap_t = int>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    std::vector<size_t> level;
    std::vector<edge_t*> itr;
    constexpr static size_t level_infty = -1;

    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)
    {
        if(src == dst || bound == 0) return bound;
        cap_t flow(0);
        for(edge_t* &e{itr[dst]}; e != adjs[dst].end(); ++e)
            if(e->rev->avbl() && level[e->dst] < level[dst])
                if(cap_t achv = dfs(src, e->dst, std::min(bound, e->rev->cap)); achv > 0)
                {
                    e->rev->flow(achv);
                    flow += achv, bound -= achv;
                    if(bound == 0) break;
                }
        return flow;
    }

public:
    using base::size;

    Dinic(size_t n = 0) : base::flow_base(n), level(n, level_infty), itr(n) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.level), itr(other.itr)  {}

    Dinic &operator=(const Dinic &rhs)
    {
        if(this != &rhs) base::operator=(rhs), level = rhs.level, itr = rhs.itr;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap) { base::add_edge(src, dst, cap, false); }

    void add_undirected_edge(size_t src, size_t dst, cap_t cap) { base::add_undirected_edge(src, dst, cap, false); }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0), bound(0);
        for(const edge_t &e : adjs[src]) bound += e.cap;
        for(std::vector<size_t> que(size()); ; std::fill(level.begin(), level.end(), level_infty))
        {
            level[que.front() = src] = 0;
            for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty && ql != qr; ++ql)
                for(const edge_t &e : adjs[*ql])
                    if(e.avbl() && level[e.dst] == level_infty)
                        level[*qr++ = e.dst] = level[*ql] + 1;
            if(level[dst] == level_infty) break;
            for(size_t node{}; node != size(); ++node) itr[node] = adjs[node].begin();
            flow += dfs(src, dst, bound);
        }
        return flow;
    }
}; // class Dinic

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

