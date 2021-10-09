#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C"

#include <cstdio>

#include "src/graph/scc.h"

int main() {
  size_t n, m, s, t;
  scanf("%zu%zu", &n, &m);

  workspace::digraph g(n);
  while (m--) {
    scanf("%zu%zu", &s, &t);
    g.add_edge(s, t);
  }

  auto scc = g.scc();
  std::vector<size_t> id(g.size());
  for (size_t i = 0; i != scc.size(); ++i)
    for (auto v : scc[i]) id[v] = i;

  scanf("%zu", &m);
  while (m--) {
    scanf("%zu%zu", &s, &t);
    printf("%d\n", id[s] == id[t]);
  }
}
