#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A"

#include <iostream>

#include "src/graph/forest.h"

int main() {
  size_t n, u, v, w;
  std::cin >> n;
  workspace::weighted_forest<size_t> g(n);

  while (--n) {
    std::cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }

  w = 0;
  for (auto &&e : g.diameter()) w += e.weight;
  std::cout << w << "\n";
}
