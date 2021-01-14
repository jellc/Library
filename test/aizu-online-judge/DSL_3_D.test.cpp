#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_D"

#include <cstdio>

#include "src/data_structure/disjoint_sparse_table.hpp"

int main() {
  using namespace workspace;

  struct min {
    int _v;
    min(int _v) : _v(_v) {}
    min operator+(min r) { return {_v < r._v ? _v : r._v}; }
  };

  int n, k, a[1 << 20];
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  disjoint_sparse_table<min> dst(a, a + n);
  for (int i = k; i < n; ++i) printf("%d ", dst.fold(i - k, i)._v);
  printf("%d\n", dst.fold(n - k, n)._v);
}
