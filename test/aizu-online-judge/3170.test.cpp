#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/3170"

#include <algorithm>
#include <cstdio>

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
    i64 min, max, add;
    std::vector<i64> v;
  };

  constexpr auto inf = __INT64_MAX__;

  buckets b(
      begin(a), end(a),
      [](auto l, auto r) {
        data d;
        d.add = 0;
        d.min = inf;
        d.max = -inf;
        d.v = std::vector(l, r);
        std::sort(d.v.begin(), d.v.end());
        return d;
      },
      [](const auto& d, auto l, auto r) {
        while (l != r) {
          *l = std::min(d.min, std::max(d.max, *l)) + d.add;
          ++l;
        }
      },
      128);

  for (int t, l, r; q--;) {
    i64 x, y;
    scanf("%d%d%d%lld", &t, &l, &r, &x);
    --l;

    switch (--t) {
      case 0:
        b(l, r, [&](auto& d) {
          auto c = x - d.add;
          if (d.min < c) return;
          d.min = c;
          if (d.max > c) d.max = c;
        });
        break;

      case 1:
        b(l, r, [&](auto& d) {
          auto c = x - d.add;
          if (d.max > c) return;
          d.max = c;
          if (d.min < c) d.min = c;
        });
        break;

      case 2:
        b(l, r, [&](auto& d) { d.add += x; });
        break;

      case 3:
        scanf("%lld", &y);
        int num = 0;
        b(l, r, [&](const auto& d) {
          int sign = 1;
          for (auto z : {x - 1 - d.add, y - d.add}) {
            sign *= -1;
            if (z < d.max) continue;
            if (z < d.min)
              num += sign * (std::upper_bound(d.v.begin(), d.v.end(), z) -
                             d.v.begin());
            else
              num += sign * (int)d.v.size();
          }
        });
        printf("%d\n", num);
        break;
    }
  }
}
