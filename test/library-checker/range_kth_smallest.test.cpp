#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include <cstdio>

#include "data_structure/Mo.hpp"
#include "utils/coordinate_compression.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (int &e : a) scanf("%d", &e);
  coordinate_compression ccmp(a);
  int bsize = std::sqrt(ccmp.count()) + 1;
  std::vector<int> cnt(ccmp.count()), bcnt(bsize);
  auto add = [&](int i) {
    int now = ccmp[i];
    cnt[now]++;
    bcnt[now / bsize]++;
  };
  auto del = [&](int i) {
    int now = ccmp[i];
    cnt[now]--;
    bcnt[now / bsize]--;
  };
  workspace::Mo mo(add, del);
  std::vector<int> k(q), ans(q);
  for (int l, r, i = 0; i < q; i++) {
    scanf("%d%d%d", &l, &r, &k[i]);
    mo.set(l, r);
  }
  mo.make();
  for (int t = 0; t < q; t++) {
    int qid = mo.process();
    for (int i = 0, j = 0, nk = k[qid]; i < bsize; i++, j += bsize) {
      if (bcnt[i] > nk) {
        int h;
        for (h = j; nk >= cnt[h]; h++) {
          nk -= cnt[h];
        }
        ans[qid] = ccmp.value(h);
        break;
      } else {
        nk -= bcnt[i];
      }
    }
  }
  for (int e : ans) printf("%d\n", e);
}
