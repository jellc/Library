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
    - Last commit date: 2020-09-04 20:59:06+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/directed/strongly_connected_components.hpp.html">graph/directed/strongly_connected_components.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include <cstdio>

#include "graph/directed/strongly_connected_components.hpp"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  strongly_connected_components scc(n);
  for (int a, b; m--;) {
    scanf("%d%d", &a, &b);
    scc.add_edge(a, b);
  }
  printf("%d\n", scc.count());
  std::vector<std::vector<size_t>> comps(scc.count());
  for (int i = 0; i < n; i++) {
    comps[scc[i]].emplace_back(i);
  }
  for (auto &comp : comps) {
    printf("%d", size(comp));
    for (int v : comp) printf(" %d", v);
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
#include <cstdio>

#line 2 "graph/directed/strongly_connected_components.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
struct strongly_connected_components
{
    strongly_connected_components(size_t n) : graph(n), low(n), made() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        graph[src].emplace_back(dst);
        made = false;
    }

    // the number of the components.
    size_t count() { make(); return comp_cnt; }

    size_t size() const { return graph.size(); }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { make(); return low[v]; }

    // the directed acyclic graph consisting of the components.
    const std::vector<std::vector<size_t>> &shrinked_dag() { make(); return dag; }

protected:
    std::vector<std::vector<size_t>> graph, dag;
    std::vector<size_t> low;
    size_t comp_cnt;
    bool made;

    void make()
    {
        if(made) return;
        made = true, comp_cnt = 0;
        low.assign(size(), 0);
        size_t *itr = new size_t[size()];
        bool *const used = new bool[size()];
        for(size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());
        delete[] itr;
        delete[] used;
        for(auto &e : low) e += comp_cnt;
        reverse(begin(dag), end(dag));
        for(auto &arcs : dag)
            for(auto &to : arcs)
                to += comp_cnt;
    }

    size_t affix(size_t src, size_t &c, size_t* &itr, bool *used)
    {
        if(low[src]) return low[src];
        size_t idx = ++c; low[src] = idx; *itr++ = src;
        for(size_t dst : graph[src]) low[src] = std::min(low[src], affix(dst, c, itr, used));
        if(low[src] == idx)
        {
            ++comp_cnt;
            used[-comp_cnt] = true;
            dag.emplace_back(0);
            auto srcp = itr;
            do { low[*--srcp] = -comp_cnt; } while(*srcp != src);
            while(itr != srcp)
            {
                auto now = *--itr;
                for(auto to : graph[now])
                {
                    if(!used[(int)low[to]])
                    {
                        dag.back().emplace_back(low[to]);
                        used[(int)low[to]] = true;
                    }
                }
            }
            for(size_t c : dag.back()) used[(int)c] = false;
            used[-comp_cnt] = false;
            return idx;
        }
        return low[src];
    }
}; // class strongly_connected_components
#line 5 "test/library-checker/scc.test.cpp"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  strongly_connected_components scc(n);
  for (int a, b; m--;) {
    scanf("%d%d", &a, &b);
    scc.add_edge(a, b);
  }
  printf("%d\n", scc.count());
  std::vector<std::vector<size_t>> comps(scc.count());
  for (int i = 0; i < n; i++) {
    comps[scc[i]].emplace_back(i);
  }
  for (auto &comp : comps) {
    printf("%d", size(comp));
    for (int v : comp) printf(" %d", v);
    puts("");
  }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

