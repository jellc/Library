#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>

#include "src/graph/directed/flow/Dinic.hpp"

int main() {
  int l, r, m;
  scanf("%d%d%d", &l, &r, &m);
  Dinic<int> dinic(l + r + 2);
  const int s = l + r, t = s + 1;

  for (int i = 0, a, b; i < m; ++i) {
    scanf("%d%d", &a, &b);
    dinic.add_edge(a, b + l, 1);
  }
  for (int i = 0; i < l; ++i) {
    dinic.add_edge(s, i, 1);
  }
  for (int i = 0; i < r; ++i) {
    dinic.add_edge(i + l, t, 1);
  }

  printf("%d\n", dinic.max_flow(s, t));

  for (int i = 0; i < l; ++i) {
    for (const auto &e : dinic[i]) {
      if (!e.cap and e.dst < l + r) {
        printf("%d %d\n", i, e.dst - l);
      }
    }
  }
}
