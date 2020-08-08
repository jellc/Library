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


# :heavy_check_mark: graph/directed/flow/min_cost_flow.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#13554c95f4603c3979d32881e43d19e6">graph/directed/flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow/min_cost_flow.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-09 02:22:50+09:00




## Depends on

* :heavy_check_mark: <a href="base.hpp.html">graph/directed/flow/base.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../../verify/test/library-checker/assignment.test.cpp.html">test/library-checker/assignment.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "base.hpp"
#include <queue>
// Successive shortest paths algorithm.
template <class cap_t, class cost_t>
class min_cost_flow : public flow_base<cap_t, cost_t>
{
    using base = flow_base<cap_t, cost_t>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    cost_t min_cost, total_cost;
    std::vector<cap_t> supp;
    std::vector<cost_t> ptnl;

    void copy_member(const min_cost_flow &other)
    {
        min_cost = other.min_cost;
        total_cost = other.total_cost;
        supp = other.supp;
        ptnl = other.ptnl;
    }

    void Dijkstra(std::vector<edge_t*> &last)
    {
        const cost_t infty(total_cost + 1);
        std::vector<cost_t> nptnl(size(), infty);
        /*/ // O((V + E)logV)
        struct node_t
        {
            size_t id; cost_t dist;
            node_t(size_t id, cost_t dist) : id(id), dist(dist) {}
            bool operator<(const node_t &rhs) const { return rhs.dist < dist; }
        };
        std::priority_queue<node_t> que;
        for(size_t src{}; src != size(); ++src)
        {
            if(supp[src] > static_cast<cap_t>(0))
            {
                nptnl[src] = 0;
                for(edge_t &e : adjs[src])
                {
                    if(supp[e.dst] > static_cast<cap_t>(0)) continue;
                    if(e.avbl() && nptnl[e.dst] > e.cost)
                    {
                        que.emplace(e.dst, (nptnl[e.dst] = e.cost) - ptnl[e.dst]);
                        last[e.dst] = &e;
                    }
                }
            }
        }
        while(!que.empty())
        {
            auto [src, ndist] = que.top();
            que.pop();
            if(ndist + ptnl[src] != nptnl[src]) continue;
            for(edge_t &e : adjs[src])
            {
                if(e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)
                {
                    que.emplace(e.dst, (nptnl[e.dst] = nptnl[src] + e.cost) - ptnl[e.dst]);
                    last[e.dst] = &e;
                }
            }
        }
        /*/ // O(V^2)
        std::vector<bool> used(size());
        for(size_t src{}; src != size(); ++src)
        {
            if(supp[src] > static_cast<cap_t>(0))
            {
                used[src] = true;
                nptnl[src] = 0;
                for(edge_t &e : adjs[src])
                {
                    if(supp[e.dst] > static_cast<cap_t>(0)) continue;
                    if(e.avbl() && nptnl[e.dst] > e.cost)
                    {
                        nptnl[e.dst] = e.cost;
                        last[e.dst] = &e;
                    }
                }
            }
        }
        for(;;)
        {
            size_t src(-1); cost_t sp{infty};
            for(size_t node{}; node != size(); ++node)
            {
                if(used[node] || nptnl[node] == infty) continue;
                cost_t dist{nptnl[node] - ptnl[node]};
                if(sp > dist)
                {
                    sp = dist;
                    src = node;
                }
            }
            if(src == static_cast<size_t>(-1)) break;
            used[src] = true;
            for(edge_t &e : adjs[src])
            {
                if(e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)
                {
                    nptnl[e.dst] = nptnl[src] + e.cost;
                    last[e.dst] = &e;
                }
            }
        }
        //*/
        ptnl.swap(nptnl);
    }

public:
    using base::size;

    min_cost_flow(size_t _n = 0) : base::flow_base(_n), min_cost(0), total_cost(0), supp(_n), ptnl(_n)  {}

    min_cost_flow(const min_cost_flow &other) : base::flow_base(other) { copy_member(other); }

