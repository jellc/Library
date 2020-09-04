#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <cstdio>
#include <ext/rope>

#include "graph/undirected/tree/lowest_common_ancestor.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  lowest_common_ancestor lca(n);
  for (int i = 1, p; i < n; i++) {
    scanf("%d", &p);
    lca.add_edge(i, p);
  }
  lca.make(0);
  for (int u, v; q--;) {
    scanf("%d%d", &u, &v);
    printf("%d\n", (int)lca.query(u, v));
  }
}
