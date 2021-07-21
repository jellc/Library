#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <cstdio>
#include <vector>

#include "src/algebra/modint.hpp"
#include "src/data_structure/segment_tree/lazy.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;
  struct endo {
    mint a = 1, b;
    endo operator*(endo rhs) const { return {a * rhs.a, b * rhs.a + rhs.b}; }
  };
  struct mono {
    mint v, c;
    mono operator+(mono rhs) const { return {v + rhs.v, c + rhs.c}; }
    mono operator*(endo rhs) const { return {v * rhs.a + c * rhs.b, c}; }
  };

  int n, q;
  scanf("%d%d", &n, &q);
  lazy_segment_tree<mono, endo> seg(n);
  for (int i = 0, v; i < n; i++) {
    scanf("%d", &v);
    seg[i] = {v, 1};
  }
  for (int t, l, r, a, b; q--;) {
    scanf("%d%d%d", &t, &l, &r);
    if (t) {
      printf("%d\n", seg.fold(l, r).v);
    } else {
      scanf("%d%d", &a, &b);
      seg.update(l, r, {a, b});
    }
  }
}
