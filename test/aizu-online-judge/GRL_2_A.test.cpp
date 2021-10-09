#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"

#include <iostream>

#include "src/graph/graph.h"

int main() {
  size_t n, m, s, t;
  uint64_t w;
  std::cin >> n >> m;

  workspace::weighted_graph<uint64_t> g(n);
  while (m--) {
    std::cin >> s >> t >> w;
    g.add_edge(s, t, w);
  }

  w = 0;
  for (auto&& e : g.prim()) w += e.weight;
  std::cout << w << "\n";
}
