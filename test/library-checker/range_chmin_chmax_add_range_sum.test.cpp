#define PROBLEM \
  "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include <algorithm>
#include <cstdio>
#include <map>

#include "src/data_structure/buckets.hpp"

int main() {
  using namespace workspace;
  using i64 = int64_t;

  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<i64> a(n);
  for (auto&& x : a) {
    scanf("%lld", &x);
  }

  struct data {
    i64 min, max, add, sum, num;
    std::map<i64, i64> map;
  };

  constexpr auto inf = 1'000'000'000'000;

  buckets b(
      begin(a), end(a),
      [](auto l, auto r) {
        data d;
        d.add = 0;
        d.sum = 0;
        d.min = inf;
        d.max = -inf;
        d.num = 0;
        while (l != r) {
          d.sum += *l;
          d.map[*l] += 1;
          d.num += 1;
          ++l;
        }
        return d;
      },
      [](const auto& d, auto l, auto r) {
        while (l != r) {
          *l = std::min(d.min, std::max(d.max, *l)) + d.add;
          ++l;
        }
      });

  for (int t, l, r; q--;) {
    scanf("%d%d%d", &t, &l, &r);
    if (t == 3) {
      i64 sum = 0;
      b(l, r, [&](const auto& x) { sum += x.sum; });
      printf("%lld\n", sum);
      continue;
    }

    i64 a;
    scanf("%lld", &a);
    switch (t) {
      case 0:
        b(l, r, [&](auto& d) {
          auto c = a - d.add;
          if (d.min < c) return;
          d.min = c;
          if (d.max > c) d.max = c;
          while (d.map.rbegin()->first > c) {
            auto [v, k] = *prev(d.map.end());
            d.map.erase(prev(d.map.end()));
            d.map[c] += k;
            d.sum += (c - v) * k;
          }
        });
        break;

      case 1:
        b(l, r, [&](auto& d) {
          auto c = a - d.add;
          if (d.max > c) return;
          d.max = c;
          if (d.min < c) d.min = c;
          while (d.map.begin()->first < c) {
            auto [v, k] = *d.map.begin();
            d.map.erase(d.map.begin());
            d.map[c] += k;
            d.sum += (c - v) * k;
          }
        });
        break;

      case 2:
        b(l, r, [&](auto& x) {
          x.sum += x.num * a;
          x.add += a;
        });
        break;
    }
  }
}
