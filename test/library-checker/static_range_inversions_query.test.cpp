#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <cstdio>

#include "src/data_structure/Mo.hpp"
#include "src/data_structure/compression.hpp"
#include "src/data_structure/segment_tree/basic.hpp"

int main() {
  using i64 = long long;
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<size_t> a(n);
  for (auto &e : a) scanf("%d", &e);
  workspace::compression ccmp(begin(a), end(a));
  ccmp.make();
  for (auto &&x : a) {
    x = ccmp.lower_bound(x);
  }
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
    mo.insert(l, r);
  }
  mo.make();
  std::vector<i64> ans(q);
  for (auto &&e : mo) {
    ans[e.index] = invs;
  }
  for (i64 x : ans) printf("%lld\n", x);
}
