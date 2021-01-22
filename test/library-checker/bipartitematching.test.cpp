#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>

#include "src/graph/directed/flow/Dinic.hpp"

int main() {
  using namespace workspace;

  int l, r, m;
  scanf("%d%d%d", &l, &r, &m);
  Dinic<int> dinic(l + r + 2);
  const int s = l + r, t = s + 1;

  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    dinic.add_edge(a, b + l);
  }
  for (int i = 0; i < l; ++i) dinic.add_edge(s, i);
  for (int i = 0; i < r; ++i) dinic.add_edge(i + l, t);

  printf("%d\n", dinic.run(s, t));
  for (int i = 0; i < l; ++i) {
    for (const auto &e : dinic[i]) {
      if (!e.cap) {
        printf("%d %d\n", i, e.dst - l);
      }
    }
  }
}
