#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <cstdio>

#include "src/data_structure/Mo.hpp"
#include "src/data_structure/coordinate_compression.hpp"
#include "src/data_structure/segment_tree/basic.hpp"

int main() {
  using i64 = int64_t;
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<size_t> a(n);
  for (auto &e : a) scanf("%d", &e);
  workspace::coordinate_compression<int> ccmp(a.begin(), a.end());
  ccmp.make();
  a = ccmp.compress(a.begin(), a.end());
  std::vector<int> cnt(ccmp.size());
  workspace::segment_tree<int> seg(n);
  i64 invs = 0;
  auto addl = [&](int i) -> auto {
    i = a[i];
    invs += seg.fold(0, i);
    seg[i]++;
  };
  auto addr = [&](int i) -> auto {
    i = a[i];
    invs += seg.fold(i + 1, n);
    seg[i]++;
  };
  auto dell = [&](int i) -> auto {
    i = a[i];
    invs -= seg.fold(0, i);
    seg[i]--;
  };
  auto delr = [&](int i) -> auto {
    i = a[i];
    invs -= seg.fold(i + 1, n);
    seg[i]--;
  };
  workspace::Mo mo(addl, dell, addr, delr);
  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    mo.add_query(l, r);
  }
  mo.make();
  std::vector<i64> ans(q);
  for (int i = 0; i < q; i++) {
    int id = mo.process();
    ans[id] = invs;
  }
  for (i64 x : ans) printf("%lld\n", x);
}
