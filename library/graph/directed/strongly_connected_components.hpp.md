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
    - Last commit date: 2020-09-05 02:51:04+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/library-checker/scc.test.cpp.html">test/library-checker/scc.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
struct strongly_connected_components {
  strongly_connected_components(size_t n) : graph(n), low(n), made() {}

  // add an edge from the vertex s to the vertex t.
  void add_edge(size_t src, size_t dst) {
    assert(src < size());
    assert(dst < size());
    graph[src].emplace_back(dst);
    made = false;
  }

  // the number of the components.
  size_t count() {
    make();
    return comp_cnt;
  }

  size_t size() const { return graph.size(); }

  // the component which the vertex v belongs to.
  size_t operator[](size_t v) {
    make();
    return low[v];
  }

  // the directed acyclic graph consisting of the components.
  const std::vector<std::vector<size_t>> &shrinked_dag() {
    make();
    return dag;
  }

 protected:
  std::vector<std::vector<size_t>> graph, dag;
  std::vector<size_t> low;
  size_t comp_cnt;
  bool made;

  void make() {
    if (made) return;
    made = true, comp_cnt = 0;
    low.assign(size(), 0);
    size_t *itr = new size_t[size()];
    bool *const used = new bool[size()];
    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());
    delete[] itr;
    delete[] used;
    for (auto &e : low) e += comp_cnt;
    reverse(begin(dag), end(dag));
    for (auto &arcs : dag)
      for (auto &to : arcs) to += comp_cnt;
  }

  size_t affix(size_t src, size_t &c, size_t *&itr, bool *used) {
    if (low[src]) return low[src];
    size_t idx = ++c;
    low[src] = idx;
    *itr++ = src;
    for (size_t dst : graph[src])
      low[src] = std::min(low[src], affix(dst, c, itr, used));
    if (low[src] == idx) {
      ++comp_cnt;
      used[-comp_cnt] = true;
      dag.emplace_back(0);
      auto srcp = itr;
      do {
        low[*--srcp] = -comp_cnt;
      } while (*srcp != src);
      while (itr != srcp) {
        auto now = *--itr;
        for (auto to : graph[now]) {
          if (!used[(int)low[to]]) {
            dag.back().emplace_back(low[to]);
            used[(int)low[to]] = true;
          }
        }
      }
      for (int c : dag.back()) used[c] = false;
      used[-comp_cnt] = false;
      return idx;
    }
    return low[src];
  }
};  // class strongly_connected_components

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/directed/strongly_connected_components.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
struct strongly_connected_components {
  strongly_connected_components(size_t n) : graph(n), low(n), made() {}

  // add an edge from the vertex s to the vertex t.
  void add_edge(size_t src, size_t dst) {
    assert(src < size());
    assert(dst < size());
    graph[src].emplace_back(dst);
    made = false;
  }

  // the number of the components.
  size_t count() {
    make();
    return comp_cnt;
  }

  size_t size() const { return graph.size(); }

  // the component which the vertex v belongs to.
  size_t operator[](size_t v) {
    make();
    return low[v];
  }

  // the directed acyclic graph consisting of the components.
  const std::vector<std::vector<size_t>> &shrinked_dag() {
    make();
    return dag;
  }

 protected:
  std::vector<std::vector<size_t>> graph, dag;
  std::vector<size_t> low;
  size_t comp_cnt;
  bool made;

  void make() {
    if (made) return;
    made = true, comp_cnt = 0;
    low.assign(size(), 0);
    size_t *itr = new size_t[size()];
    bool *const used = new bool[size()];
    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());
    delete[] itr;
    delete[] used;
    for (auto &e : low) e += comp_cnt;
    reverse(begin(dag), end(dag));
    for (auto &arcs : dag)
      for (auto &to : arcs) to += comp_cnt;
  }

  size_t affix(size_t src, size_t &c, size_t *&itr, bool *used) {
    if (low[src]) return low[src];
    size_t idx = ++c;
    low[src] = idx;
    *itr++ = src;
    for (size_t dst : graph[src])
      low[src] = std::min(low[src], affix(dst, c, itr, used));
    if (low[src] == idx) {
      ++comp_cnt;
      used[-comp_cnt] = true;
      dag.emplace_back(0);
      auto srcp = itr;
      do {
        low[*--srcp] = -comp_cnt;
      } while (*srcp != src);
      while (itr != srcp) {
        auto now = *--itr;
        for (auto to : graph[now]) {
          if (!used[(int)low[to]]) {
            dag.back().emplace_back(low[to]);
            used[(int)low[to]] = true;
          }
        }
      }
      for (int c : dag.back()) used[c] = false;
      used[-comp_cnt] = false;
      return idx;
    }
    return low[src];
  }
};  // class strongly_connected_components

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

