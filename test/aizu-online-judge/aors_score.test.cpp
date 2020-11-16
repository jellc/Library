#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017"
#include <iostream>

#include "../../src/graph/directed/flow/min_cost_flow.hpp"
using namespace workspace;

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;
  const int total = n + m + 3;
  const int dst = total - 1;
  const int dst2 = total - 2;
  const int dst3 = total - 3;
  min_cost_flow<int, int> mcf(total);
  mcf.supply(dst, -n);
  mcf.add_edge(dst2, dst, n, 0);
  mcf.add_edge(dst3, dst, n - k, 0);
  for (int i = 0; i < n; ++i) {
    mcf.supply(i, 1);
    std::cin >> k;
    mcf.add_edge(i, dst2, 1, -k);
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      std::cin >> k;
      mcf.add_edge(i, j + n, 1, -k);
    }
  }
  for (int j = 0; j < m; j++) {
    std::cin >> k;
    mcf.add_edge(j + n, dst3, k, 0);
  }
  std::cout << -mcf.optimal() << "\n";
}
