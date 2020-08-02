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


# :warning: graph/directed/flow-linked_list/Dinic.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#b98bdf6a8292f4ca195ed397b75cf977">graph/directed/flow-linked_list</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/flow-linked_list/Dinic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 16:01:43+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <queue>

// Computing the maximum flow
// depends on base.hpp
template <class cap_t>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using itr_type = typename base::adj_type::value_type::iterator;
    std::vector<size_t> level;
    cap_t max_cap;

    bool bfs(size_t src, size_t dst)
    {
        fill(level.begin(), level.end(), -1);
        std::queue<size_t> que; que.emplace(src);
        level[src] = 0;
        while(!que.empty())
        {
            size_t node{que.front()}; que.pop();
            for(const auto &e : base::adj[node])
            {
                if(e.cap > 0 && level[e.dst] == size_t(-1))
                {
                    level[e.dst] = level[node] + 1;
                    que.emplace(e.dst);
                }
            }
        }
        return ~level[dst];
    }

    cap_t dfs(size_t node, size_t dst, cap_t bound, std::vector<itr_type> &itr)
    {
        if(node == dst) return bound;
        cap_t flow(0);
        for(itr_type &e{itr[node]}; e != base::adj[node].end(); ++e)
        {
            if(e->cap > 0 && level[node] < level[e->dst])
            {
                cap_t achv = dfs(e->dst, dst, std::min(bound, e->cap), itr);
                e->cap -= achv, e->rev->cap += achv;
                flow += achv, bound -= achv;
                if(bound == 0) break;
            }
        }
        return flow;
    }

public:
    Dinic(size_t _n = 0) : base::flow_base(_n), level(_n), max_cap(0) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.size()), max_cap(0) {}

    Dinic &operator=(const Dinic &other)
    {
        base::operator=(other);
        level = other.level;
        max_cap = other.max_cap;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        max_cap = std::max(max_cap, cap);
        base::add_edge(src, dst, cap, 0);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < base::size()); assert(dst < base::size());
        cap_t flow(0);
        std::vector<itr_type> itr(base::size());
        while(bfs(src, dst))
        {
            for(size_t node{0}; node != base::size(); ++node) itr[node] = base::adj[node].begin();
            cap_t resid; while((resid = dfs(src, dst, max_cap, itr)) > 0) flow += resid;
        }
        return flow;
    }

    std::vector<bool> min_cut(size_t src, size_t dst)
    {
        max_flow(src, dst);
        std::vector<bool> res(base::size());
        for(size_t node{0}; node != base::size(); ++node) res[node] = ~level[node];
        return res;
    }
}; // class Dinic

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/directed/flow-linked_list/Dinic.hpp"
#include <queue>

// Computing the maximum flow
// depends on base.hpp
template <class cap_t>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using itr_type = typename base::adj_type::value_type::iterator;
    std::vector<size_t> level;
    cap_t max_cap;

    bool bfs(size_t src, size_t dst)
    {
        fill(level.begin(), level.end(), -1);
        std::queue<size_t> que; que.emplace(src);
        level[src] = 0;
        while(!que.empty())
        {
            size_t node{que.front()}; que.pop();
            for(const auto &e : base::adj[node])
            {
                if(e.cap > 0 && level[e.dst] == size_t(-1))
                {
                    level[e.dst] = level[node] + 1;
                    que.emplace(e.dst);
                }
            }
        }
        return ~level[dst];
    }

    cap_t dfs(size_t node, size_t dst, cap_t bound, std::vector<itr_type> &itr)
    {
        if(node == dst) return bound;
        cap_t flow(0);
        for(itr_type &e{itr[node]}; e != base::adj[node].end(); ++e)
        {
            if(e->cap > 0 && level[node] < level[e->dst])
            {
                cap_t achv = dfs(e->dst, dst, std::min(bound, e->cap), itr);
                e->cap -= achv, e->rev->cap += achv;
                flow += achv, bound -= achv;
                if(bound == 0) break;
            }
        }
        return flow;
    }

public:
    Dinic(size_t _n = 0) : base::flow_base(_n), level(_n), max_cap(0) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.size()), max_cap(0) {}

    Dinic &operator=(const Dinic &other)
    {
        base::operator=(other);
        level = other.level;
        max_cap = other.max_cap;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        max_cap = std::max(max_cap, cap);
        base::add_edge(src, dst, cap, 0);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < base::size()); assert(dst < base::size());
        cap_t flow(0);
        std::vector<itr_type> itr(base::size());
        while(bfs(src, dst))
        {
            for(size_t node{0}; node != base::size(); ++node) itr[node] = base::adj[node].begin();
            cap_t resid; while((resid = dfs(src, dst, max_cap, itr)) > 0) flow += resid;
        }
        return flow;
    }

    std::vector<bool> min_cut(size_t src, size_t dst)
    {
        max_flow(src, dst);
        std::vector<bool> res(base::size());
        for(size_t node{0}; node != base::size(); ++node) res[node] = ~level[node];
        return res;
    }
}; // class Dinic

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

