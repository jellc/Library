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


# :heavy_check_mark: test/library-checker/scc.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/scc.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 03:44:15+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/directed/strongly_connected_components.hpp.html">graph/directed/strongly_connected_components.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../../graph/directed/strongly_connected_components.hpp"
#include <cstdio>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    strongly_connected_components scc(n);
    for(int a,b; m--; )
    {
        scanf("%d%d",&a,&b);
        scc.add_edge(a,b);
    }
    printf("%d\n",scc.count());
    for(size_t i=0; i<scc.count(); i++)
    {
        printf("%d",scc.size(i));
        for(int v: scc.component(i)) printf(" %d",v);
        puts("");
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/scc.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#line 1 "graph/directed/strongly_connected_components.hpp"



#include <cassert>
#include <vector>

class strongly_connected_components
{
    std::vector<std::vector<size_t>> graph, memb;
    std::vector<size_t> comp, low;
    size_t cnt;
    bool made;

public:
    strongly_connected_components(size_t n) : graph(n), comp(n), low(n), made() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        graph[src].emplace_back(dst);
        made = false;
    }

    // the number of the components.
    size_t count() { make(); return cnt; }

    size_t size() const { return graph.size(); }

    // the number of vertices in the i-th component.
    size_t size(size_t i) { make(); return memb[i].size(); }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i) { make(); return memb[i]; }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { make(); return comp[v]; }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        make();
        std::vector<std::vector<size_t>> res(cnt);
        bool *apr = new bool[size()]{};
        size_t *stack_ptr = new size_t[size()];
        for(size_t i = 0; i != cnt; ++i)
        {
            size_t *itr = stack_ptr;
            for(size_t s : memb[i]) for(size_t t : graph[s]) if(!apr[comp[t]]) apr[comp[t]] = true, *itr++ = comp[t];
            res[i].resize(itr - stack_ptr);
            while(itr != stack_ptr) apr[res[i][--itr - stack_ptr] = *itr] = false;
        }
        delete[] apr; delete[] stack_ptr;
        return res;
    }

protected:
    void make()
    {
        if(made) return;
        made = true, cnt = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        size_t *itr = new size_t[size()];
        for(size_t v = 0, c = 0; v != size(); ++v) affix(v, c, itr);
        delete[] itr; memb.resize(cnt);
        for(size_t v = 0; v != size(); ++v) memb[comp[v] = cnt - 1 - comp[v]].emplace_back(v);
    }

    size_t affix(size_t v, size_t &c, size_t* &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++; low[v] = idx; *itr++ = v;
        for(int u : graph[v]) low[v] = std::min(low[v], affix(u, c, itr));
        if(low[v] == idx) { do { comp[*--itr] = cnt; } while(*itr != v); ++cnt; }
        return low[v];
    }
}; // class strongly_connected_components


#line 3 "test/library-checker/scc.test.cpp"
#include <cstdio>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    strongly_connected_components scc(n);
    for(int a,b; m--; )
    {
        scanf("%d%d",&a,&b);
        scc.add_edge(a,b);
    }
    printf("%d\n",scc.count());
    for(size_t i=0; i<scc.count(); i++)
    {
        printf("%d",scc.size(i));
        for(int v: scc.component(i)) printf(" %d",v);
        puts("");
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

