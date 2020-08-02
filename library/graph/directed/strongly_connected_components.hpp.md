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


# :heavy_check_mark: graph/directed/strongly_connected_components.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#969c55f60d4e435b31ce9719112e0fcf">graph/directed</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/strongly_connected_components.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 03:53:14+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/library-checker/scc.test.cpp.html">test/library-checker/scc.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef strongly_connected_components_hpp
#define strongly_connected_components_hpp

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
            for(size_t src : memb[i]) for(size_t dst : graph[src]) if(!apr[comp[dst]]) apr[comp[dst]] = true, *itr++ = comp[dst];
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

    size_t affix(size_t src, size_t &c, size_t* &itr)
    {
        if(~low[src]) return ~comp[src] ? -1 : low[src];
        size_t idx = c++; low[src] = idx; *itr++ = src;
        for(size_t dst : graph[src]) low[src] = std::min(low[src], affix(dst, c, itr));
        if(low[src] == idx) { do { comp[*--itr] = cnt; } while(*itr != src); ++cnt; }
        return low[src];
    }
}; // class strongly_connected_components

#endif // strongly_connected_components_hpp

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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
            for(size_t src : memb[i]) for(size_t dst : graph[src]) if(!apr[comp[dst]]) apr[comp[dst]] = true, *itr++ = comp[dst];
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

    size_t affix(size_t src, size_t &c, size_t* &itr)
    {
        if(~low[src]) return ~comp[src] ? -1 : low[src];
        size_t idx = c++; low[src] = idx; *itr++ = src;
        for(size_t dst : graph[src]) low[src] = std::min(low[src], affix(dst, c, itr));
        if(low[src] == idx) { do { comp[*--itr] = cnt; } while(*itr != src); ++cnt; }
        return low[src];
    }
}; // class strongly_connected_components



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

