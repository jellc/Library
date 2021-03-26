#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <cstdio>

#include "src/data_structure/Mo.hpp"
#include "src/data_structure/coordinate_compression.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<size_t> a(n);
  for (auto &e : a) scanf("%d", &e);
  workspace::coordinate_compression<size_t> ccmp(a.begin(), a.end());
  ccmp.make();
  a = ccmp.compress(a.begin(), a.end());
  int bsize = std::sqrt(ccmp.size()) + 1;
  std::vector<int> cnt(ccmp.size()), bcnt(bsize);
  auto add = [&](int i) {
    int now = a[i];
    cnt[now]++;
    bcnt[now / bsize]++;
  };
  auto del = [&](int i) {
    int now = a[i];
    cnt[now]--;
    bcnt[now / bsize]--;
  };
  workspace::Mo mo(add, del);
  std::vector<int> k(q), ans(q);
  for (int l, r, i = 0; i < q; i++) {
    scanf("%d%d%d", &l, &r, &k[i]);
    mo.add_query(l, r);
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
        ans[qid] = ccmp[h];
        break;
      } else {
        nk -= bcnt[i];
      }
    }
  }
  for (int e : ans) printf("%d\n", e);
}
