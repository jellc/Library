#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <cstdio>

#include "src/graph/directed/strongly_connected_components.hpp"

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
