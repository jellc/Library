#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include <cstdint>
#include <cstdio>

#include "src/graph/directed/flow/min_cost_flow.hpp"

int main() {
  using namespace workspace;

  int n;
  scanf("%d", &n);
  min_cost_flow<int, int64_t> mcf(n * 2);
  for (int i = 0; i < n; i++) {
    mcf.supply(i);
    mcf.demand(i + n);
    for (int j = 0; j < n; j++) {
      int a;
      scanf("%d", &a);
      mcf.add_edge(i, j + n, 1, a);
    }
  }
  assert(mcf.flow());
  printf("%lld\n", mcf.cost());
  for (int i = 0; i < n; i++) {
    for (auto &e : mcf[i]) {
      if (!e.cap) printf("%d ", e.dst - n);
    }
  }
  puts("");
}
