#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <cstdio>

#include "src/data_structure/segment_tree/basic.hpp"

int main() {
  using namespace workspace;
  int n, q;
  scanf("%d%d", &n, &q);
  segment_tree<long long> seg(n);
  for (auto &&e : seg) scanf("%lld", &e);
  for (int t, a, b; q--;) {
    scanf("%d%d%d", &t, &a, &b);
    if (t)
      printf("%lld\n", seg.fold(a, b));
    else
      seg[a] += b;
  }
}
