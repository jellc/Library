#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

#include <iostream>

#include "src/graph/directed/flow/min_cost_flow.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n, m;
  std::cin >> n >> m;
  workspace::min_cost_flow<int64_t, __int128_t> mcf(n);
  for (int i = 0; i < n; ++i) {
    int b;
    std::cin >> b;
    mcf.supply(i, b);
  }
  std::vector<std::vector<int>> ids(n);
  for (int i = 0; i < m; ++i) {
    int s, t, l, u, c;
    std::cin >> s >> t >> l >> u >> c;
    mcf.add_edge(s, t, l, u, c);
    ids[s].emplace_back(i);
  }
  if (mcf.run()) {
    std::cout << mcf.cost() << "\n";
    for (const auto &p : mcf.potential()) std::cout << p << "\n";
    std::vector<int> fs(m);
    for (int v = 0; v < n; ++v) {
      auto iter = ids[v].begin();
      for (const auto &e : mcf[v]) fs[*iter++] = e.flow;
    }
    for (const auto &f : fs) std::cout << f << "\n";
  } else
    std::cout << "infeasible\n";
}
