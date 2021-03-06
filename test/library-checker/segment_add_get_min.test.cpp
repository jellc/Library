#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdio>

#include "src/data_structure/convex_hull_trick/Li_Chao_tree.hpp"

int main() {
  using i64 = int64_t;
  int n, q;
  scanf("%d%d", &n, &q);
  workspace::Li_Chao_tree<i64> cht(-1e9, 1e9);
  while (n--) {
    i64 l, r, a, b;
    scanf("%lld%lld%lld%lld", &l, &r, &a, &b);
    cht.insert(a, b, l, r);
  }
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t) {
      int p;
      scanf("%d", &p);
      i64 ans = cht.eval(p);
      if (ans == cht.infinity)
        puts("INFINITY");
      else
        printf("%lld\n", ans);
    } else {
      i64 l, r, a, b;
      scanf("%lld%lld%lld%lld", &l, &r, &a, &b);
      cht.insert(a, b, l, r);
    }
  }
}
