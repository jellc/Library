#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/search/titles/2815"
#include "graph/directed/flow/min_cost_flow.hpp"
#include "utils/read.hpp"

using namespace workspace;

int main() {
  const int n = read(), m = read(), k = read();
  const int total = n + m + 2;
  const int dst = total - 1;
  const int dst2 = total - 2;
  min_cost_flow<int, int> mcf(total);
  mcf.supply(dst, k - n);
  mcf.supply(dst2, -k);
  for (int i = 0; i < n; ++i) {
    mcf.supply(i, 1);
    mcf.add_edge(i, dst2, 1, -read<int>());
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      mcf.add_edge(i, j + n, 1, -read<int>());
    }
  }
  for (int j = 0; j < m; j++) {
    mcf.add_edge(j + n, dst, read<int>(), 0);
  }
  std::cout << -mcf.optimal() << "\n";
}
