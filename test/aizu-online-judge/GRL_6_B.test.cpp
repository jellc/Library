#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"

#include <cstdio>

#include "src/graph/directed/flow/min_cost_flow.hpp"

int main() {
  int n, m, f;
  scanf("%d%d%d", &n, &m, &f);
  workspace::min_cost_flow<int> mcf(n);
  mcf.supply(0, f);
  mcf.demand(n - 1, f);
  while (m--) {
    int u, v, c, d;
    scanf("%d%d%d%d", &u, &v, &c, &d);
    mcf.add_edge(u, v, c, d);
  }
  if (mcf.run()) {
    printf("%d\n", mcf.cost());
  } else
    puts("-1");
}
