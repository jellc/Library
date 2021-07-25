#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>

#include "src/graph/directed/flow/Dinic.hpp"

int main() {
  using namespace workspace;

  size_t l, r, m;
  scanf("%zu%zu%zu", &l, &r, &m);
  Dinic<int> dinic(l + r + 2);

  const auto s = l + r, t = s + 1;
  for (size_t i = 0; i < l; ++i) dinic.add_edge(s, i);
  for (size_t i = 0; i < r; ++i) dinic.add_edge(i + l, t);

  for (; m--;) {
    size_t a, b;
    scanf("%zu%zu", &a, &b);
    dinic.add_edge(a, b + l);
  }

  printf("%d\n", dinic.run(s, t));
  for (size_t i = 0; i < l; ++i) {
    for (const auto &e : dinic[i]) {
      if (!e.capacity) {
        printf("%zu %zu\n", i, e.head - l);
      }
    }
  }
}
