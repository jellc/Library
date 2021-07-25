#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include <cstdint>
#include <cstdio>

#include "src/graph/directed/flow/min_cost_flow.hpp"

int main() {
  using namespace workspace;

  size_t n;
  scanf("%zu", &n);
  min_cost_flow<int, int64_t> mcf(n * 2);
  for (size_t i = 0; i < n; i++) {
    mcf.supply(i);
    mcf.demand(i + n);
    for (size_t j = 0; j < n; j++) {
      int a;
      scanf("%d", &a);
      mcf.add_edge(i, j + n, 1, a);
    }
  }
  assert(mcf.run());
  printf("%lld\n", mcf.cost());
  for (size_t i = 0; i < n; i++) {
    for (auto &e : mcf[i]) {
      if (!e.capacity) printf("%zu ", e.head - n);
    }
  }
  puts("");
}
