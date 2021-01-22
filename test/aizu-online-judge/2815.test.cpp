#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2815"

#include <iostream>

#include "src/graph/directed/flow/min_cost_flow.hpp"

int main() {
  using namespace workspace;

  int n, m, k;
  std::cin >> n >> m >> k;

  min_cost_flow<int, int> mcf;
  const auto dst = mcf.add_node();
  const auto dst2 = mcf.add_node();
  const auto dst3 = mcf.add_node();

  mcf.demand(dst, n);
  mcf.add_edge(dst2, dst, n, 0);
  mcf.add_edge(dst3, dst, n - k, 0);

  const auto r = mcf.add_nodes(n);
  for (auto u : r) {
    mcf.supply(u);
    std::cin >> k;
    mcf.add_edge(u, dst2, 1, -k);
  }

  const auto f = mcf.add_nodes(m);
  for (auto v : f) {
    for (auto u : r) {
      std::cin >> k;
      mcf.add_edge(u, v, 1, -k);
    }
  }

  for (auto v : f) {
    std::cin >> k;
    mcf.add_edge(v, dst3, k, 0);
  }

  assert(mcf.flow());
  std::cout << -mcf.cost() << "\n";
}
