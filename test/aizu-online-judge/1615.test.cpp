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

    int min = 0, max = n;
    for (int l = m / n, u; l >= 0; --l) {
      auto h = g;
      for (auto v : p) h.add_edge(v, t, l, l, 0);
      for (u = l; u - l < max - min && !h.flow(); ++u)
        for (auto &&v : p)
          for (auto &&e : h[v]) ++e.cap;
      if (u - l < max - min) min = l, max = u;
    }
    printf("%d %d\n", min, max);
  }
}
