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


# :warning: graph/directed/strongly_connected_components.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#969c55f60d4e435b31ce9719112e0fcf">graph/directed</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/directed/strongly_connected_components.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 13:58:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef strongly_connected_components_hpp
#define strongly_connected_components_hpp
#include <vector>

class strongly_connected_components
{
    const size_t V;
    std::vector<std::vector<size_t>> adj, mem;
    std::vector<size_t> comp, low;
    size_t cnt;
    bool is_built;

  public:
    strongly_connected_components(size_t _V) : V(_V), adj(V), comp(V), low(V), is_built() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t s, size_t t) { adj[s].emplace_back(t); is_built = false; }

    // the number of the components.
    size_t count() { return build(), cnt; }

    // the number of vertices in the i-th component.
    size_t size(size_t i) { return build(), mem[i].size(); }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i) { return build(), mem[i]; }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { return build(), comp[v]; }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        build();
        std::vector<std::vector<size_t>> res(cnt);
        bool *apr = new bool[V]{};
        size_t *stack_ptr = new size_t[V];
        for(size_t i = 0; i != cnt; ++i)
        {
            size_t *itr = stack_ptr;
            for(size_t s : mem[i]) for(size_t t : adj[s]) if(!apr[comp[t]]) apr[comp[t]] = true, *itr++ = comp[t];
            res[i].resize(itr - stack_ptr);
            while(itr != stack_ptr) apr[res[i][--itr - stack_ptr] = *itr] = false;
        }
        delete[] apr; delete[] stack_ptr;
        return res;
    }

  protected:
    void build()
    {
        if(is_built) return;
        is_built = true, cnt = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        size_t *itr = new size_t[V];
        for(size_t v = 0, c = 0; v != V; ++v) affix(v, c, itr);
        delete[] itr; mem.resize(cnt);
        for(size_t v = 0; v != V; ++v) mem[comp[v] = cnt - 1 - comp[v]].emplace_back(v);
    }

    size_t affix(size_t v, size_t &c, size_t* &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++; low[v] = idx; *itr++ = v;
        for(int u : adj[v]) low[v] = std::min(low[v], affix(u, c, itr));
        if(low[v] == idx) { do { comp[*--itr] = cnt; } while(*itr != v); ++cnt; }
        return low[v];
    }
}; // class strongly_connected_components

#endif // strongly_connected_components_hpp

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/directed/strongly_connected_components.hpp"


#include <vector>

class strongly_connected_components
{
    const size_t V;
    std::vector<std::vector<size_t>> adj, mem;
    std::vector<size_t> comp, low;
    size_t cnt;
    bool is_built;

  public:
    strongly_connected_components(size_t _V) : V(_V), adj(V), comp(V), low(V), is_built() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t s, size_t t) { adj[s].emplace_back(t); is_built = false; }

    // the number of the components.
    size_t count() { return build(), cnt; }

    // the number of vertices in the i-th component.
    size_t size(size_t i) { return build(), mem[i].size(); }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i) { return build(), mem[i]; }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { return build(), comp[v]; }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        build();
        std::vector<std::vector<size_t>> res(cnt);
        bool *apr = new bool[V]{};
        size_t *stack_ptr = new size_t[V];
        for(size_t i = 0; i != cnt; ++i)
        {
            size_t *itr = stack_ptr;
            for(size_t s : mem[i]) for(size_t t : adj[s]) if(!apr[comp[t]]) apr[comp[t]] = true, *itr++ = comp[t];
            res[i].resize(itr - stack_ptr);
            while(itr != stack_ptr) apr[res[i][--itr - stack_ptr] = *itr] = false;
        }
        delete[] apr; delete[] stack_ptr;
        return res;
    }

  protected:
    void build()
    {
        if(is_built) return;
        is_built = true, cnt = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        size_t *itr = new size_t[V];
        for(size_t v = 0, c = 0; v != V; ++v) affix(v, c, itr);
        delete[] itr; mem.resize(cnt);
        for(size_t v = 0; v != V; ++v) mem[comp[v] = cnt - 1 - comp[v]].emplace_back(v);
    }

    size_t affix(size_t v, size_t &c, size_t* &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++; low[v] = idx; *itr++ = v;
        for(int u : adj[v]) low[v] = std::min(low[v], affix(u, c, itr));
        if(low[v] == idx) { do { comp[*--itr] = cnt; } while(*itr != v); ++cnt; }
        return low[v];
    }
}; // class strongly_connected_components



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

