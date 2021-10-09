#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "src/graph/scc.h"

#include <cstdio>

int main() {
  size_t n, m, s, t;
  scanf("%zu%zu", &n, &m);

  workspace::digraph g(n);
  while (m--) {
    scanf("%zu%zu", &s, &t);
    g.add_edge(s, t);
  }

  auto scc = g.scc();
  printf("%zu\n", scc.size());

  for (auto &&c : scc) {
    printf("%zu", c.size());
    for (auto v : c) printf(" %zu", v);
    puts("");
  }
}