    min_cost_flow &operator=(const min_cost_flow &other)
    {
        base::operator=(other);
        copy_member(other);
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src != dst);
        if(cost < static_cast<cost_t>(0))
        {
            supp[src] -= cap;
            supp[dst] += cap;
            min_cost += cap * cost;
            total_cost -= cap * cost;
            base::add_edge(dst, src, cap, -cost);
        }
        else
        {
            total_cost += cap * cost;
            base::add_edge(src, dst, cap, cost);
        }
    }

    void supply(size_t node, cap_t vol) { assert(node < size()); supp[node] += vol; }

    bool flow()
    {
        for(bool aug = true; aug; )
        {
            aug = false;
            std::vector<edge_t*> last(size());
            Dijkstra(last);
            std::vector<bool> shut(size());
            for(size_t dst{}; dst != size(); ++dst)
            {
                if(supp[dst] < static_cast<cap_t>(0) and last[dst])
                {
                    cap_t resid{-supp[dst]};
                    size_t src{dst}, block(-1);
                    while(last[src] && !shut[src])
                    {
                        if(resid >= last[src]->cap) resid = last[block = src]->cap;
                        src = last[src]->src;
                    }
                    if(shut[src]) block = src;
                    else
                    {
                        if(resid >= supp[src])
                        {
                            resid = supp[src];
                            block = src;
                        }
                        for(edge_t *e{last[dst]}; e; e = last[e->src])
                        {
                            e->cap -= resid;
                            e->rev->cap += resid;
                        }
                        supp[src] -= resid;
                        supp[dst] += resid;
                        min_cost += ptnl[dst] * resid;
                        aug = true;
                    }
                    if(~block)
                    {
                        for(size_t node{dst}; node != block; node = last[node]->src) shut[node] = true;
                        shut[block] = true;
                    }
                }
            }
        }
        for(cap_t s : supp) if(s > static_cast<cap_t>(0)) return false;
        return true;
    }

    cost_t optimal() { assert(flow()); return min_cost; }
}; // class min_cost_flow

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
        size_t src, dst; cap_t cap; cost_t cost; edge_t *rev;
        edge_t() = default;
        edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev) : src(src), dst(dst), cap(cap), rev(rev) {}
        edge_t(size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        void flow(cap_t f) { cap -= f, rev->cap += f; }
        bool avbl() const { return cap > 0; }
    }; // class edge_t

    class adj_type
    {
        edge_t *fst, *lst, *clst;
    public:
        template <class ...Args>
        edge_t *emplace(Args&& ...args)
        {
            if(lst == clst)
            {
                size_t len(clst - fst);
                edge_t *nfst = lst = new edge_t[len << 1];
                for(edge_t *p{fst}; p != clst; ++p, ++lst) p->rev->rev = lst, *lst = *p;
                delete[] fst; fst = nfst;
                clst = lst + len;
            }
            *lst = edge_t(args...);
            return lst++;
        }
        adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
        ~adj_type() { delete[] fst; }
        edge_t &operator[](size_t i) { assert(i < size()); return *(fst + i); }
        size_t size() const { return lst - fst; }
        edge_t *begin() const { return fst; }
        edge_t *end() const { return lst; }
    }; // class adj_type

    flow_base(size_t n = 0) : adjs(n) {}

    flow_base(const flow_base& other) : adjs(other.size())
    {
        for(size_t node{}; node != size(); ++node)
            for(const auto &[src, dst, cap, cost, rev] : other[node])
                if(src == node)
                {
                    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
                    ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
                    rev->src = -1;
                }
                else rev->rev->src = node;
    }

    flow_base &operator=(const flow_base &rhs)
    {
        if(this != &rhs) std::swap(adjs, flow_base(rhs).adjs);
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
        ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);
    }

protected:
    std::vector<adj_type> adjs;
}; // class flow_base
#line 2 "graph/directed/flow/min_cost_flow.hpp"
#include <queue>
// Successive shortest paths algorithm.
template <class cap_t, class cost_t>
class min_cost_flow : public flow_base<cap_t, cost_t>
{
    using base = flow_base<cap_t, cost_t>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    cost_t min_cost, total_cost;
    std::vector<cap_t> supp;
    std::vector<cost_t> ptnl;

    void copy_member(const min_cost_flow &other)
    {
        min_cost = other.min_cost;
        total_cost = other.total_cost;
        supp = other.supp;
        ptnl = other.ptnl;
    }

