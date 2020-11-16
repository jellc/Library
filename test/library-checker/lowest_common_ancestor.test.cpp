#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <cstdio>
#include <ext/rope>

#include "src/graph/undirected/tree/heavy_light_decomposition.hpp"
#include "src/graph/undirected/tree/lowest_common_ancestor.hpp"

int main() {
  size_t n, q;
  scanf("%lu%lu", &n, &q);
  lowest_common_ancestor lca(n);
  heavy_light_decomposition hld(n);
  for (size_t i = 1, p; i < n; i++) {
    scanf("%lu", &p);
    lca.add_edge(i, p);
    hld.add_edge(i, p);
  }
  lca.make(0);
  hld.make(0);
  for (size_t u, v; q--;) {
    scanf("%lu%lu", &u, &v);
    auto [left, right] = hld.path_decomposition(u, v);
    std::tie(u, v) = std::make_pair(lca.query(u, v), hld.lca(u, v));
    assert(u == v);
    assert(u == hld.node(left.back().first));
    printf("%lu\n", u);
  }
}
