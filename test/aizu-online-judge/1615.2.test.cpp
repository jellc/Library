#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1615"

#include <cstdio>

#include "src/graph/directed/flow/min_cost_flow.hpp"

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    workspace::min_cost_flow<int> g;
    const auto p = g.add_nodes(n);
    const auto r = g.add_nodes(m);
    const auto t = g.add_node();
    g.demand(t, m);
    for (int i = 0; i < m; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g.supply(r[i], 1);
      g.add_edge(r[i], p[a]);
      g.add_edge(r[i], p[b]);
    }
    for (int i = 0; i < n; ++i)
      for (int j = 1; j < n; ++j) g.add_edge(p[i], t, 1, j * 2 + 1);

    assert(g.run());
    int min = n, max = 0;
    for (auto v : p) {
      int f = 0;
      for (const auto &e : g[v]) f += e.flow;
      if (f < min)
        min = f;
      else if (max < f)
        max = f;
    }
    printf("%d %d\n", min, max);
  }
}
