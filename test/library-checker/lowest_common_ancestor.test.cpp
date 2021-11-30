#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "src/graph/undirected/tree/lowest_common_ancestor.hpp"

#include <cstdio>

#include "src/graph/undirected/tree/heavy_light_decomposition.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  lowest_common_ancestor<> lca(n);
  heavy_light_decomposition hld(n);
  for (int i = 1, p; i < n; i++) {
    scanf("%d", &p);
    lca.add_edge(i, p);
    hld.add_edge(i, p);
  }
  lca.make(0);
  hld.make(0);
  for (int u, v; q--;) {
    scanf("%d%d", &u, &v);
    auto [left, right] = hld.split_path(u, v);
    auto x = lca.get(u, v);
    auto y = hld.lca(u, v);
    assert(x == y);
    assert(x == hld.node(left.back().first));
    printf("%d\n", x);
  }
}
