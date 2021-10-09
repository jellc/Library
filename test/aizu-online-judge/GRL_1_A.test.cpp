#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"

#include <iostream>

#include "src/graph/digraph.h"

int main() {
  size_t n, m, r, s, t;
  std::cin >> n >> m >> r;

  workspace::weighted_digraph<uint64_t> g(n);
  while (m--) {
    uint64_t w;
    std::cin >> s >> t >> w;
    g.add_edge(s, t, w);
  }

  std::vector<uint64_t> dist(g.size(), -1);
  dist[r] = 0;
  for (auto &&e : g.dijkstra(r)) {
    dist[e.head] = e.weight;
  }

  for (auto &&d : dist)
    if (~d)
      std::cout << d << "\n";
    else
      std::cout << "INF\n";
}
