#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdio>

#include "src/algebra/modint.hpp"
#include "src/data_structure/segment_tree/basic.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;
  int n, q;
  scanf("%d%d", &n, &q);
  struct mono {
    mint c = 1, d;
    mono operator+(const mono& rhs) const {
      return {rhs.c * c, rhs.c * d + rhs.d};
    }
    mint eval(mint x) const { return c * x + d; }
  };
  segment_tree<mono> seg(n);
  for (auto& [a, b] : seg) scanf("%d%d", &a, &b);
  for (int t, a, b, c; q--;) {
    scanf("%d%d%d%d", &t, &a, &b, &c);
    if (t) {
      printf("%d\n", seg.fold(a, b).eval(c));
    } else {
      seg[a] = {b, c};
    }
  }
}
