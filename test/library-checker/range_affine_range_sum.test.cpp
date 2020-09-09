#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <cstdio>
#include <vector>

#include "data_structure/segment_tree/lazy.hpp"
#include "modulus/modint.hpp"

int main() {
  using mint = modint<998244353>;
  struct endo {
    mint a = 1, b;
    endo operator*(endo rhs) { return {a * rhs.a, b * rhs.a + rhs.b}; }
  };
  struct mono {
    mint v, c;
    mono operator+(mono rhs) { return {v + rhs.v, c + rhs.c}; }
    mono operator*(endo rhs) { return {v * rhs.a + c * rhs.b, c}; }
  };

  int n, q;
  scanf("%d%d", &n, &q);
  lazy_segment_tree<mono, endo> seg;
  {
    std::vector<mono> a(n);
    for (auto &[v, c] : a) {
      int _v;
      scanf("%d", &_v);
      v = _v;
      c = 1;
    }
    seg = a;
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
