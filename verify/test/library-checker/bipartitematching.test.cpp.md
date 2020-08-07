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


# :heavy_check_mark: test/library-checker/bipartitematching.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/bipartitematching.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-08 03:08:56+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/variation/flow/Dinic.hpp.html">variation/flow/Dinic.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "variation/flow/Dinic.hpp"
#include <cstdio>

int main()
{
    int l,r,m; scanf("%d%d%d",&l,&r,&m);
    Dinic<int> dinic(l+r+2);
    const int s=l+r,t=s+1;

    for(int i = 0,a,b; i < m; ++i)
    {
        scanf("%d%d",&a,&b);
        dinic.add_edge(a,b+l,1);
    }
    for(int i = 0; i < l; ++i)
    {
        dinic.add_edge(s,i,1);
    }
    for(int i = 0; i < r; ++i)
    {
        dinic.add_edge(i+l,t,1);
    }

    printf("%d\n",dinic.max_flow(s,t));

    for(int i = 0; i < l; ++i)
    {
        for(const auto &e: dinic[i])
        {
            if(!e.cap and e.dst<l+r)
            {
                printf("%d %d\n", i, e.dst-l);
            }
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/bipartitematching.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#line 1 "variation/flow/Dinic.hpp"
#include <cassert>
#include <vector>
// compute the maximum flow.
template <class cap_t = int>
struct Dinic
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; size_t rev;
        edge_t(size_t src, size_t dst, cap_t cap, size_t rev) : src(src), dst(dst), cap(cap), rev(rev) {}
    };

    using adj_type = std::vector<edge_t>;

    Dinic(size_t n = 0) : adjs(n), level(n), itr(n) {}

    size_t size() const { return adjs.size(); }

    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node]; }
    const adj_type &operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());
        adjs[dst].emplace_back(dst, src, 0, adjs[src].size() - 1);
    }

    void add_undirected_edge(size_t src, size_t dst, cap_t cap)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());
        adjs[dst].emplace_back(dst, src, cap, adjs[src].size() - 1);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0), bound(0);
        for(const edge_t &e : adjs[src]) bound += e.cap;
        for(std::vector<size_t> que(size()); ; std::fill(itr.begin(), itr.end(), 0))
        {
            std::fill(level.begin(), level.end(), level_infty);
            level[que.front() = src] = 0;
            for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty && ql != qr; ++ql)
            {
                for(const edge_t &e : adjs[*ql])
                    if(e.cap > 0 && level[e.dst] == level_infty)
                        level[*qr++ = e.dst] = level[*ql] + 1;
            }
            if(level[dst] == level_infty) break;
            flow += dfs(src, dst, bound);
        }
        return flow;
    }

protected:
    std::vector<adj_type> adjs;
    std::vector<size_t> level, itr;
    constexpr static size_t level_infty = -1;

    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)
    {
        if(src == dst || bound == 0) return bound;
        cap_t flow(0);
        for(size_t &i{itr[dst]}; i != adjs[dst].size(); ++i)
        {
            auto &e = adjs[dst][i], &re = adjs[e.dst][e.rev];
            if(re.cap > 0 && level[e.dst] < level[dst])
            {
                if(cap_t achv = dfs(src, e.dst, std::min(bound, re.cap)); achv > 0)
                {
                    e.cap += achv, re.cap -= achv;
                    flow += achv, bound -= achv;
                    if(bound == 0) break;
                }
            }
        }
        return flow;
    }
}; // struct Dinic
#line 3 "test/library-checker/bipartitematching.test.cpp"
#include <cstdio>

int main()
{
    int l,r,m; scanf("%d%d%d",&l,&r,&m);
    Dinic<int> dinic(l+r+2);
    const int s=l+r,t=s+1;

    for(int i = 0,a,b; i < m; ++i)
    {
        scanf("%d%d",&a,&b);
        dinic.add_edge(a,b+l,1);
    }
    for(int i = 0; i < l; ++i)
    {
        dinic.add_edge(s,i,1);
    }
    for(int i = 0; i < r; ++i)
    {
        dinic.add_edge(i+l,t,1);
    }

    printf("%d\n",dinic.max_flow(s,t));

    for(int i = 0; i < l; ++i)
    {
        for(const auto &e: dinic[i])
        {
            if(!e.cap and e.dst<l+r)
            {
                printf("%d %d\n", i, e.dst-l);
            }
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