    void Dijkstra(std::vector<edge_t*> &last)
    {
        const cost_t infty(total_cost + 1);
        std::vector<cost_t> nptnl(size(), infty);
        /*/ // O((V + E)logV)
        struct node_t
        {
            size_t id; cost_t dist;
            node_t(size_t id, cost_t dist) : id(id), dist(dist) {}
            bool operator<(const node_t &rhs) const { return rhs.dist < dist; }
        };
        std::priority_queue<node_t> que;
        for(size_t src{}; src != size(); ++src)
        {
            if(supp[src] > static_cast<cap_t>(0))
            {
                nptnl[src] = 0;
                for(edge_t &e : adjs[src])
                {
                    if(supp[e.dst] > static_cast<cap_t>(0)) continue;
                    if(e.avbl() && nptnl[e.dst] > e.cost)
                    {
                        que.emplace(e.dst, (nptnl[e.dst] = e.cost) - ptnl[e.dst]);
                        last[e.dst] = &e;
                    }
                }
            }
        }
        while(!que.empty())
        {
            auto [src, ndist] = que.top();
            que.pop();
            if(ndist + ptnl[src] != nptnl[src]) continue;
            for(edge_t &e : adjs[src])
            {
                if(e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)
                {
                    que.emplace(e.dst, (nptnl[e.dst] = nptnl[src] + e.cost) - ptnl[e.dst]);
                    last[e.dst] = &e;
                }
            }
        }
        /*/ // O(V^2)
        std::vector<bool> used(size());
        for(size_t src{}; src != size(); ++src)
        {
            if(supp[src] > static_cast<cap_t>(0))
            {
                used[src] = true;
                nptnl[src] = 0;
                for(edge_t &e : adjs[src])
                {
                    if(supp[e.dst] > static_cast<cap_t>(0)) continue;
                    if(e.avbl() && nptnl[e.dst] > e.cost)
                    {
                        nptnl[e.dst] = e.cost;
                        last[e.dst] = &e;
                    }
                }
            }
        }
        for(;;)
        {
            size_t src(-1); cost_t sp{infty};
            for(size_t node{}; node != size(); ++node)
            {
                if(used[node] || nptnl[node] == infty) continue;
                cost_t dist{nptnl[node] - ptnl[node]};
                if(sp > dist)
                {
                    sp = dist;
                    src = node;
                }
            }
            if(src == static_cast<size_t>(-1)) break;
            used[src] = true;
            for(edge_t &e : adjs[src])
            {
                if(e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)
                {
                    nptnl[e.dst] = nptnl[src] + e.cost;
                    last[e.dst] = &e;
                }
            }
        }
        //*/
        ptnl.swap(nptnl);
    }

public:
    using base::size;

    min_cost_flow(size_t _n = 0) : base::flow_base(_n), min_cost(0), total_cost(0), supp(_n), ptnl(_n)  {}

    min_cost_flow(const min_cost_flow &other) : base::flow_base(other) { copy_member(other); }

    min_cost_flow &operator=(const min_cost_flow &other)
    {
        base::operator=(other);
        copy_member(other);
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src != dst);
        if(cost < static_cast<cost_t>(0))
        {
            supp[src] -= cap;
            supp[dst] += cap;
            min_cost += cap * cost;
            total_cost -= cap * cost;
            base::add_edge(dst, src, cap, -cost);
        }
        else
        {
            total_cost += cap * cost;
            base::add_edge(src, dst, cap, cost);
        }
    }

    void supply(size_t node, cap_t vol) { assert(node < size()); supp[node] += vol; }

    bool flow()
    {
        for(bool aug = true; aug; )
        {
            aug = false;
            std::vector<edge_t*> last(size());
            Dijkstra(last);
            std::vector<bool> shut(size());
            for(size_t dst{}; dst != size(); ++dst)
            {
                if(supp[dst] < static_cast<cap_t>(0) and last[dst])
                {
                    cap_t resid{-supp[dst]};
                    size_t src{dst}, block(-1);
                    while(last[src] && !shut[src])
                    {
                        if(resid >= last[src]->cap) resid = last[block = src]->cap;
                        src = last[src]->src;
                    }
                    if(shut[src]) block = src;
                    else
                    {
                        if(resid >= supp[src])
                        {
                            resid = supp[src];
                            block = src;
                        }
                        for(edge_t *e{last[dst]}; e; e = last[e->src])
                        {
                            e->cap -= resid;
                            e->rev->cap += resid;
                        }
                        supp[src] -= resid;
                        supp[dst] += resid;
                        min_cost += ptnl[dst] * resid;
                        aug = true;
                    }
                    if(~block)
                    {
                        for(size_t node{dst}; node != block; node = last[node]->src) shut[node] = true;
                        shut[block] = true;
                    }
                }
            }
        }
        for(cap_t s : supp) if(s > static_cast<cap_t>(0)) return false;
        return true;
    }

    cost_t optimal() { assert(flow()); return min_cost; }
}; // class min_cost_flow

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

