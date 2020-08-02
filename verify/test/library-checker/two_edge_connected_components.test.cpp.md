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


# :heavy_check_mark: test/library-checker/two_edge_connected_components.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/two_edge_connected_components.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-02 16:56:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/two_edge_connected_components">https://judge.yosupo.jp/problem/two_edge_connected_components</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/undirected/two_edge_connected_components.hpp.html">graph/undirected/two_edge_connected_components.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../graph/undirected/two_edge_connected_components.hpp"
#include <cstdio>
#include <algorithm>

signed main()
{
    int v,e;
    scanf("%d%d",&v,&e);
    two_edge_connected_component becc(v);
    for(int a,b; e--;)
    {
        scanf("%d%d",&a,&b);
        becc.add_edge(a,b);
    }
    becc.make();
    printf("%d\n",becc.count());
    for(size_t i=0; i<becc.count(); i++)
    {
        const auto &lst=becc.component(i);
        printf("%d",lst.size());
        for(int v: lst)
        {
            printf(" %d",v);
        }
        puts("");
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/two_edge_connected_components.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#line 1 "graph/undirected/two_edge_connected_components.hpp"
#include <cassert>
#include <vector>

// instance: an undirected and not necessarily simple graph
class two_edge_connected_component
{
    static constexpr size_t nil = -1;
    bool made;
    std::vector<size_t> stack, low, comp;
    std::vector<std::vector<size_t>> graph, tree, memb;

    void make(size_t now, size_t pre)
    {
        size_t ord = low[now] = stack.size();
        stack.emplace_back(now);
        std::vector<size_t> brid;
        for(size_t to : graph[now])
        {
            if(to == pre) { pre = nil; continue; }
            if(low[to] == nil) make(to, now);
            if(low[to] > ord)
            {
                brid.emplace_back(to);
                graph[to].emplace_back(now);
            }
            else if(low[now] > low[to]) low[now] = low[to];
        }
        brid.swap(graph[now]);
        if(ord == low[now])
        {
            auto pos = stack.end();
            tree.resize(tree.size() + 1);
            auto &adjc = tree.back();
            do
            {
                --pos;
                comp[*pos] = memb.size();
                for(size_t u : graph[*pos]) adjc.emplace_back(comp[u]);
            } while(*pos != now);
            memb.emplace_back(pos, stack.end());
            stack.erase(pos, stack.end());
        }
    }

public:
    two_edge_connected_component(size_t n) : made(false), comp(n), graph(n)
    {
        stack.reserve(n); comp.reserve(n);
        tree.reserve(n); memb.reserve(n);
    }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()), assert(v < size());
        graph[u].emplace_back(v), graph[v].emplace_back(u);
        made = false;
    }

    void make()
    {
        if(made) return;
        made = true;
        low.assign(size(), nil);
        for(size_t v = 0; v != size(); ++v) if(low[v] == nil) make(v, nil);
    }

    size_t size() const { return graph.size(); }

    size_t size(size_t i) { make(); assert(i < count()); return memb[i].size(); }

    size_t count() { make(); return memb.size(); }

    size_t operator[](size_t v) { make(); assert(v < size()); return comp[v]; }

    const std::vector<size_t> &bridge(size_t v) { make(); assert(v < size()); return graph[v]; }

    const std::vector<size_t> &component(size_t i) { make(); assert(i < count()); return memb[i]; }

    const std::vector<std::vector<size_t>> &bridge_tree() { make(); return tree; }
}; // class two_edge_connected_component
#line 3 "test/library-checker/two_edge_connected_components.test.cpp"
#include <cstdio>
#include <algorithm>

signed main()
{
    int v,e;
    scanf("%d%d",&v,&e);
    two_edge_connected_component becc(v);
    for(int a,b; e--;)
    {
        scanf("%d%d",&a,&b);
        becc.add_edge(a,b);
    }
    becc.make();
    printf("%d\n",becc.count());
    for(size_t i=0; i<becc.count(); i++)
    {
        const auto &lst=becc.component(i);
        printf("%d",lst.size());
        for(int v: lst)
        {
            printf(" %d",v);
        }
        puts("");
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

