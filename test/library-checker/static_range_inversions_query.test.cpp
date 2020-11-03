#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include <cstdio>

#include "data_structure/Mo.hpp"
#include "data_structure/segment_tree/basic.hpp"
#include "utils/coordinate_compression.hpp"
using i64 = int64_t;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (int &x : a) scanf("%d", &x);
  coordinate_compression ccmp(a);
  std::vector<int> cnt(ccmp.count());
  segment_tree<int> seg(n);
  i64 invs = 0;
  auto addl = [&](int i) -> auto {
    i = ccmp[i];
    invs += seg.fold(0, i);
    seg[i]++;
  };
  auto addr = [&](int i) -> auto {
    i = ccmp[i];
    invs += seg.fold(i + 1, n);
    seg[i]++;
  };
  auto dell = [&](int i) -> auto {
    i = ccmp[i];
    invs -= seg.fold(0, i);
    seg[i]--;
  };
  auto delr = [&](int i) -> auto {
    i = ccmp[i];
    invs -= seg.fold(i + 1, n);
    seg[i]--;
  };
  workspace::Mo mo(addl, dell, addr, delr);
  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    mo.set(l, r);
  }
  mo.make();
  std::vector<i64> ans(q);
  for (int i = 0; i < q; i++) {
    int id = mo.process();
    ans[id] = invs;
  }
  for (i64 x : ans) printf("%lld\n", x);
}
