#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <algorithm>
#include <cstdio>

#include "src/data_structure/buckets.hpp"

int main() {
  using namespace workspace;

  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (auto&& x : a) {
    scanf("%d", &x);
  }

  buckets b(
      begin(a), end(a), [](auto l, auto r) { return *std::min_element(l, r); },
      [](const auto& d, auto l, auto r) {});

  for (int l, r; q--;) {
    scanf("%d%d", &l, &r);
    int ans = __INT_MAX__;
    b(l, r, [&](auto x) {
      if (ans > x) ans = x;
    });
    printf("%d\n", ans);
  }
}
